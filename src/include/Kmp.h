#include <iostream>
#include <vector>

/**
 * @brief Klasa reprezentująca algorytm KMP
 * 
 * Klasa zawiera metody do tworzenia tablicy LPS oraz wyszukiwania wzorca w tekście
 * 
*/

class KMP{
    public:
        /**
         * @brief Metoda tworząca tablicę LPS
         * 
         * Tworzy tablicę LPS (Longest Prefix Suffix) dla danego wzorca
         * 
         * @param wzorzec Wzorzec, dla którego tworzymy tablicę LPS
        */
        std::vector<int> static stworzLPS(const std::string& wzorzec);

        /**
         * @brief Metoda wyszukująca wzorzec w tekście
         * 
         * @param tekst Tekst, w którym szukamy wzorca
         * 
         * @param wzorzec Wzorzec, który szukamy w tekście
        */ 
        std::vector<int> static kmpSzukaj(const std::string& tekst, const std::string& wzorzec);    
};

