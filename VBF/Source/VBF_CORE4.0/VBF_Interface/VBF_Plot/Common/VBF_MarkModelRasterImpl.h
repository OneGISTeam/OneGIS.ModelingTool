//*******************************************************************
// FileName��VBF_MarkModelRasterImpl.h
// Function������ʵ��ģ�͵�ģ�����ࣺʹ��դ��ͼ��ľ���,���ڱ��ָ�����Ⱦ���
// Author:   
// Date:     
//*******************************************************************

#ifndef __VBF_MARK_MODEL_RASTER_IMPL_H__
#define __VBF_MARK_MODEL_RASTER_IMPL_H__


#include <VBF_Plot/Common/IVBF_MarkModelRaster.h>
#include <VBF_Aux/VBF_GLAux/VBF_PrimitiveUtils.h>
#include <VBF_Plot/VBF_MarkModelPointImpl.h>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>
#include <VBF_Aux/VBF_GLAux/VBF_ImageTextureUtils.h>

#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrBlendFunc.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexEnv.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrPolygonMode.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLineWidth.h>
#include <VBF_Engine/VBF_SceneGraph/ImageStream>


template<class T>
class CVBF_MarkModelRasterImpl : public CVBF_MarkModelPointImpl<T>  
{
private:
	typedef CVBF_MarkModelPointImpl<T>  BaseClass;

public:
	CVBF_MarkModelRasterImpl() {}
	CVBF_MarkModelRasterImpl(const std::string& strMarkID);
	CVBF_MarkModelRasterImpl(const CVBF_MarkModelRasterImpl& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
	virtual ~CVBF_MarkModelRasterImpl();

	// ����/��ȡ����ͼ��ָ��
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache);
	virtual osg::Image* GetTexImage() { return m_piImage.get(); }

    // ����/��ȡ�����͸���ȣ�Ĭ��ֵΪ1.0��
    virtual void  SetTexAlpha(float fAlpha);
    virtual float GetTexAlpha() { return m_fTexAlpha; }
    virtual void  SetTexColor(osg::Vec4f color);

    virtual void SetAutoEnlarge(float fScaleMax, float fDelta, bool bMultify);

	// ����/��ȡ����ԭ����λͼ�е����λ�� (��������½ǣ�ֵ��Ϊ[0.0, 1.0])
	virtual void SetTexOrign(float fTexOrignX, float fTexOrignY);
	virtual void GetTexOrign(float& fTexOrignX, float& fTexOrignY)	{ fTexOrignX = m_fTexOrignX; fTexOrignY = m_fTexOrignY; }

	// ����/��ȡͼ�񾭹����ź��ʵ�ʳߴ磨��λ���ף�����������EnableFixedSizeInPixels(false)�����
	// ע�⣺����˴����õĳ���Ȳ�����ԭʼ����ȣ��ᵼ��ͼ�����
	virtual void SetSizeInMeters(float fWidth, float fHeight);
	virtual void GetSizeInMeters(float& fWidth, float& fHeight) { fWidth = m_fWidthInMeters; fHeight = m_fHeightInMeters; }

    // ��ȡģ���ڸ�������ϵ�µİ�Χ��
    virtual const osg::BoundingBoxd& GetBoundingBoxInGeo();

    // д��/��ȡģ�ͱ������Ϣ
    virtual bool WriteModelToXML(TiXmlElement* pElemMark);
    virtual bool ReadModelFromXML(TiXmlElement* pElemMark);

	// ִ��json�ű�
	void ExecuteScript(const CVBF_Config& conf);

    // ���� (ÿ֡����ǰ����)
    virtual bool Update();

protected:

	// ����ģ�͵ĳ���ͼ
	virtual bool CreateModelNode();

	// ������Ⱦ״̬
    virtual void SetStateSet();

    virtual void UpdateTexAlpha();
    virtual void UpdateTexOrign();
    virtual void UpdateSizeInMeters();

    // �����ӵ㵽ģ�͵ľ��룬�ж�ģ��/�����Ƿ��ڿɼ�������
    virtual void ClipModelByDist();

protected:
	float			m_fTexOrignX;		// ����ԭ����λͼ�е����λ�� (��������½�)
	float			m_fTexOrignY;
	float           m_fTexAlpha;		// ����͸����
    osg::Vec4f      m_vColor;// �������ɫ

