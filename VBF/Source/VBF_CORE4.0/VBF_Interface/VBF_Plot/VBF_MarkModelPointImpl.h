//*******************************************************************
// FileName：VBF_MarkModelPointImpl.h
// Function：点状标图实体模型接口
// Author:
// Date:     2009-4-1
//*******************************************************************

#ifndef __VBF_MARK_MODEL_POINT_IMPL_H__
#define __VBF_MARK_MODEL_POINT_IMPL_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/VBF_MarkModelImpl.h>
#include <Types/VBF_Matrixd.h>
#include <VBF_Common/VBF_Math/VBF_Math.h>
#include <VBF_Common/VBF_Math/VBF_GisMath.h>
#include <VBF_Base/VBF_Timer.h>
#include <VBF_Plot/VBF_TrailPointInner.h>
#include <queue>
#include <VBF_Aux/VBF_GLAux/VBF_ReadWriteUtils.h>
#include <VBF_3DMap/VBF_Terrain/CullingUtils.h>
#include <VBF_3DMap/VBF_EarthUtil/ObjectLocator>

template<class T>
class CVBF_MarkModelPointImpl : public CVBF_MarkModelImpl<T>
{
public:
	CVBF_MarkModelPointImpl() {}
	CVBF_MarkModelPointImpl(const std::string& strMarkID);
	CVBF_MarkModelPointImpl(const CVBF_MarkModelPointImpl& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
	virtual ~CVBF_MarkModelPointImpl();
	
	// 判断是否为点状模型
	virtual bool IsPointMarkModel() { return true; }

	// 修改成员变量
	virtual void SetScale(float fScaleX, float fScaleY, float fScaleZ);
	virtual void GetScale(float& fScaleX, float& fScaleY, float& fScaleZ)	{ fScaleX = m_fScaleX; fScaleY = m_fScaleY; fScaleZ = m_fScaleZ; }

	virtual void  SetFixedSizeInPixels(float fFixedSize)	{ m_fFixedSizeInPixels = fFixedSize; DirtyMatrixModelScale(); }
	virtual float GetFixedSizeInPixels()					{ return m_fFixedSizeInPixels; }

	// 设置/获取模型的旋转顺序（默认值为VBF_ROTATE_ORDER_ZXY）
	virtual void              SetRotateOrder(EVBF_ROTATE_ORDER nOrder);
	virtual EVBF_ROTATE_ORDER GetRotateOrder() { return m_nRotateOrder; }

	virtual void SetRotate(float fRotateX, float fRotateY, float fRotateZ);
	virtual void GetRotate(float& fRotateX, float& fRotateY, float& fRotateZ)	{ fRotateX = m_fRotateX; fRotateY = m_fRotateY; fRotateZ = m_fRotateZ; }

    virtual void SetRotateInit(float fRotateX, float fRotateY, float fRotateZ);
    virtual void GetRotateInit(float& fRotateX, float& fRotateY, float& fRotateZ)	{ fRotateX = m_fRotateInitX; fRotateY = m_fRotateInitY; fRotateZ = m_fRotateInitZ; }

	virtual void GetRealtimeScale(float& fScaleX, float& fScaleY, float& fScaleZ);
    virtual void GetParentRealtimeScale(float& fScaleX, float& fScaleY, float& fScaleZ);
	virtual osg::Matrixd GetParentRotateMatrix();

	// 获取系统内部自动计算的缩放比（如统一缩放、自动缩放等）
	virtual void GetInnerScale(float& fScaleX, float& fScaleY, float& fScaleZ);

    // 设置/获取模型坐标系下的平移，默认为0.0
	virtual void SetTrans(float fTransX, float fTransY, float fTransZ);
	virtual void GetTrans(float& fTransX, float& fTransY, float& fTransZ) { fTransX = m_fTransX; fTransY = m_fTransY; fTransZ = m_fTransZ; }

    virtual void SetTransInit(float fTransX, float fTransY, float fTransZ);
    virtual void GetTransInit(float& fTransX, float& fTransY, float& fTransZ) { fTransX = m_fTransInitX; fTransY = m_fTransInitY; fTransZ = m_fTransInitZ; }

	// 是否允许设置固定大小 (单位：像素)
	virtual void EnableFixedSizeInPixels(bool bEnable);
	virtual bool IsFixedSizeInPixelsEnabled()		{ return m_bEnableFixedSizeInPixels; }

	// 是否允许自动调整大小
	virtual void EnableAutoScale(bool bEnable)		{ m_bEnableAutoScale = bEnable; DirtyMatrixModelScale(); }
	virtual bool IsAutoScaleEnabled()				{ return m_bEnableAutoScale; }

	// 是否允许实时调整缩放比 (即能否通过热键实现统一缩放)
	virtual void EnableScaleDelta(bool bEnable)		{ m_bEnableScaleDelta = bEnable; DirtyMatrixModelScale(); }
	virtual bool IsScaleDeltaEnabled()				{ return m_bEnableScaleDelta; }

	// 是否随父模型旋转，默认为true
	virtual void EnableRotateWithParent(bool bEnable);
	virtual bool IsRotateWithParentEnabled()	{ return m_bRotateWithParent; }

	// 是否随父模型缩放，默认为true
	virtual void EnableScaleWithParent(bool bEnable);
	virtual bool IsScaleWithParentEnabled()		{ return m_bScaleWithParent; }

	// 是否启用地形匹配
	virtual void EnableMatchTerrain(bool bEnable)	{ m_bEnableMatchTerrain = bEnable; }	
	virtual bool IsMatchTerrainEnabled()			{ return m_bEnableMatchTerrain; }

	// 获取模型坐标系与世界坐标系之间的转换矩阵
	virtual osg::Matrixd GetModelToWorldMatrix();
	virtual osg::Matrixd GetWorldToModelMatrix();

	// 把点坐标由世界坐标系变换到模型坐标系
	virtual osg::Vec3d PointWorldToModel(const osg::Vec3d& ptWorld);

    // 计算从模型原点到模型中某点的向量（模型坐标系下）与地球的交点，返回交点及其与模型原点的距离（世界坐标系下）
    virtual bool Vector0ToPointInModelIntersectWithEarth(const osg::Vec3d& vPointInModel, double dHeightAdjust, osg::Vec3d& ptIntersect, double& dDist);

	// 计算某向量（模型坐标系下）与地球的交点，返回交点及其与向量起点的距离（世界坐标系下）
    virtual bool VectorInModelIntersectWithEarth(const osg::Vec3d& vPointInModelStart, const osg::Vec3d& vPointInModelEnd, double dHeightAdjust, osg::Vec3d& ptIntersect, double& dDist);

	// 判断某点（世界坐标系下）是否在模型范围内
	virtual bool Contains(const osg::Vec3d& ptWorld);
	virtual bool Contains(const osg::Vec3d& ptWorld, osg::Vec3d& ptModel, double& dDist) { return false; }

	// 设置模型坐标系下累加的旋转角/缩放比/平移值（在当前值的基础上）
	virtual void SetDeltaRotate(float fDeltaRotateX, float fDeltaRotateY, float fDeltaRotateZ);
	virtual void SetDeltaScale(float fDeltaScaleX, float fDeltaScaleY, float fDeltaScaleZ);
	virtual void SetDeltaTrans(float fDeltaTransX, float fDeltaTransY, float fDeltaTransZ);
    virtual void SetDeltaTransGeo(float fDeltaTransX, float fDeltaTransY, float fDeltaTransZ);

	// 恢复模型坐标系下模型初始状态，即无任何旋转角/缩放比/平移值
	virtual void SetUnTransformed();

	// 获取模型本身的旋转矩阵
	virtual osg::Matrixd GetRotateMatrix() { return m_matModelRotate; }

	// 直接使用外部设置的旋转矩阵（模型坐标系下）
	virtual void SetRotateMatrixOut(const osg::Matrixd& mat);

	// 获取模型的各个场景图节点
	virtual osg::IVBF_SGNodeGroupTransformMatrix* GetModelToWorldNode()		{ return m_piNodeModelToWorld.get(); }
	virtual osg::IVBF_SGNodeGroupTransformMatrix* GetModelTransformNode()	{ return m_piNodeTransformModel.get(); }

	virtual void SetParent(IVBF_MarkModel* pIParent);

	// 设置/获取仿真时间方式
	virtual void              SetSimTimeMode(EVBF_SIMTIME_MODE nMode) { m_nSimTimeMode = nMode; }
	virtual EVBF_SIMTIME_MODE GetSimTimeMode() { return m_nSimTimeMode; }

	// 定长方式下，设置/获取仿真时间步长，即发送相邻两个坐标数据之间的时间间隔 (只适用于定长仿真方式，单位：秒)
	virtual void  SetSimTimeStep(float fStep)	{ m_fSimTimeStep = fStep; }
	virtual float GetSimTimeStep()				{ return m_fSimTimeStep; }

	// 步进模型的地理坐标
    virtual void StepGeoPos(const osg::Vec3d& vGeo, float fRotateX, float fRotateY, float fRotateZ, const std::string& strInfo="");
    virtual void StopStepIn(); // 停止步进

    // 获取军标模型在当前帧的轨迹点信息（该信息通过StepGeoPos()函数设置，如果模型尚未开始运动，返回false）
    virtual bool GetTrailPoint(VBF_TRAILPOINT& ptTrail);

    // 设置/获取模型的观察模式
    virtual void            SetViewMode(EVBF_VIEW_MODE nMode);
    virtual EVBF_VIEW_MODE  GetViewMode() { return m_nViewMode; }

    // 获取模型在各个坐标系下的包围盒
    virtual const osg::BoundingBox&  GetBoundingBoxInWorld();
    virtual const osg::BoundingBoxd& GetBoundingBoxInGeo();

    // 获取模型的世界坐标
    virtual const osg::Vec3d& GetWorldPos();

	// 执行json脚本
    virtual void ExecuteScript(const CVBF_Config& conf);

public:

	// 更新 (每帧绘制前调用)
	virtual bool Update();

protected:

	// 初始化模型的场景图
    virtual bool InitSG();

    // 更新某些场景图节点的属性
    virtual void UpdateSGNode();

	// 使局部变换矩阵失效
	void DirtyMatrixModelScale()	{ m_bDirtyMatrixModelScale  = true; m_bDirtyMatrixModel = true; }
	void DirtyMatrixModelRotate()	{ m_bDirtyMatrixModelRotate = true; m_bDirtyMatrixModel = true; }	
    void DirtyMatrixModelTrans()	{ m_bDirtyMatrixModelTrans  = true; m_bDirtyMatrixModel = true; CVBF_MarkModelImpl<T>::DirtyPosWorld(); }

	// 计算模型的局部变换矩阵
	virtual void Transform();
    virtual void TransformByViewMode();
	virtual void CalMatrixModel();
	virtual void CalMatrixModelScale();
	virtual void CalMatrixModelRotate();
	virtual void CalMatrixModelTrans();

    void MatrixMove(osg::Matrixd& matMove);

	// 更新模型的位置
	virtual void UpdatePos();

	// 创建定位节点（绝对定位/相对定位）
	void CreateNodeLocator(bool bLocateRel);

    // 步进到下一个插值点
    void StepIt();

    // 路径插值 (同时进行坐标插值和角度插值)
    void Interpolate(int nNumInsert, const VBF_TRAILPOINTINNER& ptBegin, const VBF_TRAILPOINTINNER& ptEnd, bool bIncludingEnd);

    // 向插值点队列中追加一个点
    void PushOnePoint(const VBF_TRAILPOINTINNER& point);

	// 根据仿真时间步长方式，计算当前需要插值的点数
    int GetNumInterPoints(const VBF_TRAILPOINTINNER& ptBegin, const VBF_TRAILPOINTINNER& ptEnd);

    // 创建包围盒节点
    virtual osg::IVBF_SGNode* CreateBoundingBoxNode();

    // 判断是否需要挂接AutoTransform节点
    bool NeedAutoTransformNode();

    // 地球背面的裁剪
    virtual void ClipByEarth();

    // 串行化
    virtual bool WriteModelToXML(TiXmlElement* pElemMark);
    virtual bool ReadModelFromXML(TiXmlElement* pElemMark);

protected:
	float					m_fScaleX;					// X方向上的缩放因子
	float					m_fScaleY;					// Y方向上的缩放因子
    float					m_fScaleZ;					// Z方向上的缩放因子
    float					m_fFixedSizeInPixels;		// 固定大小 (单位：像素)
	
	// 模型旋转 (即局部坐标下的旋转，单位：角度)
	EVBF_ROTATE_ORDER		m_nRotateOrder;		// 旋转顺序
	float					m_fRotateX;
	float					m_fRotateY;
	float					m_fRotateZ;

	// 模型自身平移 (即局部坐标下的平移，单位：米)
	float					m_fTransX;
	float					m_fTransY;
	float					m_fTransZ;

    // 模型的初始旋转角（用于校正模型的建模朝向，单位：角度）
    float					m_fRotateInitX;
    float					m_fRotateInitY;
    float					m_fRotateInitZ;

    // 模型的初始平移（用于校正模型的建模原点）
    float					m_fTransInitX;
    float					m_fTransInitY;
    float					m_fTransInitZ;
	
	// 状态参数
	bool                    m_bEnableFixedSizeInPixels;	// 是否允许设置固定大小
	bool                    m_bEnableAutoScale;			// 是否允许自动调整大小
	bool					m_bEnableScaleDelta;		// 是否允许实时调整缩放比 (即能否通过热键实现统一缩放)
	bool					m_bEnableMatchTerrain;		// 是否允许地形匹配

	// 是否随父模型变换
	bool					m_bScaleWithParent;			// 是否随父模型缩放
	bool					m_bRotateWithParent;		// 是否随父模型旋转

	// 局部变换矩阵是否已经失效，如果失效，需要在绘制前重新计算
	bool					m_bDirtyMatrixModel;
	bool					m_bDirtyMatrixModelScale;
	bool					m_bDirtyMatrixModelRotate;
	bool					m_bDirtyMatrixModelTrans;
	bool					m_bDirtyFixedSizeInPixels;

    // 定位节点是否失效
    bool                    m_bDirtyNodeLocator;
    bool                    m_bLocateRelative;  // 更新后的定位方式：相对定位/绝对定位

    // 是否需要添加/移除AutoTransform节点
    bool                    m_bDirtyAutoTransformNode;

    // 模型的观察方式
    EVBF_VIEW_MODE          m_nViewMode;
    bool                    m_bDirtyViewMode;   // 观察方式是否失效

	// 局部变换矩阵
	osg::Matrixd			m_matModelScale;
	osg::Matrixd			m_matModelRotate;
	osg::Matrixd			m_matModelTrans;
	osg::Matrixd			m_matModel;		// = m_matModelScale * m_matModelRotate * m_matModelTrans;

	// 是否直接使用外部设置的旋转矩阵（模型坐标系下）
	CVBF_Optional<osg::Matrixd>	m_matModelRotateOut;
	CVBF_Optional<osg::Matrixd>	m_matModelRotateOutForWrite;  // 纯粹用于串行化

	// 与场景图有关的内容
	ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix>		m_piNodeModelToWorld;	// 模型的绝对定位节点，完成模型坐标系到世界坐标系的转换，挂接在m_piNodeRoot节点下
	ref_ptr<osg::IVBF_SGNodeGroupTransformAuto>			m_piNodeTransformAuto;	// 模型的自动变换节点，可实现固定像素大小和布告牌效果，挂接在绝对定位节点下（需要时才挂接）
	ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix>		m_piNodeTransformModel;	// 模型的局部变换节点，挂接在自动变换节点下

	// 其他需要使用的外部节点
	observer_ptr<osgEarth::Util::ObjectLocator>			m_piLocator;	// 绝对定位使用

	// 仿真步长，即发送相邻两个坐标数据之间的时间间隔 (单位：秒)
    EVBF_SIMTIME_MODE                   m_nSimTimeMode;
    float                               m_fSimTimeStep;

    // 与路径插值有关的内容
    std::queue<VBF_TRAILPOINTINNER>         m_vKeyPoints;		// 所有关键点
    std::queue<VBF_TRAILPOINTINNER>         m_vInterPoints;		// 所有插值点
    CVBF_Optional<VBF_TRAILPOINTINNER>      m_TrailPoint;       // 模型在该帧的轨迹点信息
};

//-----------------------------------------------------------------------------
// 函数：CVBF_MarkModelPointImpl()
// 描述：构造函数
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModelPointImpl<T>::CVBF_MarkModelPointImpl(const std::string& strMarkID)
	: CVBF_MarkModelImpl<T>(strMarkID) 
{
	m_fScaleX				= 1.0f;			// X方向上的缩放因子
    m_fScaleY				= 1.0f;			// Y方向上的缩放因子
    m_fScaleZ				= 1.0f;			// Z方向上的缩放因子
    m_fFixedSizeInPixels	= 50.0f;		// 固定大小 (单位：像素)

	m_nRotateOrder			= VBF_ROTATE_ORDER_ZXY;
	m_fRotateX				= 0.0f;			// 绕X轴的旋转角度(角度)
	m_fRotateY				= 0.0f;			// 绕Y轴的旋转角度(角度)
	m_fRotateZ				= 0.0f;			// 绕Z轴的旋转角度(角度)

	m_fTransX				= 0.0f;	
	m_fTransY				= 0.0f;
	m_fTransZ				= 0.0f;

    // 模型的初始旋转角（用于校正模型的建模朝向）
    m_fRotateInitX			= 0.0f;
    m_fRotateInitY			= 0.0f;
    m_fRotateInitZ			= 0.0f;

    // 模型的初始平移（用于校正模型的建模原点）
    m_fTransInitX			= 0.0f;
    m_fTransInitY			= 0.0f;
    m_fTransInitZ			= 0.0f;
	
	m_bEnableFixedSizeInPixels	= false;
	m_bEnableAutoScale			= false;
	m_bEnableScaleDelta			= true;
	m_bEnableMatchTerrain		= false;
	this->m_bEnableClipByEarth	= true;

	// 是否随父模型变换
	m_bScaleWithParent		= true;
	m_bRotateWithParent     = true;

	// 局部变换矩阵是否已经失效，如果失效，需要在绘制前重新计算
	m_bDirtyMatrixModel		  = true;
	m_bDirtyMatrixModelScale  = true;
	m_bDirtyMatrixModelRotate = true;
	m_bDirtyMatrixModelTrans  = true;
	m_bDirtyFixedSizeInPixels = true;

    // 定位节点是否失效
    m_bDirtyNodeLocator     = true;
    m_bLocateRelative       = false;  // 更新后的定位方式：相对定位/绝对定位

	// 仿真步长，即发送相邻两个坐标数据之间的时间间隔 (单位：秒)
    m_nSimTimeMode          = VBF_SIMTIME_MODE_VARIABLE;
    m_fSimTimeStep          = 1.0f;

    // 模型的观察方式
    m_nViewMode             = VBF_VIEW_MODE_NORMAL;
    m_bDirtyViewMode        = true;

    // 是否需要添加/移除AutoTransform节点
    m_bDirtyAutoTransformNode = false;

    m_matModelScale.makeIdentity();
    m_matModelRotate.makeIdentity();
    m_matModelTrans.makeIdentity();
    m_matModel.makeIdentity();
}

//-----------------------------------------------------------------------------
// 函数：CVBF_MarkModelPointImpl()
// 描述：析构函数
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModelPointImpl<T>::~CVBF_MarkModelPointImpl()
{
}

//-----------------------------------------------------------------------------
// 函数：InitSG()
// 描述：初始化模型的场景图
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::InitSG()
{
	// 创建模型的根节点，挂接在图层节点下
    this->m_piNodeRoot = new osg::Switch;
    this->m_piNodeRoot->setName("VBFNode_MarkRoot: " + this->m_strID);
    this->m_piNodeRoot->setValue(0, this->m_bVisible);
    this->m_piNodeRoot->setUserValue("VBFMarkPtr", (TYPE_PTR)this);

	// 创建模型的绝对定位节点，挂接在m_piNodeRoot节点下
	CreateNodeLocator(false);

	// 创建模型的自动变换节点，挂接在绝对定位节点下，以便实现固定像素大小等效果（需要时才挂接）
	m_piNodeTransformAuto = new osg::AutoTransform;
    m_piNodeTransformAuto->setName("VBFNode_MarkAutoTransform: " + this->m_strID);
    m_piNodeTransformAuto->setAutoScaleToScreen(m_bEnableFixedSizeInPixels);  // 设置为true时，节点固定像素大小
    m_piNodeTransformAuto->setAutoRotateMode(osg::AutoTransform::NO_ROTATION);
    m_piNodeTransformAuto->setRotation(osg::Quat(0,0,0,1));
    m_piNodeTransformAuto->setPosition(osg::Vec3d(0,0,0));

	// 创建模型的局部变换节点，作为自动变换节点的子节点
	m_piNodeTransformModel = new osg::MatrixTransform;
    m_piNodeTransformModel->setName("VBFNode_MarkModelTransform: " + this->m_strID);
	m_piNodeTransformModel->setReferenceFrame(osg::IVBF_SGNodeGroupTransform::RELATIVE_RF);
    m_piNodeTransformModel->setMatrix(osg::Matrix::identity());

	// 创建模型的Group节点，挂接在Lod节点下，用户的节点需要挂接在该节点下
    this->m_piNodeGroup = ::VBF_CreateSGNodeGroup();
    this->m_piNodeGroup->setName("VBFNode_MarkGroup: " + this->m_strID);

    // 依次挂接上述节点
    if( NeedAutoTransformNode() ) // 需要挂接AutoTransform节点
    {
        this->m_piNodeRoot->addChild(m_piNodeModelToWorld);
        m_piNodeModelToWorld->addChild(m_piNodeTransformAuto);
        m_piNodeTransformAuto->addChild(m_piNodeTransformModel);
        m_piNodeTransformModel->addChild(this->m_piNodeGroup);
    }
    else  // 不需要挂接AutoTransform节点
    {
        this->m_piNodeRoot->addChild(m_piNodeModelToWorld);
        m_piNodeModelToWorld->addChild(m_piNodeTransformModel);
        m_piNodeTransformModel->addChild(this->m_piNodeGroup);
    }

	return true;
}

//-----------------------------------------------------------------------------
// 函数：CreateNodeLocator()
// 描述：创建模型的定位节点（绝对定位/相对定位）
// 参数：bLocateRel -- 是否使用相对定位
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::CreateNodeLocator(bool bLocateRel)
{ 
    ref_ptr<osg::MatrixTransform> ipNodeNew;

	// 如果使用相对定位，m_vPoeGeo不再表示地理坐标，而表示相对父模型的偏移量
	if(bLocateRel)
	{
		// 使绝对定位失效
		m_piLocator = NULL;

        ipNodeNew = new osg::MatrixTransform;
        ipNodeNew->setName("VBFNode_MarkLocatorRelative: " + this->m_strID);
        ipNodeNew->setMatrix( osg::Matrix::translate(this->m_vPosGeo) );
	}
	else  // 没有父节点，m_vPosGeo表示地理坐标
	{
//      piNodeNew = new osgEarth::Util::ObjectLocatorNode( this->m_opMapNode->GetMap() );
        ipNodeNew = new osgEarth::Util::ObjectLocatorNode( (CVBF_Map*)this->m_ipContext->GetMap() );
        ipNodeNew->setName("VBFNode_MarkLocatorAbsolute: " + this->m_strID);
        m_piLocator = (dynamic_cast<osgEarth::Util::ObjectLocatorNode*>(ipNodeNew.get()))->getLocator();
		if(m_piLocator.valid()) m_piLocator->setPosition(this->m_vPosGeo);
	}

	// 注意：保持原有的父节点和子节点
	if( m_piNodeModelToWorld.valid() )
	{
        osg::IVBF_SGNode*      pNodeChild  = m_piNodeModelToWorld->getChild(0);
		osg::IVBF_SGNodeGroup* pNodeParent = m_piNodeModelToWorld->getParent(0);

        if(pNodeChild!=NULL)  ipNodeNew->addChild(pNodeChild);
        if(pNodeParent!=NULL) pNodeParent->replaceChild(m_piNodeModelToWorld.get(), ipNodeNew.get() );
	}

	// 用新节点替换旧节点
    m_piNodeModelToWorld = ipNodeNew.release();
}

//----------------------------------------------------------------------------
// 函数：SetScale()
// 描述：设置模型缩放系数
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetScale(float fScaleX, float fScaleY, float fScaleZ)
{ 
	m_fScaleX = fScaleX; 
	m_fScaleY = fScaleY; 
	m_fScaleZ = fScaleZ; 

	// 缩放系数不能为负值
	if( m_fScaleX < 0 ) m_fScaleX = 1.0f;
	if( m_fScaleY < 0 ) m_fScaleY = 1.0f;
	if( m_fScaleZ < 0 ) m_fScaleZ = 1.0f;

	DirtyMatrixModelScale();
}

//----------------------------------------------------------------------------
// 函数：SetRotateOrder()
// 描述：设置模型的旋转顺序（默认值为VBF_ROTATE_ORDER_ZXY）
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetRotateOrder(EVBF_ROTATE_ORDER nOrder)
{
	if(m_nRotateOrder != nOrder)
	{
		m_nRotateOrder = nOrder;
		DirtyMatrixModelRotate();
	}
}

//----------------------------------------------------------------------------
// 函数：SetRotate()
// 描述：设置模型旋转角
// 说明：x/y/z依次表示翻滚角/俯仰角/航向角(单位：角度)，右手坐标系下，从轴轴正向往原点看，逆时针为正
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetRotate(float fRotateX, float fRotateY, float fRotateZ)	
{ 
	m_fRotateX	= fRotateX; 
	m_fRotateY	= fRotateY; 
	m_fRotateZ	= fRotateZ;

	DirtyMatrixModelRotate();
}

//-----------------------------------------------------------------------------
// 函数：SetRotateInit()
// 描述：设置模型坐标系下的初始旋转（用于校正模型的建模朝向）
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetRotateInit(float fRotateX, float fRotateY, float fRotateZ)
{
    m_fRotateInitX	= fRotateX;
    m_fRotateInitY	= fRotateY;
    m_fRotateInitZ	= fRotateZ;

    DirtyMatrixModelRotate();
}

//----------------------------------------------------------------------------
// 函数：SetTrans()
// 描述：设置模型坐标系下的平移
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetTrans(float fTransX, float fTransY, float fTransZ)
{
	m_fTransX	= fTransX; 
	m_fTransY	= fTransY; 
	m_fTransZ	= fTransZ;

	DirtyMatrixModelTrans();
}

//----------------------------------------------------------------------------
// 函数：SetTransInit()
// 描述：设置模型坐标系下的初始平移（用于校正模型的建模原点）
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetTransInit(float fTransX, float fTransY, float fTransZ)
{
    m_fTransInitX	= fTransX;
    m_fTransInitY	= fTransY;
    m_fTransInitZ	= fTransZ;

    DirtyMatrixModelTrans();
}

//----------------------------------------------------------------------------
// 函数：GetRealtimeScale()
// 描述：获取模型的实时缩放系数
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::GetRealtimeScale(float& fScaleX, float& fScaleY, float& fScaleZ)	
{ 
	float fInnerScaleX, fInnerScaleY, fInnerScaleZ;
	GetInnerScale(fInnerScaleX, fInnerScaleY, fInnerScaleZ);

	fScaleX = m_fScaleX * fInnerScaleX;
	fScaleY = m_fScaleY * fInnerScaleY;
	fScaleZ = m_fScaleZ * fInnerScaleZ;
}

//----------------------------------------------------------------------------
// 函数：GetInnerScale()
// 描述：获取系统内部自动计算的缩放比（如统一缩放、自动缩放等）
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::GetInnerScale(float& fScaleX, float& fScaleY, float& fScaleZ)
{
	CVBF_3DEnvironment& env = VBF_Get3DEnvironment();
	IVBF_3DPlot* pI3DPlot = env.m_pI3DPlot;

	fScaleX = 1.0f;					
	fScaleY = 1.0f;				
	fScaleZ = 1.0f;

	if(m_bEnableFixedSizeInPixels)
	{ 
        fScaleX = m_fFixedSizeInPixels;
        fScaleY = m_fFixedSizeInPixels;
        fScaleZ = m_fFixedSizeInPixels;

        const osg::BoundingBox& box = this->GetBoundingBoxInModel();
		float fBoxSizeX = box.xMax()- box.xMin();
		float fBoxSizeY = box.yMax()- box.yMin();
		float fBoxSizeZ = box.zMax()- box.zMin();

		if(fBoxSizeX > 0.0f) fScaleX /= fBoxSizeX;
        if(fBoxSizeY > 0.0f) fScaleY /= fBoxSizeX;
        if(fBoxSizeZ > 0.0f) fScaleZ /= fBoxSizeX;
	}
	else if(m_bEnableAutoScale)
	{ 
        if(this->m_pIParent!=NULL)
		{
			fScaleX = 1.0;
			fScaleY = 1.0;
			fScaleZ = 1.0;
		}
		else
		{
			float fAutoScale = (pI3DPlot!=NULL)? pI3DPlot->GetPointMarkAutoScale() : 1.0f;
			fScaleX = fAutoScale;
			fScaleY = fAutoScale;
			fScaleZ = fAutoScale;
		}
	}
	
	// 注意：考虑缩放比的调整系数
    if(m_bEnableScaleDelta && (NULL==this->m_pIParent || !this->m_pIParent->IsPointMarkModel()))
	{ 
		float fScaleDelta = (pI3DPlot!=NULL)? pI3DPlot->GetPointMarkScaleDelta() : 1.0f;
		fScaleX *= fScaleDelta;
		fScaleY *= fScaleDelta;
		fScaleZ *= fScaleDelta;
	}
}

/****
//----------------------------------------------------------------------------
// 函数：GetParentRealtimeScale()
// 描述：获取父模型的实时缩放系数
//----------------------------------------------------------------------------
template<class T> 
void CVBF_MarkModelPointImpl<T>::GetParentRealtimeScale(float& fScaleX, float& fScaleY, float& fScaleZ)
{
	if( NULL==m_pIParent || !m_pIParent->IsPointMarkModel() ) 
	{
		fScaleX = 1.0;
		fScaleY = 1.0;
		fScaleZ = 1.0;
		return;
	}

	IVBF_MarkModelPoint* pIParentPoint = (IVBF_MarkModelPoint*)m_pIParent;

	float fScaleX0 = 1.0, fScaleY0 = 1.0, fScaleZ0 = 1.0;
	pIParentPoint->GetRealtimeScale(fScaleX0, fScaleY0, fScaleZ0);

	float fScaleX1 = 1.0, fScaleY1 = 1.0, fScaleZ1 = 1.0;
//	pIParentPoint->GetParentRealtimeScale(fScaleX1, fScaleY1, fScaleZ1);  // 需要吗？（杜莹修改：2013-11-25）

	fScaleX = fScaleX0 * fScaleX1;
	fScaleY = fScaleY0 * fScaleY1;
	fScaleZ = fScaleZ0 * fScaleZ1;
}
***/

//----------------------------------------------------------------------------
// 函数：GetParentRealtimeScale()
// 描述：获取父模型的实时缩放系数
//----------------------------------------------------------------------------
template<class T> 
void CVBF_MarkModelPointImpl<T>::GetParentRealtimeScale(float& fScaleX, float& fScaleY, float& fScaleZ)
{
	fScaleX = 1.0f;
	fScaleY = 1.0f;
	fScaleZ = 1.0f;

    if( NULL==this->m_pIParent || !this->m_pIParent->IsPointMarkModel() )
	{
		return;
	}

	IVBF_MarkModel* pIMark   = this;
	IVBF_MarkModel* pIParent = pIMark->GetParent();

	while(pIParent!=NULL)
	{
		if(pIMark->IsPointMarkModel() && pIParent->IsPointMarkModel())
		{
			IVBF_MarkModelPoint* pIMarkPoint   = (IVBF_MarkModelPoint*)pIMark;
			IVBF_MarkModelPoint* pIParentPoint = (IVBF_MarkModelPoint*)pIParent;

			if(pIMarkPoint->IsScaleWithParentEnabled() && !pIMarkPoint->IsRotateWithParentEnabled())
			{
				float fScaleX0, fScaleY0, fScaleZ0;
				pIParentPoint->GetScale(fScaleX0, fScaleY0, fScaleZ0);

				fScaleX *= fScaleX0;
				fScaleY *= fScaleY0;
				fScaleZ *= fScaleZ0;
			}
		}

		// 再获取上一个父节点
		pIMark   = pIParent;
		pIParent = pIMark->GetParent();
	}
}

//----------------------------------------------------------------------------
// 函数：GetParentRealtimeScale()
// 描述：获取所有父模型的旋转矩阵
//----------------------------------------------------------------------------
template<class T> 
osg::Matrixd CVBF_MarkModelPointImpl<T>::GetParentRotateMatrix()
{
	osg::Matrixd matRotate;
	matRotate.makeIdentity();

    if( NULL==this->m_pIParent || !this->m_pIParent->IsPointMarkModel() )
	{
		return matRotate;
	}

	IVBF_MarkModel* pIMark   = this;
	IVBF_MarkModel* pIParent = pIMark->GetParent();

	while(pIParent!=NULL)
	{
		if(pIMark->IsPointMarkModel() && pIParent->IsPointMarkModel())
		{
			IVBF_MarkModelPoint* pIMarkPoint   = (IVBF_MarkModelPoint*)pIMark;
			IVBF_MarkModelPoint* pIParentPoint = (IVBF_MarkModelPoint*)pIParent;

			if(pIMarkPoint->IsRotateWithParentEnabled() && !pIMarkPoint->IsScaleWithParentEnabled())
			{
				matRotate *= pIParentPoint->GetRotateMatrix();
			}
		}

		// 再获取上一个父节点
		pIMark   = pIParent;
		pIParent = pIMark->GetParent();
	}

	return matRotate;
}

//-----------------------------------------------------------------------------
// 函数：UpdatePos()
// 描述：更新模型的位置
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::UpdatePos()
{
    if(m_bDirtyNodeLocator)
    {
        CreateNodeLocator(m_bLocateRelative);
        m_bDirtyNodeLocator = false;
    }

    if(this->m_bDirtyPosGeo)
    {
        if(this->m_pIParent!=NULL && this->m_pIParent->IsPointMarkModel())  // 有点状父模型，地理坐标表示相对定位
        {
            if(m_piNodeModelToWorld.valid()) m_piNodeModelToWorld->setMatrix( osg::Matrix::translate(this->m_vPosGeo) );
        }
        else  // 没有父模型或父模型不是点状，地理坐标表示绝对定位
        {
            if(m_piLocator.valid()) m_piLocator->setPosition(this->m_vPosGeo);

            // 使定位节点与m_piLocator的运算同步
            osgEarth::Util::ObjectLocatorNode* pLocatorNode = dynamic_cast<osgEarth::Util::ObjectLocatorNode*>(m_piNodeModelToWorld.get());
            if(pLocatorNode) pLocatorNode->update();
        }

        this->m_bDirtyPosGeo = false;
    }
}


//-----------------------------------------------------------------------------
// 函数：Update()
// 描述：更新 (每帧绘制前调用)
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::Update()
{	
    // 添加到场景图的父节点
    this->AddToParentNode();

    // 更新某些场景图节点的属性
    UpdateSGNode();

    if(!this->m_bVisible) return false;

	// 创建模型节点
    if(this->m_bDirtyModel)
	{
        this->UpdateModelNode();
        this->m_bDirtyModel = false;
    }
	
	// 步进到下一个插值点
	StepIt();

	// 如果启用地形跟随，需要实时计算高程值
    if( NULL==this->m_pIParent && m_bEnableMatchTerrain )
	{
        osg::Vec3d vGeo = this->m_vPosGeo;
        if( this->m_ipContext->GetElevationAvail(this->m_opCamera.get(),vGeo.x(), vGeo.y(), vGeo.z()) )
        {
			vGeo.z() += 0.1;  // 微调，避免钻地
            this->SetGeoPos(vGeo);
		}
	}

	// 更新模型的位置
	UpdatePos();

	// 矩阵变换
	Transform();

	// 根据视点到模型的距离，判断模型/属性是否在可见距离内
	this->ClipByDist();

	// 地球背面的裁剪
	ClipByEarth();

	// 更新所有子模型 
    this->UpdateChildren();

    // 更新所有属性（属性需要在Transform()函数之后更新）
    this->UpdateAttrs();

    // 更新包围盒节点
    if(this->m_bDirtyBoundingBoxNode)
	{
		this->UpdateBoundingBox();
        this->m_bDirtyBoundingBoxNode = false;
	}

	// 更新渲染状态
    if(this->m_bDirtyStateSet)
	{
        this->SetStateSet();
        this->m_bDirtyStateSet = false;
	}

    // 模型动作/特效
    this->UpdateByActions();
    this->UpdateByEffects();

	return true;
}

//-----------------------------------------------------------------------------
// 函数：NeedAutoTransformNode()
// 描述：判断是否需要挂接AutoTransform节点
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::NeedAutoTransformNode()
{
	bool bNeed = (m_bEnableFixedSizeInPixels ||
				 (m_nViewMode!=VBF_VIEW_MODE_NORMAL && m_nViewMode!=VBF_VIEW_MODE_HORIZON));

	return bNeed;
}

//-----------------------------------------------------------------------------
// 函数：UpdateSGNode()
// 描述：更新某些场景图节点的属性
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::UpdateSGNode()
{
    CVBF_MarkModelImpl<T>::UpdateSGNode();

    // 说明：如果需要添加AutoTransform节点，挂接顺序为：
/*  m_piNodeRoot->addChild(m_piNodeModelToWorld);
    m_piNodeModelToWorld->addChild(m_piNodeTransformAuto);
    m_piNodeTransformAuto->addChild(m_piNodeTransformModel);
    m_piNodeTransformModel->addChild(m_piNodeGroup);
*/
    // 是否需要添加/移除AutoTransform节点
    if(m_bDirtyAutoTransformNode && m_piNodeTransformAuto.valid() && m_piNodeModelToWorld.valid() && m_piNodeTransformModel.valid())
    {
        // 判断原来是否有父节点
        bool bHadParent = (m_piNodeTransformAuto->getNumParents()>0);

        // 判断本次是否需要挂接AutoTransform节点
        bool bNeedNow = NeedAutoTransformNode();

        // 原来没有父节点，现在需要，说明需要挂接AutoTransform节点
        if(!bHadParent && bNeedNow)
        {
            m_piNodeTransformAuto->addChild(m_piNodeTransformModel);
            m_piNodeModelToWorld->replaceChild(m_piNodeTransformModel, m_piNodeTransformAuto);

            // 注意：恢复节点的初始状态
            m_piNodeTransformAuto->setAutoScaleToScreen(m_bEnableFixedSizeInPixels);  // 设置为true时，节点固定像素大小
            m_piNodeTransformAuto->setAutoRotateMode(osg::AutoTransform::NO_ROTATION);
            m_piNodeTransformAuto->setRotation(osg::Quat(0,0,0,1));
        }
        else if(bHadParent && !bNeedNow) // 原来已经有父节点，说明需要移除AutoTransform节点
        {
            m_piNodeModelToWorld->replaceChild(m_piNodeTransformAuto, m_piNodeTransformModel);
            m_piNodeTransformAuto->removeChildren(0, m_piNodeTransformAuto->getNumChildren());
        }

        m_bDirtyAutoTransformNode = false;
    }
}

//-----------------------------------------------------------------------------
// 函数：Transform()
// 描述：矩阵变换（每帧绘制前调用）
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::Transform()
{
	// 判断是否随父模型变换
	bool bWithParent = true;

	// 父模型是点状模型
    if( this->m_pIParent!=NULL && this->m_pIParent->IsPointMarkModel() )
	{
		bWithParent = (m_bScaleWithParent && m_bRotateWithParent);
		
		// 随父模型变换：  需要把子模型的根节点挂接到父模型的Group节点下，即m_piNodeGroup节点下
		// 不随父模型变换：需要把子模型的根节点挂接到父模型的定位节点下，即m_piNodeModelToWorld节点下
        if(this->m_piNodeRoot.valid())
		{
            IVBF_MarkModelPoint* pIParentPoint = (IVBF_MarkModelPoint*)this->m_pIParent;

            osg::IVBF_SGNodeGroup* pParentOld = dynamic_cast<osg::IVBF_SGNodeGroup*>(this->m_piNodeRoot->getParent(0));
			osg::IVBF_SGNodeGroup* pParentNew = (bWithParent)? pIParentPoint->GetGroupNode() : pIParentPoint->GetModelToWorldNode();
			if(pParentOld!=pParentNew)
			{
				this->SetParentNode(pParentNew);
				this->AddToParentNode();
			}
		}
	}

	// 随父模型变换
	if(bWithParent)
	{
		CalMatrixModel();
	}
	else // 不随父模型变换
	{
		CalMatrixModelScale();
		CalMatrixModelRotate();
		CalMatrixModelTrans();

		osg::Matrixd matScale = m_matModelScale;
		if(m_bScaleWithParent)
		{
			float fScaleX, fScaleY, fScaleZ;
			GetParentRealtimeScale(fScaleX, fScaleY, fScaleZ);
			
			matScale(0,0) *= fScaleX;
			matScale(1,1) *= fScaleY;
			matScale(2,2) *= fScaleZ;
		}

		osg::Matrixd matRotateWithParent;
		matRotateWithParent.makeIdentity();
		if(m_bRotateWithParent)
		{
			matRotateWithParent = GetParentRotateMatrix();
		}

		// 相对于父模型的平移
		osg::Matrixd matMove;
		MatrixMove(matMove);

		// 定位节点不再启用
		m_piNodeModelToWorld->setMatrix(osg::Matrix::identity());

		// 注意：矩阵相乘的顺序!
		osg::Matrixd matLocal = matScale * m_matModelRotate * m_matModelTrans * matMove * matRotateWithParent; 
		m_piNodeTransformModel->setMatrix(matLocal);
	}

    // 通过自动变化矩阵，实现不同的观察方式
    TransformByViewMode();
}

//-----------------------------------------------------------------------------
// 函数：TransformByViewMode()
// 描述：通过自动变换矩阵，实现不同的观察方式
// 说明：该函数要求模型的初始姿态是平行于地面的，即模型坐标系的z轴垂直于地面
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::TransformByViewMode()
{
    // 需要利用矩阵变换实现各种显示模式
    if(!m_piNodeTransformAuto.valid()) return;

    // 设置为true时，节点固定像素大小
    if(m_bDirtyFixedSizeInPixels)
    {
        m_piNodeTransformAuto->setAutoScaleToScreen(m_bEnableFixedSizeInPixels);
        m_bDirtyFixedSizeInPixels = false;
    }

    // 以下两种模式下，每帧都需要变换矩阵
    if(m_nViewMode==VBF_VIEW_MODE_BILLBOARD_H || m_nViewMode==VBF_VIEW_MODE_BILLBOARD_V)
    {

        // 获取视点的方位角
        IVBF_GlobalDataPerView* pData = VBF_Get3DGlobalData(this->m_opView.get());
        double dAngleH = - pData->GetAngleH();

        osg::Quat quat(0, 0, 0, 1);

        if(m_nViewMode==VBF_VIEW_MODE_BILLBOARD_H)		// 水平布告牌
        {
            quat.makeRotate(osg::inDegrees(dAngleH), 0.0, 0.0f, 1.0f);
        }
        else if(m_nViewMode==VBF_VIEW_MODE_BILLBOARD_V)	// 垂直布告牌
        {
            osg::Quat quatX, quatZ;
            quatX.makeRotate(osg::inDegrees(90.0),    1.0, 0.0, 0.0);	// 先绕X轴旋转90度
            quatZ.makeRotate(osg::inDegrees(dAngleH), 0.0, 0.0, 1.0);	// 再绕Z轴旋转dAngleH
            quat = quatX * quatZ;
        }

        m_piNodeTransformAuto->setAutoRotateMode(osg::AutoTransform::NO_ROTATION);
        m_piNodeTransformAuto->setRotation(quat);
        return;
    }

    if(m_bDirtyViewMode)
    {
        // 完全布告牌：不需要每帧都变换矩阵
        if(m_nViewMode==VBF_VIEW_MODE_BILLBOARD_HV)
        {
            m_piNodeTransformAuto->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
            m_piNodeTransformAuto->setRotation(osg::Quat(0,0,0,1));
        }

        m_bDirtyViewMode = false;
    }
}

//-----------------------------------------------------------------------------
// 函数：CalMatrixModel()
// 描述：重新计算模型坐标系下的变换矩阵
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::CalMatrixModel()
{
	CalMatrixModelScale();
	CalMatrixModelRotate();
	CalMatrixModelTrans();

	// 重新计算局部变换矩阵
	if(m_bDirtyMatrixModel)
	{
		m_matModel = m_matModelScale * m_matModelRotate * m_matModelTrans;
		if(m_piNodeTransformModel.valid()) m_piNodeTransformModel->setMatrix( m_matModel );

		// 重新计算包围盒
        this->DirtyBoundingBoxInModel();
        this->DirtyBoundingBoxInWorld();

		m_bDirtyMatrixModel = false;
	}
}

//-----------------------------------------------------------------------------
// 函数：CalMatrixModelScale()
// 描述：重新计算模型坐标系下的缩放矩阵
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::CalMatrixModelScale()
{
	if(m_bDirtyMatrixModelScale)
	{
		float fScaleX, fScaleY, fScaleZ;
		GetRealtimeScale(fScaleX, fScaleY, fScaleZ);

		m_matModelScale = osg::Matrix::scale(fScaleX, fScaleY, fScaleZ);

		m_bDirtyMatrixModelScale = false;
	}
}

//-----------------------------------------------------------------------------
// 函数：CalMatrixModelRotate()
// 描述：重新计算模型坐标系下的旋转矩阵
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::CalMatrixModelRotate()
{
	if(!m_bDirtyMatrixModelRotate) return;
	
	if(m_matModelRotateOut.isSet()) // 直接使用外部设置的旋转矩阵（模型坐标系下）
	{
		m_matModelRotate = m_matModelRotateOut.value();
		m_matModelRotateOut.unset();
	}
	else
	{
		float fRotateZ = osg::DegreesToRadians( m_fRotateZ + m_fRotateInitZ );  // 度 -> 弧度

		// 注意：如果模型始终平行于地面，只允许其绕Z轴旋转
		if(m_nViewMode==VBF_VIEW_MODE_HORIZON)
		{
			m_matModelRotate = osg::Matrix::rotate( fRotateZ, osg::Vec3f(0,0,1) );
		}
		else
		{
			float fRotateX = osg::DegreesToRadians( m_fRotateX + m_fRotateInitX );  // 度 -> 弧度
			float fRotateY = osg::DegreesToRadians( m_fRotateY + m_fRotateInitY );

			osg::Vec3f vAxisX(1, 0, 0);
			osg::Vec3f vAxisY(0, 1, 0);
			osg::Vec3f vAxisZ(0, 0, 1);

			switch(m_nRotateOrder)
			{
				case VBF_ROTATE_ORDER_XYZ:  { m_matModelRotate = osg::Matrix::rotate( fRotateX, vAxisX, fRotateY, vAxisY, fRotateZ, vAxisZ ); break; }
				case VBF_ROTATE_ORDER_XZY:  { m_matModelRotate = osg::Matrix::rotate( fRotateX, vAxisX, fRotateZ, vAxisZ, fRotateY, vAxisY ); break; }
				case VBF_ROTATE_ORDER_YXZ:  { m_matModelRotate = osg::Matrix::rotate( fRotateY, vAxisY, fRotateX, vAxisX, fRotateZ, vAxisZ ); break; }
				case VBF_ROTATE_ORDER_YZX:  { m_matModelRotate = osg::Matrix::rotate( fRotateY, vAxisY, fRotateZ, vAxisZ, fRotateX, vAxisX ); break; }
				case VBF_ROTATE_ORDER_ZXY:  { m_matModelRotate = osg::Matrix::rotate( fRotateZ, vAxisZ, fRotateX, vAxisX, fRotateY, vAxisY ); break; }
				case VBF_ROTATE_ORDER_ZYX:  { m_matModelRotate = osg::Matrix::rotate( fRotateZ, vAxisZ, fRotateY, vAxisY, fRotateX, vAxisX ); break; }
			}
		}
	}

	m_bDirtyMatrixModelRotate = false;
}

//-----------------------------------------------------------------------------
// 函数：CalMatrixModelTrans()
// 描述：重新计算模型坐标系下的平移矩阵
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::CalMatrixModelTrans()
{
	if(m_bDirtyMatrixModelTrans)
	{
        m_matModelTrans = osg::Matrix::translate(m_fTransX+m_fTransInitX, m_fTransY+m_fTransInitY, m_fTransZ+m_fTransInitZ);
		m_bDirtyMatrixModelTrans = false;
	}
}

//-----------------------------------------------------------------------------
// 函数：MatrixMove()
// 描述：重新计算模型坐标系下的平移矩阵
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::MatrixMove(osg::Matrixd& matMove)
{
	matMove.makeIdentity();

    const osg::Vec3d& vPos = this->GetPos();

	matMove(3,0) = vPos.x();
	matMove(3,1) = vPos.y();
	matMove(3,2) = vPos.z();
}

//-----------------------------------------------------------------------------
// 函数：EnableScaleWithParent()
// 描述：是否随父模型缩放
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::EnableScaleWithParent(bool bEnable)	
{ 
	if(bEnable==m_bScaleWithParent) return;

	m_bScaleWithParent = bEnable; 
	DirtyMatrixModelScale(); 
} 

//-----------------------------------------------------------------------------
// 函数：EnableRotateWithParent()
// 描述：是否随父模型旋转
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::EnableRotateWithParent(bool bEnable)	
{ 
	if(bEnable==m_bRotateWithParent) return;

	m_bRotateWithParent = bEnable; 
	DirtyMatrixModelRotate(); 
}
 
//-----------------------------------------------------------------------------
// 函数：EnableFixedSizeInPixels()
// 描述：是否允许设置固定大小 (单位：像素)
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::EnableFixedSizeInPixels(bool bEnable)	
{ 
	if(m_bEnableFixedSizeInPixels==bEnable) return;

	m_bEnableFixedSizeInPixels = bEnable; 
    DirtyMatrixModelScale();

    m_bDirtyFixedSizeInPixels = true;

    // 是否需要改变AutoTransform节点的挂接状态
    m_bDirtyAutoTransformNode = true;
}

//-----------------------------------------------------------------------------
// 函数：ClipByEarth()
// 描述：判断是否位于地球背面
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::ClipByEarth()
{
    if(!this->m_bEnableClipByEarth) return;
    if(this->m_bEnableDepthTest) return;
    if(!this->m_piNodeRoot.valid() || this->m_piNodeRoot->getNodeMask()==0) return;  // 已经被裁剪掉

    bool bCliped = ::VBF_IsClipedByEarth(this->m_opView.get(),this->m_ipContext->GetEllipsoid()->getRadiusPolar(),this->GetWorldPos());
    if(bCliped)
    {
        this->m_piNodeRoot->setNodeMask(0);
    }
}

//-----------------------------------------------------------------------------
// 函数：SetViewMode()
// 描述：设置模型的观察模式
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetViewMode(EVBF_VIEW_MODE nMode)
{
    if(m_nViewMode==nMode) return;

    m_nViewMode = nMode;

    m_bDirtyViewMode = true;

    // 是否需要改变AutoTransform节点的挂接状态
    m_bDirtyAutoTransformNode = true;
}

//-----------------------------------------------------------------------------
// 函数：GetModelToWorldMatrix()
// 描述：获取转换矩阵：模型坐标系 --> 世界坐标系
//-----------------------------------------------------------------------------
template<class T>
osg::Matrixd CVBF_MarkModelPointImpl<T>::GetModelToWorldMatrix()
{
	osg::Matrixd matWorld;
	matWorld.makeIdentity();

	if( m_piNodeTransformModel.valid() )
	{
		CVBF_NodeUtil::GetNodeMatrixInWorld(m_piNodeTransformModel, matWorld);
	}

	return matWorld;
}

//-----------------------------------------------------------------------------
// 函数：GetWorldToModelMatrix()
// 描述：获取转换矩阵：世界坐标系 --> 模型坐标系 
//-----------------------------------------------------------------------------
template<class T>
osg::Matrixd CVBF_MarkModelPointImpl<T>::GetWorldToModelMatrix()
{
	osg::Matrixd matWorld = GetModelToWorldMatrix();
	osg::Matrixd matModel = osg::Matrix::inverse(matWorld);
	return matModel;
}

//-----------------------------------------------------------------------------
// 函数：PointWorldToModel()
// 描述：把点坐标由世界坐标系变换到模型坐标系
//-----------------------------------------------------------------------------
template<class T>
osg::Vec3d CVBF_MarkModelPointImpl<T>::PointWorldToModel(const osg::Vec3d& ptWorld)
{
	osg::Vec3d ptModel = ptWorld * GetWorldToModelMatrix();
	return ptModel;
}

//----------------------------------------------------------------------------
// 函数：Vector0ToPointInModelIntersectWithEarth()
// 描述：计算从模型原点到模型中某点的向量（模型坐标系下）与地球的交点，
//      返回交点及其与模型原点的距离（世界坐标系下）
// 参数：dHeightAdjust -- 高度调整值，可以设置为0.0
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::Vector0ToPointInModelIntersectWithEarth(const osg::Vec3d& vPointInModel, double dHeightAdjust,
								                                         osg::Vec3d& ptIntersect, double& dDist)
{
	// 线段起点（世界坐标系下）
	osg::Vec3d ptStart = this->GetPos();
	if(this->m_pIParent!=NULL)
	{
		ptStart = ptStart * GetModelToWorldMatrix(); // 子模型
	}

	// 线段终点（世界坐标系下）
	osg::Vec3d ptEnd = vPointInModel * GetModelToWorldMatrix();

    // 线段求交
    return ::VBF_LineSegIntersectEllipsoid(ptStart, ptEnd, dHeightAdjust, ptIntersect, dDist);
}

//----------------------------------------------------------------------------
// 函数：Vector0ToPointInModelIntersectWithEarth()
// 描述：计算某向量（模型坐标系下）与地球的交点，返回交点及其与向量起点的距离（世界坐标系下）
// 参数：dHeightAdjust -- 高度调整值，可以设置为0.0
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::VectorInModelIntersectWithEarth(const osg::Vec3d& vPointInModelStart, const osg::Vec3d& vPointInModelEnd, 
	                                                             double dHeightAdjust, osg::Vec3d& ptIntersect, double& dDist)
{
	// 线段起点（世界坐标系下）
	osg::Vec3d ptStart = vPointInModelStart * GetModelToWorldMatrix();

	// 线段终点（世界坐标系下）
	osg::Vec3d ptEnd = vPointInModelEnd * GetModelToWorldMatrix();

    // 线段求交
    return ::VBF_LineSegIntersectEllipsoid(ptStart, ptEnd, dHeightAdjust, ptIntersect, dDist);
}

//-----------------------------------------------------------------------------
// 函数：SetDeltaRotate()
// 描述：设置模型坐标系下累加的旋转角（在当前值的基础上）
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetDeltaRotate(float fDeltaRotateX, float fDeltaRotateY, float fDeltaRotateZ)
{
	SetRotate(m_fRotateX+fDeltaRotateX, m_fRotateY+fDeltaRotateY, m_fRotateZ+fDeltaRotateZ);
}

//-----------------------------------------------------------------------------
// 函数：SetDeltaScale()
// 描述：设置模型坐标系下累加的缩放比（在当前值的基础上）
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetDeltaScale(float fDeltaScaleX, float fDeltaScaleY, float fDeltaScaleZ)
{
	SetScale(m_fScaleX*(1.0f+fDeltaScaleX), m_fScaleY*(1.0f+fDeltaScaleY), m_fScaleZ*(1.0f+fDeltaScaleZ));
}

//-----------------------------------------------------------------------------
// 函数：SetDeltaTrans()
// 描述：设置模型坐标系下累加的平移值（在当前值的基础上）
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetDeltaTrans(float fDeltaTransX, float fDeltaTransY, float fDeltaTransZ)
{
	SetTrans(m_fTransX+fDeltaTransX, m_fTransY+fDeltaTransY, m_fTransZ+fDeltaTransZ);
}

//-----------------------------------------------------------------------------
// 函数：SetDeltaTransGeo()
// 描述：设置模型坐标系下累加的地理坐标平移值（在当前值的基础上）
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetDeltaTransGeo(float fDeltaTransX, float fDeltaTransY, float fDeltaTransZ)
{
    osg::Vec3d vGeoPos = this->GetGeoPos();

    vGeoPos.x()+= fDeltaTransX;
    vGeoPos.y()+= fDeltaTransY;
    vGeoPos.z()+= fDeltaTransZ;

    this->SetGeoPos(vGeoPos);
}

//-----------------------------------------------------------------------------
// 函数：SetUnTransformed()
// 描述：恢复模型坐标系下模型初始状态，即无任何旋转角/缩放比/平移值
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetUnTransformed()
{
	m_fRotateX = 0.0f;
	m_fRotateY = 0.0f;
	m_fRotateZ = 0.0f;

	m_fScaleX = 1.0f;
	m_fScaleY = 1.0f;
	m_fScaleZ = 1.0f;

	m_fTransX = 0.0f;
	m_fTransY = 0.0f;
	m_fTransZ = 0.0f;

	DirtyMatrixModelRotate();
	DirtyMatrixModelScale();
	DirtyMatrixModelTrans();
}

//-----------------------------------------------------------------------------
// 函数：SetRotateMatrixOut()
// 描述：直接使用外部设置的旋转矩阵（模型坐标系下）
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetRotateMatrixOut(const osg::Matrixd& mat)
{
	m_matModelRotateOut.mutable_value()  = mat;
	m_matModelRotateOutForWrite.mutable_value() = mat;

	DirtyMatrixModelRotate();
}

//-----------------------------------------------------------------------------
// 函数：Contains()
// 描述：判断是否包含某点
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::Contains(const osg::Vec3d& ptWorld)
{
	osg::Vec3d ptModel;
	double dDist;

	return Contains(ptWorld, ptModel, dDist);
}

//-----------------------------------------------------------------------------
// 函数：SetParent()
// 描述：给子模型设置新的父模型
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetParent(IVBF_MarkModel* pIParent)
{ 
	CVBF_MarkModelImpl<T>::SetParent(pIParent);

	// 如果父模式不是点状模型，不随父模型缩放和旋转
	if( pIParent!=NULL && !pIParent->IsPointMarkModel() )
	{
		EnableScaleWithParent(false);
		EnableRotateWithParent(false);
	}

    // 使定位节点失效
    m_bDirtyNodeLocator = true;
    m_bLocateRelative   = (pIParent!=NULL && pIParent->IsPointMarkModel());
}

//-----------------------------------------------------------------------------
// 函数：PushOnePoint()
// 描述：向插值点队列尾部中追加一个点
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::PushOnePoint(const VBF_TRAILPOINTINNER& point)
{
    m_vInterPoints.push(point);
}

//-----------------------------------------------------------------------------
// 函数：GetNumInterPoints()
// 描述：根据仿真时间步长方式，计算当前需要插值的点数
//-----------------------------------------------------------------------------
template<class T>
int CVBF_MarkModelPointImpl<T>::GetNumInterPoints(const VBF_TRAILPOINTINNER& ptBegin, const VBF_TRAILPOINTINNER& ptEnd)
{
	// 获取帧速度
	double dFPS = ::VBF_GetFPS(this->m_pI3DMainCtrl);

	int nNumPoints = dFPS;
	if( m_nSimTimeMode==VBF_SIMTIME_MODE_FIXED )			// 定长
	{
		nNumPoints = (int)(m_fSimTimeStep * dFPS + 0.5);
	}
	else if( m_nSimTimeMode==VBF_SIMTIME_MODE_VARIABLE )	// 变长
	{
		// 根据两次数据点之间的时间差(秒)，计算需要插值的点数
        double dTimeInterval = CVBF_Timer::instance()->delta_s(ptBegin.timer.getStartTick(), ptEnd.timer.getStartTick());
        nNumPoints = (int)(dTimeInterval * dFPS + 0.5);
    }
	else if( m_nSimTimeMode==VBF_SIMTIME_MODE_REALTIME ) // 实时：不需要系统内部插值，直接使用StepGeoPos()中传递的坐标值
	{
		nNumPoints = 1;
	}

	return nNumPoints;
}

//-----------------------------------------------------------------------------
// 函数：Interpolate()
// 描述：路径插值 (同时对坐标、角度和时间进行插值)
// 参数：bIncludingEnd -- 插值后的点中是否需要包含终点
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::Interpolate(int nNumInsert, const VBF_TRAILPOINTINNER& ptBegin,
                                             const VBF_TRAILPOINTINNER& ptEnd, bool bIncludingEnd)
{
    // 特殊情况：避免被0除
    if(nNumInsert<=1)
    {
        if(bIncludingEnd) PushOnePoint(ptEnd);
        return;
    }

    // 便于书写
    const osg::Vec3d& vGeoBegin = ptBegin.vPosGeo;
    const osg::Vec3d& vGeoEnd   = ptEnd.vPosGeo;

    float fRotateXBegin = ptBegin.fRotateX;
    float fRotateYBegin = ptBegin.fRotateY;
    float fRotateZBegin = ptBegin.fRotateZ;

    float fRotateXEnd   = ptEnd.fRotateX;
    float fRotateYEnd   = ptEnd.fRotateY;
    float fRotateZEnd   = ptEnd.fRotateZ;

    // 工作1：坐标插值

    // 特殊处理经度跨越180度的情况 (2010-01-18)
    double dL       = vGeoEnd.x() - vGeoBegin.x();
    double dLTemp0	= vGeoBegin.x();
    double dLTemp1	= vGeoEnd.x();

    if(dL > 180)		dLTemp1 -= 360;
    else if(dL < -180)	dLTemp0 -= 360;

    dL = dLTemp1 - dLTemp0;

    // 第一种方法：基于椭球的插值 (适用于视点较远时)
//	CMCE_GisMath::GetRouteVertices( vGeoBegin, vGeoEnd, nNumVertices, pGeoVertices );

    // 第二种方法：简单的线性插值 (适用于视点较近时，有待修改)
    double dx = dL/(nNumInsert-1);
    double dy = (vGeoEnd.y() - vGeoBegin.y())/(nNumInsert-1);
    double dz = (vGeoEnd.z() - vGeoBegin.z())/(nNumInsert-1);

    // 工作2：角度插值

    // 避免角度差跨越180
    float fRotateXDelta  = fRotateXEnd - fRotateXBegin;
    float fRotateYDelta  = fRotateYEnd - fRotateYBegin;
    float fRotateZDelta  = fRotateZEnd - fRotateZBegin;

    // 特殊处理航向角
    float fRotateZTemp0	= fRotateZBegin;
    float fRotateZTemp1	= fRotateZEnd;

    if(fRotateZDelta > 180)
    {
        fRotateZTemp1 -= 360;
    }
    else if(fRotateZDelta < -180)
    {
        fRotateZTemp0 -= 360;
    }

    fRotateZDelta = fRotateZTemp1 - fRotateZTemp0;

    float fRotateXDeltaPerFrame	= 0.0f;
    float fRotateYDeltaPerFrame	= 0.0f;
    float fRotateZDeltaPerFrame	= 0.0f;

    fRotateXDeltaPerFrame  = fRotateXDelta/(nNumInsert-1);
    fRotateYDeltaPerFrame  = fRotateYDelta/(nNumInsert-1);
    fRotateZDeltaPerFrame  = fRotateZDelta/(nNumInsert-1);

    // 计算起点和终点之间的时间差，以便设置插值点的时间
    CVBF_Timer_t dDeltaTick = (ptEnd.timer.getStartTick() - ptBegin.timer.getStartTick())/(nNumInsert-1);

    // 工作3：将本次插值后的节点添加到队列中

    // 插入起点
    PushOnePoint(ptBegin);

    // 插入中间点
    for(int i=1; i<nNumInsert-1; i++)
    {
        // 插值后每帧实际的坐标
        osg::Vec3d vGeo;
        vGeo.x() = vGeoBegin.x() +  dx * i;
        vGeo.y() = vGeoBegin.y() +  dy * i;
        vGeo.z() = vGeoBegin.z() +  dz * i;

        if(vGeo.x() < -180)		vGeo.x() += 360;
        else if(vGeo.x() > 180)	vGeo.x() -= 360;

        // 插值后每帧实际的旋转角
        float fRotateXInter = fRotateXBegin + i * fRotateXDeltaPerFrame;
        float fRotateYInter = fRotateYBegin + i * fRotateYDeltaPerFrame;
        float fRotateZInter = fRotateZBegin + i * fRotateZDeltaPerFrame;

        if(fRotateZInter < 0) fRotateZInter += 360;

        VBF_TRAILPOINTINNER point(false, vGeo, fRotateXInter, fRotateYInter, fRotateZInter, "");
        point.timer.setStartTick( ptBegin.timer.getStartTick() + i * dDeltaTick );  // 对时间进行插值

        // 将节点添加到队列中
        PushOnePoint(point);
    }

    // 插入终点
    if(bIncludingEnd) PushOnePoint(ptEnd);
}

//-----------------------------------------------------------------------------
// 函数：StepIt()
// 描述：步进到下一个插值点
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::StepIt()
{
	int nNumPoints = m_vInterPoints.size();
    if(nNumPoints==0) return;

	// 步进模型的地理坐标
	m_TrailPoint = m_vInterPoints.front();

    this->SetGeoPos(m_TrailPoint.value().vPosGeo);
    SetRotate(m_TrailPoint.value().fRotateX, m_TrailPoint.value().fRotateY, m_TrailPoint.value().fRotateZ);

    // 该点运动完毕，可以删除了
    m_vInterPoints.pop();
}

template<class T>
void CVBF_MarkModelPointImpl<T>::StopStepIn()
{
    while( !m_vKeyPoints.empty() )
    {
        m_vKeyPoints.pop();
    }

    while( !m_vInterPoints.empty() )
    {
        m_vInterPoints.pop();
    }
}
//-----------------------------------------------------------------------------
// 函数：StepGeoPos()
// 描述：将模型的地理坐标步进到指定位置（需要插值）
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::StepGeoPos(const osg::Vec3d& vGeo, float fRotateX, float fRotateY, float fRotateZ, const std::string& strInfo/*=""*/)
{
    // 将该点记为关键点
    VBF_TRAILPOINTINNER ptNew(true, vGeo, fRotateX, fRotateY, fRotateZ, strInfo);

    // 实时：不需要系统内部插值，直接使用StepGeoPos()中传递的坐标值
    if( m_nSimTimeMode==VBF_SIMTIME_MODE_REALTIME )
    {
        // 只记录到插值点队列中即可，不需要记录为关键点
        PushOnePoint(ptNew);
        return;
    }

    // 如果是第一个关键点：不需要插值
    if( m_vKeyPoints.size()==0 )
    {
        PushOnePoint(ptNew);
    }
    else if( m_vKeyPoints.size()==1 || m_vInterPoints.empty() ) // 如果是第二个关键点（或者上次的插值点已经走完）：需要在两个关键点之间进行插值
    {
        const VBF_TRAILPOINTINNER& pt0 = m_vKeyPoints.back();
        const VBF_TRAILPOINTINNER& pt1 = ptNew;
        int nNumInsert = GetNumInterPoints(pt0, pt1);
        Interpolate(nNumInsert, pt0, pt1, true);

        // 插值后，即可删除上一个关键点，加入新的关键点
        m_vKeyPoints.pop();
    }
    else  // 如果是第三个及其以后的关键点：需要依次在如下三个点之间进行插值：当前步进点、上一个关键点、新关键点
    {
        // 此时还有尚未走完的插值点
        VBF_TRAILPOINTINNER        pt0 = m_vInterPoints.front();
        const VBF_TRAILPOINTINNER& pt1 = m_vKeyPoints.back();
        const VBF_TRAILPOINTINNER& pt2 = ptNew;

        // 注意：清空上次尚未走完的插值点
        while( !m_vInterPoints.empty() )
        {
            m_vInterPoints.pop();
        }

        if( m_nSimTimeMode==VBF_SIMTIME_MODE_FIXED )	// 定长
        {
            int nNumInsert = GetNumInterPoints(pt0, pt2);

            // 根据三个点形成的两条线段的长度比（概略计算即可），分配插值点数
            const osg::Vec3d& vGeo0 = pt0.vPosGeo;
            const osg::Vec3d& vGeo1 = pt1.vPosGeo;
            const osg::Vec3d& vGeo2 = pt2.vPosGeo;

            // 计算长度的平方
            double dDist01 = (vGeo1.x()-vGeo0.x())*(vGeo1.x()-vGeo0.x()) + (vGeo1.y()-vGeo0.y())*(vGeo1.y()-vGeo0.y());
            double dDist12 = (vGeo2.x()-vGeo1.x())*(vGeo2.x()-vGeo1.x()) + (vGeo2.y()-vGeo1.y())*(vGeo2.y()-vGeo1.y());

            // 计算第一条线段与两段线段长度和的比，由此分配插值点数
            float fRatio = sqrt( dDist01/(dDist01+dDist12) );

            int nNumInsert01 = (int)(nNumInsert * fRatio + 0.5f);
            int nNumInsert12 = nNumInsert - nNumInsert01;

            // 插值
            Interpolate(nNumInsert01, pt0, pt1, false);
            Interpolate(nNumInsert12, pt1, pt2, true);
        }
        else if( m_nSimTimeMode==VBF_SIMTIME_MODE_VARIABLE )	// 变长
        {
            // 根据两次数据点之间的时间差(秒)，计算需要插值的点数
            int nNumInsert01 = GetNumInterPoints(pt0, pt1);
            int nNumInsert12 = GetNumInterPoints(pt1, pt2);

            // 插值
            Interpolate(nNumInsert01, pt0, pt1, false);
            Interpolate(nNumInsert12, pt1, pt2, true);
        }

        // 插值后，即可删除上一个关键点，加入新的关键点
        m_vKeyPoints.pop();
    }

    // 加入新的关键点
    m_vKeyPoints.push(ptNew);
}

//-----------------------------------------------------------------------------
// 函数：GetTrailPoint()
// 描述：获取军标模型在当前帧的轨迹点信息（该信息通过StepGeoPos()函数设置，如果模型尚未开始运动，返回false）
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::GetTrailPoint(VBF_TRAILPOINT& ptTrail)
{
    if( !m_TrailPoint.isSet() ) return false;

    ptTrail = m_TrailPoint.value();
    return true;
}

//-----------------------------------------------------------------------------
// 函数：GetBoundingBoxInWorld()
// 描述：计算世界坐标系下的包围盒
//-----------------------------------------------------------------------------
template<class T>
const osg::BoundingBox& CVBF_MarkModelPointImpl<T>::GetBoundingBoxInWorld()
{
    if(this->m_bDirtyBoundingBoxInWorld)
    {
        // 注意：如果是绝对定位，需要确保此时已经计算过世界坐标
        if(!m_bLocateRelative && m_piNodeModelToWorld.valid())
        {
            const Matrix& mat = m_piNodeModelToWorld->getMatrix();
            if(!mat.isIdentity())
            {
                const osg::BoundingBox& boxInModel = this->GetBoundingBoxInModel();
                CVBF_NodeUtil::NodeBoundingBoxModelToWorld(m_piNodeTransformModel.get(), boxInModel, this->m_BoundingBoxInWorld);
                if(!this->m_BoundingBoxInWorld.valid()) return this->m_BoundingBoxInWorld;

                this->m_bDirtyBoundingBoxInWorld = false;
            }
        }
    }

    return this->m_BoundingBoxInWorld;
}

//-----------------------------------------------------------------------------
// 函数：GetWorldPos()
// 描述：获取模型的世界坐标
//-----------------------------------------------------------------------------
template<class T>
const osg::Vec3d& CVBF_MarkModelPointImpl<T>::GetWorldPos()
{
    // 如果世界坐标已经失效，需要重新计算
    if(this->m_bDirtyPosWorld)
    {
        // 如果没有父模型，直接通过地理坐标计算；否则需要通过局部变换节点计算
        if(NULL==this->GetParent())
        {
            this->m_ipContext->GeoToWorld(this->m_vPosGeo, true, this->m_vPosWorld);
        }
        else
        {
            if(!CVBF_NodeUtil::GetNodePosInWorld(m_piNodeTransformModel, this->m_vPosWorld)) return ::VBF_GetPosInvalid();
        }

        // 确保世界坐标有效
        if(::VBF_IsPosInvalid(this->m_vPosWorld)) return ::VBF_GetPosInvalid();

        this->m_bDirtyPosWorld = false;
    }

    return this->m_vPosWorld;
}

//-----------------------------------------------------------------------------
// 函数：CreateBoundingBoxNode()
// 描述：创建包围盒节点
//-----------------------------------------------------------------------------
template<class T>
osg::IVBF_SGNode* CVBF_MarkModelPointImpl<T>::CreateBoundingBoxNode()
{
    osg::IVBF_SGNode* pNodeDst = (this->GetChildCount()==0)? this->m_piNodeModel.get() : this->m_piNodeGroup.get();
    ref_ptr<osg::IVBF_SGNode> piNode = ::VBF_CreateBoundingBoxForNode(pNodeDst, this->m_BoundingBoxStyle);

    return piNode.release();
}

//-----------------------------------------------------------------------------
// 函数：GetBoundingBoxInGeo()
// 描述：计算地理坐标系下的包围盒
//-----------------------------------------------------------------------------
template<class T>
const osg::BoundingBoxd& CVBF_MarkModelPointImpl<T>::GetBoundingBoxInGeo()
{
    if(!this->m_bDirtyBoundingBoxInGeo) return this->m_BoundingBoxInGeo;

    // 注意：需要判断包围盒中心点的地理坐标和世界坐标是否有效
    osg::Vec3d ptCenterGeo = this->GetBoundingBoxCenterGeo();
    if(::VBF_IsPosInvalid(ptCenterGeo)) return this->m_BoundingBoxInGeo;

    osg::Vec3d ptCenterWorld = ::VBF_GetPosInvalid();
    this->m_ipContext->GeoToWorld(ptCenterGeo, true, ptCenterWorld);
    if(::VBF_IsPosInvalid(ptCenterWorld)) return this->m_BoundingBoxInGeo;

    // 注意：需要判断模型坐标系下的包围盒是否有效
    const osg::BoundingBox& boxInModel = this->GetBoundingBoxInModel();
    if(!boxInModel.valid()) return this->m_BoundingBoxInGeo;

    this->m_BoundingBoxInGeo.init();

    for(int i=0; i<8; i++)
    {
        float fScaleX, fScaleY, fScaleZ;
        GetRealtimeScale(fScaleX, fScaleY, fScaleZ);
        osg::Matrix matScale = osg::Matrix::scale(fScaleX/2, fScaleY/2, fScaleZ/2);

        osg::Vec3d ptWorld = boxInModel.corner(i)*matScale*m_matModelRotate + ptCenterWorld;

        // 世界坐标 --> 地理坐标
        osg::Vec3d ptGeo;
        this->m_ipContext->WorldToGeo(ptWorld, ptGeo);

        this->m_BoundingBoxInGeo.expandBy(ptGeo);
    }

    this->m_bDirtyBoundingBoxInGeo = false;

    return this->m_BoundingBoxInGeo;
}

//-----------------------------------------------------------------------------
// 函数：WriteModelToXML()
// 描述：写入模型本身的信息
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::WriteModelToXML(TiXmlElement* pElemMark)
{
	if(!CVBF_MarkModelImpl<T>::WriteModelToXML(pElemMark)) return false;

	// 写入：模型缩放比
	osg::Vec3f vScale(m_fScaleX, m_fScaleY, m_fScaleZ);
	::VBF_SetAttribute(pElemMark, "Scale", vScale);

	// 写入：模型旋转顺序
	::VBF_SetAttribute(pElemMark, "RotateOrder", (int)m_nRotateOrder);

    // 写入：模型旋转矩阵/旋转角
    if( m_matModelRotateOutForWrite.isSet() )
    {
        ::VBF_SetAttribute(pElemMark, "RotateMatrixOut", m_matModelRotateOutForWrite.value());
    }
    else
    {
        osg::Vec3f vRotate(m_fRotateX, m_fRotateY, m_fRotateZ);
        ::VBF_SetAttribute(pElemMark, "Rotate", vRotate);
    }

	// 写入：是否随父模型缩放/旋转
	::VBF_SetAttribute(pElemMark, "ScaleWithParent",  m_bScaleWithParent);
	::VBF_SetAttribute(pElemMark, "RotateWithParent", m_bRotateWithParent);

	::VBF_SetAttribute(pElemMark, "EnableFixedSizeInPixels", m_bEnableFixedSizeInPixels);	// 是否允许设置固定大小
	::VBF_SetAttribute(pElemMark, "EnableAutoScale",		 m_bEnableAutoScale);			// 是否允许自动调整大小
	::VBF_SetAttribute(pElemMark, "EnableScaleDelta",		 m_bEnableScaleDelta);			// 是否允许实时调整缩放比 (即能否通过热键实现统一缩放)
	::VBF_SetAttribute(pElemMark, "EnableMatchTerrain",		 m_bEnableMatchTerrain);		// 是否允许地形匹配
	::VBF_SetAttribute(pElemMark, "FixedSizeInPixels",		 m_fFixedSizeInPixels);			// 固定像素大小
	::VBF_SetAttribute(pElemMark, "ViewMode",				 (int)m_nViewMode);				// 观察方式

	return true;
}

//-----------------------------------------------------------------------------
// 函数：ReadModelFromXML()
// 描述：读取模型本身的信息
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::ReadModelFromXML(TiXmlElement* pElemMark)
{
	if(!CVBF_MarkModelImpl<T>::ReadModelFromXML(pElemMark)) return false;

	// 读取：模型缩放比
	osg::Vec3f vScale(m_fScaleX, m_fScaleY, m_fScaleZ);
	::VBF_QueryAttribute(pElemMark, "Scale", vScale);
	SetScale(vScale.x(), vScale.y(), vScale.z());

	// 读取：模型旋转顺序
	EVBF_ROTATE_ORDER nRotateOrder = GetRotateOrder();
	::VBF_QueryAttribute(pElemMark, "RotateOrder", (int&)nRotateOrder);
	SetRotateOrder(nRotateOrder);

	// 读取：模型旋转矩阵/旋转角
	osg::Matrixd matRotateOut;
	if( ::VBF_QueryAttribute(pElemMark, "RotateMatrixOut", matRotateOut) )
	{
		SetRotateMatrixOut(matRotateOut);
	}
	else
	{
		osg::Vec3f vRotate(m_fRotateX, m_fRotateY, m_fRotateZ);
		::VBF_QueryAttribute(pElemMark, "Rotate", vRotate);
		SetRotate(vRotate.x(), vRotate.y(), vRotate.z());
	}

	// 读取：是否随父模型缩放/旋转
	bool bScaleWithParent  = IsScaleWithParentEnabled();
	bool bRotateWithParent = IsRotateWithParentEnabled();
	::VBF_QueryAttribute(pElemMark, "ScaleWithParent",  bScaleWithParent);
	::VBF_QueryAttribute(pElemMark, "RotateWithParent", bRotateWithParent);

    bool bEnableFixedSizeInPixels   = IsFixedSizeInPixelsEnabled();
    bool bEnableAutoScale           = IsAutoScaleEnabled();
    bool bEnableScaleDelta          = IsScaleDeltaEnabled();
    bool bEnableMatchTerrain        = IsMatchTerrainEnabled();
    float fFixedSizeInPixels        = GetFixedSizeInPixels();
    EVBF_VIEW_MODE nViewMode        = GetViewMode();

	::VBF_QueryAttribute(pElemMark, "EnableFixedSizeInPixels", bEnableFixedSizeInPixels);	// 是否允许设置固定大小
	::VBF_QueryAttribute(pElemMark, "EnableAutoScale",		   bEnableAutoScale);			// 是否允许自动调整大小
	::VBF_QueryAttribute(pElemMark, "EnableScaleDelta",		   bEnableScaleDelta);			// 是否允许实时调整缩放比 (即能否通过热键实现统一缩放)
	::VBF_QueryAttribute(pElemMark, "EnableMatchTerrain",	   bEnableMatchTerrain);		// 是否允许地形匹配
	::VBF_QueryAttribute(pElemMark, "FixedSizeInPixels",	   fFixedSizeInPixels);			// 固定像素大小
	::VBF_QueryAttribute(pElemMark, "ViewMode",				   (int&)nViewMode);			// 观察方式

	// 更新相关参数
	EnableScaleWithParent(bScaleWithParent);
	EnableRotateWithParent(bRotateWithParent);

	EnableFixedSizeInPixels(bEnableFixedSizeInPixels);
	EnableAutoScale(bEnableAutoScale);
	EnableScaleDelta(bEnableScaleDelta);
	EnableMatchTerrain(bEnableMatchTerrain);
	SetFixedSizeInPixels(fFixedSizeInPixels);
	SetViewMode(nViewMode);

	return true;
}

//-----------------------------------------------------------------------------
// 函数：ExecuteScript()
// 描述：执行json脚本
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
    CVBF_MarkModelImpl<T>::ExecuteScript(conf);

