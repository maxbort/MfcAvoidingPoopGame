// ForFind.cpp: 구현 파일
//

#include "pch.h"
#include "ProgrammingCircleForPoopGame.h"
#include "ForFind.h"
#include "afxdialogex.h"


// ForFind 대화 상자

IMPLEMENT_DYNAMIC(ForFind, CDialog)

ForFind::ForFind(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_ForFind, pParent)
{

}

ForFind::~ForFind()
{
}

void ForFind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_namedit);
	DDX_Control(pDX, IDC_EDIT2, m_phonedit);
	DDX_Control(pDX, IDC_EDIT3, p_idedit);
	DDX_Control(pDX, IDC_EDIT4, p_namedit);
	DDX_Control(pDX, IDC_EDIT5, p_phonedit);
}


BEGIN_MESSAGE_MAP(ForFind, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, &ForFind::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ForFind::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &ForFind::OnBnClickedButton6)
END_MESSAGE_MAP()


// ForFind 메시지 처리기


void ForFind::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str1; // 입력칸 이름
	CString str2; // 비교할 이름
	CString str3; //입력칸 핸드폰 번호
	CString str4; //비교할 핸드폰 번호
	CString str5; //아이디를 얻을 공간
	int pass = 0;
	m_namedit.GetWindowTextW(str1);
	m_phonedit.GetWindowTextW(str3);
	if (str1.IsEmpty()) {
		MessageBox(L"Input ID");
		return;
	}
	else if (str3.IsEmpty()) {
		MessageBox(L"Input PhoneNumber");
		return;
	}
	try {
		BOOL bOpen = m_db.OpenEx(_T("DSN=myserver;SERVER=127.0.0.1;PORT=3306;UID=root;PWD=gh3.14159;DATABASE=myserver;"), CDatabase::noOdbcDialog);
		if (bOpen)
			m_prs = new CRecordset(&m_db);
	}
	catch (CException* e) {
		e->ReportError();
	}
	//아이디 찾기를 위해 저장할 변수: 이름 / 핸드폰 번호

	m_prs->Open(CRecordset::snapshot, _T("SELECT * FROM user"));
	
	
	while (!m_prs->IsEOF()) {
		m_prs->GetFieldValue(short(3), str2);
		m_prs->GetFieldValue(short(4), str4);
		if (str1 == str2 && str3 == str4) {
			m_namedit.SetWindowTextW(L"");
			m_phonedit.SetWindowTextW(L"");
			m_prs->GetFieldValue(short(1), str5);
			MessageBox(L"아이디는 " + str5 + L" 입니다.");

			pass = 1;
		}
		m_prs->MoveNext();
	}
	//회원정보가 없는 경우
	if (pass == 0) {
		m_namedit.SetWindowTextW(L"");
		m_phonedit.SetWindowTextW(L"");
		MessageBox(L"등록되지 않은 회원정보입니다.");

	}
	m_prs->Close();
	m_db.Close();
}



void ForFind::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//레코드셋 객체 생성
	CString str1; // 입력칸 id
	CString str2; // 비교할 id
	CString str3; //입력칸 이름
	CString str4; //비교할 이름
	CString str5; //입력칸 폰번호
	CString str6; //비교할 폰번호
	CString str7; //비밀번호를 얻을 공간

	int pass = 0;
	p_idedit.GetWindowTextW(str1);
	p_namedit.GetWindowTextW(str3);
	p_phonedit.GetWindowTextW(str5);

	if (str1.IsEmpty()) {
		MessageBox(L"Input ID");
		return;
	}
	else if (str3.IsEmpty()) {
		MessageBox(L"Input Name");
		return;
	}
	else if (str5.IsEmpty()) {
		MessageBox(L"Input PhoneNumber");
		return;
	}


	try {
		BOOL bOpen = m_db.OpenEx(_T("DSN=myserver;SERVER=127.0.0.1;PORT=3306;UID=root;PWD=gh3.14159;DATABASE=myserver;"), CDatabase::noOdbcDialog);
		if (bOpen)
			m_prs = new CRecordset(&m_db);
	}
	catch (CException* e) {
		e->ReportError();
	}
	m_prs->Open(CRecordset::snapshot, _T("SELECT * FROM user"));
	while (!m_prs->IsEOF()) {
		m_prs->GetFieldValue(short(1), str2);
		m_prs->GetFieldValue(short(3), str4);
		m_prs->GetFieldValue(short(4), str6);

		if (str1 == str2 && str3 == str4 && str5 == str6) {
			p_idedit.SetWindowTextW(L"");
			p_namedit.SetWindowTextW(L"");
			p_phonedit.SetWindowTextW(L"");
			m_prs->GetFieldValue(short(2), str7);
			MessageBox(L"비밀번호는 " + str7 + L" 입니다.");
			pass = 1;
		}
		m_prs->MoveNext();
	}
	//회원정보가 없는 경우
	if (pass == 0) {
		p_idedit.SetWindowTextW(L"");
		p_namedit.SetWindowTextW(L"");
		p_phonedit.SetWindowTextW(L"");
		MessageBox(L"등록되지 않은 회원정보입니다.");
	}
	m_prs->Close();
	m_db.Close();
}


void ForFind::OnBnClickedButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(IDD_DIALOG_ForFind);
}
