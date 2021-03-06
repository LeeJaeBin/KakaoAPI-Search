// CSettingDLG.cpp: 구현 파일
//

#include "stdafx.h"
#include "KakaoAPI.h"
#include "CSettingDLG.h"
#include "afxdialogex.h"


// CSettingDLG 대화 상자

IMPLEMENT_DYNAMIC(CSettingDLG, CDialogEx)

CSettingDLG::CSettingDLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_DIALOG, pParent)
{

}

CSettingDLG::~CSettingDLG()
{
}

void CSettingDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingDLG, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSettingDLG::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSettingDLG::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSettingDLG 메시지 처리기

static BOOL SetRegistyStartProgram(BOOL bAutoExec, LPCWSTR lpValueName, LPCWSTR lpExeFileName)
{
	HKEY hKey;
	LONG lRes;
	if (bAutoExec)
	{
		if (lpValueName == NULL || lpExeFileName == NULL)
			return FALSE;
		if (RegOpenKeyEx(
			HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0L, KEY_WRITE, &hKey) != ERROR_SUCCESS)
			return FALSE;

		lRes = RegSetValueEx(hKey, lpValueName,
			0,
			REG_SZ,
			(BYTE*)lpExeFileName,
			lstrlen(lpExeFileName));

		RegCloseKey(hKey);

		if (lRes != ERROR_SUCCESS)
			return FALSE;
	}
	else
	{
		if (RegOpenKeyEx(
			HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
			return FALSE;

		lRes = RegDeleteValue(hKey, lpValueName);

		RegCloseKey(hKey);

		if (lRes != ERROR_SUCCESS)
			return FALSE;
	}

	return TRUE;
}

void CSettingDLG::OnBnClickedButton1()
{
	SetRegistyStartProgram(TRUE, L"KakaoAPI", L"C:\\Users\\TERUTEN\\Desktop\\KakaoAPI\\Debug\\KakaoAPI.exe");
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CSettingDLG::OnBnClickedButton2()
{
	SetRegistyStartProgram(FALSE, L"KakaoAPI", NULL);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
