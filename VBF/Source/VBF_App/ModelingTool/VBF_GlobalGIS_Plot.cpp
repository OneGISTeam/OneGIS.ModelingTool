//#include "stdafx.h"
#include "VBF_FunctionRegister.h"
#include "VBF_GlobalGIS_Plot.h"

#include <VBF_Display/VBF_Viewer/VBF_EventHandlerStats.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>

#include <VBF_MainCtrl/IVBF_MainCtrl.h>
#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>

#include <VBF_Plot/IVBF_3DPlot.h>
#include <VBF_Plot/IVBF_3DPlotDoc.h>
#include <VBF_Plot/IVBF_3DPlotLayer.h>
#include <VBF_Plot/Common/IVBF_MarkModelMesh.h>
#include <VBF_Plot/Common/IVBF_MarkModelRaster.h>
#include <VBF_Plot/Common/IVBF_MarkAttrTrailLine.h>


IVBF_3DPlot* g_pI3DPlot      = NULL;         // 3D标图接口
std::string  g_strDocName    = "VBF_3DPLOTDOC_DEFAULT";    // 各类模型共用的标图文档
float        s_fMeshScale    = 100.0f;      // Mesh模型的放大倍数
osg::Vec3d   g_vGeo          = osg::Vec3d(113.567710, 34.810054, 150.0); // 模型的定位点（地理坐标）




// 各类属性的可见性
bool s_bVisibleMark				= true;
bool s_bVisibleLabel			= true;
bool s_bVisibleHintLine			= true;
bool s_bVisibleTrailLine		= true;
bool s_bVisibleTrailLinePoint	= false;
bool s_bVisibleTrailStrip		= true;
bool s_bVisiblePowerMap			= true;
bool s_bActionEnabled			= true;
bool s_bVisibleIntersect		= false;


// 图层和模型的可见距离
float s_fLayerDistMax			= FLT_MAX;
float s_fMarkDistMax			= FLT_MAX;


// 更新所有模型的可见性
void ToggleMark(IVBF_MainCtrl* pIMainCtrl, bool bVisible)
{
	IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
	if(NULL==pI3DPlot) return;

	IVBF_3DPlotDoc* pIDoc = pI3DPlot->GetActiveDoc();
	if(NULL==pIDoc) return;
	
	std::vector<IVBF_3DPlotLayer*> vLayers;
	pIDoc->GetAllLayers(vLayers);

	for(int i=0; i<(int)vLayers.size(); i++)
	{
		IVBF_3DPlotLayer* pILayer = vLayers[i];
		if(NULL==pILayer) continue;

		std::vector<IVBF_MarkModel*> vMarks;
		pILayer->GetAllMarks(vMarks);

		for(int k=0; k<(int)vMarks.size(); k++)
		{
			IVBF_MarkModel* pIMark = vMarks[k];
			if(pIMark) pIMark->SetVisible(bVisible);
		}
	}
}

// 更新所有模型某个属性的可见性
void SetAttrVisible(IVBF_MainCtrl* pIMainCtrl, DWORD dwAttrType, bool bVisible)
{
	IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
	if(NULL==pI3DPlot) return;

	IVBF_3DPlotDoc* pIDoc = pI3DPlot->GetActiveDoc();
	if(NULL==pIDoc) return;
	
	std::vector<IVBF_3DPlotLayer*> vLayers;
	pIDoc->GetAllLayers(vLayers);

	for(int i=0; i<(int)vLayers.size(); i++)
	{
		IVBF_3DPlotLayer* pILayer = vLayers[i];
		if(NULL==pILayer) continue;

		std::vector<IVBF_MarkModel*> vMarks;
		pILayer->GetAllMarks(vMarks);

		for(int k=0; k<(int)vMarks.size(); k++)
		{
			IVBF_MarkModel* pIMark = vMarks[k];
			if(NULL==pIMark) continue;

			IVBF_MarkAttr* pIAttr = pIMark->LookupMarkAttr(dwAttrType);
			if(pIAttr) pIAttr->SetVisible(bVisible);
		}
	}
}

