/**
 * @file Graf.h
 * @brief Plik nagłówkowy dla implementacji stuktur i algorytmów grafowych
 * 
 * Zawiera definicje struktur Wierzcholek, Krawedz, Graf oraz SiecPrzeplywowa
*/

#include <vector>


/**
 * @brief Struktura reprezentująca wierzchołek grafu
 * 
 * Struktura przechowuje wartość wierzchołka //TODO: wieksza uniwersalnosc, np char, string zamiast int
 * 
 * @param wartosc Wartość wierzchołka
*/
struct Wierzcholek{
    int wartosc;
    Wierzcholek(int wartosc);
};

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
    struct Wierzcholek *wierzcholek1;
    struct Wierzcholek *wierzcholek2;
    int waga;
    Krawedz(struct Wierzcholek *wierzcholek1, struct Wierzcholek *wierzcholek2, int waga);
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
    std::vector<std::vector<int>> getMacierzSasiedztwa();
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
    struct Wierzcholek *zrodlo; // S
    struct Wierzcholek *ujscie; // T
    SiecPrzeplywowa();
};