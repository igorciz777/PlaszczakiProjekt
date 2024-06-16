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

static PlotInfo plot_info_global;
static OpowiescMelodiaInfo opowiesc_melodia_global;
static GrafikInfo grafik_global;

void printInfo(){
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "Aktualne statystyki Krainy Plaszczakow:" << std::endl;
    std::cout << "-Informacje o plocie: " << std::endl;
    if(plot_info_global.poprawny){
        std::cout << "\t-Ilosc odcinkow plotu: " << plot_info_global.ilosc_odcinkow_plotu << std::endl;
        std::cout << "\t-Dlugosc plotu: " << plot_info_global.dlugosc_plotu << std::endl;
        std::cout << "\t-Ilosc tragarzy z rekoma z przodu: " << plot_info_global.ilosc_tragarzy_z_przodu << std::endl;
        std::cout << "\t-Ilosc tragarzy z rekoma z tylu: " << plot_info_global.ilosc_tragarzy_z_tylu << std::endl;
        std::cout << "\t-Ilosc par tragarzy wspolpracujacych: " << plot_info_global.ilosc_par << std::endl;
        std::cout << "\t-Maksymalny przeplyw: " << plot_info_global.maksymalny_przeplyw << std::endl;
        std::cout << "\t-Dni do zbudowania: " << plot_info_global.dni_do_zbudowania << std::endl;
    }else{
        std::cout << "\tBrak informacji o plocie! Uruchom problem pierwszy aby zbudowac plot." << std::endl;
    }

    std::cout << "-Opowiesc-melodia: " << std::endl;
    if(opowiesc_melodia_global.poprawna){
        std::cout << "\t-Opowiesc-melodia: " << opowiesc_melodia_global.opowiesc_melodia << std::endl;
        std::cout << "\t-Zakodowana melodia: " << opowiesc_melodia_global.zakodowana_melodia << std::endl;
        //std::cout << "\t-Kody Huffmana:\n " << opowiesc_melodia_global.kody_huffmana << std::endl;
        std::cout << "\t-Stopien kompresji: " << opowiesc_melodia_global.wspolczynnik_kompresji << std::endl;
    }else{
        std::cout << "\tBrak opowiesci-melodii! Uruchom problem drugi aby zapisac i zakodowac melodie." << std::endl;
    }

    std::cout << "-Grafik pracy straznikow: " << std::endl;
    if(grafik_global.poprawny){
        for(auto& grafik : grafik_global.grafik){
            std::cout << "\t-" << grafik << std::endl;
        }
        std::cout << "\tSuma odsluchan: " << grafik_global.suma_odsluchan << std::endl;
    }else{
        std::cout << "\tBrak grafiku pracy straznikow! Uruchom problem trzeci aby ustalic grafik pracy straznikow." << std::endl;
    }
    std::cout << "------------------------------------------------------------" << std::endl;
}

int menu(){
    char c;
    std::cout << "Wybierz jedna z opcji:" << std::endl;
    std::cout << "\t1. Problem 1" << std::endl;
    std::cout << "\t2. Problem 2" << std::endl;
    std::cout << "\t3. Problem 3" << std::endl;
    std::cout << "\t4. Wyswietl statystyki Krainy" << std::endl;
    std::cout << "\t5. Wyjscie" << std::endl;
    std::cin >> c;
    switch(c){
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        default:
            return 0;
    }
    return 0;
}

int main(){
    plot_info_global.poprawny = false;
    opowiesc_melodia_global.poprawna = false;
    grafik_global.poprawny = false;
    std::cout << "######## Plaszczaki Projekt ######## " << std::endl;
    int status = 1;
    while(status != 5){
        status = menu();
        switch(status){
            case 1:
                plot_info_global = problem1_init();
                std::cout << "Czy kontynuowac do problemu 3? (t/n): ";
                char c;
                std::cin >> c;
                if(c != 't' && c != 'T'){
                    break;
                }
                grafik_global = problem3_init(plot_info_global.ilosc_odcinkow_plotu);
                break;
            case 2:
                opowiesc_melodia_global = problem2_init();
                break;
            case 3:
                if(!plot_info_global.poprawny){
                    std::cout << "Uwaga! Plot nie zostal jeszcze zbudowany, grafik bedzie oparty na spekulacyjnych danych!" << std::endl;
                    std::cout << "Czy chcesz kontynuowac? (t/n): ";
                    char c;
                    std::cin >> c;
                    if(c != 't' && c != 'T'){
                        break;
                    }
                    grafik_global = problem3_init(0);
                }else{
                    grafik_global = problem3_init(plot_info_global.ilosc_odcinkow_plotu);
                }
                break;
            case 4:
                printInfo();
                break;
            case 5:
                break;
            default:
                std::cout << "Niepoprawny wybor!" << std::endl;
                break;
        }
    }
    return 0;
}