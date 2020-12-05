#include "../../lib/header.h"
#include <fstream>

console::Console *c = new console::Console();


struct seating {
    signed char row;
    signed char column;
    short id;
    seating(string data);
};

pair<float,float> calculateRange(pair<float,float> range, bool upper) {
    float ΔRange = (range.second - range.first) / 2;
    pair<float,float> returnPair = range;

    if(!upper) {
        returnPair.first += ΔRange;
    } else {
        returnPair.second -= ΔRange;
    }

    return returnPair;
}

// 127 rows total
signed char parseRow(char data[7]) {
    signed char parsed;

    pair<float,float> range = { 0, 127 };

    for(int i = 0; i < 7; i++) {
        range = calculateRange(range,data[i] == 'F');
    }

    parsed = (data[6] == 'F' ? range.second : range.first);

    return parsed;
}

signed char parseColumn(char data[2]) {
    signed char parsed;

    pair<float,float> range = { 0, 7 };

    for(int i = 0; i < 7; i++) {
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

    string testCases[3] = {"BFFFBBFRRR", "FFFBBBFRRR", "BBFFBBFRLL"};
    int expected[3] = {567,119,820};
    c->log("running tests.");
    for(int i = 0; i < 3; i++) {
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

    short highest = 0;
    while(getline(input,line)) {
        seating thisTicket(line);
        if(thisTicket.id > highest) highest = thisTicket.id;
    }
    input.close();

    c->log("highest seat ID is " + c->styleReset(c->colour(to_string(highest),console::colour::green,console::mode::bold)));
}
