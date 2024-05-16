/**
 * @file Tekst.h
 * @brief Plik nagłówkowy dla implementacji funkcji do obsługi tekstu
*/

#include <iostream>
#include <map>

/**
 * @brief Klasa Tekst
 * 
 * Klasa zawiera funkcje do obsługi tekstu
 * 
*/
class Tekst{
    public:
        /**
         * @brief Zamienia fragment w tekście
         * 
         * @param tekst Tekst
         * @param start Indeks początku fragmentu
         * @param fragment Nowy fragment
         * 
         * 
        */
        static void zamienFragment(std::string &tekst, int start, std::string fragment);
        static void zamienFragment(std::string &tekst, int start, std::pair<std::string, std::string> fragment_zamiana);
        /**
         * @brief Zamienia tekst ASCII na binarny
         * 
         * @param tekst Tekst ASCII
         * 
        */
        static std::string ASCIItoBIN(std::string tekst);
        /**
         * @brief Zamienia tekst binarny na ASCII
         * 
         * @param tekst Tekst binarny
         * 
        */
        static std::string BINtoASCII(std::string tekst);
        

};