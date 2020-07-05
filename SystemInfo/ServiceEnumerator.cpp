/* ServiceEnumerator.cpp
*/

#include "stdafx.h"
#include "ServiceEnumerator.h"

static TCHAR const* STATUS_STRING_1 = L"Stopped";
static TCHAR const* STATUS_STRING_2 = L"Starting";
static TCHAR const* STATUS_STRING_3 = L"Is stopping";
static TCHAR const* STATUS_STRING_4 = L"Running";
static TCHAR const* STATUS_STRING_5 = L"About to continue";
static TCHAR const* STATUS_STRING_6 = L"Is pausing";
static TCHAR const* STATUS_STRING_7 = L"Paused";
static TCHAR const* STATUS_STRING_0 = L"Unknown";

std::vector<ServiceStatusProcess> ServiceEnumerator::EnumerateServices(
    ServiceType const type /*= ServiceType::All*/,
        ServiceState const state /*= ServiceState::All*/,
        ServiceString const* machine /*= nullptr */,
        ServiceString const* dbname /*= nullptr */,
        ServiceString const* groupName /*= nullptr */ )
{
std::vector<ServiceStatusProcess> ssps;
auto scHandle = ServiceHandle
{
   ::OpenSCManager(
      machine == nullptr ? nullptr : machine->c_str(),
      dbname == nullptr ? nullptr : dbname->c_str(),
      SC_MANAGER_ENUMERATE_SERVICE)
};
auto bytesNeeded = DWORD{ 0 };
auto servicesReturnedCount = DWORD{ 0 };
auto resumeHandle = DWORD{ 0 };

do
{
    if (!EnumServicesStatusEx(
        scHandle,
        SC_ENUM_PROCESS_INFO,
        static_cast<DWORD>(type),
        static_cast<DWORD>(state),
        nullptr,
        0,
        &bytesNeeded,
        &servicesReturnedCount,
        &resumeHandle,
        groupName == nullptr ? nullptr : groupName->c_str()))
    {
        if (ERROR_MORE_DATA == ::GetLastError())
        {
            std::vector<unsigned char> buffer(bytesNeeded, 0);

            if (EnumServicesStatusEx(
                scHandle,
                SC_ENUM_PROCESS_INFO,
                static_cast<DWORD>(type),
                static_cast<DWORD>(state),
                reinterpret_cast<LPBYTE>(buffer.data()),
                bytesNeeded,
                &bytesNeeded,
                &servicesReturnedCount,
                nullptr,
                groupName == nullptr ? nullptr : groupName->c_str()))
            {
                auto essp = reinterpret_cast<LPENUM_SERVICE_STATUS_PROCESS>(buffer.data());

                for (auto i = DWORD{ 0 }; i < servicesReturnedCount; ++i)
                {
                    auto ssp = ServiceStatusProcess{};
                    ssp.ServiceName = essp[i].lpServiceName;
                    ssp.DisplayName = essp[i].lpDisplayName;
                    ssp.Status = essp[i].ServiceStatusProcess;

                    ssp.StatusString = L"";
                    if (essp[i].ServiceStatusProcess.dwCurrentState == SERVICE_STOPPED)
                    {
                        ssp.StatusString = STATUS_STRING_1;
                    }
                    if (essp[i].ServiceStatusProcess.dwCurrentState == SERVICE_START_PENDING)
                    {
                        ssp.StatusString = STATUS_STRING_2;
                    }
                    if (essp[i].ServiceStatusProcess.dwCurrentState == SERVICE_STOP_PENDING)
                    {
                        ssp.StatusString = STATUS_STRING_3;
                    }
                    if (essp[i].ServiceStatusProcess.dwCurrentState == SERVICE_RUNNING)
                    {
                        ssp.StatusString = STATUS_STRING_4;
                    }
                    if (essp[i].ServiceStatusProcess.dwCurrentState == SERVICE_CONTINUE_PENDING)
                    {
                        ssp.StatusString = STATUS_STRING_5;
                    }
                    if (essp[i].ServiceStatusProcess.dwCurrentState == SERVICE_PAUSE_PENDING)
                    {
                        ssp.StatusString = STATUS_STRING_6;
                    }
                    if (essp[i].ServiceStatusProcess.dwCurrentState == SERVICE_PAUSED)
                    {
                        ssp.StatusString = STATUS_STRING_7;
                    }

                    ssps.push_back(ssp);

                }
            }
            else break;
        }
        else break;
    }
} while (resumeHandle != 0);

return ssps;
}