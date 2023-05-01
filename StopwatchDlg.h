#pragma once
#include "afxwin.h"
#define MAXLAP 100
// CStopwatchDlg ��ȭ �����Դϴ�.

class CStopwatchDlg : public CDialog
{
	DECLARE_DYNAMIC(CStopwatchDlg)

public:
	CStopwatchDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CStopwatchDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STOPWATCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CButton m_LButton;
	CButton m_RButton;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonRight();
	// 0.01��
	int m_mmsec;
	int m_sec;
	int m_hour;
	int m_min;
	int RB_Flag;
	int nCount;
	afx_msg void OnBnClickedButtonLeft();
	int LB_Flag;
	int lap_mmsec;
	int lap_sec;
	int lap_min;
	int lap_nCount;
	int LapCount;
	typedef struct {
		int lmmsec;
		int lsec;
		int lmin;
	}LapSave;
	LapSave S[MAXLAP];
	CListBox m_LapList;
	int m_m;
};
