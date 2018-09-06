//***************************************************************************************
// FileName��IVBF_MainCtrl.h
// Function��ͼ�μ��ɿ�ܽӿڡ�
//           �ýӿ����ϵͳ3D���ؽӿ����ݣ�����ؼ�ע�ᡢ����ַ����¼����������
// Author:   ��Ө
// Date:     2012-03-22
//***************************************************************************************

#ifndef __IVBF_MAIN_CTRL_H__
#define __IVBF_MAIN_CTRL_H__

#include "VBF_Macros.h"
#include "IVBF_Observer.h"
#include "IVBF_Subject.h"
#include "IVBF_Component.h"

// ����ģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_MAIN[]				=	"����";	

// �����׼�ӿڵ�ID��
const char VBF_INTERFACE_MAIN_COMMAND[]	    =	"����������Ӧ�ӿ�";	
const char VBF_INTERFACE_MAIN_TOOL[]	    =	"���ؽ���������Ӧ�ӿ�";	
const char VBF_INTERFACE_MAIN_UIPROCESSOR[]	=	"�����û����洦��ӿ�";	
const char VBF_INTERFACE_MAIN_MESSAGE[]	    =	"������Ϣ��Ӧ�ӿ�";
const char VBF_INTERFACE_MAIN_EVENTHANDLER[]    =	"���ؽ����¼���Ӧ�ӿ�";

// ������ϢID��
const char VBF_MESSAGE_VIEWPORTCHANGED[]		= "Message: Viewport Changed";			// �ӿڸ�����
const char VBF_MESSAGE_ALLCOMPONENTS_INITED[]	= "Message: All Components Inited";		// ���������ʼ�����

const char VBF_MESSAGE_REGIST_COM[]		= "Message: Regist Component";	// ע�����
const char VBF_MESSAGE_UNREGIST_COM[]	= "Message: UnRegist Component";	// ע�����


// ��������ID��
const char VBF_COMMAND_CLEARSCREEN[]			= "Command: Clear Screen";

class IVBF_PropertySet;


//--------------------------------------------------------------------------------------------------
// ����ӿڣ�IVBF_MainCtrl
// �ӿ�������3Dͼ�μ��ɿ�ܽӿڣ����ϵͳ����ӿ����ݣ�����ؼ�ע�ᡢ����ַ����¼�������ͼ������
//---------------------------------------------------------------
class IVBF_MainCtrl : public IVBF_Observer, public IVBF_Subject
{
public:
	virtual ~IVBF_MainCtrl() {}

public:

	// Ϊ�˼���DTIS����ʱʹ�ã�������������
	virtual char* GetType() = 0;

	//---------------------------------------------------------------
	// ��ȡ/�������ص�IDֵ��
	//---------------------------------------------------------------
	virtual long GetID() = 0 ;
	virtual void SetID(long lID) = 0 ;

	//---------------------------------------------------------------
	// ��ȡ/�������ص���;��
	//---------------------------------------------------------------
	virtual void SetPurpose( const char* pPurpose )=0;
	virtual char* GetPurpose( ) = 0;



	//---------------------------------------------------------------
	// ɾ��ϵͳ���ض���
	//---------------------------------------------------------------
	virtual void Release() = 0;

	//---------------------------------------------------------------
	// �Ӷ�̬���ļ�ע�������
	// ����ָ���������̬���ļ���ע�����������Ϊ�����̬���ļ���ȫ·������
	// szComponentFile:������ڶ�̬����ļ�·����
	// return ����ɹ�ɾ������true�����򷵻�false��
	//---------------------------------------------------------------
    virtual bool RegisterComponentFile(const char* szComponentFile) = 0;

	//---------------------------------------------------------------
	// �������ļ�ע�������
	// ����ָ������������ļ���ע�����������Ϊ��������ļ���ȫ·������
	// ��������ļ��а���Ҫע���һ�������̬�����ơ�
	// szComponentCfgFile ��������������ļ���·����
	//---------------------------------------------------------------
	virtual bool RegisterComponentCfgFile(const char* szComponentCfgFile) = 0;

