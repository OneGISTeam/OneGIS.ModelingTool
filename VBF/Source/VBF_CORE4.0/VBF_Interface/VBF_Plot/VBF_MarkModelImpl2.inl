//-----------------------------------------------------------------------------
// ������GetPopupMenuItems()
// ��������ȡ��ģ��֧�ֵ����е����˵���
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::GetPopupMenuItems(std::vector<CVBF_PopupMenuItem>& vItems)
{
	for(CVBF_AttrList::iterator pIterAttr=m_MarkAttrList.begin(); pIterAttr!=m_MarkAttrList.end(); pIterAttr++)
	{
		IVBF_MarkAttr* pIAttr = *pIterAttr;
		if(pIAttr) pIAttr->GetPopupMenuItems(vItems);
	}

	// ����ģ�͵�ͨ������
	if(NULL==m_pIParent)
	{
		if(m_bEnableMenuZBuffer || m_bEnableMenuFillMode)
		{
			CVBF_PopupMenuItem itemSep(IDM_ITEM_STYLE_SEPARATOR);
			vItems.push_back(itemSep);

			CVBF_PopupMenuItem itemPop(IDM_ITEM_STYLE_POPUP, "ͨ������", 0, 0);
			vItems.push_back(itemPop);
		}

		if(m_bEnableMenuZBuffer)
		{
			CVBF_PopupMenuItem itemTest(IDM_ITEM_STYLE_CHECK, "��Ȳ���", IDM_MARK_OPERATE_DEPTHTEST, m_bEnableDepthTest);
			vItems.push_back(itemTest);

			CVBF_PopupMenuItem itemWrite(IDM_ITEM_STYLE_CHECK, "���д��", IDM_MARK_OPERATE_DEPTHWRITE, m_bEnableDepthWrite);
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
// ������ProcessPopupMenuItem()
// ��������Ӧĳ���˵���
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::ProcessPopupMenuItem(unsigned int nID)
{
	// ��ӦZBuffer���ز˵�
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

	// �����ӽڵ���Ӧ�˵���
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;
		if(NULL==pIChild) continue;
		if(pIChild->GetReserveFlag() & VBF_RESERVEFLAG_ATTRCHILD) continue; // ע�⣺��Ҫ���˵����Դ�������ģ��

		pIChild->ProcessPopupMenuItem(nID);
	}

	// ����������Ӧ�˵���
	for(CVBF_AttrList::iterator pIterAttr=m_MarkAttrList.begin(); pIterAttr!=m_MarkAttrList.end(); pIterAttr++)
	{
		IVBF_MarkAttr* pIAttr = *pIterAttr;
		if(pIAttr) pIAttr->ProcessPopupMenuItem(nID);
	}

	return false;
}

//-----------------------------------------------------------------------------
// ������WriteToXML()
// ������д��
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::WriteToXML(TiXmlElement* pElemMark)
{
	if(!IsAllowSerialize()) return false;
	if(NULL==pElemMark) return false;

	// д�룺ģ�ͱ������Ϣ
	WriteModelToXML(pElemMark);

	// д�룺�����ӽڵ�
	for(CVBF_MarkList::iterator pIter=m_vChildren.begin(); pIter!=m_vChildren.end(); pIter++)
	{
		IVBF_MarkModel* pIChild = *pIter;
		if(NULL==pIChild) continue;
		if(!pIChild->IsAllowSerialize()) continue;

		DWORD dwReserveFlag = pIChild->GetReserveFlag();
		if(dwReserveFlag & VBF_RESERVEFLAG_ATTRCHILD) continue; // ע�⣺��Ҫ���˵����Դ�������ģ��

		TiXmlElement* pElemChild = new TiXmlElement("Child");
		pElemMark->LinkEndChild( pElemChild );

		pIChild->WriteToXML(pElemChild);
	}

	// д�룺��������
	unsigned int nAttrCount = GetMarkAttrCount();
	for(unsigned int i=0; i<nAttrCount; i++)
	{
		IVBF_MarkAttr* pIAttr = GetMarkAttr(i);
		if(NULL==pIAttr) continue;

		TiXmlElement* pElemAttr = new TiXmlElement("Attr");
		pElemMark->LinkEndChild( pElemAttr );

		pIAttr->WriteToXML(pElemAttr);
	}

	// д�룺���й���
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
// ������ReadFromXML()
// ��������ȡ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::ReadFromXML(TiXmlElement* pElemMark)
{
	if(NULL==pElemMark) return false;

    CVBF_3DEnvironment& env = ::VBF_Get3DEnvironment();
    IVBF_3DPlot* pI3DPlot = env.m_pI3DPlot;
    if(NULL==pI3DPlot) return false;

	// ��ȡ��ģ�ͱ������Ϣ
	ReadModelFromXML(pElemMark);

	// ��ȡ�������ӽڵ�
	TiXmlElement* pElemChild = pElemMark->FirstChildElement("Child");
	while(pElemChild)
	{
		IVBF_MarkModel* pIChild = pI3DPlot->CreateMarkModel(pElemChild);
		if(pIChild!=NULL)
		{
			AddChild(pIChild);
		}

		// ������һ��<Child>�ڵ�
		pElemChild = pElemChild->NextSiblingElement("Child");
	}

	// ��ȡ����������
	TiXmlElement* pElemAttr = pElemMark->FirstChildElement("Attr");
	while(pElemAttr)
	{
		// ��ȡ�������ͣ�����Ϊ�գ�
		const char* szAttrType = pElemAttr->Attribute("Type");
		if(szAttrType!=NULL && strlen(szAttrType)>0)
		{
			// ������������
			unsigned int nAttrType = atoi(szAttrType);

			// �������
			IVBF_MarkAttr* pIAttr = AddMarkAttr(nAttrType);
			if(pIAttr!=NULL) pIAttr->ReadFromXML(pElemAttr);
		}

		// ������һ��<Attr>�ڵ�
		pElemAttr = pElemAttr->NextSiblingElement("Attr");
	}

    // ��ȡ�����й���
    TiXmlElement* pElemProc = pElemMark->FirstChildElement("Process");
    while(pElemProc)
    {
        // ��ȡ�������ͣ�����Ϊ�գ�
        const char* szProcessType = pElemProc->Attribute("Type");
        if(szProcessType!=NULL && strlen(szProcessType)>0)
        {
            // ��ӹ���
            IVBF_MarkProcess* pIProcess = pI3DPlot->CreateMarkProcess(szProcessType);
            if(pIProcess!=NULL) AddMarkProcess(pIProcess);
            if(pIProcess!=NULL) pIProcess->ReadFromXML(pElemProc);
        }

        // ������һ��<Process>�ڵ�
        pElemProc = pElemProc->NextSiblingElement("Process");
    }


	return true;
}

//-----------------------------------------------------------------------------
// ������WriteModelToXML()
// ������д��ģ�ͱ������Ϣ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::WriteModelToXML(TiXmlElement* pElemMark)
{
	if(NULL==pElemMark) return false;

	// д�룺ģ�ͻ�����Ϣ
	::VBF_SetAttribute(pElemMark, "ID",		  GetID());
	::VBF_SetAttribute(pElemMark, "Code",	  GetCode());
	::VBF_SetAttribute(pElemMark, "Type",	  GetType());
	::VBF_SetAttribute(pElemMark, "TypeDesc", GetTypeDesc());

	// д�룺״̬��Ϣ
	::VBF_SetAttribute(pElemMark, "Visible", IsVisible());

	// д�룺��С���ɼ�����
	::VBF_SetAttribute(pElemMark, "DistMin", GetDistMin());
	::VBF_SetAttribute(pElemMark, "DistMax", GetDistMax());

	// д�룺��־λ
	::VBF_SetAttribute(pElemMark, "ReserveFlag", GetReserveFlag());

	// д�룺��������/�������
	osg::Vec3d vGeoPos;
	if( m_pIParent!=NULL && m_pIParent->IsPointMarkModel() ) // ����и�ģ����Ϊ��״��������ģ�͵��������
	{
		vGeoPos = GetPos();
	}
	else  // ���û�и�ģ�ͣ�����ģ����ʵ�ĵ�������
	{
		vGeoPos = GetActualGeoPos();
	}
	::VBF_SetAttribute(pElemMark, "GeoPos", vGeoPos);

	// д�룺���ֿ���״̬
	::VBF_SetAttribute(pElemMark, "EnableLight",			IsLightEnabled());
	::VBF_SetAttribute(pElemMark, "EnablePointSmooth",		IsPointSmoothEnabled());
	::VBF_SetAttribute(pElemMark, "EnableLineSmooth",		IsLineSmoothEnabled());
	::VBF_SetAttribute(pElemMark, "EnablePolygonSmooth",	IsPolygonSmoothEnabled());
	::VBF_SetAttribute(pElemMark, "EnableClipByEarth",		IsClipByEarthEnabled());

	// д�룺��Χ����ʽ��ģ��û�и��ڵ��ǲ���Ҫд�룩
	if(NULL==m_pIParent)
	{
		TiXmlElement* pElemBox = new TiXmlElement("BoundingBox");
		pElemMark->LinkEndChild( pElemBox );
		::VBF_WriteToXML(pElemBox, m_BoundingBoxStyle);
	}

	// д�룺��ѯ��Ϣ��ģ��û�и��ڵ��ǲ���Ҫд�룩
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
// ������ReadModelFromXML()
// ��������ȡģ�ͱ������Ϣ
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkModelImpl<T>::ReadModelFromXML(TiXmlElement* pElemMark)
{
	if(NULL==pElemMark) return false;

	// ��ȡ��״̬��Ϣ
	bool bVisible = IsVisible();
	::VBF_QueryAttribute(pElemMark, "Visible", bVisible);

	// ��ȡ����С���ɼ�����
	float fDistMin = GetDistMin();
	float fDistMax = GetDistMax();
	::VBF_QueryAttribute(pElemMark, "DistMin", fDistMin);
	::VBF_QueryAttribute(pElemMark, "DistMax", fDistMax);

	// ��ȡ����־λ
	DWORD dwFlag = m_dwReserveFlag;
	::VBF_QueryAttribute(pElemMark, "ReserveFlag", dwFlag);

	// ��ȡ����������
	osg::Vec3d vPosGeo = GetGeoPos();
	::VBF_QueryAttribute(pElemMark, "GeoPos", vPosGeo);

	// ��ȡ�����ֿ���״̬
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

	// ������ز���
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

	// ��ȡ����Χ����ʽ
	TiXmlElement* pElemBox = pElemMark->FirstChildElement("BoundingBox");
	if(pElemBox!=NULL)
	{
		VBF_BOUNDINGBOXSTYLE BoxStyle = m_BoundingBoxStyle;
		::VBF_ReadFromXML(pElemBox, BoxStyle);

		// ���°�Χ�в���
		SetBoundingBoxStyle(BoxStyle);
	}

	// ��ȡ����ѯ��Ϣ
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

		// ���²�ѯ����
		SetQueriable(m_bQueriable);
		SetQueryStyle(style);
	}

	return true;
}

//-----------------------------------------------------------------------------
// ������ExecuteScript()
// ������ִ��json�ű�
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkModelImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
	if(conf.isEmpty()) return;

	// ��ȡ��״̬��Ϣ
	bool bVisible = IsVisible();
	if( conf.getIfSet("Visible", bVisible) )
	{
		SetVisible(bVisible);
	}

	// ��ȡ����С���ɼ�����
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

	// ��ȡ����־λ
	DWORD dwFlag = m_dwReserveFlag;
	if( conf.getIfSet("ReserveFlag", dwFlag) )
	{
		SetReserveFlag(dwFlag);
	}

	// ��ȡ����������
	osg::Vec3d vGeoPos = GetGeoPos();
    if( conf.getIfSet("GeoPos", vGeoPos) )
	{
		SetGeoPos(vGeoPos);
	}

	// ��ȡ�����ֿ���״̬
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

	// ��ȡ��ģ���Ƿ��ɫ�Լ���ϵ���ɫ����ϵķ�ʽ����ɫ/�滻ɫ��
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

	// ��ȡ��ģ�͵���Ⱦ˳��
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

	// ��ȡ����Χ����ʽ
	const CVBF_Config& confBox = conf.child("BoundingBox");
	if( !confBox.isEmpty() )
	{
		VBF_BOUNDINGBOXSTYLE BoxStyle = m_BoundingBoxStyle;
		::VBF_ReadFromJson(confBox, BoxStyle);

		// ���°�Χ�в���
		SetBoundingBoxStyle(BoxStyle);
	}

	// ��ȡ����ѯ��Ϣ
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

		// ���²�ѯ����
		SetQueriable(m_bQueriable);
		SetQueryStyle(style);
	}
}
