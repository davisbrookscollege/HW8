/*
Authors: Mark St. Michell and Davis Brooks
Date: Spring 2026

Purpose: This program simulates a logic circuit based
on two given input files. It will output the waveform
for each of the wires over time. It can handle the 7
main types of logic gates, each with 2 inputs, beside
the NOT gate.
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
    vector<Wire*> wires; //vector of wires
    priority_queue<Event> events; 
    Event e;
    int finalTime = 0;
    string wireFile;
    string breakLine = "-----------------------------------------------------------------------------";

    cout << "Store circuit description and vector file in a folder called 'Circuit Files'" << endl;
    cout << breakLine << endl;
    cout << "Input circuit file root name: ";
    cin >> wireFile;
    cout << breakLine << endl;

    initializeCircuit(events, wires, wireFile); //reads files, then initializes wires, gates, and known events

    //runs through all events
    while (!events.empty()) {
	    e = events.top();
	    events.pop(); //remove event
	    handleEvent(wires, e, events); //set the wire values as specified in e AT THE END of this function
    }

    //The next 5 lines fill in the characters so that the program prints properly
    finalTime = e.getTime();

    for (int i = 0; i < wires.size(); i++) {
        wires.at(i)->setHistory(wires.at(i)->getState(), finalTime);
    }

    cout << "Circuit simulation:" << endl << endl;

    printCircuit(wires);

    return 0;
}


//Opens and parses the circuit vector file
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
        cout << "Failed to open Circuit Files/" << fileName << "_v.txt" << endl;
    }

    //Remove the top line
    getline(inFS, wordStr);

    //Supply each event with its properties
    while (!inFS.eof()) {

        //This breaks if there's an extra line at the end of the file.
        inFS >> wordStr;

        //Get the wire
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

//Opens and parses the circuit description file
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
        cout << "Failed to open Circuit Files/" << fileName << ".txt" << endl;
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

//cleanly initializes the program so that it is ready to handle events
void initializeCircuit(priority_queue<Event>& events, vector<Wire*>& wires, string circuitName) {

    initalizeWiresAndGates(wires, circuitName);
    initializeCircuitEvents(events, circuitName, wires);
}

//handles a singular event and sets wire values accordingly. Adds new events as needed.
void handleEvent(vector<Wire*>& wires, Event e, priority_queue<Event>& events) {
    int wireIndex = e.getWire();
    Wire* wire = getWireByIndex(wires, wireIndex);
    vector<Gate*> gates = wire->getDrives();
    int time = e.getTime();

    //prevents infinite feedback loops
    if (time < 50) {

    //runs through every gate that is driven by the wire we're handling
        for (int i = 0; i < gates.size(); ++i) {

            Gate* curGate            = gates.at(i);
            Wire* outputWire         = curGate->getOutput();
            int nextTime             = e.getTime() + curGate->getDelay();
                
    // Evaluates the future state of the gate before the change (what it would be if the event did not occur)
            Wire::state past         = curGate->evaluate(wire);

    // Evaluates the future state of the gate after the change (what it will be after the event occurs)
            Wire::state future       = curGate->evaluate(wire, e.getState());

            if (past != future) {
                int outWireIndex = outputWire->getIndex();

                Event futureEvent = Event(outWireIndex, nextTime, future);
                events.push(futureEvent);
            }
        }
    }

    wire->setState(e.getState()); // Sets the wire value
    wire->setHistory(wire->getState(), time); //adds to the wire history
}

//prints the results
void printCircuit(const vector<Wire*>& wires) {

    bool isSneakyWire = false;

    for (int i = 0; i < wires.size(); ++i) {

        isSneakyWire = wires.at(i)->getName() == "?";

        if (!isSneakyWire) {

            if (i != 0) {cout << "      |" << endl;}

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
        }
    }
    cout << endl;
}

//Returns a wire given an index. If the wire doesn't exist it creates a new one
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

//returns the wire index given the wire name
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