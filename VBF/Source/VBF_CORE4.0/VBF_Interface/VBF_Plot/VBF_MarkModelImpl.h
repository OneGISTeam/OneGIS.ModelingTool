//*******************************************************************
// FileName��VBF_MarkModelImpl.h
// Function������ʵ��ģ�͵�ģ����
// Author:   
// Date:     2004-12-15
//*******************************************************************

#ifndef __VBF_MARK_MODEL_IMPL_H__
#define __VBF_MARK_MODEL_IMPL_H__


#include <VBF_MainCtrl/VBF_3DEnvironment.h>
#include <VBF_MainCtrl/IVBF_ObserverRef.h>
#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>

#include <Types/Vec3d>
#include <string>
#include <vector>

#include <VBF_Plot/IVBF_MarkAttr.h>
#include <VBF_Plot/IVBF_MarkAction.h>
#include <VBF_Plot/IVBF_MarkAttrIFF.h>
#include <VBF_Plot/IVBF_MarkProcess.h>

#include <VBF_Aux/VBF_GLAux/VBF_Effect.h>
#include <VBF_Aux/VBF_GLAux/VBF_StateSetUtils.h>
#include <VBF_Aux/VBF_GLAux/VBF_ReadWriteUtils.h>
#include <VBF_Aux/VBF_GLAux/VBF_NodeUtil.h>
#include <VBF_Aux/VBF_GLAux/VBF_Effect.h>
#include <VBF_Aux/VBF_GLAux/VBF_PrimitiveUtils.h>
#include <VBF_Aux/VBF_GLAux/VBF_3DPlotShaderUtils.h>
#include <VBF_Aux/VBF_GLAux/VBF_JsonReader.h>
#include <VBF_Aux/VBF_MapAux/VBF_CoordTransformUtils.h>
#include <VBF_Aux/VBF_MapAux/VBF_SceneUtils.h>
#include <VBF_Aux/VBF_MapAux/IVBF_3DGlobalData.h>

// ��osg�йص�ͷ�ļ�
#include <VBF_Base/ref_ptr>
#include <VBF_Base/observer_ptr>
#include <VBF_Display/VBF_Viewer/VBF_View.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransformCamera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupSwitch.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformAuto.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLOD.h>

// ��Ⱦ״̬
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrDepth.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLightModel.h>


// ����͸��ģ�͵���ȾԪ����
#define VBF_TRANSPARENT_BINBASE		10


typedef std::vector< ref_ptr<IVBF_MarkModel> >			CVBF_MarkList;
typedef std::vector< ref_ptr<IVBF_MarkAttr> >			CVBF_AttrList;
typedef std::vector< ref_ptr<IVBF_MarkAction> >			CVBF_ActionList;
typedef std::vector< ref_ptr<IVBF_MarkProcess> >		CVBF_ProcessList;
typedef std::vector< observer_ptr<IVBF_ObserverRef> >	CVBF_ObserverList;


