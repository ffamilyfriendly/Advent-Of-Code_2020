// Todays epic music is days n dayz
// https://open.spotify.com/track/1MGIxsVtqK2npdPmI8Dj0D?si=Cif-G157QRGE40cxWAeUyQ

// Aight had to postpone challange 2 becuase cyberpunk but now it's time to complete it! (only 2,days late)
// https://open.spotify.com/track/6bnFjTW3EnMG4BwreDnSHK?si=7jja1nGuS0WnrZI6HnjGJQ

#include "../../lib/header.h"
#include <fstream>
#include <bits/stdc++.h>

console::Console *c = new console::Console();

vector<int> adapters;

#define debug true

int getPaths(int curr, int index) {
    int validPaths = 0;

    for(int i = index; i < adapters.size(); i++) {
        if(curr+3 < adapters[i]) continue;
        else if(i == adapters.size()-1) validPaths++;
        
        validPaths += getPaths(adapters[i],i + 1);
    }

    return validPaths;
}

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
    sort(adapters.begin(), adapters.end());

    cout << adapters.size() << " adapters loaded. Beginning brute forcing combinations... don't hold your breath" << endl;

    auto timer = c->timedLog("finding paths...");
    int paths = getPaths(0,0);
    timer.end();

    cout << "there are " << paths << " paths!" << endl;
}
