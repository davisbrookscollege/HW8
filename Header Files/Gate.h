//Header file test
//MORE comments!
#include "Wire.h"

class Wire;

class Gate {
private:
    enum type {NOT, AND, NAND, OR, NOR, XOR, XNOR};
    Wire *in1, *in2, *out;
    int delay;

public:
    Gate(type, int delay, Wire *in1, Wire *in2, Wire *out);
    int getDelay() const;
    Wire* getInput(int) const;
    Wire* getOutput(int) const;
    Wire::state evaluate(type, int delay, Wire *in1, Wire *in2, Wire *out); //may change return type
};