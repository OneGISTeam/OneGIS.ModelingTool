//*******************************************************************
// FileName：VBF_SatelliteMath.h
// Function：与卫星及其轨道有关的算法
// Author:   杜莹
// Date:     2013-12-31
//*******************************************************************

#ifndef __VBF_SATELLITE_MATH_H__
#define __VBF_SATELLITE_MATH_H__


#include <VBF_Common/VBF_Math/VBF_ConstEarth.h>
#include <VBF_Common/VBF_Math/VBF_Math.h>


// 轨道点数据
struct VBF_ORBITDATA
{
        osg::Vec3d		vEciPt;		// 地惯坐标系下位置矢量
        osg::Vec3d		vEciVel;	// 地惯坐标系下位置的各方向的速度矢量
        double			dTime;
};

static double dBiasNearPoint = 0.0;

//-------------------------------------------------------------------------------
// 内联函数：Position_Velocity()
// 函数描述：根据轨道根数和平近点角，计算位置矢量和速度矢量
// 参数说明：dBeginTime的时间单位为秒
//-------------------------------------------------------------------------------
inline void Position_Velocity(const VBF_ORBIT_ELEMENTS& orbit, double dFlatPerigee, osg::Vec3d& vPt, osg::Vec3d& vVelocity)
{
	double da = orbit.da;		// 半长轴
	double de = orbit.de;		// 偏心率

	double dIncl = osg::DegreesToRadians(orbit.dIncl);	// 轨道倾角
	double dRAAN = osg::DegreesToRadians(orbit.dRAAN);	// 升交点赤经	
	double dw	 = osg::DegreesToRadians(orbit.dw);		// 近地点幅角
	
	// dBiasPerigee偏近点角
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
	
        double dSinTruePerigee   = sqrt(1-pow(de,2))*sin(dBiasPerigee)/(1-de*cos(dBiasPerigee)); //计算sin(真近点角)？ ff
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
// 内联函数：VBF_ComputeOrbitData()
// 函数描述：根据卫星轨道参数和仿真时间，计算轨道数据
// 参数说明：dBeginTime的时间单位为秒
//-------------------------------------------------------------------------------
inline bool VBF_ComputeOrbitData(const VBF_ORBIT_ELEMENTS& orbit, double dBeginTime, double dEndTime, double dTimeStep, std::vector<VBF_ORBITDATA>& vOrbitData)
{               
	// 轨道根数，为了书写方便
	const double da	 = orbit.da;	// 半长轴
	const double dTA = orbit.dTA;	// 过近地点时刻

	// 常量，避免重复计算
	const double dSqrt = sqrt( dmu/pow(da, 3) );

	// 一定轨道周期下的步数
	int num = int( (dEndTime-dBeginTime)/dTimeStep );
	vOrbitData.resize(num);

	double dTimeCurr = 0.0; // 当前位置时间	

	for(int i=0; i <num; i++) 
	{
		double dTime = dTimeCurr + dBeginTime;
		vOrbitData[i].dTime = dTime;

	//	dTime = dTimeCurr + (dBeginTime-int(dBeginTime))*3600*24;

		osg::Vec3d& vEciPt  = vOrbitData[i].vEciPt;
		osg::Vec3d& vEciVel = vOrbitData[i].vEciVel;
		
		// 平近点角（虚拟圆上的位置点、近地点、地心三者在地心构成的夹角，单位：弧度）
	    // 在轨道力学中，是轨道上的物体在辅助圆上相对于中心点的运行角度，与时间的关系是线性的
       	double dFlatPerigee = dSqrt * (dTime-dTA);  // 问题：dTA如何计算得来?
		
		Position_Velocity(orbit, dFlatPerigee, vEciPt, vEciVel);
		
		// 当导弹位置离地心距离小于6356时，函数退出
		if( vEciPt.length() < 6378.145 )
		{
			std::cout << "不能构造轨道!" << std::endl;
			return false;
		}
		
                // 计算地惯坐标系下的向量
		vEciPt  *= 1000.0;	// 位置（单位：m）
		vEciVel *= 1000.0;	// 速度（单位：m/s）
		
		dTimeCurr += dTimeStep;
	}	

	return true;
}

//-------------------------------------------------------------------------------
// 内联函数：VBF_ComputeOrbitPeriod()
// 函数描述：根据卫星轨道参数，计算轨道周期
// 参数说明：orbit:轨道六根数
//-------------------------------------------------------------------------------
inline double VBF_ComputeOrbitPeriod(const VBF_ORBIT_ELEMENTS& orbit)
{
    const double da	 = orbit.da;	// 半长轴

    const double dSqrt = sqrt( dmu/pow(da, 3) );

    double dPeriod = 2*dpi/dSqrt;

    return dPeriod;
}


//-------------------------------------------------------------------------------
// 内联函数：VBF_ComputePerigeeAndApogee()
// 函数描述：根据卫星轨道参数，计算近地点和远地点
// 参数说明：orbit:轨道六根数
//-------------------------------------------------------------------------------
inline bool VBF_ComputePerigeeAndApogee(const VBF_ORBIT_ELEMENTS& orbit, double dBeginTime,
                                        osg::Vec3d& vtPerigee, osg::Vec3d& vtApogee)
{
    // 用平近点角0度和180度来计算近地点和远地点
    for(int i=0; i<2; i++)
    {
        double dFlatPerigee = i*PI;

        osg::Vec3d vEciPt, vEciVel;
        Position_Velocity(orbit, dFlatPerigee, vEciPt, vEciVel);

        // 地惯系下，单位为m
        vEciPt  *= 1000.0;	// 位置（单位：m）
        vEciVel *= 1000.0;	// 速度（单位：m/s）

        if(i==0) vtPerigee = vEciPt;
        else vtApogee = vEciPt;
    }

    return true;
}

#endif
