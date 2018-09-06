//*******************************************************************
// FileName：VBF_MarkModelImpl.h
// Function：军标实体模型的模板类
// Author:   
// Date:     2004-12-15
//*******************************************************************

#ifndef __VBF_MARK_MODEL_IMPL_H__
#define __VBF_MARK_MODEL_IMPL_H__


#include <VBF_MainCtrl/VBF_3DEnvironment.h>
#include <VBF_MainCtrl/IVBF_ObserverRef.h>
#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>

#include <Types/Vec3d>
#include <string>
#include <vector>

#include <VBF_Plot/IVBF_MarkAttr.h>
#include <VBF_Plot/IVBF_MarkAction.h>
#include <VBF_Plot/IVBF_MarkAttrIFF.h>
#include <VBF_Plot/IVBF_MarkProcess.h>

#include <VBF_Aux/VBF_GLAux/VBF_Effect.h>
#include <VBF_Aux/VBF_GLAux/VBF_StateSetUtils.h>
#include <VBF_Aux/VBF_GLAux/VBF_ReadWriteUtils.h>
#include <VBF_Aux/VBF_GLAux/VBF_NodeUtil.h>
#include <VBF_Aux/VBF_GLAux/VBF_Effect.h>
#include <VBF_Aux/VBF_GLAux/VBF_PrimitiveUtils.h>
#include <VBF_Aux/VBF_GLAux/VBF_3DPlotShaderUtils.h>
#include <VBF_Aux/VBF_GLAux/VBF_JsonReader.h>
#include <VBF_Aux/VBF_MapAux/VBF_CoordTransformUtils.h>
#include <VBF_Aux/VBF_MapAux/VBF_SceneUtils.h>
#include <VBF_Aux/VBF_MapAux/IVBF_3DGlobalData.h>

// 与osg有关的头文件
#include <VBF_Base/ref_ptr>
#include <VBF_Base/observer_ptr>
#include <VBF_Display/VBF_Viewer/VBF_View.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransformCamera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupSwitch.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformAuto.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLOD.h>

// 渲染状态
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrDepth.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLightModel.h>


// 定义透明模型的渲染元基数
#define VBF_TRANSPARENT_BINBASE		10


typedef std::vector< ref_ptr<IVBF_MarkModel> >			CVBF_MarkList;
typedef std::vector< ref_ptr<IVBF_MarkAttr> >			CVBF_AttrList;
typedef std::vector< ref_ptr<IVBF_MarkAction> >			CVBF_ActionList;
typedef std::vector< ref_ptr<IVBF_MarkProcess> >		CVBF_ProcessList;
typedef std::vector< observer_ptr<IVBF_ObserverRef> >	CVBF_ObserverList;


