//*******************************************************************
// FileName��VBF_3DEffectAudio.h
// Function����ά��Ƶ��Ч�ӿ�
// Author:   κ��
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
	// ������szFileName	-- ��Ƶ��·��     
	CVBF_3DEffectAudio(IVBF_3DMainCtrl* pI3DMainCtrl, IVBF_View* pView,  osg::IVBF_SGNodeGroup* pParentNode);
	virtual ~CVBF_3DEffectAudio();

	// ������Ƶ�ļ�����������·��
	virtual bool SetAudioFileName(const char* szFileName);

	// ���õ�������
	virtual void SetGeoPosition(double L, double B, double H);

	// �����������ڵĽڵ�
	virtual void AttachToNode(osg::IVBF_SGNode* pNode);

	// �Ƿ�ѭ������
	virtual void SetLooping(bool bLoop=true)		{ m_bLoop = bLoop; if(m_pSoundState.valid()) m_pSoundState->setLooping(m_bLoop); }
	virtual bool IsLooping()						{ return m_bLoop; }

	// �Ƿ�Ϊ�����������Ϊ��������������������Ч
	virtual void SetAmbient(bool bAmbient)			{ m_bAmbient = bAmbient; if(m_pSoundState.valid()) m_pSoundState->setAmbient(bAmbient); }
	virtual bool IsAmbient()						{ return m_bAmbient; }

	// ����/��ȡ������С��Ĭ��Ϊ1.0f
	virtual void  SetVolume(float fVolume)			{ m_fVolume = osg::clampTo(fVolume, 0.1f, 50.0f); if(m_pSoundState.valid()) m_pSoundState->setGain(m_fVolume);	}
	virtual float GetVolume()						{ return m_fVolume; }

	// ����/��ȡ���������������� (��λ����)
	virtual void  SetMaxDistance(float fDist)		{ m_fMaxDistance = fDist; if(m_pSoundState.valid()) m_pSoundState->setMaxDistance(m_fMaxDistance); }
	virtual float GetMaxDistance()					{ return m_fMaxDistance; }

	// �������ļ���װ����Ч����ĳ�ʼ����Ϣ
	virtual bool LoadFromXML(TiXmlElement* pElemEffect);

	// ִ����Ч����Ķ��������������Ӵ������ļ�Ԫ���л�ȡ
	virtual bool StartFromXML(TiXmlElement* pElemAction);

	// ��ʼ/��ͣ/ֹͣ����
	virtual void Play();
	virtual void Pause();
	virtual void Stop();
	
private:
	bool Init();
	osgAudio::SoundState* CreateSoundState(const std::string& strFileName);
	
protected:		
	bool										m_bLoop;			// �Ƿ�ѭ��
	bool										m_bAmbient;			// �Ƿ�Ϊ�����������Ϊ��������������������Ч
	float										m_fVolume;			// ������С��Ĭ��Ϊ1.0f
	float										m_fMaxDistance;		// ���������������� (��λ����)
	std::string									m_strAudioFile;		// ��Ƶ�ļ���

	ref_ptr<ObjectLocatorNode>				m_pNodePlacer;

	ref_ptr<osg::IVBF_SGNode>						m_pAttachNode;	
	ref_ptr<osgAudio::SoundState>			m_pSoundState;	
	ref_ptr<osgAudio::SoundUpdateCB>		m_pSoundUpdateCB;
};
*/


#endif