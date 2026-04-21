/*
Authors: Mark St. Michell and Davis Brooks
Date: Spring 2026

Purpose:
*/

#ifndef WIRE_H
#define WIRE_H

#include <string>
#include <vector>

using namespace std;

class Gate;

class Wire {

public:
    enum state {HI, LO, UND};
    Wire(state initState = UND, string name = "", int index = -1);
    void setState(state);
    void setHistory(state, int, Wire*);            //State and time it's set
    void setDrives(vector<Gate*>);          //Set all of the drives (not sure if we need this one)
    void pushDrive(Gate*);                  //Adds one drive
    state getState() const;
    string getName() const;
    vector<Gate*> getDrives() const;
    int getIndex() const;
    vector<state> getHistory() const;

private:
    state curState;
    state prevState;
    string name;
    vector<Gate*> drives;
    int index;
    int lastModifiedTime;
    static int numWires;
    vector<state> history;
};

#endif