//*******************************************************************
// FileName：IVBF_MarkModelGeometry.h
// Function：实体模型接口：不规则几何体
// Author:   杜莹
// Date:     2014-09-04
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_GEOMETRY_H__
#define __IVBF_MARK_MODEL_GEOMETRY_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec3d>
#include <Types/Vec4f>
#include <vector>


//--------------------------------------------------------------------
// 定义枚举：EVBF_ATTRBIND_TYPE
// 枚举描述：几何体各类属性（顶点、颜色、纹理、法线、图元等）的绑定方式
//--------------------------------------------------------------------
enum EVBF_ATTRBIND_TYPE
{
    VBF_ATTRBIND_OFF        = 0,	// 不启用绑定
    VBF_ATTRBIND_OVERALL,			// 绑定全部顶点
    VBF_ATTRBIND_PER_PRIMITIVE_SET,	// 单个绘图基元（图元）绑定
    VBF_ATTRBIND_PER_PRIMITIVE,		// 单个独立的图元绑定
    VBF_ATTRBIND_PER_VERTEX			// 单个顶点绑定
};


class IVBF_MarkModelGeometry : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelGeometry() {}

    // 设置/获取顶点坐标数组（地理坐标）
    virtual void                    SetVertexArrayGeo(const std::vector<osg::Vec3d>& vPointsGeo)=0;
    virtual std::vector<osg::Vec3d> GetVertexArrayGeo()=0;

    // 设置/获取顶点主颜色数组
    virtual void                    SetColorArray(const std::vector<osg::Vec4f>& vColors)=0;
    virtual std::vector<osg::Vec4f> GetColorArray()=0;

    // 设置/获取顶点主颜色数组与顶点绑定方式（默认值为VBF_ATTRBIND_PER_VERTEX）
    virtual void                SetColorBinding(EVBF_ATTRBIND_TYPE nBindType)=0;
    virtual EVBF_ATTRBIND_TYPE  GetColorBinding()=0;

    // 设置/获取顶点辅颜色数组
    virtual void                    SetSecondaryColorArray(const std::vector<osg::Vec4f>& vColors)=0;
    virtual std::vector<osg::Vec4f> GetSecondaryColorArray()=0;

    // 设置/获取顶点辅颜色数组与顶点绑定方式（默认值为VBF_ATTRBIND_PER_VERTEX）
    virtual void                SetSecondaryColorBinding(EVBF_ATTRBIND_TYPE nBindType)=0;
    virtual EVBF_ATTRBIND_TYPE  GetSecondaryColorBinding()=0;

    // 设置/获取顶点法线数组
    virtual void                    SetNormalArray(const std::vector<osg::Vec3f>& vNormals)=0;
    virtual std::vector<osg::Vec3f> GetNormalArray()=0;

    // 设置/获取顶点法线数组与顶点绑定方式（默认值为VBF_ATTRBIND_PER_VERTEX）
    virtual void                SetNormalBinding(EVBF_ATTRBIND_TYPE nBindType)=0;
    virtual EVBF_ATTRBIND_TYPE  GetNormalBinding()=0;

    // 获取纹理坐标数组的总数
    virtual int GetNumTexCoordArrays()=0;

    // 设置/获取第n遍纹理的坐标数组
    virtual void SetTexCoordArray(unsigned int nTexUnit, const std::vector<osg::Vec2f>& vTexCoords)=0;
    virtual bool GetTexCoordArray(unsigned int nTexUnit, std::vector<osg::Vec2f>& vTexCoords)=0;

    // 设置/获取第n遍纹理的坐标数组与顶点绑定方式（默认值为VBF_ATTRBIND_PER_VERTEX）
    virtual void SetTexCoordArrayBinding(unsigned int nTexUnit, EVBF_ATTRBIND_TYPE nBindType)=0;
    virtual bool GetTexCoordArrayBinding(unsigned int nTexUnit, EVBF_ATTRBIND_TYPE& nBindType)=0;

	// 设置/获取第n遍纹理的图像指针
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void		SetTexImage(unsigned int nTexUnit, osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage(unsigned int nTexUnit)=0;

    // 设置/获取是否需要裁剪掉背面
    virtual void SetCullBack(bool bCull)=0;
    virtual bool IsCullBack()=0;

    // 是否/获取正面顶点的排列顺序是否为逆时针
    virtual void SetFrontCCW(bool bCCW)=0;
    virtual bool IsFrontCCW()=0;

    // 如果有点状图元，设置点的大小（默认值为1.0）
    virtual void  SetPointSize(float fSize)=0;
    virtual float GetPointSize()=0;

    // 如果有线状图元，设置线宽（默认值为1.0）
    virtual void  SetLineWidth(float fWidth)=0;
    virtual float GetLineWidth()=0;

    // 是否需要在系统内部重新计算法线（默认值为false）
    virtual void SetRecomputeNormal(bool bRecompute)=0;
    virtual bool IsRecomputeNormal()=0;

    // 添加一组图元（不使用顶点索引）
    // 参数：nMode  -- 图元类型，如GL_POINTS, GL_TRIANGLES, GL_QUADS等等
    //      nVertexFirst -- 参与该组图元的顶点起始索引号
    //      nVertexCount -- 参与该组图元的顶点个数
    virtual void AddPrimitiveSet(unsigned int nMode, int nVertexFirst, int nVertexCount)=0;

    // 添加一组图元（使用顶点索引）
    // 参数：nMode  -- 图元类型，如GL_POINTS, GL_TRIANGLES, GL_QUADS等等
    //      vIndices -- 参与该组图元的顶点的索引号
    virtual void AddPrimitiveSetIndexed(unsigned int nMode, const std::vector<unsigned int>& vIndices)=0;

    // 获取图元总数
    virtual int GetNumPrimitiveSets()=0;
};

#endif 
