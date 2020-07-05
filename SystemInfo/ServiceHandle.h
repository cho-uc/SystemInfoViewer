/*
ServiceHandle.h
*/

#pragma once

//#include "windows.h"
//#include <utility> //for std:::move

class ServiceHandle
{
private :
    SC_HANDLE _handle = nullptr;

    void Close();

public:
    ServiceHandle(SC_HANDLE const handle = nullptr) noexcept :_handle(handle) {}
    ServiceHandle(ServiceHandle&& other) noexcept : _handle(std::move(other._handle)) {}
    ServiceHandle& operator=(SC_HANDLE const handle);
    ServiceHandle& operator=(ServiceHandle&& other);
    operator SC_HANDLE() const noexcept { return _handle; }
    explicit operator bool() const noexcept { return _handle != nullptr; }
    ~ServiceHandle()
    {
        Close();
    }
};