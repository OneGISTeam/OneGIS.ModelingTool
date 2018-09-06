//**********************************************************************************
// �ļ�����  VBF_SpatialReference.h
// ������    �ռ�ο�ϵ�������ο����򡢸̻߳�׼��ͶӰ��ʽ
// ����:     ��Ө
// ����:     2013-06-21
//**********************************************************************************

#ifndef __VBF_SPATIAL_REFERENCE_H__
#define __VBF_SPATIAL_REFERENCE_H__


#include <VBF_3DMap/VBF_Terrain/Export>
#include <VBF_Common/VBF_Utils/VBF_Units.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_VerticalDatum.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupCoordSys.h>
#include <Types/Vec3>
#include <OpenThreads/ReentrantMutex>
#include <VBF_Common/VBF_Math/IVBF_SpatialReference.h>
#include <map>

using namespace osgEarth;

/*
// ����mercatorͶӰ�ķ�Χ
const double MERC_MINX		= -20037508.34278925;
const double MERC_MINY		= -20037508.34278925;
const double MERC_MAXX		=  20037508.34278925;
const double MERC_MAXY		=  20037508.34278925;
const double MERC_WIDTH		= MERC_MAXX - MERC_MINX;
const double MERC_HEIGHT	= MERC_MAXY - MERC_MINY;
*/

// ECEF: Earth-Centered Earth_Fixed�����ĵع�����ϵ����Ƶ�������ϵ��ԭ��O(0,0,0)Ϊ�������ģ�
//       z�������ƽ��ָ�򱱼��㣬x��ָ�򱾳������������Ľ��㣬y�ᴹֱ��xOzƽ�棨������90�������Ľ��㣩��������������ϵ��



// �ռ�ο�ϵ�������ο����򡢸̻߳�׼��ͶӰ��ʽ
class OSGEARTH_EXPORT CVBF_SpatialReference : public IVBF_SpatialReference, public CVBF_Referenced
{
public: // ����

	// �����ռ�ο�ϵ�� ���������ֱ��ʾˮƽ��׼�ʹ�ֱ��׼�����δָ����ֱ��׼��ϵͳ��ʹ������Ĵ�ػ�׼�棨geodetic datum for the ellipsoid��
	static CVBF_SpatialReference* create(const std::string& init, const std::string& vinit="");
	static CVBF_SpatialReference* get(const std::string& init, const std::string& vinit="") { return create(init,vinit); }

    // ����һ��osg����ϵ�ڵ㴴��һ���ռ�ο�ϵ�� ��������������Ϣ���걸������NULL
	static CVBF_SpatialReference* create(osg::CVBF_SGNodeGroupCoordSys* csn);

    // ����һ��OGR�ռ�ο��������һ���ռ�ο�ϵ�����xferOwnership��Ϊtrue����IVBF_SpatialReference������������ʱ�ͷ�OGR���
	static CVBF_SpatialReference* createFromHandle(void* ogrHandle, bool xferOwnership=false);
	

public: // �����任

    // ��һ����������һ��SRS�任����һ��SRS������任�ɹ�����true�����򷵻�false
    virtual bool transform(const osg::Vec3d& input, const IVBF_SpatialReference* outputSRS, osg::Vec3d&	output) const;
   
    // ��һ���������һ��SRS�任����һ��SRS��ֻ�е����е㶼�任�ɹ�ʱ�ŷ���true�����򷵻�false
    virtual bool transform(std::vector<osg::Vec3d>&	input, const IVBF_SpatialReference* outputSRS) const;
   
    // �任һ����ά���꣨һ�ֱȽϷ���ı任������
    virtual bool transform2D(double x, double y, const IVBF_SpatialReference* outputSRS, double& out_x, double& out_y) const;

public: // ���굥λ�任
    
    // ��һ������ֵ��һ��SRS�任����һ��SRS���������һ��SRS�ǵ�������ϵ�����нǶȵ�λ������Ӧ�ľ���ֵΪ��Բ����
    virtual double transformUnits(double distance, const IVBF_SpatialReference* outputSRS) const;

public: // ����������ϵ֮��ı任
   
