/**
 * @file Geometria.cpp
 * @brief Plik źródłowy dla implementacji struktur i algorytmów geometrycznych
 * 
*/

#include "Geometria.h"

Macierz3x3::Macierz3x3(){
    this->a11 = 0;
    this->a12 = 0;
    this->a13 = 0;
    this->a21 = 0;
    this->a22 = 0;
    this->a23 = 0;
    this->a31 = 0;
    this->a32 = 0;
    this->a33 = 0;
}

Macierz3x3::Macierz3x3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33){
    this->a11 = a11;
    this->a12 = a12;
    this->a13 = a13;
    this->a21 = a21;
    this->a22 = a22;
    this->a23 = a23;
    this->a31 = a31;
    this->a32 = a32;
    this->a33 = a33;
}

Macierz3x3::Macierz3x3(Punkt3 k1, Punkt3 k2, Punkt3 k3){
    this->a11 = k1.x;
    this->a21 = k1.y;
    this->a31 = k1.z;
    this->a12 = k2.x;
    this->a22 = k2.y;
    this->a32 = k2.z;
    this->a13 = k3.x;
    this->a23 = k3.y;
    this->a33 = k3.z;
}

void Macierz3x3::setKolumna1(Punkt3 p){
    this->a11 = p.x;
    this->a21 = p.y;
    this->a31 = p.z;
}

void Macierz3x3::setKolumna2(Punkt3 p){
    this->a12 = p.x;
    this->a22 = p.y;
    this->a32 = p.z;
}

void Macierz3x3::setKolumna3(Punkt3 p){
    this->a13 = p.x;
    this->a23 = p.y;
    this->a33 = p.z;
}

double Macierz3x3::wyznacznik(){
    return this->a11 * this->a22 * this->a33 + this->a12 * this->a23 * this->a31 + this->a13 * this->a21 * this->a32 - this->a13 * this->a22 * this->a31 - this->a12 * this->a21 * this->a33 - this->a11 * this->a23 * this->a32;
}

OtoczkaJarvis::OtoczkaJarvis(){
    this->nastPunkt = std::vector<int>();
    this->punkty = std::vector<Punkt2>();
}

int OtoczkaJarvis::orientacja(Punkt2 a, Punkt2 b, Punkt2 c){
    int det = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if(det == 0){
        return 0; //liniowe
    }
    return (det > 0) ? 1 : 2; //1 jeśli pasuje i 2 jeśli nie pasuje
}

void OtoczkaJarvis::stworzOtoczke(Punkt2 punkty[], int n){
    if(n < 3){
        std::cout << "musza byc minimum 3 punkty!" << std::endl;
    }

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
            std::cout << "(" << punkty[i].x << ", " << punkty[i].y << ")\n";
        }
    }
}