	//---------------------------------------------------------------
	// ע��/ж���Ѽ���ϵͳ�е�ȫ�������
	//---------------------------------------------------------------
    virtual void RegisterComponentCfgFileDefault() = 0;	


	//---------------------------------------------------------------
	// ɾ��ָ�������
	// szComponentID:���ID��
	// return ����ɹ�ɾ������true�����򷵻�false��
        //---------------------------------------------------------------__declspec
	virtual bool RemoveComponent(const char* szComponentID) = 0;

    virtual void* PreRemoveComponent(const char* szComponentFile)=0;

	//---------------------------------------------------------------
	// ָ�����ID����ȡ����ӿ�ָ�롣
	// szComponentID:���ID��
	// return ���ָ�룬���û�и��������NULL��
	//---------------------------------------------------------------
	virtual IVBF_Component* GetComponentPtr(const char* szComponentID) = 0;
	
	
	//---------------------------------------------------------------
	// ��ȡָ���Ľӿ�ָ�롣
	// �����޷�֪��ÿ���ӿڵ����ͣ�����ÿ���ӿڶ���void*���أ�
	// ��������Ҫͨ��ǿ������ת������Ҫ�Ľӿ����͡�
	// szInterfaceID:�ӿ�ID��
	// �ӿ�ָ�롣 szComponentID,�ų������ID����ֹ�������ң��γ���ѭ��
	//---------------------------------------------------------------
	virtual void* QueryInterface(const char* szInterfaceID,const char* szComponentID = NULL) = 0;
	
	
	//---------------------------------------------------------------
	// ִ��ָ�����
	// szCommandID:����ID��
	// pInParam:����������京��������������
	// pOutParam:����������京��������������
	// return ���ִ�гɹ�����true�����򷵻�false��
	//---------------------------------------------------------------
	virtual bool ExecuteCommand(const char* szCommandID, IVBF_PropertySet* pInParam, IVBF_PropertySet* pOutParam) = 0;

	//---------------------------------------------------------------
	// ѡ�н������ߡ�
	// szToolID:��������ID��
	// return ���ѡ��ɹ�����true�����򷵻�false��
	//---------------------------------------------------------------
	virtual bool SelectTool(const char* szToolID) = 0;
	
	//---------------------------------------------------------------
	// ��ȡ��ǰ���ߡ�
	// return ��ǰ����ID��
	//---------------------------------------------------------------
	virtual const char* GetCurrentTool() = 0;

	//---------------------------------------------------------------
	// ����¼���ڣ�Ϊ�˼���DTIS����ʱʹ�ã�������������
	// nMouseEvent:����¼����ͣ�����������ֵ֮һ:
	// DTIS_MOUSE_LBUTTONDOWN��DTIS_MOUSE_LBUTTONUP�� DTIS_MOUSE_LBUTTONDBLCLK��DTIS_MOUSE_RBUTTONDOWN��
	// DTIS_MOUSE_RBUTTONUP��DTIS_MOUSE_MOVE��DTIS_MOUSE_WHEEL��DTIS_MOUSE_CANCEL��
	// nKeyStatus: ����״̬������������ֵ�������:
	// DTIS_MOUSE_LBUTTON��DTIS_MOUSE_RBUTTON��DTIS_MOUSE_SHIFT��DTIS_MOUSE_CONTROL��DTIS_MOUSE_MBUTTON��
	// nX��nY:���ĵ�ǰλ�á�
	// nDelta:�����ֵĹ����ߴ硣
	// return 0��ʾ����¼����ɹ�������ֵ��ʾ�ɹ���ÿ��ֵ�ĺ����ɾ������������
	//---------------------------------------------------------------
	virtual bool OnMouseEvent(int nMouseEvent, int nKeyStatus, int nX, int nY, int nDelta) = 0;

