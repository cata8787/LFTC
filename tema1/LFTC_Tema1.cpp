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



/*
* unordered_map<string, int> createTable() {
    unordered_map<string, int> table;
    table["ID"] = 0;
    table["CONST"] = 1;
    table["#include<iostream>"] = 2;
    table["using"] = 3;
    table["namespace"] = 4;
    table["std"] = 5;
    table["int"] = 6;
    table["double"] = 7;
    table["main()"] = 8;
    table["cout<<"] = 9;
    table["*"] = 10;
    table["="] = 11;
    table[","] = 12;
    table[";"] = 13;
    table["{"] = 14;
    table["}"] = 15;
    return table;
}


   unordered_map<string, int> table = createTable();
   vector<string> words = readFile("sursa.txt");
   vector<FIP>* fip = new vector<FIP>();
   BST* ts = new BST();


   ts->insert(new TS("11", 1));
   ts->insert(new TS("2", 2));
   ts->insert(new TS("3", 3));
   ts->insert(new TS("5", 4));
   ts->insert(new TS("7", 0));
   ts->insert(new TS("a1", 6));
   ts->insert(new TS("a2", 7));
   ts->insert(new TS("a3", 8));
   ts->insert(new TS("f", 5));
   ts->display();


   for (string word : words) {
       bool test = false;
       // daca un simbol nu este inca in FIP, il adaug
       if (table.find(word) != table.end()) {
           fip->push_back(FIP(table.at(word), -1));
           test = true;
       }
       // altfel trebuie sa vad daca este ID sau CONST si sa il adaug in FIP
       else {
           if (FIP::checkCONST(word))
               fip->push_back(FIP(table.at("CONST"), ts->search(word)));
           else {
               if (FIP::checkID(word))
                   fip->push_back(FIP(table.at("ID"), ts->search(word)));
           }
           test = true;
       }
       // daca nu e nicaieri, atunci inseamna ca avem o eroare lexicala
       if (!test) throw new exception("Eroare lexicala!");
   }


   vector<string> descris;
   for (size_t i = 0; i < fip->size(); i++) {
       descris.push_back(fip->at(i).toString());
   }

   writeFile("FIP.txt", descris);
   */
