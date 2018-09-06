//*******************************************************************
// FileName��IVBF_MarkAttrExplosion.h
// Function��ģ�����Խӿڣ���ը
// Author:   ��Ө
// Date:     2014-12-02
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_EXPLOSION_H__
#define __IVBF_MARK_ATTR_EXPLOSION_H__


#include <VBF_Plot/IVBF_MarkAttr.h>


class IVBF_MarkAttrExplosion : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrExplosion() {}

	// ����/��ȡ��ը��ʼ��ʱ�䣨�Ӹñ�ը���Ա���ӵ�ģ��֮�����㣬��λ���룩
	virtual void  SetStartTime(float fTime)=0;
	virtual float GetStartTime()=0;

	// ����/��ȡ����������ը�����л���֡�����Ĭ��ֵΪ2��
	virtual void SetFrameInterval(int nFrameInterval)=0;
	virtual int  GetFrameInterval()=0;

	// ����/��ȡ��ըʱ�������ļ�������·����
	virtual void               SetSoundFileName(const std::string& strFileName)=0;
	virtual const std::string& GetSoundFileName()=0;

	// ����/��ȡ��ը�뾶����λ���ף�
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;

	// ����/��ȡ����ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;
};


#endif 
