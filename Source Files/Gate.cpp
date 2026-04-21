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

//returns a pointer to the output wire
Wire* Gate::getOutput() const {
    return out;
}

//evaluates the state of the gate based on the logic provided as parameters
Wire::state Gate::evaluate(Wire* inputWire, Wire::state futureState) {
    Wire::state gateState = Wire::state::UND;
    Wire::state input1 = in1->getState();
    Wire::state input2;

    if (gateType != NOT) {
        input2 = in2->getState();
    }

    //assigns inputs according to the given parameters
    if (futureState != Wire::state::DEFAULTED) {
        if (inputWire == in1) {
            input1 = futureState;
        }
        else if (inputWire == in2) {
            input2 = futureState;
        }
    }

//layer of conditional statements evaluate the logic based on the type of gate
    if (gateType == NOT) {
        //only one input, so in2 is ignored
        if (input1 == Wire::state::HI) {
            gateState = Wire::state::LO;
        }
        else if (input1 == Wire::state::LO) {
            gateState = Wire::state::HI;
        }
        //no need to deal with undefined state because gateState is initialized to UND
        
        return gateState;
    }

    //AND gate logic
    else if (gateType == AND) {
        if (input1 == Wire::state::LO || //either are low
            input2 == Wire::state::LO) {
            gateState = Wire::state::LO;
        }
        else if (input1 == Wire::state::HI && //both are high
                 input2 == Wire::state::HI) {
            gateState = Wire::state::HI;
        }
        //no need to deal with undefined state because gateState is initialized to UND

        return gateState;
    }

    //NAND gate logic
    else if (gateType == NAND) {
        if (input1 == Wire::state::LO || //either are low
            input2 == Wire::state::LO) {
            gateState = Wire::state::HI;
        }
        else if (input1 == Wire::state::HI && //both are High
                 input2 == Wire::state::HI) {
            gateState = Wire::state::LO;
        }
        //no need to deal with undefined state because gateState is initialized to UND

        return gateState;
    }

    //OR gate logic
    else if (gateType == OR) {
        if (input1 == Wire::state::HI || //either are hi
            input2 == Wire::state::HI) {
            gateState = Wire::state::HI;
        }
        else if (input1 == Wire::state::LO && //both are low
            input2 == Wire::state::LO) {
            gateState = Wire::state::LO;
        }
        //no need to deal with undefined state because gateState is initialized to UND

        return gateState;
    }

    //NOR gate logic
    else if (gateType == NOR) {
        if (input1 == Wire::state::HI || //either are HI
            input2 == Wire::state::HI) {
            gateState = Wire::state::LO;
        }
        else if (input1 == Wire::state::LO && //both are LO
            input2 == Wire::state::LO) {
            gateState = Wire::state::HI;
        }
        //no need to deal with undefined state because gateState is initialized to UND

        return gateState;
    }

    //XOR gate logic
    else if (gateType == XOR) {
        if (input1 == Wire::state::LO && //if the wires have different values
            input2 == Wire::state::HI ||
            input1 == Wire::state::HI &&
            input2 == Wire::state::LO) {
            gateState = Wire::state::HI;
        }
        if (input1 == Wire::state::LO && //if the wires have the same values
            input2 == Wire::state::LO ||
            input1 == Wire::state::HI &&
            input2 == Wire::state::HI) {
            gateState = Wire::state::LO;
        }
        //no need to deal with undefined state because gateState is initialized to UND

        return gateState;
    }

    //XNOR gate logic
    else if (gateType == XNOR) {
        if (input1 == Wire::state::LO && //if the wires have different values
            input2 == Wire::state::HI ||
            input1 == Wire::state::HI &&
            input2 == Wire::state::LO) {
            gateState = Wire::state::LO;
        }
        if (input1 == Wire::state::LO && //if the wires have the same values
            input2 == Wire::state::LO ||
            input1 == Wire::state::HI &&
            input2 == Wire::state::HI) {
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