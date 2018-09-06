//***************************************************************************************
// FileName：VBF_BakingImage.h
// Function：烘焙图像
// Author:   杜莹
// Date:     2015-09-01
//***************************************************************************************

#ifndef __VBF_BAKING_IMAGE_H__
#define __VBF_BAKING_IMAGE_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Macros.h>
#include <string>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>

class TiXmlElement;
class CVBF_Config;

class VBF_GLAUX_EXPORT CVBF_BakingImage : public osg::Image
{
public:
    CVBF_BakingImage();
    virtual ~CVBF_BakingImage();

    // 设置/获取文件名及文件中的图像行列数
    void SetFileInfo(const std::string& strFileName, int nNumRows, int nNumCols, bool bFlipDDS);
    void GetFileInfo(std::string& strFileName, int& nNumRows, int& nNumCols, bool& bFlipDDS);

	// 设置/获取相邻两幅纹理切换的帧间隔
	virtual void SetFrameInterval(int nFrameInterval);
	virtual int GetFrameInterval() { return m_nFrameInterval; }

	// 设置/获取是否循环播放（默认值为false）
	virtual void SetLoop(bool bLoop);
	virtual bool IsLoop()		{ return m_bLoop; }

    // 绑定一个几何图形，以便随该图像同步更新纹理坐标
    void           AddObserver(osg::Geometry* pGeom);
    osg::Geometry* GetObserver() { return m_piGeom.get(); }

    // 重载虚函数：开启更新回调
    virtual bool requiresUpdateCall() const { return true; }

    // 重载虚函数：更新回调
    virtual void update(osg::NodeVisitor* nv);

    // 纹理是否播放完毕
    bool IsOver() { return m_bOver; }

    // 串行化
    bool WriteToXML(TiXmlElement* pElem);
    bool ReadFromXML(TiXmlElement* pElem);
	bool ReadFromJson(const CVBF_Config& conf);

private:

    // 从头开始播放动画
    void Rewind();

private:

    // 文件中的图像行列数
    int     m_nNumRows;
    int     m_nNumCols;
    bool    m_bFlipDDS;

    bool    m_bLoop;
    int     m_nFrameInterval;

    int     m_nFrameCount;
    int     m_nCurrRow;
    int     m_nCurrCol;
    bool    m_bOver;

    // 该纹理所绑定的几何图形，以便随该图像同步更新纹理坐标
    observer_ptr<osg::Geometry> m_piGeom;
};


#endif
