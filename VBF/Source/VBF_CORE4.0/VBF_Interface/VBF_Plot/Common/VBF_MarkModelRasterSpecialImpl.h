//*******************************************************************
// FileName��VBF_MarkModelRasterSpecialImpl.h
// Function����������ľ���ʵ��ģ�͵�ģ����
// Author:   ��Ө
// Date:     2015-12-01
//*******************************************************************

#ifndef __VBF_MARK_MODEL_RASTER_SPECIAL_IMPL_H__
#define __VBF_MARK_MODEL_RASTER_SPECIAL_IMPL_H__


#include <VBF_Plot/Common/IVBF_MarkModelRasterSpecial.h>
#include <VBF_Aux/VBF_GLAux/VBF_PrimitiveUtils.h>
#include <VBF_Plot/VBF_MarkModelPointImpl.h>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>
#include <VBF_Aux/VBF_GLAux/VBF_ImageTextureUtils.h>

#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrBlendFunc.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexEnv.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrAlphaFunc.h>
#include <VBF_Engine/VBF_SceneGraph/ImageStream>


template<class T>
class CVBF_MarkModelRasterSpecialImpl : public CVBF_MarkModelImpl<T>
{
private:
	typedef CVBF_MarkModelImpl<T>  BaseClass;

public:
	CVBF_MarkModelRasterSpecialImpl() {}
	CVBF_MarkModelRasterSpecialImpl(const std::string& strMarkID);
	CVBF_MarkModelRasterSpecialImpl(const CVBF_MarkModelRasterSpecialImpl& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
	virtual ~CVBF_MarkModelRasterSpecialImpl();


	// ����/��ȡģ�͵ĳߴ���Ϣ��ע�⣺����˴����õĳ���Ȳ�����ԭʼ����ȣ��ᵼ��ͼ�����
	virtual void SetSize(bool bFixedSizeInPixels, float fWidth, float fHeight);
	virtual void GetSize(bool& bFixedSizeInPixels, float& fWidth, float& fHeight)
	{ bFixedSizeInPixels = m_bEnableFixedSizeInPixels; fWidth = m_fWidth; fHeight = m_fHeight; }


	// ����/��ȡ����ͼ��ָ��
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache);
	virtual osg::Image* GetTexImage() { return m_piImage.get(); }

    // ����/��ȡ�����͸���ȣ�Ĭ��ֵΪ1.0��
    virtual void  SetTexAlpha(float fAlpha);
    virtual float GetTexAlpha() { return m_fTexAlpha; }

	// ����/��ȡ����ԭ����λͼ�е����λ�� (��������½ǣ�ֵ��Ϊ[0.0, 1.0])
	virtual void SetTexOrign(float fTexOrignX, float fTexOrignY);
	virtual void GetTexOrign(float& fTexOrignX, float& fTexOrignY)	{ fTexOrignX = m_fTexOrignX; fTexOrignY = m_fTexOrignY; }

    // ��ȡģ���ڸ�������ϵ�µİ�Χ��
    virtual const osg::BoundingBoxd& GetBoundingBoxInGeo();

    // д��/��ȡģ�ͱ������Ϣ
    virtual bool WriteModelToXML(TiXmlElement* pElemMark);
    virtual bool ReadModelFromXML(TiXmlElement* pElemMark);

    // ���� (ÿ֡����ǰ����)
    virtual bool Update();

protected:

	// ����ģ�͵ĳ���ͼ
	virtual bool CreateModelNode();

	virtual osg::IVBF_SGNode* CreateModelNode_InPixels()=0;
	virtual osg::IVBF_SGNode* CreateModelNode_InMeters()=0;

	// ������Ⱦ״̬
	virtual void SetStateSet();

    // �����ӵ㵽ģ�͵ľ��룬�ж�ģ��/�����Ƿ��ڿɼ�������
    virtual void ClipModelByDist();

    // �����Ժ�����ͨ����ͬ����������һ���ı���
    osg::Geometry* CreateUnitQuad(bool bModelVertical);
    osg::Geometry* CreateQuad(bool bModelVertical, float fWidth, float fHeight);

protected:

	// �ߴ���Ϣ
	bool			m_bEnableFixedSizeInPixels;	// �Ƿ�̶����ش�С
	float			m_fWidth;					// ����ģ�͵Ŀ�ȣ���λ����/���أ�
	float			m_fHeight;					// ����ģ�͵ĸ߶ȣ���λ����/���أ�

