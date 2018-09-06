//***************************************************************************************
// FileName：IVBF_Log.h
// Function：日志接口，用于记录日志信息
// Author:   杜莹
// Date:     2009-11-5
//***************************************************************************************

#ifndef __IVBF_LOG_H__
#define __IVBF_LOG_H__


// 定义日志的级别
const int VBF_LOG_LEVEL_VITAL_ERROR		= 1;	// 致命错误
const int VBF_LOG_LEVEL_SERIOUS_ERROR	= 2;	// 严重错误
const int VBF_LOG_LEVEL_WARNING			= 3;	// 警告
const int VBF_LOG_LEVEL_NORMAL			= 4;	// 一般日志


// 获取程序当前运行所在的文件名及行号，
#define VBF_FILENAME		( __FILE__ )	// 可用作AddLog()函数的szFileName参数
#define VBF_LINENUMBER		( __LINE__ )	// 可用作AddLog()函数的nLineNumber参数


// 日志接口
class IVBF_Log
{
public:

	virtual ~IVBF_Log() {}

public:	

	/// \brief 增加一条日志信息。
	///
	/// 增加一条日志信息（简略信息）。
	///
	/// \return 如果成功，则返回true；否则返回false。
	///
	/// \param szFormat:	日志信息的格式化字符串
	///
    virtual bool AddLog(const char* szFormat, ...)=0;


	/// \brief 增加一条日志信息。
	///
	/// 增加一条日志信息（详细信息）。
	///
	/// \return 如果成功，则返回true；否则返回false。
	///
	/// \param nLevel:		日志的级别
	/// \param szSender:	日志的发送者，一般为类名::函数名，可以为NULL
	/// \param szFileName:	发送日志的文件名，可以为NULL
	/// \param nLineNumber: 发送日志的代码行号，如果szFileName为NULL，忽略该参数
	/// \param szFormat:	日志信息的格式化字符串
	///
    virtual bool AddLog(int nLevel, const char* szSender, const char* szFileName, int nLineNumber, const char* szFormat, ...)=0;

	

	/// \brief 获取日志信息个数。
	///
	/// \return 如果已经记录过日志信息，则返回日志信息个数；否则返回0。
	///
	/// \param 无。
	///
	virtual int GetLogCount()=0;

		/// \brief 获取日志文件名称。
	///
	/// 获取日志文件名称。
	///
	/// \return 日志文件名称。
	///
	/// \param 无
	///
    virtual const char* GetLogFileName()=0;
};


#endif
