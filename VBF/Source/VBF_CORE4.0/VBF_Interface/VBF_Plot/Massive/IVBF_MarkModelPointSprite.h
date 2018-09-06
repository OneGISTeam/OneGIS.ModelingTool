//************************************************************************
// FileName��IVBF_MarkModelPointSprite.h
// Function������ʵ��ģ�ͽӿڣ��㾫�飨�����ڻ��ƴ�����ͬ�ĵ㣩
//           �ü��������е��������ͬ���ߴ���ͬ����ʼ�ճ����ӵ�
// Author:   ��Ө
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
// ����ӿڣ�IVBF_MarkModelPointSprite
// �ӿ��������㾫��
//--------------------------------------------------------------------
class IVBF_MarkModelPointSprite : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelPointSprite() {}

	// ��ʼ�����������е�ĳߴ���Ϣ��ֻ�ܵ���һ�Σ����ұ�������ӵ���ģ��֮ǰ����
	//       fSizeInPixels  -- ������ĳߴ磨��λ�����أ�
	virtual void InitSize(float fSizeInPixels)=0;

	// ��ʼ�����ϵ�������Ϣ��ֻ�ܵ���һ�Σ����ұ�������ӵ���ģ��֮ǰ����
	// ������pTexImage -- ����������ģ�͹��õ�����ͼ��ָ��
	//      fTexAlpha  -- ����������ģ�͵�����͸���ȣ�Ĭ��ֵΪ1.0��
	virtual void InitTexture(osg::Image* pTexImage, float fTexAlpha=1.0f)=0;


	// ��ʼ���ռ�ָ��ÿ����Ԫ���д洢����������Ĭ��ֵΪ100��
	// ����ָ���<=5����ʾ���������٣���ȷ�ü����ȣ�����Ч�ʴ�֮�����򣬻���Ч�����ȣ���ȷ�ü���֮
	virtual void InitNumMaxPointsPerCell(unsigned int num)=0;

	// ���һ���㣬�����ظõ��ڼ����е���ţ�����vGeo��ʾ��ĵ�������
	virtual int AddPoint(const osg::Vec3d& vGeo)=0;

	// ��ȡ�����е�ĸ���
	virtual int GetNumPoints()=0;

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
};



#endif 
