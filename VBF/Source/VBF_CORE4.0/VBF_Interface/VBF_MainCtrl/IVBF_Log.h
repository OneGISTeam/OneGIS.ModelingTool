//***************************************************************************************
// FileName��IVBF_Log.h
// Function����־�ӿڣ����ڼ�¼��־��Ϣ
// Author:   ��Ө
// Date:     2009-11-5
//***************************************************************************************

#ifndef __IVBF_LOG_H__
#define __IVBF_LOG_H__


// ������־�ļ���
const int VBF_LOG_LEVEL_VITAL_ERROR		= 1;	// ��������
const int VBF_LOG_LEVEL_SERIOUS_ERROR	= 2;	// ���ش���
const int VBF_LOG_LEVEL_WARNING			= 3;	// ����
const int VBF_LOG_LEVEL_NORMAL			= 4;	// һ����־


// ��ȡ����ǰ�������ڵ��ļ������кţ�
#define VBF_FILENAME		( __FILE__ )	// ������AddLog()������szFileName����
#define VBF_LINENUMBER		( __LINE__ )	// ������AddLog()������nLineNumber����


// ��־�ӿ�
class IVBF_Log
{
public:

	virtual ~IVBF_Log() {}

public:	

	/// \brief ����һ����־��Ϣ��
	///
	/// ����һ����־��Ϣ��������Ϣ����
	///
	/// \return ����ɹ����򷵻�true�����򷵻�false��
	///
	/// \param szFormat:	��־��Ϣ�ĸ�ʽ���ַ���
	///
    virtual bool AddLog(const char* szFormat, ...)=0;


	/// \brief ����һ����־��Ϣ��
	///
	/// ����һ����־��Ϣ����ϸ��Ϣ����
	///
	/// \return ����ɹ����򷵻�true�����򷵻�false��
	///
	/// \param nLevel:		��־�ļ���
	/// \param szSender:	��־�ķ����ߣ�һ��Ϊ����::������������ΪNULL
	/// \param szFileName:	������־���ļ���������ΪNULL
	/// \param nLineNumber: ������־�Ĵ����кţ����szFileNameΪNULL�����Ըò���
	/// \param szFormat:	��־��Ϣ�ĸ�ʽ���ַ���
	///
    virtual bool AddLog(int nLevel, const char* szSender, const char* szFileName, int nLineNumber, const char* szFormat, ...)=0;

	

	/// \brief ��ȡ��־��Ϣ������
	///
	/// \return ����Ѿ���¼����־��Ϣ���򷵻���־��Ϣ���������򷵻�0��
	///
	/// \param �ޡ�
	///
	virtual int GetLogCount()=0;

		/// \brief ��ȡ��־�ļ����ơ�
	///
	/// ��ȡ��־�ļ����ơ�
	///
	/// \return ��־�ļ����ơ�
	///
	/// \param ��
	///
    virtual const char* GetLogFileName()=0;
};


#endif
