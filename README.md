# Kalkulator Wyrażeń (C++)

> Aplikacja konwertująca wyrażenia infiksowe z funkcjami i nawiasami na notację postfiksową, a następnie je obliczająca.

---

## 📜 Spis treści

* [Opis projektu](#opis-projektu)
* [Funkcjonalności](#funkcjonalności)
* [Technologie i umiejętności](#technologie-i-umiejętności)
* [Architektura i główne moduły](#architektura-i-główne-moduły)
* [Przykład użycia](#przykład-użycia)
* [Autor](#autor)
* [Licencja](#licencja)

---

## 📝 Opis projektu

Ten projekt implementuje kalkulator liczb całkowitych, obsługujący:

* operatory: `+`, `-`, `*`, `/` (dzielenie całkowite, zaokrąglanie w dół, ochrona przed dzieleniem przez 0)
* funkcje: `IF(a,b,c)`, negacja `N a`, wieloargumentowe `MIN(...)` i `MAX(...)`
* dowolne nawiasy do zmiany priorytetów

Wejście: liczba formuł, następnie każda formuła w notacji infiksowej kończąca się `.` i tokenizowana białymi znakami. Wyniki są wyświetlane na standardowym wyjściu, w tym stan stosu przed każdą operacją.

---

## ⚙️ Funkcjonalności

* **Konwersja**: infiks → postfiks (Reverse Polish Notation) z zachowaniem priorytetów i obsługą funkcji.
* **Ewaluacja**: obliczanie wyrażenia postfiksowego z wypisywaniem stanu stosu przed wykonaniem każdej operacji.
* **Obsługa błędów**: wykrywanie dzielenia przez zero, wypisanie `ERROR` i przejście do kolejnej formuły.
* **Funkcje specjalne**:

  * `IF(a,b,c)` – zwraca `b` jeśli `a>0`, w przeciwnym razie `c`.
  * `N a` – negacja, zwraca `-a`.
  * `MIN(a1,a2,...)`, `MAX(a1,a2,...)` – zwracają najmniejszy lub największy z argumentów.

---

## 🛠 Technologie i umiejętności

* **Język**: C++ (C++11) bez użycia `std::string` – operacje na tablicach znaków.
* **Struktury danych**: stos zbudowany na liście jednokierunkowej.
* **Algorytmy**: algorytm Shunting‑Yard do konwersji wyrażeń.
* **Zarządzanie pamięcią**: manualne alokacje (`new`/`delete`) i zwalnianie pamięci.
* **Debug i logging**: wypisywanie stanu wewnętrznych struktur dla śledzenia działania.

---

## 🏗️ Architektura i główne moduły

* **`tokenType`** – reprezentuje pojedynczy token (liczbę, operator, nazwę funkcji).
* **`stosElement`** – węzeł stosu, przechowuje `tokenType` i wskaźnik `next`.
* **Stos** – operacje `push`, `pop`, `show`, `clear`.
* **Konwersja** – funkcje do rozpoznawania tokenów, priorytetów, zliczania argumentów funkcji i przekształcania infiksu na postfiks.
* **Ewaluacja** – procedury `processIf`, `processN`, `processMinMax`, `processOperators`, które wykonują obliczenia zgodnie z notacją postfiksową.
* **Sterowanie** – główna pętla w `main`, czytanie tokenów, budowa RPN, drivery konwersji i ewaluacji.

---

## 📋 Przykład użycia

**Wejście**:

```
4
MIN ( 100 , MAX ( 1 , 34 , 2 ) , 80 ) .
2 + 3 * 4 .
N 5 * ( 2 + 3 ) .
IF ( 1 , 10 , 20 ) .
```

**Wyjście** (fragment):

```
100 1 34 2 MAX3 80 MIN2
MAX3  ...
34
...  (kolejne wyniki)
```

---

## 👤 Autor

Igor Tomkowicz
[LinkedIn](https://www.linkedin.com/in/igor-tomkowicz-a5760b358/) • [GitHub](https://github.com/npnpdev)

---

## 📄 Licencja

MIT
