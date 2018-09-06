//*******************************************************************
// FileName：VBF_MarkModelRasterImpl.h
// Function：军标实体模型的模板子类：使用栅格图像的军标,用于表达指挥所等军标
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

	// 设置/获取纹理图像指针
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache);
	virtual osg::Image* GetTexImage() { return m_piImage.get(); }

    // 设置/获取纹理的透明度（默认值为1.0）
    virtual void  SetTexAlpha(float fAlpha);
    virtual float GetTexAlpha() { return m_fTexAlpha; }
    virtual void  SetTexColor(osg::Vec4f color);

    virtual void SetAutoEnlarge(float fScaleMax, float fDelta, bool bMultify);

	// 设置/获取纹理原点在位图中的相对位置 (相对于左下角，值域为[0.0, 1.0])
	virtual void SetTexOrign(float fTexOrignX, float fTexOrignY);
	virtual void GetTexOrign(float& fTexOrignX, float& fTexOrignY)	{ fTexOrignX = m_fTexOrignX; fTexOrignY = m_fTexOrignY; }

	// 设置/获取图像经过缩放后的实际尺寸（单位：米），仅适用于EnableFixedSizeInPixels(false)的情况
	// 注意：如果此处设置的长宽比不等于原始长宽比，会导致图像变形
	virtual void SetSizeInMeters(float fWidth, float fHeight);
	virtual void GetSizeInMeters(float& fWidth, float& fHeight) { fWidth = m_fWidthInMeters; fHeight = m_fHeightInMeters; }

    // 获取模型在各个坐标系下的包围盒
    virtual const osg::BoundingBoxd& GetBoundingBoxInGeo();

    // 写入/读取模型本身的信息
    virtual bool WriteModelToXML(TiXmlElement* pElemMark);
    virtual bool ReadModelFromXML(TiXmlElement* pElemMark);

	// 执行json脚本
	void ExecuteScript(const CVBF_Config& conf);

    // 更新 (每帧绘制前调用)
    virtual bool Update();

protected:

	// 创建模型的场景图
	virtual bool CreateModelNode();

	// 设置渲染状态
    virtual void SetStateSet();

    virtual void UpdateTexAlpha();
    virtual void UpdateTexOrign();
    virtual void UpdateSizeInMeters();

    // 根据视点到模型的距离，判断模型/属性是否在可见距离内
    virtual void ClipModelByDist();

protected:
	float			m_fTexOrignX;		// 纹理原点在位图中的相对位置 (相对于左下角)
	float			m_fTexOrignY;
	float           m_fTexAlpha;		// 纹理透明度
    osg::Vec4f      m_vColor;// 纹理的颜色

	// 自动增大的效果（爆炸）
	bool			m_bAutoEnlarge;
	bool			m_bMultify;
	float			m_fScaleMax;
	float			m_fMultifyDelta;

	// 图像与纹理
	ref_ptr<osg::Image>         m_piImage;		// 图像
	ref_ptr<osg::Texture2D>     m_piTexture;	// 纹理
	bool						m_bTexToCache;	// 纹理是否需要放入缓存

    // 用户设置的图像在经过缩放后的实际尺寸（单位：米）
    bool            m_bDirtySizeInMeters;
    float           m_fWidthInMeters;
    float           m_fHeightInMeters;

    // 垂直视角的阈值，小于该值时才需要开启z-buffer
    float           m_fAngleVLimit;

    // 场景图节点
    ref_ptr<osg::Geometry>      m_piGeom;      // 模型四边形对应的Drawable
};

