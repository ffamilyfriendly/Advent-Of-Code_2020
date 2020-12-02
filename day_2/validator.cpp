#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int casesOfChar(char search, string input) {
    int cases = 0;
    for(int i = 0; i < input.length(); i++) if(input[i] == search) cases++;
    return cases;
}


/* Part one - obviusoly remove the comment if you want it to work
*
*
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
}*/

//part two

string debugPositions(int pos1,int pos2) {
    string out(20,' ');
    out[pos1-1] = '^';
    out[pos2-1] = '^';
    return out;
}

int main() {
    int correct = 0;
    fstream input("./input.txt");
    if(!input || !input.is_open()) return 1;
    string line;
    while(getline(input,line)) {
        size_t numberSeparatorPos = line.find("-");
        size_t partSeparatorPos = line.find(":");
        char specialCharacter = line[partSeparatorPos-1];
        int indexOne = atoi(line.substr(0,numberSeparatorPos).c_str());
        int indexTwo = atoi(line.substr(numberSeparatorPos+1).c_str());
        string searchThis = line.substr(partSeparatorPos + 2);
        //I was dumb and did not realise the logic had to be XOR so I just did a normal or... oops
        if(searchThis[indexOne - 1] == specialCharacter ^ searchThis[indexTwo - 1] == specialCharacter) correct++;
        //this code was used during debug and isnt needed anymore but ngl it looks kinda cool
        else if(rand() > (RAND_MAX / 6)) cout << line << " | " << "\n" << searchThis << "\n" << debugPositions(indexOne,indexTwo) << endl;
    }
    input.close(); //close file stream
    cout << "number of correctly formatted passwords: " << correct << endl;
}