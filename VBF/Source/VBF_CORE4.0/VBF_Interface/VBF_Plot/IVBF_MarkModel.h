//*******************************************************************
// FileName：IVBF_MarkModel.h
// Function：标图实体模型接口
// Author:
// Date:     2009-4-10
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_H__
#define __IVBF_MARK_MODEL_H__


// 需要使用的头文件
#include <VBF_Macros.h>
#include <Types/Vec3d>
#include <Types/Vec4f>
#include <Types/VBF_Matrixd.h>
#include <Types/VBF_BoundingBox.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>
#include <VBF_Plot/IVBF_MarkStyleManager.h>
#include <VBF_Plot/VBF_MarkPopupMenu.h>
#include <VBF_Base/IVBF_SimulationTimer.h>
#include <string>
#include <vector>
#include <VBF_Plot/IVBF_MarkContext.h>

namespace osg
{
	class IVBF_SGNodeGroup;
	class IVBF_SGNodeGroupLOD;
	class IVBF_SGNodeGroupTransformMatrix;
}

class IVBF_MarkAttr;
class IVBF_MarkAction;
class IVBF_MarkProcess;
class IVBF_MarkModel;
class IVBF_ObserverRef;
class TiXmlElement;
class CVBF_Config;

// 模型的预留标志，系统使用了最后4位
#define VBF_RESERVEFLAG_ATTRCHILD	0x0001		// 由属性创建的子模型
// 组合模型中各类部件子模型的预留标志，系统使用了最后4位
#define VBF_RESERVEFLAG_COMBINEDCHILD_LOD       0x0002
#define VBF_RESERVEFLAG_COMBINEDCHILD_GROUP     0x0004
#define VBF_RESERVEFLAG_COMBINEDCHILD_GEODE     0x0008


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModel
// 接口描述：军标实体模型
// 注意事项：别忘了把创建好的模型加入到图层内
//--------------------------------------------------------------------
class IVBF_MarkModel : public osg::CVBF_Object
{
public:
	virtual ~IVBF_MarkModel() {}

public:

	/* 设置军标的类型编码
	   参数：strCode -- 军标模型的类型编码(建议使用16位：前8位为主码，后8位为子码) 
	*/
	virtual void SetCode(const std::string& strCode)=0;

	/* 获取军标的类型编码 */
	virtual const std::string& GetCode()=0;

	/* 获取军标模型的类型 (军标模型的类型参见枚举VBF_MARK_TYPE的定义)*/
	virtual unsigned int GetType()=0;

	/* 获取军标模型的类型描述，以便用户理解 */
	virtual const std::string& GetTypeDesc()=0;

	/* 获取军标模型的全层唯一编号 */
	virtual const std::string& GetID()=0;

	/* 设置军标模型的全层唯一编号，如果该模型已经记录某个图层中，不允许修改ID号，返回false（请用户慎重使用该函数） */
	virtual bool SetID(const std::string& strID)=0;

	/* 判断军标模型是否为点状实体模型 (即是否通过唯一的坐标点定位) */
	virtual bool IsPointMarkModel()=0;

	/* 军标模型的重要性级别 (数值越小，级别越高) */
	virtual void  SetLevel(DWORD nLevel)=0;
	virtual DWORD GetLevel()=0;

	/* 军标模型可视的最小最大距离，分别默认为0.0和FLT_MAX (单位：米) */
	virtual void	SetDistMin(float fDistMin)=0;
	virtual float	GetDistMin()=0;
	virtual void	SetDistMax(float fDistMax)=0;
	virtual float	GetDistMax()=0;

	// 获取模型到视点的距离（单位：米）
	virtual double GetDistToEye()=0;

	// 根据模型到视点的距离，实时判断模型是否在可见距离内
	virtual bool IsInDistRange()=0;

	/* 军标模型的可见性 */
	virtual void	SetVisible(bool bVisible)=0;	// 设置模型是否可见
	virtual bool	IsVisible()=0;					// 判断模型是否可见

	/* 军标模型的选中状态 */
	virtual void    SetSelected(bool bSelected)=0;		// 设置模型是否被选中
	virtual bool    IsSelected()=0;						// 判断模型是否被选中
    virtual void    SetSelectable(bool bSelectable)=0;    // 设置是否可以鼠标选择
    virtual bool    IsSelectable()=0;

