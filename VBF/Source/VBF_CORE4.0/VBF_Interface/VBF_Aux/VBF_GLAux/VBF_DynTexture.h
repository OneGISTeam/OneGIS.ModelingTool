//*******************************************************************
// FileName��VBF_DynTexture.h
// Function����̬����ĸ��»ص�
// Author:   ��Ө
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
// �����ࣺCVBF_CallbackDynTexture()
// ����������̬����ĸ��»ص�
//--------------------------------------------------------------------
class VBF_GLAUX_EXPORT CVBF_CallbackDynTexture : public osg::StateAttributeCallback
{
public:

    CVBF_CallbackDynTexture(const std::vector<std::string>& vFileNames, int nFrameInterval, bool bLoop);

    virtual void operator() (osg::StateAttribute* pAttr, osg::NodeVisitor* nv);

	// ��ȡ��һ������ͼ��
	osg::Image* GetFirstImage();

	// �����ѭ�����ţ��Ƿ��Ѿ��������
	bool IsOver() { return m_bOver; }

private:
	bool						m_bLoop;				// �����Ƿ�ѭ������
	int							m_nFrameInterval;		// ��̬��������ͼ��֮���֡���
	std::vector<std::string>	m_vImageFileNames;		// ��̬�����ļ�����������·����

	// �����ѭ�����ţ��Ƿ��Ѿ��������
	bool						m_bOver;

	int							m_nFrameCount;			// ֡���ۼ�
	int							m_nImageIndex;			// ��̬�����ͼ��������
	CVBF_ImageList				m_vImagePtrs;			// ��̬�����ͼ��ָ��
};


#endif 
