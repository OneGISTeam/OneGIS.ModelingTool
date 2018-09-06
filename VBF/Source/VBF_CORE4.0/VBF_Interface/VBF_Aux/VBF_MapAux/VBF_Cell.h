//*******************************************************************
// FileName��VBF_Cell.h
// Function���ռ������еĵ�Ԫ��
// Author:   ��Ө
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
// �����ࣺCVBF_Obj
// ���������ռ������д洢�Ķ��󣨴洢�ڲ����ٷֵĵ�Ԫ���У�
//=========================================================================
class VBF_MAPAUX_EXPORT CVBF_Obj : public ::CVBF_Referenced
{
public:

    osg::Vec3d      vGeo;       // ��������
    osg::Vec3d      vWorld;     // ��������
    float           fRotateZ;   // ��Z�����ת�ǣ���λ���Ƕȣ�

    CVBF_Obj()
    {
        vGeo     = ::VBF_GetPosInvalid();
        vWorld   = ::VBF_GetPosInvalid();
        fRotateZ = 0.0f;
    }
};

typedef std::vector< ref_ptr<CVBF_Obj> > CVBF_ObjList;


//=========================================================================
// �����ࣺCVBF_Cell
// ���������ռ������е�ÿ����Ԫ�񣨿���Ƕ�ף�
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

    // ����һ����Χ����ͬ�ĵ�Ԫ��
    virtual CVBF_Cell* CloneByBound()=0;

    // ���㵥Ԫ��İ�Χ��
    virtual void ComputeBound()=0;

    // ������������ϵ�µİ�Χ��
    virtual void ComputeBoundingBoxInWorld()=0;

    // ��ȡ��������ϵ�µİ�Χ��
    const osg::BoundingBox& GetBoundingBoxInWorld() { return m_BoundingBoxInWorld; }

    // �жϸõ�Ԫ���Ƿ����ĳ������
    virtual bool ContainsObj(CVBF_Obj* pObj)=0;

    // �жϸõ�Ԫ���Ƿ����ĳ�������
    bool Contains(const osg::Vec3& position) const { return m_BoundingBox.contains(position); }

    // �õ��������Ե�Ԫ����зָ�����ռ�����
    bool Divide(unsigned int maxNumObjsPerCell=10);
    bool Divide(bool xAxis, bool yAxis, bool zAxis);

    // ��ģ�ͷ��ں��ʵĵ�Ԫ����
    void bin();

public:
    observer_ptr<osg::EllipsoidModel>  m_opEllipModel;

    CVBF_Cell*              m_pParent;
    osg::BoundingBox        m_BoundingBox;          // ����/��������ϵ�µİ�Χ��
    osg::BoundingBox        m_BoundingBoxInWorld;   // ��������ϵ�µİ�Χ��
    CVBF_CellList           m_CellList;
    CVBF_ObjList            m_ObjList;
};


//=========================================================================
// �����ࣺCVBF_CellGeo
// ��������ͨ���������깹���ռ�����
//=========================================================================
class VBF_MAPAUX_EXPORT CVBF_CellGeo : public CVBF_Cell
{
public:
    CVBF_CellGeo(osg::EllipsoidModel* pEllipModel) : CVBF_Cell(pEllipModel) {}
    virtual ~CVBF_CellGeo() {}

    // ����һ����Χ����ͬ�ĵ�Ԫ��
    virtual CVBF_Cell* CloneByBound();

    // ���㵥Ԫ��İ�Χ��
    virtual void ComputeBound();

    // ������������ϵ�µİ�Χ��
    virtual void ComputeBoundingBoxInWorld();

    // �жϸõ�Ԫ���Ƿ����ĳ������
    virtual bool ContainsObj(CVBF_Obj* pObj) { return m_BoundingBox.contains(pObj->vGeo);  }
};


//=========================================================================
// �����ࣺCVBF_CellXYZ
// ��������ͨ�����ֱ�����깹���ռ�����
//=========================================================================
class VBF_MAPAUX_EXPORT CVBF_CellXYZ : public CVBF_Cell
{
public:
    CVBF_CellXYZ(osg::EllipsoidModel* pEllipModel) : CVBF_Cell(pEllipModel) {}
    virtual ~CVBF_CellXYZ() {}

    // ����һ����Χ����ͬ�ĵ�Ԫ��
    virtual CVBF_Cell* CloneByBound();

    // ���㵥Ԫ��İ�Χ��
    virtual void ComputeBound();

    // ������������ϵ�µİ�Χ��
    virtual void ComputeBoundingBoxInWorld() { m_BoundingBoxInWorld = m_BoundingBox; }

    // �жϸõ�Ԫ���Ƿ����ĳ������
    virtual bool ContainsObj(CVBF_Obj* pObj) { return m_BoundingBox.contains(pObj->vWorld);  }
};


//=========================================================================
// �����ࣺCVBF_CullCallbackForCell
// ���������ü��ص�����ĳ����Ԫ����ɵ�����ü��Ϳɼ�����ü�
//=========================================================================
class VBF_MAPAUX_EXPORT CVBF_CullCallbackForCell : public osg::NodeCallback
{
public:
 //   CVBF_CullCallbackForCell(){}
    CVBF_CullCallbackForCell(CVBF_Cell* pCell, bool bClipByEarth, bool bClipByDist, float fDistMin=0.0, float fDistMax=FLT_MAX);
 //   CVBF_CullCallbackForCell(const CVBF_CullCallbackForCell& nc,const CopyOp&){}

 //   META_Object(osg,CVBF_CullCallbackForCell);

    // ���ز�����
    virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);

private:
    observer_ptr<CVBF_Cell>     m_opCell;

    bool                m_bClipByEarth; // �Ƿ���������ü�
    bool                m_bClipByDist;  // �Ƿ����ɼ�����ü�
    float               m_fDistMin;     // ��С�ɼ�����
    float               m_fDistMax;     // ���ɼ�����
};


//=========================================================================
// �����ࣺCVBF_CullCallbackForObj
// ���������ü��ص�����ĳ����ֹ��Ŀ�����ɵ�����ü��Ϳɼ�����ü�
//=========================================================================
class VBF_MAPAUX_EXPORT CVBF_CullCallbackForObj : public osg::Drawable::CullCallback
{
public:
    CVBF_CullCallbackForObj(const osg::Vec3d& ptWorld, bool bClipByEarth, bool bClipByDist, float fDistMin=0.0, float fDistMax=FLT_MAX);

    // ���غ���
    virtual bool cull(osg::NodeVisitor* nv, osg::Drawable* drawable, osg::RenderInfo* renderInfo) const;

private:
    osg::Vec3d          m_ptWorld;
    bool                m_bClipByEarth; // �Ƿ���������ü�
    bool                m_bClipByDist;  // �Ƿ����ɼ�����ü�
    float               m_fDistMin;     // ��С�ɼ�����
    float               m_fDistMax;     // ���ɼ�����
};

#endif 
