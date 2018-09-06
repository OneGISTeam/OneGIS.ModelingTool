#ifndef OSGEARTH_ANNOTATION_LABEL_NODE_H
#define OSGEARTH_ANNOTATION_LABEL_NODE_H 1

#include <VBF_3DMap/VBF_Annotation/OrthoNode.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>

namespace osgEarth { namespace Annotation
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;
  
	// ����ע�ǽڵ�
    class OSGEARTHANNO_EXPORT LabelNode : public OrthoNode
    {
    public:
        META_AnnotationNode( VBF_Annotation, LabelNode );

		// ע�ǵ�λ�ã��߶ȣ��������mapNode��
        LabelNode( CVBFO_SGNodeMap* mapNode, const GeoPoint& pos, const std::string& text, const Style& style =Style() );
        LabelNode( CVBFO_SGNodeMap* mapNode, const GeoPoint& pos, const std::string& text, const TextSymbol* symbol );

		// The text string must be in the text symbol
        LabelNode( CVBFO_SGNodeMap* mapNode, const GeoPoint& position, const Style& style );
        LabelNode( CVBFO_SGNodeMap* mapNode, const Style& style );

        LabelNode( const std::string& text ="", const Style& style =Style() );
        LabelNode( CVBFO_SGNodeMap* mapNode, const CVBF_Config& conf, const osgDB::Options* dbOptions );

        virtual ~LabelNode() { }

		// ����/��ȡע�ǵ�����
        void setText( const std::string& text );
        const std::string& text() const { return _text; }

		// ����/��ȡע�ǵ�Style
        const Style& style() const { return _style; }
        void setStyle( const Style& style );

    public: // OrthoNode override

        virtual void setAnnotationData( AnnotationData* data );
        virtual void setDynamic( bool value );

        virtual CVBF_Config getConfig() const;

    protected:
        void init(const Style& style);

        std::string              _text;
        Style                    _style;
        ref_ptr<osg::IVBF_SGNodeGeometry> _geode;

		// ��������
        LabelNode( const LabelNode& rhs, const osg::CopyOp& op =osg::CopyOp::DEEP_COPY_ALL ) { }
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTH_ANNOTATION_LABEL_NODE_H
