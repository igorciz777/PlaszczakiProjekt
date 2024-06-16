#include <iostream>
#include <vector>

#ifndef llu
    #define llu long long unsigned
#endif
#ifndef lli
    #define lli long long
#endif

/**
 * @file Kmp.h
 * @brief Klasa reprezentująca algorytm KMP
 * 
 * Klasa zawiera metody do tworzenia tablicy LPS oraz wyszukiwania wzorca w tekście
 * 
 * @fn stworzLPS - metoda tworząca tablicę LPS
 * @fn kmpSzukaj - metoda wyszukująca wzorzec w tekście
 * 
 * @see Kmp.cpp
*/
class KMP{
    public:
        /**
         * @brief Metoda tworząca tablicę LPS
         * 
         * Tworzy tablicę LPS (Longest Prefix Suffix) dla danego wzorca
         * 
         * @param wzorzec Wzorzec, dla którego tworzymy tablicę LPS
        */
        std::vector<lli> static stworzLPS(const std::string& wzorzec);

        /**
         * @brief Metoda wyszukująca wzorzec w tekście
         * 
         * @param tekst Tekst, w którym szukamy wzorca
         * 
         * @param wzorzec Wzorzec, który szukamy w tekście
        */ 
        std::vector<lli> static kmpSzukaj(const std::string& tekst, const std::string& wzorzec);    
};

