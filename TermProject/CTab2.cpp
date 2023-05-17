// CTab2.cpp: 구현 파일
//

#include "pch.h"
#include "TermProject.h"
#include "CTab2.h"
#include "afxdialogex.h"
#include <locale.h>

// CTab2 대화 상자
IMPLEMENT_DYNAMIC(CTab2, CDialogEx)

CTab2::CTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTab2, pParent)
	, m_add(_T(""))
	, m_DateCal(COleDateTime::GetCurrentTime())
	, m_pickVal(COleDateTime::GetCurrentTime())
	, m_pickValT(COleDateTime::GetCurrentTime())
{

}

CTab2::~CTab2()
{
}

void CTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EVENT, m_add);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR_PG2, m_DateCal);
	//  DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_DatePick);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DATE, m_pickCtrl);
	DDX_Control(pDX, IDC_MONTHCALENDAR_PG2, m_CalCtrl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATE, m_pickVal);
	DDX_Control(pDX, IDC_LIST_PG2, m_List);
	DDX_Control(pDX, IDC_EDIT_EVENT, m_Event);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TIME, m_pickCtrlT);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TIME, m_pickValT);
	DDX_Control(pDX, IDC_BUTTON_REM, m_RmButton);
}

BEGIN_MESSAGE_MAP(CTab2, CDialogEx)
	//ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &CTab2::OnMcnSelchangeMonthcalendar1)
	//ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CTab2::OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CTab2::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_REM, &CTab2::OnBnClickedButtonRem)
	ON_BN_CLICKED(IDC_BUTTON_FIX, &CTab2::OnBnClickedButtonFix)
	ON_WM_ENDSESSION()
	ON_WM_CLOSE()
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_DATE, &CTab2::OnDtnDatetimechangeDatetimepickerDate)
	ON_BN_CLICKED(IDC_BUTTON_FIN, &CTab2::OnBnClickedButtonFin)
END_MESSAGE_MAP()

// CTab2 메시지 처리기
BOOL CTab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	
	CWinThread* T = NULL; // 생성자에 스레드를 호출하여 생성과 동시에 스레드가 작동할 수 있도록 합니다.
	T = AfxBeginThread(TimeThread, this);

	setlocale(LC_ALL, "Korean"); // 언어 설정

	CTime inittime(2022, 01, 01, 0, 0, 0);
	m_pickCtrlT.SetTime(&inittime);

	m_List.InsertColumn(0, _T("날짜"), LVCFMT_LEFT, 75);
	m_List.InsertColumn(1, _T("시간"), LVCFMT_LEFT, 65);
	m_List.InsertColumn(2, _T("이벤트 이름"), LVCFMT_LEFT, 70);
	m_List.InsertColumn(3, _T("남은 시간"), LVCFMT_LEFT, 165);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

