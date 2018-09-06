
//***************************************************************************************
// FileName��VBF_EarthMath.h
// Function���������йص���ѧ���ߺ���
// Author:   ��Ө
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



// �����������������֮��Ĳ�ֵ�������ش�Բ�߲�ֵ���������յ㣩
VBF_MAPAUX_EXPORT int VBF_ComputeNumInterPoints(CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1, double hMin);


// ���������������֮���ش�Բ�߽��в�ֵ���߳�ʹ�����Բ�ֵ��
// ������nNumInter -- ����������֮��Ĳ�ֵ�������������յ㣩
VBF_MAPAUX_EXPORT void VBF_InterpolateGreatCircle(const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1,
                                                  int nNumInter, std::vector<osg::Vec3d>& vOutGeo, double dDeltaH=1.0);

// �ڶ�����������֮���ش�Բ�߽��в�ֵ���߳�ʹ�����Բ�ֵ��
// ������nNumInter -- ����������֮��Ĳ�ֵ���������������㣩
VBF_MAPAUX_EXPORT void VBF_InterpolateGreatCircle(const std::vector<osg::Vec3d>& vGeoSrc,
                                                  int nNumInter, std::vector<osg::Vec3d>& vGeoDst);


// ���������������֮���ش�Բ�߽��в�ֵ���߳�ʹ�����Բ�ֵ����ֵ�����Զ����㣩
// ������hMin -- ���е����С�߳�ֵ�����ڼ�������֮��Ĳ�ֵ����
VBF_MAPAUX_EXPORT void VBF_InterpolateGreatCircle(CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1,
                                                  const double& hMin, std::vector<osg::Vec3d>& vOutGeo, double dDeltaH=1.0);


// ���������������֮���ش�Բ�߽��в�ֵ���߳�ʹ�����Բ�ֵ����ֵ�����Զ����㣩
VBF_MAPAUX_EXPORT void VBF_InterpolateGreatCircle(CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1,
                                                  std::vector<osg::Vec3d>& vOutGeo, double dDeltaH=1.0);


// �ڶ�����������֮���ش�Բ�߽��в�ֵ���߳�ʹ�����Բ�ֵ��
// ������hMin -- ���е����С�߳�ֵ�����ڼ�������֮��Ĳ�ֵ����
VBF_MAPAUX_EXPORT void VBF_InterpolateGreatCircle(CVBFO_SGNodeMap* pMapNode, const std::vector<osg::Vec3d>& vGeoSrc,
                                                  double hMin, std::vector<osg::Vec3d>& vGeoDst);


// �ڶ�����������֮���ش�Բ�߽��в�ֵ���߳�ʹ�����Բ�ֵ��
VBF_MAPAUX_EXPORT void VBF_InterpolateGreatCircle(CVBFO_SGNodeMap* pMapNode, const std::vector<osg::Vec3d>& vGeoSrc,
                                                  std::vector<osg::Vec3d>& vGeoDst);


// ���������������֮�����Բ�ֵ(�������ӵ�Ͻ�ʱ���д��޸ģ��߳�ֵҲ�������Բ�ֵ)
VBF_MAPAUX_EXPORT void VBF_InterpolateLinear(const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1,
                                             int nNumInter, std::vector<osg::Vec3d>& vOutGeo);


// ��������ĵ������괮����ȡ���ڵ�������ϵ�µİ�Χ�У�����������Ϊ0������false
VBF_MAPAUX_EXPORT bool VBF_GetBoundingBoxInGeo(const std::vector<osg::Vec3d>& vPointsGeo, osg::BoundingBoxd& boxInGeo);


// ��������ĵ������괮����ȡ������������ϵ�µİ�Χ�У�����������Ϊ0������false
VBF_MAPAUX_EXPORT bool VBF_GetBoundingBoxInWorld(CVBFO_SGNodeMap* pMapNode, const std::vector<osg::Vec3d>& vPointsGeo, osg::BoundingBoxd& boxInWorld);


// ��-->�ȷ���
VBF_MAPAUX_EXPORT void DegreeToDMS(double dGeoCoord, int& nDegree, int& nMinute, int& nSecond);


// ���ݵ�������(���Ȼ�γ��)�������ַ���
VBF_MAPAUX_EXPORT void FormatGeoCoord(double dGeoCoord, char* strCoord);


// ��������ֵ����������Ϣ����ʾ�߳�ֵ��
VBF_MAPAUX_EXPORT void VBF_FormatCoordInfo(double L, double B, double H, bool bCoordDMS, char* szInfo);


// ��������ֵ����������Ϣ������ʾ�߳�ֵ��
VBF_MAPAUX_EXPORT void VBF_FormatCoordInfo(double L, double B, bool bCoordDMS, char* szInfo);


// ���ݾ���ֵ���������Ϣ
// ������szPrefix -- ��Ϣǰ׺���硰���룺�������ܾ���=��
//-------------------------------------------------------------------------
//VBF_MAPAUX_EXPORT void VBF_FormatDistInfo(double dDist, const char* szPrefix, char* szInfo);


// �������ֵ���������Ϣ
//VBF_MAPAUX_EXPORT void VBF_FormatAreaInfo(double dArea, char* szInfo);


