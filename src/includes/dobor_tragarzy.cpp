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

    cout << "Polacz tragarzy wspopracujacych ze soba, ile par chcesz utworzyc? " << endl;
    int l, x, y ;
    cin >> l;
    for(int i = 0; i < l; i++){
        cin >> x >> y;
        siec.dodajKrawedz(x, y, 0);
    }
    


    





    return 0;
}