	// �Զ������Ч������ը��
	bool			m_bAutoEnlarge;
	bool			m_bMultify;
	float			m_fScaleMax;
	float			m_fMultifyDelta;

	// ͼ��������
	ref_ptr<osg::Image>         m_piImage;		// ͼ��
	ref_ptr<osg::Texture2D>     m_piTexture;	// ����
	bool						m_bTexToCache;	// �����Ƿ���Ҫ���뻺��

    // �û����õ�ͼ���ھ������ź��ʵ�ʳߴ磨��λ���ף�
    bool            m_bDirtySizeInMeters;
    float           m_fWidthInMeters;
    float           m_fHeightInMeters;

    // ��ֱ�ӽǵ���ֵ��С�ڸ�ֵʱ����Ҫ����z-buffer
    float           m_fAngleVLimit;

    // ����ͼ�ڵ�
    ref_ptr<osg::Geometry>      m_piGeom;      // ģ���ı��ζ�Ӧ��Drawable
};

template<class T>
CVBF_MarkModelRasterImpl<T>::CVBF_MarkModelRasterImpl(const std::string& strMarkID)
    : BaseClass(strMarkID)
{
    this->m_nType       = VBF_MARK_RASTER;
    this->m_nViewMode   = VBF_VIEW_MODE_BILLBOARD_HV;   // �۲�ģʽ

    this->m_bEnableFixedSizeInPixels = true;
    this->m_fFixedSizeInPixels       = 16;

	m_fTexOrignX            = 0.5;
	m_fTexOrignY			= 0.0;
	m_fTexAlpha				= 1.0f;
    m_vColor                = osg::Vec4f(1.0,1.0,1.0,1.0);
	m_bTexToCache			= true;

    // �û����õ�ͼ���ھ������ź��ʵ�ʳߴ磨��λ���ף�
    m_bDirtySizeInMeters    = false;
    m_fWidthInMeters        = 0.0f;
    m_fHeightInMeters       = 0.0f;

    m_bAutoEnlarge          = false;
    m_fScaleMax             = FLT_MAX;
    m_fMultifyDelta         = 1.0f;

    m_fAngleVLimit          = 0.0f;
}

template<class T>
CVBF_MarkModelRasterImpl<T>::~CVBF_MarkModelRasterImpl()
{
    osg::ImageStream* pImageStream = dynamic_cast<osg::ImageStream*>(m_piImage.get());
    if(pImageStream) pImageStream->quit();
}

//-----------------------------------------------------------------------------
// ������SetTexImage()
// ��������������ͼ���ָ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::SetTexImage(osg::Image* pImage, bool bTexToCache)
{
	m_piImage     = pImage;
	m_bTexToCache = bTexToCache;

	// ʹģ�ͽڵ����Ⱦ״̬ʧЧ
	this->DirtyModel();
	this->DirtyStateSet();
}

//-----------------------------------------------------------------------------
// ������SetTexAlpha()
// ����������ģ�������͸����
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::SetTexAlpha(float fAlpha)
{
    if( osg::equivalent(m_fTexAlpha, fAlpha) ) return;

    m_fTexAlpha = osg::clampBetween(fAlpha, 0.0f, 1.0f);

    // ʹģ�͵Ķ�����ɫʧЧ
    this->DirtyModel();
}
// ������SetTexColor()
// ����������ģ���������ɫ
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::SetTexColor(osg::Vec4f color)
{
    m_vColor = color;

    // ʹģ�͵Ķ�����ɫʧЧ
    this->DirtyModel();
}

//-----------------------------------------------------------------------------
// ������SetTexOrign()
// ��������������ԭ����λͼ�е����λ�� (��������½ǣ�ֵ��Ϊ[0.0, 1.0])
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::SetTexOrign(float fTexOrignX, float fTexOrignY)	
{ 
    if( osg::equivalent(m_fTexOrignX, fTexOrignX) && osg::equivalent(m_fTexOrignY, fTexOrignY) ) return;

	m_fTexOrignX  = osg::clampBetween(fTexOrignX, 0.0f, 1.0f); 
	m_fTexOrignY  = osg::clampBetween(fTexOrignY, 0.0f, 1.0f);

    // ʹģ�͵Ķ�������ʧЧ
    this->DirtyModel();
}
 
