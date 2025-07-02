#pragma once

#include <windows.h>

#include "Exception.h"

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

/*
 * Defines Errors for the Mutex module.
 */
class MutexException : public Exception {
  public:
    MutexException(int status, std::string funcName);
};
