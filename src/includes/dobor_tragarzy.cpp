#include <iostream>
#include "SiecPrzeplywowa.cpp"
#include <vector>

using namespace std;



int main(){
    // int iloscTragarzy;

    // cout << "Podaj ilosc tragazy: "; cin >> iloscTragarzy; cout << endl;
    // std::vector<int> tablicaTragarzy(iloscTragarzy);
    // SiecPrzeplywowa siec = SiecPrzeplywowa(iloscTragarzy);


    // for(int i = 0; i < iloscTragarzy; i++){
    //     siec.dodajWierzcholek(i);        
    // }

    // cout << "Polacz tragarzy wspopracujacych ze soba, ile par chcesz utworzyc?" << endl;
    // int l, x, y, przepustowosc;
    // cin >> l;
    // for(int i = 0; i < l; i++){
    //     cin >> x >> y >> przepustowosc;
    //     siec.dodajKrawedz(x, y, przepustowosc);
    // }
    
    // cout << "Podaj fabryke i zrodlo:";
    // int m, n;
    // cin >> m, n;
    // cout << siec.maxPrzeplyw(m, n);
    int iloscTragarzy, recePrzod, receTyl;
    vector<int> tragarzePrzod, tragarzeTyl, tragarzePrzodTyl; //ostatni gdyby trzeba bylo miec ich razemm i po kolei
    cout << "Podaj ilu tragarzy bedzie budowac plot: ";
    cin >> iloscTragarzy;

    cout << "Ilu z nich ma rece z przodu?";
    cin >> recePrzod;
    // if(iloscTragarzy <= recePrzod){//TODO obsluga bledow!!
    //     cout << "zbyt";
    // }
    for(int i = 0; i < recePrzod; i++){
        tragarzePrzod.push_back(i); //dodajemy tragarzy z rekoma w przod do vectora
    }
    cout << "Ilu z nich ma rece z tylu>";
    cin >> receTyl;
    for(int i = 0; i < receTyl; i++){
        tragarzeTyl.push_back(i + recePrzod); // Dodajemy i + recePrzod, aby indeksy były kontynuacją
    }
     tragarzePrzodTyl.insert(tragarzePrzodTyl.end(), tragarzePrzod.begin(), tragarzePrzod.end());
    tragarzePrzodTyl.insert(tragarzePrzodTyl.end(), tragarzeTyl.begin(), tragarzeTyl.end());

    // for (int i : tragarzePrzod) {
    //     cout << i << " ";
    // } 
    // cout << endl;

    // for (int i : tragarzeTyl) {
    //     cout << i << " ";
    // }
    // cout << endl;

    // for (int i : tragarzePrzodTyl) {
    //     cout << i << " ";
    // }
    // cout << endl;

    

    // for(int i = 0; i < recePrzod; i++){
    //     tragarzePrzodTyl.push_back(tragarzePrzod[i]);
    // }
    // for(int i = recePrzod; i < iloscTragarzy; i++){
    //     tragarzePrzodTyl.push_back(tragarzeTyl[i]);
    // }

    
    for (int i = 0; i < recePrzod; i++){
        cout << tragarzePrzod[i];
    } 
    for (int i = 0; i < receTyl; i++){
        cout << tragarzeTyl[i];
    }
    for (int i = 0; i < iloscTragarzy; i++){
        cout << tragarzePrzodTyl[i];
    }



    //SiecPrzeplywowa siec = SiecPrzeplywowa(iloscTragarzy);

   return 0;
}
