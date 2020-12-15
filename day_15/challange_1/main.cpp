#include "../../lib/header.h"
#include <map>

struct entry {
    int firstTimeSpoken = 0;
    pair<int,int> prevTimes;
};


int main(int argc,  char** argv) {
    cout << "debug/normal: ";
    string mode;
    cin >> mode;

    map<int,entry> entries;
    vector<int> input;

    if(mode == "debug") {
        input = {3,2,1};
    } else {
        input = {1,20,8,12,0,14};
    }

    int lastNr;
    for(int i = 0; i < 2020; i++) {
        cout << "Turn " << i+1 << ": \n";
        if(i < input.size()) {
            lastNr = input[i];

            entry e;
            e.firstTimeSpoken = i+1;
            e.prevTimes.first = i+1;
            e.prevTimes.second = 0;
            entries[lastNr] = e;

            cout << "said number " << lastNr << " for the first time\n";
        } else {
            entry e = entries[lastNr];
            cout << "got: " << lastNr << endl;
            if(e.firstTimeSpoken != i) {
                lastNr = e.prevTimes.second - e.prevTimes.first;
                cout << "said: " << lastNr << " as it has been said before" << endl;

                if(entries[lastNr].firstTimeSpoken == 0) {
                    entries[lastNr].firstTimeSpoken = i+1;
                    entries[lastNr].prevTimes.first = i+1;
                    entries[lastNr].prevTimes.second = 0;
                } else {
                    if(entries[lastNr].prevTimes.second != 0) {
                        entries[lastNr].prevTimes.first = entries[lastNr].prevTimes.second;
                        entries[lastNr].prevTimes.second = i+1;
                    } else {
                        entries[lastNr].prevTimes.second = i+1;
                    }
                }


            } else {
                lastNr = 0;

                if(entries[lastNr].firstTimeSpoken == 0) {
                    entries[lastNr].firstTimeSpoken = i+1;
                    entries[lastNr].prevTimes.first = i+1;
                    entries[lastNr].prevTimes.second = 0;
                } else {
                    if(entries[lastNr].prevTimes.second != 0) {
                        entries[lastNr].prevTimes.first = entries[lastNr].prevTimes.second;
                        entries[lastNr].prevTimes.second = i+1;
                    } else {
                        entries[lastNr].prevTimes.second = i+1;
                    }
                }

                cout << "said: " << lastNr << " as it hasnt been said before" << endl;
            }
        }
        cout << endl;
    }
}
