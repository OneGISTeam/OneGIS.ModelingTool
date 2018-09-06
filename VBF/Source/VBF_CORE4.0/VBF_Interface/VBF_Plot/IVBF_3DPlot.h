//***************************************************************************************
// FileName�� IVBF_3DPlot.h
// Function�� 3D��ͼ�ӿڣ���������ͼ���ĵ�
// Author:    ��Ө
// Date:      2013-07-04
//***************************************************************************************

#ifndef __IVBF_3DPLOT_H__
#define __IVBF_3DPLOT_H__


#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Base/IVBF_SimulationTimer.h>

#include <VBF_Plot/IVBF_3DPlotEditor.h>
#include <VBF_Plot/IVBF_3DPlotDoc.h>
#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/IVBF_MarkAttr.h>
#include <VBF_Plot/IVBF_MarkAction.h>
#include <VBF_Plot/IVBF_MarkProcess.h>

#include <VBF_Plot/IVBF_MarkTracker.h>
#include <VBF_Plot/IVBF_MarkInputHandler.h>

#include <string>


// ����������ID��
const char VBF_COMPONENT_3DPLOT[]	= "Component: 3DPlot";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DPLOT[]	= "��ά��ͼ�ӿ�";	

// �����������������ϢVBF_MESSAGE_3DPLOT_MARK_SELECTED�ȵĲ�����
typedef std::vector< observer_ptr<IVBF_MarkModel> >	CVBF_VectorMarks;


// ������ϢID��
const char VBF_MESSAGE_3DPLOT_MARK_SELECTED[]	= "Message: 3DPlot Mark Selected";	// ��Ϣ��һ������ģ�ͱ�ѡ���ˣ�nValue=ѡ�е�ģ�͸������������Ϊ1��pValue=IVBF_MarkModel*������pValue=CVBF_VectorMarks*
const char VBF_MESSAGE_3DPLOT_MARK_DELETE[]	    = "Message: 3DPlot Mark Delete";	// ��Ϣ��һ��ģ�ͱ�ɾ���ˣ�nValue=1��pValue=IVBF_MarkModel*
const char VBF_MESSAGE_3DPLOT_MARK_ADD[]	    = "Message: 3DPlot Mark Add";		// ��Ϣ��һ��ģ�ͱ�����ˣ�nValue=1��pValue=IVBF_MarkModel*
const char VBF_MESSAGE_3DPLOT_MARK_VISIBLE[]	= "Message: 3DPlot Mark Visible";	// ��Ϣ��һ��ģ�͵Ŀɼ��Ըı��ˣ�nValue=bVisible��pValue=IVBF_MarkModel*
const char VBF_MESSAGE_3DPLOT_MARK_EDIT_END[]	= "Message: 3DPlot Mark Edit End";	// ��Ϣ��һ��ģ�͵Ŀɼ��Ըı��ˣ�nValue=bVisible��pValue=IVBF_MarkModel*


const char VBF_MESSAGE_3DPLOT_LAYER_NEW[]	    = "Message: 3DPlot Layer New";		// ��Ϣ��һ��ͼ�㱻����ˣ�nValue=1��pValue=IVBF_3DPlotLayer*
const char VBF_MESSAGE_3DPLOT_LAYER_DELETE[]	= "Message: 3DPlot Layer Delete";	// ��Ϣ��һ��ͼ�㱻ɾ���ˣ�nValue=1��pValue=strLayerName
const char VBF_MESSAGE_3DPLOT_LAYER_ACTIVE[]	= "Message: 3DPlot Layer Active";	// ��Ϣ��һ��ͼ�㱻�����ˣ�nValue=1��pValue=IVBF_3DPlotLayer*
const char VBF_MESSAGE_3DPLOT_LAYER_VISIBLE[]	= "Message: 3DPlot Layer Visible";	// ��Ϣ��һ��ͼ��Ŀɼ��Ըı��ˣ�nValue=bVisible��pValue=IVBF_3DPlotLayer*

