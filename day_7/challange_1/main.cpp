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
    c->log(b.name);
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
    cout << endl;
    return b;
}

map<string,bag> bagList;

int canHoldGold(string bag) {
    return -1;
}

//it's possible this function will crash computer
bool recurseFindBag(bag _bag) {
    bool found = false;
    for(int i = 0; i < _bag.canHold.size(); i++) {
        if(_bag.canHold[i].bagType == "shiny gold bags") {
            cout << "found!" << endl;
            found = true;
        } else {
            if(!found) found = recurseFindBag(bagList[_bag.canHold[i].bagType]);
        }
    }

    return found;
}

//descriptor colour bags contain [<numberof descriptor colour bags> repeat separated with ","]
//this was kinda hard. Apparently 1 bags is called 1 bag instead. And here I was thinking the adventofcode author wasnt a sadist
//tried: 13 (no), 21(no), 63 (no), 169 (yes!)
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

    int goldBags = 0;

    for(pair<string,bag> elem: bagList) {

        c->log("Running " + elem.first + ": ");
        if(recurseFindBag(elem.second)) goldBags++;
        c->log("\n");

    }

    input.close();

    c->log(to_string(goldBags));
}
