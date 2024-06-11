## Dokumentacja techniczna projektu PlaszczakiProjekt
### Spis treści
1. [Rozwiązanie problemu pierwszego](#rozwiązanie-problemu-pierwszego)
2. [Rozwiązanie problemu drugiego](#rozwiązanie-problemu-drugiego)
3. [Rozwiązanie problemu trzeciego](#rozwiązanie-problemu-trzeciego)

### Rozwiązanie problemu pierwszego
#### Opis problemu

#### Opis rozwiązania

### Rozwiązanie problemu drugiego

1. **Uruchomienie programu**:
   Po uruchomieniu program pyta użytkownika, czy ma odczytać zapisaną wcześniej opowieść-melodię.
   - **Odpowiedź "t"**: Program odczytuje z zadanego pliku zakodowaną za pomocą kodowania Huffmana opowieść-melodię i wyświetla ją na standardowe wyjście.
   - **Odpowiedź "n"**: Program prosi użytkownika o wprowadzenie nowej opowieści-melodii.

2. **Wprowadzenie opowieści-melodii**:
   Po wprowadzeniu opowieści-melodii przez użytkownika, program pyta, czy w tekście istnieją niepokojące fragmenty inne niż “boli” -> “poli”.
   - **Odpowiedź "n"**: Program dokonuje zamiany “boli” -> “poli” używając algorytmu KMP do znalezienia wzorców, a następnie koduje poprawioną opowieść-melodię korzystając z kodowania Huffmana.
   - Program następnie pyta użytkownika, czy zakodowana opowieść-melodia ma zostać zapisana do pliku.
     - **Odpowiedź "t"**: Program zapisuje zakodowaną melodię do pliku tekstowego o nazwie wprowadzonej przez użytkownika.
     - **Odpowiedź "n"**: Program przechodzi dalej.

3. **Wyświetlenie wyników**:
   Program wyświetla na standardowe wyjście opowieść-melodię po zamianach fragmentów oraz jej zakodowaną wersję w kodzie Huffmana.

4. **Dodatkowe zamiany**:
   W przypadku odpowiedzi "t" na pytanie o inne niepokojące fragmenty, program prosi użytkownika o ich wprowadzenie, na przykład: “goli” -> “soli”.
   - Po wprowadzeniu fragmentów, program dokonuje zamiany “boli” -> “poli” oraz podanych przez użytkownika fragmentów, używając algorytmu Aho-Corasicka do znalezienia wzorców, a następnie koduje poprawioną opowieść-melodię korzystając z kodowania Huffmana.
   - Program następnie pyta użytkownika, czy zakodowana opowieść-melodia ma zostać zapisana do pliku.
     - **Odpowiedź "t"**: Program zapisuje zakodowaną melodię do pliku tekstowego o nazwie wprowadzonej przez użytkownika.
     - **Odpowiedź "n"**: Program przechodzi dalej.

5. **Wyświetlenie wyników po dodatkowych zamianach**:
   Na koniec program wyświetla na standardowe wyjście opowieść-melodię po zamianach fragmentów oraz jej zakodowaną wersję w kodzie Huffmana.

### Rozwiązanie problemu trzeciego

### Dokumentacja do programu rozwiązującego problem 3

#### 1. Opis problemu

Strażnicy, zwani płaszczakami, mają za zadanie raz dziennie patrolować płot chroniący krainę.
Patrolowanie odbywa się zgodnie z ruchem wskazówek zegara po punktach orientacyjnych o różnej jasności.
Płaszczak musi się zatrzymać po przejściu określonej liczby punktów, aby się rozejrzeć, i zachowuje energię tylko wtedy, gdy poprzedni punkt zatrzymania był jaśniejszy od bieżącego.
Gdy punkt bieżący jest ciemniejszy lub równie jasny jak poprzedni, płaszczak traci całą energię i musi odpocząć, słuchając melodii.

Celem jest ustalenie, który płaszczak będzie patrolował danego dnia i w jakim punkcie orientacyjnym powinien rozpocząć trasę, aby liczba odsłuchań melodii była minimalna.

---

#### 2. Wymagania

- Ustalanie grafiku pracy strażników na siedem dni.
- Minimalizacja liczby odsłuchań melodii przez każdego strażnika.

---

#### 3. Struktury danych

- **Plaszczak**
  - `int id`: identyfikator płaszczaka.
  - `int co_ile_zatrzyma_sie`: liczba punktów, po której płaszczak musi się zatrzymać.
  - `bool odpoczywa`: flaga wskazująca, czy płaszczak odpoczywa.

- **PunktOrientacyjny**
  - `int id`: identyfikator punktu orientacyjnego.
  - `int jasnosc`: jasność punktu orientacyjnego.
  - `PunktOrientacyjny* nastepny`: wskaźnik na następny punkt orientacyjny.

---

#### 4. Algorytm

1. **Wczytywanie danych**:
   - Wczytanie liczby punktów orientacyjnych i liczby płaszczaków.
   - Wczytanie jasności punktów orientacyjnych.
   - Wczytanie liczby punktów, po której płaszczak musi się zatrzymać.

2. **Inicjalizacja**:
   - Utworzenie listy punktów orientacyjnych.
   - Utworzenie kolejki priorytetowej płaszczaków, posortowanej według liczby punktów do zatrzymania.

3. **Wyznaczanie grafiku**:
   - Na każdy dzień tygodnia:
     - Wybranie płaszczaka z największą liczbą punktów do zatrzymania.
     - Dla każdego punktu orientacyjnego jako punktu startowego:
       - Symulacja trasy płaszczaka, zliczanie odsłuchań melodii.
       - Wybór trasy minimalizującej liczbę odsłuchań melodii.
     - Wysłanie płaszczaka na odpoczynek po wykonaniu dnia pracy.

4. **Wyjście**:
   - Wyświetlenie grafiku pracy strażników z minimalną liczbą odsłuchań melodii.

