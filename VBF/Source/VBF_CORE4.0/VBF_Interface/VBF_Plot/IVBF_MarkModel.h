//*******************************************************************
// FileName��IVBF_MarkModel.h
// Function����ͼʵ��ģ�ͽӿ�
// Author:
// Date:     2009-4-10
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_H__
#define __IVBF_MARK_MODEL_H__


// ��Ҫʹ�õ�ͷ�ļ�
#include <VBF_Macros.h>
#include <Types/Vec3d>
#include <Types/Vec4f>
#include <Types/VBF_Matrixd.h>
#include <Types/VBF_BoundingBox.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>
#include <VBF_Plot/IVBF_MarkStyleManager.h>
#include <VBF_Plot/VBF_MarkPopupMenu.h>
#include <VBF_Base/IVBF_SimulationTimer.h>
#include <string>
#include <vector>
#include <VBF_Plot/IVBF_MarkContext.h>

namespace osg
{
	class IVBF_SGNodeGroup;
	class IVBF_SGNodeGroupLOD;
	class IVBF_SGNodeGroupTransformMatrix;
}

class IVBF_MarkAttr;
class IVBF_MarkAction;
class IVBF_MarkProcess;
class IVBF_MarkModel;
class IVBF_ObserverRef;
class TiXmlElement;
class CVBF_Config;

// ģ�͵�Ԥ����־��ϵͳʹ�������4λ
#define VBF_RESERVEFLAG_ATTRCHILD	0x0001		// �����Դ�������ģ��
// ���ģ���и��ಿ����ģ�͵�Ԥ����־��ϵͳʹ�������4λ
#define VBF_RESERVEFLAG_COMBINEDCHILD_LOD       0x0002
#define VBF_RESERVEFLAG_COMBINEDCHILD_GROUP     0x0004
#define VBF_RESERVEFLAG_COMBINEDCHILD_GEODE     0x0008


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModel
// �ӿ�����������ʵ��ģ��
// ע����������˰Ѵ����õ�ģ�ͼ��뵽ͼ����
//--------------------------------------------------------------------
class IVBF_MarkModel : public osg::CVBF_Object
{
public:
	virtual ~IVBF_MarkModel() {}

public:

	/* ���þ�������ͱ���
	   ������strCode -- ����ģ�͵����ͱ���(����ʹ��16λ��ǰ8λΪ���룬��8λΪ����) 
	*/
	virtual void SetCode(const std::string& strCode)=0;

	/* ��ȡ��������ͱ��� */
	virtual const std::string& GetCode()=0;

	/* ��ȡ����ģ�͵����� (����ģ�͵����Ͳμ�ö��VBF_MARK_TYPE�Ķ���)*/
	virtual unsigned int GetType()=0;

	/* ��ȡ����ģ�͵������������Ա��û���� */
	virtual const std::string& GetTypeDesc()=0;

	/* ��ȡ����ģ�͵�ȫ��Ψһ��� */
	virtual const std::string& GetID()=0;

	/* ���þ���ģ�͵�ȫ��Ψһ��ţ������ģ���Ѿ���¼ĳ��ͼ���У��������޸�ID�ţ�����false�����û�����ʹ�øú����� */
	virtual bool SetID(const std::string& strID)=0;

	/* �жϾ���ģ���Ƿ�Ϊ��״ʵ��ģ�� (���Ƿ�ͨ��Ψһ������㶨λ) */
	virtual bool IsPointMarkModel()=0;

	/* ����ģ�͵���Ҫ�Լ��� (��ֵԽС������Խ��) */
	virtual void  SetLevel(DWORD nLevel)=0;
	virtual DWORD GetLevel()=0;

	/* ����ģ�Ϳ��ӵ���С�����룬�ֱ�Ĭ��Ϊ0.0��FLT_MAX (��λ����) */
	virtual void	SetDistMin(float fDistMin)=0;
	virtual float	GetDistMin()=0;
	virtual void	SetDistMax(float fDistMax)=0;
	virtual float	GetDistMax()=0;

	// ��ȡģ�͵��ӵ�ľ��루��λ���ף�
	virtual double GetDistToEye()=0;

