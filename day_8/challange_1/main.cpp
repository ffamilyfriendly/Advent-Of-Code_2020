// Hello! If you reading this and arent me (or just me in the future) I'm just a friendly reminder that mischeif brew is good
// https://open.spotify.com/track/1gaLJnwwY9aEM55ZuSr4Ta?si=gTMgRuOBTzK4QWVlZsfWHA
// or https://www.youtube.com/watch?v=KKclBgisCMA

#include "../../lib/header.h"
#include <fstream>
#include <chrono>

#define DEBUG false

struct instruction {
    int argument;
    int hasBeenRan = false;
    string opcode;
};

vector<instruction> stack;

console::Console *c = new console::Console();

//note 17:45: today seems simple enough. Just make a vector with the instructions and then execute it?
//note 18:39: nope, wasnt too bad. Time for part 2

int main(int argc,  char** argv) {
    auto t1 = chrono::high_resolution_clock::now();
    int accumulator = 0;

    fstream input; 
    #if DEBUG
        input.open("debuginput.txt");
    #else
        input.open("input.txt");
    #endif

    if(!input || !input.is_open()) {
        perror("could not open input");
        exit(EXIT_FAILURE);
    }

    string line;

    while(getline(input,line)) {
        instruction lineInstruction;
        lineInstruction.argument = atoi(line.substr(4).c_str());
        lineInstruction.opcode = line.substr(0,3);
        stack.push_back(lineInstruction);
    }

    c->log("Running stack with " + to_string(stack.size()) + " instructions!");

    for(int i = 0; i < stack.size(); i++) {

        if(stack[i].hasBeenRan) break;
        stack[i].hasBeenRan = true;
            
        if(stack[i].opcode == "acc") {
            accumulator += stack[i].argument; //perform mad mafs on accumulator
        } else if(stack[i].opcode == "jmp") {
            i += stack[i].argument-1; //move to stack index - 1 since for loop adds one every loop
        }
    }

    auto t2 = chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();


    c->log("accumulator is " + to_string(accumulator) + " | execution took " + to_string(duration) + "ms");
    
}
