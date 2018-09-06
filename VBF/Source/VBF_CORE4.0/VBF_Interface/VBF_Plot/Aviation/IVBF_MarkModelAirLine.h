//*******************************************************************
// FileName��IVBF_MarkModelAirLine.h
// Function��ʵ��ģ�ͣ�����
// Author:   ��Ө
// Date:     2014-01-07
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_AIRLINE_H__
#define __IVBF_MARK_MODEL_AIRLINE_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/Aviation/VBF_3DPlotDataTypes_Aviation.h>



//------------------------------------------------------------------
// ����ö�٣�EVBF_AIRLINE_PART
// ö�����������ߵĸ�������
//------------------------------------------------------------------
enum EVBF_AIRLINE_PART
{
	VBF_AIRLINE_PART_ORIGN		= 0,	// ԭʼ����
	VBF_AIRLINE_PART_SMOOTH		= 1,	// �⻬��ĺ���
	VBF_AIRLINE_PART_HINT		= 2,	// �߶�ָʾ��
	VBF_AIRLINE_PART_PIPE		= 3,	// ����ͨ�����պϻ���
	VBF_AIRLINE_PART_COUNT				// ����
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelAirLine
// �ӿ�����������
//--------------------------------------------------------------------
class IVBF_MarkModelAirLine : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelAirLine() {}

	// ����/��ȡ���ߵ����괮���������꣩������nNumInterPoints��ʾ��ֵ����
	virtual void SetPointsGeo(const std::vector<osg::Vec3d>& vPointsGeo, int nNumInterPoints=100)=0;
	virtual void GetPointsGeo(std::vector<osg::Vec3d>& vPointsGeo, int& nNumInterPoints)=0;

	// ��ȡ���߹⻬������괮���������꣩
	virtual const std::vector<osg::Vec3d>& GetSmoothPointsGeo()=0;

	// ����/��ȡ����ͨ���Ŀ�ȣ���λ���ף�
	virtual void  SetPipeWidth(float fWidth)=0;
	virtual float GetPipeWidth()=0;

	// ����/��ȡ����ͨ���ĸ߶ȣ���λ���ף�
	virtual void  SetPipeHeight(float fHeight)=0;
	virtual float GetPipeHeight()=0;

	// ����/��ȡĳ�����ֵĿɼ���
	virtual void SetPartVisible(EVBF_AIRLINE_PART nPart, bool bVisible)=0;
	virtual bool IsPartVisible(EVBF_AIRLINE_PART nPart)=0;

	// ����/��ȡĳ�����ֵ�������ʽ
	virtual void                 SetPartLineStyle(EVBF_AIRLINE_PART nPart, const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetPartLineStyle(EVBF_AIRLINE_PART nPart)=0;

	// ����/��ȡԭʼ���ߵ��Ƿ�ɼ���Ĭ��ֵΪtrue��
	virtual void SetOrignPointVisible(bool bVisible)=0;
	virtual bool IsOrignPointVisible()=0;

    // ����/��ȡԭʼ���ߵ����ʽ�����Ĭ�ϳߴ�Ϊ6.0��
    virtual void                  SetOrignPointStyle(const VBF_POINTSTYLE& style)=0;
    virtual const VBF_POINTSTYLE& GetOrignPointStyle()=0;

    // ����/��ȡԭʼ���ߵ�ı�ǩ�Ƿ�ɼ���Ĭ��Ϊ�ɼ���
    virtual void  SetOrignPointLabelVisible(bool bVisible)=0;
    virtual bool  IsOrignPointLabelVisible()=0;

	// ����/��ȡԭʼ���ߵ�ı�ǩ��ʽ
	virtual void                 SetOrignPointLabelStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetOrignPointLabelStyle()=0;
};


#endif 
