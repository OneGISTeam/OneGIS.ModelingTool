//*******************************************************************
// FileName��VBF_MarkModelPointImpl.h
// Function����״��ͼʵ��ģ�ͽӿ�
// Author:
// Date:     2009-4-1
//*******************************************************************

#ifndef __VBF_MARK_MODEL_POINT_IMPL_H__
#define __VBF_MARK_MODEL_POINT_IMPL_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/VBF_MarkModelImpl.h>
#include <Types/VBF_Matrixd.h>
#include <VBF_Common/VBF_Math/VBF_Math.h>
#include <VBF_Common/VBF_Math/VBF_GisMath.h>
#include <VBF_Base/VBF_Timer.h>
#include <VBF_Plot/VBF_TrailPointInner.h>
#include <queue>
#include <VBF_Aux/VBF_GLAux/VBF_ReadWriteUtils.h>
#include <VBF_3DMap/VBF_Terrain/CullingUtils.h>
#include <VBF_3DMap/VBF_EarthUtil/ObjectLocator>

template<class T>
class CVBF_MarkModelPointImpl : public CVBF_MarkModelImpl<T>
{
public:
	CVBF_MarkModelPointImpl() {}
	CVBF_MarkModelPointImpl(const std::string& strMarkID);
	CVBF_MarkModelPointImpl(const CVBF_MarkModelPointImpl& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
	virtual ~CVBF_MarkModelPointImpl();
	
	// �ж��Ƿ�Ϊ��״ģ��
	virtual bool IsPointMarkModel() { return true; }

	// �޸ĳ�Ա����
	virtual void SetScale(float fScaleX, float fScaleY, float fScaleZ);
	virtual void GetScale(float& fScaleX, float& fScaleY, float& fScaleZ)	{ fScaleX = m_fScaleX; fScaleY = m_fScaleY; fScaleZ = m_fScaleZ; }

	virtual void  SetFixedSizeInPixels(float fFixedSize)	{ m_fFixedSizeInPixels = fFixedSize; DirtyMatrixModelScale(); }
	virtual float GetFixedSizeInPixels()					{ return m_fFixedSizeInPixels; }

	// ����/��ȡģ�͵���ת˳��Ĭ��ֵΪVBF_ROTATE_ORDER_ZXY��
	virtual void              SetRotateOrder(EVBF_ROTATE_ORDER nOrder);
	virtual EVBF_ROTATE_ORDER GetRotateOrder() { return m_nRotateOrder; }

	virtual void SetRotate(float fRotateX, float fRotateY, float fRotateZ);
	virtual void GetRotate(float& fRotateX, float& fRotateY, float& fRotateZ)	{ fRotateX = m_fRotateX; fRotateY = m_fRotateY; fRotateZ = m_fRotateZ; }

    virtual void SetRotateInit(float fRotateX, float fRotateY, float fRotateZ);
    virtual void GetRotateInit(float& fRotateX, float& fRotateY, float& fRotateZ)	{ fRotateX = m_fRotateInitX; fRotateY = m_fRotateInitY; fRotateZ = m_fRotateInitZ; }

	virtual void GetRealtimeScale(float& fScaleX, float& fScaleY, float& fScaleZ);
    virtual void GetParentRealtimeScale(float& fScaleX, float& fScaleY, float& fScaleZ);
	virtual osg::Matrixd GetParentRotateMatrix();

	// ��ȡϵͳ�ڲ��Զ���������űȣ���ͳһ���š��Զ����ŵȣ�
	virtual void GetInnerScale(float& fScaleX, float& fScaleY, float& fScaleZ);

    // ����/��ȡģ������ϵ�µ�ƽ�ƣ�Ĭ��Ϊ0.0
	virtual void SetTrans(float fTransX, float fTransY, float fTransZ);
	virtual void GetTrans(float& fTransX, float& fTransY, float& fTransZ) { fTransX = m_fTransX; fTransY = m_fTransY; fTransZ = m_fTransZ; }

    virtual void SetTransInit(float fTransX, float fTransY, float fTransZ);
    virtual void GetTransInit(float& fTransX, float& fTransY, float& fTransZ) { fTransX = m_fTransInitX; fTransY = m_fTransInitY; fTransZ = m_fTransInitZ; }

	// �Ƿ��������ù̶���С (��λ������)
	virtual void EnableFixedSizeInPixels(bool bEnable);
	virtual bool IsFixedSizeInPixelsEnabled()		{ return m_bEnableFixedSizeInPixels; }

	// �Ƿ������Զ�������С
	virtual void EnableAutoScale(bool bEnable)		{ m_bEnableAutoScale = bEnable; DirtyMatrixModelScale(); }
	virtual bool IsAutoScaleEnabled()				{ return m_bEnableAutoScale; }

	// �Ƿ�����ʵʱ�������ű� (���ܷ�ͨ���ȼ�ʵ��ͳһ����)
	virtual void EnableScaleDelta(bool bEnable)		{ m_bEnableScaleDelta = bEnable; DirtyMatrixModelScale(); }
	virtual bool IsScaleDeltaEnabled()				{ return m_bEnableScaleDelta; }

	// �Ƿ��游ģ����ת��Ĭ��Ϊtrue
	virtual void EnableRotateWithParent(bool bEnable);
	virtual bool IsRotateWithParentEnabled()	{ return m_bRotateWithParent; }

	// �Ƿ��游ģ�����ţ�Ĭ��Ϊtrue
	virtual void EnableScaleWithParent(bool bEnable);
	virtual bool IsScaleWithParentEnabled()		{ return m_bScaleWithParent; }

	// �Ƿ����õ���ƥ��
	virtual void EnableMatchTerrain(bool bEnable)	{ m_bEnableMatchTerrain = bEnable; }	
	virtual bool IsMatchTerrainEnabled()			{ return m_bEnableMatchTerrain; }

	// ��ȡģ������ϵ����������ϵ֮���ת������
	virtual osg::Matrixd GetModelToWorldMatrix();
	virtual osg::Matrixd GetWorldToModelMatrix();

	// �ѵ���������������ϵ�任��ģ������ϵ
	virtual osg::Vec3d PointWorldToModel(const osg::Vec3d& ptWorld);

    // �����ģ��ԭ�㵽ģ����ĳ���������ģ������ϵ�£������Ľ��㣬���ؽ��㼰����ģ��ԭ��ľ��루��������ϵ�£�
    virtual bool Vector0ToPointInModelIntersectWithEarth(const osg::Vec3d& vPointInModel, double dHeightAdjust, osg::Vec3d& ptIntersect, double& dDist);

	// ����ĳ������ģ������ϵ�£������Ľ��㣬���ؽ��㼰�����������ľ��루��������ϵ�£�
    virtual bool VectorInModelIntersectWithEarth(const osg::Vec3d& vPointInModelStart, const osg::Vec3d& vPointInModelEnd, double dHeightAdjust, osg::Vec3d& ptIntersect, double& dDist);

	// �ж�ĳ�㣨��������ϵ�£��Ƿ���ģ�ͷ�Χ��
	virtual bool Contains(const osg::Vec3d& ptWorld);
	virtual bool Contains(const osg::Vec3d& ptWorld, osg::Vec3d& ptModel, double& dDist) { return false; }

	// ����ģ������ϵ���ۼӵ���ת��/���ű�/ƽ��ֵ���ڵ�ǰֵ�Ļ����ϣ�
	virtual void SetDeltaRotate(float fDeltaRotateX, float fDeltaRotateY, float fDeltaRotateZ);
	virtual void SetDeltaScale(float fDeltaScaleX, float fDeltaScaleY, float fDeltaScaleZ);
	virtual void SetDeltaTrans(float fDeltaTransX, float fDeltaTransY, float fDeltaTransZ);
    virtual void SetDeltaTransGeo(float fDeltaTransX, float fDeltaTransY, float fDeltaTransZ);

	// �ָ�ģ������ϵ��ģ�ͳ�ʼ״̬�������κ���ת��/���ű�/ƽ��ֵ
	virtual void SetUnTransformed();

	// ��ȡģ�ͱ������ת����
	virtual osg::Matrixd GetRotateMatrix() { return m_matModelRotate; }

	// ֱ��ʹ���ⲿ���õ���ת����ģ������ϵ�£�
	virtual void SetRotateMatrixOut(const osg::Matrixd& mat);

	// ��ȡģ�͵ĸ�������ͼ�ڵ�
	virtual osg::IVBF_SGNodeGroupTransformMatrix* GetModelToWorldNode()		{ return m_piNodeModelToWorld.get(); }
	virtual osg::IVBF_SGNodeGroupTransformMatrix* GetModelTransformNode()	{ return m_piNodeTransformModel.get(); }

	virtual void SetParent(IVBF_MarkModel* pIParent);

	// ����/��ȡ����ʱ�䷽ʽ
	virtual void              SetSimTimeMode(EVBF_SIMTIME_MODE nMode) { m_nSimTimeMode = nMode; }
	virtual EVBF_SIMTIME_MODE GetSimTimeMode() { return m_nSimTimeMode; }

	// ������ʽ�£�����/��ȡ����ʱ�䲽��������������������������֮���ʱ���� (ֻ�����ڶ������淽ʽ����λ����)
	virtual void  SetSimTimeStep(float fStep)	{ m_fSimTimeStep = fStep; }
	virtual float GetSimTimeStep()				{ return m_fSimTimeStep; }

	// ����ģ�͵ĵ�������
    virtual void StepGeoPos(const osg::Vec3d& vGeo, float fRotateX, float fRotateY, float fRotateZ, const std::string& strInfo="");
    virtual void StopStepIn(); // ֹͣ����

    // ��ȡ����ģ���ڵ�ǰ֡�Ĺ켣����Ϣ������Ϣͨ��StepGeoPos()�������ã����ģ����δ��ʼ�˶�������false��
    virtual bool GetTrailPoint(VBF_TRAILPOINT& ptTrail);

    // ����/��ȡģ�͵Ĺ۲�ģʽ
    virtual void            SetViewMode(EVBF_VIEW_MODE nMode);
    virtual EVBF_VIEW_MODE  GetViewMode() { return m_nViewMode; }

    // ��ȡģ���ڸ�������ϵ�µİ�Χ��
    virtual const osg::BoundingBox&  GetBoundingBoxInWorld();
    virtual const osg::BoundingBoxd& GetBoundingBoxInGeo();

    // ��ȡģ�͵���������
    virtual const osg::Vec3d& GetWorldPos();

	// ִ��json�ű�
    virtual void ExecuteScript(const CVBF_Config& conf);

public:

	// ���� (ÿ֡����ǰ����)
	virtual bool Update();

protected:

	// ��ʼ��ģ�͵ĳ���ͼ
    virtual bool InitSG();

    // ����ĳЩ����ͼ�ڵ������
    virtual void UpdateSGNode();

	// ʹ�ֲ��任����ʧЧ
	void DirtyMatrixModelScale()	{ m_bDirtyMatrixModelScale  = true; m_bDirtyMatrixModel = true; }
	void DirtyMatrixModelRotate()	{ m_bDirtyMatrixModelRotate = true; m_bDirtyMatrixModel = true; }	
    void DirtyMatrixModelTrans()	{ m_bDirtyMatrixModelTrans  = true; m_bDirtyMatrixModel = true; CVBF_MarkModelImpl<T>::DirtyPosWorld(); }

	// ����ģ�͵ľֲ��任����
	virtual void Transform();
    virtual void TransformByViewMode();
	virtual void CalMatrixModel();
	virtual void CalMatrixModelScale();
	virtual void CalMatrixModelRotate();
	virtual void CalMatrixModelTrans();

    void MatrixMove(osg::Matrixd& matMove);

	// ����ģ�͵�λ��
	virtual void UpdatePos();

	// ������λ�ڵ㣨���Զ�λ/��Զ�λ��
	void CreateNodeLocator(bool bLocateRel);

    // ��������һ����ֵ��
    void StepIt();

    // ·����ֵ (ͬʱ���������ֵ�ͽǶȲ�ֵ)
    void Interpolate(int nNumInsert, const VBF_TRAILPOINTINNER& ptBegin, const VBF_TRAILPOINTINNER& ptEnd, bool bIncludingEnd);

    // ���ֵ�������׷��һ����
    void PushOnePoint(const VBF_TRAILPOINTINNER& point);

	// ���ݷ���ʱ�䲽����ʽ�����㵱ǰ��Ҫ��ֵ�ĵ���
    int GetNumInterPoints(const VBF_TRAILPOINTINNER& ptBegin, const VBF_TRAILPOINTINNER& ptEnd);

    // ������Χ�нڵ�
    virtual osg::IVBF_SGNode* CreateBoundingBoxNode();

    // �ж��Ƿ���Ҫ�ҽ�AutoTransform�ڵ�
    bool NeedAutoTransformNode();

    // ������Ĳü�
    virtual void ClipByEarth();

    // ���л�
    virtual bool WriteModelToXML(TiXmlElement* pElemMark);
    virtual bool ReadModelFromXML(TiXmlElement* pElemMark);

protected:
	float					m_fScaleX;					// X�����ϵ���������
	float					m_fScaleY;					// Y�����ϵ���������
    float					m_fScaleZ;					// Z�����ϵ���������
    float					m_fFixedSizeInPixels;		// �̶���С (��λ������)
	
	// ģ����ת (���ֲ������µ���ת����λ���Ƕ�)
	EVBF_ROTATE_ORDER		m_nRotateOrder;		// ��ת˳��
	float					m_fRotateX;
	float					m_fRotateY;
	float					m_fRotateZ;

	// ģ������ƽ�� (���ֲ������µ�ƽ�ƣ���λ����)
	float					m_fTransX;
	float					m_fTransY;
	float					m_fTransZ;

    // ģ�͵ĳ�ʼ��ת�ǣ�����У��ģ�͵Ľ�ģ���򣬵�λ���Ƕȣ�
    float					m_fRotateInitX;
    float					m_fRotateInitY;
    float					m_fRotateInitZ;

    // ģ�͵ĳ�ʼƽ�ƣ�����У��ģ�͵Ľ�ģԭ�㣩
    float					m_fTransInitX;
    float					m_fTransInitY;
    float					m_fTransInitZ;
	
	// ״̬����
	bool                    m_bEnableFixedSizeInPixels;	// �Ƿ��������ù̶���С
	bool                    m_bEnableAutoScale;			// �Ƿ������Զ�������С
	bool					m_bEnableScaleDelta;		// �Ƿ�����ʵʱ�������ű� (���ܷ�ͨ���ȼ�ʵ��ͳһ����)
	bool					m_bEnableMatchTerrain;		// �Ƿ��������ƥ��

	// �Ƿ��游ģ�ͱ任
	bool					m_bScaleWithParent;			// �Ƿ��游ģ������
	bool					m_bRotateWithParent;		// �Ƿ��游ģ����ת

	// �ֲ��任�����Ƿ��Ѿ�ʧЧ�����ʧЧ����Ҫ�ڻ���ǰ���¼���
	bool					m_bDirtyMatrixModel;
	bool					m_bDirtyMatrixModelScale;
	bool					m_bDirtyMatrixModelRotate;
	bool					m_bDirtyMatrixModelTrans;
	bool					m_bDirtyFixedSizeInPixels;

    // ��λ�ڵ��Ƿ�ʧЧ
    bool                    m_bDirtyNodeLocator;
    bool                    m_bLocateRelative;  // ���º�Ķ�λ��ʽ����Զ�λ/���Զ�λ

    // �Ƿ���Ҫ���/�Ƴ�AutoTransform�ڵ�
    bool                    m_bDirtyAutoTransformNode;

    // ģ�͵Ĺ۲췽ʽ
    EVBF_VIEW_MODE          m_nViewMode;
    bool                    m_bDirtyViewMode;   // �۲췽ʽ�Ƿ�ʧЧ

	// �ֲ��任����
	osg::Matrixd			m_matModelScale;
	osg::Matrixd			m_matModelRotate;
	osg::Matrixd			m_matModelTrans;
	osg::Matrixd			m_matModel;		// = m_matModelScale * m_matModelRotate * m_matModelTrans;

	// �Ƿ�ֱ��ʹ���ⲿ���õ���ת����ģ������ϵ�£�
	CVBF_Optional<osg::Matrixd>	m_matModelRotateOut;
	CVBF_Optional<osg::Matrixd>	m_matModelRotateOutForWrite;  // �������ڴ��л�

	// �볡��ͼ�йص�����
	ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix>		m_piNodeModelToWorld;	// ģ�͵ľ��Զ�λ�ڵ㣬���ģ������ϵ����������ϵ��ת�����ҽ���m_piNodeRoot�ڵ���
	ref_ptr<osg::IVBF_SGNodeGroupTransformAuto>			m_piNodeTransformAuto;	// ģ�͵��Զ��任�ڵ㣬��ʵ�̶ֹ����ش�С�Ͳ�����Ч�����ҽ��ھ��Զ�λ�ڵ��£���Ҫʱ�Źҽӣ�
	ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix>		m_piNodeTransformModel;	// ģ�͵ľֲ��任�ڵ㣬�ҽ����Զ��任�ڵ���

	// ������Ҫʹ�õ��ⲿ�ڵ�
	observer_ptr<osgEarth::Util::ObjectLocator>			m_piLocator;	// ���Զ�λʹ��

	// ���沽��������������������������֮���ʱ���� (��λ����)
    EVBF_SIMTIME_MODE                   m_nSimTimeMode;
    float                               m_fSimTimeStep;

    // ��·����ֵ�йص�����
    std::queue<VBF_TRAILPOINTINNER>         m_vKeyPoints;		// ���йؼ���
    std::queue<VBF_TRAILPOINTINNER>         m_vInterPoints;		// ���в�ֵ��
    CVBF_Optional<VBF_TRAILPOINTINNER>      m_TrailPoint;       // ģ���ڸ�֡�Ĺ켣����Ϣ
};

//-----------------------------------------------------------------------------
// ������CVBF_MarkModelPointImpl()
// ���������캯��
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModelPointImpl<T>::CVBF_MarkModelPointImpl(const std::string& strMarkID)
	: CVBF_MarkModelImpl<T>(strMarkID) 
{
	m_fScaleX				= 1.0f;			// X�����ϵ���������
    m_fScaleY				= 1.0f;			// Y�����ϵ���������
    m_fScaleZ				= 1.0f;			// Z�����ϵ���������
    m_fFixedSizeInPixels	= 50.0f;		// �̶���С (��λ������)

	m_nRotateOrder			= VBF_ROTATE_ORDER_ZXY;
	m_fRotateX				= 0.0f;			// ��X�����ת�Ƕ�(�Ƕ�)
	m_fRotateY				= 0.0f;			// ��Y�����ת�Ƕ�(�Ƕ�)
	m_fRotateZ				= 0.0f;			// ��Z�����ת�Ƕ�(�Ƕ�)

	m_fTransX				= 0.0f;	
	m_fTransY				= 0.0f;
	m_fTransZ				= 0.0f;

    // ģ�͵ĳ�ʼ��ת�ǣ�����У��ģ�͵Ľ�ģ����
    m_fRotateInitX			= 0.0f;
    m_fRotateInitY			= 0.0f;
    m_fRotateInitZ			= 0.0f;

    // ģ�͵ĳ�ʼƽ�ƣ�����У��ģ�͵Ľ�ģԭ�㣩
    m_fTransInitX			= 0.0f;
    m_fTransInitY			= 0.0f;
    m_fTransInitZ			= 0.0f;
	
	m_bEnableFixedSizeInPixels	= false;
	m_bEnableAutoScale			= false;
	m_bEnableScaleDelta			= true;
	m_bEnableMatchTerrain		= false;
	this->m_bEnableClipByEarth	= true;

	// �Ƿ��游ģ�ͱ任
	m_bScaleWithParent		= true;
	m_bRotateWithParent     = true;

	// �ֲ��任�����Ƿ��Ѿ�ʧЧ�����ʧЧ����Ҫ�ڻ���ǰ���¼���
	m_bDirtyMatrixModel		  = true;
	m_bDirtyMatrixModelScale  = true;
	m_bDirtyMatrixModelRotate = true;
	m_bDirtyMatrixModelTrans  = true;
	m_bDirtyFixedSizeInPixels = true;

    // ��λ�ڵ��Ƿ�ʧЧ
    m_bDirtyNodeLocator     = true;
    m_bLocateRelative       = false;  // ���º�Ķ�λ��ʽ����Զ�λ/���Զ�λ

	// ���沽��������������������������֮���ʱ���� (��λ����)
    m_nSimTimeMode          = VBF_SIMTIME_MODE_VARIABLE;
    m_fSimTimeStep          = 1.0f;

    // ģ�͵Ĺ۲췽ʽ
    m_nViewMode             = VBF_VIEW_MODE_NORMAL;
    m_bDirtyViewMode        = true;

    // �Ƿ���Ҫ���/�Ƴ�AutoTransform�ڵ�
    m_bDirtyAutoTransformNode = false;

    m_matModelScale.makeIdentity();
    m_matModelRotate.makeIdentity();
    m_matModelTrans.makeIdentity();
    m_matModel.makeIdentity();
}

//-----------------------------------------------------------------------------
// ������CVBF_MarkModelPointImpl()
// ��������������
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModelPointImpl<T>::~CVBF_MarkModelPointImpl()
{
}

//-----------------------------------------------------------------------------
// ������InitSG()
// ��������ʼ��ģ�͵ĳ���ͼ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::InitSG()
{
	// ����ģ�͵ĸ��ڵ㣬�ҽ���ͼ��ڵ���
    this->m_piNodeRoot = new osg::Switch;
    this->m_piNodeRoot->setName("VBFNode_MarkRoot: " + this->m_strID);
    this->m_piNodeRoot->setValue(0, this->m_bVisible);
    this->m_piNodeRoot->setUserValue("VBFMarkPtr", (TYPE_PTR)this);

	// ����ģ�͵ľ��Զ�λ�ڵ㣬�ҽ���m_piNodeRoot�ڵ���
	CreateNodeLocator(false);

	// ����ģ�͵��Զ��任�ڵ㣬�ҽ��ھ��Զ�λ�ڵ��£��Ա�ʵ�̶ֹ����ش�С��Ч������Ҫʱ�Źҽӣ�
	m_piNodeTransformAuto = new osg::AutoTransform;
    m_piNodeTransformAuto->setName("VBFNode_MarkAutoTransform: " + this->m_strID);
    m_piNodeTransformAuto->setAutoScaleToScreen(m_bEnableFixedSizeInPixels);  // ����Ϊtrueʱ���ڵ�̶����ش�С
    m_piNodeTransformAuto->setAutoRotateMode(osg::AutoTransform::NO_ROTATION);
    m_piNodeTransformAuto->setRotation(osg::Quat(0,0,0,1));
    m_piNodeTransformAuto->setPosition(osg::Vec3d(0,0,0));

	// ����ģ�͵ľֲ��任�ڵ㣬��Ϊ�Զ��任�ڵ���ӽڵ�
	m_piNodeTransformModel = new osg::MatrixTransform;
    m_piNodeTransformModel->setName("VBFNode_MarkModelTransform: " + this->m_strID);
	m_piNodeTransformModel->setReferenceFrame(osg::IVBF_SGNodeGroupTransform::RELATIVE_RF);
    m_piNodeTransformModel->setMatrix(osg::Matrix::identity());

	// ����ģ�͵�Group�ڵ㣬�ҽ���Lod�ڵ��£��û��Ľڵ���Ҫ�ҽ��ڸýڵ���
    this->m_piNodeGroup = ::VBF_CreateSGNodeGroup();
    this->m_piNodeGroup->setName("VBFNode_MarkGroup: " + this->m_strID);

    // ���ιҽ������ڵ�
    if( NeedAutoTransformNode() ) // ��Ҫ�ҽ�AutoTransform�ڵ�
    {
        this->m_piNodeRoot->addChild(m_piNodeModelToWorld);
        m_piNodeModelToWorld->addChild(m_piNodeTransformAuto);
        m_piNodeTransformAuto->addChild(m_piNodeTransformModel);
        m_piNodeTransformModel->addChild(this->m_piNodeGroup);
    }
    else  // ����Ҫ�ҽ�AutoTransform�ڵ�
    {
        this->m_piNodeRoot->addChild(m_piNodeModelToWorld);
        m_piNodeModelToWorld->addChild(m_piNodeTransformModel);
        m_piNodeTransformModel->addChild(this->m_piNodeGroup);
    }

	return true;
}

//-----------------------------------------------------------------------------
// ������CreateNodeLocator()
// ����������ģ�͵Ķ�λ�ڵ㣨���Զ�λ/��Զ�λ��
// ������bLocateRel -- �Ƿ�ʹ����Զ�λ
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::CreateNodeLocator(bool bLocateRel)
{ 
    ref_ptr<osg::MatrixTransform> ipNodeNew;

	// ���ʹ����Զ�λ��m_vPoeGeo���ٱ�ʾ�������꣬����ʾ��Ը�ģ�͵�ƫ����
	if(bLocateRel)
	{
		// ʹ���Զ�λʧЧ
		m_piLocator = NULL;

        ipNodeNew = new osg::MatrixTransform;
        ipNodeNew->setName("VBFNode_MarkLocatorRelative: " + this->m_strID);
        ipNodeNew->setMatrix( osg::Matrix::translate(this->m_vPosGeo) );
	}
	else  // û�и��ڵ㣬m_vPosGeo��ʾ��������
	{
//      piNodeNew = new osgEarth::Util::ObjectLocatorNode( this->m_opMapNode->GetMap() );
        ipNodeNew = new osgEarth::Util::ObjectLocatorNode( (CVBF_Map*)this->m_ipContext->GetMap() );
        ipNodeNew->setName("VBFNode_MarkLocatorAbsolute: " + this->m_strID);
        m_piLocator = (dynamic_cast<osgEarth::Util::ObjectLocatorNode*>(ipNodeNew.get()))->getLocator();
		if(m_piLocator.valid()) m_piLocator->setPosition(this->m_vPosGeo);
	}

	// ע�⣺����ԭ�еĸ��ڵ���ӽڵ�
	if( m_piNodeModelToWorld.valid() )
	{
        osg::IVBF_SGNode*      pNodeChild  = m_piNodeModelToWorld->getChild(0);
		osg::IVBF_SGNodeGroup* pNodeParent = m_piNodeModelToWorld->getParent(0);

        if(pNodeChild!=NULL)  ipNodeNew->addChild(pNodeChild);
        if(pNodeParent!=NULL) pNodeParent->replaceChild(m_piNodeModelToWorld.get(), ipNodeNew.get() );
	}

	// ���½ڵ��滻�ɽڵ�
    m_piNodeModelToWorld = ipNodeNew.release();
}

//----------------------------------------------------------------------------
// ������SetScale()
// ����������ģ������ϵ��
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetScale(float fScaleX, float fScaleY, float fScaleZ)
{ 
	m_fScaleX = fScaleX; 
	m_fScaleY = fScaleY; 
	m_fScaleZ = fScaleZ; 

	// ����ϵ������Ϊ��ֵ
	if( m_fScaleX < 0 ) m_fScaleX = 1.0f;
	if( m_fScaleY < 0 ) m_fScaleY = 1.0f;
	if( m_fScaleZ < 0 ) m_fScaleZ = 1.0f;

	DirtyMatrixModelScale();
}

//----------------------------------------------------------------------------
// ������SetRotateOrder()
// ����������ģ�͵���ת˳��Ĭ��ֵΪVBF_ROTATE_ORDER_ZXY��
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetRotateOrder(EVBF_ROTATE_ORDER nOrder)
{
	if(m_nRotateOrder != nOrder)
	{
		m_nRotateOrder = nOrder;
		DirtyMatrixModelRotate();
	}
}

//----------------------------------------------------------------------------
// ������SetRotate()
// ����������ģ����ת��
// ˵����x/y/z���α�ʾ������/������/�����(��λ���Ƕ�)����������ϵ�£�������������ԭ�㿴����ʱ��Ϊ��
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetRotate(float fRotateX, float fRotateY, float fRotateZ)	
{ 
	m_fRotateX	= fRotateX; 
	m_fRotateY	= fRotateY; 
	m_fRotateZ	= fRotateZ;

	DirtyMatrixModelRotate();
}

//-----------------------------------------------------------------------------
// ������SetRotateInit()
// ����������ģ������ϵ�µĳ�ʼ��ת������У��ģ�͵Ľ�ģ����
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetRotateInit(float fRotateX, float fRotateY, float fRotateZ)
{
    m_fRotateInitX	= fRotateX;
    m_fRotateInitY	= fRotateY;
    m_fRotateInitZ	= fRotateZ;

    DirtyMatrixModelRotate();
}

//----------------------------------------------------------------------------
// ������SetTrans()
// ����������ģ������ϵ�µ�ƽ��
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetTrans(float fTransX, float fTransY, float fTransZ)
{
	m_fTransX	= fTransX; 
	m_fTransY	= fTransY; 
	m_fTransZ	= fTransZ;

	DirtyMatrixModelTrans();
}

//----------------------------------------------------------------------------
// ������SetTransInit()
// ����������ģ������ϵ�µĳ�ʼƽ�ƣ�����У��ģ�͵Ľ�ģԭ�㣩
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetTransInit(float fTransX, float fTransY, float fTransZ)
{
    m_fTransInitX	= fTransX;
    m_fTransInitY	= fTransY;
    m_fTransInitZ	= fTransZ;

    DirtyMatrixModelTrans();
}

//----------------------------------------------------------------------------
// ������GetRealtimeScale()
// ��������ȡģ�͵�ʵʱ����ϵ��
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::GetRealtimeScale(float& fScaleX, float& fScaleY, float& fScaleZ)	
{ 
	float fInnerScaleX, fInnerScaleY, fInnerScaleZ;
	GetInnerScale(fInnerScaleX, fInnerScaleY, fInnerScaleZ);

	fScaleX = m_fScaleX * fInnerScaleX;
	fScaleY = m_fScaleY * fInnerScaleY;
	fScaleZ = m_fScaleZ * fInnerScaleZ;
}

//----------------------------------------------------------------------------
// ������GetInnerScale()
// ��������ȡϵͳ�ڲ��Զ���������űȣ���ͳһ���š��Զ����ŵȣ�
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::GetInnerScale(float& fScaleX, float& fScaleY, float& fScaleZ)
{
	CVBF_3DEnvironment& env = VBF_Get3DEnvironment();
	IVBF_3DPlot* pI3DPlot = env.m_pI3DPlot;

	fScaleX = 1.0f;					
	fScaleY = 1.0f;				
	fScaleZ = 1.0f;

	if(m_bEnableFixedSizeInPixels)
	{ 
        fScaleX = m_fFixedSizeInPixels;
        fScaleY = m_fFixedSizeInPixels;
        fScaleZ = m_fFixedSizeInPixels;

        const osg::BoundingBox& box = this->GetBoundingBoxInModel();
		float fBoxSizeX = box.xMax()- box.xMin();
		float fBoxSizeY = box.yMax()- box.yMin();
		float fBoxSizeZ = box.zMax()- box.zMin();

		if(fBoxSizeX > 0.0f) fScaleX /= fBoxSizeX;
        if(fBoxSizeY > 0.0f) fScaleY /= fBoxSizeX;
        if(fBoxSizeZ > 0.0f) fScaleZ /= fBoxSizeX;
	}
	else if(m_bEnableAutoScale)
	{ 
        if(this->m_pIParent!=NULL)
		{
			fScaleX = 1.0;
			fScaleY = 1.0;
			fScaleZ = 1.0;
		}
		else
		{
			float fAutoScale = (pI3DPlot!=NULL)? pI3DPlot->GetPointMarkAutoScale() : 1.0f;
			fScaleX = fAutoScale;
			fScaleY = fAutoScale;
			fScaleZ = fAutoScale;
		}
	}
	
	// ע�⣺�������űȵĵ���ϵ��
    if(m_bEnableScaleDelta && (NULL==this->m_pIParent || !this->m_pIParent->IsPointMarkModel()))
	{ 
		float fScaleDelta = (pI3DPlot!=NULL)? pI3DPlot->GetPointMarkScaleDelta() : 1.0f;
		fScaleX *= fScaleDelta;
		fScaleY *= fScaleDelta;
		fScaleZ *= fScaleDelta;
	}
}

/****
//----------------------------------------------------------------------------
// ������GetParentRealtimeScale()
// ��������ȡ��ģ�͵�ʵʱ����ϵ��
//----------------------------------------------------------------------------
template<class T> 
void CVBF_MarkModelPointImpl<T>::GetParentRealtimeScale(float& fScaleX, float& fScaleY, float& fScaleZ)
{
	if( NULL==m_pIParent || !m_pIParent->IsPointMarkModel() ) 
	{
		fScaleX = 1.0;
		fScaleY = 1.0;
		fScaleZ = 1.0;
		return;
	}

	IVBF_MarkModelPoint* pIParentPoint = (IVBF_MarkModelPoint*)m_pIParent;

	float fScaleX0 = 1.0, fScaleY0 = 1.0, fScaleZ0 = 1.0;
	pIParentPoint->GetRealtimeScale(fScaleX0, fScaleY0, fScaleZ0);

	float fScaleX1 = 1.0, fScaleY1 = 1.0, fScaleZ1 = 1.0;
//	pIParentPoint->GetParentRealtimeScale(fScaleX1, fScaleY1, fScaleZ1);  // ��Ҫ�𣿣���Ө�޸ģ�2013-11-25��

	fScaleX = fScaleX0 * fScaleX1;
	fScaleY = fScaleY0 * fScaleY1;
	fScaleZ = fScaleZ0 * fScaleZ1;
}
***/

//----------------------------------------------------------------------------
// ������GetParentRealtimeScale()
// ��������ȡ��ģ�͵�ʵʱ����ϵ��
//----------------------------------------------------------------------------
template<class T> 
void CVBF_MarkModelPointImpl<T>::GetParentRealtimeScale(float& fScaleX, float& fScaleY, float& fScaleZ)
{
	fScaleX = 1.0f;
	fScaleY = 1.0f;
	fScaleZ = 1.0f;

    if( NULL==this->m_pIParent || !this->m_pIParent->IsPointMarkModel() )
	{
		return;
	}

	IVBF_MarkModel* pIMark   = this;
	IVBF_MarkModel* pIParent = pIMark->GetParent();

	while(pIParent!=NULL)
	{
		if(pIMark->IsPointMarkModel() && pIParent->IsPointMarkModel())
		{
			IVBF_MarkModelPoint* pIMarkPoint   = (IVBF_MarkModelPoint*)pIMark;
			IVBF_MarkModelPoint* pIParentPoint = (IVBF_MarkModelPoint*)pIParent;

			if(pIMarkPoint->IsScaleWithParentEnabled() && !pIMarkPoint->IsRotateWithParentEnabled())
			{
				float fScaleX0, fScaleY0, fScaleZ0;
				pIParentPoint->GetScale(fScaleX0, fScaleY0, fScaleZ0);

				fScaleX *= fScaleX0;
				fScaleY *= fScaleY0;
				fScaleZ *= fScaleZ0;
			}
		}

		// �ٻ�ȡ��һ�����ڵ�
		pIMark   = pIParent;
		pIParent = pIMark->GetParent();
	}
}

//----------------------------------------------------------------------------
// ������GetParentRealtimeScale()
// ��������ȡ���и�ģ�͵���ת����
//----------------------------------------------------------------------------
template<class T> 
osg::Matrixd CVBF_MarkModelPointImpl<T>::GetParentRotateMatrix()
{
	osg::Matrixd matRotate;
	matRotate.makeIdentity();

    if( NULL==this->m_pIParent || !this->m_pIParent->IsPointMarkModel() )
	{
		return matRotate;
	}

	IVBF_MarkModel* pIMark   = this;
	IVBF_MarkModel* pIParent = pIMark->GetParent();

	while(pIParent!=NULL)
	{
		if(pIMark->IsPointMarkModel() && pIParent->IsPointMarkModel())
		{
			IVBF_MarkModelPoint* pIMarkPoint   = (IVBF_MarkModelPoint*)pIMark;
			IVBF_MarkModelPoint* pIParentPoint = (IVBF_MarkModelPoint*)pIParent;

			if(pIMarkPoint->IsRotateWithParentEnabled() && !pIMarkPoint->IsScaleWithParentEnabled())
			{
				matRotate *= pIParentPoint->GetRotateMatrix();
			}
		}

		// �ٻ�ȡ��һ�����ڵ�
		pIMark   = pIParent;
		pIParent = pIMark->GetParent();
	}

	return matRotate;
}

//-----------------------------------------------------------------------------
// ������UpdatePos()
// ����������ģ�͵�λ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::UpdatePos()
{
    if(m_bDirtyNodeLocator)
    {
        CreateNodeLocator(m_bLocateRelative);
        m_bDirtyNodeLocator = false;
    }

    if(this->m_bDirtyPosGeo)
    {
        if(this->m_pIParent!=NULL && this->m_pIParent->IsPointMarkModel())  // �е�״��ģ�ͣ����������ʾ��Զ�λ
        {
            if(m_piNodeModelToWorld.valid()) m_piNodeModelToWorld->setMatrix( osg::Matrix::translate(this->m_vPosGeo) );
        }
        else  // û�и�ģ�ͻ�ģ�Ͳ��ǵ�״�����������ʾ���Զ�λ
        {
            if(m_piLocator.valid()) m_piLocator->setPosition(this->m_vPosGeo);

            // ʹ��λ�ڵ���m_piLocator������ͬ��
            osgEarth::Util::ObjectLocatorNode* pLocatorNode = dynamic_cast<osgEarth::Util::ObjectLocatorNode*>(m_piNodeModelToWorld.get());
            if(pLocatorNode) pLocatorNode->update();
        }

        this->m_bDirtyPosGeo = false;
    }
}


//-----------------------------------------------------------------------------
// ������Update()
// ���������� (ÿ֡����ǰ����)
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::Update()
{	
    // ��ӵ�����ͼ�ĸ��ڵ�
    this->AddToParentNode();

    // ����ĳЩ����ͼ�ڵ������
    UpdateSGNode();

    if(!this->m_bVisible) return false;

	// ����ģ�ͽڵ�
    if(this->m_bDirtyModel)
	{
        this->UpdateModelNode();
        this->m_bDirtyModel = false;
    }
	
	// ��������һ����ֵ��
	StepIt();

	// ������õ��θ��棬��Ҫʵʱ����߳�ֵ
    if( NULL==this->m_pIParent && m_bEnableMatchTerrain )
	{
        osg::Vec3d vGeo = this->m_vPosGeo;
        if( this->m_ipContext->GetElevationAvail(this->m_opCamera.get(),vGeo.x(), vGeo.y(), vGeo.z()) )
        {
			vGeo.z() += 0.1;  // ΢�����������
            this->SetGeoPos(vGeo);
		}
	}

	// ����ģ�͵�λ��
	UpdatePos();

	// ����任
	Transform();

	// �����ӵ㵽ģ�͵ľ��룬�ж�ģ��/�����Ƿ��ڿɼ�������
	this->ClipByDist();

	// ������Ĳü�
	ClipByEarth();

	// ����������ģ�� 
    this->UpdateChildren();

    // �����������ԣ�������Ҫ��Transform()����֮����£�
    this->UpdateAttrs();

    // ���°�Χ�нڵ�
    if(this->m_bDirtyBoundingBoxNode)
	{
		this->UpdateBoundingBox();
        this->m_bDirtyBoundingBoxNode = false;
	}

	// ������Ⱦ״̬
    if(this->m_bDirtyStateSet)
	{
        this->SetStateSet();
        this->m_bDirtyStateSet = false;
	}

    // ģ�Ͷ���/��Ч
    this->UpdateByActions();
    this->UpdateByEffects();

	return true;
}

//-----------------------------------------------------------------------------
// ������NeedAutoTransformNode()
// �������ж��Ƿ���Ҫ�ҽ�AutoTransform�ڵ�
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::NeedAutoTransformNode()
{
	bool bNeed = (m_bEnableFixedSizeInPixels ||
				 (m_nViewMode!=VBF_VIEW_MODE_NORMAL && m_nViewMode!=VBF_VIEW_MODE_HORIZON));

	return bNeed;
}

//-----------------------------------------------------------------------------
// ������UpdateSGNode()
// ����������ĳЩ����ͼ�ڵ������
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::UpdateSGNode()
{
    CVBF_MarkModelImpl<T>::UpdateSGNode();

    // ˵���������Ҫ���AutoTransform�ڵ㣬�ҽ�˳��Ϊ��
/*  m_piNodeRoot->addChild(m_piNodeModelToWorld);
    m_piNodeModelToWorld->addChild(m_piNodeTransformAuto);
    m_piNodeTransformAuto->addChild(m_piNodeTransformModel);
    m_piNodeTransformModel->addChild(m_piNodeGroup);
*/
    // �Ƿ���Ҫ���/�Ƴ�AutoTransform�ڵ�
    if(m_bDirtyAutoTransformNode && m_piNodeTransformAuto.valid() && m_piNodeModelToWorld.valid() && m_piNodeTransformModel.valid())
    {
        // �ж�ԭ���Ƿ��и��ڵ�
        bool bHadParent = (m_piNodeTransformAuto->getNumParents()>0);

        // �жϱ����Ƿ���Ҫ�ҽ�AutoTransform�ڵ�
        bool bNeedNow = NeedAutoTransformNode();

        // ԭ��û�и��ڵ㣬������Ҫ��˵����Ҫ�ҽ�AutoTransform�ڵ�
        if(!bHadParent && bNeedNow)
        {
            m_piNodeTransformAuto->addChild(m_piNodeTransformModel);
            m_piNodeModelToWorld->replaceChild(m_piNodeTransformModel, m_piNodeTransformAuto);

            // ע�⣺�ָ��ڵ�ĳ�ʼ״̬
            m_piNodeTransformAuto->setAutoScaleToScreen(m_bEnableFixedSizeInPixels);  // ����Ϊtrueʱ���ڵ�̶����ش�С
            m_piNodeTransformAuto->setAutoRotateMode(osg::AutoTransform::NO_ROTATION);
            m_piNodeTransformAuto->setRotation(osg::Quat(0,0,0,1));
        }
        else if(bHadParent && !bNeedNow) // ԭ���Ѿ��и��ڵ㣬˵����Ҫ�Ƴ�AutoTransform�ڵ�
        {
            m_piNodeModelToWorld->replaceChild(m_piNodeTransformAuto, m_piNodeTransformModel);
            m_piNodeTransformAuto->removeChildren(0, m_piNodeTransformAuto->getNumChildren());
        }

        m_bDirtyAutoTransformNode = false;
    }
}

//-----------------------------------------------------------------------------
// ������Transform()
// ����������任��ÿ֡����ǰ���ã�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::Transform()
{
	// �ж��Ƿ��游ģ�ͱ任
	bool bWithParent = true;

	// ��ģ���ǵ�״ģ��
    if( this->m_pIParent!=NULL && this->m_pIParent->IsPointMarkModel() )
	{
		bWithParent = (m_bScaleWithParent && m_bRotateWithParent);
		
		// �游ģ�ͱ任��  ��Ҫ����ģ�͵ĸ��ڵ�ҽӵ���ģ�͵�Group�ڵ��£���m_piNodeGroup�ڵ���
		// ���游ģ�ͱ任����Ҫ����ģ�͵ĸ��ڵ�ҽӵ���ģ�͵Ķ�λ�ڵ��£���m_piNodeModelToWorld�ڵ���
        if(this->m_piNodeRoot.valid())
		{
            IVBF_MarkModelPoint* pIParentPoint = (IVBF_MarkModelPoint*)this->m_pIParent;

            osg::IVBF_SGNodeGroup* pParentOld = dynamic_cast<osg::IVBF_SGNodeGroup*>(this->m_piNodeRoot->getParent(0));
			osg::IVBF_SGNodeGroup* pParentNew = (bWithParent)? pIParentPoint->GetGroupNode() : pIParentPoint->GetModelToWorldNode();
			if(pParentOld!=pParentNew)
			{
				this->SetParentNode(pParentNew);
				this->AddToParentNode();
			}
		}
	}

	// �游ģ�ͱ任
	if(bWithParent)
	{
		CalMatrixModel();
	}
	else // ���游ģ�ͱ任
	{
		CalMatrixModelScale();
		CalMatrixModelRotate();
		CalMatrixModelTrans();

		osg::Matrixd matScale = m_matModelScale;
		if(m_bScaleWithParent)
		{
			float fScaleX, fScaleY, fScaleZ;
			GetParentRealtimeScale(fScaleX, fScaleY, fScaleZ);
			
			matScale(0,0) *= fScaleX;
			matScale(1,1) *= fScaleY;
			matScale(2,2) *= fScaleZ;
		}

		osg::Matrixd matRotateWithParent;
		matRotateWithParent.makeIdentity();
		if(m_bRotateWithParent)
		{
			matRotateWithParent = GetParentRotateMatrix();
		}

		// ����ڸ�ģ�͵�ƽ��
		osg::Matrixd matMove;
		MatrixMove(matMove);

		// ��λ�ڵ㲻������
		m_piNodeModelToWorld->setMatrix(osg::Matrix::identity());

		// ע�⣺������˵�˳��!
		osg::Matrixd matLocal = matScale * m_matModelRotate * m_matModelTrans * matMove * matRotateWithParent; 
		m_piNodeTransformModel->setMatrix(matLocal);
	}

    // ͨ���Զ��仯����ʵ�ֲ�ͬ�Ĺ۲췽ʽ
    TransformByViewMode();
}

//-----------------------------------------------------------------------------
// ������TransformByViewMode()
// ������ͨ���Զ��任����ʵ�ֲ�ͬ�Ĺ۲췽ʽ
// ˵�����ú���Ҫ��ģ�͵ĳ�ʼ��̬��ƽ���ڵ���ģ���ģ������ϵ��z�ᴹֱ�ڵ���
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::TransformByViewMode()
{
    // ��Ҫ���þ���任ʵ�ָ�����ʾģʽ
    if(!m_piNodeTransformAuto.valid()) return;

    // ����Ϊtrueʱ���ڵ�̶����ش�С
    if(m_bDirtyFixedSizeInPixels)
    {
        m_piNodeTransformAuto->setAutoScaleToScreen(m_bEnableFixedSizeInPixels);
        m_bDirtyFixedSizeInPixels = false;
    }

    // ��������ģʽ�£�ÿ֡����Ҫ�任����
    if(m_nViewMode==VBF_VIEW_MODE_BILLBOARD_H || m_nViewMode==VBF_VIEW_MODE_BILLBOARD_V)
    {

        // ��ȡ�ӵ�ķ�λ��
        IVBF_GlobalDataPerView* pData = VBF_Get3DGlobalData(this->m_opView.get());
        double dAngleH = - pData->GetAngleH();

        osg::Quat quat(0, 0, 0, 1);

        if(m_nViewMode==VBF_VIEW_MODE_BILLBOARD_H)		// ˮƽ������
        {
            quat.makeRotate(osg::inDegrees(dAngleH), 0.0, 0.0f, 1.0f);
        }
        else if(m_nViewMode==VBF_VIEW_MODE_BILLBOARD_V)	// ��ֱ������
        {
            osg::Quat quatX, quatZ;
            quatX.makeRotate(osg::inDegrees(90.0),    1.0, 0.0, 0.0);	// ����X����ת90��
            quatZ.makeRotate(osg::inDegrees(dAngleH), 0.0, 0.0, 1.0);	// ����Z����תdAngleH
            quat = quatX * quatZ;
        }

        m_piNodeTransformAuto->setAutoRotateMode(osg::AutoTransform::NO_ROTATION);
        m_piNodeTransformAuto->setRotation(quat);
        return;
    }

    if(m_bDirtyViewMode)
    {
        // ��ȫ�����ƣ�����Ҫÿ֡���任����
        if(m_nViewMode==VBF_VIEW_MODE_BILLBOARD_HV)
        {
            m_piNodeTransformAuto->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
            m_piNodeTransformAuto->setRotation(osg::Quat(0,0,0,1));
        }

        m_bDirtyViewMode = false;
    }
}

//-----------------------------------------------------------------------------
// ������CalMatrixModel()
// ���������¼���ģ������ϵ�µı任����
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::CalMatrixModel()
{
	CalMatrixModelScale();
	CalMatrixModelRotate();
	CalMatrixModelTrans();

	// ���¼���ֲ��任����
	if(m_bDirtyMatrixModel)
	{
		m_matModel = m_matModelScale * m_matModelRotate * m_matModelTrans;
		if(m_piNodeTransformModel.valid()) m_piNodeTransformModel->setMatrix( m_matModel );

		// ���¼����Χ��
        this->DirtyBoundingBoxInModel();
        this->DirtyBoundingBoxInWorld();

		m_bDirtyMatrixModel = false;
	}
}

//-----------------------------------------------------------------------------
// ������CalMatrixModelScale()
// ���������¼���ģ������ϵ�µ����ž���
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::CalMatrixModelScale()
{
	if(m_bDirtyMatrixModelScale)
	{
		float fScaleX, fScaleY, fScaleZ;
		GetRealtimeScale(fScaleX, fScaleY, fScaleZ);

		m_matModelScale = osg::Matrix::scale(fScaleX, fScaleY, fScaleZ);

		m_bDirtyMatrixModelScale = false;
	}
}

//-----------------------------------------------------------------------------
// ������CalMatrixModelRotate()
// ���������¼���ģ������ϵ�µ���ת����
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::CalMatrixModelRotate()
{
	if(!m_bDirtyMatrixModelRotate) return;
	
	if(m_matModelRotateOut.isSet()) // ֱ��ʹ���ⲿ���õ���ת����ģ������ϵ�£�
	{
		m_matModelRotate = m_matModelRotateOut.value();
		m_matModelRotateOut.unset();
	}
	else
	{
		float fRotateZ = osg::DegreesToRadians( m_fRotateZ + m_fRotateInitZ );  // �� -> ����

		// ע�⣺���ģ��ʼ��ƽ���ڵ��棬ֻ��������Z����ת
		if(m_nViewMode==VBF_VIEW_MODE_HORIZON)
		{
			m_matModelRotate = osg::Matrix::rotate( fRotateZ, osg::Vec3f(0,0,1) );
		}
		else
		{
			float fRotateX = osg::DegreesToRadians( m_fRotateX + m_fRotateInitX );  // �� -> ����
			float fRotateY = osg::DegreesToRadians( m_fRotateY + m_fRotateInitY );

			osg::Vec3f vAxisX(1, 0, 0);
			osg::Vec3f vAxisY(0, 1, 0);
			osg::Vec3f vAxisZ(0, 0, 1);

			switch(m_nRotateOrder)
			{
				case VBF_ROTATE_ORDER_XYZ:  { m_matModelRotate = osg::Matrix::rotate( fRotateX, vAxisX, fRotateY, vAxisY, fRotateZ, vAxisZ ); break; }
				case VBF_ROTATE_ORDER_XZY:  { m_matModelRotate = osg::Matrix::rotate( fRotateX, vAxisX, fRotateZ, vAxisZ, fRotateY, vAxisY ); break; }
				case VBF_ROTATE_ORDER_YXZ:  { m_matModelRotate = osg::Matrix::rotate( fRotateY, vAxisY, fRotateX, vAxisX, fRotateZ, vAxisZ ); break; }
				case VBF_ROTATE_ORDER_YZX:  { m_matModelRotate = osg::Matrix::rotate( fRotateY, vAxisY, fRotateZ, vAxisZ, fRotateX, vAxisX ); break; }
				case VBF_ROTATE_ORDER_ZXY:  { m_matModelRotate = osg::Matrix::rotate( fRotateZ, vAxisZ, fRotateX, vAxisX, fRotateY, vAxisY ); break; }
				case VBF_ROTATE_ORDER_ZYX:  { m_matModelRotate = osg::Matrix::rotate( fRotateZ, vAxisZ, fRotateY, vAxisY, fRotateX, vAxisX ); break; }
			}
		}
	}

	m_bDirtyMatrixModelRotate = false;
}

//-----------------------------------------------------------------------------
// ������CalMatrixModelTrans()
// ���������¼���ģ������ϵ�µ�ƽ�ƾ���
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::CalMatrixModelTrans()
{
	if(m_bDirtyMatrixModelTrans)
	{
        m_matModelTrans = osg::Matrix::translate(m_fTransX+m_fTransInitX, m_fTransY+m_fTransInitY, m_fTransZ+m_fTransInitZ);
		m_bDirtyMatrixModelTrans = false;
	}
}

//-----------------------------------------------------------------------------
// ������MatrixMove()
// ���������¼���ģ������ϵ�µ�ƽ�ƾ���
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::MatrixMove(osg::Matrixd& matMove)
{
	matMove.makeIdentity();

    const osg::Vec3d& vPos = this->GetPos();

	matMove(3,0) = vPos.x();
	matMove(3,1) = vPos.y();
	matMove(3,2) = vPos.z();
}

//-----------------------------------------------------------------------------
// ������EnableScaleWithParent()
// �������Ƿ��游ģ������
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::EnableScaleWithParent(bool bEnable)	
{ 
	if(bEnable==m_bScaleWithParent) return;

	m_bScaleWithParent = bEnable; 
	DirtyMatrixModelScale(); 
} 

//-----------------------------------------------------------------------------
// ������EnableRotateWithParent()
// �������Ƿ��游ģ����ת
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::EnableRotateWithParent(bool bEnable)	
{ 
	if(bEnable==m_bRotateWithParent) return;

	m_bRotateWithParent = bEnable; 
	DirtyMatrixModelRotate(); 
}
 
//-----------------------------------------------------------------------------
// ������EnableFixedSizeInPixels()
// �������Ƿ��������ù̶���С (��λ������)
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::EnableFixedSizeInPixels(bool bEnable)	
{ 
	if(m_bEnableFixedSizeInPixels==bEnable) return;

	m_bEnableFixedSizeInPixels = bEnable; 
    DirtyMatrixModelScale();

    m_bDirtyFixedSizeInPixels = true;

    // �Ƿ���Ҫ�ı�AutoTransform�ڵ�Ĺҽ�״̬
    m_bDirtyAutoTransformNode = true;
}

//-----------------------------------------------------------------------------
// ������ClipByEarth()
// �������ж��Ƿ�λ�ڵ�����
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::ClipByEarth()
{
    if(!this->m_bEnableClipByEarth) return;
    if(this->m_bEnableDepthTest) return;
    if(!this->m_piNodeRoot.valid() || this->m_piNodeRoot->getNodeMask()==0) return;  // �Ѿ����ü���

    bool bCliped = ::VBF_IsClipedByEarth(this->m_opView.get(),this->m_ipContext->GetEllipsoid()->getRadiusPolar(),this->GetWorldPos());
    if(bCliped)
    {
        this->m_piNodeRoot->setNodeMask(0);
    }
}

//-----------------------------------------------------------------------------
// ������SetViewMode()
// ����������ģ�͵Ĺ۲�ģʽ
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetViewMode(EVBF_VIEW_MODE nMode)
{
    if(m_nViewMode==nMode) return;

    m_nViewMode = nMode;

    m_bDirtyViewMode = true;

    // �Ƿ���Ҫ�ı�AutoTransform�ڵ�Ĺҽ�״̬
    m_bDirtyAutoTransformNode = true;
}

//-----------------------------------------------------------------------------
// ������GetModelToWorldMatrix()
// ��������ȡת������ģ������ϵ --> ��������ϵ
//-----------------------------------------------------------------------------
template<class T>
osg::Matrixd CVBF_MarkModelPointImpl<T>::GetModelToWorldMatrix()
{
	osg::Matrixd matWorld;
	matWorld.makeIdentity();

	if( m_piNodeTransformModel.valid() )
	{
		CVBF_NodeUtil::GetNodeMatrixInWorld(m_piNodeTransformModel, matWorld);
	}

	return matWorld;
}

//-----------------------------------------------------------------------------
// ������GetWorldToModelMatrix()
// ��������ȡת��������������ϵ --> ģ������ϵ 
//-----------------------------------------------------------------------------
template<class T>
osg::Matrixd CVBF_MarkModelPointImpl<T>::GetWorldToModelMatrix()
{
	osg::Matrixd matWorld = GetModelToWorldMatrix();
	osg::Matrixd matModel = osg::Matrix::inverse(matWorld);
	return matModel;
}

//-----------------------------------------------------------------------------
// ������PointWorldToModel()
// �������ѵ���������������ϵ�任��ģ������ϵ
//-----------------------------------------------------------------------------
template<class T>
osg::Vec3d CVBF_MarkModelPointImpl<T>::PointWorldToModel(const osg::Vec3d& ptWorld)
{
	osg::Vec3d ptModel = ptWorld * GetWorldToModelMatrix();
	return ptModel;
}

//----------------------------------------------------------------------------
// ������Vector0ToPointInModelIntersectWithEarth()
// �����������ģ��ԭ�㵽ģ����ĳ���������ģ������ϵ�£������Ľ��㣬
//      ���ؽ��㼰����ģ��ԭ��ľ��루��������ϵ�£�
// ������dHeightAdjust -- �߶ȵ���ֵ����������Ϊ0.0
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::Vector0ToPointInModelIntersectWithEarth(const osg::Vec3d& vPointInModel, double dHeightAdjust,
								                                         osg::Vec3d& ptIntersect, double& dDist)
{
	// �߶���㣨��������ϵ�£�
	osg::Vec3d ptStart = this->GetPos();
	if(this->m_pIParent!=NULL)
	{
		ptStart = ptStart * GetModelToWorldMatrix(); // ��ģ��
	}

	// �߶��յ㣨��������ϵ�£�
	osg::Vec3d ptEnd = vPointInModel * GetModelToWorldMatrix();

    // �߶���
    return ::VBF_LineSegIntersectEllipsoid(ptStart, ptEnd, dHeightAdjust, ptIntersect, dDist);
}

//----------------------------------------------------------------------------
// ������Vector0ToPointInModelIntersectWithEarth()
// ����������ĳ������ģ������ϵ�£������Ľ��㣬���ؽ��㼰�����������ľ��루��������ϵ�£�
// ������dHeightAdjust -- �߶ȵ���ֵ����������Ϊ0.0
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::VectorInModelIntersectWithEarth(const osg::Vec3d& vPointInModelStart, const osg::Vec3d& vPointInModelEnd, 
	                                                             double dHeightAdjust, osg::Vec3d& ptIntersect, double& dDist)
{
	// �߶���㣨��������ϵ�£�
	osg::Vec3d ptStart = vPointInModelStart * GetModelToWorldMatrix();

	// �߶��յ㣨��������ϵ�£�
	osg::Vec3d ptEnd = vPointInModelEnd * GetModelToWorldMatrix();

    // �߶���
    return ::VBF_LineSegIntersectEllipsoid(ptStart, ptEnd, dHeightAdjust, ptIntersect, dDist);
}

//-----------------------------------------------------------------------------
// ������SetDeltaRotate()
// ����������ģ������ϵ���ۼӵ���ת�ǣ��ڵ�ǰֵ�Ļ����ϣ�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetDeltaRotate(float fDeltaRotateX, float fDeltaRotateY, float fDeltaRotateZ)
{
	SetRotate(m_fRotateX+fDeltaRotateX, m_fRotateY+fDeltaRotateY, m_fRotateZ+fDeltaRotateZ);
}

//-----------------------------------------------------------------------------
// ������SetDeltaScale()
// ����������ģ������ϵ���ۼӵ����űȣ��ڵ�ǰֵ�Ļ����ϣ�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetDeltaScale(float fDeltaScaleX, float fDeltaScaleY, float fDeltaScaleZ)
{
	SetScale(m_fScaleX*(1.0f+fDeltaScaleX), m_fScaleY*(1.0f+fDeltaScaleY), m_fScaleZ*(1.0f+fDeltaScaleZ));
}

//-----------------------------------------------------------------------------
// ������SetDeltaTrans()
// ����������ģ������ϵ���ۼӵ�ƽ��ֵ���ڵ�ǰֵ�Ļ����ϣ�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetDeltaTrans(float fDeltaTransX, float fDeltaTransY, float fDeltaTransZ)
{
	SetTrans(m_fTransX+fDeltaTransX, m_fTransY+fDeltaTransY, m_fTransZ+fDeltaTransZ);
}

//-----------------------------------------------------------------------------
// ������SetDeltaTransGeo()
// ����������ģ������ϵ���ۼӵĵ�������ƽ��ֵ���ڵ�ǰֵ�Ļ����ϣ�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetDeltaTransGeo(float fDeltaTransX, float fDeltaTransY, float fDeltaTransZ)
{
    osg::Vec3d vGeoPos = this->GetGeoPos();

    vGeoPos.x()+= fDeltaTransX;
    vGeoPos.y()+= fDeltaTransY;
    vGeoPos.z()+= fDeltaTransZ;

    this->SetGeoPos(vGeoPos);
}

//-----------------------------------------------------------------------------
// ������SetUnTransformed()
// �������ָ�ģ������ϵ��ģ�ͳ�ʼ״̬�������κ���ת��/���ű�/ƽ��ֵ
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetUnTransformed()
{
	m_fRotateX = 0.0f;
	m_fRotateY = 0.0f;
	m_fRotateZ = 0.0f;

	m_fScaleX = 1.0f;
	m_fScaleY = 1.0f;
	m_fScaleZ = 1.0f;

	m_fTransX = 0.0f;
	m_fTransY = 0.0f;
	m_fTransZ = 0.0f;

	DirtyMatrixModelRotate();
	DirtyMatrixModelScale();
	DirtyMatrixModelTrans();
}

//-----------------------------------------------------------------------------
// ������SetRotateMatrixOut()
// ������ֱ��ʹ���ⲿ���õ���ת����ģ������ϵ�£�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetRotateMatrixOut(const osg::Matrixd& mat)
{
	m_matModelRotateOut.mutable_value()  = mat;
	m_matModelRotateOutForWrite.mutable_value() = mat;

	DirtyMatrixModelRotate();
}

//-----------------------------------------------------------------------------
// ������Contains()
// �������ж��Ƿ����ĳ��
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::Contains(const osg::Vec3d& ptWorld)
{
	osg::Vec3d ptModel;
	double dDist;

	return Contains(ptWorld, ptModel, dDist);
}

//-----------------------------------------------------------------------------
// ������SetParent()
// ����������ģ�������µĸ�ģ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::SetParent(IVBF_MarkModel* pIParent)
{ 
	CVBF_MarkModelImpl<T>::SetParent(pIParent);

	// �����ģʽ���ǵ�״ģ�ͣ����游ģ�����ź���ת
	if( pIParent!=NULL && !pIParent->IsPointMarkModel() )
	{
		EnableScaleWithParent(false);
		EnableRotateWithParent(false);
	}

    // ʹ��λ�ڵ�ʧЧ
    m_bDirtyNodeLocator = true;
    m_bLocateRelative   = (pIParent!=NULL && pIParent->IsPointMarkModel());
}

//-----------------------------------------------------------------------------
// ������PushOnePoint()
// ���������ֵ�����β����׷��һ����
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::PushOnePoint(const VBF_TRAILPOINTINNER& point)
{
    m_vInterPoints.push(point);
}

//-----------------------------------------------------------------------------
// ������GetNumInterPoints()
// ���������ݷ���ʱ�䲽����ʽ�����㵱ǰ��Ҫ��ֵ�ĵ���
//-----------------------------------------------------------------------------
template<class T>
int CVBF_MarkModelPointImpl<T>::GetNumInterPoints(const VBF_TRAILPOINTINNER& ptBegin, const VBF_TRAILPOINTINNER& ptEnd)
{
	// ��ȡ֡�ٶ�
	double dFPS = ::VBF_GetFPS(this->m_pI3DMainCtrl);

	int nNumPoints = dFPS;
	if( m_nSimTimeMode==VBF_SIMTIME_MODE_FIXED )			// ����
	{
		nNumPoints = (int)(m_fSimTimeStep * dFPS + 0.5);
	}
	else if( m_nSimTimeMode==VBF_SIMTIME_MODE_VARIABLE )	// �䳤
	{
		// �����������ݵ�֮���ʱ���(��)��������Ҫ��ֵ�ĵ���
        double dTimeInterval = CVBF_Timer::instance()->delta_s(ptBegin.timer.getStartTick(), ptEnd.timer.getStartTick());
        nNumPoints = (int)(dTimeInterval * dFPS + 0.5);
    }
	else if( m_nSimTimeMode==VBF_SIMTIME_MODE_REALTIME ) // ʵʱ������Ҫϵͳ�ڲ���ֵ��ֱ��ʹ��StepGeoPos()�д��ݵ�����ֵ
	{
		nNumPoints = 1;
	}

	return nNumPoints;
}

//-----------------------------------------------------------------------------
// ������Interpolate()
// ������·����ֵ (ͬʱ�����ꡢ�ǶȺ�ʱ����в�ֵ)
// ������bIncludingEnd -- ��ֵ��ĵ����Ƿ���Ҫ�����յ�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::Interpolate(int nNumInsert, const VBF_TRAILPOINTINNER& ptBegin,
                                             const VBF_TRAILPOINTINNER& ptEnd, bool bIncludingEnd)
{
    // ������������ⱻ0��
    if(nNumInsert<=1)
    {
        if(bIncludingEnd) PushOnePoint(ptEnd);
        return;
    }

    // ������д
    const osg::Vec3d& vGeoBegin = ptBegin.vPosGeo;
    const osg::Vec3d& vGeoEnd   = ptEnd.vPosGeo;

    float fRotateXBegin = ptBegin.fRotateX;
    float fRotateYBegin = ptBegin.fRotateY;
    float fRotateZBegin = ptBegin.fRotateZ;

    float fRotateXEnd   = ptEnd.fRotateX;
    float fRotateYEnd   = ptEnd.fRotateY;
    float fRotateZEnd   = ptEnd.fRotateZ;

    // ����1�������ֵ

    // ���⴦���ȿ�Խ180�ȵ���� (2010-01-18)
    double dL       = vGeoEnd.x() - vGeoBegin.x();
    double dLTemp0	= vGeoBegin.x();
    double dLTemp1	= vGeoEnd.x();

    if(dL > 180)		dLTemp1 -= 360;
    else if(dL < -180)	dLTemp0 -= 360;

    dL = dLTemp1 - dLTemp0;

    // ��һ�ַ�������������Ĳ�ֵ (�������ӵ��Զʱ)
//	CMCE_GisMath::GetRouteVertices( vGeoBegin, vGeoEnd, nNumVertices, pGeoVertices );

    // �ڶ��ַ������򵥵����Բ�ֵ (�������ӵ�Ͻ�ʱ���д��޸�)
    double dx = dL/(nNumInsert-1);
    double dy = (vGeoEnd.y() - vGeoBegin.y())/(nNumInsert-1);
    double dz = (vGeoEnd.z() - vGeoBegin.z())/(nNumInsert-1);

    // ����2���ǶȲ�ֵ

    // ����ǶȲ��Խ180
    float fRotateXDelta  = fRotateXEnd - fRotateXBegin;
    float fRotateYDelta  = fRotateYEnd - fRotateYBegin;
    float fRotateZDelta  = fRotateZEnd - fRotateZBegin;

    // ���⴦�����
    float fRotateZTemp0	= fRotateZBegin;
    float fRotateZTemp1	= fRotateZEnd;

    if(fRotateZDelta > 180)
    {
        fRotateZTemp1 -= 360;
    }
    else if(fRotateZDelta < -180)
    {
        fRotateZTemp0 -= 360;
    }

    fRotateZDelta = fRotateZTemp1 - fRotateZTemp0;

    float fRotateXDeltaPerFrame	= 0.0f;
    float fRotateYDeltaPerFrame	= 0.0f;
    float fRotateZDeltaPerFrame	= 0.0f;

    fRotateXDeltaPerFrame  = fRotateXDelta/(nNumInsert-1);
    fRotateYDeltaPerFrame  = fRotateYDelta/(nNumInsert-1);
    fRotateZDeltaPerFrame  = fRotateZDelta/(nNumInsert-1);

    // ���������յ�֮���ʱ���Ա����ò�ֵ���ʱ��
    CVBF_Timer_t dDeltaTick = (ptEnd.timer.getStartTick() - ptBegin.timer.getStartTick())/(nNumInsert-1);

    // ����3�������β�ֵ��Ľڵ���ӵ�������

    // �������
    PushOnePoint(ptBegin);

    // �����м��
    for(int i=1; i<nNumInsert-1; i++)
    {
        // ��ֵ��ÿ֡ʵ�ʵ�����
        osg::Vec3d vGeo;
        vGeo.x() = vGeoBegin.x() +  dx * i;
        vGeo.y() = vGeoBegin.y() +  dy * i;
        vGeo.z() = vGeoBegin.z() +  dz * i;

        if(vGeo.x() < -180)		vGeo.x() += 360;
        else if(vGeo.x() > 180)	vGeo.x() -= 360;

        // ��ֵ��ÿ֡ʵ�ʵ���ת��
        float fRotateXInter = fRotateXBegin + i * fRotateXDeltaPerFrame;
        float fRotateYInter = fRotateYBegin + i * fRotateYDeltaPerFrame;
        float fRotateZInter = fRotateZBegin + i * fRotateZDeltaPerFrame;

        if(fRotateZInter < 0) fRotateZInter += 360;

        VBF_TRAILPOINTINNER point(false, vGeo, fRotateXInter, fRotateYInter, fRotateZInter, "");
        point.timer.setStartTick( ptBegin.timer.getStartTick() + i * dDeltaTick );  // ��ʱ����в�ֵ

        // ���ڵ���ӵ�������
        PushOnePoint(point);
    }

    // �����յ�
    if(bIncludingEnd) PushOnePoint(ptEnd);
}

