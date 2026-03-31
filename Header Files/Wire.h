#include <string>
#include <vector>

using namespace std;

class Wire {

public:
    enum state {HI, LO, UND};
    Wire(state, string name, vector<Gate*> drives, int index);
    void setVal(state);
    void setHistory(state);
    void setDrives(Gate*); //FIXME: Do we need multiple gate parameters?
    state getState();
    string getName();
    vector<Gate*> getDrives();
    int getIndex();
    vector<state> getHistory();

private:
    state curState;
    string name;
    vector<Gate*> drives;
    int index;
    vector<state> history;
};