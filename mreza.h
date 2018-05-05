//
// Created by Nikola Stojiljkovic on 5/5/18.
//

#ifndef OOPCPP_MREZA_H_H
#define OOPCPP_MREZA_H_H

#include <set>
#include <map>

#include "linija.h"
#include "stajaliste.h"

using namespace std;

class Mreza {
private:
    // Index linija po sifri linije.
    map<string, Linija> linije;
    // Index linija po sifri stajalista.
    map<int, set<string>> linijeIndexPoSifriStajalista;

    // Index stajalista po sifri stajalista.
    map<int, Stajaliste> stajalista;

    void dodajLinijuUIndexPoSifriStajalista(const Linija& linija);
    bool pripadaZoni(const Smer& smer, int zona);
    bool pripadaZoni(const Linija& linija, int zona);
    set<Linija> getLinije(int zona);

public:
    Mreza(const set<Linija>& linije, const set<Stajaliste>& stajalista);
    set<Linija> getLinije(const set<int>& zone);
    set<Linija> getLinijeZaStajaliste(int sifraStajalista);

    static Mreza parsiraj(const string& filename);
};

#endif //OOPCPP_MREZA_H_H
