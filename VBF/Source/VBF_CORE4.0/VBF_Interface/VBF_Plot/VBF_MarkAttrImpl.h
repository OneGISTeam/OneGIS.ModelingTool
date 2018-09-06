//*******************************************************************
// FileName��CVBF_MarkAttrImpl.h
// Function����ͼʵ��ģ�����Խӿ�ʵ��
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
// ����ӿڣ�CVBF_MarkAttrImpl
// �ӿ���������ͼʵ��ģ�����Խӿ�ʵ��
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

	// ��ȡ��������
	virtual unsigned int GetType()		{ return m_nType; }

	// ��ȡ�������͵��������Ա��û����
	virtual const std::string& GetTypeDesc() { return m_strTypeDesc; }

	// ����/��ȡ�ɼ���
	virtual void SetVisible(bool bVisible);
	virtual bool IsVisible()		{ return m_bVisible; }

	// �����������󶨵�ʵ��ģ��
	virtual void SetMarkModel(IVBF_MarkModel* pIMark);
    virtual IVBF_MarkModel* GetMarkModel()	{ return m_opIAttachedMark.get(); }

	// ����/��ȡ������С���ɼ����룬���û�����ã�Ĭ��ʹ���������󶨵�ʵ��ģ�͵Ŀɼ�����
	// �����ȡ�ķ���ֵΪfalse����ʾ�û�û���������Ե���С���ɼ�����
	virtual void SetDistMin(float fDistMin)  { m_fDistMin = fDistMin; }
	virtual bool GetDistMin(float& fDistMin);

	virtual void SetDistMax(float fDistMax)  { m_fDistMax = fDistMax; }
	virtual bool GetDistMax(float& fDistMax);

	// ����
	virtual IVBF_MarkAttr* Clone() { return NULL; }
	
	virtual bool ExecuteCommand(const char* szCommandID, IVBF_PropertySet* pInParam, IVBF_PropertySet* pOutParam){ return false; }

    // �Ҽ������˵�
    virtual void GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vItems) { return; }
    virtual bool ProcessPopupMenuItem(unsigned int nID) { return false; }

    // ���л�
    virtual bool WriteToXML(TiXmlElement* pElemAttr);    // ��ģ��������Ϣд��ָ����xml�ڵ�
    virtual bool ReadFromXML(TiXmlElement* pElemAttr);   // ��ָ����xml�ڵ��ȡģ��������Ϣ

	// ��ʼ�� (�ڹ��캯��֮����ϵͳ����)
    virtual bool Init(IVBF_MarkContext* pIContext);

	// ���� (��ÿ֡����ǰ��ϵͳ����)������ֵΪfalse��ʾδ�����´�����ģ�Ͳ��ɼ�ʱ��
	virtual bool Update();

	// ִ��json�ű�
    virtual void ExecuteScript(const CVBF_Config& conf);

protected:

	// ���/�Ƴ�һ��ʵ�ָ�������ʹ�õ��ڲ���ģ��
	void AddInnerChild(IVBF_MarkModel* pIChild);
	void RemoveInnerChild(IVBF_MarkModel* pIChild);

protected:
	unsigned int 	m_nType;			// �����Ե�����
	std::string		m_strTypeDesc;		// �����Ե���������
	bool			m_bVisible;			// �Ƿ�ɼ�

	// ��С���ɼ�����
	CVBF_Optional<float>	m_fDistMin;
	CVBF_Optional<float>	m_fDistMax;

	// �����԰󶨵�ʵ��ģ��
    observer_ptr<IVBF_MarkModel>	m_opIAttachedMark;

	// ʵ�ָ�������ʹ�õ��ڲ���ģ�ͣ���ʵ��Label����ʹ��Textģ�ͣ�ʵ��Trail����ʹ�õ�Stripģ�ͣ�
	typedef std::vector< observer_ptr<IVBF_MarkModel> >	CVBF_MarkList;
	CVBF_MarkList		m_vInnerChildren;

	// ������Ҫʹ�õ��ⲿ�ڵ㣨��Init()�����л�ȡ��
	IVBF_3DMainCtrl*						m_pI3DMainCtrl;
	observer_ptr<IVBF_View>					m_opView;
	observer_ptr<osg::IVBF_Camera>			m_opCamera;
    ref_ptr<IVBF_MarkContext> m_ipContext;
};


//-----------------------------------------------------------------------------
// ������CVBF_MarkAttrImpl()
// ���������캯��
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkAttrImpl<T>::CVBF_MarkAttrImpl(unsigned int nType)
{
	m_nType			= nType;
	m_strTypeDesc	= "";
	m_bVisible		= true;
}

//-----------------------------------------------------------------------------
// ������~CVBF_MarkAttrImpl()
// ��������������
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
// ������Init()
// ��������ʼ�� (�ڹ��캯��֮����ϵͳ����)
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkAttrImpl<T>::Init(IVBF_MarkContext* pIContext)
{
    if(pIContext==NULL) return false;
    m_ipContext = pIContext;

	CVBF_3DEnvironment& env = ::VBF_Get3DEnvironment();
	m_pI3DMainCtrl = env.m_pI3DMainCtrl;

	// ��ȡģ�����ڵ���ͼ��Ŀǰ��ʱ��˴����Ժ�Ӧ�����ⲿ���룩
	m_opView = ::VBF_GetMainView(env.m_pI3DMainCtrl);
	if(!m_opView.valid()) return false;

	m_opCamera = m_opView->getCamera();
	if(!m_opCamera.valid()) return false;

	return true;
}

