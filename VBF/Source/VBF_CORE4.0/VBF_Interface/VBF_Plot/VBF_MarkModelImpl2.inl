//-----------------------------------------------------------------------------
// 函数：GetPopupMenuItems()
// 描述：获取该模型支持的所有弹出菜单项
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vItems)
{
	for(CVBF_AttrList::iterator pIterAttr=m_MarkAttrList.begin(); pIterAttr!=m_MarkAttrList.end(); pIterAttr++)
	{
		IVBF_MarkAttr* pIAttr = *pIterAttr;
		if(pIAttr) pIAttr->GetPopupMenuItems(vItems);
	}

	// 各类模型的通用属性
	if(NULL==m_pIParent)
	{
		if(m_bEnableMenuZBuffer || m_bEnableMenuFillMode)
		{
			CVBF_PopupMenuItem itemSep(IDM_ITEM_STYLE_SEPARATOR);
			vItems.push_back(itemSep);

			CVBF_PopupMenuItem itemPop(IDM_ITEM_STYLE_POPUP, "通用属性", 0, 0);
			vItems.push_back(itemPop);
		}

		if(m_bEnableMenuZBuffer)
		{
			CVBF_PopupMenuItem itemTest(IDM_ITEM_STYLE_CHECK, "深度测试", IDM_MARK_OPERATE_DEPTHTEST, m_bEnableDepthTest);
			vItems.push_back(itemTest);

			CVBF_PopupMenuItem itemWrite(IDM_ITEM_STYLE_CHECK, "深度写入", IDM_MARK_OPERATE_DEPTHWRITE, m_bEnableDepthWrite);
			vItems.push_back(itemWrite);
		}

		if(m_bEnableMenuZBuffer && m_bEnableMenuFillMode)
		{
			CVBF_PopupMenuItem itemSep(IDM_ITEM_STYLE_SEPARATOR);
			vItems.push_back(itemSep);
		}
	}

	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;
		if(pIChild) pIChild->GetPopupMenuItems(vItems);
	}
}

//-----------------------------------------------------------------------------
// 函数：ProcessPopupMenuItem()
// 描述：响应某个菜单项
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::ProcessPopupMenuItem(unsigned int nID)
{
	// 响应ZBuffer开关菜单
	if(nID==IDM_MARK_OPERATE_DEPTHTEST)
	{
		m_bEnableDepthTest = !m_bEnableDepthTest;
		for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
		{
			IVBF_MarkModel* pIChild = *pIter;
			if(pIChild) pIChild->EnableDepthTest(m_bEnableDepthTest);
		}
		return true;
	}
	if(nID==IDM_MARK_OPERATE_DEPTHWRITE)
	{
		m_bEnableDepthWrite = !m_bEnableDepthWrite;
		for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
		{
			IVBF_MarkModel* pIChild = *pIter;
			if(pIChild) pIChild->EnableDepthTest(m_bEnableDepthWrite);
		}
		return true;
	}

	// 所有子节点响应菜单项
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;
		if(NULL==pIChild) continue;
		if(pIChild->GetReserveFlag() & VBF_RESERVEFLAG_ATTRCHILD) continue; // 注意：需要过滤掉属性创建的子模型

		pIChild->ProcessPopupMenuItem(nID);
	}

	// 所有属性响应菜单项
	for(CVBF_AttrList::iterator pIterAttr=m_MarkAttrList.begin(); pIterAttr!=m_MarkAttrList.end(); pIterAttr++)
	{
		IVBF_MarkAttr* pIAttr = *pIterAttr;
		if(pIAttr) pIAttr->ProcessPopupMenuItem(nID);
	}

	return false;
}

