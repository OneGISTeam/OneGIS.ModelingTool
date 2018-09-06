//*******************************************************************
// FileName��IVBF_MarkModelPointSet.h
// Function������ʵ��ģ�ͽӿڣ��㼯��һ��ʹ����ͬ����ĵ㣩
// Author:   ��Ө
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
// ����ӿڣ�IVBF_MarkModelPointSet
// �ӿ��������㼯��һ��ʹ����ͬ����ĵ㣩
//--------------------------------------------------------------------
class IVBF_MarkModelPointSet : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelPointSet() {}
	
	// ����/��ȡ���е㹫�õ�����ͼ��ָ��
	virtual void        SetTexImage(osg::Image* pImage)=0;
	virtual osg::Image* GetTexImage()=0;

	// ����/��ȡ����ԭ����λͼ�е����λ�� (��������½ǣ�ֵ��Ϊ[0.0, 1.0]��Ĭ��ֵ�ֱ�Ϊ0.5, 0.0)
	virtual void SetTexOrign(float fTexOrignX, float fTexOrignY)=0;
	virtual void GetTexOrign(float& fTexOrignX, float& fTexOrignY)=0;

    // ����/��ȡ���е�Ĺ�ͬ��ʽ���ߴ絥λ�����أ�ֵ��Ϊ[1.0, 100.0]��Ĭ��ֵΪ2.0��
    virtual void                  SetPointStyle(const VBF_POINTSTYLE& style)=0;
    virtual const VBF_POINTSTYLE& GetPointStyle()=0;

    // ��㼯�����һ����
    // ����bUniqueID��ʾ��ID���Ƿ�Ψһ�������Ψһ��ϵͳ��Ҫǿ��ɾ����һ�����и�ID�ŵĵ㣨�ò�����Ӱ��Ч�ʣ�
    virtual void AddPoint(const std::string& strID, osg::Vec3d vGeo, bool bUniqueID=true)=0;
	
	// ��յ㼯
	virtual void Clear()=0;

	// ��ȡ�㼯�е�ĸ���
	virtual int GetNumPoints()=0;

	// ��ȡ�㼯�еĵ�n���㣨�������ڱ����������˳���޹أ�
	virtual bool GetPoint(int nIndex, std::string& strID, osg::Vec3d& vGeo)=0;
	
	// ѡ��λ����Ļĳ���ĵ㣬���ظõ��ID��
	// ����fDistLimit��ʾ������ֵ����λ�����أ�
	virtual std::string SelectPoint(float x, float y, float fDistLimit)=0;

	// �����ѡ�е��ѡ��״̬
	virtual void ClearSelected()=0;
};


#endif 
