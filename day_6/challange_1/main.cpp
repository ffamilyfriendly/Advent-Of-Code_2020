#include "../../lib/header.h"
#include <fstream>
#include <stdio.h>

console::Console *c = new console::Console();

int calcSum(string input) {
    bool answered[26] = {0};
    int output = 0;

    for(int i = 0; i < input.size(); i++) {
        if(!answered[(int)(input[i] - 'a')]) {
            answered[(int)(input[i] - 'a')] = true;
            output++;
        }
    }

    return output;
}

vector<string> testInputs = {"abc","abc","abac","aaaa","b"};
vector<int> testAnswers = {3,3,3,1,1};


//Tried 6046 (too low), 6147 (too low), 6170 (yes!)

// issue was not initializing array in calcSum by doing = {0}
// also not adding an extra \n to input.txt due to how I handle
// chuking content
int main(int argc,  char** argv) {
    c->log("running tests:");
    c->runTests(calcSum,to_string,testInputs,testAnswers);
    c->log("\nrunning input.txt:");

    fstream input;
    input.open("input.txt");

    if(!input || !input.is_open()) {
        perror("could not open input.txt");
        exit(EXIT_FAILURE);
    }

    string line;
    string batch;
    int res = 0;
    while(getline(input,line)) {
        if(!line.empty()) {
            batch += line;
        } else {
            res += calcSum(batch);
            batch = "";
        }
    }

    c->log( "result is " + c->styleReset( c->colour(to_string(res),console::colour::green) ) );
}
