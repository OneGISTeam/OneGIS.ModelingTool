//-----------------------------------------------------------------------------
// 函数：CVBF_MarkModelImpl()
// 描述：构造函数
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

    // 模型的查询信息
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
	
	// 渲染状态
	m_bEnableDepthTest	= true;
	m_bEnableDepthWrite	= true;
	m_bEnableLight		= false;
	m_bEnableClipByEarth = false;

	// 是否开启各类光滑（默认为开启）
	m_bEnablePointSmooth	= true;		
	m_bEnableLineSmooth		= true;	
	m_bEnablePolygonSmooth	= false;
	
	// 渲染顺序
	m_nBinNumber.unset();		// 模型的渲染顺序
	m_strBinName		= "";
	m_nBinNumberBox		= VBF_TRANSPARENT_BINBASE + 1;	// 包围盒的渲染顺序

	// 包围盒初始化，把包围盒设置为非法包围盒
	m_bBoundingBoxVisible = false;
    m_bBoundingBoxVisibleWhenSelected = true;	// 选中模型时，包围盒是否自动可见（默认为true）
	m_BoundingBoxInModel.init();
	m_BoundingBoxInWorld.init();
	m_BoundingBoxInGeo.init();
	
    // 模型显示的LOD范围
	m_fDistMin			= 0.0f;
    m_fDistMax			= FLT_MAX;
    m_dDistToEye        = FLT_MAX;
    m_bInDistRange      = true;

	m_vPosGeo			= osg::Vec3d(0, 0, 0);		// 地理坐标（如果有父模型，表示子模型的相对坐标）
	m_vPosWorld			= ::VBF_GetPosInvalid();	// 世界坐标

	m_bEnableBlendColor = false;
    m_bBlendModulate	= false;		// 是否使用乘色方式进行混合，否则使用替换色方式
	m_colorBlend		= osg::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	m_bEnableBlendWithParent = true;

	// 模型节点是否失效
    m_bDirtyModel               = true;
    m_bDirtyStateSet            = true;
    m_bDirtyPosGeo              = true;
    m_bDirtyPosWorld            = true;
    m_bDirtyBoundingBoxNode     = true;
    m_bDirtyBoundingBoxInModel  = true;
    m_bDirtyBoundingBoxInWorld  = true;
    m_bDirtyBoundingBoxInGeo    = true;

    // 是否需要开始/停止闪烁
    m_bFlickerToStart           = false;
    m_bFlickerToStop            = false;

    // 模型根节点是否等待添加/删除
    m_bNodeToAddToParent        = false;
    m_bNodeToRemoveFromParent   = false;

	// 是否等待添加到父节点的图层
	m_bNodeToAddToParentLayer   = false;

    // 右键弹出菜单
    m_bEnablePopupMenu      = true;
    m_bEnableMenuZBuffer    = true;
    m_bEnableMenuFillMode   = false;

    // 外部接口
    m_pI3DMainCtrl          = NULL;
}

//-----------------------------------------------------------------------------
// 函数：~CVBF_MarkModelImpl()
// 描述：析构函数
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkModelImpl<T>::~CVBF_MarkModelImpl()
{
    Clear();

	// 从场景图中删除该模型的根节点
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

    //  删除子模型
    DeleteAllChildren();
}
//-----------------------------------------------------------------------------
// 函数：SetID()
// 描述：设置军标模型的全层唯一编号，如果该模型已经记录某个图层中，不允许修改ID号，返回false（请用户慎重使用该函数）
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::SetID(const std::string& strID)
{
	// 如果模型已经记录在图层中，不允许修改ID号
	DWORD dwLayerPtr = GetLayerPtr();
	if(dwLayerPtr!=0) return false;

	m_strID = strID;
	return true;
}

//-----------------------------------------------------------------------------
// 函数：SetParentNode()
// 描述：设置标识：该模型的根节点等待添加到某个父节点
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
// 函数：Init()
// 描述：初始化 (在构造函数之后由系统调用)
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::Init(IVBF_MarkContext* pIContext)
{  
	// 避免被多次初始化
	if(m_bInited) return true;

    if(pIContext==NULL) return false;
    m_ipContext = pIContext;


	CVBF_3DEnvironment& env = ::VBF_Get3DEnvironment();
	m_pI3DMainCtrl = env.m_pI3DMainCtrl;

	// 获取模型所在的视图（目前暂时如此处理，以后应该由外部传入）
	m_opView = ::VBF_GetMainView(env.m_pI3DMainCtrl);
	if(!m_opView.valid()) return false;

	m_opCamera = m_opView->getCamera();
	if(!m_opCamera.valid()) return false;

	// 初始化模型的场景图
	if( !InitSG() ) return false;

	m_bInited = true;

	return true;
}

//-----------------------------------------------------------------------------
// 函数：InitSG()
// 描述：初始化模型的场景图
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::InitSG()
{
	// 创建模型的根节点，挂接在图层节点下
	m_piNodeRoot = new osg::Switch;
	m_piNodeRoot->setName("VBFNode_MarkRoot: " + m_strID);
	m_piNodeRoot->setValue(0, m_bVisible);
    m_piNodeRoot->setUserValue<TYPE_PTR>("VBFMarkPtr", (TYPE_PTR)this);

	// 创建模型的Group节点，挂接在根节点下，用户的节点需要挂接在该节点下
	m_piNodeGroup = ::VBF_CreateSGNodeGroup();
	m_piNodeGroup->setName("VBFNode_MarkGroup: " + m_strID);

	// 依次挂接上述节点
	m_piNodeRoot->addChild(m_piNodeGroup);
	
	return true;
}

