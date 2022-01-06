// ProgrammingCircleForPoopGame_MAIN.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ProgrammingCircleForPoopGame.h"
#include "ProgrammingCircleForPoopGame_MAIN.h"
#include "afxdialogex.h"
#include "ProgrammingCircleForPoopGameDlg.h"



// ProgrammingCircleForPoopGame_MAIN 대화 상자

IMPLEMENT_DYNAMIC(ProgrammingCircleForPoopGame_MAIN, CDialogEx)

ProgrammingCircleForPoopGame_MAIN::ProgrammingCircleForPoopGame_MAIN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Main, pParent)
{
	speed = 10;
	cha_x = 0;
	Over = false;
	score = 0;
	CDatabase m_db;
	CRecordset* m_prs;
	col = 0;
	shape = 0;

}

ProgrammingCircleForPoopGame_MAIN::~ProgrammingCircleForPoopGame_MAIN()
{
}

void ProgrammingCircleForPoopGame_MAIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ProgrammingCircleForPoopGame_MAIN, CDialogEx)
//	ON_WM_PAINT()
ON_WM_PAINT()
ON_WM_TIMER()
ON_WM_KEYDOWN()
//ON_WM_KEYUP()
ON_BN_CLICKED(IDC_BUTTON1, &ProgrammingCircleForPoopGame_MAIN::OnBnClickedButton1)
ON_EN_CHANGE(IDC_EDIT2, &ProgrammingCircleForPoopGame_MAIN::OnEnChangeEdit2)
ON_COMMAND(For_Exit, &ProgrammingCircleForPoopGame_MAIN::OnExit)
ON_COMMAND(ID_SETTING_COLOR, &ProgrammingCircleForPoopGame_MAIN::OnSettingColor)
ON_COMMAND(ID_SETTING_SHAPE, &ProgrammingCircleForPoopGame_MAIN::OnSettingShape)
ON_COMMAND(ID_SPEED_X2, &ProgrammingCircleForPoopGame_MAIN::OnSpeedX2)
ON_COMMAND(ID_SPEED_X15, &ProgrammingCircleForPoopGame_MAIN::OnSpeedX15)
ON_COMMAND(ID_SPEED_X1, &ProgrammingCircleForPoopGame_MAIN::OnSpeedX1)
ON_COMMAND(ID_SPEED_X05, &ProgrammingCircleForPoopGame_MAIN::OnSpeedX05)
END_MESSAGE_MAP()








void ProgrammingCircleForPoopGame_MAIN::OnPaint()
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
	}

	else
	{
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		COLORREF bc[] = { RGB(255,255,255), RGB(127,179,250), RGB(238,141,136) };
		CBrush Black(RGB(0, 0, 0));
		CBrush White(RGB(255, 255, 255));
		
		

		dc.SelectObject(&Black); //배경 검정
		dc.Rectangle(0, 0, rect.right, rect.bottom);

		img.Load(L"s.png"); //플레이어 이미지
		img.StretchBlt(dc, cha_x + rect.right / 2 - 20, rect.bottom - 60, 40, 60, 0, 0, 200, 300, SRCCOPY);

		for (int i = 0; i < poop.size(); i++) { //눈 그리기
			CBrush bs(bc[col]);
			dc.SelectObject(bs);
			if (shape == 0)
				dc.Ellipse(poop[i].x - 10, poop[i].y - 10, poop[i].x + 10, poop[i].y + 10);
			else if (shape == 1)
				dc.Rectangle(poop[i].x - 10, poop[i].y - 10, poop[i].x + 10, poop[i].y + 10);
		}

		CString str; //현재 스코어 출력

		str.Format(L"score: %d", score);
		dc.SetBkColor(RGB(0, 0, 0));
		dc.SetTextColor(RGB(255, 255, 255));
		dc.TextOutW(rect.right - 100, 40, str);
		dc.TextOutW(rect.right - 100, 20, playerid);

		CString s;
		s.Format(_T("최종 점수: %d\n재시도 하시겠습니까?"), score);

		for (int j = 0; j < poop.size(); j++) { //눈 맞을시 게임 종료 및 재시도 선택
			if ((poop[j].y + 10) > (rect.bottom - 60) && (poop[j].x - 10) < (cha_x + rect.right / 2 + 20) && (poop[j].x + 10) > (cha_x + rect.right / 2 - 20)) {
				KillTimer(0);
				BOOL bOpen = m_db.OpenEx(_T("DSN=myserver;SERVER=127.0.0.1;PORT=3306;UID=root;PWD=gh3.14159;DATABASE=myserver;"), CDatabase::noOdbcDialog);
				if (bOpen)
					m_prs = new CRecordset(&m_db);
				CString updatedata;
				updatedata.Format(L"UPDATE user SET score='%d' WHERE id='%s'", score, playerid);
				m_db.BeginTrans();
				try {
					m_db.ExecuteSQL(updatedata);
				}
				catch (CException* e) {
					e->ReportError();
				}
				m_db.CommitTrans();
				m_db.Close();
				if (MessageBox(s, L"게임 종료", MB_YESNO) == IDYES) { //재시도;
					
					poop.clear();
					score = 0;
					SetTimer(0, 100, NULL);
					break;
					
				}
				else { //종료
					exit(0);
				}
			}
		}

	}
	img.Destroy();
	
}


