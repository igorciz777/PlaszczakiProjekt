#include <iostream>
#include "Graf.cpp"

using namespace std;



int main(){
    int iloscTragarzy;

    cout << "Podaj ilosc tragazy: "; cin >> iloscTragarzy; cout << endl;
    std::vector<int> tablicaTragarzy(iloscTragarzy);
    SiecPrzeplywowa siec = SiecPrzeplywowa(iloscTragarzy);


    for(int i = 0; i < iloscTragarzy; i++){
        siec.dodajWierzcholek(i);        
    }

    cout << "Polacz tragarzy wspopracujacych ze soba, ile par chcesz utworzyc?" << endl;
    int l, x, y, przepustowosc;
    cin >> l;
    for(int i = 0; i < l; i++){
        cin >> x >> y >> przepustowosc;
        siec.dodajKrawedz(x, y, przepustowosc);
    }
    
    cout << "Podaj fabryke i zrodlo:";
    int m, n;
    cin >> m, n;
    cout << siec.maxPrzeplyw(m, n);
    




    





    return 0;
}