//=======================================================================================
// 定义模板类：CVBF_MarkModelImpl
// 模板类描述：军标实体模型
//=======================================================================================
template<class T>
class CVBF_MarkModelImpl : public T
{
public:	
	CVBF_MarkModelImpl() {}
	CVBF_MarkModelImpl(const std::string& strMarkID);
	CVBF_MarkModelImpl(const CVBF_MarkModelImpl& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
	virtual ~CVBF_MarkModelImpl();

	// 设置/获取军标的类型编码 (16位：前8位为主码，后8位为子码)
	virtual void SetCode(const std::string& strCode)	{ m_strCode = strCode; }
	virtual const std::string&	GetCode()				{ return m_strCode; }

	// 获取军标的编号
	virtual  const std::string&  GetID()		{ return m_strID; }

	/* 设置军标模型的全层唯一编号，如果该模型已经记录某个图层中，不允许修改ID号，返回false（请用户慎重使用该函数） */
	virtual bool SetID(const std::string& strID);

	// 获取军标的类型
	virtual  unsigned int GetType()				{ return m_nType; }

	// 获取军标模型的类型描述，以便用户理解
	virtual const std::string& GetTypeDesc()	{ return m_strTypeDesc; }

	// 判断是否为点状模型
	virtual  bool IsPointMarkModel()			{ return false; }	

	// 设置/获取军标模型的重要性级别 (数值越小，级别越高) (2010-05-28) 
	virtual void	SetLevel(DWORD nLevel)			{ m_nLevel = nLevel; }
	virtual DWORD	GetLevel()						{ return m_nLevel; }

	/* 军标模型可视的最小最大距离，分别默认为0.0和FLT_MAX (单位：米) */
	virtual void	SetDistMin(float fDistMin)      { m_fDistMin = fDistMin; }
	virtual float	GetDistMin()					{ return m_fDistMin; }
	virtual void	SetDistMax(float fDistMax)      { m_fDistMax = fDistMax; }
	virtual float	GetDistMax()					{ return m_fDistMax; }

	// 获取模型到视点的距离（单位：米）
	virtual double GetDistToEye() { return m_dDistToEye; }

	// 根据模型到视点的距离，实时判断模型是否在可见距离内
	virtual bool IsInDistRange() { return m_bInDistRange; }
	
	// 设置/获取模型的可见性
	virtual void	SetVisible(bool bVisible);
	virtual bool	IsVisible()						{ return m_bVisible; }

	// 设置模型是否存活
	virtual void	SetAlive(bool bAlive)		    { m_bAlive = bAlive; }
	virtual bool	IsAlive()						{ return m_bAlive; }

	// 选中状态
	virtual void    SetSelected(bool bSelected);	
	virtual bool    IsSelected()					{ return m_bSelected; }
    virtual void    SetSelectable(bool bSelectable) { m_bSelectable = bSelectable; }// 设置是否可以鼠标选择
    virtual bool    IsSelectable()                  { return m_bSelectable; }

	// 设置/获取选中模型时，包围盒是否自动可见（默认为true）
	virtual void    SetBoundingBoxVisibleWhenSelected(bool bVisible);
	virtual bool    IsBoundingBoxVisibleWhenSelected()	{ return m_bBoundingBoxVisibleWhenSelected; }

	// 设置该模型所在图层的指针
    virtual  void   SetLayerPtr(TYPE_PTR dwData);
    virtual  TYPE_PTR GetLayerPtr()					{ return m_dwLayerPtr; }

	// 将图层指针设置为NULL（该函数仅由系统内部调用）
	virtual  void	SetLayerPtrAsNull();
	
	// 设置/获取模型的信息
	virtual void	SetInfo(const std::string& strInfo)	{ m_strInfo = strInfo; }
	virtual const std::string&	GetInfo()				{ return m_strInfo; }

    // 设置/获取是否可查询该模型的信息（默认值为true）
    virtual void SetQueriable(bool bQueriable)      { m_bQueriable = bQueriable; }
    virtual bool IsQueriable()                      { return m_bQueriable; }

    // 设置/获取该模型被查询到后的显示样式
    virtual void                      SetQueryStyle(const VBF_MARKQUERYSTYLE& style) { m_QueryInfo = style; }
    virtual const VBF_MARKQUERYSTYLE& GetQueryStyle() { return m_QueryInfo; }

    // 设置/获取模型是否可编辑（默认值为true）
    virtual void SetEditable(bool bEditable)    { m_bEditable = bEditable; }
    virtual bool IsEditable()                   { return m_bEditable; }

	// 给用户预留的
    virtual  void SetData(TYPE_PTR dwData)			{ m_dwData = dwData; }
    virtual  TYPE_PTR GetData()						{ return m_dwData; }

	// 设置/获取预留标志，系统使用了最后4位
	virtual void  SetReserveFlag(DWORD dwFlag, bool bOR=true); 
	virtual DWORD GetReserveFlag() { return m_dwReserveFlag; }

	/* 获取军标模型的当前位置，如果有父模型，返回子模型的相对坐标；否则，返回模型的世界坐标 */
	virtual const osg::Vec3d& GetPos();

	// 获取模型的世界坐标
	virtual const osg::Vec3d& GetWorldPos();

	// 判断某点（世界坐标系下）是否在模型范围内
	virtual bool Contains(const osg::Vec3d& ptWorld)	{ osg::Vec3d ptModel; double dDist; return Contains(ptWorld, ptModel, dDist); }
	virtual bool Contains(const osg::Vec3d& ptWorld, osg::Vec3d& ptModel, double& dDist) { return false; }

	// 设置/获取模型的地理坐标（即：经过局部变换前的地理坐标，该值由用户设置）
	virtual const osg::Vec3d& GetGeoPos()		{ return m_vPosGeo; } 
	virtual void  SetGeoPos(const osg::Vec3d& vPos);

	// 获取模型实际的地理坐标（即：经过局部变换后的地理坐标，该值由系统内部计算）
	virtual osg::Vec3d GetActualGeoPos();


	// ------------------------------------------------------------------------------
	// 处理父子关系
	// ------------------------------------------------------------------------------

    virtual void			SetParent(IVBF_MarkModel* pIParent) { m_pIParent = pIParent;  }
    virtual IVBF_MarkModel*	GetParent()                         { return m_pIParent; }

	// 获取军标模型的父模型层次列表（从最顶层父模型开始，到该模型结束）
	virtual std::vector<IVBF_MarkModel*> GetParentalPaths();

	virtual bool	AddChild(IVBF_MarkModel* pIChild);

	// 移除一个子模型（不删除子模型的指针）
	virtual IVBF_MarkModel* RemoveChild(const std::string& strChildID);
	virtual void	RemoveChild(IVBF_MarkModel* pIChild);

	// 删除一个子模型（删除子模型的指针）
	virtual void	DeleteChild(const std::string& strChildID);
	virtual void	DeleteChild(IVBF_MarkModel* pIChild);

	// 子模型遍历 (nIndex纯粹表示属性的序号)
	virtual int	GetChildCount();
	virtual IVBF_MarkModel* GetChild(int nIndex);
    virtual IVBF_MarkModel* GetChild(const std::string& strChildID);
    virtual IVBF_MarkModel* GetChildNested(const std::string& strChildID);

	// 分离出指定的子模型
	virtual IVBF_MarkModel* ApartChild(const std::string& strChildID);

	// 获取子模型的地理坐标
	virtual osg::Vec3d GetChildGeoPos(const std::string& strChildID);

    // 设置标识：该模型的根节点等待添加到某个父节点
    virtual void SetParentNode(osg::IVBF_SGNodeGroup* pParentNode);

	// 设置标识：该模型的根节点等待添加到某个父节点的图层（该函数仅供内部调用）
	virtual void WaitForAddingToParentLayer() { m_bNodeToAddToParentLayer = true; }


	// ------------------------------------------------------------------------------
	// 处理模型属性
	// ------------------------------------------------------------------------------

	// 属性添加/删除/查找
	virtual bool AddMarkAttr(IVBF_MarkAttr* pIAttr);
	virtual void DeleteMarkAttr(unsigned int nAttrType);
	virtual IVBF_MarkAttr* LookupMarkAttr(unsigned int nAttrType);
	virtual IVBF_MarkAttr* AddMarkAttr(unsigned int nAttrType);

	// 属性遍历
	virtual unsigned int	GetMarkAttrCount()					{ return m_MarkAttrList.size(); }
	virtual IVBF_MarkAttr*	GetMarkAttr(unsigned int nIndex)	{ return (nIndex>=0 && nIndex<m_MarkAttrList.size())? m_MarkAttrList[nIndex] : NULL; }

    // ------------------------------------------------------------------------------
    // 处理模型行为
    // ------------------------------------------------------------------------------
    virtual bool AddMarkAction(IVBF_MarkAction* pIAction);
    virtual void DeleteMarkAction(unsigned int nIndex);

    // 行为遍历
    virtual unsigned int	 GetMarkActionCount()					{ return m_MarkActionList.size(); }
    virtual IVBF_MarkAction* GetMarkAction(unsigned int nIndex)	{ return (nIndex>=0 && nIndex<m_MarkActionList.size())? m_MarkActionList[nIndex] : NULL; }

    // ------------------------------------------------------------------------------
    // 处理模型推演过程
    // ------------------------------------------------------------------------------

    virtual bool	AddMarkProcess(IVBF_MarkProcess* pIProcess);
    virtual void	DeleteMarkProcess(unsigned int nIndex);

    virtual unsigned int	  GetMarkProcessCount()	{ return m_MarkProcessList.size(); }
    virtual IVBF_MarkProcess* GetMarkProcess(unsigned int nIndex) { return (nIndex>=0 && nIndex < m_MarkProcessList.size())? m_MarkProcessList[nIndex] : NULL; }

    virtual void ProcessSimulate(IVBF_SimulationTimer* pSimulationTimer);
    virtual void StatStartTime(double& dStartTime);  // 统计所有模型的仿真过程的起始时间
	// ------------------------------------------------------------------------------
	// 包围盒
	// ------------------------------------------------------------------------------

	// 设置/获取包围盒的可见性（默认为false）
	virtual void SetBoundingBoxVisible(bool bVisible);
	virtual bool IsBoundingBoxVisible()	{ return m_bBoundingBoxVisible; }

	// 设置/获取包围盒的样式
	virtual void SetBoundingBoxStyle(const VBF_BOUNDINGBOXSTYLE& style);
	virtual const VBF_BOUNDINGBOXSTYLE& GetBoundingBoxStyle()			{ return m_BoundingBoxStyle; }

    // 获取模型在各个坐标系下的包围盒
	virtual const osg::BoundingBox&  GetBoundingBoxInModel();
	virtual const osg::BoundingBox&  GetBoundingBoxInWorld();
	virtual const osg::BoundingBoxd& GetBoundingBoxInGeo();

    // 获取模型包围盒中心的地理坐标
	virtual osg::Vec3d GetBoundingBoxCenterGeo();	
	
	// 强行开启/关闭z-buffer测试 (默认为开启)
	virtual void EnableDepthTest(bool bEnable);
	virtual bool IsDepthTestEnabled()			{ return m_bEnableDepthTest; }

	// 强行开启/关闭深度写入 (默认为开启)
	virtual void EnableDepthWrite(bool bEnable);
	virtual bool IsDepthWriteEnabled()			{ return m_bEnableDepthWrite; }
	
	// 强行开启/关闭光照 (默认为关闭)
	virtual void EnableLight(bool bEnable);
	virtual bool IsLightEnabled()				{ return m_bEnableLight; }

	// 开启/关闭点光滑 (默认为开启)
	virtual void EnablePointSmooth(bool bEnable);
	virtual bool IsPointSmoothEnabled()			{ return m_bEnablePointSmooth; }

	// 开启/关闭线光滑 (默认为开启)
	virtual void EnableLineSmooth(bool bEnable);
	virtual bool IsLineSmoothEnabled()			{ return m_bEnableLineSmooth; }

	// 开启/关闭面光滑 (默认为关闭，开启后在某些机器上会出现三角形的边线)
	virtual void EnablePolygonSmooth(bool bEnable);
	virtual bool IsPolygonSmoothEnabled()		{ return m_bEnablePolygonSmooth; }

    // 是否开启地球背面的裁剪，点状模型默认为true，其它默认为false
    virtual void EnableClipByEarth(bool bEnable) { m_bEnableClipByEarth = bEnable; }
    virtual bool IsClipByEarthEnabled()          { return m_bEnableClipByEarth; }

    // 设置/获取模型是否随父模型同步混色（默认值为true）
    virtual void EnableBlendWithParent(bool bEnable)    { m_bEnableBlendWithParent = bEnable; }
    virtual bool IsBlendWithParentEnabled()             { return m_bEnableBlendWithParent; }

	// 设置/获取模型是否混色以及混合的颜色，混合的方式（乘色/替换色）
	virtual void SetBlendColor(bool bEnable, const osg::Vec4f& color=osg::Vec4f(1,1,1,1), bool bModulate=false);
	virtual void GetBlendColor(bool& bEnable, osg::Vec4f& color, bool& bModulate)	{ bEnable = m_bEnableBlendColor; color = m_colorBlend; bModulate = m_bBlendModulate; }

    // 开始/停止模型闪烁
    virtual void StartFlicker(int nFlickerTimes, int nFlickerInterval, bool bFlickerAlways=false);
    virtual void StopFlicker();

	// 设置模型的渲染顺序
	virtual void SetRenderOrder_Opaque(int nOrder);
	virtual void SetRenderOrder_Transparent(int nOrder);

	// 设置模型的渲染顺序
	virtual void SetRenderHint_Opaque();		
	virtual void SetRenderHint_Transparent();	
	virtual void SetRenderHint_Default();

	// 获取模型的各个场景图节点
	virtual osg::IVBF_SGNodeGroup*		GetRootNode()	{ return m_piNodeRoot.get(); }
	virtual osg::IVBF_SGNodeGroup*		GetGroupNode()	{ return m_piNodeGroup.get(); }
	virtual osg::IVBF_SGNode*			GetModelNode()	{ return m_piNodeModel.get(); }


    /* 模型做某种动作 (如车轮滚动、炮塔旋转等)
       参数：szActionName  -- 动作名称（如滚动、旋转等）
            bEnabled       -- 动作开启或停止
            pActionParam   -- 动作的参数 (如滚动速度等，具体类型和含义由动作本身决定)
    */
    virtual void DoAction(const char* szActionName, bool bEnabled);
    virtual void DoAction(const std::string& strChildID, const std::string& strActionName, bool bEnabled);

    // 绑定/解除一个消息观察者（负责接收该模型发出的各类消息）
    virtual void AttachObserver(IVBF_ObserverRef* pIObserver);
    virtual void DetachObserver(IVBF_ObserverRef* pIObserver);

	// 使模型节点/渲染状态失效
    virtual void DirtyModel()       { m_bDirtyModel = true; }
	virtual void DirtyStateSet()	{ m_bDirtyStateSet = true; }

    // 右键弹出菜单
    virtual void EnablePopupMenu(bool bEnable) { m_bEnablePopupMenu = bEnable; }
    virtual bool IsPopupMenuEnabled()          { return m_bEnablePopupMenu; }
    virtual void GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vItems);
    virtual bool ProcessPopupMenuItem(unsigned int nID);

