#include "../../lib/header.h"
#include <fstream>

#define debug false

vector<string> seats;

int surrounding(char target, int x, int y, vector<string> rows) {
    int res = 0;
    for(int i = y-1; i < y+2; i++) {
        for(int j = x-1; j < x+2; j++) {
            res += rows[i][j] == target;
        }
    }
    return res;
}

int main(int argc,  char** argv) {
    
    fstream input;

    #if debug
        input.open("debug.txt");
    #else
        input.open("input.txt");
    #endif

    string line;

    while(getline(input,line)) {
        seats.push_back('.'+line+'.');
    }

    seats.push_back(string(seats[0].size(),'.'));
    seats.insert(seats.begin(),string(seats[0].size(),'.'));

    bool hasChanged = true;
    vector<string> deltaSeats = seats;
    int availSeats = 0;

    vector<string> tempSeats = {};

    while(hasChanged) {
        availSeats = 0;
        bool thisLoopHasChanged = false;
        tempSeats = deltaSeats;
        for(int i = 1; i < deltaSeats.size()-1; i++) {
            for(int j = 1; j < deltaSeats[i].size()-1; j++) {
                if(deltaSeats[i][j] == '.') continue;

                if(surrounding('#',j,i,deltaSeats) > 4) {
                    tempSeats[i][j] = 'L';
                } else if(surrounding('#',j,i,deltaSeats) == 0) {
                    tempSeats[i][j] = '#';
                }

                availSeats += tempSeats[i][j] == '#';

                if(tempSeats[i][j] != deltaSeats[i][j]) thisLoopHasChanged = true;
            }
        }
        deltaSeats = tempSeats;
        hasChanged = thisLoopHasChanged;
    } 

    for(string row: deltaSeats) cout << row << endl;
    cout << availSeats << endl;
}
