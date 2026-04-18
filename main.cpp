/*
Authors: Mark St. Michell and Davis Brooks
Date: Spring 2026

Purpose:
*/

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "Header Files/Event.h"
#include "Header Files/Wire.h"
#include "Header Files/Gate.h"

typedef Wire::state State;
typedef Gate::type gateType;

using namespace std;

void initializeCircuitEvents(priority_queue<Event>& events, string fileName);
void initalizeWiresAndGates(vector<Wire*>& wires, string fileName);
void initializeCircuit(priority_queue<Event>& events, vector<Wire*>& wires, string circuitName);
void printCircuit(vector<Wire*> wires);
void handleEvent(Event e);
Wire* getWireByIndex(vector<Wire*> wires, int wireIndex);

int main () {
    //1. Read CD
    //2. Read VD
    //3. Simulate
    //4. Print results

    
    vector<Wire*> wires; //vector of wires
    priority_queue<Event> events; 

    initializeCircuit(events, wires, "flipflop"); //reads files, then initializes wires, gates, and known events

    //This output purely for testing purposes
    for (Wire *w : wires) {
        cout << w->getName() << " " << w->getIndex() << endl;
        for (Gate *g : w->getDrives()) {
            cout << "    " << g->getGateTypeStr() << endl;
        }
    }

    while (!events.empty()) {
	    Event e = events.top();
	    events.pop(); //remove event
	    handleEvent(e); //set the wire values as specified in e AT THE END of this function
    }

    printCircuit(wires);

    return 0;
}



void initializeCircuitEvents(priority_queue<Event>& events, string fileName) {

    ifstream inFS;
    string wordStr;
    string wireStr;
    string timeStr;
    string stateStr;
    int wire;
    int time;
    int stateInt;
    State state;

    int wireDummy = 0;

    //Open the file
    inFS.open("Circuit Files/" + fileName + "_v.txt");

    if (!inFS.is_open()) {
        cout << "failed to open " << fileName << endl;
    }

    //Remove the top line
    getline(inFS, wordStr);

    //Supply each event with its properties
    while (!inFS.eof()) {

        //This breaks if there's an extra line at the end of the file.
        inFS >> wordStr;

        //Get the wire
        //FIX ME! Need to use the already created wire's list to figure out which wire this string refers to.
        inFS >> wireStr;
        wire = wireDummy++;

        //Get the time
        inFS >> timeStr;
        time = stoi(timeStr);

        //Get the state
        inFS >> stateStr;
        int stateInt = stoi(stateStr);
        if (stateInt == 1) {
            state = State::HI;
        }
        else {
            state = State::LO;
        }

        Event e = Event(wire, time, state);
        events.push(e);
    }

    inFS.close();
}

void initalizeWiresAndGates(vector<Wire*>& wires, string fileName) {

    ifstream inFS;

    string wordStr;
    bool isNotGate = false;

    string wireName;
    string wireIndexStr;
    int wireIndex;

    string delayStr;
    int delay;

    string input1Str;
    int input1Int;
    Wire *input1;

    string input2Str;
    int input2Int;
    Wire *input2;

    string outputStr;
    int ouputInt;
    Wire *output;

    vector<Gate*> wireDrives;

    //Open the file
    inFS.open("Circuit Files/" + fileName + ".txt");

    if (!inFS.is_open()) {
        cout << "failed to open " << fileName << endl;
    }

    //Remove the goofy random line at the top
    getline(inFS, wordStr);

    
    while (!inFS.eof()) {

        inFS >> wordStr;

        //Read from file and create the wires
        if (wordStr == "INPUT" || wordStr == "OUTPUT") {

            inFS >> wireName;
            inFS >> wireIndexStr;
            wireIndex = stoi(wireIndexStr);

            Wire* w = new Wire(State::UND, wireName, wireIndex);

            wires.push_back(w);
        }

        //Read and intialize the gates
        else {

            isNotGate = false;

            //Read and intialize the delay
            inFS >> delayStr;
            delayStr.erase((delayStr.end() - 2), delayStr.end());
            delay = stoi(delayStr);

            //Read and intialize the inputs and output
            inFS >> input1Str;
            input1Int = stoi(input1Str);
            input1 = getWireByIndex(wires, input1Int);

            if (wordStr == "NOT") {
                input2 = nullptr;
                isNotGate = true;
            }
            else {
                inFS >> input2Str;
                input2 = getWireByIndex(wires, stoi(input2Str));

            }

            inFS >> outputStr;
            output = getWireByIndex(wires, stoi(outputStr));

            cout << wordStr << " " << delay << " " << input1Str << " " << input2Str << " " << outputStr << endl;

            //Intialize the gate
            Gate *g = new Gate(wordStr, delay, input1, input2, output);

            //Set which wires drive the gate
            input1->pushDrive(g);
            if (!isNotGate) { input2->pushDrive(g); }
        }   
    }

    inFS.close();
}

void initializeCircuit(priority_queue<Event>& events, vector<Wire*>& wires, string circuitName) {

    initializeCircuitEvents(events, circuitName);
    initalizeWiresAndGates(wires, circuitName);
}

void handleEvent(Event e) {

}

void printCircuit(vector<Wire*> wires) {

}

//Returns a wire given an index
//If the wire doesn't exist it creates a new one
Wire* getWireByIndex(vector<Wire*> wires, int wireIndex) {

    Wire *curWire = nullptr;
    Wire *outputWire = nullptr;

    for (int i = 0; i < wires.size(); i++){
        curWire = wires.at(i);
        if (curWire->getIndex() == wireIndex) {
            outputWire = curWire;
        }
    }

    if (outputWire == nullptr) {
        Wire *w = new Wire(State::UND, "?", wireIndex);
        wires.push_back(w);
        outputWire = w;
    }

    return outputWire;
}