//-----------------------------------------------------------------------------
// ������StepIt()
// ��������������һ����ֵ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::StepIt()
{
	int nNumPoints = m_vInterPoints.size();
    if(nNumPoints==0) return;

	// ����ģ�͵ĵ�������
	m_TrailPoint = m_vInterPoints.front();

    this->SetGeoPos(m_TrailPoint.value().vPosGeo);
    SetRotate(m_TrailPoint.value().fRotateX, m_TrailPoint.value().fRotateY, m_TrailPoint.value().fRotateZ);

    // �õ��˶���ϣ�����ɾ����
    m_vInterPoints.pop();
}

template<class T>
void CVBF_MarkModelPointImpl<T>::StopStepIn()
{
    while( !m_vKeyPoints.empty() )
    {
        m_vKeyPoints.pop();
    }

    while( !m_vInterPoints.empty() )
    {
        m_vInterPoints.pop();
    }
}
//-----------------------------------------------------------------------------
// ������StepGeoPos()
// ��������ģ�͵ĵ������경����ָ��λ�ã���Ҫ��ֵ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::StepGeoPos(const osg::Vec3d& vGeo, float fRotateX, float fRotateY, float fRotateZ, const std::string& strInfo/*=""*/)
{
    // ���õ��Ϊ�ؼ���
    VBF_TRAILPOINTINNER ptNew(true, vGeo, fRotateX, fRotateY, fRotateZ, strInfo);

    // ʵʱ������Ҫϵͳ�ڲ���ֵ��ֱ��ʹ��StepGeoPos()�д��ݵ�����ֵ
    if( m_nSimTimeMode==VBF_SIMTIME_MODE_REALTIME )
    {
        // ֻ��¼����ֵ������м��ɣ�����Ҫ��¼Ϊ�ؼ���
        PushOnePoint(ptNew);
        return;
    }

    // ����ǵ�һ���ؼ��㣺����Ҫ��ֵ
    if( m_vKeyPoints.size()==0 )
    {
        PushOnePoint(ptNew);
    }
    else if( m_vKeyPoints.size()==1 || m_vInterPoints.empty() ) // ����ǵڶ����ؼ��㣨�����ϴεĲ�ֵ���Ѿ����꣩����Ҫ�������ؼ���֮����в�ֵ
    {
        const VBF_TRAILPOINTINNER& pt0 = m_vKeyPoints.back();
        const VBF_TRAILPOINTINNER& pt1 = ptNew;
        int nNumInsert = GetNumInterPoints(pt0, pt1);
        Interpolate(nNumInsert, pt0, pt1, true);

        // ��ֵ�󣬼���ɾ����һ���ؼ��㣬�����µĹؼ���
        m_vKeyPoints.pop();
    }
    else  // ����ǵ����������Ժ�Ĺؼ��㣺��Ҫ����������������֮����в�ֵ����ǰ�����㡢��һ���ؼ��㡢�¹ؼ���
    {
        // ��ʱ������δ����Ĳ�ֵ��
        VBF_TRAILPOINTINNER        pt0 = m_vInterPoints.front();
        const VBF_TRAILPOINTINNER& pt1 = m_vKeyPoints.back();
        const VBF_TRAILPOINTINNER& pt2 = ptNew;

        // ע�⣺����ϴ���δ����Ĳ�ֵ��
        while( !m_vInterPoints.empty() )
        {
            m_vInterPoints.pop();
        }

        if( m_nSimTimeMode==VBF_SIMTIME_MODE_FIXED )	// ����
        {
            int nNumInsert = GetNumInterPoints(pt0, pt2);

            // �����������γɵ������߶εĳ��ȱȣ����Լ��㼴�ɣ��������ֵ����
            const osg::Vec3d& vGeo0 = pt0.vPosGeo;
            const osg::Vec3d& vGeo1 = pt1.vPosGeo;
            const osg::Vec3d& vGeo2 = pt2.vPosGeo;

            // ���㳤�ȵ�ƽ��
            double dDist01 = (vGeo1.x()-vGeo0.x())*(vGeo1.x()-vGeo0.x()) + (vGeo1.y()-vGeo0.y())*(vGeo1.y()-vGeo0.y());
            double dDist12 = (vGeo2.x()-vGeo1.x())*(vGeo2.x()-vGeo1.x()) + (vGeo2.y()-vGeo1.y())*(vGeo2.y()-vGeo1.y());

            // �����һ���߶��������߶γ��Ⱥ͵ıȣ��ɴ˷����ֵ����
            float fRatio = sqrt( dDist01/(dDist01+dDist12) );

            int nNumInsert01 = (int)(nNumInsert * fRatio + 0.5f);
            int nNumInsert12 = nNumInsert - nNumInsert01;

            // ��ֵ
            Interpolate(nNumInsert01, pt0, pt1, false);
            Interpolate(nNumInsert12, pt1, pt2, true);
        }
        else if( m_nSimTimeMode==VBF_SIMTIME_MODE_VARIABLE )	// �䳤
        {
            // �����������ݵ�֮���ʱ���(��)��������Ҫ��ֵ�ĵ���
            int nNumInsert01 = GetNumInterPoints(pt0, pt1);
            int nNumInsert12 = GetNumInterPoints(pt1, pt2);

            // ��ֵ
            Interpolate(nNumInsert01, pt0, pt1, false);
            Interpolate(nNumInsert12, pt1, pt2, true);
        }

        // ��ֵ�󣬼���ɾ����һ���ؼ��㣬�����µĹؼ���
        m_vKeyPoints.pop();
    }

    // �����µĹؼ���
    m_vKeyPoints.push(ptNew);
}

