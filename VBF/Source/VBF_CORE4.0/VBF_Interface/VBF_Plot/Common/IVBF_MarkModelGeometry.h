//*******************************************************************
// FileName��IVBF_MarkModelGeometry.h
// Function��ʵ��ģ�ͽӿڣ������򼸺���
// Author:   ��Ө
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
// ����ö�٣�EVBF_ATTRBIND_TYPE
// ö��������������������ԣ����㡢��ɫ���������ߡ�ͼԪ�ȣ��İ󶨷�ʽ
//--------------------------------------------------------------------
enum EVBF_ATTRBIND_TYPE
{
    VBF_ATTRBIND_OFF        = 0,	// �����ð�
    VBF_ATTRBIND_OVERALL,			// ��ȫ������
    VBF_ATTRBIND_PER_PRIMITIVE_SET,	// ������ͼ��Ԫ��ͼԪ����
    VBF_ATTRBIND_PER_PRIMITIVE,		// ����������ͼԪ��
    VBF_ATTRBIND_PER_VERTEX			// ���������
};


class IVBF_MarkModelGeometry : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelGeometry() {}

    // ����/��ȡ�����������飨�������꣩
    virtual void                    SetVertexArrayGeo(const std::vector<osg::Vec3d>& vPointsGeo)=0;
    virtual std::vector<osg::Vec3d> GetVertexArrayGeo()=0;

    // ����/��ȡ��������ɫ����
    virtual void                    SetColorArray(const std::vector<osg::Vec4f>& vColors)=0;
    virtual std::vector<osg::Vec4f> GetColorArray()=0;

    // ����/��ȡ��������ɫ�����붥��󶨷�ʽ��Ĭ��ֵΪVBF_ATTRBIND_PER_VERTEX��
    virtual void                SetColorBinding(EVBF_ATTRBIND_TYPE nBindType)=0;
    virtual EVBF_ATTRBIND_TYPE  GetColorBinding()=0;

    // ����/��ȡ���㸨��ɫ����
    virtual void                    SetSecondaryColorArray(const std::vector<osg::Vec4f>& vColors)=0;
    virtual std::vector<osg::Vec4f> GetSecondaryColorArray()=0;

    // ����/��ȡ���㸨��ɫ�����붥��󶨷�ʽ��Ĭ��ֵΪVBF_ATTRBIND_PER_VERTEX��
    virtual void                SetSecondaryColorBinding(EVBF_ATTRBIND_TYPE nBindType)=0;
    virtual EVBF_ATTRBIND_TYPE  GetSecondaryColorBinding()=0;

    // ����/��ȡ���㷨������
    virtual void                    SetNormalArray(const std::vector<osg::Vec3f>& vNormals)=0;
    virtual std::vector<osg::Vec3f> GetNormalArray()=0;

    // ����/��ȡ���㷨�������붥��󶨷�ʽ��Ĭ��ֵΪVBF_ATTRBIND_PER_VERTEX��
    virtual void                SetNormalBinding(EVBF_ATTRBIND_TYPE nBindType)=0;
    virtual EVBF_ATTRBIND_TYPE  GetNormalBinding()=0;

    // ��ȡ�����������������
    virtual int GetNumTexCoordArrays()=0;

    // ����/��ȡ��n���������������
    virtual void SetTexCoordArray(unsigned int nTexUnit, const std::vector<osg::Vec2f>& vTexCoords)=0;
    virtual bool GetTexCoordArray(unsigned int nTexUnit, std::vector<osg::Vec2f>& vTexCoords)=0;

    // ����/��ȡ��n����������������붥��󶨷�ʽ��Ĭ��ֵΪVBF_ATTRBIND_PER_VERTEX��
    virtual void SetTexCoordArrayBinding(unsigned int nTexUnit, EVBF_ATTRBIND_TYPE nBindType)=0;
    virtual bool GetTexCoordArrayBinding(unsigned int nTexUnit, EVBF_ATTRBIND_TYPE& nBindType)=0;

	// ����/��ȡ��n�������ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void		SetTexImage(unsigned int nTexUnit, osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage(unsigned int nTexUnit)=0;

    // ����/��ȡ�Ƿ���Ҫ�ü�������
    virtual void SetCullBack(bool bCull)=0;
    virtual bool IsCullBack()=0;

    // �Ƿ�/��ȡ���涥�������˳���Ƿ�Ϊ��ʱ��
    virtual void SetFrontCCW(bool bCCW)=0;
    virtual bool IsFrontCCW()=0;

    // ����е�״ͼԪ�����õ�Ĵ�С��Ĭ��ֵΪ1.0��
    virtual void  SetPointSize(float fSize)=0;
    virtual float GetPointSize()=0;

    // �������״ͼԪ�������߿�Ĭ��ֵΪ1.0��
    virtual void  SetLineWidth(float fWidth)=0;
    virtual float GetLineWidth()=0;

    // �Ƿ���Ҫ��ϵͳ�ڲ����¼��㷨�ߣ�Ĭ��ֵΪfalse��
    virtual void SetRecomputeNormal(bool bRecompute)=0;
    virtual bool IsRecomputeNormal()=0;

    // ���һ��ͼԪ����ʹ�ö���������
    // ������nMode  -- ͼԪ���ͣ���GL_POINTS, GL_TRIANGLES, GL_QUADS�ȵ�
    //      nVertexFirst -- �������ͼԪ�Ķ�����ʼ������
    //      nVertexCount -- �������ͼԪ�Ķ������
    virtual void AddPrimitiveSet(unsigned int nMode, int nVertexFirst, int nVertexCount)=0;

    // ���һ��ͼԪ��ʹ�ö���������
    // ������nMode  -- ͼԪ���ͣ���GL_POINTS, GL_TRIANGLES, GL_QUADS�ȵ�
    //      vIndices -- �������ͼԪ�Ķ����������
    virtual void AddPrimitiveSetIndexed(unsigned int nMode, const std::vector<unsigned int>& vIndices)=0;

    // ��ȡͼԪ����
    virtual int GetNumPrimitiveSets()=0;
};

#endif 
