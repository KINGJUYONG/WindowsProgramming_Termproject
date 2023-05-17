// CTab1.cpp: 구현 파일
//

#include "pch.h"
#include "TermProject.h"
#include "CTab1.h"
#include "afxdialogex.h"

#include "resource.h"
#include <locale.h>

// CTab1 대화 상자

IMPLEMENT_DYNAMIC(CTab1, CDialogEx)

CTab1::CTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTab1, pParent)
	, m_mainVal(COleDateTime::GetCurrentTime())
{
	
}

CTab1::~CTab1()
{

}

void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_mainCal);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, m_mainVal);
	DDX_Control(pDX, IDC_LIST_TODAY, m_FirList);
	DDX_Control(pDX, IDC_LIST_PG3, m_ListSec);
}


BEGIN_MESSAGE_MAP(CTab1, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &CTab1::OnLvnItemchangedList3)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &CTab1::OnMcnSelchangeMonthcalendar1)
END_MESSAGE_MAP()

// CTab1 메시지 처리기

UINT CTab1::TimeThread(LPVOID _mothod)
{
	CTab1* tk = (CTab1*)_mothod;
	CString ind, timeset, whatday;
	int YY, MM, DD;
	CStdioFile saved;
	int twice = 0;
	
		while (1) {
			CTime cTime = CTime::GetCurrentTime();
			int i = 0, k = 0, f = 0, s = 0;
			int plzslt = 0;
			int plzcho = 0;
			setlocale(LC_ALL, "Korean");
			BOOL ss = saved.Open(_T(".\\keepwrite.txt"), CStdioFile::modeRead | CFile::shareDenyNone);
			if (ss) {
				while (saved.ReadString(ind)) {
					YY = cTime.GetYear();
					MM = cTime.GetMonth();
					DD = cTime.GetDay();
					timeset.Format(L"%04d-%02d-%02d", YY, MM, DD);
					BOOL corr = timeset.Compare(ind);

					whatday.Format(_T("%04d-%02d-%02d"), tk->m_mainVal.GetYear(), tk->m_mainVal.GetMonth(), tk->m_mainVal.GetDay());
					BOOL what = whatday.Compare(ind);

					if (!corr) {
						plzslt = 4;
					}
					if (plzslt > 0) {
						if (i == 0) {
							tk->m_FirList.InsertItem(k, ind);
						}
						else {
							tk->m_FirList.SetItemText(k, i, ind);
						}
						i = i + 1;
						if (i == 4) {
							i = 0;
							k += 1;
							plzslt = 0;
						}
						plzslt--;
					}

					if (!what) {
						plzcho = 4;
					}
					if (plzcho > 0) {
						if (f == 0) {
							tk->m_ListSec.InsertItem(s, ind);
						}
						else {
							tk->m_ListSec.SetItemText(s, f, ind);
						}
						f = f + 1;
						if (f == 4) {
							f = 0;
							s += 1;
							plzcho = 0;
						}
						plzcho--;
					}
				}
				saved.Close();
			}

			CString dow, fir, sec, thi;
			int tod = cTime.GetDayOfWeek();
			while (1) {
				if (tod == 1) { dow = "월"; break; }
				else if (tod == 2) { dow = "화"; break; }
				else if (tod == 3) { dow = "수"; break; }
				else if (tod == 4) { dow = "목"; break; }
				else if (tod == 5) { dow = "금"; break; }
				else if (tod == 6) { dow = "토"; break; }
				else if (tod == 7) { dow = "일"; break; }
			}
			tk->m_Today.Format(L"오늘은 %04d년 %02d월 %02d일 %s요일", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), dow);
			tk->m_CurrentTime.Format(L"지금 시각은 %02d시 %02d분 %02d초 입니다", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
			tk->SetDlgItemText(IDC_STATIC_DAY, tk->m_Today);
			tk->SetDlgItemText(IDC_STATIC_TIME, tk->m_CurrentTime);

			Sleep(1000);
			tk->m_FirList.DeleteAllItems();
			tk->m_ListSec.DeleteAllItems();
	}
		return 0;
}

BOOL CTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	setlocale(LC_ALL, "Korean"); // 언어 설정

	CWinThread* T = NULL; // 생성자에 스레드를 호출하여 생성과 동시에 스레드가 작동할 수 있도록 합니다.
	T = AfxBeginThread(TimeThread, this);

	m_FirList.InsertColumn(0, _T("날짜"), LVCFMT_LEFT, 75);
	m_FirList.InsertColumn(1, _T("시간"), LVCFMT_LEFT, 65);
	m_FirList.InsertColumn(2, _T("이벤트 이름"), LVCFMT_LEFT, 70);
	m_FirList.InsertColumn(3, _T("남은 시간"), LVCFMT_LEFT, 165);
	m_ListSec.InsertColumn(0, _T("날짜"), LVCFMT_LEFT, 75);
	m_ListSec.InsertColumn(1, _T("시간"), LVCFMT_LEFT, 65);
	m_ListSec.InsertColumn(2, _T("이벤트 이름"), LVCFMT_LEFT, 70);
	m_ListSec.InsertColumn(3, _T("남은 시간"), LVCFMT_LEFT, 165);

	CFont m_font;

	m_font.CreatePointFont(100, _T("굴림"));
	GetDlgItem(IDC_STATIC_DAY)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_TIME)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_TODAY)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_TOMORROW)->SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTab1::OnLvnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CTab1::OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData();
	CString str;
	str.Format(_T("%d년 %d월 %d일의 이벤트"), m_mainVal.GetYear(),  m_mainVal.GetMonth(), m_mainVal.GetDay());
	GetDlgItem(IDC_STATIC_TOMORROW)->SetWindowTextW(str);
	UpdateData(FALSE);

	*pResult = 0;
}