//
// Created by Nikola Stojiljkovic on 5/5/18.
//

#include "mreza.h"
#include <fstream>
#include <iostream>
#include <regex>

const regex linijaRegex("([^!]*)!([^!]*)!([^!]*)!");

Mreza::Mreza(const set<Linija>& linije, const set<Stajaliste>& stajalista) {
    bazaStajalistaPtr = make_shared<BazaStajalista>(stajalista);
    bazaLinijaPtr = make_shared<BazaLinija>(linije, bazaStajalistaPtr);
}

string trimSpaces(const string& s) {
    int leftIdx = 0;
    while (leftIdx < s.size() && isspace(s[leftIdx])) {
        leftIdx++;
    }

    int rightIdx = s.size() - 1;
    while (rightIdx >= 0 && isspace(s[rightIdx])) {
        rightIdx--;
    }

    if (leftIdx <= rightIdx && leftIdx >= 0) {
        return s.substr(leftIdx, rightIdx + 1);
    }
    return "";
}

Mreza Mreza::parsiraj(const string& dirPath) {
    string buffer;
    string linijePath = dirPath + "_lines.txt";
    ifstream linijeFile(linijePath);

    set<Linija> linije;
    set<Stajaliste> stajalista;

    while (getline(linijeFile, buffer)) {
        buffer = trimSpaces(buffer);
        smatch match;
        if (regex_match(buffer, match, linijaRegex)) {
            string sifraLinije = match.str(1);
            string okretnica1 = match.str(2);
            string okretnica2 = match.str(3);

            string smerAPath = dirPath + sifraLinije + "_dirA.txt";
            string smerBPath = dirPath + sifraLinije + "_dirB.txt";

            vector<Stajaliste> smerAStajalista = Stajaliste::parsiraj(smerAPath);
            vector<Stajaliste> smerBStajalista = Stajaliste::parsiraj(smerBPath);

            Smer smerA(smerAStajalista);
            Smer smerB(smerBStajalista);

            Linija linija(sifraLinije, okretnica1, okretnica2, smerA, smerB);
            linije.insert(linija);
            stajalista.insert(smerAStajalista.begin(), smerAStajalista.end());
            stajalista.insert(smerBStajalista.begin(), smerBStajalista.end());
        } else {
            cout << "Greska prilikom parsiranja mreze: " << buffer << endl;
        }
    }
    linijeFile.close();
    return Mreza(linije, stajalista);
}
