#pragma once
#include "afxwin.h"
#define MAXLAP 100
// CStopwatchDlg 대화 상자입니다.

class CStopwatchDlg : public CDialog
{
	DECLARE_DYNAMIC(CStopwatchDlg)

public:
	CStopwatchDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CStopwatchDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STOPWATCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CButton m_LButton;
	CButton m_RButton;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonRight();
	// 0.01초
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
