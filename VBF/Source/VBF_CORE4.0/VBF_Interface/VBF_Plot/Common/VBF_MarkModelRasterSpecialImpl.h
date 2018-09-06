//*******************************************************************
// FileName：VBF_MarkModelRasterSpecialImpl.h
// Function：几类特殊的军标实体模型的模板类
// Author:   杜莹
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


	// 设置/获取模型的尺寸信息，注意：如果此处设置的长宽比不等于原始长宽比，会导致图像变形
	virtual void SetSize(bool bFixedSizeInPixels, float fWidth, float fHeight);
	virtual void GetSize(bool& bFixedSizeInPixels, float& fWidth, float& fHeight)
	{ bFixedSizeInPixels = m_bEnableFixedSizeInPixels; fWidth = m_fWidth; fHeight = m_fHeight; }


	// 设置/获取纹理图像指针
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache);
	virtual osg::Image* GetTexImage() { return m_piImage.get(); }

    // 设置/获取纹理的透明度（默认值为1.0）
    virtual void  SetTexAlpha(float fAlpha);
    virtual float GetTexAlpha() { return m_fTexAlpha; }

	// 设置/获取纹理原点在位图中的相对位置 (相对于左下角，值域为[0.0, 1.0])
	virtual void SetTexOrign(float fTexOrignX, float fTexOrignY);
	virtual void GetTexOrign(float& fTexOrignX, float& fTexOrignY)	{ fTexOrignX = m_fTexOrignX; fTexOrignY = m_fTexOrignY; }

    // 获取模型在各个坐标系下的包围盒
    virtual const osg::BoundingBoxd& GetBoundingBoxInGeo();

    // 写入/读取模型本身的信息
    virtual bool WriteModelToXML(TiXmlElement* pElemMark);
    virtual bool ReadModelFromXML(TiXmlElement* pElemMark);

    // 更新 (每帧绘制前调用)
    virtual bool Update();

protected:

	// 创建模型的场景图
	virtual bool CreateModelNode();

	virtual osg::IVBF_SGNode* CreateModelNode_InPixels()=0;
	virtual osg::IVBF_SGNode* CreateModelNode_InMeters()=0;

	// 设置渲染状态
	virtual void SetStateSet();

    // 根据视点到模型的距离，判断模型/属性是否在可见距离内
    virtual void ClipModelByDist();

    // 工具性函数：通过不同参数，创建一个四边形
    osg::Geometry* CreateUnitQuad(bool bModelVertical);
    osg::Geometry* CreateQuad(bool bModelVertical, float fWidth, float fHeight);

protected:

	// 尺寸信息
	bool			m_bEnableFixedSizeInPixels;	// 是否固定像素大小
	float			m_fWidth;					// 单个模型的宽度（单位：米/像素）
	float			m_fHeight;					// 单个模型的高度（单位：米/像素）

	// 纹理信息
	float           m_fTexAlpha;		// 纹理透明度
	float			m_fTexOrignX;		// 纹理原点在位图中的相对位置 (相对于左下角)
	float			m_fTexOrignY;

	// 图像与纹理
	ref_ptr<osg::Image>         m_piImage;		// 图像
	ref_ptr<osg::Texture2D>     m_piTexture;	// 纹理
	bool						m_bTexToCache;	// 纹理是否需要放入缓存

    // 垂直视角的阈值，小于该值时才需要开启z-buffer
    float           m_fAngleVLimit;

    // 场景图节点
    ref_ptr<osg::Geometry>      m_piGeom;      // 模型四边形对应的Drawable
};

template<class T>
CVBF_MarkModelRasterSpecialImpl<T>::CVBF_MarkModelRasterSpecialImpl(const std::string& strMarkID)
    : BaseClass(strMarkID)
{
    this->m_nType = VBF_MARK_RASTER;

    // 尺寸信息
    m_bEnableFixedSizeInPixels  = true;
    m_fWidth					= 35.0f;
    m_fHeight					= 35.0f;

	m_fTexAlpha				= 1.0f;
	m_fTexOrignX            = 0.5;
	m_fTexOrignY			= 0.0;
	m_bTexToCache			= true;

    m_fAngleVLimit          = 0.0f;

	// 是否开启裁剪
	this->m_bEnableClipByEarth	= false;
}

template<class T>
CVBF_MarkModelRasterSpecialImpl<T>::~CVBF_MarkModelRasterSpecialImpl()
{
    osg::ImageStream* pImageStream = dynamic_cast<osg::ImageStream*>(m_piImage.get());
    if(pImageStream) pImageStream->quit();
}

