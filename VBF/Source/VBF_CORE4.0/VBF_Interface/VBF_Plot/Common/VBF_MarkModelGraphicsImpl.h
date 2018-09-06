//*******************************************************************
// FileName��VBF_MarkModelGraphicsImpl.h
// Function�������Զ���ͼ��ʵ��ģ�͵�ģ�����
// Author:   ��Ө
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

	// ����/��ȡģ�͵����
	virtual void SetAppearance(IVBF_GraphicsAppearance* pAppearance);
	virtual IVBF_GraphicsAppearance* GetAppearance() { return &m_Appearance; }

	// ��Ӧ��۸ı����Ϣ����IVBF_GraphicsAppearanceOwner�ӿں���
	virtual void OnAppearanceChanged(EVBF_APPEARANCE_ATTR nAttr);

	// ���/�Ƴ��۲���
	virtual void AddObserver(IVBF_GraphicsObserver* pIObserver);
	virtual void RemoveObserver(IVBF_GraphicsObserver* pIObserver);

	// ��ȡ/�����۲���
	virtual int GetNumObservers()	{ return m_vObservers.size(); }
	virtual IVBF_GraphicsObserver* GetObserver(int nIndex)	{ return (nIndex>=0 && nIndex<(int)m_vObservers.size())? m_vObservers[nIndex].get() : NULL; }

	// ʹģ�ͽڵ�/��Ⱦ״̬ʧЧ
	virtual void DirtyModel();
	virtual void DirtyStateSet();

    // �Ҽ������˵�
    virtual void GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vItems);
    virtual bool ProcessPopupMenuItem(unsigned int nID);

	// ִ��json�ű�
	virtual void ExecuteScript(const CVBF_Config& conf);

protected:

	// ����ģ�ͽڵ�
	virtual bool CreateModelNode();

	// ����ģ���Զ���ͼ�Σ��������ظú�����
	virtual bool CreateModelDrawables() { return false; }

	// ������Ⱦ״̬
	virtual void SetStateSet();

	// ����/�ر�����Drawable�ı���ü������Ƿ�ͬʱ���������棩
	void EnableCullFace(bool bEnable);

	// ������ɫ��
//	virtual void SetShader_Solid(osg::StateSet* ss);

	// ֪ͨ���й۲���
	virtual void NotifyObservers(const char* szMessage);

    // ���л�
    virtual bool WriteModelToXML(TiXmlElement* pElemMark);
    virtual bool ReadModelFromXML(TiXmlElement* pElemMark);

protected:

	// ���
	CVBF_GraphicsAppearance					m_Appearance;

	// ����ͼ����
	bool									m_bUseVBO;			// �Ƿ�ʹ��VBO
	std::vector< ref_ptr<osg::Drawable>	>	m_vDrawables;		// ���ɻ�����
	ref_ptr<IVBF_SGNodeGroup>				m_piNodeSolid;		// ʵ�Ĳ���
	ref_ptr<IVBF_SGNodeGroup>				m_piNodeWireframe;	// ���񲿷�

	// �۲��ߣ��Ա�֪ͨ�Զ���ͼ�εĸ��ֱ仯
	std::vector< observer_ptr<IVBF_GraphicsObserver> > m_vObservers;
};

//-----------------------------------------------------------------------------
// ������CVBF_MarkModelGraphicsImpl()
// ���������캯��
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModelGraphicsImpl<T>::CVBF_MarkModelGraphicsImpl(const std::string& strMarkID)
	: BaseClass(strMarkID)
{
	m_bUseVBO = true;		// �Ƿ�ʹ��VBO

	// ��ģ���������������
	m_Appearance.SetOwner(this);

	// ���岿�ֱض����ڣ�ǰ���ǣ����岿��ö���ж���Ϊ0 ��
	m_Appearance.m_vPartInfos.resize(1);
	m_Appearance.m_vPartInfos[0].m_bExist = true; 

    // �Ҽ������˵�
    this->m_bEnableMenuFillMode = true;
}

//-----------------------------------------------------------------------------
// ������CVBF_MarkModelGraphicsImpl()
// ��������������
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModelGraphicsImpl<T>::~CVBF_MarkModelGraphicsImpl()
{
}
 
