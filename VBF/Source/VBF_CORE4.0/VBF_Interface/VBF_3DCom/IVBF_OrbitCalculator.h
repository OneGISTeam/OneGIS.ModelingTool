#ifndef __IVBF_ORBIT_CALCULATOR_H__
#define __IVBF_ORBIT_CALCULATOR_H__

#include "VBF_Base/VBF_Referenced.h"
#include <Types/Vec3d>

// ����������ӿ�
class IVBF_OrbitCalculator: public CVBF_Referenced
{
public:
    // �������ʱ��Ĺ��λ�ú��ٶȣ���tΪʱ�䣩
    virtual int getOrbitPV(double t, osg::Vec3d& pos, osg::Vec3d& vel) = 0;
    virtual double getEpoch() const=0;// ��ȡ��Ԫ��ʱ�䣩�������ݵ���ʼʱ��
    virtual const char* getSscID() const=0;// ��ȡ���ǵı��
};
#endif 
