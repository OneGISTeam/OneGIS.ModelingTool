//*******************************************************************
// FileName��IVBF_GraphicsAppearance.h
// Function�������Զ���ͼ�ε��������
// Author:   ��Ө
// Date:     2013-11-11
//*******************************************************************

#ifndef __IVBF_APPEARANCE_ATTR_H__
#define __IVBF_APPEARANCE_ATTR_H__


#include <Types/Vec4>
#include <string>
#include <vector>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <Types/VBF_3DStyles.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_GEOMETRY_STYLE
// �ӿ��������Զ���ͼ�εļ�����ʽ������������ö��ֵ�ĵ���
//--------------------------------------------------------------------
enum EVBF_GEOMETRY_STYLE
{
	VBF_GEOMETRY_STYLE_SOLID		= 0x01,		// ֻ����ʵ��
	VBF_GEOMETRY_STYLE_WIREFRAME	= 0x02,		// ֻ��������
	VBF_GEOMETRY_STYLE_COMPOSITE	= (VBF_GEOMETRY_STYLE_SOLID | VBF_GEOMETRY_STYLE_WIREFRAME)		// ͬʱ����ʵ�ĺ�����
};

//--------------------------------------------------------------------
// ����ö�٣�EVBF_SHADE_STYLE
// �ӿ��������Զ���ͼ�ε���ɫ��ʽ������������ö��ֵ�ĵ���
//--------------------------------------------------------------------
enum EVBF_SHADE_STYLE
{
	VBF_SHADE_STYLE_COLOR		= 0x01,		// ֻʹ����ɫ
	VBF_SHADE_STYLE_TEXTURE		= 0x02,		// ֻʹ������
	VBF_SHADE_STYLE_COMPOSITE	= (VBF_SHADE_STYLE_COLOR | VBF_SHADE_STYLE_TEXTURE)		// ͬʱʹ����ɫ������
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_GraphicsAppearance
// �ӿ������������Զ���ͼ�ε��������
//--------------------------------------------------------------------
class IVBF_GraphicsAppearance
{
public:
	virtual ~IVBF_GraphicsAppearance() {}

public:
	// ����/��ȡ������ĳ�������Ƿ�ɼ���Ĭ��ֵΪtrue
	virtual void SetVisible(int nPart, bool bVisible)=0;
	virtual bool IsVisible(int nPart)=0;

	// ����/��ȡĳ�����ֵļ�����ʽ��Ĭ��Ϊ��ʵ��+����, 
	virtual void                SetGeometryStyle(int nPart, EVBF_GEOMETRY_STYLE nStyle)=0;
	virtual EVBF_GEOMETRY_STYLE GetGeometryStyle(int nPart)=0;

	// ����/��ȡĳ�����ֵ���ɫ��ʽ��Ĭ��Ϊ��ֻʹ����ɫ
	virtual void             SetShadeStyle(int nPart, EVBF_SHADE_STYLE nStyle)=0;
	virtual EVBF_SHADE_STYLE GetShadeStyle(int nPart)=0;

	// ����ĳ�����ֵĵ�һɫ������ɫ���������������壩��Ĭ��ֵΪ(1, 1, 1, 1) 
	virtual void       SetColor(int nPart, const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetColor(int nPart)=0;

	// ����ĳ�����ֵĽ���ɫ������ɫ�Ӽ����嶥��ƽ�����䵽�ײ�����Ĭ��ֵ��Ϊ(1, 1, 1, 1) 
	// ���û�����ý���ɫ��GetColor()��������false
	virtual void SetColor(int nPart, const osg::Vec4f& color0, const osg::Vec4f& color1)=0;
	virtual bool GetColor(int nPart, osg::Vec4f& color0, osg::Vec4f& color1)=0;

	// ���ĳ�����ֵ���ʽ�а����߿������ߵĴֶȣ��ߵ���ɫ�뼸������ͬ��
    virtual void  SetLineStyle(int nPart, const VBF_LINESTYLE& ls)=0;
    virtual VBF_LINESTYLE& GetLineStyle(int nPart)=0;

	// ����/��ȡĳ�����ֵ��������ݺ᷽����ظ�������Ĭ��ֵ��Ϊ1
	virtual void SetNumTexRepeats(int nPart, int nNumRows, int nNumCols)=0;
	virtual void GetNumTexRepeats(int nPart, int& nNumRows, int& nNumCols)=0;

	// �ж�ĳ�������Ƿ�����ʹ�õ�һɫ/����ɫ/��̬����/��̬����
	virtual bool IsUsingSingleColor(int nPart)=0;
	virtual bool IsUsingFadedColor(int nPart)=0;
	virtual bool IsUsingStaticTexture(int nPart)=0;
	virtual bool IsUsingDynamicTexture(int nPart)=0;

	// ��ȡ/����ĳ�����ֵ�����ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void		SetTexImage(int nPart, osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage(int nPart)=0;
};



//--------------------------------------------------------------------
// ����ö�٣�EVBF_APPEARANCE_ATTR
// ö���������Զ���ͼ�ε��������
//--------------------------------------------------------------------
enum EVBF_APPEARANCE_ATTR
{
	VBF_APPEARANCE_ATTR_VISIBILITY		= 0,	// �ɼ���
	VBF_APPEARANCE_ATTR_COLOR			= 1,	// ��ɫ
	VBF_APPEARANCE_ATTR_LINEWIDTH		= 2,	// �߿�
	VBF_APPEARANCE_ATTR_GEOMETRYSTYLE	= 3,	// ������ʽ��ʵ��/����
	VBF_APPEARANCE_ATTR_SHADESTYLE		= 4,	// ��ɫ��ʽ������/��ɫ
	VBF_APPEARANCE_ATTR_TEXTURE			= 5,	// ��̬����
	VBF_APPEARANCE_ATTR_DYNTEXTURE		= 6,	// ��̬����
	VBF_APPEARANCE_ATTR_TEXTURECOORDS	= 7		// ��������
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_GraphicsAppearanceOwner
// �ӿ������������Զ���ͼ�ε�������Ե�������
//--------------------------------------------------------------------
class IVBF_GraphicsAppearanceOwner
{
public:
	virtual ~IVBF_GraphicsAppearanceOwner() {}

	// ��Ӧ��۸ı����Ϣ������nAttr��ʾ����е�ĳ������
	virtual void OnAppearanceChanged(EVBF_APPEARANCE_ATTR nAttr)=0;
};


#endif 
