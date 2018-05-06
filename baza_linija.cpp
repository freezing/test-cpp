//
// Created by Nikola Stojiljkovic on 5/6/18.
//

#include <set>
#include "linija.h"
#include "baza_linija.h"

void BazaLinija::dodajLinijuUIndexPoSifriStajalista(const Linija& linija) {
    vector<int> stajalistaSmerA = linija.getSmerA().getSifreStajalista();
    vector<int> stajalistaSmerB = linija.getSmerB().getSifreStajalista();
    set<int> svaStajalista;
    svaStajalista.insert(stajalistaSmerA.begin(), stajalistaSmerA.end());
    svaStajalista.insert(stajalistaSmerB.begin(), stajalistaSmerB.end());
    // Indeksiraj liniju po svim stajalistima.
    for (auto sifraStajalista : svaStajalista) {
        // Ukoliko kljuc za sifru stajalista ne postoji, operator [] ce napraviti novi sa praznim skupom za value.
        // Ukoliko postoji, vratice referencu ka trenutnom skupu linija.
        // Zatim dodajemo novu liniju u skup.
        linijeIndexPoSifriStajalista[sifraStajalista].insert(linija.getSifra());
    }
}

BazaLinija::BazaLinija(const set<Linija> &linije, const shared_ptr<BazaStajalista>& bazaStajalistaPtr) {
    for (auto linija : linije) {
        // Napravi index za linije po sifri linije (osnovni).
        this->linije[linija.getSifra()] = linija;
        // Napravi index za linije po sifri stajalista.
        dodajLinijuUIndexPoSifriStajalista(linija);
    }
    this->bazaStajalistaPtr = bazaStajalistaPtr;
}

set<Linija> BazaLinija::getLinijeZaStajaliste(int sifraStajalista) {
    const set<string>& sifreLinijaZaStajaliste = linijeIndexPoSifriStajalista[sifraStajalista];
    set<Linija> linijeZaStajaliste;
    for (auto sifraLinije : sifreLinijaZaStajaliste) {
        linijeZaStajaliste.insert(linije[sifraLinije]);
    }
    return linijeZaStajaliste;
}

bool BazaLinija::pripadaZoni(const Smer& smer, int zona) {
    const vector<int>& sifreStajalista = smer.getSifreStajalista();
    for (auto sifraStajalista : sifreStajalista) {
        Stajaliste stajaliste = bazaStajalistaPtr->getStajaliste(sifraStajalista);
        if (stajaliste.getZona() == zona) {
            return true;
        }
    }
    return false;
}

bool BazaLinija::pripadaZoni(const Linija& linija, int zona) {
    Smer smerA = linija.getSmerA();
    Smer smerB = linija.getSmerB();
    return pripadaZoni(smerA, zona) || pripadaZoni(smerB, zona);
}

set<Linija> BazaLinija::getLinije(int zona) {
    // Linije nisu indeksirane po zoni, ali ako se ispostavi da je pretraga linija po zoni spora,
    // mozemo da ih indeksiramo i po zoni.
    set<Linija> linijeZona;
    for (auto linijaEntry : linije) {
        if (pripadaZoni(linijaEntry.second, zona)) {
            linijeZona.insert(linijaEntry.second);
        }
    }
    return linijeZona;
}

set<Linija> presekSkupova(const set<Linija>& a, const set<Linija>& b) {
    set<Linija> presek;

    for (auto linija : a) {
        if (b.find(linija) != b.end()) {
            presek.insert(linija);
        }
    }

    return presek;
}

set<Linija> BazaLinija::getLinije(const set<int>& zone) {
    set<Linija> linijeZone;
    bool initialized = false;
    for (auto zona : zone) {
        if (!initialized) {
            initialized = true;
            linijeZone = getLinije(zona);
        } else {
            linijeZone = presekSkupova(linijeZone, getLinije(zona));
        }
    }
    return linijeZone;
}