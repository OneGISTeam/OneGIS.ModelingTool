//*******************************************************************
// FileName��IVBF_MarkAttrDetect.h
// Function���ɱ�̽�����Խӿ�
//           ���ڽ���̽�������¼�������̽��������ģ�͵���ʾ״̬
//           ������Visible���Ա�ʾ�Ƿ�̽�⵽
// Author:
// Date:     2013-10-23
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_DETECT_H__
#define __IVBF_MARK_ATTR_DETECT_H__

#include <VBF_Plot/IVBF_MarkAttr.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkAttrDetect
// �ӿ�������
//--------------------------------------------------------------------
class IVBF_MarkAttrDetect : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrDetect() {}

	// ����/��ȡģ�ͱ�̽�⵽�󣬰�Χ���Ƿ�ɼ���Ĭ��Ϊtrue��
	virtual void SetBoundingBoxVisibleWhenDetected(bool bVisible)=0;
	virtual bool IsBoundingBoxVisibleWhenDetected()=0;
};


#endif 
