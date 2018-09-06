//*******************************************************************
// FileName��VBF_SatelliteMath.h
// Function�������Ǽ������йص��㷨
// Author:   ��Ө
// Date:     2013-12-31
//*******************************************************************

#ifndef __VBF_SATELLITE_MATH_H__
#define __VBF_SATELLITE_MATH_H__


#include <VBF_Common/VBF_Math/VBF_ConstEarth.h>
#include <VBF_Common/VBF_Math/VBF_Math.h>


// ���������
struct VBF_ORBITDATA
{
        osg::Vec3d		vEciPt;		// �ع�����ϵ��λ��ʸ��
        osg::Vec3d		vEciVel;	// �ع�����ϵ��λ�õĸ�������ٶ�ʸ��
        double			dTime;
};

static double dBiasNearPoint = 0.0;

//-------------------------------------------------------------------------------
// ����������Position_Velocity()
// �������������ݹ��������ƽ����ǣ�����λ��ʸ�����ٶ�ʸ��
// ����˵����dBeginTime��ʱ�䵥λΪ��
//-------------------------------------------------------------------------------
inline void Position_Velocity(const VBF_ORBIT_ELEMENTS& orbit, double dFlatPerigee, osg::Vec3d& vPt, osg::Vec3d& vVelocity)
{
	double da = orbit.da;		// �볤��
	double de = orbit.de;		// ƫ����

	double dIncl = osg::DegreesToRadians(orbit.dIncl);	// ������
	double dRAAN = osg::DegreesToRadians(orbit.dRAAN);	// ������ྭ	
	double dw	 = osg::DegreesToRadians(orbit.dw);		// ���ص����
	
	// dBiasPerigeeƫ�����
	double dBiasPerigee = dFlatPerigee + (de - pow(de,3)/8)*sin(dFlatPerigee) + 1/2*(de*de)*sin(2*dFlatPerigee) + 3/8.*pow(de,3)*sin(3*dFlatPerigee);
	
	while(1)
	{
		dBiasNearPoint = dBiasPerigee - (dBiasPerigee-de*sin(dBiasPerigee)-dFlatPerigee)/(1-de*cos(dBiasPerigee));
		if((dBiasNearPoint-dBiasPerigee) < 0.000000001)
		{
			dBiasPerigee = dBiasNearPoint;
			break;
		}
		dBiasPerigee = dBiasNearPoint;
	}
	
	double dSinIncl = sin(dIncl);
	double dCosIncl = cos(dIncl);
	double dSinRAAN = sin(dRAAN);
	double dCosRAAN = cos(dRAAN);
	double dSinW    = sin(dw);
	double dCosW    = cos(dw);
	
        double dSinTruePerigee   = sqrt(1-pow(de,2))*sin(dBiasPerigee)/(1-de*cos(dBiasPerigee)); //����sin(������)�� ff
	double dCosTruePerigee   = (cos(dBiasPerigee)-de)/(1-de*cos(dBiasPerigee));
	double dCosAngleDistance = dCosW*dCosTruePerigee - dSinW*dSinTruePerigee;
	double dSinAngleDistance = dSinW*dCosTruePerigee + dCosW*dSinTruePerigee;
	
	double dOrbitRadius = da*(1-pow(de, 2)) / (1+de*dCosTruePerigee);
	vPt.x() = dOrbitRadius*(dCosRAAN*dCosAngleDistance-dSinRAAN*dSinAngleDistance*dCosIncl);
	vPt.y() = dOrbitRadius*(dSinRAAN*dCosAngleDistance+dCosRAAN*dSinAngleDistance*dCosIncl);
	vPt.z() = dOrbitRadius*dSinAngleDistance*dSinIncl;
	
	double dPositionSpeed = sqrt(dmu/da/(1-pow(de,2)));
	vVelocity.x() = -dPositionSpeed*dSinTruePerigee*(dCosW*dCosRAAN-dSinW*dSinRAAN* dCosIncl) 
						+ dPositionSpeed*(de+dCosTruePerigee)*(-dSinW*dCosRAAN- dCosW*dSinRAAN*dCosIncl);
	vVelocity.y() = -dPositionSpeed*dSinTruePerigee*(dCosW*dSinRAAN+dSinW*dCosRAAN*dCosIncl) 
						+ dPositionSpeed*(de+dCosTruePerigee)*(-dSinW*dSinRAAN+ dCosW*dCosRAAN*dCosIncl);
	vVelocity.z() = -dPositionSpeed*dSinTruePerigee*(dSinW*dSinIncl) + dPositionSpeed* (de+dCosTruePerigee)*(dCosW*dSinIncl);
}

