#include <string>
#include <vector>

using namespace std;

class Gate;

class Wire {

public:
    enum state {HI, LO, UND};
    Wire(state initState = UND, string name = "", vector<Gate*> drives = {});
    void setVal(state);
    void setHistory(state);
    void setDrives(vector<Gate*>); 
    state getState() const;
    string getName() const;
    vector<Gate*> getDrives() const;
    int getIndex() const;
    vector<state> getHistory() const;

private:
    state curState;
    string name;
    vector<Gate*> drives;
    int index;
    static int numWires;
    vector<state> history;
};