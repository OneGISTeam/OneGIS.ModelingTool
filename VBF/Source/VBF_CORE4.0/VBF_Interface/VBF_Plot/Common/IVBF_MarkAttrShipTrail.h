//*******************************************************************
// FileName��IVBF_MarkAttrShipTrail.h
// Function��ģ�����Խӿڣ���������
// Author:   ��Ө
// Date:     2014-12-02
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_SHIP_TRAIL_H__
#define __IVBF_MARK_ATTR_SHIP_TRAIL_H__


#include <VBF_Plot/IVBF_MarkAttr.h>


class IVBF_MarkAttrShipTrail : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrShipTrail() {}

    // ����/��ȡͷ�������Ŀ�Ⱥ͸߶ȣ���λ���ף�
    virtual void SetFrontSize(float fWidth, float fHeight)=0;
    virtual void GetFrontSize(float& fWidth, float& fHeight)=0;

    // ����/��ȡβ�������Ŀ�Ⱥ͸߶ȣ���λ���ף�
    virtual void SetBackSize(float fWidth, float fHeight)=0;
    virtual void GetBackSize(float& fWidth, float& fHeight)=0;

	// ����ͷ��������������ģ�����ĵ��ƫ������Ĭ��ֵΪ(0, 0, 0)��
	virtual void SetFrontOffset(float fOffsetX, float fOffsetY, float fOffsetZ)=0;
	virtual void GetFrontOffset(float& fOffsetX, float& fOffsetY, float& fOffsetZ)=0;

	// ����β��������������ģ�����ĵ��ƫ������Ĭ��ֵΪ(0, 0, 0)��
	virtual void SetBackOffset(float fOffsetX, float fOffsetY, float fOffsetZ)=0;
	virtual void GetBackOffset(float& fOffsetX, float& fOffsetY, float& fOffsetZ)=0;
};


#endif 
