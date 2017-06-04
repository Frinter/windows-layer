#include <stdexcept>
#include <windows.h>

#include "mutex.hh"

using System::Mutex;

class WindowsMutex : public Mutex
{
public:
    WindowsMutex() {
        inCriticalSection = false;
        InitializeCriticalSection(&_criticalSection);
    }

    virtual ~WindowsMutex() {
        DeleteCriticalSection(&_criticalSection);
    }

    virtual void lock() {
        EnterCriticalSection(&_criticalSection);
        inCriticalSection = true;
    }

    virtual void unlock() {
        if (inCriticalSection)
        {
            inCriticalSection = false;
            LeaveCriticalSection(&_criticalSection);
        }
    }

private:
    CRITICAL_SECTION _criticalSection;
    bool inCriticalSection;

    WindowsMutex(const WindowsMutex &o) = delete;
};

Mutex *Mutex::create()
{
    return new WindowsMutex();
}