//-----------------------------------------------------------------------------
// ������AddObserver()
// ��������ӹ۲���
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::AddObserver(IVBF_GraphicsObserver* pIObserver)
{
	if(NULL==pIObserver) return;

	// �����ظ����
	for(unsigned int i=0; i<m_vObservers.size(); i++)
	{
		if(pIObserver==m_vObservers[i].get()) return;
	}

	m_vObservers.push_back(pIObserver);
}

//-----------------------------------------------------------------------------
// ������RemoveObserver()
// �������Ƴ��۲���
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
// ������NotifyObservers()
// ������֪ͨ���й۲���
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
// ������OnAppearanceChanged()
// ��������Ӧ��۸ı����Ϣ����IVBF_GraphicsAppearanceOwner�ӿں���
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
			DirtyModel();	// ʹģ�ͽڵ�ʧЧ
			break;

		case VBF_APPEARANCE_ATTR_LINEWIDTH:
		case VBF_APPEARANCE_ATTR_TEXTURE:
		case VBF_APPEARANCE_ATTR_DYNTEXTURE:
			DirtyStateSet();  // ʹ��Ⱦ״̬ʧЧ
			break;

		default:
			break;
	}
}

//-----------------------------------------------------------------------------
// ������DirtyModel()
// ������ʹģ�ͽڵ�ʧЧ
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::DirtyModel()
{
	BaseClass::DirtyModel();
	
	m_piNodeSolid     = NULL;
	m_piNodeWireframe = NULL;

	// �ڵ�ʧЧ����Ⱦ״̬Ҳ�ض�ʧЧ
	DirtyStateSet();

	// ֪ͨ���й۲���
	NotifyObservers(VBF_GRAPHICS_MESSAGE_MODEL_CHANGED);
}

//-----------------------------------------------------------------------------
// ������DirtyStateSet()
// ������ʹģ����Ⱦ״̬ʧЧ
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::DirtyStateSet()
{
	BaseClass::DirtyStateSet();

	// ֪ͨ���й۲���
	NotifyObservers(VBF_GRAPHICS_MESSAGE_STATESET_CHANGED);
}

//-----------------------------------------------------------------------------
// ����: CreateModelNode()
// ����: ����ģ�ͽڵ�
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelGraphicsImpl<T>::CreateModelNode()
{
	if( !CreateModelDrawables() ) return false;

	// ʵ�岿��
	m_piNodeSolid = ::VBF_CreateSGNodeGroup();
    m_piNodeSolid->setName("VBFNode_MarkNodeSolid: " + this->m_strID);

	// ���񲿷�
	m_piNodeWireframe = ::VBF_CreateSGNodeGroup();
    m_piNodeWireframe->setName("VBFNode_MarkNodeWireframe: " + this->m_strID);

	for(unsigned int i=0; i<m_vDrawables.size(); i++)
	{
        ref_ptr<osg::Drawable> ipDrawable = m_vDrawables[i];
        if(!ipDrawable.valid()) continue;
		
		unsigned int nStyle = (m_Appearance.m_vPartInfos.size()>0)? m_Appearance.m_vPartInfos[0].m_nStyleGeom : VBF_GEOMETRY_STYLE_WIREFRAME;
        ipDrawable->getUserValue<unsigned int>("GeomStyle", nStyle);

		// ʵ�岿��
        ref_ptr<osg::IVBF_SGNodeGeometry> ipGeodeS;
        bool bRenderSolid = ( (nStyle & VBF_GEOMETRY_STYLE_SOLID)==VBF_GEOMETRY_STYLE_SOLID );
		if(bRenderSolid)
        {
            ipGeodeS = ::VBF_CreateSGNodeGeometry();
            ipGeodeS->addDrawable(ipDrawable);
            ipGeodeS->setName(ipDrawable->getName());
            m_piNodeSolid->addChild(ipGeodeS);
		}

		// ���񲿷�
        ref_ptr<osg::IVBF_SGNodeGeometry> ipGeodeW;
        bool bRenderWireframe = ( (nStyle & VBF_GEOMETRY_STYLE_WIREFRAME)==VBF_GEOMETRY_STYLE_WIREFRAME );
		if(bRenderWireframe) 
        {
            ipGeodeW = ::VBF_CreateSGNodeGeometry();
            ipGeodeW->addDrawable(ipDrawable);
            ipGeodeW->setName(ipDrawable->getName());
            m_piNodeWireframe->addChild(ipGeodeW);
		}

		// ���ͬʱ����ʵ������񲿷֣���Ҫ���z-fighting����
		if(bRenderSolid && bRenderWireframe)
		{
			// ���񲿷֣��ر����д��
            ref_ptr<osg::StateSet> ss1 = ipGeodeW->getOrCreateStateSet();
			ref_ptr<osg::Depth> pDepth = new osg::Depth;
			pDepth->setWriteMask(false);
			ss1->setAttributeAndModes(pDepth, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE|osg::StateAttribute::PROTECTED);
		}
	}

	// �ҽ�ʵ������񲿷�
    ref_ptr<osg::IVBF_SGNodeGroup> ipNode = ::VBF_CreateSGNodeGroup();
    if(m_piNodeWireframe.valid())  ipNode->addChild(m_piNodeWireframe);
    if(m_piNodeSolid.valid())      ipNode->addChild(m_piNodeSolid);

    this->m_piNodeModel = ipNode.release();

	return true;
}

