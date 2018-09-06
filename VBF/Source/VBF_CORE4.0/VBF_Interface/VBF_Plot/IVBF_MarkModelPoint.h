//*******************************************************************
// FileName：IVBF_MarkModelPoint.h
// Function：点状标图实体模型接口
// Author:
// Date:     2009-4-1
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_POINT_H__
#define __IVBF_MARK_MODEL_POINT_H__


// 需要使用的头文件
#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/Vec3d>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>



//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelPoint
// 接口描述：点状实体模型
//--------------------------------------------------------------------
class IVBF_MarkModelPoint : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelPoint() {}

public:
	
	/** 设置/获取缩放比，默认为1.0 */
	virtual void SetScale(float fScaleX, float fScaleY, float fScaleZ)=0;
	virtual void GetScale(float& fScaleX, float& fScaleY, float& fScaleZ)=0;

	/** 设置固定像素大小 */
	virtual void  SetFixedSizeInPixels(float fFixedSize)=0;
	virtual float GetFixedSizeInPixels()=0;

	virtual void GetRealtimeScale(float& fScaleX, float& fScaleY, float& fScaleZ)=0;
	virtual void GetParentRealtimeScale(float& fScaleX, float& fScaleY, float& fScaleZ)=0;

	// 获取系统内部自动计算的缩放比（如统一缩放、自动缩放等）
	virtual void GetInnerScale(float& fScaleX, float& fScaleY, float& fScaleZ)=0;

	// 设置/获取模型的旋转顺序（默认值为VBF_ROTATE_ORDER_ZXY）
	virtual void              SetRotateOrder(EVBF_ROTATE_ORDER nOrder)=0;
	virtual EVBF_ROTATE_ORDER GetRotateOrder()=0;

	/** 
    设置/获取模型坐标系下的旋转角，默认值均为0.0
    角度说明：x/y/z依次表示翻滚角/俯仰角/航向角(单位：角度)，右手坐标系下，从轴正向往原点看，逆时针为正
	*/
	virtual void SetRotate(float fRotateX, float fRotateY, float fRotateZ)=0;
	virtual void GetRotate(float& fRotateX, float& fRotateY, float& fRotateZ)=0;

    /** 设置/获取模型坐标系下的初始旋转角（用于校正模型的建模朝向，默认值均为0.0）**/
    virtual void SetRotateInit(float fRotateX, float fRotateY, float fRotateZ)=0;
    virtual void GetRotateInit(float& fRotateX, float& fRotateY, float& fRotateZ)=0;

	// 获取所有父模型的旋转矩阵
	virtual osg::Matrixd GetParentRotateMatrix()=0;

	/**  设置/获取模型坐标系下的平移，默认为0.0 */
	virtual void SetTrans(float fTransX, float fTransY, float fTransZ)=0;
	virtual void GetTrans(float& fTransX, float& fTransY, float& fTransZ)=0;

    /** 设置/获取模型坐标系下的初始平移（用于校正模型的建模原点，默认值均为0.0）**/
    virtual void SetTransInit(float fTransX, float fTransY, float fTransZ)=0;
    virtual void GetTransInit(float& fTransX, float& fTransY, float& fTransZ)=0;
	
	// 是否允许设置固定大小 (单位：像素)
	virtual void EnableFixedSizeInPixels(bool bEnable)=0;
	virtual bool IsFixedSizeInPixelsEnabled()=0;

	// 是否允许自动调整大小
	virtual void EnableAutoScale(bool bEnable)=0;
	virtual bool IsAutoScaleEnabled()=0;

	// 是否允许实时调整缩放比 (即能否通过热键实现统一缩放)
	virtual void EnableScaleDelta(bool bEnable)=0;
	virtual bool IsScaleDeltaEnabled()=0;

	// 是否启用地形匹配
	virtual void EnableMatchTerrain(bool bEnable)=0;	
	virtual bool IsMatchTerrainEnabled()=0;

	// 是否随父模型旋转，默认为true
	virtual void EnableRotateWithParent(bool bEnable)=0;
	virtual bool IsRotateWithParentEnabled()=0;

	// 是否随父模型缩放，默认为true
	virtual void EnableScaleWithParent(bool bEnable)=0;
	virtual bool IsScaleWithParentEnabled()=0;

	// 获取模型坐标系与世界坐标系之间的转换矩阵
	virtual osg::Matrixd GetModelToWorldMatrix()=0;
	virtual osg::Matrixd GetWorldToModelMatrix()=0;

	// 把点坐标由世界坐标系变换到模型坐标系
	virtual osg::Vec3d PointWorldToModel(const osg::Vec3d& ptWorld)=0;

    // 计算从模型原点到模型中某点的向量（模型坐标系下）与地球的交点，返回交点及其与模型原点的距离（世界坐标系下）
    virtual bool Vector0ToPointInModelIntersectWithEarth(const osg::Vec3d& vPointInModel, double dHeightAdjust, osg::Vec3d& ptIntersect, double& dDist)=0;

	// 计算某向量（模型坐标系下）与地球的交点，返回交点及其与向量起点的距离（世界坐标系下）
    virtual bool VectorInModelIntersectWithEarth(const osg::Vec3d& vPointInModelStart, const osg::Vec3d& vPointInModelEnd, double dHeightAdjust, osg::Vec3d& ptIntersect, double& dDist)=0;

	// 判断某点（世界坐标系下）是否在模型范围内
	virtual bool Contains(const osg::Vec3d& ptWorld)=0;
	virtual bool Contains(const osg::Vec3d& ptWorld, osg::Vec3d& ptModel, double& dDist)=0;

	/** 设置模型坐标系下累加的旋转角/缩放比/平移值（在当前值的基础上） */
	virtual void SetDeltaRotate(float fDeltaRotateX, float fDeltaRotateY, float fDeltaRotateZ)=0;
	virtual void SetDeltaScale(float fDeltaScaleX, float fDeltaScaleY, float fDeltaScaleZ)=0;
	virtual void SetDeltaTrans(float fDeltaTransX, float fDeltaTransY, float fDeltaTransZ)=0;
    virtual void SetDeltaTransGeo(float fDeltaTransX, float fDeltaTransY, float fDeltaTransZ)=0;

	/** 恢复模型坐标系下模型初始状态，即无任何旋转角/缩放比/平移值 */
	virtual void SetUnTransformed()=0;

	// 获取模型本身的旋转矩阵
	virtual osg::Matrixd GetRotateMatrix()=0;

	/** 是否直接使用外部设置的旋转矩阵（模型坐标系下） */
	virtual void SetRotateMatrixOut(const osg::Matrixd& mat)=0;

	// 获取点状模型的各个场景图节点
	virtual osg::IVBF_SGNodeGroupTransformMatrix* GetModelToWorldNode()=0;		// 获取模型的定位节点，即模型坐标系->世界坐标系
	virtual osg::IVBF_SGNodeGroupTransformMatrix* GetModelTransformNode()=0;	// 获取模型的局部变换节点

	// 设置/获取仿真时间方式
	virtual void              SetSimTimeMode(EVBF_SIMTIME_MODE nMode)=0;
	virtual EVBF_SIMTIME_MODE GetSimTimeMode()=0;

	// 定长方式下，设置/获取仿真时间步长，即发送相邻两个坐标数据之间的时间间隔 (只适用于定长仿真方式，单位：秒)
	virtual void  SetSimTimeStep(float fStep)=0;
	virtual float GetSimTimeStep()=0;

	/* 设置军标模型当前的位置(地理坐标)和姿态，同时对坐标和角度进行插值
	   参数：vGeoPos     -- 模型当前的位置(地理坐标)
			 fRotateX    -- 模型当前的滚转角，即模型从初始化状态起绕X轴旋转的角度，逆时针为正 (单位：角度，值域为[-180, 180])
			 fRotateY    -- 模型当前的俯仰角，即模型从初始化状态起绕Y轴旋转的角度，逆时针为正 (单位：角度，值域为[-90, 90])
			 fRotateZ    -- 模型当前的偏航角，即模型从初始化状态起绕Z轴旋转的角度，逆时针为正 (单位：角度，值域为[-180, 180])
             strInfo     -- 模型在该位置处的信息，以便在轨迹点中查询（可以为空字符串）
	         坐标系说明：右手坐标系，从轴正向往原点看，逆时针为正
	*/
    virtual void StepGeoPos(const osg::Vec3d& vGeoPos, float fRotateX, float fRotateY, float fRotateZ, const std::string& strInfo="")=0;
    virtual void StopStepIn()=0; // 停止步进

    // 获取军标模型在当前帧的轨迹点信息（该信息通过StepGeoPos()函数设置，如果模型尚未开始运动，返回false）
    virtual bool GetTrailPoint(VBF_TRAILPOINT& ptTrail)=0;

    // 设置/获取模型的观察模式
    virtual void            SetViewMode(EVBF_VIEW_MODE nMode)=0;
    virtual EVBF_VIEW_MODE  GetViewMode()=0;
};


#endif 
