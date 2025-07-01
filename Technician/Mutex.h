#pragma once

#include <windows.h>

#define MUTEX_NAME "Technician"

class Mutex {
  public:
    Mutex(LPSECURITY_ATTRIBUTES mutexAtterbuites, LPCSTR name, DWORD flags, DWORD desiredAccess);
    ~Mutex();

    HANDLE getHandle() const;

    DWORD waitForSingleObject(DWORD milliseconds);

  private:
    HANDLE m_handle;
};
