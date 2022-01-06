#pragma once
#include <vector>
#include <iostream>
#include <afxdb.h>
#include <atlimage.h>
using namespace std;


// ProgrammingCircleForPoopGame_MAIN 대화 상자

class ProgrammingCircleForPoopGame_MAIN : public CDialogEx
{
	DECLARE_DYNAMIC(ProgrammingCircleForPoopGame_MAIN)

public:
	ProgrammingCircleForPoopGame_MAIN(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ProgrammingCircleForPoopGame_MAIN();


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Main };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	vector<CPoint> poop;
	CPoint anypoop;
	int speed;
	int cha_x;
	int col;
	int shape;
//	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton1();
	bool Over;
	int score;
	afx_msg void OnEnChangeshowscore();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnExit();

	CDatabase m_db;
	CRecordset* m_prs;
	CString playerid;
	CImage img;
	afx_msg void OnSettingColor();
	afx_msg void OnSettingShape();
	afx_msg void OnSpeedX2();
	afx_msg void OnSpeedX15();
	afx_msg void OnSpeedX1();
	afx_msg void OnSpeedX05();
};
