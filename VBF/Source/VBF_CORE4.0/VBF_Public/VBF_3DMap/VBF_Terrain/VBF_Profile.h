#ifndef OSGEARTH_TILE_GRID_PROFILE_H
#define OSGEARTH_TILE_GRID_PROFILE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>
#include <vector>

class CVBF_TileKey;

using namespace osgEarth;

// Profile��������
class OSGEARTH_EXPORT CVBF_OptionsProfile : public CVBF_Options
{
public:
    CVBF_OptionsProfile( const CVBF_Options& options =CVBF_Options() );
    CVBF_OptionsProfile( const std::string& namedProfile );
    CVBF_OptionsProfile( const CVBF_OptionsProfile& rhs );

    virtual ~CVBF_OptionsProfile();
    CVBF_OptionsProfile& operator = ( const CVBF_OptionsProfile& rhs );

    bool defined() const; // �Ƿ��Ѿ����岢����

public:

 	// ��ȡ����
    CVBF_Optional<std::string>& namedProfile() { return _namedProfile; }
    const CVBF_Optional<std::string>& namedProfile() const { return _namedProfile; }

	// ��ȡ�ռ�ο�ϵͳ��ʼ���ַ���
    CVBF_Optional<std::string>& srsString() { return _srsInitString; }
    const CVBF_Optional<std::string>& srsString() const { return _srsInitString; }

 	// ��ȡ�̻߳�׼����ֱ�ο�ϵͳ��vertical spatial reference����ʼ���ַ���
    CVBF_Optional<std::string>& vsrsString() { return _vsrsInitString; }
    const CVBF_Optional<std::string>& vsrsString() const { return _vsrsInitString; }

	// ����ռ䷶Χ
    CVBF_Optional<Bounds>& bounds() { return _bounds; }
    const CVBF_Optional<Bounds>& bounds() const { return _bounds; }

	// ��0����LOD0����Ƭ��������X�᷽��
    CVBF_Optional<int>& numTilesWideAtLod0() { return _numTilesWideAtLod0; }
    const CVBF_Optional<int>& numTilesWideAtLod0() const { return _numTilesWideAtLod0; }

    // ��0����LOD0����Ƭ��������Y�᷽��
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


/*  profile���������ݵ�ͶӰ��ʽ�������ݷ�ҳ��ʽ�Լ�����ռ���չ��
	ͨ��profile���������Ĳ�����ÿ����Ƭ��TileKey����ʾ��һ�����������ܷ���������Ҫ�����������������Ƿ��ܹ������Ͷ�Ӧprofile���ݵ�������Ƭ��
	���磬���Ҫ���ɵ������ݣ�����Ҫָ��global-geodetic ����global-mercator profile����Ӧ������ԴҪ�ܹ�������profile��������Ӧ�ĵ������ݣ�
 */
class OSGEARTH_EXPORT CVBF_Profile : public ::CVBF_Referenced
{
public:
     enum ProfileType
    {
        TYPE_UNKNOWN,	// δ֪
        TYPE_GEODETIC,	// ��������ϵ
        TYPE_MERCATOR,	// ī����
        TYPE_LOCAL		// �ֲ�
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

	// �ж�profile�Ƿ���ȷ��ʼ����
    bool isOK() const;

	// ��ȡprofile�ķ�Χ����profile�Ŀռ�ο��У�
    const CVBF_GeoExtent& getExtent() const;

	// ��ȡprofile�ķ�Χ����γ�ȣ�
    const CVBF_GeoExtent& getLatLongExtent() const;

	// ��ȡ�ռ�ο�
    const CVBF_SpatialReference* getSRS() const;

	// ��ȡprofile������
    ProfileType getProfileType() const;  

	// ����x�ֱ��ʺͿռ�ο��ĵ�λ��������ӽ���LOD����
    unsigned int getLevelOfDetailForHorizResolution( double resolution, int tileSize ) const;
 
