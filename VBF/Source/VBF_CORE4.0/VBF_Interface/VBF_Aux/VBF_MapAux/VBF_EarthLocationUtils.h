//***************************************************************************************
// FileName��VBF_EarthLocationUtils.h
// Function����������������ϵĶ�λ�йصĹ��ߺ���
// Author:   ��Ө
// Date:     2013-03-04
//***************************************************************************************

#ifndef __VBF_EARTH_LOCATION_UTILS_H__
#define __VBF_EARTH_LOCATION_UTILS_H__


#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <Types/Vec3d>
#include <Types/VBF_Matrixd.h>


// ��һ����ת����ECEF����ϵ����ʹ���ṩ��world2local�������ת�����ֲ�����ϵ�����ѽ���ŵ�"output"��
VBF_MAPAUX_EXPORT void VBF_TransformAndLocalize(const osg::Vec3d& input, const CVBF_SpatialReference* inputSRS,
												osg::Vec3d& output, const CVBF_SpatialReference* outputSRS,
												const osg::Matrixd& matWorldToLocal, bool bToECEF);

// ����任���������� --> �ֲ����꣩
VBF_MAPAUX_EXPORT void VBF_ProjectToLocal(CVBFO_SGNodeMap* pMapNode, const osg::Matrixd& matWorldToLocal,
										  const osg::Vec3d& ptGeo, osg::Vec3& ptLocal);


// ���ݶ�������괮������ֲ�����������֮���ת������
VBF_MAPAUX_EXPORT void VBF_ComputeLocalizers(CVBFO_SGNodeMap* pMapNode, const std::vector<osg::Vec3d>& vPointsGeo,
											 osg::Matrixd& matLocalToWorld, osg::Matrixd& matWorldToLocal);



// ���������ϵ��ۺϱ任����ģ�Ͷ�λ���������pMapΪNULL������false��
VBF_MAPAUX_EXPORT bool VBF_ComputeEllipMatrix(CVBF_Map* pMap, const osg::Vec3d& vGeo, osg::Matrixd& matOut);


// ���������ϵ��ۺϱ任����ģ�;�����ת��Ȼ�󲢶�λ���������pMapΪNULL������false��
VBF_MAPAUX_EXPORT bool VBF_ComputeEllipMatrix(CVBF_Map* pMap, const osg::Vec3d& vGeo, float fRotateZ, osg::Matrixd& matOut);


// ���������ϵ��ۺϱ任����ģ�;������š���ת�����λ���������pMapΪNULL������false��
VBF_MAPAUX_EXPORT bool VBF_ComputeEllipMatrix(CVBF_Map* pMap, const osg::Vec3d& vGeo, float fWidth, float fHeight,
											  float fRotateZ, osg::Matrixd& matOut);
VBF_MAPAUX_EXPORT bool VBF_BuildOctree(const std::string& sFn);

#endif