	// 读取：模型缩放比
	osg::Vec3f vScale(m_fScaleX, m_fScaleY, m_fScaleZ);
	if( conf.getIfSet("Scale", vScale) )
	{
		SetScale(vScale.x(), vScale.y(), vScale.z());
	}

	// 读取：模型旋转顺序
	EVBF_ROTATE_ORDER nRotateOrder = GetRotateOrder();
	if( conf.getIfSet("RotateOrder", (int&)nRotateOrder) )
	{
		SetRotateOrder(nRotateOrder);
	}

	// 读取：模型旋转矩阵/旋转角
	osg::Matrixd matRotateOut;
	if( conf.getIfSet("RotateMatrixOut", matRotateOut) )
	{
		SetRotateMatrixOut(matRotateOut);
	}
	else
	{
		osg::Vec3f vRotate;
		GetRotate(vRotate.x(), vRotate.y(), vRotate.z());
		if( conf.getIfSet("Rotate", vRotate) )
		{
			SetRotate(vRotate.x(), vRotate.y(), vRotate.z());
		}

		osg::Vec3f vRotateInit;
		GetRotateInit(vRotateInit.x(), vRotateInit.y(), vRotateInit.z());
		if( conf.getIfSet("RotateInit", vRotateInit) )
		{
			SetRotateInit(vRotateInit.x(), vRotateInit.y(), vRotateInit.z());
		}
	}

