#pragma once

class Mutex {
public:
    static Mutex *create();

public:
    virtual ~Mutex() {}

    virtual void lock() = 0;
    virtual void unlock() = 0;
};
