#pragma once


// CCurTimeSettingDlg 대화 상자입니다.

class CCurTimeSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CCurTimeSettingDlg)

public:
	CCurTimeSettingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCurTimeSettingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CURTIMESETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_ampm;
	int m_curH;
	int m_curM;
};
