//*******************************************************************
// FileName��IVBF_MarkStyleManager.h
// Function��������ʽ�������ӿ�
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


// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_MARKSTYLEMANAGER[]		=	"Interface: MarkStyleManager";	


//------------------------------------------------------------------
// ����ṹ�壺VBF_MARKSTYLE
// �ṹ������������ģ�͵���ʽ��Ϣ
//------------------------------------------------------------------
typedef struct _tagVBFMarkStyle
{
	std::string			strCode;		// ��ʽ����
	unsigned int 		nType;          // ģ�͵����ͣ��磺VBF_MARK_MESH�ȣ�
	TiXmlElement*		pElem;			// ����ʽ��Ӧ��xml�ڵ�

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

	// ���ظ�ֵ������=
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
// ����ṹ�壺VBF_MARKIFFSTYLE
// �ṹ������������ģ�͵ĵ���ʶ����ʽ
//------------------------------------------------------------------
typedef struct _tagVBFMarkIFFStyle
{
	std::string		strName;	// ���ƣ���"δָ��"��"�ҷ�"��"�з�"��
	osg::Vec4f		color;		// ��ɫ

	_tagVBFMarkIFFStyle()
	{
		strName = "δָ��";
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
// ����ӿڣ�IVBF_MarkStyleManager
// �ӿ�����������ģ����ʽ�Ĺ�����
//------------------------------------------------------------------
class IVBF_MarkStyleManager : public CVBF_Referenced
{
public:
	virtual ~IVBF_MarkStyleManager() {}

    // ��xml�����ļ��ж�ȡģ�͵���ʽ��Ϣ���������ǰ����Ϣ��ģ������·���Ե�һ�������ļ�Ϊ׼��
    virtual bool Load(const std::string& strFileName)=0;

    // �������ģ�͵���ʽ��Ϣ
    virtual void Clear()=0;

    // ��ȡ����ģ���ļ��ľ���·��
    virtual const std::string& GetModelFilePath()=0;

	// ��ȡ����ģ�͵���ʽ��Ϣ (�����ʽ��Ϣ������Ϊ0�� ����true�����򣬷���false)
	// ������nMarkType -- ���������(�����VBF_MARK_MESH��)�����ΪVBF_MARK_UNKNOWN�������������͵ľ�����ʽ��Ϣ
	virtual bool GetStyles(unsigned int nMarkType, vector<VBF_MARKSTYLE*>& vStyles)=0;
	
	// ����ĳ��ģ�͵���ʽ��Ϣ
	virtual bool LookupStyle(const std::string& strCode, VBF_MARKSTYLE*& pStyle)=0;


    //================================= ģ�͵���ʶ�����ʽ =================================//

    /* ��ȡ����ʶ��ĸ���*/
    virtual int GetIFFCount()=0;

    /* ��ȡ��n������ʶ�����Ϣ, �������ڱ���,��˳���޹� */
    virtual bool GetIFF(int nIndex, VBF_MARKIFFSTYLE& style)=0;

    /* ���һ�ֵ���ʶ�𣬲���������ɫ (ע�⣺�����ʶ���Ѵ��ڣ�ֱ�Ӹ���)
       ������style -- ����ʶ�����ʽ��Ϣ
       ���أ���ӳɹ�����true�����򷵻�false
    */
    virtual bool AddIFF(const VBF_MARKIFFSTYLE& style)=0;

    /* ����һ�ֵ���ʶ�𣬲���ȡ����ɫ
       ������strName -- ����ʶ���Ψһ��ʶ���磺"�ҷ�"��"�з�"��"�ѷ�"��
       ���أ�color   -- �õ���ʶ�����ɫ��͸����
       ���أ��õ���ʶ����ڷ���true�����򷵻�false
    */
    virtual bool LookupIFF(const std::string& strName, VBF_MARKIFFSTYLE& style)=0;
};


#endif 
