//*******************************************************************
// FileName��IVBF_3DEffectImage3D.h
// Function��3Dͼ����Ч�ӿ�
// Author:   ��Ө
// Date:     2012-04-29
//*******************************************************************

#ifndef __IVBF_3DEFFECT_IMAGE3D_H__
#define __IVBF_3DEFFECT_IMAGE3D_H__

#include "IVBF_3DEffect.h"

// ���ļ��ж����˸߳�ֵ��ȡ��ʽ
#include "VBF_3DCom/VBF_AltitudeClampTypes.h"


class IVBF_3DEffectImage3D : public IVBF_3DEffect
{
public:	
	virtual ~IVBF_3DEffectImage3D() {}

	// ���õ�������
	virtual void SetGeoPosition(double L, double B, double H, const char* szAltitudeClamp)=0;

	// ���һ��LOD�ӽڵ㣬ͼ���ļ��������ֺ���ʧ�����߾��룬���ű�(��λ����)
	// ������bAutoScaleToScreen -- �Ƿ�̶�������	
	//       fSizeInWorld       -- ��������ϵ�µĳߴ� (��λ����)��ֻ�е�bAutoScaleToScreen=falseʱ������, ��ʱ����fScale
	//       fScale				-- ����ϵ����ֻ�е�bAutoScaleToScreen=trueʱ������
	virtual bool AddLodChild(const char* szImgFn, float fRangeMin, float fRangeMax, bool bAutoScaleToScreen, float fSizeInWorld, float fScale)=0;

	// ����������һ��3Dͼ�񶯻�
	// ������szType				-- �������ͣ��μ��������Ͷ���
	//       (L, B, H)			-- ͼƬ�ĵ�������
	//		 nClampMode			-- �߳�ֵ��ȡ��ʽ���μ�ö��VBF_ALTITUDE_CLAMP�Ķ���
	//		 nDurationFrames	-- ��������֡��
	//		 fAlpha				-- ͼƬ��͸���ȣ����ڵ��붯����ͼƬ͸���ȴ�0���䵽alpha�����ڵ���������ͼƬ͸���ȴ�alpha���䵽0
	//                             ��������������ͼƬһֱ����alpha��͸����
	//		 fScale				-- ͼƬ�����Ŵ�С
	// ���أ�����ִ�гɹ�������true�����򷵻�false
	virtual bool StartAction(const char* szType, int nDurationFrames)=0;	
};

#endif 
