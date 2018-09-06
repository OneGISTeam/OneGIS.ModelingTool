//*******************************************************************
// FileName��  VBF_3DTransBlkNote.h
// Function��  3D��������ģ�ͣ�ע�����ݿ�
// Author:     ��Ө
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
	
	// ���ÿ��ע������
	bool SetNoteData(int nNumNotes, VBF_NOTEDATA** pNoteData);		

	// ��ȡע�ǵĸ���������
	int				GetNumNotes()  { return m_nNumNotes; }
	VBF_NOTEDATA**  GetNoteData()  { return m_pNoteData; }	
	
	// �ж�ע�ǿ����Ƿ�������
	bool HasData()      { return (m_nNumNotes>0); }

private:
	void  Clear();

private:
	int              m_nNumNotes;       // ע�Ǹ���
	VBF_NOTEDATA**   m_pNoteData;       // ע������
};


//================================== ʵ�ֲ��� =================================

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
// ������Clear()
// �����������ǰ������
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
// ������SetNoteData()
// ���������ÿ��е�ע������
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