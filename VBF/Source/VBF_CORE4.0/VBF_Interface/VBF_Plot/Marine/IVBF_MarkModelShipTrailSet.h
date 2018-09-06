//************************************************************************
// FileName��IVBF_MarkModelShipTrailSet.h
// Function������ʵ��ģ�ͽӿڣ����������ļ��ϣ����Խ����������ͬʱ��ʾ������
// Author:   ��Ө
// Date:     2016-07-29
//************************************************************************

#ifndef __IVBF_MARK_MODEL_SHIPTRAIL_SET_H__
#define __IVBF_MARK_MODEL_SHIPTRAIL_SET_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Marine/VBF_3DPlotDataTypes_Marine.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Plot/Marine/VBF_TrailInfo.h>


// ������ϢID��
const char VBF_MESSAGE_3DPLOT_SHIPTRAILSET_REQUESTED[]     = "Message: ShipTrailSet Requested";
const char VBF_MESSAGE_3DPLOT_SHIPTRAILSET_SELECTED[]      = "Message: ShipTrailSet Selected";        // ��Ϣ��������ѡ���ˣ�nValue=1��pValue=VBF_TRAIL_EXTINFO*

const char VBF_MESSAGE_3DPLOT_SHIPTRAILSET_SHOWINFODIALOG[]     = "Message: ShipTrailSet ShowInfoDialog";      // ��Ϣ����Ҫ��ʾ������Ϣ��nValue=1��pValue=osg::Vec2f*
const char VBF_MESSAGE_3DPLOT_SHIPTRAILSET_UPDATEINFODIALOG[]   = "Message: ShipTrailSet UpdateInfoDialog";     // ��Ϣ����Ҫ���º�����Ϣ�Ի���
const char VBF_MESSAGE_3DPLOT_SHIPTRAILSET_CLOSEINFODIALOG[]    = "Message: ShipTrailSet CloseInfoDialog";     // ��Ϣ����Ҫ�رպ�����Ϣ�Ի���
const char VBF_MESSAGE_3DPLOT_SHIPTRAILSET_SHOWREPLAYDIALOG[]   = "Message: ShipTrailSet ShowReplayDialog";    // ��Ϣ����Ҫ��ʾ�����طŶԻ���
const char VBF_MESSAGE_3DPLOT_SHIPTRAILSET_CLOSEREPLAYDIALOG[]  = "Message: ShipTrailSet CloseReplayDialog";   // ��Ϣ����Ҫ�رպ����طŶԻ���


//--------------------------------------------------------------
// ����ṹ�壺VBF_TRAILLOD
// �ṹ����������ͬLod�ĺ�����Ϣ
//--------------------------------------------------------------
typedef struct _tagVBFTrailLod
{
public:
    float           fDistMax;           // ��Lod��ʼ���ֵ�ʱ���������߾��룩
    float           fLineLengthMin;     // �����߳��ȴ��ڵ���ֵ�����ڸ�Lod
    osg::Vec4f      colorLine;          // ��Lodʹ�õ�����ɫ

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
// ����ӿڣ�IVBF_MarkModelShipTrailSet
// �ӿ�����������
//--------------------------------------------------------------------
class IVBF_MarkModelShipTrailSet : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelShipTrailSet() {}

	// ���һ�������������ظú����ڼ����е���ţ���0��ʼ��
    virtual int AddTrail(const VBF_TRAIL_INFO& trail)=0;

	// ��ȡ������Ϣ��ǰ���Ǹú����Ѿ���ӣ����������nIndex��Ч������false��
    virtual bool GetTrail(int nIndex, VBF_TRAIL_INFO& trail)=0;

	// ��ȡ��ǰ��ѡ�����ߵĳ��ȣ���λ���ף�
	virtual double GetSelectedTrailLength()=0;

    // ͨ��ָ�������ı���(nCode)���ڼ����е����(nIndex)��ѡ�в�������ʾĳ������
    // ������bShowInfo -- �Ƿ���ʾ��ѡ��������Ϣ
    // ���أ�����������Ŵ��󣬻��ߺ���Ŀǰ���ɼ�������false
    virtual bool SelectTrailByCode(int nCode, bool bShowInfo=true)=0;
    virtual bool SelectTrailByIndex(int nIndex, bool bShowInfo=true)=0;

	// �����ǰ��ѡģ�͵ĸ���״̬
	virtual void ClearSelected()=0;

	// ������ʾ��ǰ��ѡ�����ĵ�n����
	virtual void HighlightSelectedPoint(int nPointIndex)=0;

	// �Ƿ�ֻ��ʾ��ǰ��ѡ�ĺ���������������ർ�»��ҵ����⣩
	virtual void SetOnlySelectedVisible(bool bOnlySelected)=0;
	virtual bool IsOnlySelectedVisible()=0;

	// ��ʼ��ĳ��Lod����ĺ�����Ϣ��ע�⣺�ú���ֻ�ܵ���һ�Σ����ұ�������ӵ�������֮ǰ����)
	// ������nLod -- Lod����ֻ��Ϊ0,1,2
	virtual void InitLodInfo(int nLod, const VBF_TRAILLOD& info)=0;
	virtual void GetLodInfo(int nLod, VBF_TRAILLOD& info)=0;

    // ��ʼ�������ߵ���ʽ��ע�⣺�ú���ֻ�ܵ���һ�Σ����ұ�������ӵ�������֮ǰ����)
    virtual void InitLineStyle(float fLineWidth, bool bEnableFade, float fAlphaMin=0.1f)=0;
    virtual void GetLineStyle(float& fLineWidth, bool& bEnableFade, float& fAlphaMin)=0;

    // ��ʼ������ǽ��ʽ��ע�⣺�ú���ֻ�ܵ���һ�Σ����ұ�������ӵ�������֮ǰ����)
    virtual void InitWallStyle(bool bEnableWall, float fAlpha=0.6f)=0;
    virtual void GetWallStyle(bool& bEnableWall, float& fAlpha)=0;

	// �����߿�Ϊ��߻���Ч�ʣ�����Lod�ĺ�����ʹ����ͬ���߿�
	virtual void  SetLineWidth(float fWidth)=0;
	virtual float GetLineWidth()=0;

	// ��ȡ���к������ʱ��Σ������������UTCʱ�䣬ע�⣺�ú���ֻ�������к���������֮�����)
	virtual void GetUTCRange(long& nUTCMin, long& nUTCMax)=0;

    // ����/��ȡ�ط�ʱ�Ƿ���ʾ�Ի���Ĭ��Ϊ��ʾ��
    virtual void SetReplayDialogVisible(bool bVisible)=0;
    virtual bool IsReplayDialogVisible()=0;

	// �����طţ�ָ����ʱ��α����ں���GetUTCRange()���صķ�Χ�ڣ�ע�⣺�ú���ֻ�������к���������֮����ã�
	// ������bLoop -- �Ƿ�ѭ���ط�
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

    // ����/��ȡĳ����������չ��Ϣ
    // ������bRequestFromExtern -- ����ڲ�δ������չ��Ϣ���Ƿ���Ҫ���ⲿ��������
    virtual void SetExtInfo(int nIndex, const VBF_TRAIL_EXTINFO& info)=0;
    virtual bool GetExtInfo(int nIndex, VBF_TRAIL_EXTINFO& info, bool bRequestFromExtern)=0;

    // ��ȡ��ǰ��ѡ��������չ��Ϣ
    virtual const VBF_TRAIL_EXTINFO& GetSelTrailExtInfo()=0;

    // ��Ӧ�û������е���Ϣ
    virtual void OnInfoDialogClosed()=0;    // ��Ӧ������Ϣ�Ի���ر���Ϣ
    virtual void OnReplayDialogClosed()=0;  // ��Ӧ�����طŶԻ���ر���Ϣ

    // ��ȡ��ǰѡ�еĺ�����ı��
    virtual int GetSelectedPointIndex()=0;

    // �������Ƿ�ɼ�����Ҫ�����Ӧ�ĺ����ߵĿɼ��Ա���һ��
    virtual bool IsPointVisible()=0;
};



#endif 