//-----------------------------------------------------------------------------
// 函数：SetLayerPtrAsNull()
// 描述：将图层指针设置为NULL（该函数仅由系统内部调用）
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetLayerPtrAsNull()
{
	m_dwLayerPtr = 0L;
}

//-----------------------------------------------------------------------------
// 函数：SetLayerPtr()
// 描述：设置该模型所在图层的指针
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetLayerPtr(TYPE_PTR dwData)
{ 
	if(m_dwLayerPtr==dwData) return;

	// 先从原有图层中移除
	if(m_dwLayerPtr!=0L) 
	{
		IVBF_3DPlotLayer* pILayerOld = (IVBF_3DPlotLayer*)m_dwLayerPtr;
		pILayerOld->RemoveMark(this);
	}

	// 再添加到新图层
	if(dwData!=0L)
	{
		IVBF_3DPlotLayer* pILayerNew = (IVBF_3DPlotLayer*)dwData;
		pILayerNew->AddMark(this);
	}

	m_dwLayerPtr = dwData; 
}

//-----------------------------------------------------------------------------
// 函数：SetVisible()
// 描述：设置模型的可见性
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetVisible(bool bVisible)
{
    bool bChanged = (bVisible!=m_bVisible);
    m_bVisible = bVisible;

	// 向观察者发送消息：模型可见性改变了
	if(bChanged)
	{
		NotifyObservers(VBF_MESSAGE_3DPLOT_MARK_VISIBLE, bVisible, this);
	}
}

//-----------------------------------------------------------------------------
// 函数：NotifyObservers()
// 描述：向所有观察者发送消息
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
// 函数：GetPos()
// 描述：获取军标模型的当前位置，如果有父模型，返回子模型的相对坐标；否则，返回模型的世界坐标 
//-----------------------------------------------------------------------------
template<class T>
const osg::Vec3d& CVBF_MarkModelImpl<T>::GetPos()
{
	// 有父模型，返回子模型的相对坐标
	if( m_pIParent!=NULL && m_pIParent->IsPointMarkModel() )
	{
		return m_vPosGeo;		
	}
	else // 没有父模型，返回模型的世界坐标 
	{
		return GetWorldPos();
	}
}

//-----------------------------------------------------------------------------
// 函数：GetWorldPos()
// 描述：获取模型的世界坐标
//-----------------------------------------------------------------------------
template<class T>
const osg::Vec3d& CVBF_MarkModelImpl<T>::GetWorldPos()
{	
	// 如果世界坐标已经失效，需要重新计算
	if(m_bDirtyPosWorld)  
	{
        m_ipContext->GeoToWorld(m_vPosGeo, true, m_vPosWorld);

		// 确保世界坐标有效
		if(::VBF_IsPosInvalid(m_vPosWorld)) return ::VBF_GetPosInvalid();

		// 重新计算世界矩阵
		m_bDirtyPosWorld = false;
	}

	return m_vPosWorld;
}

//-----------------------------------------------------------------------------
// 函数：GetActualGeoPos()
// 描述：获取军标模型实际的地理坐标（即：经过局部变换后的地理坐标，该值由系统内部计算）
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
// 函数：SetBoundingBoxVisible()
// 描述：设置包围盒的可见性
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetBoundingBoxVisible(bool bVisible)
{ 
	if(m_bBoundingBoxVisible==bVisible) return;

	m_bBoundingBoxVisible = bVisible; 

	// 使所有子节点包围盒的可见性与父节点相同
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;
		if(pIChild) pIChild->SetBoundingBoxVisible(bVisible);
	}

	// 使包围盒节点失效
	DirtyBoundingBoxNode();
}

//-----------------------------------------------------------------------------
// 函数：SetBoundingBoxVisibleWhenSelected()
// 描述：设置选中模型时，包围盒是否自动可见（默认为true）
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetBoundingBoxVisibleWhenSelected(bool bVisible)
{
	if(m_bBoundingBoxVisibleWhenSelected==bVisible) return;

	m_bBoundingBoxVisibleWhenSelected = bVisible; 

	// 使所有子节点包围盒的可见性与父节点相同
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;
		if(pIChild) pIChild->SetBoundingBoxVisibleWhenSelected(bVisible);
	}

	// 使包围盒节点失效
	DirtyBoundingBoxNode();
}

//-----------------------------------------------------------------------------
// 函数：SetBoundingBoxStyle()
// 描述：设置包围盒的样式
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetBoundingBoxStyle(const VBF_BOUNDINGBOXSTYLE& style) 
{ 
	if(m_BoundingBoxStyle==style) return;

	m_BoundingBoxStyle = style; 

	// 使包围盒节点失效
	DirtyBoundingBoxNode();
}

//-----------------------------------------------------------------------------
// 函数：SetSelected()
// 描述：设置模型选中与否
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetSelected(bool bSelected)
{
	if(m_bSelected==bSelected) return;

	m_bSelected = bSelected;

	// 使包围盒节点失效
	DirtyBoundingBoxNode();
}

