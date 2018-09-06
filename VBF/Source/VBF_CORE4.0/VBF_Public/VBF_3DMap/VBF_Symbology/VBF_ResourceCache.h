#ifndef OSGEARTHSYMBOLOGY_RESOURCE_CACHE_H
#define OSGEARTHSYMBOLOGY_RESOURCE_CACHE_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolSkins.h>
#include <VBF_3DMap/VBF_Symbology/VBF_ResourceMarker.h>
#include <VBF_3DMap/VBF_Symbology/VBF_ResourceInstance.h>
#include <VBF_Common/VBF_Utils/VBF_CacheLRU.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>

namespace osgEarth { namespace Symbology
{
    using namespace osgEarth;

    /**
     * Caches the runtime objects created by resources, so we can avoid creating them
     * each time they are referenced.
     *
     * This object is intended for use by a FilterContext, and therefore will only
     * run in an isolated thread. No thread-safety is required in that scenario.
     */
    class OSGEARTHSYMBOLOGY_EXPORT ResourceCache : public ::CVBF_Referenced
    {
    public:
        /** 
         * @param threadSafe Whether to protect access to the cache so that you can
         *        use it from multiple threads (default = false)
         */
        ResourceCache( const osgDB::Options* dbOptions, bool  threadSafe =false );
        virtual ~ResourceCache();

        /**
         * Fetches the StateSet implementation corresponding to a Skin.
         */
        osg::StateSet* getStateSet( SkinResource* skin );

        /**
         * Get the statistics collected from the skin cache.
         */
        const CVBF_StatsCache getSkinStats() const { return _skinCache.getStats(); }

        /**
         * Gets a node corresponding to a marker.
         * @deprecated
         */
        osg::IVBF_SGNode* getMarkerNode( MarkerResource* marker );

        /**
         * Gets a node corresponding to an instance resource.
         */
        osg::IVBF_SGNode* getInstanceNode( InstanceResource* instance );

    protected:
        ref_ptr<const osgDB::Options> _dbOptions;
        bool      _threadSafe;
        CVBF_ReadWriteMutex _mutex;

        typedef CVBF_CacheLRU<SkinResource*, ref_ptr<osg::StateSet> > SkinCache;
        SkinCache _skinCache;

        typedef CVBF_CacheLRU<MarkerResource*, ref_ptr<osg::IVBF_SGNode> > MarkerCache;
        MarkerCache _markerCache;

        typedef CVBF_CacheLRU<InstanceResource*, ref_ptr<osg::IVBF_SGNode> > InstanceCache;
        InstanceCache _instanceCache;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_RESOURCE_CACHE_H