	// ����ģ�͵��ӵ�ľ��룬ʵʱ�ж�ģ���Ƿ��ڿɼ�������
	virtual bool IsInDistRange()=0;

	/* ����ģ�͵Ŀɼ��� */
	virtual void	SetVisible(bool bVisible)=0;	// ����ģ���Ƿ�ɼ�
	virtual bool	IsVisible()=0;					// �ж�ģ���Ƿ�ɼ�

	/* ����ģ�͵�ѡ��״̬ */
	virtual void    SetSelected(bool bSelected)=0;		// ����ģ���Ƿ�ѡ��
	virtual bool    IsSelected()=0;						// �ж�ģ���Ƿ�ѡ��
    virtual void    SetSelectable(bool bSelectable)=0;    // �����Ƿ�������ѡ��
    virtual bool    IsSelectable()=0;

	// ����/��ȡѡ��ģ��ʱ����Χ���Ƿ��Զ��ɼ���Ĭ��Ϊtrue��
	virtual void    SetBoundingBoxVisibleWhenSelected(bool bVisible)=0;
	virtual bool    IsBoundingBoxVisibleWhenSelected()=0;

	/* ����ģ���Ƿ��� */
	virtual void	SetAlive(bool bAlive)=0;
	virtual bool	IsAlive()=0;

	/* ����/��ȡ����ģ�ͱ�ѡ��ʱ��Χ�еĿɼ��� */
	virtual void	SetBoundingBoxVisible(bool bVisible)=0;	
	virtual bool	IsBoundingBoxVisible()=0;

	// ����/��ȡ��Χ�е���ʽ
	virtual void SetBoundingBoxStyle(const VBF_BOUNDINGBOXSTYLE& style)=0;
	virtual const VBF_BOUNDINGBOXSTYLE& GetBoundingBoxStyle()=0;

	/** ��ȡģ���ڸ�������ϵ�µİ�Χ�� */
	virtual const osg::BoundingBox&  GetBoundingBoxInModel()=0;
	virtual const osg::BoundingBox&  GetBoundingBoxInWorld()=0;
	virtual const osg::BoundingBoxd& GetBoundingBoxInGeo()=0;

	/** ��ȡģ�Ͱ�Χ�����ĵĵ������� */
	virtual osg::Vec3d GetBoundingBoxCenterGeo()=0;	

	/* ����ģ�����ڵ�ͼ�� */
    virtual  void	SetLayerPtr(TYPE_PTR dwData)=0;				// ����ģ������ͼ���ָ��
    virtual  TYPE_PTR  GetLayerPtr()=0;							// ��ȡģ������ͼ���ָ��

	// ��ͼ��ָ������ΪNULL���ú�������ϵͳ�ڲ����ã�
	virtual  void	SetLayerPtrAsNull()=0;

	/* ����ģ�͵��ı���Ϣ */
    virtual void SetInfo(const std::string& strInfo)=0;     // ����ģ�͵��ı���Ϣ
    virtual const std::string&	GetInfo()=0;				// ��ȡģ�͵��ı���Ϣ

    // ����/��ȡ�Ƿ�ɲ�ѯ��ģ�͵���Ϣ��Ĭ��ֵΪtrue��
    virtual void SetQueriable(bool bQueriable)=0;
    virtual bool IsQueriable()=0;

    // ����/��ȡ��ģ�ͱ���ѯ�������ʾ��ʽ
    virtual void                      SetQueryStyle(const VBF_MARKQUERYSTYLE& style)=0;
    virtual const VBF_MARKQUERYSTYLE& GetQueryStyle()=0;

    // ����/��ȡģ���Ƿ�ɱ༭��Ĭ��ֵΪtrue��
    virtual void SetEditable(bool bEditable)=0;
    virtual bool IsEditable()=0;

	/* ����ģ�Ͷ�Ӧ���ڴ����� (���������ⲿ�������ϵͳ�ڲ��������ͷ�) */
    virtual  void   SetData(TYPE_PTR dwData)=0;					// ����ģ�Ͷ�Ӧ���ڴ����ݵ��׵�ַ
    virtual  TYPE_PTR GetData()=0;								// ��ȡģ�Ͷ�Ӧ���ڴ����ݵ��׵�ַ

