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

