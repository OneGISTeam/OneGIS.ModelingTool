//***************************************************************************************
// FileName�� IVBF_Fog.h
// Function�� ��Ч���ӿ�
// Author:    ��Ө
// Date:      2015-04-14
//***************************************************************************************

#ifndef __IVBF_FOG_H__
#define __IVBF_FOG_H__


#include <VBF_Base/VBF_Referenced.h>
#include <Types/Vec4f>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttribute.h>

class IVBF_Fog : public osg::StateSet::Callback
{
public:	
    virtual ~IVBF_Fog() {}

    // ����/��ȡ�Ƿ�����Ч����Ĭ��ֵΪfalse��
    virtual void Enable(bool bEnable)=0;
    virtual bool IsEnabled()=0;

    // ����/��ȡ�����ɫ��Ĭ��ֵΪ(0.66f, 0.7f, 0.81f, 1.0f)��
    virtual void              SetColor(const osg::Vec4f& color)=0;
    virtual const osg::Vec4f& GetColor()=0;

    // ����/��ȡ��Ũ��
    virtual void  SetDensity(float fDensity)=0;
    virtual float GetDensity()=0;
};

#endif 
