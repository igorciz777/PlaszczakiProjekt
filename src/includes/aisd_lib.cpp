/**
 * 
 * 
 * 
 * Biblioteka do implementacji algorytmow i struktur danych
 * 
 * 
 * 
*/
#include "aisd_lib.h"

Wierzcholek::Wierzcholek(int wartosc){
    this->wartosc = wartosc;
}

Krawedz::Krawedz(Wierzcholek *wierzcholek1, Wierzcholek *wierzcholek2, int waga){
    this->wierzcholek1 = wierzcholek1;
    this->wierzcholek2 = wierzcholek2;
    this->waga = waga;
}

Graf::Graf(){
    this->liczbaWierzcholkow = 0;
    this->liczbaKrawedzi = 0;
}
Graf::Graf(int liczbaWierzcholkow, int liczbaKrawedzi){
    this->liczbaWierzcholkow = liczbaWierzcholkow;
    this->liczbaKrawedzi = liczbaKrawedzi;
    this->wierzcholki = std::vector<Wierzcholek>(liczbaWierzcholkow);
    this->krawedzie = std::vector<Krawedz>(liczbaKrawedzi);
}
void Graf::dodajWierzcholek(int wartosc){
    this->wierzcholki.push_back(Wierzcholek(wartosc));
}
void Graf::dodajWiezcholek(Wierzcholek wierzcholek){
    this->wierzcholki.push_back(wierzcholek);
}
void Graf::dodajKrawedz(Wierzcholek *wierzcholek1, Wierzcholek *wierzcholek2, int waga){
    this->krawedzie.push_back(Krawedz(wierzcholek1, wierzcholek2, waga));
}
void Graf::dodajKrawedz(Krawedz krawedz){
    this->krawedzie.push_back(krawedz);
}
void Graf::getMacierzSasiedztwa(){
    this->macierzSasiedztwa = std::vector<std::vector<int>>(this->liczbaWierzcholkow, std::vector<int>(this->liczbaWierzcholkow, 0));
    for(int i = 0; i < this->liczbaKrawedzi; i++){
        this->macierzSasiedztwa[this->krawedzie[i].wierzcholek1->wartosc - 'A'][this->krawedzie[i].wierzcholek2->wartosc - 'A'] = this->krawedzie[i].waga;
    }
}
