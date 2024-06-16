/**
 * @file Huffman.h
 * @brief Plik nagłówkowy dla implementacji kompresji algorytmem Huffmana
 * 
 * Plik zawiera deklaracje klasy Huffman oraz struktury WezelHuffmana
 * 
 * @see Huffman.cpp
*/

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <sstream>

/**
 * @brief Struktura WezelHuffmana
 * 
 * Struktura przechowująca informacje o węźle drzewa Huffmana
 * 
 * @param znak - znak
 * @param czestotliwosc - czestotliwosc wystepowania znaku
 * @param lewy - wskaznik na lewe dziecko
 * @param prawy - wskaznik na prawe dziecko
 */
struct WezelHuffmana {
    char znak;
    int czestotliwosc;
    WezelHuffmana* lewy;
    WezelHuffmana* prawy;
};

/**
 * @brief Operator porównania dla struktury WezelHuffmana
 * 
 * Operator porównania dla struktury WezelHuffmana, porównuje czestotliwosc wystepowania znaku
 * 
 * @param a - lewy argument
 * @param b - prawy argument
 */
int operator<(const WezelHuffmana& a, const WezelHuffmana& b);


/**
 * @brief Klasa Huffman
 * 
 * Klasa Huffman zawiera metody do kompresji i dekompresji tekstu algorytmem Huffmana
 * 
 * @see WezelHuffmana
 * @see Huffman.cpp
 * 
 * @fn koduj - metoda kodująca tekst
 * @fn dekoduj - metoda dekodująca tekst
 * @fn getKorzen - metoda zwracająca korzeń drzewa Huffmana
 * @fn wypiszKod - metoda wypisująca kody Huffmana
 * 
 * @see Huffman.cpp
 */
class Huffman {
    public:
        /**
         * @brief Funkcja kodujaca tekst
         * 
         * Funkcja kodujaca tekst algorytmem Huffmana
         * 
         * @param tekst - tekst do zakodowania
         * 
         * @return zakodowany tekst
         */
        std::string koduj(const std::string& tekst);
        /**
         * @brief Funkcja dekodujaca tekst
         * 
         * Funkcja dekodujaca tekst zakodowany algorytmem Huffmana
         * 
         * @param tekst - tekst do odkodowania
         * 
         * @return odkodowany tekst
         */
        std::string dekoduj(const std::string& tekst);
        /**
         * @brief Funkcja zwracajaca korzen drzewa Huffmana
         * 
         * Funkcja zwracajaca korzen drzewa Huffmana
         * 
         * @return korzen drzewa Huffmana
         */
        WezelHuffmana* getKorzen() { return korzen; }
        /**
         * @brief Funkcja wypisujaca kody Huffmana
         * 
         * Funkcja wypisujaca kody Huffmana
         * 
         * @param korzen - korzen drzewa Huffmana
         * @param kod - kod Huffmana
         * @param out - strumien wyjsciowy
         */
        void wypiszKod(WezelHuffmana* korzen, const std::string& kod, std::stringstream& out);
    private:
        /**
         * @brief Funkcja budujaca drzewo Huffmana
         * 
         * Funkcja budujaca drzewo Huffmana
         * 
         * @param tekst - tekst do zakodowania
         */
        void zbudujDrzewo(const std::string& tekst);
        /**
         * @brief Funkcja budujaca kody Huffmana
         * 
         * Funkcja budujaca kody Huffmana
         * 
         * @param korzen - korzen drzewa Huffmana
         * @param kod - kod Huffmana
         */
        void zbudujKody(WezelHuffmana* korzen, const std::string& kod);
        /**
         * @brief Funkcja usuwajaca drzewo Huffmana
         * 
         * Funkcja usuwajaca drzewo Huffmana
         * 
         * @param korzen - korzen drzewa Huffmana
         */
        void usunDrzewo(WezelHuffmana* korzen);
        WezelHuffmana* korzen;
        std::unordered_map<char, std::string> kody;
};
