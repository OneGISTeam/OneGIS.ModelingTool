//*******************************************************************
// FileName：CVBF_MarkActionImpl.h
// Function：标图实体模型动作接口实现
// Author:
// Date:     
//*******************************************************************

#ifndef __VBF_MARK_ACTION_IMPL_H__
#define __VBF_MARK_ACTION_IMPL_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Base/observer_ptr>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>
#include <VBF_Common/VBF_XML/tinyxml.h>
#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>
#include <VBF_MainCtrl/VBF_3DEnvironment.h>
#include <VBF_Aux/VBF_GLAux/VBF_ReadWriteUtils.h>
#include <VBF_Aux/VBF_GLAux/VBF_JsonReader.h>
#include <VBF_Aux/VBF_MapAux/VBF_SceneUtils.h>

class IVBF_PropertySet;

//--------------------------------------------------------------------
// 定义接口：CVBF_MarkActionImpl
// 接口描述：标图实体模型动作接口实现
//--------------------------------------------------------------------
template<class T>
class CVBF_MarkActionImpl : public T
{
public:
    CVBF_MarkActionImpl() {}
    CVBF_MarkActionImpl(const std::string& sType);
    CVBF_MarkActionImpl(const CVBF_MarkActionImpl& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
    virtual ~CVBF_MarkActionImpl();

public:

    // 获取动作类型
    virtual const std::string& GetType()		{ return m_sType; }

    // 获取动作名称
    virtual void SetName(const std::string& sName) { m_strName = sName; }
    virtual const std::string& GetName() { return m_strName; }

    // 获取动作类型的描述，以便用户理解
	virtual const std::string& GetTypeDesc() { return m_strTypeDesc; }

	// 设置/获取可见性
    virtual void Enable(bool bEnable);
    virtual bool IsEnable() { return m_bEnable; }

    // 设置动作所绑定的实体模型
	virtual void SetMarkModel(IVBF_MarkModel* pIMark);
    virtual IVBF_MarkModel* GetMarkModel()	{ return m_opIAttachedMark.get(); }

	// 复制
    virtual IVBF_MarkAction* Clone() { return NULL; }
	
	virtual bool ExecuteCommand(const char* szCommandID, IVBF_PropertySet* pInParam, IVBF_PropertySet* pOutParam){ return false; }

    // 右键弹出菜单
    virtual void GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vItems) { return; }
    virtual bool ProcessPopupMenuItem(unsigned int nID) { return false; }

    // 串行化
    virtual bool WriteToXML(TiXmlElement* pElemAction);    // 将模型动作信息写入指定的xml节点
    virtual bool ReadFromXML(TiXmlElement* pElemAction);   // 从指定的xml节点读取模型动作信息

	// 初始化 (在构造函数之后由系统调用)
    virtual bool Init(IVBF_MarkContext* pIContext);

	// 更新 (在每帧绘制前由系统调用)，返回值为false表示未做更新处理（如模型不可见时）
	virtual bool Update();

	// 执行json脚本
    virtual void ExecuteScript(const CVBF_Config& conf);


protected:
    std::string 	m_sType;			// 该动作的类型
    std::string		m_strTypeDesc;		// 该动作的类型描述
    std::string		m_strName;		// 该动作的名称
    bool			m_bEnable;			// 是否执行


    // 该动作绑定的实体模型
    observer_ptr<IVBF_MarkModel>	m_opIAttachedMark;


	// 其它需要使用的外部节点（在Init()函数中获取）
	IVBF_3DMainCtrl*						m_pI3DMainCtrl;
	observer_ptr<IVBF_View>					m_opView;
	observer_ptr<osg::IVBF_Camera>			m_opCamera;
    ref_ptr<IVBF_MarkContext> m_ipContext;
};


//-----------------------------------------------------------------------------
// 函数：CVBF_MarkActionImpl()
// 描述：构造函数
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkActionImpl<T>::CVBF_MarkActionImpl(const std::string& sType)
{
    m_sType			= sType;
	m_strTypeDesc	= "";
    m_bEnable		= true;
}

//-----------------------------------------------------------------------------
// 函数：~CVBF_MarkActionImpl()
// 描述：析构函数
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkActionImpl<T>::~CVBF_MarkActionImpl()
{
}

//-----------------------------------------------------------------------------
// 函数：Init()
// 描述：初始化 (在构造函数之后由系统调用)
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkActionImpl<T>::Init(IVBF_MarkContext* pIContext)
{
    if(pIContext==NULL) return false;
    m_ipContext = pIContext;

	CVBF_3DEnvironment& env = ::VBF_Get3DEnvironment();
	m_pI3DMainCtrl = env.m_pI3DMainCtrl;

	// 获取模型所在的视图（目前暂时如此处理，以后应该由外部传入）
	m_opView = ::VBF_GetMainView(env.m_pI3DMainCtrl);
	if(!m_opView.valid()) return false;

	m_opCamera = m_opView->getCamera();
	if(!m_opCamera.valid()) return false;

	return true;
}

//----------------------------------------------------------------------------
// 函数：SetMarkModel()
// 描述：设置动作所绑定的实体模型
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkActionImpl<T>::SetMarkModel(IVBF_MarkModel* pIMark)
{ 
	// 最后记录新的父节点
    m_opIAttachedMark = pIMark;
}

//----------------------------------------------------------------------------
// 函数：SetVisible()
// 描述：设置动作的可见性
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkActionImpl<T>::Enable(bool bEnable)
{
    m_bEnable = bEnable;
}


//----------------------------------------------------------------------------
// 函数：Update()
// 描述：更新 (在每帧绘制前由系统调用)，返回值为false表示未做更新处理（如模型不可见时）
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkActionImpl<T>::Update()
{ 
    if(!m_bEnable) return false;

    return true;
}

//-----------------------------------------------------------------------------
// 函数：WriteToXML()
// 描述：串行化，将模型动作信息写入指定的xml节点
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkActionImpl<T>::WriteToXML(TiXmlElement* pElemAction)
{
    if(NULL==pElemAction) return false;

    ::VBF_SetAttribute(pElemAction, "Type",     m_sType);
    ::VBF_SetAttribute(pElemAction, "Name",     m_strName);
    ::VBF_SetAttribute(pElemAction, "TypeDesc", m_strTypeDesc);
    ::VBF_SetAttribute(pElemAction, "Enable",  m_bEnable);

	return true;
}

//----------------------------------------------------------------------------
// 函数：ReadFromXML()
// 描述：串行化，从指定的xml节点读取模型动作信息
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkActionImpl<T>::ReadFromXML(TiXmlElement* pElemAction)
{
    if(NULL==pElemAction) return false;

//    ::VBF_QueryAttribute(pElemAction, "Type", m_nType);
    ::VBF_QueryAttribute(pElemAction, "Name", m_strName);
    ::VBF_QueryAttribute(pElemAction, "TypeDesc", m_strTypeDesc);

    bool bEnable = IsEnable();
    ::VBF_QueryAttribute(pElemAction, "Enable", bEnable);

    // 更新相关参数
    Enable(bEnable);




    return true;
}

//----------------------------------------------------------------------------
// 函数：ExecuteScript()
// 描述：执行json脚本
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkActionImpl<T>::ExecuteScript(const CVBF_Config& conf)
{   
    conf.getIfSet("Name", m_strName);
    conf.getIfSet("TypeDesc", m_strTypeDesc);

    bool bEnable = IsEnable();
    if( conf.getIfSet("Enable", bEnable) )
	{
        Enable(bEnable);
	} 
}



#endif 
