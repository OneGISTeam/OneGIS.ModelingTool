//*******************************************************************
// FileName��IVBF_3DEffectImage2D.h
// Function��2Dͼ����Ч�ӿ�
// Author:   SunC
// Date:     2012-04-12
//*******************************************************************

#ifndef __IVBF_3DEFFECT_IMAGE2D_H__
#define __IVBF_3DEFFECT_IMAGE2D_H__

#include "IVBF_3DEffect.h"


class IVBF_3DEffectImage2D : public IVBF_3DEffect
{
public:	
	virtual ~IVBF_3DEffectImage2D() {}	

	// ����ͼ���ļ�������������·��
	virtual bool SetImageFileName(const char* szFileName)=0;

	// ������ִ�ж���
	// ������szType				-- �������ͣ��μ��������Ͷ���
	//       (x, y)				-- ͼƬ�������ӿ��е����λ��, ֵ��Ϊ[0,1]
	//		 nDurationFrames	-- ��������֡��
	//		 fAlpha				-- ͼƬ��͸���ȣ����ڵ��붯����ͼƬ͸���ȴ�0���䵽alpha�����ڵ���������ͼƬ͸���ȴ�alpha���䵽0
	//                             ��������������ͼƬһֱ����alpha��͸����
	//		 fScale				-- ͼƬ�����Ŵ�С
	// ���أ�����ִ�гɹ�������true�����򷵻�false
	virtual bool StartAction(const char* szType, float x, float y, int nDurationFrames, float fAlpha, float fScale )=0;

	// �Ƿ���Ҫ��ͼ������ӿڷ�Χ����
	virtual void SetLockInViewport(bool bLocked)=0;

	// �����Ҫ��ͼ������ӿڷ�Χ���ţ�ȷ��Image2D��Ч����Ļ��ռ�ݹ̶��İٷֱ�
	virtual void SetScaleWithViewport(bool bScale)=0;
};

#endif 
