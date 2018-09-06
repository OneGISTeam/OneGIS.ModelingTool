//*******************************************************************
// FileName：VBF_ReadWriteUtils.h
// Function：模型的读写工具函数，将各类结构体写入指定的xml节点
//           使用该头文件时，需要链接动态库：VBF_XML
// Author:   杜莹
// Date:     2015-02-20
//*******************************************************************

#ifndef __VBF_XML_READ_WRITE_UTILS_H__
#define __VBF_XML_READ_WRITE_UTILS_H__


#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>
#include <VBF_OS.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Common/VBF_XML/tinyxml.h>
#include <Types/VBF_Matrix.h>
#include <string>
#include <vector>

//======================================= 向指定的xml节点中写入变量 =======================================//

// 向指定的xml节点中写入一个基本类型的变量
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const bool& bValue);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::string& value);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const char* value);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const int& value);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const unsigned int& value);
//#ifdef _WINDEF_
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const DWORD& value);
//#endif
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const short& value);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const unsigned short& value);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const float& value);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const double& value);


// 向指定的xml节点中写入一个n纬向量
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const osg::Vec2f& value);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const osg::Vec3f& value);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const osg::Vec3d& value);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const osg::Vec4f& value);


// 向指定的xml节点中写入一个osg::Vec4f型的颜色变量
// 参数：bIncludingAlpha -- 是否写入alpha分量
VBF_UTILS_EXPORT void VBF_SetColorAttribute(TiXmlElement* pElem, const std::string& strName, const osg::Vec4f& color, bool bWriteAlpha=true);


// 向指定的xml节点中写入一个osg::Matrixd型的矩阵
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const osg::Matrixd& mat);


// 向指定的xml节点中写入各种类型的向量列表（通常用于写入各类坐标串）
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<int>& valueList);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<unsigned int>& valueList);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<osg::Vec2f>& valueList);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<osg::Vec3f>& valueList);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<osg::Vec4f>& valueList);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<osg::Vec2d>& valueList);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<osg::Vec3d>& valueList);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<osg::Vec4d>& valueList);



//======================================= 从指定的xml节点中读取变量 =======================================//

// 从指定的xml节点中读取各种基本类型的变量
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, int& value);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, unsigned int& value);
//#ifdef _WINDEF_
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, DWORD& value);
//#endif

VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, short& value);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, unsigned short& value);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::string& value);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, float& value);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, double& value);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, bool& bValue);


// 从指定的xml节点中读取一个n纬向量
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, osg::Vec2f& value);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, osg::Vec3f& value);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, osg::Vec3d& value);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, osg::Vec4f& value);


// 从指定的xml节点读取一个osg::Vec4f型的颜色变量
// 参数说明：bReadAlpha -- 是否读取alpha参数
VBF_UTILS_EXPORT bool VBF_QueryColorAttribute(TiXmlElement* pElem, const std::string& strName, osg::Vec4f& color, bool bReadAlpha=true);


// 从指定的xml节点中读取一个std::vector<***>型的坐标串， 并将其分割为类似于x y的坐标对
VBF_UTILS_EXPORT bool VBF_SplitValueList(TiXmlElement* pElem, const std::string& strName, std::vector<std::string>& valueStrList);


// 从指定的xml节点中读取一个osg::Matrixd型的矩阵
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, osg::Matrixd& mat);


// 向指定的xml节点中读取各种类型的向量列表（通常用于读取各类坐标串）
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<int>& valueList);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<unsigned int>& valueList);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<osg::Vec2f>& valueList);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<osg::Vec3f>& valueList);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<osg::Vec4f>& valueList);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<osg::Vec2d>& valueList);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<osg::Vec3d>& valueList);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<osg::Vec4d>& valueList);



//======================================= 各类结构体的读写 =======================================//


// 写入/读取点样式
VBF_UTILS_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, const VBF_POINTSTYLE& style);
VBF_UTILS_EXPORT void VBF_ReadFromXML(TiXmlElement* pElem, VBF_POINTSTYLE& style);


// 写入/读取将折线样式
VBF_UTILS_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, const VBF_LINESTYLE& style);
VBF_UTILS_EXPORT void VBF_ReadFromXML(TiXmlElement* pElem, VBF_LINESTYLE& style);


// 写入/读取二维多边形样式
VBF_UTILS_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, const VBF_POLYGON2DSTYLE& style);
VBF_UTILS_EXPORT void VBF_ReadFromXML(TiXmlElement* pElem, VBF_POLYGON2DSTYLE& style);


// 写入/读取三维多边形样式
VBF_UTILS_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, const VBF_POLYGON3DSTYLE& style);
VBF_UTILS_EXPORT void VBF_ReadFromXML(TiXmlElement* pElem, VBF_POLYGON3DSTYLE& style);


// 写入/读取文本样式
VBF_UTILS_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, const VBF_TEXTSTYLE& style);
VBF_UTILS_EXPORT void VBF_ReadFromXML(TiXmlElement* pElem, VBF_TEXTSTYLE& style);


// 写入/读取包围盒样式
VBF_UTILS_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, const VBF_BOUNDINGBOXSTYLE& style);
VBF_UTILS_EXPORT void VBF_ReadFromXML(TiXmlElement* pElem, VBF_BOUNDINGBOXSTYLE& style);


#endif
