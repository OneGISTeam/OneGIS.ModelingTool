//*******************************************************************
// FileName：CVBF_MarkAttrImpl.h
// Function：标图实体模型属性接口实现
// Author:
// Date:     
//*******************************************************************

#ifndef __VBF_MARK_ATTR_IMPL_H__
#define __VBF_MARK_ATTR_IMPL_H__


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
// 定义接口：CVBF_MarkAttrImpl
// 接口描述：标图实体模型属性接口实现
//--------------------------------------------------------------------
template<class T>
class CVBF_MarkAttrImpl : public T
{
public:
	CVBF_MarkAttrImpl() {}
	CVBF_MarkAttrImpl(unsigned int nType);
	CVBF_MarkAttrImpl(const CVBF_MarkAttrImpl& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
	virtual ~CVBF_MarkAttrImpl();

public:

	// 获取属性类型
	virtual unsigned int GetType()		{ return m_nType; }

	// 获取属性类型的描述，以便用户理解
	virtual const std::string& GetTypeDesc() { return m_strTypeDesc; }

	// 设置/获取可见性
	virtual void SetVisible(bool bVisible);
	virtual bool IsVisible()		{ return m_bVisible; }

	// 设置属性所绑定的实体模型
	virtual void SetMarkModel(IVBF_MarkModel* pIMark);
    virtual IVBF_MarkModel* GetMarkModel()	{ return m_opIAttachedMark.get(); }

	// 设置/获取属性最小最大可见距离，如果没有设置，默认使用属性所绑定的实体模型的可见距离
	// 如果获取的返回值为false，表示用户没有设置属性的最小最大可见距离
	virtual void SetDistMin(float fDistMin)  { m_fDistMin = fDistMin; }
	virtual bool GetDistMin(float& fDistMin);

	virtual void SetDistMax(float fDistMax)  { m_fDistMax = fDistMax; }
	virtual bool GetDistMax(float& fDistMax);

	// 复制
	virtual IVBF_MarkAttr* Clone() { return NULL; }
	
	virtual bool ExecuteCommand(const char* szCommandID, IVBF_PropertySet* pInParam, IVBF_PropertySet* pOutParam){ return false; }

    // 右键弹出菜单
    virtual void GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vItems) { return; }
    virtual bool ProcessPopupMenuItem(unsigned int nID) { return false; }

    // 串行化
    virtual bool WriteToXML(TiXmlElement* pElemAttr);    // 将模型属性信息写入指定的xml节点
    virtual bool ReadFromXML(TiXmlElement* pElemAttr);   // 从指定的xml节点读取模型属性信息

	// 初始化 (在构造函数之后由系统调用)
    virtual bool Init(IVBF_MarkContext* pIContext);

	// 更新 (在每帧绘制前由系统调用)，返回值为false表示未做更新处理（如模型不可见时）
	virtual bool Update();

	// 执行json脚本
    virtual void ExecuteScript(const CVBF_Config& conf);

protected:

	// 添加/移除一个实现该属性所使用的内部子模型
	void AddInnerChild(IVBF_MarkModel* pIChild);
	void RemoveInnerChild(IVBF_MarkModel* pIChild);

protected:
	unsigned int 	m_nType;			// 该属性的类型
	std::string		m_strTypeDesc;		// 该属性的类型描述
	bool			m_bVisible;			// 是否可见

	// 最小最大可见距离
	CVBF_Optional<float>	m_fDistMin;
	CVBF_Optional<float>	m_fDistMax;

	// 该属性绑定的实体模型
    observer_ptr<IVBF_MarkModel>	m_opIAttachedMark;

	// 实现该属性所使用的内部子模型（如实现Label属性使用Text模型，实现Trail属性使用的Strip模型）
	typedef std::vector< observer_ptr<IVBF_MarkModel> >	CVBF_MarkList;
	CVBF_MarkList		m_vInnerChildren;

