// CDialogClass.cpp: 구현 파일
//

#include "stdafx.h"
#include "KakaoAPI.h"
#include "CDialogClass.h"
#include "afxdialogex.h"
#include "KakaoAPIDlg.h"
#include <string>
#include "json/json.h"
#include "resource.h"

#pragma warning(disable : 4996)

using namespace std;


// CDialogClass 대화 상자

IMPLEMENT_DYNAMIC(CDialogClass, CDialogEx)

CDialogClass::CDialogClass(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CLASS, pParent)
{

}

CDialogClass::~CDialogClass()
{
}

void CDialogClass::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CDialogClass::SwitchFunction2(CKakaoAPIDlg *dlg) {

	Json::Reader reader;
	Json::Value root;

	bool parseok = reader.parse(dlg->totalData, root, false);

	auto parseArray = root["documents"];

	switch (dlg->m_Radio) {
	case 0:
		dlg->m_listctrl.InsertColumn(0, _T("Title"), 0, 200);
		dlg->m_listctrl.InsertColumn(0, _T("author"), 0, 100);

		for (int i = 0; i < 30; i++) {
			auto items = parseArray[i];

			string parsedData1 = items["title"].asString();
			if (parsedData1 == "") {
				break;
			}
			CString cs1(parsedData1.c_str());

			string parsedData2 = items["author"].asString();
			CString cs2(parsedData2.c_str());

			string parsedData3 = items["url"].asString();
			CString cs3(parsedData3.c_str());

			dlg->VideoUrl[i] = cs3;

			dlg->m_listctrl.InsertItem(i, cs2);
			dlg->m_listctrl.SetItem(i, 1, LVIF_TEXT, cs1, 0, 0, 0, NULL);
		}
		break;

	case 1:
		dlg->m_listctrl.InsertColumn(0, _T("Title"), 0, 150);
		dlg->m_listctrl.InsertColumn(0, _T("publisher"), 0, 100);

		for (int i = 0; i < 30; i++) {
			auto items = parseArray[i];

			string parsedData1 = items["title"].asString();
			if (parsedData1 == "") {
				break;
			}
			CString cs1(parsedData1.c_str());
			dlg->BookTitle[i] = cs1;

			string parsedData2 = items["publisher"].asString();
			CString cs2(parsedData2.c_str());
			dlg->BookPublisher[i] = cs2;

			string parsedData3 = items["contents"].asString();
			CString cs3(parsedData3.c_str());
			dlg->BookInfo[i] = cs3;

			string parsedData4 = items["price"].asString();
			CString cs4(parsedData4.c_str());
			dlg->BookPrice[i] = cs4;

			string parsedData5 = items["url"].asString();
			CString cs5(parsedData5.c_str());
			dlg->BookUrl[i] = cs5;

			string parsedData6 = items["category"].asString();
			CString cs6(parsedData6.c_str());
			dlg->BookCategory[i] = cs6;

			dlg->m_listctrl.InsertItem(i, cs2);
			dlg->m_listctrl.SetItem(i, 1, LVIF_TEXT, cs1, 0, 0, 0, NULL);
		}
		break;

	case 2:
		dlg->m_listctrl.InsertColumn(0, _T("Collection"), 0, 80);
		dlg->m_listctrl.InsertColumn(0, _T("display_sitename"), 0, 200);

		for (int i = 0; i < 30; i++) {
			auto items = parseArray[i];

			string parsedData1 = items["display_sitename"].asString();
			CString cs1(parsedData1.c_str());

			string parsedData2 = items["collection"].asString();
			CString cs2(parsedData2.c_str());

			string parsedData3 = items["image_url"].asString();
			CString cs3(parsedData3.c_str());
			if (parsedData3 == "") {
				break;
			}

			dlg->ImageUrl[i] = cs3;

			dlg->m_listctrl.InsertItem(i, cs1);
			dlg->m_listctrl.SetItem(i, 1, LVIF_TEXT, cs2, 0, 0, 0, NULL);
		}
		break;
	}
}


BEGIN_MESSAGE_MAP(CDialogClass, CDialogEx)
END_MESSAGE_MAP()


// CDialogClass 메시지 처리기
