#ifndef __IVBF_SPACE_OBJECT_H__
#define __IVBF_SPACE_OBJECT_H__

#include <Types/Vec3d>
#include <Types/Vec4>
#include <VBF_3DCom/IVBF_OrbitCalculator.h>
#include <string>
// 定义模块中专有接口的ID号
const char VBF_INTERFACE_SPACEOBJECT[]	= "空间对象";

class IVBF_SpaceObjectManager : public CVBF_Referenced
{
public:
    virtual void SetVisible(bool bVisible)=0;

    virtual bool readFromTLE(const std::string& sFn)=0; // 从TLE文件中读取对象列表
    virtual bool LoadScenario(const std::string& sFn)=0;// 加载方案
    virtual void SetCurrentID(int sscID)=0;             // 设置当前目标
    virtual void LoadGroundPoint()=0;                   // 加载地面点

    // 显示2D图
    virtual void Show2D(bool bShow = true,int x=200,int y=30,int nWidth=600,int nHeight=300)=0;
    virtual void Show3D(bool bShow)=0;

    virtual void UpdateTimer(double dUtcEpoch)=0;

    // 显示卫星覆盖区、覆盖区边界、星下点轨迹
    virtual void ShowCover(int sscID,bool bShow)=0;
    virtual void ShowCoverBound(int sscID,bool bShow)=0;
    virtual void ShowOrbitECF(int sscID,bool bShow)=0;
    virtual void ShowOrbitECI(int id,bool bShow)=0;

    virtual void showDebrisAll(bool s)=0;     // 显示所有碎片
    virtual void showDebrisRed(bool s)=0;     // 显示红方碎片
    virtual void showDebrisBlue(bool s)=0;    // 显示蓝方碎片
    virtual void showDebrisGreen(bool s)=0;   // 显示绿方碎片
    virtual void showDebrisWhite(bool s)=0;   // 显示白方碎片

    virtual void showTargetHud(bool s)=0;
    virtual void showTextBar(bool s)=0;
    virtual void ClearScenario()=0; // 清除方案

    // 设置目标轨道计算器
    virtual void SetObjectOrbitCalculator(int sscID,IVBF_OrbitCalculator* pIOrbitCalculator)=0;

	class CVBF_SatelliteData
	{   
	public:
        std::string intid;      // 卫星编号（国际编号）
		int sscid;          // 卫星编号（NORAD编号）
        std::string owner;      // 卫星所属
        std::string name;       // 卫星名称

        // 轨道的形状参数
        double			da;			// 半长轴（轨道的形状参数，单位：公里）
        double			de;			// 偏心率（轨道的形状参数）
        // 轨道的位置参数
        double			dIncl;		// 轨道倾角（轨道与赤道面的二面角，单位：角度）
        double			dRAAN;		// 升交点赤经（春分点、地心、升交点三者在地心构成的夹角，单位：角度）
        double			dw;			// 近地点幅角（轨道近地点、地心、升交点三者在地心构成的夹角，单位：角度）
        // 卫星在轨道上的位置
        double			dTA;		// 过近地点时刻（儒略日，单位：天）

        // 下面的参数可以不赋值
		double perigee;     // 近地点高度（公里）
		double apogee;      // 远地点高度（公里）
		double period;      // 轨道周期（分钟）
		double rcs;         // RCS
	};
    virtual void AddSpaceObject(const CVBF_SatelliteData& stSatData,IVBF_OrbitCalculator* pIOrbitCalculator=NULL,bool bShowECI=true,bool bShowECF=false,bool bShowCover=false)=0;
    virtual void AddSpaceObject(const CVBF_SatelliteData& stSatData,std::string& strFileNameOrbitData,bool bShowECI=true,bool bShowECF=false,bool bShowCover=false)=0;


    virtual void setCurrentTarget(int oldID, int newID)=0;// 设置当前目标
    virtual void SetDetectAngle(int id,double dAngleRad)=0;
    virtual void SetColor(int id,const osg::Vec4& color)=0;
};

#endif 
