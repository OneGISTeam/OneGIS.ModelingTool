#ifndef __IVBF_3DOCEAN_H__
#define __IVBF_3DOCEAN_H__


#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h>
#include <string>
#include <vector>


// ����������ID��
const char VBF_COMPONENT_3DOCEAN[]	= "Component: 3DOcean";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DOCEAN[]	= "��ά����";

// ��������ID��
const char VBF_COMMAND_SHOWDIALOG_OCEAN[] = "Command: Show Dialog Ocean";     // ��ʾ�Ի��򣺵����������


//--------------------------------------------------------------
// ����ṹ�壺CVBF_ShipWakeParameters
// �ṹ����������������
//--------------------------------------------------------------
class CVBF_ShipWakeParameters
{
public:
    double  length;         // β������
    double  beamWidth;      // β����
    double  draft;          // ����
    double  propWashOffset;

    CVBF_ShipWakeParameters()
    {
        length          = 100.0;
        beamWidth       = 20.0;
        draft           = 5.0;
        propWashOffset  = 0.0;
    }
};

class IVBF_RotorWash;
class IVBF_ShipWake;


//--------------------------------------------------------------
// ����ӿڣ�IVBF_3DOcean
// �ӿ���������ά����
//--------------------------------------------------------------
class IVBF_3DOcean : public CVBF_Referenced
{
public:	
    virtual ~IVBF_3DOcean() {}

    // ����/��ȡ�Ƿ�����ά����
    virtual void Enable(bool bEnable)=0;
    virtual bool IsEnabled()=0;

    // ����/��ȡ��ƽ��߶�
    virtual void   SetSeaLevel(double dValue)=0;
    virtual double GetSeaLevel() const=0;

    // ����/��ú�����ӻ��߶�
    virtual void   SetLodHeight(double dValue)=0;
    virtual double GetLodHeight() const=0;

    // ����/��ȡ���٣���λ����/�룩
    virtual void   SetWindSpeed(double dSpeed)=0;  //
    virtual double GetWindSpeed() const=0;

    // ����/��ȡ���򣨵�λ���Ƕȣ�����������ļнǣ�˳ʱ��Ϊ��, 0-360֮����Ч��
    virtual void   SetWindDirection(double dDirection) =0;
    virtual double GetWindDirection() const=0;

    // ��ȡ���ٺͷ���
    virtual void   GetWind(double& dSpeed, double& dDirection) const=0;

    // ����/��ȡˮ��ģ�͵ı��δ�С��ֵԽ�����Խ��Ĭ��ֵΪ0.03��
    virtual void  SetUnderWaterDistortFactor(float fFactor)=0;
    virtual float GetUnderWaterDistortFactor()=0;

    // ����/��ȡˮ�»�ɫ����ԭ����ɫ����ӵĹ�ϵ��Ĭ��ֵΪ(0,0,0)��
    virtual void       SetUnderWaterBlendColor(const osg::Vec3f& color)=0;
    virtual osg::Vec3f GetUnderWaterBlendColor()=0;

    // ����/��ȡ�������������(0=none, 1=full��Ĭ��ֵΪ0.9)
    virtual void  SetSeaFloorTextureIntensity(float value)=0;
    virtual float GetSeaFloorTextureIntensity() const=0;

    // ����/��ȡ�����������ɫ��Ĭ��ֵΪ(0.396, 0.702, 0.843)��
    virtual void       SetSeaFloorTextureColor(const osg::Vec3f& color)=0;
    virtual osg::Vec3f GetSeaFloorTextureColor()=0;

    // ����/��ȡ�Ƿ���ˮ��GodRay��Ĭ��Ϊtrue��
    virtual void EnableGodRays(bool bEnable)=0;
    virtual bool IsGodRaysEnabled()=0;

    // ��������
    virtual IVBF_RotorWash* CreateRotorWash(double pRotorDiameter, bool pSprayEffects=false, bool pUseDecals=false, double pFadeInTime=20)=0;

