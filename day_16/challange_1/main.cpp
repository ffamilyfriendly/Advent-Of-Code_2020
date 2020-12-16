#include "../../lib/header.h"
#include <fstream>
#include <sstream>
#include <math.h>

vector<pair<int,int>> ranges;

fstream dbug;

vector<pair<int,int>> getRanges(string data) {
    vector<pair<int,int>> out;

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

    out.push_back( { min(r1v1,r1v2), max(r1v1,r1v2) } );
    out.push_back( { min(r2v1,r2v2), max(r2v1,r2v2) } );

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

bool rangeContians(int num, bool log) {
    if(log) dbug << num << ": ";

    for(pair<int,int> r: ranges) {
        if(r.first <= num && r.second >= num) {
            if(log) dbug << "Mathes range " << r.first << "-" << r.second << endl;

            return true;
        }
    }

    return false;
}

int isValid(vector<int> ticket, bool log) {
    int valid = 0;
    for(int i: ticket){
        if(!rangeContians(i,log)) {valid += i; break;}
    }

    return valid;
}

// tried 29638 (too low), 175876 too high
int main(int argc,  char** argv) {
    fstream input;

    // check if there are enough parameters
    if(argc <= 1) 
        argv[1] = (char*)"input.txt";

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
    int res = 0;

    dbug.open("log.txt", ios::out);

    while(getline(input,line)) {
        if(line.empty()) continue;
        if(line == "your ticket:") {mode = 1; continue;}
        else if(line == "nearby tickets:") {mode = 2; continue;}

        switch (mode)
        {
            case 0: 
            {
                auto newVector = getRanges(line);
                ranges.insert(ranges.end(), newVector.begin(), newVector.end());
                dbug << "range: " << newVector[0].first << "-" << newVector[0].second << " " << newVector[1].first << "-" << newVector[1].second << endl;
            }
            break;
            case 1:
                //res += isValid(csv(line));
                continue;
            break;
            case 2:
                res += isValid(csv(line),true);
                dbug << "+ " << isValid(csv(line),false) << endl << endl << endl;
            break;
        }
    }
    
    cout << res << " valid tickets!" << endl;
}
