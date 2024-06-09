# Płaszczaki Projekt
Projekt na przedmiot Algorytmy i Struktury Danych 2

### Dokumentacja techniczna
[Link do dokumentacji](https://igorciz777.github.io/PlaszczakiProjekt/)

### Kompilacja
Uruchom w głównym katalogu
#### Problem 1
```terminal
  g++ -Wall -Wextra .\src\problem1.cpp -o problem1.exe
```
#### Problem 2
```terminal
  g++ -Wall -Wextra .\src\problem2.cpp .\src\include\*.cpp -o problem2.exe
```
#### Problem 3
```terminal
  g++ -Wall -Wextra .\src\problem3.cpp .\src\include\*.cpp -o problem3.exe
```

### Testy jednostkowe
Uruchom w głównym katalogu
```terminal
  g++ -Iinclude .\tests\tests.cpp .\src\include\*.cpp -o test
```

## Użyte technologie
- **C++** - język programowania
- [**Doxygen**](https://www.doxygen.nl/index.html) - generowanie dokumentacji technicznej
- [**GitHub Pages**](https://pages.github.com/) - hosting dokumentacji technicznej
- [**doctest**](https://github.com/doctest/doctest) - framework do testów jednostkowych