//-----------------------------------------------------------------------------
// 函数：UpdateBoundingBox()
// 描述：更新包围盒节点
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::UpdateBoundingBox()
{
    if(m_bDirtyBoundingBoxNode==false) return ;
    m_bDirtyBoundingBoxNode = false;
	// 判断包围盒是否可见
	bool bVisible = ( m_bBoundingBoxVisible || (m_bSelected && m_bBoundingBoxVisibleWhenSelected) );

    // 注意：如果有父模型且父模型被选中或包围盒可见，子模型不再绘制包围盒
    if(m_pIParent!=NULL && (m_pIParent->IsSelected() || m_pIParent->IsBoundingBoxVisible()) )
    {
        bVisible = false;
    }

	// 先删除原来的包围盒节点
	if(m_piNodeBoundingBox.valid()) m_piNodeGroup->removeChild(m_piNodeBoundingBox);

	// 如果包围盒可见：添加一个包围盒节点
	if(bVisible)
	{
		m_piNodeBoundingBox = CreateBoundingBoxNode();
		if(!m_piNodeBoundingBox.valid()) return;
		
		m_piNodeGroup->addChild(m_piNodeBoundingBox);

		// 设置包围盒部分的渲染状态（使用着色器）
		
		// 包围盒部分不使用纹理
		osg::StateSet* ss = m_piNodeBoundingBox->getOrCreateStateSet();
		ss->setTextureMode(0, GL_TEXTURE_2D, osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED|osg::StateAttribute::OVERRIDE);
		
		// 设置渲染顺序
		ss->setRenderBinDetails(m_nBinNumberBox, "DepthSortedBin");	

		// 设置着色器
		SetShader_BoundingBox(ss);
	}
}

//-----------------------------------------------------------------------------
// 函数：SetReserveFlag()
// 描述：设置/获取预留标志，系统使用了最后4位
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetReserveFlag(DWORD dwFlag, bool bOR)
{
	if(bOR) m_dwReserveFlag = (m_dwReserveFlag | dwFlag);
	else    m_dwReserveFlag = (m_dwReserveFlag & dwFlag);
}


//-----------------------------------------------------------------------------
// 函数：AddToParentNode()
// 描述：添加到场景图的父节点
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::AddToParentNode()
{
    // 先从原来的父节点中移除
    if(m_bNodeToRemoveFromParent)
    {
        if(m_piNodeParentOld.valid()) m_piNodeParentOld->removeChild( GetRootNode() );
        m_bNodeToRemoveFromParent = false;
    }

    // 再添加到新的父节点
    if(m_bNodeToAddToParent)
    {
        if(m_piNodeParent.valid()) m_piNodeParent->addChild( GetRootNode() );
        m_bNodeToAddToParent = false;
    }

	// 等待添加到父节点的图层（杜莹添加：2017-11-30）
	if(m_bNodeToAddToParentLayer)
    {
		// 遍历所有父模型，直到找到一个图层指针
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
// 函数：UpdateSGNode()
// 描述：更新某些场景图节点的属性
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::UpdateSGNode()
{
    if(m_piNodeRoot.valid())
    {
        // 判断模型本身是否可见
        m_piNodeRoot->setNodeMask(m_bVisible? ~0 : 0);
    }
}

//-----------------------------------------------------------------------------
// 函数：ClipByDist()
// 描述：根据视点到模型的距离，判断模型/属性是否在可见距离内
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::ClipByDist()
{
    // 如果模型可见，再根据视点到模型的距离，判断模型/属性是否在可见距离内
    if(m_bVisible)
    {
        bool bAttrChild = (m_pIParent!=NULL && (m_dwReserveFlag & VBF_RESERVEFLAG_ATTRCHILD));
        if(!bAttrChild)
        {
            ClipModelByDist();    // 判断模型是否在可见距离内
        }
        else
        {
            ClipAttrByDist();   // 判断属性是否在可见距离内
        }
    }
}

//-----------------------------------------------------------------------------
// 函数：ClipModelByDist()
// 描述：根据视点到模型的距离，判断模型是否在可见距离内
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::ClipModelByDist()
{
    if(m_bVisible && m_piNodeRoot.valid())
    {
        const osg::Vec3d& ptWorld = GetWorldPos();
        if(::VBF_IsPosInvalid(ptWorld)) return; // 确保世界坐标有效

        IVBF_GlobalDataPerView* pData = VBF_Get3DGlobalData(m_opView.get());
        const osg::Vec3d& ptEye = pData->GetEyePtInWorld();
        m_dDistToEye   = (ptEye - ptWorld).length();
        m_bInDistRange = (m_dDistToEye>=m_fDistMin && m_dDistToEye<=m_fDistMax);

        m_piNodeRoot->setNodeMask( (m_bVisible && m_bInDistRange)? ~0 : 0 );
    }
}

//-----------------------------------------------------------------------------
// 函数：ClipAttrByDist()
// 描述：根据视点到模型的距离，判断模型的某个属性是否在可见距离内
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::ClipAttrByDist()
{
    // 如果是由属性创建的子节点，强行使其可见性与父节点保持一致
    if(m_pIParent!=NULL && m_piNodeRoot.valid())
    {
        m_dDistToEye   = m_pIParent->GetDistToEye();
        m_bInDistRange = m_pIParent->IsInDistRange();
        m_piNodeRoot->setNodeMask( (m_bVisible && m_bInDistRange)? ~0 : 0 );
    }
}


//-----------------------------------------------------------------------------
// 函数：Update()
// 描述：更新 (每帧绘制前调用)
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::Update()
{
    // 添加到场景图的父节点
    AddToParentNode();

    // 更新某些场景图节点的属性
    UpdateSGNode();

    if(!m_bVisible) return false;

    // 更新模型节点
	if(m_bDirtyModel)
    {
        UpdateModelNode();
		m_bDirtyModel = false;
	}

	// 更新模型的位置
	UpdatePos();

	// 根据视点到模型的距离，判断模型/属性是否在可见距离内
	ClipByDist();

	// 地球背面的裁剪
	ClipByEarth();

	// 更新所有子模型
    UpdateChildren();

    // 更新所有属性
    UpdateAttrs();

    // 更新包围盒节点
    UpdateBoundingBox();

	// 更新渲染状态
	if(m_bDirtyStateSet)
	{
		SetStateSet();
		m_bDirtyStateSet = false;
	}

    // 模型动作/特效
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
// 函数：UpdateModelNode()
// 描述：更新模型节点
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::UpdateModelNode()
{
    // 先删除原本来的模型节点
    if( m_piNodeModel.valid() && m_piNodeGroup.valid() )
    {
        m_piNodeGroup->removeChild(m_piNodeModel);
    }

    // 再创建新的模型节点
    if( CreateModelNode() && m_piNodeModel.valid() )
    {
        m_piNodeModel->setName("VBFNode_MarkModel: " + m_strID);
        m_piNodeGroup->addChild(m_piNodeModel);

        // 更新父节点的包围球
        m_piNodeModel->dirtyBound();
    }
}

//-----------------------------------------------------------------------------
// 函数：UpdateChildren()
// 描述：更新所有子模型
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
       //   pIChild->SetDistMin(m_fDistMin);  // 调整到属性的Update()函数中（杜莹修改：2015-12-01）
       //   pIChild->SetDistMax(m_fDistMax);
            continue; // 注意：由属性创建的子模型不在此处更新
        }
		
		pIChild->Update();
	}
}


