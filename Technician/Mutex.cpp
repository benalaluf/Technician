#include "Mutex.h"

#include <iostream>

Mutex::Mutex(LPSECURITY_ATTRIBUTES mutexAtterbuites, LPCSTR name, DWORD flags, DWORD desiredAccess) {
    m_handle = CreateMutexExA(mutexAtterbuites, name, flags, desiredAccess);
}

Mutex::~Mutex() {
    ReleaseMutex(m_handle);
}

HANDLE Mutex::getHandle() const {
    return m_handle;
}

DWORD Mutex::waitForSingleObject(DWORD milliseconds) {
    return WaitForSingleObject(m_handle, 0);
}
