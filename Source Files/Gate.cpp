/*
Authors: Mark St. Michell and Davis Brooks
Dates: Spring 2026

Purpose: This is the implementation for the gate class.
*/

#include "../Header Files/Gate.h"

Gate::Gate(string gateInput, int delay, Wire *input1, Wire *input2, Wire *output):
    gateTypeStr(gateInput), delay(delay), in1(input1), in2(input2), out(output) {
    
    //Takes a string as gateInput and converts it to a input type
    if (gateInput == "NOT") {
        gateType = type::NOT;
    }
    else if (gateInput == "AND") {
        gateType = type::AND;
    }
    else if (gateInput == "NAND") {
        gateType = type::NAND;
    }
    else if (gateInput == "OR") {
        gateType = type::OR;
    }
    else if (gateInput == "NOR") {
        gateType = type::NOR;
    }
    else if (gateInput == "XOR") {
        gateType = type::XOR;
    }
    else {
        gateType = type::XNOR;
    }
}

int Gate::getDelay() const {
    return delay;
}

Gate::type Gate::getType() const {
    return gateType;
}

Wire* Gate::getInput1() {
    return in1;
}

Wire* Gate::getInput2() {
    return in2;
}

/*

//returns a pointer to either input wire 1 or input wire 2
Wire* Gate::getInput(int wireNum) const {
    if (wireNum == in1->getIndex()) {
        return in1;
    }
    return in2;
}

*/

//returns a pointer to the output wire
Wire* Gate::getOutput() const {
    return out;
}

//evaluates the state of the gate based on the logic provided as parameters
Wire::state Gate::evaluate(type gateStyle, int delay, Wire *in1, Wire *in2, Wire *out) {
    Wire::state gateState = Wire::state::UND;

//layer of conditional statements evaluate the logic based on the type of gate
    if (gateStyle == NOT) {
        //only one input, so in2 is ignored
        if (in1->getState() == Wire::state::HI) {
            gateState = Wire::state::LO;
        }
        else if (in1->getState() == Wire::state::LO) {
            gateState = Wire::state::HI;
        }
        //no need to deal with undefined state because gateState is initialized to UND
        
        return gateState;
    }

    //AND gate logic
    else if (gateStyle == AND) {
        if (in1->getState() == Wire::state::LO || //either are low
            in2->getState() == Wire::state::LO) {
            gateState = Wire::state::LO;
        }
        else if (in1->getState() == Wire::state::HI && //both are high
                 in2->getState() == Wire::state::HI) {
            gateState = Wire::state::HI;
        }
        //no need to deal with undefined state because gateState is initialized to UND

        return gateState;
    }

    //NAND gate logic
    else if (gateStyle == NAND) {
        if (in1->getState() == Wire::state::LO || //either are low
            in2->getState() == Wire::state::LO) {
            gateState = Wire::state::HI;
        }
        else if (in1->getState() == Wire::state::HI && //both are High
                 in2->getState() == Wire::state::HI) {
            gateState = Wire::state::LO;
        }
        //no need to deal with undefined state because gateState is initialized to UND

        return gateState;
    }

    //OR gate logic
    else if (gateStyle == OR) {
        if (in1->getState() == Wire::state::HI || //either are hi
            in2->getState() == Wire::state::HI) {
            gateState = Wire::state::HI;
        }
        else if (in1->getState() == Wire::state::LO && //both are low
            in2->getState() == Wire::state::LO) {
            gateState = Wire::state::LO;
        }
        //no need to deal with undefined state because gateState is initialized to UND

        return gateState;
    }

    //NOR gate logic
    else if (gateStyle == NOR) {
        if (in1->getState() == Wire::state::LO || //either are LO
            in2->getState() == Wire::state::LO) {
            gateState = Wire::state::HI;
        }
        else if (in1->getState() == Wire::state::HI && //both are HI
            in2->getState() == Wire::state::HI) {
            gateState = Wire::state::LO;
        }
        //no need to deal with undefined state because gateState is initialized to UND

        return gateState;
    }

    //XOR gate logic
    else if (gateStyle == XOR) {
        if (in1->getState() == Wire::state::LO && //if the wires have different values
            in2->getState() == Wire::state::HI ||
            in1->getState() == Wire::state::HI &&
            in2->getState() == Wire::state::LO) {
            gateState = Wire::state::HI;
        }
        if (in1->getState() == Wire::state::LO && //if the wires have the same values
            in2->getState() == Wire::state::LO ||
            in1->getState() == Wire::state::HI &&
            in2->getState() == Wire::state::HI) {
            gateState = Wire::state::LO;
        }
        //no need to deal with undefined state because gateState is initialized to UND

        return gateState;
    }

    //XNOR gate logic
    else if (gateStyle == XNOR) {
        if (in1->getState() == Wire::state::LO && //if the wires have different values
            in2->getState() == Wire::state::HI ||
            in1->getState() == Wire::state::HI &&
            in2->getState() == Wire::state::LO) {
            gateState = Wire::state::LO;
        }
        if (in1->getState() == Wire::state::LO && //if the wires have the same values
            in2->getState() == Wire::state::LO ||
            in1->getState() == Wire::state::HI &&
            in2->getState() == Wire::state::HI) {
            gateState = Wire::state::HI;
        }
        //no need to deal with undefined state because gateState is initialized to UND

        return gateState;
    }
    return gateState;
}

string Gate::getGateTypeStr() {
    return gateTypeStr;
}