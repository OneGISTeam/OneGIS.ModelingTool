//***************************************************************************************
// FileName��VBF_3DDataSetTypes.h
// Function�����ݼ�������Ҫʹ�õĹ�����������
// Author:   ��Ө
// Date:     2011-09-20
//***************************************************************************************

#ifndef __VBF_3DDATASET_TYPES_H__
#define __VBF_3DDATASET_TYPES_H__


//--------------------------------------------------------------------------
// ����ṹ�壺VBF_3DDATAPROVIDER
// �ṹ��������3D���ݼ��ṩ��
//--------------------------------------------------------------------------
typedef struct _tagVBF3DDataProvider
{	
	char	szID[64];			// �����ṩ�ߵ�ID�� (ȫ��Ψһ�����ִ�Сд)
	char	szDll[64];			// ��̬������ (����·������.dll��׺)		
	char	szDesc[256];		// ������Ϣ	

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
// ����ṹ�壺VBF_3DDATASET
// �ṹ��������3D���ݼ�����¼���ݵ�Ԫ��Ϣ��չʾ����
//--------------------------------------------------------------------------
typedef struct _tagVBF3DDataSet
{	
	char	szProviderID[64];	// �����ṩ�ߵ�ID��
	char	szURL[256];			// ����λ��	
	bool	bVisible;			// �Ƿ�ɼ�

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
// ����ṹ�壺VBF_3DDATASETTEX
// �ṹ���������������ݼ�
//--------------------------------------------------------------------------
typedef struct _tagVBF3DDataSetTex : public VBF_3DDATASET
{	
	int		nLayerIndex;		// ͼ����ţ�0��ʾ��ײ㣬-1��ʾ������
	int		nLodMin;			// �ɼ�����СLod������С����������洢����СLod
	int		nLodMax;			// �ɼ������Lod�����ܴ�����������洢�����Lod
	float	fTransparency;		// ͸����

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
// ����ṹ�壺VBF_3DDATASETDEM
// �ṹ��������Dem���ݼ�
//--------------------------------------------------------------------------
typedef struct _tagVBF3DDataSetDem : public VBF_3DDATASET
{	
	int		nPriority;			// ���ȼ���0��ʾ���ȼ����

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
// ����ṹ�壺VBF_3DDATASETNOTE
// �ṹ��������Dem���ݼ�
//--------------------------------------------------------------------------
typedef struct _tagVBF3DDataSetNote : public VBF_3DDATASET
{	
	int		nPriority;			// ���ȼ���0��ʾ���ȼ����

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

