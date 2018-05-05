//
// Created by Nikola Stojiljkovic on 5/5/18.
//

#ifndef OOPCPP_STAJALISTE_H
#define OOPCPP_STAJALISTE_H

#include <string>
#include <vector>

#include "lokacija.h"

using namespace std;

class Stajaliste {
private:
    int sifra;
    string naziv;
    Lokacija lokacija;
    int zona;

public:
    Stajaliste() {}

    Stajaliste(int sifra, const string& naziv, double x, double y, int zona)
            : sifra(sifra), naziv(naziv), lokacija(x, y), zona(zona) {}
    int getSifra() const { return sifra; }
    int getZona() const { return zona; }
    static vector<Stajaliste> parsiraj(const string& filepath);

    bool operator < (const Stajaliste& other) const {
        return sifra < other.sifra;
    }
};

#endif //OOPCPP_STAJALISTE_H
