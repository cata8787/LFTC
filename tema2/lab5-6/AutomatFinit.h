#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<sstream>
#include<unordered_set>
#include<fstream>
#include<algorithm>
#include"Tranzitie.h"
using namespace std;

class AF {
private:
    vector<string> stari = vector<string>();
    unordered_set<string> alfabet = unordered_set<string>();
    vector<Tranzitie> tranzitii = vector<Tranzitie>();
    string stareInitiala;
    vector<string> stariFinale = vector<string>();

public:
    AF() {}

    AF(string filename) {
        vector<int> tipuri = vector<int>();
        ifstream infile(filename);

        string line;
        string element;
        stringstream ss;
        vector<string> aux;


        // citirea starilor
        getline(infile, line);
        ss = stringstream(line);
        while (ss >> element) {
            stari.push_back(element);
        }

        //citirea alfabetului
        getline(infile, line);
        ss = stringstream(line);
        while (ss >> element) {
            alfabet.insert(element);
        }

        //citirea starii initiale
        getline(infile, line);
        stareInitiala = line;

        //citirea starilor finale
        getline(infile, line);
        ss = stringstream(line);
        while (ss >> element) {
            stariFinale.push_back(element);
        }

        // citirea tranzactiilor
        int nrTranzactii;
        getline(infile, line);
        nrTranzactii = stoi(line);

        for (int i = 0; i < nrTranzactii; i++) {
            getline(infile, line);
            ss = stringstream(line);
            aux = vector<string>();
            while (ss >> element) {
                aux.push_back(element);
            }
            tranzitii.push_back(Tranzitie(aux[2], aux[0], aux[1]));
        }
    }

    AF(vector<string> stari, unordered_set<string> aflabet, vector<Tranzitie> tranzitii, string stareInitiala, vector<string>stariFinale) : stari{ stari }, alfabet{ alfabet }, tranzitii{ tranzitii }, stareInitiala{ stareInitiala }, stariFinale{ stariFinale } {}

    bool verifica(string secventa) {
        // plecam de la starea initiala
        string stareInitiala_aux = stareInitiala;
        string stareFinala = "";
        bool test = true;
        // iteram pana prefixul nu mai coincide cu nici o tranzitie valida
        for (int i = 0; i < secventa.length() && test; i++) {
            // lucam caracter cu caracter pana nu mai coincide nimic
            string character = string(1, secventa.at(i)), next = "";
            // vedem daca din starePlecare putem ajunge undeva cu valoarea caracter din prefix
            for (Tranzitie tranzitie : tranzitii) {
                if (tranzitie.getStareA().compare(stareInitiala_aux) == 0 && tranzitie.getValoare().compare(character) == 0) {
                    next = tranzitie.getStareB();
                    break;
                }
            }
            // daca nu am gasit nici o stare urmatoare ne oprim
            if (next.compare("") == 0) test = false;
            // daca prefixul s-a terminat si ultimul caracter este stare finala, ne oprim
            if (find(stariFinale.begin(), stariFinale.end(), next) != stariFinale.end() && i == secventa.length() - 1) {
                test = true;
                stareFinala = next;
                break;
            }
            // trecem la urmatoarea stareInitiala si tinem minte stareFinala
            stareInitiala_aux = next;
            stareFinala = next;
        }
        // verificam daca stareFinala este intr-adevar stare finala
        if (find(stariFinale.begin(), stariFinale.end(), stareFinala) == stariFinale.end())
            test = false;
        return test;
    }

    string prefix(string secventa) {
        // plecam de la starea initiala
        string stareInitiala_aux = stareInitiala;
        string stareFinala = "";
        bool test = true;
        string result = "";
        string backup = "";
        // iteram pana prefixul nu mai coincide cu nici o tranzitie valida
        for (int i = 0; i < secventa.length() && test; i++) {
            // lucam caracter cu caracter pana nu mai coincide nimic
            string character = string(1, secventa.at(i)), next = "";
            // vedem daca din starePlecare putem ajunge undeva cu valoarea caracter din prefix
            for (Tranzitie tranzitie : tranzitii) {
                if (tranzitie.getStareA().compare(stareInitiala_aux) == 0 && tranzitie.getValoare().compare(character) == 0) {
                    next = tranzitie.getStareB();
                    result += tranzitie.getValoare();
                    break;
                }
            }
            // daca nu am gasit nici o stare urmatoare ne oprim
            if (next.compare("") == 0) {
                backup = result;
                test = false;
                break;
            }
            // daca prefixul s-a terminat si ultimul caracter este stare finala, ne oprim
            if (find(stariFinale.begin(), stariFinale.end(), next) != stariFinale.end()) {
                backup = result;
            }

            if (find(stariFinale.begin(), stariFinale.end(), next) != stariFinale.end() && i == secventa.length() - 1) {
                test = true;
                stareFinala = next;
                break;
            }
            // trecem la urmatoarea stareInitiala si tinem minte stareFinala
            stareInitiala_aux = next;
            stareFinala = next;
        }
        // verificam daca stareFinala este intr-adevar stare finala
        if (find(stariFinale.begin(), stariFinale.end(), stareFinala) == stariFinale.end())
            return backup;
        return result;
    }

    vector<string> getStari() {
        return stari;
    }

    unordered_set<string> getAlfabet() {
        return alfabet;
    }

    vector<Tranzitie> getTranzitii() {
        return tranzitii;
    }

    string getStareInitiala() {
        return stareInitiala;
    }

    vector<string> getStariFinale() {
        return stariFinale;
    }
};