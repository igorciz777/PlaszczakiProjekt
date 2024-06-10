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

#define RANDOM 0


struct Plaszczak{
    int id;
    int energia;
};

int main(){
    int liczba_puntkow, liczba_plaszczakow;
    std::cout << "Podaj liczbe punktow orientacyjnych: ";
    std::cin >> liczba_puntkow;
    std::cout << "Podaj liczbe plaszczakow: ";
    std::cin >> liczba_plaszczakow;

    std::vector<int> jasnosc_punktow(liczba_puntkow);
    std::vector<Plaszczak> plaszczaki(liczba_plaszczakow);

    std::cout << "Podaj jasnosc punktow: " << std::endl;
    for(int i = 0; i < liczba_puntkow; i++){
        std::cout << "[" << i << "]: ";
        std::cin >> jasnosc_punktow[i];
    }
#if RANDOM
    for(int i = 0; i < liczba_plaszczakow; i++){
        plaszczaki[i].id = i;
        plaszczaki[i].energia = rand() % 100;
    }
#else
    std::cout << "Podaj energie plaszczakow: " << std::endl;
    for(int i = 0; i < liczba_plaszczakow; i++){
        std::cout << "[" << i << "]: ";
        std::cin >> plaszczaki[i].energia;
        plaszczaki[i].id = i;
    }
#endif

    sort(plaszczaki.rbegin(), plaszczaki.rend(), [](const Plaszczak &a, const Plaszczak &b) {
        return a.energia > b.energia;
    });

    std::vector<int> punkty_zatrzymania(liczba_plaszczakow);
    punkty_zatrzymania[0] = 0;

    std::deque<int> kolejka;
    kolejka.push_back(0);

    /*
    TODO: reszta problemu
    */


    
    return 0;   
}