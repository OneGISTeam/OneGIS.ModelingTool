//*******************************************************************
// FileName��IVBF_3DEffectAudio.h
// Function����ά��Ƶ���Žӿ�
// Author:   κ��
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

	/// ������Ƶ�ļ�����������·��
	virtual bool SetAudioFileName(const char* szFileName)=0;

	// ������Ƶ�ĵ�������
	virtual void SetGeoPosition(double L, double B, double H)=0;

	// ������Ƶ�󶨵Ľڵ㣬�ú������ú󣬽��Զ�����SetGeoPosition()�����趨�ĵ�������
	virtual void AttachToNode(osg::IVBF_SGNode* pNode)=0;

	// �Ƿ�ѭ�����ţ�Ĭ��Ϊ��ѭ������
	virtual void SetLooping(bool bLoop)=0;
	virtual bool IsLooping()=0;

	// �Ƿ�Ϊ�����������Ϊ��������������������Ч
	virtual void SetAmbient(bool bAmbient)=0;
	virtual bool IsAmbient()=0;

	// ����/��ȡ������С��Ĭ��Ϊ1.0f��ֵ��Ϊ[0.1, 50.0]
	virtual void  SetVolume(float fVolume)=0;
	virtual float GetVolume()=0;

	// ����/��ȡ���������������� (��λ����)
	virtual void  SetMaxDistance(float fDist)=0;
	virtual float GetMaxDistance()=0;

	// ��ʼ����
	virtual void Play()=0;

	// ��ͣ����
	virtual void Pause()=0;

	// ֹͣ����
	virtual void Stop()=0;
};

#endif 
