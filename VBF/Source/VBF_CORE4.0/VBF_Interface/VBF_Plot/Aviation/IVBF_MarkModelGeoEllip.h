//*******************************************************************
// FileName：IVBF_MarkModelGeoEllip.h
// Function：实体模型：地理椭球，即与地心一致的椭球体
// Author:   杜莹
// Date:     2015-08-11
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_GEOELLIP_H__
#define __IVBF_MARK_MODEL_GEOELLIP_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Aviation/VBF_3DPlotDataTypes_Aviation.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <string>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelGeoEllip
// 接口描述：地理椭球，即与地心一致的球体，使用地理坐标中的经度和纬度
//--------------------------------------------------------------------
class IVBF_MarkModelGeoEllip : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelGeoEllip() {}

	// 设置/获取球体的经纬度范围，默认值分别为[-180, 180]和[-90, 90]
	virtual void SetTess(double dL0, double dL1, double dB0, double dB1)=0;
	virtual void GetTess(double& dL0, double& dL1, double& dB0, double& dB1)=0;

    // 设置/获取椭球体的长短半轴（默认值分别为当前地球椭球的长短半轴，单位：米）
    virtual void SetRadius(double dRadiusEquator, double dRadiusPolar)=0;
    virtual void GetRadius(double& dRadiusEquator, double& dRadiusPolar)=0;

	// 设置/获取球面分别在纵横方向（即经度和纬度方向）的分割数
	virtual void SetNumSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSplit(int& nNumSplitRow, int& nNumSplitCol)=0;

	// 设置/获取纹理图像指针
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

	// 设置/获取纹理的透明度（值域为[0.0, 1.0]，默认值为0.6）
	virtual void  SetTexAlpha(float fAlpha)=0;
	virtual float GetTexAlpha()=0;
};


#endif 
