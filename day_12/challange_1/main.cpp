#include "../../lib/header.h"
#include <fstream>
#include <math.h>

vector<pair<char,int>> instructions;
struct ship {
    //deltaEast 1 = facing east, -1 means facing west
    int deltaEast = 1;
    //delta north 1 means facing north, deltanorth -1 means facing south
    int deltaNorth = 0;

    int currentlyFacing = 90;

    int east = 0;
    int north = 0;

    void calcDegreeChange(int deltaDegree);
};

void ship::calcDegreeChange(int deltaDegree) {
    this->deltaEast = 0;
    this->deltaNorth = 0;
    this->currentlyFacing = (this->currentlyFacing + deltaDegree) % 360;

    int thing = round((float)this->currentlyFacing/100);
    switch(thing) {
        case 0:
            this->deltaNorth = 1;
        break;
        case 1:
            this->deltaEast = 1;
        break;
        case 2:
            this->deltaNorth = -1;
        break;
        case 3:
            this->deltaEast = -1;
        break;
        default:
            cout << "what? " << this->currentlyFacing << endl;
            this->deltaNorth = 1;
        break;
    }
};

int main(int argc,  char** argv) {
    string mode = "";
    cout << "Mode? (debug/normal): ";
    cin >> mode;
    bool debug = mode == "debug";

    cout << (string[]){"running in normal mode", "running in debug mode"}[debug] << endl;

    fstream input;
    if(debug) {
        input.open("debug.txt");
    } else {
        input.open("input.txt");
    }

    if(!input || !input.is_open()) {
        perror("could not open file");
        exit(EXIT_FAILURE);
    }

    string line;

    while(getline(input,line)) {
        instructions.push_back( (pair<char,int>){line[0],atoi(line.substr(1).c_str())} );
    }

    cout << "Succesfully read " << instructions.size() << " instructions! Calculating..." << endl;
    ship boat;

    for(pair<char,int> i: instructions) {
        if(i.first == 'F') {
            boat.east += (i.second * boat.deltaEast);
            boat.north += (i.second * boat.deltaNorth);
        }

        if(i.first == 'N') {
            boat.north += i.second;
        } else if(i.first == 'E') {
            boat.east += i.second;
        } else if(i.first == 'S') {
            boat.north -= i.second;
        } else if(i.first == 'W') {
            boat.east -= i.second;
        }

        if(i.first == 'R') {
            boat.calcDegreeChange(i.second);
        }

        cout << "east " << boat.east << ", north " << boat.north << endl;
    }
    int absN = abs( boat.north );
    int absE = abs( boat.east );
    cout << "answer: " << absN + absE << " abs North: " << absN << " abs east: " << absE << endl;
}
