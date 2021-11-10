#include <iostream>
#include"AutomatFinit.h"
#include"Tranzitie.h"

using namespace std;

int main()
{
    AF af=AF();
    cout<<"1. Citire date de la tastatura"<<endl;
    cout<<"2. Citire date din fisier"<<endl;
    cout<<"Dati comanda: ";
    int cmd;
    cin >> cmd;

    if (cmd == 1) {
        vector<string> stari = vector<string>();
        unordered_set<string> alfabet = unordered_set<string>();
        vector<Tranzitie> tranzitii = vector<Tranzitie>();
        string stareInitiala="";
        vector<string> stariFinale = vector<string>();

        vector<int> tipuri = vector<int>();
        string line;
        string element;
        stringstream ss;
        vector<string> aux;


        // citirea starilor
        cout << "Dati starile, fiecare element separat prin spatiu: " << endl;
        cin >> line;
        ss = stringstream(line);
        while (ss >> element) {
            stari.push_back(element);
        }

        //citirea alfabetului
        cout << "Dati alfabetul, fiecare element separat prin spatiu: " << endl;
        cin >> line;
        ss = stringstream(line);
        while (ss >> element) {
            alfabet.insert(element);
        }

        //citirea starii initiale
        cout << "Dati starea initiala: " << endl;
        cin >> line;
        stareInitiala = line;

        //citirea starilor finale
        cout << "Dati starile finale, fiecare element separat prin spatiu: " << endl;
        cin >> line;
        ss = stringstream(line);
        while (ss >> element) {
            stariFinale.push_back(element);
        }

        // citirea tranzactiilor
        int nrTranzactii;
        cout << "Dati numarul de tranzactii, numar intreg: " << endl;
        cin >> line;
        nrTranzactii = stoi(line);

        for (int i = 0; i < nrTranzactii; i++) {
            cout << "Dati tranzactia, fiecare element separat prin spatiu: ";
            cin >> line;
            ss = stringstream(line);
            aux = vector<string>();
            while (ss >> element) {
                aux.push_back(element);
            }
            tranzitii.push_back(Tranzitie(aux[2], aux[0], aux[1]));
        }

        af = AF(stari, alfabet,tranzitii, stareInitiala, stariFinale);
    }
    if (cmd == 2) {
        af = AF("sursa.txt");
    }

    cout << endl;
    cout << "1. Afisarea starilor" << endl;
    cout << "2. Afisarea alfabetului" << endl;
    cout << "3. Afisarea multimii tranzitiilor" << endl;
    cout << "4. Afisarea starilor finale" << endl;
    cout << "5. Verificare validitate secventa in AF" << endl;
    cout << "6. Cel mai lung prefix valid in AF" << endl;
    cout << "0. Iesire" << endl;

    while (true) {
        cout << endl;
        cout<<"Dati comanda: ";
        cin >> cmd;

        if (cmd == 1) {
            cout<<"Multimea starilor este: ";
            for (string stare : af.getStari()) {
                cout<<stare<<" ";
            }
        }
        else if (cmd == 2) {
            cout<<"Alfabetul de intrare este: ";
            for (string intrare : af.getAlfabet()) {
                cout<<intrare<<" ";
            }
        }
        else if (cmd == 3) {
            cout<<"Multimea tranzitiilor este:"<<endl;
            for (Tranzitie t : af.getTranzitii()) {
                cout<<t.toString()<<endl;
            }
        }
        else if (cmd == 4) {
            cout<<"Starile finale sunt: ";
            for (string stare : af.getStariFinale()) {
                cout<<stare<<" ";
            }
        }
        else if (cmd == 5) {
            cout<<"Dati secventa: ";
            string secventa;
            cin >> secventa;
            if (af.verifica(secventa)) cout<<"Secventa este acceptata!";
            else cout<<"Secventa nu este acceptata!";
        }
        else if (cmd == 6) {
            cout<<"Dati secventa: ";
            string secventa;
            cin >> secventa;
            cout<<"Cel mai lung prefix acceptat de AF este: "<<af.prefix(secventa);
        }
        else if (cmd == 0) {
            break;
        }
        else {
            cout<<"Comanda invalida!";
        }

        cout<<endl;
    }
}
