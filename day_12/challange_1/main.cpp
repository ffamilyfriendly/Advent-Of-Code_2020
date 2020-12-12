#include "../../lib/header.h"
#include <fstream>
#include <math.h>

#define pi 3.141593f

vector<pair<char,int>> instructions;

struct Vector2 {
    float x;
    float y;
    float degree;
};

struct ship {
    Vector2 shipVector;
    Vector2 shipPos;
    int currentlyFacing = 90;
};

int addDegrees(int degree1, int degree2) {
    return (degree1 + degree2) % 360;
}

Vector2 calcDegreeChange(int deltaDegree, int currentDegree = 0) {
    int degree = addDegrees(currentDegree,deltaDegree);
    Vector2 vec;

    float radian = degree * (3.141593/180);

    vec.y = cosf(radian);
    vec.x = sinf(radian);
    vec.degree = degree;

    return vec;
};


//Tried 595 (too low), 600 also too low, 1133 (correct)
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
    boat.shipVector = calcDegreeChange(0,boat.currentlyFacing);

    for(pair<char,int> i: instructions) {
        if(i.first == 'F') {
            boat.shipPos.x += i.second * boat.shipVector.x;
            boat.shipPos.y += i.second * boat.shipVector.y;
        }

        if(i.first == 'N') {
            boat.shipPos.y += i.second;
        } else if(i.first == 'E') {
            boat.shipPos.x += i.second;
        } else if(i.first == 'S') {
            boat.shipPos.y -= i.second;
        } else if(i.first == 'W') {
            boat.shipPos.x -= i.second;
        }

        if(i.first == 'R') {
            boat.shipVector = calcDegreeChange(i.second, boat.currentlyFacing);
            boat.currentlyFacing = addDegrees(boat.currentlyFacing, i.second);
        }

        if(i.first == 'L') {
            boat.shipVector = calcDegreeChange(i.second * -1, boat.currentlyFacing);
            boat.currentlyFacing = addDegrees(boat.currentlyFacing, i.second * -1);
        }
    }
    cout << "x: " << boat.shipPos.x << " y: " << boat.shipPos.y << endl;
    int absN = abs( round(boat.shipPos.y) );
    int absE = abs( round(boat.shipPos.x) );
    cout << "answer: " << absN + absE << " abs North: " << absN << " abs east: " << absE << endl;
}
