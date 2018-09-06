//************************************************************************
// FileName��IVBF_MarkModelRasterSetLod.h
// Function������ʵ��ģ�ͽӿڣ�դ��ģ�͵ļ��ϣ�֧���������������Lod�������ڻ��ƴ�����ͬ�Ķ�̬դ��ģ�ͣ�
// Author:   ��Ө
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

// ���幤��ID��
const char VBF_TOOL_QUERY_MARK_RASTERSET_LOD[]      = "Tool: Query Mark of RasterSetLod";           // ģ�Ͳ�ѯ��ͨ�����˫����ѯLodդ��ģ�ͼ����еĵ���ģ��
const char VBF_TOOL_CURSORTIP_MARK_RASTERSET_LOD[]	= "Tool: Cursor Tip for Mark of RasterSetLod";	// �����ʾ�����ӽ�Lodդ��ģ�ͼ����еĵ���ģ�ͣ��ı���״

// ������ϢID��
const char VBF_MESSAGE_3DPLOT_LODRASTERSET_SELECTED[]           = "Message: LodRasterSet Selected";         // ��Ϣ�������е�һ��ģ�ͱ�ѡ���ˣ�nValue=��ѡģ���ڼ����е���ţ�pValue=VBF_RASTER_EXTINFO*
const char VBF_MESSAGE_3DPLOT_LODRASTERSET_SHOWINFODIALOG[]     = "Message: LodRasterSet ShowInfoDialog";   // ��Ϣ����Ҫ��ʾ��ѡģ�͵���Ϣ�Ի���nValue=��ѡģ���ڼ����е���ţ�pValue=osg::Vec2f*
const char VBF_MESSAGE_3DPLOT_LODRASTERSET_CLOSEINFODIALOG[]    = "Message: LodRasterSet CloseInfoDialog";  // ��Ϣ����Ҫ�ر���Ϣ�Ի���


typedef std::map<std::string, std::string>   CVBF_UserValueMap;

//-------------------------------------------------------------------------------
// ����ṹ�壺VBF_RASTER_EXTINFO
// �ṹ��������ģ�͵���չ��Ϣ����Ҫ���ⲿģ�����󣨱�����ϵͳ�ڲ��洢��ռ���ڴ棩
//-------------------------------------------------------------------------------
typedef struct _tagVBFRasterExtInfo
{
public:
	std::vector<osg::Vec3d>		vTrailPointsGeo;	// ģ�͵��˶��켣����Ҫ�ⲿģ�鸳ֵ��
	CVBF_UserValueMap			mapUserValues;		// ģ�͵��Զ�������ԣ���Ҫ�ⲿģ�鸳ֵ��

	// �������캯��
	_tagVBFRasterExtInfo& operator=(const _tagVBFRasterExtInfo& src)
	{
		if(this==&src) return *this;

		vTrailPointsGeo.clear();
		mapUserValues.clear();

		if(!src.vTrailPointsGeo.empty()) vTrailPointsGeo = src.vTrailPointsGeo;
		if(!src.mapUserValues.empty())   mapUserValues   = src.mapUserValues;
		return *this;
	}

	// �������
	void Clear()
	{
		vTrailPointsGeo.clear();
		mapUserValues.clear();
	}

} VBF_RASTER_EXTINFO;


