//*******************************************************************
// FileName��IVBF_MarkModelAirSpace.h
// Function��ʵ��ģ�ͣ�����ϵͳ�ڲ��ش�Բ�߲�ֵ��
// Author:   ��Ө
// Date:     2014-08-12
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_AIRSPACE_H__
#define __IVBF_MARK_MODEL_AIRSPACE_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/Aviation/VBF_3DPlotDataTypes_Aviation.h>



//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelAirSpace
// �ӿ�����������
//--------------------------------------------------------------------
class IVBF_MarkModelAirSpace : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelAirSpace() {}

    // ����/��ȡǽ��Ľ���ɫ
    virtual void SetColor(const osg::Vec4f& colorTop, const osg::Vec4f& colorBottom)=0;
    virtual void GetColor(osg::Vec4f& colorTop, osg::Vec4f& colorBottom)=0;

	// ����/��ȡǽ�������͸���ȣ�ֵ��Ϊ[0.0, 1.0]��Ĭ��ֵΪ1.0��
	virtual void  SetTexAlpha(float fAlpha)=0;
	virtual float GetTexAlpha()=0;

    // ����/��ȡǽ�Ķ��������Ƿ�ɼ�
    virtual void SetLineVisible(bool bVisible)=0;
    virtual bool IsLineVisible()=0;

    // ����/��ȡǽ�Ķ���������ʽ
    virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetLineStyle()=0;

    // ���
    virtual void Clear()=0;
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelAirSpacePolyline
// �ӿ������������ο���
//--------------------------------------------------------------------
class IVBF_MarkModelAirSpacePolyline : public IVBF_MarkModelAirSpace
{
public:
    virtual ~IVBF_MarkModelAirSpacePolyline() {}

    // ���һ������
    // ������vPointsGeo -- ����������ǰ��ά��ʾ���Ⱥ�γ�ȣ�����ά��ʾǽ�����ĸ߳�ֵ������ά��ʾǽ�ײ��ĸ߳�ֵ
    // ������nNumInter -- ��������֮��Ĳ�ֵ������ <0��ʾ��Ҫϵͳ�Զ���ֵ��=0��ʾ����Ҫ��ֵ��>0��ʾ���û�ָ���ĵ������в�ֵ
    // ������pImage -- ��������ǽ�������ͼ�񣨿���Ϊ�գ�һ�����ã�������SetColor()������
    // ������nNumTexRows, nNumTexCols -- ǽ�������ļ��ں����������ظ�����
    virtual void AddLine(const std::vector<osg::Vec4d>& vPointsGeo, int nNumInter=5,
                         osg::Image* pImage=NULL, int nNumTexRows=1, int nNumTexCols=1)=0;

    // ��ȡ�û�����ӵĵ�n�����ߵ���Ϣ
    virtual bool GetLine(int nIndex, std::vector<osg::Vec4d>& vPointsGeo, int& nNumInter,
                         osg::Image*& pImage, int& nNumTexRows, int& nNumTexCols)=0;

    // ��ȡ�û�����ӵ���������
    virtual int GetNumLines()=0;
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelAirSpaceArc
// �ӿ������������ο���
//--------------------------------------------------------------------
class IVBF_MarkModelAirSpaceArc : public IVBF_MarkModelAirSpace
{
public:
    virtual ~IVBF_MarkModelAirSpaceArc() {}

    // ����/��ȡ������״����
    // ������ptCenterGeo -- ���򶥲����ڵ�Բ�ģ��������꣩
    //      fRadius     -- �뾶����λ���ף�
    //      fAngleStart, fAngleEnd -- ��ʼ����ֹ�Ƕȣ�����������ļнǣ���λ���Ƕȣ�
    //      fTheta      -- Բ����������ĽǶȼ������λ���Ƕȣ�ֵ��Ϊ[1, 30]��
    virtual void SetTess(const osg::Vec3d& ptCenterGeo, float fRadius, float fAngleStart, float fAngleEnd, float fTheta=5.0)=0;
    virtual void GetTess(osg::Vec3d& ptCenterGeo, float& fRadius, float& fAngleStart, float& fAngleEnd, float& fTheta)=0;

    // ����/��ȡ���������߶ȣ��ø߶�ֵ���ܴ���Բ�ĵ�ĸ߳�ֵ
    virtual void   SetHeight(double dHeight)=0;
    virtual double GetHeight()=0;

	// ����/��ȡǽ������ͼ��ָ�루һ�����øú�����������SetColor()������
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

	// ����/��ȡǽ���������ݺ᷽����ظ�������Ĭ��ֵ��Ϊ1
	virtual void SetNumTexRepeats(int nNumRows, int nNumCols)=0;
	virtual void GetNumTexRepeats(int& nNumRows, int& nNumCols)=0;
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelAirSpaceCircle
// �ӿ�������Բ�ο���
//--------------------------------------------------------------------
class IVBF_MarkModelAirSpaceCircle : public IVBF_MarkModelAirSpace
{
public:
    virtual ~IVBF_MarkModelAirSpaceCircle() {}

    // ����/��ȡ������״����
    // ������ptCenterGeo -- ����Բ�ģ��������꣩
    //      fRadius     -- �뾶����λ���ף�
    //      fTheta      -- Բ����������ĽǶȼ������λ���Ƕȣ�ֵ��Ϊ[1, 30]��
    virtual void SetTess(const osg::Vec3d& ptCenterGeo, float fRadius, float fTheta=5.0)=0;
    virtual void GetTess(osg::Vec3d& ptCenterGeo, float& fRadius, float& fTheta)=0;

    // ����/��ȡ���������߶ȣ��ø߶�ֵ���ܴ��ڶ���Բ�ĵ�ĸ߳�ֵ
    virtual void   SetHeight(double dHeight)=0;
    virtual double GetHeight()=0;

	// ����/��ȡǽ������ͼ��ָ�루һ�����øú�����������SetColor()������
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

	// ����/��ȡǽ���������ݺ᷽����ظ�������Ĭ��ֵ��Ϊ1
	virtual void SetNumTexRepeats(int nNumRows, int nNumCols)=0;
	virtual void GetNumTexRepeats(int& nNumRows, int& nNumCols)=0;
};


#endif 
