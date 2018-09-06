//**********************************************************************************
// �ļ�����  IVBF_SpatialReference.h
// ������    �ռ�ο�ϵ�������ο����򡢸̻߳�׼��ͶӰ��ʽ
// ����:     ��Ө
// ����:     2013-07-04
//**********************************************************************************

#ifndef __IVBF_SPATIAL_REFERENCE_H__
#define __IVBF_SPATIAL_REFERENCE_H__


#include <VBF_Common/VBF_Math/VBF_Export.h>
#include <Types/Vec3d>
#include <string>
#include <vector>


// ����mercatorͶӰ�ķ�Χ
const double MERC_MINX		= -20037508.34278925;
const double MERC_MINY		= -20037508.34278925;
const double MERC_MAXX		=  20037508.34278925;
const double MERC_MAXY		=  20037508.34278925;
const double MERC_WIDTH		= MERC_MAXX - MERC_MINX;
const double MERC_HEIGHT	= MERC_MAXY - MERC_MINY;
    
// ��Ҫʹ�õ���
class CVBFO_GeoLocator;
class CVBFO_VerticalDatum;

namespace osg
{
	class EllipsoidModel;
    class CVBF_SGNodeGroupCoordSys;
}
class CVBF_Units;


// �ռ�ο�ϵ�������ο����򡢸̻߳�׼��ͶӰ��ʽ

class IVBF_SpatialReference
{
public:
	virtual ~IVBF_SpatialReference() {}

public: // �����任
   	
    // ��һ����������һ��SRS�任����һ��SRS������任�ɹ�����true�����򷵻�false
    virtual bool transform(const osg::Vec3d& input, const IVBF_SpatialReference* outputSRS, osg::Vec3d&	output) const = 0;
   
    // ��һ���������һ��SRS�任����һ��SRS��ֻ�е����е㶼�任�ɹ�ʱ�ŷ���true�����򷵻�false
    virtual bool transform(std::vector<osg::Vec3d>&	input, const IVBF_SpatialReference* outputSRS) const = 0;
   
    // �任һ����ά���꣨һ�ֱȽϷ���ı任������
    virtual bool transform2D(double x, double y, const IVBF_SpatialReference* outputSRS, double& out_x, double& out_y) const = 0;


public: // ���굥λ�任
    
    // ��һ������ֵ��һ��SRS�任����һ��SRS�� �������һ���ǵ�������ϵ�����нǶȵ�λ������Ӧ�ľ���ֵΪ��Բ���� ��distance is measured at the equator��
    virtual double transformUnits(double distance, const IVBF_SpatialReference* outputSRS) const = 0;


public: // ����������ϵ֮��ı任
   

    // ��һ���������Ӹ�SRS�任����������ϵ����Ҫʱ�����SRS�ĸ̻߳�׼��z������й�һ������ת����ECFF
    virtual bool transformToWorld(const osg::Vec3d& input, osg::Vec3d& out_world) const = 0;
   

    // ��һ������������������ϵ�任����SRS��world:��������ϵ�µ������,	out_local:��SRS�µ������,out_geodeticZ:��ظ� (��HAE: Height Above Ellipsoid)
    virtual bool transformFromWorld(const osg::Vec3d& world, osg::Vec3d& out_local, double* out_geodeticZ=0L) const = 0;

public: // �ⲿ�任
    
	/**
	��һ���ռ䷶Χ�ɸ�SRS�任����һ��SRS���任��ķ�Χʵ����Ϊԭʼ��Χ����С��Χ���Σ�MBR: Minimum Bounding Rectangle��
	*/
    virtual bool transformExtentToMBR(const IVBF_SpatialReference* to_srs,
									  double& in_out_xmin, double& in_out_ymin, double& in_out_xmax, double& in_out_ymax ) const = 0;
       
	/**
	��һ���ռ䷶Χ�ɸ�SRS�任����һ��SRS�������ת����Χ�İ�Χ����
	*/
    virtual bool transformExtentPoints(const IVBF_SpatialReference* to_srs,
									   double in_xmin, double in_ymin, double in_xmax, double in_ymax,
									   double* x, double* y, unsigned numx, unsigned numy ) const = 0;


public: // ��������
   
