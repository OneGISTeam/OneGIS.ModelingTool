#ifndef OSGEARTHSYMBOLOGY_INSTANCE_RESOURCE_H
#define OSGEARTHSYMBOLOGY_INSTANCE_RESOURCE_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/VBF_Resource.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolInstance.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>
#include <map>

namespace osgEarth { namespace Symbology
{
    using namespace osgEarth;

    /**
     * A resource that materializes an InstanceSymbol, which is a single-point object
     * that resolves to an osg::Node. Instances are usually used for point-model
     * substitution.
     */
    class OSGEARTHSYMBOLOGY_EXPORT InstanceResource : public Resource
    {
    public:
        virtual ~InstanceResource();
        osg::IVBF_SGNode* createNode( const osgDB::Options* dbOptions ) const;

    public:
        /** Source location of the actual data to load.  */
        CVBF_Optional<URI>& uri() { return _uri; }
        const CVBF_Optional<URI>& uri() const { return _uri; }

    public: // serialization methods

        virtual CVBF_Config getConfig() const;
        void mergeConfig( const CVBF_Config& conf );

    protected:
        InstanceResource( const CVBF_Config& conf =CVBF_Config() );

        CVBF_Optional<URI>  _uri;

        virtual osg::IVBF_SGNode* createNodeFromURI( const URI& uri, const osgDB::Options* dbOptions ) const =0;
    };


} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_MARKER_RESOURCE_H
