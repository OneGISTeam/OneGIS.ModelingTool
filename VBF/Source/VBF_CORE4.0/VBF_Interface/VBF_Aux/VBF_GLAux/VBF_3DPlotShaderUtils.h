//***************************************************************************************
// FileName��VBF_3DPlotShaderUtils.h
// Function��3D��ͼģ��ʹ�õ���ɫ�����ߺ���
// Author:   ��Ө
// Date:     2013-09-22
//***************************************************************************************

#ifndef __VBF_3DPLOT_SHADER_UTILS_H__
#define __VBF_3DPLOT_SHADER_UTILS_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_OS.h>
#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>
#include <Types/VBF_3DStyles.h>


// ������ɫ��
// ������szFnVert, szFnFrag -- ����/Ƭ����ɫ�����ļ���������·������GraphicsSolid.vert
VBF_GLAUX_EXPORT osg::Program* VBF_CreateShader(IVBF_3DMainCtrl* pI3DMainCtrl, const char* szFnVert, const char* szFnFrag);


// ��ʵ�岿��������ɫ�����Ա�ʵ�ֻ�ϡ����յ�Ч��
// ������bEnableColor -- �Ƿ�������ɫ
// ������bEnableTex   -- �Ƿ���������
// ������bEnableLight -- �Ƿ�������
// ������bEnableBlend -- �Ƿ�����ɫ
// ������colorBlend   -- ��ϵ���ɫ
// ������bModulate    -- �Ƿ�ʹ�ó�ɫ
// ������bFlipTex     -- �Ƿ���Ҫ�ߵ�����
VBF_GLAUX_EXPORT void VBF_SetShader_Solid(IVBF_3DMainCtrl* pI3DMainCtrl, osg::StateSet* ss, bool bEnableColor, bool bEnableTex, bool bEnableLight,
                                          bool bEnableBlend, const osg::Vec4f& colorBlend, bool bModulate, bool bFlipTex);

VBF_GLAUX_EXPORT void VBF_SetShader_Solid(IVBF_3DMainCtrl* pI3DMainCtrl, osg::StateSet* ss, bool bEnableColor, bool bEnableTex, bool bEnableLight);


// ��ʵ�岿��������ɫ�����Ա�ʵ�ֶ�����ɫ������Ļ��Ч�����÷�ʽͬʱ���ö�����ɫ�Ͷ�������
// ������nTexEnvMode -- ������ɫ������Ļ�Ϸ�ʽ
VBF_GLAUX_EXPORT void VBF_SetShader_Solid(IVBF_3DMainCtrl* pI3DMainCtrl, osg::StateSet* ss, bool bEnableLight, EVBF_TEXENV_MODE nTexEnvMode);

// �����񲿷�������ɫ�����Ա�ʵ�ֻ�ϡ����յ�Ч��
VBF_GLAUX_EXPORT void VBF_SetShader_Wireframe(IVBF_3DMainCtrl* pI3DMainCtrl, osg::StateSet* ss);


#endif
