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

	// 从配置文件中装载特效对象的初始化信息
	virtual bool LoadFromXML(TiXmlElement* pElemEffect);

	// 执行特效对象的动作，动作参数从从配置文件元素中获取
	virtual bool StartFromXML(TiXmlElement* pElemAction);

	// 设置图像文件名
	virtual bool SetImageFileName(const char* szImgFileName);

	// 开始执行动画
	virtual bool StartAction(const char* strType, float x, float y, int nDurationFrames, float fAlpha, float fScale);//

	// 如果需要将图像框定在视口范围以内
	virtual void SetLockInViewport(bool bLocked) { m_bLockInViewport = bLocked; }	

	// 如果需要将图像根据视口范围缩放
	virtual void SetScaleWithViewport(bool bScale) { m_bScaleWithViewport = bScale; }	

    static ref_ptr<osg::IVBF_Camera> CreateHUDCamera(IVBF_3DMainCtrl* pI3DMainCtrl);
	
private:

	ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix>	CreateTransformNode();

private:	
	ref_ptr<osg::Image>					m_pImage;
	
	bool										m_bLockInViewport;		// 是否需要将图像框定在视口范围以内
	osg::Vec2f									m_RelPosition;			// 图片最终在视口中的相对位置
	osg::Vec2f									m_LastPosition;			// 图片上一次在视口中的相对位置
	ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix>			m_MatrixTransform;

	// 是否需要将图像根据视口范围缩放，从而确保Image2D特效在屏幕中占据固定的百分比
	bool										m_bScaleWithViewport;	
	int											m_nBestScreenResolutionX;	// 屏幕的最佳分辨率
	int											m_nBestScreenResolutionY;

	float										m_fAlpha;
	float										m_fScale;
	float										m_fLastScale;

	// 静态变量	
	static int									ms_nWndWidth;
	static int									ms_nWndHeight;
    ref_ptr<osg::IVBF_Camera> m_ipHUDCamera;
};

#endif
