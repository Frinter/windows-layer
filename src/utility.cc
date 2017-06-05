#include <windows.h>

#include "utility.hh"

class WindowsUtility : public Utility
{
public:
    virtual void sleep(int milliseconds)
    {
        ::Sleep(milliseconds);
    }

    virtual int getTicks()
    {
        return timeGetTime();
    }
};

Utility *Utility::getInstance()
{
    static Utility *instance = NULL;

    if (instance == NULL)
        instance = new WindowsUtility();

    return instance;
}
