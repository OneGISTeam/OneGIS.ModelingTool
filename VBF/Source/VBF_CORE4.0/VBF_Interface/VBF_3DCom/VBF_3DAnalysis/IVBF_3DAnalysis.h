//***************************************************************************************
// FileName：IVBF_3DAnalysis.h
// Function：3D分析接口
// Author:   杜莹
// Date:     2012-03-22
//***************************************************************************************

#ifndef __IVBF_3DANALYSIS_H__
#define __IVBF_3DANALYSIS_H__


#include <Types/VBF_3DStyles.h>
#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>
#include <VBF_Base/VBF_Referenced.h>
#include <vector>
#include <Types/Vec3d>


// 定义该组件的ID号
const char VBF_COMPONENT_3DANALYSIS[]				= "Component: 3DAnalysis";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DANALYSIS[]				= "三维分析接口";	

// 定义消息ID号
const char VBF_MESSAGE_ANALYSIS_GEOCOORD[]	        = "Message: Analysis GeoCoord";			// void* pValue: osg::Vec3d*
const char VBF_MESSAGE_ANALYSIS_DIST[]				= "Message: Analysis Dist";				// void* pValue: double*
const char VBF_MESSAGE_ANALYSIS_DISTPOINTGEO[]		= "Message: Analysis Dist PointGeo";	// void* vector<osg::Vec3d>*
const char VBF_MESSAGE_ANALYSIS_FLOOD_DATA[]		= "Message: Analysis Flood data";	    // void* pValue: SFloodData*
const char VBF_MESSAGE_ANALYSIS_FLOOD_WIDGET[]		= "Message: Analysis Flood Widget";	    // void* pValue: bool*
const char VBF_MESSAGE_ANALYSIS_FILLCUT_DATA[]		= "Message: Analysis FillCut data";	    // void* pValue: SFillCutData*
const char VBF_MESSAGE_ANALYSIS_FILLCUT_WIDGET[]	= "Message: Analysis FillCut Widget";	// void* pValue: bool*

// 对外请求分析结果值. void* pValue: 
const char VBF_MESSAGE_ANALYSIS_REQUEST_ASPECT[]	= "Message: Analysis Request Aspect";		// 对外请求单个点的坡向值，pValue: 
const char VBF_MESSAGE_ANALYSIS_REQUEST_SLOPE1P[]	= "Message: Analysis Request Slope 1P";		// 对外请求单个点的坡度值，

// 定义工具ID号
const char VBF_TOOL_3DANALYSIS_GEOCOORD[]			= "Tool: 3DAnalysis GeoCoord";				// 显示地理坐标
const char VBF_TOOL_3DANALYSIS_DIST[]				= "Tool: 3DAnalysis Dist";					// 计算连续多点之间的大地线距离
const char VBF_TOOL_3DANALYSIS_DIST_RADIAL[]		= "Tool: 3DAnalysis Dist Radial";			// 以起点为中心，计算多点与该点之间的大地线距离
const char VBF_TOOL_3DANALYSIS_AREA[]				= "Tool: 3DAnalysis Area";					// 计算椭球面面积
const char VBF_TOOL_3DANALYSIS_SLOPE[]				= "Tool: 3DAnalysis Slope";					// 区域内的坡度分析
const char VBF_TOOL_3DANALYSIS_HEIGHTCONTRAST[]		= "Tool: 3DAnalysis Height Contrast";		// 高差，两点间相对高程
const char VBF_TOOL_3DANALYSIS_AZIMUTH[]		    = "Tool: 3DAnalysis Azimuth";				// 方位角
const char VBF_TOOL_3DANALYSIS_ASPECT[]				= "Tool: 3DAnalysis Aspect";				// 单个点的坡向
const char VBF_TOOL_3DANALYSIS_SLOPE1P[]			= "Tool: 3DAnalysis Slope 1P";				// 单个点的坡度
const char VBF_TOOL_3DANALYSIS_HEIGHT[]				= "Tool: 3DAnalysis Height";				// 单个点的高程值
const char VBF_TOOL_3DANALYSIS_SECTION[]			= "Tool: 3DAnalysis Section";				// 两点之间的剖面分析
const char VBF_TOOL_3DANALYSIS_LOS_LINEAR[]		    = "Tool: 3DAnalysis LightOfSight Linear";	// 两点间的通视分析
const char VBF_TOOL_3DANALYSIS_LOS_RADIAL[]		    = "Tool: 3DAnalysis LightOfSight Radial";   // 环形区域内的通视分析
const char VBF_TOOL_3DANALYSIS_VISIBLE[]		    = "Tool: 3DAnalysis Visible";				// 区域内的通视分析
const char VBF_TOOL_3DANALYSIS_SPHERE_VISIBLE[]		= "Tool: 3DAnalysis Sphere Visible";		// 球面包络的通视分析
const char VBF_TOOL_3DANALYSIS_MEASUREHEIGHT[]		= "Tool: 3DAnalysis MeasureHeight";			// 量高分析
const char VBF_TOOL_3DANALYSIS_FLOOD[]				= "Tool: 3DAnalysis Flood";					// 淹没分析
const char VBF_TOOL_3DANALYSIS_FILLCUT[]		    = "Tool: 3DAnalysis FillCut";			    // 填挖方分析
const char VBF_TOOL_3DANALYSIS_BUILDINGSLINES[]		= "Tool: 3DAnalysis Buildings Lines";		// 建筑群点对点通视
const char VBF_TOOL_3DANALYSIS_GRADIENT[]		    = "Tool: 3DAnalysis Gradient";		        // 坡度坡向分析
const char VBF_TOOL_3DANALYSIS_BUIDINGS_REGION[]	= "Tool: 3DAnalysis Buildings Region";		// 点对区域通视建筑群
const char VBF_TOOL_3DANALYSIS_BUFFER[]	            = "Tool: 3DAnalysis BUFFER";		        // 缓冲区分析
const char VBF_TOOL_3DANALYSIS_INTERSECTION[]	    = "Tool: 3DAnalysis INTERSECTION";		    // 区域叠加分析

class IVBF_3DAnalysis : public CVBF_Referenced
{
public:
	virtual ~IVBF_3DAnalysis() {}

	// 获取该组件支持的所有三维分析工具
	virtual void GetAllTools(std::vector<IVBF_3DAnalysisTool*>& vTools)=0;

	// 获取指定的三维分析工具，参数szToolID为VBF_TOOL_3DANALYSIS_GEOCOORD等
	virtual IVBF_3DAnalysisTool* GetTool(const char* szToolID)=0;
};


#endif
