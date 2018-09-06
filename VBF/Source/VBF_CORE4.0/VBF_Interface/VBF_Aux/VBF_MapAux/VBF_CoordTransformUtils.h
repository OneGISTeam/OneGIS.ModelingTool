//***************************************************************************************
// FileName��VBF_CoordTransformUtils.h
// Function��������ת���йصĹ��ߺ���
// Author:   ��Ө
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


// ��ȡһ����Ч������ֵ�����ڶ���������/����������г�ʼ��
VBF_MAPAUX_EXPORT const osg::Vec3d& VBF_GetPosInvalid();

// �ж�һ������ֵ�Ƿ���Ч
VBF_MAPAUX_EXPORT bool VBF_IsPosInvalid(const osg::Vec3d& vPos);

// ����ĳ����ͼ�еĵ�ͼ�ڵ㣨ע�⣺���Ƶ�����øú�������Ӱ��Ч�ʣ�
VBF_MAPAUX_EXPORT CVBFO_SGNodeMap* VBF_FindMapNode(IVBF_View* pIView);

// ��ȡ�̲߳�ѯ���ߣ��Ա㹲�����е����ݻ���
VBF_MAPAUX_EXPORT osgEarth::ElevationQuery* VBF_GetElevQuery(CVBFO_SGNodeMap* pMapNode);

// �������� --> ��������
// ������pMapNode -- ��ͼ�ڵ㣨����ΪNULL��
VBF_MAPAUX_EXPORT bool VBF_WorldToGeo(CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptWorld, osg::Vec3d& ptGeo);

// �������� --> ��������
// ������pMapNode    -- ��ͼ�ڵ㣨����ΪNULL��
//      bAltAbsolute -- ptGeo�еĸ߳�ֵ�Ƿ�Ϊ���Ը߶ȣ���MSL/HAE���㣩
VBF_MAPAUX_EXPORT bool VBF_GeoToWorld(CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo, bool bAltAbsolute, osg::Vec3d& ptWorld);

// �������� --> ��Ļ�ͻ�������
// ������pICamera -- �ͻ����������������ΪNULL��
VBF_MAPAUX_EXPORT bool VBF_WorldToClient(osg::IVBF_Camera* pICamera, const osg::Vec3d& ptWorld, osg::Vec3d& ptWin);

// �ͻ������� --> ��������
// ������pIView -- �ͻ������ڵ���ͼ������ΪNULL��
VBF_MAPAUX_EXPORT bool VBF_ClientToWorld(IVBF_View* pIView, float x, float y, osg::Vec3d& ptWorld);

// �������� --> ��Ļ�ͻ�������
// ������pICamera -- �ͻ����������������ΪNULL��
//      pMapNode -- ��ͼ�ڵ㣨����ΪNULL��
VBF_MAPAUX_EXPORT bool VBF_GeoToClient(osg::IVBF_Camera* pICamera, CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo, bool bAltAbsolute, osg::Vec3d& ptWin);

// �ͻ������� --> �������꣨��������ȵر�ģ�͵ĸ߶ȣ�
// ������pIView -- �ͻ������ڵ���ͼ������ΪNULL��
//      pMapNode -- ��ͼ�ڵ㣨����ΪNULL��
VBF_MAPAUX_EXPORT bool VBF_ClientToGeo(IVBF_View* pIView, CVBFO_SGNodeMap* pMapNode, float x, float y, osg::Vec3d& ptGeo);

// ���ݵ��������ȡ�õ�ĸ߳�ֵ���ֱ������û�ָ��
// ������pMapNode -- ��ͼ�ڵ㣨����ΪNULL��
//      dDesiredResolution -- ���ο�����������������֮��ľ��ȼ������λ����/�㣩
VBF_MAPAUX_EXPORT bool VBF_GetElevation(CVBFO_SGNodeMap* pMapNode, double dDesiredResolution, double L, double B, double& H);

// ���ݵ��������ȡ�õ�ĸ߳�ֵ���ֱ����뵱ǰ���������൱
// ������pICamera -- �ͻ����������������ΪNULL��
//      pMapNode -- ��ͼ�ڵ㣨����ΪNULL��
VBF_MAPAUX_EXPORT bool VBF_GetElevationAvail(osg::IVBF_Camera* pICamera, CVBFO_SGNodeMap* pMapNode, double L, double B, double& H);

// ���ݵ��������ȡ�õ�ĸ߳�ֵ���ֱ���Ϊ���ݵ���߷ֱ���
// ������pMapNode -- ��ͼ�ڵ㣨����ΪNULL��
VBF_MAPAUX_EXPORT bool VBF_GetElevationBest(CVBFO_SGNodeMap* pMapNode, double L, double B, double& H);

// ����ĳ�������괦����ʾ�ֱ��ʣ���λ����/���أ�
// ������pICamera -- �ͻ����������������ΪNULL��
//      pMapNode -- ��ͼ�ڵ㣨����ΪNULL��
VBF_MAPAUX_EXPORT bool VBF_ComputeResInMeters(osg::IVBF_Camera* pICamera, CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo, float& fRes);

// ����ĳ�������괦����ʾ�ֱ��ʣ���λ����/���أ�
// ������pICamera -- �ͻ����������������ΪNULL��
//      pMapNode -- ��ͼ�ڵ㣨����ΪNULL��
VBF_MAPAUX_EXPORT bool VBF_ComputeResInDegrees(osg::IVBF_Camera* pICamera, CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo, float& fRes);


#endif
