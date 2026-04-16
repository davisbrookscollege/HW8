#include "Wire.h"

class Event {
public:

    Event(int wire, int time, Wire::state state);
    bool operator<(Event &rhs);
    int getOOA();
    int getTime();
    int getWire();
    Wire::state getState();

private:

    static int orderOfArrival;
    int time;           // What time the event will execute
    int wire;           //Which wire it's affecting
    Wire::state state;  //State the wire should be changed too

};