//*******************************************************************
// FileName：VBF_DynTexture.h
// Function：动态纹理的更新回调
// Author:   杜莹
// Date:     2013-08-01
//*******************************************************************

#ifndef __VBF_DYN_TEXTURE_H__
#define __VBF_DYN_TEXTURE_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/StateAttributeCallback>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexEnv.h>


typedef std::vector< ref_ptr<osg::Image> > CVBF_ImageList;


//--------------------------------------------------------------------
// 定义类：CVBF_CallbackDynTexture()
// 类描述：动态纹理的更新回调
//--------------------------------------------------------------------
class VBF_GLAUX_EXPORT CVBF_CallbackDynTexture : public osg::StateAttributeCallback
{
public:

    CVBF_CallbackDynTexture(const std::vector<std::string>& vFileNames, int nFrameInterval, bool bLoop);

    virtual void operator() (osg::StateAttribute* pAttr, osg::NodeVisitor* nv);

	// 获取第一幅可用图像
	osg::Image* GetFirstImage();

	// 如果不循环播放，是否已经播放完毕
	bool IsOver() { return m_bOver; }

private:
	bool						m_bLoop;				// 纹理是否循环播放
	int							m_nFrameInterval;		// 动态纹理两幅图像之间的帧间隔
	std::vector<std::string>	m_vImageFileNames;		// 动态纹理文件完整名（含路径）

	// 如果不循环播放，是否已经播放完毕
	bool						m_bOver;

	int							m_nFrameCount;			// 帧数累计
	int							m_nImageIndex;			// 动态纹理的图像索引号
	CVBF_ImageList				m_vImagePtrs;			// 动态纹理的图像指针
};


#endif 
