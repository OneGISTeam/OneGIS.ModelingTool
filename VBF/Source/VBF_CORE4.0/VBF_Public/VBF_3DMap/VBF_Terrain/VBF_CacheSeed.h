#ifndef OSGEARTH_CACHE_SEED_H
#define OSGEARTH_CACHE_SEED_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Map.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>
#include <VBF_3DMap/VBF_Terrain/Progress.h>

namespace osgEarth
{
	// 工具，用于生成（seeding）一个缓存
    class OSGEARTH_EXPORT CacheSeed
    {
    public:
        CacheSeed();
        virtual ~CacheSeed() { }

        // Set/Get the minimum level to seed to
        void setMinLevel(const unsigned int& minLevel) {_minLevel = minLevel;}
        unsigned int getMinLevel() const {return _minLevel;}


       // Set/Get the maximum level to seed to
        void setMaxLevel(const unsigned int& maxLevel) {_maxLevel = maxLevel;}
        unsigned int getMaxLevel() const {return _maxLevel;}

		// Adds an extent to cache
        void addExtent( const CVBF_GeoExtent& value );

		// Set progress callback for reporting which tiles are seeded
        void setProgressCallback(osgEarth::ProgressCallback* progress) { _progress = progress? progress : new ProgressCallback; }

		// Performs the seed operation
        void seed( CVBF_Map* map );

    protected:

        void incrementCompleted( unsigned int total ) const;

        unsigned int _minLevel;
        unsigned int _maxLevel;

        unsigned int _total;
        unsigned int _completed;

        ref_ptr<ProgressCallback> _progress;

        void processKey( const CVBF_MapFrame& mapf, const CVBF_TileKey& key ) const;
        bool cacheTile( const CVBF_MapFrame& mapf, const CVBF_TileKey& key ) const;

        std::vector< CVBF_GeoExtent > _extents;
    };
}

#endif //OSGEARTH_CACHE_SEED_H
