//*******************************************************************
// FileName��VBF_TrailPointInner.h
// Function��ģ�����˶������еĹ켣����Ϣ���ڲ�ʹ�ã�������ʱ����Ϣ��
// Author:
// Date:     2009-4-1
//*******************************************************************

#ifndef __VBF_TRAIL_POINT_INNER_H__
#define __VBF_TRAIL_POINT_INNER_H__


#include <VBF_Plot/VBF_3DPlotDataTypes.h>
#include <VBF_Base/VBF_Timer.h>



//--------------------------------------------------------------------------
// ����ṹ�壺VBF_TRAILPOINTINNER
// �ṹ��������ģ�����˶������еĹ켣����Ϣ���ڲ�ʹ�ã�������ʱ����Ϣ��
//--------------------------------------------------------------------------
typedef struct _tagVBFTrailPointInner : public VBF_TRAILPOINT
{
    CVBF_Timer      timer;

    // ���캯��
    _tagVBFTrailPointInner()
    {
        timer.setStartTick();
    }

    // ���캯��
    _tagVBFTrailPointInner(bool bKey, const osg::Vec3d& vGeo, float fRotateX0, float fRotateY0, float fRotateZ0, const std::string& strInfo0="")
        : VBF_TRAILPOINT(bKey, vGeo, fRotateX0, fRotateY0, fRotateZ0, strInfo0)
    {
        timer.setStartTick();
    }

    // �������캯��
    _tagVBFTrailPointInner(const _tagVBFTrailPoint& src)
    {
        *((VBF_TRAILPOINT*)this) = src;
    }

    // ��ֵ�����
    _tagVBFTrailPointInner& operator=(const VBF_TRAILPOINT& src)
    {
        // ��ֹsrc=src�����Ĳ���
        if( this==&src )  return *this;

        *((VBF_TRAILPOINT*)this) = src;
        return *this;
    }

    // ��ֵ�����
    _tagVBFTrailPointInner& operator=(const _tagVBFTrailPointInner& src)
    {
        // ��ֹsrc=src�����Ĳ���
        if( this==&src )  return *this;

        *((VBF_TRAILPOINT*)this) = src;
        this->timer.setStartTick( src.timer.getStartTick() );

        return *this;
    }

} VBF_TRAILPOINTINNER;


#endif 
