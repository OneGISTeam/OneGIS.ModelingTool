//**********************************************************************************
// 文件名：  IVBF_SpatialReference.h
// 描述：    空间参考系，描述参考椭球、高程基准、投影方式
// 作者:     杜莹
// 日期:     2013-07-04
//**********************************************************************************

#ifndef __IVBF_SPATIAL_REFERENCE_H__
#define __IVBF_SPATIAL_REFERENCE_H__


#include <VBF_Common/VBF_Math/VBF_Export.h>
#include <Types/Vec3d>
#include <string>
#include <vector>


// 定义mercator投影的范围
const double MERC_MINX		= -20037508.34278925;
const double MERC_MINY		= -20037508.34278925;
const double MERC_MAXX		=  20037508.34278925;
const double MERC_MAXY		=  20037508.34278925;
const double MERC_WIDTH		= MERC_MAXX - MERC_MINX;
const double MERC_HEIGHT	= MERC_MAXY - MERC_MINY;
    
// 需要使用的类
class CVBFO_GeoLocator;
class CVBFO_VerticalDatum;

namespace osg
{
	class EllipsoidModel;
    class CVBF_SGNodeGroupCoordSys;
}
class CVBF_Units;


// 空间参考系，描述参考椭球、高程基准、投影方式

class IVBF_SpatialReference
{
public:
	virtual ~IVBF_SpatialReference() {}

public: // 基本变换
   	
    // 将一个点的坐标从一个SRS变换到另一个SRS，如果变换成功返回true，否则返回false
    virtual bool transform(const osg::Vec3d& input, const IVBF_SpatialReference* outputSRS, osg::Vec3d&	output) const = 0;
   
    // 将一组点的坐标从一个SRS变换到另一个SRS，只有当所有点都变换成功时才返回true，否则返回false
    virtual bool transform(std::vector<osg::Vec3d>&	input, const IVBF_SpatialReference* outputSRS) const = 0;
   
    // 变换一个二维坐标（一种比较方便的变换方法）
    virtual bool transform2D(double x, double y, const IVBF_SpatialReference* outputSRS, double& out_x, double& out_y) const = 0;


public: // 坐标单位变换
    
    // 将一个距离值从一个SRS变换到另一个SRS， 如果其中一个是地理坐标系（即有角度单位），对应的距离值为大圆距离 （distance is measured at the equator）
    virtual double transformUnits(double distance, const IVBF_SpatialReference* outputSRS) const = 0;


public: // 与世界坐标系之间的变换
   

    // 将一个点的坐标从该SRS变换到世界坐标系，必要时会根据SRS的高程基准对z坐标进行归一化，并转换到ECFF
    virtual bool transformToWorld(const osg::Vec3d& input, osg::Vec3d& out_world) const = 0;
   

    // 将一个点的坐标从世界坐标系变换到该SRS。world:世界坐标系下点的坐标,	out_local:该SRS下点的坐标,out_geodeticZ:大地高 (即HAE: Height Above Ellipsoid)
    virtual bool transformFromWorld(const osg::Vec3d& world, osg::Vec3d& out_local, double* out_geodeticZ=0L) const = 0;

public: // 外部变换
    
	/**
	把一个空间范围由该SRS变换到另一个SRS，变换后的范围实际上为原始范围的最小包围矩形（MBR: Minimum Bounding Rectangle）
	*/
    virtual bool transformExtentToMBR(const IVBF_SpatialReference* to_srs,
									  double& in_out_xmin, double& in_out_ymin, double& in_out_xmax, double& in_out_ymax ) const = 0;
       
	/**
	把一个空间范围由该SRS变换到另一个SRS，并输出转换后范围的包围矩形
	*/
    virtual bool transformExtentPoints(const IVBF_SpatialReference* to_srs,
									   double in_xmin, double in_ymin, double in_xmax, double in_ymax,
									   double* x, double* y, unsigned numx, unsigned numy ) const = 0;


public: // 各种属性
   
	/** 是否为地理坐标系 （经度/纬度/msl）*/
    virtual bool isGeographic() const = 0;
    
	/** 是否为大地坐标系 （经度/纬度/大地高）*/
    virtual bool isGeodetic() const = 0;
    
	/** 是否为投影坐标系 （即局部坐标系）*/
    virtual bool isProjected() const = 0;
    
	/** 是否为ECEF坐标系 （地心坐标系/米）
	ECEF: Earth-Centered Earth_Fixed，地心地固坐标系，简称地心坐标系。
		  是一种以地心为原点的地固坐标系（也称号地球坐标系），也是一种笛卡尔坐标系。
	      原点O(0,0,0)为地球质心，z轴与地轴平行指向北极点，x轴指向本初子午线与赤道的交点，y轴垂直于xOz平面（即东经90度与赤道的交点），构成右手坐标系。
	*/
    virtual bool isECEF() const = 0;
   
	/** 是否使用Mercator投影 */
    virtual bool isMercator() const = 0;
    
	/** 是否使用球体Mercator伪投影（Spherical Mercator pseudo-projection），即把地球模拟为球体而非椭球体 */
    virtual bool isSphericalMercator() const = 0;
    
	/** 是否使用极射赤平投影（polar sterographic projection） 
	极射赤平投影：把面和线放在一个投影球的中心，通过球心的面和线延伸后与球面相交，分别形成弧线和点。
				 把球面上弧线和点与投影球的顶点（上半球或下半球的极点）相连，投影到赤道平面上，即为极射赤平投影。
				 赤平投影通常在构造地质学中用以解决地质构造的角度和方位问题。
	*/
    virtual bool isNorthPolar() const = 0;
    virtual bool isSouthPolar() const = 0;
    