	// ������Ϣ
	float           m_fTexAlpha;		// ����͸����
	float			m_fTexOrignX;		// ����ԭ����λͼ�е����λ�� (��������½�)
	float			m_fTexOrignY;

	// ͼ��������
	ref_ptr<osg::Image>         m_piImage;		// ͼ��
	ref_ptr<osg::Texture2D>     m_piTexture;	// ����
	bool						m_bTexToCache;	// �����Ƿ���Ҫ���뻺��

    // ��ֱ�ӽǵ���ֵ��С�ڸ�ֵʱ����Ҫ����z-buffer
    float           m_fAngleVLimit;

    // ����ͼ�ڵ�
    ref_ptr<osg::Geometry>      m_piGeom;      // ģ���ı��ζ�Ӧ��Drawable
};

template<class T>
CVBF_MarkModelRasterSpecialImpl<T>::CVBF_MarkModelRasterSpecialImpl(const std::string& strMarkID)
    : BaseClass(strMarkID)
{
    this->m_nType = VBF_MARK_RASTER;

    // �ߴ���Ϣ
    m_bEnableFixedSizeInPixels  = true;
    m_fWidth					= 35.0f;
    m_fHeight					= 35.0f;

	m_fTexAlpha				= 1.0f;
	m_fTexOrignX            = 0.5;
	m_fTexOrignY			= 0.0;
	m_bTexToCache			= true;

    m_fAngleVLimit          = 0.0f;

	// �Ƿ����ü�
	this->m_bEnableClipByEarth	= false;
}

template<class T>
CVBF_MarkModelRasterSpecialImpl<T>::~CVBF_MarkModelRasterSpecialImpl()
{
    osg::ImageStream* pImageStream = dynamic_cast<osg::ImageStream*>(m_piImage.get());
    if(pImageStream) pImageStream->quit();
}

//-----------------------------------------------------------------------------
// ������SetSize()
// ��������������ͼ���ָ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterSpecialImpl<T>::SetSize(bool bFixedSizeInPixels, float fWidth, float fHeight)
{
    m_bEnableFixedSizeInPixels = bFixedSizeInPixels;
    m_fWidth  = fWidth;
    m_fHeight = fHeight;

    this->DirtyModel();
    this->DirtyStateSet();
}

//-----------------------------------------------------------------------------
// ������SetTexImage()
// ��������������ͼ���ָ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterSpecialImpl<T>::SetTexImage(osg::Image* pImage, bool bTexToCache)
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
void CVBF_MarkModelRasterSpecialImpl<T>::SetTexAlpha(float fAlpha)
{
    if( osg::equivalent(m_fTexAlpha, fAlpha) ) return;

    m_fTexAlpha = osg::clampBetween(fAlpha, 0.0f, 1.0f);

    // ʹģ�͵Ķ�����ɫʧЧ
    this->DirtyModel();
}
 
//-----------------------------------------------------------------------------
// ������SetTexOrign()
// ��������������ԭ����λͼ�е����λ�� (��������½ǣ�ֵ��Ϊ[0.0, 1.0])
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterSpecialImpl<T>::SetTexOrign(float fTexOrignX, float fTexOrignY)
{ 
    if( osg::equivalent(m_fTexOrignX, fTexOrignX) && osg::equivalent(m_fTexOrignY, fTexOrignY) ) return;

	m_fTexOrignX  = osg::clampBetween(fTexOrignX, 0.0f, 1.0f); 
	m_fTexOrignY  = osg::clampBetween(fTexOrignY, 0.0f, 1.0f);

    // ʹģ�͵Ķ�������ʧЧ
    this->DirtyModel();
}


