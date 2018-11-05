#include "stdafx.h"
#include "CListDbclk.h"
#include "KakaoAPIDlg.h"
#include "CChildDlg1.h"
#include <afxinet.h>

#pragma warning(disable : 4996)

CChildDlg1 *childDlg;

CListDbclk::CListDbclk()
{
}


CListDbclk::~CListDbclk()
{
}

void CListDbclk::ListSwitch(CKakaoAPIDlg *dilg) {

	childDlg = new CChildDlg1();
	int itemNo = dilg->pNMItemActivate_tmp->iItem;
	switch (dilg->m_Radio) {
	case 0:
	{
		STARTUPINFO StartupInfo = { 0 };
		StartupInfo.cb = sizeof(STARTUPINFO);
		PROCESS_INFORMATION ProcessInfo;
		::CreateProcess(L"C:\\Program Files (x86)\\GRETECH\\GOMPlayer\\GOM.EXE", dilg->convertLPW, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo);
		break;
	}
	case 1:
	{
		dilg->title = dilg->BookTitle[itemNo];
		dilg->burl = dilg->BookUrl[itemNo];
		dilg->binfo = dilg->BookInfo[itemNo];
		dilg->publisher = dilg->BookPublisher[itemNo];
		dilg->price = dilg->BookPrice[itemNo];
		dilg->category = dilg->BookCategory[itemNo];

		dilg->showmodal();
		break;
	}
	case 2:

		CString strPathName;
		CString strFileName;

		CString szFilter = L"*.*||";
		CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

		if (IDOK == dlg.DoModal()) {
			strPathName = dlg.GetPathName();
			strFileName = dlg.GetFileName();
		}

		INTERNET_PORT nPort = 80;
		if (!AfxParseURL(dilg->ImageUrl[itemNo], dilg->dwServiceType, dilg->ServerUrl, dilg->ObjUrl, nPort))
		{
			ASSERT(0);
		}

		HANDLE h_wait_event = CreateEvent(NULL, TRUE, FALSE, L"TEST");

		HINTERNET h_session = ::InternetOpen(NULL, PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);
		HINTERNET h_connect = ::InternetConnect(h_session, dilg->ServerUrl, INTERNET_INVALID_PORT_NUMBER, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
		HINTERNET h_http_file = ::HttpOpenRequest(h_connect, L"GET", dilg->ObjUrl, HTTP_VERSION, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);

		BOOL request_flag = ::HttpSendRequest(h_http_file, NULL, 0, 0, 0);
		if (request_flag == TRUE) {

			// 전송받은 그림을 저장할 파일을 생성합니다.
			FILE *p_file = _wfopen(strPathName, L"wb");

			char buffer[1025], error_count = 0;
			DWORD read_byte = 0, buffer_size = 1024;

			while (::InternetReadFile(h_http_file, buffer, buffer_size, &read_byte)) {
				if (read_byte > 0 && p_file != NULL) fwrite(buffer, 1, read_byte, p_file);

				if (read_byte < 1024) {
					error_count++;
					if (error_count > 10) break;
					else ::WaitForSingleObject(h_wait_event, 50);
				}
				else error_count = 0;
			}

			::InternetCloseHandle(h_http_file);

			if (p_file != NULL)
				fclose(p_file);
		}

		::InternetCloseHandle(h_connect);
		::InternetCloseHandle(h_session);

		CloseHandle(h_wait_event);
	}
}