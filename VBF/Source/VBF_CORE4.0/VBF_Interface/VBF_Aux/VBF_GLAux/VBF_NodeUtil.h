//***************************************************************************************
// FileName��VBF_NodeUtil.h
// Function��Node���ù���
// Author:   ��Ө
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



// ������ʾ�ֱ��ʣ���/���أ�
// ������pICamera -- �ͻ����������������ΪNULL��
VBF_GLAUX_EXPORT bool VBF_ComputePixelSize(osg::IVBF_Camera* pICamera, osg::Vec4& vPixelSize);

// ����HUD������Ա���2D�ռ��л���ͼԪ
// ������pViewportRef -- ��HUD����ȴ���ӿڣ����ΪNULL��ʹ����Ļ�ֱ��ʴ�С
VBF_GLAUX_EXPORT osg::Camera* VBF_CreateHUDCamera(osg::Viewport* pViewportRef);

VBF_GLAUX_EXPORT osg::IVBF_SGNode* VBF_FindFirstNamedNode(const std::string& name,osg::IVBF_SGNode& node);
VBF_GLAUX_EXPORT void VBF_SetCenterCelestialBody(std::string sName);


class VBF_GLAUX_EXPORT CVBF_NodeUtil
{
public:

	// ��ȡ�ڵ��Χ�е����ĵ�
	static bool	GetNodeCenter(osg::IVBF_SGNode* pNode, osg::Vec3d& center);

	// ��ȡ�ڵ���������
	static bool	GetNodeMatrixInWorld(osg::IVBF_SGNode* pNode, osg::Matrixd& mat);

	// ��ȡ�ڵ����������
	static bool	GetNodePosInWorld(osg::IVBF_SGNode* pNode, osg::Vec3d& ptWorld);

	// ��ȡ�ڵ�İ�Χ��
	static bool GetNodeBoundingBox(osg::IVBF_SGNode* pNode, osg::BoundingBox& box);

	// ��ȡ�ڵ�����������ϵ�µİ�Χ��
	static bool GetNodeBoundingBoxInWorld(osg::IVBF_SGNode* pNode, osg::BoundingBox& box);

	// �ѽڵ��Χ����ģ������ϵת������������ϵ
	static bool NodeBoundingBoxModelToWorld(osg::IVBF_SGNode* pNode, const osg::BoundingBox& boxInModel, osg::BoundingBox& boxInWorld);

	// ��ȡ�ڵ��Χ������Ļ�ϵ���Ӿ���
	static bool GetNodeBoundingBoxInScreen(osg::Camera* pCamera, osg::IVBF_SGNode* pNode, float& left, float& top, float& right, float& bottom);

	// ���ƽڵ���������ֵ
	static bool CopyNodeUserValues(osg::IVBF_SGNode* pNodeSrc, osg::IVBF_SGNode* pNodeDst);	

	// �ڿ���̨������ڵ����и��׽ڵ�ĳ���ͼ·��
	static bool PrintParentalNodePath(osg::IVBF_SGNode* pNode, unsigned int nPathIndex=0, osg::IVBF_SGNode* haltTraversalAtNode=0);
};


#endif
