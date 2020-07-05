/* ServiceEnumerator.h
*/

#pragma once

#include "ServiceContants.h"
#include "ServiceHandle.h"

class ServiceEnumerator
{
public:
    static std::vector<ServiceStatusProcess> EnumerateServices(
        ServiceType const type = ServiceType::All,
        ServiceState const state = ServiceState::All,
        ServiceString const* machine = nullptr,
        ServiceString const* dbname = nullptr,
        ServiceString const* groupName = nullptr);  

};