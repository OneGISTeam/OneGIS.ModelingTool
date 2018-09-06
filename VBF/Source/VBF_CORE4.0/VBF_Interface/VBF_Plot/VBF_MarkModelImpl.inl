//-----------------------------------------------------------------------------
// ������CVBF_MarkModelImpl()
// ���������캯��
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModelImpl<T>::CVBF_MarkModelImpl(const std::string& strMarkID)
{
	m_strID				= strMarkID;

	m_strCode			= "";
	m_nType				= VBF_MARK_UNKNOWN;
	m_strTypeDesc		= "";
	m_nLevel			= 0;
	m_dwReserveFlag		= 0;

	m_strInfo			= "";

    // ģ�͵Ĳ�ѯ��Ϣ
    m_bQueriable        = true;
    m_bEditable         = true;
	
	m_pIParent			= NULL;
	m_dwLayerPtr		= 0L;
	m_dwData			= 0L;

	m_bInited			= false;
	m_bVisible			= true;	
	m_bSelected			= false;
    m_bSelectable       = true;
	m_bAlive            = true;
	m_bAllowSerialize	= true;
	
	// ��Ⱦ״̬
	m_bEnableDepthTest	= true;
	m_bEnableDepthWrite	= true;
	m_bEnableLight		= false;
	m_bEnableClipByEarth = false;

	// �Ƿ�������⻬��Ĭ��Ϊ������
	m_bEnablePointSmooth	= true;		
	m_bEnableLineSmooth		= true;	
	m_bEnablePolygonSmooth	= false;
	
	// ��Ⱦ˳��
	m_nBinNumber.unset();		// ģ�͵���Ⱦ˳��
	m_strBinName		= "";
	m_nBinNumberBox		= VBF_TRANSPARENT_BINBASE + 1;	// ��Χ�е���Ⱦ˳��

	// ��Χ�г�ʼ�����Ѱ�Χ������Ϊ�Ƿ���Χ��
	m_bBoundingBoxVisible = false;
    m_bBoundingBoxVisibleWhenSelected = true;	// ѡ��ģ��ʱ����Χ���Ƿ��Զ��ɼ���Ĭ��Ϊtrue��
	m_BoundingBoxInModel.init();
	m_BoundingBoxInWorld.init();
	m_BoundingBoxInGeo.init();
	
    // ģ����ʾ��LOD��Χ
	m_fDistMin			= 0.0f;
    m_fDistMax			= FLT_MAX;
    m_dDistToEye        = FLT_MAX;
    m_bInDistRange      = true;

	m_vPosGeo			= osg::Vec3d(0, 0, 0);		// �������꣨����и�ģ�ͣ���ʾ��ģ�͵�������꣩
	m_vPosWorld			= ::VBF_GetPosInvalid();	// ��������

	m_bEnableBlendColor = false;
    m_bBlendModulate	= false;		// �Ƿ�ʹ�ó�ɫ��ʽ���л�ϣ�����ʹ���滻ɫ��ʽ
	m_colorBlend		= osg::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	m_bEnableBlendWithParent = true;

	// ģ�ͽڵ��Ƿ�ʧЧ
    m_bDirtyModel               = true;
    m_bDirtyStateSet            = true;
    m_bDirtyPosGeo              = true;
    m_bDirtyPosWorld            = true;
    m_bDirtyBoundingBoxNode     = true;
    m_bDirtyBoundingBoxInModel  = true;
    m_bDirtyBoundingBoxInWorld  = true;
    m_bDirtyBoundingBoxInGeo    = true;

    // �Ƿ���Ҫ��ʼ/ֹͣ��˸
    m_bFlickerToStart           = false;
    m_bFlickerToStop            = false;

    // ģ�͸��ڵ��Ƿ�ȴ����/ɾ��
    m_bNodeToAddToParent        = false;
    m_bNodeToRemoveFromParent   = false;

	// �Ƿ�ȴ���ӵ����ڵ��ͼ��
	m_bNodeToAddToParentLayer   = false;

    // �Ҽ������˵�
    m_bEnablePopupMenu      = true;
    m_bEnableMenuZBuffer    = true;
    m_bEnableMenuFillMode   = false;

    // �ⲿ�ӿ�
    m_pI3DMainCtrl          = NULL;
}

//-----------------------------------------------------------------------------
// ������~CVBF_MarkModelImpl()
// ��������������
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModelImpl<T>::~CVBF_MarkModelImpl()
{
    Clear();

	// �ӳ���ͼ��ɾ����ģ�͵ĸ��ڵ�
	if(m_piNodeRoot.valid())
	{
		osg::CVBF_NodeParentList parents = m_piNodeRoot->getParents();
		for(osg::CVBF_NodeParentList::iterator pIterP=parents.begin(); pIterP!= parents.end(); pIterP++)
		{
			osg::IVBF_SGNodeGroup* pParent = *pIterP;
			if(pParent!=NULL) pParent->removeChild(m_piNodeRoot);
		}
	}
}
template<class T>
void CVBF_MarkModelImpl<T>::Clear()
{
    m_MarkAttrList.clear();
    m_MarkActionList.clear();
    m_MarkProcessList.clear();

    //  ɾ����ģ��
    DeleteAllChildren();
}
//-----------------------------------------------------------------------------
// ������SetID()
// ���������þ���ģ�͵�ȫ��Ψһ��ţ������ģ���Ѿ���¼ĳ��ͼ���У��������޸�ID�ţ�����false�����û�����ʹ�øú�����
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::SetID(const std::string& strID)
{
	// ���ģ���Ѿ���¼��ͼ���У��������޸�ID��
	DWORD dwLayerPtr = GetLayerPtr();
	if(dwLayerPtr!=0) return false;

	m_strID = strID;
	return true;
}

//-----------------------------------------------------------------------------
// ������SetParentNode()
// ���������ñ�ʶ����ģ�͵ĸ��ڵ�ȴ���ӵ�ĳ�����ڵ�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetParentNode(osg::IVBF_SGNodeGroup* pParentNode)
{
    if(m_piNodeParent.get()==pParentNode) return;

    if(m_piNodeParent.valid())
    {
        m_bNodeToRemoveFromParent = true;
        m_piNodeParentOld = m_piNodeParent;
    }

    if(pParentNode!=NULL)
    {
        m_bNodeToAddToParent = true;
    }
    m_piNodeParent = pParentNode;
}

//-----------------------------------------------------------------------------
// ������Init()
// ��������ʼ�� (�ڹ��캯��֮����ϵͳ����)
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::Init(IVBF_MarkContext* pIContext)
{  
	// ���ⱻ��γ�ʼ��
	if(m_bInited) return true;

    if(pIContext==NULL) return false;
    m_ipContext = pIContext;


	CVBF_3DEnvironment& env = ::VBF_Get3DEnvironment();
	m_pI3DMainCtrl = env.m_pI3DMainCtrl;

	// ��ȡģ�����ڵ���ͼ��Ŀǰ��ʱ��˴����Ժ�Ӧ�����ⲿ���룩
	m_opView = ::VBF_GetMainView(env.m_pI3DMainCtrl);
	if(!m_opView.valid()) return false;

	m_opCamera = m_opView->getCamera();
	if(!m_opCamera.valid()) return false;

	// ��ʼ��ģ�͵ĳ���ͼ
	if( !InitSG() ) return false;

	m_bInited = true;

	return true;
}

//-----------------------------------------------------------------------------
// ������InitSG()
// ��������ʼ��ģ�͵ĳ���ͼ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::InitSG()
{
	// ����ģ�͵ĸ��ڵ㣬�ҽ���ͼ��ڵ���
	m_piNodeRoot = new osg::Switch;
	m_piNodeRoot->setName("VBFNode_MarkRoot: " + m_strID);
	m_piNodeRoot->setValue(0, m_bVisible);
    m_piNodeRoot->setUserValue<TYPE_PTR>("VBFMarkPtr", (TYPE_PTR)this);

	// ����ģ�͵�Group�ڵ㣬�ҽ��ڸ��ڵ��£��û��Ľڵ���Ҫ�ҽ��ڸýڵ���
	m_piNodeGroup = ::VBF_CreateSGNodeGroup();
	m_piNodeGroup->setName("VBFNode_MarkGroup: " + m_strID);

	// ���ιҽ������ڵ�
	m_piNodeRoot->addChild(m_piNodeGroup);
	
	return true;
}

