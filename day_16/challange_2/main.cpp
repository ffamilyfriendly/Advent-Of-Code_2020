#include "../../lib/header.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <math.h>

//haha this is dumb
vector<pair<pair<int,int>,pair<int,int>>> ranges;
unordered_map<int, vector<int>> map;

pair<pair<int,int>,pair<int,int>> getRanges(string data) {
    pair<pair<int,int>,pair<int,int>> out;

    size_t col = data.find(":");
    size_t divider = data.find(" or ");

    string range1 = data.substr(col+2, (divider-2) - col);
    size_t r1Div = range1.find("-");

    string range2 = data.substr(divider+4);
    size_t r2Div = range2.find("-");

    int r1v1 = atoi(range1.substr(0,r1Div).c_str());
    int r1v2 = atoi(range1.substr(r1Div+1).c_str());

    int r2v1 = atoi( range2.substr(0,r2Div).c_str() );
    int r2v2 = atoi( range2.substr(r2Div+1).c_str() );

    out.first = { min(r1v1,r1v2), max(r1v1,r1v2) };
    out.second = { min(r2v1,r2v2), max(r2v1,r2v2) };

    return out;
}

vector<int> csv(string data) {
    vector<int> out;
    stringstream ss(data);
    string cell;

    while(getline(ss,cell,',')) {
        out.push_back(atoi(cell.c_str()));
    }

    return out;
}

bool rangeContians(int num, pair<pair<int,int>,pair<int,int>> range) {

    if(range.first.first <= num && range.first.second >= num) {
        return true;
    }

    if(range.second.first <= num && range.second.second >= num) {
        return true;
    }

    return false;
}

unordered_map<int,int> handleMerge(unordered_map<int,vector<int>> canBe, int rSize) {
    unordered_map<int,int> out;

    for(int i = 0; i < rSize; i++) {
        if(canBe[i].size() == 1) {
            out[canBe[i][0]] = i;

            for(int j = 0; j < rSize; j++) {
                for(int k = 0; k < canBe[j].size(); k++) {
                    if(canBe[j][k] == canBe[i][0]) canBe[j].erase(canBe[j].begin() + k);
                }
            }

            i = 0;
        }
    }

    return out;
}

// This took me wayyyyy to long to figure out.
// reason why is that i removed all rules that I thought
// wasnt going to be used anymore. That was a mistake.
// changing that gave me the correct answer
int main(int argc,  char** argv) {
    fstream input;

    // check if there are enough parameters
    if(argc <= 1) 
        argv[1] = (char*)"revamped.txt";

    // set debug mode based on second parameter
    bool dMode = argv[2] == "debug";

    // open file
    input.open(argv[1]);

    // check if file exists
    if(!input || !input.is_open()) {
        string errmsg = "file \"" + (string)argv[1] + "\" could not be opened";
        perror(errmsg.c_str());
        exit(EXIT_FAILURE);
    }

    //read the file
    string line;
    int mode = 0;
    int amountOfItems = 0;
    bool nextIsYours = false;
    vector<int> yourTicket;

    while(getline(input,line)) {
        if(line.empty()) continue;
        if(line[0] == '#') continue;
        if(line == "your ticket:") {nextIsYours = true; mode = 2; continue;}
        else if(line == "nearby tickets:") {mode = 2; continue;}

        switch (mode)
        {
            case 0: 
            {
                auto newVector = getRanges(line);
                ranges.push_back(newVector);
            }
            break;
            case 2:
                vector<int> parsed = csv(line);

                if(nextIsYours) {
                    yourTicket = parsed;
                    nextIsYours = false;
                }

                amountOfItems++;
                for(int i = 0; i < parsed.size(); i++)
                    for(int j = 0; j < ranges.size(); j++) 
                        if(rangeContians(parsed[i],ranges[j])) map[j].push_back(i);
        }
    }

    unordered_map<int,vector<int>> canBe;

    for(int i = 0; i < ranges.size(); i++) {

        int nrOfNr[200] = {0};
        for(int j = 0; j < map[i].size(); j++) {
            nrOfNr[map[i][j]]++;

            if(nrOfNr[map[i][j]] == amountOfItems) {
                canBe[map[i][j]].push_back(i);
            }
        }
    }

    long long res = 1;
    unordered_map<int,int> asdasdasd = handleMerge(canBe,amountOfItems);
    for(int i = 0; i < 6; i++) {
        cout << i << ":" << asdasdasd[i] << endl;
        res *= yourTicket[asdasdasd[i]];
    }    

    cout << endl;

    cout << res << " res!" << endl;
}
