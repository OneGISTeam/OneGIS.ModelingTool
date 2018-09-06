//***************************************************************************************
// FileName��IVBF_3DMarine.h
// Function��3D������Ϣ�ӿ�
// Author:   ��Ө
// Date:     2016-10-12
//***************************************************************************************

#ifndef __IVBF_3DMRINE_H__
#define __IVBF_3DMRINE_H__

#include <VBF_Base/VBF_Referenced.h>
#include <Types/Vec3d>
#include <vector>
#include <VBF_Aux/VBF_GLAux/VBF_GraphicsAppearance.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeCylinderS.h>
#include <VBF_Engine/VBF_SceneGraph/Image>


// ����������ID��
const char VBF_COMPONENT_3DMARINE[]		= "Component: 3DMarine";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DMARINE[]		= "��ά������Ϣ�ӿ�";


//-------------------------------------------------------------------------
// ��ά����ͼ��ʵ������һ��Բ����
//-------------------------------------------------------------------------
class IVBF_3DSection : public CVBF_Referenced
{
public:
    virtual ~IVBF_3DSection() {}

    // ��ȡID��
    virtual const std::string& GetID()=0;

    // ����/��ȡԲ�����Բ�ָܷ�����Ĭ��ֵΪ36
    virtual void SetNumSplit(int nNumSplit)=0;
    virtual int  GetNumSplit()=0;

    // ����/��ȡԲ����Ķ���Բ���ָ�����Ĭ��ֵΪ6
    virtual void SetNumTopSplit(int nNumSplit)=0;
    virtual int  GetNumTopSplit()=0;

    // ���ø߶����飺�ϱߡ��±ߡ�����
    virtual void SetTopEdgeHeights(const std::vector<double>& vHeight)=0;       // Ҫ��vHeight.size()=GetNumSplit()+1
    virtual void SetBottomEdgeHeights(const std::vector<double>& vHeight)=0;    // Ҫ��vHeight.size()=GetNumSplit()+1
    virtual void SetTopHeights(const std::vector<double>& vHeight)=0;           // Ҫ��vHeight.size()=GetNumTopSplit()*(GetNumSplit()+1)

    // ��ȡ���
    virtual IVBF_GraphicsAppearance* GetAppearance()=0;
};


//-----------------------------------------------------------------------------------------------
// ��άӰ�����ͼ��ʵ�����Ƕ������һ�����ĳ�����ͼ�����µ��ӵ�һ�𣬿����ڱ���ͬһ������ͬʱ�ε�Ӱ��
//-----------------------------------------------------------------------------------------------
class IVBF_3DOverlap : public CVBF_Referenced
{
public:
    virtual ~IVBF_3DOverlap() {}

    // ���/ɾ��һ��ͼ�㣨ͼ�����������ظ���
    virtual void AddLayer(const std::string& strLayerName, osg::Image* pImage)=0;
	virtual void InsertLayer(int nIndex, const std::string& strLayerName, osg::Image* pImage)=0;
	virtual void RemoveLayer(const std::string& strLayerName)=0;

	// ��ȡ���ӵ�ͼ������
	virtual int GetNumLayers()=0;

    // ��ȡID��
    virtual const std::string& GetID()=0;

	// ����/��ȡ����ͼ�ĵ������귶Χ
    virtual void SetGeoRange(double dL0, double dL1, double dB0, double dB1)=0;
	virtual void GetGeoRange(double& dL0, double& dL1, double& dB0, double& dB1)=0;

	// ͨ����ȡtfw��׼�ļ����ǵ�/���ĵ㣩�����õ�������ͳߴ�
	virtual bool SetGeoRangeByTfwCorner(const std::string& strFileName)=0;
	virtual bool SetGeoRangeByTfwCenter(const std::string& strFileName)=0;

	// ����/��ȡ��������֮��Ĵ�ֱ�������λ���ף�
    virtual void  SetVertInterval(float fInterval)=0;
	virtual float GetVertInterval()=0;
	
	// ����/��ȡÿ�㳤����ĺ�ȣ��ú��Ϊ���ֵ������ڴ�ֱ�����ֵ��Ϊ[0, 0.5]��
    virtual void  SetLayerThicknessRatio(float fRatio)=0;
	virtual float GetLayerThicknessRatio()=0;

