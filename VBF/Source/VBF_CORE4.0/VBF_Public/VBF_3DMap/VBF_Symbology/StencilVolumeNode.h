
#ifndef OSGEARTHSYMBOLOGY_STENCIL_VOLUME_NODE_H
#define OSGEARTHSYMBOLOGY_STENCIL_VOLUME_NODE_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/Geometry.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeMask.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <Types/Vec4>
#include <queue>

namespace osgEarth { namespace Symbology 
{
    class OSGEARTHSYMBOLOGY_EXPORT StencilVolumeNode : public CVBFO_SGNodeMask
    {
    public:
        /**
         * Constructs a stencil masking node.
         *
         * @param preRenderChildrenToDepthBuffer
         *     Normally, this node will render the stencil volumes first and then
         *     render the children (which will be masked by the stencil). If you need
         *     to pre-render the children to the depth buffer, set this to TRUE. You
         *     need to do this is you are creating a straight render mask.
         *
         * @param inverted
         *     Inverts the stencil buffer, masking the opposite pixels that would
         *     normally be masked.
         */
        StencilVolumeNode( bool preRenderChildrenToDepthBuffer =false, bool inverted =false );

        StencilVolumeNode( const StencilVolumeNode& rhs, const osg::CopyOp& op =osg::CopyOp::DEEP_COPY_ALL );
        virtual ~StencilVolumeNode() { }

        META_Node(osgEarth::Symbology,StencilVolumeNode);
        
        //override
        virtual void traverse( osg::NodeVisitor& nv );

    public: // props

        // sets the render bins and returns the next available bin.
        int setBaseRenderBin( int bin );

        // adds stenciling volume geometry (safely during the next update traversal, if necessary)
        void addVolumes( osg::IVBF_SGNode* node, bool onNextUpdate =true );
   
    public: // utilties

        /**
         * Generates a full screen quad that you can use to colorize 
         * stencil volumes
         */
        static osg::IVBF_SGNode* createFullScreenQuad( const osg::Vec4f& color );


    public: //osg::Group overrides

        virtual bool addChild(osg::IVBF_SGNode* child );
        virtual bool insertChild( unsigned int index, osg::IVBF_SGNode* child );
        virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove);
        virtual bool replaceChild(osg::IVBF_SGNode* origChild, osg::IVBF_SGNode* newChild );
        virtual bool setChild( unsigned  int i, osg::IVBF_SGNode* node );
        virtual osg::BoundingSphere computeBound() const;

    protected:
        void init();

        ref_ptr<osg::IVBF_SGNodeGroup> _root;
        osg::IVBF_SGNodeGroup* _stencilGroup1;
        osg::IVBF_SGNodeGroup* _stencilGroup2;
        osg::IVBF_SGNodeGroup* _depthPass;
        osg::IVBF_SGNodeGroup* _renderPass;
        bool _inverted;
        bool _preRenderChildrenToDepthBuffer;

        CVBF_Mutex _addVolumesMutex;
        std::queue< ref_ptr<osg::IVBF_SGNode> > _volumesToAdd;
        void addQueuedVolumes();
    };


} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_STENCIL_VOLUME_NODE_H

