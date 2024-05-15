#include <iostream>
#include "SiecPrzeplywowa.cpp"
#include <vector>

using namespace std;



int main(){
    
    int recePrzod, receTyl, tragarz1, tragarz2, iloscPar, zrodlo, ujscie, n;
    vector<int> tragarzePrzod, tragarzeTyl, tragarzePrzodTyl; //ostatni gdyby trzeba bylo miec ich razemm i po kolei
    vector<pair<int, int>> wspolpracaTragarzy;


    cout << "Podaj liczbe tragarzy z rekoma z przodu: ";
    cin >> recePrzod;
    // if(iloscTragarzy <= recePrzod){//TODO obsluga bledow!!
    //     cout << "zbyt";
    // }
    for(int i = 0; i < recePrzod; i++){
        tragarzePrzod.push_back(i); //dodajemy tragarzy z rekoma w przod do vectora
    }
    cout << "Podaj liczbe tragarzy z rekoma z tylu: ";
    cin >> receTyl;
    for(int i = 0; i < receTyl; i++){
        tragarzeTyl.push_back(i + recePrzod); // Dodajemy i + recePrzod, aby indeksy były kontynuacją
    }
    tragarzePrzodTyl.insert(tragarzePrzodTyl.end(), tragarzePrzod.begin(), tragarzePrzod.end());
    tragarzePrzodTyl.insert(tragarzePrzodTyl.end(), tragarzeTyl.begin(), tragarzeTyl.end());

    


    cout << endl;
    cout << "Tragarze z rekoma z przodu: " << endl;
    for (int i : tragarzePrzod) {
        cout << i << " ";
    } 
    cout << endl;
    cout << endl;
    cout << "Tragarze z rekoma z tylu: " << endl;
    for (int i : tragarzeTyl) {
        cout << i << " ";
    }
    cout << endl;
    cout << endl;
    cout << "Lista wszystkich tragarzy: " << endl;
    for (int i : tragarzePrzodTyl) {
        cout << i << " ";
    }
    cout << endl;
    cout << endl;

    //do wykorzystania lub nie:


    // cout << "Podaj liczbe par tragarzy, ktorzy moga wspolpracowac: ";
    // cin >> iloscPar;
    // for (int i = 0; i < iloscPar; i++) {
    //     cout << "Podaj pare tragarzy (indeks z przodu i indeks z tylu): ";
    //     cin >> tragarz1 >> tragarz2;
    //     wspolpracaTragarzy.push_back(make_pair(tragarz1, tragarz2 + recePrzod)); // Dodajemy recePrzod, aby dostosować indeksy
    // }


    // Teraz mamy graf dwudzielny z tragarzami i ich możliwymi współpracami
    // Wypiszmy współprace:
    // cout << "Mozliwe wspolprace:\n";
    // for (const auto& para : wspolpracaTragarzy) {
    //     cout << "Tragarz z przodu " << para.first << " moze wspolpracowac z tragarzem z tylu " << para.second << endl;
    // }


    
    
    cout << "Ile par moze ze soba wspolpracowac? "; 
    cin >> iloscPar;
    for(int i = 0; i < iloscPar; i++){
        cin >> tragarz1 >> tragarz2;
        wspolpracaTragarzy.push_back(make_pair(tragarz1, tragarz2));
    }
    cout << endl;
    for(auto& para : wspolpracaTragarzy){
        cout << para.first << " wspolpracuje z " << para.second << endl;
    }
    int wierzcholki = tragarzePrzodTyl.size();
    SiecPrzeplywowa siec1 = SiecPrzeplywowa(wierzcholki);
    
    for(int i = 0; i < wierzcholki; i++){
        siec1.dodajWierzcholek(tragarzePrzodTyl[i]);
    }
    for(int i = 0; i < iloscPar; i++){
        int przepustowosc;
        cout << "Podaj przepustowosc dla pary: " << wspolpracaTragarzy[i].first << ", " << wspolpracaTragarzy[i].second << ": ";
        cin >> przepustowosc;
        siec1.dodajKrawedz(wspolpracaTragarzy[i].first, wspolpracaTragarzy[i].second, przepustowosc);
    }

    cout << "Ktory tragarz jest zrodlem(fabryka)? ";
    cin >> n;
    zrodlo = tragarzePrzodTyl[n];
    cout << "Ktory jest ujsciem? ";
    cin >> n;
    ujscie = tragarzePrzodTyl[n];
    vector<vector<int>> sciezki;
    

    int maksymalnyPrzeplyw = siec1.edmondsKarp(zrodlo, ujscie, sciezki);

    cout << "Maksymalny przeplyw to: " << maksymalnyPrzeplyw << endl;
   
//tragarze w grafie dwudzielnym
//maksymalna liczba par to maksymalne skojarzenie
//przzepustowosci 1
//


    



    

   return 0;
}
