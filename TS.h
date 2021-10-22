#pragma once
#include<string>
#include <regex>
#include <sstream>
using namespace std;

class TS {
private:
    string simbol;
    int codTS;
public:
    
    TS(string simbol, int codTS) : simbol{ simbol }, codTS{ codTS } { }

    string getSimbol() {
        return simbol;
    }

    int getCodTS() {
        return codTS;
    }

    string toString() {
        ostringstream oss;
        oss << "FIP{" << "simbol=" << simbol << ", codTS=" << codTS << '}';
        string var = oss.str();
        return var;
    }
};

