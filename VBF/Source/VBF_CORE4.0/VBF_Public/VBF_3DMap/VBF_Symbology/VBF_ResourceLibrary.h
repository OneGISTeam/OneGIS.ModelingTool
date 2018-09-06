#ifndef OSGEARTHSYMBOLOGY_RESOURCE_LIBRARY_H
#define OSGEARTHSYMBOLOGY_RESOURCE_LIBRARY_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolSkins.h>
#include <VBF_3DMap/VBF_Symbology/VBF_ResourceMarker.h>
#include <VBF_3DMap/VBF_Symbology/VBF_ResourceInstance.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_Common/VBF_Math/VBF_Random.h>
#include <map>

namespace osgEarth { namespace Symbology
{
    template<typename T> struct ResourceMap : public std::map<std::string, ref_ptr<T> > { };

    /** 
     * ResourceLibrary manages a collection of external resources that a
     * build system can use the construct geometries.
     *
     * TODO: This class PROBABLY NEEDS the ability to share a mutex with
     * whatever session is using it... like in osgGIS...
     */
    class OSGEARTHSYMBOLOGY_EXPORT ResourceLibrary : public ::CVBF_Referenced
    {
    public:
        /**
         * Creates a new resource library with a source URI. The library
         * will populate upon first use..
         */
        ResourceLibrary( const std::string& name, const URI& uri);

        /**
         * Creates a new resource library from a config.
         */
        ResourceLibrary( const CVBF_Config& conf );
        virtual ~ResourceLibrary();

        /**
         * Gets the name of the lib.
         */
        const std::string& getName() const { return m_sName; }

        //Adds/Removes a resoure to the library.
        void addResource( Resource* resource );
        void removeResource( Resource* resource );


    public: // Skin resource functions

        /**
         * Finds and returns a Skin resource by name.
         */
        SkinResource* getSkin( const std::string& name, const osgDB::Options* dbOptions =0L ) const;

        /**
         * Returns a list of all Skin resources.
         */
        void getSkins( SkinResourceVector& output, const osgDB::Options* dbOptions =0L ) const;

        /**
         * Returns a list of all Skin resources that match the criteria specified
         * in the symbol.
         */
        void getSkins( const SkinSymbol* symbol, SkinResourceVector& output, const osgDB::Options* dbOptions =0L ) const;

        /**
         * Returns a skin that matches the criteria specified in the symbol. The method
         * will randomly select a suitable skin if there are more than one match. If the
         * symbol contains a random seed, it will use that to seed the selection in order
         * to provide consistency.
         */
        SkinResource* getSkin( const SkinSymbol* symbol, CVBF_Random& prng, const osgDB::Options* dbOptions =0L ) const;


    public: // Marker resource functions (deprecated)

        /**
         * Finds and returns a marker reosurce by name.
         */
        MarkerResource* getMarker( const std::string& name, const osgDB::Options* dbOptions =0L ) const;

        /**
         * Returns a list of all marker resources in this library.
         */
        void getMarkers( MarkerResourceVector& output, const osgDB::Options* dbOptions =0L ) const;


    public: // Instance functions

        /**
         * Finds an instance-resource by name.
         */
        InstanceResource* getInstance( const std::string& name, const osgDB::Options* dbOptions =0L ) const;


    public: // serialization functions

        void mergeConfig( const CVBF_Config& conf );
        CVBF_Config getConfig() const;

    protected:
        typedef std::map< const Symbol*, CVBF_Random > RandomMap;

        CVBF_Optional<URI>                      _uri;
        std::string                        m_sName;
        bool                               _initialized;
        mutable CVBF_ReadWriteMutex  _mutex;

        ResourceMap<SkinResource>          _skins;
        ResourceMap<MarkerResource>        _markers;
        ResourceMap<InstanceResource>      _instances;

        bool matches( const SkinSymbol* symbol, SkinResource* skin ) const;

        void initialize( const osgDB::Options* options );
    };


    typedef std::map< std::string, ref_ptr<ResourceLibrary> > ResourceLibraryMap;


} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_RESOURCE_LIBRARY_H
