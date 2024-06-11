## Dokumentacja techniczna projektu PlaszczakiProjekt
### Spis treści
1. [Rozwiązanie problemu pierwszego](#rozwiązanie-problemu-pierwszego)
2. [Rozwiązanie problemu drugiego](#rozwiązanie-problemu-drugiego)
3. [Rozwiązanie problemu trzeciego](#rozwiązanie-problemu-trzeciego)

### Rozwiązanie problemu pierwszego
#### Opis problemu

#### Opis rozwiązania

### Rozwiązanie problemu drugiego

**Problem 2**

(Zapisać opowieść-melodię, zamieniając “poli” na “boli” oraz inne fragmenty niepokojące i oszczędzić przy tym wykorzystane miejsce.)

Program po uruchomieniu pyta użytkownika, czy ma odczytać zapisaną wcześniej opowieść-melodię.

W przypadku odpowiedzi “t” program odczytuje z zadanego pliku zakodowaną poprzez kodowanie Huffmana opowieść-melodię i wyświetla ją na standardowe wyjście.

W przypadku odpowiedzi “n” program prosi użytkownika o wprowadzenie opowieści-melodii, następnie po wprowadzeniu jej przez użytkownika, program pyta czy w opowieści-melodii istnieją fragmenty niepokojące inne niż “boli” -> “poli”.

W przypadku odpowiedzi “n” program dokonuje zamiany “boli” -> “poli” używając algorytmu [KMP](https://igorciz777.github.io/PlaszczakiProjekt/_kmp_8h.html) do znalezienia wzorców, następnie koduje poprawioną opowieść-melodię korzystając z kodowania [Huffmana](https://igorciz777.github.io/PlaszczakiProjekt/_huffman_8h.html). Kolejno, użytkownik jest pytany o to, czy zakodowana opowieść-melodia ma zostać zapisana do pliku.

W przypadku odpowiedzi “t” program zapisuje zakodowaną melodię do pliku tekstowego o nazwie wprowadzonej przez użytkownika.

W przypadku odpowiedzi “n” program przechodzi dalej.

Na koniec program wyświetla na standardowe wyjście opowieść-melodię po zamianach fragmentów, oraz jej zakodowaną wersję w kodzie [Huffmana](https://igorciz777.github.io/PlaszczakiProjekt/_huffman_8h.html).

W przypadku odpowiedzi “t” program prosi użytkownika o wprowadzenie niepokojących fragmentów innych niż “boli” -> “poli”, na przykład: “goli” -> “soli”.

Po wprowadzeniu program dokonuje zamiany “boli” -> “poli” oraz podanych przez użytkownika fragmentów używając algorytmu [Aho-Corasicka](https://igorciz777.github.io/PlaszczakiProjekt/_aho_corasick_8h.html) do znalezienia wzorców, a następnie koduje poprawioną opowieść-melodię korzystając z kodowania [Huffmana](https://igorciz777.github.io/PlaszczakiProjekt/_huffman_8h.html). Kolejno, użytkownik jest pytany o to, czy zakodowana opowieść-melodia ma zostać zapisana do pliku.

W przypadku odpowiedzi “t” program zapisuje zakodowaną melodię do pliku tekstowego o nazwie wprowadzonej przez użytkownika.

W przypadku odpowiedzi “n” program przechodzi dalej.

Na koniec program wyświetla na standardowe wyjście opowieść-melodię po zamianach fragmentów, oraz jej zakodowaną wersję w kodzie [Huffmana](https://igorciz777.github.io/PlaszczakiProjekt/_huffman_8h.html).

### Rozwiązanie problemu trzeciego

