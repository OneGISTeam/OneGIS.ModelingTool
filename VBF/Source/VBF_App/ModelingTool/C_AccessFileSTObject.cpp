#include "C_AccessFileSTObject.h"

#include "VBF_Plot/IVBF_3DPlot.h"
#include "VBF_Plot/IVBF_3DPlotDoc.h"
#include "VBF_Plot/IVBF_3DPlotLayer.h"
#include "VBF_Plot/STObject/IVBF_MarkSTObjectPoint.h"

#include "VBF_Plot/ElecMag/IVBF_MarkModelLinkMeteor.h"
#include "VBF_Plot/ElecMag/IVBF_MarkModelLink2DDualWork.h"

#include "VBF_Aux/VBF_GLAux/VBF_ImageTextureUtils.h"

#include "VBF_Base/IVBF_System.h"
#include "VBF_Engine/VBF_SGDB/ReadFile"

C_AccessFileSTObject::C_AccessFileSTObject()
{
}


C_AccessFileSTObject::~C_AccessFileSTObject(void)
{
}

void C_AccessFileSTObject::load( const string& sFilePath )
{
	Clear();

	SetFileName(sFilePath);
	ReadFromXML(false);

	IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)m_pI3DMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
	if(pI3DPlot == NULL) return;

	IVBF_3DPlotDoc* pIPlotDoc = pI3DPlot->AddDoc("VBF_3DPLOTDOC_DEFAULT");
	if(pIPlotDoc == NULL) return;

	IVBF_3DPlotLayer* pILayer = pIPlotDoc->AddLayer("STObject", ECEF);
	if(pILayer == NULL) return;

	const string& strDataPath = this->GetPath();

	//利用读取的数据加载对象模型
	createMarkFromSTObject(this->Objects(), pI3DPlot, pILayer, strDataPath);

	createMarkFromSTObject(this->ObjectGroups(), pI3DPlot, pILayer, strDataPath);

}

void C_AccessFileSTObject::clear()
{
	CVBF_STObjectDoc::Clear();

	IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)m_pI3DMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
	if(pI3DPlot == NULL) return;

	IVBF_3DPlotDoc* pIPlotDoc = pI3DPlot->AddDoc("VBF_3DPLOTDOC_DEFAULT");
	if(pIPlotDoc == NULL) return;

	pIPlotDoc->DeleteLayer("STObject");
}

void C_AccessFileSTObject::createMarkHalfEdge( IVBF_3DPlot* pI3DPlot,IVBF_3DPlotLayer* pILayer, CVBF_STOHalfEdge* pHalfEdge,const std::string& strDataPath )
{

}

void C_AccessFileSTObject::createMarkFromSTObject( CVBF_STObjects& vObjects,IVBF_3DPlot* pI3DPlot,IVBF_3DPlotLayer* pILayer,const std::string& strDataPath )
{
	// 利用读取的数据加载模型
	int numObjs = vObjects.Size();

	for(int i=0; i<numObjs; i++)
	{
		CVBF_STObject* pObject = vObjects.GetAt(i);
		if(pObject==NULL) continue;

		createMarkFromSTObject(pObject,pI3DPlot,pILayer,strDataPath);
	}
}

void C_AccessFileSTObject::createMarkFromSTObject( CVBF_STObjectGroups& vGroups,IVBF_3DPlot* pI3DPlot,IVBF_3DPlotLayer* pILayer,const std::string& strDataPath )
{

}

void C_AccessFileSTObject::createMarkFromSTObject(CVBF_STObject* pObject)
{

}

void C_AccessFileSTObject::createMarkFromSTObject( CVBF_STObject* pObject,IVBF_3DPlot* pI3DPlot,IVBF_3DPlotLayer* pILayer,const std::string& strDataPath )
{
	if(pObject==NULL) return;

	const std::string& strObjID = pObject->GetID();

	if( pILayer->GetMark(strObjID) ) return; // 已经存在

	const std::string& strObjType = pObject->GetType();

	string strTypeLevel1 = strObjType.substr(0,1);
	string strTypeLevel2 = strObjType.substr(0,3);
	string strTypeLevel3 = strObjType.substr(0,5);

	if(strObjType=="Satellite") return ;

	// strObjType=="70000001"
	if(strTypeLevel1=="7" || strTypeLevel1=="5" ||
		strObjType=="Building" || strObjType=="Tree")
	{
		IVBF_MarkSTObjectPoint* pIMark = (IVBF_MarkSTObjectPoint*)pI3DPlot->CreateMarkModel(strObjID, VBF_MARK_STOBJECT_POINT);
		if(NULL==pIMark) return; // 创建失败，不支持该类型，可能缺少插件

		pIMark->SetDataPath(strDataPath);

		if(strObjType=="Tree")
		{
			//            pIMark->SetRenderHint_Transparent();
			//pIMark->SetRenderOrder_Transparent(INT_MAX);
			pIMark->EnableShowAttr(false);
			pIMark->SetDistMax(1500);
		}
		else if(strObjType=="Building")
		{
			pIMark->EnableAutoScale(false);
			pIMark->EnableShowAttr(false);
			pIMark->SetDistMax(10000);
		}
		else
		{
			pIMark->SetDistMax(5e8);
			pIMark->EnableAutoScale(true);
		}

		pIMark->Init(pObject);

		pIMark->SetDistMin(0);

		pIMark->EnableLight(true);  // 开启光照

		pIMark->DoAction("QianLuoXuanJiang", "RotateAxis", true);
		pIMark->DoAction("HouLuoXuanJiang", "RotateAxis", true);

		// 添加到图层
		pILayer->AddMark(pIMark);
	}
	else if(strTypeLevel3=="30201" || strTypeLevel3=="10101")
	{
		IVBF_MarkSTObjectPoint* pIMark = (IVBF_MarkSTObjectPoint*)pI3DPlot->CreateMarkModel(strObjID, VBF_MARK_STOBJECT_POINT);
		if(NULL==pIMark) return; // 创建失败，不支持该类型，可能缺少插件

		pIMark->SetDataPath(strDataPath);
		pIMark->Init(pObject);
		pIMark->EnableLight(true);  // 开启光照
		pIMark->EnableAutoScale(false);
		pIMark->SetScale(1.0,1.0,1.0);

		// 添加到图层
		pILayer->AddMark(pIMark);

	}
	else // 10200000(境界)等
	{

		IVBF_MarkSTObjectPoint* pIMark = (IVBF_MarkSTObjectPoint*)pI3DPlot->CreateMarkModel(strObjID, VBF_MARK_STOBJECT_POINT);
		if(NULL==pIMark) return; // 创建失败，不支持该类型，可能缺少插件

		pIMark->SetDataPath(strDataPath);
		pIMark->Init(pObject);
		pIMark->EnableLight(true);  // 开启光照
		pIMark->EnableAutoScale(false);
		pIMark->SetScale(1.0,1.0,1.0);

		// 添加到图层
		pILayer->AddMark(pIMark);

	}
}

const std::string& C_AccessFileSTObject::GetPath()
{
	if(CVBF_STObjectDoc::GetPath().empty() ) SetPath( VBF_GetSystem()->GetDataPath() );
	return CVBF_STObjectDoc::GetPath();
}
