// TimerEndDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TimerStopwatch.h"
#include "TimerEndDlg.h"
#include "afxdialogex.h"

// CTimerEndDlg ��ȭ �����Դϴ�.

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


// CTimerEndDlg �޽��� ó�����Դϴ�.


void CTimerEndDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	

	CDialog::OnOK();
}
