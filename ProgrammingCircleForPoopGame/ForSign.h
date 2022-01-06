#pragma once

#include <afxdb.h>
// ForSign 대화 상자

class ForSign : public CDialogEx
{
	DECLARE_DYNAMIC(ForSign)

public:
	ForSign(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ForSign();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ForSign };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSign();
	afx_msg void OnBnClickedForidcheck();
	CDatabase m_db;
	CRecordset* m_prs;
	CEdit m_idedit;
	CEdit m_psedit;
	CEdit m_namedit;
	CEdit m_pnedit;
	CButton m_idcheck;
};
