#ifndef OSGEARTH_ANNO_ORTHO_NODE_H
#define OSGEARTH_ANNO_ORTHO_NODE_H 1

#include <VBF_3DMap/VBF_Annotation/AnnotationNode.h>
#include <VBF_3DMap/VBF_Annotation/Decluttering.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>
#include <VBF_3DMap/VBF_Terrain/CullingUtils.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformAuto.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>

namespace osgEarth { namespace Annotation
{	
    using namespace osgEarth;

	// 正射节点：在屏幕空间绘制的节点，不要直接使用该类，应使用其子类（LabelNode、PlaceNode）
    class OSGEARTHANNO_EXPORT OrthoNode : public PositionedAnnotationNode, 
                                          public SupportsDecluttering
    {
    public:
        META_AnnotationNode( VBF_Annotation, OrthoNode );

        OrthoNode();

		// 位置要变换到mapNode中
        OrthoNode( CVBFO_SGNodeMap* mapNode, const GeoPoint& position );

		// Attaches a child node to the transforms. Use this instead of addChild.
        virtual osg::IVBF_SGNodeGroup* getAttachPoint() { return _attachPoint; }

		// 设置/获取位置
        virtual bool setPosition( const GeoPoint& pos );
        virtual GeoPoint getPosition() const; // (in map coordinates) 

    public:
        /**
         * Sets a "local offset" position - for an ECEF map, this is an offset in 
         * the local tangent plane of the node that is applied to the geometry.
         */
        void setLocalOffset( const osg::Vec3d& offset );
        const osg::Vec3d& getLocalOffset() const;

        // 是否启用水平自动筛选
        void setHorizonCulling( bool value );
        bool getHorizonCulling() const;

        // 开启/关闭基于射线碰撞的遮挡裁剪
        bool getOcclusionCulling() const;
        void setOcclusionCulling( bool value );

    public: // AnnotationNode

        virtual void applyStyle(const Style& style);

    public: // MapNodeObserver

        virtual void setMapNode( CVBFO_SGNodeMap* mapNode );

    public: // osg::Node

        virtual void traverse( osg::NodeVisitor& nv );

        virtual osg::BoundingSphere computeBound() const;

    protected:
        virtual ~OrthoNode() { }

    private:
        osg::IVBF_SGNodeGroupSwitch*        _switch;
        osg::IVBF_SGNodeGroup*              _oq;
        osg::AutoTransform*                 _autoxform;
        osg::IVBF_SGNodeGroupTransformMatrix*   _matxform;
        osg::IVBF_SGNodeGroup*                  _attachPoint;
        bool                           _horizonCulling;
        bool                           _occlusionCulling;
        GeoPoint                       _mapPosition;
        osg::Vec3d                     _localOffset;

        ref_ptr< CullNodeByHorizon > _horizonCuller; // 地平线裁剪
        ref_ptr< OcclusionCullingCallback > _occlusionCuller;

        void init();

        osg::Vec3d adjustOcclusionCullingPoint( const osg::Vec3d& world );

        // required by META_Node, but this object is not cloneable
        OrthoNode( const OrthoNode& rhs, const osg::CopyOp& op =osg::CopyOp::DEEP_COPY_ALL ) { }

        // autoclamping.
        virtual void reclamp( const CVBF_TileKey& key, osg::IVBF_SGNode* tile, const CVBF_Terrain* );

        bool updateTransforms( const GeoPoint& mappos, osg::IVBF_SGNode* patch =0L );
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTH_ANNO_LOCALIZED_NODE_H
