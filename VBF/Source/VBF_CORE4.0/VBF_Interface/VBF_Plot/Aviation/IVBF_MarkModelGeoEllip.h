//*******************************************************************
// FileName��IVBF_MarkModelGeoEllip.h
// Function��ʵ��ģ�ͣ��������򣬼������һ�µ�������
// Author:   ��Ө
// Date:     2015-08-11
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_GEOELLIP_H__
#define __IVBF_MARK_MODEL_GEOELLIP_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Aviation/VBF_3DPlotDataTypes_Aviation.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <string>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelGeoEllip
// �ӿ��������������򣬼������һ�µ����壬ʹ�õ��������еľ��Ⱥ�γ��
//--------------------------------------------------------------------
class IVBF_MarkModelGeoEllip : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelGeoEllip() {}

	// ����/��ȡ����ľ�γ�ȷ�Χ��Ĭ��ֵ�ֱ�Ϊ[-180, 180]��[-90, 90]
	virtual void SetTess(double dL0, double dL1, double dB0, double dB1)=0;
	virtual void GetTess(double& dL0, double& dL1, double& dB0, double& dB1)=0;

    // ����/��ȡ������ĳ��̰��ᣨĬ��ֵ�ֱ�Ϊ��ǰ��������ĳ��̰��ᣬ��λ���ף�
    virtual void SetRadius(double dRadiusEquator, double dRadiusPolar)=0;
    virtual void GetRadius(double& dRadiusEquator, double& dRadiusPolar)=0;

	// ����/��ȡ����ֱ����ݺ᷽�򣨼����Ⱥ�γ�ȷ��򣩵ķָ���
	virtual void SetNumSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSplit(int& nNumSplitRow, int& nNumSplitCol)=0;

	// ����/��ȡ����ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

	// ����/��ȡ�����͸���ȣ�ֵ��Ϊ[0.0, 1.0]��Ĭ��ֵΪ0.6��
	virtual void  SetTexAlpha(float fAlpha)=0;
	virtual float GetTexAlpha()=0;
};


#endif 