//=======================================================================================
// ����ģ���ࣺCVBF_MarkModelImpl
// ģ��������������ʵ��ģ��
//=======================================================================================
template<class T>
class CVBF_MarkModelImpl : public T
{
public:	
	CVBF_MarkModelImpl() {}
	CVBF_MarkModelImpl(const std::string& strMarkID);
	CVBF_MarkModelImpl(const CVBF_MarkModelImpl& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
	virtual ~CVBF_MarkModelImpl();

	// ����/��ȡ��������ͱ��� (16λ��ǰ8λΪ���룬��8λΪ����)
	virtual void SetCode(const std::string& strCode)	{ m_strCode = strCode; }
	virtual const std::string&	GetCode()				{ return m_strCode; }

	// ��ȡ����ı��
	virtual  const std::string&  GetID()		{ return m_strID; }

	/* ���þ���ģ�͵�ȫ��Ψһ��ţ������ģ���Ѿ���¼ĳ��ͼ���У��������޸�ID�ţ�����false�����û�����ʹ�øú����� */
	virtual bool SetID(const std::string& strID);

	// ��ȡ���������
	virtual  unsigned int GetType()				{ return m_nType; }

	// ��ȡ����ģ�͵������������Ա��û����
	virtual const std::string& GetTypeDesc()	{ return m_strTypeDesc; }

	// �ж��Ƿ�Ϊ��״ģ��
	virtual  bool IsPointMarkModel()			{ return false; }	

	// ����/��ȡ����ģ�͵���Ҫ�Լ��� (��ֵԽС������Խ��) (2010-05-28) 
	virtual void	SetLevel(DWORD nLevel)			{ m_nLevel = nLevel; }
	virtual DWORD	GetLevel()						{ return m_nLevel; }

	/* ����ģ�Ϳ��ӵ���С�����룬�ֱ�Ĭ��Ϊ0.0��FLT_MAX (��λ����) */
	virtual void	SetDistMin(float fDistMin)      { m_fDistMin = fDistMin; }
	virtual float	GetDistMin()					{ return m_fDistMin; }
	virtual void	SetDistMax(float fDistMax)      { m_fDistMax = fDistMax; }
	virtual float	GetDistMax()					{ return m_fDistMax; }

	// ��ȡģ�͵��ӵ�ľ��루��λ���ף�
	virtual double GetDistToEye() { return m_dDistToEye; }

	// ����ģ�͵��ӵ�ľ��룬ʵʱ�ж�ģ���Ƿ��ڿɼ�������
	virtual bool IsInDistRange() { return m_bInDistRange; }
	
	// ����/��ȡģ�͵Ŀɼ���
	virtual void	SetVisible(bool bVisible);
	virtual bool	IsVisible()						{ return m_bVisible; }

	// ����ģ���Ƿ���
	virtual void	SetAlive(bool bAlive)		    { m_bAlive = bAlive; }
	virtual bool	IsAlive()						{ return m_bAlive; }

	// ѡ��״̬
	virtual void    SetSelected(bool bSelected);	
	virtual bool    IsSelected()					{ return m_bSelected; }
    virtual void    SetSelectable(bool bSelectable) { m_bSelectable = bSelectable; }// �����Ƿ�������ѡ��
    virtual bool    IsSelectable()                  { return m_bSelectable; }

	// ����/��ȡѡ��ģ��ʱ����Χ���Ƿ��Զ��ɼ���Ĭ��Ϊtrue��
	virtual void    SetBoundingBoxVisibleWhenSelected(bool bVisible);
	virtual bool    IsBoundingBoxVisibleWhenSelected()	{ return m_bBoundingBoxVisibleWhenSelected; }

	// ���ø�ģ������ͼ���ָ��
    virtual  void   SetLayerPtr(TYPE_PTR dwData);
    virtual  TYPE_PTR GetLayerPtr()					{ return m_dwLayerPtr; }

	// ��ͼ��ָ������ΪNULL���ú�������ϵͳ�ڲ����ã�
	virtual  void	SetLayerPtrAsNull();
	
	// ����/��ȡģ�͵���Ϣ
	virtual void	SetInfo(const std::string& strInfo)	{ m_strInfo = strInfo; }
	virtual const std::string&	GetInfo()				{ return m_strInfo; }

    // ����/��ȡ�Ƿ�ɲ�ѯ��ģ�͵���Ϣ��Ĭ��ֵΪtrue��
    virtual void SetQueriable(bool bQueriable)      { m_bQueriable = bQueriable; }
    virtual bool IsQueriable()                      { return m_bQueriable; }

    // ����/��ȡ��ģ�ͱ���ѯ�������ʾ��ʽ
    virtual void                      SetQueryStyle(const VBF_MARKQUERYSTYLE& style) { m_QueryInfo = style; }
    virtual const VBF_MARKQUERYSTYLE& GetQueryStyle() { return m_QueryInfo; }

    // ����/��ȡģ���Ƿ�ɱ༭��Ĭ��ֵΪtrue��
    virtual void SetEditable(bool bEditable)    { m_bEditable = bEditable; }
    virtual bool IsEditable()                   { return m_bEditable; }

	// ���û�Ԥ����
    virtual  void SetData(TYPE_PTR dwData)			{ m_dwData = dwData; }
    virtual  TYPE_PTR GetData()						{ return m_dwData; }

	// ����/��ȡԤ����־��ϵͳʹ�������4λ
	virtual void  SetReserveFlag(DWORD dwFlag, bool bOR=true); 
	virtual DWORD GetReserveFlag() { return m_dwReserveFlag; }

	/* ��ȡ����ģ�͵ĵ�ǰλ�ã�����и�ģ�ͣ�������ģ�͵�������ꣻ���򣬷���ģ�͵��������� */
	virtual const osg::Vec3d& GetPos();

	// ��ȡģ�͵���������
	virtual const osg::Vec3d& GetWorldPos();

	// �ж�ĳ�㣨��������ϵ�£��Ƿ���ģ�ͷ�Χ��
	virtual bool Contains(const osg::Vec3d& ptWorld)	{ osg::Vec3d ptModel; double dDist; return Contains(ptWorld, ptModel, dDist); }
	virtual bool Contains(const osg::Vec3d& ptWorld, osg::Vec3d& ptModel, double& dDist) { return false; }

	// ����/��ȡģ�͵ĵ������꣨���������ֲ��任ǰ�ĵ������꣬��ֵ���û����ã�
	virtual const osg::Vec3d& GetGeoPos()		{ return m_vPosGeo; } 
	virtual void  SetGeoPos(const osg::Vec3d& vPos);

	// ��ȡģ��ʵ�ʵĵ������꣨���������ֲ��任��ĵ������꣬��ֵ��ϵͳ�ڲ����㣩
	virtual osg::Vec3d GetActualGeoPos();


	// ------------------------------------------------------------------------------
	// �����ӹ�ϵ
	// ------------------------------------------------------------------------------

    virtual void			SetParent(IVBF_MarkModel* pIParent) { m_pIParent = pIParent;  }
    virtual IVBF_MarkModel*	GetParent()                         { return m_pIParent; }

	// ��ȡ����ģ�͵ĸ�ģ�Ͳ���б�����㸸ģ�Ϳ�ʼ������ģ�ͽ�����
	virtual std::vector<IVBF_MarkModel*> GetParentalPaths();

	virtual bool	AddChild(IVBF_MarkModel* pIChild);

	// �Ƴ�һ����ģ�ͣ���ɾ����ģ�͵�ָ�룩
	virtual IVBF_MarkModel* RemoveChild(const std::string& strChildID);
	virtual void	RemoveChild(IVBF_MarkModel* pIChild);

	// ɾ��һ����ģ�ͣ�ɾ����ģ�͵�ָ�룩
	virtual void	DeleteChild(const std::string& strChildID);
	virtual void	DeleteChild(IVBF_MarkModel* pIChild);

	// ��ģ�ͱ��� (nIndex�����ʾ���Ե����)
	virtual int	GetChildCount();
	virtual IVBF_MarkModel* GetChild(int nIndex);
    virtual IVBF_MarkModel* GetChild(const std::string& strChildID);
    virtual IVBF_MarkModel* GetChildNested(const std::string& strChildID);

	// �����ָ������ģ��
	virtual IVBF_MarkModel* ApartChild(const std::string& strChildID);

	// ��ȡ��ģ�͵ĵ�������
	virtual osg::Vec3d GetChildGeoPos(const std::string& strChildID);

    // ���ñ�ʶ����ģ�͵ĸ��ڵ�ȴ���ӵ�ĳ�����ڵ�
    virtual void SetParentNode(osg::IVBF_SGNodeGroup* pParentNode);

	// ���ñ�ʶ����ģ�͵ĸ��ڵ�ȴ���ӵ�ĳ�����ڵ��ͼ�㣨�ú��������ڲ����ã�
	virtual void WaitForAddingToParentLayer() { m_bNodeToAddToParentLayer = true; }


	// ------------------------------------------------------------------------------
	// ����ģ������
	// ------------------------------------------------------------------------------

	// �������/ɾ��/����
	virtual bool AddMarkAttr(IVBF_MarkAttr* pIAttr);
	virtual void DeleteMarkAttr(unsigned int nAttrType);
	virtual IVBF_MarkAttr* LookupMarkAttr(unsigned int nAttrType);
	virtual IVBF_MarkAttr* AddMarkAttr(unsigned int nAttrType);

	// ���Ա���
	virtual unsigned int	GetMarkAttrCount()					{ return m_MarkAttrList.size(); }
	virtual IVBF_MarkAttr*	GetMarkAttr(unsigned int nIndex)	{ return (nIndex>=0 && nIndex<m_MarkAttrList.size())? m_MarkAttrList[nIndex] : NULL; }

    // ------------------------------------------------------------------------------
    // ����ģ����Ϊ
    // ------------------------------------------------------------------------------
    virtual bool AddMarkAction(IVBF_MarkAction* pIAction);
    virtual void DeleteMarkAction(unsigned int nIndex);

    // ��Ϊ����
    virtual unsigned int	 GetMarkActionCount()					{ return m_MarkActionList.size(); }
    virtual IVBF_MarkAction* GetMarkAction(unsigned int nIndex)	{ return (nIndex>=0 && nIndex<m_MarkActionList.size())? m_MarkActionList[nIndex] : NULL; }

    // ------------------------------------------------------------------------------
    // ����ģ�����ݹ���
    // ------------------------------------------------------------------------------

    virtual bool	AddMarkProcess(IVBF_MarkProcess* pIProcess);
    virtual void	DeleteMarkProcess(unsigned int nIndex);

    virtual unsigned int	  GetMarkProcessCount()	{ return m_MarkProcessList.size(); }
    virtual IVBF_MarkProcess* GetMarkProcess(unsigned int nIndex) { return (nIndex>=0 && nIndex < m_MarkProcessList.size())? m_MarkProcessList[nIndex] : NULL; }

    virtual void ProcessSimulate(IVBF_SimulationTimer* pSimulationTimer);
    virtual void StatStartTime(double& dStartTime);  // ͳ������ģ�͵ķ�����̵���ʼʱ��
	// ------------------------------------------------------------------------------
	// ��Χ��
	// ------------------------------------------------------------------------------

	// ����/��ȡ��Χ�еĿɼ��ԣ�Ĭ��Ϊfalse��
	virtual void SetBoundingBoxVisible(bool bVisible);
	virtual bool IsBoundingBoxVisible()	{ return m_bBoundingBoxVisible; }

	// ����/��ȡ��Χ�е���ʽ
	virtual void SetBoundingBoxStyle(const VBF_BOUNDINGBOXSTYLE& style);
	virtual const VBF_BOUNDINGBOXSTYLE& GetBoundingBoxStyle()			{ return m_BoundingBoxStyle; }

    // ��ȡģ���ڸ�������ϵ�µİ�Χ��
	virtual const osg::BoundingBox&  GetBoundingBoxInModel();
	virtual const osg::BoundingBox&  GetBoundingBoxInWorld();
	virtual const osg::BoundingBoxd& GetBoundingBoxInGeo();

    // ��ȡģ�Ͱ�Χ�����ĵĵ�������
	virtual osg::Vec3d GetBoundingBoxCenterGeo();	
	
	// ǿ�п���/�ر�z-buffer���� (Ĭ��Ϊ����)
	virtual void EnableDepthTest(bool bEnable);
	virtual bool IsDepthTestEnabled()			{ return m_bEnableDepthTest; }

	// ǿ�п���/�ر����д�� (Ĭ��Ϊ����)
	virtual void EnableDepthWrite(bool bEnable);
	virtual bool IsDepthWriteEnabled()			{ return m_bEnableDepthWrite; }
	
	// ǿ�п���/�رչ��� (Ĭ��Ϊ�ر�)
	virtual void EnableLight(bool bEnable);
	virtual bool IsLightEnabled()				{ return m_bEnableLight; }

	// ����/�رյ�⻬ (Ĭ��Ϊ����)
	virtual void EnablePointSmooth(bool bEnable);
	virtual bool IsPointSmoothEnabled()			{ return m_bEnablePointSmooth; }

	// ����/�ر��߹⻬ (Ĭ��Ϊ����)
	virtual void EnableLineSmooth(bool bEnable);
	virtual bool IsLineSmoothEnabled()			{ return m_bEnableLineSmooth; }

	// ����/�ر���⻬ (Ĭ��Ϊ�رգ���������ĳЩ�����ϻ���������εı���)
	virtual void EnablePolygonSmooth(bool bEnable);
	virtual bool IsPolygonSmoothEnabled()		{ return m_bEnablePolygonSmooth; }

    // �Ƿ���������Ĳü�����״ģ��Ĭ��Ϊtrue������Ĭ��Ϊfalse
    virtual void EnableClipByEarth(bool bEnable) { m_bEnableClipByEarth = bEnable; }
    virtual bool IsClipByEarthEnabled()          { return m_bEnableClipByEarth; }

    // ����/��ȡģ���Ƿ��游ģ��ͬ����ɫ��Ĭ��ֵΪtrue��
    virtual void EnableBlendWithParent(bool bEnable)    { m_bEnableBlendWithParent = bEnable; }
    virtual bool IsBlendWithParentEnabled()             { return m_bEnableBlendWithParent; }

	// ����/��ȡģ���Ƿ��ɫ�Լ���ϵ���ɫ����ϵķ�ʽ����ɫ/�滻ɫ��
	virtual void SetBlendColor(bool bEnable, const osg::Vec4f& color=osg::Vec4f(1,1,1,1), bool bModulate=false);
	virtual void GetBlendColor(bool& bEnable, osg::Vec4f& color, bool& bModulate)	{ bEnable = m_bEnableBlendColor; color = m_colorBlend; bModulate = m_bBlendModulate; }

    // ��ʼ/ֹͣģ����˸
    virtual void StartFlicker(int nFlickerTimes, int nFlickerInterval, bool bFlickerAlways=false);
    virtual void StopFlicker();

	// ����ģ�͵���Ⱦ˳��
	virtual void SetRenderOrder_Opaque(int nOrder);
	virtual void SetRenderOrder_Transparent(int nOrder);

	// ����ģ�͵���Ⱦ˳��
	virtual void SetRenderHint_Opaque();		
	virtual void SetRenderHint_Transparent();	
	virtual void SetRenderHint_Default();

	// ��ȡģ�͵ĸ�������ͼ�ڵ�
	virtual osg::IVBF_SGNodeGroup*		GetRootNode()	{ return m_piNodeRoot.get(); }
	virtual osg::IVBF_SGNodeGroup*		GetGroupNode()	{ return m_piNodeGroup.get(); }
	virtual osg::IVBF_SGNode*			GetModelNode()	{ return m_piNodeModel.get(); }


    /* ģ����ĳ�ֶ��� (�糵�ֹ�����������ת��)
       ������szActionName  -- �������ƣ����������ת�ȣ�
            bEnabled       -- ����������ֹͣ
            pActionParam   -- �����Ĳ��� (������ٶȵȣ��������ͺͺ����ɶ����������)
    */
    virtual void DoAction(const char* szActionName, bool bEnabled);
    virtual void DoAction(const std::string& strChildID, const std::string& strActionName, bool bEnabled);

    // ��/���һ����Ϣ�۲��ߣ�������ո�ģ�ͷ����ĸ�����Ϣ��
    virtual void AttachObserver(IVBF_ObserverRef* pIObserver);
    virtual void DetachObserver(IVBF_ObserverRef* pIObserver);

	// ʹģ�ͽڵ�/��Ⱦ״̬ʧЧ
    virtual void DirtyModel()       { m_bDirtyModel = true; }
	virtual void DirtyStateSet()	{ m_bDirtyStateSet = true; }

    // �Ҽ������˵�
    virtual void EnablePopupMenu(bool bEnable) { m_bEnablePopupMenu = bEnable; }
    virtual bool IsPopupMenuEnabled()          { return m_bEnablePopupMenu; }
    virtual void GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vItems);
    virtual bool ProcessPopupMenuItem(unsigned int nID);