//-----------------------------------------------------------------------------
// ������SetLayerPtrAsNull()
// ��������ͼ��ָ������ΪNULL���ú�������ϵͳ�ڲ����ã�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetLayerPtrAsNull()
{
	m_dwLayerPtr = 0L;
}

//-----------------------------------------------------------------------------
// ������SetLayerPtr()
// ���������ø�ģ������ͼ���ָ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetLayerPtr(TYPE_PTR dwData)
{ 
	if(m_dwLayerPtr==dwData) return;

	// �ȴ�ԭ��ͼ�����Ƴ�
	if(m_dwLayerPtr!=0L) 
	{
		IVBF_3DPlotLayer* pILayerOld = (IVBF_3DPlotLayer*)m_dwLayerPtr;
		pILayerOld->RemoveMark(this);
	}

	// ����ӵ���ͼ��
	if(dwData!=0L)
	{
		IVBF_3DPlotLayer* pILayerNew = (IVBF_3DPlotLayer*)dwData;
		pILayerNew->AddMark(this);
	}

	m_dwLayerPtr = dwData; 
}

//-----------------------------------------------------------------------------
// ������SetVisible()
// ����������ģ�͵Ŀɼ���
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetVisible(bool bVisible)
{
    bool bChanged = (bVisible!=m_bVisible);
    m_bVisible = bVisible;

	// ��۲��߷�����Ϣ��ģ�Ϳɼ��Ըı���
	if(bChanged)
	{
		NotifyObservers(VBF_MESSAGE_3DPLOT_MARK_VISIBLE, bVisible, this);
	}
}

//-----------------------------------------------------------------------------
// ������NotifyObservers()
// �����������й۲��߷�����Ϣ
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::NotifyObservers(const char* szMessage, int nValue/*=0*/, void* pValue/*=NULL*/)
{
	for(CVBF_ObserverList::iterator pIter=m_ObserverList.begin(); pIter!=m_ObserverList.end(); pIter++)
	{
		observer_ptr<IVBF_ObserverRef>& piObserver = *pIter;
		if(piObserver.valid()) piObserver->OnEvent(szMessage, nValue, pValue);
	}
}

//-----------------------------------------------------------------------------
// ������GetPos()
// ��������ȡ����ģ�͵ĵ�ǰλ�ã�����и�ģ�ͣ�������ģ�͵�������ꣻ���򣬷���ģ�͵��������� 
//-----------------------------------------------------------------------------
template<class T>
const osg::Vec3d& CVBF_MarkModelImpl<T>::GetPos()
{
	// �и�ģ�ͣ�������ģ�͵��������
	if( m_pIParent!=NULL && m_pIParent->IsPointMarkModel() )
	{
		return m_vPosGeo;		
	}
	else // û�и�ģ�ͣ�����ģ�͵��������� 
	{
		return GetWorldPos();
	}
}

//-----------------------------------------------------------------------------
// ������GetWorldPos()
// ��������ȡģ�͵���������
//-----------------------------------------------------------------------------
template<class T>
const osg::Vec3d& CVBF_MarkModelImpl<T>::GetWorldPos()
{	
	// ������������Ѿ�ʧЧ����Ҫ���¼���
	if(m_bDirtyPosWorld)  
	{
        m_ipContext->GeoToWorld(m_vPosGeo, true, m_vPosWorld);

		// ȷ������������Ч
		if(::VBF_IsPosInvalid(m_vPosWorld)) return ::VBF_GetPosInvalid();

		// ���¼����������
		m_bDirtyPosWorld = false;
	}

	return m_vPosWorld;
}

//-----------------------------------------------------------------------------
// ������GetActualGeoPos()
// ��������ȡ����ģ��ʵ�ʵĵ������꣨���������ֲ��任��ĵ������꣬��ֵ��ϵͳ�ڲ����㣩
//-----------------------------------------------------------------------------
template<class T>
osg::Vec3d CVBF_MarkModelImpl<T>::GetActualGeoPos()
{
    const osg::Vec3d& ptWorld = GetWorldPos();
    if(::VBF_IsPosInvalid(ptWorld)) return ::VBF_GetPosInvalid();

    osg::Vec3d ptGeo;
    m_ipContext->WorldToGeo(ptWorld, ptGeo);
    return ptGeo;
}

//-----------------------------------------------------------------------------
// ������SetBoundingBoxVisible()
// ���������ð�Χ�еĿɼ���
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetBoundingBoxVisible(bool bVisible)
{ 
	if(m_bBoundingBoxVisible==bVisible) return;

	m_bBoundingBoxVisible = bVisible; 

	// ʹ�����ӽڵ��Χ�еĿɼ����븸�ڵ���ͬ
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;
		if(pIChild) pIChild->SetBoundingBoxVisible(bVisible);
	}

	// ʹ��Χ�нڵ�ʧЧ
	DirtyBoundingBoxNode();
}

//-----------------------------------------------------------------------------
// ������SetBoundingBoxVisibleWhenSelected()
// ����������ѡ��ģ��ʱ����Χ���Ƿ��Զ��ɼ���Ĭ��Ϊtrue��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetBoundingBoxVisibleWhenSelected(bool bVisible)
{
	if(m_bBoundingBoxVisibleWhenSelected==bVisible) return;

	m_bBoundingBoxVisibleWhenSelected = bVisible; 

	// ʹ�����ӽڵ��Χ�еĿɼ����븸�ڵ���ͬ
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;
		if(pIChild) pIChild->SetBoundingBoxVisibleWhenSelected(bVisible);
	}

	// ʹ��Χ�нڵ�ʧЧ
	DirtyBoundingBoxNode();
}

//-----------------------------------------------------------------------------
// ������SetBoundingBoxStyle()
// ���������ð�Χ�е���ʽ
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetBoundingBoxStyle(const VBF_BOUNDINGBOXSTYLE& style) 
{ 
	if(m_BoundingBoxStyle==style) return;

	m_BoundingBoxStyle = style; 

	// ʹ��Χ�нڵ�ʧЧ
	DirtyBoundingBoxNode();
}

//-----------------------------------------------------------------------------
// ������SetSelected()
// ����������ģ��ѡ�����
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetSelected(bool bSelected)
{
	if(m_bSelected==bSelected) return;

	m_bSelected = bSelected;

	// ʹ��Χ�нڵ�ʧЧ
	DirtyBoundingBoxNode();
}

//-----------------------------------------------------------------------------
// ������UpdateBoundingBox()
// ���������°�Χ�нڵ�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::UpdateBoundingBox()
{
    if(m_bDirtyBoundingBoxNode==false) return ;
    m_bDirtyBoundingBoxNode = false;
	// �жϰ�Χ���Ƿ�ɼ�
	bool bVisible = ( m_bBoundingBoxVisible || (m_bSelected && m_bBoundingBoxVisibleWhenSelected) );

    // ע�⣺����и�ģ���Ҹ�ģ�ͱ�ѡ�л��Χ�пɼ�����ģ�Ͳ��ٻ��ư�Χ��
    if(m_pIParent!=NULL && (m_pIParent->IsSelected() || m_pIParent->IsBoundingBoxVisible()) )
    {
        bVisible = false;
    }

	// ��ɾ��ԭ���İ�Χ�нڵ�
	if(m_piNodeBoundingBox.valid()) m_piNodeGroup->removeChild(m_piNodeBoundingBox);

	// �����Χ�пɼ������һ����Χ�нڵ�
	if(bVisible)
	{
		m_piNodeBoundingBox = CreateBoundingBoxNode();
		if(!m_piNodeBoundingBox.valid()) return;
		
		m_piNodeGroup->addChild(m_piNodeBoundingBox);

		// ���ð�Χ�в��ֵ���Ⱦ״̬��ʹ����ɫ����
		
		// ��Χ�в��ֲ�ʹ������
		osg::StateSet* ss = m_piNodeBoundingBox->getOrCreateStateSet();
		ss->setTextureMode(0, GL_TEXTURE_2D, osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED|osg::StateAttribute::OVERRIDE);
		
		// ������Ⱦ˳��
		ss->setRenderBinDetails(m_nBinNumberBox, "DepthSortedBin");	

		// ������ɫ��
		SetShader_BoundingBox(ss);
	}
}

