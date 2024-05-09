#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Klasa reprezentująca krawędź w grafie przepływu
class FlowEdge {
public:
    int v, w;       // Krawędź od v do w
    int capacity;   // Pojemność krawędzi
    int flow;       // Przepływ na krawędzi

    FlowEdge(int v, int w, int capacity) : v(v), w(w), capacity(capacity), flow(0) {}
};

// Klasa reprezentująca graf przepływu
class FlowNetwork {
public:
    int V;                              // Liczba wierzchołków
    vector<vector<FlowEdge>> adjList;   // Lista sąsiedztwa

    FlowNetwork(int V) : V(V) {
        adjList.resize(V);
    }

    // Dodawanie krawędzi do grafu
    void addEdge(int v, int w, int capacity) {
        FlowEdge forwardEdge(v, w, capacity);
        FlowEdge backwardEdge(w, v, 0); // Krawędź powrotna ma początkowy przepływ 0
        adjList[v].push_back(forwardEdge);
        adjList[w].push_back(backwardEdge); // Dodajemy krawędź powrotną do uwzględnienia w przepływie
    }
};

int fordFulkerson(FlowNetwork& G, int s, int t) {
    vector<bool> visited(G.V, false);       // Tablica odwiedzonych wierzchołków
    vector<FlowEdge*> edgeTo(G.V, nullptr); // Krawędź, która prowadzi do danego wierzchołka
    int maxFlow = 0;

    // Dopóki istnieje ścieżka z s do t w grafie przepływu
    while (true) {
        // BFS w grafie rezydualnym (grafie z krawędziami powrotnymi)
        queue<int> q;
        q.push(s);
        visited.assign(G.V, false);
        visited[s] = true;
        while (!q.empty() && !visited[t]) {
            int v = q.front();
            q.pop();
            for (FlowEdge& e : G.adjList[v]) {
                int w = e.w;
                if (!visited[w] && e.capacity - e.flow > 0) {
                    visited[w] = true;
                    edgeTo[w] = &e;
                    q.push(w);
                }
            }
        }

        // Jeśli nie ma już ścieżek, przerywamy
        if (!visited[t]) break;

        // Obliczanie przepływu maksymalnego w danej ścieżce
        int bottleNeck = INT_MAX;
        for (int v = t; v != s; v = edgeTo[v]->v) {
            bottleNeck = min(bottleNeck, edgeTo[v]->capacity - edgeTo[v]->flow);
        }

        // Aktualizacja przepływu na krawędziach
        for (int v = t; v != s; v = edgeTo[v]->v) {
            edgeTo[v]->flow += bottleNeck;
            for (FlowEdge& e : G.adjList[edgeTo[v]->v]) {
                if (e.w == v) {
                    e.flow -= bottleNeck; // Odjęcie przepływu na krawędziach powrotnych
                    break;
                }
            }
        }

        maxFlow += bottleNeck; // Zwiększenie przepływu maksymalnego o przepływ w danej ścieżce
    }

    return maxFlow;
}

int main() {
    int V = 6; // Przykładowa liczba wierzchołków w grafie
    FlowNetwork G(V);

    // Dodawanie krawędzi do grafu przepływu
    G.addEdge(0, 1, 16);
    G.addEdge(0, 2, 13);
    G.addEdge(1, 2, 10);
    G.addEdge(1, 3, 12);
    G.addEdge(2, 1, 4);
    G.addEdge(2, 4, 14);
    G.addEdge(3, 2, 9);
    G.addEdge(3, 5, 20);
    G.addEdge(4, 3, 7);
    G.addEdge(4, 5, 4);

    int source = 0; // Wierzchołek źródłowy
    int sink = 5;   // Wierzchołek docelowy

    // Wywołanie algorytmu Forda-Fulkersona
    int maxFlow = fordFulkerson(G, source, sink);

    cout << "Maksymalny przepływ w grafie: " << maxFlow << endl;

    return 0;
}
