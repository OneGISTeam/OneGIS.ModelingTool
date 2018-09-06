//*******************************************************************
// FileName��IVBF_3DAnalysisTool.h
// Function��������ά�������ߵĻ���
// Date:     2015-04-22
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_H__
#define __IVBF_3DANALYSIS_TOOL_H__


#include <VBF_OS.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventAdapter.h>
#include <VBF_Display/VBF_Manipulator/IVBF_GUIActionAdapter.h>
#include <Types/VBF_3DStyles.h>


class IVBF_3DAnalysisTool : public CVBF_Referenced
{
public:
	virtual ~IVBF_3DAnalysisTool() {}

	// ��ȡ�÷������ߵ�ID��
	virtual const char* GetToolID()=0;

	// ��ȡ�ù��ߵ�ǰ�Ƿ񱻼���
	virtual bool IsActive()=0;

    // ����/��ȡ����������ı���ʽ
    virtual void                 SetTextStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetTextStyle()=0;

    // ����/��ȡ��������ı������Ƿ�ɼ�
    virtual void SetFrameVisible(bool bVisible)=0;
    virtual bool IsFrameVisible()=0;

    // ����/��ȡ��������ı�������ʽ
    virtual void                      SetFrameStyle(const VBF_POLYGON2DSTYLE& style)=0;
    virtual const VBF_POLYGON2DSTYLE& GetFrameStyle()=0;

    // ����/��ȡ�������̵�������ʽ
    virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetLineStyle()=0;

    // ����/��ȡ��������������Ƿ���Ҫ��ʾ���ศ����Ϣ
    virtual void SetTipCoordVisible(bool bVisible)=0;      // �����������ĵ������꣨������������㣬ʼ����ʾ��
    virtual bool IsTipCoordVisible()=0;

    virtual void SetTipDistVisible(bool bVisible)=0;       // ������������ڵ�Ĵ�Բ�߾��루����Ǿ������㣬ʼ����ʾ��
    virtual bool IsTipDistVisible()=0;

    virtual void SetTipAzimuthVisible(bool bVisible)=0;    // �����������ķ�λ�ǣ�����Ƿ�λ�����㣬ʼ����ʾ��
    virtual bool IsTipAzimuthVisible()=0;

    // ����/��ȡ�Ƿ�ʹ�öȷ��뷽ʽ��ʾ��������
    virtual void SetTipCoordTypeDMS(bool bDMS)=0;
    virtual bool IsTipCoordTypeDMS()=0;

    // ����/��ȡ��Ҫ��ĸ�����Ϣ��ʽ
    virtual void                 SetTipTextStyleMinor(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetTipTextStyleMinor()=0;

    virtual void                      SetTipFrameStyleMinor(const VBF_POLYGON2DSTYLE& style)=0;
    virtual const VBF_POLYGON2DSTYLE& GetTipFrameStyleMinor()=0;

    // ����/��ȡ��Ҫ��ĸ�����Ϣ��ʽ
    virtual void                 SetTipTextStyleMajor(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetTipTextStyleMajor()=0;

    virtual void                      SetTipFrameStyleMajor(const VBF_POLYGON2DSTYLE& style)=0;
    virtual const VBF_POLYGON2DSTYLE& GetTipFrameStyleMajor()=0;

    // ����/��ȡ��λ�Ǹ�����Ϣ�е��߶���ʽ(������������ָʾ�ߺͼн���)
    virtual void                 SetTipAzimuthLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetTipAzimuthLineStyle()=0;

    // ����/��ȡ��λ�Ǹ�����Ϣ�е��ı���ʽ
    virtual void                 SetTipAzimuthTextStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetTipAzimuthTextStyle()=0;

    // ���º�����ϵͳ�ڲ����ã��û��������
    virtual bool Init()=0;
    virtual void SetActive(bool bActive)=0;
    virtual void Clear()=0;
    virtual bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa)=0;
};

#endif
