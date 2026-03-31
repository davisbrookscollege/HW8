#include <iostream>
#include <string>
#include "Wire.h"

using namespace std;

typedef Wire::state state;

//STUB!
Wire::Wire(state s, string n, vector<Gate*> d, int i) {

}

//STUB!
void Wire::setVal(state s) {

}

//STUB!
void Wire::setHistory(state s) {

}

//STUB!
void Wire::setDrives(vector<Gate*> g) {

}

//STUB!
state Wire::getState() {
    state s;
    return s;
}

//STUB!
string Wire::getName() {
    string s;
    return s;
}

//STUB!
vector<Gate*> Wire::getDrives() {
    vector<Gate *> g;
    return g;
}

//STUB!
int Wire::getIndex() {
    int i;
    return i;
}

//STUB!
vector<state>  Wire::getHistory() {
    vector<state> s;
    return s;
}