/**
 * @file problem2.cpp
 * @brief Rozwiązanie problemu 2
 * 
 * Rozwiązanie problemu:
 * Zapisać opowieść-melodię w maszynie Informatyka, zamieniając wcześniej „poli” na
 * „boli” oraz próbując oszczędzić wykorzystane miejsce. Znaleźć rozwiązanie problemu ewentualnej
 * zamiany innych fragmentów opowieści-melodii, który niepokoi Heretyka oraz Informatyka.
 * 
 * Rozwiązanie teoretyczne:
 * 1. Wczytaj opowieść-melodię.
 * 2. Zapytaj Heretyka i Informatyka o fragmenty, które ich niepokoją.
 * 3. Jeśli nie ma takich fragmentów, wykonać zamianę „poli” na „boli” za pomocą algorytmu KMP.
 * 4. Jeśli są takie fragmenty, wykonać zamianę wszystkich fragmentów na poprawne za pomocą algorytmu Aho-Corasick.
 * 5. Skompresować opowieść-melodię za pomocą algorytmu Huffmana.
 * 
 * Użyte biblioteki:
 * @see AhoCorasick.h
 * @see Kmp.h
 * @see Huffman.h
 * @see Tekst.h
*/

#include "include/AhoCorasick.h"
#include "include/Kmp.h"
#include "include/Huffman.h"
#include "include/Tekst.h"
#include <fstream>

std::string dekodujHuffman(const std::string& zakodowana_melodia, const std::string& kody){
    std::unordered_map<std::string, char> mapa_kodow;
    std::stringstream ss(kody);
    std::string kod, znak;
    while(ss >> kod >> znak){
        mapa_kodow[kod] = znak[0];
    }
    std::stringstream odkodowana_melodia("");
    kod = "";
    for(char c : zakodowana_melodia){
        kod += c;
        if(mapa_kodow.find(kod) != mapa_kodow.end()){
            odkodowana_melodia << mapa_kodow[kod];
            kod = "";
        }
    }
    return odkodowana_melodia.str();
}


int main(){
    char c;
    std::ifstream file_in;
    std::ofstream file_out;
    std::string opowiesc_melodia;
    std::vector<std::pair<std::string, std::string>> zamiany = {{"poli", "boli"}};

    std::cout << "Odkodowac melodie z pliku? (t/n): ";
    std::cin >> c;
    if(c == 't' || c == 'T'){
        std::string nazwa_pliku;
        std::string zakodowana_melodia;
        std::stringstream kody("");
        
        std::cout << "Podaj nazwe pliku (.txt): ";
        std::cin >> nazwa_pliku;

        if(nazwa_pliku.empty()){
            std::cerr << "Nieprawidlowa nazwa pliku" << std::endl;
            return 1;
        }

        if(nazwa_pliku.find(".txt") == std::string::npos){
            nazwa_pliku += ".txt";
        }

        file_in.open(nazwa_pliku);

        if(!file_in.is_open()){
            std::cerr << "Nie udalo sie otworzyc pliku" << std::endl;
            return 1;
        }

        std::string line;
        while(std::getline(file_in, line)){
            if(line == "##"){
                break;
            }
            std::stringstream ss(line);
            std::string znak, kod;
            ss >> znak >> kod;
            kody << kod << " " << znak << " ";
        }
        std::getline(file_in, zakodowana_melodia);

        file_in.close();
        file_out.close();
        opowiesc_melodia = dekodujHuffman(zakodowana_melodia, kody.str());
        std::cout << "Odkodowana melodia: " << opowiesc_melodia << std::endl;
        return 0;
    }else{
        std::cin.ignore();
    }
    
    std::cout << "Podaj opowiesc-melodie: ";
    std::getline(std::cin, opowiesc_melodia);

    std::cout << "Czy sa fragmenty, ktore niepokoja Heretyka i Informatyka? (t/n): ";
    std::cin >> c;
    if(c == 't'){
        std::string fragment;
        std::cout << "Podaj fragmenty, ktore niepokoja Heretyka i Informatyka (format: fragment zamiana (oddzielone spacja) na jedna linie, zakoncz pusta linia):" << std::endl;
        
        std::cin.ignore();
        while(std::getline(std::cin, fragment)){
            if(fragment.empty()){
                break;
            }
            std::stringstream ss(fragment);
            std::string f1, f2;
            ss >> f1 >> f2;
            zamiany.push_back({f1, f2});
        }

        std::vector<std::string> wzorce;
        for(auto i : zamiany){
            wzorce.push_back(i.first);
        }
        AhoCorasick ahoCorasick(wzorce);
        std::vector<std::pair<int,int> > idx = ahoCorasick.szukaj(opowiesc_melodia);

        for(auto it = idx.rbegin(); it != idx.rend(); it++){
            int start = it->first - zamiany[it->second].first.size() + 1;
            Tekst::zamienFragment(opowiesc_melodia, start, zamiany[it->second]);
        }
    }else{
        std::vector<int> idx = KMP::kmpSzukaj(opowiesc_melodia, zamiany[0].first);
        for(int i : idx){
            Tekst::zamienFragment(opowiesc_melodia,i,zamiany[0].second);
        }
    }
    Huffman huffman;
    std::string zakodowana_melodia = huffman.koduj(opowiesc_melodia);

    std::cout << "Czy zapisac zakodowana melodie do pliku? (t/n): ";
    std::cin >> c;
    if(c == 'n' || c == 'N'){
        std::cout << "Zakodowana melodia: " << zakodowana_melodia << std::endl;
        return 0;
    }else{
        std::string nazwa_pliku;
        std::cout << "Podaj nazwe pliku (.txt): ";
        std::cin >> nazwa_pliku;

        if(nazwa_pliku.empty()){
            std::cerr << "Nieprawidlowa nazwa pliku" << std::endl;
            return 1;
        }

        if(nazwa_pliku.find(".txt") == std::string::npos){
            nazwa_pliku += ".txt";
        }

        file_out.open(nazwa_pliku);

        if(!file_out.is_open()){
            std::cerr << "Nie udalo sie otworzyc pliku" << std::endl;
            return 1;
        }
    }

    std::stringstream kody("");
    huffman.wypiszKod(huffman.getKorzen(), "", kody);

    file_out << kody.str();
    std::cout << "Melodia po zmianach: " << opowiesc_melodia << std::endl;
    std::cout << "Zakodowana melodia: " << zakodowana_melodia << std::endl;
    file_out << "##" << std::endl;
    file_out << zakodowana_melodia << std::endl;
    file_out.close();
   
    return 0;
}
