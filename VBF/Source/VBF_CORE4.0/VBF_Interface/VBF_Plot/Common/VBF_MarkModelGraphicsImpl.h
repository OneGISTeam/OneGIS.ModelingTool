//*******************************************************************
// FileName：VBF_MarkModelGraphicsImpl.h
// Function：各种自定义图形实体模型的模板基类
// Author:   杜莹
// Date:     2013-11-11
//*******************************************************************

#ifndef __VBF_MARK_MODEL_GRAPHICS_IMPL_H__
#define __VBF_MARK_MODEL_GRAPHICS_IMPL_H__


#include <VBF_Plot/VBF_MarkModelPointImpl.h>
#include <VBF_Plot/Common/IVBF_MarkModelGraphics.h>

#include <VBF_Aux/VBF_GLAux/VBF_GraphicsAppearance.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexEnv.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrPolygonMode.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrBlendFunc.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrMaterial.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLineWidth.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLightModel.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrCullFace.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrFrontFace.h>
#include <VBF_Aux/VBF_GLAux/VBF_ImageTextureUtils.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLineStipple.h>

template<class T>
class CVBF_MarkModelGraphicsImpl : public CVBF_MarkModelPointImpl<T>, 
								   public IVBF_GraphicsAppearanceOwner
{
private:
	typedef CVBF_MarkModelPointImpl<T> BaseClass;

public:
	CVBF_MarkModelGraphicsImpl() {}
	CVBF_MarkModelGraphicsImpl(const std::string& strMarkID);
	CVBF_MarkModelGraphicsImpl(const CVBF_MarkModelGraphicsImpl& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
	virtual ~CVBF_MarkModelGraphicsImpl();

	// 设置/获取模型的外观
	virtual void SetAppearance(IVBF_GraphicsAppearance* pAppearance);
	virtual IVBF_GraphicsAppearance* GetAppearance() { return &m_Appearance; }

	// 响应外观改变的消息，即IVBF_GraphicsAppearanceOwner接口函数
	virtual void OnAppearanceChanged(EVBF_APPEARANCE_ATTR nAttr);

	// 添加/移除观察者
	virtual void AddObserver(IVBF_GraphicsObserver* pIObserver);
	virtual void RemoveObserver(IVBF_GraphicsObserver* pIObserver);

	// 获取/遍历观察者
	virtual int GetNumObservers()	{ return m_vObservers.size(); }
	virtual IVBF_GraphicsObserver* GetObserver(int nIndex)	{ return (nIndex>=0 && nIndex<(int)m_vObservers.size())? m_vObservers[nIndex].get() : NULL; }

	// 使模型节点/渲染状态失效
	virtual void DirtyModel();
	virtual void DirtyStateSet();

    // 右键弹出菜单
    virtual void GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vItems);
    virtual bool ProcessPopupMenuItem(unsigned int nID);

	// 执行json脚本
	virtual void ExecuteScript(const CVBF_Config& conf);

protected:

	// 创建模型节点
	virtual bool CreateModelNode();

	// 构建模型自定义图形（必须重载该函数）
	virtual bool CreateModelDrawables() { return false; }

	// 设置渲染状态
	virtual void SetStateSet();

	// 开启/关闭所有Drawable的背面裁剪（即是否同时绘制正反面）
	void EnableCullFace(bool bEnable);

	// 设置着色器
//	virtual void SetShader_Solid(osg::StateSet* ss);

	// 通知所有观察者
	virtual void NotifyObservers(const char* szMessage);

    // 串行化
    virtual bool WriteModelToXML(TiXmlElement* pElemMark);
    virtual bool ReadModelFromXML(TiXmlElement* pElemMark);

protected:

	// 外观
	CVBF_GraphicsAppearance					m_Appearance;

	// 场景图内容
	bool									m_bUseVBO;			// 是否使用VBO
	std::vector< ref_ptr<osg::Drawable>	>	m_vDrawables;		// 若干绘制体
	ref_ptr<IVBF_SGNodeGroup>				m_piNodeSolid;		// 实心部分
	ref_ptr<IVBF_SGNodeGroup>				m_piNodeWireframe;	// 网格部分

	// 观察者，以便通知自定义图形的各种变化
	std::vector< observer_ptr<IVBF_GraphicsObserver> > m_vObservers;
};

