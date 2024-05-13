#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#define MAX 10000
using namespace std;



struct Punkt{
    int x;
    int y;
};

struct Krawedz{
    int cel;
    double przepustowosc;
    double przeplyw;
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
    //ostateczna dlugosc otoczki
	odleglosc += obliczOdleglosc(punkty[c], punkty[a]);
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
    
    for(int i = 0; i < n; i++){
        cin >> tablicaPunktow[i].x;
        cin >> tablicaPunktow[i].y;
    }
    
    
    

    stworzOtoczke(tablicaPunktow, n, odleglosc);
    cout<<"Dlugosc otoczki: "<<odleglosc<<endl;
    
    return 0;
}
