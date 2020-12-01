#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> getInputs() {
    vector<int> inputs;
    fstream file;
    file.open("input.txt",ios::in);

    if(!file || !file.is_open()) {
        printf("No input file!\n");
    } else {
        string line;
        while(getline(file, line)) {
            inputs.push_back(atoi(line.c_str())); 
        }
        file.close();
    }
    return inputs;
}

int findPair() {
    printf("Reading file\n");
    vector<int> inputs = getInputs();
    printf("Read %d lines! Finding answer...\n",inputs.size());

    for(int i: inputs) {
        for(int j: inputs) {
            if(i + j == 2020) {
                printf("Answer keys found! input[0]: %d, input[1]: %d. Answer: %d\n",i,j,i*j);
                return 0;
            }
        }
    }
    return 0;
}

int findTripple() {
    printf("Reading file\n");
    vector<int> inputs = getInputs();
    printf("Read %d lines! Finding answer...\n",inputs.size());

    for(int i: inputs) {
        for(int j: inputs) {
            for(int k: inputs) {
                if(i + j + k == 2020) {
                    printf("Answer keys found! input[0]: %d, input[1]: %d, input[2]: %d. Answer: %d\n",i,j,k,i*j*k);
                    return 0;
                }
            }
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    bool findPairMode = true;
    if(argc == 1) {
        printf("No mode selected. find=pair|tripple. Defaults pair\n");
    }
    
    //this is very ugly
    if(string(argv[1]) == string("find=tripple")) findPairMode = false;

    if(findPairMode) {
        return findPair();
    } else return findTripple();
}