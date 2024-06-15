/**
 * @file SiecPrzeplywowa.h
 * @brief Plik nagłówkowy dla implementacji sieci przepływowej
 * 
 * Plik zawiera deklaracje klasy SiecPrzeplywowa oraz struktury Krawedz
 * 
 * @see SiecPrzeplywowa.cpp
 * 
*/

#include <vector>
#include <algorithm>

#ifndef llu
    #define llu long long unsigned
#endif
#ifndef lli
    #define lli long long
#endif
#define INF 1000000000

/**
 * @brief Struktura przechowująca krawędź w grafie
 * 
 * Struktura przechowuje informacje o krawędzi w grafie, takie jak cel, przepustowość, przepływ oraz przepustowość początkową
 * 
 * @param cel - wierzchołek docelowy, graf przechowywany jest jako lista sąsiedztwa, dlatego pozycja w liście krawędzi jest równa źródłowemu wierzchołkowi, a więc potrzebny jest tylko cel
 * @param przepustowosc - przepustowość krawędzi
 * @param przeplyw - przepływ krawędzi
 * @param przepustowoscPoczatkowa - przepustowość początkowa krawędzi
*/
struct Krawedz{
    lli cel;
    lli przepustowosc;
    lli przeplyw;
    lli przepustowoscPoczatkowa;
};

/**
 * @brief Klasa reprezentująca sieć przepływową
 * 
 * Klasa reprezentuje sieć przepływową, w której wierzchołki reprezentują tragarzy, a krawędzie współpracę między nimi
 * 
 * @param n - ilość wierzchołków w grafie
 * @param graf - lista sąsiedztwa reprezentująca graf
 * @param poprzednik - tablica przechowująca poprzednik wierzchołka w ścieżce
 * 
 * @fn SiecPrzeplywowa - konstruktor klasy
 * @fn dodajWierzcholek - dodaje wierzchołek do grafu
 * @fn dodajKrawedz - dodaje krawędź do grafu
 * @fn edmondsKarp - algorytm Edmondsa-Karpa znajdujący maksymalny przepływ w grafie
 * @fn bfs - algorytm przeszukiwania wszerz znajdujący ścieżkę w grafie
*/
class SiecPrzeplywowa{
    public:
        /**
         * @brief Konstruktor klasy
         * 
         * Konstruktor klasy inicjalizuje graf o n wierzchołkach
         * 
         * @param n - ilość wierzchołków w grafie
        */
        SiecPrzeplywowa(lli n);
        /**
         * @brief Dodaje wierzchołek do grafu
         * 
         * Dodaje wierzchołek do grafu o numerze v
         * 
         * @param v - numer wierzchołka
        */
        void dodajWierzcholek(lli v);
        /**
         * @brief Dodaje krawędź do grafu
         * 
         * Dodaje krawędź do grafu między wierzchołkami u i v o przepustowości przepustowosc
         * 
         * @param u - wierzchołek źródłowy
         * @param v - wierzchołek docelowy
         * @param przepustowosc - przepustowość krawędzi
        */
        void dodajKrawedz(lli u, lli v, lli przepustowosc);
        /**
         * @brief Algorytm Edmondsa-Karpa znajdujący maksymalny przepływ w grafie
         * 
         * Algorytm Edmondsa-Karpa znajduje maksymalny przepływ w grafie między wierzchołkami s i t
         * 
         * @param s - wierzchołek źródłowy
         * @param t - wierzchołek docelowy
         * @param sciezki_out - zapisuje do zmiennej wszystkie prawidłowe ścieżki w sieci
         * 
         * @return maksymalny przepływ w grafie
        */

        lli edmondsKarp(lli s, lli t, std::vector<std::vector<lli>> &sciezki_out);
    private:
        lli n;
        std::vector<std::vector<Krawedz>> graf;
        std::vector<lli> poprzednik;
        /**
         * @brief Algorytm przeszukiwania wszerz znajdujący ścieżkę w grafie
         * 
         * Algorytm przeszukiwania wszerz znajduje ścieżkę w grafie między wierzchołkami s i t
         * 
         * @param s - wierzchołek źródłowy
         * @param t - wierzchołek docelowy
         * 
         * @return przepływ w znalezionej ścieżce
        */
        lli bfs(lli s, lli t);
};