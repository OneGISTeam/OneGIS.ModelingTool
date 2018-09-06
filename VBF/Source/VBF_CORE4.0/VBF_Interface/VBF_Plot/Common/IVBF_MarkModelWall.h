//*******************************************************************
// FileName��IVBF_MarkModelWall.h
// Function��ʵ��ģ�ͽӿڣ���ά�ռ��е�ֱ��ǽ
// Author:   ��Ө
// Date:     2014-08-15
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_WALL_H__
#define __IVBF_MARK_MODEL_WALL_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec3d>
#include <Types/Vec4>
#include <vector>


class IVBF_MarkModelWall : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelWall() {}

    // ����/��ȡǽ�������ߵ����괮���������꣩
    // ������vPointsGeo -- ����������ǰ��ά��ʾ���Ⱥ�γ�ȣ�����ά��ʾǽ�����ĸ߳�ֵ������ά��ʾǽ�ײ��ĸ߳�ֵ
    // ������bNeedInterpolate -- �Ƿ���Ҫ��ϵͳ�ڲ��ش�Բ�߲�ֵ
    virtual void SetPointsGeo(const std::vector<osg::Vec4d>& vPointsGeo, bool bNeedInterpolate)=0;
    virtual void GetPointsGeo(std::vector<osg::Vec4d>& vPointsGeo, bool& bNeedInterpolate)=0;

    // ����/��ȡǽ�Ķ��������Ƿ�ɼ�
    virtual void SetLineVisible(bool bVisible)=0;
    virtual bool IsLineVisible()=0;

    // ����/��ȡǽ�Ķ���������ʽ
    virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetLineStyle()=0;

    // ����/��ȡǽ��Ľ���ɫ
    virtual void SetColor(const osg::Vec4f& colorTop, const osg::Vec4f& colorBottom)=0;
    virtual void GetColor(osg::Vec4f& colorTop, osg::Vec4f& colorBottom)=0;

	// ����/��ȡ����ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

	// ����/��ȡ�������ݺ᷽����ظ�������Ĭ��ֵ��Ϊ1
	virtual void SetNumTexRepeats(int nNumRows, int nNumCols)=0;
	virtual void GetNumTexRepeats(int& nNumRows, int& nNumCols)=0;

	// ����/��ȡǽ�������͸���ȣ�ֵ��Ϊ[0.0, 1.0]��Ĭ��ֵΪ1.0��
	virtual void  SetTexAlpha(float fAlpha)=0;
	virtual float GetTexAlpha()=0;
};

#endif 