	// 是否允许串行化
	virtual bool IsAllowSerialize() { return m_bAllowSerialize;  }
	virtual void SetAllowSerialize(bool bAllow) { m_bAllowSerialize = bAllow; }

    // 串行化（由系统调用）
    virtual bool WriteToXML(TiXmlElement* pElemMark);    // 写入
    virtual bool ReadFromXML(TiXmlElement* pElemMark);   // 读取

	// 初始化 (在构造函数之后由系统调用)
    virtual bool Init(IVBF_MarkContext* pIContext);
    virtual IVBF_MarkContext* GetMarkContext() { return m_ipContext.get(); }
	// 更新 (每帧绘制前调用)
	virtual bool Update();

	// 执行json脚本
    virtual void ExecuteScript(const CVBF_Config& conf);

protected:
	virtual bool SelectByGeoPoint(osg::Vec3d& vCoordGeo) { return false; }

	// 初始化场景图
    virtual bool InitSG();
    virtual void Clear();

	// 更新所有属性/子模型
	void UpdateAttrs();
	void UpdateChildren();

    // 模型动作/特效
    void UpdateByActions();
    void UpdateByEffects();

    // 删除所有子模型
	void DeleteAllChildren();

	// 查找模型的IFF属性
	IVBF_MarkAttrIFF* LookupMarkAttrIFF();

