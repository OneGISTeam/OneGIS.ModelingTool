//*******************************************************************
// FileName：IVBF_MarkProcessExplosion.h
// Function：爆炸过程
// Author:   武玉国
// Date:     2010-9-20
//*******************************************************************

#ifndef __IVBF_MARK_PROCESS_EXPLOSION_H__
#define __IVBF_MARK_PROCESS_EXPLOSION_H__


#include <VBF_Plot/IVBF_MarkProTimerTrigger.h>
#include <string>

#define VBF_MARK_PROCESS_EXPLOSION   "Explosion"	// 爆炸

class IVBF_MarkProcessExplosion : public IVBF_MarkProTimerTrigger
{
protected:
	virtual ~IVBF_MarkProcessExplosion() {}

	// 设置/获取相邻两幅爆炸纹理切换的帧间隔（默认值为2）
	virtual void SetFrameInterval(int nFrameInterval)=0;
	virtual int  GetFrameInterval()=0;

	// 设置/获取爆炸时的声音文件（完整路径）
	virtual void               SetSoundFileName(const std::string& strFileName)=0;
	virtual const std::string& GetSoundFileName()=0;

	// 设置/获取爆炸半径（单位：米，默认值为10000）
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;

	// 设置/获取纹理图像指针
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;
};


#endif 