	// �Ƿ������л�
	virtual bool IsAllowSerialize() { return m_bAllowSerialize;  }
	virtual void SetAllowSerialize(bool bAllow) { m_bAllowSerialize = bAllow; }

    // ���л�����ϵͳ���ã�
    virtual bool WriteToXML(TiXmlElement* pElemMark);    // д��
    virtual bool ReadFromXML(TiXmlElement* pElemMark);   // ��ȡ

	// ��ʼ�� (�ڹ��캯��֮����ϵͳ����)
    virtual bool Init(IVBF_MarkContext* pIContext);
    virtual IVBF_MarkContext* GetMarkContext() { return m_ipContext.get(); }
	// ���� (ÿ֡����ǰ����)
	virtual bool Update();

	// ִ��json�ű�
    virtual void ExecuteScript(const CVBF_Config& conf);

protected:
	virtual bool SelectByGeoPoint(osg::Vec3d& vCoordGeo) { return false; }

	// ��ʼ������ͼ
    virtual bool InitSG();
    virtual void Clear();

	// ������������/��ģ��
	void UpdateAttrs();
	void UpdateChildren();

    // ģ�Ͷ���/��Ч
    void UpdateByActions();
    void UpdateByEffects();

    // ɾ��������ģ��
	void DeleteAllChildren();