//-----------------------------------------------------------------------------
// 函数：WriteToXML()
// 描述：写入
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::WriteToXML(TiXmlElement* pElemMark)
{
	if(!IsAllowSerialize()) return false;
	if(NULL==pElemMark) return false;

	// 写入：模型本身的信息
	WriteModelToXML(pElemMark);

	// 写入：所有子节点
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;
		if(NULL==pIChild) continue;
		if(!pIChild->IsAllowSerialize()) continue;

		DWORD dwReserveFlag = pIChild->GetReserveFlag();
		if(dwReserveFlag & VBF_RESERVEFLAG_ATTRCHILD) continue; // 注意：需要过滤掉属性创建的子模型

		TiXmlElement* pElemChild = new TiXmlElement("Child");
		pElemMark->LinkEndChild( pElemChild );

		pIChild->WriteToXML(pElemChild);
	}

	// 写入：所有属性
	unsigned int nAttrCount = GetMarkAttrCount();
	for(unsigned int i=0; i<nAttrCount; i++)
	{
		IVBF_MarkAttr* pIAttr = GetMarkAttr(i);
		if(NULL==pIAttr) continue;

		TiXmlElement* pElemAttr = new TiXmlElement("Attr");
		pElemMark->LinkEndChild( pElemAttr );

		pIAttr->WriteToXML(pElemAttr);
	}

	// 写入：所有过程
    unsigned int nProcessCount = GetMarkProcessCount();
	for(unsigned int k=0; k<nProcessCount; k++)
	{
		IVBF_MarkProcess* pIProcess = GetMarkProcess(k);
		if(NULL==pIProcess) continue;

		TiXmlElement* pElemProc = new TiXmlElement("Process");
		pElemMark->LinkEndChild( pElemProc );

		pIProcess->WriteToXML(pElemProc);
	}

	return true;
}

//-----------------------------------------------------------------------------
// 函数：ReadFromXML()
// 描述：读取
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::ReadFromXML(TiXmlElement* pElemMark)
{
	if(NULL==pElemMark) return false;

    CVBF_3DEnvironment& env = ::VBF_Get3DEnvironment();
    IVBF_3DPlot* pI3DPlot = env.m_pI3DPlot;
    if(NULL==pI3DPlot) return false;

	// 读取：模型本身的信息
	ReadModelFromXML(pElemMark);

	// 读取：所有子节点
	TiXmlElement* pElemChild = pElemMark->FirstChildElement("Child");
	while(pElemChild)
	{
		IVBF_MarkModel* pIChild = pI3DPlot->CreateMarkModel(pElemChild);
		if(pIChild!=NULL)
		{
			AddChild(pIChild);
		}

		// 查找下一个<Child>节点
		pElemChild = pElemChild->NextSiblingElement("Child");
	}

	// 读取：所有属性
	TiXmlElement* pElemAttr = pElemMark->FirstChildElement("Attr");
	while(pElemAttr)
	{
		// 读取属性类型（不能为空）
		const char* szAttrType = pElemAttr->Attribute("Type");
		if(szAttrType!=NULL && strlen(szAttrType)>0)
		{
			// 解析属性类型
			unsigned int nAttrType = atoi(szAttrType);

			// 添加属性
			IVBF_MarkAttr* pIAttr = AddMarkAttr(nAttrType);
			if(pIAttr!=NULL) pIAttr->ReadFromXML(pElemAttr);
		}

		// 查找下一个<Attr>节点
		pElemAttr = pElemAttr->NextSiblingElement("Attr");
	}

    // 读取：所有过程
    TiXmlElement* pElemProc = pElemMark->FirstChildElement("Process");
    while(pElemProc)
    {
        // 读取过程类型（不能为空）
        const char* szProcessType = pElemProc->Attribute("Type");
        if(szProcessType!=NULL && strlen(szProcessType)>0)
        {
            // 添加过程
            IVBF_MarkProcess* pIProcess = pI3DPlot->CreateMarkProcess(szProcessType);
            if(pIProcess!=NULL) AddMarkProcess(pIProcess);
            if(pIProcess!=NULL) pIProcess->ReadFromXML(pElemProc);
        }

        // 查找下一个<Process>节点
        pElemProc = pElemProc->NextSiblingElement("Process");
    }


	return true;
}

