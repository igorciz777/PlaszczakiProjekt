#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "include/doctest.h"
#include "../src/include/AhoCorasick.h"


TEST_CASE("Test 1: Konstruktor klasy AhoCorasick"){
    AhoCorasick* ac = new AhoCorasick("");
    delete ac;
}