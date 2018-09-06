//***************************************************************************************
// FileName��VBF_3DEffectImp.h
// Function��VBF_3DEffectģ����
//***************************************************************************************

#ifndef __VBF_3DEFFECT_IMPL_H__
#define __VBF_3DEFFECT_IMPL_H__

#include <VBF_OS.h>
#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>
#include "VBF_3DCom/VBF_3DEffect/IVBF_3DEffect.h"
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_Base/VBF_DelayDeleteHandler.h>
#include <VBF_Display/VBF_Viewer/VBF_ViewerSimple.h>
#include <VBF_Display/VBF_Viewer/VBF_ViewerEventHandlers.h>
#include <VBF_3DMap/VBF_3DEffect/Export>


using namespace osgEarth;


template<class T>
class CVBF_3DEffectImpl : public T
{	
public:
	CVBF_3DEffectImpl(IVBF_3DMainCtrl* pI3DMainCtrl, IVBF_View* pView, osg::IVBF_SGNodeGroup* pParentNode, const char* szType);
	virtual ~CVBF_3DEffectImpl();

	// ��ȡ��Ч����
	virtual const char* GetType()	{ return m_szType; }
	
	// ����/��ȡ��Ч��ȫ��ΨһID��
    virtual void        SetID(const char* szID)	{ if(szID!=NULL) VBF_strncpy(m_szID, szID, VBF_MAX_LENGTH_3DEFFECTID); }
	virtual const char* GetID()					{ return m_szID; }

	// ����/��ȡ��Чͼ��/��Ƶ�ļ��ĸ�·��
	virtual void		SetFilePath(const char* szPath)	{ if(szPath!=NULL) strcpy(m_szFilePath, szPath); }
	virtual const char*	GetFilePath()					{ return m_szFilePath; }

	// �������ļ���װ����Ч����ĳ�ʼ����Ϣ
	virtual bool LoadFromXML(TiXmlElement* pElemEffect) { return false; }

	// ִ����Ч����Ķ��������������Ӵ������ļ�Ԫ���л�ȡ
	virtual bool StartFromXML(TiXmlElement* pElemAction) { return false; }

protected:
    IVBF_3DMainCtrl*			m_pI3DMainCtrl;
    observer_ptr<IVBF_View>		m_opView;
    observer_ptr<CVBFO_SGNodeMap>	m_opMapNode;
    observer_ptr<osg::IVBF_SGNodeGroup>	 m_opParentNode; // ���ڵ� (���ⲿ��ȡ)

	// ��Ч�Ĺ�ͬ����
    char m_szType[VBF_MAX_LENGTH_3DEFFECTTYPE];		// ��Ч������
    char m_szID[VBF_MAX_LENGTH_3DEFFECTID];			// ��Ч��ȫ��ΨһID��
    char m_szFilePath[MAX_PATH];						// ��Ч��ͼ��/��Ƶ�ļ��ľ���·��
};

template<class T>
CVBF_3DEffectImpl<T>::CVBF_3DEffectImpl(IVBF_3DMainCtrl* pI3DMainCtrl, IVBF_View* pView, osg::IVBF_SGNodeGroup* pParentNode, const char* szType)
    : m_pI3DMainCtrl(pI3DMainCtrl), m_opView(pView), m_opParentNode(pParentNode)
{
    osg::IVBF_SGNodeGroup* pRoot = dynamic_cast<osg::IVBF_SGNodeGroup*>(m_opView->getSceneData());
	if(pRoot!=NULL)
	{
        m_opMapNode = CVBFO_SGNodeMap::findMapNode(pRoot);
	}	

	// ��Ч�Ĺ�ͬ����
	strcpy(m_szType, szType);
	
	m_szID[0]		= '\0';
	m_szFilePath[0] = '\0';
}


//---------------------------------------------------------------------
// ����������SetDeleteHandler()
// ��������������ɾ������ʹ�õĶ����ʱ��
//---------------------------------------------------------------------
inline void SetDeleteHandler()
{
	return;

	// ע�⣺���������ܻ���Σ��!!
	// Very important to call before end of main!
	if( !CVBF_Referenced::getDeleteHandler() ) 
	{
		CVBF_Referenced::setDeleteHandler( new ::DeleteHandler(2) );
	}

	if( CVBF_Referenced::getDeleteHandler() ) 
	{
		CVBF_Referenced::getDeleteHandler()->setNumFramesToRetainObjects(0);
		CVBF_Referenced::getDeleteHandler()->flushAll();
	}
}


template<class T>
CVBF_3DEffectImpl<T>::~CVBF_3DEffectImpl()
{
	SetDeleteHandler();
}


#endif