// ��������ID��
const char VBF_COMMAND_3DPLOT_SAVEMESHINFO[]	= "Command: 3DPlot_SaveMeshInfo";	// ����ģ����Ϣ
const char VBF_COMMAND_3DPLOT_LAYERMANAGER[]	= "Command: 3DPlot_LayerManager";	// ͼ�������
const char VBF_COMMAND_3DPLOT_FILE_INPUT[]		= "Command: 3DPlot_FileInput";		// ���ļ�����
const char VBF_COMMAND_3DPLOT_MODEL_UI[]		= "Command: 3DPlot_ModelUI";		// ģ��ѡ��UI
const char VBF_COMMAND_SHOWDIALOG_PLOTMANAGER[]	= "Command: Show Dialog PlotManager";	// ��ʾͼ�����Ի���


// ���幤��ID��
const char VBF_TOOL_MARK_SELECT[]					= "Tool: Select One Mark";						// ͨ������������ѡ�񵥸�ģ��
const char VBF_TOOL_MARK_SELECT_QUICK[]				= "Tool: Select One Mark Quickly";				// ͨ������ƶ�����ѡ��ģ�Ͳ���ʾģ����Ϣ
const char VBF_TOOL_MARK_SELECT_QUICK_AND_EDIT[]	= "Tool: Select One Mark Quickly And Edit";		// ͨ������ƶ�����ѡ��ģ�Ͳ���ʾģ����Ϣ���ٴε�����ģ��ʱ����༭״̬
const char VBF_TOOL_MARK_SELECT_RECT[]				= "Tool: Select By Rect";						// ͨ���������Ļ�ϵ��������ѡ����ģ��
const char VBF_TOOL_MARK_EDIT[]                     = "Tool: Plot State";                           // �༭����

//const char VBF_TOOL_MARK_EDIT_SUB_INPUT[]  =   "Tool: Edit Sub Input";
//const char VBF_TOOL_MARK_EDIT_SUB_ROTATE[] =   "Tool: Edit Sub Rotate";
//const char VBF_TOOL_MARK_EDIT_SUB_SCALE[]  =   "Tool: Edit Sub Scale";
//const char VBF_TOOL_MARK_EDIT_SUB_LOCAL[]  =   "Tool: Edit Sub Local";
//const char VBF_TOOL_MARK_EDIT_SUB_ATTR[]   =   "Tool: Edit Sub Attr";
//const char VBF_TOOL_MARK_EDIT_SUB_TRANSLATE[]  = "Tool: Edit Sub Translate";


class IVBF_MarkModelMesh;
class CVBF_Config;

//-----------------------------------------------------------
// ����ö�٣�EVBF_PLOT_STATE
// ö����������ͼģ�����״̬
//-----------------------------------------------------------
enum EVBF_PLOT_STATE
{
    VBF_PLOT_STATE_NONE = 0,
    VBF_PLOT_STATE_ATTR,        // ���Ա༭
    VBF_PLOT_STATE_TRANSLATE,   // ƽ��
    VBF_PLOT_STATE_SCALE,       // ����
    VBF_PLOT_STATE_ROTATE,      // ��ת
    VBF_PLOT_STATE_EDITLOCAL,   // �ֲ��༭
    VBF_PLOT_STATE_INPUT        // ����
};



//------------------------------------------------------------------
// ����ӿڣ�IVBF_3DPlot
// �ӿ�������3D����Ĺ���ӿ�
//------------------------------------------------------------------
class IVBF_3DPlot : public CVBF_Referenced
{
public:
	virtual ~IVBF_3DPlot() {}

public:

    // ����/��ȡ��ͼģ�����״̬��Ĭ��ֵΪVBF_PLOT_STATE_NONE
    virtual void            SetState(EVBF_PLOT_STATE nState)=0;
    virtual EVBF_PLOT_STATE GetState()=0;

    // ��ȡģ�ͱ༭�ӿ�
    virtual IVBF_3DPlotEditor* GetEditor()=0;
	
	// ��ȡϵͳ�Զ�������ȱʡ�ĵ������ĵ�������ɾ��
	virtual IVBF_3DPlotDoc* GetDefaultDoc()=0;
	virtual std::string     GetDefaultDocName()=0;

	// ���/ɾ��/����һ����ͼ�ĵ�
    virtual IVBF_3DPlotDoc* AddDoc(const std::string& strDocName,osg::IVBF_SGNodeGroup* pINodeParent=NULL)=0;
	virtual bool            DeleteDoc(const std::string& strDocName)=0;
	virtual bool            DeleteDoc(IVBF_3DPlotDoc* pIDoc)=0;
	virtual IVBF_3DPlotDoc* GetDoc(const std::string& strDocName)=0;

