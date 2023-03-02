#include "bt.hpp"

BehaviorTree *BehaviorTree::makeBehaviorTree(Robot *r) {
    BehaviorTree *bt = new BehaviorTree(r);
    return bt;
}

BehaviorTree::BehaviorTree(Robot *r) : r_(r){
}

void BehaviorTree::tick() {
    tick_cnt_ += 1;
    if (tick_cnt_ >= max_tick_) {
        tick_cnt_ = 0;
        _tick();
    }
}

void BehaviorTree::setTickRate(uint32_t max_tick) {
    max_tick_ = max_tick;
}

void BehaviorTree::_tick() {

}

