/*
Authors: Mark St. Michell and Davis Brooks
Date: Spring 2026

Purpose:
*/

#ifndef GATE_H
#define GATE_H

#include "Wire.h"

class Gate {
public:
    enum type {NOT, AND, NAND, OR, NOR, XOR, XNOR};

    Gate(type gateType, int delay, Wire *in1, Wire *in2, Wire *out); //FIXME: we may need to default *in2 for not gates
    int getDelay() const;
    Wire* getInput(int) const;
    Wire* getOutput() const;
    Wire::state evaluate(type, int delay, Wire *in1, Wire *in2, Wire *out); //may change return type

private:
    type gateType;
    Wire *in1, *in2, *out;
    int delay;
};

#endif