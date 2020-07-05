#pragma once

#include "stdafx.h"
#include "ListOfProcessDlg.h"
#include "ServiceEnumerator.h"
#include "ServiceContants.h"

static TCHAR const* COL_HEADER_PROCESS_NAME = L"Process Name";
static TCHAR const* COL_HEADER_PID = L"PID";

DWORD COL_WIDTH_PROCESS1 = 150;
DWORD COL_WIDTH_PROCESS2 = 80;

#define INFO_BUFFER_SIZE 512

LRESULT ListOfProcessDlg:: OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{	
	m_ListView.Attach(GetDlgItem(IDC_LISTVIEWCTRL_PROCESSES));
	m_ListView.InsertColumn(0, COL_HEADER_PROCESS_NAME, LVCFMT_CENTER, COL_WIDTH_PROCESS1);
	m_ListView.InsertColumn(1, COL_HEADER_PID, LVCFMT_CENTER, COL_WIDTH_PROCESS2);

	// Get the list of process identifiers.
	DWORD aProcesses[INFO_BUFFER_SIZE], cbNeeded, cProcesses;
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return 1;
	}

	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the name and process identifier for each process.
	int ProcessIDIter = 0;
	for (unsigned int i = 0; i < cProcesses; i++)
	{
		if (aProcesses[i] != 0)
		{
			TCHAR szProcessName[INFO_BUFFER_SIZE] = TEXT("<unknown>");
			// Get a handle to the process.
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
				PROCESS_VM_READ,
				FALSE, aProcesses[i]);

			// Get the process name.
			if (NULL != hProcess)
			{
				HMODULE hMod;
				DWORD cbNeeded;

				if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
					&cbNeeded))
				{
					GetModuleBaseName(hProcess, hMod, szProcessName,
						sizeof(szProcessName) / sizeof(TCHAR));
				}
			}
			CString strText;
			m_ListView.InsertItem(LVIF_TEXT | LVIF_STATE, i, &szProcessName[0],
				(i % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED, 0, 0);

			// Initialize the text of the subitems (columns to the right)
			strText.Format(_T("%i"), aProcesses[i]);
			m_ListView.SetItemText(ProcessIDIter, 1, strText); //row, col,text

			CloseHandle(hProcess);
			ProcessIDIter += 1;
		}
	}
	return (LRESULT)TRUE;
}

LRESULT ListOfProcessDlg::OnCloseCmd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

