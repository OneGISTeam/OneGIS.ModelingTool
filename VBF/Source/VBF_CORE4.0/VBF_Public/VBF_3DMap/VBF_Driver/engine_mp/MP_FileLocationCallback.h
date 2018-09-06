#ifndef OSGEARTH_ENGINE_OSGTERRAIN_FILE_LOCATION_CALLBACK_H
#define OSGEARTH_ENGINE_OSGTERRAIN_FILE_LOCATION_CALLBACK_H 1

#include "MP_TerrainEngineNode.h"
#include <VBF_Engine/VBF_SceneGraph/Version>
#include <VBF_3DMap/VBF_Terrain/Export>


// 一个分页数据库回调，决定给定的文件名是否被缓存
class CMP_FileLocationCallback : public osgDB::FileLocationCallback
{
public:
	CMP_FileLocationCallback() { }
	virtual ~CMP_FileLocationCallback() { }

	virtual Location fileLocation(const std::string& filename, const osgDB::Options* options)
	{
		unsigned int lod, x, y, id;
		sscanf(filename.c_str(), "%d/%d/%d.%d", &lod, &x, &y, &id);

		ref_ptr<CMP_TerrainEngineNode> ipEngine;
		CMP_TerrainEngineNode::getEngineByUID( (UID)id, ipEngine );

		if ( !ipEngine.valid() ) return REMOTE_FILE;


		const CVBF_Profile* profile = ipEngine->GetMap()->getProfile();
		CVBF_TileKey mapKey( lod, x, y, profile );

		CVBF_MapFrame mapf( ipEngine->GetMap() );
		for( unsigned i=0; i<4; ++i )
		{
			CVBF_TileKey childKey = mapKey.createChildKey( i );
			if ( !mapf.isCached( childKey ) ) return REMOTE_FILE;
		}

		return LOCAL_FILE;
	}

	virtual bool useFileCache() const { return false; }
};



#endif //OSGEARTH_ENGINE_OSGTERRAIN_FILE_LOCATION_CALLBACK_H
