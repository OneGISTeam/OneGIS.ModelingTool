//***************************************************************************************
// FileName：VBF_NodeUtil.h
// Function：Node常用工具
// Author:   杜莹
// Date:     2012-04-11
//***************************************************************************************

#ifndef __VBF_NODE_UTIL_H__
#define __VBF_NODE_UTIL_H__

#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <Types/Vec3d>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNode.h>
#include <Types/VBF_BoundingBox.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>
using namespace osg;

VBF_GLAUX_EXPORT const Matrix& VBF_GetEarthMatrixECI(IVBF_View* pIView);



// 计算显示分辨率（米/像素）
// 参数：pICamera -- 客户区的主相机（不能为NULL）
VBF_GLAUX_EXPORT bool VBF_ComputePixelSize(osg::IVBF_Camera* pICamera, osg::Vec4& vPixelSize);

// 创建HUD相机，以便在2D空间中绘制图元
// 参数：pViewportRef -- 与HUD相机等大的视口，如果为NULL，使用屏幕分辨率大小
VBF_GLAUX_EXPORT osg::Camera* VBF_CreateHUDCamera(osg::Viewport* pViewportRef);

VBF_GLAUX_EXPORT osg::IVBF_SGNode* VBF_FindFirstNamedNode(const std::string& name,osg::IVBF_SGNode& node);
VBF_GLAUX_EXPORT void VBF_SetCenterCelestialBody(std::string sName);


class VBF_GLAUX_EXPORT CVBF_NodeUtil
{
public:

	// 获取节点包围盒的中心点
	static bool	GetNodeCenter(osg::IVBF_SGNode* pNode, osg::Vec3d& center);

	// 获取节点的世界矩阵
	static bool	GetNodeMatrixInWorld(osg::IVBF_SGNode* pNode, osg::Matrixd& mat);

	// 获取节点的世界坐标
	static bool	GetNodePosInWorld(osg::IVBF_SGNode* pNode, osg::Vec3d& ptWorld);

	// 获取节点的包围盒
	static bool GetNodeBoundingBox(osg::IVBF_SGNode* pNode, osg::BoundingBox& box);

	// 获取节点在世界坐标系下的包围盒
	static bool GetNodeBoundingBoxInWorld(osg::IVBF_SGNode* pNode, osg::BoundingBox& box);

	// 把节点包围盒由模型坐标系转换到世界坐标系
	static bool NodeBoundingBoxModelToWorld(osg::IVBF_SGNode* pNode, const osg::BoundingBox& boxInModel, osg::BoundingBox& boxInWorld);

	// 获取节点包围盒在屏幕上的外接矩形
	static bool GetNodeBoundingBoxInScreen(osg::Camera* pCamera, osg::IVBF_SGNode* pNode, float& left, float& top, float& right, float& bottom);

	// 复制节点所有属性值
	static bool CopyNodeUserValues(osg::IVBF_SGNode* pNodeSrc, osg::IVBF_SGNode* pNodeDst);	

	// 在控制台中输出节点所有父亲节点的场景图路径
	static bool PrintParentalNodePath(osg::IVBF_SGNode* pNode, unsigned int nPathIndex=0, osg::IVBF_SGNode* haltTraversalAtNode=0);
};


#endif
