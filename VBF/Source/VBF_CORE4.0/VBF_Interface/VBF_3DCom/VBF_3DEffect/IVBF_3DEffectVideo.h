//*******************************************************************
// FileName：IVBF_3DEffectVideo.h
// Function：三维视频播放接口
// Author:   魏勇
// Date:     2012-04-30
//*******************************************************************

#ifndef __IVBF_3DEFFECT_VIDEO_H__
#define __IVBF_3DEFFECT_VIDEO_H__

#include "IVBF_3DEffect.h"

class IVBF_3DEffectVideo : public IVBF_3DEffect
{
public:	
	virtual ~IVBF_3DEffectVideo() {}	

	// 设置视频文件名，不含绝对路径
	virtual bool SetVideoFileName(const char* szFileName)=0;

	// 设置坐标
	virtual void SetPosition(bool isGeo, double x, double y, double z)=0;

	// 设置视频的透明度
	virtual void SetAlpha(float fAlpha)=0;

	// 函数：视频播放
	// 参数：isGeo		-- 视频是否在地理位置处播放
	//		 position	-- 视频播放的位置，当isGeo为true时，position的坐标为经纬高程；当isGeo为false时，position的坐标为屏幕上的位置，值域为[0.0,1.0]
	//		 fAlpha		-- 
	virtual void Play()=0;

	// 函数：暂停播放
	virtual void Pause()=0;

	// 函数：视频停止
	virtual void Stop()=0;

};

#endif 
