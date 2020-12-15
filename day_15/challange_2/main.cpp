#include "../../lib/header.h"
#include <map>
#include <unordered_map>

struct entry {
    int firstTimeSpoken = 0;
    pair<int,int> prevTimes;
};

console::Console *c = new console::Console();


int findSolution(std::vector<int> nums, int turnToStop) {
    std::unordered_map<int, uint64_t> cache;
    for (size_t i = 0; i < nums.size() - 1; ++i)
        cache[nums[i]] = i;
    nums.reserve(turnToStop);
    while(true) {
        int onTop = nums.back();
        auto it = cache.find(onTop);
        if (it == cache.end()) {
            nums.push_back(0);
        }
        else {
            int dist = nums.size() - 1 - it->second;
            nums.push_back(dist);
        }
        cache[onTop] = nums.size() - 2;
        if (nums.size() == turnToStop)
            return nums.back();
    }
    return 0;
}


int main(int argc,  char** argv) {
    cout << "debug/normal: ";
    string mode;
    cin >> mode;
    unordered_map<int,entry> entries;
    vector<int> input;

    if(mode == "debug") {
        input = {0,3,6};
    } else {
        input = {1,20,8,12,0,14};
    }

    int lastNr;

    auto timer = c->timedLog("Starting timed log...");

    // This is gonna be really slow.
    // Yep. Running on debug numbers took
    // 61115 ms or ~61 seconds. This can be made
    // increadibly much faster with something like hashmap
    // only issue is I dont know hashmap

    // V2: implemented unordered map, now takes 175594 ms or ~17 seconds. Can still be much better
    for(int i = 0; i < 30000000; i++) {
        if(i < input.size()) {
            lastNr = input[i];

            entry e;
            e.firstTimeSpoken = i+1;
            e.prevTimes.first = i+1;
            e.prevTimes.second = 0;
            entries[lastNr] = e;
        } else {
            entry e = entries[lastNr];

            if(e.firstTimeSpoken != i) {
                lastNr = e.prevTimes.second - e.prevTimes.first;


                if(entries[lastNr].firstTimeSpoken == 0) {
                    entries[lastNr].firstTimeSpoken = i+1;
                    entries[lastNr].prevTimes.first = i+1;
                    entries[lastNr].prevTimes.second = 0;
                } else {
                    if(entries[lastNr].prevTimes.second != 0) {
                        entries[lastNr].prevTimes.first = entries[lastNr].prevTimes.second;
                        entries[lastNr].prevTimes.second = i+1;
                    } else {
                        entries[lastNr].prevTimes.second = i+1;
                    }
                }


            } else {
                lastNr = 0;

                if(entries[lastNr].firstTimeSpoken == 0) {
                    entries[lastNr].firstTimeSpoken = i+1;
                    entries[lastNr].prevTimes.first = i+1;
                    entries[lastNr].prevTimes.second = 0;
                } else {
                    if(entries[lastNr].prevTimes.second != 0) {
                        entries[lastNr].prevTimes.first = entries[lastNr].prevTimes.second;
                        entries[lastNr].prevTimes.second = i+1;
                    } else {
                        entries[lastNr].prevTimes.second = i+1;
                    }
                }
            }
        }
    }

    timer.end();

    auto timer2 = c->timedLog("testing others solution");
    findSolution(input,30000000);
    timer2.end();

    cout << lastNr << endl;
}
