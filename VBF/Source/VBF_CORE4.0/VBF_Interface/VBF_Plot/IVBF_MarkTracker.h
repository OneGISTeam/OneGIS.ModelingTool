//*******************************************************************
// FileName：IVBF_MarkTracker.h
// Function：标图实体模型拖放器接口
// Author:   武玉国
// Date:     2009-4-10
//*******************************************************************

#ifndef __IVBF_MARK_TRACKER_H__
#define __IVBF_MARK_TRACKER_H__


#include <VBF_Display/VBF_Dragger/Dragger.h>
#include <VBF_Plot/IVBF_MarkModel.h>
// 定义迭代器
typedef std::vector< ref_ptr<osgManipulator::Dragger> >  CVBF_DraggerList;

class IVBF_MarkTracker : public CVBF_Referenced
{
public:
    virtual ~IVBF_MarkTracker() {}

public:

    virtual void AttachToMark(IVBF_MarkModel* pIMark)=0;
    virtual void DetachFromMark()=0;
    virtual IVBF_MarkModel* GetAttachedMark() = 0;

    // 设置功能键，以便完成某些需要组合键的动作
    virtual void SetModKey(osgGA::GUIEventAdapter::ModKeyMask nKey)=0;

    // 响应更新回调（每帧绘制前调用）
    virtual void OnUpdate()=0;
    // 获取当前使用的所有Dragger
    virtual void GetActiveDraggers(CVBF_DraggerList& vDraggers)=0;
};


#endif 