//-----------------------------------------------------------------------------
// ������SetReserveFlag()
// ����������/��ȡԤ����־��ϵͳʹ�������4λ
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetReserveFlag(DWORD dwFlag, bool bOR)
{
	if(bOR) m_dwReserveFlag = (m_dwReserveFlag | dwFlag);
	else    m_dwReserveFlag = (m_dwReserveFlag & dwFlag);
}


//-----------------------------------------------------------------------------
// ������AddToParentNode()
// ��������ӵ�����ͼ�ĸ��ڵ�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::AddToParentNode()
{
    // �ȴ�ԭ���ĸ��ڵ����Ƴ�
    if(m_bNodeToRemoveFromParent)
    {
        if(m_piNodeParentOld.valid()) m_piNodeParentOld->removeChild( GetRootNode() );
        m_bNodeToRemoveFromParent = false;
    }

    // ����ӵ��µĸ��ڵ�
    if(m_bNodeToAddToParent)
    {
        if(m_piNodeParent.valid()) m_piNodeParent->addChild( GetRootNode() );
        m_bNodeToAddToParent = false;
    }

	// �ȴ���ӵ����ڵ��ͼ�㣨��Ө��ӣ�2017-11-30��
	if(m_bNodeToAddToParentLayer)
    {
		// �������и�ģ�ͣ�ֱ���ҵ�һ��ͼ��ָ��
        IVBF_MarkModel* pIParent = this->GetParent();
        while(pIParent)
        {
			IVBF_3DPlotLayer* pILayer = (IVBF_3DPlotLayer*)pIParent->GetLayerPtr();
            if(pILayer)
            {
                this->SetParentNode( pILayer->GetNodeForNotPointMarks() );
                break;
            }
            pIParent = pIParent->GetParent();
        }
        m_bNodeToAddToParentLayer = false;
    }
}

//-----------------------------------------------------------------------------
// ������UpdateSGNode()
// ����������ĳЩ����ͼ�ڵ������
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::UpdateSGNode()
{
    if(m_piNodeRoot.valid())
    {
        // �ж�ģ�ͱ����Ƿ�ɼ�
        m_piNodeRoot->setNodeMask(m_bVisible? ~0 : 0);
    }
}

//-----------------------------------------------------------------------------
// ������ClipByDist()
// �����������ӵ㵽ģ�͵ľ��룬�ж�ģ��/�����Ƿ��ڿɼ�������
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::ClipByDist()
{
    // ���ģ�Ϳɼ����ٸ����ӵ㵽ģ�͵ľ��룬�ж�ģ��/�����Ƿ��ڿɼ�������
    if(m_bVisible)
    {
        bool bAttrChild = (m_pIParent!=NULL && (m_dwReserveFlag & VBF_RESERVEFLAG_ATTRCHILD));
        if(!bAttrChild)
        {
            ClipModelByDist();    // �ж�ģ���Ƿ��ڿɼ�������
        }
        else
        {
            ClipAttrByDist();   // �ж������Ƿ��ڿɼ�������
        }
    }
}

//-----------------------------------------------------------------------------
// ������ClipModelByDist()
// �����������ӵ㵽ģ�͵ľ��룬�ж�ģ���Ƿ��ڿɼ�������
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::ClipModelByDist()
{
    if(m_bVisible && m_piNodeRoot.valid())
    {
        const osg::Vec3d& ptWorld = GetWorldPos();
        if(::VBF_IsPosInvalid(ptWorld)) return; // ȷ������������Ч

        IVBF_GlobalDataPerView* pData = VBF_Get3DGlobalData(m_opView.get());
        const osg::Vec3d& ptEye = pData->GetEyePtInWorld();
        m_dDistToEye   = (ptEye - ptWorld).length();
        m_bInDistRange = (m_dDistToEye>=m_fDistMin && m_dDistToEye<=m_fDistMax);

        m_piNodeRoot->setNodeMask( (m_bVisible && m_bInDistRange)? ~0 : 0 );
    }
}

//-----------------------------------------------------------------------------
// ������ClipAttrByDist()
// �����������ӵ㵽ģ�͵ľ��룬�ж�ģ�͵�ĳ�������Ƿ��ڿɼ�������
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::ClipAttrByDist()
{
    // ����������Դ������ӽڵ㣬ǿ��ʹ��ɼ����븸�ڵ㱣��һ��
    if(m_pIParent!=NULL && m_piNodeRoot.valid())
    {
        m_dDistToEye   = m_pIParent->GetDistToEye();
        m_bInDistRange = m_pIParent->IsInDistRange();
        m_piNodeRoot->setNodeMask( (m_bVisible && m_bInDistRange)? ~0 : 0 );
    }
}


//-----------------------------------------------------------------------------
// ������Update()
// ���������� (ÿ֡����ǰ����)
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::Update()
{
    // ��ӵ�����ͼ�ĸ��ڵ�
    AddToParentNode();

    // ����ĳЩ����ͼ�ڵ������
    UpdateSGNode();

    if(!m_bVisible) return false;

    // ����ģ�ͽڵ�
	if(m_bDirtyModel)
    {
        UpdateModelNode();
		m_bDirtyModel = false;
	}

	// ����ģ�͵�λ��
	UpdatePos();

	// �����ӵ㵽ģ�͵ľ��룬�ж�ģ��/�����Ƿ��ڿɼ�������
	ClipByDist();

	// ������Ĳü�
	ClipByEarth();

	// ����������ģ��
    UpdateChildren();

    // ������������
    UpdateAttrs();

    // ���°�Χ�нڵ�
    UpdateBoundingBox();

	// ������Ⱦ״̬
	if(m_bDirtyStateSet)
	{
		SetStateSet();
		m_bDirtyStateSet = false;
	}

    // ģ�Ͷ���/��Ч
    UpdateByActions();
    UpdateByEffects();

	return true;
}

template<class T>
void CVBF_MarkModelImpl<T>::ProcessSimulate(IVBF_SimulationTimer* pSimulationTimer)
{
    for(CVBF_ProcessList::iterator pIter=m_MarkProcessList.begin(); pIter!=m_MarkProcessList.end(); pIter++)
    {
        ref_ptr<IVBF_MarkProcess>& ipIProcess = *pIter;
        if(ipIProcess.valid())ipIProcess->ProcessSimulate(pSimulationTimer);
    }
}

template<class T>
void CVBF_MarkModelImpl<T>::StatStartTime(double& dStartTime)
{
    for(CVBF_ProcessList::iterator pIter=m_MarkProcessList.begin(); pIter!=m_MarkProcessList.end(); pIter++)
    {
        ref_ptr<IVBF_MarkProcess>& ipIProcess = *pIter;
        if(ipIProcess.valid())ipIProcess->StatStartTime(dStartTime);
    }
}

//-----------------------------------------------------------------------------
// ������UpdateModelNode()
// ����������ģ�ͽڵ�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::UpdateModelNode()
{
    // ��ɾ��ԭ������ģ�ͽڵ�
    if( m_piNodeModel.valid() && m_piNodeGroup.valid() )
    {
        m_piNodeGroup->removeChild(m_piNodeModel);
    }

    // �ٴ����µ�ģ�ͽڵ�
    if( CreateModelNode() && m_piNodeModel.valid() )
    {
        m_piNodeModel->setName("VBFNode_MarkModel: " + m_strID);
        m_piNodeGroup->addChild(m_piNodeModel);

        // ���¸��ڵ�İ�Χ��
        m_piNodeModel->dirtyBound();
    }
}