//-----------------------------------------------------------------------------
// 函数：SetGeoPos()
// 描述：设置模型的地理坐标
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetGeoPos(const osg::Vec3d& vPos)		
{ 
	m_vPosGeo = vPos;

    // 使地理/世界坐标失效
    DirtyPosGeo();
	DirtyPosWorld();

	// 使包围盒失效
	DirtyBoundingBoxInWorld();

	// 逻辑上，UpdatePos()函数只需要在Transform()函数中调用，为什么必须在此处调用一下才能绘制出模型 ???
//	UpdatePos();

	// 使所有子节点的坐标也失效（杜莹添加：2013-12-04）
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;
		if(pIChild!=NULL) pIChild->SetGeoPos( pIChild->GetGeoPos() );
	}
}

//-----------------------------------------------------------------------------
// 函数：GetBoundingBoxNode()
// 描述：获取计算包围盒时使用的节点
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
// 函数：GetBoundingBoxInModel()
// 描述：计算模型坐标系下的包围盒
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
// 函数：GetBoundingBoxInWorld()
// 描述：计算世界坐标系下的包围盒
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
// 函数：GetBoundingBoxInGeo()
// 描述：计算地理坐标系下的包围盒
//-----------------------------------------------------------------------------
template<class T>
const osg::BoundingBoxd& CVBF_MarkModelImpl<T>::GetBoundingBoxInGeo()
{
	if(!m_bDirtyBoundingBoxInGeo) return m_BoundingBoxInGeo;

	const osg::BoundingBox& boxInWorld = GetBoundingBoxInWorld();
	if(!boxInWorld.valid()) return m_BoundingBoxInGeo;

	// 计算其在地理坐标系中的包围盒
	double dLMin = +DBL_MAX;
	double dLMax = -DBL_MAX;
	double dBMin = +DBL_MAX;
	double dBMax = -DBL_MAX;
	double dHMin = +DBL_MAX;
	double dHMax = -DBL_MAX;

	for(int i=0; i<8; i++)
	{
		osg::Vec3d ptWorldOld = boxInWorld.corner(i);

		// 世界坐标 --> 地理坐标
        osg::Vec3d ptGeo;
        m_ipContext->WorldToGeo(ptWorldOld, ptGeo);

		if(ptGeo.x() < dLMin) dLMin = ptGeo.x();
		if(ptGeo.x() > dLMax) dLMax = ptGeo.x();

		if(ptGeo.y() < dBMin) dBMin = ptGeo.y();
		if(ptGeo.y() > dBMax) dBMax = ptGeo.y();

		if(ptGeo.z() < dHMin) dHMin = ptGeo.z();
		if(ptGeo.z() > dHMax) dHMax = ptGeo.z();
	}

	// 利用地理坐标系下的最大最小值，构建包围盒
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
// 函数：GetBoundingBoxCenterGeo()
// 描述：获取模型包围盒中心的地理坐标
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
// 函数：LookupMarkAttrIFF()
// 描述：查找模型的敌我类别属性
//-----------------------------------------------------------------------------
template<class T>
IVBF_MarkAttrIFF* CVBF_MarkModelImpl<T>::LookupMarkAttrIFF()
{
	// 强制使用父节点的IFF属性
	IVBF_MarkModel*   pIMark    = (m_pIParent!=NULL)? m_pIParent : this;
	IVBF_MarkAttrIFF* pIAttrIFF = (IVBF_MarkAttrIFF*)pIMark->LookupMarkAttr(VBF_MARK_ATTR_IFF);

	return pIAttrIFF;
}


//-----------------------------------------------------------------------------
// 函数：GetChildCount()
// 描述：获取子模型个数
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
		if(dwReserveFlag & VBF_RESERVEFLAG_ATTRCHILD) continue; // 注意：需要过滤掉属性创建的子模型

		nCount++;
	}
	return nCount;
}

