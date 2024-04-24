#include <iostream>
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

long orientacja(Punkt a, Punkt b, Punkt c){
    long det = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
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
    int n;
    cout << "Okresl ile puntow orientacyjnych zawiera kraina : ";
    cin >> n;
    if(n < 3){
        cout << "musza byc minimum 3 punkty!" << endl;
        return 0;
    }
    Punkt tablicaPunktow[n];
    for(int i = 0; i < n; i++){
        cout << "Punkt " << i+1 << "x: ";
        cin >> tablicaPunktow[i].x;
        cout <<"Punkt " << i+1 << "y: ";
        cin >> tablicaPunktow[i].y;
        cout << endl;
    }
    

    stworzOtoczke(tablicaPunktow, n);



    return 0;
}
