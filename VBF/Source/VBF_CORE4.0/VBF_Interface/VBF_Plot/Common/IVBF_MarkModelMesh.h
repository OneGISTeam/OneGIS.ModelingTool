//*******************************************************************
// FileName：IVBF_MarkModelMesh.h
// Function：Mesh点状标图实体模型接口
// Author:
// Date:     2009-4-1
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_MESH_H__
#define __IVBF_MARK_MODEL_MESH_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelMesh
// 接口描述：Mesh实体模型
//--------------------------------------------------------------------
class IVBF_MarkModelMesh : public IVBF_MarkModelPoint
{
public:
	virtual ~IVBF_MarkModelMesh() {}

    // 设置/获取模型的完整文件名（含路径），如果文件不存在，返回false
    // 参数：strFileName -- 如果后缀为xml，表示该模型为组合模型，此时将忽略bFlipDDS参数
    //                     如果后缀为3ds/vmesh/flt等，表示该模型为单个模型，此时将使用bFlipDDS参数
    //       bFlipDDS   -- 模型中的dds纹理是否需要上下翻转，默认为false
    //       bTransparent -- 模型是否透明
    // 说明：OpenGL和DirectX的dds标准是反的，如果dds是用后者标准产生的，bFlipDDS需要设置为true
    virtual bool SetFileName(const std::string& strFileName, bool bFlipDDS=false, bool bTransparent=false)=0;
    virtual void GetFileName(std::string& strFileName, bool& bFlipDDS, bool& bTransparent)=0;
    virtual bool LoadActionsFromXml(TiXmlElement* pElemPart)=0;

};


#endif 
