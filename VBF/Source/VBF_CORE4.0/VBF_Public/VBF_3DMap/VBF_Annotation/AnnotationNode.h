#ifndef OSGEARTH_ANNO_ANNOTATION_NODE_H
#define OSGEARTH_ANNO_ANNOTATION_NODE_H 1

#include <VBF_3DMap/VBF_Annotation/Common>
#include <VBF_3DMap/VBF_Annotation/AnnotationData.h>
#include <VBF_3DMap/VBF_Annotation/Decoration.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Terrain/MapNodeObserver.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Terrain.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupSwitch.h>


#define META_AnnotationNode(library,name) \
    META_Node(library,name) \
    virtual bool accept(Decoration* ds, bool enable) { return ds->apply(*this, enable); }

#define META_AnnotationNodeAbstract(library,name) \
    virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
    virtual const char* className() const { return #name; } \
    virtual const char* libraryName() const { return #library; } \
    virtual void accept(osg::NodeVisitor& nv) { if (nv.validNodeMask(*this)) { nv.pushOntoNodePath(this); nv.apply(*this); nv.popFromNodePath(); } } \
    virtual bool accept(Decoration* ds, bool enable) { return ds->apply(*this, enable); }


class CVBFO_SGNodeMap;

namespace osgEarth { namespace Annotation
{	
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

	// 注记类型节点的基类
    class OSGEARTHANNO_EXPORT AnnotationNode : public osg::CVBF_SGNodeGroup,
                                               public MapNodeObserver
    {
    public:
        META_AnnotationNode(VBF_Annotation, AnnotationNode);

 		// 该注记节点关联的注记数据
        virtual void setAnnotationData( AnnotationData* data );
        AnnotationData* getAnnotationData() const { return _annoData.get(); }

		// 设置节点是否是动态的
        virtual void setDynamic( bool value );

        // 获取注记节点的关联节点
        virtual osg::IVBF_SGNodeGroup* getChildAttachPoint();

		// 从配置文件串行化
        virtual CVBF_Config getConfig() const { return CVBF_Config(); }

    public: // 装饰

		// 给注记节点添加/移除装饰
        void installDecoration( const std::string& name, Decoration* ds );
        void uninstallDecoration( const std::string& name );

		// 获取当前的装饰
        const std::string& getDecoration() const;

		// 激活一个已经添加的装饰
        virtual void setDecoration( const std::string& name );

		// 清空所有的装饰
        virtual void clearDecoration();

		// 判断是否添加了指定名字的装饰
        bool hasDecoration( const std::string& name ) const;

    public: // MapNodeObserver

        virtual void setMapNode( CVBFO_SGNodeMap* mapNode );

        CVBFO_SGNodeMap* GetMapNode() { return _mapNode.get(); }
        const CVBFO_SGNodeMap* GetMapNode() const { return _mapNode.get(); }

    public:
        virtual void setStyle(const Style& style) { }
        virtual const Style& getStyle() const { return s_emptyStyle; }
    protected:

        ref_ptr<AnnotationData> _annoData;
        bool                         _dynamic;
        bool                         _autoclamp;
        bool                         _depthAdj;
        ref_ptr<const AltitudeSymbol> _altitude;

        typedef std::map<std::string, ref_ptr<Decoration> > DecorationMap;
        DecorationMap _dsMap;
        Decoration*   _activeDs;
        std::string   _activeDsName;

        bool supportsAutoClamping( const Style& style ) const;
        
        // 检查altitude符号（如果在用）， 必要时配置自动地图固定
        virtual void configureForAltitudeMode( const AltitudeMode& mode );

        // 设置节点的Style
        virtual void applyStyle( const Style&);
        virtual void applyGeneralSymbology(const Style&);
        
        // 设置节点在地形瓦片输入时自动re-clamp几何体（如果启用了）
        // 通常不需要直接调用该函数，它由符号自动设置，但也可以调用以重载自动设置
        virtual void setCPUAutoClamping( bool value );

        // 是否启用深度调整。通常不需要直接调用该函数，它由符号自动设置，但也可以调用以重载自动设置
        virtual void setDepthAdjustment( bool value );

        // 设置光照（仅当没有设置光照时）
        void setLightingIfNotSet( bool lighting );

        // 工具函数，给geopoint一个绝对的高度
        bool makeAbsolute( GeoPoint& mapPoint, osg::IVBF_SGNode* patch =0L ) const;

        // hidden default ctor
        AnnotationNode( CVBFO_SGNodeMap* mapNode =0L );
        AnnotationNode( CVBFO_SGNodeMap* mapNode, const CVBF_Config& conf );
        AnnotationNode(const AnnotationNode& rhs, const osg::CopyOp& op=osg::CopyOp::DEEP_COPY_ALL) { }

        ref_ptr< IVBF_TerrainCallback > _autoClampCallback;
    private:
            
        observer_ptr<CVBFO_SGNodeMap>   _mapNode;
        static Style s_emptyStyle;

    public: // 内部方法，不要直接调用
        virtual void reclamp( const CVBF_TileKey& key, osg::IVBF_SGNode* tile, const CVBF_Terrain* terrain ) { }
        virtual ~AnnotationNode();
    };

    // 可以获取/设置位置的注记节点
    class PositionedAnnotationNode : public AnnotationNode
    {
    public:
        // 设置/获取节点的坐标（地图坐标系）
        virtual bool setPosition( const GeoPoint& p ) =0;
        virtual GeoPoint getPosition() const =0;

    protected:
        PositionedAnnotationNode() : AnnotationNode() { }
        PositionedAnnotationNode(CVBFO_SGNodeMap* mapNode) : AnnotationNode( mapNode ) { }
        PositionedAnnotationNode(CVBFO_SGNodeMap* mapNode, const CVBF_Config& conf)
            : AnnotationNode( mapNode, conf ) { }        
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTH_ANNO_ANNOTATION_NODE_H