	// 使包围盒失效，以便重新计算
	void DirtyBoundingBoxNode()	    { m_bDirtyBoundingBoxNode = true; }
	void DirtyBoundingBoxInModel()	{ m_bDirtyBoundingBoxInModel = true; }
	void DirtyBoundingBoxInWorld()	{ m_bDirtyBoundingBoxInWorld = true; m_bDirtyBoundingBoxInGeo = true; }

    // 使地理/世界坐标失效
    void DirtyPosGeo()              { m_bDirtyPosGeo   = true; }
    void DirtyPosWorld()			{ m_bDirtyPosWorld = true; }

	// 构建模型节点
    virtual void UpdateModelNode();
    virtual bool CreateModelNode()	{ return false; }

	// 设置渲染状态
	virtual void SetStateSet();

	// 更新模型的位置
    virtual void UpdatePos() {}

    // 添加到场景图的父节点
    void AddToParentNode();

    // 更新某些场景图节点的属性
    virtual void UpdateSGNode();

    // 根据视点到模型的距离，判断模型/属性是否在可见距离内
    virtual void ClipByDist();
    virtual void ClipModelByDist();
    virtual void ClipAttrByDist();

    // 地球背面的裁剪
    virtual void ClipByEarth() {}

    // 获取待混色节点，可能不止一个
    virtual void GetBlendNodes(std::vector< ref_ptr<osg::IVBF_SGNode> >& vNodes);

