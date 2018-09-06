//**********************************************************************************
// FileName：VBF_SGNodeBillboard.h
// Function：综合变换节点，改编自osg::Billboard
//           可综合完成水平/垂直布告牌中每个Raster模型的缩放、旋转、布告牌和定位到椭球功能
//           注意：不能用于完全布告牌
// Author:   杜莹
// Date:     2015-11-20
//**********************************************************************************

#ifndef __VBF_SGNODE_BILLBOARD_H__
#define __VBF_SGNODE_BILLBOARD_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransformImpl.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGeometryBillboard.h>

class IVBF_SGNodeBillboardCallback : public CVBF_Referenced
{
public:
    ~IVBF_SGNodeBillboardCallback(){}

    virtual double  GetAngleH()=0;	// 获取水平视角 (即方位角，单位：角度)
    // 获取显示分辨率的向量(米/像素)，用法为：float fPixelSize = ptWorld * GetPixelSizeVector()
    virtual const osg::Vec4& GetPixelSizeVector()=0;

};
// 水平/垂直布告牌：不固定像素大小，要求四边形自身带有宽高（单位：米）
class VBF_GLAUX_EXPORT CVBF_SGNodeBillboard : public osg::Billboard
{
private:
    typedef osg::Billboard BaseClass;

public:
    CVBF_SGNodeBillboard() {}
    CVBF_SGNodeBillboard(IVBF_SGNodeBillboardCallback* pICallback);
    CVBF_SGNodeBillboard(const CVBF_SGNodeBillboard&, const CopyOp& copyop=CopyOp::SHALLOW_COPY) {}

    META_Node(VBF, CVBF_SGNodeBillboard)

    // 重载函数，计算某个Drawable的布告牌矩阵
    virtual bool computeMatrix(Matrix& modelview, const Vec3& eye_local, const Vec3& pos_local) const;

    // 添加一个Drawable，同时设置世界坐标和椭球矩阵
    bool AddDrawable(Drawable* gset, const Vec3& pos, const osg::Matrix& matEllip);

    // 修改一个Drawable，同时设置世界坐标和椭球矩阵
    bool UpdateDrawable(int nIndex, const Vec3& pos, const osg::Matrix& matEllip);

    // 获取某个Drawable的椭球矩阵
    const osg::Matrix& GetDrawableMatrix(int nIndex) { return m_EllipMatrixList[nIndex]; }

protected:
    ref_ptr<IVBF_SGNodeBillboardCallback> m_ipCallback;

    // 下列变量是为了统计computeMatrix()函数将要计算到第几个Drawable，以便直接获取对应的椭球矩阵，
    // 从而避免了在computeMatrix()函数中重复计算椭球矩阵
    // 详情参见函数：CullVisitor::apply(IVBF_SGNodeGeometryBillboard& node)

    mutable int                 m_nCurrDrawableIndex;   // 当前将要计算到第几个Drawable
    std::vector<osg::Matrix>    m_EllipMatrixList;      // 每个Drawable对应的椭球矩阵，与_positionList类似
    mutable osg::Quat           m_quatRotation;         // 旋转矩阵，只与视点的方位角有关，避免重复计算
};


// 水平/垂直布告牌：固定像素大小，要求四边形为单位四边形（注意：该类不能用于完全布告牌）
class VBF_GLAUX_EXPORT CVBF_SGNodeBillboardWithFixedPixels : public CVBF_SGNodeBillboard
{
private:
    typedef CVBF_SGNodeBillboard BaseClass;

public:
    CVBF_SGNodeBillboardWithFixedPixels() {}
    CVBF_SGNodeBillboardWithFixedPixels(IVBF_SGNodeBillboardCallback* pICallback, float fWidth, float fHeight);
    CVBF_SGNodeBillboardWithFixedPixels(const CVBF_SGNodeBillboardWithFixedPixels&, const CopyOp& copyop=CopyOp::SHALLOW_COPY) {}

    META_Node(VBF, CVBF_SGNodeBillboardWithFixedPixels)

    // 重载函数，计算某个Drawable的布告牌矩阵
    virtual bool computeMatrix(Matrix& modelview, const Vec3& eye_local, const Vec3& pos_local) const;

private:

    // 显示分辨率的向量（只与相机和视口有关，每帧计算一次即可）
    mutable osg::Vec4   m_vPixelSize;           // 单位：米/像素

    float           m_fWidthInPixels;       // 宽度（单位：像素）
    float           m_fHeightInPixels;      // 高度（单位：像素）
    mutable float   m_fWidthInMeters;       // 宽度（单位：米）
    mutable float   m_fHeightInMeters;      // 高度（单位：米）
};


// 叶节点：固定像素大小，要求四边形为单位四边形
class VBF_GLAUX_EXPORT CVBF_SGGeodeWithFixedPixels : public CVBF_SGNodeBillboard
{
private:
    typedef CVBF_SGNodeBillboard BaseClass;

public:
    CVBF_SGGeodeWithFixedPixels() {}
    CVBF_SGGeodeWithFixedPixels(IVBF_SGNodeBillboardCallback* pICallback, float fWidth, float fHeight);
    CVBF_SGGeodeWithFixedPixels(const CVBF_SGGeodeWithFixedPixels&, const CopyOp& copyop=CopyOp::SHALLOW_COPY) {}

    META_Node(VBF, CVBF_SGGeodeWithFixedPixels)

    // 重载函数，计算某个Drawable的布告牌矩阵
    virtual bool computeMatrix(Matrix& modelview, const Vec3& eye_local, const Vec3& pos_local) const;

private:

    // 显示分辨率的向量（只与相机和视口有关，每帧计算一次即可）
    mutable osg::Vec4   m_vPixelSize;           // 单位：米/像素

    float               m_fWidthInPixels;       // 宽度（单位：像素）
    float               m_fHeightInPixels;      // 高度（单位：像素）
    mutable float       m_fWidthInMeters;       // 宽度（单位：米）
    mutable float       m_fHeightInMeters;      // 高度（单位：米）
};



#endif
