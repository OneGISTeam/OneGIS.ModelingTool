//*******************************************************************
// FileName��IVBF_MarkAttrTrailStrip.h
// Function��ģ�����Խӿڣ�ģ�����ԣ�ģ�͵��˶��켣�������Σ���ɻ���β����
//           ע�⣺ֻ����Mesh��ʵ��ģ��ʹ�������ι켣
// Author:   ��Ө
// Date:     2013-12-16
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_TRAIL_STRIP_H__
#define __IVBF_MARK_ATTR_TRAIL_STRIP_H__


#include <VBF_Plot/Common/IVBF_MarkAttrTrail.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/Image>


class IVBF_MarkAttrTrailStrip : public IVBF_MarkAttrTrail
{
public:
	virtual ~IVBF_MarkAttrTrailStrip() {}
	
	// ����/��ȡ��������ɫ��ע�⣺���������������ɫ��RGBA�����ֱ�������Ķ�Ӧ������ˣ�
	virtual void			  SetStripColor(const osg::Vec4f& color)=0;
	virtual const osg::Vec4f& GetStripColor()=0;

	// ����/��ȡ����ʹ�õ�����ͼ��
	virtual void		SetStripTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetStripTexImage()=0;

	// ����/��ȡβ�������Ŀ�ȣ���λ���ף�
	virtual void  SetStripWidth(float fWidth)=0;
	virtual float GetStripWidth()=0;

	// ����������������ģ��β�����ĵ��ƫ������Ĭ��ֵΪ(0, -1, 0)��
	virtual void SetStripOffset(float fOffsetX, float fOffsetY, float fOffsetZ)=0;
    virtual void GetStripOffset(float& fOffsetX, float& fOffsetY, float& fOffsetZ)=0;
};


#endif 