//-----------------------------------------------------------------------------
// ������CreateModelNode()
// ����������ģ�͵ĳ���ͼ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelRasterSpecialImpl<T>::CreateModelNode()
{
    ref_ptr<osg::IVBF_SGNode> piNode;

    if(m_bEnableFixedSizeInPixels)  // �̶����ش�С��ģ�ͳߴ絥λΪ������
    {
        piNode = CreateModelNode_InPixels();
    }
    else  // ���̶����ش�С��ģ�ͳߴ絥λΪ����
    {
        piNode = CreateModelNode_InMeters();
    }

    if(piNode.valid())
    {
        this->m_piNodeModel = piNode.release();
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------
// ����: SetStateSet()
// ����: ������Ⱦ״̬
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterSpecialImpl<T>::SetStateSet()
{
	BaseClass::SetStateSet();

    // ����ģ�ͽڵ����Ⱦ״̬
    if( this->m_piNodeModel.valid() )
	{
        osg::StateSet* ss = this->m_piNodeModel->getOrCreateStateSet();
        ss->setRenderBinDetails(VBF_TRANSPARENT_BINBASE, "DepthSortedBin");

        // ��������
        if(m_piImage.valid())
        {
            ref_ptr<osg::Texture2D> piTexture =  ::VBF_GetTextureFromCache(m_piImage);
            ss->setTextureAttributeAndModes(0, piTexture, osg::StateAttribute::ON );

            ss->setTextureAttribute(0, new osg::TexEnv );
            ss->setAttributeAndModes(new osg::BlendFunc, osg::StateAttribute::ON);

            // ͨ��������������͸����
            osg::Vec4f color(1.0f, 1.0f, 1.0f, m_fTexAlpha);

            ref_ptr<osg::Material> piMaterial = new osg::Material;
            piMaterial->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
            piMaterial->setAmbient(osg::Material::FRONT_AND_BACK, color);
            piMaterial->setDiffuse(osg::Material::FRONT_AND_BACK, color);
            ss->setAttributeAndModes(piMaterial.get(), osg::StateAttribute::ON|osg::StateAttribute::PROTECTED);
        }

        ref_ptr<osg::AlphaFunc> piAlphaFunc = new osg::AlphaFunc;
        piAlphaFunc->setFunction(osg::AlphaFunc::GEQUAL, 0.05f);
        ss->setAttributeAndModes(piAlphaFunc, osg::StateAttribute::ON);

        ss->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
        ss->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    }
}

//-----------------------------------------------------------------------------
// ������GetBoundingBoxInGeo()
// �����������������ϵ�µİ�Χ��
//-----------------------------------------------------------------------------
template<class T>
const osg::BoundingBoxd& CVBF_MarkModelRasterSpecialImpl<T>::GetBoundingBoxInGeo()
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

    // �������� --> ��������
    osg::Vec3d ptCenterWin;
    this->m_ipContext->GeoToClient(this->m_opCamera.get(), ptCenterGeo, true, ptCenterWin);

    // ���ž���
    float fScaleX = m_fWidth;
    float fScaleY = m_fHeight;
    float fScaleZ = 1.0;
    osg::Matrix matScale = osg::Matrix::scale(fScaleX/2, fScaleY/2, fScaleZ/2);

    this->m_BoundingBoxInGeo.init();

    for(int i=0; i<8; i++)
    {
        osg::Vec3d ptCornerWin = boxInModel.corner(i)*matScale + ptCenterWin;
        osg::Vec3d ptCornerGeo;
        this->m_ipContext->ClientToGeo(this->m_opView.get(), ptCornerWin.x(), ptCornerWin.y(), ptCornerGeo );
        this->m_BoundingBoxInGeo.expandBy(ptCornerGeo);
    }

    this->m_bDirtyBoundingBoxInGeo = false;

    return this->m_BoundingBoxInGeo;
}

//-----------------------------------------------------------------------------
// ������ClipModelByDist()
// �����������ӵ㵽ģ�͵ľ��룬�ж�ģ���Ƿ��ڿɼ�������
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterSpecialImpl<T>::ClipModelByDist()
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
bool CVBF_MarkModelRasterSpecialImpl<T>::Update()
{
    // ���û���ĺ���
    if(!BaseClass::Update()) return false;

    return true;
}

//-----------------------------------------------------------------------------
// ������WriteModelToXML()
// ������д��ģ�ͱ������Ϣ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelRasterSpecialImpl<T>::WriteModelToXML(TiXmlElement* pElemMark)
{
	if( !BaseClass::WriteModelToXML(pElemMark) ) return false;

	// д�룺�ߴ���Ϣ
	::VBF_SetAttribute(pElemMark, "EnableFixedSizeInPixels", m_bEnableFixedSizeInPixels);
	::VBF_SetAttribute(pElemMark, "Width",  m_fWidth);
	::VBF_SetAttribute(pElemMark, "Height", m_fHeight);

	// д�룺������Ϣ
	if(m_piImage.valid())
	{
		::VBF_SetAttribute(pElemMark, "TexAlpha",	m_fTexAlpha);
		::VBF_SetAttribute(pElemMark, "TexOrignX",	m_fTexOrignX);
		::VBF_SetAttribute(pElemMark, "TexOrignY",	m_fTexOrignY);
		::VBF_SetAttribute(pElemMark, "TexToCache",	m_bTexToCache);
		::VBF_WriteToXML(pElemMark, m_piImage);
	}

    return true;
}

//-----------------------------------------------------------------------------
// ������ReadModelFromXML()
// ��������ȡģ�ͱ������Ϣ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelRasterSpecialImpl<T>::ReadModelFromXML(TiXmlElement* pElemMark)
{
	if( !BaseClass::ReadModelFromXML(pElemMark) ) return false;

	// ��ȡ���ߴ���Ϣ
	bool bFixedSizeInPixels = false;
	float fWidth, fHeight;
	::VBF_QueryAttribute(pElemMark, "EnableFixedSizeInPixels", bFixedSizeInPixels);	// �Ƿ��������ù̶���С
	::VBF_QueryAttribute(pElemMark, "Width",  fWidth);
	::VBF_QueryAttribute(pElemMark, "Height", fHeight);

	SetSize(bFixedSizeInPixels, fWidth, fHeight);

	// ��ȡ��������Ϣ
	osg::Image* pImage = NULL;
	::VBF_ReadFromXML(pElemMark, pImage);
	if(pImage)
	{
		bool bTexToCache = false;
		::VBF_QueryAttribute(pElemMark, "TexToCache", bTexToCache);

		SetTexImage(pImage, bTexToCache);
	}

	float fAlpha = GetTexAlpha();
	float fTexOrignX, fTexOrignY;
	GetTexOrign(fTexOrignX, fTexOrignY);

	::VBF_QueryAttribute(pElemMark, "TexAlpha",	 fAlpha);
	::VBF_QueryAttribute(pElemMark, "TexOrignX", fTexOrignX);
	::VBF_QueryAttribute(pElemMark, "TexOrignY", fTexOrignY);

	// ������ز���
	SetTexOrign(fTexOrignX, fTexOrignY);
	SetTexAlpha(fAlpha);

	return true;
}

//---------------------------------------------------------------------
// ������VBF_ComputeEllipMatrix()
// ���������㶨λ����ת������ľ���
//---------------------------------------------------------------------
inline bool VBF_ComputeEllipMatrix(CVBF_Map* pMap, const osg::Vec3d& vGeo, osg::Matrixd& matOut)
{
    if(NULL==pMap) return false;

    if(pMap->isGeocentric())
    {
        const osg::EllipsoidModel* pEllipModel = pMap->getProfile()->getSRS()->getEllipsoid();
        pEllipModel->computeLocalToWorldTransformFromLatLongHeight( osg::DegreesToRadians(vGeo.y()),
                                                                    osg::DegreesToRadians(vGeo.x()),
                                                                    vGeo.z(),
                                                                    matOut );
    }
    else
    {
        matOut.makeTranslate(vGeo);
    }

    return true;
}

//---------------------------------------------------------------------
// ������VBF_ComputeMatrix()
// �����������ۺϱ任����
//---------------------------------------------------------------------
inline void VBF_ComputeMatrix(CVBF_Map* pMap, const osg::Vec3d& vGeo, float fWidth, float fHeight,
                              float fRotateZ, osg::Matrixd& matOut)
{
    // ģ������ϵ�µ���ת
    Quat quatRotation;
    quatRotation.makeRotate(osg::DegreesToRadians(fRotateZ), osg::Vec3f(0,0,1));

    // ��λ����ת������
    osg::Matrixd matEllip;
    VBF_ComputeEllipMatrix(pMap, vGeo, matEllip);

    matOut.makeRotate(quatRotation);
    matOut.postMult(matEllip);
    matOut.preMultScale(osg::Vec3(fWidth, fHeight, fHeight));
}

//-----------------------------------------------------------------------------
// ������CreateUnitQuad()
// ����������һ����λ�ı��Σ����߳�Ϊ1��ԭ��λ���ı�������
// ������bModelVertical-- ģ���Ƿ�ֱ�ڵ���
//-----------------------------------------------------------------------------
template<class T>
osg::Geometry* CVBF_MarkModelRasterSpecialImpl<T>::CreateUnitQuad(bool bModelVertical)
{
    // ����������
    osg::Geometry* pGeom = new osg::Geometry;

    int nImgSizeX = 1;
    int nImgSizeY = 1;

    if(m_piImage.valid())
    {
        nImgSizeX = m_piImage->s();
        nImgSizeY = m_piImage->t();
    }

    // ȷ��ͼ�񲻱���
    float fSizeY = 1; // ��λ����
    float fSizeX = (fSizeY * nImgSizeX)/nImgSizeY;

    float fL = -m_fTexOrignX * fSizeX;
    float fR = fL + fSizeX;

    float fB = -m_fTexOrignY * fSizeY;
    float fT = fB + fSizeY;

    // ������������
    osg::Vec3Array* pVerts = new osg::Vec3Array(4);
    if(bModelVertical)
    {
        (*pVerts)[0] = osg::Vec3(fL, 0, fB);	// ���½�
        (*pVerts)[1] = osg::Vec3(fR, 0, fB);	// ���½�
        (*pVerts)[2] = osg::Vec3(fR, 0, fT);	// ���Ͻ�
        (*pVerts)[3] = osg::Vec3(fL, 0, fT);	// ���Ͻ�
    }
    else
    {
        (*pVerts)[0] = osg::Vec3(fL, fB, 0);	// ���½�
        (*pVerts)[1] = osg::Vec3(fR, fB, 0);	// ���½�
        (*pVerts)[2] = osg::Vec3(fR, fT, 0);	// ���Ͻ�
        (*pVerts)[3] = osg::Vec3(fL, fT, 0);	// ���Ͻ�
    }

    // ������ɫ����
    osg::Vec4Array* pColors = new osg::Vec4Array(1);
    (*pColors)[0].set(1, 1, 1, 1);

    // ������������
    if(m_piImage.valid())
    {
        // ͼ���Ƿ����µߵ�
        bool flip = m_piImage.valid()? ::VBF_ImageNeedsFlip(m_piImage) : false;

        osg::Vec2Array* pTexcoords = new osg::Vec2Array(4);
        (*pTexcoords)[0].set(0.0f, (flip)? 1.0f : 0.0f);
        (*pTexcoords)[1].set(1.0f, (flip)? 1.0f : 0.0f);
        (*pTexcoords)[2].set(1.0f, (flip)? 0.0f : 1.0f);
        (*pTexcoords)[3].set(0.0f, (flip)? 0.0f : 1.0f);
        pGeom->setTexCoordArray(0, pTexcoords);
    }

    pGeom->setVertexArray(pVerts );
    pGeom->setColorArray(pColors);
    pGeom->setColorBinding(osg::Geometry::BIND_OVERALL);
    pGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
    pGeom->setUseDisplayList(true);
    pGeom->setUseVertexBufferObjects(false);  // ע�⣺�˴���������VBO������ή�ͻ����ٶ�!

    return pGeom;
}

//-----------------------------------------------------------------------------
// ������CreateQuad()
// ����������һ��ָ����ߵ��ı���
// ������fWidth, fHeight -- �ı��εĿ�Ⱥ͸߶ȣ���λ���ף�
//-----------------------------------------------------------------------------
template<class T>
osg::Geometry* CVBF_MarkModelRasterSpecialImpl<T>::CreateQuad(bool bModelVertical, float fWidth, float fHeight)
{
    osg::Geometry* pGeom = CreateUnitQuad(bModelVertical);
    if(NULL==pGeom) return NULL;

    // �Ե�λ�ı��εĶ����������
    osg::Vec3Array* pVerts = dynamic_cast<osg::Vec3Array*>(pGeom->getVertexArray());
    if(pVerts!=NULL && pVerts->size()==4)
    {
        osg::Matrix matScale;
        matScale.makeScale(fWidth, fHeight, fHeight);

        for(int i=0; i<4; i++)
        {
            (*pVerts)[i] = (*pVerts)[i] * matScale;
        }
        pVerts->dirty();
        pGeom->dirtyBound();
    }

    return pGeom;
}

#endif 
