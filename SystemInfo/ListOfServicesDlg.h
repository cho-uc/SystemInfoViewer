#pragma once

#include "stdafx.h"
#include "Resource.h"

class ListOfServicesDlg : public CDialogImpl<ListOfServicesDlg>
{
private:
	CListViewCtrl m_ListView;

public:
	enum { IDD = IDD_LIST_OF_SERVICES_DLG};

	BEGIN_MSG_MAP(ListOfServicesDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_PAINT, OnPaint);
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCloseCmd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

};