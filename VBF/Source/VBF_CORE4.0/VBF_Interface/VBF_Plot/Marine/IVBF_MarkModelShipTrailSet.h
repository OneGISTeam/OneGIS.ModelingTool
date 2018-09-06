//************************************************************************
// FileName：IVBF_MarkModelShipTrailSet.h
// Function：军标实体模型接口：多条航迹的集合，用以解决海量航迹同时显示的问题
// Author:   杜莹
// Date:     2016-07-29
//************************************************************************

#ifndef __IVBF_MARK_MODEL_SHIPTRAIL_SET_H__
#define __IVBF_MARK_MODEL_SHIPTRAIL_SET_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Marine/VBF_3DPlotDataTypes_Marine.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Plot/Marine/VBF_TrailInfo.h>


// 定义消息ID号
const char VBF_MESSAGE_3DPLOT_SHIPTRAILSET_REQUESTED[]     = "Message: ShipTrailSet Requested";
const char VBF_MESSAGE_3DPLOT_SHIPTRAILSET_SELECTED[]      = "Message: ShipTrailSet Selected";        // 消息：航迹被选中了，nValue=1，pValue=VBF_TRAIL_EXTINFO*

const char VBF_MESSAGE_3DPLOT_SHIPTRAILSET_SHOWINFODIALOG[]     = "Message: ShipTrailSet ShowInfoDialog";      // 消息：需要显示航迹信息，nValue=1，pValue=osg::Vec2f*
const char VBF_MESSAGE_3DPLOT_SHIPTRAILSET_UPDATEINFODIALOG[]   = "Message: ShipTrailSet UpdateInfoDialog";     // 消息：需要更新航迹信息对话框
const char VBF_MESSAGE_3DPLOT_SHIPTRAILSET_CLOSEINFODIALOG[]    = "Message: ShipTrailSet CloseInfoDialog";     // 消息：需要关闭航迹信息对话框
const char VBF_MESSAGE_3DPLOT_SHIPTRAILSET_SHOWREPLAYDIALOG[]   = "Message: ShipTrailSet ShowReplayDialog";    // 消息：需要显示航迹回放对话框
const char VBF_MESSAGE_3DPLOT_SHIPTRAILSET_CLOSEREPLAYDIALOG[]  = "Message: ShipTrailSet CloseReplayDialog";   // 消息：需要关闭航迹回放对话框


//--------------------------------------------------------------
// 定义结构体：VBF_TRAILLOD
// 结构体描述：不同Lod的航迹信息
//--------------------------------------------------------------
typedef struct _tagVBFTrailLod
{
public:
    float           fDistMax;           // 该Lod开始出现的时机（即视线距离）
    float           fLineLengthMin;     // 航迹线长度大于等于值，属于该Lod
    osg::Vec4f      colorLine;          // 该Lod使用的线颜色

	_tagVBFTrailLod()
	{
		fDistMax		= 3e7;
		fLineLengthMin	= 1e5;
        colorLine		= osg::Vec4f(1.0, 0.0, 0.0, 1.0);
	}

	_tagVBFTrailLod& operator=(const _tagVBFTrailLod& src)
	{
		if(this==&src) return *this;

		fDistMax		= src.fDistMax;
		fLineLengthMin	= src.fLineLengthMin;
        colorLine		= src.colorLine;

		return *this;
	}

} VBF_TRAILLOD;



