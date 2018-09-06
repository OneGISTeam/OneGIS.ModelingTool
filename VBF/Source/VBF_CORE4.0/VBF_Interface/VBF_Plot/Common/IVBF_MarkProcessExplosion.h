//*******************************************************************
// FileName��IVBF_MarkProcessExplosion.h
// Function����ը����
// Author:   �����
// Date:     2010-9-20
//*******************************************************************

#ifndef __IVBF_MARK_PROCESS_EXPLOSION_H__
#define __IVBF_MARK_PROCESS_EXPLOSION_H__


#include <VBF_Plot/IVBF_MarkProTimerTrigger.h>
#include <string>

#define VBF_MARK_PROCESS_EXPLOSION   "Explosion"	// ��ը

class IVBF_MarkProcessExplosion : public IVBF_MarkProTimerTrigger
{
protected:
	virtual ~IVBF_MarkProcessExplosion() {}

	// ����/��ȡ����������ը�����л���֡�����Ĭ��ֵΪ2��
	virtual void SetFrameInterval(int nFrameInterval)=0;
	virtual int  GetFrameInterval()=0;

	// ����/��ȡ��ըʱ�������ļ�������·����
	virtual void               SetSoundFileName(const std::string& strFileName)=0;
	virtual const std::string& GetSoundFileName()=0;

	// ����/��ȡ��ը�뾶����λ���ף�Ĭ��ֵΪ10000��
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;

	// ����/��ȡ����ͼ��ָ��
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;
};


#endif 
