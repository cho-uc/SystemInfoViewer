#pragma once

#include "stdafx.h"
#include "Resource.h"
#include "ListOfProcessDlg.h"
#include "ListOfInstalledProgramsDlg.h"
#include "ListOfServicesDlg.h"

/**
* This class is the GUI part of the program. It contains a MSG
* map, a DDX map and handles for Buttons, ListViewControls, etc.
*
*/

class MainWindow : public CDialogImpl<MainWindow>
{
protected:
	CListBox m_ListBox;
    CListViewCtrl m_ListView;
	ListOfProcessDlg dlgListOfProcess;
	ListOfInstalledProgramsDlg dlgListOfInstalledPrograms;
	ListOfServicesDlg dlgListOfService;

public:
    MainWindow();

    enum {IDD = IDD_MAIN_DIALOG};

    BEGIN_MSG_MAP(MainWindow)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInit);
        MESSAGE_HANDLER(WM_CLOSE, OnClose);
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy);
        COMMAND_ID_HANDLER(IDD_LIST_OF_PROCESS_DLG, OnDetailProcessButtonClick)
        COMMAND_ID_HANDLER(IDD_LIST_OF_INSTALLED_PROGRAMS_DLG, OnDetailInstalledProgramButtonClick)
        COMMAND_ID_HANDLER(IDD_LIST_OF_SERVICES_DLG, OnDetailServicesButtonClick)
        COMMAND_HANDLER(IDC_CLOSE, BN_CLICKED, OnCloseButtonClick);
    END_MSG_MAP()

    LRESULT OnInit(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnClose(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDestroy(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnCloseButtonClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    LRESULT OnDetailProcessButtonClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    LRESULT OnDetailInstalledProgramButtonClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    LRESULT OnDetailServicesButtonClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

};