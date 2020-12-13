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

        if(thing == "x") out.push_back(0);
        else {
            cout << "found bus " << thing << endl;
            out.push_back(atoi(thing.c_str()));
        }
    }

    return out;
}

//correct answer 626670513163231
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
    auto timestamps = parseTimeTable(lines[1]);

    long depart = 0;
    int busID = 0;

    for(int j = 0; j < timestamps.size(); j++) {
        if(timestamps[j] == 0) {continue;}
        cout << -j << " | ";
        cout << timestamps[j] << endl;
    }
    cout << "\nsolve above with https://www.dcode.fr/chinese-remainder" << endl;
}
