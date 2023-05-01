// StopwatchDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TimerStopwatch.h"
#include "StopwatchDlg.h"
#include "afxdialogex.h"

#include <math.h>
#define PI 3.141592

// CStopwatchDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CStopwatchDlg, CDialog)

CStopwatchDlg::CStopwatchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_STOPWATCH, pParent)
	, m_mmsec(0)
	, m_sec(0)
	, m_hour(0)
	, m_min(0)
	, RB_Flag(0)
	, nCount(0)
	, LB_Flag(0)
	, lap_mmsec(0)
	, lap_sec(0)
	, lap_min(0)
	, lap_nCount(0)
	, LapCount(0)
	, m_m(0)
{

}

CStopwatchDlg::~CStopwatchDlg()
{
}

void CStopwatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LEFT, m_LButton);
	DDX_Control(pDX, IDC_BUTTON_RIGHT, m_RButton);
	DDX_Control(pDX, IDC_LIST_LAPTIME, m_LapList);
}


BEGIN_MESSAGE_MAP(CStopwatchDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CStopwatchDlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CStopwatchDlg::OnBnClickedButtonLeft)
END_MESSAGE_MAP()


// CStopwatchDlg 메시지 처리기입니다.


void CStopwatchDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	// 배경 설정
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(RGB(0, 0, 0));
	CBrush *pOld = dc.SelectObject(&myBrush);
	BOOL bRes = dc.PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
	dc.SelectObject(pOld);
	myBrush.DeleteObject();
					   
	// 좌표 얻기
	CRect dlgRect(50, 50, 350, 350);
	CPoint center(dlgRect.CenterPoint().x, dlgRect.CenterPoint().y);
	
	// 펜 설정
	CPen WhitePen, GrayPen, GrayPen2, *pOldPen;
	WhitePen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	GrayPen.CreatePen(PS_SOLID, 1, RGB(90,90,90));

	int angle;
	double startX, startY;
	double endX, endY;
	double rad_angle;
	
	// 30도 간격 하얀색눈금
	pOldPen = dc.SelectObject(&WhitePen);
	for (angle = 0; angle < 360; angle+=30) {
		rad_angle = angle * (PI / 180);
		startX = center.x + (150 * cos(rad_angle));
		startY = center.y + (150 * sin(rad_angle));
		endX = center.x + (132 * cos(rad_angle));
		endY = center.y + (132 * sin(rad_angle));
		dc.MoveTo(startX, startY);
		dc.LineTo(endX, endY);
	}
	dc.SelectObject(pOldPen);
	WhitePen.DeleteObject();
	// 6도 간격 회색눈금
	pOldPen = dc.SelectObject(&GrayPen);
	for (angle = 0; angle < 360; angle += 6) {
		if (angle % 30 == 0) {
			continue;
		}
		rad_angle = angle * (PI / 180);
		startX = center.x + (150 * cos(rad_angle));
		startY = center.y + (150 * sin(rad_angle));
		endX = center.x + (134 * cos(rad_angle));
		endY = center.y + (134 * sin(rad_angle));
		dc.MoveTo(startX, startY);
		dc.LineTo(endX, endY);
	}
	// 1도간격 회색눈금
	for (angle = 0; angle < 360; angle += 1) {
		if (angle % 30 == 0) {
			continue;
		}
		rad_angle = angle * (PI / 180);
		startX = center.x + (150 * cos(rad_angle));
		startY = center.y + (150 * sin(rad_angle));
		endX = center.x + (143 * cos(rad_angle));
		endY = center.y + (143 * sin(rad_angle));
		dc.MoveTo(startX, startY);
		dc.LineTo(endX, endY);
	}
	dc.SelectObject(pOldPen);
	GrayPen.DeleteObject();
	
	// 숫자 표기
	CFont NumFont, MFont, *pOldFont; // 폰트 설정
	NumFont.CreateFont(30, //가로세로크기
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
	MFont.CreateFont(15, //가로세로크기
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
	dc.SetBkColor(RGB(0, 0, 0));
	dc.SetTextColor(RGB(255, 255, 255));
	pOldFont = dc.SelectObject(&NumFont);
	double nX, nY;
	int num_t = 5;
	pOldPen = dc.SelectObject(&WhitePen);
	for (angle = -60; angle < 300; angle += 30) { // main
		rad_angle = angle*(PI / 180);
		nX = center.x + (110 * cos(rad_angle));
		nY = center.y + (110 * sin(rad_angle));
		CRect n(nX - 15, nY - 10, nX + 15, nY + 10);
		CString num;
		num.Format(_T("%d"), num_t);
		dc.DrawText(num, n, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		num_t += 5;
	}
	int num_m = 5;
	pOldFont = dc.SelectObject(&MFont);
	for (angle = -30; angle <= 270; angle += 60) { // minute
		rad_angle = angle*(PI / 180);
		nX = center.x + (30 * cos(rad_angle));
		nY = center.y-50 + (30 * sin(rad_angle));
		CRect n(nX - 10, nY - 5, nX + 10, nY + 5);
		CString num;
		num.Format(_T("%d"), num_m);
		dc.DrawText(num, n, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		num_m += 5;
	}
	dc.SelectObject(pOldPen);
	WhitePen.DeleteObject();
	dc.SelectObject(pOldFont);
	NumFont.DeleteObject();
	MFont.DeleteObject();


	// 디지털 표기
	CPoint center_(dlgRect.CenterPoint().x, dlgRect.CenterPoint().y + 55);
	CRect c(center_.x - 30, center_.y - 13, center_.x + 30, center_.y + 13);
	CFont DigitClockFont; // 폰트 설정
	DigitClockFont.CreateFont(20, //가로세로크기
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
	pOldFont = dc.SelectObject(&DigitClockFont);
	dc.SetBkColor(RGB(0, 0, 0));
	dc.SetTextColor(RGB(255, 255, 255));
	CString str;
	str.Format(_T("%02d:%02d:%d"), m_min, m_sec, m_mmsec);
	dc.DrawText(str, c, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc.SelectObject(pOldFont);
	DigitClockFont.DeleteObject();

	// 아날로그 침
	// 시침 (오랜지색)
	CPen orangePen;
	orangePen.CreatePen(PS_SOLID, 3, RGB(255, 127, 0));
	pOldPen = dc.SelectObject(&orangePen);
	double mainX, mainY;
	double swangle = nCount * 0.6;
	rad_angle = swangle*(PI / 180);
	mainX = center.x + (150 * cos(rad_angle - (PI / 2)));
	mainY = center.y + (150 * sin(rad_angle - (PI / 2)));
	dc.MoveTo(mainX, mainY);
	dc.LineTo(center.x, center.y);
	// 분침 (오랜지색)
	double minX, minY;
	double mangle = m_m * 2;
	rad_angle = mangle*(PI / 180);
	minX = center.x + (30 * cos(rad_angle - (PI / 2)));
	minY = center.y - 50 + (30 * sin(rad_angle - (PI / 2)));
	dc.MoveTo(minX, minY);
	dc.LineTo(center.x, center.y - 50);
	dc.SelectObject(pOldPen);
	orangePen.DeleteObject();

	// lap 침 (파란색)
	if (LapCount > 0) {
		CPen bluePen;
		bluePen.CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
		pOldPen = dc.SelectObject(&bluePen);
		double lapX, lapY;
		double lap_swangle = lap_nCount * 0.6;
		double lap_rad_angle = lap_swangle*(PI / 180);
		lapX = center.x + (150 * cos(lap_rad_angle - (PI / 2)));
		lapY = center.y + (150 * sin(lap_rad_angle - (PI / 2)));
		dc.MoveTo(lapX, lapY);
		dc.LineTo(center.x, center.y);
		dc.SelectObject(pOldPen);
		bluePen.DeleteObject();
	}
}


// OnTimer
void CStopwatchDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 2) {
		m_mmsec++;
		nCount++;
		if (nCount == 600) {
			nCount = 0;
		}
		if (m_mmsec == 10) {
			m_sec++;
			m_mmsec = 0;
			if (m_sec == 10) {
				m_m++;
			}
			else if (m_sec == 60) {
				m_min++;
				m_sec = 0;
			}
		}
	}
	else if (nIDEvent >= 3) {
		lap_mmsec++;
		lap_nCount++;
		if (lap_nCount == 600) {
			lap_nCount = 0;
		}
		if (lap_mmsec == 10) {
			lap_sec++;
			lap_mmsec = 0;
			if (lap_sec == 60) {
				lap_min++;
				lap_sec = 0;
			}
		}
	}
	Invalidate();
	CDialog::OnTimer(nIDEvent);
}

// 검은색 배경
BOOL CStopwatchDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return TRUE;
}


// 오른쪽 버튼 처리기
void CStopwatchDlg::OnBnClickedButtonRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (RB_Flag == 1) { // Stop
		KillTimer(2);
		if (LapCount != 0) {
			KillTimer(LapCount + 2);
		}
		m_RButton.SetWindowTextW(_T("Start"));
		RB_Flag = 0;
		m_LButton.SetWindowText(_T("Reset"));
		LB_Flag = 1; //reset
	}
	else if (RB_Flag == 0) { // Start
		SetTimer(2, 100, NULL);
		if (LapCount != 0) {
			SetTimer(LapCount + 2, 100, NULL);
		}
		m_RButton.SetWindowText(_T("Stop"));
		RB_Flag = 1;
		m_LButton.SetWindowText(_T("Lap"));
		LB_Flag = 2; //lap
	}
}

// 왼쪽 버튼
void CStopwatchDlg::OnBnClickedButtonLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (LB_Flag == 2) { // Lap
		if (LapCount == 0) { // 처음 랩 누름
			CString lapstr;
			S[LapCount].lmmsec = m_mmsec;
			S[LapCount].lsec = m_sec;
			S[LapCount].lmin = m_min;
			lapstr.Format(_T("  Lap %2d                                                                 %02d:%02d:%d  "),
				LapCount + 1, S[LapCount].lmin, S[LapCount].lsec, S[LapCount].lmmsec);
			m_LapList.AddString(lapstr);
			LapCount++;
			SetTimer(LapCount + 2, 100, NULL);
		}
		else if (LapCount != 0) { // 일반 누름
			KillTimer(LapCount + 2);
			S[LapCount].lmmsec = lap_mmsec;
			S[LapCount].lsec = lap_sec;
			S[LapCount].lmin = lap_min;
			CString lapstr;
			lapstr.Format(_T("  Lap %2d                                                                 %02d:%02d:%d  "),
				LapCount + 1, S[LapCount].lmin, S[LapCount].lsec, S[LapCount].lmmsec);
			m_LapList.AddString(lapstr);
			lap_mmsec = 0;
			lap_sec = 0;
			lap_min = 0;
			lap_nCount = 0;
			LapCount++;
			SetTimer(LapCount + 2, 100, NULL);
		}
	}
	else if (LB_Flag == 1) { // Reset
		m_LapList.ResetContent();
		m_mmsec = 0;
		m_sec = 0;
		m_min = 0;
		m_m = 0;
		nCount = 0;
		lap_mmsec = 0;
		lap_sec = 0;
		lap_min = 0;
		lap_nCount = 0;
		LapCount = 0;
		LB_Flag = 0;
		m_LButton.SetWindowText(_T("Lap"));
	}
	else if (LB_Flag == 0) {
		// 실행 안됨
	}
	Invalidate();
}