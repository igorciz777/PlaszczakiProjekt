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

int main(){
    std::string opowiesc_melodia;
    std::vector<std::pair<std::string, std::string>> zamiany = {{"poli", "boli"}};
    
    std::cout << "Podaj opowieść-melodię: ";
    std::getline(std::cin, opowiesc_melodia);

    std::cout << "Czy są fragmenty, które niepokoją Heretyka i Informatyka? (t/n): ";
    char c;
    std::cin >> c;
    if(c == 't'){
        std::vector<std::string> fragmenty;
        std::cout << "Podaj fragmenty, które niepokoją Heretyka i Informatyka (po jednym w linii, zakończ pustą linią):" << std::endl;
        std::string fragment;
        while(std::getline(std::cin, fragment) && !fragment.empty()){
            fragmenty.push_back(fragment);
        }
        //AhoCorasick aho_corasick;
        //aho_corasick.zamienFragmenty(opowiesc_melodia, fragmenty, zamiany);
    }else{
        //KMP kmp;
        //kmp.zamienFragment(opowiesc_melodia, zamiany);
    }
    Huffman huffman;
    huffman.kompresuj(opowiesc_melodia);

    return 0;
}
