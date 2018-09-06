//************************************************************************
// FileName：IVBF_MarkModelRasterSetLod.h
// Function：军标实体模型接口：栅格模型的集合，支持两级网格和三级Lod（适用于绘制大量相同的动态栅格模型）
// Author:   杜莹
// Date:     2015-10-23
//************************************************************************

#ifndef __IVBF_MARK_MODEL_RASTERSET_LOD_H__
#define __IVBF_MARK_MODEL_RASTERSET_LOD_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Massive/VBF_3DPlotDataTypes_Massive.h>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <string>
#include <map>

// 定义工具ID号
const char VBF_TOOL_QUERY_MARK_RASTERSET_LOD[]      = "Tool: Query Mark of RasterSetLod";           // 模型查询：通过鼠标双击查询Lod栅格模型集合中的单个模型
const char VBF_TOOL_CURSORTIP_MARK_RASTERSET_LOD[]	= "Tool: Cursor Tip for Mark of RasterSetLod";	// 鼠标提示：鼠标接近Lod栅格模型集合中的单个模型，改变形状

// 定义消息ID号
const char VBF_MESSAGE_3DPLOT_LODRASTERSET_SELECTED[]           = "Message: LodRasterSet Selected";         // 消息：集合中的一个模型被选中了，nValue=被选模型在集合中的序号，pValue=VBF_RASTER_EXTINFO*
const char VBF_MESSAGE_3DPLOT_LODRASTERSET_SHOWINFODIALOG[]     = "Message: LodRasterSet ShowInfoDialog";   // 消息：需要显示被选模型的信息对话框，nValue=被选模型在集合中的序号，pValue=osg::Vec2f*
const char VBF_MESSAGE_3DPLOT_LODRASTERSET_CLOSEINFODIALOG[]    = "Message: LodRasterSet CloseInfoDialog";  // 消息：需要关闭信息对话框


typedef std::map<std::string, std::string>   CVBF_UserValueMap;

//-------------------------------------------------------------------------------
// 定义结构体：VBF_RASTER_EXTINFO
// 结构体描述：模型的扩展信息，需要向外部模块请求（避免在系统内部存储，占用内存）
//-------------------------------------------------------------------------------
typedef struct _tagVBFRasterExtInfo
{
public:
	std::vector<osg::Vec3d>		vTrailPointsGeo;	// 模型的运动轨迹（需要外部模块赋值）
	CVBF_UserValueMap			mapUserValues;		// 模型的自定义参数对（需要外部模块赋值）

	// 拷贝构造函数
	_tagVBFRasterExtInfo& operator=(const _tagVBFRasterExtInfo& src)
	{
		if(this==&src) return *this;

		vTrailPointsGeo.clear();
		mapUserValues.clear();

		if(!src.vTrailPointsGeo.empty()) vTrailPointsGeo = src.vTrailPointsGeo;
		if(!src.mapUserValues.empty())   mapUserValues   = src.mapUserValues;
		return *this;
	}

	// 清空数据
	void Clear()
	{
		vTrailPointsGeo.clear();
		mapUserValues.clear();
	}

} VBF_RASTER_EXTINFO;


//-------------------------------------------------------------------------------
// 定义结构体：VBF_MESH_INFO
// 结构体描述：Lod=2时使用的三维模型的信息（如3ds、flt、ive等）
//-------------------------------------------------------------------------------
typedef struct _tagVBFMeshInfo
{
public:
    bool            bFlipDDS;           // 是否需要翻转模型中的dds纹理
    bool            bTransparent;       // 模型中的纹理是否透明
    float           fScale;             // 模型的缩放系数
    float           fRotateZInit;       // 模型主体正向（如车头、船头、机头）需要绕Z轴旋转的初始角度（逆时针为正，单位：角度）
    std::string     strMeshFileName;    // 模型文件名（含路径）

    _tagVBFMeshInfo()
    {
        bFlipDDS        = false;
        bTransparent    = false;
        fScale          = 1.0f;
        fRotateZInit    = 0.0f;
        strMeshFileName = "";
    }

    _tagVBFMeshInfo& operator=(const _tagVBFMeshInfo& src)
    {
        if(this==&src) return *this;

        bFlipDDS        = src.bFlipDDS;
        bTransparent    = src.bTransparent;
        fScale          = src.fScale;
        fRotateZInit    = src.fRotateZInit;
        strMeshFileName = src.strMeshFileName;

        return *this;
    }

} VBF_MESH_INFO;


