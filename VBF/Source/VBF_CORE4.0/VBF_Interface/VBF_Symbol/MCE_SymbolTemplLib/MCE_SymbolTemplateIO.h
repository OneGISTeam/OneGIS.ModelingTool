
#ifndef __MCE_SYMBOLTEMPLATEIO_H__
#define __MCE_SYMBOLTEMPLATEIO_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <afxmt.h>
#include <afxcoll.h>

#include "IMCE_SymbolMeta.h"
#include "IMCE_SymbolTemplate.h"


#ifndef MCE_SYMBOLTEMPLATEIO

    #define MCE_SYMBOLTEMPLATEIO_EXPORT _declspec(dllimport)


	#if _MSC_VER == 1200

		#ifdef _DEBUG
			#pragma comment(lib,"..\\..\\Lib6D\\MCE_SymbolTemplateDllD.lib") 
			#pragma message("自动连接  MCE_SymbolTemplateDllD.dll") 
		#else 
			#pragma comment(lib,"..\\..\\Lib6R\\MCE_SymbolTemplateDll.lib") 
			#pragma message("自动连接  MCE_SymbolTemplateDll.dll") 
		#endif 

	#else if _MSC_VER == 2000

		#ifdef _DEBUG
			#pragma comment(lib,"..\\..\\Lib10D\\MCE_SymbolTemplateDllD.lib") 
			#pragma message("自动连接  MCE_SymbolTemplateDllD.dll") 
		#else 
			#pragma comment(lib,"..\\..\\Lib10R\\MCE_SymbolTemplateDll.lib") 
			#pragma message("自动连接  MCE_SymbolTemplateDll.dll") 
		#endif 

	#endif 


#else 
    #define MCE_SYMBOLTEMPLATEIO_EXPORT _declspec(dllexport) 
#endif 

#ifndef DtisPlotDirFN
	#define DtisPlotDirFN  _T("DtisPlot.dir")
#endif 

extern "C" AFX_EXT_API 
void WINAPI DtisInitMAPSblTemplateIODLL();

MCE_SYMBOLTEMPLATEIO_EXPORT IMCE_SymbolMetaArc* MCE_CreateSymbolMetaArc(osg::Vec2i ptCenter,int nRadianL,int nRadianS,float fAngleB,float fAngleE);

MCE_SYMBOLTEMPLATEIO_EXPORT IMCE_SymbolMetaPoly* MCE_CreateSymbolMetaPoly(CDTIS_Array<osg::Vec2i>& apt,bool bClose);
MCE_SYMBOLTEMPLATEIO_EXPORT IMCE_SymbolMetaText* MCE_CreateSymbolMetaText();
MCE_SYMBOLTEMPLATEIO_EXPORT IMCE_SymbolMetaBoundText* MCE_CreateSymbolMetaBoundText();
MCE_SYMBOLTEMPLATEIO_EXPORT IMCE_SymbolMetaMultiImage* MCE_CreateSymbolMetaMultiImage();
MCE_SYMBOLTEMPLATEIO_EXPORT IMCE_SymbolMetaCombination* MCE_CreateSymbolMetaCombination();

MCE_SYMBOLTEMPLATEIO_EXPORT IMCE_LineSymbolTemplate* MCE_CreateSymbolTemplateLine();
MCE_SYMBOLTEMPLATEIO_EXPORT IMCE_PointSymbolTemplate* MCE_CreateSymbolTemplatePoint();

#endif