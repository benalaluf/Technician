#pragma once

#include "Mutex.h"
#include "Exception.h"

#define MUTEX_NAME "Technician"

/*
* Allow the program to run only one time simultaneously 
*/
class RunGuard {
  public:
    Mutex *m_mutex;
    RunGuard();
    ~RunGuard();
};


class RunGuardException : public Exception {
  public:
    RunGuardException(int status, std::string funcName);
};
