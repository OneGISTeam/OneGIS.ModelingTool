#ifndef OSGEARTH_ANNO_MODEL_NODE_H
#define OSGEARTH_ANNO_MODEL_NODE_H 1

#include <VBF_3DMap/VBF_Annotation/LocalizedNode.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>
#include <VBF_3DMap/VBF_Terrain/VBF_CachePolicy.h>
#include <VBF_Engine/VBF_SGDB/ReaderWriter>

namespace osgEarth { namespace Annotation
{	
    using namespace osgEarth;
    using namespace osgEarth::Symbology;


    // ����һ����ά���Ų��������ڵ�����
    class OSGEARTHANNO_EXPORT ModelNode : public LocalizedNode
    {
    public:
        // style�������һ��InstanceSymbol (ModelSymbol��IconSymbol)
        ModelNode( CVBFO_SGNodeMap* mapNode, const Style& style, const osgDB::Options* dbOptions   =0L );

        void setStyle( const Style& style ); // �����µķ��Ų��ؽ��ڵ�
        const Style& getStyle() const { return _style; }

    public:

        // ���л�CVBF_Config����ModelNode(�ڲ�����)
        ModelNode(CVBFO_SGNodeMap* mapNode, const CVBF_Config& conf, const osgDB::Options* dbOptions );

        virtual CVBF_Config getConfig() const;

    protected: // LocalizedNode

        virtual osg::IVBF_SGNodeGroupTransformMatrix* getTransform() { return _xform.get(); }

    protected:

        Style _style;
        ref_ptr<const osgDB::Options> _dbOptions;
        ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix> _xform;

        void init();

        virtual ~ModelNode() { }
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTH_ANNO_LOCAL_GEOMETRY_NODE_H
