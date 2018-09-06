//*******************************************************************
// FileName��IVBF_MarkProcessMove.h
// Function���˶����̣�����У�
// Author:   �����
// Date:     2010-9-20
//*******************************************************************

#ifndef __IVBF_MARK_PROCESS_MOVE_H__
#define __IVBF_MARK_PROCESS_MOVE_H__


#include "VBF_Plot/IVBF_MarkProTimerTrigger.h"
#include <vector>
#include <Types/Vec3d>

#define VBF_MARK_PROCESS_MOVE        "PathMove"      // ·���˶�
#define VBF_MARK_PROCESS_MOVESIX     "PathMoveSix"   // �����ɶ�·���˶�


class IVBF_MarkProcessMove : public IVBF_MarkProTimerTrigger
{
public:
    virtual ~IVBF_MarkProcessMove() {}

    // ����/��ȡ·�����괮(ע�⣺��Ҫ��AddMarkProcess֮����ã�������Ч��)
    virtual void SetPath(const std::vector<osg::Vec3d>& vGeo,bool bNeedSmooth=false,int numInterPoints=0)=0;
    virtual const std::vector<osg::Vec3d>&  GetPath()=0;
};


#endif 
