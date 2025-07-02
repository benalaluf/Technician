#include "Mutex.h"

#include <iostream>

Mutex::Mutex() {
    // 
}

Mutex::Mutex(LPSECURITY_ATTRIBUTES mutexAtterbuites, LPCSTR name, DWORD flags, DWORD desiredAccess) {
    m_handle = CreateMutexExA(mutexAtterbuites, name, flags, desiredAccess);

    if (m_handle == NULL) {
        throw MutexException(1, "Invalid mutex handle"); 
    }
}

Mutex::~Mutex() {
    ReleaseMutex(m_handle);
}

HANDLE Mutex::getHandle() const {
    return m_handle;
}

DWORD Mutex::waitForSingleObject(DWORD milliseconds) {
    return WaitForSingleObject(m_handle, milliseconds);
}

MutexException::MutexException(int status, std::string funcName): Exception(status, funcName) {
    // Intentionally left empty
}