//-----------------------------------------------------------------------------
// ������UpdateChildren()
// ����������������ģ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::UpdateChildren()
{
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;
		if(NULL==pIChild) continue;

		DWORD dwReserveFlag = pIChild->GetReserveFlag();
		if(dwReserveFlag & VBF_RESERVEFLAG_ATTRCHILD)
        {
       //   pIChild->SetDistMin(m_fDistMin);  // ���������Ե�Update()�����У���Ө�޸ģ�2015-12-01��
       //   pIChild->SetDistMax(m_fDistMax);
            continue; // ע�⣺�����Դ�������ģ�Ͳ��ڴ˴�����
        }
		
		pIChild->Update();
	}
}


//-----------------------------------------------------------------------------
// ������SetGeoPos()
// ����������ģ�͵ĵ�������
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetGeoPos(const osg::Vec3d& vPos)		
{ 
	m_vPosGeo = vPos;

    // ʹ����/��������ʧЧ
    DirtyPosGeo();
	DirtyPosWorld();

	// ʹ��Χ��ʧЧ
	DirtyBoundingBoxInWorld();

	// �߼��ϣ�UpdatePos()����ֻ��Ҫ��Transform()�����е��ã�Ϊʲô�����ڴ˴�����һ�²��ܻ��Ƴ�ģ�� ???
//	UpdatePos();

	// ʹ�����ӽڵ������ҲʧЧ����Ө��ӣ�2013-12-04��
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;
		if(pIChild!=NULL) pIChild->SetGeoPos( pIChild->GetGeoPos() );
	}
}

//-----------------------------------------------------------------------------
// ������GetBoundingBoxNode()
// ��������ȡ�����Χ��ʱʹ�õĽڵ�
//-----------------------------------------------------------------------------
template<class T>
osg::IVBF_SGNode* CVBF_MarkModelImpl<T>::GetBoundingBoxNode()
{
    if(m_piNodeModel.valid())
        return m_piNodeModel.get();

    else if(m_piNodeGroup.valid() && m_piNodeGroup->getNumChildren()>0)
        return m_piNodeGroup.get();

    else if(m_piNodeRoot.valid())
        return m_piNodeRoot.get();

    else
        return NULL;
}
	
//-----------------------------------------------------------------------------
// ������GetBoundingBoxInModel()
// ����������ģ������ϵ�µİ�Χ��
//-----------------------------------------------------------------------------
template<class T>
const osg::BoundingBox& CVBF_MarkModelImpl<T>::GetBoundingBoxInModel() 
{ 
	if(m_bDirtyBoundingBoxInModel)
	{
        osg::IVBF_SGNode* pNode = GetBoundingBoxNode();
        if(NULL==pNode) return m_BoundingBoxInModel;

        CVBF_NodeUtil::GetNodeBoundingBox(pNode, m_BoundingBoxInModel);
        if(!m_BoundingBoxInModel.valid()) return m_BoundingBoxInModel;

		m_bDirtyBoundingBoxInModel = false;
	}
	
	return m_BoundingBoxInModel; 
}

//-----------------------------------------------------------------------------
// ������GetBoundingBoxInWorld()
// ������������������ϵ�µİ�Χ��
//-----------------------------------------------------------------------------
template<class T>
const osg::BoundingBox& CVBF_MarkModelImpl<T>::GetBoundingBoxInWorld()
{
	if(m_bDirtyBoundingBoxInWorld)
	{
        m_BoundingBoxInWorld = GetBoundingBoxInModel();
        if(!m_BoundingBoxInWorld.valid()) return m_BoundingBoxInWorld;

		m_bDirtyBoundingBoxInWorld = false;
	}

	return m_BoundingBoxInWorld;
}

//-----------------------------------------------------------------------------
// ������GetBoundingBoxInGeo()
// �����������������ϵ�µİ�Χ��
//-----------------------------------------------------------------------------
template<class T>
const osg::BoundingBoxd& CVBF_MarkModelImpl<T>::GetBoundingBoxInGeo()
{
	if(!m_bDirtyBoundingBoxInGeo) return m_BoundingBoxInGeo;

	const osg::BoundingBox& boxInWorld = GetBoundingBoxInWorld();
	if(!boxInWorld.valid()) return m_BoundingBoxInGeo;

	// �������ڵ�������ϵ�еİ�Χ��
	double dLMin = +DBL_MAX;
	double dLMax = -DBL_MAX;
	double dBMin = +DBL_MAX;
	double dBMax = -DBL_MAX;
	double dHMin = +DBL_MAX;
	double dHMax = -DBL_MAX;

	for(int i=0; i<8; i++)
	{
		osg::Vec3d ptWorldOld = boxInWorld.corner(i);

		// �������� --> ��������
        osg::Vec3d ptGeo;
        m_ipContext->WorldToGeo(ptWorldOld, ptGeo);

		if(ptGeo.x() < dLMin) dLMin = ptGeo.x();
		if(ptGeo.x() > dLMax) dLMax = ptGeo.x();

		if(ptGeo.y() < dBMin) dBMin = ptGeo.y();
		if(ptGeo.y() > dBMax) dBMax = ptGeo.y();

		if(ptGeo.z() < dHMin) dHMin = ptGeo.z();
		if(ptGeo.z() > dHMax) dHMax = ptGeo.z();
	}

	// ���õ�������ϵ�µ������Сֵ��������Χ��
	m_BoundingBoxInGeo.xMin() = dLMin;
	m_BoundingBoxInGeo.xMax() = dLMax;

	m_BoundingBoxInGeo.yMin() = dBMin;
	m_BoundingBoxInGeo.yMax() = dBMax;

	m_BoundingBoxInGeo.zMin() = dHMin;
	m_BoundingBoxInGeo.zMax() = dHMax;

	m_bDirtyBoundingBoxInGeo = false;

	return m_BoundingBoxInGeo;
}

//-----------------------------------------------------------------------------
// ������GetBoundingBoxCenterGeo()
// ��������ȡģ�Ͱ�Χ�����ĵĵ�������
//-----------------------------------------------------------------------------
template<class T>
osg::Vec3d CVBF_MarkModelImpl<T>::GetBoundingBoxCenterGeo()
{
	const osg::BoundingBox& box = GetBoundingBoxInWorld();

    osg::Vec3d vGeo;
    if(m_ipContext->WorldToGeo(box.center(),vGeo))
    {
        return vGeo;
    }
	return ::VBF_GetPosInvalid();
}

//-----------------------------------------------------------------------------
// ������LookupMarkAttrIFF()
// ����������ģ�͵ĵ����������
//-----------------------------------------------------------------------------
template<class T>
IVBF_MarkAttrIFF* CVBF_MarkModelImpl<T>::LookupMarkAttrIFF()
{
	// ǿ��ʹ�ø��ڵ��IFF����
	IVBF_MarkModel*   pIMark    = (m_pIParent!=NULL)? m_pIParent : this;
	IVBF_MarkAttrIFF* pIAttrIFF = (IVBF_MarkAttrIFF*)pIMark->LookupMarkAttr(VBF_MARK_ATTR_IFF);

	return pIAttrIFF;
}


//-----------------------------------------------------------------------------
// ������GetChildCount()
// ��������ȡ��ģ�͸���
//-----------------------------------------------------------------------------
template<class T>
int CVBF_MarkModelImpl<T>::GetChildCount()
{ 
	int nCount = 0;
	
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;
		if(NULL==pIChild) continue;

		DWORD dwReserveFlag = pIChild->GetReserveFlag(); 
		if(dwReserveFlag & VBF_RESERVEFLAG_ATTRCHILD) continue; // ע�⣺��Ҫ���˵����Դ�������ģ��

		nCount++;
	}
	return nCount;
}

