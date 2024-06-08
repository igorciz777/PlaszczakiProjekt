/**
 * @file Tekst.cpp
 * @brief Plik implementacji funkcji do obsługi tekstu
 * 
 * Plik zawiera implementacje funkcji zamieniających fragmenty tekstu oraz konwersji ASCII <-> BIN
 * 
 * @see Tekst.h
*/

#include "Tekst.h"
#define llu long long unsigned



void Tekst::zamienFragment(std::string &tekst, int start, std::string fragment){
    tekst = tekst.substr(0, start) + fragment + tekst.substr(start + fragment.size());
}

void Tekst::zamienFragment(std::string &tekst, int start, std::pair<std::string, std::string> fragment_zamiana){
    tekst = tekst.substr(0, start) + fragment_zamiana.second + tekst.substr(start + fragment_zamiana.first.size());
}

std::string Tekst::ASCIItoBIN(std::string tekst){
    std::string wynik;
    for(char c : tekst){
        for(int i = 7; i >= 0; i--){
            wynik += ((c >> i) & 1) + '0';
        }
    }
    return wynik;
}

std::string Tekst::BINtoASCII(std::string tekst){
    std::string wynik;
    for(llu i = 0; i < tekst.size(); i += 8){
        char c = 0;
        for(int j = 0; j < 8; j++){
            c += (tekst[i + j] - '0') << (7 - j);
        }
        wynik += c;
    }
    return wynik;
}