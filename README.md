# Płaszczaki Projekt
Projekt na przedmiot Algorytmy i Struktury Danych 2

### Dokumentacja opisowa
[Link do dokumentacji](https://docs.google.com/document/d/1JqA5u0gE-6G75cN4mcdqnfFWQBzu6YQKedxCKFQmzMY/edit?usp=sharing)

### Dokumentacja techniczna
[Link do dokumentacji](https://igorciz777.github.io/PlaszczakiProjekt/)

### Kompilacja
Uruchom w głównym katalogu

#### Main
```terminal
  g++ -Wall -Wextra .\src\main.cpp .\src\include\*.cpp -o main
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
