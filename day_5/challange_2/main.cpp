#include "../../lib/header.h"
#include <fstream>
#include <math.h>

console::Console *c = new console::Console();

bool ticketIDs[850];

struct seating {
    int row;
    int column;
    short id;
    seating(string data);
};

pair<int,int> calculateRange(pair<int,int> range, bool upper) {
    int ΔRange = round((float)(range.second - range.first) / 2);
    pair<int,int> returnPair = range;
    //cout << "action: " << (!upper ? "range[0]+n " : "range[1]-n ") << "range[0]:" << range.first << " range[1]:" << range.second << " ΔRange:" << ΔRange << endl;
    if(!upper) {
        returnPair.first += ΔRange;
    } else {
        returnPair.second -= ΔRange;
    }

    return returnPair;
}

// 127 rows total
int parseRow(char data[7]) {
    int parsed;

    pair<int,int> range = { 0, 127 };

    for(int i = 0; i < 7; i++) {
        range = calculateRange(range,data[i] == 'F');
    }

    parsed = (data[6] == 'F' ? range.second : range.first);

    return parsed;
}

int parseColumn(char data[3]) {
    int parsed;

    pair<int,int> range = { 0, 7 };

    for(int i = 0; i < 3; i++) {
        range = calculateRange(range,data[i] == 'L');
    }

    parsed = (data[1] == 'R' ? range.second : range.first);

    return parsed;
};

seating::seating(string data) {

    char row[7] = {data[0],data[1],data[2],data[3],data[4],data[5],data[6]};
    char column[3] = {data[7],data[8],data[9]};
    this->row = parseRow(row);
    this->column = parseColumn(column);
    this->id = (this->row * 8) + this->column; 
}


int main(int argc,  char** argv) {
    c->log(c->styleReset(c->colour("Reading input.txt...",console::colour::cyan,console::mode::bold)));

    string testCases[10] = {"BBFBFBFLRL","BFFFBBFRRR", "FFFBBBFRRR", "BBFFBBFRLL","FFFBBFBRLR","FFFBBFFLRR","FFFBBFBRLL","FFFBBFFRLR","FFFBBFBLRR","FFFBBFFRLL"};
    int expected[10] = {850,567,119,820,109,99,108,101,107,100};
    c->log("running tests.");
    for(int i = 0; i < 10; i++) {
        seating TEST(testCases[i]);

        console::colour resCol = console::colour::green;
        string resStr = " PASSED ";

        if(TEST.id != expected[i]) {
            resCol = console::colour::red;
            resStr = " FAILED ";
        }

        c->log(c->styleReset( c->colourBG( c->colour(resStr, console::colour::black),resCol)) + " " + testCases[i] + "\nexpected " + to_string(expected[i]) + " got " + to_string(TEST.id) + "\n");
    }

    fstream input;
    string line;
    input.open("input.txt");

    if(!input || !input.is_open()) {
        c->log(c->styleReset(c->colour("could not open file",console::colour::red,console::mode::bold)));
        perror("reason");
        exit(EXIT_FAILURE);
    }

    while(getline(input,line)) {
        seating thisTicket(line);
        ticketIDs[thisTicket.id] = true;
    }
    input.close();

    int searchID = 0;

    for(int i = 1; i < 850; i++) {
        if(!ticketIDs[i] && ticketIDs[i+1] && ticketIDs[i-1]) searchID = i;
    } 

    c->log("our seat ID is " + c->styleReset(c->colour(to_string(searchID),console::colour::green,console::mode::bold)));
}
