//***************************************************************************************
// FileName��VBF_StateSetUtils.h
// Function������Ⱦ״̬�йصĹ��ߺ���
// Author:   ��Ө
// Date:     2014-11-21
//***************************************************************************************

#ifndef __VBF_STATESET_UTILS_H__
#define __VBF_STATESET_UTILS_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/StateSet>


// ����/�رյ�⻬
VBF_GLAUX_EXPORT void VBF_EnablePointSmooth(osg::StateSet* ss, bool bEnable);


// ����/�ر��߹⻬
VBF_GLAUX_EXPORT void VBF_EnableLineSmooth(osg::StateSet* ss, bool bEnable);


// ����/�ر���⻬
VBF_GLAUX_EXPORT void VBF_EnablePolygonSmooth(osg::StateSet* ss, bool bEnable);


// ���z-fighting����
VBF_GLAUX_EXPORT void VBF_ProcessZFighting(osg::StateSet* ss);


#endif
