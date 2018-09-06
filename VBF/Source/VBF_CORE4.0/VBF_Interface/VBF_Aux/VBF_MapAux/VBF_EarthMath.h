
//***************************************************************************************
// FileName：VBF_EarthMath.h
// Function：与椭球有关的数学工具函数
// Author:   杜莹
// Date:     2014-08-15
//***************************************************************************************

#ifndef __VBF_EARTH_MATH_H__
#define __VBF_EARTH_MATH_H__


#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_3DMap/VBF_Terrain/ElevationQuery.h>
#include <Types/Vec2i.h>
#include <Types/Vec3d>
#include <Types/VBF_BoundingBox.h>
#include <vector>



// 计算两个地理坐标点之间的插值个数（沿大圆线插值，含起点和终点）
VBF_MAPAUX_EXPORT int VBF_ComputeNumInterPoints(CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1, double hMin);


// 在两个地理坐标点之间沿大圆线进行插值（高程使用线性插值）
// 参数：nNumInter -- 相邻两个点之间的插值点数（含起点和终点）
VBF_MAPAUX_EXPORT void VBF_InterpolateGreatCircle(const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1,
                                                  int nNumInter, std::vector<osg::Vec3d>& vOutGeo, double dDeltaH=1.0);

// 在多个地理坐标点之间沿大圆线进行插值（高程使用线性插值）
// 参数：nNumInter -- 相邻两个点之间的插值点数（含这两个点）
VBF_MAPAUX_EXPORT void VBF_InterpolateGreatCircle(const std::vector<osg::Vec3d>& vGeoSrc,
                                                  int nNumInter, std::vector<osg::Vec3d>& vGeoDst);


// 在两个地理坐标点之间沿大圆线进行插值（高程使用线性插值，插值点数自动计算）
// 参数：hMin -- 所有点的最小高程值，用于计算两点之间的插值点数
VBF_MAPAUX_EXPORT void VBF_InterpolateGreatCircle(CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1,
                                                  const double& hMin, std::vector<osg::Vec3d>& vOutGeo, double dDeltaH=1.0);


// 在两个地理坐标点之间沿大圆线进行插值（高程使用线性插值，插值点数自动计算）
VBF_MAPAUX_EXPORT void VBF_InterpolateGreatCircle(CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1,
                                                  std::vector<osg::Vec3d>& vOutGeo, double dDeltaH=1.0);


// 在多个地理坐标点之间沿大圆线进行插值（高程使用线性插值）
// 参数：hMin -- 所有点的最小高程值，用于计算两点之间的插值点数
VBF_MAPAUX_EXPORT void VBF_InterpolateGreatCircle(CVBFO_SGNodeMap* pMapNode, const std::vector<osg::Vec3d>& vGeoSrc,
                                                  double hMin, std::vector<osg::Vec3d>& vGeoDst);


// 在多个地理坐标点之间沿大圆线进行插值（高程使用线性插值）
VBF_MAPAUX_EXPORT void VBF_InterpolateGreatCircle(CVBFO_SGNodeMap* pMapNode, const std::vector<osg::Vec3d>& vGeoSrc,
                                                  std::vector<osg::Vec3d>& vGeoDst);


// 在两个地理坐标点之间线性插值(适用于视点较近时，有待修改，高程值也进行线性插值)
VBF_MAPAUX_EXPORT void VBF_InterpolateLinear(const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1,
                                             int nNumInter, std::vector<osg::Vec3d>& vOutGeo);


// 根据输入的地理坐标串，获取其在地理坐标系下的包围盒，如果顶点个数为0，返回false
VBF_MAPAUX_EXPORT bool VBF_GetBoundingBoxInGeo(const std::vector<osg::Vec3d>& vPointsGeo, osg::BoundingBoxd& boxInGeo);


// 根据输入的地理坐标串，获取其在世界坐标系下的包围盒，如果顶点个数为0，返回false
VBF_MAPAUX_EXPORT bool VBF_GetBoundingBoxInWorld(CVBFO_SGNodeMap* pMapNode, const std::vector<osg::Vec3d>& vPointsGeo, osg::BoundingBoxd& boxInWorld);


// 度-->度分秒
VBF_MAPAUX_EXPORT void DegreeToDMS(double dGeoCoord, int& nDegree, int& nMinute, int& nSecond);


// 根据地理坐标(经度或纬度)，构建字符串
VBF_MAPAUX_EXPORT void FormatGeoCoord(double dGeoCoord, char* strCoord);


// 根据坐标值构造坐标信息（显示高程值）
VBF_MAPAUX_EXPORT void VBF_FormatCoordInfo(double L, double B, double H, bool bCoordDMS, char* szInfo);


// 根据坐标值构造坐标信息（不显示高程值）
VBF_MAPAUX_EXPORT void VBF_FormatCoordInfo(double L, double B, bool bCoordDMS, char* szInfo);


// 根据距离值构造距离信息
// 参数：szPrefix -- 信息前缀，如“距离：”，或“总距离=”
//-------------------------------------------------------------------------
//VBF_MAPAUX_EXPORT void VBF_FormatDistInfo(double dDist, const char* szPrefix, char* szInfo);


