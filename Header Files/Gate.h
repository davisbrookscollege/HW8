/*
Authors: Mark St. Michell and Davis Brooks
Date: Spring 2026

Purpose:
*/

#ifndef GATE_H
#define GATE_H

#include <string>
#include "Wire.h"

class Gate {
public:
    enum type {NOT, AND, NAND, OR, NOR, XOR, XNOR};

    Gate(string gateInput, int delay, Wire *in1, Wire *in2, Wire *out); //FIXME: we may need to default *in2 for not gates
    int getDelay() const;
    //Wire* getInput(int) const;
    Wire* getOutput() const;
    Wire::state evaluate(type, int delay, Wire *in1, Wire *in2, Wire *out); //may change return type
    string getGateTypeStr();
    type getType() const;
    Wire* getInput1();
    Wire* getInput2();

private:
    type gateType;
    string gateTypeStr;
    Wire *in1, *in2, *out;
    int delay;
};

#endif