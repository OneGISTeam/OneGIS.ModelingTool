//*******************************************************************
// FileName��VBF_ReadWriteUtils.h
// Function��ģ�͵Ķ�д���ߺ�����������ṹ��д��ָ����xml�ڵ�
//           ʹ�ø�ͷ�ļ�ʱ����Ҫ���Ӷ�̬�⣺VBF_XML
// Author:   ��Ө
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

// д��/��ȡ�����������ʽ
VBF_GLAUX_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, const VBF_LINETEXSTYLE& style);
VBF_GLAUX_EXPORT void VBF_ReadFromXML(TiXmlElement* pElem, VBF_LINETEXSTYLE& style);


// д��/��ȡͼ����Ϣ
VBF_GLAUX_EXPORT void VBF_WriteToXML(TiXmlElement* pElem, osg::Image* pImage);
VBF_GLAUX_EXPORT bool VBF_ReadFromXML(TiXmlElement* pElem, osg::Image*& pImage);


// д��/��ȡ��̬������Ϣ
// ����˵����strTexFileNames -- ���ж�̬������ļ���������·����
//          nFrameInterval -- ��������ͼ��֮������֡��
//          bLoop          -- �����Ƿ�ѭ������
VBF_GLAUX_EXPORT bool VBF_WriteToXML_DynTex(TiXmlElement* pElem, const std::vector<std::string>& vTexFileNames, int nFrameInterval, bool bLoop);
VBF_GLAUX_EXPORT bool VBF_ReadFromXML_DynTex(TiXmlElement* pElem, std::vector<std::string>& vTexFileNames, int& nFrameInterval, bool& bLoop);


// д��/��ȡ�決������Ϣ
// ����˵����strTexFileName -- �決������ļ���������·����
//          nFrameInterval -- ��������ͼ��֮������֡��
//          bLoop          -- �����Ƿ�ѭ������
VBF_GLAUX_EXPORT bool VBF_WriteToXML_BakingTex(TiXmlElement* pElem, const std::string& strTexFileName, int nNumRows, int nNumCols, int nFrameInterval, bool bLoop);
VBF_GLAUX_EXPORT bool VBF_ReadFromXML_BakingTex(TiXmlElement* pElem, std::string& strTexFileName, int& nNumRows, int& nNumCols, int& nFrameInterval, bool& bLoop);



#endif
