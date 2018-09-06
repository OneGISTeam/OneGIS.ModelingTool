//*******************************************************************
// FileName：VBF_MarkModel2DImpl.h
// Function：
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

	// 设置/获取坐标原点是否位于屏幕左上角（默认为true）
	virtual void SetOriginTopLeft(bool bTopLeft);
	virtual bool IsOriginTopLeft() { return m_bOriginTopLeft; }

    // 设置/获取图形占据的屏幕矩形
    virtual void SetClientRect(float x0, float x1, float y0, float y1);
    virtual void GetClientRect(float& x0, float& x1, float& y0, float& y1) { x0 = m_x0; y0 = m_y0; x1 = m_x1; y1 = m_y1; }

    // 串行化
    virtual bool WriteModelToXML(TiXmlElement* pElemMark);
    virtual bool ReadModelFromXML(TiXmlElement* pElemMark);

	// 执行json脚本
	virtual void ExecuteScript(const CVBF_Config& conf);

    // 设置渲染状态
    virtual void SetStateSet();

protected:

    // 初始化场景图
    virtual bool InitSG();

	// 如果用户输入的原点位于左上角，而OpenGL原点位于左下角，因此需要将y坐标反向
	void FlipCoordY(float& y0, float& y1);

protected:

	// 坐标原点是否位于屏幕左上角（默认为true）
	bool	m_bOriginTopLeft;

    // 屏幕矩形
    float	m_x0, m_x1, m_y0, m_y1;

    // 与场景图有关的内容
    ref_ptr<osg::Camera>	m_piHUDCamera;
};

//-----------------------------------------------------------------------------
// 函数：CVBF_MarkModel2DImpl()
// 描述：构造函数
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

    // 不需要地球背面的裁剪
    this->m_bEnableClipByEarth = false;
}

//-----------------------------------------------------------------------------
// 函数：InitSG()
// 描述：初始化模型的场景图
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModel2DImpl<T>::InitSG()
{
    // 创建模型的根节点，挂接在图层节点下
    this->m_piNodeRoot = new osg::Switch;
    this->m_piNodeRoot->setName("VBFNode_MarkRoot: " + this->m_strID);
    this->m_piNodeRoot->setValue(0, this->m_bVisible);
    this->m_piNodeRoot->setUserValue("VBFMarkPtr", (TYPE_PTR)this);

    // 创建HUD相机，添加到模型根节点下
    m_piHUDCamera = ::VBF_CreateHUDCamera( this->m_opCamera->getViewport() );
    m_piHUDCamera->setName("VBFNode_HUDCamera: " + this->m_strID);

    // 创建模型的Group节点，挂接在HUD相机下
    this->m_piNodeGroup = ::VBF_CreateSGNodeGroup();
    this->m_piNodeGroup->setName("VBFNode_MarkGroup: " + this->m_strID);

    // 依次挂接上述节点
    this->m_piNodeRoot->addChild(m_piHUDCamera);
    m_piHUDCamera->addChild(this->m_piNodeGroup);

    return true;
}

//---------------------------------------------------------------------------------------
// 函数：SetStateSet()
// 描述：设置渲染状态
//---------------------------------------------------------------------------------------
template<class T>
void CVBF_MarkModel2DImpl<T>::SetStateSet()
{
    BaseClass::SetStateSet();
}

//-----------------------------------------------------------------------------
// 函数：SetOriginTopLeft()
// 描述：设置坐标原点是否位于屏幕左上角（默认为true）
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModel2DImpl<T>::SetOriginTopLeft(bool bTopLeft)
{
	if(m_bOriginTopLeft==bTopLeft) return;

	m_bOriginTopLeft = bTopLeft;
	this->DirtyModel();
}

//-----------------------------------------------------------------------------
// 函数：SetClientRect()
// 描述：设置图形占据的屏幕矩形
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModel2DImpl<T>::SetClientRect(float x0, float x1, float y0, float y1)
{
    // 确保x0<x1, y0<y1
    m_x0 = osg::minimum(x0, x1);
    m_x1 = osg::maximum(x0, x1);
    m_y0 = osg::minimum(y0, y1);
    m_y1 = osg::maximum(y0, y1);

    this->DirtyModel();
}

//-----------------------------------------------------------------------------
// 函数：FlipCoordY()
// 描述：如果用户输入的原点位于左上角，而OpenGL原点位于左下角，因此需要将y坐标反向
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
// 函数：WriteModelToXML()
// 描述：写入
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModel2DImpl<T>::WriteModelToXML(TiXmlElement* pElemMark)
{
    if( !BaseClass::WriteModelToXML(pElemMark) ) return false;

    // 写入：图形占据的屏幕矩形
    ::VBF_SetAttribute(pElemMark, "x0",	m_x0);
    ::VBF_SetAttribute(pElemMark, "x1",	m_x1);
    ::VBF_SetAttribute(pElemMark, "y0",	m_y0);
    ::VBF_SetAttribute(pElemMark, "y1",	m_y1);

	// 写入：原点是否位于左上角
	::VBF_SetAttribute(pElemMark, "OriginTopLeft", m_bOriginTopLeft);

    return true;
}

//----------------------------------------------------------------------------
// 函数：ReadModelFromXML()
// 描述：读取
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModel2DImpl<T>::ReadModelFromXML(TiXmlElement* pElemMark)
{
    if(!BaseClass::ReadModelFromXML(pElemMark)) return false;

    // 读取：图形占据的屏幕矩形
    float x0, x1, y0, y1;
    GetClientRect(x0, x1, y0, y1);

    ::VBF_QueryAttribute(pElemMark, "x0", x0);
    ::VBF_QueryAttribute(pElemMark, "x1", x1);
    ::VBF_QueryAttribute(pElemMark, "y0", y0);
    ::VBF_QueryAttribute(pElemMark, "y1", y1);
    SetClientRect(x0, x1, y0, y1);

	// 读取：原点是否位于左上角
	bool bTopLeft = IsOriginTopLeft();
	::VBF_QueryAttribute(pElemMark, "OriginTopLeft", bTopLeft);
	SetOriginTopLeft(bTopLeft);

    return true;
}

//----------------------------------------------------------------------------
// 函数：ExecuteScript()
// 描述：执行json脚本
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModel2DImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
	BaseClass::ExecuteScript(conf);

	// 读取：图形占据的屏幕矩形
    osg::Vec4f vRect;
	GetClientRect(vRect.x(), vRect.y(), vRect.z(), vRect.w());
	if( conf.getIfSet("ClientRect", vRect) )
	{
		SetClientRect(vRect.x(), vRect.y(), vRect.z(), vRect.w()); 
	}

	// 读取：原点是否位于左上角
	bool bTopLeft = IsOriginTopLeft();
	if( conf.getIfSet("OriginTopLeft", bTopLeft) )
	{
		SetOriginTopLeft(bTopLeft);
	}
}


#endif 
