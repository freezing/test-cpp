//
// Created by Nikola Stojiljkovic on 5/6/18.
//

#ifndef OOPCPP_BAZA_LINIJA_H
#define OOPCPP_BAZA_LINIJA_H

#include <set>
#include <string>
#include <map>
#include "linija.h"
#include "baza_stajalista.h"

using namespace std;

class BazaLinija {
private:
    // Index linija po sifri linije.
    map<string, Linija> linije;
    // Index linija po sifri stajalista.
    map<int, set<string>> linijeIndexPoSifriStajalista;

    shared_ptr<BazaStajalista> bazaStajalistaPtr;

    bool pripadaZoni(const Smer& smer, int zona);
    bool pripadaZoni(const Linija& linija, int zona);
    void dodajLinijuUIndexPoSifriStajalista(const Linija& linija);
    void dodajLiniju(const Linija& linija);
    void obrisiLiniju(const string& sifraLinije);

public:
    BazaLinija(const set<Linija>& linije, const shared_ptr<BazaStajalista>& bazaStajalistaPtr);
    set<Linija> getLinije(int zona);
    set<Linija> getLinije(const set<int>& zone);
    set<Linija> getLinijeZaStajaliste(int sifraStajalista);
    void promeniSifruLinije(const string& staraSifra, const string& novaSifra);
};

#endif //OOPCPP_BAZA_LINIJA_H
