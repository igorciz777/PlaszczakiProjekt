#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "include/doctest.h"

#include "../src/include/AhoCorasick.h"
#include "../src/include/Huffman.h"
#include "../src/include/Kmp.h"
#include "../src/include/Tekst.h"
#include "../src/problem1.cpp"

#include <iostream>

TEST_CASE("KMP") {
    SUBCASE("Znajdz wzorzec w tekscie"){
        KMP kmp;
        std::string pattern = "test";
        std::string text = "aaatestaaa";
        std::vector<long long> result = kmp.kmpSzukaj(text, pattern);
        std::vector<long long> expected = {3};
        for(int i = 0; i < result.size(); i++){
            CHECK(result[i] == expected[i]);
        }
    }
    SUBCASE("Szukaj powtarzajacy sie wzor"){
        KMP kmp;
        std::string pattern = "test";
        std::string text = "testtesttest";
        std::vector<long long> result = kmp.kmpSzukaj(text, pattern);
        std::vector<long long> expected = {0, 4, 8};
        for(int i = 0; i < result.size(); i++){
            CHECK(result[i] == expected[i]);
        }
    }
    SUBCASE("Tekst bez wzorca"){
        KMP kmp;
        std::string pattern = "test";
        std::string text = "aaaaaaa";
        std::vector<long long> result = kmp.kmpSzukaj(text, pattern);
        std::vector<long long> expected = {};
        CHECK(result == expected);
    }
}

TEST_CASE("AhoCorasick") {
    SUBCASE("Znajdz jeden wzorzec w tekscie"){
        std::string pattern = "test";
        std::string text = "aaatestaaa";
        AhoCorasick aho(pattern);
        std::vector<std::pair<long long,long long> > result = aho.szukaj(text);
        std::vector<std::pair<long long,long long> > expected = {{6, 0}};
        for(int i = 0; i < result.size(); i++){
            CHECK(result[i].first == expected[i].first);
            CHECK(result[i].second == expected[i].second);
        }
    }
    SUBCASE("Znajdz wiele wzorcow w tekscie"){
        std::vector<std::string> patterns = {"test", "abc"};
        std::string text = "aaatestaaaabc";
        AhoCorasick aho(patterns);
        std::vector<std::pair<long long,long long> > result = aho.szukaj(text);
        std::vector<std::pair<long long,long long> > expected = {{6, 0}, {12, 1}};
        for(int i = 0; i < result.size(); i++){
            CHECK(result[i].first == expected[i].first);
            CHECK(result[i].second == expected[i].second);
        }
    }
    SUBCASE("Znajdz powtarzajace sie wzorce"){
        std::vector<std::string> patterns = {"test", "abc"};
        std::string text = "testtesttestabcabcabc";
        AhoCorasick aho(patterns);
        std::vector<std::pair<long long,long long> > result = aho.szukaj(text);
        std::vector<std::pair<long long,long long> > expected = {{3, 0}, {7, 0}, {11, 0}, {14, 1}, {17, 1}, {20, 1}};
        for(int i = 0; i < result.size(); i++){
            CHECK(result[i].first == expected[i].first);
            CHECK(result[i].second == expected[i].second);
        }
    }
    
}

TEST_CASE("Huffman") {
    Huffman huffman;
    SUBCASE("Kodowanie"){
        std::string text = "test";
        std::string encoded = huffman.koduj(text);
        /*
            t - 2 = 0
            e - 1 = 11
            s - 1 = 10

            test = 011100
        */
        CHECK(encoded == "011100");
    }
    SUBCASE("Dekodowanie"){
        std::string text = "test";
        std::string encoded = huffman.koduj(text);
        std::string decoded = huffman.dekoduj(encoded);
        CHECK(decoded == text);
    }
    SUBCASE("Kodowanie i dekodowanie tekstu z wieloma znakami"){
        std::string text = "testtesttest";
        std::string encoded = huffman.koduj(text);
        std::string decoded = huffman.dekoduj(encoded);
        CHECK(decoded == text);
    }
}

