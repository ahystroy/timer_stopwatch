
// TimerStopwatch.h : TimerStopwatch ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CTimerStopwatchApp:
// �� Ŭ������ ������ ���ؼ��� TimerStopwatch.cpp�� �����Ͻʽÿ�.
//

class CTimerStopwatchApp : public CWinApp
{
public:
	CTimerStopwatchApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTimerStopwatchApp theApp;
