#pragma once

#include <windows.h>

#define MUTEX_NAME "Technician"

/*
* WinAPI Mutex wrapper 
*/
class Mutex {
  public:
    Mutex();
    Mutex(LPSECURITY_ATTRIBUTES mutexAtterbuites, LPCSTR name, DWORD flags, DWORD desiredAccess);
    ~Mutex();

    /*
    * returns handle to mutex
    */
    HANDLE getHandle() const;
    
    /*
    * wraps WaitForSingleObject
    */
    DWORD waitForSingleObject(DWORD milliseconds);

  private:
    HANDLE m_handle;
};