	// ����Ԥ����־��ϵͳʹ�������4λ
	virtual void  SetReserveFlag(DWORD dwFlag, bool bOR=true)=0;
	virtual DWORD GetReserveFlag()=0;

	/* ��ȡ����ģ�͵�ǰ��λ�ã�����и�ģ�ͣ�������ģ�͵�������ꣻ���򣬷���ģ�͵��������� */
	virtual const osg::Vec3d& GetPos()=0;

	/* ��ȡģ�͵����������� */
	virtual const osg::Vec3d& GetWorldPos()=0;

	/* ����/��ȡģ�͵ĵ������꣨���������ֲ��任ǰ�ĵ������꣬��ֵ���û����ã� */
	virtual void SetGeoPos(const osg::Vec3d& vGeoPos)=0;
	virtual const osg::Vec3d& GetGeoPos()=0;

	// ��ȡ����ģ��ʵ�ʵĵ������꣨���������ֲ��任��ĵ������꣬��ֵ��ϵͳ�ڲ����㣩
	virtual osg::Vec3d GetActualGeoPos()=0;


	// ------------------------------------------------------------------------------
	// �����ӹ�ϵ
	// ------------------------------------------------------------------------------

	/* ���þ���ģ�͵ĸ�ģ�� (ÿ��ģ�����ֻ����һ����ģ��)
	   ������pIParent -- ��ģ�͵�ָ��
	*/
	virtual void SetParent(IVBF_MarkModel* pIParent)=0;

	/* ��ȡ����ģ�͵ĸ�ģ�� 
	   ���أ�pIParent -- ��ģ�͵�ָ�룬NULL��ʾû�и�ģ��
	*/
	virtual IVBF_MarkModel* GetParent()=0;

	// ��ȡ����ģ�͵ĸ�ģ�Ͳ���б�����㸸ģ�Ϳ�ʼ������ģ�ͽ�����
	virtual std::vector<IVBF_MarkModel*> GetParentalPaths()=0;

	/* Ϊ����ģ�����һ����ģ�� 
	   ������pIChild -- ��ģ�͵�ָ��
	   ������Child�ظ�������ظ��򷵻�false
	*/
	virtual bool	AddChild(IVBF_MarkModel* pIChild)=0;
	
	// �Ƴ�һ����ģ�ͣ���ɾ����ģ�͵�ָ�룩
	virtual IVBF_MarkModel* RemoveChild(const std::string& strChildID)=0;
	virtual void	RemoveChild(IVBF_MarkModel* pIChild)=0;

	// ɾ��һ����ģ�ͣ�ɾ����ģ�͵�ָ�룩
	virtual void	DeleteChild(const std::string& strChildID)=0;
	virtual void	DeleteChild(IVBF_MarkModel* pIChild)=0;

	/* ��ȡ����ģ�͵���ģ�͸��� */	
	virtual int     GetChildCount()=0;

    /* ��ȡ����ģ�͵�ĳ����ģ��
	   ������nIndex -- ����ģ�͵���� (�ɽ��GetChildCount()����ʵ����ģ�͵ı���)
	   ���أ���n����ģ�͵�ָ��
	*/
	virtual IVBF_MarkModel* GetChild(int nIndex)=0; 

    /* ��ȡ����ģ�͵�ĳ����ģ��
	   ������strChildID -- ����ģ�͵�ID��
	   ���أ���ģ�͵�ָ��
	*/
	virtual IVBF_MarkModel* GetChild(const std::string& strChildID)=0;

    /* ��ȡ����ģ�͵�ĳ����ģ�ͣ���Ȳ������У���������ģ�͵���ģ�ͣ�
       ������strChildID -- ����ģ�͵�ID��
       ���أ���ģ�͵�ָ��
    */
    virtual IVBF_MarkModel* GetChildNested(const std::string& strChildID)=0;

