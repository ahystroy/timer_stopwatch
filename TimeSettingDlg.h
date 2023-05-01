#pragma once


// CTimeSettingDlg 대화 상자입니다.

class CTimeSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CTimeSettingDlg)

public:
	CTimeSettingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTimeSettingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TIMESETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_hour;
	int m_min;
	int m_sec;
};