	/** 是否为用户自定义的SRS （即GDAL不支持的一种SRS）*/
    virtual bool isUserDefined() const = 0;
   
	/** 该SRS中的坐标是否来源于一个连续空间，非连续空间中的相邻坐标在地图中的实际位置不一定相邻 */
    virtual bool isContiguous() const = 0;
    
	/** 是否为osgEarth内部定义的Unified Cube投影 */
    virtual bool isCube() const = 0;
   
	/** 是否为osgEarth内部定义的局部切平面投影（Local Tangent Plane projection）*/
    virtual bool isLTP() const = 0;
    
	/** Whether this is a geographic plate carre SRS */
    virtual bool isPlateCarre() const = 0;

    /** 获取该SRS的名称 */
    virtual const std::string& getName() const = 0;

    /** 获取该SRS使用的参考椭球 */
    virtual const osg::EllipsoidModel* getEllipsoid() const = 0;
    
	/** 获取描述该SRS的标准字符串（WKT Well-Known Text）
	WKT: 是一种文本标记语言，用于表示矢量几何对象、空间参考系以及空间参考系之间的转换。该格式由OGC制定。
	*/
    virtual const std::string& getWKT() const = 0;
    
	/** 获取初始类型（如PROJ4, WKT，等等）*/
    virtual const std::string& getInitType() const = 0;
    
	/** 获取水平基准面的初始字符串 */
    virtual const std::string& getHorizInitString() const = 0;
    
	/** 获取垂直基准面的初始字符串 */
    virtual const std::string& getVertInitString() const = 0;
    
	/** 获取该SRS使用的基准面的标识符（可以为空）*/
    virtual const std::string& getDatumName() const = 0;
    
	/** 获取该SRS使用的坐标单位 */
    virtual const CVBF_Units& getUnits() const = 0;
   
	/** 判断两个SRS是否完全相同 */
    virtual bool isEquivalentTo( const IVBF_SpatialReference* rhs ) const = 0;

    /** 判断两个SRS使用的水平基准面是否相同 */
    virtual bool isHorizEquivalentTo( const IVBF_SpatialReference* rhs ) const = 0;

    /** 判断两个SRS使用的垂直基准面是否相同 */
    virtual bool isVertEquivalentTo( const IVBF_SpatialReference* rhs ) const = 0;
    
	/** 获取该SRS使用的地理坐标系 */
    virtual const IVBF_SpatialReference* getGeographicSRS() const = 0;
    
	/** 获取该SRS使用的大地坐标系，实际上就是在地理坐标系+垂直基准（Z坐标表示大地高） */
    virtual const IVBF_SpatialReference* getGeodeticSRS() const = 0;
    
	/** 获取该SRS椭球使用的ECEF参考系  */
    virtual const IVBF_SpatialReference* getECEF() const = 0;
    
	/** 获取垂直基准，如果为null，系统使用一个默认的大地垂直基准 */
    virtual const CVBFO_VerticalDatum* getVerticalDatum() const = 0;
   
	/** 利用该SRS中的一个坐标点，构建一个局部坐标系到世界坐标系的变换矩阵 */
    virtual bool createLocalToWorld(const osg::Vec3d& point, osg::Matrixd& out_local2world) const = 0;
    
	/** 利用该SRS中的一个坐标点，构建一个世界坐标系到局部坐标系的变换矩阵 */
    virtual bool createWorldToLocal(const osg::Vec3d& point, osg::Matrix& out_world2local) const = 0;

    /** Creates and returns a local trangent plane SRS at the given reference location.
        The reference location is expressed in this object's SRS, but it tangent to
        the globe at getGeographicSRS(). LTP units are in meters. */
	/** 
	在指定参考点处构建并返回该点的局部切平面SRS，单位为米。
	参考点位于该SRS内，与球在getGeographicSRS()处相切???
	*/
    virtual const IVBF_SpatialReference* createTangentPlaneSRS(const osg::Vec3d& refPos) const = 0;
    
	/** 在指定经纬度坐标处构建该点的横轴Mercator投影 */
    virtual const IVBF_SpatialReference* createTransMercFromLongitude( const Angular& lon ) const = 0;

	/** 
	在指定经纬度坐标处和UTM分带，构建通用横轴Mercator投影（UTM） 
	注意：该函数比上一个函数效率稍高一些。
	*/
    virtual const IVBF_SpatialReference* createUTMFromLonLat(const Angle& lon, const Angle& lat) const = 0;

	/** 复制该SRS，为区别起见，复制后的SRS标识为Plate Carre模式 */
    virtual const IVBF_SpatialReference* createPlateCarreGeographicSRS() const = 0;
    
	/** 以该SRS为基础，创建一个新的坐标系节点 */
    virtual osg::CVBF_SGNodeGroupCoordSys* createCoordinateSystemNode() const = 0;
    
	/** 将该SRS的信息填充到一个坐标系节点中 */
    virtual bool populateCoordinateSystemNode(osg::CVBF_SGNodeGroupCoordSys* csn) const = 0;
    
	/**
	以该SRS为基础，创建一个新的Locator对象。
	@param xmin, ymin, xmax, ymax	Locator的坐标范围，单位：度
	@param plate_carre				是否使用plate_carre模式
	*/
    virtual CVBFO_GeoLocator* createLocator(double xmin, double ymin, double xmax, double ymax, bool plate_carre=false) const = 0;
};


#endif 
