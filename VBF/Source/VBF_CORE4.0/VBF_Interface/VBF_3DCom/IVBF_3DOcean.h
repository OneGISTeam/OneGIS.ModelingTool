#ifndef __IVBF_3DOCEAN_H__
#define __IVBF_3DOCEAN_H__


#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h>
#include <string>
#include <vector>


// 定义该组件的ID号
const char VBF_COMPONENT_3DOCEAN[]	= "Component: 3DOcean";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DOCEAN[]	= "三维海洋";

// 定义命令ID号
const char VBF_COMMAND_SHOWDIALOG_OCEAN[] = "Command: Show Dialog Ocean";     // 显示对话框：调整海洋参数


//--------------------------------------------------------------
// 定义结构体：CVBF_ShipWakeParameters
// 结构体描述：船迹参数
//--------------------------------------------------------------
class CVBF_ShipWakeParameters
{
public:
    double  length;         // 尾迹长度
    double  beamWidth;      // 尾迹宽
    double  draft;          // 气流
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
// 定义接口：IVBF_3DOcean
// 接口描述：三维海洋
//--------------------------------------------------------------
class IVBF_3DOcean : public CVBF_Referenced
{
public:	
    virtual ~IVBF_3DOcean() {}

    // 设置/获取是否开启三维海洋
    virtual void Enable(bool bEnable)=0;
    virtual bool IsEnabled()=0;

    // 设置/获取海平面高度
    virtual void   SetSeaLevel(double dValue)=0;
    virtual double GetSeaLevel() const=0;

    // 设置/获得海洋可视化高度
    virtual void   SetLodHeight(double dValue)=0;
    virtual double GetLodHeight() const=0;

    // 设置/获取风速（单位：米/秒）
    virtual void   SetWindSpeed(double dSpeed)=0;  //
    virtual double GetWindSpeed() const=0;

    // 设置/获取风向（单位：角度，与正北方向的夹角，顺时针为正, 0-360之间有效）
    virtual void   SetWindDirection(double dDirection) =0;
    virtual double GetWindDirection() const=0;

    // 获取风速和风向
    virtual void   GetWind(double& dSpeed, double& dDirection) const=0;

    // 设置/获取水下模型的变形大小（值越大变形越大，默认值为0.03）
    virtual void  SetUnderWaterDistortFactor(float fFactor)=0;
    virtual float GetUnderWaterDistortFactor()=0;

    // 设置/获取水下混色（与原有颜色是相加的关系，默认值为(0,0,0)）
    virtual void       SetUnderWaterBlendColor(const osg::Vec3f& color)=0;
    virtual osg::Vec3f GetUnderWaterBlendColor()=0;

    // 设置/获取海底纹理的亮度(0=none, 1=full，默认值为0.9)
    virtual void  SetSeaFloorTextureIntensity(float value)=0;
    virtual float GetSeaFloorTextureIntensity() const=0;

    // 设置/获取海底纹理的颜色（默认值为(0.396, 0.702, 0.843)）
    virtual void       SetSeaFloorTextureColor(const osg::Vec3f& color)=0;
    virtual osg::Vec3f GetSeaFloorTextureColor()=0;

    // 设置/获取是否开启水下GodRay（默认为true）
    virtual void EnableGodRays(bool bEnable)=0;
    virtual bool IsGodRaysEnabled()=0;

    // 创建旋涡
    virtual IVBF_RotorWash* CreateRotorWash(double pRotorDiameter, bool pSprayEffects=false, bool pUseDecals=false, double pFadeInTime=20)=0;

    // 创建舰船尾迹
    virtual IVBF_ShipWake*  CreateShipWake(const CVBF_ShipWakeParameters& par)=0;

    // 给定某点的世界坐标及法向量，获取该点的海面实时浪高及法向量
    // 注意：返回的height+GetSeaLevel() = 高程值
    virtual bool GetHeight(const osg::Vec3d& point, const osg::Vec3d& direction, float& height, osg::Vec3d& normal,
                           bool visualCorrelation=true, bool includeWakes=true, bool highResolution=true, bool threadSafe=true)=0;

    // 添加一个反射节点
    virtual void AddReflectionNode(osg::IVBF_SGNode* pNode)=0;

    // 获取海洋节点
    virtual osg::IVBF_SGNode* GetTritonNode()=0;

    // 获取海洋目前是否正在显示
    virtual bool IsShow() const=0;

    // 获取各个参数的有效值范围
    virtual double GetLodHeightMin()=0;             // 获取海洋可视化高度最小值（单位：米）
    virtual double GetLodHeightMax()=0;             // 获取海洋可视化高度最大值（单位：米）
    virtual double GetSeaLevelMin()=0;              // 获取海平面最小值（单位：米）
    virtual double GetSeaLevelMax()=0;              // 获取海平面最大值（单位：米）
    virtual double GetWindSpeedMin()=0;             // 获取风速最小值（单位：米/秒）
    virtual double GetWindSpeedMax()=0;             // 获取风速最大值（单位：米/秒）
    virtual double GetWindDirectionMin()=0;         // 获取风向最小值（单位：角度），与正北方向的夹角
    virtual double GetWindDirectionMax()=0;         // 获取风向最大值（单位：角度）
    virtual float  GetUnderWaterDistortMin()=0;     // 获取水下变形最小值
    virtual float  GetUnderWaterDistortMax()=0;     // 获取水下变形最大值

    // 海洋配置参数的串行化
    virtual bool AddConfig(std::string strConfigName)=0;     // 添加一个配置方案
    virtual void DeleteConfig(std::string strConfigName)=0;  // 删除一个配置方案
    virtual void SaveConfig(std::string strConfigName)=0;    // 将当前场景保存为指定名称的配置方案
    virtual bool SetCurrConfig(std::string strConfigName)=0;    // 使用指定的配置方案设置场景
    virtual std::string GetCurrConfig()=0;      // 获取当前场景使用的方案
    virtual void GetConfigNameList(std::vector<std::string>& vConfigNames)=0;  // 获取所有配置方案名称

    // 获取系统默认方案的名称（该方案不允许删除或修改）
    virtual const std::string& GetDefaultConfigName()=0;
};

//--------------------------------------------------------------
// 定义接口：IVBF_RotorWash
// 接口描述：漩涡
//--------------------------------------------------------------
class IVBF_RotorWash
{
public:
    virtual ~IVBF_RotorWash() {}
    virtual void Update(const osg::Vec3d& pos, const osg::Vec3d& direction, double pVelocity, double pTime)=0;
};


//--------------------------------------------------------------
// 定义接口：IVBF_ShipWake
// 接口描述：船迹
//--------------------------------------------------------------
class IVBF_ShipWake
{
public:
    virtual ~IVBF_ShipWake() {}
    virtual void Update(const osg::Vec3d& pos, const osg::Vec3d& direction, double pVelocity, double pTime)=0;
    virtual void SetLODDistance(double distance)=0;
};

#endif 
