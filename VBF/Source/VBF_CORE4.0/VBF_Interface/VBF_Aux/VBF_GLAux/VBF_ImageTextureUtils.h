//*******************************************************************
// FileName��VBF_ImageTextureUtils.h
// Function��ͼ����������
// Author:   ��Ө
// Date:     2014-09-04
//*******************************************************************

#ifndef __VBF_IMAGE_TEXTURE_UTILS_H__
#define __VBF_IMAGE_TEXTURE_UTILS_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>
#include <string>
#include <VBF_Engine/VBF_SceneGraph/ImageSequence>



// ͨ������·����ͼ���ļ���������ͼ��ͼ���뻺���޹أ�����ֵΪNULL��ʾ�ļ������ڣ���ͼ���ʽ��֧�֣�
// ������bFlipDDS -- ddsͼ���Ƿ���Ҫ���·�ת��ע�⣺�����Ҫ��ת��ͼ��Ŀ�߶�����Ϊ2���ݣ�
VBF_GLAUX_EXPORT osg::Image* VBF_CreateImageFromFile(const std::string& strFileName, bool bFlipDDS=false);


// ͨ��RGB���ɫ��ʽ���ڴ����ݣ�����ͼ�񣨷���ֵΪNULL��ʾ�ڴ����ݲ�����Ҫ��
VBF_GLAUX_EXPORT osg::Image* VBF_CreateImageFromBufRGB(int nWidth, int nHeight, unsigned char* pBuf);


// ͨ��RGB���ɫ��ʽ���ڴ����ݣ�����ͼ�񣨷���ֵΪNULL��ʾ�ڴ����ݲ�����Ҫ��
// ������colorBack -- ͼ������Ҫ͸��������ı���ɫ
VBF_GLAUX_EXPORT osg::Image* VBF_CreateImageFromBufRGB(int nWidth, int nHeight, unsigned char* pBuf, const osg::Vec3s& colorBack);


// ͨ��RGBA���ɫ��ʽ���ڴ����ݣ�����ͼ�񣨷���ֵΪNULL��ʾ�ڴ����ݲ�����Ҫ��
VBF_GLAUX_EXPORT osg::Image* VBF_CreateImageFromBufRGBA(int nWidth, int nHeight, unsigned char* pBuf);


// ͨ��һ��ͼ���ļ�����������ͼ�����У�ע�⣺�ú��������κ�ͼ����з�ת��
// ������strFilePath    -- ��̬�����ļ��Ĺ�ͬ·��
//      vFileNames     -- ��̬�����ļ���������·����
//      nFrameInterval -- ��������ͼ��֮������֡��
//      bLoop		   -- �Ƿ�ѭ������
VBF_GLAUX_EXPORT osg::ImageSequence* VBF_CreateImageSequenceFromFiles(const std::string& strFilePath, const std::vector<std::string>& vFileNames,
																	  int nFrameInterval, bool bLoop);


// ͨ��һ��ͼ���ļ�����������ͼ�����У�ע�⣺�ú��������κ�ͼ����з�ת��
// ������strFilePath    -- ��̬�����ļ��Ĺ�ͬ·��
//      nNumTextures   -- ��̬�����ļ�������
//      strFilePrefix  -- �ļ�����ͳһǰ׺������Ϊ���ַ�����
//      strFileExtWithoutDot  -- �ļ���׺����dds, jpg, png�ȣ�
//      nFrameInterval -- ��������ͼ��֮������֡��
//      bLoop		   -- �Ƿ�ѭ������
VBF_GLAUX_EXPORT osg::ImageSequence* VBF_CreateImageSequenceFromFiles(const std::string& strFilePath, int nNumTextures,
																	  const std::string& strFilePrefix, const std::string& strFileExtWithoutDot,
																	  int nFrameInterval, bool bLoop);


// �ӻ����л�ȡͼ�񣬱����ظ���ȡ��ע�⣺���ͼ������Ƶ��ʽ�����ܷŵ������У�����ᵼ��ͬ������Ƶ�ļ���ȫͬ�����ţ�
// ������bFlipDDS -- ddsͼ���Ƿ���Ҫ���·�ת��ע�⣺�����Ҫ��ת��ͼ��Ŀ�߶�����Ϊ2���ݣ�
VBF_GLAUX_EXPORT osg::Image* VBF_GetImageFromCache(const std::string& strFileName, bool bFlipDDS=false);


// �ӻ����л�ȡ���������ظ�����������ͬ����������
// ������bFlipDDS -- ddsͼ���Ƿ���Ҫ���·�ת��ע�⣺�����Ҫ��ת��ͼ��Ŀ�߶�����Ϊ2���ݣ�
VBF_GLAUX_EXPORT osg::Texture2D* VBF_GetTextureFromCache(const std::string& strFileName, bool bFlipDDS=false);


// �ӻ����л�ȡͼ���Ӧ�����������ظ�����������ͬ����������
VBF_GLAUX_EXPORT osg::Texture2D* VBF_GetTextureFromCache(osg::Image* pImage);


// ����ͼ�񣬴�������
VBF_GLAUX_EXPORT osg::Texture2D* VBF_CreateTextureFromImage(osg::Image* pImage);


// �ж�һ��ͼ���Ƿ���Ҫ���·�ת
VBF_GLAUX_EXPORT bool VBF_ImageNeedsFlip(osg::Image* pImage);


// ����֡���������ͼ�����еĲ���ʱ��
VBF_GLAUX_EXPORT float VBF_CalTimeFromFrameInterval(int nFrameInterval, int nNumFiles);

// ����ͼ�����еĲ���ʱ�䣬����֡���
VBF_GLAUX_EXPORT int VBF_CalFrameIntervalFromTime(float fTime, int nNumFiles);

// ����ɫ��ͼ���ȡ��ɫֵ��Ҫ��ͼ��ɫ���Ǻ���ģ�
VBF_GLAUX_EXPORT void VBF_GetColorsFromImage(const std::string& sFnColor,std::vector<osg::Vec4f>& vColors);


#endif 
