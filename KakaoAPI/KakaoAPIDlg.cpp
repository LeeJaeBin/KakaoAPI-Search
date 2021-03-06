
// KakaoAPIDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "KakaoAPI.h"
#include "KakaoAPIDlg.h"
#include "afxdialogex.h"
#include <afxinet.h>
#include <string>
#include "CChildDlg1.h"
#include "Resource.h"
#include "json/json.h"
#include "CSettingDLG.h"
#include "CTestClass.h"
#include <fstream>
#include "CDialogClass.h"
#include "CListDbclk.h"
#include "CRequestClass.h"

using namespace std;

CDialogClass *search;
CListDbclk *dbclk;
CRequestClass *req;

#pragma comment(lib, "json/lib_json")
#pragma warning(disable : 4996)
#pragma comment(lib, "wininet.lib")

CInternetSession session(_T("TestSession"));

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



TCHAR destBuffer[30000] = { 0, };

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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CKakaoAPIDlg 대화 상자

CKakaoAPIDlg::CKakaoAPIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KAKAOAPI_DIALOG, pParent)
	, m_Radio(0)
	, test2(_T(""))
{
}

void CKakaoAPIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_VIDEO, m_Radio);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_editSearch);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
	DDX_Control(pDX, IDCANCEL, m_test1);
}

BEGIN_MESSAGE_MAP(CKakaoAPIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CKakaoAPIDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO_VIDEO, &CKakaoAPIDlg::OnBnClickedRadioVideo)
	ON_BN_CLICKED(IDC_RADIO_BOOK, &CKakaoAPIDlg::OnBnClickedRadioBook)
	ON_BN_CLICKED(IDC_RADIO_IMAGE, &CKakaoAPIDlg::OnBnClickedRadioImage)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CKakaoAPIDlg::OnNMDblclkList1)
	ON_COMMAND(ID_OPEN, &CKakaoAPIDlg::OnPopOpen)
	ON_MESSAGE(WM_TRAYICON_MSG, CKakaoAPIDlg::TrayIconMessage)
	ON_COMMAND(ID_OPEN_ASDF, &CKakaoAPIDlg::OnOpenTest)
	ON_COMMAND(ID_OPEN_FDSA, &CKakaoAPIDlg::OnOpenFdsa)
END_MESSAGE_MAP()


// CKakaoAPIDlg 메시지 처리기

void CKakaoAPIDlg::TraySetting(void)
{
	NOTIFYICONDATA  nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage = WM_TRAYICON_MSG;
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	lstrcpy(nid.szTip, L"KakaoAPI");
	Shell_NotifyIcon(NIM_ADD, &nid);
	SendMessage(WM_SETICON, (WPARAM)TRUE, (LPARAM)nid.hIcon);
	m_bTrayStatus = true;
}

BOOL CKakaoAPIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	CString query;

	LPCTSTR converQuery = (LPCTSTR)query;

	wchar_t ObjQuery[50] = _T("?query=");

	m_bTrayStatus = false;
	TraySetting();

	search = new CDialogClass();
	dbclk = new CListDbclk();

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CKakaoAPIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CKakaoAPIDlg::OnPaint()
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

HCURSOR CKakaoAPIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CKakaoAPIDlg::OnBnClickedButton1()
{
	req->RequestFunction(this);
	
	cnt++;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CKakaoAPIDlg::OnBnClickedRadioVideo()
{
	wchar_t Server[50] = _T("https://dapi.kakao.com/v2/search/vclip");
	wcscpy(ServerQuery, Server);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CKakaoAPIDlg::OnBnClickedRadioBook()
{
	wchar_t Server[50] = _T("https://dapi.kakao.com/v2/search/book");
	wcscpy(ServerQuery, Server);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CKakaoAPIDlg::OnBnClickedRadioImage()
{
	wchar_t Server[50] = _T("https://dapi.kakao.com/v2/search/image");
	wcscpy(ServerQuery, Server);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CKakaoAPIDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	pNMItemActivate_tmp = pNMItemActivate;

	CString url;

	if (pNMItemActivate->iItem != -1) {
		url = VideoUrl[pNMItemActivate->iItem];
	}


	CString param = L"GOM ";
	param += url;

	convertLPW = (LPWSTR)(LPCTSTR)param;

	UpdateData(TRUE);

	dbclk->ListSwitch(this);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

LRESULT CKakaoAPIDlg::TrayIconMessage(WPARAM wParam, LPARAM lParam)
{
	if (lParam == WM_LBUTTONDBLCLK) {
		ShowWindow(SW_SHOW);
	}
	else if (lParam == WM_RBUTTONDOWN) {
		CMenu menu, *pSubMenu;

		if (!menu.LoadMenu(IDR_MENU_POPUP))
			return 0;
		if (!(pSubMenu = menu.GetSubMenu(0)))
			return 0;

		CPoint pos;
		GetCursorPos(&pos);
		SetForegroundWindow();

		pSubMenu->TrackPopupMenu(TPM_RIGHTALIGN, pos.x, pos.y, this);
		menu.DestroyMenu();
	}
	return 0;
}

void CKakaoAPIDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_bTrayStatus) {
		NOTIFYICONDATA  nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd = m_hWnd; // 메인 윈도우 핸들
		nid.uID = IDR_MAINFRAME;
		// 작업 표시줄(TaskBar)의 상태 영역에 아이콘을 삭제한다.
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}
}


void CKakaoAPIDlg::OnPopOpen()
{
}


void CKakaoAPIDlg::OnOpenTest()
{
	ShowWindow(SW_SHOW);
}


void CKakaoAPIDlg::OnOpenFdsa()
{
	CSettingDLG SettingDLG;
	SettingDLG.DoModal();
}

void CKakaoAPIDlg::showmodal()
{
	CChildDlg1 childdlg;
	childdlg.DoModal();
}

void CKakaoAPIDlg::exFunction()
{
	UpdateData(true);

	search->SwitchFunction2(this);
}