//-----------------------------------------------------------------------------
// ������SetAutoEnlarge()
// �����������Զ�����ϵ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::SetAutoEnlarge(float fScaleMax, float fDelta, bool bMultify)
{
	m_bAutoEnlarge	= true;
	m_fScaleMax		= fScaleMax;
	m_fMultifyDelta	= fDelta;
	m_bMultify		= bMultify;
}

//-----------------------------------------------------------------------------
// ������CreateModelNode()
// ����������ģ�͵ĳ���ͼ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelRasterImpl<T>::CreateModelNode()
{
    // ����������
    m_piTexture = (m_bTexToCache)? ::VBF_GetTextureFromCache(m_piImage) : ::VBF_CreateTextureFromImage(m_piImage);
    if(!m_piTexture.valid()) return false;

    ref_ptr<osg::IVBF_SGNodeGeometry> piGeode = ::VBF_CreateSGNodeGeometry();
    piGeode->setName("VBFNode_MarkModel: " + this->m_strID);
    piGeode->setDataVariance(osg::CVBF_Object::STATIC);

    // ����Drawable��ԭ��λ�ھ������½ǣ���ƽ���ڵ��棩
    if(m_piTexture.valid()) m_piGeom = ::VBF_CreateTexturedQuad( m_piTexture.get(), false );
    if(!m_piGeom.valid()) return false;

    // ���Drawable
    piGeode->addDrawable(m_piGeom);

    this->m_piNodeModel = piGeode.release();

    UpdateTexOrign();
    UpdateTexAlpha();

    return true;
}

//-----------------------------------------------------------------------------
// ����: SetStateSet()
// ����: ������Ⱦ״̬
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::SetStateSet()
{
	BaseClass::SetStateSet();

	// ������Ⱦ˳��
    if( this->m_piNodeModel.valid() )
	{
        osg::StateSet* ss = this->m_piNodeModel->getOrCreateStateSet();
        ss->setRenderBinDetails(VBF_TRANSPARENT_BINBASE, "DepthSortedBin");
    }
}

//-----------------------------------------------------------------------------
// ������GetBoundingBoxInGeo()
// �����������������ϵ�µİ�Χ��
//-----------------------------------------------------------------------------
template<class T>
const osg::BoundingBoxd& CVBF_MarkModelRasterImpl<T>::GetBoundingBoxInGeo()
{
    if(!this->m_bDirtyBoundingBoxInGeo) return this->m_BoundingBoxInGeo;

    // ע�⣺��Ҫ�жϰ�Χ�����ĵ�ĵ�����������������Ƿ���Ч
    osg::Vec3d ptCenterGeo = this->GetBoundingBoxCenterGeo();
    if(::VBF_IsPosInvalid(ptCenterGeo)) return this->m_BoundingBoxInGeo;

    osg::Vec3d ptCenterWorld = ::VBF_GetPosInvalid();
    this->m_ipContext->GeoToWorld(ptCenterGeo, true, ptCenterWorld);
    if(::VBF_IsPosInvalid(ptCenterWorld)) return this->m_BoundingBoxInGeo;

    // ע�⣺��Ҫ�ж�ģ������ϵ�µİ�Χ���Ƿ���Ч
    const osg::BoundingBox& boxInModel = this->GetBoundingBoxInModel();
    if(!boxInModel.valid()) return this->m_BoundingBoxInGeo;

    osg::Vec3d ptCenterWin;
    this->m_ipContext->GeoToClient(this->m_opCamera.get(), ptCenterGeo, true, ptCenterWin);

    // ���ž���
    float fScaleX, fScaleY, fScaleZ;
    this->GetRealtimeScale(fScaleX, fScaleY, fScaleZ);
    osg::Matrix matScale = osg::Matrix::scale(fScaleX/2, fScaleY/2, fScaleZ/2);

    this->m_BoundingBoxInGeo.init();

    for(int i=0; i<8; i++)
    {
        osg::Vec3d ptCornerWin = boxInModel.corner(i)*matScale + ptCenterWin;
        osg::Vec3d ptCornerGeo;
        this->m_ipContext->ClientToGeo(this->m_opView.get(),ptCornerWin.x(), ptCornerWin.y(), ptCornerGeo );
        this->m_BoundingBoxInGeo.expandBy(ptCornerGeo);
    }

    this->m_bDirtyBoundingBoxInGeo = false;

    return this->m_BoundingBoxInGeo;
}

