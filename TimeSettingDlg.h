#pragma once


// CTimeSettingDlg ��ȭ �����Դϴ�.

class CTimeSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CTimeSettingDlg)

public:
	CTimeSettingDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTimeSettingDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TIMESETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_hour;
	int m_min;
	int m_sec;
};