	// 其它需要使用的外部节点（在Init()函数中获取）
	IVBF_3DMainCtrl*						m_pI3DMainCtrl;
	observer_ptr<IVBF_View>					m_opView;
	observer_ptr<osg::IVBF_Camera>			m_opCamera;
    ref_ptr<IVBF_MarkContext> m_ipContext;
};


//-----------------------------------------------------------------------------
// 函数：CVBF_MarkAttrImpl()
// 描述：构造函数
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkAttrImpl<T>::CVBF_MarkAttrImpl(unsigned int nType)
{
	m_nType			= nType;
	m_strTypeDesc	= "";
	m_bVisible		= true;
}

//-----------------------------------------------------------------------------
// 函数：~CVBF_MarkAttrImpl()
// 描述：析构函数
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkAttrImpl<T>::~CVBF_MarkAttrImpl()
{
    if(m_opIAttachedMark.valid())
	{
		for(CVBF_MarkList::iterator pIter=m_vInnerChildren.begin(); pIter!=m_vInnerChildren.end(); pIter++)
		{
			observer_ptr<IVBF_MarkModel>& piChild = *pIter;
            if(piChild.valid()) m_opIAttachedMark->DeleteChild(piChild.get());
		}
	}
	m_vInnerChildren.clear();
}

//-----------------------------------------------------------------------------
// 函数：Init()
// 描述：初始化 (在构造函数之后由系统调用)
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkAttrImpl<T>::Init(IVBF_MarkContext* pIContext)
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
// 函数：AddInnerChild()
// 描述：添加一个实现该属性所使用的内部子模型
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkAttrImpl<T>::AddInnerChild(IVBF_MarkModel* pIChild)
{
	if(pIChild!=NULL) m_vInnerChildren.push_back(pIChild);
}

//----------------------------------------------------------------------------
// 函数：RemoveInnerChild()
// 描述：移除一个实现该属性所使用的内部子模型
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkAttrImpl<T>::RemoveInnerChild(IVBF_MarkModel* pIChild)
{
	if(NULL==pIChild) return;

	CVBF_MarkList::iterator pIter = std::find(m_vInnerChildren.begin(), m_vInnerChildren.end(), pIChild);
	if(pIter!=m_vInnerChildren.end())
	{
		m_vInnerChildren.erase(pIter);
	}
}

//----------------------------------------------------------------------------
// 函数：SetMarkModel()
// 描述：设置属性所绑定的实体模型
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkAttrImpl<T>::SetMarkModel(IVBF_MarkModel* pIMark)
{ 
	// 将所有子节点从原来的父节点中移走
    if(m_opIAttachedMark.valid())
	{
		for(CVBF_MarkList::iterator pIter=m_vInnerChildren.begin(); pIter!=m_vInnerChildren.end(); pIter++)
		{
			observer_ptr<IVBF_MarkModel> piChild = *pIter;
            if(piChild.valid()) m_opIAttachedMark->RemoveChild(piChild.get());
		}
	}

	// 给所有子节点设置新的父节点
	if(pIMark!=NULL)
	{
		for(CVBF_MarkList::iterator pIter=m_vInnerChildren.begin(); pIter!=m_vInnerChildren.end(); pIter++)
		{
			observer_ptr<IVBF_MarkModel> piChild = *pIter;
			if(piChild.valid()) pIMark->AddChild(piChild.get());
		}
	}

	// 最后记录新的父节点
    m_opIAttachedMark = pIMark;
}

//----------------------------------------------------------------------------
// 函数：SetVisible()
// 描述：设置属性的可见性
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkAttrImpl<T>::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;

	// 同步更新所有子节点的可见性
	for(CVBF_MarkList::iterator pIter=m_vInnerChildren.begin(); pIter!=m_vInnerChildren.end(); pIter++)
	{
		observer_ptr<IVBF_MarkModel> piChild = *pIter;
		if(piChild.valid()) piChild->SetVisible(bVisible);
	}
}

