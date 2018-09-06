//***************************************************************************************
// FileName：IVBF_3DPerform.h
// Function：三维演播控制接口，主要用于
// Author:   
// Date:     2012-4-16
//***************************************************************************************
#ifndef __IVBF_3DPERFORM_H__
#define __IVBF_3DPERFORM_H__

// 定义该组件的ID号
const char VBF_COMPONENT_3DPERFORM[]			= "Component: 3DPerform";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DPERFORM[]			= "三维演播控制";

// 定义命令ID号
const char VBF_COMMAND_3DPERFORM_NEXT[]			= "Command: 3DPerform Next";			// 下一个
const char VBF_COMMAND_3DPERFORM_PREV[]			= "Command: 3DPerform Prev";			// 上一个
const char VBF_COMMAND_3DPERFORM_PLAY[]			= "Command: 3DPerform Play";			// 播放
const char VBF_COMMAND_3DPERFORM_STOP[]		    = "Command: 3DPerform Stop";			// 停止


class CVBF_Config;
class IVBF_3DPerform
{
public: 	
	virtual ~IVBF_3DPerform() {}

public:
	//获取页数
	virtual int GetPageCount()=0;

	//获取某页的名称
	virtual	char* GetPageName(int nID)=0;
	
	//跳至某页
	virtual	void JumpToPage(int nPage)=0;

    virtual	bool SetConfigFileName(const char* szFn)=0;

    // 执行脚本操作
    virtual void ExecuteScript(const CVBF_Config&)=0;

    virtual void PPTControlSwitch()=0;

};

#endif





















