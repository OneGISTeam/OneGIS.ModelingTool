//*******************************************************************
// FileName：IVBF_MarkModelShapeRevoSurface.h
// Function：形状实体模型：简单回转面（回转面：Revolution Surface，此处简写为RevoSurface）
// Author:   杜莹
// Date:     2013-11-07
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_REVOSURFACE_H__
#define __IVBF_MARK_MODEL_SHAPE_REVOSURFACE_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_REVOSURFACE_PART
// 枚举描述：简单回转面的各个部分
//--------------------------------------------------------------------
enum EVBF_REVOSURFACE_PART
{
	VBF_REVOSURFACE_PART_BODY		= 0,	// 主体（由包络线旋转而成，类似于电扇的外壳）
	VBF_REVOSURFACE_PART_TOP		= 1,	// 顶部（由顶部圆心和顶部圆周点形成的平面）
	VBF_REVOSURFACE_PART_BOTTOM		= 2,	// 底部（由底部圆心和底部圆周点形成的平面）
	VBF_REVOSURFACE_PART_LOBE		= 3,	// 波瓣（连接圆心与圆周的扇形，类似于电扇的叶片）
	VBF_REVOSURFACE_PART_COUNT				// 总数
};


//-----------------------------------------------------------------
// 定义结构体：VBF_ENVELOPE_DATA
// 结构体描述：回转面的包络数据
//-----------------------------------------------------------------
struct VBF_ENVELOPE_DATA
{
    float	fAngle;		// 方向角（单位：角度）
    float	fDist;		// 与原点的距离（单位：米）

    VBF_ENVELOPE_DATA()
    {
        fAngle = 0.0f;
        fDist  = 0.0f;
    }
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeRevoSurface
// 接口描述：简单回转面
//--------------------------------------------------------------------
class IVBF_MarkModelShapeRevoSurface : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeRevoSurface() {}

	// 设置/获取配置文件名（含完整路径和后缀）
	// 参数：bPolarCoord -- 配置文件中的点是否是使用极坐标（默认为true）
	// 参数：bDistUnitKm -- 配置文件中距离的单位是否为公里（默认为true）
	virtual void SetConfigFileName(const std::string& strFileName, bool bPolarCoord=true, bool bDistUnitKm=true)=0;
	virtual void GetConfigFileName(std::string& strFileName, bool& bPolarCoord, bool& bDistUnitKm)=0;

	// 设置/获取配置文件中顶点的排列顺序是否为逆时针（默认为true）
	virtual void SetConfigPointsCCW(bool bCCW)=0;
	virtual bool IsConfigPointsCCW()=0;

    // 设置/获取包络数据
    virtual void SetEnvelopeData(const std::vector<VBF_ENVELOPE_DATA>& vData)=0;
    virtual const std::vector<VBF_ENVELOPE_DATA>& GetEnvelopeData()=0;

	// 设置/获取主体的水平起始角和终止角（默认值分别为0度, 360度）
	virtual void SetAngleH(float fAngleH0, float fAngleH1)=0;
	virtual void GetAngleH(float& fAngleH0, float& fAngleH1)=0;

	// 设置/获取主体圆周分割数（默认值为60）
	virtual void SetNumSplit(int num)=0;
	virtual int  GetNumSplit()=0;

	// 获取从配置文件中读取的水平方向的最小/最大半径（单位：米，用户可以根据这两个值调整缩放比）
	virtual float GetRadiusMin()=0;
	virtual float GetRadiusMax()=0;

	// 设置/获取用户自定义的水平方向的最大半径（单位：米，实际上是调整XY方向的缩放比）
	virtual void  SetCustomRadiusMax(float fRadiusMax)=0;
	virtual float GetCustomRadiusMax()=0;

	// 设置/获取波瓣的扫描范围（默认为0到360度）
	virtual void SetLobeAngleRange(float fAngleMin, float fAngleMax)=0;
	virtual void GetLobeAngleRange(float& fAngleMin, float& fAngleMax)=0;

	// 设置/获取波瓣的角度间隔
	virtual void  SetLobeAngleInterval(float fAngle)=0;
	virtual float GetLobeAngleInterval()=0;

	// 设置/获取是否开启波瓣扫描
	virtual void EnableLobeScan(bool bEnable)=0;
	virtual bool IsLobeScanEnabled()=0;

	// 设置/获取波瓣扫描速度（度/秒，默认值为50.0）
	virtual void  SetLobeScanSpeed(float fScanSpeed)=0;
	virtual float GetLobeScanSpeed()=0;
};


#endif 
