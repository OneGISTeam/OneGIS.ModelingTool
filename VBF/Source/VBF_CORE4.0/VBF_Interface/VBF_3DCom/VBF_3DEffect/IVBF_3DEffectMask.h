//***************************************************************************************
// FileName��IVBF_3DEffectMask.h
// Function��3D�ɰ���ӿ�
// Author:   SunC
// Date:     2012-04-07
//***************************************************************************************

#ifndef __IVBF_3DEFFECT_MASK_H__
#define __IVBF_3DEFFECT_MASK_H__

#include "IVBF_3DEffect.h"
#include <string>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <Types/Vec2d>
#include <Types/Vec4f>


//-------------------------------------------------------------------
// ����ṹ�壺VBF_3DMASKSTYLE
// �ṹ���������ɰ���ʽ
//-------------------------------------------------------------------
typedef struct _tagVBF3DMaskStyle
{
	osg::Vec4f			cFillColor;				// �ɰ�������ɫ
	osg::Vec4f			cLineColor;				// �ɰ�߽��ߵ���ɫ
	float				fLineWidth;				// �ɰ�߽��ߵ��߿�
	float				fExtrusionHeight;		// �ɰ強���ĸ߶�

	// ���캯��
	_tagVBF3DMaskStyle()
	{
		cFillColor		  = osg::Vec4f(0.1f, 0.6f, 0.6f, 0.5f);	
		cLineColor		  = osg::Vec4f(0.1f, 0.6f, 0.6f, 0.5f);	
		fLineWidth		  = 1.0f;
		fExtrusionHeight  = 0.0f;
	}

	_tagVBF3DMaskStyle& operator=(const _tagVBF3DMaskStyle& src)
	{
		this->cFillColor		    = src.cFillColor;
		this->cLineColor		    = src.cLineColor;
		this->fLineWidth		    = src.fLineWidth;
		this->fExtrusionHeight  = src.fExtrusionHeight;

		return *this;
	}

} VBF_3DMASKSTYLE;


//-------------------------------------------------------------------
// ����ӿڣ�IVBF_3DEffectMask
// �ӿ��������ɰ���Ч
//-------------------------------------------------------------------
class IVBF_3DEffectMask : public IVBF_3DEffect
{
public:
	virtual ~IVBF_3DEffectMask() {}

public:

	// ���õ������괮
	virtual bool SetGeoVertices(osg::Vec3dArray* pVertices)=0;

	// ������ʽ
	virtual bool SetStyle(VBF_3DMASKSTYLE* pStyle)=0;

	// ���ñ�ǩ
	virtual bool SetLabel(const char* szLabel)=0;

    //-------------------------------------------------------------------------------------------------
	// ������StartAction()
	// �������ɶ��󴴽�����
	// ������EffectType			-- �������ͣ��μ��������Ͷ���
	//		nDurationFrames		-- ��������֡��
	//		alpha				-- ͸���ȣ����ڵ��붯����͸���ȴ�0���䵽alpha,���ڵ���������͸���ȴ�alpha���䵽0,��������������һֱ����alpha��͸����
	//		extrusionHeight		-- �ɰ強���߶�
	//-------------------------------------------------------------------------------------------------
	virtual bool StartAction(const char* szEffectType, int nDurationFrames, float fAlpha)=0;	
};

#endif