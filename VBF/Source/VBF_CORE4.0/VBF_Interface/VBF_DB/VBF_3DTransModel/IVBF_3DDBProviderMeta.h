//***************************************************************************************
// FileName：IVBF_3DDBProviderMeta.h
// Function：地形数据提供者元数据接口
//           每个地形数据提供者都要实现该接口，完成浏览选择URL的功能
// Author:   魏勇
// Date:     2011-10-19
//***************************************************************************************

#ifndef __IVBF_3DDBPROVDIER_META_H__
#define __IVBF_3DDBPROVDIER_META_H__

#include "VBF_3DTransModel/VBF_3DTransBlkDataTypes.h"

class IVBF_3DDBProviderMeta
{
public:
	virtual ~IVBF_3DDBProviderMeta() {}

public:	

 	// 初始化/释放插件
 	virtual void Init()=0;
 	virtual void Release()=0;	
	
	// 功能：获取该Meta所对应的ProviderID
	virtual const char* GetProviderID()=0;

	// 功能：获取该Meta所对应的Provider的描述信息
	virtual const char* GetDesc()=0;

	// 功能：打开URL浏览对话框
	// 参数：pParentHWnd -- 浏览对话框父窗口的句柄，如果为NULL，则没有父窗口
	//		 nType       -- 需要浏览的数据类型
	//       szURL       -- 返回的URL
	// 返回：如果用户按下确认键，返回值为true；否则为false
	virtual bool  BrowseURL(HWND pParentHWnd, VBF_BLK_TYPE nType, char* szURL)=0;
};


#endif

