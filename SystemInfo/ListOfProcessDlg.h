#pragma once

#include "stdafx.h"
#include "Resource.h"

class ListOfProcessDlg : public CDialogImpl<ListOfProcessDlg>
{
private:	
	CListViewCtrl m_ListView;

public:
	enum { IDD = IDD_LIST_OF_PROCESS_DLG};
	
	BEGIN_MSG_MAP(ListOfProcessDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCloseCmd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};