#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<fstream>
#include<unordered_map>
#include<map>
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

unordered_map<string, int> createTable() {
    unordered_map<string, int> table;
    table["ID"] = 0;
    table["CONST"] = 1;
    table["#include<iostream>"] = 2;
    table["using"] = 3;
    table["namespace"] = 4;
    table["std"] = 5;
    table["main"] = 6;
    table["int"] = 7;
    table["double"] = 8;
    table["struct"] = 9;
    table["cin>>"] = 10;
    table["cout<<"] = 11;
    table["if"] = 12;
    table["while"] = 13;
    table["+"] = 14;
    table["-"] = 15;
    table["*"] = 16;
    table["/"] = 17;
    table["%"] = 18;
    table["!="] = 19;
    table["<"] = 20;
    table["<="] = 21;
    table[">"] = 22;
    table[">="] = 23;
    table["="] = 24;
    table["("] = 25;
    table[")"] = 26;
    table["{"] = 27;
    table["}"] = 28;
    table[","] = 29;
    table[";"] = 30;

    return table;
   
}

BST* createTS(vector<string> words, unordered_map<string,int> table) {
    BST* ts = new BST();
    unordered_map<string, int> ts_table; // dictionar auxiliar pentru tabela de simboluri

    int j = 0;
    for (string word : words) {
        //daca e cuvant cheie 
        if (table.find(word) == table.end()) // daca nu este cuvant rezervat atunci 
            if (FIP::checkCONST(word) || FIP::checkID(word)) // verific daca e id sau constanta
                if (ts_table.find(word) == ts_table.end()) // evit duplicarea id-urile si a constantelor in tabela de simboluri cu ajutorul unui dictionar auxiliar
                    ts_table[word] = j++;

    }

    for (auto const& pair : ts_table) {
        // construiesc tabela de simboluri cu ajutorul dictionarului auxiliar
        ts->insert(new TS(pair.first, pair.second));

    }

    return ts;

}

vector<FIP>* createFIP(vector<string> words, unordered_map<string, int> table, BST* ts) {
    vector<FIP>* fip = new vector<FIP>();

    for (string word : words) {
        bool test = false;
        // daca un simbol nu este inca in FIP, il adaug

        if (table.find(word) != table.end()) { // daca este cuvant cheie
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

    return fip;

}

int main()
{
    vector<string> words = readFile("sursa.txt");
    
    unordered_map<string, int> table = createTable(); // dictionar auxiliar cu simboluri
    BST* ts = createTS(words,table); // ts
    vector<FIP>* fip = createFIP(words,table, ts);  //fip

    //afisare tabela de simboluri sub forma de arbore binar
    ts->display();
    
    // afisare forma interna a programului
    vector<string> descris;
    for (size_t i = 0; i < fip->size(); i++) {
        descris.push_back(fip->at(i).toString());
    }

    writeFile("FIP.txt", descris);
    
    return 0;
}