//-----------------------------------------------------------------------------
// ������SetSizeInMeters()
// ����������ͼ�񾭹����ź��ʵ�ʳߴ磨��λ���ף�����������EnableFixedSizeInPixels(false)�����
// ע�⣺����˴����õĳ���Ȳ�����ԭʼ����ȣ��ᵼ��ͼ�����
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::SetSizeInMeters(float fWidth, float fHeight)
{
    m_fWidthInMeters  = fWidth;
    m_fHeightInMeters = fHeight;

    m_bDirtySizeInMeters = true;
}

//-----------------------------------------------------------------------------
// ������UpdateSizeInMeters()
// ����������ͼ�񾭹����ź��ʵ�ʳߴ磨��λ���ף����óߴ����û����ⲿ����
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::UpdateSizeInMeters()
{
    // ��������EnableFixedSizeInPixels(false)�����
    if(this->m_bEnableFixedSizeInPixels) return;

    if(!m_piTexture.valid()) return;

    int nImgSizeX = m_piTexture->getTextureWidth();
    int nImgSizeY = m_piTexture->getTextureHeight();

    // ���������У�ͼ��߶�Ϊ1
    float fSizeY = 1; // ��λ����
    float fSizeX = (fSizeY * nImgSizeX)/nImgSizeY;

    // ������Ҫ�Ŵ�ı���
    float fScaleX = m_fWidthInMeters/fSizeX;
    float fScaleY = m_fHeightInMeters/fSizeY;

    this->SetScale(fScaleX, fScaleY, 1.0);
}

//-----------------------------------------------------------------------------
// ������UpdateTexAlpha()
// ��������������͸����
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::UpdateTexAlpha()
{
    if(!m_piGeom.valid()) return;

    osg::Vec4Array* pColors = dynamic_cast<osg::Vec4Array*>( m_piGeom->getColorArray() );
    if(pColors!=NULL && pColors->size()==1)
    {
        // ��ɫΪ��ɫ��Ĭ�ϣ�ʱ��ʹ��m_fTexAlpha
        if( m_vColor == osg::Vec4f(1.0,1.0,1.0,1.0) )
        {
            (*pColors)[0].a() = m_fTexAlpha;
        }
        else // ʹ����ɫ
        {
            (*pColors)[0] = m_vColor;
        }


        pColors->dirty();
        m_piGeom->dirtyDisplayList();
    }
}

//-----------------------------------------------------------------------------
// ������UpdateTexOrign()
// ��������������ԭ����λͼ�е����λ�� (��������½ǣ�ֵ��Ϊ[0.0, 1.0])
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::UpdateTexOrign()
{
    if(!m_piGeom.valid()) return;
    if(!m_piTexture.valid()) return;

    int nImgSizeX = m_piTexture->getTextureWidth();
    int nImgSizeY = m_piTexture->getTextureHeight();

    // ȷ��ͼ�񲻱���
    float fSizeY = 1; // ��λ����
    float fSizeX = (fSizeY * nImgSizeX)/nImgSizeY;

    float fL = -m_fTexOrignX * fSizeX;
    float fR = fL + fSizeX;

    float fB = -m_fTexOrignY * fSizeY;
    float fT = fB + fSizeY;

    osg::Vec3Array* pVerts = dynamic_cast<osg::Vec3Array*>( m_piGeom->getVertexArray() );
    if(pVerts!=NULL && pVerts->size()==4)
    {
        (*pVerts)[0] = osg::Vec3(fL, fB, 0);	// ���½�
        (*pVerts)[1] = osg::Vec3(fR, fB, 0);	// ���½�
        (*pVerts)[2] = osg::Vec3(fR, fT, 0);	// ���Ͻ�
        (*pVerts)[3] = osg::Vec3(fL, fT, 0);	// ���Ͻ�

        pVerts->dirty();
        m_piGeom->dirtyBound();
    }
}

