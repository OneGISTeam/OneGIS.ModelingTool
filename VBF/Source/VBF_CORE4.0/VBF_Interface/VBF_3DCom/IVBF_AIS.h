//***************************************************************************************
// FileName：IVBF_AIS.h
// Function：AIS
// Author:   
// Date:     2018-3-25
//***************************************************************************************
#ifndef __IVBF_AIS_H__
#define __IVBF_AIS_H__

// 定义该组件的ID号
const char VBF_COMPONENT_AIS[]			= "Component: AIS";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_AIS[]			= "三维应用层";

// 定义命令ID号

#include <VBF_Base/VBF_Referenced.h>

class IVBF_AIS// : public CVBF_Referenced
{
public: 	
	virtual ~IVBF_AIS() {}

};

#endif





















