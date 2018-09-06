//*******************************************************************
// FileName��IVBF_3DLayout.h
// Function����ά�����ϲ���Ҫ�ع���ӿڣ���ָ�����
// Author:   ��Ө
// Date:     2012-04-23
//*******************************************************************

#ifndef __IVBF_3DLAYOUT_H__
#define __IVBF_3DLAYOUT_H__

#include <VBF_Base/VBF_Referenced.h>

// ����������ID��
const char VBF_COMPONENT_3DLAYOUT[]	= "Component: 3DLayout";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DLAYOUT[]	= "��ά���沼��Ҫ�ع���";


class IVBF_3DLayout : public CVBF_Referenced
{
public:	
	virtual ~IVBF_3DLayout() {}

    // ����/��ȡָ����Ŀɼ���
	virtual void SetCompassVisible(bool bVisible)=0;
	virtual bool IsCompassVisible()=0;		

	// ����/��ȡ������������ʾ��Ϣ�Ƿ�ɼ���Ĭ��Ϊ���ɼ�
	virtual void SetFramedTextVisible(bool bVisible)=0;
	virtual bool IsFramedTextVisible()=0;

	// ���ñ��������ֵ���ʽ
	virtual void SetFramedTextSize(float fSize)=0;					// ���ִ�С��Ĭ��Ϊ56.0
	virtual void SetFramedTextFont(const char* szFontFile)=0;		// �����ļ���������·������"simhei.ttf"
	virtual void SetFramedTextColor(float r, float g, float b)=0;	// ������ɫ��Ĭ��Ϊ(1,1,1)

	// ���ñ����������Ƿ�ѭ����ʾ��Ĭ��Ϊ��ѭ��,��ʾ��Ϻ������ر�
	virtual void SetFramedTextLooping(bool bLooping)=0;				

	// ����Ļ�ײ����ƾ��б������������ʾ��Ϣ�����У��ɹ�����ͬʱ�Զ�ʹ������ɼ�
	virtual void ShowFramedText(const char* szText)=0;

	//����/��ȡ�������Ŀɼ���
	virtual void SetNavigatorVisible(bool bVisible)=0;
	virtual bool IsNavigatorVisible()=0;

	// ����/��ȡ���ͼ�Ŀɼ���
	virtual void SetAirViewVisible(bool bVisible)=0;
	virtual bool IsAirViewVisible()=0;

    // ����/��ȡ����ʱ��Ŀɼ���
    virtual void SetTimerVisible(bool bVisible)=0;
    virtual bool IsTimerVisible()=0;
};

#endif 
