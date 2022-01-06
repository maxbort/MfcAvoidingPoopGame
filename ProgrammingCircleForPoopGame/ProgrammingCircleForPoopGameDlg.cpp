
// ProgrammingCircleForPoopGameDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ProgrammingCircleForPoopGame.h"
#include "ProgrammingCircleForPoopGameDlg.h"
#include "afxdialogex.h"
#include "ProgrammingCircleForPoopGame_MAIN.h"
#include "ForFind.h"
#include "ForSign.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CProgrammingCircleForPoopGameDlg 대화 상자



CProgrammingCircleForPoopGameDlg::CProgrammingCircleForPoopGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROGRAMMINGCIRCLEFORPOOPGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProgrammingCircleForPoopGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CProgrammingCircleForPoopGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CProgrammingCircleForPoopGameDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CProgrammingCircleForPoopGameDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CProgrammingCircleForPoopGameDlg::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CProgrammingCircleForPoopGameDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON4, &CProgrammingCircleForPoopGameDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CProgrammingCircleForPoopGameDlg 메시지 처리기

BOOL CProgrammingCircleForPoopGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;
	m_list.GetClientRect(&rect);
	int r = rect.right / 2;
	m_list.InsertColumn(0, L"user", LVCFMT_CENTER, r);
	m_list.InsertColumn(1, L"score", LVCFMT_CENTER, r);

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	try {
		BOOL bOpen = m_db.OpenEx(_T("DSN=myserver;SERVER=127.0.0.1;PORT=3306;UID=root;PWD=gh3.14159;DATABASE=myserver;"), CDatabase::noOdbcDialog);
		if (bOpen)
			m_prs = new CRecordset(&m_db);
	}
	catch (CException* e) {
		e->ReportError();
	}
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CProgrammingCircleForPoopGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.



// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CProgrammingCircleForPoopGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include <vector>
#include <iostream>	
using namespace std;

void CProgrammingCircleForPoopGameDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CClientDC dc(this);
	CString id, pass;
	CString mid, mpass;
	GetDlgItemText(IDC_EDIT1, id);
	GetDlgItemText(IDC_EDIT2, pass);
	
	if (id.IsEmpty()) {
		MessageBox(L"Input ID");
		return;
	}
	if (pass.IsEmpty()) {
		MessageBox(L"Input Password");
		return;
	}
	try {
		BOOL bOpen = m_prs->Open(CRecordset::snapshot, _T("SELECT id,passwd from user"));
		if (bOpen) {
			int iRow = 1;
			BOOL blsEOF = m_prs->IsEOF();
			DWORD dwSize = m_prs->GetRowsetSize();
			if (blsEOF)
				MessageBox(L"There is no data");
			if (!blsEOF) {
				for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {
					int fieldc = m_prs->GetODBCFieldCount();
					for (int i = 0; i < fieldc-1; i++) {
						CString userid, userpass;
						m_prs->SetAbsolutePosition(iRow);
						m_prs->GetFieldValue(i, userid);
						mid.Format(userid);
						m_prs->SetAbsolutePosition(iRow);
						m_prs->GetFieldValue(i + 1, userpass);
						mpass.Format(userpass);
						if (mid == id && mpass == pass) {
							p_main = new ProgrammingCircleForPoopGame_MAIN();
							p_main->Create(IDD_DIALOG_Main, this);
							p_main->ShowWindow(SW_SHOW);
							p_main->playerid = mid;
						// 로그인 후 로그인 창 닫기 구현하기
							return;
						}
					}
					iRow++;
				}
			}
			MessageBox(L"Wrong ID or Password");
			m_prs->Close();
		}

	}
	catch (CException* e)
	{
		e->ReportError();
	}
	//((ProgrammingCircleForPoopGame_MAIN*)GetParent())->playerid = id;



}
	


void CProgrammingCircleForPoopGameDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	p_find = new ForFind();
	p_find->Create(IDD_DIALOG_ForFind, this);
	p_find->ShowWindow(SW_SHOW);

}


void CProgrammingCircleForPoopGameDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	p_sign = new ForSign();
	p_sign->Create(IDD_DIALOG_ForSign, this);
	p_sign->ShowWindow(SW_SHOW);

}



void CProgrammingCircleForPoopGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}

	else
	{
		CDialogEx::OnPaint();
	}
}

void CProgrammingCircleForPoopGameDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

void CProgrammingCircleForPoopGameDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	try {
		CString sData[2] = { L"" };
		BOOL bOpen = m_prs->Open(CRecordset::snapshot, _T("SELECT user.id,user.score FROM user order by score desc"));
		
		if (bOpen) {
			int iRow = 1;
			BOOL blsEOF = m_prs->IsEOF();
			DWORD dwSzie = m_prs->GetRowsetSize();

			if (!blsEOF) {
				for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {
					int iFieldCnt = m_prs->GetODBCFieldCount();
					for (int iCol = 0; iCol < iFieldCnt; iCol++) {
						CString sItem;
						m_prs->SetAbsolutePosition(iRow);
						m_prs->GetFieldValue(iCol, sItem);
						sData[iCol] = sItem;
					}
					int i = m_list.GetItemCount();
					m_list.InsertItem(i, sData[0], 1);
					m_list.SetItemText(i, 1, sData[1]);
					//m_list.SetItemText(i, 2, sData[2]);
					iRow++;
				}
			}
		}
	}

	catch (CException* e) {
		e->ReportError();
	}
	m_prs->Close();
}
