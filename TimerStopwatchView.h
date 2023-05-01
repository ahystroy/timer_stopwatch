
// TimerStopwatchView.h : CTimerStopwatchView Ŭ������ �������̽�
//

#pragma once


class CTimerStopwatchView : public CView
{
protected: // serialization������ ��������ϴ�.
	CTimerStopwatchView();
	DECLARE_DYNCREATE(CTimerStopwatchView)

// Ư���Դϴ�.
public:
	CTimerStopwatchDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CTimerStopwatchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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
	// SetTimer�� �� "�ð�" ����
	int m_timerHour;
	// SetTimer�� �� "��" ����
	int m_timerMin;
	// SetTimer�� �� "��" ����
	int m_timerSec;
	// ���� ��ư�� ���ȴ��� �Ǻ�
	int start_Flag;
	// Ÿ�̸Ӱ� ����Ǿ����� �˸��� ǥ��
	int finish_Flag;
	afx_msg void OnStopwatchOpenstopwatch();
	// ������ ���α׷����� ���� ����
	int m_TimerCount;
	// Ÿ�̸� ����
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

#ifndef _DEBUG  // TimerStopwatchView.cpp�� ����� ����
inline CTimerStopwatchDoc* CTimerStopwatchView::GetDocument() const
   { return reinterpret_cast<CTimerStopwatchDoc*>(m_pDocument); }
#endif

