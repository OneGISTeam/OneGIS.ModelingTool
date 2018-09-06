//***************************************************************************************
// FileName��IVBF_3DPlotLayer.h
// Function��3D��ͼͼ��ӿ�
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

	/* ��ȡͼ�����ڵı�ͼ�ĵ�ָ�� */
	virtual  DWORD  GetDocPtr()=0;

	/* ����/��ȡͼ����ӵ���С���룬Ĭ��Ϊ0.0 (��λ����) */
	virtual void	SetDistMin(float fDistMin)=0;
	virtual float	GetDistMin()=0;

	/* ����/��ȡͼ����ӵ������룬Ĭ��ΪFLT_MAX (��λ����) */
	virtual void	SetDistMax(float fDistMax)=0;
	virtual float	GetDistMax()=0;

	virtual void	SetVisible(bool bVisible)=0;							// ����ͼ���Ƿ���ʾ
	virtual bool	IsVisible()=0;											// �ж�ͼ���Ƿ�ɼ�

	// ͼ���Ƿ񼤻�
	virtual bool   IsActive()=0;

	virtual const std::string& GetLayerName()=0;							// ��ȡͼ����
	virtual void  AlterLayerName(const std::string& strLayerName)=0;		// ����ͼ����

    // ���ģ��
    virtual void AddMark(IVBF_MarkModel* pIMarkModel)=0;

    // ɾ��ģ��
    virtual void DeleteMark(const std::string& strMarkID)=0;
    virtual void DeleteMark(IVBF_MarkModel* pIMarkModel)=0;
	virtual void DeleteAllMarks()=0;
	
	// �Ƴ�ģ�ͣ���ɾ��ģ�͵�ָ�룬ע�⣺����ֵIVBF_MarkModel*�ںܶ�ʱ��֮�����ü�����Ϊ0������ⲿ��ʹ�ø�ָ������������ü�����
    virtual IVBF_MarkModel* RemoveMark(const std::string& strMarkID)=0;
    virtual void RemoveMark(IVBF_MarkModel* pIMarkModel)=0;

    // ����ģ��
    virtual IVBF_MarkModel* GetMark(const std::string& strMarkID)=0;

	// ��ȡ�ò��ϵ����о���ģ��
	virtual void GetAllMarks(std::vector<IVBF_MarkModel*>& vMarks)=0;

	// ѡ�񵥸�ģ�� (���ûѡ�У�����NULL)
	virtual IVBF_MarkModel* SelectMark(const std::string& strMarkID, bool bClear=true)=0;

	// ѡ����ģ�� (���һ����ûѡ�У�����false)
	virtual bool SelectMark(const std::vector<std::string>& vMarkIDList, bool bClear=true)=0;

	// ��ȡ��ǰ���б�ѡ�е�Ŀ��
	virtual void GetSelectedMarks(std::vector<IVBF_MarkModel*>& vSelMarks)=0;

	virtual void ClearSelectedMark()=0;		// ���ѡ��
	virtual void DeleteSelectedMark()=0;    // ɾ��ѡ��ľ���

	// �Ƿ�Ϊ�ڲ�ͼ�㣨Ĭ��Ϊfalse��
	virtual bool IsInnerLayer()=0;
	virtual void SetInnerLayer(bool bInnerLayer)=0;

	// �Ƿ������л���Ĭ��Ϊtrue��
	virtual bool IsAllowSerialize()=0;
	virtual void SetAllowSerialize(bool bAllow)=0;

	// ��ͼ���йҽ�/�Ƴ�һ���ڵ㣬ע�⣺�ýڵ����Ϊ����ģ�͵ĸ��ڵ�
	virtual void AddSGNode(osg::IVBF_SGNode* pNode)=0;
	virtual void RemoveSGNode(osg::IVBF_SGNode* pNode)=0;

    // ��/���һ����Ϣ�۲��ߣ�������ո�ͼ�㷢���ĸ�����Ϣ��
    virtual void AttachObserver(IVBF_ObserverRef* pIObserver)=0;
    virtual void DetachObserver(IVBF_ObserverRef* pIObserver)=0;

	// ��ȡͼ��ĳ���ͼ���ڵ�
	virtual osg::IVBF_SGNodeGroup* GetRootNode()=0;
    // ��ȡר��Ϊ�ǵ�״ģ�ʹ����ĸ��ڵ㣬���������ܵ���ģ�;����Ӱ��
    virtual osg::IVBF_SGNodeGroup* GetNodeForNotPointMarks()=0;
};


#endif
