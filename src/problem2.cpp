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
*/

#include "includes/AhoCorasick.cpp"
#include "includes/Kmp.cpp"
#include "includes/Huffman.cpp"
#include "includes/Tekst.cpp"
#include <sstream>

int main(){
    std::string opowiesc_melodia;
    std::vector<std::pair<std::string, std::string>> zamiany = {{"poli", "boli"}};
    
    std::cout << "Podaj opowiesc-melodie: ";
    std::getline(std::cin, opowiesc_melodia);

    std::cout << "Czy sa fragmenty, ktore niepokoja Heretyka i Informatyka? (t/n): ";
    char c;
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
    std::cout << "Melodia po zmianach: " << opowiesc_melodia << std::endl;
    std::cout << "Zakodowana melodia: " << zakodowana_melodia << std::endl;
    return 0;
}