	// ����ģ�͵�IFF����
	IVBF_MarkAttrIFF* LookupMarkAttrIFF();

	// ʹ��Χ��ʧЧ���Ա����¼���
	void DirtyBoundingBoxNode()	    { m_bDirtyBoundingBoxNode = true; }
	void DirtyBoundingBoxInModel()	{ m_bDirtyBoundingBoxInModel = true; }
	void DirtyBoundingBoxInWorld()	{ m_bDirtyBoundingBoxInWorld = true; m_bDirtyBoundingBoxInGeo = true; }

    // ʹ����/��������ʧЧ
    void DirtyPosGeo()              { m_bDirtyPosGeo   = true; }
    void DirtyPosWorld()			{ m_bDirtyPosWorld = true; }

	// ����ģ�ͽڵ�
    virtual void UpdateModelNode();
    virtual bool CreateModelNode()	{ return false; }

	// ������Ⱦ״̬
	virtual void SetStateSet();

	// ����ģ�͵�λ��
    virtual void UpdatePos() {}

    // ��ӵ�����ͼ�ĸ��ڵ�
    void AddToParentNode();

    // ����ĳЩ����ͼ�ڵ������
    virtual void UpdateSGNode();

    // �����ӵ㵽ģ�͵ľ��룬�ж�ģ��/�����Ƿ��ڿɼ�������
    virtual void ClipByDist();
    virtual void ClipModelByDist();
    virtual void ClipAttrByDist();

