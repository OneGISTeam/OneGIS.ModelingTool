//************************************************************************
// FileName��IVBF_MarkModelRasterSet.h
// Function������ʵ��ģ�ͽӿڣ�դ��ģ�͵ļ��ϣ������ڻ��ƴ�����ͬ��դ��ģ�ͣ�
//           �ü���������ģ��������ͬ���ߴ���ͬ����ת��ʽ��ͬ
// Author:   ��Ө
// Date:     2015-10-23
//************************************************************************

#ifndef __IVBF_MARK_MODEL_RASTERSET_H__
#define __IVBF_MARK_MODEL_RASTERSET_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Massive/VBF_3DPlotDataTypes_Massive.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <string>



// ������ϢID��
const char VBF_MESSAGE_3DPLOT_RASTERSET_SHOWINFODIALOG[]    = "Message: RasterSet ShowInfoDialog";   // ��Ϣ����Ҫ��ʾ�����б�ѡģ�͵���Ϣ�Ի���
const char VBF_MESSAGE_3DPLOT_RASTERSET_CLOSEINFODIALOG[]   = "Message: RasterSet CloseInfoDialog";  // ��Ϣ����Ҫ�ر���Ϣ�Ի���


typedef std::map<std::string, std::string>  CVBF_UserValueMap;


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelRasterSet
// �ӿ�������դ��ģ�͵ļ��ϣ��ü���������ģ��ʹ����ͬ������
//--------------------------------------------------------------------
class IVBF_MarkModelRasterSet : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelRasterSet() {}


	// ��ʼ�����ϵĳߴ���Ϣ��ֻ�ܵ���һ�Σ����ұ�������ӵ���ģ��֮ǰ����
	// ������bFixedSizeInPixels -- �Ƿ�̶����ش�С�����Ϊtrue����Ⱥ͸߶Ȳ����ĵ�λΪ����
	//       fWidth, hfHeight  -- ����ģ�͵Ŀ�Ⱥ͸߶ȣ���λ������/�ף�
	virtual void  InitSize(bool bFixedSizeInPixels, float fWidth, float fHeight)=0;
	virtual bool  IsFixedSizeInPixels()=0;
	virtual float GetWidth()=0;
	virtual float GetHeight()=0;


	// ��ʼ�����ϵ�������Ϣ��ֻ�ܵ���һ�Σ����ұ�������ӵ���ģ��֮ǰ����
	// ������pTexImage -- ����������ģ�͹��õ�����ͼ��ָ��
	//      fTexAlpha  -- ����������ģ�͵�����͸���ȣ�Ĭ��ֵΪ1.0��
	//      fTexOrignX, fTexOrignY-- ����ԭ����λͼ�е����λ�� (��������½ǣ�ֵ��Ϊ[0.0, 1.0]��Ĭ��ֵ�ֱ�Ϊ0.5, 0.5)
	virtual void InitTexture(osg::Image* pTexImage, float fTexAlpha=1.0f, float fTexOrignX=0.5f, float fTexOrignY=0.5f)=0;
	virtual osg::Image* GetImage()=0;
	virtual float GetTexAlpha()	=0;
	virtual float GetTexOrignX()=0;
	virtual float GetTexOrignY()=0;


	// ��ʼ���ռ�ָ��ÿ����Ԫ���д洢�����ģ�͸�����Ĭ��ֵΪ100��
	// ����ָ���<=5����ʾRasterģ���������٣���ȷ�ü����ȣ�����Ч�ʴ�֮�����򣬻���Ч�����ȣ���ȷ�ü���֮
	virtual void         InitNumMaxRastersPerCell(unsigned int num)=0;
	virtual unsigned int GetNumMaxRastersPerCell()=0;

	// ��ȡ������դ��ģ�͸���
	virtual int GetNumRasters()=0;

	// ��ȡĳ��ģ�͵ĵ�������
	virtual const osg::Vec3d& GetRasterGeoPos(int nIndex)=0;


	// ���/�Ƴ�/��ȡ�û��Զ���ļ��Բ����ԣ�������ʾ��ѡģ�͵ļ�����Ϣ��ǰ���Ǹ�ģ���Ѿ����
	virtual void AddUserValue(int nIndex, const std::string& strName, const std::string& strValue, bool bOverwrite=true)=0;
	virtual void RemoveUseValue(int nIndex, const std::string& strName)=0;
	virtual bool GetUserValue(int nIndex, const std::string& strName, std::string& strValue)=0;
	virtual void SetUserValues(int nIndex, const CVBF_UserValueMap& values)=0;
	virtual bool GetUserValues(int nIndex, CVBF_UserValueMap& values)=0;

	// ���/�Ƴ�/��ȡ�û��Զ������ϸ�����ԣ�������ʾ��ѡģ�͵���ϸ��Ϣ��ǰ���Ǹ�ģ���Ѿ����
	virtual void AddUserValueDetail(int nIndex, const std::string& strName, const std::string& strValue, bool bOverwrite=true)=0;
	virtual void RemoveUseValueDetail(int nIndex, const std::string& strName)=0;
	virtual bool GetUserValueDetail(int nIndex, const std::string& strName, std::string& strValue)=0;
	virtual void SetUserValuesDetail(int nIndex, const CVBF_UserValueMap& values)=0;
	virtual bool GetUserValuesDetail(int nIndex, CVBF_UserValueMap& values)=0;

    // ��Ӧ�û������е���Ϣ
    virtual void OnInfoDialogClosed()=0;  // ��Ӧģ����Ϣ�Ի���ر���Ϣ

    // Ŀǰ�������Ƿ��б�ѡ�е�ģ��
    virtual bool HasSelected()=0;

    // ��ȡ�����е�ǰ��ѡ�е�ģ�͵����
    virtual int GetSelectedIndex()=0;
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelRasterSetBoardH
// �ӿ�������դ��ģ�͵ļ��ϣ������е�ÿ��ģ����ˮƽ����ʹ�ò�����
//--------------------------------------------------------------------
class IVBF_MarkModelRasterSetBoardH : public IVBF_MarkModelRasterSet
{
public:
	virtual ~IVBF_MarkModelRasterSetBoardH() {}

