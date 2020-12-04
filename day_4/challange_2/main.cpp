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
        string invalidationReason = "";
        bool valid = true;
};

vector<vector<string>> debug = {{"valid","byr","iyr","eyr","hgt","hcl","ecl","pid","cid","invalidation reason"}};

bool includes(string input) {
    string validColours[7] = {"amb","blu","brn","gry","grn","hzl","oth"};
    bool doesInclude = false;
    for(int i = 0; i < 7; i++) {
        size_t _cciicmn = input.find(validColours[i]);
        if(_cciicmn != string::npos) doesInclude = true;
    }
    return doesInclude;
}

bool hexCorrect(string input) {
    bool valid = true;
    if(input[0] != '#') valid = false;
    for(int i = 0; i < input.length(); i++) {
        if('f' > 'a' + input[i]) valid = false;
    }
    return valid;
}

bool idCorrect(string input) {
    bool valid = true;
    for(int i = 0; i < input.length()-1; i++) {
        if('a' <= input[i] || input[i] == ' ') valid = false;
    }
    return valid;
}

/* Add validation 
*   byr: 4 digits,  1920 <= byr >= 2002
*   iyr: 4 digits, 2010 <= iyr >= 2020
*   eyr: 4 digits, 2020 <= byr >= 2030
*   hgt: (inches/cm), 150-193cm, 59-76in
*   hcl: # followed by 6 chars
*   ecl: amb, blu, brn, gry, grn, hzl, or oth
*   pid: 9 digit number
*   ignored
*/

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

    if(byr != string::npos) {
        this->byr = data.substr(byr+4,4+1);
        if(this->byr.back() != ' ') {
            this->valid = false;
            this->invalidationReason += "value too big. ";
        }
        int int_byr = atoi(this->byr.c_str());
        if(1920 > int_byr || int_byr > 2002) {
            this->invalidationReason += "byr out of bounds. ";
            this->valid = false;
        }
    }
    else this->valid = false;

    if(iyr != string::npos) {
        this->iyr = data.substr(iyr+4,4+1);
        if(this->iyr.back() != ' ') {
            this->valid = false;
            this->invalidationReason += "value too big. ";
        }
        int int_iyr = atoi(this->iyr.c_str());
        if(2010 > int_iyr || int_iyr > 2020) {
            this->invalidationReason += "iyr out of bounds. ";
            this->valid = false;
        }
    }
    else this->valid = false;

    if(eyr != string::npos) {
        this->eyr = data.substr(eyr+4,4+1);
        if(this->eyr.back() != ' ') {
            this->valid = false;
            this->invalidationReason += "value too big. ";
        }
        int int_eyr = atoi(this->eyr.c_str());
        if(2020 > int_eyr || int_eyr > 2030) {
            this->invalidationReason += "eyr out of bounds. ";
            this->valid = false;
        }
    }
    else this->valid = false;

    if(hgt != string::npos) {
        this->hgt = data.substr(hgt+4,5+1);

        int int_hgt = atoi(this->hgt.c_str());
        size_t yankee = data.find("in");
        size_t normal = data.find("cm");    
        if(yankee == string::npos && normal == string::npos) {
            this->invalidationReason += "malformatted height. ";
            this->valid = false;
        } else {
            if(yankee == string::npos) {
                //cm
                if(150 > int_hgt || int_hgt > 193) {
                    this->invalidationReason += "height out of bounds. ";
                    this->valid = false;
                }
                if(this->hgt[5] != ' ') {
                    this->valid = false;
                    this->invalidationReason += "value too big. ";
                }
            } else {
                //yankee
                if(59 > int_hgt || int_hgt > 76) {
                    this->invalidationReason += "height out of bounds. ";
                    this->valid = false;
                }
                if(this->hgt[4] != ' ') {
                    this->valid = false;
                    this->invalidationReason += "value too big. ";
                }
            }
        }
    }
    else this->valid = false;

    if(hcl != string::npos) {
        this->hcl = data.substr(hcl+4,7+1);
        if(this->hcl.back() != ' ') {
            this->valid = false;
            this->invalidationReason += "value too big. ";
        }
        if(!hexCorrect(this->hcl)) {
            this->invalidationReason += "malformatted hair colour. ";
            this->valid = false;
        }
    }
    else this->valid = false;

    if(ecl != string::npos) {
        this->ecl = data.substr(ecl+4,3+1);
        if(this->ecl.back() != ' ') {
            this->valid = false;
            this->invalidationReason += "value too big. ";
        }
        if(!includes(this->ecl)) {
            this->invalidationReason += "wrong eye colour. ";
            this->valid = false;
        }
    }
    else this->valid = false;

    if(pid != string::npos) {
        this->pid = data.substr(pid+4,9+1);
        if(this->pid.back() != ' ') {
            this->valid = false;
            this->invalidationReason += "value too big. ";
        }
        if(!idCorrect(this->pid)) {
            this->invalidationReason += "malformatted ID. ";
            this->valid = false;
        }
    }
    else this->valid = false;

    if(cid != string::npos) this->cid = data.substr(cid+4,3);
    //else this->valid = false;
    //oops... seems someone commented out this line
    

    if(this->valid) debug.push_back({(this->valid ? "valid" : "invalid"),this->byr,this->iyr,this->eyr,this->hgt,this->hcl,this->ecl,this->pid,this->cid,this->invalidationReason});
}

//152 (too low), 195 (too high), 175 (wrong but correct for someone else), !!!195!!! correct
//ok so main issue was me not checking the actual data length which was dumb
int main(int argc,  char** argv) {
    
    c->log(c->styleReset(c->colour("Valid passports:",console::colour::green)));

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
    debug.push_back({"valid","byr","iyr","eyr","hgt","hcl","ecl","pid","cid","invalidation reason"});
    c->box(debug);
   c->log( c->styleReset( c->colourBG(to_string(valid) + " valid passports!",console::colour::green)) );
}