//----------------------------------------------------------------------------
// 函数：GetDistMin()
// 描述：获取属性的最小可见距离，返回值为false表示用户没有设置最小可见距离
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkAttrImpl<T>::GetDistMin(float& fDistMin)
{
	if(m_fDistMin.isSet())
	{
		fDistMin = m_fDistMin.value();
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------
// 函数：GetDistMax()
// 描述：获取属性的最大可见距离，返回值为false表示用户没有设置最大可见距离
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkAttrImpl<T>::GetDistMax(float& fDistMax)
{
	if(m_fDistMax.isSet())
	{
		fDistMax = m_fDistMax.value();
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------
// 函数：Update()
// 描述：更新 (在每帧绘制前由系统调用)，返回值为false表示未做更新处理（如模型不可见时）
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkAttrImpl<T>::Update()
{ 
	// 每帧都需要更新所有内部子模型的可见性，否则属性从true切换为false后仍然可见（杜莹添加：2017-11-24）
	for(CVBF_MarkList::iterator pIter=m_vInnerChildren.begin(); pIter!=m_vInnerChildren.end(); pIter++)
    {
        observer_ptr<IVBF_MarkModel> piChild = *pIter;
		if(piChild.valid() && piChild->GetRootNode()!=NULL)
		{
			piChild->GetRootNode()->setNodeMask(m_bVisible? ~0 : 0);
		}
	}
	
    if(!m_bVisible) return false;

    // 设置属性的可见距离
    if(m_opIAttachedMark.valid())
    {
        float fDistMin = m_fDistMin.isSet()? m_fDistMin.value() : m_opIAttachedMark->GetDistMin();
        float fDistMax = m_fDistMax.isSet()? m_fDistMax.value() : m_opIAttachedMark->GetDistMax();

        // 更新所有子节点的可见距离
        for(CVBF_MarkList::iterator pIter=m_vInnerChildren.begin(); pIter!=m_vInnerChildren.end(); pIter++)
        {
            observer_ptr<IVBF_MarkModel> piChild = *pIter;
            if(piChild.valid())
            {
                piChild->SetDistMin(fDistMin);
                piChild->SetDistMax(fDistMax);

				// 如果父模型是点状，但子模型不是点状，需要判断是否已经添加到场景图中（杜莹添加：2017-11-08）
				if( m_opIAttachedMark->IsPointMarkModel() && !piChild->IsPointMarkModel() )
				{
					// 需要将子模型的根节点添加到Plot专门设置的一个节点下，避免子模型受到父模型或更上层父模型矩阵的影响（杜莹修改：2015-06-03）
					IVBF_3DPlotLayer* pILayer = (IVBF_3DPlotLayer*)m_opIAttachedMark->GetLayerPtr();
					if(pILayer) piChild->SetParentNode(pILayer->GetNodeForNotPointMarks());
				}
            }
        }
    }

	return true;
}

//-----------------------------------------------------------------------------
// 函数：WriteToXML()
// 描述：串行化，将模型属性信息写入指定的xml节点
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkAttrImpl<T>::WriteToXML(TiXmlElement* pElemAttr)
{
	if(NULL==pElemAttr) return false;

	::VBF_SetAttribute(pElemAttr, "Type",     m_nType);
	::VBF_SetAttribute(pElemAttr, "TypeDesc", m_strTypeDesc);
	::VBF_SetAttribute(pElemAttr, "Visible",  m_bVisible);

	return true;
}

//----------------------------------------------------------------------------
// 函数：ReadFromXML()
// 描述：串行化，从指定的xml节点读取模型属性信息
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkAttrImpl<T>::ReadFromXML(TiXmlElement* pElemAttr)
{
    if(NULL==pElemAttr) return false;

    bool bVisible = IsVisible();
    ::VBF_QueryAttribute(pElemAttr, "Visible", bVisible);

    // 更新相关参数
    SetVisible(bVisible);

    return true;
}

//----------------------------------------------------------------------------
// 函数：ExecuteScript()
// 描述：执行json脚本
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkAttrImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
	bool bVisible = IsVisible();
    if( conf.getIfSet("Visible", bVisible) )
	{
		SetVisible(bVisible);
	} 
}



#endif 