    // ������Ĳü�
    virtual void ClipByEarth() {}

    // ��ȡ����ɫ�ڵ㣬���ܲ�ֹһ��
    virtual void GetBlendNodes(std::vector< ref_ptr<osg::IVBF_SGNode> >& vNodes);

    // ���Χ���йصĺ���
    virtual osg::IVBF_SGNode* GetBoundingBoxNode();     // ��ȡ�����Χ��ʱʹ�õĽڵ�
    virtual osg::IVBF_SGNode* CreateBoundingBoxNode();  // ������Χ�нڵ�
    virtual void              UpdateBoundingBox();      // ���°�Χ�нڵ�
    virtual void              SetShader_BoundingBox(osg::StateSet* ss); // ���ð�Χ�е���ɫ��

    // �����й۲��߷�����Ϣ
    void NotifyObservers(const char* szMessage, int nValue=0, void* pValue=NULL);

    // ���л���д��/��ȡģ�ͱ������Ϣ
    virtual bool WriteModelToXML(TiXmlElement* pElemMark);
    virtual bool ReadModelFromXML(TiXmlElement* pElemMark);

protected:

	// ģ�͵ı�ʶ����
	std::string				m_strID;			// ģ��ID�ţ�ͼ����Ψһ
	std::string				m_strCode;          // ģ�����ͱ��� (16λ��ǰ8λΪ���룬��8λΪ����)
	unsigned int			m_nType;			// ģ������
	std::string				m_strTypeDesc;		// ģ�����͵�������Ϣ