//-----------------------------------------------------------------------------
// ������GetTrailPoint()
// ��������ȡ����ģ���ڵ�ǰ֡�Ĺ켣����Ϣ������Ϣͨ��StepGeoPos()�������ã����ģ����δ��ʼ�˶�������false��
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::GetTrailPoint(VBF_TRAILPOINT& ptTrail)
{
    if( !m_TrailPoint.isSet() ) return false;

    ptTrail = m_TrailPoint.value();
    return true;
}

//-----------------------------------------------------------------------------
// ������GetBoundingBoxInWorld()
// ������������������ϵ�µİ�Χ��
//-----------------------------------------------------------------------------
template<class T>
const osg::BoundingBox& CVBF_MarkModelPointImpl<T>::GetBoundingBoxInWorld()
{
    if(this->m_bDirtyBoundingBoxInWorld)
    {
        // ע�⣺����Ǿ��Զ�λ����Ҫȷ����ʱ�Ѿ��������������
        if(!m_bLocateRelative && m_piNodeModelToWorld.valid())
        {
            const Matrix& mat = m_piNodeModelToWorld->getMatrix();
            if(!mat.isIdentity())
            {
                const osg::BoundingBox& boxInModel = this->GetBoundingBoxInModel();
                CVBF_NodeUtil::NodeBoundingBoxModelToWorld(m_piNodeTransformModel.get(), boxInModel, this->m_BoundingBoxInWorld);
                if(!this->m_BoundingBoxInWorld.valid()) return this->m_BoundingBoxInWorld;

                this->m_bDirtyBoundingBoxInWorld = false;
            }
        }
    }

    return this->m_BoundingBoxInWorld;
}

