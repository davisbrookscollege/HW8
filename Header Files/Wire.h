/*

*/
#include <string>
#include <vector>

using namespace std;

class Gate;

class Wire {
private:
    enum state {HI, LO, UND};
    string name;
    vector<Gate*> drives;
    int index;
    vector<state> history;

public:
    Wire(state, string name, vector<Gate*> drives, int index);
    void setVal(state);
    void setHistory(state);
    void setDrives(Gate*); //FIXME: Do we need multiple gate parameters?
    state getState();
    string getName();
    vector<Gate*> getDrives();
    int getIndex();
    vector<state> getHistory();
};