UINT CTab2::TimeThread(LPVOID _mothod)
{
	CTab2* ti = (CTab2*)_mothod;
	CStdioFile file, save, keep, load;
	CString saved, result, ind, FinTime;

	int sleep = 0;
	while (1)
	{
		CTime cTime = CTime::GetCurrentTime();

		if (sleep == 1) {
			int first = 0, second = 0;
			setlocale(LC_ALL, "Korean");
			ti->m_List.DeleteAllItems();
			BOOL ss = load.Open(_T(".\\keepwrite.txt"), CStdioFile::modeRead | CFile::shareDenyNone);
			if (ss) {
				while (load.ReadString(ind)) {
					if (ind == "") {
					}
					else {
						if (first == 0) {
							ti->m_List.InsertItem(second, ind);
						}
						else {
							ti->m_List.SetItemText(second, first, ind);
						}
						first = first + 1;
						if (first == 4) {
							first = 0;
							second += 1;
						}
					}
				}
				load.Close();
			}
		}
		sleep += 1;
		for (int k = 0; k < ti->indexofFor + 1; k++) {

			CString TD, DATE, TIME, Year, Month, Day, Hour, Min, Sec, Message, GetString;
			int tmp = 0, num = 0, sum = 0, Yeartmp = 0, Monthtmp = 0, Daytmp = 0, Hourtmp = 0, Mintmp = 0, Sectmp = 0;

			DATE = ti->m_List.GetItemText(k, 0);
			TIME = ti->m_List.GetItemText(k, 1);

			Year = DATE.Left(4);
			Month = DATE.Mid(5, 2);
			Day = DATE.Right(2);

			Hour = TIME.Left(2);
			Min = TIME.Mid(3, 2);
			Sec = TIME.Right(2);

			if (sleep > 1) {
				tmp = _ttoi(Year); // year를 int형으로
				num = tmp - cTime.GetYear(); // 연산결과를 num에 저장
				sum += num * 60 * 60 * 24 * 365;
				tmp = _ttoi(Month);
				num = tmp - cTime.GetMonth();
				sum += num * 60 * 60 * 24 * 30;
				tmp = _ttoi(Day);
				num = tmp - cTime.GetDay();
				sum += num * 60 * 60 * 24;
				tmp = _ttoi(Hour);
				num = tmp - cTime.GetHour();
				sum += num * 60 * 60;
				tmp = _ttoi(Min);
				num = tmp - cTime.GetMinute();
				sum += num * 60;
				tmp = _ttoi(Sec);
				num = tmp - cTime.GetSecond();
				sum += num;
			}

			Yeartmp = sum / (60 * 60 * 24 * 365);
			Monthtmp = (sum % (60 * 60 * 24 * 365)) / (60 * 60 * 24 * 30);
			Daytmp = (sum % (60 * 60 * 24 * 30)) / (60 * 60 * 24);
			Hourtmp = (sum % (60 * 60 * 24)) / (60 * 60);
			Mintmp = (sum % (60 * 60)) / 60;
			Sectmp = sum % 60;

			if (Yeartmp > 0) {
				TD.Format(_T("%d년 %d월 %d일 %d시간 %d분 %d초 남았습니다."), Yeartmp, Monthtmp, Daytmp, Hourtmp, Mintmp, Sectmp);
				ti->m_List.SetItemText(k, 3, TD);
			}
			else if (Monthtmp > 0) {
				TD.Format(_T("%d월 %d일 %d시간 %d분 %d초 남았습니다."), Monthtmp, Daytmp, Hourtmp, Mintmp, Sectmp);
				ti->m_List.SetItemText(k, 3, TD);
			}
			else if (Daytmp > 0) {
				TD.Format(_T("%d일 %d시간 %d분 %d초 남았습니다."), Daytmp, Hourtmp, Mintmp, Sectmp);
				ti->m_List.SetItemText(k, 3, TD);
			}
			else if (Hourtmp > 0) {
				TD.Format(_T("%d시간 %d분 %d초 남았습니다."), Hourtmp, Mintmp, Sectmp);
				ti->m_List.SetItemText(k, 3, TD);
			}
			else if (Mintmp > 0) {
				TD.Format(_T("%d분 %d초 남았습니다."), Mintmp, Sectmp);
				ti->m_List.SetItemText(k, 3, TD);
			}
			else if (Sectmp > 0) {
				TD.Format(_T("%d초 남았습니다."), Sectmp);
				ti->m_List.SetItemText(k, 3, TD);
			}
			else {
				BOOL bOpen = file.Open(_T(".\\finished.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeWrite | CFile::shareDenyWrite);
				if (!bOpen) {
					AfxMessageBox(_T("파일 열기 실패"));
				}
				else {
					file.SeekToEnd();
				}
				for (int i = 0; i < 3; i++) {
					GetString.Format(L"%s\n", ti->m_List.GetItemText(k, i));
					file.WriteString(GetString);
					if (i == 2) {
						FinTime.Format(L"%04d-%02d-%02d %02d:%02d:%02d\n", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
						file.WriteString(FinTime);
					}
				}
				Message.Format(_T("%s 이벤트가 종료되었습니다 !"), ti->m_List.GetItemText(k, 2));
				AfxMessageBox(Message);

				file.Close();
				ti->m_List.DeleteItem(k);
			}

			remove(".\\keepwrite.txt");
			BOOL keeps = keep.Open(_T(".\\keepwrite.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeWrite | CFile::shareDenyWrite);
			if (!keeps) {
				AfxMessageBox(_T("파일 열기 실패"));
			}
			else {
				for (int k = 0; k < ti->indexofFor + 1; k++) {
					for (int i = 0; i < 4; i++) {
						result.Format(L"%s\n", ti->m_List.GetItemText(k, i));
						keep.WriteString(result);
					}
				}
			}
			keep.Close();
		}
		Sleep(500);
	}
	return 0;
}

void CTab2::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString GET;
	CStdioFile fileadd;

	BOOL bOpen = fileadd.Open(_T(".\\added.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeWrite | CFile::shareDenyWrite);
	if (!bOpen) {
		AfxMessageBox(_T("파일 열기 실패"));
	}
	else {
		fileadd.SeekToEnd();
	}
	
	UpdateData(TRUE);

	CString DATE, TIME, NAME = _T("");

	CTime adddate, addtime;
	m_pickCtrl.GetTime(adddate);
	m_pickCtrlT.GetTime(addtime);

	DATE.Format(L"%04d-%02d-%02d", adddate.GetYear(), adddate.GetMonth(), adddate.GetDay());
	TIME.Format(L"%02d:%02d:%02d", addtime.GetHour(), addtime.GetMinute(), addtime.GetSecond());
	m_Event.GetWindowTextW(NAME);

	m_List.InsertItem(0, DATE);
	m_List.SetItemText(0, 1, TIME);
	m_List.SetItemText(0, 2, NAME);

	for (int i = 0; i < 3; i++) {
		GET.Format(L"%s\n", m_List.GetItemText(0, i));
		fileadd.WriteString(GET);
	}

	indexofFor++;

	m_add.SetString(_T(""));

	fileadd.Close();
	UpdateData(FALSE);
	AfxMessageBox(_T("추가가 정상적으로 처리되었습니다."));
}


void CTab2::OnBnClickedButtonFix()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString DATE, TIME, NAME = _T("");
	CTime adddate, addtime;

	m_pickCtrl.GetTime(adddate);
	m_pickCtrlT.GetTime(addtime);

	DATE.Format(L"%04d-%02d-%02d", adddate.GetYear(), adddate.GetMonth(), adddate.GetDay());
	TIME.Format(L"%02d:%02d:%02d", addtime.GetHour(), addtime.GetMinute(), addtime.GetSecond());
	m_Event.GetWindowTextW(NAME);

	int nItem;
	POSITION pos;
	pos = m_List.GetFirstSelectedItemPosition();
	nItem = m_List.GetNextSelectedItem(pos);
	m_List.DeleteItem(nItem);

	m_List.InsertItem(nItem, DATE);
	m_List.SetItemText(nItem, 1, TIME);
	m_List.SetItemText(nItem, 2, NAME);


	m_add.SetString(_T(""));

	UpdateData(FALSE);
	AfxMessageBox(_T("수정이 정상적으로 처리되었습니다."));
}

void CTab2::OnBnClickedButtonFin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString GET, FinTime;
	CStdioFile FileFin;

	CTime currenttime = CTime::GetCurrentTime();
	BOOL bOpen = FileFin.Open(_T(".\\finished.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeWrite | CFile::shareDenyWrite);
	if (!bOpen) {
		AfxMessageBox(_T("파일 열기 실패"));
	}
	else {
		FileFin.SeekToEnd();
	}

	int nItem;
	POSITION pos;
	pos = m_List.GetFirstSelectedItemPosition();
	while (pos != NULL)
	{
		nItem = m_List.GetNextSelectedItem(pos);
		for (int i = 0; i < 3; i++) {
			GET.Format(L"%s\n", m_List.GetItemText(nItem, i));
			FileFin.WriteString(GET);
			if (i == 2) {
				FinTime.Format(L"%04d-%02d-%02d %02d:%02d:%02d\n", currenttime.GetYear(), currenttime.GetMonth(), currenttime.GetDay(), currenttime.GetHour(), currenttime.GetMinute(), currenttime.GetSecond());
				FileFin.WriteString(FinTime);
			}
		}
		m_List.DeleteItem(nItem);
		pos = m_List.GetFirstSelectedItemPosition();
	}

	m_add.SetString(_T(""));
	FileFin.Close();

	AfxMessageBox(_T("완료가 정상적으로 처리되었습니다."));

}

void CTab2::OnBnClickedButtonRem()
{
	CString GET, RemTime;
	CStdioFile filerem;
	CTime currenttime = CTime::GetCurrentTime();

	BOOL bOpen = filerem.Open(_T(".\\removed.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeWrite | CFile::shareDenyWrite);
	if (!bOpen) {
		AfxMessageBox(_T("파일 열기 실패"));
	}
	else {
		filerem.SeekToEnd();
	}

	int nItem;
	POSITION pos;
	pos = m_List.GetFirstSelectedItemPosition();
	while (pos != NULL)
	{
		nItem = m_List.GetNextSelectedItem(pos);
		for (int i = 0; i < 3; i++) {
			GET.Format(L"%s\n", m_List.GetItemText(nItem, i));
			filerem.WriteString(GET);
			if (i == 2) {
				RemTime.Format(L"%04d-%02d-%02d %02d:%02d:%02d\n", currenttime.GetYear(), currenttime.GetMonth(), currenttime.GetDay(), currenttime.GetHour(), currenttime.GetMinute(), currenttime.GetSecond());
				filerem.WriteString(RemTime);
			}
		}
		m_List.DeleteItem(nItem);
		pos = m_List.GetFirstSelectedItemPosition();
	}

	m_add.SetString(_T(""));
	filerem.Close();
	AfxMessageBox(_T("삭제가 정상적으로 처리되었습니다."));
}


void CTab2::OnDtnDatetimechangeDatetimepickerDate(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CTime sel;

	m_pickCtrl.GetTime(sel);

	CTime myTime(sel.GetYear(), sel.GetMonth(), sel.GetDay(), 0, 0, 0);

	CMonthCalCtrl* pCalendar = (CMonthCalCtrl*)GetDlgItem(IDC_MONTHCALENDAR_PG2);
	pCalendar->SetCurSel(myTime);

	*pResult = 0;
}

