
// TimerStopwatchView.cpp : CTimerStopwatchView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "TimerStopwatch.h"
#endif

#include "TimerStopwatchDoc.h"
#include "TimerStopwatchView.h"

#include "TimeSettingDlg.h" // �ð� ���� ��ȭ���ڿ��� �ð��� �Է¹ޱ� ����
#include "CurTimeSettingDlg.h" // ���� �ð� ���� ��ȭ����
#include <time.h> // �ð� �ҷ�����
#include <math.h> // sin, cos
#define PI 3.141592

#include "StopwatchDlg.h" // �����ġ
#include "Clock.h" // �ð�

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTimerStopwatchView

IMPLEMENT_DYNCREATE(CTimerStopwatchView, CView)

BEGIN_MESSAGE_MAP(CTimerStopwatchView, CView)
	// ǥ�� �μ� ����Դϴ�.
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

// CTimerStopwatchView ����/�Ҹ�

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
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CTimerStopwatchView::~CTimerStopwatchView()
{
}

BOOL CTimerStopwatchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CTimerStopwatchView �׸���

void CTimerStopwatchView::OnDraw(CDC* pDC)
{
	CTimerStopwatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	/* Timer */
	// ���ڿ� ����
	CString str, finish, curTime, ampm;
	finish = _T("TIMER END");
	str.Format(_T("%02d:%02d:%02d"), m_hour, m_min, m_sec);

	// ����ð� ����
	
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

	// ��Ʈ ����
	CFont TimerFont, ClockFont, EndFont;
	TimerFont.CreateFont(70, //���μ���ũ��
		0, 0, 0, //������ ����
		FW_DONTCARE, //��Ʈ�� ����
		FALSE, //���Ÿ��÷���
		FALSE, //��������÷���
		FALSE, //STRIKEOUT �÷���
		DEFAULT_CHARSET, //CHAR SET 
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		_T("Arial"));
	ClockFont.CreateFont(30, //���μ���ũ��
		0, 0, 0, //������ ����
		FW_BOLD, //��Ʈ�� ����
		FALSE, //���Ÿ��÷���
		FALSE, //��������÷���
		FALSE, //STRIKEOUT �÷���
		DEFAULT_CHARSET, //CHAR SET 
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		_T("Arial"));
	EndFont.CreateFont(70, //���μ���ũ��
		0, 0, 0, //������ ����
		FW_BOLD, //��Ʈ�� ����
		FALSE, //���Ÿ��÷���
		FALSE, //��������÷���
		FALSE, //STRIKEOUT �÷���
		DEFAULT_CHARSET, //CHAR SET 
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		_T("Arial"));

	// dc setting
	CClientDC dc(this);
	dc.SetTextAlign(TA_CENTER);
	// Ÿ�̸� ǥ��
	dc.SelectObject(&TimerFont);
	dc.TextOutW(325, 230, str);
	// ���� �ð� ǥ��
	dc.SelectObject(&ClockFont);
	dc.TextOutW(325, 305, curTime);

	// �� ����
	CPen blackPen, orangePen, TimePen, ltgrayPen;
	blackPen.CreatePen(PS_SOLID, 15, RGB(0, 0, 0));
	orangePen.CreatePen(PS_SOLID, 12, RGB(255, 127, 0));
	TimePen.CreatePen(PS_SOLID, 12, RGB(0, 0, 0));
	ltgrayPen.CreatePen(PS_SOLID, 1, RGB(211, 211, 211));
	// �귯�� ����
	CBrush timerBrush, innerBrush;
	timerBrush.CreateStockObject(LTGRAY_BRUSH);
	innerBrush.CreateStockObject(LTGRAY_BRUSH);

	// Rect ����
	CRect border(50, 50, 600, 600);
	CRect TimerRect(125, 75, 525, 475);
	CPoint center(TimerRect.CenterPoint().x, TimerRect.CenterPoint().y);

	// Ÿ�̸� �׵θ� �׸���
	CPen *pOldPen;
	pOldPen = pDC->SelectObject(&blackPen);
	pDC->Rectangle(&border);
	pDC->SelectObject(pOldPen);
	blackPen.DeleteObject();
	// Ÿ�̸� �귯�� �׸���
	CBrush *pOldBrush;
	pOldBrush = pDC->SelectObject(&timerBrush);
	pDC->Rectangle(&border);
	pDC->SelectObject(pOldBrush);
	timerBrush.DeleteObject();
	// Ÿ�̸� ���� �� �׸���
	pOldPen = pDC->SelectObject(&orangePen);
	pDC->Ellipse(&TimerRect);
	pDC->SelectObject(pOldPen);
	orangePen.DeleteObject();

	// �ð��� �带���� �����ٰ� �پ��� ����
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

	// ���� ȸ������ ä���
	pOldPen = pDC->SelectObject(&ltgrayPen);
	pDC->Ellipse(130, 80, 520, 470);
	pDC->SelectObject(pOldPen);
	ltgrayPen.DeleteObject();

	if (finish_Flag) { // Ÿ�̸� ����
		dc.SelectObject(&EndFont);
		dc.TextOutW(325, 230, finish);
		MessageBox(_T("TIMER END!"), _T("TIMER"), MB_ICONINFORMATION);
		finish_Flag = 0;
	}
}


