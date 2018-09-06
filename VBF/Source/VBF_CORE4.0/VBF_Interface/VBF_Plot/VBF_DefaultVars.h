//*******************************************************************
// FileName：VBF_DefaultVars.h
// Function：定义静态变量，以便作为某些参数的默认值，并以const形式返回
// Author:   杜莹
// Date:     2013-12-16
//*******************************************************************

#ifndef __VBF_DEFAULT_VARS_H__
#define __VBF_DEFAULT_VARS_H__


#include <Types/VBF_3DStyles.h>


// 定义静态变量，以便作为const函数的返回值
static osg::Vec4f			s_colorWhite = osg::Vec4f(1,1,1,1);
static std::string			s_strEmpty	 = "";

static VBF_TEXTSTYLE		s_TextStyleDef;
static VBF_POINTSTYLE		s_PointStyleDef;
static VBF_LINESTYLE		s_LineStyleDef;
static VBF_POLYGON2DSTYLE	s_PolygonStyleDef;

#endif
