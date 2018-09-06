//***************************************************************************************
// FileName：IVBF_3DPlotLayer.h
// Function：3D标图图层接口
// Author:
// Date:     2007-12-15
//***************************************************************************************

#ifndef __IVBF_3DPLOT_LAYER_H__
#define __IVBF_3DPLOT_LAYER_H__

#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Plot/IVBF_MarkModel.h>
#include <string>
#include <vector>

namespace osg
{
	class IVBF_SGNode;
}

class IVBF_ObserverRef;


class IVBF_3DPlotLayer : public osg::CVBF_Object
{
public:
	virtual ~IVBF_3DPlotLayer() {}

public:	

	/* 获取图层所在的标图文档指针 */
	virtual  DWORD  GetDocPtr()=0;

	/* 设置/获取图层可视的最小距离，默认为0.0 (单位：米) */
	virtual void	SetDistMin(float fDistMin)=0;
	virtual float	GetDistMin()=0;

	/* 设置/获取图层可视的最大距离，默认为FLT_MAX (单位：米) */
	virtual void	SetDistMax(float fDistMax)=0;
	virtual float	GetDistMax()=0;

	virtual void	SetVisible(bool bVisible)=0;							// 设置图层是否显示
	virtual bool	IsVisible()=0;											// 判断图层是否可见

	// 图层是否激活
	virtual bool   IsActive()=0;

	virtual const std::string& GetLayerName()=0;							// 获取图层名
	virtual void  AlterLayerName(const std::string& strLayerName)=0;		// 更改图层名

    // 添加模型
    virtual void AddMark(IVBF_MarkModel* pIMarkModel)=0;

    // 删除模型
    virtual void DeleteMark(const std::string& strMarkID)=0;
    virtual void DeleteMark(IVBF_MarkModel* pIMarkModel)=0;
	virtual void DeleteAllMarks()=0;
	
	// 移除模型（不删除模型的指针，注意：返回值IVBF_MarkModel*在很短时间之后引用计数将为0，如果外部想使用该指针必须增加引用计数）
    virtual IVBF_MarkModel* RemoveMark(const std::string& strMarkID)=0;
    virtual void RemoveMark(IVBF_MarkModel* pIMarkModel)=0;

    // 查找模型
    virtual IVBF_MarkModel* GetMark(const std::string& strMarkID)=0;

	// 获取该层上的所有军标模型
	virtual void GetAllMarks(std::vector<IVBF_MarkModel*>& vMarks)=0;

	// 选择单个模型 (如果没选中，返回NULL)
	virtual IVBF_MarkModel* SelectMark(const std::string& strMarkID, bool bClear=true)=0;

	// 选择多个模型 (如果一个都没选中，返回false)
	virtual bool SelectMark(const std::vector<std::string>& vMarkIDList, bool bClear=true)=0;

	// 获取当前所有被选中的目标
	virtual void GetSelectedMarks(std::vector<IVBF_MarkModel*>& vSelMarks)=0;

	virtual void ClearSelectedMark()=0;		// 清空选择集
	virtual void DeleteSelectedMark()=0;    // 删除选择的军标

	// 是否为内部图层（默认为false）
	virtual bool IsInnerLayer()=0;
	virtual void SetInnerLayer(bool bInnerLayer)=0;

	// 是否允许串行化（默认为true）
	virtual bool IsAllowSerialize()=0;
	virtual void SetAllowSerialize(bool bAllow)=0;

	// 向图层中挂接/移除一个节点，注意：该节点必须为军标模型的根节点
	virtual void AddSGNode(osg::IVBF_SGNode* pNode)=0;
	virtual void RemoveSGNode(osg::IVBF_SGNode* pNode)=0;

    // 绑定/解除一个消息观察者（负责接收该图层发出的各类消息）
    virtual void AttachObserver(IVBF_ObserverRef* pIObserver)=0;
    virtual void DetachObserver(IVBF_ObserverRef* pIObserver)=0;

	// 获取图层的场景图根节点
	virtual osg::IVBF_SGNodeGroup* GetRootNode()=0;
    // 获取专门为非点状模型创建的根节点，避免他们受到父模型矩阵的影响
    virtual osg::IVBF_SGNodeGroup* GetNodeForNotPointMarks()=0;
};


#endif
