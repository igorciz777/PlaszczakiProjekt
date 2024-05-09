/**
 * @file Graf.cpp
 * @brief Plik źródłowy dla implementacji stuktur i algorytmów grafowych
 *
 * Zawiera definicje metod dla struktur Wierzcholek, Krawedz, klasy Graf oraz SiecPrzeplywowa
 */

#include "Graf.h"

Wierzcholek::Wierzcholek()
{
    this->wartosc = 0;
}

Wierzcholek::Wierzcholek(int wartosc)
{
    this->wartosc = wartosc;
}
Krawedz::Krawedz()
{
    this->wierzcholek1 = nullptr;
    this->wierzcholek2 = nullptr;
    this->waga = 0;
}
Krawedz::Krawedz(Wierzcholek *wierzcholek1, Wierzcholek *wierzcholek2, int waga)
{
    this->wierzcholek1 = wierzcholek1;
    this->wierzcholek2 = wierzcholek2;
    this->waga = waga;
}

Graf::Graf()
{
    this->liczbaWierzcholkow = 0;
    this->liczbaKrawedzi = 0;
}
Graf::Graf(int liczbaWierzcholkow, int liczbaKrawedzi)
{
    this->liczbaWierzcholkow = liczbaWierzcholkow;
    this->liczbaKrawedzi = liczbaKrawedzi;
    this->wierzcholki = std::vector<Wierzcholek>(liczbaWierzcholkow);
    this->krawedzie = std::vector<Krawedz>(liczbaKrawedzi);
}
void Graf::dodajWierzcholek(int wartosc)
{
    this->wierzcholki.push_back(Wierzcholek(wartosc));
}
void Graf::dodajWiezcholek(Wierzcholek wierzcholek)
{
    this->wierzcholki.push_back(wierzcholek);
}
void Graf::dodajKrawedz(Wierzcholek *wierzcholek1, Wierzcholek *wierzcholek2, int waga)
{
    this->krawedzie.push_back(Krawedz(wierzcholek1, wierzcholek2, waga));
}
void Graf::dodajKrawedz(Krawedz krawedz)
{
    this->krawedzie.push_back(krawedz);
}
int Graf::getLiczbaWierzcholkow()
{
    return this->liczbaWierzcholkow;
}
int Graf::getLiczbaKrawedzi()
{
    return this->liczbaKrawedzi;
}
std::vector<Wierzcholek> Graf::getWierzcholki()
{
    return this->wierzcholki;
}
std::vector<Krawedz> Graf::getKrawedzie()
{
    return this->krawedzie;
}
/**
 * @brief Metoda zwracająca macierz sąsiedztwa
 *
 * Metoda tworzy macierz sąsiedztwa na podstawie wektora krawędzi
 *
 */
std::vector<std::vector<int>> Graf::getMacierzSasiedztwa()
{
    this->macierzSasiedztwa = std::vector<std::vector<int>>(this->liczbaWierzcholkow, std::vector<int>(this->liczbaWierzcholkow, 0));
    for (int i = 0; i < this->liczbaKrawedzi; i++)
    {
        this->macierzSasiedztwa[this->krawedzie[i].wierzcholek1->wartosc - 'A'][this->krawedzie[i].wierzcholek2->wartosc - 'A'] = this->krawedzie[i].waga;
    }
    return this->macierzSasiedztwa;
}

std::vector<std::vector<int>> SiecPrzeplywowa::getPrzeplyw()
{
    return this->przeplyw;
}

int SiecPrzeplywowa::bfs(int zrodlo, int ujscie, std::vector<int> &poprzednik)
{
    std::vector<std::vector<int>> adj = this->getMacierzSasiedztwa();
    std::vector<std::vector<int>> cap = this->getPrzeplyw();
    std::fill(poprzednik.begin(), poprzednik.end(), -1);
    poprzednik[zrodlo] = -2;
    std::queue<std::pair<int, int>> q;
    q.push({zrodlo, INF});

    while (!q.empty())
    {
        int aktualny = q.front().first;
        int przeplyw = q.front().second;
        q.pop();

        for (int next : adj[aktualny])
        {
            if (poprzednik[next] == -1 && cap[aktualny][next])
            {
                poprzednik[next] = aktualny;
                int nowyPrzeplyw = std::min(przeplyw, cap[aktualny][next]);
                if (next == ujscie)
                    return nowyPrzeplyw;
                q.push({next, nowyPrzeplyw});
            }
        }
    }

    return 0;
}

int SiecPrzeplywowa::maxPrzeplyw(int zrodlo, int ujscie){
    std::vector<int> poprzednik(this->getLiczbaWierzcholkow());
    int przeplyw = 0;
    int nowyPrzeplyw;

    while((nowyPrzeplyw = bfs(zrodlo, ujscie, poprzednik))){
        przeplyw += nowyPrzeplyw;
        int aktualny = ujscie;
        while(aktualny != zrodlo){
            int poprzedni = poprzednik[aktualny];
            this->przeplyw[poprzedni][aktualny] -= nowyPrzeplyw;
            this->przeplyw[aktualny][poprzedni] += nowyPrzeplyw;
            aktualny = poprzedni;
        }
    }
    return przeplyw;
}