//-------------------------------------------------------------------------------
// 定义结构体：VBF_LOD_INFO
// 结构体描述：Lod=0,1时，单个Lod级别中所有栅格模型的通用信息
//-------------------------------------------------------------------------------
typedef struct _tagVBFLodInfo
{
public:

	// 该级Lod中所有模型的可见距离
    float               fDistMax;		// 最大可见距离（单位：米）
    float               fDistMin;		// 最小可见距离（单位：米）

    // 高程的拔高值，解决z-buffer问题
    double              dHeightAdjust;

    // Lod=0,1时的图像信息
    float               fWidth;			// 单个模型的宽度（单位：像素），所有模型均固定像素大小
    float               fHeight;		// 单个模型的高度（单位：像素）
    ref_ptr<osg::Image>	ipImage;        // 纹理图像
    float               fTexAlpha;		// 纹理透明度
    float               fTexOrignX;		// 纹理原点在位图中的相对位置 (相对于左下角)
    float               fTexOrignY;

    // Lod=2时的模型信息
    VBF_MESH_INFO       meshInfo;       // 模型信息

	_tagVBFLodInfo()
	{
		fDistMax		= FLT_MAX;
		fDistMin		= 0;
        dHeightAdjust	= 0.0;
		fWidth			= 35;
		fHeight			= 35;
		fTexAlpha		= 1.0f;
		fTexOrignX		= 0.5f;
        fTexOrignY		= 0.5f;
	}

	_tagVBFLodInfo& operator=(const _tagVBFLodInfo& src)
	{
		if(this==&src) return *this;

		fDistMax		= src.fDistMax;
		fDistMin		= src.fDistMin;
        dHeightAdjust	= src.dHeightAdjust;
		fWidth			= src.fWidth;
		fHeight			= src.fHeight;
		ipImage			= src.ipImage;
		fTexAlpha		= src.fTexAlpha;
		fTexOrignX		= src.fTexOrignX;
        fTexOrignY		= src.fTexOrignY;
        meshInfo        = src.meshInfo;

		return *this;
	}

} VBF_LOD_INFO;


