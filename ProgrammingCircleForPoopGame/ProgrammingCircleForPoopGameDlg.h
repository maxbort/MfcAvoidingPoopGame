#include "ProgrammingCircleForPoopGame_MAIN.h"
#include "ForFind.h"
#include "ForSign.h"
#include <afxdb.h>
// ProgrammingCircleForPoopGameDlg.h: 헤더 파일
//
#pragma once


// CProgrammingCircleForPoopGameDlg 대화 상자
class CProgrammingCircleForPoopGameDlg : public CDialogEx
{
// 생성입니다.
public:
	CProgrammingCircleForPoopGameDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	ProgrammingCircleForPoopGame_MAIN* p_main;
	ForFind* p_find;
	ForSign* p_sign;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROGRAMMINGCIRCLEFORPOOPGAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CDatabase m_db;
	CRecordset* m_prs;

	afx_msg void OnBnClickedButton3();
	
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_list;
	afx_msg void OnBnClickedButton4();
};
