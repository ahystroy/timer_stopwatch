#pragma once


// CCurTimeSettingDlg ��ȭ �����Դϴ�.

class CCurTimeSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CCurTimeSettingDlg)

public:
	CCurTimeSettingDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCurTimeSettingDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CURTIMESETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_ampm;
	int m_curH;
	int m_curM;
};