	/** �Ƿ�Ϊ��������ϵ ������/γ��/msl��*/
    virtual bool isGeographic() const = 0;
    
	/** �Ƿ�Ϊ�������ϵ ������/γ��/��ظߣ�*/
    virtual bool isGeodetic() const = 0;
    
	/** �Ƿ�ΪͶӰ����ϵ �����ֲ�����ϵ��*/
    virtual bool isProjected() const = 0;
    
	/** �Ƿ�ΪECEF����ϵ ����������ϵ/�ף�
	ECEF: Earth-Centered Earth_Fixed�����ĵع�����ϵ����Ƶ�������ϵ��
		  ��һ���Ե���Ϊԭ��ĵع�����ϵ��Ҳ�ƺŵ�������ϵ����Ҳ��һ�ֵѿ�������ϵ��
	      ԭ��O(0,0,0)Ϊ�������ģ�z�������ƽ��ָ�򱱼��㣬x��ָ�򱾳������������Ľ��㣬y�ᴹֱ��xOzƽ�棨������90�������Ľ��㣩��������������ϵ��
	*/
    virtual bool isECEF() const = 0;
   
	/** �Ƿ�ʹ��MercatorͶӰ */
    virtual bool isMercator() const = 0;
    
	/** �Ƿ�ʹ������MercatorαͶӰ��Spherical Mercator pseudo-projection�������ѵ���ģ��Ϊ������������� */
    virtual bool isSphericalMercator() const = 0;
    
	/** �Ƿ�ʹ�ü����ƽͶӰ��polar sterographic projection�� 
	�����ƽͶӰ��������߷���һ��ͶӰ������ģ�ͨ�����ĵ������������������ཻ���ֱ��γɻ��ߺ͵㡣
				 �������ϻ��ߺ͵���ͶӰ��Ķ��㣨�ϰ�����°���ļ��㣩������ͶӰ�����ƽ���ϣ���Ϊ�����ƽͶӰ��
				 ��ƽͶӰͨ���ڹ������ѧ�����Խ�����ʹ���ĽǶȺͷ�λ���⡣
	*/
    virtual bool isNorthPolar() const = 0;
    virtual bool isSouthPolar() const = 0;
    
	/** �Ƿ�Ϊ�û��Զ����SRS ����GDAL��֧�ֵ�һ��SRS��*/
    virtual bool isUserDefined() const = 0;
   
	/** ��SRS�е������Ƿ���Դ��һ�������ռ䣬�������ռ��е����������ڵ�ͼ�е�ʵ��λ�ò�һ������ */
    virtual bool isContiguous() const = 0;
    
	/** �Ƿ�ΪosgEarth�ڲ������Unified CubeͶӰ */
    virtual bool isCube() const = 0;
   
	/** �Ƿ�ΪosgEarth�ڲ�����ľֲ���ƽ��ͶӰ��Local Tangent Plane projection��*/
    virtual bool isLTP() const = 0;
    
	/** Whether this is a geographic plate carre SRS */
    virtual bool isPlateCarre() const = 0;

    /** ��ȡ��SRS������ */
    virtual const std::string& getName() const = 0;

    /** ��ȡ��SRSʹ�õĲο����� */
    virtual const osg::EllipsoidModel* getEllipsoid() const = 0;
    
	/** ��ȡ������SRS�ı�׼�ַ�����WKT Well-Known Text��
	WKT: ��һ���ı�������ԣ����ڱ�ʾʸ�����ζ��󡢿ռ�ο�ϵ�Լ��ռ�ο�ϵ֮���ת�����ø�ʽ��OGC�ƶ���
	*/
    virtual const std::string& getWKT() const = 0;
    
	/** ��ȡ��ʼ���ͣ���PROJ4, WKT���ȵȣ�*/
    virtual const std::string& getInitType() const = 0;
    
	/** ��ȡˮƽ��׼��ĳ�ʼ�ַ��� */
    virtual const std::string& getHorizInitString() const = 0;
    
	/** ��ȡ��ֱ��׼��ĳ�ʼ�ַ��� */
    virtual const std::string& getVertInitString() const = 0;
    
	/** ��ȡ��SRSʹ�õĻ�׼��ı�ʶ��������Ϊ�գ�*/
    virtual const std::string& getDatumName() const = 0;
    
