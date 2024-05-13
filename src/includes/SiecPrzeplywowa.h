/**
 * @file SiecPrzeplywowa.h
 * @brief Plik nagłówkowy dla implementacji sieci przepływowej
*/

#include <vector>
#include <algorithm>

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
    int cel;
    int przepustowosc;
    int przeplyw;
    int przepustowoscPoczatkowa;
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
        SiecPrzeplywowa(int n);
        /**
         * @brief Dodaje wierzchołek do grafu
         * 
         * Dodaje wierzchołek do grafu o numerze v
         * 
         * @param v - numer wierzchołka
        */
        void dodajWierzcholek(int v);
        /**
         * @brief Dodaje krawędź do grafu
         * 
         * Dodaje krawędź do grafu między wierzchołkami u i v o przepustowości przepustowosc
         * 
         * @param u - wierzchołek źródłowy
         * @param v - wierzchołek docelowy
         * @param przepustowosc - przepustowość krawędzi
        */
        void dodajKrawedz(int u, int v, int przepustowosc);
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

        int edmondsKarp(int s, int t, std::vector<std::vector<int>> &sciezki_out);
    private:
        int n;
        std::vector<std::vector<Krawedz>> graf;
        std::vector<int> poprzednik;
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
        int bfs(int s, int t);
};