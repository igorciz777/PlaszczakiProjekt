#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "include/doctest.h"

#include "../src/problem1.cpp"
#include "../src/problem2.cpp"
#include "../src/problem3.cpp"

#include <iostream>
#include <fstream>

TEST_CASE("Problem 1") {
    std::streambuf *backup = std::cin.rdbuf();
    SUBCASE("Dane nr 1"){
        std::ifstream in("tests/data/p1/prob1_case1.test");
        std::cin.rdbuf(in.rdbuf());
        if(!in.is_open()){
            std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
        }
        PlotInfo result = problem1_init();
        CHECK(result.poprawny == true);
        CHECK(result.dni_do_zbudowania == 5);
        CHECK(result.maksymalny_przeplyw == 15);
        CHECK(result.ilosc_odcinkow_plotu == 5);
        CHECK(result.dlugosc_plotu > 62.4);
        CHECK(result.dlugosc_plotu < 62.5);
        CHECK(result.ilosc_par == 3);
        std::cin.rdbuf(backup);
    }
    SUBCASE("Dane nr 2"){
        std::ifstream in("tests/data/p1/prob1_case2.test");
        std::cin.rdbuf(in.rdbuf());
        if(!in.is_open()){
            std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
        }
        PlotInfo result = problem1_init();
        CHECK(result.poprawny == true);
        CHECK(result.dni_do_zbudowania == 7);
        CHECK(result.maksymalny_przeplyw == 8);
        CHECK(result.ilosc_odcinkow_plotu == 9);
        CHECK(result.dlugosc_plotu > 48);
        CHECK(result.dlugosc_plotu < 49);
        CHECK(result.ilosc_par == 2);
        std::cin.rdbuf(backup);
    }
}
TEST_CASE("Problem 2") {
    std::streambuf *backup = std::cin.rdbuf();
    SUBCASE("Dane nr 1"){
        std::ifstream in("tests/data/p2/prob2_case1.test");
        std::cin.rdbuf(in.rdbuf());
        if(!in.is_open()){
            std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
        }
        OpowiescMelodiaInfo result = problem2_init();
        CHECK(result.poprawna == true);
        CHECK(result.wspolczynnik_kompresji > 1.6);
        CHECK(result.wspolczynnik_kompresji < 1.7);
        std::cin.rdbuf(backup);
    }
    SUBCASE("Dane nr 2"){
        std::ifstream in("tests/data/p2/prob2_case2.test");
        std::cin.rdbuf(in.rdbuf());
        if(!in.is_open()){
            std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
        }
        OpowiescMelodiaInfo result = problem2_init();
        CHECK(result.poprawna == true);
        CHECK(result.wspolczynnik_kompresji > 1.7);
        CHECK(result.wspolczynnik_kompresji < 1.8);
        std::cin.rdbuf(backup);
    }
    SUBCASE("Dane nr 3"){
        std::ifstream in("tests/data/p2/prob2_case3.test");
        std::cin.rdbuf(in.rdbuf());
        if(!in.is_open()){
            std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
        }
        OpowiescMelodiaInfo result = problem2_init();
        CHECK(result.poprawna == true);
        CHECK(result.wspolczynnik_kompresji > 1.6);
        CHECK(result.wspolczynnik_kompresji < 1.7);
        std::cin.rdbuf(backup);
    }
    SUBCASE("Dane nr 4"){
        std::ifstream in("tests/data/p2/prob2_case4.test");
        std::cin.rdbuf(in.rdbuf());
        if(!in.is_open()){
            std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
        }
        OpowiescMelodiaInfo result = problem2_init();
        CHECK(result.poprawna == true);
        CHECK(result.wspolczynnik_kompresji > 1.7);
        CHECK(result.wspolczynnik_kompresji < 1.8);
        std::cin.rdbuf(backup);
    }
    SUBCASE("Dane nr 5"){
        std::ifstream in("tests/data/p2/prob2_case5.test");
        std::cin.rdbuf(in.rdbuf());
        if(!in.is_open()){
            std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
        }
        OpowiescMelodiaInfo result = problem2_init();
        CHECK(result.poprawna == true);
        CHECK(result.wspolczynnik_kompresji > 1.7);
        CHECK(result.wspolczynnik_kompresji < 1.8);
        std::cin.rdbuf(backup);
    }
}
TEST_CASE("Problem 3") {
    std::streambuf *backup = std::cin.rdbuf();
    SUBCASE("Dane nr 1"){
        std::ifstream in("tests/data/p3/prob3_case1.test");
        std::cin.rdbuf(in.rdbuf());
        if(!in.is_open()){
            std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
        }
        GrafikInfo result = problem3_init(0);
        CHECK(result.poprawny == true);
        CHECK(result.suma_odsluchan == 92);
        std::cin.rdbuf(backup);
    }
    SUBCASE("Dane nr 2"){
        std::ifstream in("tests/data/p3/prob3_case2.test");
        std::cin.rdbuf(in.rdbuf());
        if(!in.is_open()){
            std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
        }
        GrafikInfo result = problem3_init(0);
        CHECK(result.poprawny == true);
        CHECK(result.suma_odsluchan == 603);
        std::cin.rdbuf(backup);
    }
    SUBCASE("Dane nr 3"){
        std::ifstream in("tests/data/p3/prob3_case3.test");
        std::cin.rdbuf(in.rdbuf());
        if(!in.is_open()){
            std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
        }
        GrafikInfo result = problem3_init(0);
        CHECK(result.poprawny == true);
        CHECK(result.suma_odsluchan == 22);
        std::cin.rdbuf(backup);
    }
    SUBCASE("Dane nr 4"){
        std::ifstream in("tests/data/p3/prob3_case4.test");
        std::cin.rdbuf(in.rdbuf());
        if(!in.is_open()){
            std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
        }
        GrafikInfo result = problem3_init(0);
        CHECK(result.poprawny == true);
        CHECK(result.suma_odsluchan == 751);
        std::cin.rdbuf(backup);
    }
    SUBCASE("Dane nr 5"){
        std::ifstream in("tests/data/p3/prob3_case5.test");
        std::cin.rdbuf(in.rdbuf());
        if(!in.is_open()){
            std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
        }
        GrafikInfo result = problem3_init(0);
        CHECK(result.poprawny == true);
        CHECK(result.suma_odsluchan == 1099);
        std::cin.rdbuf(backup);
    }
}