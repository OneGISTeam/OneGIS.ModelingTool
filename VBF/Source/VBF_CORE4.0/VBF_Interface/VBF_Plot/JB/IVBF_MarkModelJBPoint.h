//*******************************************************************
// FileName��IVBF_MarkModelJBPoint.h
// Function��ʵ��ģ�ͣ���״����
// Author:   ��Ө
// Date:     2014-05-14
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_JB_POINT_H__
#define __IVBF_MARK_MODEL_JB_POINT_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/JB/VBF_3DPlotDataTypes_JB.h>
#include <Types/VBF_3DStyles.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelJBPoint
// �ӿ���������״����
//--------------------------------------------------------------------
class IVBF_MarkModelJBPoint : public IVBF_MarkModelPoint
{
public:
	virtual ~IVBF_MarkModelJBPoint() {}

	// ����ָ���ľ�����ļ���ģ���ھ�����еı�ţ�������״���꣬����ļ����Ų����ڣ�����false
	// ˵�����ú����������ȵ���
	virtual bool Create(const std::string& strJBFileName, unsigned int nSymbolID)=0;

	// ��ȡ�þ������ڵľ�����ļ���������·������ʵ���Ϸ���ֵ������Create()�����ĵ�һ������
	virtual std::string GetJBFileName()=0;

	// ��ȡ�����ھ�����еı��/���ƣ�ʵ���Ϸ���ֵ������Create()�����ĵڶ�������
	virtual int         GetSymbolID()=0;
	virtual std::string GetSymbolName()=0;

	// ��ȡ�����ھ�����е������/�������
	virtual int         GetSymbolClassID()=0;
    virtual std::string GetSymbolClassName()=0;
	
	// ����/��ȡ������ĳ�����ֵ��ı�����
	virtual void               SetText(int nTextIndex, const std::string& strText)=0;
	virtual const std::string& GetText(int nTextIndex)=0;

	// ����/��ȡ������ĳ�����ֵ��ı���ʽ
	virtual void                 SetTextStyle(int nTextIndex, const VBF_TEXTSTYLE& style)=0;
	virtual const VBF_TEXTSTYLE& GetTextStyle(int nTextIndex)=0;

	// ����/��ȡ���ŵĿ�ȣ�Ĭ��ֵΪ3.0��
	virtual void  SetWidth(float fWidth)=0;
	virtual float GetWidth()=0;

	// ����/��ȡ���ŵĺ��
	virtual void  SetThickness(float fThickness)=0;
	virtual float GetThickness()=0;

	// ����/��ȡ���ŵ�����ɫ
	virtual void       SetFrameColor(const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetFrameColor()=0;

	// ����/��ȡ���ŵ��ڳ���ɫ
	virtual void       SetSerifColorInner(const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetSerifColorInner()=0;

	// ����/��ȡ���ŵ������ɫ
	virtual void       SetSerifColorOuter(const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetSerifColorOuter()=0;

	// ����/��ȡ���ŵ����ɫ
	virtual void       SetFillColor(int nRgnIndex, const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetFillColor(int nRgnIndex)=0;

	// ����/��ȡ��䲿���������������İ��ݱ�����ֵ��Ϊ[0.0, 1.0]��Ĭ��ֵΪ0.2��
	virtual void  SetFillOffsetScale(float fScale)=0;
	virtual float GetFillOffsetScale()=0;

	// ����/��ȡ�ı�������������������͹��������ֵ��Ϊ[0.0, 1.0]��Ĭ��ֵΪ0.1��
	virtual void  SetTextOffsetScale(float fScale)=0;
	virtual float GetTextOffsetScale()=0;
};


#endif 
