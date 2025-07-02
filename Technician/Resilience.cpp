#include "Resilience.h"

RunGuard::RunGuard() {
    try {
        m_mutex = new Mutex(NULL, MUTEX_NAME, NULL, MUTEX_ALL_ACCESS);
        DWORD wait = m_mutex->waitForSingleObject(0);

        if (wait != 0) {
            throw RunGuardException(1, "Process Is Already running");
        }
    } catch (const MutexException& error) {
        throw RunGuardException(1, "Mutex Error" + error.funcName);
    }
}

RunGuard::~RunGuard() {
    delete m_mutex;
}

RunGuardException::RunGuardException(int status, std::string funcName) : Exception(status, funcName) {
    // Intentionally left empty
}