    // ��һ���������Ӹ�SRS�任����������ϵ����Ҫʱ�����SRS�ĸ̻߳�׼��z������й�һ������ת����ECFF
    virtual bool transformToWorld(const osg::Vec3d& input, osg::Vec3d& out_world) const;
   
    // ��һ�����������������ϵ�任����SRS��world[in]Ϊ��������ϵ�µ�����꣬out_local[out]Ϊ��SRS�µ������
    // out_geodeticZ[out, optional]Ϊ��ظ� (��HAE: Height Above Ellipsoid)
    virtual bool transformFromWorld(const osg::Vec3d& world, osg::Vec3d& out_local, double*	out_geodeticZ=0L) const;

public: // �ⲿ�任
    
    // ��һ���ռ䷶Χ�ɸ�SRS�任����һ��SRS���任��ķ�Χʵ����Ϊԭʼ��Χ����С��Χ���Σ�MBR: Minimum Bounding Rectangle��
    virtual bool transformExtentToMBR(const IVBF_SpatialReference* to_srs,
                    double& in_out_xmin, double& in_out_ymin, double& in_out_xmax, double& in_out_ymax ) const;
       
    // ��һ���ռ䷶Χ�ɸ�SRS�任����һ��SRS�������ת����Χ�İ�Χ����
    virtual bool transformExtentPoints(const IVBF_SpatialReference* to_srs,
                    double in_xmin, double in_ymin, double in_xmax, double in_ymax,
                    double* x, double* y, unsigned numx, unsigned numy ) const;

public: // ��������
    
    virtual bool isGeographic() const; // �Ƿ�Ϊ��������ϵ ������/γ��/msl��
    virtual bool isGeodetic() const;   // �Ƿ�Ϊ�������ϵ ������/γ��/��ظߣ�
    
    virtual bool isProjected() const; //�Ƿ�ΪͶӰ����ϵ �����ֲ�����ϵ��
    
    virtual bool isECEF() const; // �Ƿ�ΪECEF����ϵ ����������ϵ/�ף�
    virtual bool isMercator() const;//�Ƿ�ʹ��MercatorͶӰ
    
    virtual bool isSphericalMercator() const; // �Ƿ�ʹ������MercatorαͶӰ��Spherical Mercator pseudo-projection�������ѵ���ģ��Ϊ�������������
    
	/** �Ƿ�ʹ�ü����ƽͶӰ��polar sterographic projection�� 
	�����ƽͶӰ��������߷���һ��ͶӰ������ģ�ͨ�����ĵ������������������ཻ���ֱ��γɻ��ߺ͵㡣
				 �������ϻ��ߺ͵���ͶӰ��Ķ��㣨�ϰ�����°���ļ��㣩������ͶӰ�����ƽ���ϣ���Ϊ�����ƽͶӰ��
				 ��ƽͶӰͨ���ڹ������ѧ�����Խ�����ʹ���ĽǶȺͷ�λ���⡣
	*/
    virtual bool isNorthPolar() const;
    virtual bool isSouthPolar() const;
    
    //�Ƿ�Ϊ�û��Զ����SRS ����GDAL��֧�ֵ�һ��SRS)
    virtual bool isUserDefined() const;
   
    // ��SRS�е������Ƿ���Դ��һ�������ռ䣬�������ռ��е����������ڵ�ͼ�е�ʵ��λ�ò�һ������
    virtual bool isContiguous() const;
    
    //�Ƿ�Ϊ�ڲ������Unified CubeͶӰ
    virtual bool isCube() const;
   
    // �Ƿ�Ϊ�ڲ�����ľֲ���ƽ��ͶӰ��Local Tangent Plane projection��
    virtual bool isLTP() const { return _is_ltp; }
    
    // �Ƿ�Ϊgeographic plate carre SRS
    virtual bool isPlateCarre() const { return _is_plate_carre; }