// CTimerStopwatchView �μ�

BOOL CTimerStopwatchView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CTimerStopwatchView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CTimerStopwatchView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CTimerStopwatchView ����

#ifdef _DEBUG
void CTimerStopwatchView::AssertValid() const
{
	CView::AssertValid();
}

void CTimerStopwatchView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTimerStopwatchDoc* CTimerStopwatchView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTimerStopwatchDoc)));
	return (CTimerStopwatchDoc*)m_pDocument;
}
#endif //_DEBUG


// CTimerStopwatchView �޽��� ó����

// �ð��Է� ��ȭ����
void CTimerStopwatchView::OnTimerTimesetting()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CTimeSettingDlg dlg;
	dlg.m_hour = m_hour;
	dlg.m_min = m_min;
	dlg.m_sec = m_sec;

	dlg.DoModal(); // �ð����� ��ȭ���� ����

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

// ��ư ����
int CTimerStopwatchView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_StartButton.Create(_T("Start"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(375, 500, 590, 590), this, 101);
	m_CancelButton.Create(_T("Cancel"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(60, 500, 275, 590), this, 102);
	
	return 0;
}


// START, STOP ��ư
void CTimerStopwatchView::OnStartButtonClicked() // ��ư1 -> START, STOP
{
	if (start_Flag == 0) { // start flag = 0 �� �� (Ÿ�̸� ���� ��)
		SetTimer(1, 1000, NULL);
		m_StartButton.SetWindowText(_T("Pause")); // �����ϸ� �Ͻ����� ��ư���� ����
		start_Flag = 1; // Ÿ�̸� ���� ������ ǥ��
		m_StartButton.SetState(BST_UNCHECKED);
		CurAngle = 1;
	}
	else if (start_Flag) { // start flag = 1 �� �� (Ÿ�̸� ���� ��)
		m_StartButton.SetWindowText(_T("Resume")); // �Ͻ����� ��ư�� ������ ���� ��ư���� ����
		KillTimer(1);
		start_Flag = 0; // Ÿ�̸� �Ͻ����� �� ���� ǥ��
	}
}

// CANCEL ��ư
void CTimerStopwatchView::OnCancelButtonClicked() // ��ư2 -> ���
{
	m_StartButton.SetWindowTextW(_T("Start"));
	KillTimer(1);
	start_Flag = 0;

	// �ð� �ʱ�ȭ
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CString temp, finished;
	finished.Format(_T("�������ϴ�."));
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
					else if (m_hour == 0) { // Ÿ�̸� ����
						finish_Flag = 1;
						KillTimer(1);
						m_StartButton.SetWindowTextW(_T("START"));
						start_Flag = 0;
						// �ð� ������ �����ߴ� �ð� �ٽ� �ҷ���.
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


// �����ġ ����
void CTimerStopwatchView::OnStopwatchOpenstopwatch()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CStopwatchDlg swdlg;
	swdlg.DoModal();
}


// ����ð� ����
void CTimerStopwatchView::OnTimerCurrenttimesetting()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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


// �ð� ����
void CTimerStopwatchView::OnClockOpenclock()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CClock dlg;
	dlg.DoModal();
}
