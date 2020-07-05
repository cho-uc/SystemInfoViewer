#include "stdafx.h"
#include "MainWindow.h"

#define INFO_BUFFER_SIZE 512
#define IP_LENGTH 46 //default value in Windows

static TCHAR const* COL_HEADER_MAIN_INFO = L"Info";
static TCHAR const* COL_HEADER_MAIN_VALUE = L"Value";

static TCHAR const* INFO_USERNAME = L"Username"; 
static TCHAR const* INFO_IPv4 = L"IPv4";
static TCHAR const* INFO_IPv6 = L"IPv6";
static TCHAR const* INFO_PROCESSOR_NAME = L"Processor Name";
static TCHAR const* INFO_COMP_NAME = L"Computer Name";
static TCHAR const* INFO_DOMAIN_NAME = L"Workgroup";
static TCHAR const* INFO_OS_NAME = L"Operating system";

static TCHAR const* OS_WINXP = L"Windows XP Or Greater version %u.%u";
static TCHAR const* OS_WINXPSP1 = L"Windows XPSP1 Or Greater version %u.%u";
static TCHAR const* OS_WINXPSP2 = L"Windows XPSP2 Or Greater version %u.%u";
static TCHAR const* OS_WINXPSP3 = L"Windows XPSP3 Or Greater version %u.%u";
static TCHAR const* OS_WINVIS = L"Windows Vista Or Greater version %u.%u";
static TCHAR const* OS_WINVIS_SP1 = L"Windows Vista SP1 Or Greater version %u.%u";
static TCHAR const* OS_WINVIS_SP2 = L"Windows Vista SP1 Or Greater version %u.%u";
static TCHAR const* OS_WIN7 = L"Windows 7 Or Greater version %u.%u";
static TCHAR const* OS_WIN7SP1 = L"Windows 7SP1 Or Greater %u.%u";
static TCHAR const* OS_WIN8 = L"Windows 8 Or Greater version %u.%u";
static TCHAR const* OS_WIN81 = L"Windows 8.1 Or Greater version %u.%u";
static TCHAR const* OS_WIN10 = L"Windows 10 Or Greater version %u.%u";

DWORD COL_WIDTH_MAIN0 = 110;
DWORD COL_WIDTH_MAIN1 = 270;

std::wstring getOSName()
{
	CString OSVersion = L"";
	OSVERSIONINFOEX info;
	ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((LPOSVERSIONINFOW)&info);

	if (IsWindowsXPOrGreater())
	{
		OSVersion.Format(OS_WINXP, info.dwMajorVersion, info.dwMinorVersion);
	}

	if (IsWindowsXPSP1OrGreater())
	{
		OSVersion.Format(OS_WINXPSP1, info.dwMajorVersion, info.dwMinorVersion);
	}

	if (IsWindowsXPSP2OrGreater())
	{
		OSVersion.Format(OS_WINXPSP2, info.dwMajorVersion, info.dwMinorVersion);
	}

	if (IsWindowsXPSP3OrGreater())
	{
		OSVersion.Format(OS_WINXPSP3, info.dwMajorVersion, info.dwMinorVersion);
	}

	if (IsWindowsVistaOrGreater())
	{
		OSVersion.Format(OS_WINVIS, info.dwMajorVersion, info.dwMinorVersion);
	}

	if (IsWindowsVistaSP1OrGreater())
	{
		OSVersion.Format(OS_WINVIS_SP1, info.dwMajorVersion, info.dwMinorVersion);
	}

	if (IsWindowsVistaSP2OrGreater())
	{
		OSVersion.Format(OS_WINVIS_SP2, info.dwMajorVersion, info.dwMinorVersion);
	}

	if (IsWindows7OrGreater())
	{
		OSVersion.Format(OS_WIN7, info.dwMajorVersion, info.dwMinorVersion);
	}

	if (IsWindows7SP1OrGreater())
	{
		OSVersion.Format(OS_WIN7SP1, info.dwMajorVersion, info.dwMinorVersion);
	}

	if (IsWindows8OrGreater())
	{
		OSVersion.Format(OS_WIN8, info.dwMajorVersion, info.dwMinorVersion);
	}

	if (IsWindows8Point1OrGreater())
	{
		OSVersion.Format(OS_WIN81, info.dwMajorVersion, info.dwMinorVersion);
	}

	if (IsWindows10OrGreater())
	{
		OSVersion.Format(OS_WIN10, info.dwMajorVersion, info.dwMinorVersion);
	}
	/*
	Apps not manifested for Win 8.1 or Win 10 will return the Win 8 OS version value (6.2). 
	To target the apps for Windows 8.1 or Windows 10, include manifest in the project.
	*/
	return OSVersion;
}

