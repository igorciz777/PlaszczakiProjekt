/**
 * @file Geometria.h
 * @brief Plik nagłówkowy dla implementacji struktur i algorytmów geometrycznych
 * 
*/
#include <iostream>
#include <vector>
#include <string>

struct Punkt2{
    double x;
    double y;
};

struct Punkt3{
    double x;
    double y;
    double z;
};

struct Macierz3x3{
    double a11, a12, a13;
    double a21, a22, a23;
    double a31, a32, a33;
    Macierz3x3();
    Macierz3x3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33);
    void setKolumna1(Punkt3 p);
    void setKolumna2(Punkt3 p);
    void setKolumna3(Punkt3 p);
    double wyznacznik();
};

class OtoczkaJarvis{
    public:
        OtoczkaJarvis();
        void stworzOtoczke(Punkt2 punkty[], int n);
    private:
        int orientacja(Punkt2 a, Punkt2 b, Punkt2 c);
        std::vector<int> nastPunkt;
        std::vector<Punkt2> punkty;
};