// 更新所有模型某个属性的样式：轨迹线
void TestPlot_UpdateAttrTrailLine(IVBF_MainCtrl* pIMainCtrl)
{
	static int s_nCount = 0;
	s_nCount++;

	IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
	if(NULL==pI3DPlot) return;

	IVBF_3DPlotDoc* pIDoc = pI3DPlot->GetActiveDoc();
	if(NULL==pIDoc) return;

	std::vector<IVBF_3DPlotLayer*> vLayers;
	pIDoc->GetAllLayers(vLayers);

	for(int i=0; i<(int)vLayers.size(); i++)
	{
		IVBF_3DPlotLayer* pILayer = vLayers[i];
		if(NULL==pILayer) continue;

		std::vector<IVBF_MarkModel*> vMarks;
		pILayer->GetAllMarks(vMarks);

		for(int k=0; k<(int)vMarks.size(); k++)
		{
			IVBF_MarkModel* pIMark = vMarks[k];
			if(NULL==pIMark) continue;

			IVBF_MarkAttrTrailLine* pIAttr = dynamic_cast<IVBF_MarkAttrTrailLine*>(pIMark->LookupMarkAttr(VBF_MARK_ATTR_TRAILLINE));
			if(NULL==pIAttr) continue;

            pIAttr->SetVisible(s_bVisibleTrailLine);
            pIAttr->SetNumPointsVisible(s_nCount*10);

            // 线段样式
            VBF_LINESTYLE style;
            style.color  = osg::Vec4f(1.0, 1.0, 0.0, 1.0f);
            style.fWidth = 4.0f;

            VBF_POINTSTYLE stylePoint;
            stylePoint.color = osg::Vec4f(0, 1, 1, 1.0f);
            stylePoint.fSize = 6.f;

    //      pIAttr->EnableFade( !pIAttr->IsFadeEnabled() );
    //      pIAttr->SetLineStyle(style);
    //      pIAttr->SetPointStyle(stylePoint);
        }
    }
}


// 开关模型
void TestPlot_ToggleMark(IVBF_MainCtrl* pIMainCtrl)
{
	s_bVisibleMark = !s_bVisibleMark;
	ToggleMark(pIMainCtrl, s_bVisibleMark);
}

// 开关模型属性：标签
void TestPlot_ToggleAttrLabel(IVBF_MainCtrl* pIMainCtrl)
{
	s_bVisibleLabel = !s_bVisibleLabel;
    SetAttrVisible(pIMainCtrl, VBF_MARK_ATTR_LABEL, s_bVisibleLabel);
}

// 开关模型属性：威力图
void TestPlot_ToggleAttrPowerMap(IVBF_MainCtrl* pIMainCtrl)
{
    s_bVisiblePowerMap = !s_bVisiblePowerMap;
    SetAttrVisible(pIMainCtrl, VBF_MARK_ATTR_POWERMAP, s_bVisiblePowerMap);
}

// 开关模型属性：高度线
void TestPlot_ToggleAttrHintLine(IVBF_MainCtrl* pIMainCtrl)
{
	s_bVisibleHintLine = !s_bVisibleHintLine;
    SetAttrVisible(pIMainCtrl, VBF_MARK_ATTR_HINTLINE, s_bVisibleHintLine);
}

// 开关模型属性：轨迹线
void TestPlot_ToggleAttrTrailLine(IVBF_MainCtrl* pIMainCtrl)
{
	s_bVisibleTrailLine = !s_bVisibleTrailLine;
    SetAttrVisible(pIMainCtrl, VBF_MARK_ATTR_TRAILLINE, s_bVisibleTrailLine);
}

