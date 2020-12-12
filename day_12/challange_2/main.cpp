// Hello! Music for today is Chet baker
// https://www.youtube.com/watch?v=3zrSoHgAAWo

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
};

int addDegrees(int degree1, int degree2) {
    return (degree1 + degree2) % 360;
}

// Dear god have mercy on my soul please and thanks amen
Vector2 rotateVector(Vector2 v, int degrees, bool clockwise) {
    Vector2 res;
    float radian = degrees * (3.141593/180);

    res.x = v.x*cosf(radian) - v.y*sinf(radian);
    res.y = v.y*sinf(radian) + v.x*cosf(radian);
    return res;
}

// couldnt figure out how to rotate vector so I stole this code from this video by Craig Chasseur (youtube.com/user/spoonboy42)
// https://www.youtube.com/watch?v=E8jPEARt8FA
// to my defense I did try doing some weird stuff I found on wikipedia above

Vector2 rotateLeft90(Vector2 coords) {
    Vector2 rV;
    rV.x = (coords.y * -1);
    rV.y = coords.x;

    return rV;
}

//latitude = up down
Vector2 rotateRight90(Vector2 coords) {
    Vector2 rV;
    rV.x = coords.y;
    rV.y = (coords.x * -1);

    return rV;
}

//Tried 94905(seems way too high)(yep, too high), 34459 (too low)
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
    ship waypoint; //struct name might not be the best anymore lol;

    waypoint.shipPos.x = 10;
    waypoint.shipPos.y = 1;

    boat.shipPos.x = 0;
    boat.shipPos.y = 0;
    
    for(pair<char,int> i: instructions) {
        if(i.first == 'F') {
            for(int j = 0; j < i.second; j++) {
                Vector2 calcWaypointPos;
                calcWaypointPos.x = boat.shipPos.x + waypoint.shipPos.x;
                calcWaypointPos.y = boat.shipPos.y + waypoint.shipPos.y;

                boat.shipPos.x = calcWaypointPos.x;
                boat.shipPos.y = calcWaypointPos.y;
            }
        }

        if(i.first == 'N') {
            waypoint.shipPos.y += i.second;
        } else if(i.first == 'E') {
            waypoint.shipPos.x += i.second;
        } else if(i.first == 'S') {
            waypoint.shipPos.y -= i.second;
        } else if(i.first == 'W') {
            waypoint.shipPos.x -= i.second;
        }

        cout << "ship pos: " << boat.shipPos.x << ", " << boat.shipPos.y <<  endl;
        if(i.first == 'R') {
            for(int j = 0; j < (i.second / 90); j++) {
                waypoint.shipPos = rotateRight90(waypoint.shipPos);
            }
        }

        if(i.first == 'L') {
            for(int j = 0; j < (i.second / 90); j++) {
                waypoint.shipPos = rotateLeft90(waypoint.shipPos);
            }
        }
    }
    int absN = abs( round(boat.shipPos.y) );
    int absE = abs( round(boat.shipPos.x) );
    cout << "answer: " << absN + absE << " abs North: " << absN << " abs east: " << absE << endl;
}
