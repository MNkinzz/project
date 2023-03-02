#pragma once

#include <stdint.h>

class Robot;

class BehaviorTree {
public:
    static BehaviorTree *makeBehaviorTree(Robot *r);

public:
    void tick();
    void setTickRate(uint32_t max_tick);

private:
    explicit BehaviorTree(Robot *r);

private:
    void _tick();

private:
    uint32_t tick_cnt_ = 0;
    uint32_t max_tick_ = 0;

private:
    Robot *r_;
};
