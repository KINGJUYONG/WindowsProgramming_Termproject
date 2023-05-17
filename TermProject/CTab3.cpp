// CTab3.cpp: 구현 파일
//

#include "pch.h"
#include "TermProject.h"
#include "CTab3.h"
#include "afxdialogex.h"


// CTab3 대화 상자

IMPLEMENT_DYNAMIC(CTab3, CDialogEx)

CTab3::CTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTab3, pParent)
{

}

CTab3::~CTab3()
{
}

void CTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REM, m_listR);
	DDX_Control(pDX, IDC_LIST_FIN, m_listF);
}


BEGIN_MESSAGE_MAP(CTab3, CDialogEx)

END_MESSAGE_MAP()


// CTab3 메시지 처리기

UINT CTab3::TimeThread(LPVOID _mothod)
{
	CTab3* ts = (CTab3*)_mothod;
	CString ind;
	int i = 0;
	CStdioFile file2, filerem;
	while (1) {
		int k = 0;
		BOOL open = file2.Open(_T(".\\finished.txt"), CStdioFile::modeRead | CFile::shareDenyNone);
		if (open) {
			while (file2.ReadString(ind)) {
				if (i == 0) {
					ts->m_listF.InsertItem(k, ind);
				}
				else {
					ts->m_listF.SetItemText(k, i, ind);
				}
				//AfxMessageBox(ind);
				i = i + 1;
				if (i == 4) {
					i = 0;
					k += 1;
				}
			}
		}
		k = 0;
		BOOL openend = filerem.Open(_T(".\\removed.txt"), CStdioFile::modeRead | CFile::shareDenyNone);
		if (openend) {
			while (filerem.ReadString(ind)) {
				if (i == 0) {
					ts->m_listR.InsertItem(k, ind);
				}
				else {
					ts->m_listR.SetItemText(k, i, ind);
				}
				i = i + 1;
				if (i == 4) {
					i = 0;
					k += 1;
				}
			}
		}
		
		file2.Close();
		filerem.Close();

		Sleep(1000);
		
		ts->m_listF.DeleteAllItems();
		ts->m_listR.DeleteAllItems();
	}
	return 0;
}

BOOL CTab3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CWinThread* T = NULL; // 생성자에 스레드를 호출하여 생성과 동시에 스레드가 작동할 수 있도록 합니다.
	T = AfxBeginThread(TimeThread, this);

	m_listR.InsertColumn(0, _T("날짜"), LVCFMT_LEFT, 75);
	m_listR.InsertColumn(1, _T("시간"), LVCFMT_LEFT, 65);
	m_listR.InsertColumn(2, _T("이벤트 이름"), LVCFMT_LEFT, 105);
	m_listR.InsertColumn(3, _T("삭제된 시간"), LVCFMT_LEFT, 130);
	m_listF.InsertColumn(0, _T("날짜"), LVCFMT_LEFT, 75);
	m_listF.InsertColumn(1, _T("시간"), LVCFMT_LEFT, 65);
	m_listF.InsertColumn(2, _T("이벤트 이름"), LVCFMT_LEFT, 105);
	m_listF.InsertColumn(3, _T("완료된 시간"), LVCFMT_LEFT, 130);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
