/**
 * @file Tekst.h
 * @brief Plik nagłówkowy dla implementacji funkcji do obsługi tekstu
 * 
 * Plik zawiera deklaracje klasy Tekst oraz funkcji zamieniających fragmenty tekstu oraz konwersji ASCII <-> BIN
 * 
 * @see Tekst.cpp
*/

#include <iostream>
#include <map>

/**
 * @brief Klasa Tekst
 * 
 * Klasa zawiera funkcje do obsługi tekstu
 * 
 * @fn zamienFragment - funkcja zamieniająca fragment w tekście
 * @fn ASCIItoBIN - funkcja zamieniająca tekst ASCII na binarny
 * @fn BINtoASCII - funkcja zamieniająca tekst binarny na ASCII
 * 
 * @see Tekst.cpp
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