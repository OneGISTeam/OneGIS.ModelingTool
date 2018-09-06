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


IVBF_3DPlot* g_pI3DPlot      = NULL;         // 3D��ͼ�ӿ�
std::string  g_strDocName    = "VBF_3DPLOTDOC_DEFAULT";    // ����ģ�͹��õı�ͼ�ĵ�
float        s_fMeshScale    = 100.0f;      // Meshģ�͵ķŴ���
osg::Vec3d   g_vGeo          = osg::Vec3d(113.567710, 34.810054, 150.0); // ģ�͵Ķ�λ�㣨�������꣩




// �������ԵĿɼ���
bool s_bVisibleMark				= true;
bool s_bVisibleLabel			= true;
bool s_bVisibleHintLine			= true;
bool s_bVisibleTrailLine		= true;
bool s_bVisibleTrailLinePoint	= false;
bool s_bVisibleTrailStrip		= true;
bool s_bVisiblePowerMap			= true;
bool s_bActionEnabled			= true;
bool s_bVisibleIntersect		= false;


// ͼ���ģ�͵Ŀɼ�����
float s_fLayerDistMax			= FLT_MAX;
float s_fMarkDistMax			= FLT_MAX;


// ��������ģ�͵Ŀɼ���
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

// ��������ģ��ĳ�����ԵĿɼ���
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

// ��������ģ��ĳ�����Ե���ʽ���켣��
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

            // �߶���ʽ
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


// ����ģ��
void TestPlot_ToggleMark(IVBF_MainCtrl* pIMainCtrl)
{
	s_bVisibleMark = !s_bVisibleMark;
	ToggleMark(pIMainCtrl, s_bVisibleMark);
}

// ����ģ�����ԣ���ǩ
void TestPlot_ToggleAttrLabel(IVBF_MainCtrl* pIMainCtrl)
{
	s_bVisibleLabel = !s_bVisibleLabel;
    SetAttrVisible(pIMainCtrl, VBF_MARK_ATTR_LABEL, s_bVisibleLabel);
}

// ����ģ�����ԣ�����ͼ
void TestPlot_ToggleAttrPowerMap(IVBF_MainCtrl* pIMainCtrl)
{
    s_bVisiblePowerMap = !s_bVisiblePowerMap;
    SetAttrVisible(pIMainCtrl, VBF_MARK_ATTR_POWERMAP, s_bVisiblePowerMap);
}

// ����ģ�����ԣ��߶���
void TestPlot_ToggleAttrHintLine(IVBF_MainCtrl* pIMainCtrl)
{
	s_bVisibleHintLine = !s_bVisibleHintLine;
    SetAttrVisible(pIMainCtrl, VBF_MARK_ATTR_HINTLINE, s_bVisibleHintLine);
}

// ����ģ�����ԣ��켣��
void TestPlot_ToggleAttrTrailLine(IVBF_MainCtrl* pIMainCtrl)
{
	s_bVisibleTrailLine = !s_bVisibleTrailLine;
    SetAttrVisible(pIMainCtrl, VBF_MARK_ATTR_TRAILLINE, s_bVisibleTrailLine);
}

// ����ģ�����ԣ��켣���ϵĵ�
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

// ����ģ�����ԣ��ɻ�β��
void TestPlot_ToggleAttrTrailStrip(IVBF_MainCtrl* pIMainCtrl)
{
	s_bVisibleTrailStrip = !s_bVisibleTrailStrip;
    SetAttrVisible(pIMainCtrl, VBF_MARK_ATTR_TRAILSTRIP, s_bVisibleTrailStrip);
}

// ����ģ�͵�ѡ
void TestPlot_SelectMark(IVBF_MainCtrl* pIMainCtrl)
{
    pIMainCtrl->SelectTool(VBF_TOOL_MARK_SELECT);
}

// ����ģ�Ͷ�ѡ
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

