/*
Authors: Mark St. Michell and Davis Brooks
Date: Spring 2026

Purpose:
*/

#include <iostream>
#include <string>
#include "Wire.h"

using namespace std;

typedef Wire::state state;

int Wire::numWires = -1;

//Constructs the class with minimal default values
Wire::Wire(state initState, string initName, int initIndex):
    curState(initState), name(initName), index(initIndex) {
    drives = {};
    numWires++;
    history = {};
    lastModifiedTime = 0;
    prevState = state::UND;
}

//Sets the current state of the wire
void Wire::setState(state inputState) {
    curState = inputState;
}

//Pushes back 1 state to the history
void Wire::setHistory(state inputState, int setTime) {

    int curTime = lastModifiedTime;

    while (curTime < setTime) {

        history.push_back(prevState);
        curTime++;

    }

    history.push_back(inputState);
    lastModifiedTime = setTime;
    prevState = inputState;
}

//Assignes drives with the input drives
void Wire::setDrives(vector<Gate*> inputDrives) {
    drives = inputDrives;
}

void Wire::pushDrive(Gate *gate) {
    drives.push_back(gate);
}

//Returns the current state of the wire;
state Wire::getState() const {
    return curState;
}

//Returns the name of the wire
string Wire::getName() const {
    return name;
}

//Returns a reference to the drivers
//FIX ME! May need to return by reference
vector<Gate*> Wire::getDrives() const {
    return drives;
}

//Returns the index of the wire
int Wire::getIndex() const {
    return index;
}

//Returns the wire history
//FIX ME! May need to return by reference
vector<state>  Wire::getHistory() const {
    return history;
}