//-----------------------------------------------------------------------------
// ����: SetAppearance()
// ����: ����ģ�͵����
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::SetAppearance(IVBF_GraphicsAppearance* pAppearance) 
{ 
	if(pAppearance!=NULL) m_Appearance = *((CVBF_GraphicsAppearance*)pAppearance);

	// ֪ͨ���й۲���
	NotifyObservers(VBF_GRAPHICS_MESSAGE_APPEARANCE_CHANGED);
}

//-----------------------------------------------------------------------------
// ����: SetStateSet()
// ����: ������Ⱦ״̬
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::SetStateSet()
{
	BaseClass::SetStateSet();

	// ����ģ�͵���Ⱦ״̬
    if( this->m_piNodeModel.valid() )
	{
        osg::StateSet* ss = this->m_piNodeModel->getOrCreateStateSet();

		// ������Ⱦ˳��͸����
		ss->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

		// �������
		ss->setAttributeAndModes(new osg::BlendFunc(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA));
		ss->setMode(GL_BLEND, osg::StateAttribute::ON|osg::StateAttribute::PROTECTED|osg::StateAttribute::OVERRIDE);

		// �ر����д�루�����������͸��ģ���໥�ڵ������⣩
        osg::Depth* pDepth = dynamic_cast<osg::Depth*>( ss->getAttribute(osg::StateAttribute::DEPTH) );
        if(NULL==pDepth) pDepth = new osg::Depth;
        pDepth->setFunction(this->m_bEnableDepthTest? osg::Depth::LEQUAL : osg::Depth::ALWAYS);
		pDepth->setWriteMask(false);
		ss->setAttributeAndModes(pDepth, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE|osg::StateAttribute::PROTECTED);
	}

	// �������񲿷ֵ���Ⱦ״̬��ʹ����ɫ����
	if( m_piNodeWireframe.valid() )
	{
		osg::StateSet* ss1 = m_piNodeWireframe->getOrCreateStateSet();
		ss1->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE));

		// ע�⣺���񲿷ֲ�ʹ������/����
		ss1->setTextureMode(0, GL_TEXTURE_2D, osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED|osg::StateAttribute::OVERRIDE);
		ss1->setMode(GL_LIGHTING, osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED|osg::StateAttribute::OVERRIDE);

		// ������ɫ��
		::VBF_SetShader_Wireframe(this->m_pI3DMainCtrl, ss1);

		// ������Ⱦ˳��
		ss1->setRenderBinDetails(VBF_TRANSPARENT_BINBASE, "DepthSortedBin");

        // ��ÿ�����ֵ��������߿�
        int nNumParts = m_Appearance.m_vPartInfos.size();
        for(int i=0; i<nNumParts; i++)
        {
            CVBF_PartInfo& part = m_Appearance.m_vPartInfos[i];

            ref_ptr<osg::Drawable>& ipDrawable = part.m_ipDrawableWireframe;
            if(!ipDrawable.valid()) continue;

            osg::StateSet* ss = ipDrawable->getOrCreateStateSet();
            ss->setAttributeAndModes( new osg::LineWidth(part.m_LineStyle.fWidth) );

            // ���õ㻮��
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

	// ����ʵ�岿�ֵ���Ⱦ״̬��ʹ����ɫ����
	if( m_piNodeSolid.valid() )
	{
		osg::StateSet* ss0 = m_piNodeSolid->getOrCreateStateSet();
		ss0->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL));

        // Ϊÿ�����ֵ�����������
        int nNumParts = m_Appearance.m_vPartInfos.size();
        for(int i=0; i<nNumParts; i++)
        {
            CVBF_PartInfo& part = m_Appearance.m_vPartInfos[i];

            ref_ptr<osg::Drawable>& ipDrawable = part.m_ipDrawableSolid;
            if(!ipDrawable.valid()) continue;

            osg::StateSet* ssDrawable = ipDrawable->getOrCreateStateSet();

            // ��������
            ::VBF_SetPartTexture(ssDrawable, part);

            // ������ɫ��
            bool bEnableColor = (part.m_nStyleShade & VBF_SHADE_STYLE_COLOR)==VBF_SHADE_STYLE_COLOR;
            bool bEnableTex   = part.m_bEnableTex;

            // �ж������Ƿ���Ҫ���·�ת
            bool bFlipTex = false;
            if(bEnableTex && part.m_piImage.valid())
            {
                bFlipTex = ::VBF_ImageNeedsFlip( part.m_piImage.get() );
            }

            ::VBF_SetShader_Solid(this->m_pI3DMainCtrl, ssDrawable, bEnableColor, bEnableTex, this->m_bEnableLight,
                                  this->m_bEnableBlendColor, this->m_colorBlend, this->m_bBlendModulate, bFlipTex);

        }

		// �����Զ���һ����ע�⣺���߽�������������ϵ�������ã�
	#if !defined(OSG_GLES2_AVAILABLE)
		ss0->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
	#endif

		// ������Ⱦ˳��ȷ�������񲿷�֮����Ⱦ��
		ss0->setRenderBinDetails(VBF_TRANSPARENT_BINBASE+1, "DepthSortedBin");
	}
}

