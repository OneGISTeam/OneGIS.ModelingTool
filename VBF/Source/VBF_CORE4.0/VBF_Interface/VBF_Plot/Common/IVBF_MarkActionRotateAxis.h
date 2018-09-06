//*******************************************************************
// FileName��IVBF_MarkActionRotateAxis.h
// Function��ģ����Ϊ�ӿڣ���ĳ��֧�㴦������ת���磺�ɻ���������ת����
// Author:
// Date:     2017-12-28
//*******************************************************************

#ifndef __IVBF_MARK_ACTION_ROTATEAXIS_H__
#define __IVBF_MARK_ACTION_ROTATEAXIS_H__


#include <VBF_Plot/IVBF_MarkAction.h>
#include <Types/VBF_3DStyles.h>


class IVBF_MarkActionRotateAxis : public IVBF_MarkAction
{
public:
    virtual ~IVBF_MarkActionRotateAxis() {}
    virtual void SetPivot(const osg::Vec3d& vPivot)=0; // ֧��
    virtual void SetAxis(const osg::Vec3d& vAxis)=0; // ��ת��
    virtual void SetSpeed(float fSpeed)=0; // ��ת�ٶȣ���λ����/�룩

};


#endif 
