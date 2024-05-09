#include <iostream>
#include "Graf.cpp"

using namespace std;



int main(){
    int iloscTragarzy;

    cout << "Podaj ilosc tragazy: "; cin >> iloscTragarzy; cout << endl;
    std::vector<int> tablicaTragarzy(iloscTragarzy);

    cout << "Nazwij ich (liczba calkowita): " << endl;
    for(int i = 0; i < iloscTragarzy; i++){
        cin >> tablicaTragarzy[i];
    }

    Graf G = Graf();
    for(int i = 0; i < iloscTragarzy; i++){
        G.dodajWierzcholek(tablicaTragarzy[i]);
    }





    return 0;
}