//-------------------------------------------------------------------------------
// ����������VBF_ComputeOrbitData()
// �����������������ǹ�������ͷ���ʱ�䣬����������
// ����˵����dBeginTime��ʱ�䵥λΪ��
//-------------------------------------------------------------------------------
inline bool VBF_ComputeOrbitData(const VBF_ORBIT_ELEMENTS& orbit, double dBeginTime, double dEndTime, double dTimeStep, std::vector<VBF_ORBITDATA>& vOrbitData)
{               
	// ���������Ϊ����д����
	const double da	 = orbit.da;	// �볤��
	const double dTA = orbit.dTA;	// �����ص�ʱ��

	// �����������ظ�����
	const double dSqrt = sqrt( dmu/pow(da, 3) );

	// һ����������µĲ���
	int num = int( (dEndTime-dBeginTime)/dTimeStep );
	vOrbitData.resize(num);

	double dTimeCurr = 0.0; // ��ǰλ��ʱ��	

	for(int i=0; i <num; i++) 
	{
		double dTime = dTimeCurr + dBeginTime;
		vOrbitData[i].dTime = dTime;

	//	dTime = dTimeCurr + (dBeginTime-int(dBeginTime))*3600*24;

		osg::Vec3d& vEciPt  = vOrbitData[i].vEciPt;
		osg::Vec3d& vEciVel = vOrbitData[i].vEciVel;
		
		// ƽ����ǣ�����Բ�ϵ�λ�õ㡢���ص㡢���������ڵ��Ĺ��ɵļнǣ���λ�����ȣ�
	    // �ڹ����ѧ�У��ǹ���ϵ������ڸ���Բ����������ĵ�����нǶȣ���ʱ��Ĺ�ϵ�����Ե�
       	double dFlatPerigee = dSqrt * (dTime-dTA);  // ���⣺dTA��μ������?
		
		Position_Velocity(orbit, dFlatPerigee, vEciPt, vEciVel);
		
		// ������λ������ľ���С��6356ʱ�������˳�
		if( vEciPt.length() < 6378.145 )
		{
			std::cout << "���ܹ�����!" << std::endl;
			return false;
		}
		
                // ����ع�����ϵ�µ�����
		vEciPt  *= 1000.0;	// λ�ã���λ��m��
		vEciVel *= 1000.0;	// �ٶȣ���λ��m/s��
		
		dTimeCurr += dTimeStep;
	}	

	return true;
}

//-------------------------------------------------------------------------------
// ����������VBF_ComputeOrbitPeriod()
// �����������������ǹ������������������
// ����˵����orbit:���������
//-------------------------------------------------------------------------------
inline double VBF_ComputeOrbitPeriod(const VBF_ORBIT_ELEMENTS& orbit)
{
    const double da	 = orbit.da;	// �볤��

    const double dSqrt = sqrt( dmu/pow(da, 3) );

    double dPeriod = 2*dpi/dSqrt;

    return dPeriod;
}


//-------------------------------------------------------------------------------
// ����������VBF_ComputePerigeeAndApogee()
// �����������������ǹ��������������ص��Զ�ص�
// ����˵����orbit:���������
//-------------------------------------------------------------------------------
inline bool VBF_ComputePerigeeAndApogee(const VBF_ORBIT_ELEMENTS& orbit, double dBeginTime,
                                        osg::Vec3d& vtPerigee, osg::Vec3d& vtApogee)
{
    // ��ƽ�����0�Ⱥ�180����������ص��Զ�ص�
    for(int i=0; i<2; i++)
    {
        double dFlatPerigee = i*PI;

        osg::Vec3d vEciPt, vEciVel;
        Position_Velocity(orbit, dFlatPerigee, vEciPt, vEciVel);

        // �ع�ϵ�£���λΪm
        vEciPt  *= 1000.0;	// λ�ã���λ��m��
        vEciVel *= 1000.0;	// �ٶȣ���λ��m/s��

        if(i==0) vtPerigee = vEciPt;
        else vtApogee = vEciPt;
    }

    return true;
}

#endif