	// ģ�͵���Ϣ����
	std::string				m_strInfo;	        // ģ�͵���Ϣ
	DWORD					m_nLevel;			// ����ģ�͵���Ҫ�Լ��� (��ֵԽС������Խ��) 
	DWORD					m_dwReserveFlag;	// Ԥ����־��ϵͳʹ�����4λ

    // ģ�͵Ĳ�ѯ��Ϣ
    bool                    m_bQueriable;           // �Ƿ�ɲ�ѯ
    VBF_MARKQUERYSTYLE      m_QueryInfo;            // ��ѯ��Ϣ

    // ģ���Ƿ�ɱ༭
    bool                    m_bEditable;

	bool					m_bInited;			// �Ƿ��ʼ���ɹ�
	bool					m_bVisible;			// �Ƿ�ɼ�
	bool					m_bSelected;		// �Ƿ�ѡ��
    bool                    m_bSelectable;      // �Ƿ�ɱ�ѡ��

	bool                    m_bAlive;			// �Ƿ���
	bool					m_bAllowSerialize;	// �Ƿ������л�

	// ģ�͵�����
    bool                    m_bDirtyPosGeo;     // ���������Ƿ�ʧЧ
	bool					m_bDirtyPosWorld;	// ���������Ƿ�ʧЧ
	osg::Vec3d				m_vPosGeo;			// ��������	
	osg::Vec3d				m_vPosWorld;		// ��������

    TYPE_PTR					m_dwLayerPtr;		// ����ͼ���ָ��
    TYPE_PTR					m_dwData;			// ��Ӧ���ݵ�ָ��

	// ��Ⱦ״̬
	bool					m_bEnableDepthTest;			// �Ƿ�����Ȳ��ԣ�Ĭ��Ϊ������
	bool					m_bEnableDepthWrite;		// �Ƿ������д�루Ĭ��Ϊ������
	bool                    m_bEnableLight;				// �Ƿ������� (Ĭ��Ϊ�ر�)
	bool					m_bEnableClipByEarth;		// �Ƿ���������Ĳü���Ĭ��Ϊfalse

	// �Ƿ�������⻬��Ĭ��Ϊ������
	bool					m_bEnablePointSmooth;
	bool					m_bEnableLineSmooth;	
	bool					m_bEnablePolygonSmooth;
	
	// �ɼ�����
	float					m_fDistMin;			// ��С���Ӿ���
	float					m_fDistMax;			// �����Ӿ���

	// ���±��������ж�ģ���Ƿ��ڿɼ�������
	double					m_dDistToEye;		// ģ�͵��ӵ�ľ��루��λ���ף�
	bool					m_bInDistRange;		// ģ�ͱ�֡�Ƿ��ڿɼ�������

	// ��ɫ�������ں��������ͻ��Ŀ�ꡢ������ֵ�
	bool					m_bEnableBlendColor;	// �Ƿ�������ɫ���
    bool					m_bBlendModulate;		// �Ƿ�ʹ�ó�ɫ��ʽ���л�ϣ�����ʹ���滻ɫ��ʽ��
	osg::Vec4f				m_colorBlend; 
	bool					m_bEnableBlendWithParent;	// �Ƿ��游ģ��ͬ����ɫ

	// ģ�͵İ�Χ��
	bool						m_bBoundingBoxVisible;		// ��Χ���Ƿ�ɼ�
	bool						m_bBoundingBoxVisibleWhenSelected;	// ģ��ѡ��ʱ����Χ���Ƿ��Զ��ɼ���ֻ��ģ��ѡ��ʱ�������Բ����ã�
    VBF_BOUNDINGBOXSTYLE		m_BoundingBoxStyle;			// ��Χ�е���ʽ
	osg::BoundingBox			m_BoundingBoxInModel;		// ģ������ϵ�µİ�Χ��
	osg::BoundingBox			m_BoundingBoxInWorld;		// ��������ϵ�µİ�Χ��
	osg::BoundingBoxd			m_BoundingBoxInGeo;			// ��������ϵ�µİ�Χ��
	ref_ptr<osg::IVBF_SGNode>	m_piNodeBoundingBox;		// ��Χ�нڵ�

    // ģ�͵ĸ��ӹ�ϵ
	IVBF_MarkModel*			m_pIParent;
	CVBF_MarkList			m_vChildren;