    virtual const std::string& getName() const;//��ȡ��SRS������

    // ��ȡ��SRSʹ�õĲο�����
    virtual const osg::EllipsoidModel* getEllipsoid() const;
    
    // ��ȡ������SRS�ı�׼�ַ�����WKT��Well-Known Text��
    // WKT: ��һ���ı�������ԣ����ڱ�ʾʸ�����ζ��󡢿ռ�ο�ϵ�Լ��ռ�ο�ϵ֮���ת�����ø�ʽ��OGC�ƶ�
    virtual const std::string& getWKT() const;
    
    virtual const std::string& getInitType() const;//��ȡ��ʼ���ͣ���PROJ4, WKT���ȵȣ�
    
    //��ȡ��ʼ�ؼ�ֵ
	typedef std::pair<std::string, std::string> Key;
    virtual const Key& getKey() const;
    
    // ��ȡˮƽ��׼��ĳ�ʼ�ַ���
    virtual const std::string& getHorizInitString() const;
    
    // ��ȡ��ֱ��׼��ĳ�ʼ�ַ���
    virtual const std::string& getVertInitString() const;

    //��ȡ��SRSʹ�õĻ�׼��ı�ʶ��������Ϊ�գ�
    virtual const std::string& getDatumName() const;
    
    // ��ȡ��SRSʹ�õ����굥λ
    virtual const CVBF_Units& getUnits() const;
   
    // �ж�����SRS�Ƿ���ȫ��ͬ
    virtual bool isEquivalentTo(const IVBF_SpatialReference* rhs) const;

    // �ж�����SRSʹ�õ�ˮƽ��׼���Ƿ���ͬ
    virtual bool isHorizEquivalentTo(const IVBF_SpatialReference* rhs) const;

    // �ж�����SRSʹ�õĴ�ֱ��׼���Ƿ���ͬ
    virtual bool isVertEquivalentTo(const IVBF_SpatialReference* rhs) const;
    
    // ��ȡ��SRSʹ�õĵ�������ϵ
    virtual const IVBF_SpatialReference* getGeographicSRS() const;
    
    // ��ȡ��SRSʹ�õĴ������ϵ��ʵ���Ͼ����ڵ�������ϵ+��ֱ��׼��Z�����ʾ��ظߣ�
    virtual const IVBF_SpatialReference* getGeodeticSRS() const;
    
    // ��ȡ��SRS����ʹ�õ�ECEF�ο�ϵ
    virtual const IVBF_SpatialReference* getECEF() const;
    
    // ��ȡ��ֱ��׼�����Ϊnull��ϵͳʹ��һ��Ĭ�ϵĴ�ش�ֱ��׼
    virtual const CVBFO_VerticalDatum* getVerticalDatum() const;
   
    // ���ø�SRS�е�һ������㣬����һ���ֲ�����ϵ����������ϵ�ı任����
    virtual bool createLocalToWorld(const osg::Vec3d& point, osg::Matrixd& out_local2world) const;
    
    // ���ø�SRS�е�һ������㣬����һ����������ϵ���ֲ�����ϵ�ı任����
    virtual bool createWorldToLocal(const osg::Vec3d& point, osg::Matrix& out_world2local) const;

    /** Creates and returns a local trangent plane SRS at the given reference location.
        The reference location is expressed in this object's SRS, but it tangent to
        the globe at getGeographicSRS(). LTP units are in meters. */
	/** 
	��ָ���ο��㴦���������ظõ�ľֲ���ƽ��SRS����λΪ�ס�
	�ο���λ�ڸ�SRS�ڣ�������getGeographicSRS()������???
	*/
    virtual const IVBF_SpatialReference* createTangentPlaneSRS(const osg::Vec3d& refPos) const;
    
    // ��ָ����γ�����괦�����õ�ĺ���MercatorͶӰ
    virtual const IVBF_SpatialReference* createTransMercFromLongitude( const Angular& lon ) const;