	// ���һ��դ��ģ��
	// ������vGeo -- ģ�͵ĵ�������
	virtual int AddRaster(const osg::Vec3d& vGeo)=0;
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelRasterSetBoardV
// �ӿ�������դ��ģ�͵ļ��ϣ������е�ÿ��ģ���ڴ�ֱ����ʹ�ò�����
//--------------------------------------------------------------------
class IVBF_MarkModelRasterSetBoardV : public IVBF_MarkModelRasterSet
{
public:
	virtual ~IVBF_MarkModelRasterSetBoardV() {}

	// ���һ��դ��ģ��
	// ������vGeo -- ģ�͵ĵ�������
	virtual int AddRaster(const osg::Vec3d& vGeo)=0;
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelRasterSetBoardHV
// �ӿ�������դ��ģ�͵ļ��ϣ������е�ÿ��ģ����ͬʱˮƽ�ʹ�ֱ����ʹ�ò�����
//--------------------------------------------------------------------
class IVBF_MarkModelRasterSetBoardHV : public IVBF_MarkModelRasterSet
{
public:
	virtual ~IVBF_MarkModelRasterSetBoardHV() {}

	// ���һ��դ��ģ�ͣ������ظ�ģ���ڼ����е����
	// ������vGeo -- ģ�͵ĵ�������
	virtual int AddRaster(const osg::Vec3d& vGeo)=0;
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelRasterSetHorizon
// �ӿ�������դ��ģ�͵ļ��ϣ������е�ÿ��ģ��ʼ��ƽ���ڵ��棬���ӵ��޹أ�ֻ������Z����ת
//--------------------------------------------------------------------
class IVBF_MarkModelRasterSetHorizon : public IVBF_MarkModelRasterSet
{
public:
	virtual ~IVBF_MarkModelRasterSetHorizon() {}

	// ���һ��դ��ģ��
	// ������vGeo -- ģ�͵ĵ�������
	//      fAngleZ -- ģ����Z�����ת�ǣ���λ���Ƕȣ�
	virtual int AddRaster(const osg::Vec3d& vGeo, float fAngleZ=0.0f)=0;
};


#endif 
