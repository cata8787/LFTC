#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<fstream>
#include<unordered_map>
#include"TAD.h"
#include"FIP.h"
#include"TS.h"
using namespace std;

vector<string> readFile(string filename) {
    vector<string> lista = vector<string>();
    ifstream fin(filename);
    string word;
    while (fin >> word) {
        lista.push_back(word);
    }
    return lista;
}

void writeFile(string filename, vector<string> lista) {
    ofstream fout(filename);
    for (const auto& word : lista) {
        fout << word << endl;
    }
}


vector<string> separareAtomi() {

    vector<string> identificatori;
    identificatori.push_back("Identificatori:\n");

    vector<string> constante;
    constante.push_back("Constante:\n");

    vector<string> cuv_cheie;
    cuv_cheie.push_back("Cuvinte cheie:\n");

    vector<string> operatori;
    operatori.push_back("Operatori:\n");

    vector<string> separatori;
    separatori.push_back("Separatori:\n");

    vector<string> text = readFile("sursa.txt");

    for (string word : text) {
        if (word.compare("#include<iostream>") == 0 || word.compare("using") == 0 || word.compare("namespace") == 0 || word.compare("std") == 0 || word.compare("int") == 0
            || word.compare("double") == 0 || word.compare("main()") == 0 || word.compare("cout<<") == 0)
            cuv_cheie.push_back(word);
        else
            if (word.compare("*") == 0 || word.compare("=") == 0)
                operatori.push_back(word);
            else
                if (word.compare(",") == 0 || word.compare(";") == 0 || word.compare("{") == 0 || word.compare("}") == 0)
                    separatori.push_back(word);
                else
                    if (FIP::checkCONST(word))
                        constante.push_back(word);
                    else 
                        if (FIP::checkID(word))
                            identificatori.push_back(word);
    }

    cuv_cheie.insert(cuv_cheie.end(), identificatori.begin(), identificatori.end());
    cuv_cheie.insert(cuv_cheie.end(), constante.begin(), constante.end());
    cuv_cheie.insert(cuv_cheie.end(), operatori.begin(), operatori.end());
    cuv_cheie.insert(cuv_cheie.end(), separatori.begin(), separatori.end());

    vector<string>::iterator it_cuv_cheie;
    it_cuv_cheie = unique(cuv_cheie.begin(), cuv_cheie.end());
    cuv_cheie.resize(distance(cuv_cheie.begin(), it_cuv_cheie));

    return cuv_cheie;

}

int main()
{
    vector<string> table = separareAtomi();
    writeFile("atomi.txt", table);

    return 0;

}


