//*******************************************************************
// FileName：VBF_SymbolManager.h
// Function：点状军标符号管理器
// Author:   杜莹
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

	// 获取军标文件中所有符号类的信息
	const std::map<int, VBF_SYMBOLCLASS_INFO>* GetAllSymbolClassInfos(const char* szFileName);

	// 获取军标文件中所有符号的信息
	const std::map<int, CVBF_Symbol*>* GetAllSymbolInfos(const char* szFileName);

	// 查询军标信息
	CVBF_Symbol* LookupSymbol(const char* szFileName, unsigned int nID);

private:

	// 清除所有军标信息
	void Clear();

	// 加载军标文件
	bool LoadFile(const char* szFileName);
};



#endif 
