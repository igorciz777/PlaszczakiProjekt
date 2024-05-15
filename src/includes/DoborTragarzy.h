// DoborTragarzy.h
#include <vector>
#include <queue>
#include <iostream>

class DoborTragarzy {
private:
    static const int MAKS = 1000;  // Maksymalna liczba pracowników
    int skojarzeniaZPrzodu[MAKS];
    int skojarzeniaZTylu[MAKS];
    int odleglosc[MAKS];
    std::vector<int> listaSasiedztwa[MAKS];

    bool wyszukiwanieWszerz();
    bool wyszukiwanieWGleb(int u);

public:
    DoborTragarzy();
    void dodajPolaczenie(int zPrzodu, int zTylu);
    int algorytmHopcroftaKarpa();
    void inicjalizujTragarzy(int liczbaPracownikowZPrzodu, int liczbaPracownikowZTylu);
};