//-----------------------------------------------------------------------------
// 函数：WriteModelToXML()
// 描述：写入模型本身的信息
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::WriteModelToXML(TiXmlElement* pElemMark)
{
	if(NULL==pElemMark) return false;

	// 写入：模型基本信息
	::VBF_SetAttribute(pElemMark, "ID",		  GetID());
	::VBF_SetAttribute(pElemMark, "Code",	  GetCode());
	::VBF_SetAttribute(pElemMark, "Type",	  GetType());
	::VBF_SetAttribute(pElemMark, "TypeDesc", GetTypeDesc());

	// 写入：状态信息
	::VBF_SetAttribute(pElemMark, "Visible", IsVisible());

	// 写入：最小最大可见距离
	::VBF_SetAttribute(pElemMark, "DistMin", GetDistMin());
	::VBF_SetAttribute(pElemMark, "DistMax", GetDistMax());

	// 写入：标志位
	::VBF_SetAttribute(pElemMark, "ReserveFlag", GetReserveFlag());

	// 写入：地理坐标/相对坐标
	osg::Vec3d vGeoPos;
	if( m_pIParent!=NULL && m_pIParent->IsPointMarkModel() ) // 如果有父模型且为点状，返回子模型的相对坐标
	{
		vGeoPos = GetPos();
	}
	else  // 如果没有父模型，返回模型真实的地理坐标
	{
		vGeoPos = GetActualGeoPos();
	}
	::VBF_SetAttribute(pElemMark, "GeoPos", vGeoPos);

	// 写入：各种开关状态
	::VBF_SetAttribute(pElemMark, "EnableLight",			IsLightEnabled());
	::VBF_SetAttribute(pElemMark, "EnablePointSmooth",		IsPointSmoothEnabled());
	::VBF_SetAttribute(pElemMark, "EnableLineSmooth",		IsLineSmoothEnabled());
	::VBF_SetAttribute(pElemMark, "EnablePolygonSmooth",	IsPolygonSmoothEnabled());
	::VBF_SetAttribute(pElemMark, "EnableClipByEarth",		IsClipByEarthEnabled());

	// 写入：包围盒样式（模型没有父节点是才需要写入）
	if(NULL==m_pIParent)
	{
		TiXmlElement* pElemBox = new TiXmlElement("BoundingBox");
		pElemMark->LinkEndChild( pElemBox );
		::VBF_WriteToXML(pElemBox, m_BoundingBoxStyle);
	}

	// 写入：查询信息（模型没有父节点是才需要写入）
	if(NULL==m_pIParent)
	{
		TiXmlElement* pElemQuery = new TiXmlElement("Query");
		pElemMark->LinkEndChild( pElemQuery );

		const VBF_MARKQUERYSTYLE& style = GetQueryStyle();

		::VBF_SetAttribute(pElemQuery,		"Queriable",    IsQueriable());
		::VBF_SetColorAttribute(pElemQuery, "BlendColor",	style.colorBlend);
		::VBF_SetAttribute(pElemQuery,		"Modulate",		style.bModulate);
		::VBF_SetAttribute(pElemQuery,		"InfoItem",     style.dwInfoItem);
		::VBF_SetAttribute(pElemQuery,		"CustomInfo",   style.strCustomInfo);
		::VBF_SetAttribute(pElemQuery,		"FrameVisible", style.bFrameVisible);

		::VBF_WriteToXML(pElemQuery, style.FrameStyle);
		::VBF_WriteToXML(pElemQuery, style.TextStyle);
	}

	return true;
}