	// �����ָ������ģ��
	virtual IVBF_MarkModel* ApartChild(const std::string& strChildID)=0;

	// ��ȡ��ģ�͵ĵ�������
	virtual osg::Vec3d GetChildGeoPos(const std::string& strChildID)=0;

    // ���ñ�ʶ����ģ�͵ĸ��ڵ�ȴ���ӵ�ĳ�����ڵ�
    virtual void SetParentNode(osg::IVBF_SGNodeGroup* pParentNode)=0;

	// ���ñ�ʶ����ģ�͵ĸ��ڵ�ȴ���ӵ�ĳ�����ڵ��ͼ�㣨�ú��������ڲ����ã�
    virtual void WaitForAddingToParentLayer()=0;


	// ------------------------------------------------------------------------------
	// ����ģ������
	// ------------------------------------------------------------------------------

	// �������/ɾ��/����
	virtual bool AddMarkAttr(IVBF_MarkAttr* pIAttr)=0;
	virtual void DeleteMarkAttr(unsigned int nAttrType)=0;
	virtual IVBF_MarkAttr* LookupMarkAttr(unsigned int nAttrType)=0;
	virtual IVBF_MarkAttr* AddMarkAttr(unsigned int nAttrType)=0;

	// ���Ա���
	virtual unsigned int	GetMarkAttrCount()=0;
	virtual IVBF_MarkAttr*	GetMarkAttr(unsigned int nIndex)=0;

    // ------------------------------------------------------------------------------
    // ����ģ����Ϊ
    // ------------------------------------------------------------------------------
    virtual bool AddMarkAction(IVBF_MarkAction* pIAction)=0;
    virtual void DeleteMarkAction(unsigned int nIndex)=0;

    virtual unsigned int	 GetMarkActionCount()=0;
    virtual IVBF_MarkAction* GetMarkAction(unsigned int nIndex)=0;

    // ------------------------------------------------------------------------------
    // ����ģ�����ݹ���
    // ------------------------------------------------------------------------------

    virtual bool AddMarkProcess(IVBF_MarkProcess* pIProcess)=0;
    virtual void DeleteMarkProcess(unsigned int nIndex)=0;

    virtual unsigned int	  GetMarkProcessCount()=0;
    virtual IVBF_MarkProcess* GetMarkProcess(unsigned int nIndex)=0;

    virtual void ProcessSimulate(IVBF_SimulationTimer* pSimulationTimer)=0;
    virtual void StatStartTime(double& dStartTime)=0;


	// �ж�ͨ�����������Ƿ�ѡ��ģ��
	virtual bool SelectByGeoPoint(osg::Vec3d& vCoordGeo)=0;

	// ǿ�п���/�ر���Ȳ��� (Ĭ��Ϊ����)
	virtual void EnableDepthTest(bool bEnable)=0;
	virtual bool IsDepthTestEnabled()=0;

	// ǿ�п���/�ر����д�� (Ĭ��Ϊ����)
	virtual void EnableDepthWrite(bool bEnable)=0;
	virtual bool IsDepthWriteEnabled()=0;

	// ǿ�п���/�رչ��� (Ĭ��Ϊ�ر�)
	virtual void EnableLight(bool bEnable)=0;
	virtual bool IsLightEnabled()=0;

	// ����/�رյ�⻬ (Ĭ��Ϊ����)
	virtual void EnablePointSmooth(bool bEnable)=0;
	virtual bool IsPointSmoothEnabled()=0;

	// ����/�ر��߹⻬ (Ĭ��Ϊ����)
	virtual void EnableLineSmooth(bool bEnable)=0;
	virtual bool IsLineSmoothEnabled()=0;

	// ����/�ر���⻬ (Ĭ��Ϊ�رգ���������ĳЩ�����ϻ���������εı���)
	virtual void EnablePolygonSmooth(bool bEnable)=0;
	virtual bool IsPolygonSmoothEnabled()=0;

    // �Ƿ���������Ĳü�����״ģ��Ĭ��Ϊtrue������Ĭ��Ϊfalse
    virtual void EnableClipByEarth(bool bEnable)=0;
    virtual bool IsClipByEarthEnabled()=0;