	// ����һ����ͼ�ĵ�
	virtual void               ActivateDoc(const std::string& strDocName)=0;   
	virtual IVBF_3DPlotDoc*    GetActiveDoc()=0;
	virtual const std::string& GetActiveDocName()=0;

	// ������ͼ�ĵ�
	virtual int             GetDocCount()=0;          
	virtual IVBF_3DPlotDoc* GetDoc(int nIndex)=0;

	// ��ȡ���б�ͼ�ĵ�
	virtual void GetAllDocs(std::vector<IVBF_3DPlotDoc*>& vDocs)=0;

    // ����һ������ģ�ͣ�ͨ���˻������ķ�ʽ
    virtual void InputMark(unsigned int nType, const std::string& strCode="")=0;
    virtual IVBF_MarkInputHandler* GetInputHandler()=0; // ��ȡ���봦����

    // ͨ��ָ�����ͣ�����һ������ģ��
    virtual IVBF_MarkModel* CreateMarkModel(const std::string& strMarkID, unsigned int nMarkType)=0;

    // ͨ��ָ��MarkStyle.xml�����ļ��е����ͱ��룬����һ������ģ�Ͳ���ȡģ����Ϣ
    virtual IVBF_MarkModel* CreateMarkModel(const std::string& strMarkID, const std::string& strCode)=0;

    // ͨ��ָ��xml�ڵ㣬����һ������ģ�Ͳ���ȡģ����Ϣ
    virtual IVBF_MarkModel* CreateMarkModel(TiXmlElement* pElemMark)=0;

	// ����һ����������
	virtual IVBF_MarkAttr* CreateMarkAttr(unsigned int nAttrType)=0;

    // ����һ����Ϊ
    virtual IVBF_MarkAction* CreateMarkAction(const std::string& strActionType)=0;

    // ����һ������
    virtual IVBF_MarkProcess* CreateMarkProcess(const std::string& strProcessType)=0;

    virtual void ProcessSimulate()=0; // ����ģ��
    virtual void StatStartTime(double& dStartTime)=0;// ͳ�����й��̵���ʼʱ��


	// �����е�״ģ������һ��ͳһ���Զ����ű�
	virtual float GetPointMarkAutoScale()=0;

	// �����е�״ģ������һ��ͳһ�����ű�ϵ��
	virtual void  SetPointMarkScaleDelta(float fScaleDelta)=0;
	virtual float GetPointMarkScaleDelta()=0;

    // �����Ժ���������ģ��ָ�룬��ȡ�����ڵ��ĵ���ͼ������
    virtual bool GetDocLayerNameOfMark(IVBF_MarkModel* pIMark, std::string& strDocName, std::string& strLayerName)=0;

    // �����Ժ���������ģ�����ڵ��ĵ���ͼ�㼰ģ��ID�ţ���ȡģ��ָ��
    virtual IVBF_MarkModel* FindMark(const std::string& strDocName, const std::string& strLayerName, const std::string& strMarkID)=0;
    // �������ĵ��ڲ���ģ��
    virtual IVBF_MarkModel* FindMark(const std::string& strMarkID)=0;

	// ���л�������ͼ��Ϣд��ָ����xml�ļ���ڵ�
	virtual bool WriteToXML(const std::string& strFn)=0;
	virtual bool WriteToXML(TiXmlElement* pElemPlot)=0;

	// ���л�����ָ����xml�ļ���ڵ��ȡ��ͼ��Ϣ
	virtual bool ReadFromXML(const std::string& strFn)=0;
	virtual bool ReadFromXML(TiXmlElement* pElemPlot)=0;

	virtual void SetLineSmooth(bool bSmooth)=0;
	virtual void SetPolySmooth(bool bSmooth)=0;

    virtual void UpdateEciMatrix(double dEpochUTC,const Matrix& matJ20002Ecef)=0;

    // ִ�нű�����Plot
    virtual CVBF_Config ExecuteScript(const CVBF_Config&)=0;

	
};


#endif
