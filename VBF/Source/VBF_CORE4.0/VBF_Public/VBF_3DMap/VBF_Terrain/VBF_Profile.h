#ifndef OSGEARTH_TILE_GRID_PROFILE_H
#define OSGEARTH_TILE_GRID_PROFILE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>
#include <vector>

class CVBF_TileKey;

using namespace osgEarth;

// Profile的配置项
class OSGEARTH_EXPORT CVBF_OptionsProfile : public CVBF_Options
{
public:
    CVBF_OptionsProfile( const CVBF_Options& options =CVBF_Options() );
    CVBF_OptionsProfile( const std::string& namedProfile );
    CVBF_OptionsProfile( const CVBF_OptionsProfile& rhs );

    virtual ~CVBF_OptionsProfile();
    CVBF_OptionsProfile& operator = ( const CVBF_OptionsProfile& rhs );

    bool defined() const; // 是否已经定义并可用

public:

 	// 获取名称
    CVBF_Optional<std::string>& namedProfile() { return _namedProfile; }
    const CVBF_Optional<std::string>& namedProfile() const { return _namedProfile; }

	// 获取空间参考系统初始化字符串
    CVBF_Optional<std::string>& srsString() { return _srsInitString; }
    const CVBF_Optional<std::string>& srsString() const { return _srsInitString; }

 	// 获取高程基准（垂直参考系统，vertical spatial reference）初始化字符串
    CVBF_Optional<std::string>& vsrsString() { return _vsrsInitString; }
    const CVBF_Optional<std::string>& vsrsString() const { return _vsrsInitString; }

	// 地理空间范围
    CVBF_Optional<Bounds>& bounds() { return _bounds; }
    const CVBF_Optional<Bounds>& bounds() const { return _bounds; }

	// 第0级（LOD0）瓦片的数量（X轴方向）
    CVBF_Optional<int>& numTilesWideAtLod0() { return _numTilesWideAtLod0; }
    const CVBF_Optional<int>& numTilesWideAtLod0() const { return _numTilesWideAtLod0; }

    // 第0级（LOD0）瓦片的数量（Y轴方向）
    CVBF_Optional<int>& numTilesHighAtLod0() { return _numTilesHighAtLod0; }
    const CVBF_Optional<int>& numTilesHighAtLod0() const { return _numTilesHighAtLod0; }

public:
    CVBF_Config getConfig() const;

protected:
    void mergeConfig( const CVBF_Config& conf ) 
	{
        CVBF_Options::mergeConfig( conf );
        fromConfig( conf );
    }

private:
    void fromConfig( const CVBF_Config& conf );

    CVBF_Optional<std::string>		_namedProfile;
    CVBF_Optional<std::string>		_srsInitString;
    CVBF_Optional<std::string>		_vsrsInitString;
    CVBF_Optional<Bounds>			_bounds;
    CVBF_Optional<int>				_numTilesWideAtLod0;
    CVBF_Optional<int>				_numTilesHighAtLod0;
};


/*  profile定义了数据的投影方式或者数据分页方式以及地理空间延展；
	通过profile创建数据四叉树，每个瓦片用TileKey来标示；一个地形数据能否正常工作要看创建它的驱动器是否能够创建和对应profile兼容的数据瓦片；
	比如，如果要生成地球数据，就需要指定global-geodetic 或者global-mercator profile，相应的数据源要能够在这种profile下生成相应的地形数据；
 */
class OSGEARTH_EXPORT CVBF_Profile : public ::CVBF_Referenced
{
public:
     enum ProfileType
    {
        TYPE_UNKNOWN,	// 未知
        TYPE_GEODETIC,	// 地理坐标系
        TYPE_MERCATOR,	// 墨卡托
        TYPE_LOCAL		// 局部
    };

public:

    static const CVBF_Profile* create( const std::string& srs_string, double xmin, double ymin, 
		            double xmax, double ymax, const std::string& vsrs_string ="",
                    unsigned int numTilesWideAtLod0 =0, unsigned int numTilesHighAtLod0 =0 );

    static const CVBF_Profile* create( const CVBF_SpatialReference* srs,double xmin, double ymin, 
					double xmax, double ymax, double geoxmin, double geoymin, double geoxmax, double geoymax,
					unsigned int numTilesWideAtLod0 =0, unsigned int numTilesHighAtLod0 =0 );

    static const CVBF_Profile* create( const CVBF_SpatialReference* srs,
					double xmin, double ymin, double xmax, double ymax,
					unsigned int numTilesWideAtLod0 =0, unsigned int numTilesHighAtLod0 =0 );

    static const CVBF_Profile* create( const std::string& srs_string, const std::string& vsrs_string ="",
					unsigned int numTilesWideAtLod0 =0, unsigned int numTilesHighAtLod0 =0 );

    static const CVBF_Profile* create( const CVBF_OptionsProfile& options );

	// 判断profile是否正确初始化了
    bool isOK() const;