//-----------------------------------------------------------------------------
// ������GetWorldPos()
// ��������ȡģ�͵���������
//-----------------------------------------------------------------------------
template<class T>
const osg::Vec3d& CVBF_MarkModelPointImpl<T>::GetWorldPos()
{
    // ������������Ѿ�ʧЧ����Ҫ���¼���
    if(this->m_bDirtyPosWorld)
    {
        // ���û�и�ģ�ͣ�ֱ��ͨ������������㣻������Ҫͨ���ֲ��任�ڵ����
        if(NULL==this->GetParent())
        {
            this->m_ipContext->GeoToWorld(this->m_vPosGeo, true, this->m_vPosWorld);
        }
        else
        {
            if(!CVBF_NodeUtil::GetNodePosInWorld(m_piNodeTransformModel, this->m_vPosWorld)) return ::VBF_GetPosInvalid();
        }

        // ȷ������������Ч
        if(::VBF_IsPosInvalid(this->m_vPosWorld)) return ::VBF_GetPosInvalid();

        this->m_bDirtyPosWorld = false;
    }

    return this->m_vPosWorld;
}

//-----------------------------------------------------------------------------
// ������CreateBoundingBoxNode()
// ������������Χ�нڵ�
//-----------------------------------------------------------------------------
template<class T>
osg::IVBF_SGNode* CVBF_MarkModelPointImpl<T>::CreateBoundingBoxNode()
{
    osg::IVBF_SGNode* pNodeDst = (this->GetChildCount()==0)? this->m_piNodeModel.get() : this->m_piNodeGroup.get();
    ref_ptr<osg::IVBF_SGNode> piNode = ::VBF_CreateBoundingBoxForNode(pNodeDst, this->m_BoundingBoxStyle);

    return piNode.release();
}

