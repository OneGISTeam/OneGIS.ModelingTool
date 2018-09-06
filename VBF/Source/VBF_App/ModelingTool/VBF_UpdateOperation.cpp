//#include "stdafx.h"
#include "VBF_UpdateOperation.h"
#include "VBF_LoadThread.h"
#include "VBF_GlobalGIS_Plot.h"

#include <VBF_Engine/VBF_SceneGraph/OperationThread>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>
#include <VBF_Plot/IVBF_3DPlot.h>
#include <VBF_Plot/Common/IVBF_MarkModelMesh.h>
#include <VBF_Plot/Common/IVBF_MarkModelRaster.h>
#include <VBF_Plot/Common/IVBF_MarkAttrLabel.h>
#include <VBF_Plot/Common/IVBF_MarkAttrHintLine.h>
#include <VBF_Plot/Common/IVBF_MarkAttrTrailLine.h>
#include <VBF_Plot/Common/IVBF_MarkAttrTrailStrip.h>
#include <VBF_Plot/Common/IVBF_MarkAttrTrailSmoke.h>
#include <VBF_Plot/IVBF_MarkAttrIFF.h>
#include <VBF_Plot/ElecMag/IVBF_MarkAttrPowerMap.h>
#include <VBF_Common/VBF_Utils/VBF_FileNameUtils.h>
#include <VBF_Aux/VBF_GLAux/VBF_ImageTextureUtils.h>


// 各类属性的可见性
extern bool s_bVisibleMark;
extern bool s_bVisibleLabel;
extern bool s_bVisibleHintLine;
extern bool s_bVisibleTrailLine;
extern bool s_bVisibleTrailLinePoint;
extern bool s_bVisibleTrailStrip;
extern bool s_bVisiblePowerMap;
extern bool s_bActionEnabled;

// 图层和模型的可见距离
extern float s_fLayerDistMax;
extern float s_fMarkDistMax;


CVBF_UpdateOperation::CVBF_UpdateOperation(const std::string& name, IVBF_3DMainCtrl* p3DMainCtrl) :
		osg::Operation(name, true), 
		m_pI3DMainCtrl(p3DMainCtrl)
{
    m_pI3DPlot = (IVBF_3DPlot*)m_pI3DMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);

    // 提取一个数据的时间间隔（单位：秒）
    m_dDeltaTime = 0.03;

    // 开启线程
    m_pThread = new CVBF_LoadThread();
    m_pThread->start();

    // 开始计时
    m_Timer.setStartTick();
    m_TimerSim.setStartTick();
}

CVBF_UpdateOperation::~CVBF_UpdateOperation()
{
    // 停止线程
    if(m_pThread!=NULL &&m_pThread->isRunning()) m_pThread->cancel();
	SAFE_DELETE(m_pThread);
}

void CVBF_UpdateOperation::operator()(osg::CVBF_Object* pObject)
{
    // 每隔1秒提取一个数据
    double dDeltaTime = m_Timer.time_s();
    if(dDeltaTime >= m_dDeltaTime)
    {
        if(m_pThread!=NULL) UpdateSituMark();

        // 重新开始计时
        m_Timer.setStartTick();
    }
}

// 删除所有模型
void CVBF_UpdateOperation::Clear()
{
    if(m_pI3DPlot!=NULL) m_pI3DPlot->DeleteDoc(g_strDocName);
}