TEST_CASE("Edmonds-Karp") {
    SUBCASE("Test sieci nr1"){ //Źródło przykladu - Introduction to Algorithms CLRS
        SiecPrzeplywowa siec(6);
        siec.dodajKrawedz(0, 1, 16);
        siec.dodajKrawedz(0, 2, 13);
        siec.dodajKrawedz(1, 2, 10);
        siec.dodajKrawedz(1, 3, 12);
        siec.dodajKrawedz(2, 1, 4);
        siec.dodajKrawedz(2, 4, 14);
        siec.dodajKrawedz(3, 2, 9);
        siec.dodajKrawedz(3, 5, 20);
        siec.dodajKrawedz(4, 3, 7);
        siec.dodajKrawedz(4, 5, 4);
        std::vector<std::vector<long long>> sciezki;
        long long result = siec.edmondsKarp(0, 5, sciezki);
        CHECK(result == 23);
    }
    SUBCASE("Test sieci nr2"){
        SiecPrzeplywowa siec(6);
        siec.dodajKrawedz(0, 1, 10);
        siec.dodajKrawedz(0, 2, 10);
        siec.dodajKrawedz(1, 3, 4);
        siec.dodajKrawedz(1, 4, 8);
        siec.dodajKrawedz(2, 4, 9);
        siec.dodajKrawedz(3, 5, 10);
        siec.dodajKrawedz(4, 3, 6);
        siec.dodajKrawedz(4, 5, 10);
        std::vector<std::vector<long long>> sciezki;
        long long result = siec.edmondsKarp(0, 5, sciezki);
        CHECK(result == 19);
    }
    SUBCASE("Test sieci nr3"){
        SiecPrzeplywowa siec(6);
        siec.dodajKrawedz(0, 1, 10);
        siec.dodajKrawedz(0, 2, 10);
        siec.dodajKrawedz(1, 3, 10);
        siec.dodajKrawedz(2, 4, 10);
        siec.dodajKrawedz(3, 5, 10);
        siec.dodajKrawedz(4, 5, 10);
        std::vector<std::vector<long long>> sciezki;
        long long result = siec.edmondsKarp(0, 5, sciezki);
        CHECK(result == 20);
    }
}

TEST_CASE("Tekst") {
    SUBCASE("Zamien fragment w tekscie"){
        std::string text = "test";
        Tekst::zamienFragment(text, 0, "abc");
        CHECK(text == "abct");
    }
    SUBCASE("Zamien fragment w tekscie z pary"){
        std::string text = "test";
        Tekst::zamienFragment(text, 0, std::make_pair("te", "abc"));
        CHECK(text == "abcst");
    }   
}

TEST_CASE("Jarvis March"){
    SUBCASE("Test otoczki nr1"){
        Punkt punkty[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
        double dlugosc_plotu = 0;
        int wynik = 0;
        std::vector<int> punktyOtoczki;
        stworzOtoczke(punkty, 7, dlugosc_plotu, wynik, punktyOtoczki);
        CHECK(wynik == 4);
    }
    SUBCASE("Test otoczki nr2"){
        Punkt punkty[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}, {1, 2}};
        double dlugosc_plotu = 0;
        int wynik = 0;
        std::vector<int> punktyOtoczki;
        stworzOtoczke(punkty, 8, dlugosc_plotu, wynik, punktyOtoczki);
        CHECK(wynik == 4);
    }
    SUBCASE("Test otoczki nr3"){
        Punkt punkty[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}, {1, -1}, {1, 4}};
        double dlugosc_plotu = 0;
        int wynik = 0;
        std::vector<int> punktyOtoczki;
        stworzOtoczke(punkty, 9, dlugosc_plotu, wynik, punktyOtoczki);
        CHECK(wynik == 6);
    }
}
