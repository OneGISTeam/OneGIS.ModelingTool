//***************************************************************************************
// FileName��VBF_JBPointLibInclude.h
// Function����״�����İ����ļ���ʹ��ʱ��Ҫ��ʽ�������ļ�
// Author:   ��Ө
// Date:     2014-05-14
//***************************************************************************************

#ifndef __VBF_JBPOINT_LIB_INCLUDE_H__
#define __VBF_JBPOINT_LIB_INCLUDE_H__


#include <VBF_Symbol/VBF_JBPointLib/VBF_JBPointLibExport.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_JBPointLibDataTypes.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_Symbol.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_SymbolManager.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_ShapeLine.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_ShapePolyline.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_ShapeHandLine.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_ShapeRectangle.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_ShapePolygon.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_ShapeArbPolygon.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_ShapeCurve.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_ShapeClosedCurve.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_ShapeArc.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_ShapeCircle.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_ShapeAngleArc.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_ShapeSector.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_ShapeEllipse.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_ShapeText.h>


// ȫ�ֺ�������ȡ�����ļ������з��������Ϣ
VBF_JBPOINTLIB_EXPORT const std::map<int, VBF_SYMBOLCLASS_INFO>* VBF_GetAllSymbolClassInfos(const char* szFileName);

// ȫ�ֺ�������ȡ�����ļ������з��ŵ���Ϣ
VBF_JBPOINTLIB_EXPORT const std::map<int, CVBF_Symbol*>* VBF_GetAllSymbolInfos(const char* szFileName);

// ȫ�ֺ������Ӿ����ļ����в���ָ����ŵľ�����Ϣ
VBF_JBPOINTLIB_EXPORT CVBF_Symbol* VBF_LookupSymbolInfo(const char* szFileName, unsigned int nID);

#endif