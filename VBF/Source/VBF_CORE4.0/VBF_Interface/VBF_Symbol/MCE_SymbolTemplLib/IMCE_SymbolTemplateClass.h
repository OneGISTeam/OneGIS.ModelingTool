
#ifndef __SYSBOLTEMPLATCLASS_H__
#define __SYSBOLTEMPLATCLASS_H__

//#include "Symbols_MapSB.h"
class IMCE_SymbolTemplate;
class IMCE_SymbolTemplateClass
{
public:
	virtual ~IMCE_SymbolTemplateClass(){}
public:
	virtual void Free()=0;
	virtual IMCE_SymbolTemplate* GetAtEx(int nIndex) =0 ;
	virtual unsigned int GetFirstSymbolCode() =0 ;
	virtual int GetIndex( unsigned int uCode ) =0 ;
	virtual int GetCount() =0 ;
	virtual POSITION GetHeadPosition() =0 ;
	virtual CObject* GetNext(POSITION& pos) =0 ;
	virtual CObject* GetAt(POSITION pos) =0 ;
	virtual POSITION FindIndex(int idx) =0 ;

};

#endif 
