//*******************************************************************
// FileName��IVBF_MarkModelPolylineTex.h
// Function��ʵ��ģ�ͽӿڣ���ά�ռ��е����ߣ��������ظ�������
// Author:   ��Ө
// Date:     2015-08-25
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_POLYLINE_TEXT_H__
#define __IVBF_MARK_MODEL_POLYLINE_TEXT_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <vector>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


class IVBF_MarkModelPolylineTex : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelPolylineTex() {}

	// ����/��ȡ�����Ƿ񾭳��仯��Ĭ��ֵΪfalse��
	virtual void SetDataDynamic(bool bDynamic)=0;
	virtual bool IsDataDynamic()=0;

	// ����/��ȡ�Ƿ���Ҫ��ϵͳ�ڲ��ش�Բ�߲�ֵ��Ĭ��ֵΪfalse��
	virtual void SetInterpolatable(bool bInterpolate)=0;
	virtual bool IsInterpolatable()=0;

	// ����/��ȡ���ߵ����괮���������꣩
	virtual void                           SetPointsGeo(const std::vector<osg::Vec3d>& vPointsGeo)=0;
	virtual const std::vector<osg::Vec3d>& GetPointsGeo()=0;

	// ���һ���㣨�������꣩
	virtual void AddPointGeo(const osg::Vec3d& ptGeo)=0;

	// �������
	virtual void Clear()=0;

	// ����/��ȡ���ߵ�������ʽ
	virtual void                    SetTextureStyle(const VBF_LINETEXSTYLE& style)=0;
	virtual const VBF_LINETEXSTYLE& GetTextureStyle()=0;
};

#endif 
