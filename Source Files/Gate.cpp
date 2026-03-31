/*
Authors: Mark St. Michell and Davis Brooks
Dates: Spring 2026

Purpose: This is the implementation for the gate class.
*/

#include "Gate.h"

Gate::Gate(type gateType, int delay, Wire *input1, Wire *input2, Wire *output):
    gateType(gateType), delay(delay), in1(input1), in2(input2), out(output) {}

int Gate::getDelay() const {
    return delay;
}

Wire* Gate::getInput(int wireNum) const {

}

Wire* Gate::getOutput(int wireNum) const {

}

Wire::curState Gate::evaluate(type, int delay, Wire *in1, Wire *in2, Wire *out) {

}