//-----------------------------------------------------------------------------
// 函数：GetChild()
// 描述：子模型遍历 (nIndex纯粹表示属性的序号)
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
		if(dwReserveFlag & VBF_RESERVEFLAG_ATTRCHILD) continue; // 注意：需要过滤掉属性创建的子模型

		idx++;
		if(idx==nIndex) return pIChild;			
	}

	return NULL;
}

//-----------------------------------------------------------------------------
// 函数：GetChild()
// 描述：获取子模型
//-----------------------------------------------------------------------------
template<class T>
IVBF_MarkModel* CVBF_MarkModelImpl<T>::GetChild(const std::string& strChildID)
{
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;

		DWORD dwReserveFlag = pIChild->GetReserveFlag(); 
		if(dwReserveFlag & VBF_RESERVEFLAG_ATTRCHILD) continue; // 注意：需要过滤掉属性创建的子模型

		if(strChildID==pIChild->GetID()) return pIChild;
	}

	return NULL;
}

//-----------------------------------------------------------------------------
// 函数：GetChildNested()
// 描述：获取子模型
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
// 函数：GetParentalPaths()
// 描述：获取军标模型的父模型层次列表（从最顶层父模型开始，到该模型结束）
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
// 函数：AddChild()
// 描述：添加一个子节点
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::AddChild(IVBF_MarkModel* pIChild)
{
	if(NULL==pIChild) return false;

	// 不允许重复添加同一个子节点
	for(unsigned int i=0; i<m_vChildren.size(); i++)
	{
		IVBF_MarkModel* pIChildT = m_vChildren[i];
		if(pIChildT==pIChild) return false;
	}

	pIChild->SetParent(this);
	m_vChildren.push_back(pIChild);

    // 给子模型设置新的父节点（杜莹修改：2014-12-12）
    if( !this->IsPointMarkModel() )
    {
        pIChild->SetParentNode(this->m_piNodeGroup);
    }
    else
    {
        if( pIChild->IsPointMarkModel() )  // 父模型是点状，子模型也是点状
        {
            pIChild->SetParentNode(this->m_piNodeGroup);
        }
        else  // 父模型是点状，但子模型不是点状
        {
            // 需要将子模型的根节点添加到Plot专门设置的一个节点下，避免子模型受到父模型或更上层父模型矩阵的影响（杜莹修改：2015-06-03）
        //  IVBF_3DPlotLayer* pILayer = (IVBF_3DPlotLayer*)m_dwLayerPtr;
        //  if(pILayer) pIChild->SetParentNode(pILayer->GetNodeForNotPointMarks()); // 如果父节点有图层指针，添加到父节点所在的图层

			// 有可能父节点根本就没有图层指针，或者此时尚未添加到图层，所以此处仅做标识（杜莹修改：2017-11-30）
			pIChild->WaitForAddingToParentLayer();
        }
    }

	// 使包围盒失效
	DirtyBoundingBoxNode();
	DirtyBoundingBoxInModel();
	DirtyBoundingBoxInWorld();

	return true;
}

//-----------------------------------------------------------------------------
// 函数：RemoveChild()
// 描述：移除一个子节点，但不删除子节点指针
//-----------------------------------------------------------------------------
template<class T>
IVBF_MarkModel* CVBF_MarkModelImpl<T>::RemoveChild(const std::string& strChildID)
{
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		ref_ptr<IVBF_MarkModel> pIChild = *pIter;
		if(pIChild.valid() && pIChild->GetID()==strChildID)
		{
            pIChild->SetParentNode(NULL);  // 解除子模型的父节点

			m_vChildren.erase(pIter);
			return pIChild.release();
		}
	}

	return NULL;
}

//-----------------------------------------------------------------------------
// 函数：RemoveChild()
// 描述：移除一个子节点，但不删除子节点指针
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::RemoveChild(IVBF_MarkModel* pIChild)
{
	if(NULL==pIChild) return;

	CVBF_MarkList::iterator pIter = std::find(m_vChildren.begin(), m_vChildren.end(), pIChild);
	if(pIter!=m_vChildren.end())
	{
		pIChild->SetParentNode(NULL);	// 解除子模型的父节点
		pIChild->SetParent(NULL);		// 解除子模型的父模型（杜莹添加：2015-04-17）
		m_vChildren.erase(pIter);
	}
}

