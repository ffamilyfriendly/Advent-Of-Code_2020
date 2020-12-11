// Todays epic music is days n dayz
// https://open.spotify.com/track/1MGIxsVtqK2npdPmI8Dj0D?si=Cif-G157QRGE40cxWAeUyQ

#include "../../lib/header.h"
#include <fstream>
#include <bits/stdc++.h>

vector<int> adapters;

#define debug false

int main(int argc,  char** argv) {

    fstream input;

    #if debug
        input.open("debug.txt");
    #else
        input.open("input.txt");
    #endif

    if(!input || !input.is_open()) {
        perror("FILE!?!?!?");
        exit(EXIT_FAILURE);
    }

    string line;

    while(getline(input,line)) {
        adapters.push_back(atoi(line.c_str()));
    }

    sort(adapters.begin(), adapters.end());

    int differences[3] = {1,1,1};

    for(int i = 0; i < adapters.size(); i++) {
        differences[(adapters[i+1] - adapters[i])-1]++;
    }

    cout << "differences[0]:" << differences[0] << " differences[1]:" << differences[1] << " differences[2]:" << differences[2] << " answer:" << differences[0] * differences[2]  << endl;
}
