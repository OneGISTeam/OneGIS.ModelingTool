//*******************************************************************
// FileName��IVBF_MarkModelMesh.h
// Function��Mesh��״��ͼʵ��ģ�ͽӿ�
// Author:
// Date:     2009-4-1
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_MESH_H__
#define __IVBF_MARK_MODEL_MESH_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelMesh
// �ӿ�������Meshʵ��ģ��
//--------------------------------------------------------------------
class IVBF_MarkModelMesh : public IVBF_MarkModelPoint
{
public:
	virtual ~IVBF_MarkModelMesh() {}

    // ����/��ȡģ�͵������ļ�������·����������ļ������ڣ�����false
    // ������strFileName -- �����׺Ϊxml����ʾ��ģ��Ϊ���ģ�ͣ���ʱ������bFlipDDS����
    //                     �����׺Ϊ3ds/vmesh/flt�ȣ���ʾ��ģ��Ϊ����ģ�ͣ���ʱ��ʹ��bFlipDDS����
    //       bFlipDDS   -- ģ���е�dds�����Ƿ���Ҫ���·�ת��Ĭ��Ϊfalse
    //       bTransparent -- ģ���Ƿ�͸��
    // ˵����OpenGL��DirectX��dds��׼�Ƿ��ģ����dds���ú��߱�׼�����ģ�bFlipDDS��Ҫ����Ϊtrue
    virtual bool SetFileName(const std::string& strFileName, bool bFlipDDS=false, bool bTransparent=false)=0;
    virtual void GetFileName(std::string& strFileName, bool& bFlipDDS, bool& bTransparent)=0;
    virtual bool LoadActionsFromXml(TiXmlElement* pElemPart)=0;

};


#endif 