// 根据面积值构造面积信息
//VBF_MAPAUX_EXPORT void VBF_FormatAreaInfo(double dArea, char* szInfo);


// 计算椭球上折线的长度
VBF_MAPAUX_EXPORT double VBF_GetDist(const std::vector<osg::Vec3d>& vPointsGeo, osgEarth::GeoInterpolation nGeoInterpolation,double dR);


// 计算椭球上两点之间的距离
VBF_MAPAUX_EXPORT double VBF_GetDist(const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1, osgEarth::GeoInterpolation nGeoInterpolation,double dR);


// 计算世界坐标系下两点之间的距离
VBF_MAPAUX_EXPORT double VBF_GetDistInWorld(osg::IVBF_Camera* pICamera, CVBFO_SGNodeMap* pMapNode,
											const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1);


// 计算世界坐标系下折线的长度
VBF_MAPAUX_EXPORT double VBF_GetDistInWorld(osg::IVBF_Camera* pICamera, CVBFO_SGNodeMap* pMapNode,
											const std::vector<osg::Vec3d>& vPointsGeo);


// 计算椭球上计算多边形面积
VBF_MAPAUX_EXPORT double VBF_GetArea(int nNumVertices, osg::Vec3d* pGeoVertices);


// 计算多边形的外接矩形 (地理坐标)
VBF_MAPAUX_EXPORT void VBF_CalBoundingRectGeo(const std::vector<osg::Vec3d>& vPointsGeo,
											 double& dLMin, double& dBMin, double& dLMax, double& dBMax);


// 计算多边形的外接矩形 (屏幕坐标)
VBF_MAPAUX_EXPORT void VBF_CalBoundingRectClient(osg::IVBF_Camera* pICamera, CVBFO_SGNodeMap* pMapNode, const std::vector<osg::Vec3d>& vPointsGeo,
												 double& xMin, double& yMin, double& xMax, double& yMax);


// 装载Dem数据
// 参数：dLMin, dLMax, dBMin, dBMax -- Dem网格的经度和纬度范围
//		nNumRows, nNumCols -- Dem网格的行数和列数
VBF_MAPAUX_EXPORT bool VBF_LoadDem(osgEarth::ElevationQuery* pElevQuery, const CVBF_SpatialReference* pPointSRS,
									double dLMin, double dBMin, double dLMax, double dBMax,
									int nNumRows, int nNumCols, double dResolution, float**& pDem);


// 装载Dem数据
// 参数：dLMin, dLMax, dBMin, dBMax -- Dem网格的经度和纬度范围
//		 nNumRows, nNumCols -- Dem网格的行数和列数
VBF_MAPAUX_EXPORT bool VBF_LoadDem(osgEarth::ElevationQuery* pElevQuery, const CVBF_SpatialReference* pPointSRS,
								   double dLMin, double dBMin, double dLMax, double dBMax,
								   int nNumRows, int nNumCols, double dResolution, std::vector<float>& vHeightList);


// 装载Dem数据，并进行重新采样（双线性插值）
// 参数：dLMin, dBMin, dLMax, dBMax -- Dem网格的经度和纬度范围
//		nNumRowsSrc, nNumColsSrc   -- 需要读取的Dem网格密度
//	    nNumRowsDst, nNumColsDst   -- 插值后的Dem网格密度
VBF_MAPAUX_EXPORT bool VBF_LoadAndResampleDem(osgEarth::ElevationQuery* pElevQuery, const CVBF_SpatialReference* pPointSRS,
											  double dLMin, double dBMin, double dLMax, double dBMax, double dResolution,
											  int nNumRowsSrc, int nNumColsSrc, int nNumRowsDst, int nNumColsDst, float**& pDem);


// 计算单点坡度
VBF_MAPAUX_EXPORT float VBF_Slope(int i, int j, float** pDem, short nRows, short nCols);


// 计算点和原点构成的方位角（单位：弧度）
VBF_MAPAUX_EXPORT double VBF_GetAzimuthAngle(double dx, double dy);


// 提取一条线段经过的所有像素点（DDA: Digital Differential Analyzer，数值微分法）
VBF_MAPAUX_EXPORT void VBF_LineDDA(int x0, int y0, int x1, int y1, std::vector<osg::Vec2i>& vPoints);


// 求椭球面上任意一点的法线
VBF_MAPAUX_EXPORT bool VBF_CalEllipNormal(CVBFO_SGNodeMap* pMapNode, double L, double B, osg::Vec3d& vNormal);

// 对路径进行光滑，相对于地形高度，输入的是地理坐标，输出的是XYZ坐标
VBF_MAPAUX_EXPORT void VBF_Smooth(CVBFO_SGNodeMap* pNodeMap,std::vector<osg::Vec3d>& vRawPathGeo, std::vector<osg::Vec3d>& aPathSmooth,int numPtSmoothed=100);
// 对路径进行光滑，绝对高度，输入的是地理坐标，输出的是XYZ坐标
VBF_MAPAUX_EXPORT void VBF_Smooth(const CVBF_SpatialReference* pSRS,std::vector<osg::Vec3d>& vRawPathGeo, std::vector<osg::Vec3d>& aPathSmooth,int numPtSmoothed=100);

#endif