// 开关模型属性：轨迹线上的点
void TestPlot_ToggleAttrTrailLinePoint(IVBF_MainCtrl* pIMainCtrl)
{
	s_bVisibleTrailLinePoint = !s_bVisibleTrailLinePoint;

	IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
	if(NULL==pI3DPlot) return;

	IVBF_3DPlotDoc* pIDoc = pI3DPlot->GetActiveDoc();
	if(NULL==pIDoc) return;

	std::vector<IVBF_3DPlotLayer*> vLayers;
	pIDoc->GetAllLayers(vLayers);

	for(int i=0; i<(int)vLayers.size(); i++)
	{
		IVBF_3DPlotLayer* pILayer = vLayers[i];
		if(NULL==pILayer) continue;

		std::vector<IVBF_MarkModel*> vMarks;
		pILayer->GetAllMarks(vMarks);

		for(int k=0; k<(int)vMarks.size(); k++)
		{
			IVBF_MarkModel* pIMark = vMarks[k];
			if(NULL==pIMark) continue;

			IVBF_MarkAttrTrailLine* pIAttr = dynamic_cast<IVBF_MarkAttrTrailLine*>(pIMark->LookupMarkAttr(VBF_MARK_ATTR_TRAILLINE));
			if(pIAttr) pIAttr->SetRenderStyle(s_bVisibleTrailLinePoint? VBF_TRAIL_STYLE_COMPOSITE : VBF_TRAIL_STYLE_LINE);
		}
	}
}

// 开关模型属性：飞机尾迹
void TestPlot_ToggleAttrTrailStrip(IVBF_MainCtrl* pIMainCtrl)
{
	s_bVisibleTrailStrip = !s_bVisibleTrailStrip;
    SetAttrVisible(pIMainCtrl, VBF_MARK_ATTR_TRAILSTRIP, s_bVisibleTrailStrip);
}

// 测试模型单选
void TestPlot_SelectMark(IVBF_MainCtrl* pIMainCtrl)
{
    pIMainCtrl->SelectTool(VBF_TOOL_MARK_SELECT);
}

// 测试模型多选
void TestPlot_SelectMarkMulti(IVBF_MainCtrl* pIMainCtrl)
{
	IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
	if(NULL==pI3DPlot) return;

	IVBF_3DPlotDoc* pIDoc = pI3DPlot->GetActiveDoc();
	if(NULL==pIDoc) return;

	std::vector<IVBF_3DPlotLayer*> vLayers;
	pIDoc->GetAllLayers(vLayers);

	for(int i=0; i<(int)vLayers.size(); i++)
	{
		IVBF_3DPlotLayer* pILayer = vLayers[i];
		if(NULL==pILayer) continue;

		std::vector<IVBF_MarkModel*> vMarks;
		pILayer->GetAllMarks(vMarks);

		for(int k=0; k<(int)vMarks.size(); k++)
		{
			IVBF_MarkModel* pIMark = vMarks[k];
			if(pIMark) pILayer->SelectMark(pIMark->GetID(), false);
		}
	}
}

// 测试模型拉框选择
void TestPlot_SelectMarkByRect(IVBF_MainCtrl* pIMainCtrl)
{
	if(pIMainCtrl) pIMainCtrl->SelectTool(VBF_TOOL_MARK_SELECT_RECT);
}