// 创建Mesh类模型
IVBF_MarkModelMesh* CVBF_UpdateOperation::CreateMarkMesh(const std::string& strMarkID, std::string strModelFileName)
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)m_pI3DMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return NULL;

    bool bFromXml = ( ::VBF_getFileExtension(strModelFileName)=="xml" );

    IVBF_MarkModelMesh* pIMark = (IVBF_MarkModelMesh*)pI3DPlot->CreateMarkModel(strMarkID, VBF_MARK_MESH);
    if(NULL==pIMark) return NULL;

    pIMark->SetFileName(strModelFileName);
    pIMark->SetRotateInit(0, 0, -180);
    pIMark->SetScale(100, 100, 100);
    pIMark->EnableScaleDelta(true);

    // 模型动作
    if( strstr(strModelFileName.c_str(), "Zhi9Wu")!=NULL )
    {
        IVBF_MarkModel* pIScrewFront = pIMark->GetChildNested("QianLuoXuanJiang");
        if(pIScrewFront!=NULL) pIScrewFront->DoAction("RotateAxis", s_bActionEnabled);

        IVBF_MarkModel* pIScrewBack = pIMark->GetChildNested("HouLuoXuanJiang");
        if(pIScrewBack!=NULL) pIScrewBack->DoAction("RotateAxis", s_bActionEnabled);
    }
    else if( strstr(strModelFileName.c_str(), "KJ-200")!=NULL )
    {

        IVBF_MarkModel* pIScrew0 = pIMark->GetChildNested("LuoXuanJiang0");
        if(pIScrew0!=NULL) pIScrew0->DoAction("RotateAxis", s_bActionEnabled);

        IVBF_MarkModel* pIScrew1 = pIMark->GetChildNested("LuoXuanJiang1");
        if(pIScrew1!=NULL) pIScrew1->DoAction("RotateAxis", s_bActionEnabled);

        IVBF_MarkModel* pIScrew2 = pIMark->GetChildNested("LuoXuanJiang2");
        if(pIScrew2!=NULL) pIScrew2->DoAction("RotateAxis", s_bActionEnabled);

        IVBF_MarkModel* pIScrew3 = pIMark->GetChildNested("LuoXuanJiang3");
        if(pIScrew3!=NULL) pIScrew3->DoAction("RotateAxis", s_bActionEnabled);
    }
    else if( strstr(strModelFileName.c_str(), "03轻履")!=NULL )
    {

        IVBF_MarkModel* pIPedrail = pIMark->GetChildNested("履带");
        if(pIPedrail!=NULL) pIPedrail->DoAction("TexAnim", s_bActionEnabled);


        for(int n=0; n<20; n++)
        {
            char szWheelID[32];
            sprintf(szWheelID, "Wheel%d", n);
            IVBF_MarkModel* pIWheel = pIMark->GetChildNested(szWheelID);
            if(pIWheel!=NULL) pIWheel->DoAction("RotateAxis", s_bActionEnabled);
        }
    }

    return pIMark;
}

// 创建Raster类模型
IVBF_MarkModelRaster* CVBF_UpdateOperation::CreateMarkRaster(const std::string& strMarkID)
{
    IVBF_3DPlot* pI3DPlot = (IVBF_3DPlot*)m_pI3DMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
    if(NULL==pI3DPlot) return NULL;

    IVBF_MarkModelRaster* pIMark = dynamic_cast<IVBF_MarkModelRaster*>(pI3DPlot->CreateMarkModel(strMarkID, VBF_MARK_RASTER));
    if(NULL==pIMark) return NULL;

    pIMark->EnableFixedSizeInPixels(true);
    pIMark->SetFixedSizeInPixels(50.0f);
    pIMark->EnableScaleDelta(false);
    pIMark->SetTexImage( ::VBF_GetImageFromCache(g_sDataPath + "/Icon/AirPort.dds"), true );
    pIMark->SetTexOrign(0.5, 0.0);

    return pIMark;
}

