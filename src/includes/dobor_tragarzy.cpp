#include <iostream>
#include "SiecPrzeplywowa.cpp"
#include <vector>

using namespace std;



int main(){
    
    int recePrzod, receTyl;
    vector<int> tragarzePrzod, tragarzeTyl, tragarzePrzodTyl; //ostatni gdyby trzeba bylo miec ich razemm i po kolei
    

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

   return 0;
}
