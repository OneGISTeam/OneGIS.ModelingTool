//***************************************************************************************
// FileName：VBF_EarthLocationUtils.h
// Function：与坐标点在球面上的定位有关的工具函数
// Author:   杜莹
// Date:     2013-03-04
//***************************************************************************************

#ifndef __VBF_EARTH_LOCATION_UTILS_H__
#define __VBF_EARTH_LOCATION_UTILS_H__


#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <Types/Vec3d>
#include <Types/VBF_Matrixd.h>


// 把一个点转换到ECEF坐标系，并使用提供的world2local矩阵把它转换到局部坐标系，并把结果放到"output"中
VBF_MAPAUX_EXPORT void VBF_TransformAndLocalize(const osg::Vec3d& input, const CVBF_SpatialReference* inputSRS,
												osg::Vec3d& output, const CVBF_SpatialReference* outputSRS,
												const osg::Matrixd& matWorldToLocal, bool bToECEF);

// 坐标变换（地理坐标 --> 局部坐标）
VBF_MAPAUX_EXPORT void VBF_ProjectToLocal(CVBFO_SGNodeMap* pMapNode, const osg::Matrixd& matWorldToLocal,
										  const osg::Vec3d& ptGeo, osg::Vec3& ptLocal);


// 根据多边形坐标串，计算局部与世界坐标之间的转换矩阵
VBF_MAPAUX_EXPORT void VBF_ComputeLocalizers(CVBFO_SGNodeMap* pMapNode, const std::vector<osg::Vec3d>& vPointsGeo,
											 osg::Matrixd& matLocalToWorld, osg::Matrixd& matWorldToLocal);



// 计算椭球上的综合变换矩阵：模型定位到椭球（如果pMap为NULL，返回false）
VBF_MAPAUX_EXPORT bool VBF_ComputeEllipMatrix(CVBF_Map* pMap, const osg::Vec3d& vGeo, osg::Matrixd& matOut);


// 计算椭球上的综合变换矩阵：模型经过旋转，然后并定位到椭球（如果pMap为NULL，返回false）
VBF_MAPAUX_EXPORT bool VBF_ComputeEllipMatrix(CVBF_Map* pMap, const osg::Vec3d& vGeo, float fRotateZ, osg::Matrixd& matOut);


// 计算椭球上的综合变换矩阵：模型经过缩放、旋转，最后定位到椭球（如果pMap为NULL，返回false）
VBF_MAPAUX_EXPORT bool VBF_ComputeEllipMatrix(CVBF_Map* pMap, const osg::Vec3d& vGeo, float fWidth, float fHeight,
											  float fRotateZ, osg::Matrixd& matOut);
VBF_MAPAUX_EXPORT bool VBF_BuildOctree(const std::string& sFn);

#endif
