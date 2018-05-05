//
// Created by Nikola Stojiljkovic on 5/5/18.
//

#include <fstream>
#include <regex>
#include <iostream>

#include "stajaliste.h"

const regex stajalisteRegex("([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)");

vector<Stajaliste> Stajaliste::parsiraj(const string& filepath) {
    vector<Stajaliste> stajalista;

    ifstream stajalistaFile(filepath);
    string buffer;
    while (getline(stajalistaFile, buffer)) {
        smatch match;
        if (regex_match(buffer, match, stajalisteRegex)) {
            int sifra = atoi(match.str(1).c_str());
            string naziv = match.str(2);
            double x = atof(match.str(3).c_str());
            double y = atof(match.str(4).c_str());
            int zona = atoi(match.str(5).c_str());
            Stajaliste stajaliste(sifra, naziv, x, y, zona);
            stajalista.push_back(stajaliste);
        } else {
            cout << "Greska prilikom parsiranja stajalista: " << buffer << endl;
        }
    }

    stajalistaFile.close();
    return stajalista;
}