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

using namespace std;

class SkojarzenieDwudzielne {
private:
    vector<vector<int>> graf;    // Graf reprezentowany jako lista sąsiedztwa
    vector<int> parowanieU, parowanieV, odleglosc;
    int rozmiarU, rozmiarV;

public:
    SkojarzenieDwudzielne(int rozmiarU, int rozmiarV) : rozmiarU(rozmiarU), rozmiarV(rozmiarV), graf(rozmiarU) {
        parowanieU.assign(rozmiarU, -1);
        parowanieV.assign(rozmiarV, -1);
        odleglosc.resize(rozmiarU + 1);
    }

    void dodajKrawedz(int u, int v) {
        graf[u].push_back(v);
    }

    bool bfs() {
        queue<int> kolejka;
        for (int u = 0; u < rozmiarU; u++) {
            if (parowanieU[u] == -1) {
                odleglosc[u] = 0;
                kolejka.push(u);
            } else {
                odleglosc[u] = INT_MAX;
            }
        }
        odleglosc[rozmiarU] = INT_MAX;
        while (!kolejka.empty()) {
            int u = kolejka.front();
            kolejka.pop();
            if (odleglosc[u] < odleglosc[rozmiarU]) {
                for (int v : graf[u]) {
                    if (odleglosc[parowanieV[v]] == INT_MAX) {
                        odleglosc[parowanieV[v]] = odleglosc[u] + 1;
                        kolejka.push(parowanieV[v]);
                    }
                }
            }
        }
        return odleglosc[rozmiarU] != INT_MAX;
    }

    bool dfs(int u) {
        if (u != -1) {
            for (int v : graf[u]) {
                if (odleglosc[parowanieV[v]] == odleglosc[u] + 1) {
                    if (parowanieV[v] == -1 || dfs(parowanieV[v])) {
                        parowanieV[v] = u;
                        parowanieU[u] = v;
                        return true;
                    }
                }
            }
            odleglosc[u] = INT_MAX;
            return false;
        }
        return true;
    }

    int znajdzMaksymalneSkojarzenie() {
        int skojarzenie = 0;
        while (bfs()) {
            for (int u = 0; u < rozmiarU; u++) {
                if (parowanieU[u] == -1) {
                    if (dfs(u)) {
                        skojarzenie++;
                    }
                }
            }
        }
        return skojarzenie;
    }
};

int main() {
    int liczbaTragarzyPrzod = 3, liczbaTragarzyTyl = 3;

    SkojarzenieDwudzielne graf(liczbaTragarzyPrzod, liczbaTragarzyTyl);
    for (int u = 0; u < liczbaTragarzyPrzod; u++) {
        for (int v = 0; v < liczbaTragarzyTyl; v++) {
            graf.dodajKrawedz(u, v);
        }
    }

    int wynik = graf.znajdzMaksymalneSkojarzenie();
    cout << "Maksymalne skojarzenie: " << wynik << endl;

    return 0;
}