// 添加/更新从子线程中读取的态势数据
void CVBF_UpdateOperation::UpdateSituMark()
{
    if(NULL==m_pThread) return;

    // 获取一个态势数据
    VBF_SITUDATA Data;
    if(!m_pThread->GetNextData(Data)) return;

    if(NULL==m_pI3DPlot) return;

    // 添加文档
    if(!m_pIDoc.valid())
    {
        m_pIDoc = m_pI3DPlot->AddDoc(g_strDocName);
        if(!m_pIDoc.valid()) return;

        m_pI3DPlot->ActivateDoc(g_strDocName);
    }

    // 添加图层
    IVBF_3DPlotLayer* pILayer = m_pIDoc->AddLayer(Data.szLayerName);
    if(NULL==pILayer) return;

    pILayer->SetDistMax(s_fLayerDistMax);

    bool bMesh = ( strstr(Data.szLabel, "干扰机")!=0 || strstr(Data.szLabel, "无人机")!=0 ||
                   strstr(Data.szLabel, "子母弹")!=0 || strstr(Data.szLabel, "平台")!=0 );

    // 利用读取的数据添加/更新模型
    IVBF_MarkModelPoint* pIMark = dynamic_cast<IVBF_MarkModelPoint*>(pILayer->GetMark(Data.szMarkID));
    if(NULL==pIMark)
    {
        if(bMesh)  // 测试不同类模型
        {
            if( strcmp(Data.szMarkID, "587")==0)
            {
                pIMark = CreateMarkMesh(Data.szMarkID, g_sDataPath+"/Model/Zhi9Wu/Zhi9Wu.xml");
            }
            else
            {
                pIMark = CreateMarkMesh(Data.szMarkID, g_sDataPath+"/Model/KJ-200/KJ-200.xml");
            }
        }
        else
        {
            pIMark = CreateMarkRaster(Data.szMarkID);
        }
        if(NULL==pIMark) return;

        pILayer->AddMark(pIMark);
    }

    pIMark->EnableLight(false);  // 开启光照
    pIMark->EnableAutoScale(false);
    pIMark->SetVisible((Data.bVisible==TRUE));
    pIMark->SetCode(Data.szMarkCode);
    pIMark->SetSimTimeMode(VBF_SIMTIME_MODE_VARIABLE);
    pIMark->SetDistMax(s_fMarkDistMax);

    // 步进地理坐标，同时传递轨迹点信息
    double dDeltaTime = m_TimerSim.time_s();
    char szPointInfo[64];
    sprintf(szPointInfo, "%s：%.3f秒", Data.szLabel, dDeltaTime);

    pIMark->SetSimTimeMode(VBF_SIMTIME_MODE_VARIABLE);
    if(bMesh)
        pIMark->StepGeoPos(Data.vPosGeo, Data.fRotateX, Data.fRotateY, Data.fRotateZ, szPointInfo);
    else
        pIMark->SetGeoPos(Data.vPosGeo);

    // 设置包围盒样式
    VBF_BOUNDINGBOXSTYLE BoxStyle;
    BoxStyle.nFlickerInterval = 10;
    BoxStyle.nFlickerTimes    = 5;
    BoxStyle.bFlickerAlways   = false;
    BoxStyle.fExpand          = 0.05f;
    BoxStyle.color            = osg::Vec4f(0, 1, 1, 0.4);

    pIMark->SetBoundingBoxStyle(BoxStyle);

    // 添加属性：敌我识别
    osg::Vec4f colorIFF(1, 1, 1, 1);

    IVBF_MarkAttrIFF* pIAttrIFF = dynamic_cast<IVBF_MarkAttrIFF*>(pIMark->AddMarkAttr(VBF_MARK_ATTR_IFF));
    if(pIAttrIFF!=NULL)
    {
        std::string strIFFName = "";
        if(Data.nATT==1)		strIFFName = "我方";
        else if(Data.nATT==2)	strIFFName = "敌方";
        else if(Data.nATT==3)	strIFFName = "友方";
        else 					strIFFName = "不明方";

        pIAttrIFF->SetIFFName(strIFFName);
        pIAttrIFF->SetVisible(true);

        VBF_MARKIFFSTYLE style;
        if(pIAttrIFF->GetIFFStyle(style))
        {
            colorIFF = style.color;
        }
    }

    // 设置标签参数
    IVBF_MarkAttrLabel* pIAttrLabel = dynamic_cast<IVBF_MarkAttrLabel*>(pIMark->AddMarkAttr(VBF_MARK_ATTR_LABEL));
    if(pIAttrLabel!=NULL)
    {
        pIAttrLabel->SetVisible(s_bVisibleLabel);
        pIAttrLabel->SetSimpleText(Data.szLabel);
        pIAttrLabel->SetDetailText(Data.szLabel);
        pIAttrLabel->SetTextItem(VBF_LABELITEM_SIMPLE);
    //  pIAttrLabel->SetPosType(bMesh? VBF_LABELPOS_ORIGIN : VBF_LABELPOS_BOXTOPCENTER);
        pIAttrLabel->SetPosType(VBF_LABELPOS_ORIGIN);

        VBF_TEXTSTYLE style;
        style.bSerif        = false;
        style.fFontSize		= 16;
        style.colorText		= osg::Vec4f(1.0f, 1.0f, 1.0f, 1.0f); // 字色
        style.colorSerif    = osg::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);

        pIAttrLabel->SetTextStyle(style);

        // 背景框样式
        VBF_POLYGON2DSTYLE stylePoly;
        stylePoly.bShadowed     = false;
        stylePoly.nShadowOffset = 4;
        stylePoly.colorFill		= osg::Vec4f(colorIFF.r(), colorIFF.g(), colorIFF.b(), 0.4f);
        stylePoly.colorShadow   = osg::Vec4f(0.1, 0.1, 0.1, 1.0);

        pIAttrLabel->SetFrameStyle(stylePoly);
        pIAttrLabel->SetFrameVisible(true);
    }

    // 为飞机类模型添加如下属性
