//***************************************************************************************
// FileName： IVBF_3DPlotDoc.h
// Function： 3D标图文档接口，负责管理标图的图层
// Author:    杜莹
// Date:      2013-07-04
//***************************************************************************************

#ifndef __IVBF_3DPLOT_DOC_H__
#define __IVBF_3DPLOT_DOC_H__

#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Plot/IVBF_3DPlotLayer.h>
#include <VBF_Plot/IVBF_MarkModel.h>
#include <string>
#include <vector>
#include <VBF_Common/VBF_Math/IVBF_SrsDefine.h>

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DPLOTDOC[]	= "三维标图文档接口";	


//------------------------------------------------------------------
// 定义接口：IVBF_3DPlotDoc
// 接口描述：3D标图文档的管理接口
//------------------------------------------------------------------
class IVBF_3DPlotDoc : public osg::CVBF_Object
{
public:
	virtual ~IVBF_3DPlotDoc() {}

public:

	// 获取标图文档的名称
	virtual const std::string GetName()=0;

	// 删除一个或一组军标
	virtual void  DeleteMark(const std::string& strLayerName, const char* szMarkID)=0;
	virtual void  DeleteMark(const std::string& strLayerName, std::vector<std::string>& vsMarkID)=0;

	// 通过ID号，在所有图层上查找军标，返回第一个找到的军标
	virtual IVBF_MarkModel* GetMark(const std::string& strMarkID)=0;
	
	// 清除当前选择的军标
	virtual void  ClearSelected()=0;
	
	// 图层操作，strLayerName: 图层名
    virtual IVBF_3DPlotLayer*  AddLayer(const std::string& strLayerName,EVBF_SRS srs = ECEF)=0;	// 添加图层
	virtual IVBF_3DPlotLayer*  GetLayer(const std::string& strLayerName)=0;	// 查找图层
	virtual IVBF_3DPlotLayer*  GetActiveLayer()=0;

	virtual void  ClearAllLayers()=0;
	virtual void  DeleteLayer(const std::string& strLayerName)=0;			// 删除图层
	virtual void  ActivateLayer(const std::string& strLayerName)=0;          // 激活图层

	virtual int   GetLayerCount()=0; 
	virtual void  GetAllLayers(std::vector<IVBF_3DPlotLayer*>& vLayers)=0;		// 获取所有图层
	virtual void  GetAllLayerNames(std::vector<std::string>& vLayerNames)=0;	// 获取所有图层名

	virtual void AddMarkToLayer(const std::string& strLayerName, IVBF_MarkModel* pMarkModel)=0;

	// 文档是否激活
	virtual bool IsActive()=0;

    // 一个文档具有一个标图环境
    virtual IVBF_MarkContext* GetContext()=0;
};


#endif
