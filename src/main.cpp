/**
 * @file main.cpp
 * 
 * @brief Główny plik projektu
 * 
 * Główny plik wykonywalny projektu, jest odpowiednikiem menu wyboru, w którym użytkownik wybiera w jaki sposób rozwiązać i łączyć problemy.
 */

#include "problem1.cpp"
#include "problem2.cpp"
#include "problem3.cpp"

int main(){
    char c;
    std::cout << "Wybierz problem do rozwiazania (1, 2, 3): ";
    std::cin >> c;
    switch(c){
        case '1':
            problem1_init();
            break;
        case '2':
            problem2_init();
            break;
        case '3':
            problem3_init();
            break;
        default:
            std::cerr << "Nieprawidlowa opcja" << std::endl;
            break;
    }
    return 0;
}