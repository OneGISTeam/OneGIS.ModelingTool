//*******************************************************************
// FileName：IVBF_MarkProcessMoveCurrent.h
// Function：即刻运动，即从过程添加的那一刻起开始运动
// Author:   杜莹
// Date:     2017-08-21
//*******************************************************************

#ifndef __IVBF_MARK_PROCESS_MOVE_CURRENT_H__
#define __IVBF_MARK_PROCESS_MOVE_CURRENT_H__


#include "VBF_Plot/IVBF_MarkProTimerTrigger.h"
#include <vector>
#include <Types/Vec3d>

#define VBF_MARK_PROCESS_MOVECURRENT "CurrentMove"	// 即刻运动

class IVBF_MarkProcessMoveCurrent : public IVBF_MarkProcess
{
public:
    virtual ~IVBF_MarkProcessMoveCurrent() {}

	// 设置/获取完成一次过程需要的时间（单位：秒）
	virtual void   SetDuration(double dDuration)=0;
	virtual double GetDuration()=0;

	// 设置/获取过程是否重复执行（默认值为false）
	virtual void SetLoop(bool bLoop)=0;
	virtual bool IsLoop()=0;
	
    // 设置/获取路径坐标串
    virtual void                            SetPath(const std::vector<osg::Vec3d>& vGeo)=0;
    virtual const std::vector<osg::Vec3d>&  GetPath()=0;
};


#endif 
