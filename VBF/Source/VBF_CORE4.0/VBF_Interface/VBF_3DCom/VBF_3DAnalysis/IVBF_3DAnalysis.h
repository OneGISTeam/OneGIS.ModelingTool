//***************************************************************************************
// FileName��IVBF_3DAnalysis.h
// Function��3D�����ӿ�
// Author:   ��Ө
// Date:     2012-03-22
//***************************************************************************************

#ifndef __IVBF_3DANALYSIS_H__
#define __IVBF_3DANALYSIS_H__


#include <Types/VBF_3DStyles.h>
#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>
#include <VBF_Base/VBF_Referenced.h>
#include <vector>
#include <Types/Vec3d>


// ����������ID��
const char VBF_COMPONENT_3DANALYSIS[]				= "Component: 3DAnalysis";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DANALYSIS[]				= "��ά�����ӿ�";	

// ������ϢID��
const char VBF_MESSAGE_ANALYSIS_GEOCOORD[]	        = "Message: Analysis GeoCoord";			// void* pValue: osg::Vec3d*
const char VBF_MESSAGE_ANALYSIS_DIST[]				= "Message: Analysis Dist";				// void* pValue: double*
const char VBF_MESSAGE_ANALYSIS_DISTPOINTGEO[]		= "Message: Analysis Dist PointGeo";	// void* vector<osg::Vec3d>*
const char VBF_MESSAGE_ANALYSIS_FLOOD_DATA[]		= "Message: Analysis Flood data";	    // void* pValue: SFloodData*
const char VBF_MESSAGE_ANALYSIS_FLOOD_WIDGET[]		= "Message: Analysis Flood Widget";	    // void* pValue: bool*
const char VBF_MESSAGE_ANALYSIS_FILLCUT_DATA[]		= "Message: Analysis FillCut data";	    // void* pValue: SFillCutData*
const char VBF_MESSAGE_ANALYSIS_FILLCUT_WIDGET[]	= "Message: Analysis FillCut Widget";	// void* pValue: bool*

// ��������������ֵ. void* pValue: 
const char VBF_MESSAGE_ANALYSIS_REQUEST_ASPECT[]	= "Message: Analysis Request Aspect";		// �������󵥸��������ֵ��pValue: 
const char VBF_MESSAGE_ANALYSIS_REQUEST_SLOPE1P[]	= "Message: Analysis Request Slope 1P";		// �������󵥸�����¶�ֵ��

// ���幤��ID��
const char VBF_TOOL_3DANALYSIS_GEOCOORD[]			= "Tool: 3DAnalysis GeoCoord";				// ��ʾ��������
const char VBF_TOOL_3DANALYSIS_DIST[]				= "Tool: 3DAnalysis Dist";					// �����������֮��Ĵ���߾���
const char VBF_TOOL_3DANALYSIS_DIST_RADIAL[]		= "Tool: 3DAnalysis Dist Radial";			// �����Ϊ���ģ���������õ�֮��Ĵ���߾���
const char VBF_TOOL_3DANALYSIS_AREA[]				= "Tool: 3DAnalysis Area";					// �������������
const char VBF_TOOL_3DANALYSIS_SLOPE[]				= "Tool: 3DAnalysis Slope";					// �����ڵ��¶ȷ���
const char VBF_TOOL_3DANALYSIS_HEIGHTCONTRAST[]		= "Tool: 3DAnalysis Height Contrast";		// �߲�������Ը߳�
const char VBF_TOOL_3DANALYSIS_AZIMUTH[]		    = "Tool: 3DAnalysis Azimuth";				// ��λ��
const char VBF_TOOL_3DANALYSIS_ASPECT[]				= "Tool: 3DAnalysis Aspect";				// �����������
const char VBF_TOOL_3DANALYSIS_SLOPE1P[]			= "Tool: 3DAnalysis Slope 1P";				// ��������¶�
const char VBF_TOOL_3DANALYSIS_HEIGHT[]				= "Tool: 3DAnalysis Height";				// ������ĸ߳�ֵ
const char VBF_TOOL_3DANALYSIS_SECTION[]			= "Tool: 3DAnalysis Section";				// ����֮����������
const char VBF_TOOL_3DANALYSIS_LOS_LINEAR[]		    = "Tool: 3DAnalysis LightOfSight Linear";	// ������ͨ�ӷ���
const char VBF_TOOL_3DANALYSIS_LOS_RADIAL[]		    = "Tool: 3DAnalysis LightOfSight Radial";   // ���������ڵ�ͨ�ӷ���
const char VBF_TOOL_3DANALYSIS_VISIBLE[]		    = "Tool: 3DAnalysis Visible";				// �����ڵ�ͨ�ӷ���
const char VBF_TOOL_3DANALYSIS_SPHERE_VISIBLE[]		= "Tool: 3DAnalysis Sphere Visible";		// ��������ͨ�ӷ���
const char VBF_TOOL_3DANALYSIS_MEASUREHEIGHT[]		= "Tool: 3DAnalysis MeasureHeight";			// ���߷���
const char VBF_TOOL_3DANALYSIS_FLOOD[]				= "Tool: 3DAnalysis Flood";					// ��û����
const char VBF_TOOL_3DANALYSIS_FILLCUT[]		    = "Tool: 3DAnalysis FillCut";			    // ���ڷ�����
const char VBF_TOOL_3DANALYSIS_BUILDINGSLINES[]		= "Tool: 3DAnalysis Buildings Lines";		// ����Ⱥ��Ե�ͨ��
const char VBF_TOOL_3DANALYSIS_GRADIENT[]		    = "Tool: 3DAnalysis Gradient";		        // �¶��������
const char VBF_TOOL_3DANALYSIS_BUIDINGS_REGION[]	= "Tool: 3DAnalysis Buildings Region";		// �������ͨ�ӽ���Ⱥ
const char VBF_TOOL_3DANALYSIS_BUFFER[]	            = "Tool: 3DAnalysis BUFFER";		        // ����������
const char VBF_TOOL_3DANALYSIS_INTERSECTION[]	    = "Tool: 3DAnalysis INTERSECTION";		    // ������ӷ���

class IVBF_3DAnalysis : public CVBF_Referenced
{
public:
	virtual ~IVBF_3DAnalysis() {}

	// ��ȡ�����֧�ֵ�������ά��������
	virtual void GetAllTools(std::vector<IVBF_3DAnalysisTool*>& vTools)=0;

	// ��ȡָ������ά�������ߣ�����szToolIDΪVBF_TOOL_3DANALYSIS_GEOCOORD��
	virtual IVBF_3DAnalysisTool* GetTool(const char* szToolID)=0;
};


#endif
