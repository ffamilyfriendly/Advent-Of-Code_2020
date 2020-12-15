// today music is country
// https://open.spotify.com/track/71geaRAZ2M5w08T3kl5Xvs?si=q3YjbccETiWdPNfowNZfpQ

#include "../../lib/header.h"
#include <map>
#include <unordered_map>

console::Console *c = new console::Console();

int main(int argc,  char** argv) {
    cout << "debug/normal: ";
    string mode;
    cin >> mode;
    unordered_map<int,pair<int,int>> entries;
    vector<int> input;

    if(mode == "debug") {
        input = {0,3,6};
    } else {
        input = {1,20,8,12,0,14};
    }

    auto timer = c->timedLog("Starting timed log...",17000);

    int lastNr;
    for(int i = 0; i < input.size(); i++)
        lastNr = input[i], entries[lastNr] = {i+1,0};

    // this is better but far from good. ~17 seconds --> ~13 seconds
    for(int i = input.size(); i < 30000000; i++) {
            pair<int,int> e = entries[lastNr];

            if(e.first != i)
                lastNr = e.second - e.first;
            else
                lastNr = 0;
            
            if(entries.find(lastNr) == entries.end())
                entries[lastNr] = {i+1,0};
            else {
                pair<int,int> entriePair = entries[lastNr];
                entries[lastNr] = { (entriePair.second == 0 ? entriePair.first : entriePair.second) , i+1 };
            }
    }

    timer.end();

    cout << lastNr << endl;
}