//-----------------------------------------------------------------------------
// ������ClipModelByDist()
// �����������ӵ㵽ģ�͵ľ��룬�ж�ģ���Ƿ��ڿɼ�������
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::ClipModelByDist()
{
   BaseClass::ClipModelByDist();

   // �������ߵĸ����ǣ������Ƿ���z-write��������������洹ֱʱ�������Ʋ������
   IVBF_GlobalDataPerView* pData = VBF_Get3DGlobalData(this->m_opView.get());
   double dAngleV = pData->GetAngleV();
   if(dAngleV<0) dAngleV = -dAngleV;

   bool bEnableDepthTest = ( dAngleV < m_fAngleVLimit );

   this->EnableDepthTest(bEnableDepthTest);
   this->EnableDepthWrite(bEnableDepthTest);

}


//-----------------------------------------------------------------------------
// ������Update()
// ���������� (ÿ֡����ǰ����)
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelRasterImpl<T>::Update()
{
    if(m_bAutoEnlarge)
    {
        if(this->m_fScaleX > m_fScaleMax)
        {
            this->m_bAlive = false;
        }

        if(m_bMultify)
        {
            this->m_fScaleX *= m_fMultifyDelta;
            this->m_fScaleY *= m_fMultifyDelta;
            this->m_fScaleZ *= m_fMultifyDelta;
        }
        else
        {
            this->m_fScaleX += m_fMultifyDelta;
            this->m_fScaleY += m_fMultifyDelta;
            this->m_fScaleZ += m_fMultifyDelta;
        }
    }

    // ���û���ĺ���
    if(!BaseClass::Update()) return false;

    // ����ͼ�񾭹����ź��ʵ�ʳߴ磨��λ���ף����óߴ����û����ⲿ����
    if(m_bDirtySizeInMeters)
    {
        UpdateSizeInMeters();
        m_bDirtySizeInMeters = false;
    }

    return true;
}

//-----------------------------------------------------------------------------
// ������WriteModelToXML()
// ������д��ģ�ͱ������Ϣ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelRasterImpl<T>::WriteModelToXML(TiXmlElement* pElemMark)
{
	if( !BaseClass::WriteModelToXML(pElemMark) ) return false;

	::VBF_SetAttribute(pElemMark, "TexOrignX",		m_fTexOrignX);
	::VBF_SetAttribute(pElemMark, "TexOrignY",		m_fTexOrignY);
	::VBF_SetAttribute(pElemMark, "TexAlpha",		m_fTexAlpha);

	// д�룺�Զ������Ч������ը��
	::VBF_SetAttribute(pElemMark, "AutoEnlarge",		m_bAutoEnlarge);
	::VBF_SetAttribute(pElemMark, "ScaleMax",			m_fScaleMax);
	::VBF_SetAttribute(pElemMark, "Multify",			m_bMultify);
	::VBF_SetAttribute(pElemMark, "MultifyDelta",		m_fMultifyDelta);

    // д�룺�û����õ�ͼ���ھ������ź��ʵ�ʳߴ磨��λ���ף�
    ::VBF_SetAttribute(pElemMark, "EnableSizeInMeters",   m_bDirtySizeInMeters);
    ::VBF_SetAttribute(pElemMark, "WidthInMeters",        m_fWidthInMeters);
    ::VBF_SetAttribute(pElemMark, "HeightInMeters",       m_fHeightInMeters);

	// д�룺������Ϣ
	::VBF_SetAttribute(pElemMark, "TexToCache", m_bTexToCache);
	::VBF_WriteToXML(pElemMark, m_piImage);

    return true;
}

