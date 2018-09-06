//*******************************************************************
// FileName��IVBF_MarkModelFanGeo.h
// Function��ʵ��ģ�ͽӿڣ�ʹ�õ�����������Σ����ر�
// Author:   ��Ө
// Date:     2014-03-04
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_FAN_H__
#define __IVBF_MARK_MODEL_FAN_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <vector>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


class IVBF_MarkModelFanGeo : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelFanGeo() {}

	// ����/��ȡ�����Ƿ񾭳��仯��Ĭ��ֵΪfalse��
	virtual void SetDataDynamic(bool bDynamic)=0;
	virtual bool IsDataDynamic()=0;

	// ����/��ȡ���ε�Բ�ĵ㣬�����յ㣨�������꣩
	virtual void SetTessGeo(const osg::Vec3d& ptCenter, const osg::Vec3d& ptBegin, const osg::Vec3d& ptEnd)=0;
	virtual void GetTessGeo(osg::Vec3d& ptCenter, osg::Vec3d& ptBegin, osg::Vec3d& ptEnd)=0;

	// ��ȡ���β�ֵ������ж��㣨�������꣬��Բ�ĵ����������㵽�յ������
	virtual void GetPointsGeo(std::vector<osg::Vec3d>& vPointsGeo)=0;

	// ����/��ȡ����εı����Ƿ�ɼ�
	virtual void SetLineVisible(bool bVisible)=0;
	virtual bool IsLineVisible()=0;

	// ����/��ȡ���ߵ���ʽ
	virtual void				 SetLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle()=0;

	// ����/��ȡ����ε������ʽ������������ʱ��ʹ�ø���ʽ�е�Alphaֵ��Ϊ͸���ȣ�
	virtual void				      SetPolygonStyle(const VBF_POLYGON3DSTYLE& style)=0;
	virtual const VBF_POLYGON3DSTYLE& GetPolygonStyle()=0;
};



#endif 
