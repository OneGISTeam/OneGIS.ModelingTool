//***************************************************************************************
// FileName�� IVBF_3DPlotDoc.h
// Function�� 3D��ͼ�ĵ��ӿڣ���������ͼ��ͼ��
// Author:    ��Ө
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

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DPLOTDOC[]	= "��ά��ͼ�ĵ��ӿ�";	


//------------------------------------------------------------------
// ����ӿڣ�IVBF_3DPlotDoc
// �ӿ�������3D��ͼ�ĵ��Ĺ���ӿ�
//------------------------------------------------------------------
class IVBF_3DPlotDoc : public osg::CVBF_Object
{
public:
	virtual ~IVBF_3DPlotDoc() {}

public:

	// ��ȡ��ͼ�ĵ�������
	virtual const std::string GetName()=0;

	// ɾ��һ����һ�����
	virtual void  DeleteMark(const std::string& strLayerName, const char* szMarkID)=0;
	virtual void  DeleteMark(const std::string& strLayerName, std::vector<std::string>& vsMarkID)=0;

	// ͨ��ID�ţ�������ͼ���ϲ��Ҿ��꣬���ص�һ���ҵ��ľ���
	virtual IVBF_MarkModel* GetMark(const std::string& strMarkID)=0;
	
	// �����ǰѡ��ľ���
	virtual void  ClearSelected()=0;
	
	// ͼ�������strLayerName: ͼ����
    virtual IVBF_3DPlotLayer*  AddLayer(const std::string& strLayerName,EVBF_SRS srs = ECEF)=0;	// ���ͼ��
	virtual IVBF_3DPlotLayer*  GetLayer(const std::string& strLayerName)=0;	// ����ͼ��
	virtual IVBF_3DPlotLayer*  GetActiveLayer()=0;

	virtual void  ClearAllLayers()=0;
	virtual void  DeleteLayer(const std::string& strLayerName)=0;			// ɾ��ͼ��
	virtual void  ActivateLayer(const std::string& strLayerName)=0;          // ����ͼ��

	virtual int   GetLayerCount()=0; 
	virtual void  GetAllLayers(std::vector<IVBF_3DPlotLayer*>& vLayers)=0;		// ��ȡ����ͼ��
	virtual void  GetAllLayerNames(std::vector<std::string>& vLayerNames)=0;	// ��ȡ����ͼ����

	virtual void AddMarkToLayer(const std::string& strLayerName, IVBF_MarkModel* pMarkModel)=0;

	// �ĵ��Ƿ񼤻�
	virtual bool IsActive()=0;

    // һ���ĵ�����һ����ͼ����
    virtual IVBF_MarkContext* GetContext()=0;
};


#endif