// �������������ߵĳ���
VBF_MAPAUX_EXPORT double VBF_GetDist(const std::vector<osg::Vec3d>& vPointsGeo, osgEarth::GeoInterpolation nGeoInterpolation,double dR);


// ��������������֮��ľ���
VBF_MAPAUX_EXPORT double VBF_GetDist(const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1, osgEarth::GeoInterpolation nGeoInterpolation,double dR);


// ������������ϵ������֮��ľ���
VBF_MAPAUX_EXPORT double VBF_GetDistInWorld(osg::IVBF_Camera* pICamera, CVBFO_SGNodeMap* pMapNode,
											const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1);


// ������������ϵ�����ߵĳ���
VBF_MAPAUX_EXPORT double VBF_GetDistInWorld(osg::IVBF_Camera* pICamera, CVBFO_SGNodeMap* pMapNode,
											const std::vector<osg::Vec3d>& vPointsGeo);


// ���������ϼ����������
VBF_MAPAUX_EXPORT double VBF_GetArea(int nNumVertices, osg::Vec3d* pGeoVertices);


// �������ε���Ӿ��� (��������)
VBF_MAPAUX_EXPORT void VBF_CalBoundingRectGeo(const std::vector<osg::Vec3d>& vPointsGeo,
											 double& dLMin, double& dBMin, double& dLMax, double& dBMax);


// �������ε���Ӿ��� (��Ļ����)
VBF_MAPAUX_EXPORT void VBF_CalBoundingRectClient(osg::IVBF_Camera* pICamera, CVBFO_SGNodeMap* pMapNode, const std::vector<osg::Vec3d>& vPointsGeo,
												 double& xMin, double& yMin, double& xMax, double& yMax);


// װ��Dem����
// ������dLMin, dLMax, dBMin, dBMax -- Dem����ľ��Ⱥ�γ�ȷ�Χ
//		nNumRows, nNumCols -- Dem���������������
VBF_MAPAUX_EXPORT bool VBF_LoadDem(osgEarth::ElevationQuery* pElevQuery, const CVBF_SpatialReference* pPointSRS,
									double dLMin, double dBMin, double dLMax, double dBMax,
									int nNumRows, int nNumCols, double dResolution, float**& pDem);


// װ��Dem����
// ������dLMin, dLMax, dBMin, dBMax -- Dem����ľ��Ⱥ�γ�ȷ�Χ
//		 nNumRows, nNumCols -- Dem���������������
VBF_MAPAUX_EXPORT bool VBF_LoadDem(osgEarth::ElevationQuery* pElevQuery, const CVBF_SpatialReference* pPointSRS,
								   double dLMin, double dBMin, double dLMax, double dBMax,
								   int nNumRows, int nNumCols, double dResolution, std::vector<float>& vHeightList);


// װ��Dem���ݣ����������²�����˫���Բ�ֵ��
// ������dLMin, dBMin, dLMax, dBMax -- Dem����ľ��Ⱥ�γ�ȷ�Χ
//		nNumRowsSrc, nNumColsSrc   -- ��Ҫ��ȡ��Dem�����ܶ�
//	    nNumRowsDst, nNumColsDst   -- ��ֵ���Dem�����ܶ�
VBF_MAPAUX_EXPORT bool VBF_LoadAndResampleDem(osgEarth::ElevationQuery* pElevQuery, const CVBF_SpatialReference* pPointSRS,
											  double dLMin, double dBMin, double dLMax, double dBMax, double dResolution,
											  int nNumRowsSrc, int nNumColsSrc, int nNumRowsDst, int nNumColsDst, float**& pDem);


// ���㵥���¶�
VBF_MAPAUX_EXPORT float VBF_Slope(int i, int j, float** pDem, short nRows, short nCols);


// ������ԭ�㹹�ɵķ�λ�ǣ���λ�����ȣ�
VBF_MAPAUX_EXPORT double VBF_GetAzimuthAngle(double dx, double dy);


// ��ȡһ���߶ξ������������ص㣨DDA: Digital Differential Analyzer����ֵ΢�ַ���
VBF_MAPAUX_EXPORT void VBF_LineDDA(int x0, int y0, int x1, int y1, std::vector<osg::Vec2i>& vPoints);


// ��������������һ��ķ���
VBF_MAPAUX_EXPORT bool VBF_CalEllipNormal(CVBFO_SGNodeMap* pMapNode, double L, double B, osg::Vec3d& vNormal);

// ��·�����й⻬������ڵ��θ߶ȣ�������ǵ������꣬�������XYZ����
VBF_MAPAUX_EXPORT void VBF_Smooth(CVBFO_SGNodeMap* pNodeMap,std::vector<osg::Vec3d>& vRawPathGeo, std::vector<osg::Vec3d>& aPathSmooth,int numPtSmoothed=100);
// ��·�����й⻬�����Ը߶ȣ�������ǵ������꣬�������XYZ����
VBF_MAPAUX_EXPORT void VBF_Smooth(const CVBF_SpatialReference* pSRS,std::vector<osg::Vec3d>& vRawPathGeo, std::vector<osg::Vec3d>& aPathSmooth,int numPtSmoothed=100);

#endif