// 定义映射表
typedef std::map<int, ref_ptr<osg::Image> >  CVBF_RasterImageMap;
typedef std::map<int, VBF_MESH_INFO>         CVBF_RasterMeshMap;


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelRasterSetLod
// 接口描述：栅格模型的集合，支持三级Lod，该集合中所有模型使用相同的纹理
//--------------------------------------------------------------------
class IVBF_MarkModelRasterSetLod : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelRasterSetLod() {}


	// 初始化模型可能达到的最大数量（默认值为200000，注意：该函数只能调用一次，而且必须在添加单个模型之前调用)
	virtual void InitCapacity(int nNumRasters)=0;


	// 注意：视点很远时，只绘制模型所在的网格及其标签（显示该网格内的模型个数），不绘制模型


	// 初始化网格信息（注意：初始化函数只能调用一次，而且必须在添加单个模型之前调用)
	// 参数：colorCell -- 网格的颜色
	//      dCellHeight -- 网格的高程值（避免z-buffer争夺问题）
	virtual void InitCellInfo(const osg::Vec4f& color, double dCellHeight=1e4)=0;
	virtual void GetCellInfo(osg::Vec4f& color, double& dCellHeight)=0;


	// 初始化网格标签信息（注意：初始化函数只能调用一次，而且必须在添加单个模型之前调用)
	// 参数：nCellLod -- 网格的Lod，只能为0和1
	//      style    -- 网格标签的文本样式
	//      fDistMax -- 网格标签开始出现的视点距离
	virtual void InitCellLabelInfo(int nCellLod, const VBF_TEXTSTYLE& style, float fDistMax)=0;
	virtual void GetCellLabelInfo(int nCellLod, VBF_TEXTSTYLE& style, float& fDistMax)=0;


	// 初始化某个Lod级别的模型信息（注意：初始化函数只能调用一次，而且必须在添加单个模型之前调用)
    // 参数：nLod -- Lod级别，只能为0,1,2
	virtual void InitLodInfo(int nLod, const VBF_LOD_INFO& info)=0;
    virtual void GetLodInfo(int nLod, VBF_LOD_INFO& info)=0;


	// 初始化被选模型轨迹线样式（注意：初始化函数只能调用一次，而且必须在添加单个模型之前调用)
	virtual void                 InitTrailStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetTrailStyle()=0;

    // 初始化/获取是否显示所有模型的高度线（仅适用于Lod=1,2的模型，注意：初始化函数只能调用一次，如果大量显示高度线会影响绘制效率）
    virtual void InitHintLineVisible(bool bVisible)=0;
    virtual bool IsHintLineVisible()=0;

    // 初始化/获取所有模型的高度线样式（仅适用于Lod=1,2的模型，注意：初始化函数只能调用一次）
    virtual void InitHintLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetHintLineStyle()=0;

	// 设置/获取模型的扩展信息是否由系统内部存储，默认为false（注意：该函数只能调用一次，而且必须在添加单个模型之前调用)
	// 参数：bSave -- 是否需要将模型的扩展信息保存在系统内部（如果为true，会占用大量内存；如果为false，需要通过外部模块提供扩展信息）
	virtual void SetExtInfoSaved(bool bSave)=0;
	virtual bool IsExtInfoSaved()=0;

    // 初始化/获取Lod=1时的图像映射表（注意：该函数只能调用一次，而且必须在添加单个模型之前调用)
	// 注意：如果调用了该函数，将忽略InitLodInfo()函数中当Lod=1时的模型图像；否则，所有模型均使用InitLodInfo()函数设置的图像
	virtual void InitRasterImageMap(const CVBF_RasterImageMap& mapImages)=0;
	virtual const CVBF_RasterImageMap& GetRasterImageMap()=0;

    // 初始化/获取Lod=2时的三维模型映射表（注意：该函数只能调用一次，而且必须在添加单个模型之前调用)
    // 注意：如果调用了该函数，将忽略InitLodInfo()函数中当Lod=2时的模型；否则，所有模型均使用InitLodInfo()函数设置的模型
    virtual void InitRasterMeshMap(const CVBF_RasterMeshMap& mapMeshes)=0;
    virtual const CVBF_RasterMeshMap& GetRasterMeshMap()=0;

    // 设置/获取Lod=2时三维模型可见的最小垂直视角（即：模型和视点连线与地形线形成的夹角，单位：角度，默认值为10度）
    // 用户可根据计算机性能调整该参数，性能越高，该参数越小
    virtual void  SetMeshVisibleAngleV(float fAngleV)=0;
    virtual float GetMeshVisibleAngleV()=0;

	// 添加一个模型，并返回该模型在集合中的序号（从0开始）
	// 参数：nType，该模型的类型，系统将根据该类型从SetRasterImageMap()函数中获取对应的图像
	virtual int AddRaster(int nType)=0;

	// 删除一个模型
	virtual void DeleteRaster(int nIndex)=0;

    // 设置/获取某个模型是否可见，前提是该模型已经添加
    virtual void SetRasterVisible(int nIndex, bool bVisible)=0;
    virtual bool IsRasterVisible(int nIndex)=0;

    // 获取集合中模型个数（包含已经被删除了的模型）
    virtual int GetNumRastersIncludingDeleted()=0;

    // 获取集合中模型个数（不含已经被删除了的模型）
    virtual int GetNumRastersExcludingDeleted()=0;

	// 设置/获取某个模型的地理坐标，前提是该模型已经添加
	// 参数：nIndex -- 模型的序号
	virtual void              SetRasterGeoPos(int nIndex, const osg::Vec3d& vGeo)=0;
	virtual const osg::Vec3d& GetRasterGeoPos(int nIndex)=0;

	// 设置/获取某个模型的航向角（即绕Z轴的旋转角），前提是该模型已经添加
	// 参数：nIndex -- 模型的序号
	virtual void  SetRasterRotateZ(int nIndex, float fRotateZ)=0;
	virtual float GetRasterRotateZ(int nIndex)=0;

	// 同时设置模型的地理坐标和航向角（即绕Z轴的旋转角），前提是该模型已经添加
	// 参数：nIndex -- 模型的序号
	//      bSave  -- 是否需要将该点保存在运动轨迹中（如果为true，会占用一定量的内存；如果为false，需要通过外部模块提供运动轨迹数据）
	virtual void SetRasterGeoPos(int nIndex, const osg::Vec3d& vGeo, float fRotateZ)=0;


	// 添加/移除/获取用户自定义的参数对，用于显示被选模型的信息，前提是该模型已经添加
	// 如果没有显式调用SetExtInfoSaved(true)，如下函数将被忽略
	// bOverwrite -- 如果该参数对的名字已经存在，是否覆盖原有值
	virtual void AddUserValue(int nIndex, const std::string& strName, const std::string& strValue, bool bOverwrite=true)=0;
	virtual void RemoveUseValue(int nIndex, const std::string& strName)=0;
	virtual bool GetUserValue(int nIndex, const std::string& strName, std::string& strValue)=0;
	virtual void SetUserValues(int nIndex, const CVBF_UserValueMap& values)=0;
	virtual bool GetUserValues(int nIndex, CVBF_UserValueMap& values)=0;

	// 获取实时信息
	virtual bool IsCellVisible()=0;		// 目前网格是否可见（网格与模型不能同时可见）
	virtual bool IsRasterVisible()=0;	// 目前模型是否可见
	virtual int  GetCellLod()=0;		// 如果网格可见，获取其目前的Lod（只能为0, 1）
    virtual int  GetRasterLod()=0;		// 如果模型可见，获取其目前的Lod（只能为0, 1, 2）

	// 获取当前被选模型的扩展信息
    virtual const VBF_RASTER_EXTINFO& GetSelRasterExtInfo()=0;

    // 响应用户界面中的消息
    virtual void OnInfoDialogClosed()=0;  // 响应模型信息对话框关闭消息

    // 目前集合中是否有被选中的模型
    virtual bool HasSelected()=0;

    // 获取集合中当前被选中的模型的序号
    virtual int GetSelectedIndex()=0;
};


#endif 
