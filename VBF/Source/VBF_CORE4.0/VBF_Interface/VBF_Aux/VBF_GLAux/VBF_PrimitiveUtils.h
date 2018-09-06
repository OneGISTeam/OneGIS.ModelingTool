//***************************************************************************************
// FileName��VBF_PrimitiveUtils.h
// Function���������е�ͼԪ���ߺ���
// Author:   ��Ө
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
// ����ṹ�壺VBF_PRIMITIVESET_DATA
// �ṹ���������������е�ͼԪ������
//---------------------------------------------------------------
typedef struct _tagVBFPrimitiveSetData
{
	ref_ptr<osg::UIntArray>		pIndices;		// ��������������ΪNULL��
	unsigned int				nMode;			// ͼԪ���Ʒ�ʽ
    CVBF_Optional<int>          nVertexFirst;   // ��ʹ�ö�������ʱ�������ͼԪ�Ķ�����ʼ�����ţ�Ĭ��ֵΪ0
    CVBF_Optional<int>          nVertexCount;   // ��ʹ�ö�������ʱ�������ͼԪ�Ķ��������Ĭ��ֵΪpVerts->size()

	_tagVBFPrimitiveSetData(osg::UIntArray* indices, unsigned int mode)
		: pIndices(indices), nMode(mode)
	{
	}

} VBF_PRIMITIVESET_DATA;


//---------------------------------------------------------------
// ����ṹ�壺VBF_GEOMETRY_PARAM
// �ṹ���������������еĸ�������
//---------------------------------------------------------------
typedef struct _tagVBFGeometryParam
{
	// ��������
	osg::Geometry::ArrayData		VertexData;				// ��������
    osg::Geometry::ArrayData		NormalData;				// ���㷨��
    osg::Geometry::ArrayData		ColorData;				// ��������ɫ
    osg::Geometry::ArrayData		SecondaryColorData;		// ���㸨��ɫ
    osg::Geometry::ArrayData		FogCoordData;			// ����������

    osg::Geometry::ArrayDataList    TexCoordList;			// n�鶥����������
    osg::Geometry::ArrayDataList	VertexAttribList;		// n�鶥������
	
	// ��������
	std::vector<VBF_PRIMITIVESET_DATA>	PrimSetList;		// n��ͼԪ��

	// ��Ⱦ״̬
	bool					bUseDispList;	// �Ƿ�ʹ����ʾ�б�
	bool					bUseVBO;		// �Ƿ�ʹ��VBO�����Ϊtrue������ʹ����ʾ�б�
	CVBF_Optional<bool>		bCullBack;		// �Ƿ�ü�������
	CVBF_Optional<bool>		bFrontCCW;		// ���涥�������˳���Ƿ�Ϊ��ʱ��

	_tagVBFGeometryParam()
	{
		bUseDispList = false;
		bUseVBO		 = true;

		VertexData.binding	= osg::Geometry::BIND_PER_VERTEX;
	}

	// ���ö�������
	void SetVertexArray(osg::Array* pArray, osg::Geometry::AttributeBinding nBinding=osg::Geometry::BIND_PER_VERTEX) 
	{  
		VertexData.array   = pArray;
		VertexData.binding = nBinding;
	}

	// ���ö��㷨��
	void SetNormalArray(osg::Array* pArray, osg::Geometry::AttributeBinding nBinding=osg::Geometry::BIND_PER_VERTEX) 
	{  
		NormalData.array   = pArray;
		NormalData.binding = nBinding;
	}

	// ���ö�������ɫ
	void SetColorArray(osg::Array* pArray, osg::Geometry::AttributeBinding nBinding=osg::Geometry::BIND_PER_VERTEX) 
	{  
		ColorData.array   = pArray;
		ColorData.binding = nBinding;
	}

	// ���ö��㸨��ɫ
	void SetSecondaryColorArray(osg::Array* pArray, osg::Geometry::AttributeBinding nBinding=osg::Geometry::BIND_PER_VERTEX) 
	{  
		SecondaryColorData.array   = pArray;
		SecondaryColorData.binding = nBinding;
	}

	// ���ö���������
	void SetFogCoordArray(osg::Array* pArray, osg::Geometry::AttributeBinding nBinding=osg::Geometry::BIND_PER_VERTEX) 
	{  
		FogCoordData.array   = pArray;
		FogCoordData.binding = nBinding;
	}

	// ���һ����������
	void AddTexCoord(osg::Array* pArray, osg::Geometry::AttributeBinding nBinding=osg::Geometry::BIND_PER_VERTEX)
	{
		TexCoordList.push_back( osg::Geometry::ArrayData(pArray, nBinding) );
	}

	// ���һ�鶥������
	void AddVertexAttrib(osg::Array* pArray, osg::Geometry::AttributeBinding nBinding=osg::Geometry::BIND_PER_VERTEX)
	{
		VertexAttribList.push_back( osg::Geometry::ArrayData(pArray, nBinding) );
	}

	// ���һ��ͼԪ��
	void AddPrimitiveSet(osg::UIntArray* pIndices, unsigned int nMode)
	{
		PrimSetList.push_back( VBF_PRIMITIVESET_DATA(pIndices, nMode) );
	}

} VBF_GEOMETRY_PARAM;