//-----------------------------------------------------------------------------
// ������GetChild()
// ��������ģ�ͱ��� (nIndex�����ʾ���Ե����)
//-----------------------------------------------------------------------------
template<class T>
IVBF_MarkModel* CVBF_MarkModelImpl<T>::GetChild(int nIndex) 
{ 
	int idx = -1;
	
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;
		if(pIChild==NULL) continue;

		DWORD dwReserveFlag = pIChild->GetReserveFlag(); 
		if(dwReserveFlag & VBF_RESERVEFLAG_ATTRCHILD) continue; // ע�⣺��Ҫ���˵����Դ�������ģ��

		idx++;
		if(idx==nIndex) return pIChild;			
	}

	return NULL;
}

//-----------------------------------------------------------------------------
// ������GetChild()
// ��������ȡ��ģ��
//-----------------------------------------------------------------------------
template<class T>
IVBF_MarkModel* CVBF_MarkModelImpl<T>::GetChild(const std::string& strChildID)
{
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;

		DWORD dwReserveFlag = pIChild->GetReserveFlag(); 
		if(dwReserveFlag & VBF_RESERVEFLAG_ATTRCHILD) continue; // ע�⣺��Ҫ���˵����Դ�������ģ��

		if(strChildID==pIChild->GetID()) return pIChild;
	}

	return NULL;
}

//-----------------------------------------------------------------------------
// ������GetChildNested()
// ��������ȡ��ģ��
//-----------------------------------------------------------------------------
template<class T>
IVBF_MarkModel* CVBF_MarkModelImpl<T>::GetChildNested(const std::string& strChildID)
{
    int nNumChildren = GetChildCount();
    if(nNumChildren==0) return NULL;

    IVBF_MarkModel* pIChild = GetChild(strChildID);
    if(pIChild!=NULL) return pIChild;

    for(int i=0; i<nNumChildren; i++)
    {
        pIChild = GetChild(i);
        if(NULL==pIChild) continue;

        IVBF_MarkModel* pIChildNested = pIChild->GetChildNested(strChildID);
        if(pIChildNested!=NULL) return pIChildNested;
    }

    return NULL;
}

//-----------------------------------------------------------------------------
// ������GetParentalPaths()
// ��������ȡ����ģ�͵ĸ�ģ�Ͳ���б�����㸸ģ�Ϳ�ʼ������ģ�ͽ�����
//-----------------------------------------------------------------------------
template<class T>
std::vector<IVBF_MarkModel*> CVBF_MarkModelImpl<T>::GetParentalPaths()
{
    std::vector<IVBF_MarkModel*> vPaths;
    vPaths.clear();

    IVBF_MarkModel* pIParent = this;
    while(pIParent)
    {
        vPaths.push_back(pIParent);
        pIParent = pIParent->GetParent();
    }

    if(vPaths.size() > 0)
    {
        std::reverse(vPaths.begin(), vPaths.end());
    }

    return vPaths;
}

//-----------------------------------------------------------------------------
// ������AddChild()
// ���������һ���ӽڵ�
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::AddChild(IVBF_MarkModel* pIChild)
{
	if(NULL==pIChild) return false;

	// �������ظ����ͬһ���ӽڵ�
	for(unsigned int i=0; i<m_vChildren.size(); i++)
	{
		IVBF_MarkModel* pIChildT = m_vChildren[i];
		if(pIChildT==pIChild) return false;
	}

	pIChild->SetParent(this);
	m_vChildren.push_back(pIChild);

    // ����ģ�������µĸ��ڵ㣨��Ө�޸ģ�2014-12-12��
    if( !this->IsPointMarkModel() )
    {
        pIChild->SetParentNode(this->m_piNodeGroup);
    }
    else
    {
        if( pIChild->IsPointMarkModel() )  // ��ģ���ǵ�״����ģ��Ҳ�ǵ�״
        {
            pIChild->SetParentNode(this->m_piNodeGroup);
        }
        else  // ��ģ���ǵ�״������ģ�Ͳ��ǵ�״
        {
            // ��Ҫ����ģ�͵ĸ��ڵ���ӵ�Plotר�����õ�һ���ڵ��£�������ģ���ܵ���ģ�ͻ���ϲ㸸ģ�;����Ӱ�죨��Ө�޸ģ�2015-06-03��
        //  IVBF_3DPlotLayer* pILayer = (IVBF_3DPlotLayer*)m_dwLayerPtr;
        //  if(pILayer) pIChild->SetParentNode(pILayer->GetNodeForNotPointMarks()); // ������ڵ���ͼ��ָ�룬��ӵ����ڵ����ڵ�ͼ��

			// �п��ܸ��ڵ������û��ͼ��ָ�룬���ߴ�ʱ��δ��ӵ�ͼ�㣬���Դ˴�������ʶ����Ө�޸ģ�2017-11-30��
			pIChild->WaitForAddingToParentLayer();
        }
    }

	// ʹ��Χ��ʧЧ
	DirtyBoundingBoxNode();
	DirtyBoundingBoxInModel();
	DirtyBoundingBoxInWorld();

	return true;
}

//-----------------------------------------------------------------------------
// ������RemoveChild()
// �������Ƴ�һ���ӽڵ㣬����ɾ���ӽڵ�ָ��
//-----------------------------------------------------------------------------
template<class T>
IVBF_MarkModel* CVBF_MarkModelImpl<T>::RemoveChild(const std::string& strChildID)
{
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		ref_ptr<IVBF_MarkModel> pIChild = *pIter;
		if(pIChild.valid() && pIChild->GetID()==strChildID)
		{
            pIChild->SetParentNode(NULL);  // �����ģ�͵ĸ��ڵ�

			m_vChildren.erase(pIter);
			return pIChild.release();
		}
	}

	return NULL;
}

//-----------------------------------------------------------------------------
// ������RemoveChild()
// �������Ƴ�һ���ӽڵ㣬����ɾ���ӽڵ�ָ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::RemoveChild(IVBF_MarkModel* pIChild)
{
	if(NULL==pIChild) return;

	CVBF_MarkList::iterator pIter = std::find(m_vChildren.begin(), m_vChildren.end(), pIChild);
	if(pIter!=m_vChildren.end())
	{
		pIChild->SetParentNode(NULL);	// �����ģ�͵ĸ��ڵ�
		pIChild->SetParent(NULL);		// �����ģ�͵ĸ�ģ�ͣ���Ө��ӣ�2015-04-17��
		m_vChildren.erase(pIter);
	}
}

//-----------------------------------------------------------------------------
// ������DeleteChild()
// ������ɾ��һ���ӽڵ㣬ͬʱɾ����ָ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DeleteChild(const std::string& strChildID)
{
	IVBF_MarkModel* pIChild = GetChild(strChildID);
	DeleteChild(pIChild);
}

//-----------------------------------------------------------------------------
// ������DeleteChild()
// ������ɾ��һ���ӽڵ㣬ͬʱɾ����ָ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DeleteChild(IVBF_MarkModel* pIChild)
{
	if(NULL==pIChild) return;

	CVBF_MarkList::iterator pIter = std::find(m_vChildren.begin(), m_vChildren.end(), pIChild);
	if(pIter!=m_vChildren.end())
	{
		pIChild->SetParentNode(NULL);  // �����ģ�͵ĸ��ڵ�
		m_vChildren.erase(pIter);
	}
}

//-----------------------------------------------------------------------------
// ������DeleteAllChildren()
// ������ɾ��������ģ�ͼ���ָ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DeleteAllChildren()
{
	for(CVBF_MarkList::iterator pIterChild=m_vChildren.begin(); pIterChild!=m_vChildren.end(); pIterChild++)
	{
		ref_ptr<IVBF_MarkModel> pIChild = *pIterChild;
        pIChild->SetParentNode(NULL);  // �����ģ�͵ĸ��ڵ�
	}
	m_vChildren.clear();
}