//-----------------------------------------------------------------------------
// ����: EnableCullFace()
// ����: ����/�ر�����Drawable�ı���ü������Ƿ�ͬʱ���������棩
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
// ������GetPopupMenuItems()
// ��������ȡ��ģ��֧�ֵ����е����˵���
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vItems)
{
	BaseClass::GetPopupMenuItems(vItems);

	// ���ģʽ
	if(NULL==this->m_pIParent && this->m_bEnableMenuFillMode)
	{
		EVBF_GEOMETRY_STYLE nStyle = m_Appearance.GetGeometryStyle(0);  // Ϊ�������ֻ�޸����岿�ֵ����ģʽ

		CVBF_PopupMenuItem itemSolid(IDM_ITEM_STYLE_RADIO_BEGIN, "���ģʽ", IDM_MARK_OPERATE_FILLMODE_SOLID, (nStyle==VBF_GEOMETRY_STYLE_SOLID) );
		vItems.push_back(itemSolid);

		CVBF_PopupMenuItem itemLine(IDM_ITEM_STYLE_RADIO, "����ģʽ", IDM_MARK_OPERATE_FILLMODE_WIREFRAME, (nStyle==VBF_GEOMETRY_STYLE_WIREFRAME) );
		vItems.push_back(itemLine);

		CVBF_PopupMenuItem itemComp(IDM_ITEM_STYLE_RADIO_END, "���ģʽ", IDM_MARK_OPERATE_FILLMODE_SOLIDWIREFRAME, (nStyle==VBF_GEOMETRY_STYLE_COMPOSITE) );
		vItems.push_back(itemComp);
	}
}

//-----------------------------------------------------------------------------
// ������ProcessPopupMenuItem()
// ��������Ӧĳ���˵���
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelGraphicsImpl<T>::ProcessPopupMenuItem(unsigned int nID)
{
	BaseClass::ProcessPopupMenuItem(nID);

	// ��Ӧ���ģʽ�˵���Ϊ�������ֻ�޸����岿�ֵ����ģʽ��
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
// ������WriteModelToXML()
// ������д��
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
// ������ReadModelFromXML()
// ��������ȡ
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
// ������ExecuteScript()
// ������ִ��json�ű�
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelGraphicsImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
	BaseClass::ExecuteScript(conf);

	conf.getIfSet("UseVBO", m_bUseVBO);
	
	m_Appearance.ExecuteScript(conf);  
}

#endif
