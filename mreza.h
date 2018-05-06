//
// Created by Nikola Stojiljkovic on 5/5/18.
//

#ifndef OOPCPP_MREZA_H_H
#define OOPCPP_MREZA_H_H

#include <set>
#include <map>

#include "linija.h"
#include "stajaliste.h"
#include "baza_linija.h"
#include "baza_stajalista.h"

using namespace std;

class Mreza {
private:
    shared_ptr<BazaStajalista> bazaStajalistaPtr;
    shared_ptr<BazaLinija> bazaLinijaPtr;

public:
    Mreza(const set<Linija>& linije, const set<Stajaliste>& stajalista);
    static Mreza parsiraj(const string& filename);
    shared_ptr<BazaLinija> getBazaLinija() const { return bazaLinijaPtr; }
    shared_ptr<BazaStajalista> getBazaStajalista() const { return bazaStajalistaPtr; }
};

#endif //OOPCPP_MREZA_H_H
