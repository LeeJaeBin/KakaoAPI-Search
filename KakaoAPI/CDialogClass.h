#pragma once


// CDialogClass 대화 상자

class CKakaoAPIDlg;

class CDialogClass : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogClass)

public:
	CDialogClass(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDialogClass();
	void SwitchFunction2(CKakaoAPIDlg*);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CLASS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
