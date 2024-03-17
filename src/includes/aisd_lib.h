/**
 * @file aisd_lib.h
 * @brief Biblioteka do obsługi struktur danych i algorytmów
*/

/**
 * @brief Struktura reprezentująca wierzchołek
 * 
 * Struktura reprezentująca wierzchołek w grafie
 * @param data - wartość wierzchołka
*/
struct Node{
    char data;
};

/**
 * @brief Struktura reprezentująca krawędź
 * 
 * Struktura reprezentująca krawędź w grafie
 * @param src - wskaźnik na wierzchołek źródłowy
 * @param dest - wskaźnik na wierzchołek docelowy
*/
struct Edge{
    struct Node *src;
    struct Node *dest;
};

/**
 * @brief Struktura reprezentująca krawędź w sieci przepływowej
 * 
 * Struktura reprezentująca krawędź w sieci przepływowej
 * @param capacity - pojemność krawędzi
 * @param flow - przepływ krawędzi
*/
struct Arc : public Edge{
    int capacity;
    int flow;
};

/**
 * @brief Struktura reprezentująca sieć przepływową
 * 
 * Struktura reprezentująca sieć przepływową
 * @param V - liczba wierzchołków
 * @param E - liczba krawędzi
 * @param arc - tablica krawędzi
 * @param node - tablica wierzchołków
 * @param start - wskaźnik na wierzchołek źródłowy
 * @param target - wskaźnik na wierzchołek docelowy
*/
struct FlowNetwork{
    int V, E;
    struct Arc *arc;
    struct Node *node;
    struct Node *start, *target;
    int **adjMatrix;
};

