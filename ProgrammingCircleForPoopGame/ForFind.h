#pragma once
#include <afxdb.h>

// ForFind 대화 상자

class ForFind : public CDialog
{
	DECLARE_DYNAMIC(ForFind)

public:
	ForFind(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ForFind();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ForFind };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	CDatabase m_db;
	CRecordset* m_prs;
	CEdit m_namedit;
	CEdit m_phonedit;
	
	afx_msg void OnBnClickedButton4();
	CEdit p_idedit;
	CEdit p_namedit;
	CEdit p_phonedit;
	afx_msg void OnBnClickedButton6();
};
