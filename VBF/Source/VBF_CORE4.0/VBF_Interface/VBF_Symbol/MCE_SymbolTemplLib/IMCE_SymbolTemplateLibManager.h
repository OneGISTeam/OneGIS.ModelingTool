
#ifndef __SYSBOLTEMPLATLIBMANAGER_H__
#define __SYSBOLTEMPLATLIBMANAGER_H__

#include "IMCE_SymbolTemplate.h"
#include "IMCE_SymbolTemplateClass.h"

#pragma warning(disable: 4786)
#include <string>
using namespace std ;


typedef struct  _tagIntPlusString
{
	_tagIntPlusString()
	{
	}
	_tagIntPlusString( long lT,CString& sT )
	{
		lData = lT ;
		sData = sT ;
	}
	_tagIntPlusString( _tagIntPlusString& cls )
	{
		Set( cls ) ;
	}
	_tagIntPlusString& operator=( _tagIntPlusString& cls )
	{
		Set( cls ) ;
		return *this ;
	}

	void Set( _tagIntPlusString& cls )
	{
		lData = cls.lData ;
		sData = cls.sData ;
	}

	void Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			ar << lData ;
			ar << sData ;
		}
		else
		{
			ar >> lData ;
			ar >> sData ;
		}
	}

	long		lData;
	CString		sData;

} INTPLUSSTRING ;

class IMCE_SymbolTemplateLibManager
{
public:
	virtual ~IMCE_SymbolTemplateLibManager(){}
public:

	// 装载符号模板库名与相应的文件名对照表
	virtual bool AutoLoadLibMapTable(CString sDataPath) =0;


	// 获取所有的符号模板库的名称
	virtual void GetPointLibNames( CStringArray& a ) =0;
	virtual void GetPointLibNames_S( CStringArray& a ) =0;
	virtual void GetLineLibNames( CStringArray& a )  =0;

	virtual string GetPointLibPathName( const string& sKey )  =0;
	virtual string GetPointLibPathName_S( const string& sKey )  =0;
	virtual string GetLineLibPathName( const string& sKey )  =0;

	// 获取符号模板库中符号模板的编码数组
	virtual bool GetSupperSymbolCodes( CString sFN,CDTIS_Array<unsigned int>& auCodes )=0;

	virtual bool GetPointLibClassTable( CString sFN,CDTIS_Array< INTPLUSSTRING >& cls )=0;
	virtual bool GetLineLibClassTable( CString sFN,CDTIS_Array< INTPLUSSTRING >& cls ) =0;

	//根据编码获取符号模板类
	virtual IMCE_SymbolTemplateClass* FindPointSymbolClass_File( CString sFN,unsigned int uCode )=0;	
	virtual IMCE_SymbolTemplateClass* FindLineSymbolClass_File( CString sFN,unsigned int uCode )=0;
	
	//根据编码获取符号模板
	virtual IMCE_PointSymbolTemplate*  FindPointSymbol( const CString& sLibN,unsigned int uCode)=0;
	virtual IMCE_LineSymbolTemplate*   FindLineSymbol( const CString& sLibN,unsigned int uCode)=0;
	virtual IMCE_SupperSymbolTemplate* FindPointSymbol_S( const CString& sLibN,unsigned int uCode)=0;

	virtual IMCE_PointSymbolTemplate*  FindPointSymbol_File( CString sFN,unsigned int uCode )=0;
	virtual IMCE_LineSymbolTemplate*   FindLineSymbol_File( CString sFN,unsigned int uCode )=0;
	virtual IMCE_SupperSymbolTemplate* FindSupperSymbol_File( CString sFN,unsigned int uCode )=0;

};
MCE_SYMBOLTEMPLATEIO_EXPORT IMCE_SymbolTemplateLibManager* MCE_GetSymbolTemplateLibManager();
#endif 
