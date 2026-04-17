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


using namespace std;

void initializeCircuit(priority_queue<Event>& events, vector<Wire*> wires);
void printCircuit(vector<Wire*> wires);
void handleEvent(Event e);

int main () {
    //1. Read CD
    //2. Read VD
    //3. Simulate
    //4. Print results

    
    vector<Wire*> wires; //vector of wires
    priority_queue<Event> events; 

    initializeCircuit(events, wires); //reads files, then initializes wires, gates, and known events

    while (!events.empty()) {
	    Event e = events.top();
	    events.pop(); //remove event
	    handleEvent(e); //set the wire values as specified in e AT THE END of this function
    }

    printCircuit(wires);

    return 0;
}


void initializeCircuit(priority_queue<Event>& events, vector<Wire*> wires) {

}


void handleEvent(Event e) {

}

void printCircuit(vector<Wire*> wires) {

}