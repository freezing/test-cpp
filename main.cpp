#include <iostream>
#include "mreza.h"

using namespace std;

int main(int argc, char** argv) {
    Mreza mreza = Mreza::parsiraj("/Users/freezing/mreza_data/");
    int sifraStajalista = 3629;
    cout << "Sifra stajalista: " << sifraStajalista << endl;
    set<Linija> linijeZaSifruStajalista = mreza.getBazaLinija()->getLinijeZaStajaliste(sifraStajalista);
    for (auto linija : linijeZaSifruStajalista) {
        cout << "  Sifra linije: " << linija.getSifra() << endl;
    }
    return 0;
}