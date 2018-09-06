#ifndef __VBF_GRAPHICS_UTILS_H__
#define __VBF_GRAPHICS_UTILS_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>
#include <Types/VBF_3DStyles.h>


// 全局函数：设置实体/网格/坐标点部分的渲染状态
VBF_GLAUX_EXPORT void VBF_SetStateSet_Solid(osg::StateSet* ss, EVBF_SHADE_STYLE nStyleShade, osg::Image* pImage=NULL, EVBF_TEXENV_MODE nTexEnvMode=VBF_TEXENV_MODULATE);
VBF_GLAUX_EXPORT void VBF_SetStateSet_Wireframe(osg::StateSet* ss, const VBF_LINESTYLE& LineStyle);
VBF_GLAUX_EXPORT void VBF_SetStateSet_Point(osg::StateSet* ss, const VBF_POINTSTYLE& PointStyle);

// 全局函数：设置着色器
VBF_GLAUX_EXPORT void VBF_SetShader_Solid(osg::StateSet* ss, bool bEnableColor, bool bEnableTex, EVBF_TEXENV_MODE nTexEnvMode);
VBF_GLAUX_EXPORT void VBF_SetShader_Wireframe(osg::StateSet* ss);



#endif
