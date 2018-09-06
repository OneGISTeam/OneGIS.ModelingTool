//***************************************************************************************
// FileName：VBF_Effect.h
// Function：为节点增加/删除特效
// Author:   杜莹
// Date:     2013-07-10
//***************************************************************************************

#ifndef __VBF_EFFECT_H__
#define __VBF_EFFECT_H__

#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNode.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>


/** 全局函数：为指定节点添加/删除一个高亮特效 */
VBF_GLAUX_EXPORT bool VBF_AddEffectToNode_Highlight(osg::IVBF_SGNode* pNode, const osg::Vec4f& color, int nHighlightTimes, int nHighlightInterval, bool bHighlightAlways, bool bModulate=true);
VBF_GLAUX_EXPORT bool VBF_RemoveEffectFromNode_Highlight(osg::IVBF_SGNode* pNode);

/** 全局函数：为指定节点删除一个特效，如果参数szEffectName为NULL，表示不考虑特效的类型 */
VBF_GLAUX_EXPORT bool VBF_RemoveEffectFromNode(osg::IVBF_SGNode* pNode, const char* szEffectName=NULL);

/** 全局函数：为指定节点开启/停止闪烁特效
    函数参数：nFlickerTimes	  -- 闪烁的总次数
             nFlickerInterval -- 两次闪烁之间的间隔 (单位：帧)
             bFlickerAlways	  -- 是否一直闪烁，如果为true，参数nFlickerTimes将被忽略
*/
VBF_GLAUX_EXPORT void VBF_StartFlicker(osg::IVBF_SGNode* pNode, int nFlickerTimes, int nFlickerInterval, bool bFlickerAlways=false);
VBF_GLAUX_EXPORT void VBF_StartFlicker(osg::Drawable* pDrawable, int nFlickerTimes, int nFlickerInterval, bool bFlickerAlways=false);
VBF_GLAUX_EXPORT void VBF_StopFlicker(osg::IVBF_SGNode* pNode);
VBF_GLAUX_EXPORT void VBF_StopFlicker(osg::Drawable* pDrawable);


/** 为节点添加/删除包围盒效果 */
VBF_GLAUX_EXPORT osg::IVBF_SGNode*     VBF_CreateBoundingBoxForNode(osg::IVBF_SGNode* pNode, const VBF_BOUNDINGBOXSTYLE& style);
VBF_GLAUX_EXPORT bool           VBF_RemoveBoundingBoxFromNode(osg::IVBF_SGNode* pNode);

// 利用8个角点坐标，创建一个包围盒节点
VBF_GLAUX_EXPORT osg::IVBF_SGNode* VBF_CreateBoundingBoxNode(osg::Vec3 v[8], const VBF_BOUNDINGBOXSTYLE& style, const std::string& strNodeName="");

/** 为布告牌节点添加/删除包围盒效果 */
VBF_GLAUX_EXPORT osg::Geometry* VBF_CreateBoundingBoxForBillboard(osg::IVBF_SGNodeGeometryBillboard* pGeode, const VBF_BOUNDINGBOXSTYLE& style);
VBF_GLAUX_EXPORT bool           VBF_RemoveBoundingBoxFromBillboard(osg::IVBF_SGNodeGeometryBillboard* pGeode);

/** 全局函数：为指定节点添加/删除一个混色特效 */
VBF_GLAUX_EXPORT bool VBF_AddEffectToNode_Blend(osg::IVBF_SGNode* pNode, const osg::Vec4f& color, bool bModulate=true);
VBF_GLAUX_EXPORT bool VBF_RemoveEffectFromNode_Blend(osg::IVBF_SGNode* pNode);


#endif
