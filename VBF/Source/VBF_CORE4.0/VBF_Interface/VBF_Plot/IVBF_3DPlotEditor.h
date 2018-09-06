//***************************************************************************************
// FileName�� IVBF_3DPlotEditor.h
// Function�� 3D��ͼ�༭���ӿڣ�����ģ�͵ı༭
// Author:    ��Ө
// Date:      2015-01-02
//***************************************************************************************

#ifndef __IVBF_3DPLOT_EDITOR_H__
#define __IVBF_3DPLOT_EDITOR_H__


#include <VBF_Base/VBF_Referenced.h>
#include <string>
#include <Types/Vec4>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>

//------------------------------------------------------------------
// ����ö�٣�EVBF_EDITOR_ROTATE_TYPE
// ö��������ģ�ͱ༭ʱ����ת��ʽ
//------------------------------------------------------------------
enum EVBF_EDITOR_ROTATE_TYPE
{
	VBF_EDITOR_ROTATE_NONE	= 0,		// ��ֹ��ת
	VBF_EDITOR_ROTATE_XYZ	= 1,		// ͬʱ������ƽ������ת
	VBF_EDITOR_ROTATE_Z		= 2			// ����xoyƽ����ת
};

//------------------------------------------------------------------
// ����ö�٣�EVBF_EDITOR_SCALE_TYPE
// ö��������ģ�ͱ༭ʱ�����ŷ�ʽ
//------------------------------------------------------------------
enum EVBF_EDITOR_SCALE_TYPE
{
	VBF_EDITOR_SCALE_NONE	= 0,		// ��ֹ����
	VBF_EDITOR_SCALE_XYZ	= 1			// ͬʱ������������
};

//------------------------------------------------------------------
// ����ö�٣�EVBF_EDITOR_TRANSLATE_TYPE
// ö��������ģ�ͱ༭ʱ��ƽ�Ʒ�ʽ
//------------------------------------------------------------------
enum EVBF_EDITOR_TRANSLATE_TYPE
{
	VBF_EDITOR_TRANSLATE_NONE				= 0,	// ��ֹƽ��
	VBF_EDITOR_TRANSLATE_XYPLANE_ZAXIS		= 1,	// ������xyƽ�桢z��ȫ��ƽ��
	VBF_EDITOR_TRANSLATE_LOCAL_SAMEHEIGHT	= 2,	// �ֲ����Ƶ�����ͬ�߶��ƶ�
	VBF_EDITOR_TRANSLATE_LOCAL_DIFFHEIGHT	= 3		// �ֲ����Ƶ��ڲ�ͬ�߶��ƶ�
};
class IVBF_MarkModel;
// ����ѡ����Ϣ��ʾ�������Զ���ͼ��ʱͼ��Ĵ�����
class IVBF_MarkGraphicsCreator : public CVBF_Referenced
{
public:
    virtual CVBF_Graphics* CreateGraphics(IVBF_MarkModel* pIMark)=0;
};
//------------------------------------------------------------------
// ����ӿڣ�IVBF_3DPlotEditor
// �ӿ�������3D����ģ�͵ı༭�ӿ�
//------------------------------------------------------------------
class IVBF_3DPlotEditor : public CVBF_Referenced
{
public:
	virtual ~IVBF_3DPlotEditor() {}

    // ����/��ȡģ�ͱ༭ʹ�õ�Dragger�Ƿ�̶���С (��λ������)
	virtual void SetDraggerFixedSizeInPixels(bool bEnable, float fSizeInPixels=260)=0;
	virtual void GetDraggerFixedSizeInPixels(bool& bEnable, float& fSizeInPixels)=0;

	// ����/��ȡDragger���߶εĿ�ȣ�Ĭ��ֵΪ2.0��
	virtual void  SetDraggerLineWidth(float fWidth)=0;
	virtual float GetDraggerLineWidth()=0;

	// ����/��ȡDragger���߶��Ƿ�⻬��Ĭ��ֵΪtrue�����ĳЩ�Կ����߶��г��ֺ�ɫϸ�ߣ��ɽ���ѡ������Ϊfalse��
	virtual void EnableDraggerLineSmooth(bool bEnable)=0;
	virtual bool IsDraggerLineSmoothEnabled()=0;

	// ����/��ȡDragger���������������ɫ��Ĭ��ֵ�ֱ�Ϊ�졢�̡�����
	virtual void SetDraggerAxisColor(const osg::Vec4f& colorX, const osg::Vec4f& colorY, const osg::Vec4f& colorZ)=0;
	virtual void GetDraggerAxisColor(osg::Vec4f& colorX, osg::Vec4f& colorY, osg::Vec4f& colorZ)=0;
    virtual void SetQuickSelectInfTipAsChart(IVBF_MarkGraphicsCreator* pICreator)=0;
};


#endif
