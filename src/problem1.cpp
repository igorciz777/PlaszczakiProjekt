/**
 * @file problem1.cpp
 * @brief Rozwiązanie problemu 1
 *
 * Rozwiązanie problemu:
 * Zbudować płot dookoła krainy wykorzystująć punkty orientacyjne.
 * Dobranie tragrzy w taki sposób, aby ze sobą współpracowali.
 * Ustalenie par tragarzy oraz drogi do dostarczenia odstd::cinków w odpowiednie miejsce
 *
 * Rozwiązanie teoretyczne:
 * 1. Wczytaj punty orientacyjne.
 * 2. Na podstawie tych punktow zbuduj otoczkę.
 * 3. Zapytaj ilu jest tragarzy z rękoma z przodu i rękoma z tyłu.
 * 4. Zapytaj kto z kim się lubi i połącz tragarzy w pray tak aby było tych par najwięcej.
 * 5. Zapytaj który punkt spoza otoczki jest fabryką, a nastepnie połącz tą fabrykę z resztą punktów tak aby byla droga do otoczki.
 *
 * Użyte biblioteki:
 * @see SiecPrzeplywowa.cpp
 * @see DoborTragarzy.cpp
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <climits>
#include <algorithm>
#include "include/SiecPrzeplywowa.h"

#ifndef llu
#define llu long long unsigned
#endif
#ifndef lli
#define lli long long
#endif

struct PlotInfo
{
    bool poprawny = false;
    llu ilosc_odcinkow_plotu;
    double dlugosc_plotu;
    llu ilosc_tragarzy_z_przodu;
    llu ilosc_tragarzy_z_tylu;
    llu ilosc_par;
    llu maksymalny_przeplyw;
    llu dni_do_zbudowania;
};

const lli MAKS = 1000; // Maksymalna liczba pracowników w każdej grupie
std::vector<lli> skojarzeniaZPrzodu(MAKS, -1);
std::vector<lli> skojarzeniaZTylu(MAKS, -1);
std::vector<lli> odleglosc(MAKS + 1);
std::vector<std::vector<lli>> listaSasiedztwa(MAKS);

struct Punkt
{
    lli x;
    lli y;
};

double obliczOdleglosc(Punkt a, Punkt b)
{
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

long orientacja(Punkt a, Punkt b, Punkt c)
{
    long det = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (det == 0)
    {
        return 0; // liniowe
    }
    return (det > 0) ? 1 : 2; // 1 jeśli pasuje i 2 jeśli nie pasuje
}

void stworzOtoczke(Punkt punkty[], lli n, double &odleglosc, lli &wynik, std::vector<lli> &punktyOtoczki)
{

    std::vector<lli> nastPunkt(n);
    for (lli i = 0; i < n; i++)
    {
        nastPunkt[i] = -1;
    }

    // szukanie punktu na lewo
    lli l = 0;
    for (lli i = 1; i < n; i++)
    {
        if (punkty[i].x < punkty[l].x)
        {
            l = i;
        }
    }
    // zaczynamy od punktu najbardziej po lewej, zgodnie ze wskazówkami zegara aż dojdziemy do startowego

    lli a = l, b; // c=1;
    do
    {
        // szukamy punktu b którego kąt(a, i, b) jest <180
        b = (a + 1) % n;
        for (lli i = 0; i < n; i++)
        {
            lli o = orientacja(punkty[a], punkty[i], punkty[b]);
            if (o == 2 || (o == 0 && obliczOdleglosc(punkty[a], punkty[i]) > obliczOdleglosc(punkty[a], punkty[b])))
            {
                b = i;
            }
        }
        nastPunkt[a] = b;
        odleglosc += obliczOdleglosc(punkty[a], punkty[b]);
        a = b;

    } while (a != l);
    // wypisz wynik
    for (lli i = 0; i < n; i++)
    {
        if (nastPunkt[i] != -1)
        {
            std::cout << "(" << punkty[i].x << ", " << punkty[i].y << ")\n";
            wynik++;
            punktyOtoczki.push_back(i);
        }
    }
}

bool wyszukiwanieWszerz()
{
    std::queue<lli> kolejka;
    for (lli u = 0; u < MAKS; ++u)
    {
        if (skojarzeniaZPrzodu[u] == -1)
        {
            odleglosc[u] = 0;
            kolejka.push(u);
        }
        else
        {
            odleglosc[u] = INT_MAX;
        }
    }
    odleglosc[-1] = INT_MAX;
    while (!kolejka.empty())
    {
        lli u = kolejka.front();
        kolejka.pop();
        if (u != -1)
        {
            for (lli v : listaSasiedztwa[u])
            {
                if (odleglosc[skojarzeniaZTylu[v]] == INT_MAX)
                {
                    odleglosc[skojarzeniaZTylu[v]] = odleglosc[u] + 1;
                    kolejka.push(skojarzeniaZTylu[v]);
                }
            }
        }
    }
    return odleglosc[-1] != INT_MAX;
}

bool wyszukiwanieWGlab(lli u)
{
    if (u != -1)
    {
        for (lli v : listaSasiedztwa[u])
        {
            if (odleglosc[skojarzeniaZTylu[v]] == odleglosc[u] + 1)
            {
                if (wyszukiwanieWGlab(skojarzeniaZTylu[v]))
                {
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

lli algorytmHopcroftaKarpa()
{
    lli skojarzenia = 0;
    while (wyszukiwanieWszerz())
    {
        for (lli u = 0; u < MAKS; ++u)
        {
            if (skojarzeniaZPrzodu[u] == -1 && wyszukiwanieWGlab(u))
            {
                skojarzenia++;
            }
        }
    }
    return skojarzenia;
}

void czyPunktNalezyDoOtoczki(std::vector<lli> punktyOtoczki, lli p, bool &jestRozny)
{
    for (llu i = 0; i < punktyOtoczki.size(); ++i)
    {
        if (punktyOtoczki[i] == p)
        {
            jestRozny = false;
            break;
        }
        jestRozny = true;
    }
}

PlotInfo problem1_init()
{
    PlotInfo result;
    lli n;
    std::cout << "Okresl ile puntow orientacyjnych zawiera kraina : ";
    std::cin >> n;
    double odleglosc;
    if (n < 3)
    {
        std::cout << "musza byc minimum 3 punkty!" << std::endl;
        return result;
    }
    std::vector<Punkt> tablicaPunktow(n);
    std::map<lli, lli> nazwyPunktow;
    std::cout << "Podaj wspolrzedne punktow orientacyjnych (x i y oddzielone spacja): " << std::endl;
    for (lli i = 0; i < n; i++)
    {
        std::cin >> tablicaPunktow[i].x;
        std::cin >> tablicaPunktow[i].y;
        nazwyPunktow[i] = i;
    }

    for (lli i = 0; i < n; i++)
    {
        std::cout << "Punkt " << nazwyPunktow[i] << ": (" << tablicaPunktow[i].x << ", " << tablicaPunktow[i].y << ")" << std::endl;
    }

    lli superUjscie = n;
    n++;
    SiecPrzeplywowa siecBudowy = SiecPrzeplywowa(n);
    siecBudowy.dodajWierzcholek(n - 1);

    std::vector<lli> punktyOtoczki;
    lli wynik = 0;
    stworzOtoczke(tablicaPunktow.data(), n - 1, odleglosc, wynik, punktyOtoczki);
    while (wynik < 3)
    {
        std::cout << "Otoczka jest linia prosta. Podaj punkty ponownie." << std::endl;
        std::cout << "Okresl ile puntow orientacyjnych zawiera kraina : ";
        std::cin >> n;
        for (lli i = 0; i < n; i++)
        {
            std::cin >> tablicaPunktow[i].x;
            std::cin >> tablicaPunktow[i].y;
            nazwyPunktow[i] = i;
        }
    }
    lli liczbaPracownikowZPrzodu, liczbaPracownikowZTylu, liczbaPolaczen;
    std::cout << "Podaj liczbe pracownikow z rekoma z przodu: ";
    std::cin >> liczbaPracownikowZPrzodu;
    while (liczbaPracownikowZPrzodu <= 0)
    {
        std::cout << "Podales zle dane. Sprobuj ponownie: ";
        std::cin >> liczbaPracownikowZPrzodu;
    }
    std::cout << "Podaj liczbe pracownikow z rekoma z tylu: ";
    std::cin >> liczbaPracownikowZTylu;
    while (liczbaPracownikowZTylu <= 0)
    {
        std::cout << "Podales zle dane. Sprobuj ponownie: ";
        std::cin >> liczbaPracownikowZTylu;
    }
    std::cout << "Pracownicy z rekoma z przodu (indeksy 0 do " << liczbaPracownikowZPrzodu - 1 << "):" << std::endl;
    for (lli i = 0; i < liczbaPracownikowZPrzodu; i++)
    {
        std::cout << "Pracownik z przodu [" << i << "]" << std::endl;
    }

    std::cout << "Pracownicy z rekoma z tylu (indeksy 0 do " << liczbaPracownikowZTylu - 1 << "):" << std::endl;
    for (lli j = 0; j < liczbaPracownikowZTylu; j++)
    {
        std::cout << "Pracownik z tylu [" << j << "]" << std::endl;
    }

    std::cout << "Podaj liczbe polaczen miedzy pracownikami: ";
    std::cin >> liczbaPolaczen;
    while (liczbaPolaczen < 1)
    {
        std::cout << "Podales zle dane. Sprobuj ponownie: ";
        std::cin >> liczbaPolaczen;
    }

    for (lli i = 0; i < liczbaPolaczen; ++i)
    {
        lli zPrzodu, zTylu;
        std::cout << "Podaj pare pracownikow (z przodu i z tylu), ktorzy wspolpracuja: ";
        std::cin >> zPrzodu >> zTylu;
        while (zPrzodu < 0 || zPrzodu >= liczbaPracownikowZPrzodu || zTylu < 0 || zTylu >= liczbaPracownikowZTylu)
        {
            std::cout << "Podales zle dane. Sprobuj ponownie: ";
            std::cin >> zPrzodu >> zTylu;
        }
        listaSasiedztwa[zPrzodu].push_back(zTylu);
    }

    lli maksymalneSkojarzenie = algorytmHopcroftaKarpa();
    std::cout << "Maksymalne skojarzenie: " << algorytmHopcroftaKarpa() << std::endl;
    for (lli i = 0; i < n; i++)
    {
        siecBudowy.dodajWierzcholek(nazwyPunktow[i]);
    }
    std::cout << "Punkty na otoczce: ";
    for (llu i = 0; i < punktyOtoczki.size(); i++)
    {
        std::cout << nazwyPunktow[punktyOtoczki[i]] << " ";
    }
    std::cout << std::endl;
    llu fabryka, p, fabryka_punkt;
    std::cout << "Wybierz punkt (nie moze byc na otoczce) ktory jest fabryka: ";
    std::cin >> p;
    bool jestRozny = true;
    czyPunktNalezyDoOtoczki(punktyOtoczki, p, jestRozny);
    while (jestRozny == false)
    {
        std::cout << "Podales zle dane. Sprobuj ponownie: ";
        std::cin >> p;
        czyPunktNalezyDoOtoczki(punktyOtoczki, p, jestRozny);
    }
    fabryka = nazwyPunktow[p];
    std::cout << "Fabryka to punkt: " << fabryka << std::endl;
    std::cout << "Z iloma punktami (spoza otoczki) chcesz polaczyc fabryke? ";
    std::cin >> fabryka_punkt;
    while (fabryka_punkt < 1 || fabryka_punkt >= n - punktyOtoczki.size() - 1)
    {
        std::cout << "Podales zle dane. Sprobuj ponownie: ";
        std::cin >> fabryka_punkt;
    }
    std::vector<lli> punkty_polaczone_z_fabryka;
    for (llu i = 0; i < fabryka_punkt; i++)
    {
        lli cel;
        std::cout << i + 1 << "Punkt: ";
        std::cin >> cel;
        while (cel < 0 || cel >= n - 1)
        {
            std::cout << "Podales zle dane. Sprobuj ponownie: ";
            std::cin >> cel;
        }
        czyPunktNalezyDoOtoczki(punktyOtoczki, cel, jestRozny);
        while (jestRozny == false)
        {
            std::cout << "Podales zle dane. Sprobuj ponownie: ";
            std::cin >> cel;
            while (cel < 0 || cel >= n - 1)
            {
                std::cout << "Podales zle dane. Sprobuj ponownie: ";
                std::cin >> cel;
            }
            czyPunktNalezyDoOtoczki(punktyOtoczki, cel, jestRozny);
        }
        punkty_polaczone_z_fabryka.push_back(cel);
        siecBudowy.dodajKrawedz(fabryka, cel, maksymalneSkojarzenie);
    }
    std::cout << "Ile polaczen punktow spoza otoczki z wierzcholkami plotu? ";
    lli ilosc_polaczen_punkt_otoczka;
    std::cin >> ilosc_polaczen_punkt_otoczka;
    while (ilosc_polaczen_punkt_otoczka < 1)
    {
        std::cout << "Podales zle dane. Sprobuj ponownie: ";
        std::cin >> ilosc_polaczen_punkt_otoczka;
    }
    std::cout << std::endl;
    llu rozmiar = punktyOtoczki.size();
    // lli tab[rozmiar];
    std::vector<lli> tab(rozmiar);
    for (llu i = 0; i < rozmiar; i++)
    {
        tab[i] = 0;
    }
    for (lli i = 0; i < ilosc_polaczen_punkt_otoczka; i++)
    {
        lli zrodlo, cel;
        std::cout << "Jakie dwa punkty chcesz polaczyc (1 nie z otoczki(ktory jest polaczony z fabryka), 2 z otoczki): ";
        std::cin >> zrodlo >> cel;
        std::cout << std::endl;
        czyPunktNalezyDoOtoczki(punkty_polaczone_z_fabryka, zrodlo, jestRozny);
        while (jestRozny != false)
        {
            std::cout << "Punkt nie jest polaczony z fabryka. Sprobuj ponownie: ";
            std::cin >> zrodlo;
            czyPunktNalezyDoOtoczki(punkty_polaczone_z_fabryka, zrodlo, jestRozny);
        }
        czyPunktNalezyDoOtoczki(punktyOtoczki, zrodlo, jestRozny);
        while (jestRozny == false)
        {
            std::cout << "1 punkt nalezy do otoczki. Sprobuj ponownie: ";
            std::cin >> zrodlo;
            while (jestRozny != false)
            {
                std::cout << "Punkt nie jest polaczony z fabryka. Sprobuj ponownie: ";
                std::cin >> zrodlo;
                czyPunktNalezyDoOtoczki(punkty_polaczone_z_fabryka, zrodlo, jestRozny);
            }
            czyPunktNalezyDoOtoczki(punktyOtoczki, zrodlo, jestRozny);
        }
        czyPunktNalezyDoOtoczki(punktyOtoczki, cel, jestRozny);
        while (jestRozny != false)
        {
            std::cout << "2 punkt nie nalezy do otoczki. Sprobuj ponownie: ";
            std::cin >> cel;
            czyPunktNalezyDoOtoczki(punktyOtoczki, cel, jestRozny);
        }
        siecBudowy.dodajKrawedz(nazwyPunktow[zrodlo], nazwyPunktow[cel], maksymalneSkojarzenie);
        auto it = find(punktyOtoczki.begin(), punktyOtoczki.end(), cel);
        tab[distance(punktyOtoczki.begin(), it)]++;
    }
    while (std::any_of(tab.data(), tab.data() + rozmiar, [](lli i)
                  { return i == 0; }))
    {
        std::cout << "Ktorys punkt z otoczki nie ma polaczenia do fabryki. Musisz podac kolejne punkty ktore chcesz polaczyc." << std::endl;

        std::cout << "Ile polaczen punktow spoza otoczki z wierzcholkami plotu? ";
        std::cin >> ilosc_polaczen_punkt_otoczka;
        while (ilosc_polaczen_punkt_otoczka < 1)
        {
            std::cout << "Podales zle dane. Sprobuj ponownie: ";
            std::cin >> ilosc_polaczen_punkt_otoczka;
        }
        std::cout << std::endl;

        for (lli i = 0; i < ilosc_polaczen_punkt_otoczka; i++)
        {
            lli zrodlo, cel;
            std::cout << "Jakie dwa punkty chcesz polaczyc (1 nie z otoczki(ktory jest polaczony z fabryka), 2 z otoczki): ";
            std::cin >> zrodlo >> cel;
            std::cout << std::endl;
            czyPunktNalezyDoOtoczki(punkty_polaczone_z_fabryka, zrodlo, jestRozny);
            while (jestRozny != false)
            {
                std::cout << "Punkt nie jest polaczony z fabryka. Sprobuj ponownie: ";
                std::cin >> zrodlo;
                czyPunktNalezyDoOtoczki(punkty_polaczone_z_fabryka, zrodlo, jestRozny);
            }
            czyPunktNalezyDoOtoczki(punktyOtoczki, zrodlo, jestRozny);
            while (jestRozny == false)
            {
                std::cout << "1 punkt nalezy do otoczki. Sprobuj ponownie: ";
                std::cin >> zrodlo;
                while (jestRozny != false)
                {
                    std::cout << "Punkt nie jest polaczony z fabryka. Sprobuj ponownie: ";
                    std::cin >> zrodlo;
                    czyPunktNalezyDoOtoczki(punkty_polaczone_z_fabryka, zrodlo, jestRozny);
                }
                czyPunktNalezyDoOtoczki(punktyOtoczki, zrodlo, jestRozny);
            }
            czyPunktNalezyDoOtoczki(punktyOtoczki, cel, jestRozny);
            while (jestRozny != false)
            {
                std::cout << "2 punkt nie nalezy do otoczki. Sprobuj ponownie: ";
                std::cin >> cel;
                czyPunktNalezyDoOtoczki(punktyOtoczki, cel, jestRozny);
            }
            siecBudowy.dodajKrawedz(nazwyPunktow[zrodlo], nazwyPunktow[cel], maksymalneSkojarzenie);
            auto it = find(punktyOtoczki.begin(), punktyOtoczki.end(), cel);
            tab[distance(punktyOtoczki.begin(), it)]++;
        }
    }
    for (llu i = 0; i < punktyOtoczki.size(); i++)
    {
        siecBudowy.dodajKrawedz(nazwyPunktow[punktyOtoczki[i]], superUjscie, maksymalneSkojarzenie);
    }

    std::cout << "Dlugosc otoczki: " << odleglosc << std::endl;
    result.dlugosc_plotu = odleglosc;
    std::vector<std::vector<lli>> sciez;
    lli maksymalnyPrzeplyw = siecBudowy.edmondsKarp(fabryka, superUjscie, sciez);
    std::cout << "Maksymalny przeplyw to: " << maksymalnyPrzeplyw << std::endl;

    lli ilosc_dni_potrzebnych_do_budowy_plotu = 0;

    while (odleglosc > 0)
    {
        odleglosc -= maksymalnyPrzeplyw;
        ilosc_dni_potrzebnych_do_budowy_plotu++;
    }

    std::cout << "Tragarze potrzebuja " << ilosc_dni_potrzebnych_do_budowy_plotu << " dni do zbudowania plotu." << std::endl;

    result.poprawny = true;
    result.ilosc_odcinkow_plotu = punktyOtoczki.size();
    result.ilosc_tragarzy_z_przodu = liczbaPracownikowZPrzodu;
    result.ilosc_tragarzy_z_tylu = liczbaPracownikowZTylu;
    result.ilosc_par = maksymalneSkojarzenie;
    result.maksymalny_przeplyw = maksymalnyPrzeplyw;
    result.dni_do_zbudowania = ilosc_dni_potrzebnych_do_budowy_plotu;

    return result;
}