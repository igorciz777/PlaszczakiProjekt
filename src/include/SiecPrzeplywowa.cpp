/**
 * @file SiecPrzeplywowa.cpp
 * @brief Plik źródłowy klasy SiecPrzeplywowa
 * 
 * Plik zawiera implementację metod klasy SiecPrzeplywowa
 * 
 * @see SiecPrzeplywowa.h
 */
#include <iostream>
#include "SiecPrzeplywowa.h"

SiecPrzeplywowa::SiecPrzeplywowa(lli n){
    this->n = n;
    this->graf = std::vector<std::vector<Krawedz>>(n);
    this->poprzednik = std::vector<lli>(n);
}

void SiecPrzeplywowa::dodajWierzcholek(lli v){
    this->graf[v] = std::vector<Krawedz>();
}

void SiecPrzeplywowa::dodajKrawedz(lli u, lli v, lli przepustowosc){
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

lli SiecPrzeplywowa::edmondsKarp(lli s, lli t, std::vector<std::vector<lli>> &sciezki_out){
    lli maxPrzeplyw = 0;
    lli przeplyw = 0;
    while((przeplyw = bfs(s, t))){
        maxPrzeplyw += przeplyw;
        lli v = t;
        std::vector<lli> sciezka;
        while(v != s){
            lli u = this->poprzednik[v];
            sciezka.push_back(v);
            for(llu i = 0; i < this->graf[u].size(); i++){
                if(this->graf[u][i].cel == v){
                    this->graf[u][i].przeplyw += przeplyw;
                    break;
                }
            }
            for(llu i = 0; i < this->graf[v].size(); i++){
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


lli SiecPrzeplywowa::bfs(lli s, lli t){
    std::vector<bool> odwiedzone = std::vector<bool>(this->n);
    std::vector<lli> przeplyw = std::vector<lli>(this->n);
    for(lli i = 0; i < this->n; i++){
        odwiedzone[i] = false;
        przeplyw[i] = 0;
    }
    std::vector<lli> kolejka = std::vector<lli>();
    kolejka.push_back(s);
    odwiedzone[s] = true;
    przeplyw[s] = INF;
    while(!kolejka.empty()){
        lli u = kolejka[0];
        kolejka.erase(kolejka.begin());
        for(llu i = 0; i < this->graf[u].size(); i++){
            lli v = this->graf[u][i].cel;
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