//-----------------------------------------------------------------------------
// 函数：CVBF_MarkModelGraphicsImpl()
// 描述：构造函数
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModelGraphicsImpl<T>::CVBF_MarkModelGraphicsImpl(const std::string& strMarkID)
	: BaseClass(strMarkID)
{
	m_bUseVBO = true;		// 是否使用VBO

	// 给模型外观设置所有者
	m_Appearance.SetOwner(this);

	// 主体部分必定存在（前提是：主体部分枚举中定义为0 ）
	m_Appearance.m_vPartInfos.resize(1);
	m_Appearance.m_vPartInfos[0].m_bExist = true; 

    // 右键弹出菜单
    this->m_bEnableMenuFillMode = true;
}

//-----------------------------------------------------------------------------
// 函数：CVBF_MarkModelGraphicsImpl()
// 描述：析构函数
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModelGraphicsImpl<T>::~CVBF_MarkModelGraphicsImpl()
{
}
 
//-----------------------------------------------------------------------------
// 函数：AddObserver()
// 描述：添加观察者
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::AddObserver(IVBF_GraphicsObserver* pIObserver)
{
	if(NULL==pIObserver) return;

	// 避免重复添加
	for(unsigned int i=0; i<m_vObservers.size(); i++)
	{
		if(pIObserver==m_vObservers[i].get()) return;
	}

	m_vObservers.push_back(pIObserver);
}

//-----------------------------------------------------------------------------
// 函数：RemoveObserver()
// 描述：移除观察者
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::RemoveObserver(IVBF_GraphicsObserver* pIObserver)
{
	if(NULL==pIObserver) return;

	for(unsigned int i=0; i<m_vObservers.size(); i++)
	{
		if(pIObserver==m_vObservers[i].get())
		{
			m_vObservers.erase( m_vObservers.begin()+i );
			return;
		}
	}
}

//-----------------------------------------------------------------------------
// 函数：NotifyObservers()
// 描述：通知所有观察者
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::NotifyObservers(const char* szMessage)
{
	for(unsigned int i=0; i<m_vObservers.size(); i++)
	{
		m_vObservers[i]->OnGraphicsMessage(this, szMessage);
	}
}
 
//-----------------------------------------------------------------------------
// 函数：OnAppearanceChanged()
// 描述：响应外观改变的消息，即IVBF_GraphicsAppearanceOwner接口函数
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::OnAppearanceChanged(EVBF_APPEARANCE_ATTR nAttr)
{
	switch(nAttr)
	{
		case VBF_APPEARANCE_ATTR_VISIBILITY:
		case VBF_APPEARANCE_ATTR_COLOR:
		case VBF_APPEARANCE_ATTR_GEOMETRYSTYLE:
		case VBF_APPEARANCE_ATTR_SHADESTYLE:
		case VBF_APPEARANCE_ATTR_TEXTURECOORDS:
			DirtyModel();	// 使模型节点失效
			break;

		case VBF_APPEARANCE_ATTR_LINEWIDTH:
		case VBF_APPEARANCE_ATTR_TEXTURE:
		case VBF_APPEARANCE_ATTR_DYNTEXTURE:
			DirtyStateSet();  // 使渲染状态失效
			break;

		default:
			break;
	}
}

//-----------------------------------------------------------------------------
// 函数：DirtyModel()
// 描述：使模型节点失效
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::DirtyModel()
{
	BaseClass::DirtyModel();
	
	m_piNodeSolid     = NULL;
	m_piNodeWireframe = NULL;

	// 节点失效，渲染状态也必定失效
	DirtyStateSet();

	// 通知所有观察者
	NotifyObservers(VBF_GRAPHICS_MESSAGE_MODEL_CHANGED);
}

//-----------------------------------------------------------------------------
// 函数：DirtyStateSet()
// 描述：使模型渲染状态失效
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::DirtyStateSet()
{
	BaseClass::DirtyStateSet();

	// 通知所有观察者
	NotifyObservers(VBF_GRAPHICS_MESSAGE_STATESET_CHANGED);
}