//-----------------------------------------------------------------------------
// ������ReadModelFromXML()
// ��������ȡģ�ͱ������Ϣ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelRasterImpl<T>::ReadModelFromXML(TiXmlElement* pElemMark)
{
	if( !BaseClass::ReadModelFromXML(pElemMark) ) return false;

	float fAlpha = GetTexAlpha();
	float  fTexOrignX, fTexOrignY;
	GetTexOrign(fTexOrignX, fTexOrignY);

	::VBF_QueryAttribute(pElemMark, "TexOrignX",	fTexOrignX);
	::VBF_QueryAttribute(pElemMark, "TexOrignY",	fTexOrignY);
	::VBF_QueryAttribute(pElemMark, "TexAlpha",		fAlpha);

	// ��ȡ���Զ������Ч������ը��
	::VBF_QueryAttribute(pElemMark, "AutoEnlarge",	m_bAutoEnlarge);
	::VBF_QueryAttribute(pElemMark, "ScaleMax",		m_fScaleMax);
	::VBF_QueryAttribute(pElemMark, "Multify",		m_bMultify);
	::VBF_QueryAttribute(pElemMark, "MultifyDelta",	m_fMultifyDelta);

    // ��ȡ���û����õ�ͼ���ھ������ź��ʵ�ʳߴ磨��λ���ף�
    ::VBF_QueryAttribute(pElemMark, "EnableSizeInMeters",  m_bDirtySizeInMeters);
    ::VBF_QueryAttribute(pElemMark, "WidthInMeters",       m_fWidthInMeters);
    ::VBF_QueryAttribute(pElemMark, "HeightInMeters",      m_fHeightInMeters);

	// ������ز���
	SetTexOrign(fTexOrignX, fTexOrignY);
	SetTexAlpha(fAlpha);

	if(m_bAutoEnlarge)
	{
		SetAutoEnlarge(m_fScaleMax, m_fMultifyDelta, m_bMultify);
	}

	if(m_bDirtySizeInMeters)
	{
		SetSizeInMeters(m_fWidthInMeters, m_fHeightInMeters);
	}

	// ��ȡ��������Ϣ
	osg::Image* pImage = NULL;
	::VBF_ReadFromXML(pElemMark, pImage);
	if(pImage)
	{
		bool bTexToCache = false;
		::VBF_QueryAttribute(pElemMark, "TexToCache", bTexToCache);

		SetTexImage(pImage, bTexToCache);
	}

	return true;
}

//-----------------------------------------------------------------------------
// ������ExecuteScript()
// ������ִ��json�ű�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
	BaseClass::ExecuteScript(conf);

	float  fTexOrignX, fTexOrignY;
	GetTexOrign(fTexOrignX, fTexOrignY);

	if( conf.getIfSet("TexOrignX", fTexOrignX) && conf.getIfSet("TexOrignY", fTexOrignY) )
	{
		SetTexOrign(fTexOrignX, fTexOrignY);
	}

	float fAlpha = GetTexAlpha();
	if( conf.getIfSet("TexAlpha", fAlpha) )
	{
		SetTexAlpha(fAlpha);
	}

	// ��ȡ���Զ������Ч������ը��
	bool bAutoEnlarge = m_bAutoEnlarge;
	if( conf.getIfSet("AutoEnlarge", bAutoEnlarge) && bAutoEnlarge )
	{
		float fScaleMax		= m_fScaleMax;
		bool  bMultify		= m_bMultify;
		float fMultifyDelta = m_fMultifyDelta;

		conf.getIfSet("ScaleMax",	  fScaleMax);
		conf.getIfSet("Multify",	  bMultify);
		conf.getIfSet("MultifyDelta", fMultifyDelta);

		SetAutoEnlarge(fScaleMax, fMultifyDelta, bMultify);
	}

    // ��ȡ���û����õ�ͼ���ھ������ź��ʵ�ʳߴ磨��λ���ף�
	bool bDirtySizeInMeters = m_bDirtySizeInMeters;
	float fWidthInMeters	= m_fWidthInMeters;
	float fHeightInMeters	= m_fHeightInMeters;

    if( conf.getIfSet("EnableSizeInMeters", bDirtySizeInMeters) && bDirtySizeInMeters )
	{
		conf.getIfSet("WidthInMeters",  fWidthInMeters);
		conf.getIfSet("HeightInMeters", fHeightInMeters);

		SetSizeInMeters(fWidthInMeters, fHeightInMeters);
	}

	// ��ȡ��������Ϣ
	osg::Image* pImage = NULL;
	if( ::VBF_ReadFromJson(conf, pImage) )
	{
		bool bTexToCache = false;
		conf.getIfSet("TexToCache", bTexToCache);

		SetTexImage(pImage, bTexToCache);
	} 
}

#endif 
