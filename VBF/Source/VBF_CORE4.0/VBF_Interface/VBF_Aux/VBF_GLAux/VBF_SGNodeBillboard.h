//**********************************************************************************
// FileName��VBF_SGNodeBillboard.h
// Function���ۺϱ任�ڵ㣬�ı���osg::Billboard
//           ���ۺ����ˮƽ/��ֱ��������ÿ��Rasterģ�͵����š���ת�������ƺͶ�λ��������
//           ע�⣺����������ȫ������
// Author:   ��Ө
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

    virtual double  GetAngleH()=0;	// ��ȡˮƽ�ӽ� (����λ�ǣ���λ���Ƕ�)
    // ��ȡ��ʾ�ֱ��ʵ�����(��/����)���÷�Ϊ��float fPixelSize = ptWorld * GetPixelSizeVector()
    virtual const osg::Vec4& GetPixelSizeVector()=0;

};
// ˮƽ/��ֱ�����ƣ����̶����ش�С��Ҫ���ı���������п�ߣ���λ���ף�
class VBF_GLAUX_EXPORT CVBF_SGNodeBillboard : public osg::Billboard
{
private:
    typedef osg::Billboard BaseClass;

public:
    CVBF_SGNodeBillboard() {}
    CVBF_SGNodeBillboard(IVBF_SGNodeBillboardCallback* pICallback);
    CVBF_SGNodeBillboard(const CVBF_SGNodeBillboard&, const CopyOp& copyop=CopyOp::SHALLOW_COPY) {}

    META_Node(VBF, CVBF_SGNodeBillboard)

    // ���غ���������ĳ��Drawable�Ĳ����ƾ���
    virtual bool computeMatrix(Matrix& modelview, const Vec3& eye_local, const Vec3& pos_local) const;

    // ���һ��Drawable��ͬʱ��������������������
    bool AddDrawable(Drawable* gset, const Vec3& pos, const osg::Matrix& matEllip);

    // �޸�һ��Drawable��ͬʱ��������������������
    bool UpdateDrawable(int nIndex, const Vec3& pos, const osg::Matrix& matEllip);

    // ��ȡĳ��Drawable���������
    const osg::Matrix& GetDrawableMatrix(int nIndex) { return m_EllipMatrixList[nIndex]; }

protected:
    ref_ptr<IVBF_SGNodeBillboardCallback> m_ipCallback;

    // ���б�����Ϊ��ͳ��computeMatrix()������Ҫ���㵽�ڼ���Drawable���Ա�ֱ�ӻ�ȡ��Ӧ���������
    // �Ӷ���������computeMatrix()�������ظ������������
    // ����μ�������CullVisitor::apply(IVBF_SGNodeGeometryBillboard& node)

    mutable int                 m_nCurrDrawableIndex;   // ��ǰ��Ҫ���㵽�ڼ���Drawable
    std::vector<osg::Matrix>    m_EllipMatrixList;      // ÿ��Drawable��Ӧ�����������_positionList����
    mutable osg::Quat           m_quatRotation;         // ��ת����ֻ���ӵ�ķ�λ���йأ������ظ�����
};


// ˮƽ/��ֱ�����ƣ��̶����ش�С��Ҫ���ı���Ϊ��λ�ı��Σ�ע�⣺���಻��������ȫ�����ƣ�
class VBF_GLAUX_EXPORT CVBF_SGNodeBillboardWithFixedPixels : public CVBF_SGNodeBillboard
{
private:
    typedef CVBF_SGNodeBillboard BaseClass;

public:
    CVBF_SGNodeBillboardWithFixedPixels() {}
    CVBF_SGNodeBillboardWithFixedPixels(IVBF_SGNodeBillboardCallback* pICallback, float fWidth, float fHeight);
    CVBF_SGNodeBillboardWithFixedPixels(const CVBF_SGNodeBillboardWithFixedPixels&, const CopyOp& copyop=CopyOp::SHALLOW_COPY) {}

    META_Node(VBF, CVBF_SGNodeBillboardWithFixedPixels)

    // ���غ���������ĳ��Drawable�Ĳ����ƾ���
    virtual bool computeMatrix(Matrix& modelview, const Vec3& eye_local, const Vec3& pos_local) const;

private:

    // ��ʾ�ֱ��ʵ�������ֻ��������ӿ��йأ�ÿ֡����һ�μ��ɣ�
    mutable osg::Vec4   m_vPixelSize;           // ��λ����/����

    float           m_fWidthInPixels;       // ��ȣ���λ�����أ�
    float           m_fHeightInPixels;      // �߶ȣ���λ�����أ�
    mutable float   m_fWidthInMeters;       // ��ȣ���λ���ף�
    mutable float   m_fHeightInMeters;      // �߶ȣ���λ���ף�
};


// Ҷ�ڵ㣺�̶����ش�С��Ҫ���ı���Ϊ��λ�ı���
class VBF_GLAUX_EXPORT CVBF_SGGeodeWithFixedPixels : public CVBF_SGNodeBillboard
{
private:
    typedef CVBF_SGNodeBillboard BaseClass;

public:
    CVBF_SGGeodeWithFixedPixels() {}
    CVBF_SGGeodeWithFixedPixels(IVBF_SGNodeBillboardCallback* pICallback, float fWidth, float fHeight);
    CVBF_SGGeodeWithFixedPixels(const CVBF_SGGeodeWithFixedPixels&, const CopyOp& copyop=CopyOp::SHALLOW_COPY) {}

    META_Node(VBF, CVBF_SGGeodeWithFixedPixels)

    // ���غ���������ĳ��Drawable�Ĳ����ƾ���
    virtual bool computeMatrix(Matrix& modelview, const Vec3& eye_local, const Vec3& pos_local) const;

private:

    // ��ʾ�ֱ��ʵ�������ֻ��������ӿ��йأ�ÿ֡����һ�μ��ɣ�
    mutable osg::Vec4   m_vPixelSize;           // ��λ����/����

    float               m_fWidthInPixels;       // ��ȣ���λ�����أ�
    float               m_fHeightInPixels;      // �߶ȣ���λ�����أ�
    mutable float       m_fWidthInMeters;       // ��ȣ���λ���ף�
    mutable float       m_fHeightInMeters;      // �߶ȣ���λ���ף�
};



#endif
