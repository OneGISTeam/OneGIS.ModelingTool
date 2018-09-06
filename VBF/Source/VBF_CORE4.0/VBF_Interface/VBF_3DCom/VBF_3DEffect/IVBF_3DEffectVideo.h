//*******************************************************************
// FileName��IVBF_3DEffectVideo.h
// Function����ά��Ƶ���Žӿ�
// Author:   κ��
// Date:     2012-04-30
//*******************************************************************

#ifndef __IVBF_3DEFFECT_VIDEO_H__
#define __IVBF_3DEFFECT_VIDEO_H__

#include "IVBF_3DEffect.h"

class IVBF_3DEffectVideo : public IVBF_3DEffect
{
public:	
	virtual ~IVBF_3DEffectVideo() {}	

	// ������Ƶ�ļ�������������·��
	virtual bool SetVideoFileName(const char* szFileName)=0;

	// ��������
	virtual void SetPosition(bool isGeo, double x, double y, double z)=0;

	// ������Ƶ��͸����
	virtual void SetAlpha(float fAlpha)=0;

	// ��������Ƶ����
	// ������isGeo		-- ��Ƶ�Ƿ��ڵ���λ�ô�����
	//		 position	-- ��Ƶ���ŵ�λ�ã���isGeoΪtrueʱ��position������Ϊ��γ�̣߳���isGeoΪfalseʱ��position������Ϊ��Ļ�ϵ�λ�ã�ֵ��Ϊ[0.0,1.0]
	//		 fAlpha		-- 
	virtual void Play()=0;

	// ��������ͣ����
	virtual void Pause()=0;

	// ��������Ƶֹͣ
	virtual void Stop()=0;

};

#endif 
