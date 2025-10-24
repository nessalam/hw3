#ifndef EVENT_H
#define EVENT_H
#include "wire.h"

struct Event
{
    uint64_t time;
    Wire* wire;
    char state;
};

typedef struct EventLess {
        //write the operator() required to make this a functor that compares Events by time
        bool operator()(const Event* a, const Event* b){
            return a->time < b->time; //if b time bigger, it goes down in min-heap
            //was reversed when i did return a->time > b->time, resulted in fialed outputs
        }
} EventLess;
	
#endif