	// 获取profile的范围（在profile的空间参考中）
    const CVBF_GeoExtent& getExtent() const;

	// 获取profile的范围（经纬度）
    const CVBF_GeoExtent& getLatLongExtent() const;

	// 获取空间参考
    const CVBF_SpatialReference* getSRS() const;

	// 获取profile的类型
    ProfileType getProfileType() const;  

	// 给定x分辨率和空间参考的单位，返回最接近的LOD级别
    unsigned int getLevelOfDetailForHorizResolution( double resolution, int tileSize ) const;
 
	// 获取根（LOD 0）的所有瓦片的键值（key）。等同于getAllKeysAtLOD(0)
    void getRootKeys(std::vector<CVBF_TileKey>& out_keys ) const;

	// 获取给定LOD的所有瓦片键值
    void getAllKeysAtLOD(unsigned lod, std::vector<CVBF_TileKey>& out_keys) const;

	// 计算给定瓦片的范围
    virtual CVBF_GeoExtent calculateExtent( unsigned int lod, unsigned int tileX, unsigned int tileY );

	// 从空间参考（SRS）推断profile的类型
    static ProfileType getProfileTypeFromSRS(const std::string &srs);

	// 判断两个profile是否相等
    bool isEquivalentTo( const CVBF_Profile* rhs ) const;

	// 判断两个profile是否相等（不考虑任何垂直基准信息，如果SRS垂直基准不同仍然返回true）
    bool isHorizEquivalentTo( const CVBF_Profile* rhs ) const;

	// 获取给定LOD的瓦片尺寸
    void getTileDimensions(unsigned int lod, double& out_width, double& out_height) const;

	// 获取给定LOD的瓦片数（宽、高）
    void getNumTiles(unsigned int lod, unsigned int& out_tiles_wide, unsigned int& out_tiles_high) const;

   
	// Gets the intersecting tiles of this CVBF_Profile with the given CVBF_TileKey.
    void getIntersectingTiles( const CVBF_TileKey& key, std::vector<CVBF_TileKey>& out_intersectingKeys) const;

  	// 根据给定的范围，获取相交的瓦片（键值）
	virtual void getIntersectingTiles( const CVBF_GeoExtent& extent, std::vector<CVBF_TileKey>& out_intersectingKeys) const;

	// 把输入的范围裁剪到此profile的范围，并把裁剪后的范围转换到此profile的SRC，如果转换失败返回GeoExtent::INVALID
    CVBF_GeoExtent clampAndTransformExtent( const CVBF_GeoExtent& input, bool* out_clamped =0L ) const;

	// 创建一个TileKey，在此profile的空间参考下描述坐标，如果超出了此profile的范围则返回NULL
    CVBF_TileKey createTileKey( double x, double y, unsigned int level ) const;

	// 返回一个此profile的描述
    std::string VBF_toString() const;

	// 创建并返回一个此profile的CVBF_OptionsProfile
    CVBF_OptionsProfile toProfileOptions() const;

	// 返回一个唯一标识此profile的哈希码签名
    const std::string& getFullSignature() const { return _fullSignature; }

	// 返回一个唯一标识此profile的哈希码签名（不包括任何垂直基准信息），可用于判断两个profiles是否水平面兼容的（horizontally compatible）
    const std::string& getHorizSignature() const { return _horizSignature; }

	// 输入一个profile及该profile中的LOD，确定一个在this中差不多相等的LOD级
    unsigned int getEquivalentLOD( const CVBF_Profile* profile, unsigned int lod ) const;

public:

	// 制作一个拷贝，但是用自己的空间参考替换原来的空间参考
    CVBF_Profile* overrideSRS( const CVBF_SpatialReference* srs ) const;

protected:       

    CVBF_Profile( const CVBF_SpatialReference* srs, double xmin, double ymin, double xmax, double ymax,
				  unsigned int x_tiles_at_lod0 =0, unsigned int y_tiles_at_lod0 =0 );      

    CVBF_Profile( const CVBF_SpatialReference* srs, double xmin, double ymin, double xmax, double ymax,
				  double geoxmin, double geoymin, double geoxmax, double geoymax,
				  unsigned int x_tiles_at_lod0 =0, unsigned int y_tiles_at_lod0 =0 );


    virtual ~CVBF_Profile() { }
        

    virtual void addIntersectingTiles( const CVBF_GeoExtent& key_ext, std::vector<CVBF_TileKey>& out_intersectingKeys) const;


private:

    // 地理范围（不一定是地理坐标范围）
    CVBF_GeoExtent		_extent;        // 地理范围
    CVBF_GeoExtent		_latlong_extent;// 经纬度范围（地理坐标范围）

    // 顶级分块
    unsigned			_numTilesWideAtLod0;
    unsigned			_numTilesHighAtLod0;

    // 签名
    std::string			_fullSignature;
    std::string			_horizSignature;
};


#endif // OSGEARTH_TILE_GRID_PROFILE_H
