
// TimerStopwatchView.cpp : CTimerStopwatchView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "TimerStopwatch.h"
#endif

#include "TimerStopwatchDoc.h"
#include "TimerStopwatchView.h"

#include "TimeSettingDlg.h" // 시간 설정 대화상자에서 시간을 입력받기 위해
#include "CurTimeSettingDlg.h" // 현재 시간 설정 대화상자
#include <time.h> // 시간 불러오기
#include <math.h> // sin, cos
#define PI 3.141592

#include "StopwatchDlg.h" // 스톱워치
#include "Clock.h" // 시계

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTimerStopwatchView

IMPLEMENT_DYNCREATE(CTimerStopwatchView, CView)

BEGIN_MESSAGE_MAP(CTimerStopwatchView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_TIMER_TIMESETTING, &CTimerStopwatchView::OnTimerTimesetting)
	ON_WM_CREATE()
	ON_BN_CLICKED(101, &OnStartButtonClicked)
	ON_BN_CLICKED(102, &OnCancelButtonClicked)
	ON_WM_TIMER()
	ON_COMMAND(ID_STOPWATCH_OPENSTOPWATCH, &CTimerStopwatchView::OnStopwatchOpenstopwatch)
	ON_COMMAND(ID_TIMER_CURRENTTIMESETTING, &CTimerStopwatchView::OnTimerCurrenttimesetting)
	ON_COMMAND(ID_CLOCK_OPENCLOCK, &CTimerStopwatchView::OnClockOpenclock)
END_MESSAGE_MAP()

// CTimerStopwatchView 생성/소멸

CTimerStopwatchView::CTimerStopwatchView()
	: m_hour(0)
	, m_min(0)
	, m_sec(0)
	, ncount(0)
	, m_timerHour(0)
	, m_timerMin(0)
	, m_timerSec(0)
	, start_Flag(0)
	, finish_Flag(0)
	, m_TimerCount(0)
	, m_TimerAngle(0)
	, CurAngle(0)
	, m_curH(0)
	, m_curM(0)
	, m_ampm(0)
	, curtime_flag(0)
	, m_CurAngle(360)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTimerStopwatchView::~CTimerStopwatchView()
{
}

BOOL CTimerStopwatchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTimerStopwatchView 그리기

