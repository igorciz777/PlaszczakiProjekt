/**
 * @file problem1.cpp
 * @brief Rozwiązanie problemu 1
 * 
 * Rozwiązanie problemu:
 * Zbudować płot dookoła krainy wykorzystująć punkty orientacyjne.
 * Dobranie tragrzy w taki sposób, aby ze sobą współpracowali.
 * Ustalenie par tragarzy oraz drogi do dostarczenia odcinków w odpowiednie miejsce
 * 
 * Rozwiązanie teoretyczne:
 * 1. Wczytaj punty orientacyjne.
 * 2. Na podstawie tych punktow zbuduj otoczkę.
 * 3. Zapytaj ilu jest tragarzy z rękoma z przodu i rękoma z tyłu.
 * 4. Zapytaj kto z kim się lubi i połącz tragarzy w pray tak aby było tych par najwięcej.
 * 5. Zapytaj który punkt spoza otoczki jest fabryką, a nastepnie połącz tą fabrykę z resztą punktów tak aby byla droga do otoczki.
 * 
 * @see SiecPrzeplywowa.h
*/

#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <map>
#include <climits>
#include <cstring>
#include <algorithm>
#include <queue>
#include "include/SiecPrzeplywowa.h"

#ifndef llu
    #define llu long long unsigned
#endif
#ifndef lli
    #define lli long long
#endif

struct PlotInfo{
    bool poprawny = false;
    llu ilosc_odcinkow_plotu;
    double dlugosc_plotu;
    llu ilosc_tragarzy_z_przodu;
    llu ilosc_tragarzy_z_tylu;
    llu ilosc_par;
    llu maksymalny_przeplyw;
    llu dni_do_zbudowania;
};

#define MAX 10000
using namespace std;
const int MAKS = 10000;  // Maksymalna liczba pracowników w każdej grupie
int skojarzeniaZPrzodu[MAKS], skojarzeniaZTylu[MAKS], odleglosc[MAKS];
vector<int> listaSasiedztwa[MAKS];

/**
 * @brief Struktura Punkt
 * 
 * Struktura przechowująca informacje o punkcie
 * 
 * @param x - współrzędna x
 * @param y - współrzędna y
 */

struct Punkt{
    int x;
    int y;
};

/**
 * @brief Obliczanie odległości
 * 
 * Funkcja oblicza odległość między dwoma punktami
 * 
 * @param a - punkt a
 * @param b - punkt b
 * @return double - odległość
 */

