//*******************************************************************
// FileName��IVBF_MarkModelLink.h
// Function��ʵ��ģ�ͽӿڣ���ͨ��
// Author:   ��Ө
// Date:     2013-11-13
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_LINK_H__
#define __IVBF_MARK_MODEL_LINK_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/ElecMag/VBF_3DPlotDataTypes_ElecMag.h>
#include <Types/VBF_Optional.h>
#include <Types/VBF_3DStyles.h>
#include <Types/Vec4f>
#include <string>



//-------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelLink
// �ӿ���������ͨ��
//-------------------------------------------------------------------
class IVBF_MarkModelLink : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelLink() {}

	// ����/��ȡ��ͨ״̬����ͨ?�Ͽ�
	virtual void SetLinked(bool bLinked)=0;
	virtual bool IsLinked()=0;

	// ����/��ȡԴ��ͨ���ģ�ͣ������ں���SetGeoSrc()
	virtual void			SetMarkSrc(IVBF_MarkModel* pIMarkSrc)=0;
	virtual IVBF_MarkModel*	GetMarkSrc()=0;

	// ����/��ȡĿ����ͨ���ģ�ͣ������ں���SetGeoDst()
	virtual void			SetMarkDst(IVBF_MarkModel* pIMarkDst)=0;
	virtual IVBF_MarkModel*	GetMarkDst()=0;

	// ����/��ȡԴ��ͨ��ĵ�������
	virtual void				SetGeoSrc(const osg::Vec3d& ptGeo)=0;
	virtual const osg::Vec3d&	GetGeoSrc()=0;

	// ����/��ȡĿ����ͨ��ĵ�������
	virtual void			  SetGeoDst(const osg::Vec3d& ptGeo)=0;
	virtual const osg::Vec3d& GetGeoDst()=0;


    // ����·���м�㣨�����㣬���㣩
    virtual void SetCheckPointGeo(const std::vector<osg::Vec3d>& vPointsGeo)=0;


    // ����/��ȡԴ��Ŀ����ͨ��֮����Զ����ֵ������������֮�䣩���������յ㣬��СֵΪ2�����δ���ã�ϵͳ�ڲ����Զ����㣩
	virtual void SetNumInterpolatePoints(int num)=0;
	virtual int  GetNumInterpolatePoints()=0;

    virtual const std::vector<osg::Vec3d>& GetInterPointsGeo() = 0;

    // ����/��ȡ���ε����߶ȣ�Ĭ��ֵΪ0
    virtual void   SetArcMaxHeight(double dHeight) = 0;
    virtual double GetArcMaxHeight() = 0;
};

#endif 
