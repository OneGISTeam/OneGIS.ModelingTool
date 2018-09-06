//*******************************************************************
// FileName：VBF_JsonReader.h
// Function：Json脚本的读取工具
// Author:   杜莹
// Date:     2017-07-16
//*******************************************************************

#ifndef __VBF_JSON_READER_WRITER_H__
#define __VBF_JSON_READER_WRITER_H__


#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>
#include <VBF_OS.h>
#include <Types/VBF_3DStyles.h>
#include <Types/VBF_Matrix.h>
#include <string>
#include <vector>
#include <VBF_Common/VBF_Utils/VBF_Config.h>


// 从json脚本中读取Matrix "00 01 02 03, 10 11 12 13, 20 21 22 23, 30 31 32 33"
template<> inline
bool CVBF_Config::getIfSet<osg::Matrixf>(const std::string& key, osg::Matrixf& output) const 
{
    if( !hasValue( key ) ) return false;

	const std::string& strValue = value(key);
	if(strValue.empty()) return false;

	output.makeIdentity();
	sscanf( strValue.c_str(), "%f %f %f %f, %f %f %f %f, %f %f %f %f, %f %f %f %f",
							  output(0,0), output(0,1), output(0,2), output(0,3),
							  output(1,0), output(1,1), output(1,2), output(1,3),
							  output(2,0), output(2,1), output(2,2), output(2,3),
							  output(3,0), output(3,1), output(3,2), output(3,3) );
    
	return true; 
}


template<> inline
bool CVBF_Config::getIfSet<osg::Matrixd>(const std::string& key, osg::Matrixd& output) const 
{
    if( !hasValue( key ) )return false;

	const std::string& strValue = value(key);
	if(strValue.empty()) return false;

	output.makeIdentity();
	sscanf( strValue.c_str(), "%lf %lf %lf %lf, %lf %lf %lf %lf, %lf %lf %lf %lf, %lf %lf %lf %lf",
							  output(0,0), output(0,1), output(0,2), output(0,3),
							  output(1,0), output(1,1), output(1,2), output(1,3),
							  output(2,0), output(2,1), output(2,2), output(2,3),
							  output(3,0), output(3,1), output(3,2), output(3,3) );
    
	return true; 
}

// 从指定的json脚本节点中读取各种类型的向量列表（通常用于读取各类坐标串）
VBF_UTILS_EXPORT bool VBF_ReadFromJson(const CVBF_Config& conf, std::vector<int>& valueList);
VBF_UTILS_EXPORT bool VBF_ReadFromJson(const CVBF_Config& conf, std::vector<unsigned int>& valueList);
VBF_UTILS_EXPORT bool VBF_ReadFromJson(const CVBF_Config& conf, std::vector<float>& valueList);
VBF_UTILS_EXPORT bool VBF_ReadFromJson(const CVBF_Config& conf, std::vector<double>& valueList);
VBF_UTILS_EXPORT bool VBF_ReadFromJson(const CVBF_Config& conf, std::vector<osg::Vec2f>& valueList);
VBF_UTILS_EXPORT bool VBF_ReadFromJson(const CVBF_Config& conf, std::vector<osg::Vec3f>& valueList);
VBF_UTILS_EXPORT bool VBF_ReadFromJson(const CVBF_Config& conf, std::vector<osg::Vec4f>& valueList);
VBF_UTILS_EXPORT bool VBF_ReadFromJson(const CVBF_Config& conf, std::vector<osg::Vec2d>& valueList);
VBF_UTILS_EXPORT bool VBF_ReadFromJson(const CVBF_Config& conf, std::vector<osg::Vec3d>& valueList);
VBF_UTILS_EXPORT bool VBF_ReadFromJson(const CVBF_Config& conf, std::vector<osg::Vec4d>& valueList);


//=============================== 从指定的json脚本节点中读取结构体变量 ===========================//

VBF_UTILS_EXPORT void VBF_ReadFromJson(const CVBF_Config& conf, VBF_POINTSTYLE& style);			// 读取点样式
VBF_UTILS_EXPORT void VBF_ReadFromJson(const CVBF_Config& conf, VBF_LINESTYLE& style);			// 读取折线样式
VBF_UTILS_EXPORT void VBF_ReadFromJson(const CVBF_Config& conf, VBF_POLYGON2DSTYLE& style);		// 读取二维多边形样式
VBF_UTILS_EXPORT void VBF_ReadFromJson(const CVBF_Config& conf, VBF_POLYGON3DSTYLE& style);		// 读取三维多边形样式
VBF_UTILS_EXPORT void VBF_ReadFromJson(const CVBF_Config& conf, VBF_TEXTSTYLE& style);			// 读取文本样式
VBF_UTILS_EXPORT void VBF_ReadFromJson(const CVBF_Config& conf, VBF_BOUNDINGBOXSTYLE& style);	// 读取包围盒样式


/*
VBF_UTILS_EXPORT void VBF_ReadFromJson(const CVBF_Config& conf, VBF_LINETEXSTYLE& style);		// 读取沿线纹理的样式
VBF_UTILS_EXPORT bool VBF_ReadFromJson(const CVBF_Config& conf, osg::Image*& pImage);			// 读取图像信息

// 读取动态纹理信息
// 参数说明：strTexFileNames -- 所有动态纹理的文件名（完整路径）
//          nFrameInterval -- 相邻两幅图像之间间隔的帧数
//          bLoop          -- 纹理是否循环播放
VBF_UTILS_EXPORT bool VBF_ReadFromJson_DynTex(const CVBF_Config& conf, std::vector<std::string>& vTexFileNames, int& nFrameInterval, bool& bLoop);


// 读取烘焙纹理信息
// 参数说明：strTexFileName -- 烘焙纹理的文件名（完整路径）
//          nFrameInterval -- 相邻两幅图像之间间隔的帧数
//          bLoop          -- 纹理是否循环播放
VBF_UTILS_EXPORT bool VBF_ReadFromJson_BakingTex(const CVBF_Config& conf, std::string& strTexFileName, int& nNumRows, int& nNumCols, int& nFrameInterval, bool& bLoop);
*/

#endif
