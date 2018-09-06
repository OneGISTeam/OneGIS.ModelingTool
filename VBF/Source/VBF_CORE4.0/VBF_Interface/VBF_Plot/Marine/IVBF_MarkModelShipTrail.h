//************************************************************************
// FileName��IVBF_MarkModelShipTrail.h
// Function������ʵ��ģ�ͽӿڣ���������
// Author:   ��Ө
// Date:     2016-07-27
//************************************************************************

#ifndef __IVBF_MARK_MODEL_SHIPTRAIL_H__
#define __IVBF_MARK_MODEL_SHIPTRAIL_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Marine/VBF_3DPlotDataTypes_Marine.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Plot/Marine/VBF_TrailInfo.h>


// ������ϢID��
const char VBF_MESSAGE_3DPLOT_SHIPTRAIL_REQUESTED[]         = "Message: ShipTrail Requested";
const char VBF_MESSAGE_3DPLOT_SHIPTRAIL_SELECTED[]          = "Message: ShipTrail Selected";            // ��Ϣ��������ѡ���ˣ�nValue=1��pValue=VBF_TRAIL_EXTINFO*

const char VBF_MESSAGE_3DPLOT_SHIPTRAIL_SHOWINFODIALOG[]    = "Message: ShipTrail ShowInfoDialog";      // ��Ϣ����Ҫ��ʾ������Ϣ��nValue=1��pValue=osg::Vec2f*
const char VBF_MESSAGE_3DPLOT_SHIPTRAIL_UPDATEINFODIALOG[]  = "Message: ShipTrail UpdateInfoDialog";    // ��Ϣ����Ҫ���º�����Ϣ
const char VBF_MESSAGE_3DPLOT_SHIPTRAIL_CLOSEINFODIALOG[]   = "Message: ShipTrail CloseInfoDialog";     // ��Ϣ����Ҫ�رպ�����Ϣ�Ի���
const char VBF_MESSAGE_3DPLOT_SHIPTRAIL_SHOWREPLAYDIALOG[]  = "Message: ShipTrail ShowReplayDialog";    // ��Ϣ����Ҫ��ʾ�����طŶԻ���
const char VBF_MESSAGE_3DPLOT_SHIPTRAIL_CLOSEREPLAYDIALOG[] = "Message: ShipTrail CloseReplayDialog";   // ��Ϣ����Ҫ�رպ����طŶԻ���



//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShipTrail
// �ӿ���������������
//--------------------------------------------------------------------
class IVBF_MarkModelShipTrail : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelShipTrail() {}

    // ���ú�����Ϣ
    virtual void SetTrailInfo(const VBF_TRAIL_INFO& trail)=0;

    // ��ȡ������Ϣ�����������Ϣ��δ���ã�����false��
    virtual bool GetTrailInfo(VBF_TRAIL_INFO& trail)=0;

    // ��ȡ�����ߵĳ��ȣ���λ���ף�
    virtual double GetTrailLength()=0;

    // ѡ�в�������ʾ����
    // ������bShowInfo -- �Ƿ���ʾ��ѡ��������Ϣ
    virtual void SelectTrail(bool bShowInfo=true)=0;

    // ���ģ�͵ĸ���״̬
	virtual void ClearSelected()=0;

    // ������ʾ�����ĵ�n����
    virtual void HighlightSelectedPoint(int nPointIndex)=0;


    // ���ú����ߵ���ʽ
    // ������bEnableFade -- �Ƿ�ʹ�ý���
    //      fAlphaMin   -- ����ʱ����С͸���ȣ����͸����Ϊ����style.color.a��
    virtual void SetLineStyle(const VBF_LINESTYLE& style, bool bEnableFade, float fAlphaMin=0.1f)=0;
    virtual void GetLineStyle(VBF_LINESTYLE& style, bool& bEnableFade, float& fAlphaMin)=0;


    // ���ú���ǽ��ʽ
    // ������bEnableWall -- �Ƿ�ʹ�ú���ǽ
    //      fAlpha      -- ����ǽ��͸����
    virtual void SetWallStyle(bool bEnableWall, float fAlpha=0.6f)=0;
    virtual void GetWallStyle(bool& bEnableWall, float& fAlpha)=0;

    // ��ȡ�ú����������к������ʱ��Σ������������UTCʱ��)
	virtual void GetUTCRange(long& nUTCMin, long& nUTCMax)=0;

    // ����/��ȡ�ط�ʱ�Ƿ���ʾ�Ի���Ĭ��Ϊ��ʾ��
    virtual void SetReplayDialogVisible(bool bVisible)=0;
    virtual bool IsReplayDialogVisible()=0;

    // �����طţ�ָ����ʱ��α����ں���GetUTCRange()���صķ�Χ�ڣ�ע�⣺�ú���ֻ���ں���������֮����ã�
	// ������bLoop -- �Ƿ�ѭ���ط�
    virtual void ReplayStart(bool bLoop=false)=0;
    virtual void ReplayStart(long nUTCMin, long nUTCMax, bool bLoop=false)=0;
    virtual void ReplayPause()=0;
    virtual void ReplayContinue()=0;
    virtual void ReplayStop()=0;
    virtual void SetReplaySpeed(int nSpeed)=0;


	// ��ȡ�û����õĻطŲ���
	virtual void GetReplayUTCRange(long& nUTCMin, long& nUTCMax)=0;
    virtual bool IsReplayLoop()=0;
    virtual int  GetReplaySpeed()=0;

	// ��ȡ�طŹ����еĵ�ǰʱ���
    virtual long GetReplayUTCCurr()=0;

	// ��ȡ�طŵĵ�ǰ״̬
    virtual VBF_REPLAY_STATE GetReplayState()=0;

    // ����/��ȡ��������չ��Ϣ�Ƿ���ϵͳ�ڲ��洢��Ĭ��Ϊfalse��ע�⣺�ú���ֻ�ܵ���һ�Σ����ұ�������Ӻ���֮ǰ����)
    // ������bSave -- �Ƿ���Ҫ����չ��Ϣ������ϵͳ�ڲ������Ϊtrue����ռ�ô����ڴ棻���Ϊfalse����Ҫͨ���ⲿģ���ṩ��չ��Ϣ��
    virtual void SetExtInfoSaved(bool bSave)=0;
    virtual bool IsExtInfoSaved()=0;

    // ����/��ȡ��������չ��Ϣ
    // ������bRequestFromExtern -- ����ڲ�δ������չ��Ϣ���Ƿ���Ҫ���ⲿ��������
    virtual void SetExtInfo(const VBF_TRAIL_EXTINFO& info)=0;
    virtual bool GetExtInfo(VBF_TRAIL_EXTINFO& info, bool bRequestFromExtern)=0;

    // ��Ӧ�û������е���Ϣ
    virtual void OnInfoDialogClosed()=0;    // ��Ӧ������Ϣ�Ի���ر���Ϣ
    virtual void OnReplayDialogClosed()=0;  // ��Ӧ�����طŶԻ���ر���Ϣ

    // ��ȡ��ǰѡ�еĺ�����ı��
    virtual int GetSelectedPointIndex()=0;
};



#endif 
