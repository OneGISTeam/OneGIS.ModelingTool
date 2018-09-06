//*******************************************************************
// FileName��VBF_GlobalGIS_Plot.h
// Function�����Ա�ͼģ����Ҫ�Ĺ���ͷ�ļ����ṩ���õı�������������
// Author:   ��Ө
// Date:     2014-09-04
//*******************************************************************

#ifndef __VBF_GLOBALGIS_PLOT_H__
#define __VBF_GLOBALGIS_PLOT_H__


#include <string>
#include <vector>

#include <VBF_MainCtrl/IVBF_MainCtrl.h>
#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>
#include <VBF_Plot/IVBF_3DPlot.h>
#include <VBF_Plot/IVBF_3DPlotDoc.h>
#include <VBF_Plot/IVBF_3DPlotLayer.h>
#include <VBF_Display/IVBF_3DDisplay.h>


extern string g_sDataPath;

extern IVBF_3DPlot* g_pI3DPlot;         // 3D��ͼ�ӿ�
extern std::string  g_strDocName;    // ����ģ�͹��õı�ͼ�ĵ�
extern float        s_fMeshScale;      // Meshģ�͵ķŴ���
extern osg::Vec3d   g_vGeo; // ģ�͵Ķ�λ�㣨�������꣩



//-----------------------------------------------------------------------------
// ����������VBF_Get3DPlot()
// ������������ȡ3D��ͼ�ӿ�
//-----------------------------------------------------------------------------
inline IVBF_3DPlot* VBF_Get3DPlot(IVBF_MainCtrl* pIMainCtrl)
{
    if(g_pI3DPlot!=NULL) return g_pI3DPlot;

    if(NULL==pIMainCtrl) return NULL;

    g_pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    return g_pI3DPlot;
}

//-----------------------------------------------------------------------------
// ����������VBF_CreateDocLayer()
// ����������������ͼ�ĵ���ͼ��
//-----------------------------------------------------------------------------
inline bool VBF_CreateDocLayer(IVBF_MainCtrl* pIMainCtrl, const std::string& strDocName, const std::string& strLayerName,
                               IVBF_3DPlotDoc*& pIDoc, IVBF_3DPlotLayer*& pILayer,EVBF_SRS srs = ECEF)
{
    if(NULL==pIMainCtrl) return false;

    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return false;

    pIDoc = pI3DPlot->AddDoc(strDocName);
    if(NULL==pIDoc) return false;

    pI3DPlot->ActivateDoc(strDocName);

    pILayer = pIDoc->AddLayer(strLayerName,srs);
    if(NULL==pILayer) return false;

    return true;
}

//-----------------------------------------------------------------------------
// ����������VBF_DeleteDoc()
// ����������ɾ��ָ���ı�ͼ�ĵ�
//-----------------------------------------------------------------------------
inline void VBF_DeleteDoc(IVBF_MainCtrl* pIMainCtrl, const std::string& strDocName)
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(pI3DPlot) pI3DPlot->DeleteDoc(strDocName);
}

//-----------------------------------------------------------------------------
// ����������VBF_Locate()
// ������������λ��ָ��λ��
//-----------------------------------------------------------------------------
inline void VBF_Locate(IVBF_MainCtrl* pIMainCtrl, const osg::Vec3d& ptGeo, double dViewDist, double dAngleH, double dAngleV=-90.0, double dDurationSec=3.0)
{
    IVBF_3DDisplay* pI3DDisplay = (IVBF_3DDisplay*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DDISPLAY, NULL);
    if(NULL==pI3DDisplay) return;

    CVBF_Viewpoint point(ptGeo, dAngleH, dAngleV, dViewDist);
    pI3DDisplay->SetViewpoint(point, dDurationSec, false);
}


#endif