	// 设置/获取选中模型时，包围盒是否自动可见（默认为true）
	virtual void    SetBoundingBoxVisibleWhenSelected(bool bVisible)=0;
	virtual bool    IsBoundingBoxVisibleWhenSelected()=0;

	/* 设置模型是否存活 */
	virtual void	SetAlive(bool bAlive)=0;
	virtual bool	IsAlive()=0;

	/* 设置/获取军标模型被选中时包围盒的可见性 */
	virtual void	SetBoundingBoxVisible(bool bVisible)=0;	
	virtual bool	IsBoundingBoxVisible()=0;

	// 设置/获取包围盒的样式
	virtual void SetBoundingBoxStyle(const VBF_BOUNDINGBOXSTYLE& style)=0;
	virtual const VBF_BOUNDINGBOXSTYLE& GetBoundingBoxStyle()=0;

	/** 获取模型在各个坐标系下的包围盒 */
	virtual const osg::BoundingBox&  GetBoundingBoxInModel()=0;
	virtual const osg::BoundingBox&  GetBoundingBoxInWorld()=0;
	virtual const osg::BoundingBoxd& GetBoundingBoxInGeo()=0;

	/** 获取模型包围盒中心的地理坐标 */
	virtual osg::Vec3d GetBoundingBoxCenterGeo()=0;	

	/* 军标模型所在的图层 */
    virtual  void	SetLayerPtr(TYPE_PTR dwData)=0;				// 设置模型所在图层的指针
    virtual  TYPE_PTR  GetLayerPtr()=0;							// 获取模型所在图层的指针

	// 将图层指针设置为NULL（该函数仅由系统内部调用）
	virtual  void	SetLayerPtrAsNull()=0;

	/* 军标模型的文本信息 */
    virtual void SetInfo(const std::string& strInfo)=0;     // 设置模型的文本信息
    virtual const std::string&	GetInfo()=0;				// 获取模型的文本信息

    // 设置/获取是否可查询该模型的信息（默认值为true）
    virtual void SetQueriable(bool bQueriable)=0;
    virtual bool IsQueriable()=0;

    // 设置/获取该模型被查询到后的显示样式
    virtual void                      SetQueryStyle(const VBF_MARKQUERYSTYLE& style)=0;
    virtual const VBF_MARKQUERYSTYLE& GetQueryStyle()=0;

    // 设置/获取模型是否可编辑（默认值为true）
    virtual void SetEditable(bool bEditable)=0;
    virtual bool IsEditable()=0;

	/* 军标模型对应的内存数据 (该数据由外部负责管理，系统内部不负责释放) */
    virtual  void   SetData(TYPE_PTR dwData)=0;					// 设置模型对应的内存数据的首地址
    virtual  TYPE_PTR GetData()=0;								// 获取模型对应的内存数据的首地址

	// 设置预留标志，系统使用了最后4位
	virtual void  SetReserveFlag(DWORD dwFlag, bool bOR=true)=0;
	virtual DWORD GetReserveFlag()=0;

	/* 获取军标模型当前的位置，如果有父模型，返回子模型的相对坐标；否则，返回模型的世界坐标 */
	virtual const osg::Vec3d& GetPos()=0;

	/* 获取模型当的世界坐标 */
	virtual const osg::Vec3d& GetWorldPos()=0;

	/* 设置/获取模型的地理坐标（即：经过局部变换前的地理坐标，该值由用户设置） */
	virtual void SetGeoPos(const osg::Vec3d& vGeoPos)=0;
	virtual const osg::Vec3d& GetGeoPos()=0;

	// 获取军标模型实际的地理坐标（即：经过局部变换后的地理坐标，该值由系统内部计算）
	virtual osg::Vec3d GetActualGeoPos()=0;


	// ------------------------------------------------------------------------------
	// 处理父子关系
	// ------------------------------------------------------------------------------

	/* 设置军标模型的父模型 (每个模型最多只能有一个父模型)
	   参数：pIParent -- 父模型的指针
	*/
	virtual void SetParent(IVBF_MarkModel* pIParent)=0;

	/* 获取军标模型的父模型 
	   返回：pIParent -- 父模型的指针，NULL表示没有父模型
	*/
	virtual IVBF_MarkModel* GetParent()=0;

	// 获取军标模型的父模型层次列表（从最顶层父模型开始，到该模型结束）
	virtual std::vector<IVBF_MarkModel*> GetParentalPaths()=0;

	/* 为军标模型添加一个子模型 
	   参数：pIChild -- 子模型的指针
	   不允许Child重复，如果重复则返回false
	*/
	virtual bool	AddChild(IVBF_MarkModel* pIChild)=0;
	
	// 移除一个子模型（不删除子模型的指针）
	virtual IVBF_MarkModel* RemoveChild(const std::string& strChildID)=0;
	virtual void	RemoveChild(IVBF_MarkModel* pIChild)=0;

	// 删除一个子模型（删除子模型的指针）
	virtual void	DeleteChild(const std::string& strChildID)=0;
	virtual void	DeleteChild(IVBF_MarkModel* pIChild)=0;

	/* 获取军标模型的子模型个数 */	
	virtual int     GetChildCount()=0;

    /* 获取军标模型的某个子模型
	   参数：nIndex -- 该子模型的序号 (可结合GetChildCount()函数实现子模型的遍历)
	   返回：第n个子模型的指针
	*/
	virtual IVBF_MarkModel* GetChild(int nIndex)=0; 

    /* 获取军标模型的某个子模型
	   参数：strChildID -- 该子模型的ID号
	   返回：子模型的指针
	*/
	virtual IVBF_MarkModel* GetChild(const std::string& strChildID)=0;

    /* 获取军标模型的某个子模型（深度查找所有，即查找子模型的子模型）
       参数：strChildID -- 该子模型的ID号
       返回：子模型的指针
    */
    virtual IVBF_MarkModel* GetChildNested(const std::string& strChildID)=0;

	// 分离出指定的子模型
	virtual IVBF_MarkModel* ApartChild(const std::string& strChildID)=0;

	// 获取子模型的地理坐标
	virtual osg::Vec3d GetChildGeoPos(const std::string& strChildID)=0;

    // 设置标识：该模型的根节点等待添加到某个父节点
    virtual void SetParentNode(osg::IVBF_SGNodeGroup* pParentNode)=0;

	// 设置标识：该模型的根节点等待添加到某个父节点的图层（该函数仅供内部调用）
    virtual void WaitForAddingToParentLayer()=0;


	// ------------------------------------------------------------------------------
	// 处理模型属性
	// ------------------------------------------------------------------------------

	// 属性添加/删除/查找
	virtual bool AddMarkAttr(IVBF_MarkAttr* pIAttr)=0;
	virtual void DeleteMarkAttr(unsigned int nAttrType)=0;
	virtual IVBF_MarkAttr* LookupMarkAttr(unsigned int nAttrType)=0;
	virtual IVBF_MarkAttr* AddMarkAttr(unsigned int nAttrType)=0;

	// 属性遍历
	virtual unsigned int	GetMarkAttrCount()=0;
	virtual IVBF_MarkAttr*	GetMarkAttr(unsigned int nIndex)=0;

    // ------------------------------------------------------------------------------
    // 处理模型行为
    // ------------------------------------------------------------------------------
    virtual bool AddMarkAction(IVBF_MarkAction* pIAction)=0;
    virtual void DeleteMarkAction(unsigned int nIndex)=0;

    virtual unsigned int	 GetMarkActionCount()=0;
    virtual IVBF_MarkAction* GetMarkAction(unsigned int nIndex)=0;

    // ------------------------------------------------------------------------------
    // 处理模型推演过程
    // ------------------------------------------------------------------------------

    virtual bool AddMarkProcess(IVBF_MarkProcess* pIProcess)=0;
    virtual void DeleteMarkProcess(unsigned int nIndex)=0;

    virtual unsigned int	  GetMarkProcessCount()=0;
    virtual IVBF_MarkProcess* GetMarkProcess(unsigned int nIndex)=0;

    virtual void ProcessSimulate(IVBF_SimulationTimer* pSimulationTimer)=0;
    virtual void StatStartTime(double& dStartTime)=0;


	// 判断通过地理坐标是否选中模型
	virtual bool SelectByGeoPoint(osg::Vec3d& vCoordGeo)=0;

	// 强行开启/关闭深度测试 (默认为开启)
	virtual void EnableDepthTest(bool bEnable)=0;
	virtual bool IsDepthTestEnabled()=0;

	// 强行开启/关闭深度写入 (默认为开启)
	virtual void EnableDepthWrite(bool bEnable)=0;
	virtual bool IsDepthWriteEnabled()=0;

	// 强行开启/关闭光照 (默认为关闭)
	virtual void EnableLight(bool bEnable)=0;
	virtual bool IsLightEnabled()=0;

	// 开启/关闭点光滑 (默认为开启)
	virtual void EnablePointSmooth(bool bEnable)=0;
	virtual bool IsPointSmoothEnabled()=0;

	// 开启/关闭线光滑 (默认为开启)
	virtual void EnableLineSmooth(bool bEnable)=0;
	virtual bool IsLineSmoothEnabled()=0;

	// 开启/关闭面光滑 (默认为关闭，开启后在某些机器上会出现三角形的边线)
	virtual void EnablePolygonSmooth(bool bEnable)=0;
	virtual bool IsPolygonSmoothEnabled()=0;

    // 是否开启地球背面的裁剪，点状模型默认为true，其它默认为false
    virtual void EnableClipByEarth(bool bEnable)=0;
    virtual bool IsClipByEarthEnabled()=0;

    // 设置/获取模型是否随父模型同步混色（默认值为true）
    virtual void EnableBlendWithParent(bool bEnable)=0;
    virtual bool IsBlendWithParentEnabled()=0;

	// 设置/获取模型是否混色以及混合的颜色
	virtual void SetBlendColor(bool bEnable, const osg::Vec4f& color=osg::Vec4f(1,1,1,1), bool bModulate=false)=0;
    virtual void GetBlendColor(bool& bEnable, osg::Vec4f& color, bool& bModulate)=0;

    // 开始/停止模型闪烁
    virtual void StartFlicker(int nFlickerTimes, int nFlickerInterval, bool bFlickerAlways=false)=0;
    virtual void StopFlicker()=0;

	// 设置模型的渲染顺序
	virtual void SetRenderOrder_Opaque(int nOrder)=0;			// 不透明模型
	virtual void SetRenderOrder_Transparent(int nOrder)=0;		// 透明模型

	// 快捷设置模型的渲染顺序
	virtual void SetRenderHint_Opaque()=0;			// 不透明模型
	virtual void SetRenderHint_Transparent()=0;		// 透明模型
	virtual void SetRenderHint_Default()=0;

	// 获取模型的各个场景图节点
	virtual osg::IVBF_SGNodeGroup*		GetRootNode()=0;	// 获取模型的场景图根节点
	virtual osg::IVBF_SGNodeGroup*		GetGroupNode()=0;	// 获取模型的组节点，所有子节点挂接在此下
	virtual osg::IVBF_SGNode*			GetModelNode()=0;	// 获取模型的实际数据节点

    /* 模型做某种动作 (如车轮滚动、炮塔旋转等)
       参数：szActionName  -- 动作名称（如滚动、旋转等）
            bEnabled       -- 动作开启或停止
    */
    virtual void DoAction(const char* szActionName, bool bEnabled)=0;
    virtual void DoAction(const std::string& strChildID, const std::string& strActionName, bool bEnabled)=0;


    // 绑定/解除一个消息观察者（负责接收该模型发出的各类消息）
    virtual void AttachObserver(IVBF_ObserverRef* pIObserver)=0;
    virtual void DetachObserver(IVBF_ObserverRef* pIObserver)=0;

    // 右键弹出菜单
    virtual void EnablePopupMenu(bool bEnable)=0;
    virtual bool IsPopupMenuEnabled()=0;
    virtual void GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vPopupMenuItemInf)=0;
    virtual bool ProcessPopupMenuItem(unsigned int nID)=0;

	// 是否允许串行化（默认为true）
	virtual bool IsAllowSerialize()=0;
	virtual void SetAllowSerialize(bool bAllow)=0;

    // 串行化
    virtual bool WriteToXML(TiXmlElement* pElemMark)=0;    // 写入：将模型信息写入指定的xml节点
    virtual bool ReadFromXML(TiXmlElement* pElemMark)=0;   // 读取：从指定的xml节点读取模型信息

	// 初始化 (在构造函数之后由系统调用)
    virtual bool Init(IVBF_MarkContext* pIContext)=0;
    virtual IVBF_MarkContext* GetMarkContext()=0;

	// 更新 (在每帧绘制前由系统调用)，返回值为false表示未做更新处理（如模型不可见时）
	virtual bool Update()=0;

    virtual void UpdateBoundingBox()=0;      // 更新包围盒节点

	// 执行json脚本
    virtual void ExecuteScript(const CVBF_Config& conf)=0;


};


#endif 
