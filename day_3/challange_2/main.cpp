#include <string>
#include <fstream>
#include <iostream>
using namespace std;


int calcIndex(int x) {
    return x % 31;
}

string debugMarkers(int len, int pos, char character) {
    string marker(len,' ');
    marker[pos] = character;
    return marker;
}

int calcSlopeHits(int right, int down) {
    int trees = 0;
    string map[324];
    fstream input;
    input.open("./input.txt");
    string line;
    int lineItterator = 0;
    if(!input || !input.is_open()) {
        perror("could not open input file");
        exit(EXIT_FAILURE);
    }
    while(getline(input,line)) {
        map[lineItterator] = line;
        lineItterator++;
    }
    input.close();
    for(int i = 0; i < 323; i+=down) {
        int index = calcIndex(i/down*right);
        if(map[i][index] == '#') trees++;
    }
    return trees;
}

//tried 913204400 (too low), 1518805760 (too low), 5813773056 (correct)
int main(int argc,  char** argv) {

    //just put these into a calculator idk
    cout << calcSlopeHits(1,1) << "," << calcSlopeHits(3,1) << "," << calcSlopeHits(5,1) << "," << calcSlopeHits(7,1) << "," << calcSlopeHits(1,2) << endl;
    return 0;
}
