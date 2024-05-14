#include "Kmp.h"

std::vector<int> KMP::stworzLPS(const std::string& wzorzec) {
    int m = wzorzec.length();
    std::vector<int> lps(m, 0);
    int len = 0;
    int i = 1;

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

std::vector<int> KMP::kmpSzukaj(const std::string& tekst, const std::string& wzorzec) {
    std::vector<int> lps = stworzLPS(wzorzec);
    std::vector<int> indices;

    int n = tekst.length();
    int m = wzorzec.length();
    int i = 0;
    int j = 0;

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