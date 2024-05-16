/**
 * @file Huffman.cpp
 * 
 * @brief Plik implementacji kompresji algorytmem Huffmana
 * 
 * Plik zawiera implementację funkcji kompresującej tekst algorytmem Huffmana
*/

#include "Huffman.h"

int operator<(const WezelHuffmana& a, const WezelHuffmana& b) {
    return a.czestotliwosc > b.czestotliwosc;
}

std::string Huffman::koduj(const std::string& tekst) {
    zbudujDrzewo(tekst);
    zbudujKody(korzen, "");
    std::string zakodowany_tekst = "";
    for (char znak : tekst) {
        zakodowany_tekst += kody[znak];
    }
    
    return zakodowany_tekst;
}

std::string Huffman::dekoduj(const std::string& tekst) {
    std::string odkodowany_tekst = "";
    WezelHuffmana* aktualny = korzen;
    for (char znak : tekst) {
        if (znak == '0') {
            aktualny = aktualny->lewy;
        } else {
            aktualny = aktualny->prawy;
        }

        if (aktualny->lewy == nullptr && aktualny->prawy == nullptr) {
            odkodowany_tekst += aktualny->znak;
            aktualny = korzen;
        }
    }
    usunDrzewo(korzen);
    return odkodowany_tekst;
}

void Huffman::zbudujDrzewo(const std::string& tekst) {
    std::unordered_map<char, int> czestotliwosci;
    for (char znak : tekst) {
        czestotliwosci[znak]++;
    }

    std::priority_queue<WezelHuffmana> kolejka;
    for (auto para : czestotliwosci) {
        WezelHuffmana* wezel = new WezelHuffmana();
        wezel->znak = para.first;
        wezel->czestotliwosc = para.second;
        wezel->lewy = nullptr;
        wezel->prawy = nullptr;
        kolejka.push(*wezel);
    }

    while (kolejka.size() > 1) {
        WezelHuffmana* lewy = new WezelHuffmana(kolejka.top());
        kolejka.pop();
        WezelHuffmana* prawy = new WezelHuffmana(kolejka.top());
        kolejka.pop();

        WezelHuffmana* wezel = new WezelHuffmana();
        wezel->czestotliwosc = lewy->czestotliwosc + prawy->czestotliwosc;
        wezel->lewy = lewy;
        wezel->prawy = prawy;
        kolejka.push(*wezel);
    }

    korzen = new WezelHuffmana(kolejka.top());
}

void Huffman::zbudujKody(WezelHuffmana* korzen, const std::string& kod) {
    if (korzen->lewy == nullptr && korzen->prawy == nullptr) {
        kody[korzen->znak] = kod;
    } else {
        zbudujKody(korzen->lewy, kod + "0");
        zbudujKody(korzen->prawy, kod + "1");
    }
}

void Huffman::usunDrzewo(WezelHuffmana* korzen) {
    if (korzen->lewy != nullptr) {
        usunDrzewo(korzen->lewy);
    }
    if (korzen->prawy != nullptr) {
        usunDrzewo(korzen->prawy);
    }
    delete korzen;
}

void Huffman::wypiszKod(WezelHuffmana* korzen, const std::string& kod) {
    if (korzen->lewy == nullptr && korzen->prawy == nullptr) {
        std::cout << korzen->znak << ": " << kod << std::endl;
    } else {
        wypiszKod(korzen->lewy, kod + "0");
        wypiszKod(korzen->prawy, kod + "1");
    }
}