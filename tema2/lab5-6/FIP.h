#pragma once
#include<string>
#include <sstream>
using namespace std;

class FIP {
private:
    int codAtom;
    int codTS;

public:

    FIP(int codAtom, int codTS) : codAtom{ codAtom }, codTS{ codTS } { }
    
    int getCodAtom() {
        return codAtom;
    }

    int getCodTS() {
        return codTS;
    }

    string toString() {
        ostringstream oss;
        oss << "codAtom = " << codAtom << " | codTS = " << codTS;
        string var = oss.str();
        return var;
    }
};
