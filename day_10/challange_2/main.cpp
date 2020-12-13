// Todays epic music is days n dayz
// https://open.spotify.com/track/1MGIxsVtqK2npdPmI8Dj0D?si=Cif-G157QRGE40cxWAeUyQ

// Aight had to postpone challange 2 becuase cyberpunk but now it's time to complete it! (only 2,days late)
// https://open.spotify.com/track/6bnFjTW3EnMG4BwreDnSHK?si=7jja1nGuS0WnrZI6HnjGJQ

#include "../../lib/header.h"
#include <fstream>
#include <bits/stdc++.h>

console::Console *c = new console::Console();

vector<int> adapters;

#define debug false

// I'll be honest, I stole this from u/TheElTea because I have no idea what to do.
// I'll analyse it so I understand it
long getPaths() {
    long validPaths = 1;
    int cCount = 0;
    vector<int> runlen;

    for(int i = 0; i < adapters.size(); i++) {
        if(adapters[i+1] - adapters[i] == 1) cCount++;
        else {
            cCount--;
            if(cCount >= 1) {
                runlen.push_back(cCount);
            }
            cCount = 0;
        }
        
    }

    int what[] = { 1, 2, 4, 7 };

    for(int c: runlen) {
        validPaths *= what[c];
    }

    return validPaths;
}


// there are 13816758796288 combinations...
// that explains why my initial recursive function
// ran at 100% cpu for over 9 hours and did not
// solve the problem. It would take like days to brute force it (shorter if I implemented caching)
int main(int argc, char **argv)
{
    fstream input;

#if debug
    input.open("debug.txt");
#else
    input.open("input.txt");
#endif

    if (!input || !input.is_open())
    {
        perror("FILE!?!?!?");
        exit(EXIT_FAILURE);
    }

    string line;

    while (getline(input, line))
    {
        adapters.push_back(atoi(line.c_str()));
    }
    adapters.push_back(0);
    sort(adapters.begin(), adapters.end());
    adapters.push_back(adapters[adapters.size() - 1] + 3);

    cout << adapters.size() << " adapters loaded. " << endl;

    auto timer = c->timedLog("finding paths...");
    long paths = getPaths();
    timer.end();

    cout << "there are " << paths << " paths!" << endl;
}
