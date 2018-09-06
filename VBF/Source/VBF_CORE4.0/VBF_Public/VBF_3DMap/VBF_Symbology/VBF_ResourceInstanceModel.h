#ifndef OSGEARTHSYMBOLOGY_MODEL_RESOURCE_H
#define OSGEARTHSYMBOLOGY_MODEL_RESOURCE_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/VBF_ResourceInstance.h>

namespace osgEarth { namespace Symbology
{
    using namespace osgEarth;

    /**
     * A resource that materializes an InstanceSymbol, which is a single-point object
     * that resolves to an osg::Node. Instances are usually used for point-model
     * substitution.
     */
    class OSGEARTHSYMBOLOGY_EXPORT ModelResource : public InstanceResource
    {
    public:
        ModelResource( const CVBF_Config& conf =CVBF_Config() );
        virtual ~ModelResource();

    public: // serialization methods

        virtual CVBF_Config getConfig() const;
        void mergeConfig( const CVBF_Config& conf );

    protected: // InstanceResource

        virtual osg::IVBF_SGNode* createNodeFromURI( const URI& uri, const osgDB::Options* dbOptions ) const;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_MODEL_RESOURCE_H
