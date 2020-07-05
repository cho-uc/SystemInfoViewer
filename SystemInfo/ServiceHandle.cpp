#include "stdafx.h"
#include "ServiceHandle.h"

void ServiceHandle::Close()
{
    if (_handle != nullptr)
        ::CloseServiceHandle(_handle);
}

ServiceHandle& ServiceHandle::operator=(SC_HANDLE const handle)
{
    if (_handle != handle)
    {
        Close();

        _handle = handle;
    }
    return *this;
}

ServiceHandle& ServiceHandle::operator=(ServiceHandle&& other)
{
    if (this != &other)
    {
        _handle = std::move(other._handle);
        other._handle = nullptr;
    }
    return *this;
}