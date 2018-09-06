//*******************************************************************
// FileName��  VBF_MemFile.h
// Function��  �ڴ��ļ���
// Author:     κ��
// Date:       2011-08-28
// ��ע:	   �ο���cximage��
//*******************************************************************

#ifndef __VBF_MEMFILE_H__
#define __VBF_MEMFILE_H__



#include "VBF_Common/VBF_Utils/VBF_UtilsExport.h"
#include "VBF_Macros.h"

typedef unsigned char BYTE;

//////////////////////////////////////////////////////////
class VBF_UTILS_EXPORT CVBF_MemFile
{
public:
	CVBF_MemFile(BYTE* pBuffer = NULL, DWORD size = 0);
	virtual ~CVBF_MemFile();

	bool  Open();
	BYTE* GetBuffer(bool bDetachBuffer = true);

	bool	Close();
	size_t	Read(void *buffer, size_t size, size_t count=1);
	size_t	Write(const void *buffer, size_t size, size_t count=1);
	bool	Seek(long offset, int origin);
	long	Tell();
	long	Size();
	bool	Flush();
	bool	Eof();
	long	Error();
	bool	PutC(unsigned char c);
	long	GetC();
	char *	GetS(char *string, int n);
	long	Scanf(const char *format, void* output);

	// ��Ө��ӣ�2013-01-11
	BYTE*	Detach();

protected:
	bool	Alloc(DWORD nBytes);
	void	Free();

protected:
	BYTE*	m_pBuffer;
	DWORD	m_Size;
	bool	m_bFreeOnClose;
	long	m_Position;	//current position
	long	m_Edge;		//buffer size
};

#endif