	// ����/��ȡÿ�㳤����Ĳ�����ɫ����λ���ף�
    virtual void              SetSideColor(const osg::Vec4f& color)=0;
	virtual const osg::Vec4f& GetSideColor()=0;

	// ����/��ȡ�õ���ͼ�Ƿ�ɼ�
	virtual void SetVisible(bool bVisible)=0;
	virtual bool IsVisible()=0;

	// ��ȡ�õ���ͼ�Ƿ񼤻ֻ�б�����ſ���ʾͼ�����ɲ鿴ÿһ�㣩
	virtual bool IsActive()=0;
};

//-------------------------------------------------------------------------------
// 3D������Ϣ�ӿ�
//-------------------------------------------------------------------------------
class IVBF_3DMarine : public CVBF_Referenced
{
public:	
    virtual ~IVBF_3DMarine() {}


	//---------------- ��Բ��������ͼ�йصĺ��� ------------------------------

    // ����һ������ͼ��������ΨһID��
    virtual IVBF_3DSection* CreateSection(const std::string& strID)=0;

    // ���Ӵ��������/�Ƴ�һ������ͼ
    virtual void AddSection(IVBF_3DSection* pISection)=0;
    virtual void RemoveSection(IVBF_3DSection* pISection)=0;
    virtual void RemoveSection(const std::string& strID)=0;

    // ��ȡ�Ѿ���ӵ�����ͼ�������δ��ӻ��Ѿ����Ƴ�������NULL
    virtual IVBF_3DSection* GetSection(const std::string& strID)=0;

    // ����/��ȡ����ͼԲ������泤����İ뾶�����߲���ȱ�ʾ��Բ���壬������ȱ�ʾԲ����
    virtual void SetSectionRadius(float fRadiusX, float fRadiusY)=0;
    virtual void GetSectionRadius(float& fRadiusX, float& fRadiusY)=0;

    // ����/��ȡ����ͼԲ����߶�
    virtual void  SetSectionHeight(float fHeight)=0;
    virtual float GetSectionHeight()=0;

    // ע�⣺�����Ӵ��ھ�ָ����ͼ���ڵ��Ӵ���

    // ����/��ȡ�Ӵ����Ƿ�ɼ���Ĭ��Ϊtrue��
    virtual void SetSubViewVisible(bool bVisible)=0;
    virtual bool IsSubViewVisible()=0;

    // ����/��ȡ�Ӵ��ڵı���
    virtual void SetSubViewTitle(const std::string& strTitle)=0;
    virtual const std::string& GetSubViewTitle()=0;

    // ����/��ȡ�Ӵ��ڵĳߴ磨��λ�����أ�
    virtual void SetSubViewSize(int nSizeX, int nSizeY)=0;
    virtual void GetSubViewSize(int& nSizeX, int& nSizeY)=0;

    // ����/��ȡ�Ӵ��ڵ�λ�ã���λ�����أ�ԭ��λ���ӿ����½ǣ�
    virtual void SetSubViewPos(float x, float y)=0;
    virtual void GetSubViewPos(float& x, float& y)=0;

    // ����/��ȡ�Ӵ��ڵı���ɫ
    virtual void SetSubViewBackColor(const osg::Vec4f& color)=0;
    virtual const osg::Vec4f& GetSubViewBackColor()=0;


	//---------------- ��Ӱ�����ͼ�йصĺ��� ------------------------------

    // ����һ������ͼ��������ΨһID��
    virtual IVBF_3DOverlap* CreateOverlap(const std::string& strID)=0;

    // ���Ӵ��������/�Ƴ�һ������ͼ
    virtual void AddOverlap(IVBF_3DOverlap* pIOverlap)=0;
    virtual void RemoveOverlap(IVBF_3DOverlap* pIOverlap)=0;
    virtual void RemoveOverlap(const std::string& strID)=0;

    // ��ȡ�Ѿ���ӵĵ���ͼ�������δ��ӻ��Ѿ����Ƴ�������NULL
    virtual IVBF_3DOverlap* GetOverlap(const std::string& strID)=0;

	// ����/��ȡ��ǰ����ĵ���ͼ��ֻ�б�����ĵ���ͼ�ſ���ʾͼ�����ɲ鿴ÿһ�㣩
	virtual void SetActiveOverlap(const std::string& strID)=0;
	virtual std::string GetActiveOverlap()=0;
};


#endif 
