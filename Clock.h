#pragma once


// CClock ��ȭ �����Դϴ�.

class CClock : public CDialog
{
	DECLARE_DYNAMIC(CClock)

public:
	CClock(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CClock();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLOCK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	int m_sec;
	int m_min;
	int m_hour;
	int m_day;
	int m_mon;
	int m_year;
	int m_wday;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