//-----------------------------------------------------------------------------
// 函数：DeleteChild()
// 描述：删除一个子节点，同时删除其指针
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DeleteChild(const std::string& strChildID)
{
	IVBF_MarkModel* pIChild = GetChild(strChildID);
	DeleteChild(pIChild);
}

//-----------------------------------------------------------------------------
// 函数：DeleteChild()
// 描述：删除一个子节点，同时删除其指针
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DeleteChild(IVBF_MarkModel* pIChild)
{
	if(NULL==pIChild) return;

	CVBF_MarkList::iterator pIter = std::find(m_vChildren.begin(), m_vChildren.end(), pIChild);
	if(pIter!=m_vChildren.end())
	{
		pIChild->SetParentNode(NULL);  // 解除子模型的父节点
		m_vChildren.erase(pIter);
	}
}

//-----------------------------------------------------------------------------
// 函数：DeleteAllChildren()
// 描述：删除所有子模型及其指针
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DeleteAllChildren()
{
	for(CVBF_MarkList::iterator pIterChild=m_vChildren.begin(); pIterChild!=m_vChildren.end(); pIterChild++)
	{
		ref_ptr<IVBF_MarkModel> pIChild = *pIterChild;
        pIChild->SetParentNode(NULL);  // 解除子模型的父节点
	}
	m_vChildren.clear();
}

//-----------------------------------------------------------------------------
// 函数：GetChildGeoPos()
// 描述：根据子模型在父模型中的位置，计算子模型的地理坐标
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
// 函数：ApartChild()
// 描述：分离一个子模型
//-----------------------------------------------------------------------------
template<class T>
IVBF_MarkModel* CVBF_MarkModelImpl<T>::ApartChild(const std::string& strChildID)
{
	ref_ptr<IVBF_MarkModel> piChild = GetChild(strChildID);
	if(!piChild.valid()) return NULL;

	// 根据设置子模型在父模型中的位置，计算子模型的地理坐标
	osg::Vec3d vChildGeo = GetChildGeoPos(strChildID);
	piChild->SetGeoPos(vChildGeo);

	// 根据父模型的姿态，设置子模型的姿态
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
// 函数：EnableDepthTest()
// 描述：强行开启/关闭深度测试（默认为开启）
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::EnableDepthTest(bool bEnable)
{ 
	if(m_bEnableDepthTest==bEnable) return;

	m_bEnableDepthTest = bEnable;
    DirtyStateSet();
}

//-----------------------------------------------------------------------------
// 函数：EnableDepthWrite()
// 描述：强行开启/关闭深度写入（默认为开启）
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::EnableDepthWrite(bool bEnable)
{ 
	if(m_bEnableDepthWrite==bEnable) return;

	m_bEnableDepthWrite = bEnable;
    DirtyStateSet();
}

//-----------------------------------------------------------------------------
// 函数：EnableLight()
// 描述：强行开启/关闭光照 (默认为关闭)
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::EnableLight(bool bEnable) 
{ 
	if(m_bEnableLight==bEnable) return;

	m_bEnableLight = bEnable;
	DirtyStateSet();
}

//-----------------------------------------------------------------------------
// 函数：EnablePointSmooth()
// 描述：强行开启/关闭点光滑 (默认为开启)
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::EnablePointSmooth(bool bEnable) 
{ 
	if(m_bEnablePointSmooth==bEnable) return;

	m_bEnablePointSmooth = bEnable;
	DirtyStateSet();
}

//-----------------------------------------------------------------------------
// 函数：EnableLineSmooth()
// 描述：强行开启/关闭线光滑 (默认为开启)
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::EnableLineSmooth(bool bEnable) 
{ 
	if(m_bEnableLineSmooth==bEnable) return;

	m_bEnableLineSmooth = bEnable;
	DirtyStateSet();
}

//-----------------------------------------------------------------------------
// 函数：EnablePolygonSmooth()
// 描述：强行开启/关闭面光滑 (默认为关闭)
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::EnablePolygonSmooth(bool bEnable) 
{ 
	if(m_bEnablePolygonSmooth==bEnable) return;

	m_bEnablePolygonSmooth = bEnable;
	DirtyStateSet();
}

//-----------------------------------------------------------------------------
// 函数: SetShader_BoundingBox()
// 描述: 对包围盒设置着色器
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetShader_BoundingBox(osg::StateSet* ss)
{
	if(NULL==ss) return;

	// 设置材质
    ref_ptr<osg::Material> ipMaterial = new osg::Material;
    ipMaterial->setColorMode(osg::Material::DIFFUSE);
    ipMaterial->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
    ipMaterial->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
    ipMaterial->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
    ipMaterial->setShininess(osg::Material::FRONT_AND_BACK, 100.0f);  // 有效值为[0.0, 128.0]，值越大，高光区越小
    ipMaterial->setEmission(osg::Material::FRONT_AND_BACK,osg::Vec4(0, 0, 0, 1));
    ss->setAttributeAndModes(ipMaterial.get(), osg::StateAttribute::ON);

	// 设置光照模型
    ref_ptr<osg::LightModel> ipLightModel = new osg::LightModel;
    ipLightModel->setAmbientIntensity(osg::Vec4(0.1f, 0.1f, 0.1f, 1.0f));
    ss->setAttributeAndModes(ipLightModel, osg::StateAttribute::ON);

	// 创建着色器
	osg::Program* pProg = ::VBF_CreateShader(::VBF_Get3DEnvironment().m_pI3DMainCtrl, "GraphicsSolid.vert", "GraphicsSolid.frag");
	if(NULL==pProg) return;

	ss->addUniform( new osg::Uniform("bEnableColor", true) );
	ss->addUniform( new osg::Uniform("bEnableTex",   false) );
	ss->addUniform( new osg::Uniform("bEnableLight", true) );
	ss->addUniform( new osg::Uniform("bEnableFog",   false) );

	ss->setAttributeAndModes( pProg, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE|osg::StateAttribute::PROTECTED );
}

//-----------------------------------------------------------------------------
// 函数: SetStateSet()
// 描述: 设置渲染状态
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetStateSet()
{   
    if( m_piNodeRoot.valid() )
    {
        osg::StateSet* ss = m_piNodeRoot->getOrCreateStateSet();

        // 开启/关闭深度测试和深度写入
        osg::Depth* pDepth = dynamic_cast<osg::Depth*>( ss->getAttribute(osg::StateAttribute::DEPTH) );
        if(NULL==pDepth) pDepth = new osg::Depth;

        pDepth->setFunction(m_bEnableDepthTest? osg::Depth::LEQUAL : osg::Depth::ALWAYS);
        pDepth->setWriteMask(m_bEnableDepthWrite);
        ss->setAttributeAndModes(pDepth, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE|osg::StateAttribute::PROTECTED);

        // 设置模型的渲染顺序
        if(m_nBinNumber.isSet()) ss->setRenderBinDetails(m_nBinNumber.value(), m_strBinName, osg::StateSet::USE_RENDERBIN_DETAILS);

    }

    // 颜色混合
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

	// 设置模型的渲染状态
	if( m_piNodeModel.valid() )
	{
		osg::StateSet* ss = m_piNodeModel->getOrCreateStateSet();

		// 开启/关闭光照（有待修改）
		int nValue = (m_bEnableLight)? osg::StateAttribute::ON : osg::StateAttribute::OFF;
		ss->setMode(GL_LIGHTING, nValue|osg::StateAttribute::PROTECTED|osg::StateAttribute::OVERRIDE);

		// 开启/关闭光滑
		::VBF_EnablePointSmooth(ss, m_bEnablePointSmooth);
		::VBF_EnableLineSmooth(ss, m_bEnableLineSmooth);
		::VBF_EnablePolygonSmooth(ss, m_bEnablePolygonSmooth);


#if !defined(OSG_GLES2_AVAILABLE)
        ss->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
#endif
    }
}

//-----------------------------------------------------------------------------
// 函数：SetBlendColor()
// 描述：设置模型是否混色以及混合的颜色，混合的方式（乘色/替换色）
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

    // 使渲染状态失效
    DirtyStateSet();

	// 使所有子节点混色
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		ref_ptr<IVBF_MarkModel>& piChild = *pIter;
		if(!piChild.valid() || (piChild->GetReserveFlag() & VBF_RESERVEFLAG_ATTRCHILD)) continue;
		if(!piChild->IsBlendWithParentEnabled()) continue;

		piChild->SetBlendColor(bEnable, color, bModulate);
	}
}

