//***************************************************************************************
// FileName：VBF_3DDataSetTypes.h
// Function：数据集配置需要使用的公共数据类型
// Author:   杜莹
// Date:     2011-09-20
//***************************************************************************************

#ifndef __VBF_3DDATASET_TYPES_H__
#define __VBF_3DDATASET_TYPES_H__


//--------------------------------------------------------------------------
// 定义结构体：VBF_3DDATAPROVIDER
// 结构体描述：3D数据集提供者
//--------------------------------------------------------------------------
typedef struct _tagVBF3DDataProvider
{	
	char	szID[64];			// 数据提供者的ID号 (全局唯一，区分大小写)
	char	szDll[64];			// 动态库名字 (不含路径，含.dll后缀)		
	char	szDesc[256];		// 描述信息	

	_tagVBF3DDataProvider()
	{
		szID[0]		= '\0';
		szDll[0]	= '\0';
		szDesc[0]	= '\0';
	}

	_tagVBF3DDataProvider& operator=(_tagVBF3DDataProvider& src)
	{
		strcpy(szID,   src.szID);
		strcpy(szDll,  src.szDll);
		strcpy(szDesc, src.szDesc);

		return *this;
	}

} VBF_3DDATAPROVIDER;


//--------------------------------------------------------------------------
// 定义结构体：VBF_3DDATASET
// 结构体描述：3D数据集，记录数据的元信息和展示方案
//--------------------------------------------------------------------------
typedef struct _tagVBF3DDataSet
{	
	char	szProviderID[64];	// 数据提供者的ID号
	char	szURL[256];			// 数据位置	
	bool	bVisible;			// 是否可见

	_tagVBF3DDataSet()
	{
		szProviderID[0]	= '\0';
		szURL[0]		= '\0';
		bVisible		= true;
	}

	_tagVBF3DDataSet& operator=(const _tagVBF3DDataSet& src)
	{
		Copy(src);
		return *this;
	}

	bool operator==(const _tagVBF3DDataSet& src)
	{
		return ( strcmp(szProviderID, src.szProviderID)==0 && stricmp(szURL, src.szURL)==0);
	}

protected:

	virtual void Copy(const _tagVBF3DDataSet& src)
	{
		strcpy(szProviderID, src.szProviderID);
		strcpy(szURL,        src.szURL);

		bVisible = src.bVisible;
	}

} VBF_3DDATASET;


//--------------------------------------------------------------------------
// 定义结构体：VBF_3DDATASETTEX
// 结构体描述：纹理数据集
//--------------------------------------------------------------------------
typedef struct _tagVBF3DDataSetTex : public VBF_3DDATASET
{	
	int		nLayerIndex;		// 图层序号，0表示最底层，-1表示不启用
	int		nLodMin;			// 可见的最小Lod，不能小于数据物理存储的最小Lod
	int		nLodMax;			// 可见的最大Lod，不能大于数据物理存储的最大Lod
	float	fTransparency;		// 透明度

	_tagVBF3DDataSetTex() : VBF_3DDATASET()
	{
		nLayerIndex		= 0;
		nLodMin			= 0;
		nLodMax			= 30;
		fTransparency	= 1.0f;
	}

	_tagVBF3DDataSetTex& operator=(const _tagVBF3DDataSetTex& src) 
	{
		Copy( (VBF_3DDATASET&)src );

		nLayerIndex		= src.nLayerIndex;		
		nLodMin			= src.nLodMin;			
		nLodMax			= src.nLodMax;	
		fTransparency	= src.fTransparency;

		return *this;
	}

} VBF_3DDATASETTEX;


//--------------------------------------------------------------------------
// 定义结构体：VBF_3DDATASETDEM
// 结构体描述：Dem数据集
//--------------------------------------------------------------------------
typedef struct _tagVBF3DDataSetDem : public VBF_3DDATASET
{	
	int		nPriority;			// 优先级，0表示优先级最低

	_tagVBF3DDataSetDem() : VBF_3DDATASET()
	{
		nPriority	= 0;
	}

	_tagVBF3DDataSetDem& operator=(const _tagVBF3DDataSetDem& src)
	{
		Copy( (VBF_3DDATASET&)src );

		nPriority = src.nPriority;
		return *this;
	}

} VBF_3DDATASETDEM;


//--------------------------------------------------------------------------
// 定义结构体：VBF_3DDATASETNOTE
// 结构体描述：Dem数据集
//--------------------------------------------------------------------------
typedef struct _tagVBF3DDataSetNote : public VBF_3DDATASET
{	
	int		nPriority;			// 优先级，0表示优先级最低

	_tagVBF3DDataSetNote() : VBF_3DDATASET()
	{
		nPriority	= 0;
	}

	_tagVBF3DDataSetNote& operator=(const _tagVBF3DDataSetNote& src)
	{
		Copy( (VBF_3DDATASET&)src );

		nPriority = src.nPriority;
		return *this;
	}

} VBF_3DDATASETNOTE;



#endif

