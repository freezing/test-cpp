//
// Created by Nikola Stojiljkovic on 5/5/18.
//

#ifndef OOPCPP_SMER_H
#define OOPCPP_SMER_H

#include <vector>
#include "stajaliste.h"

using namespace std;

class Smer {
private:
    vector<int> sifreStajalista;

public:
    Smer() {}
    Smer(const vector<Stajaliste>& stajalista) {
        for (auto stajaliste : stajalista) {
            sifreStajalista.push_back(stajaliste.getSifra());
        }
    }

    const vector<int>& getSifreStajalista() const { return sifreStajalista; }
};

#endif //OOPCPP_SMER_H
