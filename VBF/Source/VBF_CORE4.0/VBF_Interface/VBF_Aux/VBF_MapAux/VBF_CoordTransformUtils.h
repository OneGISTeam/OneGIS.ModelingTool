//***************************************************************************************
// FileName：VBF_CoordTransformUtils.h
// Function：与坐标转换有关的工具函数
// Author:   杜莹
// Date:     2014-04-04
//***************************************************************************************

#ifndef __VBF_COORD_TRANSFORM_UTILS_H__
#define __VBF_COORD_TRANSFORM_UTILS_H__


#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransformCamera.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_3DMap/VBF_Terrain/ElevationQuery.h>
#include <Types/Vec3d>


// 获取一个无效的坐标值，用于对世界坐标/地理坐标进行初始化
VBF_MAPAUX_EXPORT const osg::Vec3d& VBF_GetPosInvalid();

// 判断一个坐标值是否无效
VBF_MAPAUX_EXPORT bool VBF_IsPosInvalid(const osg::Vec3d& vPos);

// 查找某个视图中的地图节点（注意：如果频繁调用该函数，会影响效率）
VBF_MAPAUX_EXPORT CVBFO_SGNodeMap* VBF_FindMapNode(IVBF_View* pIView);

// 获取高程查询工具，以便共享其中的数据缓存
VBF_MAPAUX_EXPORT osgEarth::ElevationQuery* VBF_GetElevQuery(CVBFO_SGNodeMap* pMapNode);

// 世界坐标 --> 地理坐标
// 参数：pMapNode -- 地图节点（不能为NULL）
VBF_MAPAUX_EXPORT bool VBF_WorldToGeo(CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptWorld, osg::Vec3d& ptGeo);

// 地理坐标 --> 世界坐标
// 参数：pMapNode    -- 地图节点（不能为NULL）
//      bAltAbsolute -- ptGeo中的高程值是否为绝对高度（从MSL/HAE起算）
VBF_MAPAUX_EXPORT bool VBF_GeoToWorld(CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo, bool bAltAbsolute, osg::Vec3d& ptWorld);

// 世界坐标 --> 屏幕客户区坐标
// 参数：pICamera -- 客户区的主相机（不能为NULL）
VBF_MAPAUX_EXPORT bool VBF_WorldToClient(osg::IVBF_Camera* pICamera, const osg::Vec3d& ptWorld, osg::Vec3d& ptWin);

// 客户区坐标 --> 世界坐标
// 参数：pIView -- 客户区所在的视图（不能为NULL）
VBF_MAPAUX_EXPORT bool VBF_ClientToWorld(IVBF_View* pIView, float x, float y, osg::Vec3d& ptWorld);

// 地理坐标 --> 屏幕客户区坐标
// 参数：pICamera -- 客户区的主相机（不能为NULL）
//      pMapNode -- 地图节点（不能为NULL）
VBF_MAPAUX_EXPORT bool VBF_GeoToClient(osg::IVBF_Camera* pICamera, CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo, bool bAltAbsolute, osg::Vec3d& ptWin);

// 客户区坐标 --> 地理坐标（含建筑物等地表模型的高度）
// 参数：pIView -- 客户区所在的视图（不能为NULL）
//      pMapNode -- 地图节点（不能为NULL）
VBF_MAPAUX_EXPORT bool VBF_ClientToGeo(IVBF_View* pIView, CVBFO_SGNodeMap* pMapNode, float x, float y, osg::Vec3d& ptGeo);

// 根据地理坐标获取该点的高程值，分辨率由用户指定
// 参数：pMapNode -- 地图节点（不能为NULL）
//      dDesiredResolution -- 地形块中相邻两个格网点之间的经度间隔（单位：度/点）
VBF_MAPAUX_EXPORT bool VBF_GetElevation(CVBFO_SGNodeMap* pMapNode, double dDesiredResolution, double L, double B, double& H);

// 根据地理坐标获取该点的高程值，分辨率与当前场景大致相当
// 参数：pICamera -- 客户区的主相机（不能为NULL）
//      pMapNode -- 地图节点（不能为NULL）
VBF_MAPAUX_EXPORT bool VBF_GetElevationAvail(osg::IVBF_Camera* pICamera, CVBFO_SGNodeMap* pMapNode, double L, double B, double& H);

// 根据地理坐标获取该点的高程值，分辨率为数据的最高分辨率
// 参数：pMapNode -- 地图节点（不能为NULL）
VBF_MAPAUX_EXPORT bool VBF_GetElevationBest(CVBFO_SGNodeMap* pMapNode, double L, double B, double& H);

// 计算某地理坐标处的显示分辨率（单位：米/像素）
// 参数：pICamera -- 客户区的主相机（不能为NULL）
//      pMapNode -- 地图节点（不能为NULL）
VBF_MAPAUX_EXPORT bool VBF_ComputeResInMeters(osg::IVBF_Camera* pICamera, CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo, float& fRes);

// 计算某地理坐标处的显示分辨率（单位：度/像素）
// 参数：pICamera -- 客户区的主相机（不能为NULL）
//      pMapNode -- 地图节点（不能为NULL）
VBF_MAPAUX_EXPORT bool VBF_ComputeResInDegrees(osg::IVBF_Camera* pICamera, CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo, float& fRes);


#endif
