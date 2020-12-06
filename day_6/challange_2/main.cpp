#include "../../lib/header.h"
#include <fstream>
#include <stdio.h>

console::Console *c = new console::Console();

int calcSum(string input) {
    int answered[26] = {0};
    int output = 0;
    int peopleInGroup = atoi(input.c_str());

    for(int i = 1; i < input.size(); i++) {
        answered[(int)(input[i] - 'a')]++;
    }

    for(int i = 0; i < 26; i++) {
        if(answered[i] == peopleInGroup) output++;
    }

    return output;
}

vector<string> testInputs = {"1abc","3abc","2abac","4aaaa","1b"};
vector<int> testAnswers = {3,0,1,1,1};

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
    int peopleInGroup = 0;
    int res = 0;
    while(getline(input,line)) {
        if(!line.empty()) {
            batch += line;
            peopleInGroup++;
        } else {
            res += calcSum(to_string(peopleInGroup) + batch);
            batch = "";
            peopleInGroup = 0;
        }
    } 

    c->log( "result is " + c->styleReset( c->colour(to_string(res),console::colour::green) ) );
}
