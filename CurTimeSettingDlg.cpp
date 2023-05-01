// CurTimeSettingDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TimerStopwatch.h"
#include "CurTimeSettingDlg.h"
#include "afxdialogex.h"


// CCurTimeSettingDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCurTimeSettingDlg, CDialog)

CCurTimeSettingDlg::CCurTimeSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_CURTIMESETTING, pParent)
	, m_ampm(0)
	, m_curH(0)
	, m_curM(0)
{

}

CCurTimeSettingDlg::~CCurTimeSettingDlg()
{
}

void CCurTimeSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_AM, m_ampm);
	DDX_Text(pDX, IDC_EDIT_CURH, m_curH);
	DDV_MinMaxInt(pDX, m_curH, 0, 12);
	DDX_Text(pDX, IDC_EDIT_CURM, m_curM);
	DDV_MinMaxInt(pDX, m_curM, 0, 59);
}


BEGIN_MESSAGE_MAP(CCurTimeSettingDlg, CDialog)
END_MESSAGE_MAP()


// CCurTimeSettingDlg �޽��� ó�����Դϴ�.