    // 与包围盒有关的函数
    virtual osg::IVBF_SGNode* GetBoundingBoxNode();     // 获取计算包围盒时使用的节点
    virtual osg::IVBF_SGNode* CreateBoundingBoxNode();  // 创建包围盒节点
    virtual void              UpdateBoundingBox();      // 更新包围盒节点
    virtual void              SetShader_BoundingBox(osg::StateSet* ss); // 设置包围盒的着色器

    // 向所有观察者发送消息
    void NotifyObservers(const char* szMessage, int nValue=0, void* pValue=NULL);

    // 串行化，写入/读取模型本身的信息
    virtual bool WriteModelToXML(TiXmlElement* pElemMark);
    virtual bool ReadModelFromXML(TiXmlElement* pElemMark);

protected:

	// 模型的标识属性
	std::string				m_strID;			// 模型ID号，图层内唯一
	std::string				m_strCode;          // 模型类型编码 (16位：前8位为主码，后8位为子码)
	unsigned int			m_nType;			// 模型类型
	std::string				m_strTypeDesc;		// 模型类型的描述信息

	// 模型的信息属性
	std::string				m_strInfo;	        // 模型的信息
	DWORD					m_nLevel;			// 军标模型的重要性级别 (数值越小，级别越高) 
	DWORD					m_dwReserveFlag;	// 预留标志，系统使用最后4位

