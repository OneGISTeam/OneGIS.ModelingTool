//*******************************************************************
// FileName��IVBF_MarkAttrSphereAttitude.h
// Function�����ԣ�ģ�͵���̬��
// Author:   ��Ө
// Date:     2015-04-28
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_SPHEREATTITUDE_H__
#define __IVBF_MARK_ATTR_SPHEREATTITUDE_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeSphereAttitude.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkAttrSphereAttitude
// �ӿ����������ԣ�ģ�͵���̬��
//--------------------------------------------------------------------
class IVBF_MarkAttrSphereAttitude : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrSphereAttitude() {}

    // ����/��ȡ����Lod������̬���л�ʱ��ģ�;����ӵ�ľ��루��λ���ף�
    virtual void  SetToggleDist(float fDist)=0;
    virtual float GetToggleDist()=0;

	// ����/��ȡx/y/z�������Ƿ�ɼ�
	virtual void SetAxisVisible(EVBF_AXIS nAxis, bool bVisible)=0;
	virtual bool IsAxisVisible(EVBF_AXIS nAxis)=0;

	// ����/��ȡx/y/z���������ɫ
	virtual void       SetAxisColor(EVBF_AXIS nAxis, const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetAxisColor(EVBF_AXIS nAxis)=0;

	// ����/��ȡx/y/z�������ͷ����ɫ
	virtual void       SetAxisArrowColor(EVBF_AXIS nAxis, const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetAxisArrowColor(EVBF_AXIS nAxis)=0;

	// ����/��ȡx/y/z������ı�ǩ�Ƿ�ɼ���Ĭ��ֵΪfalse��
	virtual void SetAxisTextVisible(EVBF_AXIS nAxis, bool bVisible)=0;
	virtual bool IsAxisTextVisible(EVBF_AXIS nAxis)=0;

	// ����/��ȡx/y/z������ı�ǩ��ʽ
	virtual void          SetAxisTextStyle(EVBF_AXIS nAxis, const VBF_TEXTSTYLE& style)=0;
	virtual VBF_TEXTSTYLE GetAxisTextStyle(EVBF_AXIS nAxis)=0;

    // ����/��ȡ��������뾭���ϵĿ̶��Ƿ�ɼ���Ĭ��ֵΪtrue��
    virtual void SetLabelVisible(bool bVisible)=0;
    virtual bool IsLabelVisible()=0;

    // ����/��ȡ��������뾭���ϵĿ̶���ʽ
    virtual void                 SetLabelStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetLabelStyle()=0;

    // ���/ɾ��һ�����������ᣨ����Ѿ����ڣ������ظ���ӣ�����false��
    virtual bool AddExtraAxis(const std::string& strAxisID, const osg::Vec3f& vAxisDir)=0;
    virtual void DeleteExtraAxis(const std::string& strAxisID)=0;

    // ����/��ȡĳ������������ĳ���ǰ���Ǹø������Ѿ��ɹ���ӣ�
    virtual void SetExtraAxisDir(const std::string& strAxisID, const osg::Vec3f& vAxisDir)=0;
    virtual bool GetExtraAxisDir(const std::string& strAxisID, osg::Vec3f& vAxisDir)=0;

    // ����/��ȡĳ���������������ɫ��ǰ���Ǹø������Ѿ��ɹ���ӣ�
    virtual void SetExtraAxisColor(const std::string& strAxisID, const osg::Vec4f& colorAxis, const osg::Vec4f& colorArrow)=0;
    virtual bool GetExtraAxisColor(const std::string& strAxisID, osg::Vec4f& colorAxis, osg::Vec4f& colorArrow)=0;

    // ����/��ȡĳ��������������ı���ʽ��ǰ���Ǹø������Ѿ��ɹ���ӣ�
    virtual void SetExtraAxisTextStyle(const std::string& strAxisID, const VBF_TEXTSTYLE& TextStyle)=0;
    virtual bool GetExtraAxisTextStyle(const std::string& strAxisID, VBF_TEXTSTYLE& TextStyle)=0;
};


#endif 
