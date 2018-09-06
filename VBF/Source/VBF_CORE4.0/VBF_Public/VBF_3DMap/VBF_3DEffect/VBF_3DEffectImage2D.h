#ifndef __VBF_3DEFFECT_ACTION_H__
#define __VBF_3DEFFECT_ACTION_H__

#include "VBF_3DCom/VBF_3DEffect/IVBF_3DEffectImage2D.h"
#include <VBF_3DMap/VBF_3DEffect/VBF_3DEffectImpl.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SGDB/ReadFile>
#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Display/VBF_Viewer/VBF_ViewerSimple.h>
#include <VBF_3DMap/VBF_3DEffect/Export>

#include <map>
using namespace std;

class VBF_3DEFFECT_EXPORT CVBF_3DEffectImage2D : public CVBF_3DEffectImpl<IVBF_3DEffectImage2D>
{
public:	
    CVBF_3DEffectImage2D(IVBF_3DMainCtrl* pI3DMainCtrl, IVBF_View* pView, osg::IVBF_SGNodeGroup* pParentNode,osg::IVBF_Camera* pHUDCamera);
	virtual ~CVBF_3DEffectImage2D();	

	// �������ļ���װ����Ч����ĳ�ʼ����Ϣ
	virtual bool LoadFromXML(TiXmlElement* pElemEffect);

	// ִ����Ч����Ķ��������������Ӵ������ļ�Ԫ���л�ȡ
	virtual bool StartFromXML(TiXmlElement* pElemAction);

	// ����ͼ���ļ���
	virtual bool SetImageFileName(const char* szImgFileName);

	// ��ʼִ�ж���
	virtual bool StartAction(const char* strType, float x, float y, int nDurationFrames, float fAlpha, float fScale);//

	// �����Ҫ��ͼ������ӿڷ�Χ����
	virtual void SetLockInViewport(bool bLocked) { m_bLockInViewport = bLocked; }	

	// �����Ҫ��ͼ������ӿڷ�Χ����
	virtual void SetScaleWithViewport(bool bScale) { m_bScaleWithViewport = bScale; }	

    static ref_ptr<osg::IVBF_Camera> CreateHUDCamera(IVBF_3DMainCtrl* pI3DMainCtrl);
	
private:

	ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix>	CreateTransformNode();

private:	
	ref_ptr<osg::Image>					m_pImage;
	
	bool										m_bLockInViewport;		// �Ƿ���Ҫ��ͼ������ӿڷ�Χ����
	osg::Vec2f									m_RelPosition;			// ͼƬ�������ӿ��е����λ��
	osg::Vec2f									m_LastPosition;			// ͼƬ��һ�����ӿ��е����λ��
	ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix>			m_MatrixTransform;

	// �Ƿ���Ҫ��ͼ������ӿڷ�Χ���ţ��Ӷ�ȷ��Image2D��Ч����Ļ��ռ�ݹ̶��İٷֱ�
	bool										m_bScaleWithViewport;	
	int											m_nBestScreenResolutionX;	// ��Ļ����ѷֱ���
	int											m_nBestScreenResolutionY;

	float										m_fAlpha;
	float										m_fScale;
	float										m_fLastScale;

	// ��̬����	
	static int									ms_nWndWidth;
	static int									ms_nWndHeight;
    ref_ptr<osg::IVBF_Camera> m_ipHUDCamera;
};

#endif
