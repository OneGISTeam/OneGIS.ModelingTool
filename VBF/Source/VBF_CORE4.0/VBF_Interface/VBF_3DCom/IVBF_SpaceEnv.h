#ifndef __IVBF_SPACEENV_H__
#define __IVBF_SPACEENV_H__

#include <Types/Vec3d>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <VBF_3DCom/IVBF_SpaceBase.h>

// 定义该组件的ID号
const char VBF_COMPONENT_SPACEENV[]	= "Component: SpaceEnv";

// 定义模块中专有接口的ID号
const char VBF_INTERFACE_SPACEENV[]	= "空间环境";

namespace osg
{
	class Light;
}

class IVBF_SpaceEnv
{
public:	
	virtual ~IVBF_SpaceEnv() {}

	// 设置/获取是否开启空间环境
	virtual void Enable(bool bEnable)=0;
	virtual bool IsEnabled()=0;

	virtual int GetCenterObjectIdx()=0;
	virtual void SetCenterObject(int idxObject)=0;      // 设置中心天体
	virtual osg::IVBF_SGNodeGroup* GetSpaceObjectNode(int idxObject)=0;   // 获取天体的场景图节点
	virtual void Advance(double dSeconds)=0; // 时钟走X秒
	virtual const osg::Matrix& getEarthRotation() const=0; // 获取地球的旋转矩阵
	virtual const osg::Matrix& getRotation(int planet) const=0; // 获取星球的旋转矩阵
	virtual void setMatrix(const osg::Matrix& mat)=0;
	virtual double GetEpoch()=0;
	virtual void SetEpoch(double JD)=0;
	virtual void SetEpoch(int nYear,  int nMonth,  int nDay,  int nHour = 12, int nMinute = 0, double dSecond = 0)=0;
	virtual void GetEpoch(int& nYear, int& nMonth, int& nDay, int& nHour, int& nMinute, double& dSecond)=0;

	// 获取/设置sun light
	virtual osg::Light *getSunLight() const=0;
	virtual void setSunLight(osg::Light *light)=0;

	virtual float GetPlanetMajorRadius(int idx)=0; // 获取行星长半径（包括月球）
	virtual float GetPlanetMinorRadius(int idx)=0; // 获取行星短半径（包括月球）
	virtual osg::Vec3 GetCentralPosition()=0;    // 获取中心天体的位置

	virtual const char* GetCenterObjectName(int idxObject)=0;//

	virtual IVBF_SpaceOption* GetDefaultSpaceOption()=0;
};

#endif 