// 测试模型光照
void TestPlotLight(IVBF_MainCtrl* pIMainCtrl)
{
	IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
	if(NULL==pI3DPlot) return;

	std::vector<IVBF_3DPlotDoc*> vDocs;
	pI3DPlot->GetAllDocs(vDocs);

	// 遍历所有文档
	for(unsigned int nDoc=0; nDoc<vDocs.size(); nDoc++)
	{
		IVBF_3DPlotDoc* pIDoc = vDocs[nDoc];
		if(NULL==pIDoc) continue;

		std::vector<IVBF_3DPlotLayer*> vLayers;
		pIDoc->GetAllLayers(vLayers);

		// 遍历文档中的所有图层
		for(unsigned int n=0; n<vLayers.size(); n++)
		{
			IVBF_3DPlotLayer* pILayer = vLayers[n];
			if(NULL==pILayer) continue;

			std::vector<IVBF_MarkModel*> vMarks;
			pILayer->GetAllMarks(vMarks);

			// 遍历图层中的所有模型
			for(int i=0; i<(int)vMarks.size(); i++)
			{
				IVBF_MarkModel* pIMark = vMarks[i];
				if(NULL==pIMark) continue;

				pIMark->EnableLight( !pIMark->IsLightEnabled() );

				for(int k=0; k<pIMark->GetChildCount(); k++)
				{
					IVBF_MarkModel* pIChild = pIMark->GetChild(k);
					if(pIChild) pIChild->EnableLight( !pIChild->IsLightEnabled() );
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
// 函数：TestPlot_ClearAllDocs()
// 描述：删除所有标图文档
//-----------------------------------------------------------------------------
void TestPlot_ClearAllDocs(IVBF_MainCtrl* pIMainCtrl)
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return;

    std::vector<IVBF_3DPlotDoc*> vDocs;
    pI3DPlot->GetAllDocs(vDocs);

    for(std::vector<IVBF_3DPlotDoc*>::iterator pIter=vDocs.begin(); pIter!=vDocs.end(); pIter++)
    {
        IVBF_3DPlotDoc* pIDoc = *pIter;
        if(NULL==pIDoc) continue;

        std::vector<IVBF_3DPlotLayer*> vLayers;
        pIDoc->GetAllLayers(vLayers);

        // 遍历文档中的所有图层
        for(unsigned int n=0; n<vLayers.size(); n++)
        {
            IVBF_3DPlotLayer* pILayer = vLayers[n];
            if(NULL==pILayer) continue;

            pIDoc->DeleteLayer( pILayer->GetLayerName() );
        }

        pI3DPlot->DeleteDoc(pIDoc); 
    }
}

//-----------------------------------------------------------------------------
// 函数：TestPlot_ClearAllMarks()
// 描述：删除所有模型
//-----------------------------------------------------------------------------
void TestPlot_ClearAllMarks(IVBF_MainCtrl* pIMainCtrl)
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return;

    IVBF_3DPlotDoc* pIDoc = pI3DPlot->GetActiveDoc();
    if(NULL==pIDoc) return;

    std::vector<IVBF_3DPlotLayer*> vLayers;
    pIDoc->GetAllLayers(vLayers);

    // 遍历文档中的所有图层
    for(unsigned int n=0; n<vLayers.size(); n++)
    {
        IVBF_3DPlotLayer* pILayer = vLayers[n];
        if(NULL==pILayer) continue;

		pIDoc->DeleteLayer( pILayer->GetLayerName() );
	}
}

//-----------------------------------------------------------------------------
// 函数：TestPlot_SetAllMarksVisible()
// 描述：显示/隐藏所有模型
// 参数：strLayerName -- 模型所在的图层名，如果为空，表示显示/隐藏所有图层中的模型
//-----------------------------------------------------------------------------
void TestPlot_SetAllMarksVisible(IVBF_MainCtrl* pIMainCtrl, bool bVisible, const std::string& strLayerName="")
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return;

    std::vector<IVBF_3DPlotDoc*> vDocs;
    pI3DPlot->GetAllDocs(vDocs);

	// 遍历所有文档
	for(unsigned int nDoc=0; nDoc<vDocs.size(); nDoc++)
	{
		IVBF_3DPlotDoc* pIDoc = vDocs[nDoc];
		if(NULL==pIDoc) continue;

		std::vector<IVBF_3DPlotLayer*> vLayers;
		pIDoc->GetAllLayers(vLayers);

		// 遍历文档中的所有图层
		for(unsigned int n=0; n<vLayers.size(); n++)
		{
			IVBF_3DPlotLayer* pILayer = vLayers[n];
			if(NULL==pILayer) continue;
			if(pILayer->IsInnerLayer()) continue;

			// 隐藏指定图层中的模型
			if(strLayerName!="" && strLayerName!=pILayer->GetLayerName())
			{
				continue;
			}

			std::vector<IVBF_MarkModel*> vMarks;
			pILayer->GetAllMarks(vMarks);

			// 遍历图层中的所有模型
			for(int i=0; i<(int)vMarks.size(); i++)
			{
				IVBF_MarkModel* pIMark = vMarks[i];
				if(pIMark) pIMark->SetVisible(bVisible);
			}
		}
	}
}

// 显示所有模型
void TestPlot_ShowAllMarks(IVBF_MainCtrl* pIMainCtrl)
{
	TestPlot_SetAllMarksVisible(pIMainCtrl, true, "");
}

// 隐藏所有模型
void TestPlot_HideAllMarks(IVBF_MainCtrl* pIMainCtrl)
{
	TestPlot_SetAllMarksVisible(pIMainCtrl, false, "");
}

//-----------------------------------------------------------------------------
// 函数：TestPlot_SetLayerDist()
// 描述：设置所有图层的可见距离
//-----------------------------------------------------------------------------
void TestPlot_SetLayerDist(IVBF_MainCtrl* pIMainCtrl, float fDistMax)
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return;

    std::vector<IVBF_3DPlotDoc*> vDocs;
    pI3DPlot->GetAllDocs(vDocs);

	// 遍历所有文档
	for(unsigned int nDoc=0; nDoc<vDocs.size(); nDoc++)
	{
		IVBF_3DPlotDoc* pIDoc = vDocs[nDoc];
		if(NULL==pIDoc) continue;

		std::vector<IVBF_3DPlotLayer*> vLayers;
		pIDoc->GetAllLayers(vLayers);

		// 遍历文档中的所有图层
		for(unsigned int n=0; n<vLayers.size(); n++)
		{
			IVBF_3DPlotLayer* pILayer = vLayers[n];
			if(NULL==pILayer) continue;
			if(pILayer->IsInnerLayer())  continue;

			pILayer->SetDistMin(0);
			pILayer->SetDistMax(fDistMax);
		}
	}
}

//-----------------------------------------------------------------------------
// 函数：TestPlot_SetMarkDist()
// 描述：设置所有模型的可见距离
//-----------------------------------------------------------------------------
void TestPlot_SetMarkDist(IVBF_MainCtrl* pIMainCtrl, float fDistMax)
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return;

    std::vector<IVBF_3DPlotDoc*> vDocs;
    pI3DPlot->GetAllDocs(vDocs);

	// 遍历所有文档
	for(unsigned int nDoc=0; nDoc<vDocs.size(); nDoc++)
	{
		IVBF_3DPlotDoc* pIDoc = vDocs[nDoc];
		if(NULL==pIDoc) continue;

		std::vector<IVBF_3DPlotLayer*> vLayers;
		pIDoc->GetAllLayers(vLayers);

		// 遍历文档中的所有图层
		for(unsigned int n=0; n<vLayers.size(); n++)
		{
			IVBF_3DPlotLayer* pILayer = vLayers[n];
			if(NULL==pILayer) continue;

			std::vector<IVBF_MarkModel*> vMarks;
			pILayer->GetAllMarks(vMarks);

			// 遍历图层中的所有模型
			for(int i=0; i<(int)vMarks.size(); i++)
			{
				IVBF_MarkModel* pIMark = vMarks[i];
				if(NULL==pIMark) continue;

				pIMark->SetDistMin(0);
				pIMark->SetDistMax(fDistMax);
			}
		}
	}
}

