#ifndef __VBF_GRAPHICS_UTILS_H__
#define __VBF_GRAPHICS_UTILS_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>
#include <Types/VBF_3DStyles.h>


// ȫ�ֺ���������ʵ��/����/����㲿�ֵ���Ⱦ״̬
VBF_GLAUX_EXPORT void VBF_SetStateSet_Solid(osg::StateSet* ss, EVBF_SHADE_STYLE nStyleShade, osg::Image* pImage=NULL, EVBF_TEXENV_MODE nTexEnvMode=VBF_TEXENV_MODULATE);
VBF_GLAUX_EXPORT void VBF_SetStateSet_Wireframe(osg::StateSet* ss, const VBF_LINESTYLE& LineStyle);
VBF_GLAUX_EXPORT void VBF_SetStateSet_Point(osg::StateSet* ss, const VBF_POINTSTYLE& PointStyle);

// ȫ�ֺ�����������ɫ��
VBF_GLAUX_EXPORT void VBF_SetShader_Solid(osg::StateSet* ss, bool bEnableColor, bool bEnableTex, EVBF_TEXENV_MODE nTexEnvMode);
VBF_GLAUX_EXPORT void VBF_SetShader_Wireframe(osg::StateSet* ss);



#endif
