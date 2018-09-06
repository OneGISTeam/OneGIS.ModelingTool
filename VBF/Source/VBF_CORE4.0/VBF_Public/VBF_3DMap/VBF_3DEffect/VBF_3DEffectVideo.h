#ifndef __VBF_3DEFFECT_VIDEO_H__
#define __VBF_3DEFFECT_VIDEO_H__

#include "VBF_3DCom/VBF_3DEffect/IVBF_3DEffectVideo.h"
#include <VBF_3DMap/VBF_3DEffect/VBF_3DEffectImpl.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SGDB/ReadFile>
#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Display/VBF_Viewer/VBF_ViewerSimple.h>
#include <VBF_Engine/VBF_SceneGraph/ImageStream>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTextureRectangle.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrDepth.h>
using namespace std;

#include <VBF_Display/IVBF_3DDisplay.h>

class CVBF_3DEffectVideo : public CVBF_3DEffectImpl<IVBF_3DEffectVideo>
{
public:	
	// ������szFileName	-- ��Ƶ��·��     
	CVBF_3DEffectVideo(IVBF_3DMainCtrl* pI3DMainCtrl, IVBF_View* pView,  osg::IVBF_SGNodeGroup* pParentNode);
	virtual ~CVBF_3DEffectVideo();

	// ������Ƶ�ļ�������������·��
	virtual bool SetVideoFileName(const char* szFileName);

	// �������ļ���װ����Ч����ĳ�ʼ����Ϣ
	virtual bool LoadFromXML(TiXmlElement* pElemEffect);

	// ִ����Ч����Ķ��������������Ӵ������ļ�Ԫ���л�ȡ
	virtual bool StartFromXML(TiXmlElement* pElemAction);

	// ��������
	virtual void SetPosition(bool isGeo, double x, double y, double z) { m_bGeo = isGeo; m_Position = osg::Vec3f(x, y, z); }

	// ������Ƶ��͸����
	virtual void SetAlpha(float fAlpha) { m_fAlpha = osg::clampTo(fAlpha, 0.0f, 1.0f); }

	// ��������Ƶ����
	virtual void Play();

	// ��������ͣ����
	virtual void Pause();

	// ��������Ƶ�˳�
	virtual void Stop();
	
private:
	bool Init();
	bool LoadVideo(const std::string  szFileName);
    ref_ptr<osg::IVBF_Camera> CreateHUDCamera();
    ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix> CreateHUDNode();
	ref_ptr<osg::Geometry>  CreateGeometry();
	ref_ptr<osg::IVBF_SGNodeGeometry>  CreateGeode();
	
protected:		
    osg::Vec3f								m_Position;		// ��Ƶ�Ĳ���λ��
    ref_ptr<osg::IVBF_SGNodeGeometry>		m_pGeode;

    bool									m_bGeo;	// �Ƿ�Ϊ��������
    float									m_fAlpha;

	// ��̬����	
    static int								ms_nWndWidth;
    static int								ms_nWndHeight;
    static ref_ptr<osg::IVBF_Camera>		ms_pHUDCamera;
    static map< string, ref_ptr<osg::Image> >	ms_mapImages;

    ref_ptr<osg::ImageStream>				m_ImageStream;		// ��¼Image��
    std::string								m_strImageFile;	// ��Ƶ·����
};

// ֻ�����ַ�����ImageStream������ϲ�������Ϣ��
class QuitCallback : public osg::NodeCallback
{
public:
	QuitCallback(osg::ImageStream* imagestream):_ImageStream(imagestream)
	{
		if(NULL!=_ImageStream) _length = _ImageStream->getLength();
	}

    virtual ~QuitCallback(){}
	virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv)
    {
		_current = _ImageStream->getReferenceTime();
		// κ�£��������Ϊ0.1s����ʱû�кõĽ���취
		if(osg::equivalent(_current, _length, 1e-1) )
		{
				_ImageStream->quit();
				osg::IVBF_SGNodeGeometry* geode = dynamic_cast<osg::IVBF_SGNodeGeometry*>(node);
				if(NULL != geode) 	geode->removeDrawables(0,1);
		}

        traverse(node,nv);
    }

protected:
	osg::ImageStream* _ImageStream;
	double _length;
	double _current;
};

class CVBF_VideoStateSetUpdateCallback : public osg::StateSet::Callback
{
public:
	CVBF_VideoStateSetUpdateCallback(IVBF_3DDisplay* pI3DDisplay) : m_pI3DDisplay(pI3DDisplay)
	{
	}	
	
    virtual void operator()(osg::StateSet* state, osg::NodeVisitor* nv)
    { 
        if(m_pI3DDisplay && state && nv->getVisitorType()==osg::NodeVisitor::UPDATE_VISITOR)
		{
			// �������ߵĸ����ǣ������Ƿ���z-write��������������洹ֱʱ�������Ʋ������
			osg::Depth* pDepth = dynamic_cast<osg::Depth*>( state->getAttribute(osg::StateAttribute::DEPTH) );
			if(pDepth) 
			{
                CVBF_Viewpoint vp = m_pI3DDisplay->GetViewpoint();
                bool bWriteMask = ( fabs(vp.getPitch()) < 50);

				pDepth->setWriteMask(bWriteMask);  
				pDepth->setFunction(bWriteMask? osg::Depth::LESS : osg::Depth::ALWAYS);
			}
        }
    }

private:
	IVBF_3DDisplay*		m_pI3DDisplay;
};

#endif
