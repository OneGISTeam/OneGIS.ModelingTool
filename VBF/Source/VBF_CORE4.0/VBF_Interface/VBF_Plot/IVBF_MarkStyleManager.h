//*******************************************************************
// FileName：IVBF_MarkStyleManager.h
// Function：军标样式管理器接口
// Author: 
// Date:     2009-7-4
//*******************************************************************

#ifndef __IVBF_MARK_STYLE_MANAGER_H__
#define __IVBF_MARK_STYLE_MANAGER_H__


#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Macros.h>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>
#include <VBF_STL.h>
#include <VBF_OS.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <string>
#include <Types/Vec4f>
#include <VBF_Common/VBF_XML/tinyxml.h>


// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_MARKSTYLEMANAGER[]		=	"Interface: MarkStyleManager";	


//------------------------------------------------------------------
// 定义结构体：VBF_MARKSTYLE
// 结构体描述：军标模型的样式信息
//------------------------------------------------------------------
typedef struct _tagVBFMarkStyle
{
	std::string			strCode;		// 样式编码
	unsigned int 		nType;          // 模型的类型（如：VBF_MARK_MESH等）
	TiXmlElement*		pElem;			// 该样式对应的xml节点

	_tagVBFMarkStyle()
	{
		strCode	= "";
		nType	= VBF_MARK_UNKNOWN;
		pElem	= NULL;
	}

	virtual ~_tagVBFMarkStyle()
	{
		SAFE_DELETE(pElem);
	}

	// 重载赋值操作符=
	_tagVBFMarkStyle& operator=(const _tagVBFMarkStyle& src)
	{
		if(this==&src) return *this;

		strCode	= src.strCode;
		nType	= src.nType;
		pElem	= (TiXmlElement*)src.pElem->Clone();

		return *this;
	}

} VBF_MARKSTYLE;



//------------------------------------------------------------------
// 定义结构体：VBF_MARKIFFSTYLE
// 结构体描述：军标模型的敌我识别样式
//------------------------------------------------------------------
typedef struct _tagVBFMarkIFFStyle
{
	std::string		strName;	// 名称，如"未指派"、"我方"，"敌方"等
	osg::Vec4f		color;		// 颜色

	_tagVBFMarkIFFStyle()
	{
		strName = "未指派";
		color	= osg::Vec4f(1.0f, 1.0f, 1.0f, 0.2f);
	}

	_tagVBFMarkIFFStyle(const std::string& strName0, const osg::Vec4f& color0)
	{
		strName	= strName0;
		color	= color0;
	}

	_tagVBFMarkIFFStyle& operator=(const _tagVBFMarkIFFStyle& src)
	{
		if(this==&src) return *this;

		strName	= src.strName;
		color	= src.color;
		return *this;
	}

	bool operator==(const _tagVBFMarkIFFStyle& src)
	{
		return (strName==src.strName && color==src.color);
	}

} VBF_MARKIFFSTYLE;



//------------------------------------------------------------------
// 定义接口：IVBF_MarkStyleManager
// 接口描述：军标模型样式的管理器
//------------------------------------------------------------------
class IVBF_MarkStyleManager : public CVBF_Referenced
{
public:
	virtual ~IVBF_MarkStyleManager() {}

    // 从xml配置文件中读取模型的样式信息（不清除以前的信息，模型数据路径以第一个配置文件为准）
    virtual bool Load(const std::string& strFileName)=0;

    // 清除所有模型的样式信息
    virtual void Clear()=0;

    // 获取所有模型文件的绝对路径
    virtual const std::string& GetModelFilePath()=0;

	// 获取所有模型的样式信息 (如果样式信息个数不为0， 返回true；否则，返回false)
	// 参数：nMarkType -- 军标的类型(定义见VBF_MARK_MESH等)，如果为VBF_MARK_UNKNOWN，返回所有类型的军标样式信息
	virtual bool GetStyles(unsigned int nMarkType, vector<VBF_MARKSTYLE*>& vStyles)=0;
	
	// 查找某类模型的样式信息
	virtual bool LookupStyle(const std::string& strCode, VBF_MARKSTYLE*& pStyle)=0;


    //================================= 模型敌我识别的样式 =================================//

    /* 获取敌我识别的个数*/
    virtual int GetIFFCount()=0;

    /* 获取第n个敌我识别的信息, 纯粹用于遍历,与顺序无关 */
    virtual bool GetIFF(int nIndex, VBF_MARKIFFSTYLE& style)=0;

    /* 添加一种敌我识别，并设置其颜色 (注意：如果该识别已存在，直接覆盖)
       参数：style -- 敌我识别的样式信息
       返回：添加成功返回true，否则返回false
    */
    virtual bool AddIFF(const VBF_MARKIFFSTYLE& style)=0;

    /* 查找一种敌我识别，并获取其颜色
       参数：strName -- 敌我识别的唯一标识，如："我方"、"敌方"、"友方"等
       返回：color   -- 该敌我识别的颜色和透明度
       返回：该敌我识别存在返回true，否则返回false
    */
    virtual bool LookupIFF(const std::string& strName, VBF_MARKIFFSTYLE& style)=0;
};


#endif 
