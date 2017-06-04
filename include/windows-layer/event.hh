#pragma once

class Event
{
public:
    static Event *create(const char *name);

public:
    virtual ~Event() {}

    virtual void trigger() = 0;
    virtual void wait() = 0;
    virtual void wait(int millisecondTimeout) = 0;
};
