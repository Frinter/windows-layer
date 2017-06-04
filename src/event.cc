#include <windows.h>

#include "event.hh"

class WindowsEvent : public Event
{
public:
    WindowsEvent(const char *name)
    {
        _eventHandle = CreateEvent(NULL, true, false, name);
        ResetEvent(_eventHandle);
    }

    virtual void trigger()
    {
        SetEvent(_eventHandle);
    }

    virtual void wait()
    {
        WaitForSingleObject(_eventHandle, INFINITE);
    }

    virtual void wait(int millisecondTimeout)
    {
        WaitForSingleObject(_eventHandle, millisecondTimeout);
    }

private:
    HANDLE _eventHandle;
};

Event *Event::create(const char *name)
{
    return new WindowsEvent(name);
}
