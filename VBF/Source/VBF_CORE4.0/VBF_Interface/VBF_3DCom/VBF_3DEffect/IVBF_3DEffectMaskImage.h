//***************************************************************************************
// FileName��IVBF_3DEffectMaskImage.h
// Function��3Dͼ���ɰ���ӿ�
// Author:   SunC
// Date:     2012-04-23
//***************************************************************************************

#ifndef __IVBF_3DEFFECT_MASKIMAGE_H__
#define __IVBF_3DEFFECT_MASKIMAGE_H__

#include "IVBF_3DEffect.h"
#include <string>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <Types/Vec2d>
#include <Types/Vec4f>



//-------------------------------------------------------------------
// ����ӿڣ�IVBF_3DEffectMaskImage
// �ӿ�������ͼ���ɰ���Ч
//-------------------------------------------------------------------
class IVBF_3DEffectMaskImage : public IVBF_3DEffect
{
public:
	virtual ~IVBF_3DEffectMaskImage() {}

public:   

	// ����ͼ����ļ���
	virtual bool SetImageFileName(const char* szImgFn)=0;

	// ����ͼ��ĵ���Χ
	virtual bool SetGeoBounds(double xmin, double ymin, double xmax, double ymax)=0;

	// ����͸����
	virtual void SetAlpha(float fAlpha)=0;

	// ������Ե���ĸ߶�
	virtual void SetRelativeHeight(double dheight)=0;

    //-------------------------------------------------------------------------------------------------
	// ������StartAction()
	// �������ɶ��󴴽�����
	// ������EffectType			-- �������ͣ��μ��������Ͷ���
	//		nDurationFrames		-- ��������֡��
	// ��ע��Ŀǰ���ڵ����ͼ���ɰ�δ�������춯��,ʹ�ô˶���ʱSetHeight()��dHeightӦ����Ϊ0.0
	//-------------------------------------------------------------------------------------------------
	virtual bool StartAction(const char* szEffectType, int nDurationFrames)=0;
};

#endif