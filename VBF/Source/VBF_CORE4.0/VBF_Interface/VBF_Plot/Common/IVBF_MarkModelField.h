//************************************************************************
// FileName：IVBF_MarkModelField.h
// Function：军标实体模型接口：与海洋有关的各类场，如风场、洋流、温度、盐度等
// Author:   杜莹
// Date:     2018-01-16
//************************************************************************

#ifndef __IVBF_MARK_MODEL_FIELD_H__
#define __IVBF_MARK_MODEL_FIELD_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Marine/VBF_3DPlotDataTypes_Marine.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/Image>


// 定义消息ID号
const char VBF_MESSAGE_3DPLOT_MARKFIELD_SHOWINFODIALOG[]    = "Message: MarkField ShowInfoDialog";      // 消息：需要显示场模型信息，pSender=pIMark, nValue=0，pValue=osg::Vec2f*(对话框的屏幕坐标，可以为NULL)
const char VBF_MESSAGE_3DPLOT_MARKFIELD_UPDATEINFODIALOG[]  = "Message: MarkField UpdateInfoDialog";    // 消息：需要更新场模型信息，pSender=pIMark, nValue=0，pValue=NULL
const char VBF_MESSAGE_3DPLOT_MARKFIELD_CLOSEINFODIALOG[]   = "Message: MarkField CloseInfoDialog";     // 消息：需要关闭场模型信息对话框，nValue=0，pValue=pIMark


//--------------------------------------------------------------------
// 定义结构体：VBF_FIELD_TYPE
// 结构体描述：场的类型
//--------------------------------------------------------------------
enum VBF_FIELD_TYPE
{
	VBF_FIELD_WIND			= 0,  // 风场（默认值）
	VBF_FIELD_OCEANCURRENT	= 1,  // 洋流
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelField
// 接口描述：与海洋有关的各类场
//--------------------------------------------------------------------
class IVBF_MarkModelField : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelField() {}

	// 设置/获取数据的完整文件名（含路径）及场类型，如果文件不存在或不符合要求，返回false
    virtual bool SetFileName(const std::string& strFileName, VBF_FIELD_TYPE nType)=0;
    virtual const std::string& GetFileName()=0;
	virtual VBF_FIELD_TYPE     GetFieldType()=0;

	// 设置/获取场转换成的图像的尺寸，默认值为512*512
    virtual void SetImageSize(int nWidth, int nHeight)=0;
    virtual void GetImageSize(int& nWidth, int& nHeight)=0;

	// 设置/获取流速的调整系数，默认值为1.0
    virtual void  SetSpeedScale(float fScale)=0;
    virtual float GetSpeedScale()=0;

	// 获取场数据信息
	virtual int  GetNumDepth()=0;	// 获取深度总数（即层数）
	virtual bool GetGeoRange(double& dL0, double& dL1, double& dB0, double& dB1)=0;  // 获取经纬度范围

	// 设置/获取某个深度的数据是否可见
	virtual void SetDepthVisible(int nDepthIndex, bool bVisible)=0;
	virtual bool IsDepthVisible(int nDepthIndex)=0;

	// 设置/获取每个深度层的厚度（单位：米，默认值为50000）
    virtual void  SetDepthThickness(float fThickness)=0;
	virtual float GetDepthThickness()=0;
};

#endif 
