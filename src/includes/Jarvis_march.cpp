#include <iostream>
using namespace std;

#define MAX 10000

struct Punkt{
    int x;
    int y;
};

int orientacja(Punkt a, Punkt b, Punkt c){
    int det = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if(det == 0){
        return 0; //liniowe
    }
    return (det > 0) ? 1 : 2; //1 jeśli pasuje i 2 jeśli nie pasuje
}

void stworzOtoczke(Punkt punkty[], int n){
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
    Punkt punkty[] = {{0, 3}, {2, 2}, {1,1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    cout << "Punkty: ";
    int n = sizeof(punkty) / sizeof(punkty[0]);
    if(n < 3){
        cout << "musza byc minimum 3 punkty!" << endl;
    }
    stworzOtoczke(punkty, n);
    return 0;
}
