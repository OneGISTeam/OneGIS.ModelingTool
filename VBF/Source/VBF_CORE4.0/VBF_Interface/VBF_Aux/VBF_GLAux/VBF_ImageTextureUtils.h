//*******************************************************************
// FileName：VBF_ImageTextureUtils.h
// Function：图像与纹理工具
// Author:   杜莹
// Date:     2014-09-04
//*******************************************************************

#ifndef __VBF_IMAGE_TEXTURE_UTILS_H__
#define __VBF_IMAGE_TEXTURE_UTILS_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>
#include <string>
#include <VBF_Engine/VBF_SceneGraph/ImageSequence>



// 通过完整路径的图像文件名，创建图像（图像与缓存无关，返回值为NULL表示文件不存在，或图像格式不支持）
// 参数：bFlipDDS -- dds图像是否需要上下翻转（注意：如果需要翻转，图像的宽高都必须为2的幂）
VBF_GLAUX_EXPORT osg::Image* VBF_CreateImageFromFile(const std::string& strFileName, bool bFlipDDS=false);


// 通过RGB真彩色格式的内存数据，创建图像（返回值为NULL表示内存数据不符合要求）
VBF_GLAUX_EXPORT osg::Image* VBF_CreateImageFromBufRGB(int nWidth, int nHeight, unsigned char* pBuf);


// 通过RGB真彩色格式的内存数据，创建图像（返回值为NULL表示内存数据不符合要求）
// 参数：colorBack -- 图像中需要透明处理掉的背景色
VBF_GLAUX_EXPORT osg::Image* VBF_CreateImageFromBufRGB(int nWidth, int nHeight, unsigned char* pBuf, const osg::Vec3s& colorBack);


// 通过RGBA真彩色格式的内存数据，创建图像（返回值为NULL表示内存数据不符合要求）
VBF_GLAUX_EXPORT osg::Image* VBF_CreateImageFromBufRGBA(int nWidth, int nHeight, unsigned char* pBuf);


// 通过一组图像文件，创建动画图像序列（注意：该函数不对任何图像进行翻转）
// 参数：strFilePath    -- 动态纹理文件的共同路径
//      vFileNames     -- 动态纹理文件名（不含路径）
//      nFrameInterval -- 相邻两幅图像之间间隔的帧数
//      bLoop		   -- 是否循环播放
VBF_GLAUX_EXPORT osg::ImageSequence* VBF_CreateImageSequenceFromFiles(const std::string& strFilePath, const std::vector<std::string>& vFileNames,
																	  int nFrameInterval, bool bLoop);


// 通过一组图像文件，创建动画图像序列（注意：该函数不对任何图像进行翻转）
// 参数：strFilePath    -- 动态纹理文件的共同路径
//      nNumTextures   -- 动态纹理文件的总数
//      strFilePrefix  -- 文件名的统一前缀（可以为空字符串）
//      strFileExtWithoutDot  -- 文件后缀（如dds, jpg, png等）
//      nFrameInterval -- 相邻两幅图像之间间隔的帧数
//      bLoop		   -- 是否循环播放
VBF_GLAUX_EXPORT osg::ImageSequence* VBF_CreateImageSequenceFromFiles(const std::string& strFilePath, int nNumTextures,
																	  const std::string& strFilePrefix, const std::string& strFileExtWithoutDot,
																	  int nFrameInterval, bool bLoop);


// 从缓存中获取图像，避免重复读取（注意：如果图像是视频格式，不能放到缓存中，否则会导致同名的视频文件完全同步播放）
// 参数：bFlipDDS -- dds图像是否需要上下翻转（注意：如果需要翻转，图像的宽高都必须为2的幂）
VBF_GLAUX_EXPORT osg::Image* VBF_GetImageFromCache(const std::string& strFileName, bool bFlipDDS=false);


// 从缓存中获取纹理，避免重复创建具有相同参数的纹理
// 参数：bFlipDDS -- dds图像是否需要上下翻转（注意：如果需要翻转，图像的宽高都必须为2的幂）
VBF_GLAUX_EXPORT osg::Texture2D* VBF_GetTextureFromCache(const std::string& strFileName, bool bFlipDDS=false);


// 从缓存中获取图像对应的纹理，避免重复创建具有相同参数的纹理
VBF_GLAUX_EXPORT osg::Texture2D* VBF_GetTextureFromCache(osg::Image* pImage);


// 根据图像，创建纹理
VBF_GLAUX_EXPORT osg::Texture2D* VBF_CreateTextureFromImage(osg::Image* pImage);


// 判断一个图像是否需要上下翻转
VBF_GLAUX_EXPORT bool VBF_ImageNeedsFlip(osg::Image* pImage);


// 根据帧间隔，计算图像序列的播放时间
VBF_GLAUX_EXPORT float VBF_CalTimeFromFrameInterval(int nFrameInterval, int nNumFiles);

// 根据图像序列的播放时间，计算帧间隔
VBF_GLAUX_EXPORT int VBF_CalFrameIntervalFromTime(float fTime, int nNumFiles);

// 根据色谱图像获取颜色值（要求图像色谱是横向的）
VBF_GLAUX_EXPORT void VBF_GetColorsFromImage(const std::string& sFnColor,std::vector<osg::Vec4f>& vColors);


#endif 