    // ģ�͵������б����Բ������ظ�
	CVBF_AttrList			m_MarkAttrList;

    // ģ�͵���Ϊ�б������ظ�
    CVBF_ActionList			m_MarkActionList;


    // ģ�͵Ĺ����б����������ظ�
    CVBF_ProcessList        m_MarkProcessList;

    // ģ�͵���Ϣ�۲���
    CVBF_ObserverList       m_ObserverList;


    // ģ�͵ĸ��ֲ����Ƿ�ʧЧ
    bool					m_bDirtyModel;              // ģ�ͽڵ��Ƿ�ʧЧ
    bool					m_bDirtyStateSet;           // ģ����Ⱦ״̬�Ƿ�ʧЧ
    bool					m_bDirtyBoundingBoxNode;	// ��Χ�нڵ��Ƿ�ʧЧ
    bool					m_bDirtyBoundingBoxInModel; // ģ������ϵ�µİ�Χ���Ƿ�ʧЧ
    bool					m_bDirtyBoundingBoxInWorld; // ��������ϵ�µİ�Χ���Ƿ�ʧЧ
    bool					m_bDirtyBoundingBoxInGeo;   // ��������ϵ�µİ�Χ���Ƿ�ʧЧ

    // �Ƿ���Ҫ��ʼ/ֹͣ��˸
    bool                    m_bFlickerToStart;
    bool                    m_bFlickerToStop;
    VBF_FLICKERPARAM        m_FlickerParam;
	
	// ģ�͵���Ⱦ˳��
	CVBF_Optional<int>		m_nBinNumber;
	std::string				m_strBinName;
	int						m_nBinNumberBox;    // ��Χ�е���ȾԪ��ţ�ȷ����Χ����ģ��֮����Ⱦ��

    // �Ҽ������˵�
    bool                    m_bEnablePopupMenu;
    bool                    m_bEnableMenuZBuffer;
    bool					m_bEnableMenuFillMode;

    // ��ģ�͵ĸ��ڵ��Ƿ�ȴ����/ɾ��
    bool                                    m_bNodeToAddToParent;       // �Ƿ�ȴ���ӵ�����ͼ�еĸ��ڵ�
    bool                                    m_bNodeToRemoveFromParent;  // �Ƿ�ȴ��ӳ���ͼ�еĸ��ڵ����Ƴ�
    observer_ptr<osg::IVBF_SGNodeGroup>     m_piNodeParent;             // ����ͼ�еĸ��ڵ�
    observer_ptr<osg::IVBF_SGNodeGroup>     m_piNodeParentOld;          // ����ͼ��ԭ���ĸ��ڵ�

	// ��ģ�͵ĸ��ڵ��Ƿ�ȴ���ӵ����ڵ��ͼ�㣨�����ڸ�ģ���ǵ�״������ģ�Ͳ��ǵ�״������һ����״ģ�������Text�ӽڵ��Label���ԣ�
    bool                                    m_bNodeToAddToParentLayer; 

	// �볡��ͼ�йص�����
	ref_ptr<osg::IVBF_SGNodeGroupSwitch>	m_piNodeRoot;			// ģ�͵ĸ��ڵ㣬�ҽ���ͼ��ڵ���
	ref_ptr<osg::IVBF_SGNodeGroup>			m_piNodeGroup;			// ģ�͵���ڵ㣬�ҽ��ڸ��ڵ��£�ģ�ͽڵ㼰�����ӽڵ���ҽ��ڸýڵ���
    ref_ptr<osg::IVBF_SGNode>				m_piNodeModel;			// ģ�͵�ʵ�����ݽڵ㣬�ҽ���Group�ڵ��£����û���ɸýڵ�Ĵ������޸�

	// ������Ҫʹ�õ��ⲿ�ڵ㣨��Init()�����л�ȡ��
	IVBF_3DMainCtrl*						m_pI3DMainCtrl;
	observer_ptr<IVBF_View>					m_opView;
	observer_ptr<osg::IVBF_Camera>			m_opCamera;

    ref_ptr<IVBF_MarkContext> m_ipContext;
};



#include "VBF_MarkModelImpl.inl"
#include "VBF_MarkModelImpl2.inl"

#endif 
