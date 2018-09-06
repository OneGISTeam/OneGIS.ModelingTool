//*******************************************************************
// FileName��IVBF_MarkAttrMissileFire.h
// Function��ģ�����Խӿڣ�����β��
// Author:   ��Ө
// Date:     2014-12-02
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_MISSILE_FIRE_H__
#define __IVBF_MARK_ATTR_MISSILE_FIRE_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <VBF_Engine/VBF_SceneGraph/Image>


class IVBF_MarkAttrMissileFire : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrMissileFire() {}

    // ����/��ȡβ��Ŀ�Ⱥ͸߶ȣ���λ���ף�
    virtual void SetSize(float fWidth, float fHeight)=0;
    virtual void GetSize(float& fWidth, float& fHeight)=0;

    // ����/��ȡβ��Ķ�̬����ֵ��Ĭ��ֵΪ0.2��
    virtual void  SetRandomScale(float fScale)=0;
    virtual float GetRandomScale()=0;

    // ����/��ȡβ���������
    virtual void              SetAxis(const osg::Vec3f& vAxis)=0;
    virtual const osg::Vec3f& GetAxis()=0;

	// ����β����������ģ�����ĵ��ƫ������Ĭ��ֵΪ(0, 0, 0)��
	virtual void SetOffset(float fOffsetX, float fOffsetY, float fOffsetZ)=0;
	virtual void GetOffset(float& fOffsetX, float& fOffsetY, float& fOffsetZ)=0;

	// ����/��ȡ����ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;
};


#endif 