void CTimerStopwatchView::OnDraw(CDC* pDC)
{
	CTimerStopwatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	/* Timer */
	// 문자열 설정
	CString str, finish, curTime, ampm;
	finish = _T("TIMER END");
	str.Format(_T("%02d:%02d:%02d"), m_hour, m_min, m_sec);

	// 현재시간 설정
	
	if (curtime_flag == 0) {
		time_t t = time(NULL);
		tm tm;
		localtime_s(&tm, &t);
		if (tm.tm_hour > 12) {
			tm.tm_hour = tm.tm_hour - 12;
			ampm = _T("PM");
		}
		else ampm = _T("AM");
		curTime.Format(_T("%02d:%02d  %s"), tm.tm_hour, tm.tm_min, ampm);
	}
	else {
		if (m_ampm == 0) ampm = _T("AM");
		else ampm = _T("PM");
		curTime.Format(_T("%02d:%02d  %s"), m_curH, m_curM, ampm);
	}

	// 폰트 설정
	CFont TimerFont, ClockFont, EndFont;
	TimerFont.CreateFont(70, //가로세로크기
		0, 0, 0, //기울어짐 각도
		FW_DONTCARE, //폰트의 굵기
		FALSE, //이탤릭플러그
		FALSE, //언더라인플러그
		FALSE, //STRIKEOUT 플러그
		DEFAULT_CHARSET, //CHAR SET 
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		_T("Arial"));
	ClockFont.CreateFont(30, //가로세로크기
		0, 0, 0, //기울어짐 각도
		FW_BOLD, //폰트의 굵기
		FALSE, //이탤릭플러그
		FALSE, //언더라인플러그
		FALSE, //STRIKEOUT 플러그
		DEFAULT_CHARSET, //CHAR SET 
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		_T("Arial"));
	EndFont.CreateFont(70, //가로세로크기
		0, 0, 0, //기울어짐 각도
		FW_BOLD, //폰트의 굵기
		FALSE, //이탤릭플러그
		FALSE, //언더라인플러그
		FALSE, //STRIKEOUT 플러그
		DEFAULT_CHARSET, //CHAR SET 
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		_T("Arial"));

	// dc setting
	CClientDC dc(this);
	dc.SetTextAlign(TA_CENTER);
	// 타이머 표기
	dc.SelectObject(&TimerFont);
	dc.TextOutW(325, 230, str);
	// 현재 시간 표기
	dc.SelectObject(&ClockFont);
	dc.TextOutW(325, 305, curTime);

	// 펜 세팅
	CPen blackPen, orangePen, TimePen, ltgrayPen;
	blackPen.CreatePen(PS_SOLID, 15, RGB(0, 0, 0));
	orangePen.CreatePen(PS_SOLID, 12, RGB(255, 127, 0));
	TimePen.CreatePen(PS_SOLID, 12, RGB(0, 0, 0));
	ltgrayPen.CreatePen(PS_SOLID, 1, RGB(211, 211, 211));
	// 브러쉬 세팅
	CBrush timerBrush, innerBrush;
	timerBrush.CreateStockObject(LTGRAY_BRUSH);
	innerBrush.CreateStockObject(LTGRAY_BRUSH);

	// Rect 설정
	CRect border(50, 50, 600, 600);
	CRect TimerRect(125, 75, 525, 475);
	CPoint center(TimerRect.CenterPoint().x, TimerRect.CenterPoint().y);

	// 타이머 테두리 그리기
	CPen *pOldPen;
	pOldPen = pDC->SelectObject(&blackPen);
	pDC->Rectangle(&border);
	pDC->SelectObject(pOldPen);
	blackPen.DeleteObject();
	// 타이머 브러쉬 그리기
	CBrush *pOldBrush;
	pOldBrush = pDC->SelectObject(&timerBrush);
	pDC->Rectangle(&border);
	pDC->SelectObject(pOldBrush);
	timerBrush.DeleteObject();
	// 타이머 원형 바 그리기
	pOldPen = pDC->SelectObject(&orangePen);
	pDC->Ellipse(&TimerRect);
	pDC->SelectObject(pOldPen);
	orangePen.DeleteObject();

	// 시간이 흐를수록 원형바가 줄어드는 동작
	if (CurAngle != 0) {
		double endX, endY;
		double rad_angle = (double)m_CurAngle*(PI / 180);
		endX = center.x + (200 * cos(rad_angle - (PI / 2)));
		endY = center.y + (200 * sin(rad_angle - (PI / 2)));
		CPen black_Pen;
		black_Pen.CreatePen(PS_SOLID, 16, RGB(192, 192, 192));
		pOldPen = pDC->SelectObject(&black_Pen);
		pDC->Pie(&TimerRect, CPoint(center.x, TimerRect.top), CPoint(endX, endY));
		pDC->SelectObject(pOldPen);
		black_Pen.DeleteObject();
	}

	// 안쪽 회색으로 채우기
	pOldPen = pDC->SelectObject(&ltgrayPen);
	pDC->Ellipse(130, 80, 520, 470);
	pDC->SelectObject(pOldPen);
	ltgrayPen.DeleteObject();

	if (finish_Flag) { // 타이머 끝남
		dc.SelectObject(&EndFont);
		dc.TextOutW(325, 230, finish);
		MessageBox(_T("TIMER END!"), _T("TIMER"), MB_ICONINFORMATION);
		finish_Flag = 0;
	}
}


// CTimerStopwatchView 인쇄

BOOL CTimerStopwatchView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTimerStopwatchView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTimerStopwatchView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CTimerStopwatchView 진단

#ifdef _DEBUG
void CTimerStopwatchView::AssertValid() const
{
	CView::AssertValid();
}

void CTimerStopwatchView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTimerStopwatchDoc* CTimerStopwatchView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTimerStopwatchDoc)));
	return (CTimerStopwatchDoc*)m_pDocument;
}
#endif //_DEBUG


// CTimerStopwatchView 메시지 처리기