//-----------------------------------------------------------------------------
// ������GetBoundingBoxInGeo()
// �����������������ϵ�µİ�Χ��
//-----------------------------------------------------------------------------
template<class T>
const osg::BoundingBoxd& CVBF_MarkModelPointImpl<T>::GetBoundingBoxInGeo()
{
    if(!this->m_bDirtyBoundingBoxInGeo) return this->m_BoundingBoxInGeo;

    // ע�⣺��Ҫ�жϰ�Χ�����ĵ�ĵ�����������������Ƿ���Ч
    osg::Vec3d ptCenterGeo = this->GetBoundingBoxCenterGeo();
    if(::VBF_IsPosInvalid(ptCenterGeo)) return this->m_BoundingBoxInGeo;

    osg::Vec3d ptCenterWorld = ::VBF_GetPosInvalid();
    this->m_ipContext->GeoToWorld(ptCenterGeo, true, ptCenterWorld);
    if(::VBF_IsPosInvalid(ptCenterWorld)) return this->m_BoundingBoxInGeo;

    // ע�⣺��Ҫ�ж�ģ������ϵ�µİ�Χ���Ƿ���Ч
    const osg::BoundingBox& boxInModel = this->GetBoundingBoxInModel();
    if(!boxInModel.valid()) return this->m_BoundingBoxInGeo;

    this->m_BoundingBoxInGeo.init();

    for(int i=0; i<8; i++)
    {
        float fScaleX, fScaleY, fScaleZ;
        GetRealtimeScale(fScaleX, fScaleY, fScaleZ);
        osg::Matrix matScale = osg::Matrix::scale(fScaleX/2, fScaleY/2, fScaleZ/2);

        osg::Vec3d ptWorld = boxInModel.corner(i)*matScale*m_matModelRotate + ptCenterWorld;

        // �������� --> ��������
        osg::Vec3d ptGeo;
        this->m_ipContext->WorldToGeo(ptWorld, ptGeo);

        this->m_BoundingBoxInGeo.expandBy(ptGeo);
    }

    this->m_bDirtyBoundingBoxInGeo = false;

    return this->m_BoundingBoxInGeo;
}