    // ����/��ȡģ���Ƿ��游ģ��ͬ����ɫ��Ĭ��ֵΪtrue��
    virtual void EnableBlendWithParent(bool bEnable)=0;
    virtual bool IsBlendWithParentEnabled()=0;

	// ����/��ȡģ���Ƿ��ɫ�Լ���ϵ���ɫ
	virtual void SetBlendColor(bool bEnable, const osg::Vec4f& color=osg::Vec4f(1,1,1,1), bool bModulate=false)=0;
    virtual void GetBlendColor(bool& bEnable, osg::Vec4f& color, bool& bModulate)=0;

    // ��ʼ/ֹͣģ����˸
    virtual void StartFlicker(int nFlickerTimes, int nFlickerInterval, bool bFlickerAlways=false)=0;
    virtual void StopFlicker()=0;

	// ����ģ�͵���Ⱦ˳��
	virtual void SetRenderOrder_Opaque(int nOrder)=0;			// ��͸��ģ��
	virtual void SetRenderOrder_Transparent(int nOrder)=0;		// ͸��ģ��

	// �������ģ�͵���Ⱦ˳��
	virtual void SetRenderHint_Opaque()=0;			// ��͸��ģ��
	virtual void SetRenderHint_Transparent()=0;		// ͸��ģ��
	virtual void SetRenderHint_Default()=0;

	// ��ȡģ�͵ĸ�������ͼ�ڵ�
	virtual osg::IVBF_SGNodeGroup*		GetRootNode()=0;	// ��ȡģ�͵ĳ���ͼ���ڵ�
	virtual osg::IVBF_SGNodeGroup*		GetGroupNode()=0;	// ��ȡģ�͵���ڵ㣬�����ӽڵ�ҽ��ڴ���
	virtual osg::IVBF_SGNode*			GetModelNode()=0;	// ��ȡģ�͵�ʵ�����ݽڵ�

    /* ģ����ĳ�ֶ��� (�糵�ֹ�����������ת��)
       ������szActionName  -- �������ƣ����������ת�ȣ�
            bEnabled       -- ����������ֹͣ
    */
    virtual void DoAction(const char* szActionName, bool bEnabled)=0;
    virtual void DoAction(const std::string& strChildID, const std::string& strActionName, bool bEnabled)=0;


    // ��/���һ����Ϣ�۲��ߣ�������ո�ģ�ͷ����ĸ�����Ϣ��
    virtual void AttachObserver(IVBF_ObserverRef* pIObserver)=0;
    virtual void DetachObserver(IVBF_ObserverRef* pIObserver)=0;

    // �Ҽ������˵�
    virtual void EnablePopupMenu(bool bEnable)=0;
    virtual bool IsPopupMenuEnabled()=0;
    virtual void GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vPopupMenuItemInf)=0;
    virtual bool ProcessPopupMenuItem(unsigned int nID)=0;

	// �Ƿ������л���Ĭ��Ϊtrue��
	virtual bool IsAllowSerialize()=0;
	virtual void SetAllowSerialize(bool bAllow)=0;

    // ���л�
    virtual bool WriteToXML(TiXmlElement* pElemMark)=0;    // д�룺��ģ����Ϣд��ָ����xml�ڵ�
    virtual bool ReadFromXML(TiXmlElement* pElemMark)=0;   // ��ȡ����ָ����xml�ڵ��ȡģ����Ϣ

	// ��ʼ�� (�ڹ��캯��֮����ϵͳ����)
    virtual bool Init(IVBF_MarkContext* pIContext)=0;
    virtual IVBF_MarkContext* GetMarkContext()=0;

	// ���� (��ÿ֡����ǰ��ϵͳ����)������ֵΪfalse��ʾδ�����´�����ģ�Ͳ��ɼ�ʱ��
	virtual bool Update()=0;

    virtual void UpdateBoundingBox()=0;      // ���°�Χ�нڵ�

	// ִ��json�ű�
    virtual void ExecuteScript(const CVBF_Config& conf)=0;


};


#endif 