    // 模型的查询信息
    bool                    m_bQueriable;           // 是否可查询
    VBF_MARKQUERYSTYLE      m_QueryInfo;            // 查询信息

    // 模型是否可编辑
    bool                    m_bEditable;

	bool					m_bInited;			// 是否初始化成功
	bool					m_bVisible;			// 是否可见
	bool					m_bSelected;		// 是否被选中
    bool                    m_bSelectable;      // 是否可被选中

	bool                    m_bAlive;			// 是否存活
	bool					m_bAllowSerialize;	// 是否允许串行化

	// 模型的坐标
    bool                    m_bDirtyPosGeo;     // 地理坐标是否失效
	bool					m_bDirtyPosWorld;	// 世界坐标是否失效
	osg::Vec3d				m_vPosGeo;			// 地理坐标	
	osg::Vec3d				m_vPosWorld;		// 世界坐标

    TYPE_PTR					m_dwLayerPtr;		// 所在图层的指针
    TYPE_PTR					m_dwData;			// 对应数据的指针

	// 渲染状态
	bool					m_bEnableDepthTest;			// 是否开启深度测试（默认为开启）
	bool					m_bEnableDepthWrite;		// 是否开启深度写入（默认为开启）
	bool                    m_bEnableLight;				// 是否开启光照 (默认为关闭)
	bool					m_bEnableClipByEarth;		// 是否开启地球背面的裁剪，默认为false

	// 是否开启各类光滑（默认为开启）
	bool					m_bEnablePointSmooth;
	bool					m_bEnableLineSmooth;	
	bool					m_bEnablePolygonSmooth;
	
	// 可见距离
	float					m_fDistMin;			// 最小可视距离
	float					m_fDistMax;			// 最大可视距离

	// 以下变量用于判断模型是否在可见距离内
	double					m_dDistToEye;		// 模型到视点的距离（单位：米）
	bool					m_bInDistRange;		// 模型本帧是否在可见距离内

	// 混色，可用于红外相机、突出目标、类别区分等
	bool					m_bEnableBlendColor;	// 是否启用颜色混合
    bool					m_bBlendModulate;		// 是否使用乘色方式进行混合（否则使用替换色方式）
	osg::Vec4f				m_colorBlend; 
	bool					m_bEnableBlendWithParent;	// 是否随父模型同步混色

