#pragma once

class Utility {
public:
    static Utility *getInstance();

public:
    virtual void sleep(int milliseconds) = 0;
    virtual int getTicks() = 0;
};