//----------------------------------------------------------------------------
// ������AddInnerChild()
// ���������һ��ʵ�ָ�������ʹ�õ��ڲ���ģ��
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkAttrImpl<T>::AddInnerChild(IVBF_MarkModel* pIChild)
{
	if(pIChild!=NULL) m_vInnerChildren.push_back(pIChild);
}

//----------------------------------------------------------------------------
// ������RemoveInnerChild()
// �������Ƴ�һ��ʵ�ָ�������ʹ�õ��ڲ���ģ��
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
// ������SetMarkModel()
// �����������������󶨵�ʵ��ģ��
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkAttrImpl<T>::SetMarkModel(IVBF_MarkModel* pIMark)
{ 
	// �������ӽڵ��ԭ���ĸ��ڵ�������
    if(m_opIAttachedMark.valid())
	{
		for(CVBF_MarkList::iterator pIter=m_vInnerChildren.begin(); pIter!=m_vInnerChildren.end(); pIter++)
		{
			observer_ptr<IVBF_MarkModel> piChild = *pIter;
            if(piChild.valid()) m_opIAttachedMark->RemoveChild(piChild.get());
		}
	}

	// �������ӽڵ������µĸ��ڵ�
	if(pIMark!=NULL)
	{
		for(CVBF_MarkList::iterator pIter=m_vInnerChildren.begin(); pIter!=m_vInnerChildren.end(); pIter++)
		{
			observer_ptr<IVBF_MarkModel> piChild = *pIter;
			if(piChild.valid()) pIMark->AddChild(piChild.get());
		}
	}

	// ����¼�µĸ��ڵ�
    m_opIAttachedMark = pIMark;
}

//----------------------------------------------------------------------------
// ������SetVisible()
// �������������ԵĿɼ���
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkAttrImpl<T>::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;

	// ͬ�����������ӽڵ�Ŀɼ���
	for(CVBF_MarkList::iterator pIter=m_vInnerChildren.begin(); pIter!=m_vInnerChildren.end(); pIter++)
	{
		observer_ptr<IVBF_MarkModel> piChild = *pIter;
		if(piChild.valid()) piChild->SetVisible(bVisible);
	}
}

//----------------------------------------------------------------------------
// ������GetDistMin()
// ��������ȡ���Ե���С�ɼ����룬����ֵΪfalse��ʾ�û�û��������С�ɼ�����
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
// ������GetDistMax()
// ��������ȡ���Ե����ɼ����룬����ֵΪfalse��ʾ�û�û���������ɼ�����
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
// ������Update()
// ���������� (��ÿ֡����ǰ��ϵͳ����)������ֵΪfalse��ʾδ�����´�����ģ�Ͳ��ɼ�ʱ��
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkAttrImpl<T>::Update()
{ 
	// ÿ֡����Ҫ���������ڲ���ģ�͵Ŀɼ��ԣ��������Դ�true�л�Ϊfalse����Ȼ�ɼ�����Ө��ӣ�2017-11-24��
	for(CVBF_MarkList::iterator pIter=m_vInnerChildren.begin(); pIter!=m_vInnerChildren.end(); pIter++)
    {
        observer_ptr<IVBF_MarkModel> piChild = *pIter;
		if(piChild.valid() && piChild->GetRootNode()!=NULL)
		{
			piChild->GetRootNode()->setNodeMask(m_bVisible? ~0 : 0);
		}
	}
	
    if(!m_bVisible) return false;

    // �������ԵĿɼ�����
    if(m_opIAttachedMark.valid())
    {
        float fDistMin = m_fDistMin.isSet()? m_fDistMin.value() : m_opIAttachedMark->GetDistMin();
        float fDistMax = m_fDistMax.isSet()? m_fDistMax.value() : m_opIAttachedMark->GetDistMax();

        // ���������ӽڵ�Ŀɼ�����
        for(CVBF_MarkList::iterator pIter=m_vInnerChildren.begin(); pIter!=m_vInnerChildren.end(); pIter++)
        {
            observer_ptr<IVBF_MarkModel> piChild = *pIter;
            if(piChild.valid())
            {
                piChild->SetDistMin(fDistMin);
                piChild->SetDistMax(fDistMax);

				// �����ģ���ǵ�״������ģ�Ͳ��ǵ�״����Ҫ�ж��Ƿ��Ѿ���ӵ�����ͼ�У���Ө��ӣ�2017-11-08��
				if( m_opIAttachedMark->IsPointMarkModel() && !piChild->IsPointMarkModel() )
				{
					// ��Ҫ����ģ�͵ĸ��ڵ���ӵ�Plotר�����õ�һ���ڵ��£�������ģ���ܵ���ģ�ͻ���ϲ㸸ģ�;����Ӱ�죨��Ө�޸ģ�2015-06-03��
					IVBF_3DPlotLayer* pILayer = (IVBF_3DPlotLayer*)m_opIAttachedMark->GetLayerPtr();
					if(pILayer) piChild->SetParentNode(pILayer->GetNodeForNotPointMarks());
				}
            }
        }
    }

	return true;
}

//-----------------------------------------------------------------------------
// ������WriteToXML()
// ���������л�����ģ��������Ϣд��ָ����xml�ڵ�
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
// ������ReadFromXML()
// ���������л�����ָ����xml�ڵ��ȡģ��������Ϣ
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkAttrImpl<T>::ReadFromXML(TiXmlElement* pElemAttr)
{
    if(NULL==pElemAttr) return false;

    bool bVisible = IsVisible();
    ::VBF_QueryAttribute(pElemAttr, "Visible", bVisible);

    // ������ز���
    SetVisible(bVisible);

    return true;
}

//----------------------------------------------------------------------------
// ������ExecuteScript()
// ������ִ��json�ű�
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
