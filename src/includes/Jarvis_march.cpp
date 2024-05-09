#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#define MAX 10000
using namespace std;

struct Tragarz{//#TODO zrobic tragarzy
    int wiek; // grupa wiekowa 18 - 30 lub 30+; do wspolpracy potrzeba tragarzy z tego samego przedzialu wiekowego;
    int rece; //jesli rece = 0 to rece z przodu, jesli 1 to rece z tylu; 
};

struct Punkt{
    int x;
    int y;
};

struct Krawedz{
    int cel;
    double przepustowosc;
    double przeplyw;
};

//funkcja obliczajaca odleglosc miedzy punktami, odleglosc ta bedzie stanowic przepustowowsc

int obliczOdleglosc(Punkt a, Punkt b){
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

// Funkcja do tworzenia grafu na podstawie podanych punktów
vector<vector<Krawedz>> stworzGraf(vector<Punkt> punkty, int n) {
    vector<vector<Krawedz>> graf(n); // Tworzymy wektor wektorów reprezentujących krawędzie

    // Iterujemy po wszystkich punktach
    for (int i = 0; i < n; ++i) {
        // Dla każdej pary punktów, sprawdzamy odległość między nimi
        // i tworzymy krawędź między nimi w grafie
        for (int j = 0; j < n; ++j) {
            if (i != j) { // Ignorujemy ten sam punkt
                double odleglosc = obliczOdleglosc(punkty[i], punkty[j]);
                // Dodajemy krawędź z punktu i do punktu j z odpowiednią pojemnością (przepustowością)
                Krawedz krawedz;
                krawedz.cel = j;
                krawedz.przepustowosc = odleglosc; // Pojemność krawędzi to odległość między punktami
                krawedz.przeplyw = 0; // Na początku przepływ jest zerowy
                graf[i].push_back(krawedz);
            }
        }
    }

    return graf;
}

long orientacja(Punkt a, Punkt b, Punkt c){
    long det = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if(det == 0){
        return 0; //liniowe
    }
    return (det > 0) ? 1 : 2; //1 jeśli pasuje i 2 jeśli nie pasuje
}

void stworzOtoczke(vector<Punkt> punkty, int n){

    //int nastPunkt[n];
    vector<int> nastPunkt(n);
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

    int a = l, b;
    do{
        //szukamy punktu b którego kąt(a, i, b) jest <180
        b = (a + 1) % n;
        for(int i = 0; i < n; i++){
            if(orientacja(punkty[a], punkty[i], punkty[b]) == 2){
                b = i;
            }
        }
        nastPunkt[a] = b;
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
    if(n < 3){
        cout << "musza byc minimum 3 punkty!" << endl;
        return 0;
    }

    //Punkt tablicaPunktow[n];
    //Jak dynamicznie przydzielamy tablice zmienna n to vectorem albo pointerem
    
    vector<Punkt> tablicaPunktow(n);
    // for(int i = 0; i < n; i++){
    //     cout << "Punkt " << i+1 << "x: ";
    //     cin >> tablicaPunktow[i].x;
    //     cout <<"Punkt " << i+1 << "y: ";
    //     cin >> tablicaPunktow[i].y;
    //     cout << endl;
    // }
    Punkt fabryka;
    for(int i = 0; i < n; i++){
        cin >> tablicaPunktow[i].x;
        cin >> tablicaPunktow[i].y;

        
    }
    fabryka.x = tablicaPunktow[0].x;
    fabryka.y = tablicaPunktow[0].y; //fabryka to pierwszy podany przez uzytkownika punkt

    
    

    stworzOtoczke(tablicaPunktow, n);
    vector<vector<Krawedz>> v = stworzGraf(tablicaPunktow, n);
    // Iteracja po wszystkich wierzchołkach grafu
    for(int i = 0; i < v.size(); i++){
        cout << "Krawedzie wychodzace z wierzcholka " << i << ":\n";

    // Iteracja po wszystkich krawędziach wychodzących z danego wierzchołka
        for(int j = 0; j < v[i].size(); j++) {
            cout << "Cel: " << v[i][j].cel << ", Przepustowosc: " << v[i][j].przepustowosc << ", Przeplyw: " << v[i][j].przeplyw << "\n";
        }
        cout << "\n";
    }



    return 0;
}
