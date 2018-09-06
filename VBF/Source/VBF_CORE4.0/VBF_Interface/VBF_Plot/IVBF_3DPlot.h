//***************************************************************************************
// FileName： IVBF_3DPlot.h
// Function： 3D标图接口，负责管理标图的文档
// Author:    杜莹
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


// 定义该组件的ID号
const char VBF_COMPONENT_3DPLOT[]	= "Component: 3DPlot";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DPLOT[]	= "三维标图接口";	

// 定义迭代器（用作消息VBF_MESSAGE_3DPLOT_MARK_SELECTED等的参数）
typedef std::vector< observer_ptr<IVBF_MarkModel> >	CVBF_VectorMarks;


// 定义消息ID号
const char VBF_MESSAGE_3DPLOT_MARK_SELECTED[]	= "Message: 3DPlot Mark Selected";	// 消息：一个或多个模型被选中了，nValue=选中的模型个数，如果个数为1，pValue=IVBF_MarkModel*，否则pValue=CVBF_VectorMarks*
const char VBF_MESSAGE_3DPLOT_MARK_DELETE[]	    = "Message: 3DPlot Mark Delete";	// 消息：一个模型被删除了，nValue=1，pValue=IVBF_MarkModel*
const char VBF_MESSAGE_3DPLOT_MARK_ADD[]	    = "Message: 3DPlot Mark Add";		// 消息：一个模型被添加了，nValue=1，pValue=IVBF_MarkModel*
const char VBF_MESSAGE_3DPLOT_MARK_VISIBLE[]	= "Message: 3DPlot Mark Visible";	// 消息：一个模型的可见性改变了，nValue=bVisible，pValue=IVBF_MarkModel*
const char VBF_MESSAGE_3DPLOT_MARK_EDIT_END[]	= "Message: 3DPlot Mark Edit End";	// 消息：一个模型的可见性改变了，nValue=bVisible，pValue=IVBF_MarkModel*


const char VBF_MESSAGE_3DPLOT_LAYER_NEW[]	    = "Message: 3DPlot Layer New";		// 消息：一个图层被添加了，nValue=1，pValue=IVBF_3DPlotLayer*
const char VBF_MESSAGE_3DPLOT_LAYER_DELETE[]	= "Message: 3DPlot Layer Delete";	// 消息：一个图层被删除了，nValue=1，pValue=strLayerName
const char VBF_MESSAGE_3DPLOT_LAYER_ACTIVE[]	= "Message: 3DPlot Layer Active";	// 消息：一个图层被激活了，nValue=1，pValue=IVBF_3DPlotLayer*
const char VBF_MESSAGE_3DPLOT_LAYER_VISIBLE[]	= "Message: 3DPlot Layer Visible";	// 消息：一个图层的可见性改变了，nValue=bVisible，pValue=IVBF_3DPlotLayer*

// 定义命令ID号
const char VBF_COMMAND_3DPLOT_SAVEMESHINFO[]	= "Command: 3DPlot_SaveMeshInfo";	// 保存模型信息
const char VBF_COMMAND_3DPLOT_LAYERMANAGER[]	= "Command: 3DPlot_LayerManager";	// 图层管理窗口
const char VBF_COMMAND_3DPLOT_FILE_INPUT[]		= "Command: 3DPlot_FileInput";		// 从文件导入
const char VBF_COMMAND_3DPLOT_MODEL_UI[]		= "Command: 3DPlot_ModelUI";		// 模型选择UI
const char VBF_COMMAND_SHOWDIALOG_PLOTMANAGER[]	= "Command: Show Dialog PlotManager";	// 显示图标管理对话框


// 定义工具ID号
const char VBF_TOOL_MARK_SELECT[]					= "Tool: Select One Mark";						// 通过鼠标左键单击选择单个模型
const char VBF_TOOL_MARK_SELECT_QUICK[]				= "Tool: Select One Mark Quickly";				// 通过鼠标移动快速选择模型并显示模型信息
const char VBF_TOOL_MARK_SELECT_QUICK_AND_EDIT[]	= "Tool: Select One Mark Quickly And Edit";		// 通过鼠标移动快速选择模型并显示模型信息，再次单击该模型时进入编辑状态
const char VBF_TOOL_MARK_SELECT_RECT[]				= "Tool: Select By Rect";						// 通过鼠标在屏幕上的拉框矩形选择多个模型
const char VBF_TOOL_MARK_EDIT[]                     = "Tool: Plot State";                           // 编辑军标

//const char VBF_TOOL_MARK_EDIT_SUB_INPUT[]  =   "Tool: Edit Sub Input";
//const char VBF_TOOL_MARK_EDIT_SUB_ROTATE[] =   "Tool: Edit Sub Rotate";
//const char VBF_TOOL_MARK_EDIT_SUB_SCALE[]  =   "Tool: Edit Sub Scale";
//const char VBF_TOOL_MARK_EDIT_SUB_LOCAL[]  =   "Tool: Edit Sub Local";
//const char VBF_TOOL_MARK_EDIT_SUB_ATTR[]   =   "Tool: Edit Sub Attr";
//const char VBF_TOOL_MARK_EDIT_SUB_TRANSLATE[]  = "Tool: Edit Sub Translate";


class IVBF_MarkModelMesh;
class CVBF_Config;

