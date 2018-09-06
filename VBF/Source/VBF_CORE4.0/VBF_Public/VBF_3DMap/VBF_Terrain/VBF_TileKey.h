#ifndef OSGEARTH_TILE_KEY_H
#define OSGEARTH_TILE_KEY_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Profile.h>
#include <VBF_Base/ref_ptr>
#include <VBF_Engine/VBF_SceneGraph/Version>
#include <VBF_Engine/VBF_Terrain/TerrainTile>
#include <string>


// ��Ƭ��Ψһ��ʶ����Profiles��أ�Profiles������ԭ�㣨0��0�������Ͻǣ�
class OSGEARTH_EXPORT CVBF_TileKey
{
public:     
    
    CVBF_TileKey() { } //��Ч��TileKey

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

    static CVBF_TileKey INVALID; // ��׼����ЧTileKey

	// TileKey���ַ�������ʽΪlod_x_y
    std::string str() const { return _key; }

	// ת��ΪTileID
    osgTerrain::TileID getTileId() const;

	// ��ȡprofile
    const CVBF_Profile* getProfile() const;

	// �Ƿ�����Ч�ļ�ֵ
    bool valid() const { return _profile.valid(); }

public:

	// ��ȡ�Ӽ������Ĳ�����0��1��2��3��
    CVBF_TileKey createChildKey( unsigned int quadrant ) const;

	// ��ȡ����
    CVBF_TileKey createParentKey() const;

	// ��ȡ���ȼ���ancestorLod�����ȵ�LOD����
    CVBF_TileKey createAncestorKey( int ancestorLod ) const;

    
	// ��ȡ�ھӣ�LOD��ͬ���ļ�ֵ������Ϊ��Ա����ƫ�������磬xoffset=-1 yoffset=1����SW�ļ�ֵ
    CVBF_TileKey createNeighborKey( int xoffset, int yoffset ) const;

	// ��ȡLOD
     unsigned GetLOD() const { return _lod; }

	// ��ȡ����ĵ���Χ
    const CVBF_GeoExtent& getExtent() const { return _extent; }

	// ��ȡ����ķ�Χ�����أ�
    void getPixelExtents( unsigned int& out_minx, unsigned int& out_miny,
                          unsigned int& out_maxx, unsigned int& out_maxy, const unsigned int& tile_size) const;

	// ��ȡ�����XY����
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