	//---------------------------------------------------------------
	// �����¼���ڣ�Ϊ�˼���DTIS����ʱʹ�ã�������������
	// nKeyEvent:�����¼�����:����������ֵ֮һ
	// DTIS_KEY_DOWN��DTIS_KEY_UP��DTIS_KEY_CHAR��	
	// nChar:���̰��µ��ַ���
	// nRepCount:�ظ����´�����
	// nFlag:״̬���������庬��μ�msdn��OnKeyDown,OnKeyUp��nFlags��˵����
	// return 0��ʾ����¼����ɹ�������ֵ��ʾ�ɹ���ÿ��ֵ�ĺ����ɾ������������
	//---------------------------------------------------------------
	virtual bool OnKeyEvent(int nKeyEvent, int nChar, int nRepCount, int nFlag) = 0;


	//---------------------------------------------------------------
	// ������¡�
	// ���ù�������˵�����Ӧ������ĸ�����Ϣ���ú�����ϵͳ���á�
	// szCommandID:����id��
	// pEnable:�Ƿ���á�
	// pCheck:�Ƿ�ѡ�С�
	// pRadio:�Ƿ�ѡ��
	// szText:�������ݡ�
	// return ����Ѿ����������true�����򷵻�false��
	//---------------------------------------------------------------
	virtual bool UpdateUI(const char* szCommandID, int* pEnable, int* pCheck, int* pRadio, char* szText) = 0;
	

	//---------------------------------------------------------------
	// ����/ȡ������ָ������Ϣ��
	// �ú���ʵ����Ϣ�ġ�����-������ģʽ��ϵͳ���ػ����Ϣ���������˸���Ϣ�������
	// szMessage: ��ϢID��
	// pIMessage: ��Ϣ������
	//---------------------------------------------------------------
	virtual void SubscribeMessage(const char* szMessage, IVBF_Component* pIComponent) = 0;
	virtual void UnSubscribeMessage(const char* szMessage, IVBF_Component* pIComponent) = 0;

	//---------------------------------------------------------------
	// ������Ϣ��
	// �ú����������������������Ϣ��ϵͳ���ػ����Ϣ����������Ӧ����Ϣ�������
	// szMessage:��ϢID��
	// nValue, pValue:��Ϣ���������庬������Ϣ���������
	//---------------------------------------------------------------
    virtual void SendMessage(void* pSender,const char* szMessage, int nValue, void* pValue) = 0;

	
	//---------------------------------------------------------------
	// ���
	// �ڶ��ĵ������У�ÿ���л���ǰ�ĵ�ʱ����Ҫ�ѵ�ǰ�ĵ�����Ϊ�״̬�����ػ���ÿ�����������Ϣ��
	// ÿ����������ڴ�ʱ��һЩ�л��������繤�����ϵĶԻ�������ڴ�ʱ����������������أ�һЩ��ģ̬�Ի�������ڴ�ʱ�л�����������أ���
	//---------------------------------------------------------------
	virtual void SetActive(bool bActive) = 0;

	virtual void  SetAppPath(const char* szPath)=0;
	virtual char* GetAppPath()=0;
	virtual void  SetSysSetPath(const char* szPath)=0;
	virtual char* GetSysSetPath()=0;
};


#ifdef WIN32
    #ifdef MAIN_EXPORTS
            #define MAIN_API extern "C" __declspec(dllexport)
    #else
            #define MAIN_API extern "C" __declspec(dllimport)
    #endif
#else

    #ifdef MAIN_EXPORTS
            #define MAIN_API extern "C"
    #else
            #define MAIN_API  extern "C"
    #endif
#endif


//----------------------------------------------------------------------
// �������ؽӿں���������3D����ָ�롣
//----------------------------------------------------------------------
MAIN_API IVBF_MainCtrl*  VBF_CreateMainObject();


#endif
