//*******************************************************************
// FileName��VBF_JsonReader.h
// Function��Json�ű��Ķ�ȡ����
// Author:   ��Ө
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


// ��json�ű��ж�ȡMatrix "00 01 02 03, 10 11 12 13, 20 21 22 23, 30 31 32 33"
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

// ��ָ����json�ű��ڵ��ж�ȡ�������͵������б�ͨ�����ڶ�ȡ�������괮��
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


//=============================== ��ָ����json�ű��ڵ��ж�ȡ�ṹ����� ===========================//

VBF_UTILS_EXPORT void VBF_ReadFromJson(const CVBF_Config& conf, VBF_POINTSTYLE& style);			// ��ȡ����ʽ
VBF_UTILS_EXPORT void VBF_ReadFromJson(const CVBF_Config& conf, VBF_LINESTYLE& style);			// ��ȡ������ʽ
VBF_UTILS_EXPORT void VBF_ReadFromJson(const CVBF_Config& conf, VBF_POLYGON2DSTYLE& style);		// ��ȡ��ά�������ʽ
VBF_UTILS_EXPORT void VBF_ReadFromJson(const CVBF_Config& conf, VBF_POLYGON3DSTYLE& style);		// ��ȡ��ά�������ʽ
VBF_UTILS_EXPORT void VBF_ReadFromJson(const CVBF_Config& conf, VBF_TEXTSTYLE& style);			// ��ȡ�ı���ʽ
VBF_UTILS_EXPORT void VBF_ReadFromJson(const CVBF_Config& conf, VBF_BOUNDINGBOXSTYLE& style);	// ��ȡ��Χ����ʽ


/*
VBF_UTILS_EXPORT void VBF_ReadFromJson(const CVBF_Config& conf, VBF_LINETEXSTYLE& style);		// ��ȡ�����������ʽ
VBF_UTILS_EXPORT bool VBF_ReadFromJson(const CVBF_Config& conf, osg::Image*& pImage);			// ��ȡͼ����Ϣ

// ��ȡ��̬������Ϣ
// ����˵����strTexFileNames -- ���ж�̬������ļ���������·����
//          nFrameInterval -- ��������ͼ��֮������֡��
//          bLoop          -- �����Ƿ�ѭ������
VBF_UTILS_EXPORT bool VBF_ReadFromJson_DynTex(const CVBF_Config& conf, std::vector<std::string>& vTexFileNames, int& nFrameInterval, bool& bLoop);


// ��ȡ�決������Ϣ
// ����˵����strTexFileName -- �決������ļ���������·����
//          nFrameInterval -- ��������ͼ��֮������֡��
//          bLoop          -- �����Ƿ�ѭ������
VBF_UTILS_EXPORT bool VBF_ReadFromJson_BakingTex(const CVBF_Config& conf, std::string& strTexFileName, int& nNumRows, int& nNumCols, int& nFrameInterval, bool& bLoop);
*/

#endif
