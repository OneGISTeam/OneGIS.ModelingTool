#ifndef __IVBF_SPACEENV_H__
#define __IVBF_SPACEENV_H__

#include <Types/Vec3d>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <VBF_3DCom/IVBF_SpaceBase.h>

// ����������ID��
const char VBF_COMPONENT_SPACEENV[]	= "Component: SpaceEnv";

// ����ģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_SPACEENV[]	= "�ռ价��";

namespace osg
{
	class Light;
}

class IVBF_SpaceEnv
{
public:	
	virtual ~IVBF_SpaceEnv() {}

	// ����/��ȡ�Ƿ����ռ价��
	virtual void Enable(bool bEnable)=0;
	virtual bool IsEnabled()=0;

	virtual int GetCenterObjectIdx()=0;
	virtual void SetCenterObject(int idxObject)=0;      // ������������
	virtual osg::IVBF_SGNodeGroup* GetSpaceObjectNode(int idxObject)=0;   // ��ȡ����ĳ���ͼ�ڵ�
	virtual void Advance(double dSeconds)=0; // ʱ����X��
	virtual const osg::Matrix& getEarthRotation() const=0; // ��ȡ�������ת����
	virtual const osg::Matrix& getRotation(int planet) const=0; // ��ȡ�������ת����
	virtual void setMatrix(const osg::Matrix& mat)=0;
	virtual double GetEpoch()=0;
	virtual void SetEpoch(double JD)=0;
	virtual void SetEpoch(int nYear,  int nMonth,  int nDay,  int nHour = 12, int nMinute = 0, double dSecond = 0)=0;
	virtual void GetEpoch(int& nYear, int& nMonth, int& nDay, int& nHour, int& nMinute, double& dSecond)=0;

	// ��ȡ/����sun light
	virtual osg::Light *getSunLight() const=0;
	virtual void setSunLight(osg::Light *light)=0;

	virtual float GetPlanetMajorRadius(int idx)=0; // ��ȡ���ǳ��뾶����������
	virtual float GetPlanetMinorRadius(int idx)=0; // ��ȡ���Ƕ̰뾶����������
	virtual osg::Vec3 GetCentralPosition()=0;    // ��ȡ���������λ��

	virtual const char* GetCenterObjectName(int idxObject)=0;//

	virtual IVBF_SpaceOption* GetDefaultSpaceOption()=0;
};

#endif 
