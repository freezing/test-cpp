//
// Created by Nikola Stojiljkovic on 5/5/18.
//

#include "mreza.h"
#include <fstream>
#include <iostream>
#include <regex>

const regex linijaRegex("([^!]*)!([^!]*)!([^!]*)!");

void Mreza::dodajLinijuUIndexPoSifriStajalista(const Linija& linija) {
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

Mreza::Mreza(const set<Linija>& linije, const set<Stajaliste>& stajalista) {
    for (auto linija : linije) {
        // Napravi index za linije po sifri linije (osnovni).
        this->linije[linija.getSifra()] = linija;
        // Napravi index za linije po sifri stajalista.
        dodajLinijuUIndexPoSifriStajalista(linija);
    }

    for (auto stajaliste : stajalista) {
        // Napravi index za stajalista po sifri stajalista (osnovni).
        this->stajalista[stajaliste.getSifra()] = stajaliste;
    }
}

set<Linija> Mreza::getLinijeZaStajaliste(int sifraStajalista) {
    const set<string>& sifreLinijaZaStajaliste = linijeIndexPoSifriStajalista[sifraStajalista];
    set<Linija> linijeZaStajaliste;
    for (auto sifraLinije : sifreLinijaZaStajaliste) {
        linijeZaStajaliste.insert(linije[sifraLinije]);
    }
    return linijeZaStajaliste;
}

bool Mreza::pripadaZoni(const Smer& smer, int zona) {
    const vector<int>& sifreStajalista = smer.getSifreStajalista();
    for (auto sifraStajalista : sifreStajalista) {
        Stajaliste stajaliste = stajalista[sifraStajalista];
        if (stajaliste.getZona() == zona) {
            return true;
        }
    }
    return false;
}

bool Mreza::pripadaZoni(const Linija& linija, int zona) {
    Smer smerA = linija.getSmerA();
    Smer smerB = linija.getSmerB();
    return pripadaZoni(smerA, zona) || pripadaZoni(smerB, zona);
}

set<Linija> Mreza::getLinije(int zona) {
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

    for (auto linija : b) {
        if (a.find(linija) != a.end()) {
            presek.insert(linija);
        }
    }

    return presek;
}

set<Linija> Mreza::getLinije(const set<int>& zone) {
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
