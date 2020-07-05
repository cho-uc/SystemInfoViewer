#include "stdafx.h"
#include "ListOfServicesDlg.h"
#include "ServiceEnumerator.h"
#include "ServiceContants.h"

#define SERVICE_BUFFER_SIZE 128

static TCHAR const* COL_HEADER_SERVICE_NAME = L"Service Name";
static TCHAR const* COL_HEADER_SERVICE_DESC = L"Description";
static TCHAR const* COL_HEADER_SERVICE_STAT = L"Status";

DWORD COL_WIDTH_SERVICE1 = 150;
DWORD COL_WIDTH_SERVICE2 = 150;
DWORD COL_WIDTH_SERVICE3 = 80;

LRESULT ListOfServicesDlg :: OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_ListView.Attach(GetDlgItem(IDC_LISTVIEWCTRL_SERVICES));

	m_ListView.InsertColumn(0, COL_HEADER_SERVICE_NAME, LVCFMT_CENTER, COL_WIDTH_SERVICE1);
	m_ListView.InsertColumn(1, COL_HEADER_SERVICE_DESC, LVCFMT_CENTER, COL_WIDTH_SERVICE2);
	m_ListView.InsertColumn(2, COL_HEADER_SERVICE_STAT, LVCFMT_CENTER, COL_WIDTH_SERVICE3);

	SERVICE_STATUS        g_ServiceStatus = { 0 };
	SERVICE_STATUS_HANDLE g_StatusHandle = NULL;

	DWORD iter_output = 0; //required to enumerate output to table
	auto services = ServiceEnumerator::EnumerateServices();
	for (auto const& s : services)
	{
		const WCHAR* pServiceName_wchar = s.ServiceName.c_str();
		const WCHAR* pDisplayName_wchar = s.DisplayName.c_str();
		const WCHAR* pStatusString_wchar = s.StatusString.c_str();

		m_ListView.InsertItem(iter_output, pServiceName_wchar);
		// Initialize the text of the subitems (columns to the right)				
		m_ListView.SetItemText(iter_output, 1, pDisplayName_wchar); //row, col,text
		m_ListView.SetItemText(iter_output, 2, pStatusString_wchar);
		iter_output++;
	}

	return (LRESULT)TRUE;
}

LRESULT ListOfServicesDlg::OnCloseCmd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT ListOfServicesDlg::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{	
	return 0;
}