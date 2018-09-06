//*******************************************************************
// FileName：IVBF_MarkModelLod.h
// Function：Lod实体模型接口
// Author:   杜莹
// Date:     2014-08-07
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_LOD_H__
#define __IVBF_MARK_MODEL_LOD_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


// Lod模型中各个子节点的预留标志，系统使用了最后4位
#define VBF_RESERVEFLAG_LODCHILD       0x0010



//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelLod
// 接口描述：Lod实体模型
//--------------------------------------------------------------------
class IVBF_MarkModelLod : public IVBF_MarkModelPoint
{
public:
    virtual ~IVBF_MarkModelLod() {}

    // 添加一个Lod子节点
    virtual bool AddLodChild(IVBF_MarkModelPoint* pIChild)=0;

    // 根据样式文件中的xml节点信息，加载所有子节点
    virtual bool LoadLodChildFromStyleXml(TiXmlElement* pElemMark)=0;

    // 获取Lod子节点的个数
    virtual int GetLodChildCount()=0;

    // 获取第n个Lod子节点，用于遍历
    virtual IVBF_MarkModelPoint* GetLodChild(int nIndex)=0;
};


#endif 
