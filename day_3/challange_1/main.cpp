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

/* INSTRUCTIONS
* every step go right 3 down 1
*
*
*/
int main(int argc,  char** argv) {
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
    for(int i = 0; i < 323; i++) {
        int index = calcIndex(i*3);
        if(map[i][index] == '#') trees++;
    }
    cout << "Trees: " << trees << "... hope you have insurance" << endl;
    return 0;
}
