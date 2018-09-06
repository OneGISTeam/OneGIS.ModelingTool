//*******************************************************************
// FileName��IVBF_MarkActionTexAnim.h
// Function��ģ����Ϊ�ӿڣ��������任���磺̹���Ĵ���ת����
// Author:
// Date:     2017-12-28
//*******************************************************************

#ifndef __IVBF_MARK_ACTION_TEXANIM_H__
#define __IVBF_MARK_ACTION_TEXANIM_H__


#include <VBF_Plot/IVBF_MarkAction.h>
#include <Types/VBF_3DStyles.h>


class IVBF_MarkActionTexAnim : public IVBF_MarkAction
{
public:
    virtual ~IVBF_MarkActionTexAnim() {}
    virtual void SetSpeedU(float fSpeedU)=0; // ÿ��任���������꣨�����ˮƽ����
    virtual void SetSpeedV(float fSpeedV)=0; // ÿ��任���������꣨����Ĵ�ֱ����
};


#endif 
