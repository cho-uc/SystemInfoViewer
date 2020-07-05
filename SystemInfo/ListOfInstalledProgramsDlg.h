#pragma once

#include "stdafx.h"
#include "Resource.h"

class ListOfInstalledProgramsDlg : public CDialogImpl<ListOfInstalledProgramsDlg>
{
private:
	CListViewCtrl m_ListView;

public:
	enum { IDD = IDD_LIST_OF_INSTALLED_PROGRAMS_DLG };

	BEGIN_MSG_MAP(ListOfInstalledProgramsDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCloseCmd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	
};