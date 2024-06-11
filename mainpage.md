# Dokumentacja techniczna projektu PlaszczakiProjekt

## Rozwiązanie problemu pierwszego

---





## Rozwiązanie problemu drugiego

#### 1. Opis problemu

Program ma za zadanie przetwarzać opowieść-melodię, zamieniając w niej określone fragmenty tekstu. Standardowo zamienia „poli” na „boli”, a jeśli zostaną zgłoszone dodatkowe fragmenty do zamiany, to zamienia również te fragmenty. Po dokonaniu zamian, melodia jest kompresowana za pomocą algorytmu Huffmana w celu oszczędzenia miejsca.

---

#### 2. Algorytmy i struktury danych

- [Aho-Corasick](#AhoCorasick): Używany do jednoczesnego wyszukiwania wielu wzorców w tekście.
- [Knuth-Morris-Pratt (KMP)](#KMP): Używany do wyszukiwania pojedynczego wzorca w tekście.
- **Huffman**: Używany do kompresji tekstu.

---

#### 3. Struktura kodu


**Funkcja główna:**

1. **Inicjalizacja i odczyt danych wejściowych:**
   - Użytkownik wybiera, czy odkodować melodię z pliku.
   - Jeśli tak, wczytywana jest zakodowana melodia oraz kody Huffmana z pliku, a następnie melodia jest dekodowana.
   - Jeśli nie, użytkownik podaje opowieść-melodię ręcznie.

2. **Sprawdzanie dodatkowych fragmentów do zamiany:**
   - Użytkownik może podać dodatkowe fragmenty tekstu do zamiany.
   - W przypadku podania dodatkowych fragmentów, używany jest algorytm Aho-Corasick do jednoczesnego wyszukiwania i zamiany wszystkich fragmentów.
   - W przypadku braku dodatkowych fragmentów, używany jest algorytm KMP do zamiany „poli” na „boli”.

3. **Kompresja melodii:**
   - Po dokonaniu zamian, melodia jest kompresowana za pomocą algorytmu Huffmana.
   - Użytkownik może wybrać, czy zapisać zakodowaną melodię do pliku.


---





## Rozwiązanie problemu trzeciego

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

