#pragma once
#include "afxwin.h"


// CTimerEndDlg ��ȭ �����Դϴ�.

class CTimerEndDlg : public CDialog
{
	DECLARE_DYNAMIC(CTimerEndDlg)

public:
	CTimerEndDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTimerEndDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CFont EndFont;
	afx_msg void OnBnClickedOk();
};