	/** ��ȡ��SRSʹ�õ����굥λ */
    virtual const CVBF_Units& getUnits() const = 0;
   
	/** �ж�����SRS�Ƿ���ȫ��ͬ */
    virtual bool isEquivalentTo( const IVBF_SpatialReference* rhs ) const = 0;

    /** �ж�����SRSʹ�õ�ˮƽ��׼���Ƿ���ͬ */
    virtual bool isHorizEquivalentTo( const IVBF_SpatialReference* rhs ) const = 0;

    /** �ж�����SRSʹ�õĴ�ֱ��׼���Ƿ���ͬ */
    virtual bool isVertEquivalentTo( const IVBF_SpatialReference* rhs ) const = 0;
    
	/** ��ȡ��SRSʹ�õĵ�������ϵ */
    virtual const IVBF_SpatialReference* getGeographicSRS() const = 0;
    
	/** ��ȡ��SRSʹ�õĴ������ϵ��ʵ���Ͼ����ڵ�������ϵ+��ֱ��׼��Z�����ʾ��ظߣ� */
    virtual const IVBF_SpatialReference* getGeodeticSRS() const = 0;
    
	/** ��ȡ��SRS����ʹ�õ�ECEF�ο�ϵ  */
    virtual const IVBF_SpatialReference* getECEF() const = 0;
    
	/** ��ȡ��ֱ��׼�����Ϊnull��ϵͳʹ��һ��Ĭ�ϵĴ�ش�ֱ��׼ */
    virtual const CVBFO_VerticalDatum* getVerticalDatum() const = 0;
   
	/** ���ø�SRS�е�һ������㣬����һ���ֲ�����ϵ����������ϵ�ı任���� */
    virtual bool createLocalToWorld(const osg::Vec3d& point, osg::Matrixd& out_local2world) const = 0;
    
	/** ���ø�SRS�е�һ������㣬����һ����������ϵ���ֲ�����ϵ�ı任���� */
    virtual bool createWorldToLocal(const osg::Vec3d& point, osg::Matrix& out_world2local) const = 0;

    /** Creates and returns a local trangent plane SRS at the given reference location.
        The reference location is expressed in this object's SRS, but it tangent to
        the globe at getGeographicSRS(). LTP units are in meters. */
	/** 
	��ָ���ο��㴦���������ظõ�ľֲ���ƽ��SRS����λΪ�ס�
	�ο���λ�ڸ�SRS�ڣ�������getGeographicSRS()������???
	*/
    virtual const IVBF_SpatialReference* createTangentPlaneSRS(const osg::Vec3d& refPos) const = 0;
    
	/** ��ָ����γ�����괦�����õ�ĺ���MercatorͶӰ */
    virtual const IVBF_SpatialReference* createTransMercFromLongitude( const Angular& lon ) const = 0;

	/** 
	��ָ����γ�����괦��UTM�ִ�������ͨ�ú���MercatorͶӰ��UTM�� 
	ע�⣺�ú�������һ������Ч���Ը�һЩ��
	*/
    virtual const IVBF_SpatialReference* createUTMFromLonLat(const Angle& lon, const Angle& lat) const = 0;

	/** ���Ƹ�SRS��Ϊ������������ƺ��SRS��ʶΪPlate Carreģʽ */
    virtual const IVBF_SpatialReference* createPlateCarreGeographicSRS() const = 0;
    
	/** �Ը�SRSΪ����������һ���µ�����ϵ�ڵ� */
    virtual osg::CVBF_SGNodeGroupCoordSys* createCoordinateSystemNode() const = 0;
    
	/** ����SRS����Ϣ��䵽һ������ϵ�ڵ��� */
    virtual bool populateCoordinateSystemNode(osg::CVBF_SGNodeGroupCoordSys* csn) const = 0;
    
	/**
	�Ը�SRSΪ����������һ���µ�Locator����
	@param xmin, ymin, xmax, ymax	Locator�����귶Χ����λ����
	@param plate_carre				�Ƿ�ʹ��plate_carreģʽ
	*/
    virtual CVBFO_GeoLocator* createLocator(double xmin, double ymin, double xmax, double ymax, bool plate_carre=false) const = 0;
};


#endif 
