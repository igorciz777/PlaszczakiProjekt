#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <map>
#include <cmath>
#include "SiecPrzeplywowa.cpp"
#define MAX 10000
using namespace std;



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

void stworzOtoczke(Punkt punkty[], int n, double &odleglosc){

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
    //wypisz wynik
    for(int i = 0; i < n; i++){
        if(nastPunkt[i] != -1){
            cout << "(" << punkty[i].x << ", " << punkty[i].y << ")\n";
        }
    }

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
    
    
    



    stworzOtoczke(tablicaPunktow, n, odleglosc);
    SiecPrzeplywowa siecBudowy = SiecPrzeplywowa(n);
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
        siecBudowy.dodajKrawedz(fabryka, cel, 8); //TODO przepustowosc na sztywno, to musi byc maks skojarzenie
    }
    cout << "ile punktow chcesz polaczyc z punktami na otoczce? ";
    int ilosc_polaczen_punkt_otoczka;
    cin >> ilosc_polaczen_punkt_otoczka;
    cout << endl;
    for(int i = 0; i < ilosc_polaczen_punkt_otoczka; i++){
        int zrodlo, cel;
        cout << "Jakie dwa punkty chcesz polaczyc (1 nie z otoczki, 2 z otoczki): ";
        cin >> zrodlo >> cel; cout << endl;
        siecBudowy.dodajKrawedz(nazwyPunktow[zrodlo], nazwyPunktow[cel], 8); //TODO przepustowosc na sztywno, to musi byc maks skojarzenie
    }


    cout<<"Dlugosc otoczki: "<<odleglosc<<endl;
    vector<vector<int>> sciez;
    int maksymalnyPrzeplyw = siecBudowy.edmondsKarp(fabryka, nazwyPunktow[5], sciez);
    cout << "Maksymalny przeplyw to: " << maksymalnyPrzeplyw << endl;
    
    int ilosc_dni_potrzebnych_do_budowy_plotu = 0;
    
    while(odleglosc > 0){
        odleglosc -= maksymalnyPrzeplyw;
        ilosc_dni_potrzebnych_do_budowy_plotu++;
    }
    
    cout << "Tragarze potrzebuja " << ilosc_dni_potrzebnych_do_budowy_plotu << " dni do zbudowania plotu." << endl;



    return 0;
}
