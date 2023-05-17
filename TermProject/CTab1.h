#pragma once

#include "CTab2.h"
#include "CTab3.h"

// CTab1 대화 상자

class CTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab1)

public:
	CTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab1();




// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CTab1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_CurrentTime;
	CString m_Today;
	static UINT TimeThread(LPVOID _method);

	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);
	CMonthCalCtrl m_mainCal;
	COleDateTime m_mainVal;
	CListCtrl m_FirList;


	CListCtrl m_ListSec;
};
