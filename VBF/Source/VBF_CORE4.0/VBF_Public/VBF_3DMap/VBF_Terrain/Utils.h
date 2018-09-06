
#ifndef OSGEARTH_UTILS_H
#define OSGEARTH_UTILS_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_StringUtils.h>

#include <Types/Vec3f>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNode.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransform.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformAuto.h>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_Engine/VBF_SGUtil/CullVisitor>
#include <VBF_Engine/VBF_SGUtil/RenderBin>

#include <string>
#include <list>
#include <map>

namespace osg
{
    class EllipsoidModel;
}

namespace osgEarth
{    
    //------------------------------------------------------------------------

    struct Utils
    {
		// 截取并从一个区间映射到另一个区间
        static double remap( double v, double vmin, double vmax, double r0, double r1 )
        {
            float vr = (osg::clampBetween(v, vmin, vmax)-vmin)/(vmax-vmin);
            return r0 + vr * (r1-r0);
        }
    };

    /**
     * Removes the given event handler from the view.
     * This is the equivalent of CVBF_View::removeEventHandler which is not available
     * in older versions of OSG
     */
    extern OSGEARTH_EXPORT void removeEventHandler(IVBF_View* view, osgGA::GUIEventHandler* handler);

	// 遍历节点的仿函数
    template<typename T> struct TraverseFunctor 
	{
        T* _target;
        TraverseFunctor(T* target) : _target(target) { }
        void operator()(osg::NodeVisitor& nv) { _target->T::traverse(nv); }
    };

    // utility: node that traverses another node via a functor
    template<typename T>
    struct TraverseNode : public osg::CVBF_SGNode 
	{
        TraverseFunctor<T> _tf;
        TraverseNode(TraverseFunctor<T>& tf) : _tf(tf) { }
        TraverseNode(T* target) : _tf(TraverseFunctor<T>(target)) { }
        void traverse(osg::NodeVisitor& nv) { _tf(nv); }
        osg::BoundingSphere computeBound() const { return _tf._target->getBound(); }
    };

    // utility: cull callback that traverses another node
    struct TraverseNodeCallback : public osg::NodeCallback
	{
        ref_ptr<osg::IVBF_SGNode> _node;
        TraverseNodeCallback(osg::IVBF_SGNode* node) : _node(node) { }
        void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv) 
		{
            _node->accept(*nv);
            traverse(node, nv);
        }
    };

    // a cull callback that prevents objects from being included in the near/fear clip
    // plane calculates that OSG does.
    struct DoNotComputeNearFarCullCallback : public osg::NodeCallback
    {
        void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);
    };

    /**
     * A pixel-based AutoTransform variant.
     */
    class OSGEARTH_EXPORT PixelAutoTransform : public osg::AutoTransform
    {
    public:
        PixelAutoTransform();

        /** 
         * Sets the minimim width of the object, in pixels, when the scale
         * factor is 1.0.
         */
        void setMinPixelWidthAtScaleOne( double pixels ) { _minPixels = pixels; }

        /**
         * Sets the node to use to calculate the screen size. If this is NULL,
         * it will use the size of the first child node.
         */
        void setSizingNode( osg::IVBF_SGNode* node ) { _sizingNode = node; dirty(); }

        /**
         * Forces a recalculation of the autoscale on the next traversal
         * (this usually doesn't happen unless the camera moves)
         */
        void dirty();

    public: // override
        void accept( osg::NodeVisitor& nv );

    protected:
        double _minPixels;
        bool   m_bDirty;
        observer_ptr<osg::IVBF_SGNode> _sizingNode;
    };

    /**
     * Proxy class that registers a custom render bin's prototype with the
     * rendering system
     */
    template<class T>
    struct osgEarthRegisterRenderBinProxy
    {
        osgEarthRegisterRenderBinProxy(const std::string& name)
        {
            _prototype = new T();
            osgUtil::RenderBin::addRenderBinPrototype(name, _prototype.get());
        }

        ~osgEarthRegisterRenderBinProxy()
        {
            osgUtil::RenderBin::removeRenderBinPrototype(_prototype.get());
            _prototype = 0L;
        }

        ref_ptr<T> _prototype;
    };
}

#endif // OSGEARTH_UTILS_H
