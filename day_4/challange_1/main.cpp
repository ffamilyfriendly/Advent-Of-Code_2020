#include "../../lib/header.h"
#include <fstream>

console::Console *c = new console::Console(); //for debuggning

struct PassPort {
        PassPort(string data);
        string byr; //brith year
        string iyr; //issue year
        string eyr; //expiry year
        string hgt; //height
        string hcl; //hair colour
        string ecl; //eye colour
        string pid; //passport ID
        string cid; //country ID
        bool valid = true;
};

vector<vector<string>> debug = {{"valid","byr","iyr","eyr","hgt","hcl","ecl","pid","cid"}};

PassPort::PassPort(string data) {
    size_t byr = data.find("byr:");
    size_t iyr = data.find("iyr:");
    size_t eyr = data.find("eyr:");
    size_t hgt = data.find("hgt:");
    size_t hcl = data.find("hcl:");
    size_t ecl = data.find("ecl:");
    size_t pid = data.find("pid:");
    size_t cid = data.find("cid:");

    this->valid = true;

    if(byr != string::npos) this->byr = data.substr(byr+4,4);
    else this->valid = false;

    if(iyr != string::npos) this->iyr = data.substr(iyr+4,4);
    else this->valid = false;

    if(eyr != string::npos) this->eyr = data.substr(eyr+4,4);
    else this->valid = false;

    if(hgt != string::npos) this->hgt = data.substr(hgt+4,5);
    else this->valid = false;

    if(hcl != string::npos) this->hcl = data.substr(hcl+4,7);
    else this->valid = false;

    if(ecl != string::npos) this->ecl = data.substr(ecl+4,3);
    else this->valid = false;

    if(pid != string::npos) this->pid = data.substr(pid+4,9);
    else this->valid = false;

    if(cid != string::npos) this->cid = data.substr(cid+4,3);
    //else this->valid = false;
    //oops... seems someone commented out this line
    

    debug.push_back({(this->valid ? "valid" : "invalid"),this->byr,this->iyr,this->eyr,this->hgt,this->hcl,this->ecl,this->pid,this->cid});
}

//tried 234 (too low), 235 (correct)
//issue was input file not ending in \n thus not parsing the last passport in "currentBatch".
//Fixed by adding a \n to end of input
int main(int argc,  char** argv) {
    
    c->log(c->styleReset(c->colour("test!",console::colour::blue)));

    fstream input;
    input.open("./input.txt");
    if(!input || !input.is_open()) {
        perror("could not open passport file");
        exit(EXIT_FAILURE);
    }

    string line;
    string currentBatch = "";
    int valid = 0;

    while(getline(input,line)) {
        if(line == "") {
            PassPort person = PassPort(currentBatch);
            if(person.valid) valid++;
            currentBatch = "";
        } else {
            currentBatch += line + " ";
        }
    }
    input.close();
    debug.push_back({"valid","byr","iyr","eyr","hgt","hcl","ecl","pid","cid"});
    c->box(debug);
   c->log( c->styleReset( c->colourBG(to_string(valid) + " valid passports!",console::colour::green)) );
}
