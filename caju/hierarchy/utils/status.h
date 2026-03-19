//
// Created by dantas on 24/10/20.
//

#ifndef CAJU_STATUS_H
#define CAJU_STATUS_H

#include <stdio.h>

enum State {
    NILL = 0x00,
    SUCCESS = 0x01,
    NOT_FOUND = 0x02,
    STORAGE_FULL = 0x03,
    OCCUPATION_THRESHOLD_REACHED = 0X04,
    DELAYED = 0X05,
    MISS = 0x06
};

template <class R>
class Status {
public:
    State state;
    R return_value;

    //TODO check if this move can be moving elements that were supposed to be copied 
    Status(State s, R return_value_) : state(s), return_value(std::move(return_value_)) {} 
    Status(R return_value_) : state(SUCCESS), return_value(std::move(return_value_)) {}
    Status(State s) : state(s) {}
};

#endif //CAJU_STATUS_H
