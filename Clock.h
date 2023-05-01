#pragma once


// CClock 대화 상자입니다.

class CClock : public CDialog
{
	DECLARE_DYNAMIC(CClock)

public:
	CClock(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CClock();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLOCK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
