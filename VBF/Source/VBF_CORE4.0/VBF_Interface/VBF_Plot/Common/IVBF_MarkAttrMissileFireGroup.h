//*******************************************************************
// FileName��IVBF_MarkAttrMissileFireGroup.h
// Function��ģ�����Խӿڣ�һ�鵼��β�棬�����ڶ������������β��
// Author:   ��Ө
// Date:     2014-12-02
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_MISSILE_FIRE_GROUP_H__
#define __IVBF_MARK_ATTR_MISSILE_FIRE_GROUP_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <VBF_Engine/VBF_SceneGraph/Image>


class IVBF_MarkAttrMissileFireGroup : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrMissileFireGroup() {}

	// ��������β�������
	virtual void SetNumMissileFires(int num)=0;
	virtual int  GetNumMissileFires()=0;

	// ��������ĳ��β����������ģ�����ĵ��ƫ������Ĭ��ֵΪ(0, 0, 0)��
	virtual void SetOffset(int nIndex, float fOffsetX, float fOffsetY, float fOffsetZ)=0;
	virtual void GetOffset(int nIndex, float& fOffsetX, float& fOffsetY, float& fOffsetZ)=0;

    // ����/��ȡ��������β��Ŀ�Ⱥ͸߶ȣ���λ���ף�
    virtual void SetSize(float fWidth, float fHeight)=0;
    virtual void GetSize(float& fWidth, float& fHeight)=0;

    // ����/��ȡ��������β��Ķ�̬����ֵ��Ĭ��ֵΪ0.2��
    virtual void  SetRandomScale(float fScale)=0;
    virtual float GetRandomScale()=0;

    // ����/��ȡ��������β���������
    virtual void              SetAxis(const osg::Vec3f& vAxis)=0;
    virtual const osg::Vec3f& GetAxis()=0;

	// ����/��ȡ��������β�������ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;
};


#endif 