double obliczOdleglosc(Punkt a, Punkt b){
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

/**
 * @brief Orientacja
 * 
 * Funkcja sprawdza orientacje punktow
 * 
 * @param a - punkt a
 * @param b - punkt b
 * @param c - punkt c
 * @return long - 0 jeśli liniowe, 1 jeśli pasuje, 2 jeśli nie pasuje
 */

long orientacja(Punkt a, Punkt b, Punkt c){
    long det = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if(det == 0){
        return 0; //liniowe
    }
    return (det > 0) ? 1 : 2; //1 jeśli pasuje i 2 jeśli nie pasuje
}

/**
 * @brief Stworzenie otoczki
 * 
 * Funkcja tworzy otoczke na podstawie punktow orientacyjnych za pomoca algorytmu Jarvisa
 * 
 * @param punkty - punkty orientacyjne
 * @param n - ilosc punktow
 * @param dlugosc_plotu - dlugosc plotu
 * @param wynik - wynik
 * @param punktyOtoczki - punkty otoczki
 */

void stworzOtoczke(Punkt punkty[], int n, double &dlugosc_plotu, int &wynik, vector<int> &punktyOtoczki){


    std::vector<int> nastPunkt(n);
    for(int i = 0; i < n; i++){
        nastPunkt[i] = -1;
    }

    //szukanie punktu na lewo
    int l = 0;
    for(int i = 1; i < n; i++){
        if(punkty[i].x < punkty[l].x){
            l = i;
        }
    }
    //zaczynamy od punktu najbardziej po lewej, zgodnie ze wskazówkami zegara aż dojdziemy do startowego
	
    int a = l, b;//, c = 1;
    do{
        //szukamy punktu b którego kąt(a, i, b) jest <180
        b = (a + 1) % n;
        for(int i = 0; i < n; i++){
            int o = orientacja(punkty[a], punkty[i], punkty[b]);
            if (o == 2 || (o == 0 && obliczOdleglosc(punkty[a], punkty[i]) > obliczOdleglosc(punkty[a], punkty[b]))) {
                b = i;
            }
        }
        nastPunkt[a] = b;
        dlugosc_plotu += obliczOdleglosc(punkty[a], punkty[b]);
        a = b;
		
    }while(a != l);
    //wypisz wynik
    for(int i = 0; i < n; i++){
        if(nastPunkt[i] != -1){
            cout << "(" << punkty[i].x << ", " << punkty[i].y << ")\n";
            wynik++;
            punktyOtoczki.push_back(i);
        }
    }

}

/**
 * @brief Wyszukiwanie w szerz
 * 
 * Funkcja przeszukuje graf w szerz
 * 
 * @return true - jeśli znaleziono
 * @return false - jeśli nie znaleziono
 */

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

/**
 * @brief Wyszukiwanie w głąb
 * 
 * Funkcja przeszukuje graf w głąb
 * 
 * @param u - wierzchołek
 * @return true - jeśli znaleziono
 * @return false - jeśli nie znaleziono
 */
bool wyszukiwanieWGlab( int u ) {
    if (u != -1) {
        for (int v : listaSasiedztwa[u]) {
            if (odleglosc[skojarzeniaZTylu[v]] == odleglosc[u] + 1) {
                if (wyszukiwanieWGlab(skojarzeniaZTylu[v])) {
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

/**
 * @brief Algorytm Hopcrofta-Karpa
 * 
 * Algorytm znajduje maksymalne skojarzenie w grafie dwudzielnym.
 * 
 * @return int - maksymalne skojarzenie
 */
int algorytmHopcroftaKarpa() {
    memset(skojarzeniaZPrzodu, -1, sizeof(skojarzeniaZPrzodu));
    memset(skojarzeniaZTylu, -1, sizeof(skojarzeniaZTylu));
    int skojarzenia = 0;
    while (wyszukiwanieWszerz()) {
        for (int u = 0; u < MAKS; ++u) {
            if (skojarzeniaZPrzodu[u] == -1 && wyszukiwanieWGlab(u)) {
                skojarzenia++;
            }
        }
    }
    return skojarzenia;
}

/**
 * @brief Sprawdza czy punkt należy do otoczki
 * 
 * Funkcja sprawdza czy punkt należy do otoczki
 * 
 * @param punktyOtoczki - punkty otoczki
 * @param p - punkt
 * @param jestRozny - zmienna pomocnicza
 */
void czyPunktNalezyDoOtoczki(vector <int> punktyOtoczki, int p, bool &jestRozny){
	for (llu i = 0; i < punktyOtoczki.size(); ++i) {
        if (punktyOtoczki[i] == p) {
            jestRozny = false;
            break;
        }
        jestRozny = true;
    }
}

/**
 * @brief Inicjalizacja problemu 1
 * 
 * Funkcja rozwiązująca problem 1, zwracająca informacje o budowie plotu
 * 
 * @return PlotInfo - struktura z informacjami o budowie plotu
 */

PlotInfo problem1_init()
{
    PlotInfo result;
    int n;
    cout << "Okresl ile puntow orientacyjnych zawiera kraina : ";
    cin >> n;
    double dlugosc_plotu;
    if(n < 3){
        cout << "musza byc minimum 3 punkty!" << endl;
        return result;
    }
    vector<Punkt> tablicaPunktow(n);
    map<int, int> nazwyPunktow;
    for(int i = 0; i < n; i++){
        cin >> tablicaPunktow[i].x;
        cin >> tablicaPunktow[i].y;
        nazwyPunktow[i] =  i;
    }

    for (int i = 0; i < n; i++) {
        cout << "Punkt " << nazwyPunktow[i] << ": (" << tablicaPunktow[i].x << ", " << tablicaPunktow[i].y << ")" << endl;
    }
    
    int superUjscie = n;
    n++;
    SiecPrzeplywowa siecBudowy = SiecPrzeplywowa(n);
    siecBudowy.dodajWierzcholek(n-1);
   
	vector<int> punktyOtoczki;
	int wynik = 0;
    stworzOtoczke(tablicaPunktow.data(), n-1, dlugosc_plotu, wynik, punktyOtoczki);
    while(wynik < 3){
    	cout<<"Otoczka jest linia prosta. Podaj punkty ponownie."<<endl;
    	cout << "Okresl ile puntow orientacyjnych zawiera kraina : ";
    	cin >> n;
    	for(int i = 0; i < n; i++){
        	cin >> tablicaPunktow[i].x;
        	cin >> tablicaPunktow[i].y;
        	nazwyPunktow[i] =  i;
    	}
	}
    int liczbaPracownikowZPrzodu, liczbaPracownikowZTylu, liczbaPolaczen;
    cout << "Podaj liczbe pracownikow z rekoma z przodu: ";
    cin >> liczbaPracownikowZPrzodu;
    while(liczbaPracownikowZPrzodu <= 0){
    	cout<<"Podales zle dane. Sprobuj ponownie: ";
    	cin >> liczbaPracownikowZPrzodu;
	}
    cout << "Podaj liczbe pracownikow z rekoma z tylu: ";
    cin >> liczbaPracownikowZTylu;
	while(liczbaPracownikowZTylu <= 0){
    	cout<<"Podales zle dane. Sprobuj ponownie: ";
    	cin >> liczbaPracownikowZTylu;
	}
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
    while(liczbaPolaczen<1){
    	cout<<"Podales zle dane. Sprobuj ponownie: ";
    	cin >> liczbaPolaczen;
	}

    for (int i = 0; i < liczbaPolaczen; ++i) {
        int zPrzodu, zTylu;
        cout << "Podaj pare pracownikow (z przodu i z tylu), ktorzy wspolpracuja: ";
        cin >> zPrzodu >> zTylu;
        while(zPrzodu < 0 || zPrzodu >= liczbaPracownikowZPrzodu || zTylu < 0 || zTylu >= liczbaPracownikowZTylu){
        	cout<<"Podales zle dane. Sprobuj ponownie: ";
        	cin >> zPrzodu >> zTylu;
		}
        listaSasiedztwa[zPrzodu].push_back(zTylu);
    }

    int maksymalneSkojarzenie = algorytmHopcroftaKarpa();
    cout << "Maksymalne skojarzenie: " << algorytmHopcroftaKarpa() << endl;
    for(int i = 0; i < n; i++){
        siecBudowy.dodajWierzcholek(nazwyPunktow[i]);
    }
    llu fabryka, p, fabryka_punkt;
    cout << "Wybierz punkt (nie moze byc na otoczce) ktory jest fabryka: ";
    cin >> p;
    bool jestRozny = true;
    czyPunktNalezyDoOtoczki(punktyOtoczki, p, jestRozny);
    while (jestRozny == false) {
        cout <<"Podales zle dane. Sprobuj ponownie: ";
        cin >> p;
        czyPunktNalezyDoOtoczki(punktyOtoczki, p, jestRozny);
    }
    fabryka = nazwyPunktow[p];
    cout << "Fabryka to punkt: " << fabryka << endl;
    cout << "Z iloma punktami (spoza otoczki) chcesz polaczyc fabryke? ";
    cin >> fabryka_punkt;
    while(fabryka_punkt < 1 || fabryka_punkt >= n - punktyOtoczki.size() - 1){
    	cout<<"Podales zle dane. Sprobuj ponownie: ";
    	cin >> fabryka_punkt;
	}
	vector<int> punkty_polaczone_z_fabryka;
    for(llu i = 0; i < fabryka_punkt; i++){
        int cel;
        cout << i + 1 << "Punkt: ";
        cin >> cel;
        while(cel < 0 || cel >= n-1){
    		cout <<"Podales zle dane. Sprobuj ponownie: ";
    		cin >> cel;
		}
        czyPunktNalezyDoOtoczki(punktyOtoczki, cel, jestRozny);
        while (jestRozny == false) {
        	cout <<"Podales zle dane. Sprobuj ponownie: ";
        	cin >> cel;
        	while(cel < 0 || cel >= n-1){
    			cout <<"Podales zle dane. Sprobuj ponownie: ";
    			cin >> cel;
			}
        	czyPunktNalezyDoOtoczki(punktyOtoczki, cel, jestRozny);
    	}
    	punkty_polaczone_z_fabryka.push_back(cel);
        siecBudowy.dodajKrawedz(fabryka, cel, maksymalneSkojarzenie); 
    }
    cout << "Ile polaczen punktow spoza otoczki z wierzcholkami plotu? ";
    int ilosc_polaczen_punkt_otoczka;
    cin >> ilosc_polaczen_punkt_otoczka;
    while(ilosc_polaczen_punkt_otoczka<1){
    	cout <<"Podales zle dane. Sprobuj ponownie: ";
        cin >> ilosc_polaczen_punkt_otoczka;
	}
    cout << endl;
    int rozmiar = punktyOtoczki.size();
    //int tab[rozmiar];
    vector<int> tab(rozmiar);
    for(int i=0; i<rozmiar;i++){
    	tab[i]=0;
	}
    for(int i = 0; i < ilosc_polaczen_punkt_otoczka; i++){
        int zrodlo, cel;
        cout << "Jakie dwa punkty chcesz polaczyc (1 nie z otoczki(ktory jest polaczony z fabryka), 2 z otoczki): ";
        cin >> zrodlo >> cel; cout << endl;
        czyPunktNalezyDoOtoczki(punkty_polaczone_z_fabryka, zrodlo, jestRozny);
        while(jestRozny != false){
        	cout <<"Punkt nie jest polaczony z fabryka. Sprobuj ponownie: ";
        	cin >> zrodlo;
        	czyPunktNalezyDoOtoczki(punkty_polaczone_z_fabryka, zrodlo, jestRozny);
		}
        czyPunktNalezyDoOtoczki(punktyOtoczki, zrodlo, jestRozny);
        while (jestRozny == false) {
        	cout <<"1 punkt nalezy do otoczki. Sprobuj ponownie: ";
        	cin >> zrodlo;
        	while(jestRozny != false){
        		cout <<"Punkt nie jest polaczony z fabryka. Sprobuj ponownie: ";
        		cin >> zrodlo;
        		czyPunktNalezyDoOtoczki(punkty_polaczone_z_fabryka, zrodlo, jestRozny);
			}
        	czyPunktNalezyDoOtoczki(punktyOtoczki, zrodlo, jestRozny);
    	}
    	czyPunktNalezyDoOtoczki(punktyOtoczki, cel, jestRozny);
    	while (jestRozny != false) {
        	cout <<"2 punkt nie nalezy do otoczki. Sprobuj ponownie: ";
        	cin >> cel;
        	czyPunktNalezyDoOtoczki(punktyOtoczki, cel, jestRozny);
    	}
        siecBudowy.dodajKrawedz(nazwyPunktow[zrodlo], nazwyPunktow[cel], maksymalneSkojarzenie);
        auto it = find(punktyOtoczki.begin(), punktyOtoczki.end(), cel);
        tab[distance(punktyOtoczki.begin(), it)]++;
    }
    while (any_of(tab.data(), tab.data() + rozmiar, [](int i) { return i == 0; })) {
        cout << "Ktorys punkt z otoczki nie ma polaczenia do fabryki. Musisz podac kolejne punkty ktore chcesz polaczyc." <<endl;
        
        cout << "Ile polaczen punktow spoza otoczki z wierzcholkami plotu? ";
    	cin >> ilosc_polaczen_punkt_otoczka;
    	while(ilosc_polaczen_punkt_otoczka<1){
    		cout <<"Podales zle dane. Sprobuj ponownie: ";
        	cin >> ilosc_polaczen_punkt_otoczka;
		}
    	cout << endl;
		
		for(int i = 0; i < ilosc_polaczen_punkt_otoczka; i++){
        	int zrodlo, cel;
        	cout << "Jakie dwa punkty chcesz polaczyc (1 nie z otoczki(ktory jest polaczony z fabryka), 2 z otoczki): ";
        	cin >> zrodlo >> cel; cout << endl;
        	czyPunktNalezyDoOtoczki(punkty_polaczone_z_fabryka, zrodlo, jestRozny);
        	while(jestRozny != false){
        		cout <<"Punkt nie jest polaczony z fabryka. Sprobuj ponownie: ";
        		cin >> zrodlo;
        		czyPunktNalezyDoOtoczki(punkty_polaczone_z_fabryka, zrodlo, jestRozny);
			}
        	czyPunktNalezyDoOtoczki(punktyOtoczki, zrodlo, jestRozny);
        	while (jestRozny == false) {
        		cout <<"1 punkt nalezy do otoczki. Sprobuj ponownie: ";
        		cin >> zrodlo;
        		while(jestRozny != false){
        			cout <<"Punkt nie jest polaczony z fabryka. Sprobuj ponownie: ";
        			cin >> zrodlo;
        			czyPunktNalezyDoOtoczki(punkty_polaczone_z_fabryka, zrodlo, jestRozny);
				}	
        		czyPunktNalezyDoOtoczki(punktyOtoczki, zrodlo, jestRozny);
    		}
    		czyPunktNalezyDoOtoczki(punktyOtoczki, cel, jestRozny);
    		while (jestRozny != false) {
        		cout <<"2 punkt nie nalezy do otoczki. Sprobuj ponownie: ";
        		cin >> cel;
        		czyPunktNalezyDoOtoczki(punktyOtoczki, cel, jestRozny);
    		}
        	siecBudowy.dodajKrawedz(nazwyPunktow[zrodlo], nazwyPunktow[cel], maksymalneSkojarzenie);
        	auto it = find(punktyOtoczki.begin(), punktyOtoczki.end(), cel);
        	tab[distance(punktyOtoczki.begin(), it)]++;
    	}
    }
    for(llu i = 0; i < punktyOtoczki.size(); i++){
    	siecBudowy.dodajKrawedz(nazwyPunktow[punktyOtoczki[i]], superUjscie, maksymalneSkojarzenie); 
	}


    cout<<"Dlugosc otoczki: "<<dlugosc_plotu<<endl;
    result.dlugosc_plotu = dlugosc_plotu;
    vector<vector<lli>> sciez;
    int maksymalnyPrzeplyw = siecBudowy.edmondsKarp(fabryka, superUjscie, sciez);
    cout << "Maksymalny przeplyw to: " << maksymalnyPrzeplyw << endl;
    
    int ilosc_dni_potrzebnych_do_budowy_plotu = 0;
    
    while(dlugosc_plotu > 0){
        dlugosc_plotu -= maksymalnyPrzeplyw;
        ilosc_dni_potrzebnych_do_budowy_plotu++;
    }
    
    cout << "Tragarze potrzebuja " << ilosc_dni_potrzebnych_do_budowy_plotu << " dni do zbudowania plotu." << endl;

    result.poprawny = true;
    result.ilosc_odcinkow_plotu = punktyOtoczki.size();
    result.ilosc_tragarzy_z_przodu = liczbaPracownikowZPrzodu;
    result.ilosc_tragarzy_z_tylu = liczbaPracownikowZTylu;
    result.ilosc_par = maksymalneSkojarzenie;
    result.maksymalny_przeplyw = maksymalnyPrzeplyw;
    result.dni_do_zbudowania = ilosc_dni_potrzebnych_do_budowy_plotu;

    
    for(int i = 0; i < MAKS; i++){
        skojarzeniaZPrzodu[i] = -1;
        skojarzeniaZTylu[i] = -1;
        odleglosc[i] = 0;
        listaSasiedztwa[i].clear();
    }

    return result;
}