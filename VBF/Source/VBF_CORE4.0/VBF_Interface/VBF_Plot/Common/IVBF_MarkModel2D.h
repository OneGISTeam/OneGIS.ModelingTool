//*******************************************************************
// FileName��IVBF_MarkModel2D.h
// Function��ʵ��ģ�ͽӿڣ�2D��ʹ����Ļ����
// Author:
// Date:
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_2D_H__
#define __IVBF_MARK_MODEL_2D_H__

#include <VBF_Plot/IVBF_MarkModel.h>

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModel2D
// �ӿ�������2D��ʹ����Ļ����
//--------------------------------------------------------------------
class IVBF_MarkModel2D : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModel2D() {}

    // ����/��ȡͼ��ռ�ݵ���Ļ����
    virtual void SetClientRect(float x0, float x1, float y0, float y1)=0;
    virtual void GetClientRect(float& x0, float& x1, float& y0, float& y1)=0;

	// ����/��ȡ����ԭ���Ƿ�λ����Ļ���Ͻǣ�Ĭ��Ϊtrue��
	virtual void SetOriginTopLeft(bool bTopLeft)=0;
	virtual bool IsOriginTopLeft()=0;
};



#endif 