//-----------------------------------------------------------------------------
// 函数: CreateModelNode()
// 描述: 创建模型节点
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelGraphicsImpl<T>::CreateModelNode()
{
	if( !CreateModelDrawables() ) return false;

	// 实体部分
	m_piNodeSolid = ::VBF_CreateSGNodeGroup();
    m_piNodeSolid->setName("VBFNode_MarkNodeSolid: " + this->m_strID);

	// 网格部分
	m_piNodeWireframe = ::VBF_CreateSGNodeGroup();
    m_piNodeWireframe->setName("VBFNode_MarkNodeWireframe: " + this->m_strID);

	for(unsigned int i=0; i<m_vDrawables.size(); i++)
	{
        ref_ptr<osg::Drawable> ipDrawable = m_vDrawables[i];
        if(!ipDrawable.valid()) continue;
		
		unsigned int nStyle = (m_Appearance.m_vPartInfos.size()>0)? m_Appearance.m_vPartInfos[0].m_nStyleGeom : VBF_GEOMETRY_STYLE_WIREFRAME;
        ipDrawable->getUserValue<unsigned int>("GeomStyle", nStyle);

		// 实体部分
        ref_ptr<osg::IVBF_SGNodeGeometry> ipGeodeS;
        bool bRenderSolid = ( (nStyle & VBF_GEOMETRY_STYLE_SOLID)==VBF_GEOMETRY_STYLE_SOLID );
		if(bRenderSolid)
        {
            ipGeodeS = ::VBF_CreateSGNodeGeometry();
            ipGeodeS->addDrawable(ipDrawable);
            ipGeodeS->setName(ipDrawable->getName());
            m_piNodeSolid->addChild(ipGeodeS);
		}

		// 网格部分
        ref_ptr<osg::IVBF_SGNodeGeometry> ipGeodeW;
        bool bRenderWireframe = ( (nStyle & VBF_GEOMETRY_STYLE_WIREFRAME)==VBF_GEOMETRY_STYLE_WIREFRAME );
		if(bRenderWireframe) 
        {
            ipGeodeW = ::VBF_CreateSGNodeGeometry();
            ipGeodeW->addDrawable(ipDrawable);
            ipGeodeW->setName(ipDrawable->getName());
            m_piNodeWireframe->addChild(ipGeodeW);
		}

		// 如果同时绘制实体和网格部分，需要解决z-fighting问题
		if(bRenderSolid && bRenderWireframe)
		{
			// 网格部分：关闭深度写入
            ref_ptr<osg::StateSet> ss1 = ipGeodeW->getOrCreateStateSet();
			ref_ptr<osg::Depth> pDepth = new osg::Depth;
			pDepth->setWriteMask(false);
			ss1->setAttributeAndModes(pDepth, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE|osg::StateAttribute::PROTECTED);
		}
	}

	// 挂接实体和网格部分
    ref_ptr<osg::IVBF_SGNodeGroup> ipNode = ::VBF_CreateSGNodeGroup();
    if(m_piNodeWireframe.valid())  ipNode->addChild(m_piNodeWireframe);
    if(m_piNodeSolid.valid())      ipNode->addChild(m_piNodeSolid);

    this->m_piNodeModel = ipNode.release();

	return true;
}

//-----------------------------------------------------------------------------
// 函数: SetAppearance()
// 描述: 设置模型的外观
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::SetAppearance(IVBF_GraphicsAppearance* pAppearance) 
{ 
	if(pAppearance!=NULL) m_Appearance = *((CVBF_GraphicsAppearance*)pAppearance);

	// 通知所有观察者
	NotifyObservers(VBF_GRAPHICS_MESSAGE_APPEARANCE_CHANGED);
}