//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShipTrailSet
// 接口描述：航迹
//--------------------------------------------------------------------
class IVBF_MarkModelShipTrailSet : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelShipTrailSet() {}

	// 添加一条航迹，并返回该航迹在集合中的序号（从0开始）
    virtual int AddTrail(const VBF_TRAIL_INFO& trail)=0;

	// 获取航迹信息（前提是该航迹已经添加，如果索引号nIndex无效，返回false）
    virtual bool GetTrail(int nIndex, VBF_TRAIL_INFO& trail)=0;

	// 获取当前所选航迹线的长度（单位：米）
	virtual double GetSelectedTrailLength()=0;

    // 通过指定航迹的编码(nCode)或在集合中的序号(nIndex)，选中并高亮显示某条航迹
    // 参数：bShowInfo -- 是否显示被选航迹的信息
    // 返回：如果编码或序号错误，或者航迹目前不可见，返回false
    virtual bool SelectTrailByCode(int nCode, bool bShowInfo=true)=0;
    virtual bool SelectTrailByIndex(int nIndex, bool bShowInfo=true)=0;

	// 清除当前被选模型的高亮状态
	virtual void ClearSelected()=0;

	// 高亮显示当前所选航迹的第n个点
	virtual void HighlightSelectedPoint(int nPointIndex)=0;

	// 是否只显示当前所选的航迹（解决航迹过多导致混乱的问题）
	virtual void SetOnlySelectedVisible(bool bOnlySelected)=0;
	virtual bool IsOnlySelectedVisible()=0;

	// 初始化某个Lod级别的航迹信息（注意：该函数只能调用一次，而且必须在添加单个航迹之前调用)
	// 参数：nLod -- Lod级别，只能为0,1,2
	virtual void InitLodInfo(int nLod, const VBF_TRAILLOD& info)=0;
	virtual void GetLodInfo(int nLod, VBF_TRAILLOD& info)=0;

    // 初始化航迹线的样式（注意：该函数只能调用一次，而且必须在添加单个航迹之前调用)
    virtual void InitLineStyle(float fLineWidth, bool bEnableFade, float fAlphaMin=0.1f)=0;
    virtual void GetLineStyle(float& fLineWidth, bool& bEnableFade, float& fAlphaMin)=0;

    // 初始化航迹墙样式（注意：该函数只能调用一次，而且必须在添加单个航迹之前调用)
    virtual void InitWallStyle(bool bEnableWall, float fAlpha=0.6f)=0;
    virtual void GetWallStyle(bool& bEnableWall, float& fAlpha)=0;

	// 设置线宽（为提高绘制效率，所有Lod的航迹线使用相同的线宽）
	virtual void  SetLineWidth(float fWidth)=0;
	virtual float GetLineWidth()=0;

	// 获取所有航迹点的时间段（即最早和最晚UTC时间，注意：该函数只能在所有航迹加载完之后调用)
	virtual void GetUTCRange(long& nUTCMin, long& nUTCMax)=0;

    // 设置/获取回放时是否显示对话框（默认为显示）
    virtual void SetReplayDialogVisible(bool bVisible)=0;
    virtual bool IsReplayDialogVisible()=0;

	// 航迹回放（指定的时间段必须在函数GetUTCRange()返回的范围内，注意：该函数只能在所有航迹加载完之后调用）
	// 参数：bLoop -- 是否循环回放
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

    // 设置/获取某条航迹的扩展信息
    // 参数：bRequestFromExtern -- 如果内部未保存扩展信息，是否需要向外部发送请求
    virtual void SetExtInfo(int nIndex, const VBF_TRAIL_EXTINFO& info)=0;
    virtual bool GetExtInfo(int nIndex, VBF_TRAIL_EXTINFO& info, bool bRequestFromExtern)=0;

    // 获取当前被选航迹的扩展信息
    virtual const VBF_TRAIL_EXTINFO& GetSelTrailExtInfo()=0;

    // 响应用户界面中的消息
    virtual void OnInfoDialogClosed()=0;    // 响应航迹信息对话框关闭消息
    virtual void OnReplayDialogClosed()=0;  // 响应航迹回放对话框关闭消息

    // 获取当前选中的航迹点的编号
    virtual int GetSelectedPointIndex()=0;

    // 航迹点是否可见：需要与其对应的航迹线的可见性保持一致
    virtual bool IsPointVisible()=0;
};



#endif 
