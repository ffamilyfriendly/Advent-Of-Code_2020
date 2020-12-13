#include "../../lib/header.h"
#include <fstream>

vector<int> parseTimeTable(string data) {
    vector<int> out;

    bool parsing = true;
    int currentIndex = 0;

    while(parsing) {
        string s = data.substr(currentIndex);
        size_t firstC = s.find(",");
        if(firstC == string::npos) {parsing = false;}

        string thing = s.substr(0,firstC);
        currentIndex += thing.size() + 1;

        if(thing == "x") continue;
        else {
            cout << "found bus " << thing << endl;
            out.push_back(atoi(thing.c_str()));
        }
    }

    return out;
}

int main(int argc,  char** argv) {
    system("clear");

    string file;
    cout << "Specify file: ";
    cin >> file;

    if(file.find(".") == string::npos) file += ".txt";

    fstream input;
    input.open(file);

    if(!input || !input.is_open()) {
        perror(string("could not open file \"" + file + "\"").c_str());
        exit(EXIT_FAILURE);
    }

    cout << "succesfully opened \"" << file << "\". Parsing file..." << endl; 

    string line;
    vector<string> lines;

    while(getline(input,line)) {
        lines.push_back(line);
    }

    int time = atoi(lines[0].c_str());
    auto timestamps = parseTimeTable(lines[1]);

    int depart = 0;
    int busID = 0;

    for(int i = time; depart == 0; i++) {
        for(int bus: timestamps) {
            if(i % bus == 0) {depart = i - time; busID = bus;}
        }
    }

    cout << "Bus id is " << busID << " wait time: " << depart << " answer: " << busID * depart << endl;
}
