# INF205 – Oppgave 2: Grafdatastruktur

## Filstruktur

```
graph.h               ← Abstrakt grensesnitt (basis for begge implementeringer)
incidenceListGraph.h      ← Deklarasjon: insidensliste-implementering
incidenceListGraph.cpp    ← Implementasjon: insidensliste
adjacencyMatrixGraph.h        ← Deklarasjon: matrisebasert implementering
adjacencyMatrixGraph.cpp      ← Implementasjon: adjasensmatrise
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

### `incidenceListGraph.h` / `incidencListGraph.cpp`
**Insidensliste-implementering** (Oppgave 2.1).  
Noder og kanter er begge objekter. Grafen er rettet, og insidens er modellert eksplisitt
ved at hver node holder separate lister for inn- og utgående kanter.

```
Node {
label
out → liste over utgående kanter
in → liste over inngående kanter
}

Edge {
label
from → startnode
to → målnode
}
```

Implementerer også **femmerregelen** (Oppgave 2.6) siden klassen eier heap-minne:

| Del av femmerregelen | Hvorfor |
|---|---|
| Destruktør | `= default` (ressurser eies av `std::unique_ptr`) |
| Kopikonstruktør | Dyp kopi av noder og kanter |
| Kopitildelingsoperator `=` | Implementert med *copy-and-swap* |
| Flyttekonstruktør | `= default` |
| Flyttetildelingsoperator `=` | `= default` |

---

### `adjacencyMatrixGraph.h` / `adjacencyMatrixGraph.cpp`
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