//-----------------------------------------------------------------------------
// ������WriteModelToXML()
// ������д��ģ�ͱ������Ϣ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::WriteModelToXML(TiXmlElement* pElemMark)
{
	if(!CVBF_MarkModelImpl<T>::WriteModelToXML(pElemMark)) return false;

	// д�룺ģ�����ű�
	osg::Vec3f vScale(m_fScaleX, m_fScaleY, m_fScaleZ);
	::VBF_SetAttribute(pElemMark, "Scale", vScale);

	// д�룺ģ����ת˳��
	::VBF_SetAttribute(pElemMark, "RotateOrder", (int)m_nRotateOrder);

    // д�룺ģ����ת����/��ת��
    if( m_matModelRotateOutForWrite.isSet() )
    {
        ::VBF_SetAttribute(pElemMark, "RotateMatrixOut", m_matModelRotateOutForWrite.value());
    }
    else
    {
        osg::Vec3f vRotate(m_fRotateX, m_fRotateY, m_fRotateZ);
        ::VBF_SetAttribute(pElemMark, "Rotate", vRotate);
    }

	// д�룺�Ƿ��游ģ������/��ת
	::VBF_SetAttribute(pElemMark, "ScaleWithParent",  m_bScaleWithParent);
	::VBF_SetAttribute(pElemMark, "RotateWithParent", m_bRotateWithParent);

	::VBF_SetAttribute(pElemMark, "EnableFixedSizeInPixels", m_bEnableFixedSizeInPixels);	// �Ƿ��������ù̶���С
	::VBF_SetAttribute(pElemMark, "EnableAutoScale",		 m_bEnableAutoScale);			// �Ƿ������Զ�������С
	::VBF_SetAttribute(pElemMark, "EnableScaleDelta",		 m_bEnableScaleDelta);			// �Ƿ�����ʵʱ�������ű� (���ܷ�ͨ���ȼ�ʵ��ͳһ����)
	::VBF_SetAttribute(pElemMark, "EnableMatchTerrain",		 m_bEnableMatchTerrain);		// �Ƿ��������ƥ��
	::VBF_SetAttribute(pElemMark, "FixedSizeInPixels",		 m_fFixedSizeInPixels);			// �̶����ش�С
	::VBF_SetAttribute(pElemMark, "ViewMode",				 (int)m_nViewMode);				// �۲췽ʽ

	return true;
}

