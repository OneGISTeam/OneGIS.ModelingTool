//*******************************************************************
// FileName��IVBF_MarkModelPolygon.h
// Function��ʵ��ģ�ͽӿڣ���ά�ռ��еĶ���Σ���Ϊ���غͲ��������֣�
// Author:   ��Ө
// Date:     2014-01-10
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_POLYGON_H__
#define __IVBF_MARK_MODEL_POLYGON_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <vector>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec3s>
#include <VBF_Engine/VBF_SceneGraph/Image>


class IVBF_MarkModelPolygon : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelPolygon() {}

	// ����/��ȡ�����Ƿ񾭳��仯��Ĭ��ֵΪfalse��
	virtual void SetDataDynamic(bool bDynamic)=0;
	virtual bool IsDataDynamic()=0;

	// ����/��ȡ���ߵ����괮���������꣩
	virtual void						   SetPointsGeo(const std::vector<osg::Vec3d>& vPointsGeo)=0;
	virtual const std::vector<osg::Vec3d>& GetPointsGeo()=0;

	// ����/��ȡ���ߵ����괮���������꣩���0����������
	// ע�⣺���������������������˳��һ��
	virtual void SetPointsGeoAndTexCoords(const std::vector<osg::Vec3d>& vPointsGeo, const std::vector<osg::Vec2f>& vTexCoords)=0;
	virtual void GetPointsGeoAndTexCoords(std::vector<osg::Vec3d>& vPointsGeo, std::vector<osg::Vec2f>& vTexCoords)=0;

	// ����/��ȡ����εı����Ƿ�ɼ�
	virtual void SetLineVisible(bool bVisible)=0;
	virtual bool IsLineVisible()=0;

	// ����/��ȡ���ߵ���ʽ
	virtual void				 SetLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle()=0;

	// ����/��ȡ����ζ����������ʽ������������ʱ������ʽ��Ч��
	virtual void				      SetPolygonStyle(const VBF_POLYGON3DSTYLE& style)=0;
	virtual const VBF_POLYGON3DSTYLE& GetPolygonStyle()=0;

	// ����/��ȡ����ζ�Ӧ������ͼ��ָ��
	// ������bTexToCache -- �Ƿ���Ҫ��������������뻺�棬Ĭ��Ϊfalse
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

	// ����/��ȡ���������͸���ȣ�ֵ��Ϊ[0.0, 1.0]��Ĭ��ֵΪ0.6��
	virtual void  SetTexAlpha(float fAlpha)=0;
	virtual float GetTexAlpha()=0;

	// ����/��ȡ�Ƿ�ʹ�õ���Ч��
	virtual void EnableFadeIn(bool bEnabled)=0;
	virtual bool IsFadeInEnable()=0;

	// ����/��ȡ����ĳ���ʱ�䣨��λ���룬Ĭ��ֵΪ1.0�룩
	virtual void  SetFadeTime(float fTime)=0;
	virtual float GetFadeTime()=0;
};



// ���ض���Σ�Match Terrain
class IVBF_MarkModelPolygonMT : public IVBF_MarkModelPolygon
{
public:
	virtual ~IVBF_MarkModelPolygonMT() {}
};



// �����ض���Σ�Not Match Terrain
class IVBF_MarkModelPolygonNMT : public IVBF_MarkModelPolygon
{
public:
	virtual ~IVBF_MarkModelPolygonNMT() {}

	// ����/��ȡ����β���������ʽ����������������ʱ������ʽ��Ч��
	virtual void				      SetSideStyle(const VBF_POLYGON3DSTYLE& style)=0;
	virtual const VBF_POLYGON3DSTYLE& GetSideStyle()=0;

	// ����/��ȡ��������в���������ļ�����һ�����øú�����������SetSideStyle()������
	// ������bTexToCache -- �����Ƿ���Ҫ���뻺�棬Ĭ��Ϊfalse
	virtual void			  SetSideTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual const osg::Image* GetSideTexImage()=0;

	// ����/��ȡ�����ÿ������������ļ�����һ�����øú�����������SetSideStyle()������
	// ������nSideIndex  -- ����������ţ�������SetPointsGeo()�����еĶ���˳�򱣳�һ��
	//      strFileName -- ����ʹ�õ������ļ�
	//      nNumRows, nNumCols -- �����ڸò����ݺ᷽����ظ�����
	//      bTexToCache -- �����Ƿ���Ҫ���뻺�棬Ĭ��Ϊfalse
	virtual void SetSideTexImage(int nSideIndex, osg::Image*  pImage, int nNumRows,  int nNumCols, bool bTexToCache)=0;
	virtual bool GetSideTexImage(int nSideIndex, osg::Image*& pImage, int& nNumRows, int& nNumCols)=0;

	// ����/��ȡ����β��������͸���ȣ�ֵ��Ϊ[0.0, 1.0]��Ĭ��ֵΪ1.0��
	virtual void  SetSideTexAlpha(float fAlpha)=0;
	virtual float GetSideTexAlpha()=0;

	// ����/��ȡ�Ƿ�ʹ�ö���κ�ȣ��Լ���ȣ���λ���ף�
	virtual void SetThickness(bool bHasThickness, float fThickness)=0;
	virtual void GetThickness(bool& bHasThickness, float& fThickness)=0;

	// ����/��ȡ�Ƿ�ʹ�ü���Ч��
	virtual void EnableExtrusion(bool bEnable)=0;
	virtual bool IsExtrusionEnabled()=0;

	// ����/��ȡ�����ĳ���ʱ��
	virtual void  SetExtrusionTime(float fTime)=0;
	virtual float GetExtrusionTime()=0;

	// ����/��ȡ�к��ʱ�ײ��Ƿ�ɼ���Ĭ��ֵΪfalse��
	virtual void SetBottomVisible(bool bVisible)=0;
	virtual bool IsBottomVisible()=0;
};

#endif 
