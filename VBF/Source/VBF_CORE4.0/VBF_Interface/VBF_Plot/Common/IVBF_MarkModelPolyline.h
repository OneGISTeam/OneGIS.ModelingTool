//*******************************************************************
// FileName��IVBF_MarkModelPolyline.h
// Function��ʵ��ģ�ͽӿڣ���ά�ռ��е����ߣ�����������(NMT)������(MT)����
// Author:   ��Ө
// Date:     2013-12-05
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_POLYLINE_H__
#define __IVBF_MARK_MODEL_POLYLINE_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <vector>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


class IVBF_MarkModelPolyline : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelPolyline() {}

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

	// ����/��ȡ���ߵ���ʽ
	virtual void				 SetLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle()=0;
};

// ����������
class IVBF_MarkModelPolylineNMT : public IVBF_MarkModelPolyline
{
public:
	virtual ~IVBF_MarkModelPolylineNMT() {}

	// ͬʱ�������ߵĵ�����������괮����ʱ����ϵͳ�ڲ���ֵ��
	virtual void SetPointsGeoAndWorld(const std::vector<osg::Vec3d>& vPointsGeo, const std::vector<osg::Vec3d>& vPointsWorld)=0;
};


// ��������
class IVBF_MarkModelPolylineMT : public IVBF_MarkModelPolyline
{
public:
	virtual ~IVBF_MarkModelPolylineMT() {}
};

#endif 
