//*******************************************************************
// FileName：VBF_Cell.h
// Function：空间索引中的单元格
// Author:   杜莹
// Date:     2015-11-17
//*******************************************************************

#ifndef __VBF_CELL_H__
#define __VBF_CELL_H__


#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Base/ref_ptr>
#include <Types/Vec3>
#include <Types/Vec4ub>
#include <Types/VBF_BoundingBox.h>
#include <vector>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Base/observer_ptr>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupCoordSys.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawable.h>
#include <VBF_Aux/VBF_MapAux/VBF_CoordTransformUtils.h>


//=========================================================================
// 定义类：CVBF_Obj
// 类描述：空间索引中存储的对象（存储在不可再分的单元格中）
//=========================================================================
class VBF_MAPAUX_EXPORT CVBF_Obj : public ::CVBF_Referenced
{
public:

    osg::Vec3d      vGeo;       // 地理坐标
    osg::Vec3d      vWorld;     // 世界坐标
    float           fRotateZ;   // 绕Z轴的旋转角（单位：角度）

    CVBF_Obj()
    {
        vGeo     = ::VBF_GetPosInvalid();
        vWorld   = ::VBF_GetPosInvalid();
        fRotateZ = 0.0f;
    }
};

typedef std::vector< ref_ptr<CVBF_Obj> > CVBF_ObjList;


//=========================================================================
// 定义类：CVBF_Cell
// 类描述：空间索引中的每个单元格（可以嵌套）
//=========================================================================
class VBF_MAPAUX_EXPORT CVBF_Cell : public ::CVBF_Referenced
{
public:
    typedef std::vector< ref_ptr<CVBF_Cell> > CVBF_CellList;

    CVBF_Cell(osg::EllipsoidModel* pEllipModel) : m_opEllipModel(pEllipModel), m_pParent(NULL) {}
    virtual ~CVBF_Cell() {}

    void addCell(CVBF_Cell* pCell) { pCell->m_pParent=this; m_CellList.push_back(pCell); }
    void addObj(CVBF_Obj* pObj) { m_ObjList.push_back(pObj); }
    void addObjs(const CVBF_ObjList& trees) { m_ObjList.insert(m_ObjList.end(), trees.begin(), trees.end()); }

    // 复制一个包围盒相同的单元格
    virtual CVBF_Cell* CloneByBound()=0;

    // 计算单元格的包围盒
    virtual void ComputeBound()=0;

    // 计算世界坐标系下的包围盒
    virtual void ComputeBoundingBoxInWorld()=0;

    // 获取世界坐标系下的包围盒
    const osg::BoundingBox& GetBoundingBoxInWorld() { return m_BoundingBoxInWorld; }

    // 判断该单元格是否包含某个对象
    virtual bool ContainsObj(CVBF_Obj* pObj)=0;

    // 判断该单元格是否包含某个坐标点
    bool Contains(const osg::Vec3& position) const { return m_BoundingBox.contains(position); }

    // 用迭代方法对单元格进行分割，构建空间索引
    bool Divide(unsigned int maxNumObjsPerCell=10);
    bool Divide(bool xAxis, bool yAxis, bool zAxis);

    // 把模型放在合适的单元格中
    void bin();

public:
    observer_ptr<osg::EllipsoidModel>  m_opEllipModel;

    CVBF_Cell*              m_pParent;
    osg::BoundingBox        m_BoundingBox;          // 地理/世界坐标系下的包围盒
    osg::BoundingBox        m_BoundingBoxInWorld;   // 世界坐标系下的包围盒
    CVBF_CellList           m_CellList;
    CVBF_ObjList            m_ObjList;
};


//=========================================================================
// 定义类：CVBF_CellGeo
// 类描述：通过地理坐标构建空间索引
//=========================================================================
class VBF_MAPAUX_EXPORT CVBF_CellGeo : public CVBF_Cell
{
public:
    CVBF_CellGeo(osg::EllipsoidModel* pEllipModel) : CVBF_Cell(pEllipModel) {}
    virtual ~CVBF_CellGeo() {}

    // 复制一个包围盒相同的单元格
    virtual CVBF_Cell* CloneByBound();

    // 计算单元格的包围盒
    virtual void ComputeBound();

    // 计算世界坐标系下的包围盒
    virtual void ComputeBoundingBoxInWorld();

    // 判断该单元格是否包含某个对象
    virtual bool ContainsObj(CVBF_Obj* pObj) { return m_BoundingBox.contains(pObj->vGeo);  }
};


//=========================================================================
// 定义类：CVBF_CellXYZ
// 类描述：通过大地直角坐标构建空间索引
//=========================================================================
class VBF_MAPAUX_EXPORT CVBF_CellXYZ : public CVBF_Cell
{
public:
    CVBF_CellXYZ(osg::EllipsoidModel* pEllipModel) : CVBF_Cell(pEllipModel) {}
    virtual ~CVBF_CellXYZ() {}

    // 复制一个包围盒相同的单元格
    virtual CVBF_Cell* CloneByBound();

    // 计算单元格的包围盒
    virtual void ComputeBound();

    // 计算世界坐标系下的包围盒
    virtual void ComputeBoundingBoxInWorld() { m_BoundingBoxInWorld = m_BoundingBox; }

    // 判断该单元格是否包含某个对象
    virtual bool ContainsObj(CVBF_Obj* pObj) { return m_BoundingBox.contains(pObj->vWorld);  }
};


//=========================================================================
// 定义类：CVBF_CullCallbackForCell
// 类描述：裁剪回调，对某个单元格完成地球背面裁剪和可见距离裁剪
//=========================================================================
class VBF_MAPAUX_EXPORT CVBF_CullCallbackForCell : public osg::NodeCallback
{
public:
 //   CVBF_CullCallbackForCell(){}
    CVBF_CullCallbackForCell(CVBF_Cell* pCell, bool bClipByEarth, bool bClipByDist, float fDistMin=0.0, float fDistMax=FLT_MAX);
 //   CVBF_CullCallbackForCell(const CVBF_CullCallbackForCell& nc,const CopyOp&){}

 //   META_Object(osg,CVBF_CullCallbackForCell);

    // 重载操作符
    virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);

private:
    observer_ptr<CVBF_Cell>     m_opCell;

    bool                m_bClipByEarth; // 是否开启地球背面裁剪
    bool                m_bClipByDist;  // 是否开启可见距离裁剪
    float               m_fDistMin;     // 最小可见距离
    float               m_fDistMax;     // 最大可见距离
};


//=========================================================================
// 定义类：CVBF_CullCallbackForObj
// 类描述：裁剪回调，对某个静止的目标点完成地球背面裁剪和可见距离裁剪
//=========================================================================
class VBF_MAPAUX_EXPORT CVBF_CullCallbackForObj : public osg::Drawable::CullCallback
{
public:
    CVBF_CullCallbackForObj(const osg::Vec3d& ptWorld, bool bClipByEarth, bool bClipByDist, float fDistMin=0.0, float fDistMax=FLT_MAX);

    // 重载函数
    virtual bool cull(osg::NodeVisitor* nv, osg::Drawable* drawable, osg::RenderInfo* renderInfo) const;

private:
    osg::Vec3d          m_ptWorld;
    bool                m_bClipByEarth; // 是否开启地球背面裁剪
    bool                m_bClipByDist;  // 是否开启可见距离裁剪
    float               m_fDistMin;     // 最小可见距离
    float               m_fDistMax;     // 最大可见距离
};

#endif 
