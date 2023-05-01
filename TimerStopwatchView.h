
// TimerStopwatchView.h : CTimerStopwatchView 클래스의 인터페이스
//

#pragma once


class CTimerStopwatchView : public CView
{
protected: // serialization에서만 만들어집니다.
	CTimerStopwatchView();
	DECLARE_DYNCREATE(CTimerStopwatchView)

// 특성입니다.
public:
	CTimerStopwatchDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CTimerStopwatchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimerTimesetting();
	int m_hour;
	int m_min;
	int m_sec;
	CButton m_StartButton;
	CButton m_CancelButton;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnStartButtonClicked();
	void OnCancelButtonClicked();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int ncount;
	// SetTimer에 들어갈 "시간" 변수
	int m_timerHour;
	// SetTimer에 들어갈 "분" 변수
	int m_timerMin;
	// SetTimer에 들어갈 "초" 변수
	int m_timerSec;
	// 시작 버튼이 눌렸는지 판별
	int start_Flag;
	// 타이머가 종료되었음을 알리는 표시
	int finish_Flag;
	afx_msg void OnStopwatchOpenstopwatch();
	// 원형바 프로그레스를 위한 변수
	int m_TimerCount;
	// 타이머 각도
	double m_TimerAngle;
	double CurAngle;
	afx_msg void OnTimerCurrenttimesetting();
	int m_curH;
	int m_curM;
	int m_ampm;
	int curtime_flag;
	afx_msg void OnClockOpenclock();
	double m_CurAngle;
};

#ifndef _DEBUG  // TimerStopwatchView.cpp의 디버그 버전
inline CTimerStopwatchDoc* CTimerStopwatchView::GetDocument() const
   { return reinterpret_cast<CTimerStopwatchDoc*>(m_pDocument); }
#endif

