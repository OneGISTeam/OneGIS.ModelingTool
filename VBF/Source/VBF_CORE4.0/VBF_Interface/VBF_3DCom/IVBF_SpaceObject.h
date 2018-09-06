#ifndef __IVBF_SPACE_OBJECT_H__
#define __IVBF_SPACE_OBJECT_H__

#include <Types/Vec3d>
#include <Types/Vec4>
#include <VBF_3DCom/IVBF_OrbitCalculator.h>
#include <string>
// ����ģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_SPACEOBJECT[]	= "�ռ����";

class IVBF_SpaceObjectManager : public CVBF_Referenced
{
public:
    virtual void SetVisible(bool bVisible)=0;

    virtual bool readFromTLE(const std::string& sFn)=0; // ��TLE�ļ��ж�ȡ�����б�
    virtual bool LoadScenario(const std::string& sFn)=0;// ���ط���
    virtual void SetCurrentID(int sscID)=0;             // ���õ�ǰĿ��
    virtual void LoadGroundPoint()=0;                   // ���ص����

    // ��ʾ2Dͼ
    virtual void Show2D(bool bShow = true,int x=200,int y=30,int nWidth=600,int nHeight=300)=0;
    virtual void Show3D(bool bShow)=0;

    virtual void UpdateTimer(double dUtcEpoch)=0;

    // ��ʾ���Ǹ��������������߽硢���µ�켣
    virtual void ShowCover(int sscID,bool bShow)=0;
    virtual void ShowCoverBound(int sscID,bool bShow)=0;
    virtual void ShowOrbitECF(int sscID,bool bShow)=0;
    virtual void ShowOrbitECI(int id,bool bShow)=0;

    virtual void showDebrisAll(bool s)=0;     // ��ʾ������Ƭ
    virtual void showDebrisRed(bool s)=0;     // ��ʾ�췽��Ƭ
    virtual void showDebrisBlue(bool s)=0;    // ��ʾ������Ƭ
    virtual void showDebrisGreen(bool s)=0;   // ��ʾ�̷���Ƭ
    virtual void showDebrisWhite(bool s)=0;   // ��ʾ�׷���Ƭ

    virtual void showTargetHud(bool s)=0;
    virtual void showTextBar(bool s)=0;
    virtual void ClearScenario()=0; // �������

    // ����Ŀ����������
    virtual void SetObjectOrbitCalculator(int sscID,IVBF_OrbitCalculator* pIOrbitCalculator)=0;

	class CVBF_SatelliteData
	{   
	public:
        std::string intid;      // ���Ǳ�ţ����ʱ�ţ�
		int sscid;          // ���Ǳ�ţ�NORAD��ţ�
        std::string owner;      // ��������
        std::string name;       // ��������

        // �������״����
        double			da;			// �볤�ᣨ�������״��������λ�����
        double			de;			// ƫ���ʣ��������״������
        // �����λ�ò���
        double			dIncl;		// �����ǣ����������Ķ���ǣ���λ���Ƕȣ�
        double			dRAAN;		// ������ྭ�����ֵ㡢���ġ������������ڵ��Ĺ��ɵļнǣ���λ���Ƕȣ�
        double			dw;			// ���ص���ǣ�������ص㡢���ġ������������ڵ��Ĺ��ɵļнǣ���λ���Ƕȣ�
        // �����ڹ���ϵ�λ��
        double			dTA;		// �����ص�ʱ�̣������գ���λ���죩

        // ����Ĳ������Բ���ֵ
		double perigee;     // ���ص�߶ȣ����
		double apogee;      // Զ�ص�߶ȣ����
		double period;      // ������ڣ����ӣ�
		double rcs;         // RCS
	};
    virtual void AddSpaceObject(const CVBF_SatelliteData& stSatData,IVBF_OrbitCalculator* pIOrbitCalculator=NULL,bool bShowECI=true,bool bShowECF=false,bool bShowCover=false)=0;
    virtual void AddSpaceObject(const CVBF_SatelliteData& stSatData,std::string& strFileNameOrbitData,bool bShowECI=true,bool bShowECF=false,bool bShowCover=false)=0;


    virtual void setCurrentTarget(int oldID, int newID)=0;// ���õ�ǰĿ��
    virtual void SetDetectAngle(int id,double dAngleRad)=0;
    virtual void SetColor(int id,const osg::Vec4& color)=0;
};

#endif 
