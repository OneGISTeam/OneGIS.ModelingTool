//***************************************************************************************
// FileName：VBF_SceneUtils.h
// Function：与场景有关的工具函数
// Author:   杜莹
// Date:     2014-04-04
//***************************************************************************************

#ifndef __VBF_SCENE_UTILS_H__
#define __VBF_SCENE_UTILS_H__


#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransformCamera.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>
#include <Types/Vec3d>
#include <Types/Vec4>


// 获取整个三维场景的主视图
VBF_MAPAUX_EXPORT IVBF_View* VBF_GetMainView(IVBF_3DMainCtrl* pI3DMainCtrl);

// 获取主视图中的主相机
VBF_MAPAUX_EXPORT osg::IVBF_Camera* VBF_GetMainCamera(IVBF_3DMainCtrl* pI3DMainCtrl);

// 获取主相机中的主视口
VBF_MAPAUX_EXPORT osg::Viewport* VBF_GetMainViewport(IVBF_3DMainCtrl* pI3DMainCtrl);

// 获取主视图中的地图节点
VBF_MAPAUX_EXPORT CVBFO_SGNodeMap* VBF_GetMainMapNode(IVBF_3DMainCtrl* pI3DMainCtrl);


// 获取帧速度（单位：帧/秒）
VBF_MAPAUX_EXPORT double VBF_GetFPS(IVBF_3DMainCtrl* pI3DMainCtrl);

#endif