//-----------------------------------------------------------------------------
// 函数：ReadModelFromXML()
// 描述：读取模型本身的信息
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::ReadModelFromXML(TiXmlElement* pElemMark)
{
	if(NULL==pElemMark) return false;

	// 读取：状态信息
	bool bVisible = IsVisible();
	::VBF_QueryAttribute(pElemMark, "Visible", bVisible);

	// 读取：最小最大可见距离
	float fDistMin = GetDistMin();
	float fDistMax = GetDistMax();
	::VBF_QueryAttribute(pElemMark, "DistMin", fDistMin);
	::VBF_QueryAttribute(pElemMark, "DistMax", fDistMax);

	// 读取：标志位
	DWORD dwFlag = m_dwReserveFlag;
	::VBF_QueryAttribute(pElemMark, "ReserveFlag", dwFlag);

	// 读取：地理坐标
	osg::Vec3d vPosGeo = GetGeoPos();
	::VBF_QueryAttribute(pElemMark, "GeoPos", vPosGeo);

	// 读取：各种开关状态
	bool bEnableLight			= IsLightEnabled();
	bool bEnablePointSmooth		= IsPointSmoothEnabled();
	bool bEnableLineSmooth		= IsLineSmoothEnabled();
	bool bEnablePolygonSmooth	= IsPolygonSmoothEnabled();
	bool bEnableClipByEarth     = IsClipByEarthEnabled();

	::VBF_QueryAttribute(pElemMark, "EnableLight",			bEnableLight);
	::VBF_QueryAttribute(pElemMark, "EnablePointSmooth",	bEnablePointSmooth);
	::VBF_QueryAttribute(pElemMark, "EnableLineSmooth",		bEnableLineSmooth);
	::VBF_QueryAttribute(pElemMark, "EnablePolygonSmooth",	bEnablePolygonSmooth);
	::VBF_QueryAttribute(pElemMark, "EnableClipByEarth",	bEnableClipByEarth);

	// 更新相关参数
	SetGeoPos(vPosGeo);
	SetVisible(bVisible);
	SetDistMin(fDistMin);
	SetDistMax(fDistMax);
	SetReserveFlag(dwFlag);

	EnableLight(bEnableLight);
	EnablePointSmooth(bEnablePointSmooth);
	EnableLineSmooth(bEnableLineSmooth);
	EnablePolygonSmooth(bEnablePolygonSmooth);
	EnableClipByEarth(bEnableClipByEarth);

	// 读取：包围盒样式
	TiXmlElement* pElemBox = pElemMark->FirstChildElement("BoundingBox");
	if(pElemBox!=NULL)
	{
		VBF_BOUNDINGBOXSTYLE BoxStyle = m_BoundingBoxStyle;
		::VBF_ReadFromXML(pElemBox, BoxStyle);

		// 更新包围盒参数
		SetBoundingBoxStyle(BoxStyle);
	}

	// 读取：查询信息
	TiXmlElement* pElemQuery = pElemMark->FirstChildElement("Query");
	if(pElemQuery!=NULL)
	{
		VBF_MARKQUERYSTYLE style = GetQueryStyle();

		::VBF_QueryAttribute(pElemQuery,		"Queriable",    m_bQueriable);
		::VBF_QueryColorAttribute(pElemQuery,	"BlendColor",	style.colorBlend);
		::VBF_QueryAttribute(pElemQuery,		"Modulate",		style.bModulate);
		::VBF_QueryAttribute(pElemQuery,		"InfoItem",     style.dwInfoItem);
		::VBF_QueryAttribute(pElemQuery,		"CustomInfo",   style.strCustomInfo);
		::VBF_QueryAttribute(pElemQuery,		"FrameVisible", style.bFrameVisible);

		::VBF_ReadFromXML(pElemQuery, style.FrameStyle);
		::VBF_ReadFromXML(pElemQuery, style.TextStyle);

		// 更新查询参数
		SetQueriable(m_bQueriable);
		SetQueryStyle(style);
	}

	return true;
}