//-----------------------------------------------------------------------------
// 函数: SetStateSet()
// 描述: 设置渲染状态
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::SetStateSet()
{
	BaseClass::SetStateSet();

	// 设置模型的渲染状态
    if( this->m_piNodeModel.valid() )
	{
        osg::StateSet* ss = this->m_piNodeModel->getOrCreateStateSet();

		// 设置渲染顺序（透明）
		ss->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

		// 开启混合
		ss->setAttributeAndModes(new osg::BlendFunc(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA));
		ss->setMode(GL_BLEND, osg::StateAttribute::ON|osg::StateAttribute::PROTECTED|osg::StateAttribute::OVERRIDE);

		// 关闭深度写入（解决内外两个透明模型相互遮挡的问题）
        osg::Depth* pDepth = dynamic_cast<osg::Depth*>( ss->getAttribute(osg::StateAttribute::DEPTH) );
        if(NULL==pDepth) pDepth = new osg::Depth;
        pDepth->setFunction(this->m_bEnableDepthTest? osg::Depth::LEQUAL : osg::Depth::ALWAYS);
		pDepth->setWriteMask(false);
		ss->setAttributeAndModes(pDepth, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE|osg::StateAttribute::PROTECTED);
	}

	// 设置网格部分的渲染状态（使用着色器）
	if( m_piNodeWireframe.valid() )
	{
		osg::StateSet* ss1 = m_piNodeWireframe->getOrCreateStateSet();
		ss1->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE));

		// 注意：网格部分不使用纹理/光照
		ss1->setTextureMode(0, GL_TEXTURE_2D, osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED|osg::StateAttribute::OVERRIDE);
		ss1->setMode(GL_LIGHTING, osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED|osg::StateAttribute::OVERRIDE);

		// 设置着色器
		::VBF_SetShader_Wireframe(this->m_pI3DMainCtrl, ss1);

		// 设置渲染顺序
		ss1->setRenderBinDetails(VBF_TRANSPARENT_BINBASE, "DepthSortedBin");

        // 对每个部分单独设置线宽
        int nNumParts = m_Appearance.m_vPartInfos.size();
        for(int i=0; i<nNumParts; i++)
        {
            CVBF_PartInfo& part = m_Appearance.m_vPartInfos[i];

            ref_ptr<osg::Drawable>& ipDrawable = part.m_ipDrawableWireframe;
            if(!ipDrawable.valid()) continue;

            osg::StateSet* ss = ipDrawable->getOrCreateStateSet();
            ss->setAttributeAndModes( new osg::LineWidth(part.m_LineStyle.fWidth) );

            // 设置点划线
            if( part.m_LineStyle.nStipplePattern != 0xFFFF )
            {
                osg::LineStipple* pStipple = new osg::LineStipple(part.m_LineStyle.nStippleFactor, part.m_LineStyle.nStipplePattern);
                ss->setAttributeAndModes(pStipple, osg::StateAttribute::ON);
                ss->setMode(GL_LINE_STIPPLE, osg::StateAttribute::ON|osg::StateAttribute::PROTECTED|osg::StateAttribute::OVERRIDE);
            }
            else
            {
                ss->setMode(GL_LINE_STIPPLE, osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED|osg::StateAttribute::OVERRIDE);
            }
        }
	}

	// 设置实体部分的渲染状态（使用着色器）
	if( m_piNodeSolid.valid() )
	{
		osg::StateSet* ss0 = m_piNodeSolid->getOrCreateStateSet();
		ss0->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL));

        // 为每个部分单独设置纹理
        int nNumParts = m_Appearance.m_vPartInfos.size();
        for(int i=0; i<nNumParts; i++)
        {
            CVBF_PartInfo& part = m_Appearance.m_vPartInfos[i];

            ref_ptr<osg::Drawable>& ipDrawable = part.m_ipDrawableSolid;
            if(!ipDrawable.valid()) continue;

            osg::StateSet* ssDrawable = ipDrawable->getOrCreateStateSet();

            // 设置纹理
            ::VBF_SetPartTexture(ssDrawable, part);

            // 设置着色器
            bool bEnableColor = (part.m_nStyleShade & VBF_SHADE_STYLE_COLOR)==VBF_SHADE_STYLE_COLOR;
            bool bEnableTex   = part.m_bEnableTex;

            // 判断纹理是否需要上下翻转
            bool bFlipTex = false;
            if(bEnableTex && part.m_piImage.valid())
            {
                bFlipTex = ::VBF_ImageNeedsFlip( part.m_piImage.get() );
            }

            ::VBF_SetShader_Solid(this->m_pI3DMainCtrl, ssDrawable, bEnableColor, bEnableTex, this->m_bEnableLight,
                                  this->m_bEnableBlendColor, this->m_colorBlend, this->m_bBlendModulate, bFlipTex);

        }

		// 法线自动归一化（注意：法线仅仅在人眼坐标系中起作用）
	#if !defined(OSG_GLES2_AVAILABLE)
		ss0->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
	#endif

		// 设置渲染顺序（确保在网格部分之后渲染）
		ss0->setRenderBinDetails(VBF_TRANSPARENT_BINBASE+1, "DepthSortedBin");
	}
}

