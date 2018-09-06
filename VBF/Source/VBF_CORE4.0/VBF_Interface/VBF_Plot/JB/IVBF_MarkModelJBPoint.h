//*******************************************************************
// FileName：IVBF_MarkModelJBPoint.h
// Function：实体模型：点状军标
// Author:   杜莹
// Date:     2014-05-14
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_JB_POINT_H__
#define __IVBF_MARK_MODEL_JB_POINT_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/JB/VBF_3DPlotDataTypes_JB.h>
#include <Types/VBF_3DStyles.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelJBPoint
// 接口描述：点状军标
//--------------------------------------------------------------------
class IVBF_MarkModelJBPoint : public IVBF_MarkModelPoint
{
public:
	virtual ~IVBF_MarkModelJBPoint() {}

	// 根据指定的军标库文件和模型在军标库中的编号，创建点状军标，如果文件或编号不存在，返回false
	// 说明：该函数必须最先调用
	virtual bool Create(const std::string& strJBFileName, unsigned int nSymbolID)=0;

	// 获取该军标所在的军标库文件名（完整路径），实际上返回值来自于Create()函数的第一个参数
	virtual std::string GetJBFileName()=0;

	// 获取符号在军标库中的编号/名称，实际上返回值来自于Create()函数的第二个参数
	virtual int         GetSymbolID()=0;
	virtual std::string GetSymbolName()=0;

	// 获取符号在军标库中的类别编号/类别名称
	virtual int         GetSymbolClassID()=0;
    virtual std::string GetSymbolClassName()=0;
	
	// 设置/获取符号中某个部分的文本内容
	virtual void               SetText(int nTextIndex, const std::string& strText)=0;
	virtual const std::string& GetText(int nTextIndex)=0;

	// 设置/获取符号中某个部分的文本样式
	virtual void                 SetTextStyle(int nTextIndex, const VBF_TEXTSTYLE& style)=0;
	virtual const VBF_TEXTSTYLE& GetTextStyle(int nTextIndex)=0;

	// 设置/获取符号的宽度（默认值为3.0）
	virtual void  SetWidth(float fWidth)=0;
	virtual float GetWidth()=0;

	// 设置/获取符号的厚度
	virtual void  SetThickness(float fThickness)=0;
	virtual float GetThickness()=0;

	// 设置/获取符号的轮廓色
	virtual void       SetFrameColor(const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetFrameColor()=0;

	// 设置/获取符号的内衬线色
	virtual void       SetSerifColorInner(const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetSerifColorInner()=0;

	// 设置/获取符号的外衬线色
	virtual void       SetSerifColorOuter(const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetSerifColorOuter()=0;

	// 设置/获取符号的填充色
	virtual void       SetFillColor(int nRgnIndex, const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetFillColor(int nRgnIndex)=0;

	// 设置/获取填充部分相对于轮廓正面的凹陷比例（值域为[0.0, 1.0]，默认值为0.2）
	virtual void  SetFillOffsetScale(float fScale)=0;
	virtual float GetFillOffsetScale()=0;

	// 设置/获取文本部分相对于轮廓正面的凸出比例（值域为[0.0, 1.0]，默认值为0.1）
	virtual void  SetTextOffsetScale(float fScale)=0;
	virtual float GetTextOffsetScale()=0;
};


#endif 
