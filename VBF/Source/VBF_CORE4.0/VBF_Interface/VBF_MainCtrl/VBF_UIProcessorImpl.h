//***************************************************************************************
// FileName：VBF_UIProcessorImpl.h
// Function：命令更新接口的模板实现类
// Author:   杜莹
// Date:     2012-10-31
//***************************************************************************************

#ifndef __VBF_UI_PROCESSOR_IMPL_H__
#define __VBF_UI_PROCESSOR_IMPL_H__


#include "VBF_MainCtrl/IVBF_UIProcessor.h"
#include <vector>

class CVBF_UIProcessorImpl : public IVBF_UIProcessor
{
public:
	CVBF_UIProcessorImpl() {}
	virtual ~CVBF_UIProcessorImpl() {}
	
	virtual int			GetUIProcessorCount()			{ return m_vPubProcessorsID.size(); }
	virtual const char* GetUIProcessorID(int nIndex)	{ return ( nIndex>=0 && nIndex<(int)m_vPubProcessorsID.size() )? m_vPubProcessorsID[nIndex] : NULL; }
	virtual bool		UpdateUI(const char* szCommandID, int* piEnable, int* piCheck, int* piRadio, char* szText) { return false; }

public:	
	virtual void Release()	{ delete this; }

protected:	
	std::vector<const char*>		m_vPubProcessorsID;			// 该组件公布的命令更新
};

#endif 
