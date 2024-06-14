/**
 * @file Kmp.cpp
 * 
 * @brief Plik implementacji algorytmu wyszukiwania wzorca w tekście
 * 
 * Plik zawiera implementację algorytmu wyszukiwania wzorca w tekście
 * 
 * @see Kmp.h
 */
#include "Kmp.h"

std::vector<lli> KMP::stworzLPS(const std::string& wzorzec) {
    llu m = wzorzec.length();
    std::vector<lli> lps(m, 0);
    llu len = 0;
    llu i = 1;

    while (i < m) {
        if (wzorzec[i] == wzorzec[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

std::vector<lli> KMP::kmpSzukaj(const std::string& tekst, const std::string& wzorzec) {
    std::vector<lli> lps = stworzLPS(wzorzec);
    std::vector<lli> indices;

    llu n = tekst.length();
    llu m = wzorzec.length();
    llu i = 0;
    llu j = 0;

    while (i < n) {
        if (wzorzec[j] == tekst[i]) {
            j++;
            i++;
        }

        if (j == m) {
            indices.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && wzorzec[j] != tekst[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return indices;
}