// ����ģ������ѡ��
void TestPlot_SelectMarkByRect(IVBF_MainCtrl* pIMainCtrl)
{
	if(pIMainCtrl) pIMainCtrl->SelectTool(VBF_TOOL_MARK_SELECT_RECT);
}



// ����ģ�͹���
void TestPlotLight(IVBF_MainCtrl* pIMainCtrl)
{
	IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
	if(NULL==pI3DPlot) return;

	std::vector<IVBF_3DPlotDoc*> vDocs;
	pI3DPlot->GetAllDocs(vDocs);

	// ���������ĵ�
	for(unsigned int nDoc=0; nDoc<vDocs.size(); nDoc++)
	{
		IVBF_3DPlotDoc* pIDoc = vDocs[nDoc];
		if(NULL==pIDoc) continue;

		std::vector<IVBF_3DPlotLayer*> vLayers;
		pIDoc->GetAllLayers(vLayers);

		// �����ĵ��е�����ͼ��
		for(unsigned int n=0; n<vLayers.size(); n++)
		{
			IVBF_3DPlotLayer* pILayer = vLayers[n];
			if(NULL==pILayer) continue;

			std::vector<IVBF_MarkModel*> vMarks;
			pILayer->GetAllMarks(vMarks);

			// ����ͼ���е�����ģ��
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
// ������TestPlot_ClearAllDocs()
// ������ɾ�����б�ͼ�ĵ�
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

        // �����ĵ��е�����ͼ��
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
// ������TestPlot_ClearAllMarks()
// ������ɾ������ģ��
//-----------------------------------------------------------------------------
void TestPlot_ClearAllMarks(IVBF_MainCtrl* pIMainCtrl)
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return;

    IVBF_3DPlotDoc* pIDoc = pI3DPlot->GetActiveDoc();
    if(NULL==pIDoc) return;

    std::vector<IVBF_3DPlotLayer*> vLayers;
    pIDoc->GetAllLayers(vLayers);

    // �����ĵ��е�����ͼ��
    for(unsigned int n=0; n<vLayers.size(); n++)
    {
        IVBF_3DPlotLayer* pILayer = vLayers[n];
        if(NULL==pILayer) continue;

		pIDoc->DeleteLayer( pILayer->GetLayerName() );
	}
}

//-----------------------------------------------------------------------------
// ������TestPlot_SetAllMarksVisible()
// ��������ʾ/��������ģ��
// ������strLayerName -- ģ�����ڵ�ͼ���������Ϊ�գ���ʾ��ʾ/��������ͼ���е�ģ��
//-----------------------------------------------------------------------------
void TestPlot_SetAllMarksVisible(IVBF_MainCtrl* pIMainCtrl, bool bVisible, const std::string& strLayerName="")
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return;

    std::vector<IVBF_3DPlotDoc*> vDocs;
    pI3DPlot->GetAllDocs(vDocs);

	// ���������ĵ�
	for(unsigned int nDoc=0; nDoc<vDocs.size(); nDoc++)
	{
		IVBF_3DPlotDoc* pIDoc = vDocs[nDoc];
		if(NULL==pIDoc) continue;

		std::vector<IVBF_3DPlotLayer*> vLayers;
		pIDoc->GetAllLayers(vLayers);

		// �����ĵ��е�����ͼ��
		for(unsigned int n=0; n<vLayers.size(); n++)
		{
			IVBF_3DPlotLayer* pILayer = vLayers[n];
			if(NULL==pILayer) continue;
			if(pILayer->IsInnerLayer()) continue;

			// ����ָ��ͼ���е�ģ��
			if(strLayerName!="" && strLayerName!=pILayer->GetLayerName())
			{
				continue;
			}

			std::vector<IVBF_MarkModel*> vMarks;
			pILayer->GetAllMarks(vMarks);

			// ����ͼ���е�����ģ��
			for(int i=0; i<(int)vMarks.size(); i++)
			{
				IVBF_MarkModel* pIMark = vMarks[i];
				if(pIMark) pIMark->SetVisible(bVisible);
			}
		}
	}
}

// ��ʾ����ģ��
void TestPlot_ShowAllMarks(IVBF_MainCtrl* pIMainCtrl)
{
	TestPlot_SetAllMarksVisible(pIMainCtrl, true, "");
}

// ��������ģ��
void TestPlot_HideAllMarks(IVBF_MainCtrl* pIMainCtrl)
{
	TestPlot_SetAllMarksVisible(pIMainCtrl, false, "");
}

//-----------------------------------------------------------------------------
// ������TestPlot_SetLayerDist()
// ��������������ͼ��Ŀɼ�����
//-----------------------------------------------------------------------------
void TestPlot_SetLayerDist(IVBF_MainCtrl* pIMainCtrl, float fDistMax)
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return;

    std::vector<IVBF_3DPlotDoc*> vDocs;
    pI3DPlot->GetAllDocs(vDocs);

	// ���������ĵ�
	for(unsigned int nDoc=0; nDoc<vDocs.size(); nDoc++)
	{
		IVBF_3DPlotDoc* pIDoc = vDocs[nDoc];
		if(NULL==pIDoc) continue;

		std::vector<IVBF_3DPlotLayer*> vLayers;
		pIDoc->GetAllLayers(vLayers);

		// �����ĵ��е�����ͼ��
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
// ������TestPlot_SetMarkDist()
// ��������������ģ�͵Ŀɼ�����
//-----------------------------------------------------------------------------
void TestPlot_SetMarkDist(IVBF_MainCtrl* pIMainCtrl, float fDistMax)
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return;

    std::vector<IVBF_3DPlotDoc*> vDocs;
    pI3DPlot->GetAllDocs(vDocs);

	// ���������ĵ�
	for(unsigned int nDoc=0; nDoc<vDocs.size(); nDoc++)
	{
		IVBF_3DPlotDoc* pIDoc = vDocs[nDoc];
		if(NULL==pIDoc) continue;

		std::vector<IVBF_3DPlotLayer*> vLayers;
		pIDoc->GetAllLayers(vLayers);

		// �����ĵ��е�����ͼ��
		for(unsigned int n=0; n<vLayers.size(); n++)
		{
			IVBF_3DPlotLayer* pILayer = vLayers[n];
			if(NULL==pILayer) continue;

			std::vector<IVBF_MarkModel*> vMarks;
			pILayer->GetAllMarks(vMarks);

			// ����ͼ���е�����ģ��
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

// ��������ͼ��Ŀɼ�����
void TestPlot_SetLayerDist(IVBF_MainCtrl* pIMainCtrl)
{
	s_fLayerDistMax = 5e6;
	TestPlot_SetLayerDist(pIMainCtrl, s_fLayerDistMax);
}

// ȡ������ͼ��Ŀɼ�����
void TestPlot_CancelLayerDist(IVBF_MainCtrl* pIMainCtrl)
{
	s_fLayerDistMax = FLT_MAX;
	TestPlot_SetLayerDist(pIMainCtrl, s_fLayerDistMax);
}

// ��������ģ�͵Ŀɼ�����
void TestPlot_SetMarkDist(IVBF_MainCtrl* pIMainCtrl)
{
	s_fMarkDistMax = 5e6;
	::TestPlot_SetMarkDist(pIMainCtrl, s_fMarkDistMax);
}

// ȡ������ģ�͵Ŀɼ�����
void TestPlot_CancelMarkDist(IVBF_MainCtrl* pIMainCtrl)
{
	s_fMarkDistMax = FLT_MAX;
	::TestPlot_SetMarkDist(pIMainCtrl, s_fMarkDistMax);
}

// ����ģ�Ϳ�ʼ��˸
void TestPlot_StartFlicker(IVBF_MainCtrl* pIMainCtrl)
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return;

    std::vector<IVBF_3DPlotDoc*> vDocs;
    pI3DPlot->GetAllDocs(vDocs);

	// ���������ĵ�
	for(unsigned int nDoc=0; nDoc<vDocs.size(); nDoc++)
	{
		IVBF_3DPlotDoc* pIDoc = vDocs[nDoc];
		if(NULL==pIDoc) continue;

		std::vector<IVBF_3DPlotLayer*> vLayers;
		pIDoc->GetAllLayers(vLayers);

		// �����ĵ��е�����ͼ��
		for(unsigned int n=0; n<vLayers.size(); n++)
		{
			IVBF_3DPlotLayer* pILayer = vLayers[n];
			if(NULL==pILayer) continue;

			std::vector<IVBF_MarkModel*> vMarks;
			pILayer->GetAllMarks(vMarks);

			// ����ͼ���е�����ģ��
			for(int i=0; i<(int)vMarks.size(); i++)
			{
				IVBF_MarkModel* pIMark = vMarks[i];
				if(pIMark) pIMark->StartFlicker(3, 10, true);
			}
		}
	}
}

// ����ģ��ֹͣ��˸
void TestPlot_StopFlicker(IVBF_MainCtrl* pIMainCtrl)
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return;

    std::vector<IVBF_3DPlotDoc*> vDocs;
    pI3DPlot->GetAllDocs(vDocs);

	// ���������ĵ�
	for(unsigned int nDoc=0; nDoc<vDocs.size(); nDoc++)
	{
		IVBF_3DPlotDoc* pIDoc = vDocs[nDoc];
		if(NULL==pIDoc) continue;

		std::vector<IVBF_3DPlotLayer*> vLayers;
		pIDoc->GetAllLayers(vLayers);

		// �����ĵ��е�����ͼ��
		for(unsigned int n=0; n<vLayers.size(); n++)
		{
			IVBF_3DPlotLayer* pILayer = vLayers[n];
			if(NULL==pILayer) continue;

			std::vector<IVBF_MarkModel*> vMarks;
			pILayer->GetAllMarks(vMarks);

			// ����ͼ���е�����ģ��
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

// ����/�ر�����ģ�͵Ĺ���Ч��
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


// ����ģ�͹���
void TestPlot_EnableMarkLight(IVBF_MainCtrl* pIMainCtrl)
{
    EnableMarkLight(pIMainCtrl, true);
}

// �ر�ģ�͹���
void TestPlot_DisableMarkLight(IVBF_MainCtrl* pIMainCtrl)
{
    EnableMarkLight(pIMainCtrl, false);
}

// �ر���⻬
void TestPlot_DisablePolygonSmooth(IVBF_MainCtrl* pIMainCtrl)
{
	IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
	if(pI3DPlot) pI3DPlot->SetPolySmooth(false);
}

// ͼ�����
void PlotManager(IVBF_MainCtrl* pIMainCtrl)
{
	if(pIMainCtrl==NULL) return;

	IVBF_3DMainCtrl* pI3DMainCtrl = (IVBF_3DMainCtrl*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DMAIN);
	if(NULL==pI3DMainCtrl) return;

	// ͨ��������ʾ�Ի���
	pI3DMainCtrl->ExecuteCommand(VBF_COMMAND_SHOWDIALOG_PLOTMANAGER, NULL, NULL);
}


// ע�ắ��
VBF_REGISTER_FUNCTION(TestPlot_SelectMark) //ѡ�����
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

VBF_REGISTER_FUNCTION(TestPlot_EnableMarkLight)     // ����ģ�͹���
VBF_REGISTER_FUNCTION(TestPlot_DisableMarkLight)    // �ر�ģ�͹���

VBF_REGISTER_FUNCTION(TestPlot_StartFlicker)
VBF_REGISTER_FUNCTION(TestPlot_StopFlicker)
VBF_REGISTER_FUNCTION(TestPlot_Observer)
VBF_REGISTER_FUNCTION(TestPlot_DisablePolygonSmooth)

VBF_REGISTER_FUNCTION(PlotManager)	//ͼ�����


