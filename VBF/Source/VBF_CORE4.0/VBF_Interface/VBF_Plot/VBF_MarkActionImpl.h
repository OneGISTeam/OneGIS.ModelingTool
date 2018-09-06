//*******************************************************************
// FileName��CVBF_MarkActionImpl.h
// Function����ͼʵ��ģ�Ͷ����ӿ�ʵ��
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
// ����ӿڣ�CVBF_MarkActionImpl
// �ӿ���������ͼʵ��ģ�Ͷ����ӿ�ʵ��
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

    // ��ȡ��������
    virtual const std::string& GetType()		{ return m_sType; }

    // ��ȡ��������
    virtual void SetName(const std::string& sName) { m_strName = sName; }
    virtual const std::string& GetName() { return m_strName; }

    // ��ȡ�������͵��������Ա��û����
	virtual const std::string& GetTypeDesc() { return m_strTypeDesc; }

	// ����/��ȡ�ɼ���
    virtual void Enable(bool bEnable);
    virtual bool IsEnable() { return m_bEnable; }

    // ���ö������󶨵�ʵ��ģ��
	virtual void SetMarkModel(IVBF_MarkModel* pIMark);
    virtual IVBF_MarkModel* GetMarkModel()	{ return m_opIAttachedMark.get(); }

	// ����
    virtual IVBF_MarkAction* Clone() { return NULL; }
	
	virtual bool ExecuteCommand(const char* szCommandID, IVBF_PropertySet* pInParam, IVBF_PropertySet* pOutParam){ return false; }

    // �Ҽ������˵�
    virtual void GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vItems) { return; }
    virtual bool ProcessPopupMenuItem(unsigned int nID) { return false; }

    // ���л�
    virtual bool WriteToXML(TiXmlElement* pElemAction);    // ��ģ�Ͷ�����Ϣд��ָ����xml�ڵ�
    virtual bool ReadFromXML(TiXmlElement* pElemAction);   // ��ָ����xml�ڵ��ȡģ�Ͷ�����Ϣ

	// ��ʼ�� (�ڹ��캯��֮����ϵͳ����)
    virtual bool Init(IVBF_MarkContext* pIContext);

	// ���� (��ÿ֡����ǰ��ϵͳ����)������ֵΪfalse��ʾδ�����´�����ģ�Ͳ��ɼ�ʱ��
	virtual bool Update();

	// ִ��json�ű�
    virtual void ExecuteScript(const CVBF_Config& conf);


protected:
    std::string 	m_sType;			// �ö���������
    std::string		m_strTypeDesc;		// �ö�������������
    std::string		m_strName;		// �ö���������
    bool			m_bEnable;			// �Ƿ�ִ��


    // �ö����󶨵�ʵ��ģ��
    observer_ptr<IVBF_MarkModel>	m_opIAttachedMark;


	// ������Ҫʹ�õ��ⲿ�ڵ㣨��Init()�����л�ȡ��
	IVBF_3DMainCtrl*						m_pI3DMainCtrl;
	observer_ptr<IVBF_View>					m_opView;
	observer_ptr<osg::IVBF_Camera>			m_opCamera;
    ref_ptr<IVBF_MarkContext> m_ipContext;
};


//-----------------------------------------------------------------------------
// ������CVBF_MarkActionImpl()
// ���������캯��
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkActionImpl<T>::CVBF_MarkActionImpl(const std::string& sType)
{
    m_sType			= sType;
	m_strTypeDesc	= "";
    m_bEnable		= true;
}

//-----------------------------------------------------------------------------
// ������~CVBF_MarkActionImpl()
// ��������������
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkActionImpl<T>::~CVBF_MarkActionImpl()
{
}

//-----------------------------------------------------------------------------
// ������Init()
// ��������ʼ�� (�ڹ��캯��֮����ϵͳ����)
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkActionImpl<T>::Init(IVBF_MarkContext* pIContext)
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
// ������SetMarkModel()
// ���������ö������󶨵�ʵ��ģ��
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkActionImpl<T>::SetMarkModel(IVBF_MarkModel* pIMark)
{ 
	// ����¼�µĸ��ڵ�
    m_opIAttachedMark = pIMark;
}

//----------------------------------------------------------------------------
// ������SetVisible()
// ���������ö����Ŀɼ���
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkActionImpl<T>::Enable(bool bEnable)
{
    m_bEnable = bEnable;
}


//----------------------------------------------------------------------------
// ������Update()
// ���������� (��ÿ֡����ǰ��ϵͳ����)������ֵΪfalse��ʾδ�����´�����ģ�Ͳ��ɼ�ʱ��
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkActionImpl<T>::Update()
{ 
    if(!m_bEnable) return false;

    return true;
}

//-----------------------------------------------------------------------------
// ������WriteToXML()
// ���������л�����ģ�Ͷ�����Ϣд��ָ����xml�ڵ�
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
// ������ReadFromXML()
// ���������л�����ָ����xml�ڵ��ȡģ�Ͷ�����Ϣ
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

    // ������ز���
    Enable(bEnable);




    return true;
}

//----------------------------------------------------------------------------
// ������ExecuteScript()
// ������ִ��json�ű�
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
