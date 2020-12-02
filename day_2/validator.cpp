#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int casesOfChar(char search, string input) {
    int cases = 0;
    for(int i = 0; i < input.length(); i++) if(input[i] == search) cases++;
    return cases;
}

int main() {
    int correct = 0;
    fstream input("./input.txt");
    if(!input || !input.is_open()) return 1;
    string line;
    while(getline(input,line)) {
        size_t numberSeparatorPos = line.find("-"); //find number divider
        size_t partSeparatorPos = line.find(":"); //find specifier/input divider
        char specialCharacter = line[partSeparatorPos-1]; //get character
        int minNumberOf = atoi(line.substr(0,numberSeparatorPos).c_str()); //get min number of char
        int maxNumberOf = atoi(line.substr(numberSeparatorPos+1).c_str()); //get max number of char
        int cases = casesOfChar(specialCharacter,line); //find how many cases in string
        if(!(maxNumberOf < cases-1 || cases < minNumberOf+1)) correct++; //check required stufff
    }
    input.close(); //close file stream
    cout << "number of correctly formatted passwords: " << correct << endl;
}