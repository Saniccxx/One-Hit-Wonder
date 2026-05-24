#pragma once

class Display {
public:
    virtual ~Display() = default;

    virtual void init() = 0;
    virtual void tick() = 0;
};

