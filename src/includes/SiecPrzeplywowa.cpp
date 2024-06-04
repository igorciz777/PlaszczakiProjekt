#include <iostream>
#include "SiecPrzeplywowa.h"

SiecPrzeplywowa::SiecPrzeplywowa(int n){
    this->n = n;
    this->graf = std::vector<std::vector<Krawedz>>(n);
    this->poprzednik = std::vector<int>(n);
}

void SiecPrzeplywowa::dodajWierzcholek(int v){
    this->graf[v] = std::vector<Krawedz>();
}

void SiecPrzeplywowa::dodajKrawedz(int u, int v, int przepustowosc){
    Krawedz k1 = Krawedz();
    k1.cel = v;
    k1.przepustowosc = przepustowosc;
    k1.przeplyw = 0;
    k1.przepustowoscPoczatkowa = przepustowosc;
    this->graf[u].push_back(k1);
    Krawedz k2 = Krawedz();
    k2.cel = u;
    k2.przepustowosc = 0;
    k2.przeplyw = 0;
    k2.przepustowoscPoczatkowa = 0;
    this->graf[v].push_back(k2);
}

int SiecPrzeplywowa::edmondsKarp(int s, int t, std::vector<std::vector<int>> &sciezki_out){
    int maxPrzeplyw = 0;
    int przeplyw = 0;
    while(przeplyw = bfs(s, t)){
        maxPrzeplyw += przeplyw;
        int v = t;
        std::vector<int> sciezka;
        while(v != s){
            int u = this->poprzednik[v];
            sciezka.push_back(v);
            for(int i = 0; i < this->graf[u].size(); i++){
                if(this->graf[u][i].cel == v){
                    this->graf[u][i].przeplyw += przeplyw;
                    break;
                }
            }
            for(int i = 0; i < this->graf[v].size(); i++){
                if(this->graf[v][i].cel == u){
                    this->graf[v][i].przeplyw -= przeplyw;
                    break;
                }
            }
            v = u;
        }
        sciezka.push_back(s);
        std::reverse(sciezka.begin(), sciezka.end());
        sciezki_out.push_back(sciezka);
    }
    return maxPrzeplyw;
}


int SiecPrzeplywowa::bfs(int s, int t){
    std::vector<bool> odwiedzone = std::vector<bool>(this->n);
    std::vector<int> przeplyw = std::vector<int>(this->n);
    for(int i = 0; i < this->n; i++){
        odwiedzone[i] = false;
        przeplyw[i] = 0;
    }
    std::vector<int> kolejka = std::vector<int>();
    kolejka.push_back(s);
    odwiedzone[s] = true;
    przeplyw[s] = INF;
    while(!kolejka.empty()){
        int u = kolejka[0];
        kolejka.erase(kolejka.begin());
        for(int i = 0; i < this->graf[u].size(); i++){
            int v = this->graf[u][i].cel;
            if(!odwiedzone[v] && this->graf[u][i].przepustowosc - this->graf[u][i].przeplyw > 0){
                this->poprzednik[v] = u;
                przeplyw[v] = std::min(przeplyw[u], this->graf[u][i].przepustowosc - this->graf[u][i].przeplyw);
                if(v == t){
                    return przeplyw[t];
                }
                kolejka.push_back(v);
                odwiedzone[v] = true;
            }
        }
    }
    return 0;
}