    // ��������β��
    virtual IVBF_ShipWake*  CreateShipWake(const CVBF_ShipWakeParameters& par)=0;

    // ����ĳ����������꼰����������ȡ�õ�ĺ���ʵʱ�˸߼�������
    // ע�⣺���ص�height+GetSeaLevel() = �߳�ֵ
    virtual bool GetHeight(const osg::Vec3d& point, const osg::Vec3d& direction, float& height, osg::Vec3d& normal,
                           bool visualCorrelation=true, bool includeWakes=true, bool highResolution=true, bool threadSafe=true)=0;

    // ���һ������ڵ�
    virtual void AddReflectionNode(osg::IVBF_SGNode* pNode)=0;

    // ��ȡ����ڵ�
    virtual osg::IVBF_SGNode* GetTritonNode()=0;

    // ��ȡ����Ŀǰ�Ƿ�������ʾ
    virtual bool IsShow() const=0;

    // ��ȡ������������Чֵ��Χ
    virtual double GetLodHeightMin()=0;             // ��ȡ������ӻ��߶���Сֵ����λ���ף�
    virtual double GetLodHeightMax()=0;             // ��ȡ������ӻ��߶����ֵ����λ���ף�
    virtual double GetSeaLevelMin()=0;              // ��ȡ��ƽ����Сֵ����λ���ף�
    virtual double GetSeaLevelMax()=0;              // ��ȡ��ƽ�����ֵ����λ���ף�
    virtual double GetWindSpeedMin()=0;             // ��ȡ������Сֵ����λ����/�룩
    virtual double GetWindSpeedMax()=0;             // ��ȡ�������ֵ����λ����/�룩
    virtual double GetWindDirectionMin()=0;         // ��ȡ������Сֵ����λ���Ƕȣ�������������ļн�
    virtual double GetWindDirectionMax()=0;         // ��ȡ�������ֵ����λ���Ƕȣ�
    virtual float  GetUnderWaterDistortMin()=0;     // ��ȡˮ�±�����Сֵ
    virtual float  GetUnderWaterDistortMax()=0;     // ��ȡˮ�±������ֵ

    // �������ò����Ĵ��л�
    virtual bool AddConfig(std::string strConfigName)=0;     // ���һ�����÷���
    virtual void DeleteConfig(std::string strConfigName)=0;  // ɾ��һ�����÷���
    virtual void SaveConfig(std::string strConfigName)=0;    // ����ǰ��������Ϊָ�����Ƶ����÷���
    virtual bool SetCurrConfig(std::string strConfigName)=0;    // ʹ��ָ�������÷������ó���
    virtual std::string GetCurrConfig()=0;      // ��ȡ��ǰ����ʹ�õķ���
    virtual void GetConfigNameList(std::vector<std::string>& vConfigNames)=0;  // ��ȡ�������÷�������

    // ��ȡϵͳĬ�Ϸ��������ƣ��÷���������ɾ�����޸ģ�
    virtual const std::string& GetDefaultConfigName()=0;
};

//--------------------------------------------------------------
// ����ӿڣ�IVBF_RotorWash
// �ӿ�����������
//--------------------------------------------------------------
class IVBF_RotorWash
{
public:
    virtual ~IVBF_RotorWash() {}
    virtual void Update(const osg::Vec3d& pos, const osg::Vec3d& direction, double pVelocity, double pTime)=0;
};


//--------------------------------------------------------------
// ����ӿڣ�IVBF_ShipWake
// �ӿ�����������
//--------------------------------------------------------------
class IVBF_ShipWake
{
public:
    virtual ~IVBF_ShipWake() {}
    virtual void Update(const osg::Vec3d& pos, const osg::Vec3d& direction, double pVelocity, double pTime)=0;
    virtual void SetLODDistance(double distance)=0;
};

#endif 
