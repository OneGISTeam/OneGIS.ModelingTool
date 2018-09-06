#if !defined(AFX_CLRFILEDIALOG_H__07D9A911_2543_4915_97A9_3FFA4D43DB97__INCLUDED_)
#define AFX_CLRFILEDIALOG_H__07D9A911_2543_4915_97A9_3FFA4D43DB97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClrFileDialog.h : header file
//

#include "ColorLookUpTable.h"
/////////////////////////////////////////////////////////////////////////////
// CClrFileDialog dialog

class CClrFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CClrFileDialog)

public:
	CClrFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	enum { IDD = IDD_FILECOLORTMP_DIALOG };

//user data
	CColorLookUpTable m_ColorTable;

	void DrawColorSpectrum();


protected:
	//{{AFX_MSG(CClrFileDialog)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnFileNameChange();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLRFILEDIALOG_H__07D9A911_2543_4915_97A9_3FFA4D43DB97__INCLUDED_)
