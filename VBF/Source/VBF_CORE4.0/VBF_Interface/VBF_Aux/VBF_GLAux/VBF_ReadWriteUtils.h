//*******************************************************************
// FileName：VBF_ReadWriteUtils.h
// Function：模型的读写工具函数，将各类结构体写入指定的xml节点
//           使用该头文件时，需要链接动态库：VBF_XML
// Author:   杜莹
// Date:     2015-02-20
//*******************************************************************

#ifndef __VBF_READ_WRITE_UTILS_H__
#define __VBF_READ_WRITE_UTILS_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_OS.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Common/VBF_XML/tinyxml.h>
#include <Types/VBF_Matrix.h>
#include <string>
#include <vector>
#include <VBF_Common/VBF_Utils/VBF_XmlUtils.h>

// 写入/读取沿线纹理的样式
VBF_GLAUX_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, const VBF_LINETEXSTYLE& style);
VBF_GLAUX_EXPORT void VBF_ReadFromXML(TiXmlElement* pElem, VBF_LINETEXSTYLE& style);


// 写入/读取图像信息
VBF_GLAUX_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, osg::Image* pImage);
VBF_GLAUX_EXPORT bool VBF_ReadFromXML(TiXmlElement* pElem, osg::Image*& pImage);


// 写入/读取动态纹理信息
// 参数说明：strTexFileNames -- 所有动态纹理的文件名（完整路径）
//          nFrameInterval -- 相邻两幅图像之间间隔的帧数
//          bLoop          -- 纹理是否循环播放
VBF_GLAUX_EXPORT bool VBF_WriteToXML_DynTex(TiXmlElement* pElem, const std::vector<std::string>& vTexFileNames, int nFrameInterval, bool bLoop);
VBF_GLAUX_EXPORT bool VBF_ReadFromXML_DynTex(TiXmlElement* pElem, std::vector<std::string>& vTexFileNames, int& nFrameInterval, bool& bLoop);


// 写入/读取烘焙纹理信息
// 参数说明：strTexFileName -- 烘焙纹理的文件名（完整路径）
//          nFrameInterval -- 相邻两幅图像之间间隔的帧数
//          bLoop          -- 纹理是否循环播放
VBF_GLAUX_EXPORT bool VBF_WriteToXML_BakingTex(TiXmlElement* pElem, const std::string& strTexFileName, int nNumRows, int nNumCols, int nFrameInterval, bool bLoop);
VBF_GLAUX_EXPORT bool VBF_ReadFromXML_BakingTex(TiXmlElement* pElem, std::string& strTexFileName, int& nNumRows, int& nNumCols, int& nFrameInterval, bool& bLoop);



#endif
