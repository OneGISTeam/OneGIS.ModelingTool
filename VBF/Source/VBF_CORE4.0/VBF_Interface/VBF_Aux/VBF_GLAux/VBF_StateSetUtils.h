//***************************************************************************************
// FileName：VBF_StateSetUtils.h
// Function：与渲染状态有关的工具函数
// Author:   杜莹
// Date:     2014-11-21
//***************************************************************************************

#ifndef __VBF_STATESET_UTILS_H__
#define __VBF_STATESET_UTILS_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/StateSet>


// 开启/关闭点光滑
VBF_GLAUX_EXPORT void VBF_EnablePointSmooth(osg::StateSet* ss, bool bEnable);


// 开启/关闭线光滑
VBF_GLAUX_EXPORT void VBF_EnableLineSmooth(osg::StateSet* ss, bool bEnable);


// 开启/关闭面光滑
VBF_GLAUX_EXPORT void VBF_EnablePolygonSmooth(osg::StateSet* ss, bool bEnable);


// 解决z-fighting问题
VBF_GLAUX_EXPORT void VBF_ProcessZFighting(osg::StateSet* ss);


#endif
