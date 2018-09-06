//*******************************************************************
// FileName��IVBF_MarkAttrPowerMap.h
// Function������ͼ
// Author:   ��Ө
// Date:     2013-11-11 
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_POWER_MAP_H__
#define __IVBF_MARK_ATTR_POWER_MAP_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkAttrPowerMap
// �ӿ�����������ͼ
//--------------------------------------------------------------------
class IVBF_MarkAttrPowerMap : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrPowerMap() {}

public:

	// ����/��ȡ����ͼˮƽ�ʹ�ֱ�������ʼ�Ǻ���ֹ�ǣ�ֵ��ֱ�Ϊ[0, 360],[0, 180]
	// ˵������ֱ��Ϊ0�ȱ�ʾ��������ֱ��Ϊ180�ȱ�ʾ�ϼ���Ĭ������£�ԭ��λ�����ģ��뾶Ϊ1��
	virtual void SetTess(float fAngleH0, float fAngleH1, float fAngleV0, float fAngleV1)=0;
	virtual void GetTess(float& fAngleH0, float& fAngleH1, float& fAngleV0, float& fAngleV1)=0;

	// ����/��ȡ����ͼ�뾶��Ĭ��ֵΪ��1.0e5��
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;

	// ����/��ȡ����ͼ����ɫ
	virtual void       SetColor(const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetColor()=0;
	
	// ����/��ȡ����ͼ�ļ�����ʽ��Ĭ��Ϊ��ʵ��+����
	virtual void                SetGeometryStyle(EVBF_GEOMETRY_STYLE nStyle)=0;
	virtual EVBF_GEOMETRY_STYLE GetGeometryStyle()=0;
};



#endif 
