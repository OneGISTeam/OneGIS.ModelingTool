//*******************************************************************
// FileName��VBF_MarkModel2DImpl.h
// Function��
// Author:   
// Date:     
//*******************************************************************

#ifndef __VBF_MARK_MODEL_2D_IMPL_H__
#define __VBF_MARK_MODEL_2D_IMPL_H__

#include <VBF_Plot/VBF_MarkModelImpl.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrBlendFunc.h>


template<class T>
class CVBF_MarkModel2DImpl : public CVBF_MarkModelImpl<T>
{
private:
    typedef CVBF_MarkModelImpl<T> BaseClass;

public:
    CVBF_MarkModel2DImpl() {}
    CVBF_MarkModel2DImpl(const std::string& strMarkID);
    virtual ~CVBF_MarkModel2DImpl() {}

	// ����/��ȡ����ԭ���Ƿ�λ����Ļ���Ͻǣ�Ĭ��Ϊtrue��
	virtual void SetOriginTopLeft(bool bTopLeft);
	virtual bool IsOriginTopLeft() { return m_bOriginTopLeft; }

    // ����/��ȡͼ��ռ�ݵ���Ļ����
    virtual void SetClientRect(float x0, float x1, float y0, float y1);
    virtual void GetClientRect(float& x0, float& x1, float& y0, float& y1) { x0 = m_x0; y0 = m_y0; x1 = m_x1; y1 = m_y1; }

    // ���л�
    virtual bool WriteModelToXML(TiXmlElement* pElemMark);
    virtual bool ReadModelFromXML(TiXmlElement* pElemMark);

	// ִ��json�ű�
	virtual void ExecuteScript(const CVBF_Config& conf);

    // ������Ⱦ״̬
    virtual void SetStateSet();

protected:

    // ��ʼ������ͼ
    virtual bool InitSG();

	// ����û������ԭ��λ�����Ͻǣ���OpenGLԭ��λ�����½ǣ������Ҫ��y���귴��
	void FlipCoordY(float& y0, float& y1);

protected:

	// ����ԭ���Ƿ�λ����Ļ���Ͻǣ�Ĭ��Ϊtrue��
	bool	m_bOriginTopLeft;

    // ��Ļ����
    float	m_x0, m_x1, m_y0, m_y1;

    // �볡��ͼ�йص�����
    ref_ptr<osg::Camera>	m_piHUDCamera;
};

//-----------------------------------------------------------------------------
// ������CVBF_MarkModel2DImpl()
// ���������캯��
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModel2DImpl<T>::CVBF_MarkModel2DImpl(const std::string& strMarkID)
	: BaseClass(strMarkID)
{
	m_bOriginTopLeft = true;

    m_x0	= 0.0f;
    m_x1	= 100.0f;
    m_y0	= 0.0f;
    m_y1	= 100.0f;

    // ����Ҫ������Ĳü�
    this->m_bEnableClipByEarth = false;
}

//-----------------------------------------------------------------------------
// ������InitSG()
// ��������ʼ��ģ�͵ĳ���ͼ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModel2DImpl<T>::InitSG()
{
    // ����ģ�͵ĸ��ڵ㣬�ҽ���ͼ��ڵ���
    this->m_piNodeRoot = new osg::Switch;
    this->m_piNodeRoot->setName("VBFNode_MarkRoot: " + this->m_strID);
    this->m_piNodeRoot->setValue(0, this->m_bVisible);
    this->m_piNodeRoot->setUserValue("VBFMarkPtr", (TYPE_PTR)this);

    // ����HUD�������ӵ�ģ�͸��ڵ���
    m_piHUDCamera = ::VBF_CreateHUDCamera( this->m_opCamera->getViewport() );
    m_piHUDCamera->setName("VBFNode_HUDCamera: " + this->m_strID);

    // ����ģ�͵�Group�ڵ㣬�ҽ���HUD�����
    this->m_piNodeGroup = ::VBF_CreateSGNodeGroup();
    this->m_piNodeGroup->setName("VBFNode_MarkGroup: " + this->m_strID);

    // ���ιҽ������ڵ�
    this->m_piNodeRoot->addChild(m_piHUDCamera);
    m_piHUDCamera->addChild(this->m_piNodeGroup);

    return true;
}

//---------------------------------------------------------------------------------------
// ������SetStateSet()
// ������������Ⱦ״̬
//---------------------------------------------------------------------------------------
template<class T>
void CVBF_MarkModel2DImpl<T>::SetStateSet()
{
    BaseClass::SetStateSet();
}