//-----------------------------------------------------------------------------
// 函数：SetSize()
// 描述：设置纹理图像的指针
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
// 函数：SetTexImage()
// 描述：设置纹理图像的指针
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterSpecialImpl<T>::SetTexImage(osg::Image* pImage, bool bTexToCache)
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
void CVBF_MarkModelRasterSpecialImpl<T>::SetTexAlpha(float fAlpha)
{
    if( osg::equivalent(m_fTexAlpha, fAlpha) ) return;

    m_fTexAlpha = osg::clampBetween(fAlpha, 0.0f, 1.0f);

    // 使模型的顶点颜色失效
    this->DirtyModel();
}
 
//-----------------------------------------------------------------------------
// 函数：SetTexOrign()
// 描述：设置纹理原点在位图中的相对位置 (相对于左下角，值域为[0.0, 1.0])
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterSpecialImpl<T>::SetTexOrign(float fTexOrignX, float fTexOrignY)
{ 
    if( osg::equivalent(m_fTexOrignX, fTexOrignX) && osg::equivalent(m_fTexOrignY, fTexOrignY) ) return;

	m_fTexOrignX  = osg::clampBetween(fTexOrignX, 0.0f, 1.0f); 
	m_fTexOrignY  = osg::clampBetween(fTexOrignY, 0.0f, 1.0f);

    // 使模型的顶点坐标失效
    this->DirtyModel();
}


