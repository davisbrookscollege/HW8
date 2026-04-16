/*
Authors: Mark St. Michell and Davis Brooks
Date: Spring 2026

Purpose:
*/

#include "Event.h";

int Event::numEvents = 0;

Event::Event(int w, int t, Wire::state s) : wire(w), time(t), state(s) {

    orderOfArrival = numEvents;
    numEvents++;
}

bool Event::operator<(Event &rhs){

    if (time == rhs.getTime()){
        return orderOfArrival < rhs.getOOA();
    }
    else {
        return time < rhs.getTime();
    }
}

int Event::getOOA(){
    return orderOfArrival;
}

int Event::getTime(){
    return time;
}







