//*******************************************************************
// FileName：IVBF_MarkModelPointSet.h
// Function：军标实体模型接口：点集（一组使用相同纹理的点）
// Author:   杜莹
// Date:     2013-12-30
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_POINTSET_H__
#define __IVBF_MARK_MODEL_POINTSET_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <string>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelPointSet
// 接口描述：点集（一组使用相同纹理的点）
//--------------------------------------------------------------------
class IVBF_MarkModelPointSet : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelPointSet() {}
	
	// 设置/获取所有点公用的纹理图像指针
	virtual void        SetTexImage(osg::Image* pImage)=0;
	virtual osg::Image* GetTexImage()=0;

	// 设置/获取纹理原点在位图中的相对位置 (相对于左下角，值域为[0.0, 1.0]，默认值分别为0.5, 0.0)
	virtual void SetTexOrign(float fTexOrignX, float fTexOrignY)=0;
	virtual void GetTexOrign(float& fTexOrignX, float& fTexOrignY)=0;

    // 设置/获取所有点的共同样式（尺寸单位：像素，值域为[1.0, 100.0]，默认值为2.0）
    virtual void                  SetPointStyle(const VBF_POINTSTYLE& style)=0;
    virtual const VBF_POINTSTYLE& GetPointStyle()=0;

    // 向点集中添加一个点
    // 参数bUniqueID表示该ID号是否唯一，如果不唯一，系统需要强行删除上一个具有该ID号的点（该操作会影响效率）
    virtual void AddPoint(const std::string& strID, osg::Vec3d vGeo, bool bUniqueID=true)=0;
	
	// 清空点集
	virtual void Clear()=0;

	// 获取点集中点的个数
	virtual int GetNumPoints()=0;

	// 获取点集中的第n个点（纯粹用于遍历，与添加顺序无关）
	virtual bool GetPoint(int nIndex, std::string& strID, osg::Vec3d& vGeo)=0;
	
	// 选择位于屏幕某处的点，返回该点的ID号
	// 参数fDistLimit表示距离阈值（单位：像素）
	virtual std::string SelectPoint(float x, float y, float fDistLimit)=0;

	// 清除被选中点的选择状态
	virtual void ClearSelected()=0;
};


#endif 
