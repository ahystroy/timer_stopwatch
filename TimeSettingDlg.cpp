// TimeSettingDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TimerStopwatch.h"
#include "TimeSettingDlg.h"
#include "afxdialogex.h"


// CTimeSettingDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTimeSettingDlg, CDialog)

CTimeSettingDlg::CTimeSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_TIMESETTING, pParent)
	, m_hour(0)
	, m_min(0)
	, m_sec(0)
{

}

CTimeSettingDlg::~CTimeSettingDlg()
{
}

void CTimeSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HOUR, m_hour);
	DDV_MinMaxInt(pDX, m_hour, 0, 23);
	DDX_Text(pDX, IDC_EDIT_MINUTE, m_min);
	DDV_MinMaxInt(pDX, m_min, 0, 59);
	DDX_Text(pDX, IDC_EDIT_SECOND, m_sec);
	DDV_MinMaxInt(pDX, m_sec, 0, 59);
}


BEGIN_MESSAGE_MAP(CTimeSettingDlg, CDialog)
END_MESSAGE_MAP()


// CTimeSettingDlg 메시지 처리기입니다.
