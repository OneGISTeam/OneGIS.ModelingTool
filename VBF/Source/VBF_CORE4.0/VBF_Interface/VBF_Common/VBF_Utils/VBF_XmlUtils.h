//*******************************************************************
// FileName��VBF_ReadWriteUtils.h
// Function��ģ�͵Ķ�д���ߺ�����������ṹ��д��ָ����xml�ڵ�
//           ʹ�ø�ͷ�ļ�ʱ����Ҫ���Ӷ�̬�⣺VBF_XML
// Author:   ��Ө
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

//======================================= ��ָ����xml�ڵ���д����� =======================================//

// ��ָ����xml�ڵ���д��һ���������͵ı���
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


// ��ָ����xml�ڵ���д��һ��nγ����
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const osg::Vec2f& value);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const osg::Vec3f& value);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const osg::Vec3d& value);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const osg::Vec4f& value);


// ��ָ����xml�ڵ���д��һ��osg::Vec4f�͵���ɫ����
// ������bIncludingAlpha -- �Ƿ�д��alpha����
VBF_UTILS_EXPORT void VBF_SetColorAttribute(TiXmlElement* pElem, const std::string& strName, const osg::Vec4f& color, bool bWriteAlpha=true);


// ��ָ����xml�ڵ���д��һ��osg::Matrixd�͵ľ���
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const osg::Matrixd& mat);


// ��ָ����xml�ڵ���д��������͵������б�ͨ������д��������괮��
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<int>& valueList);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<unsigned int>& valueList);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<osg::Vec2f>& valueList);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<osg::Vec3f>& valueList);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<osg::Vec4f>& valueList);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<osg::Vec2d>& valueList);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<osg::Vec3d>& valueList);
VBF_UTILS_EXPORT void VBF_SetAttribute(TiXmlElement* pElem, const std::string& strName, const std::vector<osg::Vec4d>& valueList);



//======================================= ��ָ����xml�ڵ��ж�ȡ���� =======================================//

// ��ָ����xml�ڵ��ж�ȡ���ֻ������͵ı���
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


// ��ָ����xml�ڵ��ж�ȡһ��nγ����
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, osg::Vec2f& value);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, osg::Vec3f& value);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, osg::Vec3d& value);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, osg::Vec4f& value);


// ��ָ����xml�ڵ��ȡһ��osg::Vec4f�͵���ɫ����
// ����˵����bReadAlpha -- �Ƿ��ȡalpha����
VBF_UTILS_EXPORT bool VBF_QueryColorAttribute(TiXmlElement* pElem, const std::string& strName, osg::Vec4f& color, bool bReadAlpha=true);


// ��ָ����xml�ڵ��ж�ȡһ��std::vector<***>�͵����괮�� ������ָ�Ϊ������x y�������
VBF_UTILS_EXPORT bool VBF_SplitValueList(TiXmlElement* pElem, const std::string& strName, std::vector<std::string>& valueStrList);


// ��ָ����xml�ڵ��ж�ȡһ��osg::Matrixd�͵ľ���
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, osg::Matrixd& mat);


// ��ָ����xml�ڵ��ж�ȡ�������͵������б�ͨ�����ڶ�ȡ�������괮��
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<int>& valueList);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<unsigned int>& valueList);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<osg::Vec2f>& valueList);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<osg::Vec3f>& valueList);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<osg::Vec4f>& valueList);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<osg::Vec2d>& valueList);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<osg::Vec3d>& valueList);
VBF_UTILS_EXPORT bool VBF_QueryAttribute(TiXmlElement* pElem, const std::string& strName, std::vector<osg::Vec4d>& valueList);



//======================================= ����ṹ��Ķ�д =======================================//


// д��/��ȡ����ʽ
VBF_UTILS_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, const VBF_POINTSTYLE& style);
VBF_UTILS_EXPORT void VBF_ReadFromXML(TiXmlElement* pElem, VBF_POINTSTYLE& style);


// д��/��ȡ��������ʽ
VBF_UTILS_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, const VBF_LINESTYLE& style);
VBF_UTILS_EXPORT void VBF_ReadFromXML(TiXmlElement* pElem, VBF_LINESTYLE& style);


// д��/��ȡ��ά�������ʽ
VBF_UTILS_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, const VBF_POLYGON2DSTYLE& style);
VBF_UTILS_EXPORT void VBF_ReadFromXML(TiXmlElement* pElem, VBF_POLYGON2DSTYLE& style);


// д��/��ȡ��ά�������ʽ
VBF_UTILS_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, const VBF_POLYGON3DSTYLE& style);
VBF_UTILS_EXPORT void VBF_ReadFromXML(TiXmlElement* pElem, VBF_POLYGON3DSTYLE& style);


// д��/��ȡ�ı���ʽ
VBF_UTILS_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, const VBF_TEXTSTYLE& style);
VBF_UTILS_EXPORT void VBF_ReadFromXML(TiXmlElement* pElem, VBF_TEXTSTYLE& style);


// д��/��ȡ��Χ����ʽ
VBF_UTILS_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, const VBF_BOUNDINGBOXSTYLE& style);
VBF_UTILS_EXPORT void VBF_ReadFromXML(TiXmlElement* pElem, VBF_BOUNDINGBOXSTYLE& style);


#endif