//-----------------------------------------------------------------------------
// 函数：AddMarkAttr()
// 描述：为模型添加一个属性
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::AddMarkAttr(IVBF_MarkAttr* pIAttr)
{
	if(NULL==pIAttr) return false;

	// 不允许属性类型重复
	unsigned int nAttrType = (unsigned int)pIAttr->GetType();
	if(LookupMarkAttr(nAttrType)!=NULL) return false;

	pIAttr->SetMarkModel(this);
	m_MarkAttrList.push_back(pIAttr);

	return true;
}

//-----------------------------------------------------------------------------
// 函数：AddMarkAttr()
// 描述：为模型添加一个属性，如果该属性已经存在，直接返回原来的属性接口
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
// 函数：DeleteMarkAttr()
// 描述：删除模型的某个属性
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
// 函数：LookupMarkAttr()
// 描述：查找模型的某个属性
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
// 函数：UpdateAttrs()
// 描述：更新所有属性
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
// 函数：AddMarkAction()
// 描述：为模型添加一个行为
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
// 函数：DeleteMarkAction()
// 描述：删除模型的某个行为
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DeleteMarkAction(unsigned int nIndex)
{
    if(nIndex<0 || nIndex>=m_MarkActionList.size()) return;

    CVBF_ActionList::iterator pIterBegin = m_MarkActionList.begin();
    m_MarkActionList.erase(pIterBegin+nIndex);
}


//-----------------------------------------------------------------------------
// 函数：AddMarkProcess()
// 描述：为模型添加一个推演过程
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
// 函数：DeleteMarkProcess()
// 描述：删除模型的某个推演过程
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DeleteMarkProcess(unsigned int nIndex)
{
    if(nIndex<0 || nIndex>=m_MarkProcessList.size()) return;

    CVBF_ProcessList::iterator pIterBegin = m_MarkProcessList.begin();
    m_MarkProcessList.erase(pIterBegin+nIndex);
}