//-----------------------------------------------------------------------------
// ������ReadModelFromXML()
// ��������ȡģ�ͱ������Ϣ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelPointImpl<T>::ReadModelFromXML(TiXmlElement* pElemMark)
{
	if(!CVBF_MarkModelImpl<T>::ReadModelFromXML(pElemMark)) return false;

	// ��ȡ��ģ�����ű�
	osg::Vec3f vScale(m_fScaleX, m_fScaleY, m_fScaleZ);
	::VBF_QueryAttribute(pElemMark, "Scale", vScale);
	SetScale(vScale.x(), vScale.y(), vScale.z());

	// ��ȡ��ģ����ת˳��
	EVBF_ROTATE_ORDER nRotateOrder = GetRotateOrder();
	::VBF_QueryAttribute(pElemMark, "RotateOrder", (int&)nRotateOrder);
	SetRotateOrder(nRotateOrder);

	// ��ȡ��ģ����ת����/��ת��
	osg::Matrixd matRotateOut;
	if( ::VBF_QueryAttribute(pElemMark, "RotateMatrixOut", matRotateOut) )
	{
		SetRotateMatrixOut(matRotateOut);
	}
	else
	{
		osg::Vec3f vRotate(m_fRotateX, m_fRotateY, m_fRotateZ);
		::VBF_QueryAttribute(pElemMark, "Rotate", vRotate);
		SetRotate(vRotate.x(), vRotate.y(), vRotate.z());
	}

	// ��ȡ���Ƿ��游ģ������/��ת
	bool bScaleWithParent  = IsScaleWithParentEnabled();
	bool bRotateWithParent = IsRotateWithParentEnabled();
	::VBF_QueryAttribute(pElemMark, "ScaleWithParent",  bScaleWithParent);
	::VBF_QueryAttribute(pElemMark, "RotateWithParent", bRotateWithParent);

    bool bEnableFixedSizeInPixels   = IsFixedSizeInPixelsEnabled();
    bool bEnableAutoScale           = IsAutoScaleEnabled();
    bool bEnableScaleDelta          = IsScaleDeltaEnabled();
    bool bEnableMatchTerrain        = IsMatchTerrainEnabled();
    float fFixedSizeInPixels        = GetFixedSizeInPixels();
    EVBF_VIEW_MODE nViewMode        = GetViewMode();

	::VBF_QueryAttribute(pElemMark, "EnableFixedSizeInPixels", bEnableFixedSizeInPixels);	// �Ƿ��������ù̶���С
	::VBF_QueryAttribute(pElemMark, "EnableAutoScale",		   bEnableAutoScale);			// �Ƿ������Զ�������С
	::VBF_QueryAttribute(pElemMark, "EnableScaleDelta",		   bEnableScaleDelta);			// �Ƿ�����ʵʱ�������ű� (���ܷ�ͨ���ȼ�ʵ��ͳһ����)
	::VBF_QueryAttribute(pElemMark, "EnableMatchTerrain",	   bEnableMatchTerrain);		// �Ƿ��������ƥ��
	::VBF_QueryAttribute(pElemMark, "FixedSizeInPixels",	   fFixedSizeInPixels);			// �̶����ش�С
	::VBF_QueryAttribute(pElemMark, "ViewMode",				   (int&)nViewMode);			// �۲췽ʽ

	// ������ز���
	EnableScaleWithParent(bScaleWithParent);
	EnableRotateWithParent(bRotateWithParent);

	EnableFixedSizeInPixels(bEnableFixedSizeInPixels);
	EnableAutoScale(bEnableAutoScale);
	EnableScaleDelta(bEnableScaleDelta);
	EnableMatchTerrain(bEnableMatchTerrain);
	SetFixedSizeInPixels(fFixedSizeInPixels);
	SetViewMode(nViewMode);

	return true;
}

