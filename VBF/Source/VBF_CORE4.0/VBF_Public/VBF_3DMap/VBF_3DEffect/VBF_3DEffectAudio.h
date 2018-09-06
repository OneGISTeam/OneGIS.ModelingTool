//*******************************************************************
// FileName：VBF_3DEffectAudio.h
// Function：三维视频特效接口
// Author:   魏勇
// Date:     2012-04-12
//*******************************************************************

#ifndef __VBF_3DEFFECT_AUDIO_H__
#define __VBF_3DEFFECT_AUDIO_H__
/*
#include "VBF_3DEffect\\IVBF_3DEffectAudio.h"
#include "VBF_3DEffectImpl.h"

#include <VBF_Engine/VBF_SceneGraph/image>
#include <VBF_Engine/VBF_SGDB/readFile>
#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Display/VBF_Viewer/VBF_ViewerSimple.h>
#include <VBF_Engine/VBF_SceneGraph/ImageStream>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTextureRectangle.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrDepth.h>
#include <osgAudio/SoundState.h>
#include <osgAudio/SoundUpdateCB.h>
#include <VBF_3DMap/VBF_EarthUtil/ObjectLocator>

using namespace std;
using namespace osgEarth;
using namespace osgEarth::Util;

#include <VBF_Display/IVBF_3DDisplay.h>

#ifdef _DEBUG
	#pragma comment(lib, "osgAudiod.lib")
	#pragma comment(lib, "openalppd.lib")
#else
	#pragma comment(lib, "osgAudio.lib")
	#pragma comment(lib, "openalpp.lib")
#endif

class CVBF_3DEffectAudio : public CVBF_3DEffectImpl<IVBF_3DEffectAudio>
{
public:	
	// 参数：szFileName	-- 音频的路径     
	CVBF_3DEffectAudio(IVBF_3DMainCtrl* pI3DMainCtrl, IVBF_View* pView,  osg::IVBF_SGNodeGroup* pParentNode);
	virtual ~CVBF_3DEffectAudio();

	// 设置视频文件名，含绝对路径
	virtual bool SetAudioFileName(const char* szFileName);

	// 设置地理坐标
	virtual void SetGeoPosition(double L, double B, double H);

	// 设置声音所在的节点
	virtual void AttachToNode(osg::IVBF_SGNode* pNode);

	// 是否循环播放
	virtual void SetLooping(bool bLoop=true)		{ m_bLoop = bLoop; if(m_pSoundState.valid()) m_pSoundState->setLooping(m_bLoop); }
	virtual bool IsLooping()						{ return m_bLoop; }

	// 是否为环境音，如果为环境音，则声音坐标无效
	virtual void SetAmbient(bool bAmbient)			{ m_bAmbient = bAmbient; if(m_pSoundState.valid()) m_pSoundState->setAmbient(bAmbient); }
	virtual bool IsAmbient()						{ return m_bAmbient; }

	// 设置/获取音量大小，默认为1.0f
	virtual void  SetVolume(float fVolume)			{ m_fVolume = osg::clampTo(fVolume, 0.1f, 50.0f); if(m_pSoundState.valid()) m_pSoundState->setGain(m_fVolume);	}
	virtual float GetVolume()						{ return m_fVolume; }

	// 设置/获取声音传播的最大距离 (单位：米)
	virtual void  SetMaxDistance(float fDist)		{ m_fMaxDistance = fDist; if(m_pSoundState.valid()) m_pSoundState->setMaxDistance(m_fMaxDistance); }
	virtual float GetMaxDistance()					{ return m_fMaxDistance; }

	// 从配置文件中装载特效对象的初始化信息
	virtual bool LoadFromXML(TiXmlElement* pElemEffect);

	// 执行特效对象的动作，动作参数从从配置文件元素中获取
	virtual bool StartFromXML(TiXmlElement* pElemAction);

	// 开始/暂停/停止播放
	virtual void Play();
	virtual void Pause();
	virtual void Stop();
	
private:
	bool Init();
	osgAudio::SoundState* CreateSoundState(const std::string& strFileName);
	
protected:		
	bool										m_bLoop;			// 是否循环
	bool										m_bAmbient;			// 是否为环境音，如果为环境音，则声音坐标无效
	float										m_fVolume;			// 音量大小，默认为1.0f
	float										m_fMaxDistance;		// 声音传播的最大距离 (单位：米)
	std::string									m_strAudioFile;		// 音频文件名

	ref_ptr<ObjectLocatorNode>				m_pNodePlacer;

	ref_ptr<osg::IVBF_SGNode>						m_pAttachNode;	
	ref_ptr<osgAudio::SoundState>			m_pSoundState;	
	ref_ptr<osgAudio::SoundUpdateCB>		m_pSoundUpdateCB;
};
*/


#endif