//-----------------------------------------------------------------------------
// ������GetChildGeoPos()
// ������������ģ���ڸ�ģ���е�λ�ã�������ģ�͵ĵ�������
//-----------------------------------------------------------------------------
template<class T>
osg::Vec3d CVBF_MarkModelImpl<T>::GetChildGeoPos(const std::string& strChildID)
{
	IVBF_MarkModel* pIChild = GetChild(strChildID);
	if(NULL==pIChild) return ::VBF_GetPosInvalid();

//!!
/*
	if( m_opMapNode.valid() )
	{
		osg::Vec3d ptWorld = pIChild->GetWorldPos();
		if(::VBF_IsPosInvalid(ptWorld)) return ::VBF_GetPosInvalid();

		osgEarth::GeoPoint ptGeoT;
		if( ptGeoT.fromWorld(m_opMapNode->GetMapSRS(), ptWorld) )
		{
			osg::Vec3d ptGeo = ptGeoT.vec3d();
			return ptGeo;
		}
	}
*/


    osg::Vec3d ptWorld = pIChild->GetWorldPos();
    if(::VBF_IsPosInvalid(ptWorld)) return ::VBF_GetPosInvalid();

    osg::Vec3d ptGeo;
    if(m_ipContext->WorldToGeo(ptWorld,ptGeo))
    {
        return ptGeo;
    }


	
	return ::VBF_GetPosInvalid();
}

//-----------------------------------------------------------------------------
// ������ApartChild()
// ����������һ����ģ��
//-----------------------------------------------------------------------------
template<class T>
IVBF_MarkModel* CVBF_MarkModelImpl<T>::ApartChild(const std::string& strChildID)
{
	ref_ptr<IVBF_MarkModel> piChild = GetChild(strChildID);
	if(!piChild.valid()) return NULL;

	// ����������ģ���ڸ�ģ���е�λ�ã�������ģ�͵ĵ�������
	osg::Vec3d vChildGeo = GetChildGeoPos(strChildID);
	piChild->SetGeoPos(vChildGeo);

	// ���ݸ�ģ�͵���̬��������ģ�͵���̬
	if( piChild->IsPointMarkModel() )
	{
		IVBF_MarkModelPoint* pIChildPoint = (IVBF_MarkModelPoint*)piChild.get();

		float fRotateX = 0.0f;
		float fRotateY = 0.0f;
		float fRotateZ = 0.0f;

		float fScaleX = 1.0f;
		float fScaleY = 1.0f;
		float fScaleZ = 1.0f;
				
		if( this->IsPointMarkModel() )
		{
			((IVBF_MarkModelPoint*)this)->GetRotate(fRotateX, fRotateY, fRotateZ);
			((IVBF_MarkModelPoint*)this)->GetScale(fScaleX, fScaleY, fScaleZ);
		}
		pIChildPoint->SetRotate(fRotateX, fRotateY, fRotateZ);
		pIChildPoint->SetScale(fScaleX, fScaleY, fScaleZ);
	}

	RemoveChild(piChild);

	return piChild.release();
}

//-----------------------------------------------------------------------------
// ������EnableDepthTest()
// ������ǿ�п���/�ر���Ȳ��ԣ�Ĭ��Ϊ������
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::EnableDepthTest(bool bEnable)
{ 
	if(m_bEnableDepthTest==bEnable) return;

	m_bEnableDepthTest = bEnable;
    DirtyStateSet();
}

//-----------------------------------------------------------------------------
// ������EnableDepthWrite()
// ������ǿ�п���/�ر����д�루Ĭ��Ϊ������
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::EnableDepthWrite(bool bEnable)
{ 
	if(m_bEnableDepthWrite==bEnable) return;

	m_bEnableDepthWrite = bEnable;
    DirtyStateSet();
}

//-----------------------------------------------------------------------------
// ������EnableLight()
// ������ǿ�п���/�رչ��� (Ĭ��Ϊ�ر�)
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::EnableLight(bool bEnable) 
{ 
	if(m_bEnableLight==bEnable) return;

	m_bEnableLight = bEnable;
	DirtyStateSet();
}

//-----------------------------------------------------------------------------
// ������EnablePointSmooth()
// ������ǿ�п���/�رյ�⻬ (Ĭ��Ϊ����)
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::EnablePointSmooth(bool bEnable) 
{ 
	if(m_bEnablePointSmooth==bEnable) return;

	m_bEnablePointSmooth = bEnable;
	DirtyStateSet();
}

//-----------------------------------------------------------------------------
// ������EnableLineSmooth()
// ������ǿ�п���/�ر��߹⻬ (Ĭ��Ϊ����)
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::EnableLineSmooth(bool bEnable) 
{ 
	if(m_bEnableLineSmooth==bEnable) return;

	m_bEnableLineSmooth = bEnable;
	DirtyStateSet();
}

//-----------------------------------------------------------------------------
// ������EnablePolygonSmooth()
// ������ǿ�п���/�ر���⻬ (Ĭ��Ϊ�ر�)
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::EnablePolygonSmooth(bool bEnable) 
{ 
	if(m_bEnablePolygonSmooth==bEnable) return;

	m_bEnablePolygonSmooth = bEnable;
	DirtyStateSet();
}

//-----------------------------------------------------------------------------
// ����: SetShader_BoundingBox()
// ����: �԰�Χ��������ɫ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetShader_BoundingBox(osg::StateSet* ss)
{
	if(NULL==ss) return;

	// ���ò���
    ref_ptr<osg::Material> ipMaterial = new osg::Material;
    ipMaterial->setColorMode(osg::Material::DIFFUSE);
    ipMaterial->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
    ipMaterial->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
    ipMaterial->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
    ipMaterial->setShininess(osg::Material::FRONT_AND_BACK, 100.0f);  // ��ЧֵΪ[0.0, 128.0]��ֵԽ�󣬸߹���ԽС
    ipMaterial->setEmission(osg::Material::FRONT_AND_BACK,osg::Vec4(0, 0, 0, 1));
    ss->setAttributeAndModes(ipMaterial.get(), osg::StateAttribute::ON);

	// ���ù���ģ��
    ref_ptr<osg::LightModel> ipLightModel = new osg::LightModel;
    ipLightModel->setAmbientIntensity(osg::Vec4(0.1f, 0.1f, 0.1f, 1.0f));
    ss->setAttributeAndModes(ipLightModel, osg::StateAttribute::ON);

	// ������ɫ��
	osg::Program* pProg = ::VBF_CreateShader(::VBF_Get3DEnvironment().m_pI3DMainCtrl, "GraphicsSolid.vert", "GraphicsSolid.frag");
	if(NULL==pProg) return;

	ss->addUniform( new osg::Uniform("bEnableColor", true) );
	ss->addUniform( new osg::Uniform("bEnableTex",   false) );
	ss->addUniform( new osg::Uniform("bEnableLight", true) );
	ss->addUniform( new osg::Uniform("bEnableFog",   false) );

	ss->setAttributeAndModes( pProg, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE|osg::StateAttribute::PROTECTED );
}

