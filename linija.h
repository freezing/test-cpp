//
// Created by Nikola Stojiljkovic on 5/5/18.
//

#ifndef OOPCPP_LINIJA_H
#define OOPCPP_LINIJA_H

#include <string>

#include "smer.h"

using namespace std;

class Linija {
private:
    string sifra;
    string okretnica1, okretnica2;
    Smer smerA, smerB;

public:
    Linija() {}
    Linija(const string& sifra,
           const string& okretnica1,
           const string& okretnica2,
           const Smer& smerA,
           const Smer& smerB)
            : sifra(sifra), okretnica1(okretnica1), okretnica2(okretnica2), smerA(smerA), smerB(smerB) {}

    const Smer& getSmerA() const { return smerA; }
    const Smer& getSmerB() const { return smerB; }

    string getSifra() const {
        return sifra;
    }

    bool operator < (const Linija& other) const {
        return sifra < other.sifra;
    }
};

#endif //OOPCPP_LINIJA_H
