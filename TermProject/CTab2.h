#pragma once
#include "CTab1.h"
#include "CTab3.h"

// CTab2 대화 상자

static class CTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab2)

public:
	CTab2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CTab2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_add;
	COleDateTime m_DateCal;
	CDateTimeCtrl m_pickCtrl;
	CMonthCalCtrl m_CalCtrl;
	COleDateTime m_pickVal;
	CListCtrl m_List;
	CEdit m_Event;
	afx_msg void OnBnClickedButtonAdd();
	virtual BOOL OnInitDialog();

	CDateTimeCtrl m_pickCtrlT;
	COleDateTime m_pickValT;
	static UINT TimeThread(LPVOID _method);
	int indexofFor = 0;

	CButton m_RmButton;
	afx_msg void OnBnClickedButtonRem();
	afx_msg void OnBnClickedButtonFix();
	afx_msg void OnDtnDatetimechangeDatetimepickerDate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonFin();
};
