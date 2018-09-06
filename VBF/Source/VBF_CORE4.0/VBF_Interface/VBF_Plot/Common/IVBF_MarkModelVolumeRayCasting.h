//*******************************************************************
// FileName：IVBF_MarkModelVolumeRayCasting.h
// Function：体数据模型接口（光线投射法）
// Author:   杜莹
// Date:     2018-03-31
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_VOLUME_RAY_CASTING_H__
#define __IVBF_MARK_MODEL_VOLUME_RAY_CASTING_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec4ub>
#include <map>


// 定义颜色映射表（避免代码过长）
typedef std::map< float, osg::Vec4ub, less<float> >	CVBF_ColorMap;


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelVolumeRayCasting
// 接口描述：体数据模型接口（光线投射法）
//--------------------------------------------------------------------
class IVBF_MarkModelVolumeRayCasting : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelVolumeRayCasting() {}

	// 设置/获取体数据文件名
	// 说明：1）目前只支持.fld格式的体数据文件，且每个数据点的值类型为double；
	//      2）该路径下必须有一个同名且后缀为.inf的信息文件，格式为xml，注明该体数据的经纬度范围等信息
    virtual bool SetVolumeFileName(const std::string& strFileName)=0;
	virtual const std::string& GetVolumeFileName()=0;

	// 设置/获取颜色表：key=颜色关键点数值，value=对应的颜色，关键点数值从小到大
	virtual void SetColorTable(const CVBF_ColorMap& mapColorTable)=0;
	virtual const CVBF_ColorMap& GetColorTable()=0;
};


#endif 
