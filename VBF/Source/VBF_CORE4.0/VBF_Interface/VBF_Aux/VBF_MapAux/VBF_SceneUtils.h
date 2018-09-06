//***************************************************************************************
// FileName��VBF_SceneUtils.h
// Function���볡���йصĹ��ߺ���
// Author:   ��Ө
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


// ��ȡ������ά����������ͼ
VBF_MAPAUX_EXPORT IVBF_View* VBF_GetMainView(IVBF_3DMainCtrl* pI3DMainCtrl);

// ��ȡ����ͼ�е������
VBF_MAPAUX_EXPORT osg::IVBF_Camera* VBF_GetMainCamera(IVBF_3DMainCtrl* pI3DMainCtrl);

// ��ȡ������е����ӿ�
VBF_MAPAUX_EXPORT osg::Viewport* VBF_GetMainViewport(IVBF_3DMainCtrl* pI3DMainCtrl);

// ��ȡ����ͼ�еĵ�ͼ�ڵ�
VBF_MAPAUX_EXPORT CVBFO_SGNodeMap* VBF_GetMainMapNode(IVBF_3DMainCtrl* pI3DMainCtrl);


// ��ȡ֡�ٶȣ���λ��֡/�룩
VBF_MAPAUX_EXPORT double VBF_GetFPS(IVBF_3DMainCtrl* pI3DMainCtrl);

#endif
