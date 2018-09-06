//*******************************************************************
// FileName��IVBF_MarkTracker.h
// Function����ͼʵ��ģ���Ϸ����ӿ�
// Author:   �����
// Date:     2009-4-10
//*******************************************************************

#ifndef __IVBF_MARK_TRACKER_H__
#define __IVBF_MARK_TRACKER_H__


#include <VBF_Display/VBF_Dragger/Dragger.h>
#include <VBF_Plot/IVBF_MarkModel.h>
// ���������
typedef std::vector< ref_ptr<osgManipulator::Dragger> >  CVBF_DraggerList;

class IVBF_MarkTracker : public CVBF_Referenced
{
public:
    virtual ~IVBF_MarkTracker() {}

public:

    virtual void AttachToMark(IVBF_MarkModel* pIMark)=0;
    virtual void DetachFromMark()=0;
    virtual IVBF_MarkModel* GetAttachedMark() = 0;

    // ���ù��ܼ����Ա����ĳЩ��Ҫ��ϼ��Ķ���
    virtual void SetModKey(osgGA::GUIEventAdapter::ModKeyMask nKey)=0;

    // ��Ӧ���»ص���ÿ֡����ǰ���ã�
    virtual void OnUpdate()=0;
    // ��ȡ��ǰʹ�õ�����Dragger
    virtual void GetActiveDraggers(CVBF_DraggerList& vDraggers)=0;
};


#endif 
