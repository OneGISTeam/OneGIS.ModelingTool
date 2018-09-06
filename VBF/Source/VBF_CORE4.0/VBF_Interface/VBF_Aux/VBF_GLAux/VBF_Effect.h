//***************************************************************************************
// FileName��VBF_Effect.h
// Function��Ϊ�ڵ�����/ɾ����Ч
// Author:   ��Ө
// Date:     2013-07-10
//***************************************************************************************

#ifndef __VBF_EFFECT_H__
#define __VBF_EFFECT_H__

#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNode.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>


/** ȫ�ֺ�����Ϊָ���ڵ����/ɾ��һ��������Ч */
VBF_GLAUX_EXPORT bool VBF_AddEffectToNode_Highlight(osg::IVBF_SGNode* pNode, const osg::Vec4f& color, int nHighlightTimes, int nHighlightInterval, bool bHighlightAlways, bool bModulate=true);
VBF_GLAUX_EXPORT bool VBF_RemoveEffectFromNode_Highlight(osg::IVBF_SGNode* pNode);

/** ȫ�ֺ�����Ϊָ���ڵ�ɾ��һ����Ч���������szEffectNameΪNULL����ʾ��������Ч������ */
VBF_GLAUX_EXPORT bool VBF_RemoveEffectFromNode(osg::IVBF_SGNode* pNode, const char* szEffectName=NULL);

/** ȫ�ֺ�����Ϊָ���ڵ㿪��/ֹͣ��˸��Ч
    ����������nFlickerTimes	  -- ��˸���ܴ���
             nFlickerInterval -- ������˸֮��ļ�� (��λ��֡)
             bFlickerAlways	  -- �Ƿ�һֱ��˸�����Ϊtrue������nFlickerTimes��������
*/
VBF_GLAUX_EXPORT void VBF_StartFlicker(osg::IVBF_SGNode* pNode, int nFlickerTimes, int nFlickerInterval, bool bFlickerAlways=false);
VBF_GLAUX_EXPORT void VBF_StartFlicker(osg::Drawable* pDrawable, int nFlickerTimes, int nFlickerInterval, bool bFlickerAlways=false);
VBF_GLAUX_EXPORT void VBF_StopFlicker(osg::IVBF_SGNode* pNode);
VBF_GLAUX_EXPORT void VBF_StopFlicker(osg::Drawable* pDrawable);


/** Ϊ�ڵ����/ɾ����Χ��Ч�� */
VBF_GLAUX_EXPORT osg::IVBF_SGNode*     VBF_CreateBoundingBoxForNode(osg::IVBF_SGNode* pNode, const VBF_BOUNDINGBOXSTYLE& style);
VBF_GLAUX_EXPORT bool           VBF_RemoveBoundingBoxFromNode(osg::IVBF_SGNode* pNode);

// ����8���ǵ����꣬����һ����Χ�нڵ�
VBF_GLAUX_EXPORT osg::IVBF_SGNode* VBF_CreateBoundingBoxNode(osg::Vec3 v[8], const VBF_BOUNDINGBOXSTYLE& style, const std::string& strNodeName="");

/** Ϊ�����ƽڵ����/ɾ����Χ��Ч�� */
VBF_GLAUX_EXPORT osg::Geometry* VBF_CreateBoundingBoxForBillboard(osg::IVBF_SGNodeGeometryBillboard* pGeode, const VBF_BOUNDINGBOXSTYLE& style);
VBF_GLAUX_EXPORT bool           VBF_RemoveBoundingBoxFromBillboard(osg::IVBF_SGNodeGeometryBillboard* pGeode);

/** ȫ�ֺ�����Ϊָ���ڵ����/ɾ��һ����ɫ��Ч */
VBF_GLAUX_EXPORT bool VBF_AddEffectToNode_Blend(osg::IVBF_SGNode* pNode, const osg::Vec4f& color, bool bModulate=true);
VBF_GLAUX_EXPORT bool VBF_RemoveEffectFromNode_Blend(osg::IVBF_SGNode* pNode);


#endif
