//*******************************************************************
// FileName��IVBF_MarkAttrTrailSmoke.h
// Function��ģ�����Խӿڣ�ģ�͵��˶��켣������״��ʹ������ϵͳʵ�֣�
// Author:   ��Ө
// Date:     2015-11-03
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_TRAIL_SMOKE_H__
#define __IVBF_MARK_ATTR_TRAIL_SMOKE_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <Types/VBF_3DStyles.h>


class IVBF_MarkAttrTrailSmoke : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrTrailSmoke() {}

    // ����/��ȡβ�̿�ȣ�Ĭ��ֵΪ20����λ���ף�
    virtual void  SetWidth(float fWidth)=0;
    virtual float GetWidth()=0;
};


#endif 
