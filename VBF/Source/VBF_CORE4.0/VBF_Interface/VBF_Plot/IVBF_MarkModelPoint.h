//*******************************************************************
// FileName��IVBF_MarkModelPoint.h
// Function����״��ͼʵ��ģ�ͽӿ�
// Author:
// Date:     2009-4-1
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_POINT_H__
#define __IVBF_MARK_MODEL_POINT_H__


// ��Ҫʹ�õ�ͷ�ļ�
#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/Vec3d>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>



//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelPoint
// �ӿ���������״ʵ��ģ��
//--------------------------------------------------------------------
class IVBF_MarkModelPoint : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelPoint() {}

public:
	
	/** ����/��ȡ���űȣ�Ĭ��Ϊ1.0 */
	virtual void SetScale(float fScaleX, float fScaleY, float fScaleZ)=0;
	virtual void GetScale(float& fScaleX, float& fScaleY, float& fScaleZ)=0;

	/** ���ù̶����ش�С */
	virtual void  SetFixedSizeInPixels(float fFixedSize)=0;
	virtual float GetFixedSizeInPixels()=0;

	virtual void GetRealtimeScale(float& fScaleX, float& fScaleY, float& fScaleZ)=0;
	virtual void GetParentRealtimeScale(float& fScaleX, float& fScaleY, float& fScaleZ)=0;

	// ��ȡϵͳ�ڲ��Զ���������űȣ���ͳһ���š��Զ����ŵȣ�
	virtual void GetInnerScale(float& fScaleX, float& fScaleY, float& fScaleZ)=0;

	// ����/��ȡģ�͵���ת˳��Ĭ��ֵΪVBF_ROTATE_ORDER_ZXY��
	virtual void              SetRotateOrder(EVBF_ROTATE_ORDER nOrder)=0;
	virtual EVBF_ROTATE_ORDER GetRotateOrder()=0;

	/** 
    ����/��ȡģ������ϵ�µ���ת�ǣ�Ĭ��ֵ��Ϊ0.0
    �Ƕ�˵����x/y/z���α�ʾ������/������/�����(��λ���Ƕ�)����������ϵ�£�����������ԭ�㿴����ʱ��Ϊ��
	*/
	virtual void SetRotate(float fRotateX, float fRotateY, float fRotateZ)=0;
	virtual void GetRotate(float& fRotateX, float& fRotateY, float& fRotateZ)=0;

    /** ����/��ȡģ������ϵ�µĳ�ʼ��ת�ǣ�����У��ģ�͵Ľ�ģ����Ĭ��ֵ��Ϊ0.0��**/
    virtual void SetRotateInit(float fRotateX, float fRotateY, float fRotateZ)=0;
    virtual void GetRotateInit(float& fRotateX, float& fRotateY, float& fRotateZ)=0;

	// ��ȡ���и�ģ�͵���ת����
	virtual osg::Matrixd GetParentRotateMatrix()=0;

	/**  ����/��ȡģ������ϵ�µ�ƽ�ƣ�Ĭ��Ϊ0.0 */
	virtual void SetTrans(float fTransX, float fTransY, float fTransZ)=0;
	virtual void GetTrans(float& fTransX, float& fTransY, float& fTransZ)=0;

    /** ����/��ȡģ������ϵ�µĳ�ʼƽ�ƣ�����У��ģ�͵Ľ�ģԭ�㣬Ĭ��ֵ��Ϊ0.0��**/
    virtual void SetTransInit(float fTransX, float fTransY, float fTransZ)=0;
    virtual void GetTransInit(float& fTransX, float& fTransY, float& fTransZ)=0;
	
	// �Ƿ��������ù̶���С (��λ������)
	virtual void EnableFixedSizeInPixels(bool bEnable)=0;
	virtual bool IsFixedSizeInPixelsEnabled()=0;

	// �Ƿ������Զ�������С
	virtual void EnableAutoScale(bool bEnable)=0;
	virtual bool IsAutoScaleEnabled()=0;

	// �Ƿ�����ʵʱ�������ű� (���ܷ�ͨ���ȼ�ʵ��ͳһ����)
	virtual void EnableScaleDelta(bool bEnable)=0;
	virtual bool IsScaleDeltaEnabled()=0;

	// �Ƿ����õ���ƥ��
	virtual void EnableMatchTerrain(bool bEnable)=0;	
	virtual bool IsMatchTerrainEnabled()=0;

	// �Ƿ��游ģ����ת��Ĭ��Ϊtrue
	virtual void EnableRotateWithParent(bool bEnable)=0;
	virtual bool IsRotateWithParentEnabled()=0;

	// �Ƿ��游ģ�����ţ�Ĭ��Ϊtrue
	virtual void EnableScaleWithParent(bool bEnable)=0;
	virtual bool IsScaleWithParentEnabled()=0;

	// ��ȡģ������ϵ����������ϵ֮���ת������
	virtual osg::Matrixd GetModelToWorldMatrix()=0;
	virtual osg::Matrixd GetWorldToModelMatrix()=0;

	// �ѵ���������������ϵ�任��ģ������ϵ
	virtual osg::Vec3d PointWorldToModel(const osg::Vec3d& ptWorld)=0;

    // �����ģ��ԭ�㵽ģ����ĳ���������ģ������ϵ�£������Ľ��㣬���ؽ��㼰����ģ��ԭ��ľ��루��������ϵ�£�
    virtual bool Vector0ToPointInModelIntersectWithEarth(const osg::Vec3d& vPointInModel, double dHeightAdjust, osg::Vec3d& ptIntersect, double& dDist)=0;

	// ����ĳ������ģ������ϵ�£������Ľ��㣬���ؽ��㼰�����������ľ��루��������ϵ�£�
    virtual bool VectorInModelIntersectWithEarth(const osg::Vec3d& vPointInModelStart, const osg::Vec3d& vPointInModelEnd, double dHeightAdjust, osg::Vec3d& ptIntersect, double& dDist)=0;

	// �ж�ĳ�㣨��������ϵ�£��Ƿ���ģ�ͷ�Χ��
	virtual bool Contains(const osg::Vec3d& ptWorld)=0;
	virtual bool Contains(const osg::Vec3d& ptWorld, osg::Vec3d& ptModel, double& dDist)=0;

	/** ����ģ������ϵ���ۼӵ���ת��/���ű�/ƽ��ֵ���ڵ�ǰֵ�Ļ����ϣ� */
	virtual void SetDeltaRotate(float fDeltaRotateX, float fDeltaRotateY, float fDeltaRotateZ)=0;
	virtual void SetDeltaScale(float fDeltaScaleX, float fDeltaScaleY, float fDeltaScaleZ)=0;
	virtual void SetDeltaTrans(float fDeltaTransX, float fDeltaTransY, float fDeltaTransZ)=0;
    virtual void SetDeltaTransGeo(float fDeltaTransX, float fDeltaTransY, float fDeltaTransZ)=0;

	/** �ָ�ģ������ϵ��ģ�ͳ�ʼ״̬�������κ���ת��/���ű�/ƽ��ֵ */
	virtual void SetUnTransformed()=0;

	// ��ȡģ�ͱ������ת����
	virtual osg::Matrixd GetRotateMatrix()=0;

	/** �Ƿ�ֱ��ʹ���ⲿ���õ���ת����ģ������ϵ�£� */
	virtual void SetRotateMatrixOut(const osg::Matrixd& mat)=0;

	// ��ȡ��״ģ�͵ĸ�������ͼ�ڵ�
	virtual osg::IVBF_SGNodeGroupTransformMatrix* GetModelToWorldNode()=0;		// ��ȡģ�͵Ķ�λ�ڵ㣬��ģ������ϵ->��������ϵ
	virtual osg::IVBF_SGNodeGroupTransformMatrix* GetModelTransformNode()=0;	// ��ȡģ�͵ľֲ��任�ڵ�

	// ����/��ȡ����ʱ�䷽ʽ
	virtual void              SetSimTimeMode(EVBF_SIMTIME_MODE nMode)=0;
	virtual EVBF_SIMTIME_MODE GetSimTimeMode()=0;

	// ������ʽ�£�����/��ȡ����ʱ�䲽��������������������������֮���ʱ���� (ֻ�����ڶ������淽ʽ����λ����)
	virtual void  SetSimTimeStep(float fStep)=0;
	virtual float GetSimTimeStep()=0;

	/* ���þ���ģ�͵�ǰ��λ��(��������)����̬��ͬʱ������ͽǶȽ��в�ֵ
	   ������vGeoPos     -- ģ�͵�ǰ��λ��(��������)
			 fRotateX    -- ģ�͵�ǰ�Ĺ�ת�ǣ���ģ�ʹӳ�ʼ��״̬����X����ת�ĽǶȣ���ʱ��Ϊ�� (��λ���Ƕȣ�ֵ��Ϊ[-180, 180])
			 fRotateY    -- ģ�͵�ǰ�ĸ����ǣ���ģ�ʹӳ�ʼ��״̬����Y����ת�ĽǶȣ���ʱ��Ϊ�� (��λ���Ƕȣ�ֵ��Ϊ[-90, 90])
			 fRotateZ    -- ģ�͵�ǰ��ƫ���ǣ���ģ�ʹӳ�ʼ��״̬����Z����ת�ĽǶȣ���ʱ��Ϊ�� (��λ���Ƕȣ�ֵ��Ϊ[-180, 180])
             strInfo     -- ģ���ڸ�λ�ô�����Ϣ���Ա��ڹ켣���в�ѯ������Ϊ���ַ�����
	         ����ϵ˵������������ϵ������������ԭ�㿴����ʱ��Ϊ��
	*/
    virtual void StepGeoPos(const osg::Vec3d& vGeoPos, float fRotateX, float fRotateY, float fRotateZ, const std::string& strInfo="")=0;
    virtual void StopStepIn()=0; // ֹͣ����

    // ��ȡ����ģ���ڵ�ǰ֡�Ĺ켣����Ϣ������Ϣͨ��StepGeoPos()�������ã����ģ����δ��ʼ�˶�������false��
    virtual bool GetTrailPoint(VBF_TRAILPOINT& ptTrail)=0;

    // ����/��ȡģ�͵Ĺ۲�ģʽ
    virtual void            SetViewMode(EVBF_VIEW_MODE nMode)=0;
    virtual EVBF_VIEW_MODE  GetViewMode()=0;
};


#endif 