//  if(!bMesh || pIMark->GetMarkID()!="587") return;
    if(!bMesh) return;

    // 添加属性：威力图
    IVBF_MarkAttrPowerMap* pIAttrPowerMap = dynamic_cast<IVBF_MarkAttrPowerMap*>(pIMark->AddMarkAttr(VBF_MARK_ATTR_POWERMAP));
    if(pIAttrPowerMap!=NULL)
    {
        pIAttrPowerMap->SetTess(0, 360, 0, 180);
        pIAttrPowerMap->SetRadius(1e4);
        pIAttrPowerMap->SetColor(osg::Vec4f(1,1,1,0.2));
        pIAttrPowerMap->SetGeometryStyle(VBF_GEOMETRY_STYLE_COMPOSITE);
        pIAttrPowerMap->SetVisible(s_bVisiblePowerMap);
    }

    // 添加属性：轨迹线
    IVBF_MarkAttrTrailLine* pIAttrTrailLine = dynamic_cast<IVBF_MarkAttrTrailLine*>(pIMark->LookupMarkAttr(VBF_MARK_ATTR_TRAILLINE));
    if(NULL==pIAttrTrailLine)
    {
        pIAttrTrailLine = dynamic_cast<IVBF_MarkAttrTrailLine*>(pIMark->AddMarkAttr(VBF_MARK_ATTR_TRAILLINE));
        if(pIAttrTrailLine!=NULL)
        {
            pIAttrTrailLine->SetVisible(s_bVisibleTrailLine);
            pIAttrTrailLine->SetNumPointsRetained(1000);
            pIAttrTrailLine->SetNumPointsVisible(500);
            pIAttrTrailLine->EnableFade(false);

            // 线段样式
            VBF_LINESTYLE style;
            style.color  = osg::Vec4f(colorIFF.r(), colorIFF.g(), colorIFF.b(), 1.0f);
            style.fWidth = 3.0f;
            pIAttrTrailLine->SetLineStyle(style);

            VBF_POINTSTYLE stylePoint;
            stylePoint.color = osg::Vec4f(0, 1, 1, 1.0f);
            stylePoint.fSize = 6.f;
            pIAttrTrailLine->SetPointStyle(stylePoint);
            pIAttrTrailLine->SetRenderStyle(s_bVisibleTrailLinePoint? VBF_TRAIL_STYLE_COMPOSITE : VBF_TRAIL_STYLE_LINE);

            // 轨迹点查询信息的样式
            pIAttrTrailLine->SetQueryFrameVisible(false);
        }
    }

/*
    // 添加属性：飞机尾迹
    IVBF_MarkAttrTrailStrip* pIAttrTrailStrip = dynamic_cast<IVBF_MarkAttrTrailStrip*>(pIMark->AddMarkAttr(VBF_MARK_ATTR_TRAILSTRIP));
    if(pIAttrTrailStrip!=NULL)
    {
        // 条带样式
        pIAttrTrailStrip->SetStripColor( osg::Vec4f(0.0f, 1.0f, 1.0f, 0.2f) );
        pIAttrTrailStrip->SetStripWidth(10.0f);
    //  pIAttrTrailStrip->SetStripOffset(0, -1, -5);

        pIAttrTrailStrip->SetVisible(s_bVisibleTrailStrip);
        pIAttrTrailStrip->SetRenderStyle(VBF_TRAIL_STYLE_LINE);
    }

    // 添加属性：尾烟
    IVBF_MarkAttrTrailSmoke* pIAttrTrailSmoke = dynamic_cast<IVBF_MarkAttrTrailSmoke*>(pIMark->AddMarkAttr(VBF_MARK_ATTR_TRAILSMOKE));
    if(pIAttrTrailSmoke!=NULL)
    {
        pIAttrTrailSmoke->SetWidth(100.0f);
    }
*/
    // 添加属性：高度线
    IVBF_MarkAttrHintLine* pIAttrHintLine = dynamic_cast<IVBF_MarkAttrHintLine*>(pIMark->AddMarkAttr(VBF_MARK_ATTR_HINTLINE));
    if(pIAttrHintLine!=NULL)
    {
        // 线段样式
        VBF_LINESTYLE style;
        style.fWidth = 1.0f;
        style.color  = osg::Vec4f(0.7f, 0.7f, 0.7f, 1.0f);
        pIAttrHintLine->SetLineStyle(style);
        pIAttrHintLine->SetVisible(s_bVisibleHintLine);
    }
}