//-----------------------------------------------------------------------------
// ������SetOriginTopLeft()
// ��������������ԭ���Ƿ�λ����Ļ���Ͻǣ�Ĭ��Ϊtrue��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModel2DImpl<T>::SetOriginTopLeft(bool bTopLeft)
{
	if(m_bOriginTopLeft==bTopLeft) return;

	m_bOriginTopLeft = bTopLeft;
	this->DirtyModel();
}

//-----------------------------------------------------------------------------
// ������SetClientRect()
// ����������ͼ��ռ�ݵ���Ļ����
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModel2DImpl<T>::SetClientRect(float x0, float x1, float y0, float y1)
{
    // ȷ��x0<x1, y0<y1
    m_x0 = osg::minimum(x0, x1);
    m_x1 = osg::maximum(x0, x1);
    m_y0 = osg::minimum(y0, y1);
    m_y1 = osg::maximum(y0, y1);

    this->DirtyModel();
}

//-----------------------------------------------------------------------------
// ������FlipCoordY()
// ����������û������ԭ��λ�����Ͻǣ���OpenGLԭ��λ�����½ǣ������Ҫ��y���귴��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModel2DImpl<T>::FlipCoordY(float& y0, float& y1)
{
	if(m_bOriginTopLeft && m_piHUDCamera.valid())
	{
		int nWndHeight = m_piHUDCamera->getViewport()->height();

		float dRectH = y1 - y0;
		y0 = nWndHeight - y1; 
		y1 = y0 + dRectH;
	}
}

//----------------------------------------------------------------------------
// ������WriteModelToXML()
// ������д��
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModel2DImpl<T>::WriteModelToXML(TiXmlElement* pElemMark)
{
    if( !BaseClass::WriteModelToXML(pElemMark) ) return false;

    // д�룺ͼ��ռ�ݵ���Ļ����
    ::VBF_SetAttribute(pElemMark, "x0",	m_x0);
    ::VBF_SetAttribute(pElemMark, "x1",	m_x1);
    ::VBF_SetAttribute(pElemMark, "y0",	m_y0);
    ::VBF_SetAttribute(pElemMark, "y1",	m_y1);

	// д�룺ԭ���Ƿ�λ�����Ͻ�
	::VBF_SetAttribute(pElemMark, "OriginTopLeft", m_bOriginTopLeft);

    return true;
}

//----------------------------------------------------------------------------
// ������ReadModelFromXML()
// ��������ȡ
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModel2DImpl<T>::ReadModelFromXML(TiXmlElement* pElemMark)
{
    if(!BaseClass::ReadModelFromXML(pElemMark)) return false;

    // ��ȡ��ͼ��ռ�ݵ���Ļ����
    float x0, x1, y0, y1;
    GetClientRect(x0, x1, y0, y1);

    ::VBF_QueryAttribute(pElemMark, "x0", x0);
    ::VBF_QueryAttribute(pElemMark, "x1", x1);
    ::VBF_QueryAttribute(pElemMark, "y0", y0);
    ::VBF_QueryAttribute(pElemMark, "y1", y1);
    SetClientRect(x0, x1, y0, y1);

	// ��ȡ��ԭ���Ƿ�λ�����Ͻ�
	bool bTopLeft = IsOriginTopLeft();
	::VBF_QueryAttribute(pElemMark, "OriginTopLeft", bTopLeft);
	SetOriginTopLeft(bTopLeft);

    return true;
}

//----------------------------------------------------------------------------
// ������ExecuteScript()
// ������ִ��json�ű�
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModel2DImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
	BaseClass::ExecuteScript(conf);

	// ��ȡ��ͼ��ռ�ݵ���Ļ����
    osg::Vec4f vRect;
	GetClientRect(vRect.x(), vRect.y(), vRect.z(), vRect.w());
	if( conf.getIfSet("ClientRect", vRect) )
	{
		SetClientRect(vRect.x(), vRect.y(), vRect.z(), vRect.w()); 
	}

	// ��ȡ��ԭ���Ƿ�λ�����Ͻ�
	bool bTopLeft = IsOriginTopLeft();
	if( conf.getIfSet("OriginTopLeft", bTopLeft) )
	{
		SetOriginTopLeft(bTopLeft);
	}
}


#endif 