void ProgrammingCircleForPoopGame_MAIN::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(rect);
	
	anypoop.x = rand() % (rect.right - 20);
	anypoop.y = 0;
	poop.push_back(anypoop);
	for (int i = 0; i < poop.size(); i++) {
		poop[i].y += speed;
		if (poop[i].y >= rect.bottom - 10) {
			poop.erase(poop.begin() + i);
			score += 10;
		}
	}


	/*for (int i = 0; i < poop.size(); i++) {
		int dx = poop[i].x - cha_x;
		if (dx < 20) {
			MessageBox(L"GameOver");

			
		}
	}
	*/

	Invalidate();
	CDialogEx::OnTimer(nIDEvent);
}


void ProgrammingCircleForPoopGame_MAIN::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SPACE) {
		if (Over == true) {
			KillTimer(0);
			Over = false;
		}
		else {
			SetTimer(0, 100, NULL);
			Over = true;
		}
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);

}


//void ProgrammingCircleForPoopGame_MAIN::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
//}


BOOL ProgrammingCircleForPoopGame_MAIN::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CRect rect;
	GetClientRect(rect);
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_LEFT) {
			if (cha_x + rect.right / 2 - 10 <= 0)
				cha_x = - rect.right / 2 + 10;
			else
				cha_x -= 20;
		}
		if (pMsg->wParam == VK_RIGHT) {
			if (cha_x + rect.right / 2 + 10 >= rect.right-10)
				cha_x = rect.right / 2 - 10;
			else
				cha_x += 20;
		}
	}
	Invalidate();


	return CDialogEx::PreTranslateMessage(pMsg);
}


void ProgrammingCircleForPoopGame_MAIN::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void ProgrammingCircleForPoopGame_MAIN::OnEnChangeshowscore()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ProgrammingCircleForPoopGame_MAIN::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ProgrammingCircleForPoopGame_MAIN::OnExit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	exit(0);
}


void ProgrammingCircleForPoopGame_MAIN::OnSettingColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (col == 0)
		col = 1;
	else if (col = 1)
		col = 2;
	else if (col == 2)
		col = 0;

	Invalidate();
}


void ProgrammingCircleForPoopGame_MAIN::OnSettingShape()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (shape == 0)
		shape = 1;
	else if (shape == 1)
		shape = 0;
}


void ProgrammingCircleForPoopGame_MAIN::OnSpeedX2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	speed = 20;
	Invalidate();
}


void ProgrammingCircleForPoopGame_MAIN::OnSpeedX15()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	speed = 15;
	Invalidate();
}


void ProgrammingCircleForPoopGame_MAIN::OnSpeedX1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	speed = 10;
	Invalidate();
}


void ProgrammingCircleForPoopGame_MAIN::OnSpeedX05()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	speed = 5;
	Invalidate();
}