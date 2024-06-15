/**
 * @file problem3.cpp
 * @brief Rozwiązanie problemu 3
 * 
 * Rozwiązanie problemu:
 * Ustalić jak najszybciej grafik pracy strażników i jak najmniejszą liczbę odsłuchań melodii dla każdego strażnika.
 * 
 * Rozwiązanie teoretyczne:
 * 1. Wczytaj liczbę punktów orientacyjnych i liczbę płaszczaków.
 * 2. Wczytaj jasność punktów orientacyjnych.
 * 3. Wczytaj co ile punktów płaszczak musi się zatrzymać.
 * 4. Dla każdego dnia:
 * 5.     Wybierz płaszczaka z kolejki.
 * 6.     Znajdź taki punkt startowy, przez który odslucha jak najmniej melodii.
 * 7.     Zapisz płaszczaka jako strażnika na dany dzień.
 * 8.     Oznacz płaszczaka jako odpoczywającego i dodaj go na koniec kolejki.
 * 9. Wyświetl grafik pracy strażników.
 * 
 * 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <string>
#include <climits>

#ifndef llu
    #define llu long long unsigned
#endif
#ifndef lli
    #define lli long long
#endif

/**
 * @brief Struktura Plaszczak
 * 
 * Struktura przechowująca informacje o plaszczaku
 * 
 * @param id - identyfikator plaszczaka
 * @param co_ile_zatrzyma_sie - co ile punktów plaszczak musi się zatrzymać
 * @param odpoczywa - czy plaszczak odpoczywa
 */
struct Plaszczak{
    lli id;
    lli co_ile_zatrzyma_sie = 0;
    bool odpoczywa = false;
};

bool operator<(const Plaszczak& a, const Plaszczak& b){
    return a.co_ile_zatrzyma_sie < b.co_ile_zatrzyma_sie;
}
bool operator>(const Plaszczak& a, const Plaszczak& b){
    return a.co_ile_zatrzyma_sie > b.co_ile_zatrzyma_sie;
}

/**
 * @brief Struktura PunktOrientacyjny
 * 
 * Struktura przechowująca informacje o punkcie orientacyjnym
 * 
 * @param id - identyfikator punktu orientacyjnego
 * @param jasnosc - jasnosc punktu orientacyjnego
 * @param nastepny - wskaznik na nastepny punkt orientacyjny
 */
struct PunktOrientacyjny{
    lli id;
    lli jasnosc;
    PunktOrientacyjny* nastepny;
};

struct GrafikInfo{
    bool poprawny = false;
    std::vector<std::string> grafik;
    llu suma_odsluchan = 0;
};


/**
 * @brief Funkcja inicjalizująca problem 3
 * 
 * Funkcja rozwiązująca problem 3, ustalająca jak najszybciej grafik pracy strażników i jak najmniejszą liczbę odsłuchań melodii dla każdego strażnika
 * Dane wejściowe:
 * 1. Liczba punktów orientacyjnych
 * 2. Liczba plaszczakow
 * 3. Jasność punktów orientacyjnych
 * 4. Co ile punktów plaszczak musi się zatrzymać
 * 
 * Dane wyjściowe:
 * 1. Grafik pracy strażników
 * 2. Suma odsłuchań melodii
 * 
 * @param liczba_punktow - liczba punktow orientacyjnych przez ktore przechodzi plot, uzyskana z problemu 1
 * 
 * @return GrafikInfo - struktura przechowująca informacje o rozwiązaniu problemu
 */
