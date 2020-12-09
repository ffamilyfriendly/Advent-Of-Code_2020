// HEllo! it is time for music again. This time the devil makes three, enjoy!
// https://open.spotify.com/track/7FqrsV0vBwNiQNQI6jfzni?si=Bfg1-0igQGqV09_GX7V7_A
// or https://www.youtube.com/watch?v=ARL3u5nr7LU

#include "../../lib/header.h"
#include <fstream>

#define debug false

console::Console *c = new console::Console();
int preLen = 25;

int numbers[1000] = {0};

int main(int argc,  char** argv) {
    
    // goal execution time is under 5 ms
    auto timer = c->timedLog("find XMAS weakness",5);

    fstream input;

    #if debug
        input.open("debug.txt");
        preLen = 5;
    #else
        input.open("input.txt");
    #endif

    if(!input || !input.is_open()) {
        perror("could not input?!?!?!?!!");
        exit(EXIT_FAILURE);
    }

    string line;
    int i = 0;
    while(getline(input, line)) {
        numbers[i++] = atoi(line.c_str());
    }

    int res = 0;

    for(int i = preLen; i < 1000; i++) {
        bool thisCycle = false;
        for(int first = 0; first < preLen; first++) {
            for(int second = 0; second < preLen; second++) {
                if((numbers[first+i - preLen] + numbers[second+i - preLen]) == numbers[i]) {thisCycle = true; break;}
            }
        }
        if(!thisCycle) {res = numbers[i]; break;}
    }

    timer.end();

    c->log("weakness is " + to_string(res));
    
}
