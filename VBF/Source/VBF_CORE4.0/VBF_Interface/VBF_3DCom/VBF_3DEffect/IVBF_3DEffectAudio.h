//*******************************************************************
// FileName：IVBF_3DEffectAudio.h
// Function：三维音频播放接口
// Author:   魏勇
// Date:     2012-04-30
//*******************************************************************

#ifndef __IVBF_3DEFFECT_AUDIO_H__
#define __IVBF_3DEFFECT_AUDIO_H__

#include "IVBF_3DEffect.h"

namespace osg
{
	class Node;
}


class IVBF_3DEffectAudio : public IVBF_3DEffect
{
public:	
	virtual ~IVBF_3DEffectAudio() {}

	/// 设置音频文件名，含绝对路径
	virtual bool SetAudioFileName(const char* szFileName)=0;

	// 设置音频的地理坐标
	virtual void SetGeoPosition(double L, double B, double H)=0;

	// 设置音频绑定的节点，该函数调用后，将自动覆盖SetGeoPosition()函数设定的地理坐标
	virtual void AttachToNode(osg::IVBF_SGNode* pNode)=0;

	// 是否循环播放，默认为不循环播放
	virtual void SetLooping(bool bLoop)=0;
	virtual bool IsLooping()=0;

	// 是否为环境音，如果为环境音，则声音坐标无效
	virtual void SetAmbient(bool bAmbient)=0;
	virtual bool IsAmbient()=0;

	// 设置/获取音量大小，默认为1.0f，值域为[0.1, 50.0]
	virtual void  SetVolume(float fVolume)=0;
	virtual float GetVolume()=0;

	// 设置/获取声音传播的最大距离 (单位：米)
	virtual void  SetMaxDistance(float fDist)=0;
	virtual float GetMaxDistance()=0;

	// 开始播放
	virtual void Play()=0;

	// 暂停播放
	virtual void Pause()=0;

	// 停止播放
	virtual void Stop()=0;
};

#endif 