MainWindow::MainWindow()
{
	
}

LRESULT MainWindow::OnInit(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_ListView.Attach(GetDlgItem(IDC_LISTCTRL_MAIN));
	m_ListView.InsertColumn(0, COL_HEADER_MAIN_INFO, LVCFMT_CENTER, COL_WIDTH_MAIN0);
	m_ListView.InsertColumn(1, COL_HEADER_MAIN_VALUE, LVCFMT_CENTER, COL_WIDTH_MAIN1);

	int UIRowIter = 0; //row iteration for CListViewCtrl
	
	//Username, Comp name, Workgroup-------------------------------------------------------
	TCHAR  userNameBuf[INFO_BUFFER_SIZE];
	TCHAR  compNameBuf[INFO_BUFFER_SIZE];
	TCHAR  workGroupBuf[INFO_BUFFER_SIZE];

	DWORD  userNameBufCount = INFO_BUFFER_SIZE;
	DWORD  compNameBufCount = INFO_BUFFER_SIZE;
	DWORD  workGroupBufCount = INFO_BUFFER_SIZE;

	GetComputerName(compNameBuf, &compNameBufCount);
	GetUserName(userNameBuf, &userNameBufCount);

	DWORD bufSize = MAX_PATH;
	TCHAR domainNameBuf[MAX_PATH];
	GetComputerNameEx(ComputerNameDnsDomain, domainNameBuf, &bufSize);// temporary solution instead of using NetWkstaGetInfo() 

	m_ListView.InsertItem(UIRowIter, INFO_USERNAME);
	m_ListView.SetItemText(UIRowIter, 1, userNameBuf); //row, col,text
	UIRowIter++;
	m_ListView.InsertItem(UIRowIter, INFO_COMP_NAME);
	m_ListView.SetItemText(UIRowIter, 1, compNameBuf); //row, col,text
	UIRowIter++;
	m_ListView.InsertItem(UIRowIter, INFO_DOMAIN_NAME);
	m_ListView.SetItemText(UIRowIter, 1, domainNameBuf); //row, col,text
	UIRowIter++;

	//Get OS Name----------------------------------------------------------
	std::wstring OSName = getOSName();
	m_ListView.InsertItem(UIRowIter, INFO_OS_NAME);
	m_ListView.SetItemText(UIRowIter, 1, &OSName[0]); //row, col,text
	UIRowIter++;
	
	//Get Processor name--------------------------------------------------------
	int cpuInfo[4] = { -1 };
	char cpuBrand[INFO_BUFFER_SIZE];
	__cpuid(cpuInfo, 0x80000000);
	unsigned int nExIds = cpuInfo[0];
	memset(cpuBrand, 0, sizeof(cpuBrand));

	// Get the information associated with each extended ID.
	for (int i = 0x80000000; i <= nExIds; ++i) {
		__cpuid(cpuInfo, i);
		// Interpret CPU brand string.
		if (i == 0x80000002)
			memcpy(cpuBrand, cpuInfo, sizeof(cpuInfo));
		else if (i == 0x80000003)
			memcpy(cpuBrand + 16, cpuInfo, sizeof(cpuInfo));
		else if (i == 0x80000004)
			memcpy(cpuBrand + 32, cpuInfo, sizeof(cpuInfo));
	}

	//Convert char to wchar
	const WCHAR* cpuBrandWChar;
	int nChars = MultiByteToWideChar(CP_ACP, 0, (char*)&cpuBrand, -1, NULL, 0);
	cpuBrandWChar = new WCHAR[nChars];
	MultiByteToWideChar(CP_ACP, 0, (char*)&cpuBrand, -1, (LPWSTR)cpuBrandWChar, nChars);

	m_ListView.InsertItem(UIRowIter, INFO_PROCESSOR_NAME);
	m_ListView.SetItemText(UIRowIter, 1, cpuBrandWChar); //row, col,text
	UIRowIter++;
	delete[] cpuBrandWChar;

	//Get IPv4-------------------------------------------------------------
	char host[INFO_BUFFER_SIZE];
	host[INFO_BUFFER_SIZE - 1] = '\0';
	char* ip;
	struct hostent* host_entry;
	int hostname;
	WSADATA wsaData;

	//This code is required before calling gethostname (WSACleanup() is in the end)
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		//Notify failure
		return FALSE;
	}

	//TODO: should use the getaddrinfo instead of the gethostbyname 
	hostname = gethostname(host, sizeof(host)); //return 0 if succeed
	host_entry = gethostbyname(host);
	ip = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0])); //Convert into IP string

	//Convert char to wchar
	const WCHAR* IP_wchar;
	int nChars_IP = MultiByteToWideChar(CP_ACP, 0, ip, -1, NULL, 0);
	IP_wchar = new WCHAR[nChars_IP];
	MultiByteToWideChar(CP_ACP, 0, ip, -1, (LPWSTR)IP_wchar, nChars_IP);
	
	m_ListView.InsertItem(UIRowIter, INFO_IPv4);
	m_ListView.SetItemText(UIRowIter, 1, IP_wchar); //row, col,text
	UIRowIter++;
	delete[] IP_wchar;

	//Get IPv6--------------------------------------------------------
	//TODO: Iterate over all available sockets instead of only just the top of linked list

	char port[INFO_BUFFER_SIZE] = "80";
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		//Notify failure
		return 1;
	}

	int err = WSAGetLastError();
	INT iRetval;
	DWORD dwRetval;
	int i = 1;
	struct addrinfo* result = NULL;
	struct addrinfo* ptr = NULL;
	struct addrinfo hints;
	struct sockaddr_in* sockaddr_ipv4;
	LPSOCKADDR sockaddr_ip;
	DWORD ipbufferlength = IP_LENGTH;
	char ipstringbuffer[INFO_BUFFER_SIZE]; //for IPv6

	// Setup the hints address info structure
	// which is passed to the getaddrinfo() function
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Call getaddrinfo(). If the call succeeds,
	// the result variable will hold a linked list
	// of addrinfo structures containing response information
	dwRetval = getaddrinfo(host, port, &hints, &result);
	if (dwRetval != 0) {
		//Notify failure
		WSACleanup();
		return 1;
	}

	// Retrieve each address and print out the hex bytes
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		switch (ptr->ai_family) {
		case AF_INET:
			sockaddr_ipv4 = (struct sockaddr_in*) ptr->ai_addr;
			break;

		case AF_INET6:
			// the InetNtop function is available on Windows Vista and later
			// We use WSAAddressToString since it is supported on Windows XP and later
			sockaddr_ip = (LPSOCKADDR)ptr->ai_addr;
			// The buffer length is changed by each call to WSAAddresstoString
			// So we need to set it for each iteration through the loop for safety
			ipbufferlength = 46;

			iRetval = WSAAddressToString(sockaddr_ip, (DWORD)ptr->ai_addrlen, NULL,
				(LPWSTR)ipstringbuffer, &ipbufferlength);
			if (iRetval) {
				//Notify failure
			}
			break;

		default:
			break;
		}//end of switch

	}//end of for loop
	
	m_ListView.InsertItem(UIRowIter, INFO_IPv6);
	m_ListView.SetItemText(UIRowIter, 1, (LPCTSTR)ipstringbuffer); //row, col,text
	UIRowIter++;

	freeaddrinfo(result);
	WSACleanup();

	return 0;
}

LRESULT MainWindow::OnDetailProcessButtonClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	dlgListOfProcess.DoModal();
	return 0;
};

LRESULT MainWindow::OnDetailInstalledProgramButtonClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{	
	dlgListOfInstalledPrograms.DoModal();
	return 0;
};

LRESULT MainWindow::OnDetailServicesButtonClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	
	dlgListOfService.DoModal();
	return 0;
};

LRESULT MainWindow::OnClose(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DestroyWindow();
	return 0;
}

LRESULT MainWindow::OnCloseButtonClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DestroyWindow();
	return 0;
}

LRESULT MainWindow::OnDestroy(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0);
	return 0;
}