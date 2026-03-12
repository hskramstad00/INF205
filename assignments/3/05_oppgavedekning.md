# Oppgavedekning – hvordan alle krav er besvart

---

## Oppgavesett 2

### 2.1 – Insidensliste-implementasjon

**Krav:** Linked data structure med Node- og Edge-objekter, rettet graf, unike
nodelabels, ikke-unike kantelabels, selvlooper og multiple kanter mellom samme par.

**Besvart i:** `incidenceListGraph.h/.cpp`

Hvert `Node`-objekt holder to lister: `out` (utgående kanter) og `in` (inngående).
Hvert `Edge`-objekt holder pekere til `from`-node og `to`-node, pluss kantetiketten.
`insert_edge(a, label, b)` oppretter node-objekter for `a` og/eller `b` automatisk
hvis de ikke finnes, via `get_or_create_node_()`.

---

### 2.2 – Fil-I/O

**Krav:** Lese og skrive i formatet `nodeA etikett nodeB.` (én kant per linje,
avsluttet med punktum).

**Besvart i:** `read()` og `write()` i begge grafklasser.

```cpp
// Write: én linje per kant
os << from->label << " " << edge->label << " " << to->label << ".\n";

// Read: tok-for-tok, fjern eventuell punktum fra siste token
while (is >> a >> el >> b) {
    if (!b.empty() && b.back() == '.') b.pop_back();
    insert_edge(a, el, b);
}
```

---

### 2.3 – Abstrakt klasse som interface

**Krav:** Abstrakt baseklasse `Graph` med pure virtual-metoder. Begge
implementasjoner arver og overskriver med `override`.

**Besvart i:** `graph.h`, samt `override`-deklarasjonene i begge `.h`-filer.

`main.cpp` demonstrerer polymorfisme ved å bruke `Graph*` for å peke på et
`IncidenceGraph`-objekt.

---

### 2.4 – Matrisebasert implementasjon

**Krav:** Tilsvarende implementasjon som bruker en adjacency-matrise der
`adjacency[i][j]` representerer kanter fra node `i` til node `j`. Må støtte
multiple kanter og ikke-unike kantetiketter.

**Besvart i:** `adjacencyMatrixGraph.h/.cpp`

Matrisen er `vector<vector<list<string>>>` – en `list<string>` per celle slik at
vi kan lagre flere kantetiketter mellom samme nodepar.

---

### 2.5 – Slette kanter og noder

**Krav:** `disconnect(a, b)` fjerner alle kanter fra `a` til `b`.
`remove_node(label)` fjerner en node og alle dens kanter. Begge skal fjerne
isolerte noder som oppstår.

**Besvart i:** `disconnect()` og `remove_node()` i begge grafklasser.

- `disconnect`: itererer `from->out` og kaller `remove_edge_()` for kanter til `b`
- `remove_node`: fjerner alle ut- og inngående kanter, deretter noden selv
- Begge kaller `cleanup_isolated_nodes_()` / `remove_isolated_nodes_()` til slutt

---

### 2.6 – Rule of five

**Krav:** Alle fem elementer av rule of five implementert.

**Besvart i:** `incidenceListGraph.cpp` (manuell), `adjacencyMatrixGraph.h` (default)

**IncidenceGraph** krever manuell kopi fordi interne pekere (Node*, Edge*)
ikke kan kopieres naivt – de ville peke på originalens objekter:

```
Kopikonstruktøren:
  1. Kopier alle Node-objekter, bygg map: gammel Node* → ny Node*
  2. Kopier alle Edge-objekter, slå opp ny from/to via mapen
  3. Oppdater out/in-listene til de nye Node-objektene
```

Kopitildelingsoperatoren bruker copy-and-swap-idiom.
Move-konstruktør og move-tildelingsoperator er `= default`.

**MatrixGraph** trenger ingen manuell implementasjon fordi
`vector<vector<list<string>>>` eier alt minnet og kopieres/flyttes korrekt
av standardbiblioteket.

---

## Oppgavesett 3

### 3.1 – Sterkt sammenhengende komponenter (Tarjans algoritme)

**Krav:** Implementer Tarjans algoritme. Les graf i triple-notasjon. Bruk abstrakt
interface. Støtte for verbose/silent mode via kommandolinjeflagg.

**Besvart i:** `scc.cpp/h` + `main_scc.cpp`

Algoritmen er implementert **iterativt** (ikke rekursivt) for å unngå stack overflow
på store grafer. En eksplisitt `call_stack` av `TarjanFrame`-objekter simulerer
rekursjonen, der hvert frame husker hvilken kant som behandles neste.

```bash
./scc -v graf.dat          # verbose
./scc -s graf.dat          # silent
./scc -m matrix graf.dat   # matriserepresentasjon
```

---

### 3.2 – Diamond-shaped paths

**Krav:** Finn alle nodepar `(ni, nj)` der det finnes både en sti med
etikettsekvens `r0 r2 r4...` og en sti med sekvens `r1 r3 r5...` fra `ni` til `nj`.
Les query fra fil.

**Besvart i:** `diamond.cpp/h` + `main_diamond.cpp`

For hvert startnode `ni` bruker `follow_path()` et frontier-sett som propageres
trinn for trinn langs de to sekvensene separat. Snittet av de to frontier-settene
på slutten gir gyldige `nj`-noder.

```bash
./diamond -v graf.dat query.dat
./diamond -s -m matrix graf.dat query.dat
```

---

### 3.3 – GNU make demo-targets

**Krav:** `make pro22`, `make pro25`, `make pro31`, `make pro32` skal fungere
og ikke ta uforholdsmessig lang tid.

**Besvart i:** `Makefile`

```makefile
make pro22   # Kjører ./graph (viser fil-I/O fra oppgave 2.2)
make pro25   # Kjører ./graph (viser disconnect/remove_node fra oppgave 2.5)
make pro31   # Genererer liten SCC-graf, kjører ./scc -v
make pro32   # Genererer liten knowledge graph, kjører ./diamond -v
```

Alle fire targets bygger avhengige programmer automatisk.

---

### 3.4 – Skalering og runtime-måling

**Krav:** Mål gjennomsnittlig tid for begge algoritmer kombinert med begge
datastrukturer, som funksjon av antall noder `n`. Analyser skalering.

**Delvis besvart i kode:** Begge programmer måler tid med
`std::chrono::high_resolution_clock` og skriver ut millisekunder.

For systematisk måling: kjør med `-s` (silent) og vari `n` med grafgeneratorene:

```bash
for n in 100 200 500 1000 2000 5000; do
    ./graph-benchmark-scc $n $((n*4)) scc_tmp.dat
    ./scc -s scc_tmp.dat
done
```

Diagrammer og analyse besvares i rapporten (oppgave 3.6).

---

### 3.5 – ER-diagram

**Krav:** ER-diagram over data/klasse-arkitekturen.

Tegnes for hånd eller i et verktøy (draw.io, Lucidchart, o.l.) som del av
rapporten. Se `01_oversikt.md` for ASCII-arkitekturoversikt som utgangspunkt.

---

### 3.6 – Rapport (PDF, maks 3 sider)

**Krav:** Kortfattet rapport med seksjoner 2.1–3.5.

Foreslått struktur:
- **Side 1:** Oppgave 2 (datastrukturer, rule of five, fil-I/O)
- **Side 2:** Oppgave 3.1–3.3 (algoritmer, arkitektur, kjøring)
- **Side 3:** Oppgave 3.4 (skaleringsdiagrammer) + 3.5 (ER-diagram)
