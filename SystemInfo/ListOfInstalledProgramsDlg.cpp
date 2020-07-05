#include "stdafx.h"
#include "ListOfInstalledProgramsDlg.h"

#define INFO_BUFFER_SIZE 512

static TCHAR const* COL_HEADER_SOFTWARE_NAME = L"Sofware Name";
static TCHAR const* COL_HEADER_SOFTWARE_VER = L"Software Version";
DWORD COL_WIDTH_SOFTWARE1 = 350;
DWORD COL_WIDTH_SOFTWARE2 = 120;

LRESULT ListOfInstalledProgramsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_ListView.Attach(ATL::CWindow::GetDlgItem(IDC_LISTVIEWCTRL_PROGRAMS));
	m_ListView.InsertColumn(0, COL_HEADER_SOFTWARE_NAME, LVCFMT_CENTER, COL_WIDTH_SOFTWARE1);
	m_ListView.InsertColumn(1, COL_HEADER_SOFTWARE_VER, LVCFMT_CENTER, COL_WIDTH_SOFTWARE2);

	UINT ret = 0;
	DWORD dwIndex = 0; //start from 0 until end of increment of successful run 
	TCHAR szInstalledProductCode[INFO_BUFFER_SIZE] = { 0 };
	TCHAR szSid[INFO_BUFFER_SIZE] = { 0 };
	DWORD cchSid;
	MSIINSTALLCONTEXT dwInstalledContext;
	TCHAR currentProductCode[INFO_BUFFER_SIZE] = { 0 };
	DWORD iter_output = 0; //required to enumerate output to table

	while (ret == ERROR_SUCCESS) {
		cchSid = sizeof(szSid) / sizeof(szSid[0]);

		ret = ::MsiEnumProductsEx(
			NULL,           // all the products in the context
			NULL,  // Current user
			MSIINSTALLCONTEXT_USERMANAGED | MSIINSTALLCONTEXT_USERUNMANAGED | MSIINSTALLCONTEXT_MACHINE,
			dwIndex,
			szInstalledProductCode,
			&dwInstalledContext,
			szSid,
			&cchSid);

		if (ret == ERROR_SUCCESS)
		{
			TCHAR name[INFO_BUFFER_SIZE] = { 0 };
			TCHAR SoftwareVersion[INFO_BUFFER_SIZE] = { 0 };
			DWORD cchValue = 0;

			UINT ret2 = ::MsiGetProductInfoEx(
				szInstalledProductCode,
				cchSid == 0 ? NULL : szSid,
				dwInstalledContext,
				INSTALLPROPERTY_INSTALLEDPRODUCTNAME,
				NULL,
				&cchValue);

			if (ret2 == ERROR_SUCCESS)
			{
				cchValue++;
				//Get Software Name-----------------------------------------------
				::MsiGetProductInfoEx(
					szInstalledProductCode,
					cchSid == 0 ? NULL : szSid,
					dwInstalledContext,
					INSTALLPROPERTY_INSTALLEDPRODUCTNAME,
					(LPTSTR)&name[0],
					&cchValue);
			
				//Get Software Version-----------------------------------------------
				::MsiGetProductInfoEx(
					szInstalledProductCode,
					cchSid == 0 ? NULL : szSid,
					dwInstalledContext,
					INSTALLPROPERTY_VERSIONSTRING,
					(LPTSTR)&SoftwareVersion[0],
					&cchValue);

				m_ListView.InsertItem(iter_output, &name[0]);
				// Initialize the text of the subitems (columns to the right)				
				m_ListView.SetItemText(iter_output, 1, &SoftwareVersion[0]); //row, col,text
				iter_output++;
			}
		}
		dwIndex++;
	}
	return (LRESULT)TRUE;
}

LRESULT ListOfInstalledProgramsDlg::OnCloseCmd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}
