/**
 * @file Huffman.h
 * @brief Plik nagłówkowy dla implementacji kompresji algorytmem Huffmana
*/

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

struct WezelHuffmana {
    char znak;
    int czestotliwosc;
    WezelHuffmana* lewy;
    WezelHuffmana* prawy;
};

int operator<(const WezelHuffmana& a, const WezelHuffmana& b);

class Huffman {
    public:
        std::string koduj(const std::string& tekst);
        std::string dekoduj(const std::string& tekst);
        WezelHuffmana* getKorzen() { return korzen; }
    private:
        void wypiszKod(WezelHuffmana* korzen, const std::string& kod);
        void zbudujDrzewo(const std::string& tekst);
        void zbudujKody(WezelHuffmana* korzen, const std::string& kod);
        void usunDrzewo(WezelHuffmana* korzen);
        WezelHuffmana* korzen;
        std::unordered_map<char, std::string> kody;
};
