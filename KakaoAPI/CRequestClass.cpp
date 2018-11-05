#include "stdafx.h"
#include "CRequestClass.h"
#include "KakaoAPIDlg.h"
#include <afxinet.h>

#pragma warning(disable : 4996)

CRequestClass::CRequestClass()
{
}


CRequestClass::~CRequestClass()
{
}

void CRequestClass::RequestFunction(CKakaoAPIDlg *dilg) {
	CInternetSession session(_T("TestSession"));

	if (dilg->cnt > 0) {
		dilg->m_listctrl.DeleteColumn(0);
		dilg->m_listctrl.DeleteColumn(0);
	}


	dilg->m_listctrl.DeleteAllItems();
	wchar_t ObjQuery[50] = _T("?size=30&query=");
	dilg->ResultQuery = _T("");
	wcscpy(dilg->tmp_ServerQuery, dilg->ServerQuery);
	dilg->m_editSearch.GetWindowTextW(dilg->query);

	dilg->MidQuery = wcscat(ObjQuery, dilg->query);
	dilg->ResultQuery = wcscat(dilg->tmp_ServerQuery, dilg->MidQuery);

	INTERNET_PORT nPort;

	if (!AfxParseURL(dilg->ResultQuery, dilg->dwServiceType, dilg->ServerUrl, dilg->ObjUrl, nPort))
	{
		ASSERT(0);
	}

	CHttpConnection *pConnection = session.GetHttpConnection(dilg->ServerUrl, nPort);

	CHttpFile *pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, dilg->ObjUrl, nullptr, 1, nullptr, nullptr,
		INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_CACHE_WRITE
		| INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID);

	try {
		BOOL result = pFile->SendRequest(dilg->strHeaders, nullptr, 0);

		pFile->QueryInfoStatusCode(dilg->dwRet);
	}

	catch (CInternetException* e) {
		TCHAR Error[255];
		e->GetErrorMessage(Error, 255);
		e->Delete();
	}

	pFile->Read(dilg->totalData, 30000);

	dilg->exFunction();

	pFile->Close();

	delete pConnection;
	delete pFile;
}