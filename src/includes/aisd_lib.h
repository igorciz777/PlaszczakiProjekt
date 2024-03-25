/**
 * @file aisd_lib.h
 * @brief Biblioteka do obsługi struktur danych i algorytmów
*/

#include <vector>

struct Wierzcholek{
    int wartosc;
    Wierzcholek(int wartosc);
};

struct Krawedz{
    struct Wierzcholek *wierzcholek1;
    struct Wierzcholek *wierzcholek2;
    int waga;
    Krawedz(struct Wierzcholek *wierzcholek1, struct Wierzcholek *wierzcholek2, int waga);
};

struct Graf{
    int liczbaWierzcholkow;
    int liczbaKrawedzi;
    std::vector<std::vector<int>> macierzSasiedztwa;
    std::vector<struct Wierzcholek> wierzcholki;
    std::vector<struct Krawedz> krawedzie;
    Graf();
    Graf(int liczbaWierzcholkow, int liczbaKrawedzi);
    void dodajWierzcholek(int wartosc);
    void dodajWiezcholek(struct Wierzcholek wierzcholek);
    void dodajKrawedz(struct Wierzcholek *wierzcholek1, struct Wierzcholek *wierzcholek2, int waga);
    void dodajKrawedz(struct Krawedz krawedz);
    void getMacierzSasiedztwa();
};

struct SiecPrzeplywowa : Graf{
    struct Wierzcholek *zrodlo; // S
    struct Wierzcholek *ujscie; // T
    SiecPrzeplywowa();
};



