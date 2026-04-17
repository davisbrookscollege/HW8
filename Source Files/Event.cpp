/*
Authors: Mark St. Michell and Davis Brooks
Date: Spring 2026

Purpose:
*/

#include "Event.h"
#include "Wire.h"

int Event::numEvents = 0;

Event::Event(){ }

Event::Event(int inputWire, int inputTime, Wire::state inputState) {

    wire = inputWire;
    time = inputTime;
    state = inputState;
    orderOfArrival = numEvents;
    numEvents++;
}

bool Event::operator<(const Event &rhs) const {

    if (time == rhs.getTime()){
        return orderOfArrival < rhs.getOOA();
    }
    else {
        return time < rhs.getTime();
    }
}

int Event::getOOA() const {
    return orderOfArrival;
}

int Event::getTime() const{
    return time;
}

int Event::getWire() const{
    return time;
}

Wire::state Event::getState() const{
    return state;
}







