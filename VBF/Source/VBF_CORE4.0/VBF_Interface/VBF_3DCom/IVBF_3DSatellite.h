//*******************************************************************
// FileName：IVBF_3DSatellite.h
// Function：海量卫星管理接口
// Author:   杜莹
// Date:     2013-12-31
//*******************************************************************

#ifndef __IVBF_3DSATELLITE_H__
#define __IVBF_3DSATELLITE_H__

#include <string>
#include <Types/Vec4f>
#include <VBF_Base/VBF_Referenced.h>


class IVBF_MarkModelSatellite;

// 定义该组件的ID号
const char VBF_COMPONENT_3DSATELLITE[]	= "Component: 3DSatellite";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DSATELLITE[]	= "海量卫星管理";	

// 定义工具ID号
const char VBF_TOOL_SELECT_SATELLITE[]	= "Tool: Select Satellite";	 // 选择卫星


class IVBF_3DSatellite : public CVBF_Referenced
{
public:	
	virtual ~IVBF_3DSatellite() {}

	// 从xml配置文件中加载卫星，同时设置卫星的颜色、大小、纹理文件（可以为空）
	// 如果同时设置了颜色与纹理，二者使用相乘方式进行混合
	virtual bool LoadData(const std::string& strFileName, const osg::Vec4f& color, float fSize, const std::string& strTexFileName="")=0;

	// 清除已经加载的卫星
	virtual void Clear()=0;

    // 获取当前选中的卫星模型
    virtual IVBF_MarkModelSatellite* GetSatelliteModel()=0;
};

#endif 