//-----------------------------------------------------------------------------
// 函数：CreateModelNode()
// 描述：创建模型的场景图
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelRasterSpecialImpl<T>::CreateModelNode()
{
    ref_ptr<osg::IVBF_SGNode> piNode;

    if(m_bEnableFixedSizeInPixels)  // 固定像素大小，模型尺寸单位为：像素
    {
        piNode = CreateModelNode_InPixels();
    }
    else  // 不固定像素大小，模型尺寸单位为：米
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
// 函数: SetStateSet()
// 描述: 设置渲染状态
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterSpecialImpl<T>::SetStateSet()
{
	BaseClass::SetStateSet();

    // 设置模型节点的渲染状态
    if( this->m_piNodeModel.valid() )
	{
        osg::StateSet* ss = this->m_piNodeModel->getOrCreateStateSet();
        ss->setRenderBinDetails(VBF_TRANSPARENT_BINBASE, "DepthSortedBin");

        // 启用纹理
        if(m_piImage.valid())
        {
            ref_ptr<osg::Texture2D> piTexture =  ::VBF_GetTextureFromCache(m_piImage);
            ss->setTextureAttributeAndModes(0, piTexture, osg::StateAttribute::ON );

            ss->setTextureAttribute(0, new osg::TexEnv );
            ss->setAttributeAndModes(new osg::BlendFunc, osg::StateAttribute::ON);

            // 通过材质体现纹理透明度
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
// 函数：GetBoundingBoxInGeo()
// 描述：计算地理坐标系下的包围盒
//-----------------------------------------------------------------------------
template<class T>
const osg::BoundingBoxd& CVBF_MarkModelRasterSpecialImpl<T>::GetBoundingBoxInGeo()
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

    // 世界坐标 --> 地理坐标
    osg::Vec3d ptCenterWin;
    this->m_ipContext->GeoToClient(this->m_opCamera.get(), ptCenterGeo, true, ptCenterWin);

    // 缩放矩阵
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
// 函数：ClipModelByDist()
// 描述：根据视点到模型的距离，判断模型是否在可见距离内
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelRasterSpecialImpl<T>::ClipModelByDist()
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
bool CVBF_MarkModelRasterSpecialImpl<T>::Update()
{
    // 调用基类的函数
    if(!BaseClass::Update()) return false;

    return true;
}

//-----------------------------------------------------------------------------
// 函数：WriteModelToXML()
// 描述：写入模型本身的信息
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelRasterSpecialImpl<T>::WriteModelToXML(TiXmlElement* pElemMark)
{
	if( !BaseClass::WriteModelToXML(pElemMark) ) return false;

	// 写入：尺寸信息
	::VBF_SetAttribute(pElemMark, "EnableFixedSizeInPixels", m_bEnableFixedSizeInPixels);
	::VBF_SetAttribute(pElemMark, "Width",  m_fWidth);
	::VBF_SetAttribute(pElemMark, "Height", m_fHeight);

	// 写入：纹理信息
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
// 函数：ReadModelFromXML()
// 描述：读取模型本身的信息
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelRasterSpecialImpl<T>::ReadModelFromXML(TiXmlElement* pElemMark)
{
	if( !BaseClass::ReadModelFromXML(pElemMark) ) return false;

	// 读取：尺寸信息
	bool bFixedSizeInPixels = false;
	float fWidth, fHeight;
	::VBF_QueryAttribute(pElemMark, "EnableFixedSizeInPixels", bFixedSizeInPixels);	// 是否允许设置固定大小
	::VBF_QueryAttribute(pElemMark, "Width",  fWidth);
	::VBF_QueryAttribute(pElemMark, "Height", fHeight);

	SetSize(bFixedSizeInPixels, fWidth, fHeight);

	// 读取：纹理信息
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

	// 更新相关参数
	SetTexOrign(fTexOrignX, fTexOrignY);
	SetTexAlpha(fAlpha);

	return true;
}

//---------------------------------------------------------------------
// 函数：VBF_ComputeEllipMatrix()
// 描述：计算定位并旋转到椭球的矩阵
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
// 函数：VBF_ComputeMatrix()
// 描述：计算综合变换矩阵
//---------------------------------------------------------------------
inline void VBF_ComputeMatrix(CVBF_Map* pMap, const osg::Vec3d& vGeo, float fWidth, float fHeight,
                              float fRotateZ, osg::Matrixd& matOut)
{
    // 模型坐标系下的旋转
    Quat quatRotation;
    quatRotation.makeRotate(osg::DegreesToRadians(fRotateZ), osg::Vec3f(0,0,1));

    // 定位并旋转到椭球
    osg::Matrixd matEllip;
    VBF_ComputeEllipMatrix(pMap, vGeo, matEllip);

    matOut.makeRotate(quatRotation);
    matOut.postMult(matEllip);
    matOut.preMultScale(osg::Vec3(fWidth, fHeight, fHeight));
}

//-----------------------------------------------------------------------------
// 函数：CreateUnitQuad()
// 描述：创建一个单位四边形，即边长为1，原点位于四边形中心
// 参数：bModelVertical-- 模型是否垂直于地面
//-----------------------------------------------------------------------------
template<class T>
osg::Geometry* CVBF_MarkModelRasterSpecialImpl<T>::CreateUnitQuad(bool bModelVertical)
{
    // 创建几何体
    osg::Geometry* pGeom = new osg::Geometry;

    int nImgSizeX = 1;
    int nImgSizeY = 1;

    if(m_piImage.valid())
    {
        nImgSizeX = m_piImage->s();
        nImgSizeY = m_piImage->t();
    }

    // 确保图像不变形
    float fSizeY = 1; // 单位：米
    float fSizeX = (fSizeY * nImgSizeX)/nImgSizeY;

    float fL = -m_fTexOrignX * fSizeX;
    float fR = fL + fSizeX;

    float fB = -m_fTexOrignY * fSizeY;
    float fT = fB + fSizeY;

    // 创建顶点数组
    osg::Vec3Array* pVerts = new osg::Vec3Array(4);
    if(bModelVertical)
    {
        (*pVerts)[0] = osg::Vec3(fL, 0, fB);	// 左下角
        (*pVerts)[1] = osg::Vec3(fR, 0, fB);	// 右下角
        (*pVerts)[2] = osg::Vec3(fR, 0, fT);	// 右上角
        (*pVerts)[3] = osg::Vec3(fL, 0, fT);	// 左上角
    }
    else
    {
        (*pVerts)[0] = osg::Vec3(fL, fB, 0);	// 左下角
        (*pVerts)[1] = osg::Vec3(fR, fB, 0);	// 右下角
        (*pVerts)[2] = osg::Vec3(fR, fT, 0);	// 右上角
        (*pVerts)[3] = osg::Vec3(fL, fT, 0);	// 左上角
    }

    // 创建颜色数组
    osg::Vec4Array* pColors = new osg::Vec4Array(1);
    (*pColors)[0].set(1, 1, 1, 1);

    // 创建纹理数组
    if(m_piImage.valid())
    {
        // 图像是否上下颠倒
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
    pGeom->setUseVertexBufferObjects(false);  // 注意：此处不能启用VBO，否则会降低绘制速度!

    return pGeom;
}

//-----------------------------------------------------------------------------
// 函数：CreateQuad()
// 描述：创建一个指定宽高的四边形
// 参数：fWidth, fHeight -- 四边形的宽度和高度（单位：米）
//-----------------------------------------------------------------------------
template<class T>
osg::Geometry* CVBF_MarkModelRasterSpecialImpl<T>::CreateQuad(bool bModelVertical, float fWidth, float fHeight)
{
    osg::Geometry* pGeom = CreateUnitQuad(bModelVertical);
    if(NULL==pGeom) return NULL;

    // 对单位四边形的顶点进行缩放
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
