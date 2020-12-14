#include "../../lib/header.h"
#include <fstream>
#include <map>

map<long long, long long> mem;


// ngl I stole this from u/gpodsiadlo
// https://www.reddit.com/r/adventofcode/comments/kcr1ct/2020_day_14_solutions/gfsmlc5/?context=3
// I've never done masks before or really any bitwise OPs but Ill try to understand
long long doMask(long long number, string mask) {
    unsigned long long m_ask = (1ULL << 37) - 1;
    unsigned long long o_ask = {};

    for(int i {}; i < mask.size(); i++) {
        if (mask[mask.size() - i - 1] == '1') o_ask += 1ULL << i;
        else if  (mask[mask.size() - i - 1] == '0') m_ask ^= 1ULL << i;
    }

    return (number | o_ask) & m_ask;
}


//tried 1498719533 too low 7440382076205 (yes)
int main(int argc,  char** argv) {
    string fileName;
    cout << "Enter input file name: ";
    cin >> fileName;

    if(fileName.find(".") == string::npos) fileName += ".txt";

    fstream input;
    input.open(fileName);

    if(!input || !input.is_open()) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }

    string mask;
    string line;
    while(getline(input,line)) {
        if(line.substr(0,4) == "mask") {
            mask = line.substr(7);
            cout << "Applying mask \"" << mask << "\"" << endl;
        } else {
            int memAddr = atoi(line.substr(line.find("[")+1,(line.find("]")-line.find("[") - 1)).c_str());
            long long val = (long long)atoi(line.substr(line.find("]")+3).c_str());

            cout << "mem[" << memAddr << "] = " << val << " 🠒 ";

            val = doMask(val,mask);   
            mem[memAddr] = val;
            cout << val;
            cout << endl;
        }
    }

    // stole this as well from above link since it looked dope
    auto res = [](const auto &mem) {
        unsigned long long sum {};
        for(const auto &m : mem)
            sum += m.second;
        return sum;
    };

    cout << "answer: " << res(mem) << endl;
}
