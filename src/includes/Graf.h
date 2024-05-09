/**
 * @file Graf.h
 * @brief Plik nagłówkowy dla implementacji stuktur i algorytmów grafowych
 * 
 * Zawiera definicje struktur Wierzcholek, Krawedz, Graf oraz SiecPrzeplywowa
*/

#include <vector>
#include <queue>

#define INF 1000000

/**
 * @brief Struktura reprezentująca krawędź grafu
 * 
 * Struktura przechowuje wskaźniki na wierzchołki, które łączy krawędź oraz wagę krawędzi
 * 
 * @param wierzcholek1 Wskaźnik na pierwszy wierzchołek
 * @param wierzcholek2 Wskaźnik na drugi wierzchołek
 * @param waga Waga krawędzi
*/
struct Krawedz{
    int wierzcholek1;
    int wierzcholek2;
    int waga;
    Krawedz();
    Krawedz(int wierzcholek1, int wierzcholek2, int waga);
};

/**
 * @brief Klasa reprezentująca graf
 * 
 * Klasa przechowuje informacje o liczbie wierzchołków i krawędzi, wierzchołkach, krawędziach oraz macierzy sąsiedztwa
 * 
 * @param liczbaWierzcholkow Liczba wierzchołków
 * @param liczbaKrawedzi Liczba krawędzi
 * @param macierzSasiedztwa Macierz sąsiedztwa
 * @param wierzcholki Wektor wierzchołków
 * @param krawedzie Wektor krawędzi
*/
class Graf{
    private:
        int liczbaWierzcholkow;
        int liczbaKrawedzi;
        std::vector<std::vector<int>> macierzSasiedztwa;
        std::vector<int> wierzcholki;
        std::vector<struct Krawedz> krawedzie;
    public:
        Graf();
        Graf(int liczbaWierzcholkow, int liczbaKrawedzi);
        void dodajWierzcholek(int wartosc);
        void dodajKrawedz(int wierzcholek1, int wierzcholek2, int waga);
        void dodajKrawedz(struct Krawedz krawedz);
        std::vector<std::vector<int>> getMacierzSasiedztwa();
        std::vector<int> getWierzcholki();
        std::vector<struct Krawedz> getKrawedzie();
        int getLiczbaWierzcholkow();
        int getLiczbaKrawedzi();
        bool wierzcholekIstnieje(int wierzcholek);
};

/**
 * @brief Struktura reprezentująca sieć przepływową
 * 
 * Struktura dziedziczy po klasie Graf i dodaje pola zrodlo i ujscie
 * 
 * @param zrodlo Wskaźnik na wierzchołek źródłowy
 * @param ujscie Wskaźnik na wierzchołek ujściowy
*/
class SiecPrzeplywowa : Graf{
    private:
        int zrodlo; // S
        int ujscie; // T
        std::vector<std::vector<int>> przeplyw;
    public:
        int bfs(int zrodlo, int ujscie, std::vector<int> &poprzednik);
        int maxPrzeplyw(int zrodlo, int ujscie);
        SiecPrzeplywowa();
        std::vector<std::vector<int>> getPrzeplyw();
};