//-----------------------------------------------------------------------------
// 函数：SetRenderOrder_Opaque()
// 描述：设置不透明模型的渲染顺序
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetRenderOrder_Opaque(int nOrder)
{
	m_strBinName = "RenderBin";
	m_nBinNumber = nOrder;

	// 使渲染状态失效
	DirtyStateSet();

}

//-----------------------------------------------------------------------------
// 函数：SetRenderOrder_Transparent()
// 描述：设置透明模型的渲染顺序
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetRenderOrder_Transparent(int nOrder)
{
	m_strBinName = "DepthSortedBin";
	m_nBinNumber = nOrder;

	// 使渲染状态失效
	DirtyStateSet();
}

//-----------------------------------------------------------------------------
// 函数：SetRenderHint_Opaque()
// 描述：快捷设置不透明模型的渲染顺序
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetRenderHint_Opaque()
{
	SetRenderOrder_Opaque(0);
}

//-----------------------------------------------------------------------------
// 函数：SetRenderHint_Transparent()
// 描述：快捷设置透明模型的渲染顺序
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetRenderHint_Transparent()
{
	SetRenderOrder_Transparent(10);
}

//-----------------------------------------------------------------------------
// 函数：SetRenderHint_Default()
// 描述：快捷设置模型的渲染顺序
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::SetRenderHint_Default()
{
	m_strBinName = "";
	m_nBinNumber = 0;

	// 使渲染状态失效
	DirtyStateSet();
}

//-----------------------------------------------------------------------------
// 函数：GetBlendNodes()
// 描述：获取待混色节点
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
// 函数：DoAction()
// 描述：模型做某种动作 (如车轮滚动、炮塔旋转等)
// 参数：szActionName  -- 动作名称（如滚动、旋转等）
//     bEnabled       -- 动作开启或停止
//     pActionParam   -- 动作的参数 (如滚动速度等，具体类型和含义由动作本身决定)
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
// 函数：DoAction()
// 描述：模型的某个子节点做某种动作 (如车轮滚动、炮塔旋转等)
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
// 函数：UpdateByActions()
// 描述：更新模型动作
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
// 函数：UpdateByEffects()
// 描述：更新模型特效
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::UpdateByEffects()
{
    // 开始闪烁
    if(m_bFlickerToStart)
    {
        if(m_piNodeRoot.valid()) ::VBF_StartFlicker(m_piNodeRoot, m_FlickerParam.nFlickerTimes, m_FlickerParam.nFlickerInterval, m_FlickerParam.bFlickerAlways);
        m_bFlickerToStart = false;
    }

    // 停止闪烁
    if(m_bFlickerToStop)
    {
        if(m_piNodeRoot.valid()) ::VBF_StopFlicker(m_piNodeRoot);
        m_bFlickerToStop = false;
    }
}

//-----------------------------------------------------------------------------
// 函数：StartFlicker()
// 描述：开始闪烁
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
// 函数：StopFlicker()
// 描述：停止闪烁
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::StopFlicker()
{
    m_bFlickerToStart = false;
    m_bFlickerToStop  = true;
}

//-----------------------------------------------------------------------------
// 函数：CreateBoundingBoxNode()
// 描述：创建包围盒节点
//-----------------------------------------------------------------------------
template<class T>
osg::IVBF_SGNode* CVBF_MarkModelImpl<T>::CreateBoundingBoxNode()
{
	osg::BoundingBoxd boxInGeo = GetBoundingBoxInGeo();

	// 获取包围盒的经差、纬差和高差
	double dL = boxInGeo.xMax() - boxInGeo.xMin();
	double dB = boxInGeo.yMax() - boxInGeo.yMin();
	double dH = boxInGeo.zMax() - boxInGeo.zMin();

	// 如果经差或纬差为0，不绘制包围盒
	if(osg::equivalent(dL, 0.0) || osg::equivalent(dB, 0.0)) return NULL;

	// 包围盒微量外扩
	float fExpand = m_BoundingBoxStyle.fExpand;

	boxInGeo.xMin() -= dL * fExpand;
	boxInGeo.xMax() += dL * fExpand;

	boxInGeo.yMin() -= dB * fExpand;
	boxInGeo.yMax() += dB * fExpand;

	// 如果高差为0，强行给包围盒设置一个高度值
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

	// 将包围盒重新转换到世界坐标系
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
// 函数：AttachObserver()
// 描述：绑定一个消息观察者
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::AttachObserver(IVBF_ObserverRef* pIObserver)
{
	if(NULL==pIObserver) return;

	// 不允许重复添加
	CVBF_ObserverList::iterator pIter = std::find(m_ObserverList.begin(), m_ObserverList.end(), pIObserver);
	if(pIter==m_ObserverList.end()) m_ObserverList.push_back(pIObserver);
}

//-----------------------------------------------------------------------------
// 函数：DetachObserver()
// 描述：解除一个消息观察者
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::DetachObserver(IVBF_ObserverRef* pIObserver)
{
	if(NULL==pIObserver) return;

	// 不允许重复添加
	CVBF_ObserverList::iterator pIter = std::find(m_ObserverList.begin(), m_ObserverList.end(), pIObserver);
	if(pIter!=m_ObserverList.end()) m_ObserverList.erase(pIter);
}