	// ��ȡ����LOD 0����������Ƭ�ļ�ֵ��key������ͬ��getAllKeysAtLOD(0)
    void getRootKeys(std::vector<CVBF_TileKey>& out_keys ) const;

	// ��ȡ����LOD��������Ƭ��ֵ
    void getAllKeysAtLOD(unsigned lod, std::vector<CVBF_TileKey>& out_keys) const;

	// ���������Ƭ�ķ�Χ
    virtual CVBF_GeoExtent calculateExtent( unsigned int lod, unsigned int tileX, unsigned int tileY );

	// �ӿռ�ο���SRS���ƶ�profile������
    static ProfileType getProfileTypeFromSRS(const std::string &srs);

	// �ж�����profile�Ƿ����
    bool isEquivalentTo( const CVBF_Profile* rhs ) const;

	// �ж�����profile�Ƿ���ȣ��������κδ�ֱ��׼��Ϣ�����SRS��ֱ��׼��ͬ��Ȼ����true��
    bool isHorizEquivalentTo( const CVBF_Profile* rhs ) const;

	// ��ȡ����LOD����Ƭ�ߴ�
    void getTileDimensions(unsigned int lod, double& out_width, double& out_height) const;

	// ��ȡ����LOD����Ƭ�������ߣ�
    void getNumTiles(unsigned int lod, unsigned int& out_tiles_wide, unsigned int& out_tiles_high) const;

   
	// Gets the intersecting tiles of this CVBF_Profile with the given CVBF_TileKey.
    void getIntersectingTiles( const CVBF_TileKey& key, std::vector<CVBF_TileKey>& out_intersectingKeys) const;

  	// ���ݸ����ķ�Χ����ȡ�ཻ����Ƭ����ֵ��
	virtual void getIntersectingTiles( const CVBF_GeoExtent& extent, std::vector<CVBF_TileKey>& out_intersectingKeys) const;

	// ������ķ�Χ�ü�����profile�ķ�Χ�����Ѳü���ķ�Χת������profile��SRC�����ת��ʧ�ܷ���GeoExtent::INVALID
    CVBF_GeoExtent clampAndTransformExtent( const CVBF_GeoExtent& input, bool* out_clamped =0L ) const;

	// ����һ��TileKey���ڴ�profile�Ŀռ�ο����������꣬��������˴�profile�ķ�Χ�򷵻�NULL
    CVBF_TileKey createTileKey( double x, double y, unsigned int level ) const;

	// ����һ����profile������
    std::string VBF_toString() const;

	// ����������һ����profile��CVBF_OptionsProfile
    CVBF_OptionsProfile toProfileOptions() const;

	// ����һ��Ψһ��ʶ��profile�Ĺ�ϣ��ǩ��
    const std::string& getFullSignature() const { return _fullSignature; }

	// ����һ��Ψһ��ʶ��profile�Ĺ�ϣ��ǩ�����������κδ�ֱ��׼��Ϣ�����������ж�����profiles�Ƿ�ˮƽ����ݵģ�horizontally compatible��
    const std::string& getHorizSignature() const { return _horizSignature; }

	// ����һ��profile����profile�е�LOD��ȷ��һ����this�в����ȵ�LOD��
    unsigned int getEquivalentLOD( const CVBF_Profile* profile, unsigned int lod ) const;

public:

	// ����һ���������������Լ��Ŀռ�ο��滻ԭ���Ŀռ�ο�
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

    // ����Χ����һ���ǵ������귶Χ��
    CVBF_GeoExtent		_extent;        // ����Χ
    CVBF_GeoExtent		_latlong_extent;// ��γ�ȷ�Χ���������귶Χ��

    // �����ֿ�
    unsigned			_numTilesWideAtLod0;
    unsigned			_numTilesHighAtLod0;

    // ǩ��
    std::string			_fullSignature;
    std::string			_horizSignature;
};


#endif // OSGEARTH_TILE_GRID_PROFILE_H
