//*******************************************************************
// FileName：IVBF_MarkModelCombined.h
// Function：组合模型，其成员必须为点状模型
// Author:   杜莹
// Date:     2015-05-13
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_COMBINED_H__
#define __IVBF_MARK_MODEL_COMBINED_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


// Combined模型中各个成员的预留标志，系统使用了最后4位
#define VBF_RESERVEFLAG_COMBINEDMEMBER       0x0020



//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelCombined
// 接口描述：组合模型，其中的成员同时也是该组合模型的子节点，
//          只是该子节点的ReserveFlag为VBF_RESERVEFLAG_COMBINEDMEMBER
//--------------------------------------------------------------------
class IVBF_MarkModelCombined : public IVBF_MarkModelPoint
{
public:
    virtual ~IVBF_MarkModelCombined() {}

    // 获取组合模型中的成员总数
    virtual int GetNumMembers()=0;

    // 通过索引号，获取组合模型中的成员
    virtual IVBF_MarkModelPoint* GetMember(int nIndex)=0;

    // 通过ID号，获取组合模型中的成员
    virtual IVBF_MarkModelPoint* GetMember(const std::string& strMarkID)=0;

    // 添加一个成员
    virtual bool AddMember(IVBF_MarkModelPoint* pIMark)=0;

    // 设置/获取缩放时是否保持成员与模型定位点之间的距离不变（默认值为true）
    virtual void KeepDistWhenScaled(bool bKeep)=0;
    virtual bool IsKeepingDistWhenScaled()=0;
};


#endif 