// ���ô���Ĳ���param�����¼�����
// ������bRecomputeNormal -- �Ƿ���Ҫ�ڸú��������¼��㷨��
VBF_GLAUX_EXPORT bool VBF_UpdateGeometry(osg::Geometry* pGeom, const VBF_GEOMETRY_PARAM& param, bool bRecomputeNormal);

// ���ô���Ĳ���param������������
// ������bRecomputeNormal -- �Ƿ���Ҫ�ڸú��������¼��㷨��
VBF_GLAUX_EXPORT osg::Geometry* VBF_CreateGeometry(const VBF_GEOMETRY_PARAM& param, bool bRecomputeNormal);

// ����һ����һ��ɫ�Ķ�����ɫ����
VBF_GLAUX_EXPORT void VBF_CreateOverallColorArray(const osg::Vec4f& color, VBF_GEOMETRY_PARAM& param);

// �����ı��εĶ������������Ʒ�ʽΪ��GL_QUADS�����涥�������˳��Ϊ��ʱ��
VBF_GLAUX_EXPORT osg::UIntArray* VBF_CreateQuadIndices(int nNumRows, int nNumCols);


// ָ��һ����������һ���ı��Σ�ԭ��λ�ھ������½ǣ�
// ������bModelVertical-- ģ���Ƿ�ֱ�ڵ���
VBF_GLAUX_EXPORT osg::Geometry* VBF_CreateTexturedQuad(osg::Texture2D* pTexture, bool bModelVertical=true);

// ָ��һ��ͼ�񣬴���һ���ı��Σ�ԭ��λ�ھ������½ǣ�
// ������bModelVertical-- ģ���Ƿ�ֱ�ڵ���
VBF_GLAUX_EXPORT osg::Geometry* VBF_CreateTexturedQuad(osg::Image* pImage, bool bModelVertical=true);


// ����һ����λ�ı��Σ����߳�Ϊ1��ԭ��Ĭ��λ���ı������ģ�ע�⣺�ú���ֻ�����ı��Σ�����������
// ������bModelVertical-- ģ���Ƿ�ֱ�ڵ���
// ������pImage -- �ı���ʹ�õ�ͼ�񣨿���ΪNULL��
// ������fTexOrignX, fTexOrignY -- ����ԭ����λͼ�е����λ�ã���������½ǣ�
VBF_GLAUX_EXPORT osg::Geometry* VBF_CreateUnitQuad(bool bModelVertical, osg::Image* pImage=NULL, float fTexOrignX=0.5f, float fTexOrignY=0.5f);


// ����һ��ָ����ת�ǵĵ�λ�ı��Σ�ע�⣺�ú���ֻ�����ı��Σ�����������
// ������fRotateZ -- �ı�����Z�����ת�ǣ���λ���Ƕȣ�
VBF_GLAUX_EXPORT osg::Geometry* VBF_CreateUnitQuad(bool bModelVertical, float fRotateZ, osg::Image* pImage=NULL, float fTexOrignX=0.5f, float fTexOrignY=0.5f);


// ����һ��ָ����ߵ��ı��Σ�ע�⣺�ú���ֻ�����ı��Σ�����������
// ������fWidth, fHeight -- �ı��εĿ�Ⱥ͸߶ȣ���λ���ף�
VBF_GLAUX_EXPORT osg::Geometry* VBF_CreateQuad(bool bModelVertical, float fWidth, float fHeight, osg::Image* pImage=NULL, float fTexOrignX=0.5f, float fTexOrignY=0.5f);



// ��һ������ͼ�ε���������������·�ת
VBF_GLAUX_EXPORT void VBF_FlipTexCoords(osg::Geometry* pGeom);


#endif
