//*******************************************************************
// FileName��IVBF_MarkModelLod.h
// Function��Lodʵ��ģ�ͽӿ�
// Author:   ��Ө
// Date:     2014-08-07
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_LOD_H__
#define __IVBF_MARK_MODEL_LOD_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


// Lodģ���и����ӽڵ��Ԥ����־��ϵͳʹ�������4λ
#define VBF_RESERVEFLAG_LODCHILD       0x0010



//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelLod
// �ӿ�������Lodʵ��ģ��
//--------------------------------------------------------------------
class IVBF_MarkModelLod : public IVBF_MarkModelPoint
{
public:
    virtual ~IVBF_MarkModelLod() {}

    // ���һ��Lod�ӽڵ�
    virtual bool AddLodChild(IVBF_MarkModelPoint* pIChild)=0;

    // ������ʽ�ļ��е�xml�ڵ���Ϣ�����������ӽڵ�
    virtual bool LoadLodChildFromStyleXml(TiXmlElement* pElemMark)=0;

    // ��ȡLod�ӽڵ�ĸ���
    virtual int GetLodChildCount()=0;

    // ��ȡ��n��Lod�ӽڵ㣬���ڱ���
    virtual IVBF_MarkModelPoint* GetLodChild(int nIndex)=0;
};


#endif 