//-----------------------------------------------------------------------------
// ������ExecuteScript()
// ������ִ��json�ű�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelPointImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
    CVBF_MarkModelImpl<T>::ExecuteScript(conf);

	// ��ȡ��ģ�����ű�
	osg::Vec3f vScale(m_fScaleX, m_fScaleY, m_fScaleZ);
	if( conf.getIfSet("Scale", vScale) )
	{
		SetScale(vScale.x(), vScale.y(), vScale.z());
	}

	// ��ȡ��ģ����ת˳��
	EVBF_ROTATE_ORDER nRotateOrder = GetRotateOrder();
	if( conf.getIfSet("RotateOrder", (int&)nRotateOrder) )
	{
		SetRotateOrder(nRotateOrder);
	}

	// ��ȡ��ģ����ת����/��ת��
	osg::Matrixd matRotateOut;
	if( conf.getIfSet("RotateMatrixOut", matRotateOut) )
	{
		SetRotateMatrixOut(matRotateOut);
	}
	else
	{
		osg::Vec3f vRotate;
		GetRotate(vRotate.x(), vRotate.y(), vRotate.z());
		if( conf.getIfSet("Rotate", vRotate) )
		{
			SetRotate(vRotate.x(), vRotate.y(), vRotate.z());
		}

		osg::Vec3f vRotateInit;
		GetRotateInit(vRotateInit.x(), vRotateInit.y(), vRotateInit.z());
		if( conf.getIfSet("RotateInit", vRotateInit) )
		{
			SetRotateInit(vRotateInit.x(), vRotateInit.y(), vRotateInit.z());
		}
	}

	// ��ȡ������ģ�͵�ƽ�ƺͳ�ʼƽ�ƣ�����У��ģ�͵Ľ�ģԭ�㣩
	osg::Vec3f vTrans;
	GetTrans(vTrans.x(), vTrans.y(), vTrans.z());
	if( conf.getIfSet("Translate", vTrans) )
	{
		SetTrans(vTrans.x(), vTrans.y(), vTrans.z());
	}

	osg::Vec3f vTransInit;
	GetTransInit(vTransInit.x(), vTransInit.y(), vTransInit.z());
	if( conf.getIfSet("TranslateInit", vTransInit) )
	{
		SetTransInit(vTransInit.x(), vTransInit.y(), vTransInit.z());
	}

	// ��ȡ���Ƿ��游ģ������/��ת
	bool bScaleWithParent  = IsScaleWithParentEnabled();
	bool bRotateWithParent = IsRotateWithParentEnabled();
	if( conf.getIfSet("ScaleWithParent",  bScaleWithParent) )
	{
		EnableScaleWithParent(bScaleWithParent);
	}
	if( conf.getIfSet("RotateWithParent", bRotateWithParent) )
	{
		EnableRotateWithParent(bRotateWithParent);
	}

    bool bEnableFixedSizeInPixels   = IsFixedSizeInPixelsEnabled();
    bool bEnableAutoScale           = IsAutoScaleEnabled();
    bool bEnableScaleDelta          = IsScaleDeltaEnabled();
    bool bEnableMatchTerrain        = IsMatchTerrainEnabled();
    float fFixedSizeInPixels        = GetFixedSizeInPixels();
    EVBF_VIEW_MODE nViewMode        = GetViewMode();

	if( conf.getIfSet("EnableFixedSizeInPixels", bEnableFixedSizeInPixels) ){ EnableFixedSizeInPixels(bEnableFixedSizeInPixels); }
	if( conf.getIfSet("EnableAutoScale",		bEnableAutoScale) )			{ EnableAutoScale(bEnableAutoScale); }
	if( conf.getIfSet("EnableScaleDelta",		bEnableScaleDelta) )		{ EnableScaleDelta(bEnableScaleDelta); }
	if( conf.getIfSet("EnableMatchTerrain",		bEnableMatchTerrain) )		{ EnableMatchTerrain(bEnableMatchTerrain); }
	if( conf.getIfSet("FixedSizeInPixels",		fFixedSizeInPixels) )		{ SetFixedSizeInPixels(fFixedSizeInPixels); }
	if( conf.getIfSet("ViewMode",				(int&)nViewMode) )			{ SetViewMode(nViewMode); }
}

#endif 
