#include <iostream>
#include <string>
#include "Wire.h"

using namespace std;

typedef Wire::state state;

int Wire::numWires = -1;

//Constructs the class with minimal default values
Wire::Wire(state initState, string initName, vector<Gate*> initDrives):
    curState(initState), name(initName), drives(initDrives) {
    numWires++;
    index = numWires;
    history = {};
}

//Sets the current state of the wire
void Wire::setVal(state inputState) {
    curState = inputState;
}

//Pushes back 1 state to the history
void Wire::setHistory(state inputState) {
    history.push_back(inputState);
}

//Assignes drives with the input drives
void Wire::setDrives(vector<Gate*> inputDrives) {
    drives = inputDrives;
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