	// 读取：整个模型的平移和初始平移（用于校正模型的建模原点）
	osg::Vec3f vTrans;
	GetTrans(vTrans.x(), vTrans.y(), vTrans.z());
	if( conf.getIfSet("Translate", vTrans) )
	{
		SetTrans(vTrans.x(), vTrans.y(), vTrans.z());
	}

	osg::Vec3f vTransInit;
	GetTransInit(vTransInit.x(), vTransInit.y(), vTransInit.z());
	if( conf.getIfSet("TranslateInit", vTransInit) )
	{
		SetTransInit(vTransInit.x(), vTransInit.y(), vTransInit.z());
	}

	// 读取：是否随父模型缩放/旋转
	bool bScaleWithParent  = IsScaleWithParentEnabled();
	bool bRotateWithParent = IsRotateWithParentEnabled();
	if( conf.getIfSet("ScaleWithParent",  bScaleWithParent) )
	{
		EnableScaleWithParent(bScaleWithParent);
	}
	if( conf.getIfSet("RotateWithParent", bRotateWithParent) )
	{
		EnableRotateWithParent(bRotateWithParent);
	}

    bool bEnableFixedSizeInPixels   = IsFixedSizeInPixelsEnabled();
    bool bEnableAutoScale           = IsAutoScaleEnabled();
    bool bEnableScaleDelta          = IsScaleDeltaEnabled();
    bool bEnableMatchTerrain        = IsMatchTerrainEnabled();
    float fFixedSizeInPixels        = GetFixedSizeInPixels();
    EVBF_VIEW_MODE nViewMode        = GetViewMode();

	if( conf.getIfSet("EnableFixedSizeInPixels", bEnableFixedSizeInPixels) ){ EnableFixedSizeInPixels(bEnableFixedSizeInPixels); }
	if( conf.getIfSet("EnableAutoScale",		bEnableAutoScale) )			{ EnableAutoScale(bEnableAutoScale); }
	if( conf.getIfSet("EnableScaleDelta",		bEnableScaleDelta) )		{ EnableScaleDelta(bEnableScaleDelta); }
	if( conf.getIfSet("EnableMatchTerrain",		bEnableMatchTerrain) )		{ EnableMatchTerrain(bEnableMatchTerrain); }
	if( conf.getIfSet("FixedSizeInPixels",		fFixedSizeInPixels) )		{ SetFixedSizeInPixels(fFixedSizeInPixels); }
	if( conf.getIfSet("ViewMode",				(int&)nViewMode) )			{ SetViewMode(nViewMode); }
}

#endif 
