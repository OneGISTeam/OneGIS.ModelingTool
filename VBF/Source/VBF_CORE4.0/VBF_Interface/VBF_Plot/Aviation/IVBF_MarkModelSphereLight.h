//*******************************************************************
// FileName��IVBF_MarkModelSphereLight.h
// Function��ʵ��ģ�ͣ������Ӱ
// Author��  ��Ө
// Date��    2015-04-14
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SPHERE_LIGHT_H__
#define __IVBF_MARK_MODEL_SPHERE_LIGHT_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <Types/Vec3d>
#include <VBF_Plot/Aviation/VBF_3DPlotDataTypes_Aviation.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelSphereLight
// �ӿ�������ʵ��ģ�ͣ������Ӱ
//--------------------------------------------------------------------
class IVBF_MarkModelSphereLight : public IVBF_MarkModelPoint
{
public:
	virtual ~IVBF_MarkModelSphereLight() {}

	// ����/��������ʵ������Z���ָ��
	virtual void              SetAxis(const osg::Vec3d& vAxis)=0;
	virtual const osg::Vec3d& GetAxis()=0;

	// ����/��ȡ��Ӱ�ĺ�ȣ���λ���ף�Ĭ��ֵΪ30000�ף�
	virtual void  SetThickness(float hThickness)=0;
	virtual float GetThickness()=0;

	// �����ݺ᷽��ķָ���
	virtual void SetNumSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSplit(int& nNumSplitRow, int& nNumSplitCol)=0;
};


#endif 