// 시간입력 대화상자
void CTimerStopwatchView::OnTimerTimesetting()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CTimeSettingDlg dlg;
	dlg.m_hour = m_hour;
	dlg.m_min = m_min;
	dlg.m_sec = m_sec;

	dlg.DoModal(); // 시간설정 대화상자 열림

	m_hour = dlg.m_hour;
	m_min = dlg.m_min;
	m_sec = dlg.m_sec;

	m_timerHour = m_hour;
	m_timerMin = m_min;
	m_timerSec = m_sec;
	
	m_TimerCount = dlg.m_hour * 3600 + dlg.m_min * 60 + dlg.m_sec;
	m_TimerAngle = 360.0 / (double)m_TimerCount;

	Invalidate();
}

// 버튼 생성
int CTimerStopwatchView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_StartButton.Create(_T("Start"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(375, 500, 590, 590), this, 101);
	m_CancelButton.Create(_T("Cancel"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(60, 500, 275, 590), this, 102);
	
	return 0;
}


// START, STOP 버튼
void CTimerStopwatchView::OnStartButtonClicked() // 버튼1 -> START, STOP
{
	if (start_Flag == 0) { // start flag = 0 일 때 (타이머 시작 전)
		SetTimer(1, 1000, NULL);
		m_StartButton.SetWindowText(_T("Pause")); // 시작하면 일시정지 버튼으로 변경
		start_Flag = 1; // 타이머 동작 중임을 표기
		m_StartButton.SetState(BST_UNCHECKED);
		CurAngle = 1;
	}
	else if (start_Flag) { // start flag = 1 일 때 (타이머 동작 중)
		m_StartButton.SetWindowText(_T("Resume")); // 일시정지 버튼을 누르면 시작 버튼으로 변경
		KillTimer(1);
		start_Flag = 0; // 타이머 일시정지 중 임을 표기
	}
}

// CANCEL 버튼
void CTimerStopwatchView::OnCancelButtonClicked() // 버튼2 -> 취소
{
	m_StartButton.SetWindowTextW(_T("Start"));
	KillTimer(1);
	start_Flag = 0;

	// 시간 초기화
	m_hour = m_timerHour;
	m_min = m_timerMin;
	m_sec = m_timerSec;
	m_TimerCount = m_hour * 3600 + m_min * 60 + m_sec;
	m_TimerAngle = 360.0 / (double)m_TimerCount;
	m_CurAngle = 360;
	CurAngle = 0;

	Invalidate();
}


// OnTimer
void CTimerStopwatchView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString temp, finished;
	finished.Format(_T("끝났습니다."));
	CRect rect;
	GetClientRect(&rect);

	if (nIDEvent == 1) { 
		if (m_sec >= 0) {
			m_sec--;
			m_CurAngle -= m_TimerAngle;
			if (m_sec == -1) { m_sec = 59;
				if (m_min > 0) { m_min--;
				}
				else if (m_min == 0) {
					if (m_hour > 0) {
						m_min = 59;
						m_hour--;
					}
					else if (m_hour == 0) { // 타이머 종료
						finish_Flag = 1;
						KillTimer(1);
						m_StartButton.SetWindowTextW(_T("START"));
						start_Flag = 0;
						// 시간 설정때 설정했던 시간 다시 불러옴.
						m_hour = m_timerHour;
						m_min = m_timerMin;
						m_sec = m_timerSec;
						m_CurAngle = 360;
						CurAngle = 0;
					}
				}
			}
		}
		Invalidate();
	}

	CView::OnTimer(nIDEvent);
}


// 스톱워치 열기
void CTimerStopwatchView::OnStopwatchOpenstopwatch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CStopwatchDlg swdlg;
	swdlg.DoModal();
}


// 현재시간 설정
void CTimerStopwatchView::OnTimerCurrenttimesetting()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CCurTimeSettingDlg dlg;
	dlg.m_ampm = m_ampm;
	dlg.m_curH = m_curH;
	dlg.m_curM = m_curM;

	dlg.DoModal();

	m_ampm = dlg.m_ampm;
	m_curH = dlg.m_curH;
	m_curM = dlg.m_curM;

	curtime_flag++;

	Invalidate();
}


// 시계 열기
void CTimerStopwatchView::OnClockOpenclock()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CClock dlg;
	dlg.DoModal();
}
