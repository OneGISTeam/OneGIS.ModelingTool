#ifndef OSGEARTH_TILE_KEY_H
#define OSGEARTH_TILE_KEY_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Profile.h>
#include <VBF_Base/ref_ptr>
#include <VBF_Engine/VBF_SceneGraph/Version>
#include <VBF_Engine/VBF_Terrain/TerrainTile>
#include <string>


// 瓦片的唯一标识（和Profiles相关，Profiles定义了原点（0，0）在左上角）
class OSGEARTH_EXPORT CVBF_TileKey
{
public:     
    
    CVBF_TileKey() { } //无效的TileKey

    CVBF_TileKey(unsigned int lod, unsigned int tile_x, unsigned int tile_y, const CVBF_Profile* profile );
    CVBF_TileKey(const CVBF_TileKey& rhs);

    virtual ~CVBF_TileKey() { }

    bool operator == (const CVBF_TileKey& rhs) const 
	{
        return valid() && rhs.valid() && _lod==rhs._lod && _x==rhs._x && _y==rhs._y;
    }
    bool operator != (const CVBF_TileKey& rhs) const 
	{
        return !(*this == rhs);
    }
    bool operator < (const CVBF_TileKey& rhs) const 
	{
        if (_lod < rhs._lod) return true;
        if (_lod > rhs._lod) return false;
        if (_x < rhs._x) return true;
        if (_x > rhs._x) return false;
        return _y < rhs._y;
    }

    static CVBF_TileKey INVALID; // 标准的无效TileKey

	// TileKey的字符串表达，格式为lod_x_y
    std::string str() const { return _key; }

	// 转换为TileID
    osgTerrain::TileID getTileId() const;

	// 获取profile
    const CVBF_Profile* getProfile() const;

	// 是否是有效的键值
    bool valid() const { return _profile.valid(); }

public:

	// 获取子键（用四叉树，0，1，2，3）
    CVBF_TileKey createChildKey( unsigned int quadrant ) const;

	// 获取父键
    CVBF_TileKey createParentKey() const;

	// 获取祖先键（ancestorLod，祖先的LOD级）
    CVBF_TileKey createAncestorKey( int ancestorLod ) const;

    
	// 获取邻居（LOD相同）的键值，参数为相对本块的偏移量，如，xoffset=-1 yoffset=1返回SW的键值
    CVBF_TileKey createNeighborKey( int xoffset, int yoffset ) const;

	// 获取LOD
     unsigned GetLOD() const { return _lod; }

	// 获取本块的地理范围
    const CVBF_GeoExtent& getExtent() const { return _extent; }

	// 获取本块的范围（像素）
    void getPixelExtents( unsigned int& out_minx, unsigned int& out_miny,
                          unsigned int& out_maxx, unsigned int& out_maxy, const unsigned int& tile_size) const;

	// 获取本块的XY索引
    void getTileXY( unsigned int& out_tile_x, unsigned int& out_tile_y) const;

    unsigned int getTileX() const { return _x; }
    unsigned int getTileY() const { return _y; }
        
	static inline int GetLOD(const osgTerrain::TileID& id) { return id.level; }

protected:
    std::string							_key;
    unsigned int						_lod;
    unsigned int						_x;
    unsigned int						_y;
    ref_ptr<const CVBF_Profile>	        _profile;
    CVBF_GeoExtent							_extent;
};


#endif // OSGEARTH_TILE_KEY_H
