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

void initializeCircuitEvents(priority_queue<Event>& events, string fileName, const vector<Wire*>& wires);
void initalizeWiresAndGates(vector<Wire*>& wires, string fileName);
void initializeCircuit(priority_queue<Event>& events, vector<Wire*>& wires, string circuitName);
void printCircuit(const vector<Wire*>& wires);
void handleEvent(vector<Wire*>& wires, Event e, priority_queue<Event>& events);
Wire* getWireByIndex(vector<Wire*>& wires, int wireIndex);
int getWireIndexByName(const vector<Wire*>& wires, string name);

int main () {
    //1. Read CD
    //2. Read VD
    //3. Simulate
    //4. Print results

    
    vector<Wire*> wires; //vector of wires
    priority_queue<Event> events; 

    initializeCircuit(events, wires, "flipflop"); //reads files, then initializes wires, gates, and known events

    while (!events.empty()) {
	    Event e = events.top();
	    events.pop(); //remove event
	    handleEvent(wires, e, events); //set the wire values as specified in e AT THE END of this function
    }

    printCircuit(wires);

    return 0;
}



void initializeCircuitEvents(priority_queue<Event>& events, string fileName, const vector<Wire*>& wires) {

    ifstream inFS;
    string wordStr;
    string wireStr;
    string timeStr;
    string stateStr;
    int wire;
    int time;
    int stateInt;
    State state;

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
        //FIX ME: use wire's name to get the wire
        inFS >> wireStr;
        wire = getWireIndexByName(wires, wireStr);

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

    initalizeWiresAndGates(wires, circuitName);
    initializeCircuitEvents(events, circuitName, wires);
}

void handleEvent(vector<Wire*>& wires, Event e, priority_queue<Event>& events) {

    //gather values needed to evaluate the event
    int wireIndex = e.getWire();
    Wire* wire = getWireByIndex(wires, wireIndex);
    vector<Gate*> gates = wire->getDrives();
    int time = e.getTime();
    bool newEvent = true;
    priority_queue<Event> eventsCopy = events;

    //Add wire value to the history
    wire->setState(e.getState());
    wire->setHistory(wire->getState(), time);

    //Ensures no infinite loops
    if (time < 20){

        //evaluate gate(s) (don't forget gate delay)
        //for loop iterates through all the gates which are driven by the wire.
        //Then creates a new event if its output wire is changed
        for (int i = 0; i < gates.size(); ++i) {
        
            //the following lines retrieve the information needed to evalute the gate
            Gate* curGate = gates.at(i);
            Wire* outputWire = curGate->getOutput();
            Gate::type gateType = curGate->getType();
            Wire* input1 = curGate->getInput1();
            Wire* input2 = curGate->getInput2();
            int delay = curGate->getDelay();
            int nextTime = e.getTime() + curGate->getDelay();
            Wire::state oldState = outputWire->getState();

            //Evaluates gate
            Wire::state newState = curGate->evaluate(gateType, delay, input1, input2, outputWire);

/*
            eventsCopy = events;

            for (int i = 0; i < eventsCopy.size(); i++) {
                if (eventsCopy.top().getTime() == nextTime && eventsCopy.top().getWire() == outputWire->getIndex()){
                    newEvent = false;
                }
                eventsCopy.pop();
            }

            //create new event if there isn't one already
            if (newEvent) {
                int outWireIndex = outputWire->getIndex();

                Event futureEvent = Event(outWireIndex, nextTime, newState);
                events.push(futureEvent);
            }

*/
            int outWireIndex = outputWire->getIndex();

            //creates new event
            Event futureEvent = Event(outWireIndex, nextTime, newState);
            events.push(futureEvent);  

        }
    }
}

void printCircuit(const vector<Wire*>& wires) {
    cout << "Wire traces:" << endl;
    
    for (int i = 0; i < wires.size(); ++i) {
        cout << "    " << wires.at(i)->getName() << " | ";
        for (int j = 0; j < wires.at(i)->getHistory().size(); ++j) {
            if (wires.at(i)->getHistory().at(j) == State::HI) {
                cout << "-";
            }
            else if (wires.at(i)->getHistory().at(j) == State::LO) {
                cout << "_";
            }
            else if (wires.at(i)->getHistory().at(j) == State::UND) {
                cout << "x";
            }
        }
        cout << endl;
        cout << "      |" << endl;

        if (i == wires.size() - 1) {
            cout << "       _______________________" << endl;
        }
    }
}

//Returns a wire given an index
//If the wire doesn't exist it creates a new one
Wire* getWireByIndex(vector<Wire*>& wires, int wireIndex) {

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

int getWireIndexByName(const vector<Wire*>& wires, string name) {

    Wire *curWire = nullptr;
    int index = -1;

    for (int i = 0; i < wires.size(); i++){
        curWire = wires.at(i);
        if (curWire->getName() == name) {
            index = curWire->getIndex();
        }
    }

    return index;
}