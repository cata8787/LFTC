#pragma once
#include<string>
#include <regex>
#include <sstream>
using namespace std;

class FIP {
private:
    int codAtom;
    int codTS;

public:
    FIP(int codAtom, int codTS) : codAtom{ codAtom }, codTS{ codTS } { }

    static bool checkID(string word) {
        ;
        return regex_match(word, regex("[a-zA-Z0-9]+")) && word.length() <= 8;
    }

    static bool checkCONST(string word) {
        return regex_match(word, regex("[0-9]{1,13}(\\.[0-9]*)?"));
    }

    string toString() {
        ostringstream oss;
        oss << "codAtom = " << codAtom << " | codTS = " << codTS;
        string var = oss.str();
        return var;
    }
};

