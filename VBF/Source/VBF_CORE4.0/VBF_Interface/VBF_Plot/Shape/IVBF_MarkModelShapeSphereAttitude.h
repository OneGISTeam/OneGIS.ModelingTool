//*******************************************************************
// FileName��IVBF_MarkModelShapeSphereAttitude.h
// Function������ʵ��ģ�ͣ���̬������չ�ַ�������ģ�����˶������е���̬��
// Author:   ��Ө
// Date:     2013-07-12
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_SPHERE_ATTITUDE_H__
#define __IVBF_MARK_MODEL_SHAPE_SPHERE_ATTITUDE_H__


#include <VBF_Plot/Shape/IVBF_MarkModelShapeDome.h>


//-----------------------------------------------------
// ����ö�٣�EVBF_AXIS
// ö��������������
//-----------------------------------------------------
enum EVBF_AXIS
{
	VBF_AXIS_X = 0,
	VBF_AXIS_Y = 1,
	VBF_AXIS_Z = 2
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeSphereAttitude
// �ӿ���������̬��
//--------------------------------------------------------------------
class IVBF_MarkModelShapeSphereAttitude : public IVBF_MarkModelShapeDome
{
public:
	virtual ~IVBF_MarkModelShapeSphereAttitude() {}

public:

	// ����/��ȡ����뾶��Ĭ������£�ԭ��λ�����ģ��뾶Ϊ1.0��
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;

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
