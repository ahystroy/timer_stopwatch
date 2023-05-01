// TimerEndDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TimerStopwatch.h"
#include "TimerEndDlg.h"
#include "afxdialogex.h"

// CTimerEndDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTimerEndDlg, CDialog)

CTimerEndDlg::CTimerEndDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_END, pParent)
{
	
}

CTimerEndDlg::~CTimerEndDlg()
{
}

void CTimerEndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTimerEndDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CTimerEndDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTimerEndDlg 메시지 처리기입니다.


void CTimerEndDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	

	CDialog::OnOK();
}