//-----------------------------------------------------------
// 定义枚举：EVBF_PLOT_STATE
// 枚举描述：标图模块的子状态
//-----------------------------------------------------------
enum EVBF_PLOT_STATE
{
    VBF_PLOT_STATE_NONE = 0,
    VBF_PLOT_STATE_ATTR,        // 属性编辑
    VBF_PLOT_STATE_TRANSLATE,   // 平移
    VBF_PLOT_STATE_SCALE,       // 缩放
    VBF_PLOT_STATE_ROTATE,      // 旋转
    VBF_PLOT_STATE_EDITLOCAL,   // 局部编辑
    VBF_PLOT_STATE_INPUT        // 输入
};



//------------------------------------------------------------------
// 定义接口：IVBF_3DPlot
// 接口描述：3D军标的管理接口
//------------------------------------------------------------------
class IVBF_3DPlot : public CVBF_Referenced
{
public:
	virtual ~IVBF_3DPlot() {}

public:

    // 设置/获取标图模块的子状态，默认值为VBF_PLOT_STATE_NONE
    virtual void            SetState(EVBF_PLOT_STATE nState)=0;
    virtual EVBF_PLOT_STATE GetState()=0;

    // 获取模型编辑接口
    virtual IVBF_3DPlotEditor* GetEditor()=0;
	
	// 获取系统自动创建的缺省文档，该文档不允许删除
	virtual IVBF_3DPlotDoc* GetDefaultDoc()=0;
	virtual std::string     GetDefaultDocName()=0;

	// 添加/删除/查找一个标图文档
    virtual IVBF_3DPlotDoc* AddDoc(const std::string& strDocName,osg::IVBF_SGNodeGroup* pINodeParent=NULL)=0;
	virtual bool            DeleteDoc(const std::string& strDocName)=0;
	virtual bool            DeleteDoc(IVBF_3DPlotDoc* pIDoc)=0;
	virtual IVBF_3DPlotDoc* GetDoc(const std::string& strDocName)=0;

	// 激活一个标图文档
	virtual void               ActivateDoc(const std::string& strDocName)=0;   
	virtual IVBF_3DPlotDoc*    GetActiveDoc()=0;
	virtual const std::string& GetActiveDocName()=0;

	// 遍历标图文档
	virtual int             GetDocCount()=0;          
	virtual IVBF_3DPlotDoc* GetDoc(int nIndex)=0;

	// 获取所有标图文档
	virtual void GetAllDocs(std::vector<IVBF_3DPlotDoc*>& vDocs)=0;

    // 输入一个军标模型，通过人机交互的方式
    virtual void InputMark(unsigned int nType, const std::string& strCode="")=0;
    virtual IVBF_MarkInputHandler* GetInputHandler()=0; // 获取输入处理器

    // 通过指定类型，创建一个军标模型
    virtual IVBF_MarkModel* CreateMarkModel(const std::string& strMarkID, unsigned int nMarkType)=0;

    // 通过指定MarkStyle.xml配置文件中的类型编码，创建一个军标模型并读取模型信息
    virtual IVBF_MarkModel* CreateMarkModel(const std::string& strMarkID, const std::string& strCode)=0;

    // 通过指定xml节点，创建一个军标模型并读取模型信息
    virtual IVBF_MarkModel* CreateMarkModel(TiXmlElement* pElemMark)=0;

	// 创建一个军标属性
	virtual IVBF_MarkAttr* CreateMarkAttr(unsigned int nAttrType)=0;

    // 创建一个行为
    virtual IVBF_MarkAction* CreateMarkAction(const std::string& strActionType)=0;

    // 创建一个过程
    virtual IVBF_MarkProcess* CreateMarkProcess(const std::string& strProcessType)=0;

    virtual void ProcessSimulate()=0; // 过程模拟
    virtual void StatStartTime(double& dStartTime)=0;// 统计所有过程的起始时间


	// 给所有点状模型设置一个统一的自动缩放比
	virtual float GetPointMarkAutoScale()=0;

	// 给所有点状模型设置一个统一的缩放比系数
	virtual void  SetPointMarkScaleDelta(float fScaleDelta)=0;
	virtual float GetPointMarkScaleDelta()=0;

    // 工具性函数：根据模型指针，获取其所在的文档和图层名称
    virtual bool GetDocLayerNameOfMark(IVBF_MarkModel* pIMark, std::string& strDocName, std::string& strLayerName)=0;

    // 工具性函数：根据模型所在的文档、图层及模型ID号，获取模型指针
    virtual IVBF_MarkModel* FindMark(const std::string& strDocName, const std::string& strLayerName, const std::string& strMarkID)=0;
    // 在所有文档内查找模型
    virtual IVBF_MarkModel* FindMark(const std::string& strMarkID)=0;

	// 串行化，将标图信息写入指定的xml文件或节点
	virtual bool WriteToXML(const std::string& strFn)=0;
	virtual bool WriteToXML(TiXmlElement* pElemPlot)=0;

	// 串行化，从指定的xml文件或节点读取标图信息
	virtual bool ReadFromXML(const std::string& strFn)=0;
	virtual bool ReadFromXML(TiXmlElement* pElemPlot)=0;

	virtual void SetLineSmooth(bool bSmooth)=0;
	virtual void SetPolySmooth(bool bSmooth)=0;

    virtual void UpdateEciMatrix(double dEpochUTC,const Matrix& matJ20002Ecef)=0;

    // 执行脚本操作Plot
    virtual CVBF_Config ExecuteScript(const CVBF_Config&)=0;

	
};


#endif
