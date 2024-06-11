/**
 * @file problem3.cpp
 * @brief Rozwiązanie problemu 3
 * 
 * Rozwiązanie problemu:
 * 
*/
/*
Płaszczaki uznały, że dla zwiększenia bezpieczeństwa raz dziennie dookoła płotu powinien przejść strażnik.
Punkty orientacyjne, przez które przebiega płot, są różnej jasności i zgodnie z ruchem wskazówek zegara wyznaczają trasę strażnika.
Punkt pierwszy trasy (po jednym okrążeniu) jest jednocześnie punktem końcowym dla strażnika.
Strażnikiem może zostać każdy płaszczak, który ma odpowiednią ilość energii.
Niestety ilość energii każdego płaszczaka jest losowej wielkości.
Płaszczak po wykonaniu pracy strażnika musi przez tydzień odpoczywać.
Heretyk, który zazwyczaj mąci, ponumerował płaszczaki.
W ramach oszczędności zaproponował, by każdego dnia strzegł Krainy jeden strażnik wybrany z kilku płaszczaków o kolejnych numerach,
i wystarczy, by to był ten, który z nich ma najwięcej energii.

Problem jednak polega na tym,
że strażnik po minięciu co najwyżej pewnej liczby punktów orientacyjnych musi zatrzymać się, by dokładniej rozejrzeć się dookoła.
Jednak zachowuje całą energię do pracy tylko wtedy, gdy poprzednim punktem zatrzymania był punkt jaśniejszy od tego,
w którym się aktualnie zatrzymuje (nie męczą mu się oczy).
W przeciwnym razie całą energię traci i wtedy musi w tym punkcie odpocząć i posłuchać melodii, by energię odzyskać.
Ponieważ niektóre płaszczaki planują urlopy, trzeba szybko ustalić kolejnych strażników na cały krainowy tydzień.
Dla każdego z nich trzeba też wybrać takie punkty zatrzymania się, by liczba odsłuchań melodii przez strażnika była jak najmniejsza,
bo słuchając jej strasznie się nudzą.
Heretyk, któremu zlecono rolę ustalenia kolejnych strażników, ma mało czasu i potrzebuje Twojej pomocy.


Problem. Ustalić jak najszybciej grafik pracy strażników i jak najmniejszą liczbę odsłuchań melodii dla każdego strażnika.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>

struct Plaszczak{
    int id;
    int co_ile_zatrzyma_sie = 0;
    bool odpoczywa = false;
};

bool operator<(const Plaszczak& a, const Plaszczak& b){
    return a.co_ile_zatrzyma_sie < b.co_ile_zatrzyma_sie;
}
bool operator>(const Plaszczak& a, const Plaszczak& b){
    return a.co_ile_zatrzyma_sie > b.co_ile_zatrzyma_sie;
}

struct PunktOrientacyjny{
    int id;
    int jasnosc;
    PunktOrientacyjny* nastepny;
};

int main(){
    int liczba_puntkow, liczba_plaszczakow;
    std::cout << "Podaj liczbe punktow orientacyjnych: ";
    std::cin >> liczba_puntkow;
    std::cout << "Podaj liczbe plaszczakow: ";
    std::cin >> liczba_plaszczakow;

    std::vector<PunktOrientacyjny> punkty(liczba_puntkow);
    std::vector<Plaszczak> plaszczaki(liczba_plaszczakow);

    std::cout << "Podaj jasnosc punktow: " << std::endl;
    for(int i = 0; i < liczba_puntkow; i++){
        std::cout << "[" << i << "]: ";
        std::cin >> punkty[i].jasnosc;
        punkty[i].id = i;
        punkty[i].nastepny = &punkty[(i + 1) % liczba_puntkow];
    }

    std::cout << "Podaj co ile punktow plaszczak musi sie zatrzymac aby dokladniej sie rozejrzec: " << std::endl;
    for(int i = 0; i < liczba_plaszczakow; i++){
        std::cout << "[" << i << "]: ";
        std::cin >> plaszczaki[i].co_ile_zatrzyma_sie;
        plaszczaki[i].id = i;
    }

    std::queue<Plaszczak> kolejka_plaszczakow;
    std::sort(plaszczaki.begin(), plaszczaki.end(), std::greater<Plaszczak>());
    for(int i = 0; i < liczba_plaszczakow; i++){
        kolejka_plaszczakow.push(plaszczaki[i]);
    }

    for(int dzien = 0; dzien < 7; dzien++){
        //dla kazdego plaszczaka znajdz taki punkt startowy (za razem koncowy) przez ktory odslucha jak najmniej melodii
        Plaszczak* plaszczak = &kolejka_plaszczakow.front();
        kolejka_plaszczakow.pop();
        if(plaszczak->odpoczywa){
            std::cout << "Niewystarczajaca liczba plaszczakow aby wypelnic grafik wraz z odpoczynkiem" << std::endl;
            break;
        }
        int min_odsluchan = 0;
        int id_wybranego_straznika = 0;
        PunktOrientacyjny* wybrany_punkt = nullptr;
        for(int i = 0; i < liczba_puntkow; i++){
            PunktOrientacyjny* punkt_startowy = &punkty[i];
            PunktOrientacyjny* aktualny_punkt = punkt_startowy->nastepny;
            int liczba_odsluchan = 0;
            int krok = 1;
            while(aktualny_punkt != punkt_startowy){
                if(krok == plaszczak->co_ile_zatrzyma_sie){
                    if(aktualny_punkt->jasnosc < aktualny_punkt->nastepny->jasnosc){
                        liczba_odsluchan++;
                    }
                    krok = 0;
                }
                aktualny_punkt = aktualny_punkt->nastepny;
                krok++;
            }
            if(i == 0 || liczba_odsluchan < min_odsluchan){
                min_odsluchan = liczba_odsluchan;
                id_wybranego_straznika = plaszczak->id;
                wybrany_punkt = punkt_startowy;
            }
        }
        std::cout << "Dzien " << dzien+1 << ": Plaszczak " << id_wybranego_straznika << " zaczyna od punktu " << wybrany_punkt->id << " i odslucha " << min_odsluchan << " melodii" << std::endl;
        plaszczak->odpoczywa = true;
        kolejka_plaszczakow.push(*plaszczak);
    }

    return 0;
}