// DoborTragarzy.cpp
#include "DoborTragarzy.h"
#include <cstring>
#include <climits>
#include <algorithm>

DoborTragarzy::DoborTragarzy() {
    std::memset(skojarzeniaZPrzodu, -1, sizeof(skojarzeniaZPrzodu));
    std::memset(skojarzeniaZTylu, -1, sizeof(skojarzeniaZTylu));
}

/*Dlaczego bfs i dfs sa tutaj i w problemie1.cpp*/
bool DoborTragarzy::wyszukiwanieWszerz() {
    std::queue<int> kolejka;
    for (int u = 0; u < MAKS; ++u) {
        if (skojarzeniaZPrzodu[u] == -1) {
            odleglosc[u] = 0;
            kolejka.push(u);
        } else {
            odleglosc[u] = INT_MAX;
        }
    }
    //odleglosc[-1] = INT_MAX;
    odleglosc[MAKS-1] = INT_MAX;
    while (!kolejka.empty()) {
        int u = kolejka.front();
        kolejka.pop();
        if (odleglosc[u] < odleglosc[MAKS-1]) {
            for (int v : listaSasiedztwa[u]) {
                if (odleglosc[skojarzeniaZTylu[v]] == INT_MAX) {
                    odleglosc[skojarzeniaZTylu[v]] = odleglosc[u] + 1;
                    kolejka.push(skojarzeniaZTylu[v]);
                }
            }
        }
    }
    //return (odleglosc[-1] != INT_MAX);
    return (odleglosc[MAKS-1] != INT_MAX);
}

bool DoborTragarzy::wyszukiwanieWGleb(int u) {
    if (u != -1) {
        for (int v : listaSasiedztwa[u]) {
            if (odleglosc[skojarzeniaZTylu[v]] == odleglosc[u] + 1) {
                if (wyszukiwanieWGleb(skojarzeniaZTylu[v])) {
                    skojarzeniaZTylu[v] = u;
                    skojarzeniaZPrzodu[u] = v;
                    return true;
                }
            }
        }
        odleglosc[u] = INT_MAX;
        return false;
    }
    return true;
}

int DoborTragarzy::algorytmHopcroftaKarpa() {
    int skojarzenia = 0;
    while (wyszukiwanieWszerz()) {
        for (int u = 0; u < MAKS; ++u) {
            if (skojarzeniaZPrzodu[u] == -1 && wyszukiwanieWGleb(u)) {
                skojarzenia++;
            }
        }
    }
    return skojarzenia;
}

void DoborTragarzy::dodajPolaczenie(int zPrzodu, int zTylu) {
    listaSasiedztwa[zPrzodu].push_back(zTylu);
}

void DoborTragarzy::inicjalizujTragarzy(int liczbaTragarzyZPrzodu, int liczbaTragarzyZTylu) {
    std::cout << "Pracownicy z rekoma z przodu (indeksy 0 do " << liczbaTragarzyZPrzodu - 1 << "):" << std::endl;
    for (int i = 0; i < liczbaTragarzyZPrzodu; i++) {
        std::cout << "Tragarz z rekoma z przodu [" << i << "]" << std::endl;
    }

    std::cout << "Pracownicy z rekoma z tylu (indeksy 0 do " << liczbaTragarzyZTylu - 1 << "):" << std::endl;
    for (int j = 0; j < liczbaTragarzyZTylu; j++) {
        std::cout << "Tragarz z rekoam tylu [" << j << "]" << std::endl;
    }
}