	// 模型的包围盒
	bool						m_bBoundingBoxVisible;		// 包围盒是否可见
	bool						m_bBoundingBoxVisibleWhenSelected;	// 模型选中时，包围盒是否自动可见（只有模型选中时，该属性才启用）
    VBF_BOUNDINGBOXSTYLE		m_BoundingBoxStyle;			// 包围盒的样式
	osg::BoundingBox			m_BoundingBoxInModel;		// 模型坐标系下的包围盒
	osg::BoundingBox			m_BoundingBoxInWorld;		// 世界坐标系下的包围盒
	osg::BoundingBoxd			m_BoundingBoxInGeo;			// 地理坐标系下的包围盒
	ref_ptr<osg::IVBF_SGNode>	m_piNodeBoundingBox;		// 包围盒节点

    // 模型的父子关系
	IVBF_MarkModel*			m_pIParent;
	CVBF_MarkList			m_vChildren;

    // 模型的属性列表，属性不允许重复
	CVBF_AttrList			m_MarkAttrList;

    // 模型的行为列表，允许重复
    CVBF_ActionList			m_MarkActionList;


    // 模型的过程列表，过程允许重复
    CVBF_ProcessList        m_MarkProcessList;

    // 模型的消息观察者
    CVBF_ObserverList       m_ObserverList;


    // 模型的各种参数是否失效
    bool					m_bDirtyModel;              // 模型节点是否失效
    bool					m_bDirtyStateSet;           // 模型渲染状态是否失效
    bool					m_bDirtyBoundingBoxNode;	// 包围盒节点是否失效
    bool					m_bDirtyBoundingBoxInModel; // 模型坐标系下的包围盒是否失效
    bool					m_bDirtyBoundingBoxInWorld; // 世界坐标系下的包围盒是否失效
    bool					m_bDirtyBoundingBoxInGeo;   // 地理坐标系下的包围盒是否失效

    // 是否需要开始/停止闪烁
    bool                    m_bFlickerToStart;
    bool                    m_bFlickerToStop;
    VBF_FLICKERPARAM        m_FlickerParam;
	
	// 模型的渲染顺序
	CVBF_Optional<int>		m_nBinNumber;
	std::string				m_strBinName;
	int						m_nBinNumberBox;    // 包围盒的渲染元序号（确保包围盒在模型之后渲染）

    // 右键弹出菜单
    bool                    m_bEnablePopupMenu;
    bool                    m_bEnableMenuZBuffer;
    bool					m_bEnableMenuFillMode;

    // 该模型的根节点是否等待添加/删除
    bool                                    m_bNodeToAddToParent;       // 是否等待添加到场景图中的父节点
    bool                                    m_bNodeToRemoveFromParent;  // 是否等待从场景图中的父节点中移除
    observer_ptr<osg::IVBF_SGNodeGroup>     m_piNodeParent;             // 场景图中的父节点
    observer_ptr<osg::IVBF_SGNodeGroup>     m_piNodeParentOld;          // 场景图中原来的父节点

	// 该模型的根节点是否等待添加到父节点的图层（适用于父模型是点状，但子模型不是点状，如在一个点状模型下添加Text子节点或Label属性）
    bool                                    m_bNodeToAddToParentLayer; 

	// 与场景图有关的内容
	ref_ptr<osg::IVBF_SGNodeGroupSwitch>	m_piNodeRoot;			// 模型的根节点，挂接在图层节点下
	ref_ptr<osg::IVBF_SGNodeGroup>			m_piNodeGroup;			// 模型的组节点，挂接在根节点下，模型节点及所有子节点均挂接在该节点下
    ref_ptr<osg::IVBF_SGNode>				m_piNodeModel;			// 模型的实际数据节点，挂接在Group节点下，由用户完成该节点的创建与修改

	// 其它需要使用的外部节点（在Init()函数中获取）
	IVBF_3DMainCtrl*						m_pI3DMainCtrl;
	observer_ptr<IVBF_View>					m_opView;
	observer_ptr<osg::IVBF_Camera>			m_opCamera;

    ref_ptr<IVBF_MarkContext> m_ipContext;
};



#include "VBF_MarkModelImpl.inl"
#include "VBF_MarkModelImpl2.inl"

#endif 
