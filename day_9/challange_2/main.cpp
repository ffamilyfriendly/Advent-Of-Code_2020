// HEllo! it is time for music again. This time the devil makes three, enjoy!
// https://open.spotify.com/track/7FqrsV0vBwNiQNQI6jfzni?si=Bfg1-0igQGqV09_GX7V7_A
// or https://www.youtube.com/watch?v=ARL3u5nr7LU

#include "../../lib/header.h"
#include <fstream>

#define debug false

console::Console *c = new console::Console();

int numbers[1000] = {0};

int main(int argc,  char** argv) {
    
    // goal execution time is under 5 ms
    auto timer = c->timedLog("find XMAS weakness",5);

    fstream input;

    #if debug
        input.open("debug.txt");
        int invalidNumber = 127;
    #else
        input.open("input.txt");
        int invalidNumber = 70639851;
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

    pair<int,int> smallAndLarge = { INT32_MAX, 0 };

    for(int i = 0; i < 1000; i++) {

        for(int j = i; j < 1000; j++) {
            res += numbers[j];
            
            if(smallAndLarge.first > numbers[j]) smallAndLarge.first = numbers[j];
            if(smallAndLarge.second < numbers[j]) smallAndLarge.second = numbers[j];

            if(numbers[j] == 0) cout << "WHAT?" << endl;

            if(res == invalidNumber && j > 2) break;
            else if(res > invalidNumber) {
                res = 0;
                smallAndLarge = { INT32_MAX, 0 };
                break;
            }
        }
        if(res == invalidNumber) break;
    }

    timer.end();

    c->log("Magic numbers are " + to_string(smallAndLarge.first) + " and " + to_string(smallAndLarge.second) + " sum of both: " + to_string(smallAndLarge.first + smallAndLarge.second));
    
}
