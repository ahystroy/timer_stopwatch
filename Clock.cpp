// Clock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TimerStopwatch.h"
#include "Clock.h"
#include "afxdialogex.h"

#include <time.h> // �ð� ���� ���
#define PI 3.141592

// CClock ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CClock, CDialog)

CClock::CClock(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CLOCK, pParent)
	, m_sec(0)
	, m_min(0)
	, m_hour(0)
	, m_day(0)
	, m_mon(0)
	, m_year(0)
	, m_wday(0)
{
	time_t t = time(NULL);
	tm tm;
	localtime_s(&tm, &t);
	m_sec = tm.tm_sec;
	m_min = tm.tm_min;
	m_hour = tm.tm_hour;
	m_day = tm.tm_mday;
	m_mon = tm.tm_mon + 1;
	m_year = tm.tm_year + 1900;
}

CClock::~CClock()
{
}

void CClock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CClock, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CClock �޽��� ó�����Դϴ�.


BOOL CClock::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(RGB(0, 0, 0));
	CBrush *pOld = pDC->SelectObject(&myBrush);
	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOld);
	myBrush.DeleteObject();
	return bRes;

	return CDialog::OnEraseBkgnd(pDC);
}


void CClock::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
					   // 30�� ���� �Ͼ������
	// ��ǥ ���
	CRect dlgRect(50, 50, 350, 350);
	CPoint center(dlgRect.CenterPoint().x, dlgRect.CenterPoint().y);
					   
	// �� ����
	CPen WhitePen, GrayPen, GrayPen2, *pOldPen;
	WhitePen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	GrayPen.CreatePen(PS_SOLID, 1, RGB(90, 90, 90));
	
	int angle;
	double startX, startY;
	double endX, endY;
	double rad_angle;

	// 30�� ���� ���
	pOldPen = dc.SelectObject(&WhitePen);
	for (angle = 0; angle < 360; angle += 30) {
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
	// 6�� ���� ȸ������
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
	// 1������ ȸ������
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

	// ���� ǥ��
	CFont NumFont, MFont, *pOldFont; // ��Ʈ ����
	NumFont.CreateFont(30, //���μ���ũ��
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
	dc.SetBkColor(RGB(0, 0, 0));
	dc.SetTextColor(RGB(255, 255, 255));
	pOldFont = dc.SelectObject(&NumFont);
	double nX, nY;
	int num_t = 1;
	pOldPen = dc.SelectObject(&WhitePen);
	for (angle = -60; angle < 300; angle += 30) { // main
		rad_angle = angle*(PI / 180);
		nX = center.x + (110 * cos(rad_angle));
		nY = center.y + (110 * sin(rad_angle));
		CRect n(nX - 15, nY - 10, nX + 15, nY + 10);
		CString num;
		num.Format(_T("%d"), num_t);
		dc.DrawText(num, n, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		num_t++;
	}

	// ������ ǥ��
	CPoint center_(dlgRect.CenterPoint().x, dlgRect.CenterPoint().y + 55);
	CRect c(center_.x - 100, center_.y - 13, center_.x + 100, center_.y + 13);
	CFont DigitClockFont; // ��Ʈ ����
	DigitClockFont.CreateFont(20, //���μ���ũ��
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
	pOldFont = dc.SelectObject(&DigitClockFont);
	dc.SetBkColor(RGB(0, 0, 0));
	dc.SetTextColor(RGB(255, 255, 255));
	CString str;
	str.Format(_T("%d.%2d.%2d   %02d:%02d:%02d"), m_year, m_mon, m_day, m_hour, m_min, m_sec);
	dc.DrawText(str, c, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc.SelectObject(pOldFont);
	DigitClockFont.DeleteObject();

	// �Ƴ��α� ħ
	double mainX, mainY, swangle;
	// ��ħ
	CPen whitePen;
	whitePen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	pOldPen = dc.SelectObject(&whitePen);
	swangle = m_sec * 6.0;
	rad_angle = swangle*(PI / 180);
	mainX = center.x + (75 * cos(rad_angle - (PI / 2)));
	mainY = center.y + (75 * sin(rad_angle - (PI / 2)));
	dc.MoveTo(mainX, mainY);
	dc.LineTo(center.x, center.y);
	// ��ħ
	CPen orangePen;
	orangePen.CreatePen(PS_SOLID, 3, RGB(255, 127, 0));
	pOldPen = dc.SelectObject(&orangePen);
	swangle = m_min * 6.0;
	rad_angle = swangle*(PI / 180);
	mainX = center.x + (135 * cos(rad_angle - (PI / 2)));
	mainY = center.y + (135 * sin(rad_angle - (PI / 2)));
	dc.MoveTo(mainX, mainY);
	dc.LineTo(center.x, center.y);
	// ��ħ
	swangle = (double)m_hour*(60/12) * 6 + (double)m_min/2.0;
	rad_angle = swangle*(PI / 180);
	mainX = center.x + (80 * cos(rad_angle - (PI / 2)));
	mainY = center.y + (80 * sin(rad_angle - (PI / 2)));
	dc.MoveTo(mainX, mainY);
	dc.LineTo(center.x, center.y);

	SetTimer(5, 1000, NULL);
}


void CClock::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nIDEvent == 5) {
		time_t t = time(NULL);
		tm tm;
		localtime_s(&tm, &t);
		m_sec = tm.tm_sec;
		m_min = tm.tm_min;
		m_hour = tm.tm_hour;
		if (m_hour > 12) 
			m_hour -= 12;
		m_day = tm.tm_mday;
		m_mon = tm.tm_mon + 1;
		m_year = tm.tm_year + 1900;
		Invalidate();
	}
	CDialog::OnTimer(nIDEvent);
}