//-------------------------------------------------------------------------------
// ����ṹ�壺VBF_MESH_INFO
// �ṹ��������Lod=2ʱʹ�õ���άģ�͵���Ϣ����3ds��flt��ive�ȣ�
//-------------------------------------------------------------------------------
typedef struct _tagVBFMeshInfo
{
public:
    bool            bFlipDDS;           // �Ƿ���Ҫ��תģ���е�dds����
    bool            bTransparent;       // ģ���е������Ƿ�͸��
    float           fScale;             // ģ�͵�����ϵ��
    float           fRotateZInit;       // ģ�����������糵ͷ����ͷ����ͷ����Ҫ��Z����ת�ĳ�ʼ�Ƕȣ���ʱ��Ϊ������λ���Ƕȣ�
    std::string     strMeshFileName;    // ģ���ļ�������·����

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
// ����ṹ�壺VBF_LOD_INFO
// �ṹ��������Lod=0,1ʱ������Lod����������դ��ģ�͵�ͨ����Ϣ
//-------------------------------------------------------------------------------
typedef struct _tagVBFLodInfo
{
public:

	// �ü�Lod������ģ�͵Ŀɼ�����
    float               fDistMax;		// ���ɼ����루��λ���ף�
    float               fDistMin;		// ��С�ɼ����루��λ���ף�

    // �̵߳İθ�ֵ�����z-buffer����
    double              dHeightAdjust;

    // Lod=0,1ʱ��ͼ����Ϣ
    float               fWidth;			// ����ģ�͵Ŀ�ȣ���λ�����أ�������ģ�;��̶����ش�С
    float               fHeight;		// ����ģ�͵ĸ߶ȣ���λ�����أ�
    ref_ptr<osg::Image>	ipImage;        // ����ͼ��
    float               fTexAlpha;		// ����͸����
    float               fTexOrignX;		// ����ԭ����λͼ�е����λ�� (��������½�)
    float               fTexOrignY;

    // Lod=2ʱ��ģ����Ϣ
    VBF_MESH_INFO       meshInfo;       // ģ����Ϣ

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


// ����ӳ���
typedef std::map<int, ref_ptr<osg::Image> >  CVBF_RasterImageMap;
typedef std::map<int, VBF_MESH_INFO>         CVBF_RasterMeshMap;


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelRasterSetLod
// �ӿ�������դ��ģ�͵ļ��ϣ�֧������Lod���ü���������ģ��ʹ����ͬ������
//--------------------------------------------------------------------
class IVBF_MarkModelRasterSetLod : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelRasterSetLod() {}


	// ��ʼ��ģ�Ϳ��ܴﵽ�����������Ĭ��ֵΪ200000��ע�⣺�ú���ֻ�ܵ���һ�Σ����ұ�������ӵ���ģ��֮ǰ����)
	virtual void InitCapacity(int nNumRasters)=0;


	// ע�⣺�ӵ��Զʱ��ֻ����ģ�����ڵ��������ǩ����ʾ�������ڵ�ģ�͸�������������ģ��


	// ��ʼ��������Ϣ��ע�⣺��ʼ������ֻ�ܵ���һ�Σ����ұ�������ӵ���ģ��֮ǰ����)
	// ������colorCell -- �������ɫ
	//      dCellHeight -- ����ĸ߳�ֵ������z-buffer�������⣩
	virtual void InitCellInfo(const osg::Vec4f& color, double dCellHeight=1e4)=0;
	virtual void GetCellInfo(osg::Vec4f& color, double& dCellHeight)=0;


	// ��ʼ�������ǩ��Ϣ��ע�⣺��ʼ������ֻ�ܵ���һ�Σ����ұ�������ӵ���ģ��֮ǰ����)
	// ������nCellLod -- �����Lod��ֻ��Ϊ0��1
	//      style    -- �����ǩ���ı���ʽ
	//      fDistMax -- �����ǩ��ʼ���ֵ��ӵ����
	virtual void InitCellLabelInfo(int nCellLod, const VBF_TEXTSTYLE& style, float fDistMax)=0;
	virtual void GetCellLabelInfo(int nCellLod, VBF_TEXTSTYLE& style, float& fDistMax)=0;


	// ��ʼ��ĳ��Lod�����ģ����Ϣ��ע�⣺��ʼ������ֻ�ܵ���һ�Σ����ұ�������ӵ���ģ��֮ǰ����)
    // ������nLod -- Lod����ֻ��Ϊ0,1,2
	virtual void InitLodInfo(int nLod, const VBF_LOD_INFO& info)=0;
    virtual void GetLodInfo(int nLod, VBF_LOD_INFO& info)=0;


	// ��ʼ����ѡģ�͹켣����ʽ��ע�⣺��ʼ������ֻ�ܵ���һ�Σ����ұ�������ӵ���ģ��֮ǰ����)
	virtual void                 InitTrailStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetTrailStyle()=0;

    // ��ʼ��/��ȡ�Ƿ���ʾ����ģ�͵ĸ߶��ߣ���������Lod=1,2��ģ�ͣ�ע�⣺��ʼ������ֻ�ܵ���һ�Σ����������ʾ�߶��߻�Ӱ�����Ч�ʣ�
    virtual void InitHintLineVisible(bool bVisible)=0;
    virtual bool IsHintLineVisible()=0;

    // ��ʼ��/��ȡ����ģ�͵ĸ߶�����ʽ����������Lod=1,2��ģ�ͣ�ע�⣺��ʼ������ֻ�ܵ���һ�Σ�
    virtual void InitHintLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetHintLineStyle()=0;

	// ����/��ȡģ�͵���չ��Ϣ�Ƿ���ϵͳ�ڲ��洢��Ĭ��Ϊfalse��ע�⣺�ú���ֻ�ܵ���һ�Σ����ұ�������ӵ���ģ��֮ǰ����)
	// ������bSave -- �Ƿ���Ҫ��ģ�͵���չ��Ϣ������ϵͳ�ڲ������Ϊtrue����ռ�ô����ڴ棻���Ϊfalse����Ҫͨ���ⲿģ���ṩ��չ��Ϣ��
	virtual void SetExtInfoSaved(bool bSave)=0;
	virtual bool IsExtInfoSaved()=0;

    // ��ʼ��/��ȡLod=1ʱ��ͼ��ӳ���ע�⣺�ú���ֻ�ܵ���һ�Σ����ұ�������ӵ���ģ��֮ǰ����)
	// ע�⣺��������˸ú�����������InitLodInfo()�����е�Lod=1ʱ��ģ��ͼ�񣻷�������ģ�;�ʹ��InitLodInfo()�������õ�ͼ��
	virtual void InitRasterImageMap(const CVBF_RasterImageMap& mapImages)=0;
	virtual const CVBF_RasterImageMap& GetRasterImageMap()=0;

    // ��ʼ��/��ȡLod=2ʱ����άģ��ӳ���ע�⣺�ú���ֻ�ܵ���һ�Σ����ұ�������ӵ���ģ��֮ǰ����)
    // ע�⣺��������˸ú�����������InitLodInfo()�����е�Lod=2ʱ��ģ�ͣ���������ģ�;�ʹ��InitLodInfo()�������õ�ģ��
    virtual void InitRasterMeshMap(const CVBF_RasterMeshMap& mapMeshes)=0;
    virtual const CVBF_RasterMeshMap& GetRasterMeshMap()=0;

    // ����/��ȡLod=2ʱ��άģ�Ϳɼ�����С��ֱ�ӽǣ�����ģ�ͺ��ӵ�������������γɵļнǣ���λ���Ƕȣ�Ĭ��ֵΪ10�ȣ�
    // �û��ɸ��ݼ�������ܵ����ò���������Խ�ߣ��ò���ԽС
    virtual void  SetMeshVisibleAngleV(float fAngleV)=0;
    virtual float GetMeshVisibleAngleV()=0;

	// ���һ��ģ�ͣ������ظ�ģ���ڼ����е���ţ���0��ʼ��
	// ������nType����ģ�͵����ͣ�ϵͳ�����ݸ����ʹ�SetRasterImageMap()�����л�ȡ��Ӧ��ͼ��
	virtual int AddRaster(int nType)=0;

	// ɾ��һ��ģ��
	virtual void DeleteRaster(int nIndex)=0;

    // ����/��ȡĳ��ģ���Ƿ�ɼ���ǰ���Ǹ�ģ���Ѿ����
    virtual void SetRasterVisible(int nIndex, bool bVisible)=0;
    virtual bool IsRasterVisible(int nIndex)=0;

    // ��ȡ������ģ�͸����������Ѿ���ɾ���˵�ģ�ͣ�
    virtual int GetNumRastersIncludingDeleted()=0;

    // ��ȡ������ģ�͸����������Ѿ���ɾ���˵�ģ�ͣ�
    virtual int GetNumRastersExcludingDeleted()=0;

	// ����/��ȡĳ��ģ�͵ĵ������꣬ǰ���Ǹ�ģ���Ѿ����
	// ������nIndex -- ģ�͵����
	virtual void              SetRasterGeoPos(int nIndex, const osg::Vec3d& vGeo)=0;
	virtual const osg::Vec3d& GetRasterGeoPos(int nIndex)=0;

	// ����/��ȡĳ��ģ�͵ĺ���ǣ�����Z�����ת�ǣ���ǰ���Ǹ�ģ���Ѿ����
	// ������nIndex -- ģ�͵����
	virtual void  SetRasterRotateZ(int nIndex, float fRotateZ)=0;
	virtual float GetRasterRotateZ(int nIndex)=0;

	// ͬʱ����ģ�͵ĵ�������ͺ���ǣ�����Z�����ת�ǣ���ǰ���Ǹ�ģ���Ѿ����
	// ������nIndex -- ģ�͵����
	//      bSave  -- �Ƿ���Ҫ���õ㱣�����˶��켣�У����Ϊtrue����ռ��һ�������ڴ棻���Ϊfalse����Ҫͨ���ⲿģ���ṩ�˶��켣���ݣ�
	virtual void SetRasterGeoPos(int nIndex, const osg::Vec3d& vGeo, float fRotateZ)=0;


	// ���/�Ƴ�/��ȡ�û��Զ���Ĳ����ԣ�������ʾ��ѡģ�͵���Ϣ��ǰ���Ǹ�ģ���Ѿ����
	// ���û����ʽ����SetExtInfoSaved(true)�����º�����������
	// bOverwrite -- ����ò����Ե������Ѿ����ڣ��Ƿ񸲸�ԭ��ֵ
	virtual void AddUserValue(int nIndex, const std::string& strName, const std::string& strValue, bool bOverwrite=true)=0;
	virtual void RemoveUseValue(int nIndex, const std::string& strName)=0;
	virtual bool GetUserValue(int nIndex, const std::string& strName, std::string& strValue)=0;
	virtual void SetUserValues(int nIndex, const CVBF_UserValueMap& values)=0;
	virtual bool GetUserValues(int nIndex, CVBF_UserValueMap& values)=0;

	// ��ȡʵʱ��Ϣ
	virtual bool IsCellVisible()=0;		// Ŀǰ�����Ƿ�ɼ���������ģ�Ͳ���ͬʱ�ɼ���
	virtual bool IsRasterVisible()=0;	// Ŀǰģ���Ƿ�ɼ�
	virtual int  GetCellLod()=0;		// �������ɼ�����ȡ��Ŀǰ��Lod��ֻ��Ϊ0, 1��
    virtual int  GetRasterLod()=0;		// ���ģ�Ϳɼ�����ȡ��Ŀǰ��Lod��ֻ��Ϊ0, 1, 2��

	// ��ȡ��ǰ��ѡģ�͵���չ��Ϣ
    virtual const VBF_RASTER_EXTINFO& GetSelRasterExtInfo()=0;

    // ��Ӧ�û������е���Ϣ
    virtual void OnInfoDialogClosed()=0;  // ��Ӧģ����Ϣ�Ի���ر���Ϣ

    // Ŀǰ�������Ƿ��б�ѡ�е�ģ��
    virtual bool HasSelected()=0;

    // ��ȡ�����е�ǰ��ѡ�е�ģ�͵����
    virtual int GetSelectedIndex()=0;
};


#endif 