GrafikInfo problem3_init(llu liczba_punktow){
    GrafikInfo result;
    llu liczba_plaszczakow;
    if(liczba_punktow < 1){
        std::cout << "Podaj liczbe punktow orientacyjnych: ";
        std::cin >> liczba_punktow;
    }
    if(liczba_punktow < 3){
        std::cout << "Za malo punktow orientacyjnych aby stworzyc trase" << std::endl;
        return result;
    }
    std::cout << "Podaj liczbe plaszczakow: ";
    std::cin >> liczba_plaszczakow;

    if(liczba_plaszczakow < 1){
        std::cout << "Niepoprawna liczba plaszczakow" << std::endl;
        return result;
    }

    std::vector<PunktOrientacyjny> punkty(liczba_punktow);
    std::vector<Plaszczak> plaszczaki(liczba_plaszczakow);

    std::cout << "Podaj jasnosc punktow: " << std::endl;
    for(llu i = 0; i < liczba_punktow; i++){
        std::cout << "[" << i << "]: ";
        std::cin >> punkty[i].jasnosc;
        punkty[i].id = i;
        punkty[i].nastepny = &punkty[(i + 1) % liczba_punktow];
    }

    std::cout << "Podaj co ile punktow plaszczak musi sie zatrzymac aby dokladniej sie rozejrzec: " << std::endl;
    for(llu i = 0; i < liczba_plaszczakow; i++){
        std::cout << "[" << i << "]: ";
        std::cin >> plaszczaki[i].co_ile_zatrzyma_sie;
        plaszczaki[i].id = i;
    }

    std::queue<Plaszczak> kolejka_plaszczakow;
    std::sort(plaszczaki.begin(), plaszczaki.end(), std::greater<Plaszczak>()); /*TODO: czy sortowac po tym czy zaimplementowac energie z powrotem*/
    
    for (llu i = 0; i < liczba_plaszczakow; i++) {
        kolejka_plaszczakow.push(plaszczaki[i]);
    }

    for (llu dzien = 0; dzien < 7; dzien++) {
        // dla kazdego plaszczaka znajdz taki punkt startowy (za razem koncowy) przez ktory odslucha jak najmniej melodii
        Plaszczak* plaszczak = &kolejka_plaszczakow.front();
        kolejka_plaszczakow.pop();
        if (plaszczak->odpoczywa) {
            std::cout << "Niewystarczajaca liczba plaszczakow aby wypelnic grafik wraz z odpoczynkiem" << std::endl;
            break;
        }
        llu min_odsluchan = INT_MAX;
        lli id_wybranego_straznika = 0;
        PunktOrientacyjny* wybrany_punkt = nullptr;
        for (llu i = 0; i < liczba_punktow; i++) {
            PunktOrientacyjny* punkt_startowy = &punkty[i];
            PunktOrientacyjny* aktualny_punkt = punkt_startowy;
            llu liczba_odsluchan = 0;
            PunktOrientacyjny* poprzedni_punkt = punkt_startowy;
            lli krok = 0;

            do {
                if (krok == plaszczak->co_ile_zatrzyma_sie) {
                    if (poprzedni_punkt->jasnosc < aktualny_punkt->jasnosc) {
                        liczba_odsluchan++;
                    }
                    krok = 0;
                    poprzedni_punkt = aktualny_punkt;
                }
                aktualny_punkt = aktualny_punkt->nastepny;
                krok++;
            } while (aktualny_punkt != punkt_startowy);

            if (liczba_odsluchan < min_odsluchan) {
                min_odsluchan = liczba_odsluchan;
                id_wybranego_straznika = plaszczak->id;
                wybrany_punkt = punkt_startowy;
            }
        }
        std::cout << "Dzien " << dzien + 1 << ": Plaszczak " << id_wybranego_straznika << " zaczyna od punktu " << wybrany_punkt->id << " i odslucha " << min_odsluchan << " melodii" << std::endl;
        result.grafik.push_back("Dzien " + std::to_string(dzien + 1) + ": Plaszczak " + std::to_string(id_wybranego_straznika) + " zaczyna od punktu " + std::to_string(wybrany_punkt->id) + " i odslucha " + std::to_string(min_odsluchan) + " melodii");
        plaszczak->odpoczywa = true;
        result.suma_odsluchan += min_odsluchan;
        kolejka_plaszczakow.push(*plaszczak);
    }
    result.poprawny = true;

    return result;
}