//-----------------------------------------------------------------------------
// ����: SetStateSet()
// ����: ������Ⱦ״̬
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetStateSet()
{   
    if( m_piNodeRoot.valid() )
    {
        osg::StateSet* ss = m_piNodeRoot->getOrCreateStateSet();

        // ����/�ر���Ȳ��Ժ����д��
        osg::Depth* pDepth = dynamic_cast<osg::Depth*>( ss->getAttribute(osg::StateAttribute::DEPTH) );
        if(NULL==pDepth) pDepth = new osg::Depth;

        pDepth->setFunction(m_bEnableDepthTest? osg::Depth::LEQUAL : osg::Depth::ALWAYS);
        pDepth->setWriteMask(m_bEnableDepthWrite);
        ss->setAttributeAndModes(pDepth, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE|osg::StateAttribute::PROTECTED);

        // ����ģ�͵���Ⱦ˳��
        if(m_nBinNumber.isSet()) ss->setRenderBinDetails(m_nBinNumber.value(), m_strBinName, osg::StateSet::USE_RENDERBIN_DETAILS);

    }

    // ��ɫ���
    std::vector< ref_ptr<osg::IVBF_SGNode> > vBlendNodes;
    GetBlendNodes(vBlendNodes);
    for(unsigned int i=0; i<vBlendNodes.size(); i++)
    {
        ref_ptr<osg::IVBF_SGNode>& piBlendNode = vBlendNodes[i];
        if(!piBlendNode.valid()) continue;

        if(m_bEnableBlendColor)
            ::VBF_AddEffectToNode_Blend(piBlendNode, m_colorBlend, m_bBlendModulate);
        else
            ::VBF_RemoveEffectFromNode_Blend(piBlendNode);
    }

	// ����ģ�͵���Ⱦ״̬
	if( m_piNodeModel.valid() )
	{
		osg::StateSet* ss = m_piNodeModel->getOrCreateStateSet();

		// ����/�رչ��գ��д��޸ģ�
		int nValue = (m_bEnableLight)? osg::StateAttribute::ON : osg::StateAttribute::OFF;
		ss->setMode(GL_LIGHTING, nValue|osg::StateAttribute::PROTECTED|osg::StateAttribute::OVERRIDE);

		// ����/�رչ⻬
		::VBF_EnablePointSmooth(ss, m_bEnablePointSmooth);
		::VBF_EnableLineSmooth(ss, m_bEnableLineSmooth);
		::VBF_EnablePolygonSmooth(ss, m_bEnablePolygonSmooth);


#if !defined(OSG_GLES2_AVAILABLE)
        ss->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
#endif
    }
}

//-----------------------------------------------------------------------------
// ������SetBlendColor()
// ����������ģ���Ƿ��ɫ�Լ���ϵ���ɫ����ϵķ�ʽ����ɫ/�滻ɫ��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetBlendColor(bool bEnable, const osg::Vec4f& color, bool bModulate)
{
	if(m_bEnableBlendColor==bEnable && m_colorBlend==color && m_bBlendModulate==bModulate)
	{
		return;
	}

	m_bEnableBlendColor = bEnable;
	m_bBlendModulate    = bModulate;

	m_colorBlend.r() = osg::clampBetween(color.r(), 0.0f, 1.0f);
	m_colorBlend.g() = osg::clampBetween(color.g(), 0.0f, 1.0f);
	m_colorBlend.b() = osg::clampBetween(color.b(), 0.0f, 1.0f);
	m_colorBlend.a() = osg::clampBetween(color.a(), 0.0f, 1.0f);

    // ʹ��Ⱦ״̬ʧЧ
    DirtyStateSet();

	// ʹ�����ӽڵ��ɫ
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		ref_ptr<IVBF_MarkModel>& piChild = *pIter;
		if(!piChild.valid() || (piChild->GetReserveFlag() & VBF_RESERVEFLAG_ATTRCHILD)) continue;
		if(!piChild->IsBlendWithParentEnabled()) continue;

		piChild->SetBlendColor(bEnable, color, bModulate);
	}
}

//-----------------------------------------------------------------------------
// ������AddMarkAttr()
// ������Ϊģ�����һ������
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::AddMarkAttr(IVBF_MarkAttr* pIAttr)
{
	if(NULL==pIAttr) return false;

	// ���������������ظ�
	unsigned int nAttrType = (unsigned int)pIAttr->GetType();
	if(LookupMarkAttr(nAttrType)!=NULL) return false;

	pIAttr->SetMarkModel(this);
	m_MarkAttrList.push_back(pIAttr);

	return true;
}

//-----------------------------------------------------------------------------
// ������AddMarkAttr()
// ������Ϊģ�����һ�����ԣ�����������Ѿ����ڣ�ֱ�ӷ���ԭ�������Խӿ�
//-----------------------------------------------------------------------------
template<class T>
IVBF_MarkAttr* CVBF_MarkModelImpl<T>::AddMarkAttr(unsigned int nAttrType)
{
	IVBF_MarkAttr* pIAttr = LookupMarkAttr(nAttrType);
	if(pIAttr!=NULL) return pIAttr;

	CVBF_3DEnvironment& env = ::VBF_Get3DEnvironment();
	if(env.m_pI3DPlot!=NULL)
	{
		pIAttr = env.m_pI3DPlot->CreateMarkAttr(nAttrType);
		if(pIAttr!=NULL) AddMarkAttr(pIAttr);
	}
	
	return pIAttr;
}

//-----------------------------------------------------------------------------
// ������DeleteMarkAttr()
// ������ɾ��ģ�͵�ĳ������
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DeleteMarkAttr(unsigned int nAttrType)
{
	for(CVBF_AttrList::iterator pIter=m_MarkAttrList.begin(); pIter!=m_MarkAttrList.end(); pIter++)
	{
        ref_ptr<IVBF_MarkAttr>& pIAttr = *pIter;
        if(pIAttr.valid() && pIAttr->GetType()==nAttrType)
		{
			m_MarkAttrList.erase(pIter);
			return;
		}
	}
}

//-----------------------------------------------------------------------------
// ������LookupMarkAttr()
// ����������ģ�͵�ĳ������
//-----------------------------------------------------------------------------
template<class T>
IVBF_MarkAttr* CVBF_MarkModelImpl<T>::LookupMarkAttr(unsigned int nAttrType)
{
	for(CVBF_AttrList::iterator pIter=m_MarkAttrList.begin(); pIter!=m_MarkAttrList.end(); pIter++)
	{
        ref_ptr<IVBF_MarkAttr>& pIAttr = *pIter;
        if(pIAttr.valid() && pIAttr->GetType()==nAttrType) return pIAttr.get();
	}
	return NULL;
}

//-----------------------------------------------------------------------------
// ������UpdateAttrs()
// ������������������
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::UpdateAttrs()
{
	for(CVBF_AttrList::iterator pIter=m_MarkAttrList.begin(); pIter!=m_MarkAttrList.end(); pIter++)
	{
        ref_ptr<IVBF_MarkAttr>& pIAttr = *pIter;
        if(pIAttr.valid()) pIAttr->Update();
	}
}



//-----------------------------------------------------------------------------
// ������AddMarkAction()
// ������Ϊģ�����һ����Ϊ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::AddMarkAction(IVBF_MarkAction* pIAction)
{
    if(NULL==pIAction) return false;

    pIAction->SetMarkModel(this);
    m_MarkActionList.push_back(pIAction);

    return true;
}

//-----------------------------------------------------------------------------
// ������DeleteMarkAction()
// ������ɾ��ģ�͵�ĳ����Ϊ
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DeleteMarkAction(unsigned int nIndex)
{
    if(nIndex<0 || nIndex>=m_MarkActionList.size()) return;

    CVBF_ActionList::iterator pIterBegin = m_MarkActionList.begin();
    m_MarkActionList.erase(pIterBegin+nIndex);
}


//-----------------------------------------------------------------------------
// ������AddMarkProcess()
// ������Ϊģ�����һ�����ݹ���
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::AddMarkProcess(IVBF_MarkProcess* pIProcess)
{
    if(NULL==pIProcess) return false;

    pIProcess->SetMarkModel(this);
    m_MarkProcessList.push_back(pIProcess);

    return true;
}

//-----------------------------------------------------------------------------
// ������DeleteMarkProcess()
// ������ɾ��ģ�͵�ĳ�����ݹ���
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DeleteMarkProcess(unsigned int nIndex)
{
    if(nIndex<0 || nIndex>=m_MarkProcessList.size()) return;

    CVBF_ProcessList::iterator pIterBegin = m_MarkProcessList.begin();
    m_MarkProcessList.erase(pIterBegin+nIndex);
}

//-----------------------------------------------------------------------------
// ������SetRenderOrder_Opaque()
// ���������ò�͸��ģ�͵���Ⱦ˳��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetRenderOrder_Opaque(int nOrder)
{
	m_strBinName = "RenderBin";
	m_nBinNumber = nOrder;

	// ʹ��Ⱦ״̬ʧЧ
	DirtyStateSet();

}

