// CChildDlg1.cpp: 구현 파일
//

#include "stdafx.h"
#include "resource.h"
#include "KakaoAPI.h"
#include "KakaoAPIDlg.h"
#include "CChildDlg1.h"
#include "afxdialogex.h"


// CChildDlg1 대화 상자

IMPLEMENT_DYNAMIC(CChildDlg1, CDialogEx)

CChildDlg1::CChildDlg1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ChildDlg1, pParent)
{

}

CChildDlg1::~CChildDlg1()
{
}

void CChildDlg1::DoDataExchange(CDataExchange* pDX)
{
	CString title = ((CKakaoAPIDlg *)GetParent())->title;
	CString url = ((CKakaoAPIDlg *)GetParent())->burl;
	CString info = ((CKakaoAPIDlg *)GetParent())->binfo;
	CString publisher = ((CKakaoAPIDlg *)GetParent())->publisher;
	CString price = ((CKakaoAPIDlg *)GetParent())->price;
	CString category = ((CKakaoAPIDlg *)GetParent())->category;

	//	m_Example2.SetWindowText(asdf);
	SetDlgItemText(IDC_EXAMPLE, title);
	SetDlgItemText(IDC_URL, url);
	SetDlgItemText(IDC_INFO, info);
	SetDlgItemText(IDC_PUBLISHER, publisher);
	SetDlgItemText(IDC_PRICE, price);
	SetDlgItemText(IDC_CATEGORY, category);
}


BEGIN_MESSAGE_MAP(CChildDlg1, CDialogEx)
END_MESSAGE_MAP()


// CChildDlg1 메시지 처리기

