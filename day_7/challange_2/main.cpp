#include "../../lib/header.h"
#include <fstream>
#include <map>

console::Console *c = new console::Console();

struct bag {
    struct content {
        string bagType;
        int count;
    };
    string name;
    vector<bag::content> canHold;
};

bag parseBag(string data) {
    bag b;
    size_t name = data.find("contain");
    b.name = data.substr(0,name-1);

    string adjusted = data.substr(name + 7);
    string current = "";
    for(int i = 0; i < adjusted.length(); i++) {
        if(adjusted[i] != ',' && i != adjusted.length()-1) {
            current += adjusted[i];
        } else {
            current = current.substr(1); //first char is always a space
            bag::content el_contente; //mr worldwide today, sorry spain
            el_contente.count = atoi(current.c_str()); //get number
            el_contente.bagType = current.substr(current.find(" ")+1); // remove number from string

            if(el_contente.count == 1) el_contente.bagType += "s";

            b.canHold.push_back(el_contente); //push content
            //c->log("    [" + to_string(el_contente.count) + "] " + el_contente.bagType); //log content

            current = ""; //set current to ""
        }
     }
    return b;
}

map<string,bag> bagList;

int canHoldGold(string bag) {
    return -1;
}

//it's possible this function will crash computer
int recurseFindBag(bag _bag) {
    int slightlyCool = 0;
    for(int i = 0; i < _bag.canHold.size(); i++) {
        slightlyCool += _bag.canHold[i].count;
        c->log(to_string(slightlyCool));
        slightlyCool += (_bag.canHold[i].count * recurseFindBag(bagList[_bag.canHold[i].bagType]));
    }

    return slightlyCool;
}

// tried: 221 (too low), 82372(??? cant be correct) (ok it was lol)
int main(int argc,  char** argv) {
    fstream input;
    //input.open("input.txt");
    input.open("input.txt");

    if(!input || !input.is_open()) {
        perror("could not open input");
        exit(EXIT_FAILURE);
    }

    string line;

    while(getline(input,line)) {
        bag thisBag = parseBag(line);
        bagList.insert(pair<string,bag>(thisBag.name,thisBag));
    }

    bag yourBag = bagList["shiny gold bags"];
    int nrOfBags = recurseFindBag(yourBag);

    input.close();

    c->log("->" + to_string(nrOfBags) + "<-");
}
