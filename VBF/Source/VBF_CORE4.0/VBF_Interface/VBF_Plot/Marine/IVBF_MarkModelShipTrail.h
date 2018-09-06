//************************************************************************
// FileName：IVBF_MarkModelShipTrail.h
// Function：军标实体模型接口：单条航迹
// Author:   杜莹
// Date:     2016-07-27
//************************************************************************

#ifndef __IVBF_MARK_MODEL_SHIPTRAIL_H__
#define __IVBF_MARK_MODEL_SHIPTRAIL_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Marine/VBF_3DPlotDataTypes_Marine.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Plot/Marine/VBF_TrailInfo.h>


// 定义消息ID号
const char VBF_MESSAGE_3DPLOT_SHIPTRAIL_REQUESTED[]         = "Message: ShipTrail Requested";
const char VBF_MESSAGE_3DPLOT_SHIPTRAIL_SELECTED[]          = "Message: ShipTrail Selected";            // 消息：航迹被选中了，nValue=1，pValue=VBF_TRAIL_EXTINFO*

const char VBF_MESSAGE_3DPLOT_SHIPTRAIL_SHOWINFODIALOG[]    = "Message: ShipTrail ShowInfoDialog";      // 消息：需要显示航迹信息，nValue=1，pValue=osg::Vec2f*
const char VBF_MESSAGE_3DPLOT_SHIPTRAIL_UPDATEINFODIALOG[]  = "Message: ShipTrail UpdateInfoDialog";    // 消息：需要更新航迹信息
const char VBF_MESSAGE_3DPLOT_SHIPTRAIL_CLOSEINFODIALOG[]   = "Message: ShipTrail CloseInfoDialog";     // 消息：需要关闭航迹信息对话框
const char VBF_MESSAGE_3DPLOT_SHIPTRAIL_SHOWREPLAYDIALOG[]  = "Message: ShipTrail ShowReplayDialog";    // 消息：需要显示航迹回放对话框
const char VBF_MESSAGE_3DPLOT_SHIPTRAIL_CLOSEREPLAYDIALOG[] = "Message: ShipTrail CloseReplayDialog";   // 消息：需要关闭航迹回放对话框



//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShipTrail
// 接口描述：单条航迹
//--------------------------------------------------------------------
class IVBF_MarkModelShipTrail : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelShipTrail() {}

    // 设置航迹信息
    virtual void SetTrailInfo(const VBF_TRAIL_INFO& trail)=0;

    // 获取航迹信息（如果航迹信息尚未设置，返回false）
    virtual bool GetTrailInfo(VBF_TRAIL_INFO& trail)=0;

    // 获取航迹线的长度（单位：米）
    virtual double GetTrailLength()=0;

    // 选中并高亮显示航迹
    // 参数：bShowInfo -- 是否显示被选航迹的信息
    virtual void SelectTrail(bool bShowInfo=true)=0;

    // 清除模型的高亮状态
	virtual void ClearSelected()=0;

    // 高亮显示航迹的第n个点
    virtual void HighlightSelectedPoint(int nPointIndex)=0;


    // 设置航迹线的样式
    // 参数：bEnableFade -- 是否使用渐变
    //      fAlphaMin   -- 渐变时的最小透明度（最大透明度为函数style.color.a）
    virtual void SetLineStyle(const VBF_LINESTYLE& style, bool bEnableFade, float fAlphaMin=0.1f)=0;
    virtual void GetLineStyle(VBF_LINESTYLE& style, bool& bEnableFade, float& fAlphaMin)=0;


    // 设置航迹墙样式
    // 参数：bEnableWall -- 是否使用航迹墙
    //      fAlpha      -- 航迹墙的透明度
    virtual void SetWallStyle(bool bEnableWall, float fAlpha=0.6f)=0;
    virtual void GetWallStyle(bool& bEnableWall, float& fAlpha)=0;

    // 获取该航迹线上所有航迹点的时间段（即最早和最晚UTC时间)
	virtual void GetUTCRange(long& nUTCMin, long& nUTCMax)=0;

    // 设置/获取回放时是否显示对话框（默认为显示）
    virtual void SetReplayDialogVisible(bool bVisible)=0;
    virtual bool IsReplayDialogVisible()=0;

    // 航迹回放（指定的时间段必须在函数GetUTCRange()返回的范围内，注意：该函数只能在航迹加载完之后调用）
	// 参数：bLoop -- 是否循环回放
    virtual void ReplayStart(bool bLoop=false)=0;
    virtual void ReplayStart(long nUTCMin, long nUTCMax, bool bLoop=false)=0;
    virtual void ReplayPause()=0;
    virtual void ReplayContinue()=0;
    virtual void ReplayStop()=0;
    virtual void SetReplaySpeed(int nSpeed)=0;


	// 获取用户设置的回放参数
	virtual void GetReplayUTCRange(long& nUTCMin, long& nUTCMax)=0;
    virtual bool IsReplayLoop()=0;
    virtual int  GetReplaySpeed()=0;

	// 获取回放过程中的当前时间点
    virtual long GetReplayUTCCurr()=0;

	// 获取回放的当前状态
    virtual VBF_REPLAY_STATE GetReplayState()=0;

    // 设置/获取航迹的扩展信息是否由系统内部存储，默认为false（注意：该函数只能调用一次，而且必须在添加航迹之前调用)
    // 参数：bSave -- 是否需要将扩展信息保存在系统内部（如果为true，会占用大量内存；如果为false，需要通过外部模块提供扩展信息）
    virtual void SetExtInfoSaved(bool bSave)=0;
    virtual bool IsExtInfoSaved()=0;

    // 设置/获取航迹的扩展信息
    // 参数：bRequestFromExtern -- 如果内部未保存扩展信息，是否需要向外部发送请求
    virtual void SetExtInfo(const VBF_TRAIL_EXTINFO& info)=0;
    virtual bool GetExtInfo(VBF_TRAIL_EXTINFO& info, bool bRequestFromExtern)=0;

    // 响应用户界面中的消息
    virtual void OnInfoDialogClosed()=0;    // 响应航迹信息对话框关闭消息
    virtual void OnReplayDialogClosed()=0;  // 响应航迹回放对话框关闭消息

    // 获取当前选中的航迹点的编号
    virtual int GetSelectedPointIndex()=0;
};



#endif 
