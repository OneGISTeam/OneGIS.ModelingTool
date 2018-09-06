//************************************************************************
// FileName：IVBF_MarkModelPointSprite.h
// Function：军标实体模型接口：点精灵（适用于绘制大量相同的点）
//           该集合中所有点的纹理相同，尺寸相同，且始终朝向视点
// Author:   杜莹
// Date:     2015-11-23
//************************************************************************

#ifndef __IVBF_MARK_MODEL_POINTSPRITE_H__
#define __IVBF_MARK_MODEL_POINTSPRITE_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Massive/VBF_3DPlotDataTypes_Massive.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/Image>


typedef std::map<std::string, std::string>  CVBF_UserValueMap;


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelPointSprite
// 接口描述：点精灵
//--------------------------------------------------------------------
class IVBF_MarkModelPointSprite : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelPointSprite() {}

	// 初始化集合中所有点的尺寸信息，只能调用一次，而且必须在添加单个模型之前调用
	//       fSizeInPixels  -- 单个点的尺寸（单位：像素）
	virtual void InitSize(float fSizeInPixels)=0;

	// 初始化集合的纹理信息，只能调用一次，而且必须在添加单个模型之前调用
	// 参数：pTexImage -- 集合中所有模型公用的纹理图像指针
	//      fTexAlpha  -- 集合中所有模型的纹理透明度（默认值为1.0）
	virtual void InitTexture(osg::Image* pTexImage, float fTexAlpha=1.0f)=0;


	// 初始化空间分割后每个单元格中存储的最大点数（默认值为100）
	// 如果分割数<=5，表示点总数较少，精确裁剪优先，绘制效率次之；否则，绘制效率优先，精确裁剪次之
	virtual void InitNumMaxPointsPerCell(unsigned int num)=0;

	// 添加一个点，并返回该点在集合中的序号，参数vGeo表示点的地理坐标
	virtual int AddPoint(const osg::Vec3d& vGeo)=0;

	// 获取集合中点的个数
	virtual int GetNumPoints()=0;

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
};



#endif 
