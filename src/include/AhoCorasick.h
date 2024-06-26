/**
 * @file AhoCorasick.h
 * @brief Plik nagłówkowy klasy AhoCorasick
 * 
 * Plik zawiera deklaracje klasy AhoCorasick oraz struktury Wezel
 * 
 * @see AhoCorasick.cpp
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

#ifndef llu
    #define llu long long unsigned
#endif
#ifndef lli
    #define lli long long
#endif

/**
 * @brief Struktura reprezentująca węzeł drzewa Aho-Corasicka
 * 
 * Struktura przechowuje wskaźniki na następne węzły, wskaźnik na węzeł sufiksowy, wektory wzorców i znaków
 * 
 * @param sufiks Wskaźnik na węzeł sufiksowy
 * @param nast Tablica wskaźników na następne węzły
 * @param wzorce Wektor wzorców
 * @param id Identyfikator węzła (dla debugowania)
*/
struct Wezel{
    Wezel* sufiks;
    Wezel* nast[256];
    std::vector<int> wzorce;
    int id;
    /**
     * @brief Konstruktor struktury Wezel
     * 
     * Tworzy nowy węzeł drzewa Aho-Corasicka
    */
    Wezel();
};

/**
 * @brief Klasa reprezentująca algorytm Aho-Corasicka
 * 
 * Klasa przechowuje wskaźnik na korzeń drzewa Aho-Corasicka
 * 
 * @param trie Wskaźnik na korzeń drzewa Aho-Corasicka
 * @param nast_id Identyfikator następnego węzła
 * 
 * @fn AhoCorasick - konstruktor klasy
 * @fn szukaj - metoda szukająca wzorców w tekście
 * 
 * @see AhoCorasick.cpp
*/
class AhoCorasick{
    private:
        static int nast_id;
        Wezel* trie;
        /**
         * @brief Metoda tworząca nowy węzeł
         * 
         * Tworzy nowy węzeł drzewa Aho-Corasicka
         * 
         * @return Wskaźnik na nowy węzeł
        */
        Wezel* sufiks(Wezel* x, char c);
        /**
         * @brief Metoda wstawiająca wzorzec do drzewa
         * 
         * Wstawia wzorzec do drzewa Aho-Corasicka
         * 
         * @param x Wskaźnik na węzeł
         * @param s Wzorzec
         * @param id Identyfikator węzła (dla debugowania)
        */
        void wstaw(Wezel* x, std::string s, int id);
    public:
        /**
         * @brief Konstruktor klasy AhoCorasick
         * 
         * Tworzy obiekt klasy AhoCorasick na podstawie wektora wzorców.
         * 
         * @param p Wektor wzorców
         */
        AhoCorasick(std::vector<std::string> &p);
        
        /**
         * @brief Konstruktor klasy AhoCorasick
         * 
         * Tworzy obiekt klasy AhoCorasick na podstawie pojedynczego wzorca.
         * 
         * @param p Wzorzec
         */
        AhoCorasick(std::string p);
        
        /**
         * @brief Metoda szukająca wzorców w tekście
         * 
         * Szuka wszystkich wzorców z drzewa w podanym tekście.
         * 
         * @param s Tekst
         * @return Wektor par (pozycja wzorca, identyfikator wzorca)
         */
        std::vector<std::pair<lli,lli> > szukaj(std::string s);
};