#ifndef OSGEARTHSYMBOLOGY_INSTANCE_SYMBOL_H
#define OSGEARTHSYMBOLOGY_INSTANCE_SYMBOL_H 1

#include <climits>

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Symbology/VBF_Symbol.h>
#include <VBF_3DMap/VBF_Symbology/Expression.h>
#include <Types/Vec3f>

namespace osgEarth { namespace Symbology
{
    class InstanceResource;
    class IconSymbol;
    class ModelSymbol;

    // 使用一个外部资源作为点符号，如一个图标或一个模型
    class OSGEARTHSYMBOLOGY_EXPORT InstanceSymbol : public Symbol
    {
    public:
        // 控制放置的位置
        enum Placement
        {
            /** Places one instance at the centroid of the feature. */
            PLACEMENT_CENTROID,

            /** Places an instance at each feature point. */
            PLACEMENT_VERTEX,

            /** Places instances at regular intervals within/along the feature geometry,
                according to density. */
            PLACEMENT_INTERVAL,

            /** Scatter instances randomly within/along feature, according to density. */
            PLACEMENT_RANDOM
        };

    public:
        virtual ~InstanceSymbol();

        /** URI of the instance to use for substitution. */
        CVBF_Optional<StringExpression>& url() { return _url; }
        const CVBF_Optional<StringExpression>& url() const { return _url; }

        /** Name of the resource library to use with this symbol (optional) */
        CVBF_Optional<StringExpression>& libraryName() { return _libraryName; }
        const CVBF_Optional<StringExpression>& libraryName() const { return _libraryName; }   

        /** How to map feature geometry to instance placement. (default is PLACEMENT_CENTROID) */
        CVBF_Optional<Placement>& placement() { return _placement; }
        const CVBF_Optional<Placement>& placement() const { return _placement; }

        /** For PLACEMENT_RANDOM/INTERVAL, the scattering density in instances per sqkm */
        CVBF_Optional<float>& density() { return _density; }
        const CVBF_Optional<float>& density() const { return _density; }

        /** Model instance scale factor */
        CVBF_Optional<NumericExpression>& scale() { return _scale; }
        const CVBF_Optional<NumericExpression>& scale() const { return _scale; }

        /** Seeding value for the randomizer */
        CVBF_Optional<unsigned>& randomSeed() { return _randomSeed; }
        const CVBF_Optional<unsigned>& randomSeed() const { return _randomSeed; }

        /** URI alias map for embedded resources */
        CVBF_Optional<URIAliasMap>& uriAliasMap() { return _uriAliasMap; }
        const CVBF_Optional<URIAliasMap>& uriAliasMap() const { return _uriAliasMap; }

    public: // conversions to built-in base classes, for convenience.

        const IconSymbol* asIcon() const;
        const ModelSymbol* asModel() const;

    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );

    public: // internal
        /** Creates a new (empty) resource appropriate for this symbol */
        virtual InstanceResource* createResource() const =0;

    protected:
        InstanceSymbol( const CVBF_Config& conf =CVBF_Config() );

    protected:
        CVBF_Optional<StringExpression>   _url;
        CVBF_Optional<StringExpression>   _libraryName;
        CVBF_Optional<NumericExpression>  _scale;
        CVBF_Optional<Placement>          _placement;
        CVBF_Optional<float>              _density;
        CVBF_Optional<unsigned>           _randomSeed;
        CVBF_Optional<URIAliasMap>        _uriAliasMap;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_MARKER_SYMBOL_H
