//***************************************************************************************
// FileName��VBF_BakingImage.h
// Function���決ͼ��
// Author:   ��Ө
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

    // ����/��ȡ�ļ������ļ��е�ͼ��������
    void SetFileInfo(const std::string& strFileName, int nNumRows, int nNumCols, bool bFlipDDS);
    void GetFileInfo(std::string& strFileName, int& nNumRows, int& nNumCols, bool& bFlipDDS);

	// ����/��ȡ�������������л���֡���
	virtual void SetFrameInterval(int nFrameInterval);
	virtual int GetFrameInterval() { return m_nFrameInterval; }

	// ����/��ȡ�Ƿ�ѭ�����ţ�Ĭ��ֵΪfalse��
	virtual void SetLoop(bool bLoop);
	virtual bool IsLoop()		{ return m_bLoop; }

    // ��һ������ͼ�Σ��Ա����ͼ��ͬ��������������
    void           AddObserver(osg::Geometry* pGeom);
    osg::Geometry* GetObserver() { return m_piGeom.get(); }

    // �����麯�����������»ص�
    virtual bool requiresUpdateCall() const { return true; }

    // �����麯�������»ص�
    virtual void update(osg::NodeVisitor* nv);

    // �����Ƿ񲥷����
    bool IsOver() { return m_bOver; }

    // ���л�
    bool WriteToXML(TiXmlElement* pElem);
    bool ReadFromXML(TiXmlElement* pElem);
	bool ReadFromJson(const CVBF_Config& conf);

private:

    // ��ͷ��ʼ���Ŷ���
    void Rewind();

private:

    // �ļ��е�ͼ��������
    int     m_nNumRows;
    int     m_nNumCols;
    bool    m_bFlipDDS;

    bool    m_bLoop;
    int     m_nFrameInterval;

    int     m_nFrameCount;
    int     m_nCurrRow;
    int     m_nCurrCol;
    bool    m_bOver;

    // ���������󶨵ļ���ͼ�Σ��Ա����ͼ��ͬ��������������
    observer_ptr<osg::Geometry> m_piGeom;
};


#endif
