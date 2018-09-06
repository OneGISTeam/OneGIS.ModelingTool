//***************************************************************************************
// FileName：VBF_PrimitiveUtils.h
// Function：几何体中的图元工具函数
// Author:   杜莹
// Date:     2013-09-22
//***************************************************************************************

#ifndef __VBF_PRIMITIVE_UTILS_H__
#define __VBF_PRIMITIVE_UTILS_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_OS.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>
#include <Types/VBF_Optional.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>


//---------------------------------------------------------------
// 定义结构体：VBF_PRIMITIVESET_DATA
// 结构体描述：几何体中的图元集参数
//---------------------------------------------------------------
typedef struct _tagVBFPrimitiveSetData
{
	ref_ptr<osg::UIntArray>		pIndices;		// 顶点索引（可以为NULL）
	unsigned int				nMode;			// 图元绘制方式
    CVBF_Optional<int>          nVertexFirst;   // 不使用顶点索引时，参与该图元的顶点起始索引号，默认值为0
    CVBF_Optional<int>          nVertexCount;   // 不使用顶点索引时，参与该图元的顶点个数，默认值为pVerts->size()

	_tagVBFPrimitiveSetData(osg::UIntArray* indices, unsigned int mode)
		: pIndices(indices), nMode(mode)
	{
	}

} VBF_PRIMITIVESET_DATA;


//---------------------------------------------------------------
// 定义结构体：VBF_GEOMETRY_PARAM
// 结构体描述：几何体中的各个参数
//---------------------------------------------------------------
typedef struct _tagVBFGeometryParam
{
	// 顶点数据
	osg::Geometry::ArrayData		VertexData;				// 顶点坐标
    osg::Geometry::ArrayData		NormalData;				// 顶点法线
    osg::Geometry::ArrayData		ColorData;				// 顶点主颜色
    osg::Geometry::ArrayData		SecondaryColorData;		// 顶点辅颜色
    osg::Geometry::ArrayData		FogCoordData;			// 顶点雾化坐标

    osg::Geometry::ArrayDataList    TexCoordList;			// n组顶点纹理坐标
    osg::Geometry::ArrayDataList	VertexAttribList;		// n组顶点属性
	
	// 顶点索引
	std::vector<VBF_PRIMITIVESET_DATA>	PrimSetList;		// n组图元集

	// 渲染状态
	bool					bUseDispList;	// 是否使用显示列表
	bool					bUseVBO;		// 是否使用VBO（如果为true，不再使用显示列表）
	CVBF_Optional<bool>		bCullBack;		// 是否裁剪掉背面
	CVBF_Optional<bool>		bFrontCCW;		// 正面顶点的排列顺序是否为逆时针

	_tagVBFGeometryParam()
	{
		bUseDispList = false;
		bUseVBO		 = true;

		VertexData.binding	= osg::Geometry::BIND_PER_VERTEX;
	}

	// 设置顶点坐标
	void SetVertexArray(osg::Array* pArray, osg::Geometry::AttributeBinding nBinding=osg::Geometry::BIND_PER_VERTEX) 
	{  
		VertexData.array   = pArray;
		VertexData.binding = nBinding;
	}

	// 设置顶点法线
	void SetNormalArray(osg::Array* pArray, osg::Geometry::AttributeBinding nBinding=osg::Geometry::BIND_PER_VERTEX) 
	{  
		NormalData.array   = pArray;
		NormalData.binding = nBinding;
	}

	// 设置顶点主颜色
	void SetColorArray(osg::Array* pArray, osg::Geometry::AttributeBinding nBinding=osg::Geometry::BIND_PER_VERTEX) 
	{  
		ColorData.array   = pArray;
		ColorData.binding = nBinding;
	}

	// 设置顶点辅颜色
	void SetSecondaryColorArray(osg::Array* pArray, osg::Geometry::AttributeBinding nBinding=osg::Geometry::BIND_PER_VERTEX) 
	{  
		SecondaryColorData.array   = pArray;
		SecondaryColorData.binding = nBinding;
	}

	// 设置顶点雾化坐标
	void SetFogCoordArray(osg::Array* pArray, osg::Geometry::AttributeBinding nBinding=osg::Geometry::BIND_PER_VERTEX) 
	{  
		FogCoordData.array   = pArray;
		FogCoordData.binding = nBinding;
	}

	// 添加一组纹理坐标
	void AddTexCoord(osg::Array* pArray, osg::Geometry::AttributeBinding nBinding=osg::Geometry::BIND_PER_VERTEX)
	{
		TexCoordList.push_back( osg::Geometry::ArrayData(pArray, nBinding) );
	}

	// 添加一组顶点属性
	void AddVertexAttrib(osg::Array* pArray, osg::Geometry::AttributeBinding nBinding=osg::Geometry::BIND_PER_VERTEX)
	{
		VertexAttribList.push_back( osg::Geometry::ArrayData(pArray, nBinding) );
	}

	// 添加一组图元集
	void AddPrimitiveSet(osg::UIntArray* pIndices, unsigned int nMode)
	{
		PrimSetList.push_back( VBF_PRIMITIVESET_DATA(pIndices, nMode) );
	}

} VBF_GEOMETRY_PARAM;


