//***************************************************************************************
// FileName：VBF_3DPlotShaderUtils.h
// Function：3D标图模块使用的着色器工具函数
// Author:   杜莹
// Date:     2013-09-22
//***************************************************************************************

#ifndef __VBF_3DPLOT_SHADER_UTILS_H__
#define __VBF_3DPLOT_SHADER_UTILS_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_OS.h>
#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>
#include <Types/VBF_3DStyles.h>


// 创建着色器
// 参数：szFnVert, szFnFrag -- 顶点/片段着色器的文件名，不含路径，如GraphicsSolid.vert
VBF_GLAUX_EXPORT osg::Program* VBF_CreateShader(IVBF_3DMainCtrl* pI3DMainCtrl, const char* szFnVert, const char* szFnFrag);


// 对实体部分设置着色器，以便实现混合、光照等效果
// 参数：bEnableColor -- 是否启用颜色
// 参数：bEnableTex   -- 是否启用纹理
// 参数：bEnableLight -- 是否开启光照
// 参数：bEnableBlend -- 是否开启混色
// 参数：colorBlend   -- 混合的颜色
// 参数：bModulate    -- 是否使用乘色
// 参数：bFlipTex     -- 是否需要颠倒纹理
VBF_GLAUX_EXPORT void VBF_SetShader_Solid(IVBF_3DMainCtrl* pI3DMainCtrl, osg::StateSet* ss, bool bEnableColor, bool bEnableTex, bool bEnableLight,
                                          bool bEnableBlend, const osg::Vec4f& colorBlend, bool bModulate, bool bFlipTex);

VBF_GLAUX_EXPORT void VBF_SetShader_Solid(IVBF_3DMainCtrl* pI3DMainCtrl, osg::StateSet* ss, bool bEnableColor, bool bEnableTex, bool bEnableLight);


// 对实体部分设置着色器，以便实现顶点颜色与纹理的混合效果（该方式同时启用顶点颜色和顶点纹理）
// 参数：nTexEnvMode -- 顶点颜色与纹理的混合方式
VBF_GLAUX_EXPORT void VBF_SetShader_Solid(IVBF_3DMainCtrl* pI3DMainCtrl, osg::StateSet* ss, bool bEnableLight, EVBF_TEXENV_MODE nTexEnvMode);

// 对网格部分设置着色器，以便实现混合、光照等效果
VBF_GLAUX_EXPORT void VBF_SetShader_Wireframe(IVBF_3DMainCtrl* pI3DMainCtrl, osg::StateSet* ss);


#endif
