#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <map>
#include <cmath>
#include <climits>
#include <cstring>
#include "SiecPrzeplywowa.cpp"
#include "DoborTragarzy.cpp"
#define MAX 10000
using namespace std;
const int MAKS = 1000;  // Maksymalna liczba pracowników w każdej grupie
int skojarzeniaZPrzodu[MAKS], skojarzeniaZTylu[MAKS], odleglosc[MAKS];
vector<int> listaSasiedztwa[MAKS];


struct Punkt{
    int x;
    int y;
};

double obliczOdleglosc(Punkt a, Punkt b){
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

long orientacja(Punkt a, Punkt b, Punkt c){
    long det = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if(det == 0){
        return 0; //liniowe
    }
    return (det > 0) ? 1 : 2; //1 jeśli pasuje i 2 jeśli nie pasuje
}

void stworzOtoczke(Punkt punkty[], int n, double &odleglosc, vector<int> &indeksy_otoczki){

    int nastPunkt[n];
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
	
    int a = l, b, c = 1;
    do{
        //szukamy punktu b którego kąt(a, i, b) jest <180
        b = (a + 1) % n;
        for(int i = 0; i < n; i++){
            if(orientacja(punkty[a], punkty[i], punkty[b]) == 2){
                b = i;
            }
        }
        nastPunkt[a] = b;
        odleglosc += obliczOdleglosc(punkty[a], punkty[b]);
        a = b;
		
    }while(a != l);
    cout<<endl;
    //wypisz wynik
    for(int i = 0; i < n; i++){
        if(nastPunkt[i] != -1){
            cout << "(" << punkty[i].x << ", " << punkty[i].y << ")\n";
            indeksy_otoczki.push_back(i);
        }
    }
    

}

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


int main()
{
    
    int n;
    cout << "Okresl ile puntow orientacyjnych zawiera kraina : ";
    cin >> n;
    double odleglosc;
    if(n < 3){
        cout << "musza byc minimum 3 punkty!" << endl;
        return 0;
    }
    Punkt tablicaPunktow[n];
    vector<Punkt> punkty(n);
    map<int, int> nazwyPunktow;
    for(int i = 0; i < n; i++){
        cin >> tablicaPunktow[i].x;
        cin >> tablicaPunktow[i].y;
        nazwyPunktow[i] =  i;
    }

    for (int i = 0; i < n; i++) {
        cout << "Punkt " << nazwyPunktow[i] << ": (" << tablicaPunktow[i].x << ", " << tablicaPunktow[i].y << ")" << endl;
    }
    
	int superZrodlo = n;
   	n++;
   	SiecPrzeplywowa siecBudowy = SiecPrzeplywowa(n);
	siecBudowy.dodajWierzcholek(n-1);
	vector<int> indeksy_otoczki;
    stworzOtoczke(tablicaPunktow, n-1, odleglosc, indeksy_otoczki);
    
    
    
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

    int maksymalneSkojarzenie = algorytmHopcroftaKarpa();
    cout << "Maksymalne skojarzenie: " << algorytmHopcroftaKarpa() << endl;

    
    for(int i = 0; i < n; i++){
        siecBudowy.dodajWierzcholek(nazwyPunktow[i]);
    }
    int fabryka, p, fabryka_punkt;
    cout << "Wybierz punkt (nie moze byc na otoczce) ktory jest fabryka: ";
    cin >> p;
    fabryka = nazwyPunktow[p];
    cout << "fabryka to punkt: " << fabryka << endl;
    cout << "z iloma punktami (spoza otoczki) chcesz polaczyc fabryke? ";
    cin >> fabryka_punkt;
    for(int i = 0; i < fabryka_punkt; i++){
        int cel;
        cout << i + 1 << "Punkt: ";
        cin >> cel;
        siecBudowy.dodajKrawedz(fabryka, cel, maksymalneSkojarzenie); 
    }
    cout << "ile punktow chcesz polaczyc z punktami na otoczce? ";
    int ilosc_polaczen_punkt_otoczka;
    cin >> ilosc_polaczen_punkt_otoczka;
    cout << endl;
    
    for(int i = 0; i < ilosc_polaczen_punkt_otoczka; i++){
        int zrodlo, cel;
        cout << "Jakie dwa punkty chcesz polaczyc (1 nie z otoczki, 2 z otoczki): ";
        cin >> zrodlo >> cel; cout << endl;
        siecBudowy.dodajKrawedz(nazwyPunktow[zrodlo], nazwyPunktow[cel], 8); 
    }
    for(int i = 0; i < indeksy_otoczki.size(); i++){
    	siecBudowy.dodajKrawedz(nazwyPunktow[indeksy_otoczki[i]], superZrodlo, 8); 
	}


    cout<<"Dlugosc otoczki: "<<odleglosc<<endl;
    vector<vector<int>> sciez;
    int maksymalnyPrzeplyw = siecBudowy.edmondsKarp(fabryka, superZrodlo, sciez);
    cout << "Maksymalny przeplyw to: " << maksymalnyPrzeplyw << endl;
    
    int ilosc_dni_potrzebnych_do_budowy_plotu = 0;
    
    while(odleglosc > 0){
        odleglosc -= maksymalnyPrzeplyw;
        ilosc_dni_potrzebnych_do_budowy_plotu++;
    }
    
    cout << "Tragarze potrzebuja " << ilosc_dni_potrzebnych_do_budowy_plotu << " dni do zbudowania plotu." << endl;



    return 0;
}
