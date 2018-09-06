#pragma once
#include <string>
#include "VBF_Common/VBF_STObject/VBF_STObjectDoc.h"
#include "VBF_MainCtrl/IVBF_3DMainCtrl.h"

class IVBF_3DPlot;
class IVBF_3DPlotLayer;
class CVBF_STOHalfEdge;
class CVBF_STObject;

using namespace std;

class C_AccessFileSTObject: public CVBF_STObjectDoc
{
public:
	C_AccessFileSTObject();
	~C_AccessFileSTObject(void);

	void set3DMainCtrl(IVBF_3DMainCtrl* p3dMainCtrl) {m_pI3DMainCtrl = p3dMainCtrl;}

	void load(const string& sFilePath);

	void clear();

	void createMarkHalfEdge(IVBF_3DPlot* pI3DPlot,IVBF_3DPlotLayer* pILayer, CVBF_STOHalfEdge* pHalfEdge,const std::string& strDataPath);
	void createMarkFromSTObject(CVBF_STObjects& vObjects,IVBF_3DPlot* pI3DPlot,IVBF_3DPlotLayer* pILayer,const std::string& strDataPath);
	void createMarkFromSTObject(CVBF_STObject* pObject,IVBF_3DPlot* pI3DPlot,IVBF_3DPlotLayer* pILayer,const std::string& strDataPath);
	void createMarkFromSTObject(CVBF_STObjectGroups& vGroups,IVBF_3DPlot* pI3DPlot,IVBF_3DPlotLayer* pILayer,const std::string& strDataPath);
	void createMarkFromSTObject(CVBF_STObject* pObject);

private:
	const std::string& GetPath();

private:
	IVBF_3DMainCtrl* m_pI3DMainCtrl;
};

