/*
Authors: Mark St. Michell and Davis Brooks
Date: Spring 2026

Purpose: Event class specification file.
*/

#ifndef EVENT_H
#define EVENT_H

#include "Wire.h"

class Event {
public:

    Event();
    Event(int wire, int time, Wire::state state);
    bool operator<(const Event &rhs) const;
    int getOOA() const;
    int getTime() const;
    int getWire() const;
    Wire::state getState() const;

private:

    static int numEvents;
    int orderOfArrival;
    int time;           // What time the event will execute
    int wire;           //Which wire it's affecting
    Wire::state state;  //State the wire should be changed too

};

#endif