// 利用传入的参数param，更新几何体
// 参数：bRecomputeNormal -- 是否需要在该函数中重新计算法线
VBF_GLAUX_EXPORT bool VBF_UpdateGeometry(osg::Geometry* pGeom, const VBF_GEOMETRY_PARAM& param, bool bRecomputeNormal);

// 利用传入的参数param，创建几何体
// 参数：bRecomputeNormal -- 是否需要在该函数中重新计算法线
VBF_GLAUX_EXPORT osg::Geometry* VBF_CreateGeometry(const VBF_GEOMETRY_PARAM& param, bool bRecomputeNormal);

// 创建一个单一颜色的顶点颜色数组
VBF_GLAUX_EXPORT void VBF_CreateOverallColorArray(const osg::Vec4f& color, VBF_GEOMETRY_PARAM& param);

// 创建四边形的顶点索引，绘制方式为：GL_QUADS，正面顶点的排列顺序为逆时针
VBF_GLAUX_EXPORT osg::UIntArray* VBF_CreateQuadIndices(int nNumRows, int nNumCols);


// 指定一个纹理，创建一个四边形（原点位于矩形左下角）
// 参数：bModelVertical-- 模型是否垂直于地面
VBF_GLAUX_EXPORT osg::Geometry* VBF_CreateTexturedQuad(osg::Texture2D* pTexture, bool bModelVertical=true);

// 指定一个图像，创建一个四边形（原点位于矩形左下角）
// 参数：bModelVertical-- 模型是否垂直于地面
VBF_GLAUX_EXPORT osg::Geometry* VBF_CreateTexturedQuad(osg::Image* pImage, bool bModelVertical=true);


// 创建一个单位四边形，即边长为1，原点默认位于四边形中心（注意：该函数只创建四边形，不设置纹理）
// 参数：bModelVertical-- 模型是否垂直于地面
// 参数：pImage -- 四边形使用的图像（可以为NULL）
// 参数：fTexOrignX, fTexOrignY -- 纹理原点在位图中的相对位置（相对于左下角）
VBF_GLAUX_EXPORT osg::Geometry* VBF_CreateUnitQuad(bool bModelVertical, osg::Image* pImage=NULL, float fTexOrignX=0.5f, float fTexOrignY=0.5f);


// 创建一个指定旋转角的单位四边形（注意：该函数只创建四边形，不设置纹理）
// 参数：fRotateZ -- 四边形绕Z轴的旋转角（单位：角度）
VBF_GLAUX_EXPORT osg::Geometry* VBF_CreateUnitQuad(bool bModelVertical, float fRotateZ, osg::Image* pImage=NULL, float fTexOrignX=0.5f, float fTexOrignY=0.5f);


// 创建一个指定宽高的四边形（注意：该函数只创建四边形，不设置纹理）
// 参数：fWidth, fHeight -- 四边形的宽度和高度（单位：米）
VBF_GLAUX_EXPORT osg::Geometry* VBF_CreateQuad(bool bModelVertical, float fWidth, float fHeight, osg::Image* pImage=NULL, float fTexOrignX=0.5f, float fTexOrignY=0.5f);



// 对一个几何图形的纹理坐标进行上下翻转
VBF_GLAUX_EXPORT void VBF_FlipTexCoords(osg::Geometry* pGeom);


#endif
