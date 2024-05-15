/*Program buduje graf dwudzielny, w którym każdy tragarz z przodu
 jest połączony z każdym tragarzem z tyłu. Następnie za pomocą 
 algorytmu BFS i DFS szuka maksymalnego skojarzenia, które jest 
 maksymalną liczbą par, gdzie każda para składa się z tragarza z przodu 
 i tragarza z tyłu. Wynikowy maksymalny skojarzenie reprezentuje 
 maksymalną liczbę par, które mogą efektywnie współpracować.*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

const int MAKS = 1000;  // Maksymalna liczba pracowników w każdej grupie
int skojarzeniaZPrzodu[MAKS], skojarzeniaZTylu[MAKS], odleglosc[MAKS];
vector<int> listaSasiedztwa[MAKS];

bool wyszukiwanieWszerz() {
    queue<int> kolejka;
    for (int u = 0; u < MAKS; ++u) {
        if (skojarzeniaZPrzodu[u] == -1) {
            odleglosc[u] = 0;
            kolejka.push(u);
        } else {
            odleglosc[u] = INT_MAX;
        }
    }
    odleglosc[-1] = INT_MAX;
    while (!kolejka.empty()) {
        int u = kolejka.front();
        kolejka.pop();
        if (odleglosc[u] < odleglosc[-1]) {
            for (int v : listaSasiedztwa[u]) {
                if (odleglosc[skojarzeniaZTylu[v]] == INT_MAX) {
                    odleglosc[skojarzeniaZTylu[v]] = odleglosc[u] + 1;
                    kolejka.push(skojarzeniaZTylu[v]);
                }
            }
        }
    }
    return (odleglosc[-1] != INT_MAX);
}

bool wyszukiwanieWGleb( int u ) {
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

int algorytmHopcroftaKarpa() {
    memset(skojarzeniaZPrzodu, -1, sizeof(skojarzeniaZPrzodu));
    memset(skojarzeniaZTylu, -1, sizeof(skojarzeniaZTylu));
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

int main() {
    int liczbaPracownikowZPrzodu, liczbaPracownikowZTylu, liczbaPolaczen;
    cout << "Podaj liczbe pracownikow z rekoma z przodu: ";
    cin >> liczbaPracownikowZPrzodu;
    cout << "Podaj liczbe pracownikow z rekoma z tylu: ";
    cin >> liczbaPracownikowZTylu;

     cout << "Pracownicy z rekoma z przodu (indeksy 0 do " << liczbaPracownikowZPrzodu - 1 << "):" << endl;
    for (int i = 0; i < liczbaPracownikowZPrzodu; i++) {
        cout << "Pracownik z przodu [" << i << "]" << endl;
    }

    cout << "Pracownicy z rekoma z tylu (indeksy 0 do " << liczbaPracownikowZTylu - 1 << "):" << endl;
    for (int j = 0; j < liczbaPracownikowZTylu; j++) {
        cout << "Pracownik z tylu [" << j << "]" << endl;
    }
    
    cout << "Podaj liczbe polaczen miedzy pracownikami: ";
    cin >> liczbaPolaczen;

    for (int i = 0; i < liczbaPolaczen; ++i) {
        int zPrzodu, zTylu;
        cout << "Podaj pare pracownikow (z przodu i z tylu), ktorzy wspolpracuja: ";
        cin >> zPrzodu >> zTylu;
        listaSasiedztwa[zPrzodu].push_back(zTylu);
    }

    cout << "Maksymalne skojarzenie: " << algorytmHopcroftaKarpa() << endl;
    return 0;
}

