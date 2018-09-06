#ifndef OSGEARTH_DRAGGERS_H
#define OSGEARTH_DRAGGERS_H

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>
#include <VBF_3DMap/VBF_Terrain/MapNodeObserver.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableShape.h>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>
#include <VBF_Display/VBF_Dragger/Projector.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Terrain.h>

class CVBFO_SGNodeMap;
class CVBF_Terrain;

namespace osgEarth
{
    class OSGEARTH_EXPORT Dragger : public osg::MatrixTransform, public MapNodeObserver
    {
    public:
		// 回调函数，在位置改变时被激发
        struct PositionChangedCallback : public ::CVBF_Referenced
        {
        public:
            virtual void onPositionChanged(const Dragger* sender, const osgEarth::GeoPoint& position) {};
            virtual ~PositionChangedCallback() { }
        };

        typedef std::list< ref_ptr<PositionChangedCallback> > PositionChangedCallbackList;

        enum DragMode
        {
          DRAGMODE_HORIZONTAL,
          DRAGMODE_VERTICAL
        };

        Dragger( CVBFO_SGNodeMap* mapNode, int modKeyMask=0, const DragMode& defaultMode=DRAGMODE_HORIZONTAL );

        virtual ~Dragger();

		// 是否在拖动
        bool getDragging() const;

		// 鼠标是否在目标上面
        bool getHovered() const;

        const osgEarth::GeoPoint& getPosition() const;

        void setPosition( const osgEarth::GeoPoint& position, bool fireEvents=true);

        void setModKeyMask(int mask) { _modKeyMask = mask; }

        int getModKeyMask() const { return _modKeyMask; }

        void setDefaultDragMode(const DragMode& mode) { _defaultMode = mode; }

        DragMode& getDefaultDragMode() { return _defaultMode; }

        void setVerticalMinimum(double min) { _verticalMinimum = min; }

        double getVerticalMinimim() const { return _verticalMinimum; }


        void updateTransform(osg::IVBF_SGNode* patch = 0);

        virtual void enter();

        virtual void leave();

        virtual void setColor( const osg::Vec4f& color ) =0;

        virtual void setPickColor( const osg::Vec4f& color ) =0;

        void addPositionChangedCallback( PositionChangedCallback* callback );

        void removePositionChangedCallback( PositionChangedCallback* callback );

        virtual void traverse(osg::NodeVisitor& nv);        

        virtual void reclamp( const CVBF_TileKey& key, osg::IVBF_SGNode* tile, const CVBF_Terrain* terrain );


    public: // MapNodeObserver

        virtual void setMapNode( CVBFO_SGNodeMap* mapNode );

        virtual CVBFO_SGNodeMap* GetMapNode() { return _mapNode.get(); }


    protected:
        virtual bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);
        void setHover( bool hovered);
        void firePositionChanged();

        ref_ptr< IVBF_TerrainCallback > _autoClampCallback;

        observer_ptr< CVBFO_SGNodeMap > _mapNode;
        osgEarth::GeoPoint _position;
        bool _dragging;
        bool _hovered;
        PositionChangedCallbackList _callbacks;

        ref_ptr<  osgManipulator::LineProjector >  _projector;
        osgManipulator::PointerInfo  _pointer;
        osg::Vec3d _startProjectedPoint;
        int _modKeyMask;
        DragMode _defaultMode;

        bool _elevationDragging;
        double _verticalMinimum;
    };


	class OSGEARTH_EXPORT SphereDragger : public Dragger
    {
    public:
        SphereDragger(CVBFO_SGNodeMap* mapNode);
        virtual ~SphereDragger() { }

        const osg::Vec4f& getColor() const;

        void setColor(const osg::Vec4f& color);

        const osg::Vec4f& getPickColor() const;

        void setPickColor(const osg::Vec4f& pickColor);

        float getSize() const;
        void setSize(float size);

        virtual void enter();

        virtual void leave();

    protected:

        void updateColor();

        osg::IVBF_SGNodeGroupTransformMatrix* _scaler;
        osg::ShapeDrawable* _shapeDrawable;
        osg::Vec4f _pickColor;
        osg::Vec4f _color;
        float _size;
    };


} // namespace osgEarth

#endif // OSGEARTH_DRAGGERS_H
