
// TermProjectDlg.h: 헤더 파일
//

#pragma once

#include "CTab1.h"
#include "CTab2.h"
#include "CTab3.h"


// CTermProjectDlg 대화 상자
class CTermProjectDlg : public CDialogEx
{
// 생성입니다.
public:
	CTermProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TERMPROJECT_DIALOG };
#endif

	protected:

		CTab1* pDlg1;
		CTab2* pDlg2;
		CTab3* pDlg3;

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabMain;
	afx_msg void OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
};
