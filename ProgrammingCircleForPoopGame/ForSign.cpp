// ForSign.cpp: 구현 파일
//

#include "pch.h"
#include "ProgrammingCircleForPoopGame.h"
#include "ForSign.h"
#include "afxdialogex.h"
#pragma comment(lib,"odbc32.lib")


// ForSign 대화 상자

IMPLEMENT_DYNAMIC(ForSign, CDialogEx)

ForSign::ForSign(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ForSign, pParent)
{

}

ForSign::~ForSign()
{
}

void ForSign::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, m_ForIdCheck, m_idcheck);
	DDX_Control(pDX, IDC_EDIT1, m_idedit);
	DDX_Control(pDX, IDC_EDIT2, m_psedit);
	DDX_Control(pDX, IDC_EDIT3, m_namedit);
	DDX_Control(pDX, IDC_EDIT4, m_pnedit);

}


BEGIN_MESSAGE_MAP(ForSign, CDialogEx)
	ON_BN_CLICKED(m_Sign, &ForSign::OnBnClickedSign)
	ON_BN_CLICKED(m_ForIdCheck, &ForSign::OnBnClickedForidcheck)
END_MESSAGE_MAP()


// ForSign 메시지 처리기


void ForSign::OnBnClickedSign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString id;
	CString passwd;
	CString name;

	int phone = 0;
	//CString sqlstr;
	m_idedit.GetWindowTextW(id);
	m_psedit.GetWindowTextW(passwd);
	m_namedit.GetWindowTextW(name);
	phone = GetDlgItemInt(IDC_EDIT4);

	//입력 칸이 모두 채워진 경우에만 실행가능한 코드
	if (id.IsEmpty() || passwd.IsEmpty() || name.IsEmpty() || phone == 0)
		MessageBox(L"입력되지 않은 칸이 남아있습니다.");
	else {
		//데이터 베이스 생성
		m_db.OpenEx(_T("DSN=myserver;SERVER=127.0.0.1;PORT=3306;UID=root;PWD=gh3.14159;DATABASE=myserver;"), CDatabase::noOdbcDialog);		//레코드셋 객체 생성
		m_prs = new CRecordset(&m_db);
		//레코드셋의 열 갯수

		//데이터 갯수를 구하기 위해 while문을 사용해서 num을 데이터갯수만큼 증가시키는 코드
	
		

		//여기서부터 데이터 대입
		CString sqlstr;
		sqlstr.Format(_T("INSERT INTO user(id, passwd, name, phone) VALUES('%s', '%s', '%s', '%d')"), id, passwd, name, phone);
		m_db.BeginTrans();
		try
		{
			m_db.ExecuteSQL(sqlstr);
		}
		catch (CDBException* e)
		{
			e->ReportError();       //에러나면자동으로메시지박스뜬다
			m_db.CommitTrans();
			return;
		}
		m_db.CommitTrans();
		m_prs->Close();
		m_db.Close();

		MessageBox(L"회원가입을 축하드립니다!");
		EndDialog(IDD_DIALOG_ForSign);
	}


}


void ForSign::OnBnClickedForidcheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str1;
	CString str2;
	int pass = 0;
	m_idedit.GetWindowTextW(str1);
	if (str1.IsEmpty()) {
		MessageBox(L"Input ID");
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
	m_prs->Open(CRecordset::snapshot, _T("SELECT id FROM USER"));
	while (!m_prs->IsEOF()) {
		m_prs->GetFieldValue(short(0), str2);
		if (str1 == str2) {
			MessageBox(_T("중복된 아이디입니다."));
			pass = 1;
		}
		m_prs->MoveNext();
	}
	if (pass == 0)
		MessageBox(_T("사용가능한 아이디입니다."));
	m_prs->Close();
	m_db.Close();
}
