#pragma once
#include<string>
#include <sstream>

using namespace std;
class Tranzitie {
private:
    string valoare;
    string stareA;
    string stareB;


public:
    Tranzitie(string valoare, string stareA, string stareB) : valoare{ valoare }, stareA{ stareA }, stareB{ stareB } { }

    string getValoare() {
        return valoare;
    }

    string getStareA() {
        return stareA;
    }

    string getStareB() {
        return stareB;
    }

    string toString() {
        ostringstream oss;
        oss << stareA << " -- " << valoare<< " --> " << stareB;
        string var = oss.str();
        return var;
    }
};

