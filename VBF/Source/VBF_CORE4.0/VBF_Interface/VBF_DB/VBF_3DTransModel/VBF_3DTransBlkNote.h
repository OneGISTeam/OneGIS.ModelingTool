//*******************************************************************
// FileName：  VBF_3DTransBlkNote.h
// Function：  3D交换数据模型：注记数据块
// Author:     杜莹
// Date:       2011-07-23
//*******************************************************************

#ifndef __VBF_3DTRANS_BLK_NOTE_H__
#define __VBF_3DTRANS_BLK_NOTE_H__

#include "VBF_3DTransBlk.h"
#include "VBF_DB\\VBF_DemTexDataType.h"

class CVBF_TransBlkNote : public CVBF_TransBlk
{
public:
	CVBF_TransBlkNote();
	virtual ~CVBF_TransBlkNote();
	
	// 设置块的注记数据
	bool SetNoteData(int nNumNotes, VBF_NOTEDATA** pNoteData);		

	// 获取注记的个数和数据
	int				GetNumNotes()  { return m_nNumNotes; }
	VBF_NOTEDATA**  GetNoteData()  { return m_pNoteData; }	
	
	// 判断注记块中是否有数据
	bool HasData()      { return (m_nNumNotes>0); }

private:
	void  Clear();

private:
	int              m_nNumNotes;       // 注记个数
	VBF_NOTEDATA**   m_pNoteData;       // 注记数据
};


//================================== 实现部分 =================================

inline CVBF_TransBlkNote::CVBF_TransBlkNote()
	: CVBF_TransBlk(VBF_BLK_NOTE)
{
	m_nNumNotes = 0;
	m_pNoteData = NULL;
}

inline CVBF_TransBlkNote::~CVBF_TransBlkNote()
{
	Clear();	
}

//----------------------------------------------------------------------------------------
// 函数：Clear()
// 描述：清除当前的数据
//----------------------------------------------------------------------------------------
inline void CVBF_TransBlkNote::Clear()
{
	if(NULL==m_pNoteData) return;

	for(int i=0; i<m_nNumNotes; i++)
	{
		SAFE_DELETE(m_pNoteData[i]);
	}
	SAFE_DELETE(m_pNoteData);

	m_nNumNotes = 0;
}

//----------------------------------------------------------------------------------------
// 函数：SetNoteData()
// 描述：设置块中的注记数据
//----------------------------------------------------------------------------------------
inline bool CVBF_TransBlkNote::SetNoteData(int nNumNotes, VBF_NOTEDATA** pNoteData)
{
	if(nNumNotes<=0 || NULL==pNoteData) return true;

	Clear();

	m_nNumNotes = nNumNotes;
	m_pNoteData = new VBF_NOTEDATA*[m_nNumNotes];
	
	for(int i=0; i<m_nNumNotes; i++)
	{
		m_pNoteData[i] = new VBF_NOTEDATA;
		*(m_pNoteData[i]) = *(pNoteData[i]);		
	}

	return true;
}

#endif