//-----------------------------------------------------------------------------
// 函数: EnableCullFace()
// 描述: 开启/关闭所有Drawable的背面裁剪（即是否同时绘制正反面）
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::EnableCullFace(bool bEnable)
{
	osg::StateAttribute::GLModeValue nCullMode = (bEnable)? osg::StateAttribute::ON : osg::StateAttribute::OFF;

	for(unsigned int i=0; i<m_vDrawables.size(); i++)
	{
		ref_ptr<osg::Drawable> piDrawable = m_vDrawables[i];
		if(!piDrawable.valid()) continue;

		ref_ptr<osg::StateSet> ss = piDrawable->getOrCreateStateSet();
		ss->setMode(GL_CULL_FACE, nCullMode|osg::StateAttribute::PROTECTED);
	}
}

//-----------------------------------------------------------------------------
// 函数：GetPopupMenuItems()
// 描述：获取该模型支持的所有弹出菜单项
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vItems)
{
	BaseClass::GetPopupMenuItems(vItems);

	// 填充模式
	if(NULL==this->m_pIParent && this->m_bEnableMenuFillMode)
	{
		EVBF_GEOMETRY_STYLE nStyle = m_Appearance.GetGeometryStyle(0);  // 为简单起见，只修改主体部分的填充模式

		CVBF_PopupMenuItem itemSolid(IDM_ITEM_STYLE_RADIO_BEGIN, "填充模式", IDM_MARK_OPERATE_FILLMODE_SOLID, (nStyle==VBF_GEOMETRY_STYLE_SOLID) );
		vItems.push_back(itemSolid);

		CVBF_PopupMenuItem itemLine(IDM_ITEM_STYLE_RADIO, "网格模式", IDM_MARK_OPERATE_FILLMODE_WIREFRAME, (nStyle==VBF_GEOMETRY_STYLE_WIREFRAME) );
		vItems.push_back(itemLine);

		CVBF_PopupMenuItem itemComp(IDM_ITEM_STYLE_RADIO_END, "混合模式", IDM_MARK_OPERATE_FILLMODE_SOLIDWIREFRAME, (nStyle==VBF_GEOMETRY_STYLE_COMPOSITE) );
		vItems.push_back(itemComp);
	}
}

//-----------------------------------------------------------------------------
// 函数：ProcessPopupMenuItem()
// 描述：响应某个菜单项
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelGraphicsImpl<T>::ProcessPopupMenuItem(unsigned int nID)
{
	BaseClass::ProcessPopupMenuItem(nID);

	// 响应填充模式菜单（为简单起见，只修改主体部分的填充模式）
	if(nID==IDM_MARK_OPERATE_FILLMODE_SOLID)
	{
		m_Appearance.SetGeometryStyle(0, VBF_GEOMETRY_STYLE_SOLID);
		return true;
	}
	else if(nID==IDM_MARK_OPERATE_FILLMODE_WIREFRAME)
	{
		m_Appearance.SetGeometryStyle(0, VBF_GEOMETRY_STYLE_WIREFRAME);
		return true;
	}
	else if(nID==IDM_MARK_OPERATE_FILLMODE_SOLIDWIREFRAME)
	{
		m_Appearance.SetGeometryStyle(0, VBF_GEOMETRY_STYLE_COMPOSITE);
		return true;
	}

	return false;
}

//----------------------------------------------------------------------------
// 函数：WriteModelToXML()
// 描述：写入
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelGraphicsImpl<T>::WriteModelToXML(TiXmlElement* pElemMark)
{
    if( !BaseClass::WriteModelToXML(pElemMark) ) return false;

    ::VBF_SetAttribute(pElemMark, "UseVBO", m_bUseVBO);

    TiXmlElement* pElemAppr = new TiXmlElement("Appearance");
    pElemMark->LinkEndChild(pElemAppr);

    m_Appearance.WriteToXML(pElemAppr);

    return true;
}

//----------------------------------------------------------------------------
// 函数：ReadModelFromXML()
// 描述：读取
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelGraphicsImpl<T>::ReadModelFromXML(TiXmlElement* pElemMark)
{
    if(!BaseClass::ReadModelFromXML(pElemMark)) return false;

    ::VBF_QueryAttribute(pElemMark, "UseVBO", m_bUseVBO);

    TiXmlElement* pElemAppr = pElemMark->FirstChildElement("Appearance");
    if(pElemAppr!=NULL)
    {
        m_Appearance.ReadFromXML(pElemAppr);
    }

    return true;
}

//----------------------------------------------------------------------------
// 函数：ExecuteScript()
// 描述：执行json脚本
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
	BaseClass::ExecuteScript(conf);

	conf.getIfSet("UseVBO", m_bUseVBO);
	
	m_Appearance.ExecuteScript(conf);  
}

#endif
