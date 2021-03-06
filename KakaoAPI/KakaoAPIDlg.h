
// KakaoAPIDlg.h: 헤더 파일
//

#pragma once
#define  WM_TRAYICON_MSG WM_USER + 1

class CChildDlg1;

// CKakaoAPIDlg 대화 상자
class CKakaoAPIDlg : public CDialogEx
{
// 생성입니다.
public:
	CKakaoAPIDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KAKAOAPI_DIALOG };
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

	DECLARE_MESSAGE_MAP();
	BOOL m_bTrayStatus;

public:
	int m_Radio;
	CEdit m_editSearch;
	afx_msg void OnBnClickedButton1();
	CListCtrl m_listctrl;
	afx_msg void OnBnClickedRadioVideo();
	afx_msg void OnBnClickedRadioBook();
	afx_msg void OnBnClickedRadioImage();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_test1;
	CString test2;
	CString title;
	CString burl;
	CString binfo;
	CString publisher;
	CString price;
	CString category;
	void TraySetting(void);

	void exFunction();

	CString query;

	HWND hwnd;

	wchar_t ObjQuery[100] = _T("?size=30&query=");
	wchar_t ServerQuery[100] = _T("https://dapi.kakao.com/v2/search/vclip");
	wchar_t tmp_ServerQuery[100];
	wchar_t *MidQuery;
	wchar_t *ResultQuery;
	CString strHeaders = _T("Authorization : KakaoAK b55dd9e2e4eb440b6f6eef38c3ed6cc5 \nContent-Type:application/json");

	int cnt = 0;

	DWORD dwServiceType;
	DWORD dwRet = 0;


	CString ServerUrl, ObjUrl;
	void showmodal();

	LPWSTR convertLPW;

	LPNMITEMACTIVATE pNMItemActivate_tmp;

	CString VideoUrl[30] = { 0, };

	CString BookTitle[30];
	CString tmp;
	CString BookInfo[30];
	CString BookUrl[30];
	CString BookPublisher[30];
	CString BookPrice[30];
	CString BookCategory[30];

	CString Testing = L"asdf";

	char totalData[30000] = { 0, };

	CString ImageUrl[30];
	CMenu m_TrayMenu;
	afx_msg LRESULT TrayIconMessage(WPARAM wParam, LPARAM lParam);

protected:
	
public:
	afx_msg void OnDestroy();
	afx_msg void OnPopOpen();
	afx_msg void OnOpenTest();
	afx_msg void OnOpenFdsa();
};