// 设置所有图层的可见距离
void TestPlot_SetLayerDist(IVBF_MainCtrl* pIMainCtrl)
{
	s_fLayerDistMax = 5e6;
	TestPlot_SetLayerDist(pIMainCtrl, s_fLayerDistMax);
}

// 取消所有图层的可见距离
void TestPlot_CancelLayerDist(IVBF_MainCtrl* pIMainCtrl)
{
	s_fLayerDistMax = FLT_MAX;
	TestPlot_SetLayerDist(pIMainCtrl, s_fLayerDistMax);
}

// 设置所有模型的可见距离
void TestPlot_SetMarkDist(IVBF_MainCtrl* pIMainCtrl)
{
	s_fMarkDistMax = 5e6;
	::TestPlot_SetMarkDist(pIMainCtrl, s_fMarkDistMax);
}

// 取消所有模型的可见距离
void TestPlot_CancelMarkDist(IVBF_MainCtrl* pIMainCtrl)
{
	s_fMarkDistMax = FLT_MAX;
	::TestPlot_SetMarkDist(pIMainCtrl, s_fMarkDistMax);
}

// 所有模型开始闪烁
void TestPlot_StartFlicker(IVBF_MainCtrl* pIMainCtrl)
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return;

    std::vector<IVBF_3DPlotDoc*> vDocs;
    pI3DPlot->GetAllDocs(vDocs);

	// 遍历所有文档
	for(unsigned int nDoc=0; nDoc<vDocs.size(); nDoc++)
	{
		IVBF_3DPlotDoc* pIDoc = vDocs[nDoc];
		if(NULL==pIDoc) continue;

		std::vector<IVBF_3DPlotLayer*> vLayers;
		pIDoc->GetAllLayers(vLayers);

		// 遍历文档中的所有图层
		for(unsigned int n=0; n<vLayers.size(); n++)
		{
			IVBF_3DPlotLayer* pILayer = vLayers[n];
			if(NULL==pILayer) continue;

			std::vector<IVBF_MarkModel*> vMarks;
			pILayer->GetAllMarks(vMarks);

			// 遍历图层中的所有模型
			for(int i=0; i<(int)vMarks.size(); i++)
			{
				IVBF_MarkModel* pIMark = vMarks[i];
				if(pIMark) pIMark->StartFlicker(3, 10, true);
			}
		}
	}
}

