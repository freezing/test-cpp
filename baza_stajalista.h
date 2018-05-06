//
// Created by Nikola Stojiljkovic on 5/6/18.
//

#ifndef OOPCPP_BAZA_STAJALISTA_H
#define OOPCPP_BAZA_STAJALISTA_H

#include <map>
#include <set>

#include "stajaliste.h"

using namespace std;

class BazaStajalista {
private:
    // Index stajalista po sifri stajalista.
    map<int, Stajaliste> stajalista;

public:
    BazaStajalista(const set<Stajaliste>& stajalista) {
        for (auto stajaliste : stajalista) {
            // Napravi index za stajalista po sifri stajalista (osnovni).
            this->stajalista[stajaliste.getSifra()] = stajaliste;
        }
    }

    Stajaliste getStajaliste(int sifraStajalista) {
        return stajalista[sifraStajalista];
    }
};

#endif //OOPCPP_BAZA_STAJALISTA_H