//-----------------------------------------------------------------------------
// ������SetRenderOrder_Transparent()
// ����������͸��ģ�͵���Ⱦ˳��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetRenderOrder_Transparent(int nOrder)
{
	m_strBinName = "DepthSortedBin";
	m_nBinNumber = nOrder;

	// ʹ��Ⱦ״̬ʧЧ
	DirtyStateSet();
}

//-----------------------------------------------------------------------------
// ������SetRenderHint_Opaque()
// ������������ò�͸��ģ�͵���Ⱦ˳��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetRenderHint_Opaque()
{
	SetRenderOrder_Opaque(0);
}

//-----------------------------------------------------------------------------
// ������SetRenderHint_Transparent()
// �������������͸��ģ�͵���Ⱦ˳��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetRenderHint_Transparent()
{
	SetRenderOrder_Transparent(10);
}

//-----------------------------------------------------------------------------
// ������SetRenderHint_Default()
// �������������ģ�͵���Ⱦ˳��
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetRenderHint_Default()
{
	m_strBinName = "";
	m_nBinNumber = 0;

	// ʹ��Ⱦ״̬ʧЧ
	DirtyStateSet();
}

//-----------------------------------------------------------------------------
// ������GetBlendNodes()
// ��������ȡ����ɫ�ڵ�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::GetBlendNodes(std::vector< ref_ptr<osg::IVBF_SGNode> >& vNodes)
{
    vNodes.clear();

    if(m_piNodeModel.valid())       vNodes.push_back( m_piNodeModel );
    else if(m_piNodeGroup.valid())  vNodes.push_back( m_piNodeGroup );
    else                            return;
}

//-----------------------------------------------------------------------------
// ������DoAction()
// ������ģ����ĳ�ֶ��� (�糵�ֹ�����������ת��)
// ������szActionName  -- �������ƣ����������ת�ȣ�
//     bEnabled       -- ����������ֹͣ
//     pActionParam   -- �����Ĳ��� (������ٶȵȣ��������ͺͺ����ɶ����������)
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DoAction(const char* szActionName, bool bEnabled)
{
    for(CVBF_ActionList::iterator pIter=m_MarkActionList.begin(); pIter!=m_MarkActionList.end(); pIter++)
    {
        ref_ptr<IVBF_MarkAction>& ipIAction = *pIter;
        if(ipIAction.valid())
        {
            if(ipIAction->GetName()== szActionName)
            {
                ipIAction->Enable(bEnabled);
                return;
            }
        }
    }
}

//-----------------------------------------------------------------------------
// ������DoAction()
// ������ģ�͵�ĳ���ӽڵ���ĳ�ֶ��� (�糵�ֹ�����������ת��)
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DoAction(const std::string& strChildID,
                                  const std::string& strActionName, bool bEnabled)
{
    if(strChildID.empty() || strActionName.empty()) return;

    IVBF_MarkModel* pIChild = GetChildNested(strChildID);
    if(NULL==pIChild) return;

    pIChild->DoAction(strActionName.c_str(), bEnabled);

}


//-----------------------------------------------------------------------------
// ������UpdateByActions()
// ����������ģ�Ͷ���
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::UpdateByActions()
{
    for(CVBF_ActionList::iterator pIter=m_MarkActionList.begin(); pIter!=m_MarkActionList.end(); pIter++)
    {
        ref_ptr<IVBF_MarkAction>& pIAction = *pIter;
        if(pIAction.valid()) pIAction->Update();
    }
}

//-----------------------------------------------------------------------------
// ������UpdateByEffects()
// ����������ģ����Ч
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::UpdateByEffects()
{
    // ��ʼ��˸
    if(m_bFlickerToStart)
    {
        if(m_piNodeRoot.valid()) ::VBF_StartFlicker(m_piNodeRoot, m_FlickerParam.nFlickerTimes, m_FlickerParam.nFlickerInterval, m_FlickerParam.bFlickerAlways);
        m_bFlickerToStart = false;
    }

    // ֹͣ��˸
    if(m_bFlickerToStop)
    {
        if(m_piNodeRoot.valid()) ::VBF_StopFlicker(m_piNodeRoot);
        m_bFlickerToStop = false;
    }
}

//-----------------------------------------------------------------------------
// ������StartFlicker()
// ��������ʼ��˸
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::StartFlicker(int nFlickerTimes, int nFlickerInterval, bool bFlickerAlways/*=false*/)
{
    m_FlickerParam.nFlickerTimes    = nFlickerTimes;
    m_FlickerParam.nFlickerInterval = nFlickerInterval;
    m_FlickerParam.bFlickerAlways   = bFlickerAlways;

    m_bFlickerToStart = true;
    m_bFlickerToStop  = false;
}

//-----------------------------------------------------------------------------
// ������StopFlicker()
// ������ֹͣ��˸
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::StopFlicker()
{
    m_bFlickerToStart = false;
    m_bFlickerToStop  = true;
}

//-----------------------------------------------------------------------------
// ������CreateBoundingBoxNode()
// ������������Χ�нڵ�
//-----------------------------------------------------------------------------
template<class T>
osg::IVBF_SGNode* CVBF_MarkModelImpl<T>::CreateBoundingBoxNode()
{
	osg::BoundingBoxd boxInGeo = GetBoundingBoxInGeo();

	// ��ȡ��Χ�еľ��γ��͸߲�
	double dL = boxInGeo.xMax() - boxInGeo.xMin();
	double dB = boxInGeo.yMax() - boxInGeo.yMin();
	double dH = boxInGeo.zMax() - boxInGeo.zMin();

	// ��������γ��Ϊ0�������ư�Χ��
	if(osg::equivalent(dL, 0.0) || osg::equivalent(dB, 0.0)) return NULL;

	// ��Χ��΢������
	float fExpand = m_BoundingBoxStyle.fExpand;

	boxInGeo.xMin() -= dL * fExpand;
	boxInGeo.xMax() += dL * fExpand;

	boxInGeo.yMin() -= dB * fExpand;
	boxInGeo.yMax() += dB * fExpand;

	// ����߲�Ϊ0��ǿ�и���Χ������һ���߶�ֵ
	if(osg::equivalent(dH, 0.0))
	{
		dH = osg::minimum(dL, dB) * 3600 * 30 * 0.1;

		boxInGeo.zMin() -= dH;
		boxInGeo.zMax() += dH;
	}
	else
	{
		boxInGeo.zMin() -= dH * fExpand;
		boxInGeo.zMax() += dH * fExpand;
	}

	// ����Χ������ת������������ϵ
	osg::Vec3 v[8];
	for(int i=0; i<8; ++i)
	{
		osg::Vec3d ptWorld;
        m_ipContext->GeoToWorld(boxInGeo.corner(i), true, ptWorld);
		v[i] = ptWorld;
	}

	return ::VBF_CreateBoundingBoxNode(v, m_BoundingBoxStyle, m_strID);
}

//-----------------------------------------------------------------------------
// ������AttachObserver()
// ��������һ����Ϣ�۲���
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::AttachObserver(IVBF_ObserverRef* pIObserver)
{
	if(NULL==pIObserver) return;

	// �������ظ����
	CVBF_ObserverList::iterator pIter = std::find(m_ObserverList.begin(), m_ObserverList.end(), pIObserver);
	if(pIter==m_ObserverList.end()) m_ObserverList.push_back(pIObserver);
}

//-----------------------------------------------------------------------------
// ������DetachObserver()
// ���������һ����Ϣ�۲���
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DetachObserver(IVBF_ObserverRef* pIObserver)
{
	if(NULL==pIObserver) return;

	// �������ظ����
	CVBF_ObserverList::iterator pIter = std::find(m_ObserverList.begin(), m_ObserverList.end(), pIObserver);
	if(pIter!=m_ObserverList.end()) m_ObserverList.erase(pIter);
}

