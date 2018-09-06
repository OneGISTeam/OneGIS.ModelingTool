//************************************************************************
// FileName��IVBF_MarkModelField.h
// Function������ʵ��ģ�ͽӿڣ��뺣���йصĸ��ೡ����糡���������¶ȡ��ζȵ�
// Author:   ��Ө
// Date:     2018-01-16
//************************************************************************

#ifndef __IVBF_MARK_MODEL_FIELD_H__
#define __IVBF_MARK_MODEL_FIELD_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Marine/VBF_3DPlotDataTypes_Marine.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/Image>


// ������ϢID��
const char VBF_MESSAGE_3DPLOT_MARKFIELD_SHOWINFODIALOG[]    = "Message: MarkField ShowInfoDialog";      // ��Ϣ����Ҫ��ʾ��ģ����Ϣ��pSender=pIMark, nValue=0��pValue=osg::Vec2f*(�Ի������Ļ���꣬����ΪNULL)
const char VBF_MESSAGE_3DPLOT_MARKFIELD_UPDATEINFODIALOG[]  = "Message: MarkField UpdateInfoDialog";    // ��Ϣ����Ҫ���³�ģ����Ϣ��pSender=pIMark, nValue=0��pValue=NULL
const char VBF_MESSAGE_3DPLOT_MARKFIELD_CLOSEINFODIALOG[]   = "Message: MarkField CloseInfoDialog";     // ��Ϣ����Ҫ�رճ�ģ����Ϣ�Ի���nValue=0��pValue=pIMark


//--------------------------------------------------------------------
// ����ṹ�壺VBF_FIELD_TYPE
// �ṹ����������������
//--------------------------------------------------------------------
enum VBF_FIELD_TYPE
{
	VBF_FIELD_WIND			= 0,  // �糡��Ĭ��ֵ��
	VBF_FIELD_OCEANCURRENT	= 1,  // ����
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelField
// �ӿ��������뺣���йصĸ��ೡ
//--------------------------------------------------------------------
class IVBF_MarkModelField : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelField() {}

	// ����/��ȡ���ݵ������ļ�������·�����������ͣ�����ļ������ڻ򲻷���Ҫ�󣬷���false
    virtual bool SetFileName(const std::string& strFileName, VBF_FIELD_TYPE nType)=0;
    virtual const std::string& GetFileName()=0;
	virtual VBF_FIELD_TYPE     GetFieldType()=0;

	// ����/��ȡ��ת���ɵ�ͼ��ĳߴ磬Ĭ��ֵΪ512*512
    virtual void SetImageSize(int nWidth, int nHeight)=0;
    virtual void GetImageSize(int& nWidth, int& nHeight)=0;

	// ����/��ȡ���ٵĵ���ϵ����Ĭ��ֵΪ1.0
    virtual void  SetSpeedScale(float fScale)=0;
    virtual float GetSpeedScale()=0;

	// ��ȡ��������Ϣ
	virtual int  GetNumDepth()=0;	// ��ȡ�����������������
	virtual bool GetGeoRange(double& dL0, double& dL1, double& dB0, double& dB1)=0;  // ��ȡ��γ�ȷ�Χ

	// ����/��ȡĳ����ȵ������Ƿ�ɼ�
	virtual void SetDepthVisible(int nDepthIndex, bool bVisible)=0;
	virtual bool IsDepthVisible(int nDepthIndex)=0;

	// ����/��ȡÿ����Ȳ�ĺ�ȣ���λ���ף�Ĭ��ֵΪ50000��
    virtual void  SetDepthThickness(float fThickness)=0;
	virtual float GetDepthThickness()=0;
};

#endif 