    // ��ָ����γ�����괦��UTM�ִ�������ͨ�ú���MercatorͶӰ��UTM��,�ú�������һ������Ч���Ը�һЩ��
    virtual const IVBF_SpatialReference* createUTMFromLonLat(const Angle& lon, const Angle& lat) const;

    // ���Ƹ�SRS��Ϊ������������ƺ��SRS��ʶΪPlate Carreģʽ
    virtual const IVBF_SpatialReference* createPlateCarreGeographicSRS() const;
    
    // �Ը�SRSΪ����������һ���µ�����ϵ�ڵ�
    virtual osg::CVBF_SGNodeGroupCoordSys* createCoordinateSystemNode() const;
    
    // ����SRS����Ϣ��䵽һ������ϵ�ڵ���
    virtual bool populateCoordinateSystemNode(osg::CVBF_SGNodeGroupCoordSys* csn) const;
    
    // �Ը�SRSΪ����������һ���µ�Locator����xmin,ymin,xmax,ymaxΪLocator�����귶Χ����λ���ȡ�plate_carreΪ�Ƿ�ʹ��plate_carreģʽ
    virtual CVBFO_GeoLocator* createLocator(double xmin, double ymin,  double xmax, double ymax, bool plate_carre=false) const;


protected:
	CVBF_SpatialReference(void* handle, const std::string& type);
    CVBF_SpatialReference(void* handle, bool ownsHandle=true );

    virtual ~CVBF_SpatialReference();

    void init();
	
	// �û������������������������к�����ע�⣺����ʱ��Ҫͬʱ���û���ĺ���
    virtual void _init();
    virtual bool _isEquivalentTo(const CVBF_SpatialReference* srs, bool considerVDatum=true) const;

    virtual bool preTransform(std::vector<osg::Vec3d>&) const { return true; }
    virtual bool postTransform(std::vector<osg::Vec3d>&) const { return true; }

    bool transformXYPointArrays(double* x, double* y, unsigned numPoints, const CVBF_SpatialReference* out_srs) const;
    bool transformZ(std::vector<osg::Vec3d>& points, const CVBF_SpatialReference* outputSRS, bool pointsAreGeodetic) const;

    typedef std::map<Key, ref_ptr<CVBF_SpatialReference> > SRSCache;
    static SRSCache& getSRSCache();

protected:
    bool								_initialized;
    void*								_handle;
    bool								_owns_handle;
    bool								_is_geographic;
    bool								_is_mercator;
    bool								_is_spherical_mercator;
    bool								_is_north_polar, _is_south_polar;
    bool								_is_cube;
    bool								_is_contiguous;
    bool								_is_user_defined;
    bool								_is_ltp;
    bool								_is_plate_carre;
    bool								_is_ecef;
    unsigned							_ellipsoidId;
    std::string							m_sName;
    Key									_key;
    std::string							_wkt;
    std::string							_proj4;
    std::string							_init_type;
    std::string							_datum;
    CVBF_Units							_units;
    ref_ptr<osg::EllipsoidModel>		_ellipsoid;
    ref_ptr<CVBF_SpatialReference>		_geo_srs;
    ref_ptr<CVBF_SpatialReference>		_geodetic_srs;  // _geo_srs with a NULL vdatum.
    ref_ptr<CVBF_SpatialReference>		_ecef_srs;
    ref_ptr<CVBFO_VerticalDatum>		_vdatum;

    typedef std::map<std::string, void*>	TransformHandleCache;
    TransformHandleCache					_transformHandleCache;

private:
    static CVBF_SpatialReference* create(const Key& key, bool useCache);
    static CVBF_SpatialReference* createFromWKT(const std::string& wkt, const std::string& name ="");
    static CVBF_SpatialReference* createFromPROJ4(const std::string& proj4, const std::string& name = "");
    static CVBF_SpatialReference* createCube();

    CVBF_SpatialReference* fixWKT();
};



#endif 
