#include "../../lib/header.h"
#include <fstream>

#define debug true

console::Console *c = new console::Console();

vector<string> seats;

// I'll be honest, I stole this part from
// https://github.com/mateom99/Advent-of-Code/blob/main/2020/Day%2011/day11.cpp
int surrounding(int row, int col, vector<string> _seats) {
   		int count = 0;

		// Check seat above
		if (row-1 >= 0 && _seats[row-1][col] == '#')
			count++;
		// Check seat below
		if (row+1 < _seats.size() && _seats[row+1][col] == '#')
			count++;
		// Check seat to right
		if (col+1 < _seats[row].size() && _seats[row][col+1] == '#')
			count++;
		// Check seat to left
		if (col-1 >= 0 && _seats[row][col-1] == '#')
			count++;
		// Check upper left corner
		if (row-1 >= 0 && col-1 >= 0 && _seats[row-1][col-1] == '#')
			count++;
		// Check lower left corner
		if (row+1 < _seats.size() && col-1 >= 0 && _seats[row+1][col-1] == '#')
			count++;
		// Check upper right corner
		if (row-1 >= 0 && col+1 < _seats[row].size() && _seats[row-1][col+1] == '#')
			count++;
		// Check lower right corner
		if (row+1 < _seats.size() && col+1 < _seats[row].size() && _seats[row+1][col+1] == '#')
			count++;

		// Return the total adjacent seats
		return count;
}

int main(int argc,  char** argv) {

    auto timer = c->timedLog("Solving!");
    
    fstream input;

    #if debug
        input.open("debug.2.txt");
    #else
        input.open("input.txt");
    #endif

    string line;

    while(getline(input,line)) {
        seats.push_back(line);
    }

    input.close();

    bool hasChanged = true;
    vector<string> deltaSeats = seats;
    int availSeats = 0;

    vector<string> tempSeats = {};


    int throttle = 0;
    bool doCheck = true;

    /*while(hasChanged) {

        throttle++;

        availSeats = 0;
        bool thisLoopHasChanged = false;
        tempSeats = deltaSeats;
        for(int i = 0; i < deltaSeats.size(); i++) {
            for(int j = 0; j < deltaSeats[i].length(); j++) {

                //cout << surrounding('#',j,i,deltaSeats) << endl;
                if(deltaSeats[i][j] == '.') continue;
                if(surrounding('#',j,i,deltaSeats) > 3) {
                    tempSeats[i][j] = 'L';
                }
                
                if(surrounding('#',j,i,deltaSeats) == 0) {
                    tempSeats[i][j] = '#';
                }
                availSeats += tempSeats[i][j] == '#';

                if(tempSeats[i][j] != deltaSeats[i][j]) thisLoopHasChanged = true;
            }
        } 

        deltaSeats = tempSeats;

        system("clear");
        for(string row: deltaSeats) cout << row << endl;
        cout << endl;

        hasChanged = thisLoopHasChanged;
        if(throttle > 1000 && doCheck) {
            char answer;
            cout << "[LOOP] loop might be stuck. Continue? (y/n):\n[LOOP] d/D to disable check" << endl;
            cin >> answer;

            if(answer == 'y' || answer == 'Y') throttle = 0;
            else if(answer == 'd' || answer == 'D') doCheck = false;
            else hasChanged = false;
        }
    } 

*/
    cout << surrounding(4,3,deltaSeats) << endl;
    deltaSeats[4][3] = '*';
    for(string row: deltaSeats) cout << row << endl;
    cout << endl;
    




    timer.end();

    cout << availSeats << endl;
}
