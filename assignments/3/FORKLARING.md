# INF205 – Oppgave 2: Grafdatastruktur

## Filstruktur

```
graph.h               ← Abstrakt grensesnitt (basis for begge implementeringer)
incidence_graph.h     ← Deklarasjon: insidensliste-implementering
incidence_graph.cpp   ← Implementasjon: insidensliste
matrix_graph.h        ← Deklarasjon: matrisebasert implementering
matrix_graph.cpp      ← Implementasjon: adjasensmatrise
main.cpp              ← Testing og demonstrasjon
```

---

## Hva hver fil gjør

### `graph.h`
Abstrakt baseklasse (grensesnitt) som begge implementeringer arver fra.  
Definerer hvilke metoder som **må** finnes – ingen implementasjon her.

| Metode | Hva den skal gjøre |
|---|---|
| `insert_edge(a, kant, b)` | Legg til kant fra node a til node b |
| `disconnect(a, b)` | Slett alle kanter fra a til b |
| `remove_node(label)` | Slett en node og alle dens kanter |
| `write(os)` | Skriv grafen til en strøm (fil/skjerm) |
| `read(is)` | Les grafen fra en strøm (fil) |

Ingen `.cpp` fil – alt er `= 0` (rene virtuelle metoder).

---

### `incidence_graph.h` / `incidence_graph.cpp`
**Insidensliste-implementering** (Oppgave 2.1).  
Noder og kanter er begge objekter. Hvert objekt har en liste over de andre objektene det er direkte koblet til.

```
Node { label, liste over insidente kanter }
Edge { label, peker til from-node, peker til to-node }
```

Implementerer også **femmerregelen** (Oppgave 2.6) siden klassen eier heap-minne:

| Del av femmerregelen | Hvorfor |
|---|---|
| Destruktør `~IncidenceGraph()` | `delete` alle noder og kanter |
| Kopikonstruktør | Lag dype kopier – nye objekter med riktige pekere |
| Kopitildelingsoperator `=` | Frigjør gammelt, kopier nytt |
| Flyttekonstruktør | Ta over pekerne fra `other` |
| Flyttetildelingsoperator `=` | Frigjør eget, ta over fra `other` |

---

### `matrix_graph.h` / `matrix_graph.cpp`
**Matrisebasert implementering** (Oppgave 2.4).  
Bare noder er objekter. Kanter representeres som verdier i en 2D-tabell.

```
node_labels[i]        → navn på node i
adjacency[i][j]       → liste over kantetiketter fra node i til node j
```

Siden `vector` og `list` håndterer minnet selv, trengs ikke femmerregelen implementeres manuelt her (`= default` holder).

---

### `main.cpp`
Demonstrerer og tester all funksjonalitet:
- Opprette grafer med begge implementeringer
- Lese fra / skrive til fil
- Slette kanter og noder
- Kopiere og flytte graf-objekter

---

## Filformat (Oppgave 2.2)

Filer leses og skrives på formen:
```
Oslo fly Bergen
Bergen tog Trondheim
Trondheim buss Oslo
```
Én kant per linje: `fra-node kant-etikett til-node`

---

## Makefile – kompilering og kjøring

Makefilen finner automatisk alle `.cpp` filer i mappa og kompilerer dem.

### Kommandoer

| Kommando | Hva den gjør |
|---|---|
| `make` | Kompiler alle `.cpp` filer til `graph` |
| `make run` | Kompiler og kjør programmet |
| `make clean` | Slett `.o` objektfiler |
| `make clear` | Slett `.o`, zip, binary og `.bmp` filer |
| `make zip` | Lag `2.zip` klar for Canvas-innlevering |

### Hvordan Makefilen fungerer

- **`wildcard *.cpp`** → finner automatisk alle `.cpp` filer i mappa, ingen manuell listing
- **`patsubst %.cpp,%.o,...`** → bytter `.cpp` med `.o` for å lage objektfil-liste
- **`-g3`** → inkluderer debug-info (nyttig med `gdb`)
- **`zip`-kommandoen** inkluderer kun `Makefile`, `.cpp`, `.h` og `.pxl` – **ingen kompilerte filer** ✓

### Eksempel

```bash
make run    # bygg og kjør
make zip    # lag 2.zip for innlevering på Canvas
```

> **OBS:** Innrykk i Makefile **må** være TAB, ikke mellomrom – ellers feiler `make`

---

## Konsepter fra forelesningen brukt her

| Konsept | Hvor brukt |
|---|---|
| Abstrakt klasse / grensesnitt | `graph.h` |
| Virtuell metode (`virtual`) | Alle metoder i `graph.h` |
| Overstyring (`override`) | Alle metoder i subklassene |
| Insidensliste | `incidence_graph` |
| Adjasensmatrise | `matrix_graph` |
| Femmerregelen | `incidence_graph` |
| `new` / `delete` | `incidence_graph.cpp` |
| Minnelekkasje-unngåelse | Destruktør i `incidence_graph` |
| Fil-I/O (`fstream`) | `write()` og `read()` i begge |

---

## Vanlige feil å passe på

- **Mangler `#include <iostream>`** → feil på `<<` og `>>` operatorene
- **Bruker `delete` istedet for `delete[]`** → bare første element frigjøres
- **Glemmer å oppdatere insidenslista til begge noder** ved sletting
- **Ikke sjekker om node finnes** før `disconnect`/`remove_node` → krasj
- **Leverer kompilerte filer** – bruk `make zip` så er dette håndtert automatisk ✓
- **Innrykk i Makefile med mellomrom istedet for TAB** → `make` feiler med kryptisk feilmelding
