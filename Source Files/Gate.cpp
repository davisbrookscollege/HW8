/*
Authors: Mark St. Michell and Davis Brooks
Dates: Spring 2026

Purpose: This is the implementation for the gate class.
*/

#include "Gate.h"

Gate::Gate(type gateType, int delay, Wire *input1, Wire *input2, Wire *output):
    gateType(gateType), delay(delay), in1(input1), in2(input2), out(output)
{}

int Gate::getDelay() const {
    return delay;
}

//returns a pointer to either input wire 1 or input wire 2
Wire* Gate::getInput(int wireNum) const {
    if (wireNum == in1->getIndex()) {
        return in1;
    }
    return in2;
}

//returns a pointer to the output wire
Wire* Gate::getOutput() const {
    return out;
}

Wire::state Gate::evaluate(type, int delay, Wire *in1, Wire *in2, Wire *out) {

}