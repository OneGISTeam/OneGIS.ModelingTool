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

	// ע�����ͽڵ�Ļ���
    class OSGEARTHANNO_EXPORT AnnotationNode : public osg::CVBF_SGNodeGroup,
                                               public MapNodeObserver
    {
    public:
        META_AnnotationNode(VBF_Annotation, AnnotationNode);

 		// ��ע�ǽڵ������ע������
        virtual void setAnnotationData( AnnotationData* data );
        AnnotationData* getAnnotationData() const { return _annoData.get(); }

		// ���ýڵ��Ƿ��Ƕ�̬��
        virtual void setDynamic( bool value );

        // ��ȡע�ǽڵ�Ĺ����ڵ�
        virtual osg::IVBF_SGNodeGroup* getChildAttachPoint();

		// �������ļ����л�
        virtual CVBF_Config getConfig() const { return CVBF_Config(); }

    public: // װ��

		// ��ע�ǽڵ����/�Ƴ�װ��
        void installDecoration( const std::string& name, Decoration* ds );
        void uninstallDecoration( const std::string& name );

		// ��ȡ��ǰ��װ��
        const std::string& getDecoration() const;

		// ����һ���Ѿ���ӵ�װ��
        virtual void setDecoration( const std::string& name );

		// ������е�װ��
        virtual void clearDecoration();

		// �ж��Ƿ������ָ�����ֵ�װ��
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
        
        // ���altitude���ţ�������ã��� ��Ҫʱ�����Զ���ͼ�̶�
        virtual void configureForAltitudeMode( const AltitudeMode& mode );

        // ���ýڵ��Style
        virtual void applyStyle( const Style&);
        virtual void applyGeneralSymbology(const Style&);
        
        // ���ýڵ��ڵ�����Ƭ����ʱ�Զ�re-clamp�����壨��������ˣ�
        // ͨ������Ҫֱ�ӵ��øú��������ɷ����Զ����ã���Ҳ���Ե����������Զ�����
        virtual void setCPUAutoClamping( bool value );

        // �Ƿ�������ȵ�����ͨ������Ҫֱ�ӵ��øú��������ɷ����Զ����ã���Ҳ���Ե����������Զ�����
        virtual void setDepthAdjustment( bool value );

        // ���ù��գ�����û�����ù���ʱ��
        void setLightingIfNotSet( bool lighting );

        // ���ߺ�������geopointһ�����Եĸ߶�
        bool makeAbsolute( GeoPoint& mapPoint, osg::IVBF_SGNode* patch =0L ) const;

        // hidden default ctor
        AnnotationNode( CVBFO_SGNodeMap* mapNode =0L );
        AnnotationNode( CVBFO_SGNodeMap* mapNode, const CVBF_Config& conf );
        AnnotationNode(const AnnotationNode& rhs, const osg::CopyOp& op=osg::CopyOp::DEEP_COPY_ALL) { }

        ref_ptr< IVBF_TerrainCallback > _autoClampCallback;
    private:
            
        observer_ptr<CVBFO_SGNodeMap>   _mapNode;
        static Style s_emptyStyle;

    public: // �ڲ���������Ҫֱ�ӵ���
        virtual void reclamp( const CVBF_TileKey& key, osg::IVBF_SGNode* tile, const CVBF_Terrain* terrain ) { }
        virtual ~AnnotationNode();
    };

    // ���Ի�ȡ/����λ�õ�ע�ǽڵ�
    class PositionedAnnotationNode : public AnnotationNode
    {
    public:
        // ����/��ȡ�ڵ�����꣨��ͼ����ϵ��
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
