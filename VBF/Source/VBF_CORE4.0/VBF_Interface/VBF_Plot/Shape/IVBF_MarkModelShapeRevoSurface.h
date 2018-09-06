//*******************************************************************
// FileName��IVBF_MarkModelShapeRevoSurface.h
// Function����״ʵ��ģ�ͣ��򵥻�ת�棨��ת�棺Revolution Surface���˴���дΪRevoSurface��
// Author:   ��Ө
// Date:     2013-11-07
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_REVOSURFACE_H__
#define __IVBF_MARK_MODEL_SHAPE_REVOSURFACE_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_REVOSURFACE_PART
// ö���������򵥻�ת��ĸ�������
//--------------------------------------------------------------------
enum EVBF_REVOSURFACE_PART
{
	VBF_REVOSURFACE_PART_BODY		= 0,	// ���壨�ɰ�������ת���ɣ������ڵ��ȵ���ǣ�
	VBF_REVOSURFACE_PART_TOP		= 1,	// �������ɶ���Բ�ĺͶ���Բ�ܵ��γɵ�ƽ�棩
	VBF_REVOSURFACE_PART_BOTTOM		= 2,	// �ײ����ɵײ�Բ�ĺ͵ײ�Բ�ܵ��γɵ�ƽ�棩
	VBF_REVOSURFACE_PART_LOBE		= 3,	// ���꣨����Բ����Բ�ܵ����Σ������ڵ��ȵ�ҶƬ��
	VBF_REVOSURFACE_PART_COUNT				// ����
};


//-----------------------------------------------------------------
// ����ṹ�壺VBF_ENVELOPE_DATA
// �ṹ����������ת��İ�������
//-----------------------------------------------------------------
struct VBF_ENVELOPE_DATA
{
    float	fAngle;		// ����ǣ���λ���Ƕȣ�
    float	fDist;		// ��ԭ��ľ��루��λ���ף�

    VBF_ENVELOPE_DATA()
    {
        fAngle = 0.0f;
        fDist  = 0.0f;
    }
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShapeRevoSurface
// �ӿ��������򵥻�ת��
//--------------------------------------------------------------------
class IVBF_MarkModelShapeRevoSurface : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeRevoSurface() {}

	// ����/��ȡ�����ļ�����������·���ͺ�׺��
	// ������bPolarCoord -- �����ļ��еĵ��Ƿ���ʹ�ü����꣨Ĭ��Ϊtrue��
	// ������bDistUnitKm -- �����ļ��о���ĵ�λ�Ƿ�Ϊ���Ĭ��Ϊtrue��
	virtual void SetConfigFileName(const std::string& strFileName, bool bPolarCoord=true, bool bDistUnitKm=true)=0;
	virtual void GetConfigFileName(std::string& strFileName, bool& bPolarCoord, bool& bDistUnitKm)=0;

	// ����/��ȡ�����ļ��ж��������˳���Ƿ�Ϊ��ʱ�루Ĭ��Ϊtrue��
	virtual void SetConfigPointsCCW(bool bCCW)=0;
	virtual bool IsConfigPointsCCW()=0;

    // ����/��ȡ��������
    virtual void SetEnvelopeData(const std::vector<VBF_ENVELOPE_DATA>& vData)=0;
    virtual const std::vector<VBF_ENVELOPE_DATA>& GetEnvelopeData()=0;

	// ����/��ȡ�����ˮƽ��ʼ�Ǻ���ֹ�ǣ�Ĭ��ֵ�ֱ�Ϊ0��, 360�ȣ�
	virtual void SetAngleH(float fAngleH0, float fAngleH1)=0;
	virtual void GetAngleH(float& fAngleH0, float& fAngleH1)=0;

	// ����/��ȡ����Բ�ָܷ�����Ĭ��ֵΪ60��
	virtual void SetNumSplit(int num)=0;
	virtual int  GetNumSplit()=0;

	// ��ȡ�������ļ��ж�ȡ��ˮƽ�������С/���뾶����λ���ף��û����Ը���������ֵ�������űȣ�
	virtual float GetRadiusMin()=0;
	virtual float GetRadiusMax()=0;

	// ����/��ȡ�û��Զ����ˮƽ��������뾶����λ���ף�ʵ�����ǵ���XY��������űȣ�
	virtual void  SetCustomRadiusMax(float fRadiusMax)=0;
	virtual float GetCustomRadiusMax()=0;

	// ����/��ȡ�����ɨ�跶Χ��Ĭ��Ϊ0��360�ȣ�
	virtual void SetLobeAngleRange(float fAngleMin, float fAngleMax)=0;
	virtual void GetLobeAngleRange(float& fAngleMin, float& fAngleMax)=0;

	// ����/��ȡ����ĽǶȼ��
	virtual void  SetLobeAngleInterval(float fAngle)=0;
	virtual float GetLobeAngleInterval()=0;

	// ����/��ȡ�Ƿ�������ɨ��
	virtual void EnableLobeScan(bool bEnable)=0;
	virtual bool IsLobeScanEnabled()=0;

	// ����/��ȡ����ɨ���ٶȣ���/�룬Ĭ��ֵΪ50.0��
	virtual void  SetLobeScanSpeed(float fScanSpeed)=0;
	virtual float GetLobeScanSpeed()=0;
};


#endif 