//-----------------------------------------------------------------------------
// 函数：ExecuteScript()
// 描述：执行json脚本
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
	if(conf.isEmpty()) return;

	// 读取：状态信息
	bool bVisible = IsVisible();
	if( conf.getIfSet("Visible", bVisible) )
	{
		SetVisible(bVisible);
	}

	// 读取：最小最大可见距离
	float fDistMin = GetDistMin();
	float fDistMax = GetDistMax();
	if( conf.getIfSet("DistMin", fDistMin) )
	{
		SetDistMin(fDistMin);
	}
	if( conf.getIfSet("DistMax", fDistMax) )
	{
		SetDistMax(fDistMax);
	}

	// 读取：标志位
	DWORD dwFlag = m_dwReserveFlag;
	if( conf.getIfSet("ReserveFlag", dwFlag) )
	{
		SetReserveFlag(dwFlag);
	}

	// 读取：地理坐标
	osg::Vec3d vGeoPos = GetGeoPos();
    if( conf.getIfSet("GeoPos", vGeoPos) )
	{
		SetGeoPos(vGeoPos);
	}

	// 读取：各种开关状态
	bool bEnableLight			= IsLightEnabled();
	bool bEnablePointSmooth		= IsPointSmoothEnabled();
	bool bEnableLineSmooth		= IsLineSmoothEnabled();
	bool bEnablePolygonSmooth	= IsPolygonSmoothEnabled();
	bool bEnableClipByEarth     = IsClipByEarthEnabled();
	bool bEnableDepthTest		= IsDepthTestEnabled();
	bool bEnableDepthWrite		= IsDepthWriteEnabled();
	bool bEnableBlendWithParent = IsBlendWithParentEnabled();

	if( conf.getIfSet("EnableLight",			bEnableLight) )				{ EnableLight(bEnableLight); }
	if( conf.getIfSet("EnablePointSmooth",		bEnablePointSmooth) )		{ EnablePointSmooth(bEnablePointSmooth); }
	if( conf.getIfSet("EnableLineSmooth",		bEnableLineSmooth) )		{ EnableLineSmooth(bEnableLineSmooth); }
	if( conf.getIfSet("EnablePolygonSmooth",	bEnablePolygonSmooth) )		{ EnablePolygonSmooth(bEnablePolygonSmooth); }
	if( conf.getIfSet("EnableClipByEarth",		bEnableClipByEarth) )		{ EnableClipByEarth(bEnableClipByEarth); }
	if( conf.getIfSet("EnableDepthTest",		bEnableDepthTest) )			{ EnableDepthTest(bEnableDepthTest); }
	if( conf.getIfSet("EnableBlendWithParent",	bEnableBlendWithParent) )	{ EnableBlendWithParent(bEnableBlendWithParent); }

	// 读取：模型是否混色以及混合的颜色，混合的方式（乘色/替换色）
	bool bEnableBlend;
	osg::Vec4f colorBlend;
	bool bModulate;
	GetBlendColor(bEnableBlend, colorBlend, bModulate);
	if( conf.getIfSet("EnableBlend", bEnableBlend) )
	{
		conf.getIfSet("BlendColor", colorBlend);
		conf.getIfSet("Modulate",   bModulate);
		SetBlendColor(bEnableBlend, colorBlend, bModulate);
	}

	// 读取：模型的渲染顺序
	int nOrder = 0;
	if( conf.getIfSet("RenderOrder_Opaque", nOrder) )
	{
		SetRenderOrder_Opaque(nOrder);
	}
	else if( conf.getIfSet("RenderOrder_Transparent", nOrder) )
	{
		SetRenderOrder_Transparent(nOrder);
	}

	bool bRenderHint = false;
	if( conf.getIfSet("RenderHint_Opaque", bRenderHint) )
	{
		SetRenderHint_Opaque();
	}
	else if( conf.getIfSet("RenderHint_Transparent", bRenderHint) )
	{
		SetRenderHint_Transparent();
	}
	else if( conf.getIfSet("RenderHint_Default", bRenderHint) )
	{
		SetRenderHint_Default();
	}

	// 读取：包围盒样式
	const CVBF_Config& confBox = conf.child("BoundingBox");
	if( !confBox.isEmpty() )
	{
		VBF_BOUNDINGBOXSTYLE BoxStyle = m_BoundingBoxStyle;
		::VBF_ReadFromJson(confBox, BoxStyle);

		// 更新包围盒参数
		SetBoundingBoxStyle(BoxStyle);
	}

	// 读取：查询信息
	const CVBF_Config& confQuery = conf.child("Query");
	if( !confQuery.isEmpty() )
	{
		VBF_MARKQUERYSTYLE style = GetQueryStyle();

		confQuery.getIfSet("Queriable",		m_bQueriable);
		confQuery.getIfSet("BlendColor",	style.colorBlend);
		confQuery.getIfSet("Modulate",		style.bModulate);
		confQuery.getIfSet("InfoItem",		style.dwInfoItem);
		confQuery.getIfSet("CustomInfo",	style.strCustomInfo);
		confQuery.getIfSet("FrameVisible",	style.bFrameVisible);

		::VBF_ReadFromJson(confQuery, style.FrameStyle);
		::VBF_ReadFromJson(confQuery, style.TextStyle);

		// 更新查询参数
		SetQueriable(m_bQueriable);
		SetQueryStyle(style);
	}
}
