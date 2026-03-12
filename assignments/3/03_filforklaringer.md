# Filforklaringer – hvordan hver fil fungerer

---

## `graph.h` – Det abstrakte interfacet

Definerer kontrakten som **begge** grafrepresentasjoner må oppfylle.
Ingen data er lagret her – alt er pure virtual (`= 0`).

```
Graph (abstrakt)
│
├── insert_edge(a, label, b)   ← legg til kant
├── disconnect(a, b)           ← fjern alle kanter a→b
├── remove_node(label)         ← fjern node + alle dens kanter
├── write(ostream)             ← skriv til fil/skjerm
├── read(istream)              ← les fra fil
├── clear()                    ← tøm hele grafen
│
├── nodes()                    ← [NYT oppg. 3] liste alle nodelabels
├── out_edges(node)            ← [NYT oppg. 3] alle utgående kanter
└── successors(node, label)    ← [NYT oppg. 3] etterfølgere via én etikett
```

Fordi algoritmene i oppgave 3 bare tar `Graph&` som parameter, er de
**helt uavhengige** av om det er en insidensliste eller matrise under.

---

## `incidenceListGraph.h/.cpp` – Linked data structure

### Intern datamodell

```
nodes_  ──► [Node "Oslo"]   out ──► [Edge*]  [Edge*]
             [Node "Bergen"] out ──► [Edge*]
             ...

edges_  ──► [Edge "fly"  from=Oslo   to=Bergen ]
             [Edge "tog"  from=Bergen to=Trondheim]
             ...

by_label_  ──► { "Oslo" → Node*, "Bergen" → Node*, ... }   (O(1) oppslag)
```

### Nøkkelvalg

| Aspekt | Løsning |
|--------|---------|
| Nodeoppsalg | `unordered_map<string, Node*>` → O(1) |
| Kantfjerning | Fjerner fra `from->out`, `to->in` og `edges_`-listen |
| Isolerte noder | `cleanup_isolated_nodes_()` kalles etter `disconnect`/`remove_node` |
| Kopihåndtering | Kopikonstruktør + kopitildelingsoperator manuelt implementert (pekerne må remappes) |
| Move | `= default` (flytter `unique_ptr`-listene) |

### Tidskompleksitet

| Operasjon | Kompleksitet |
|-----------|-------------|
| `insert_edge` | O(1) amortisert |
| `find_node_` | O(1) via hashmap |
| `disconnect` | O(grad til `a`) |
| `remove_node` | O(grad til noden) |
| `nodes()` | O(n) |
| `out_edges()` | O(grad til noden) |
| `successors()` | O(grad til noden) |

---

## `adjacencyMatrixGraph.h/.cpp` – Matrisebasert

### Intern datamodell

```
node_labels_  = ["Oslo", "Bergen", "Trondheim"]
                    0        1          2

adjacency_[i][j] = list<string>  ← kantetiketter fra node i til j

adjacency_[0][1] = {"fly", "buss"}   ← Oslo→Bergen: to kanter
adjacency_[1][2] = {"tog"}           ← Bergen→Trondheim: én kant
adjacency_[0][0] = {"fly"}           ← selvloop Oslo→Oslo
```

### Nøkkelvalg

| Aspekt | Løsning |
|--------|---------|
| Nodeoppsalg | Lineært søk O(n) – ingen hashmap |
| Matrisevekst | `find_or_create_node_()` utvider alle rader + legger til ny rad |
| Multiple kanter | `list<string>` per celle, ikke én bool |
| Isolerte noder | `remove_isolated_nodes_()` etter `disconnect`/`remove_node` |
| Rule of five | Alle fem `= default` – `vector<vector<list<string>>>` eier alt minnet |

### Tidskompleksitet

| Operasjon | Kompleksitet |
|-----------|-------------|
| `find_node_` | O(n) |
| `insert_edge` | O(n) pga. nodeoppsalg |
| `disconnect` | O(n) |
| `remove_node` | O(n²) (sletting av rad+kolonne) |
| `nodes()` | O(n) |
| `out_edges()` | O(n) – itererer hele raden |
| `successors()` | O(n · kanter per celle) |

---

## `scc.h/.cpp` – Tarjans algoritme

### Hva er en SCC?

En **sterkt sammenkoblet komponent** (SCC) er en maksimal mengde noder der
alle noder kan nå hverandre via rettede stier.

```
A ──► B ──► D
▲    │
└─── C

SCC 1: {A, B, C}  (syklus)
SCC 2: {D}        (ingen vei tilbake)
```

### Tarjans algoritme – kort

Algoritmen gjør én DFS og bruker to tall per node:
- `index`: når noden ble besøkt
- `lowlink`: laveste `index` nåbar via DFS-tre + én bakover-kant

Når `lowlink[v] == index[v]` etter at alle barn er ferdigbehandlet, er `v`
**roten av en SCC**. Da popper vi alle noder fra Tarjan-stacken ned til `v`.

### Iterativ implementasjon

Rekursiv Tarjan krasjer med stack overflow på store grafer (f.eks. 10 000+ noder).
Vi bruker derfor en **eksplisitt call-stack** av `TarjanFrame`-objekter:

```cpp
struct TarjanFrame {
    std::string node;
    std::vector<std::pair<std::string,std::string>> edges;  // snapshot av utgående kanter
    std::size_t edge_idx;  // hvilken kant vi jobber med nå
};
```

Når `edge_idx == edges.size()` er alle barn ferdigbehandlet → sjekk SCC-root.

### Retur

```cpp
std::vector<std::vector<std::string>> tarjan_scc(const Graph& g, bool verbose);
```

Returnerer en liste av SCCer. Hver SCC er en liste av nodelabels.
Rekkefølge: **reverse topologisk** (sink-SCCer først).

---

## `diamond.h/.cpp` – Diamond path query

### Problemet

Finn alle par `(ni, nj)` der det finnes:
- En sti `ni -[r0]→ ... -[r2m-2]→ nj`  (path1)
- En sti `ni -[r1]→ ... -[r2m-1]→ nj`  (path2)

```
        ──r0──► B ──r2──►
ni ──►  (                ) ──► nj   (diamond-form)
        ──r1──► C ──r3──►
```

### Algoritmen

Hjelpefunksjonen `follow_path(g, start, labels)` holder et **frontier-sett**:

```
frontier = {ni}
for each label in [r0, r2, r4, ...]:
    next = alle noder nåbar fra frontier via label
    frontier = next
return frontier   ← alle nj nåbare fra ni via den sekvensen
```

For hvert startnode `ni`:
1. `ends1 = follow_path(g, ni, path1)`
2. `ends2 = follow_path(g, ni, path2)`
3. `ends1 ∩ ends2` → gyldige `nj`-kandidater → legg til i resultat

### Query-filformat

```
r0 r2 r4.
r1 r3 r5.
```

To linjer, mellomrom-separerte etiketter, avsluttet med punktum.
Leses av `read_query(istream, path1, path2)`.

---

## `main_scc.cpp` og `main_diamond.cpp`

Kommandolinjeprogrammer som kobler alt sammen. De:
1. Parser kommandolinjeflagg
2. Oppretter enten `IncidenceGraph` eller `MatrixGraph` basert på `-m`-flagget
3. Leser grafen via `g->read()`
4. Kaller algoritmen
5. Skriver ut resultat + tid

Se [kjøring.md](./04_kjoring.md) for konkrete eksempler.
