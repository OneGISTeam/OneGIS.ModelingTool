//************************************************************************
// FileName：IVBF_MarkModelRasterSet.h
// Function：军标实体模型接口：栅格模型的集合（适用于绘制大量相同的栅格模型）
//           该集合中所有模型纹理相同，尺寸相同，旋转方式相同
// Author:   杜莹
// Date:     2015-10-23
//************************************************************************

#ifndef __IVBF_MARK_MODEL_RASTERSET_H__
#define __IVBF_MARK_MODEL_RASTERSET_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Massive/VBF_3DPlotDataTypes_Massive.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <string>



// 定义消息ID号
const char VBF_MESSAGE_3DPLOT_RASTERSET_SHOWINFODIALOG[]    = "Message: RasterSet ShowInfoDialog";   // 消息：需要显示集合中被选模型的信息对话框
const char VBF_MESSAGE_3DPLOT_RASTERSET_CLOSEINFODIALOG[]   = "Message: RasterSet CloseInfoDialog";  // 消息：需要关闭信息对话框


typedef std::map<std::string, std::string>  CVBF_UserValueMap;


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelRasterSet
// 接口描述：栅格模型的集合，该集合中所有模型使用相同的纹理
//--------------------------------------------------------------------
class IVBF_MarkModelRasterSet : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelRasterSet() {}


	// 初始化集合的尺寸信息，只能调用一次，而且必须在添加单个模型之前调用
	// 参数：bFixedSizeInPixels -- 是否固定像素大小，如果为true，宽度和高度参数的单位为像素
	//       fWidth, hfHeight  -- 单个模型的宽度和高度（单位：像素/米）
	virtual void  InitSize(bool bFixedSizeInPixels, float fWidth, float fHeight)=0;
	virtual bool  IsFixedSizeInPixels()=0;
	virtual float GetWidth()=0;
	virtual float GetHeight()=0;


	// 初始化集合的纹理信息，只能调用一次，而且必须在添加单个模型之前调用
	// 参数：pTexImage -- 集合中所有模型公用的纹理图像指针
	//      fTexAlpha  -- 集合中所有模型的纹理透明度（默认值为1.0）
	//      fTexOrignX, fTexOrignY-- 纹理原点在位图中的相对位置 (相对于左下角，值域为[0.0, 1.0]，默认值分别为0.5, 0.5)
	virtual void InitTexture(osg::Image* pTexImage, float fTexAlpha=1.0f, float fTexOrignX=0.5f, float fTexOrignY=0.5f)=0;
	virtual osg::Image* GetImage()=0;
	virtual float GetTexAlpha()	=0;
	virtual float GetTexOrignX()=0;
	virtual float GetTexOrignY()=0;


	// 初始化空间分割后每个单元格中存储的最大模型个数（默认值为100）
	// 如果分割数<=5，表示Raster模型总数较少，精确裁剪优先，绘制效率次之；否则，绘制效率优先，精确裁剪次之
	virtual void         InitNumMaxRastersPerCell(unsigned int num)=0;
	virtual unsigned int GetNumMaxRastersPerCell()=0;

	// 获取集合中栅格模型个数
	virtual int GetNumRasters()=0;

	// 获取某个模型的地理坐标
	virtual const osg::Vec3d& GetRasterGeoPos(int nIndex)=0;


	// 添加/移除/获取用户自定义的简略参数对，用于显示被选模型的简略信息，前提是该模型已经添加
	virtual void AddUserValue(int nIndex, const std::string& strName, const std::string& strValue, bool bOverwrite=true)=0;
	virtual void RemoveUseValue(int nIndex, const std::string& strName)=0;
	virtual bool GetUserValue(int nIndex, const std::string& strName, std::string& strValue)=0;
	virtual void SetUserValues(int nIndex, const CVBF_UserValueMap& values)=0;
	virtual bool GetUserValues(int nIndex, CVBF_UserValueMap& values)=0;

	// 添加/移除/获取用户自定义的详细参数对，用于显示被选模型的详细信息，前提是该模型已经添加
	virtual void AddUserValueDetail(int nIndex, const std::string& strName, const std::string& strValue, bool bOverwrite=true)=0;
	virtual void RemoveUseValueDetail(int nIndex, const std::string& strName)=0;
	virtual bool GetUserValueDetail(int nIndex, const std::string& strName, std::string& strValue)=0;
	virtual void SetUserValuesDetail(int nIndex, const CVBF_UserValueMap& values)=0;
	virtual bool GetUserValuesDetail(int nIndex, CVBF_UserValueMap& values)=0;

    // 响应用户界面中的消息
    virtual void OnInfoDialogClosed()=0;  // 响应模型信息对话框关闭消息

    // 目前集合中是否有被选中的模型
    virtual bool HasSelected()=0;

    // 获取集合中当前被选中的模型的序号
    virtual int GetSelectedIndex()=0;
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelRasterSetBoardH
// 接口描述：栅格模型的集合：集合中的每个模型在水平方向使用布告牌
//--------------------------------------------------------------------
class IVBF_MarkModelRasterSetBoardH : public IVBF_MarkModelRasterSet
{
public:
	virtual ~IVBF_MarkModelRasterSetBoardH() {}

	// 添加一个栅格模型
	// 参数：vGeo -- 模型的地理坐标
	virtual int AddRaster(const osg::Vec3d& vGeo)=0;
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelRasterSetBoardV
// 接口描述：栅格模型的集合：集合中的每个模型在垂直方向使用布告牌
//--------------------------------------------------------------------
class IVBF_MarkModelRasterSetBoardV : public IVBF_MarkModelRasterSet
{
public:
	virtual ~IVBF_MarkModelRasterSetBoardV() {}

	// 添加一个栅格模型
	// 参数：vGeo -- 模型的地理坐标
	virtual int AddRaster(const osg::Vec3d& vGeo)=0;
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelRasterSetBoardHV
// 接口描述：栅格模型的集合：集合中的每个模型在同时水平和垂直方向使用布告牌
//--------------------------------------------------------------------
class IVBF_MarkModelRasterSetBoardHV : public IVBF_MarkModelRasterSet
{
public:
	virtual ~IVBF_MarkModelRasterSetBoardHV() {}

	// 添加一个栅格模型，并返回该模型在集合中的序号
	// 参数：vGeo -- 模型的地理坐标
	virtual int AddRaster(const osg::Vec3d& vGeo)=0;
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelRasterSetHorizon
// 接口描述：栅格模型的集合：集合中的每个模型始终平行于地面，与视点无关，只允许绕Z轴旋转
//--------------------------------------------------------------------
class IVBF_MarkModelRasterSetHorizon : public IVBF_MarkModelRasterSet
{
public:
	virtual ~IVBF_MarkModelRasterSetHorizon() {}

	// 添加一个栅格模型
	// 参数：vGeo -- 模型的地理坐标
	//      fAngleZ -- 模型绕Z轴的旋转角（单位：角度）
	virtual int AddRaster(const osg::Vec3d& vGeo, float fAngleZ=0.0f)=0;
};


#endif 