// 所有模型停止闪烁
void TestPlot_StopFlicker(IVBF_MainCtrl* pIMainCtrl)
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return;

    std::vector<IVBF_3DPlotDoc*> vDocs;
    pI3DPlot->GetAllDocs(vDocs);

	// 遍历所有文档
	for(unsigned int nDoc=0; nDoc<vDocs.size(); nDoc++)
	{
		IVBF_3DPlotDoc* pIDoc = vDocs[nDoc];
		if(NULL==pIDoc) continue;

		std::vector<IVBF_3DPlotLayer*> vLayers;
		pIDoc->GetAllLayers(vLayers);

		// 遍历文档中的所有图层
		for(unsigned int n=0; n<vLayers.size(); n++)
		{
			IVBF_3DPlotLayer* pILayer = vLayers[n];
			if(NULL==pILayer) continue;

			std::vector<IVBF_MarkModel*> vMarks;
			pILayer->GetAllMarks(vMarks);

			// 遍历图层中的所有模型
			for(int i=0; i<(int)vMarks.size(); i++)
			{
				IVBF_MarkModel* pIMark = vMarks[i];
				if(pIMark) pIMark->StopFlicker();
			}
		}
	}
}
class CVBF_Observer2 : public IVBF_Observer
{
public:
    virtual void OnEvent(const char* szMessage, int nValue=0, void* pValue=NULL)
    {
        int ii=0;
    }

};


void TestPlot_Observer(IVBF_MainCtrl* pIMainCtrl)
{
    pIMainCtrl->SelectTool(VBF_TOOL_MARK_EDIT);

    IVBF_3DMainCtrl* pI3DMainCtrl = (IVBF_3DMainCtrl*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DMAIN);
    if(NULL==pI3DMainCtrl) return;

    pI3DMainCtrl->Attach(new CVBF_Observer2() );

    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return;

    pI3DPlot->SetState(VBF_PLOT_STATE_ATTR);
}

