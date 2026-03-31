//Header file test
//MORE comments!
#include "Wire.h"

class Wire;

class Gate {
public:
    enum type {NOT, AND, NAND, OR, NOR, XOR, XNOR};

    Gate(type gateType, int delay, Wire *in1, Wire *in2, Wire *out);
    int getDelay() const;
    Wire* getInput(int) const;
    Wire* getOutput(int) const;
    Wire::curState evaluate(type, int delay, Wire *in1, Wire *in2, Wire *out); //may change return type

private:
    type gateType;
    Wire *in1, *in2, *out;
    int delay;
};