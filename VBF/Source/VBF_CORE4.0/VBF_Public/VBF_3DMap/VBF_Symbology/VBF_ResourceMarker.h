#ifndef OSGEARTHSYMBOLOGY_MARKER_RESOURCE_H
#define OSGEARTHSYMBOLOGY_MARKER_RESOURCE_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/VBF_Resource.h>
#include <VBF_3DMap/VBF_Symbology/VBF_Symbol.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolMarker.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>
#include <map>

namespace osgEarth { namespace Symbology
{
    using namespace osgEarth;

    /**
     * Markers are used typically fro point-model subsitution and to
     * manage externally referenced (or dynamically created) scene graph nodes.
     */
    // 指向一个"marker"的资源，"marker"是用于表达一个场景对象的模型
    class OSGEARTHSYMBOLOGY_EXPORT MarkerResource : public Resource
    {
    public:
        MarkerResource( const CVBF_Config& conf =CVBF_Config() );
        virtual ~MarkerResource();

        // 创建一个表示marker的节点
        osg::IVBF_SGNode* createNode( const osgDB::Options* dbOptions ) const;

    public:
        CVBF_Optional<URI>& uri() { return _markerURI; }
        const CVBF_Optional<URI>& uri() const { return _markerURI; }

    public:
        virtual CVBF_Config getConfig() const;
        void mergeConfig( const CVBF_Config& conf );

    protected:
        CVBF_Optional<URI>  _markerURI;

        osg::IVBF_SGNode* createNodeFromURI( const URI& uri, const osgDB::Options* dbOptions ) const;
    };

    typedef std::vector< ref_ptr<MarkerResource> > MarkerResourceVector;

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_MARKER_RESOURCE_H
