//*******************************************************************
// FileName��VBF_SymbolManager.h
// Function����״������Ź�����
// Author:   ��Ө
// Date:     2014-05-14
//*******************************************************************

#ifndef __VBF_SYMBOL_MANAGER_H__
#define __VBF_SYMBOL_MANAGER_H__

#include <VBF_Symbol/VBF_JBPointLib/VBF_Symbol.h>

class VBF_JBPOINTLIB_EXPORT CVBF_SymbolManager
{
public:
	CVBF_SymbolManager();
	virtual ~CVBF_SymbolManager();

public:

	// ��ȡ�����ļ������з��������Ϣ
	const std::map<int, VBF_SYMBOLCLASS_INFO>* GetAllSymbolClassInfos(const char* szFileName);

	// ��ȡ�����ļ������з��ŵ���Ϣ
	const std::map<int, CVBF_Symbol*>* GetAllSymbolInfos(const char* szFileName);

	// ��ѯ������Ϣ
	CVBF_Symbol* LookupSymbol(const char* szFileName, unsigned int nID);

private:

	// ������о�����Ϣ
	void Clear();

	// ���ؾ����ļ�
	bool LoadFile(const char* szFileName);
};



#endif 