// 开启/关闭所有模型的光照效果
void EnableMarkLight(IVBF_MainCtrl* pIMainCtrl, bool bEnable)
{
	IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
	if(NULL==pI3DPlot) return;

	IVBF_3DPlotDoc* pIDoc = pI3DPlot->GetActiveDoc();
	if(NULL==pIDoc) return;

	std::vector<IVBF_3DPlotLayer*> vLayers;
	pIDoc->GetAllLayers(vLayers);

	for(int i=0; i<(int)vLayers.size(); i++)
	{
		IVBF_3DPlotLayer* pILayer = vLayers[i];
		if(NULL==pILayer) continue;

		std::vector<IVBF_MarkModel*> vMarks;
		pILayer->GetAllMarks(vMarks);

		for(int k=0; k<(int)vMarks.size(); k++)
		{
			IVBF_MarkModel* pIMark = vMarks[k];
			if(pIMark) pIMark->EnableLight(bEnable);
		}
	}
}


// 开启模型光照
void TestPlot_EnableMarkLight(IVBF_MainCtrl* pIMainCtrl)
{
    EnableMarkLight(pIMainCtrl, true);
}

// 关闭模型光照
void TestPlot_DisableMarkLight(IVBF_MainCtrl* pIMainCtrl)
{
    EnableMarkLight(pIMainCtrl, false);
}

// 关闭面光滑
void TestPlot_DisablePolygonSmooth(IVBF_MainCtrl* pIMainCtrl)
{
	IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
	if(pI3DPlot) pI3DPlot->SetPolySmooth(false);
}

// 图标管理
void PlotManager(IVBF_MainCtrl* pIMainCtrl)
{
	if(pIMainCtrl==NULL) return;

	IVBF_3DMainCtrl* pI3DMainCtrl = (IVBF_3DMainCtrl*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DMAIN);
	if(NULL==pI3DMainCtrl) return;

	// 通过命令显示对话框
	pI3DMainCtrl->ExecuteCommand(VBF_COMMAND_SHOWDIALOG_PLOTMANAGER, NULL, NULL);
}


// 注册函数
VBF_REGISTER_FUNCTION(TestPlot_SelectMark) //选择军标
VBF_REGISTER_FUNCTION(TestPlot_SelectMarkMulti)
VBF_REGISTER_FUNCTION(TestPlot_SelectMarkByRect)


VBF_REGISTER_FUNCTION(TestPlot_ToggleMark)
VBF_REGISTER_FUNCTION(TestPlot_ToggleAttrLabel)
VBF_REGISTER_FUNCTION(TestPlot_ToggleAttrPowerMap)
VBF_REGISTER_FUNCTION(TestPlot_ToggleAttrHintLine)
VBF_REGISTER_FUNCTION(TestPlot_ToggleAttrTrailLine)
VBF_REGISTER_FUNCTION(TestPlot_ToggleAttrTrailLinePoint)
VBF_REGISTER_FUNCTION(TestPlot_ToggleAttrTrailStrip)

VBF_REGISTER_FUNCTION(TestPlot_UpdateAttrTrailLine)

VBF_REGISTER_FUNCTION(TestPlotLight)

VBF_REGISTER_FUNCTION(TestPlot_ClearAllDocs)
VBF_REGISTER_FUNCTION(TestPlot_ClearAllMarks)
VBF_REGISTER_FUNCTION(TestPlot_ShowAllMarks)
VBF_REGISTER_FUNCTION(TestPlot_HideAllMarks)

VBF_REGISTER_FUNCTION(TestPlot_SetLayerDist)
VBF_REGISTER_FUNCTION(TestPlot_CancelLayerDist)
VBF_REGISTER_FUNCTION(TestPlot_SetMarkDist)
VBF_REGISTER_FUNCTION(TestPlot_CancelMarkDist)

VBF_REGISTER_FUNCTION(TestPlot_EnableMarkLight)     // 开启模型光照
VBF_REGISTER_FUNCTION(TestPlot_DisableMarkLight)    // 关闭模型光照

VBF_REGISTER_FUNCTION(TestPlot_StartFlicker)
VBF_REGISTER_FUNCTION(TestPlot_StopFlicker)
VBF_REGISTER_FUNCTION(TestPlot_Observer)
VBF_REGISTER_FUNCTION(TestPlot_DisablePolygonSmooth)

VBF_REGISTER_FUNCTION(PlotManager)	//图标管理


