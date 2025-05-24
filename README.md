# Kalkulator Wyrażeń (C++) / Expression Calculator (C++)

[English](#english-version) | [Polski](#wersja-polska)

---

## English Version

### Project Description

This C++ program is an integer calculator that:

* Parses infix expressions with operators `+`, `-`, `*`, `/` (integer division, floor, protects against division by zero)
* Supports functions: `IF(a,b,c)`, unary negation `N a`, variadic `MIN(...)` and `MAX(...)`
* Uses parentheses to override operator precedence

### Features

* Conversion from infix to postfix notation (RPN) using the Shunting‑Yard algorithm
* Evaluation of postfix expressions, printing the stack state before each operation
* Detection of division by zero: prints `ERROR` and proceeds to the next expression
* Handling of special functions `IF`, `N`, `MIN`, `MAX`

### Technologies and Skills

* Standard C++11 without `std::string` (uses fixed-size char arrays)
* Custom stack implemented as a singly-linked list with manual memory management (`new`/`delete`)
* Implementation of the Shunting‑Yard algorithm and postfix evaluation
* Console-based internal logging for debugging

### Architecture and Modules

* **tokenType**: represents a token (number, operator, function)
* **StackNode**: node of the linked-list stack holding a tokenType
* **Stack module**: operations `push`, `pop`, `show`, `clear`
* **Conversion module**: token parsing, operator precedence, argument counting, infix→postfix
* **Evaluation module**: routines `processIf`, `processN`, `processMinMax`, `processOperators`
* **Main loop**: reads tokens, constructs RPN, runs evaluation

### Example

**Input:**

```
4
MIN ( 100 , MAX ( 1 , 34 , 2 ) , 80 ) .
2 + 3 * 4 .
N 5 * ( 2 + 3 ) .
IF ( 1 , 10 , 20 ) .
```

**Output (snippet):**

```
100 1 34 2 MAX3 80 MIN2
...
```

---

## Wersja polska

### Opis projektu

Program w C++ będący kalkulatorem liczb całkowitych, który:

* Parsuje wyrażenia infiksowe z operatorami `+`, `-`, `*`, `/` (dzielenie całkowite, zaokrąglanie w dół, ochrona przed dzieleniem przez 0)
* Obsługuje funkcje: `IF(a,b,c)`, negację `N a`, wieloargumentowe `MIN(...)` i `MAX(...)`
* Wspiera nawiasy zmieniające kolejność wykonywania operacji

### Funkcjonalności

* Konwersja infiksu na postfiks (RPN) algorytmem Shunting‑Yard
* Ewaluacja notacji postfiksowej, z wyświetlaniem stanu stosu przed każdą operacją
* Wykrywanie dzielenia przez zero: wypisanie `ERROR` i przejście do kolejnego wyrażenia
* Obsługa funkcji `IF`, `N`, `MIN`, `MAX`

### Technologie i umiejętności

* C++11 bez `std::string` (tablice znaków)
* Własny stos z listy jednokierunkowej, manualne zarządzanie pamięcią (`new`/`delete`)
* Implementacja algorytmu Shunting‑Yard i ewaluacji RPN
* Konsolowe logowanie stanu aplikacji (debug)

### Architektura i moduły

* **tokenType**: reprezentuje token (liczbę/operator/funkcję)
* **stosElement**: węzeł stosu na liście z tokenType
* **Moduł stosu**: `push`, `pop`, `show`, `clear`
* **Moduł konwersji**: parsowanie, priorytety, zliczanie argumentów, infiks→postfiks
* **Moduł ewaluacji**: `processIf`, `processN`, `processMinMax`, `processOperators`
* **Główna pętla**: odczyt tokenów, konstrukcja RPN, ewaluacja

### Przykład

**Wejście:**

```
4
MIN ( 100 , MAX ( 1 , 34 , 2 ) , 80 ) .
2 + 3 * 4 .
N 5 * ( 2 + 3 ) .
IF ( 1 , 10 , 20 ) .
```

**Wyjście (fragment):**

```
100 1 34 2 MAX3 80 MIN2
...
```

---

## Autor / Author

Igor Tomkowicz
[LinkedIn](https://www.linkedin.com/in/igor-tomkowicz-a5760b358/) | [GitHub](https://github.com/npnpdev)

---

## Licencja / License

MIT
