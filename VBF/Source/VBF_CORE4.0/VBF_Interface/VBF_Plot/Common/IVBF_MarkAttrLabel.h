//*******************************************************************
// FileName��IVBF_MarkAttrLabel.h
// Function��ģ�����Խӿڣ���ǩ��������ʾģ�͵�ǰ��ĳЩ��Ϣ�����š�����ȣ�
// Author:   ��Ө
// Date:     2013-12-16
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_LABEL_H__
#define __IVBF_MARK_ATTR_LABEL_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <VBF_Plot/Common/IVBF_MarkModelText.h>


// ���幤��ID��
const char VBF_TOOL_MARKATTR_TOGGLE_LABEL[]	 = "Tool: Toggle Label Between Simple and Detail";	// ͨ�����˫���ڼ������֮���л�


//--------------------------------------------------------------------
// ����ö�٣�EVBF_LABELPOS_TYPE
// ö����������ǩ�Ķ�λ��ʽ
//--------------------------------------------------------------------
enum EVBF_LABELPOS_TYPE
{
	VBF_LABELPOS_ORIGIN			= 0,	// ģ��ԭʼ��λ�㣨Ĭ��ֵ��
	VBF_LABELPOS_BOXCENTER		= 1,	// ģ�Ͱ�Χ������
	VBF_LABELPOS_BOXCORNER		= 2,	// ģ�Ͱ�Χ�нǵ�
	VBF_LABELPOS_BOXTOPCENTER	= 3		// ģ�Ͱ�Χ�ж������ģ�ע�⣺��ʱҪ��ģ�ͱ���ΪRaster�ࣩ
};


// �����ǩ����Ҫ��ʾ��������û������ʹ�����е�һ������
#define VBF_LABELITEM_ID			0x00000001	// ģ�͵�ID��
#define VBF_LABELITEM_CODE			0x00000002	// ģ�͵ı���
#define VBF_LABELITEM_COORDGEO		0x00000004	// ģ�͵ĵ�������
#define VBF_LABELITEM_COORDECI		0x00000008	// ģ�͵ĵع�����
#define VBF_LABELITEM_COORDECF		0x00000010	// ģ�͵ĵع�����
#define VBF_LABELITEM_SIMPLE		0x00000020	// �û��Զ���ļ��ı�
#define VBF_LABELITEM_DETAIL		0x00000040	// �û��Զ������ϸ�ı�


class IVBF_MarkAttrLabel : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrLabel() {}

	// ����/��ȡ��ǩ�������ֵ�μ���ͷ�ļ���VBF_LABELITEM_ID�ȳ����Ķ��壩
	virtual void  SetTextItem(DWORD dwItem)=0;
	virtual DWORD GetTextItem()=0;

    // ����/��ȡ�û��Զ���ļ��ı�
    virtual void               SetSimpleText(const std::string& strText)=0;
    virtual const std::string& GetSimpleText()=0;

    // ����/��ȡ�û��Զ������ϸ�ı�
    virtual void               SetDetailText(const std::string& strText)=0;
    virtual const std::string& GetDetailText()=0;

	// ��ȡ��ǰ��ʾ���ı�
	virtual const std::string& GetText()=0;

	// ����/��ȡ��ǩ�Ķ�λ��ʽ��ֵ�μ���ͷ�ļ���ö��VBF_LABELPOS_TYPE�Ķ��壩
    virtual void               SetPosType(EVBF_LABELPOS_TYPE nPosType)=0;
    virtual EVBF_LABELPOS_TYPE GetPosType()=0;

	// ����/��ȡ�ı���ʽ
	virtual void                 SetTextStyle(const VBF_TEXTSTYLE& style)=0;
	virtual const VBF_TEXTSTYLE& GetTextStyle()=0;

	// ����/��ȡ�ı�������Ŀɼ���
	virtual void SetFrameVisible(bool bVisible)=0;
	virtual bool IsFrameVisible()=0;

	// ����/��ȡ�ı����������ʽ
	virtual void                      SetFrameStyle(const VBF_POLYGON2DSTYLE& style)=0;
	virtual const VBF_POLYGON2DSTYLE& GetFrameStyle()=0;

    // ����/��ȡ�Ƿ���Ʊ������еĶ�λ��ʶ�������ı�������ߵ�С�����Σ�Ĭ��Ϊtrue��
    virtual void SetIndicatorVisible(bool bVisible)=0;
    virtual bool IsIndicatorVisible()=0;

	// ����/��ȡ�ı����䱳��������Ļ����ϵ�µ�ƫ��������λ�����أ�Ĭ��ֵ��Ϊ0��
	virtual void SetScreenOffset(float fOffsetX, float fOffsetY)=0;
	virtual void GetScreenOffset(float& fOffsetX, float& fOffsetY)=0;

    // �ж��Ƿ����ָ�������λ�ã��л��������ʱʹ�ã�
    virtual bool Contains(float x, float y)=0;
};


#endif 