template<class T>
CVBF_MarkModelRasterImpl<T>::CVBF_MarkModelRasterImpl(const std::string& strMarkID)
    : BaseClass(strMarkID)
{
    this->m_nType       = VBF_MARK_RASTER;
    this->m_nViewMode   = VBF_VIEW_MODE_BILLBOARD_HV;   // 观察模式

    this->m_bEnableFixedSizeInPixels = true;
    this->m_fFixedSizeInPixels       = 16;

	m_fTexOrignX            = 0.5;
	m_fTexOrignY			= 0.0;
	m_fTexAlpha				= 1.0f;
    m_vColor                = osg::Vec4f(1.0,1.0,1.0,1.0);
	m_bTexToCache			= true;

    // 用户设置的图像在经过缩放后的实际尺寸（单位：米）
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
// 函数：SetTexImage()
// 描述：设置纹理图像的指针
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::SetTexImage(osg::Image* pImage, bool bTexToCache)
{
	m_piImage     = pImage;
	m_bTexToCache = bTexToCache;

	// 使模型节点和渲染状态失效
	this->DirtyModel();
	this->DirtyStateSet();
}

//-----------------------------------------------------------------------------
// 函数：SetTexAlpha()
// 描述：设置模型纹理的透明度
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::SetTexAlpha(float fAlpha)
{
    if( osg::equivalent(m_fTexAlpha, fAlpha) ) return;

    m_fTexAlpha = osg::clampBetween(fAlpha, 0.0f, 1.0f);

    // 使模型的顶点颜色失效
    this->DirtyModel();
}
// 函数：SetTexColor()
// 描述：设置模型纹理的颜色
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::SetTexColor(osg::Vec4f color)
{
    m_vColor = color;

    // 使模型的顶点颜色失效
    this->DirtyModel();
}

//-----------------------------------------------------------------------------
// 函数：SetTexOrign()
// 描述：设置纹理原点在位图中的相对位置 (相对于左下角，值域为[0.0, 1.0])
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::SetTexOrign(float fTexOrignX, float fTexOrignY)	
{ 
    if( osg::equivalent(m_fTexOrignX, fTexOrignX) && osg::equivalent(m_fTexOrignY, fTexOrignY) ) return;

	m_fTexOrignX  = osg::clampBetween(fTexOrignX, 0.0f, 1.0f); 
	m_fTexOrignY  = osg::clampBetween(fTexOrignY, 0.0f, 1.0f);

    // 使模型的顶点坐标失效
    this->DirtyModel();
}
 
//-----------------------------------------------------------------------------
// 函数：SetAutoEnlarge()
// 描述：设置自动增大系数
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
// 函数：CreateModelNode()
// 描述：创建模型的场景图
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelRasterImpl<T>::CreateModelNode()
{
    // 纹理必须存在
    m_piTexture = (m_bTexToCache)? ::VBF_GetTextureFromCache(m_piImage) : ::VBF_CreateTextureFromImage(m_piImage);
    if(!m_piTexture.valid()) return false;

    ref_ptr<osg::IVBF_SGNodeGeometry> piGeode = ::VBF_CreateSGNodeGeometry();
    piGeode->setName("VBFNode_MarkModel: " + this->m_strID);
    piGeode->setDataVariance(osg::CVBF_Object::STATIC);

    // 创建Drawable（原点位于矩形左下角，且平行于地面）
    if(m_piTexture.valid()) m_piGeom = ::VBF_CreateTexturedQuad( m_piTexture.get(), false );
    if(!m_piGeom.valid()) return false;

    // 添加Drawable
    piGeode->addDrawable(m_piGeom);

    this->m_piNodeModel = piGeode.release();

    UpdateTexOrign();
    UpdateTexAlpha();

    return true;
}

//-----------------------------------------------------------------------------
// 函数: SetStateSet()
// 描述: 设置渲染状态
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::SetStateSet()
{
	BaseClass::SetStateSet();

	// 设置渲染顺序
    if( this->m_piNodeModel.valid() )
	{
        osg::StateSet* ss = this->m_piNodeModel->getOrCreateStateSet();
        ss->setRenderBinDetails(VBF_TRANSPARENT_BINBASE, "DepthSortedBin");
    }
}

//-----------------------------------------------------------------------------
// 函数：GetBoundingBoxInGeo()
// 描述：计算地理坐标系下的包围盒
//-----------------------------------------------------------------------------
template<class T>
const osg::BoundingBoxd& CVBF_MarkModelRasterImpl<T>::GetBoundingBoxInGeo()
{
    if(!this->m_bDirtyBoundingBoxInGeo) return this->m_BoundingBoxInGeo;

    // 注意：需要判断包围盒中心点的地理坐标和世界坐标是否有效
    osg::Vec3d ptCenterGeo = this->GetBoundingBoxCenterGeo();
    if(::VBF_IsPosInvalid(ptCenterGeo)) return this->m_BoundingBoxInGeo;

    osg::Vec3d ptCenterWorld = ::VBF_GetPosInvalid();
    this->m_ipContext->GeoToWorld(ptCenterGeo, true, ptCenterWorld);
    if(::VBF_IsPosInvalid(ptCenterWorld)) return this->m_BoundingBoxInGeo;

    // 注意：需要判断模型坐标系下的包围盒是否有效
    const osg::BoundingBox& boxInModel = this->GetBoundingBoxInModel();
    if(!boxInModel.valid()) return this->m_BoundingBoxInGeo;

    osg::Vec3d ptCenterWin;
    this->m_ipContext->GeoToClient(this->m_opCamera.get(), ptCenterGeo, true, ptCenterWin);

    // 缩放矩阵
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
// 函数：SetSizeInMeters()
// 描述：设置图像经过缩放后的实际尺寸（单位：米），仅适用于EnableFixedSizeInPixels(false)的情况
// 注意：如果此处设置的长宽比不等于原始长宽比，会导致图像变形
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::SetSizeInMeters(float fWidth, float fHeight)
{
    m_fWidthInMeters  = fWidth;
    m_fHeightInMeters = fHeight;

    m_bDirtySizeInMeters = true;
}

//-----------------------------------------------------------------------------
// 函数：UpdateSizeInMeters()
// 描述：更新图像经过缩放后的实际尺寸（单位：米），该尺寸由用户在外部设置
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::UpdateSizeInMeters()
{
    // 仅适用于EnableFixedSizeInPixels(false)的情况
    if(this->m_bEnableFixedSizeInPixels) return;

    if(!m_piTexture.valid()) return;

    int nImgSizeX = m_piTexture->getTextureWidth();
    int nImgSizeY = m_piTexture->getTextureHeight();

    // 顶点坐标中，图像高度为1
    float fSizeY = 1; // 单位：米
    float fSizeX = (fSizeY * nImgSizeX)/nImgSizeY;

    // 计算需要放大的倍率
    float fScaleX = m_fWidthInMeters/fSizeX;
    float fScaleY = m_fHeightInMeters/fSizeY;

    this->SetScale(fScaleX, fScaleY, 1.0);
}

//-----------------------------------------------------------------------------
// 函数：UpdateTexAlpha()
// 描述：更新纹理透明度
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::UpdateTexAlpha()
{
    if(!m_piGeom.valid()) return;

    osg::Vec4Array* pColors = dynamic_cast<osg::Vec4Array*>( m_piGeom->getColorArray() );
    if(pColors!=NULL && pColors->size()==1)
    {
        // 颜色为白色（默认）时，使用m_fTexAlpha
        if( m_vColor == osg::Vec4f(1.0,1.0,1.0,1.0) )
        {
            (*pColors)[0].a() = m_fTexAlpha;
        }
        else // 使用颜色
        {
            (*pColors)[0] = m_vColor;
        }


        pColors->dirty();
        m_piGeom->dirtyDisplayList();
    }
}

//-----------------------------------------------------------------------------
// 函数：UpdateTexOrign()
// 描述：更新纹理原点在位图中的相对位置 (相对于左下角，值域为[0.0, 1.0])
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::UpdateTexOrign()
{
    if(!m_piGeom.valid()) return;
    if(!m_piTexture.valid()) return;

    int nImgSizeX = m_piTexture->getTextureWidth();
    int nImgSizeY = m_piTexture->getTextureHeight();

    // 确保图像不变形
    float fSizeY = 1; // 单位：米
    float fSizeX = (fSizeY * nImgSizeX)/nImgSizeY;

    float fL = -m_fTexOrignX * fSizeX;
    float fR = fL + fSizeX;

    float fB = -m_fTexOrignY * fSizeY;
    float fT = fB + fSizeY;

    osg::Vec3Array* pVerts = dynamic_cast<osg::Vec3Array*>( m_piGeom->getVertexArray() );
    if(pVerts!=NULL && pVerts->size()==4)
    {
        (*pVerts)[0] = osg::Vec3(fL, fB, 0);	// 左下角
        (*pVerts)[1] = osg::Vec3(fR, fB, 0);	// 右下角
        (*pVerts)[2] = osg::Vec3(fR, fT, 0);	// 右上角
        (*pVerts)[3] = osg::Vec3(fL, fT, 0);	// 左上角

        pVerts->dirty();
        m_piGeom->dirtyBound();
    }
}

//-----------------------------------------------------------------------------
// 函数：ClipModelByDist()
// 描述：根据视点到模型的距离，判断模型是否在可见距离内
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterImpl<T>::ClipModelByDist()
{
   BaseClass::ClipModelByDist();

   // 根据视线的俯仰角，决定是否开启z-write，避免视线与地面垂直时，布告牌部分钻地
   IVBF_GlobalDataPerView* pData = VBF_Get3DGlobalData(this->m_opView.get());
   double dAngleV = pData->GetAngleV();
   if(dAngleV<0) dAngleV = -dAngleV;

   bool bEnableDepthTest = ( dAngleV < m_fAngleVLimit );

   this->EnableDepthTest(bEnableDepthTest);
   this->EnableDepthWrite(bEnableDepthTest);

}


//-----------------------------------------------------------------------------
// 函数：Update()
// 描述：更新 (每帧绘制前调用)
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

    // 调用基类的函数
    if(!BaseClass::Update()) return false;

    // 更新图像经过缩放后的实际尺寸（单位：米），该尺寸由用户在外部设置
    if(m_bDirtySizeInMeters)
    {
        UpdateSizeInMeters();
        m_bDirtySizeInMeters = false;
    }

    return true;
}

//-----------------------------------------------------------------------------
// 函数：WriteModelToXML()
// 描述：写入模型本身的信息
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelRasterImpl<T>::WriteModelToXML(TiXmlElement* pElemMark)
{
	if( !BaseClass::WriteModelToXML(pElemMark) ) return false;

	::VBF_SetAttribute(pElemMark, "TexOrignX",		m_fTexOrignX);
	::VBF_SetAttribute(pElemMark, "TexOrignY",		m_fTexOrignY);
	::VBF_SetAttribute(pElemMark, "TexAlpha",		m_fTexAlpha);

	// 写入：自动增大的效果（爆炸）
	::VBF_SetAttribute(pElemMark, "AutoEnlarge",		m_bAutoEnlarge);
	::VBF_SetAttribute(pElemMark, "ScaleMax",			m_fScaleMax);
	::VBF_SetAttribute(pElemMark, "Multify",			m_bMultify);
	::VBF_SetAttribute(pElemMark, "MultifyDelta",		m_fMultifyDelta);

    // 写入：用户设置的图像在经过缩放后的实际尺寸（单位：米）
    ::VBF_SetAttribute(pElemMark, "EnableSizeInMeters",   m_bDirtySizeInMeters);
    ::VBF_SetAttribute(pElemMark, "WidthInMeters",        m_fWidthInMeters);
    ::VBF_SetAttribute(pElemMark, "HeightInMeters",       m_fHeightInMeters);

	// 写入：纹理信息
	::VBF_SetAttribute(pElemMark, "TexToCache", m_bTexToCache);
	::VBF_WriteToXML(pElemMark, m_piImage);

    return true;
}

//-----------------------------------------------------------------------------
// 函数：ReadModelFromXML()
// 描述：读取模型本身的信息
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

	// 读取：自动增大的效果（爆炸）
	::VBF_QueryAttribute(pElemMark, "AutoEnlarge",	m_bAutoEnlarge);
	::VBF_QueryAttribute(pElemMark, "ScaleMax",		m_fScaleMax);
	::VBF_QueryAttribute(pElemMark, "Multify",		m_bMultify);
	::VBF_QueryAttribute(pElemMark, "MultifyDelta",	m_fMultifyDelta);

    // 读取：用户设置的图像在经过缩放后的实际尺寸（单位：米）
    ::VBF_QueryAttribute(pElemMark, "EnableSizeInMeters",  m_bDirtySizeInMeters);
    ::VBF_QueryAttribute(pElemMark, "WidthInMeters",       m_fWidthInMeters);
    ::VBF_QueryAttribute(pElemMark, "HeightInMeters",      m_fHeightInMeters);

	// 更新相关参数
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

	// 读取：纹理信息
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
// 函数：ExecuteScript()
// 描述：执行json脚本
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

	// 读取：自动增大的效果（爆炸）
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

    // 读取：用户设置的图像在经过缩放后的实际尺寸（单位：米）
	bool bDirtySizeInMeters = m_bDirtySizeInMeters;
	float fWidthInMeters	= m_fWidthInMeters;
	float fHeightInMeters	= m_fHeightInMeters;

    if( conf.getIfSet("EnableSizeInMeters", bDirtySizeInMeters) && bDirtySizeInMeters )
	{
		conf.getIfSet("WidthInMeters",  fWidthInMeters);
		conf.getIfSet("HeightInMeters", fHeightInMeters);

		SetSizeInMeters(fWidthInMeters, fHeightInMeters);
	}

	// 读取：纹理信息
	osg::Image* pImage = NULL;
	if( ::VBF_ReadFromJson(conf, pImage) )
	{
		bool bTexToCache = false;
		conf.getIfSet("TexToCache", bTexToCache);

		SetTexImage(pImage, bTexToCache);
	} 
}

#endif 
