#include "includes/Geometria.cpp"
#include <iostream>

int main(){
    Punkt2 punkty[] = {{0, 3}, {2, 2}, {1,1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    std::cout << "Punkty: ";
    int n = sizeof(punkty) / sizeof(punkty[0]);
    OtoczkaJarvis otoczka = OtoczkaJarvis();
    otoczka.stworzOtoczke(punkty, n);
    return 0;
}