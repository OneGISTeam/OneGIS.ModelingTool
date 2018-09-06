//*******************************************************************
// FileName��IVBF_MarkModelCombined.h
// Function�����ģ�ͣ����Ա����Ϊ��״ģ��
// Author:   ��Ө
// Date:     2015-05-13
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_COMBINED_H__
#define __IVBF_MARK_MODEL_COMBINED_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


// Combinedģ���и�����Ա��Ԥ����־��ϵͳʹ�������4λ
#define VBF_RESERVEFLAG_COMBINEDMEMBER       0x0020



//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelCombined
// �ӿ����������ģ�ͣ����еĳ�ԱͬʱҲ�Ǹ����ģ�͵��ӽڵ㣬
//          ֻ�Ǹ��ӽڵ��ReserveFlagΪVBF_RESERVEFLAG_COMBINEDMEMBER
//--------------------------------------------------------------------
class IVBF_MarkModelCombined : public IVBF_MarkModelPoint
{
public:
    virtual ~IVBF_MarkModelCombined() {}

    // ��ȡ���ģ���еĳ�Ա����
    virtual int GetNumMembers()=0;

    // ͨ�������ţ���ȡ���ģ���еĳ�Ա
    virtual IVBF_MarkModelPoint* GetMember(int nIndex)=0;

    // ͨ��ID�ţ���ȡ���ģ���еĳ�Ա
    virtual IVBF_MarkModelPoint* GetMember(const std::string& strMarkID)=0;

    // ���һ����Ա
    virtual bool AddMember(IVBF_MarkModelPoint* pIMark)=0;

    // ����/��ȡ����ʱ�Ƿ񱣳ֳ�Ա��ģ�Ͷ�λ��֮��ľ��벻�䣨Ĭ��ֵΪtrue��
    virtual void KeepDistWhenScaled(bool bKeep)=0;
    virtual bool IsKeepingDistWhenScaled()=0;
};


#endif 
