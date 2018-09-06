//*******************************************************************
// FileName��IVBF_MarkProcessMoveCurrent.h
// Function�������˶������ӹ�����ӵ���һ����ʼ�˶�
// Author:   ��Ө
// Date:     2017-08-21
//*******************************************************************

#ifndef __IVBF_MARK_PROCESS_MOVE_CURRENT_H__
#define __IVBF_MARK_PROCESS_MOVE_CURRENT_H__


#include "VBF_Plot/IVBF_MarkProTimerTrigger.h"
#include <vector>
#include <Types/Vec3d>

#define VBF_MARK_PROCESS_MOVECURRENT "CurrentMove"	// �����˶�

class IVBF_MarkProcessMoveCurrent : public IVBF_MarkProcess
{
public:
    virtual ~IVBF_MarkProcessMoveCurrent() {}

	// ����/��ȡ���һ�ι�����Ҫ��ʱ�䣨��λ���룩
	virtual void   SetDuration(double dDuration)=0;
	virtual double GetDuration()=0;

	// ����/��ȡ�����Ƿ��ظ�ִ�У�Ĭ��ֵΪfalse��
	virtual void SetLoop(bool bLoop)=0;
	virtual bool IsLoop()=0;
	
    // ����/��ȡ·�����괮
    virtual void                            SetPath(const std::vector<osg::Vec3d>& vGeo)=0;
    virtual const std::vector<osg::Vec3d>&  GetPath()=0;
};


#endif 
