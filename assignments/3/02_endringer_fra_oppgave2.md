# Endringer fra oppgavesett 2 til oppgavesett 3

Alle filer fra oppgave 2 er **beholdt og uendret i logikk**. Det som ble lagt til er
minimalt og følger nøye av hva algoritmene i oppgave 3 trenger.

---

## 1. `graph.h` – tre nye pure virtual-metoder

Den abstrakte baseklassen fikk tre nye metoder:

```cpp
// Returnerer etikettene til alle noder i grafen
virtual std::vector<std::string> nodes() const = 0;

// Returnerer alle utgående kanter som {kantetikett, målnode}-par
virtual std::vector<std::pair<std::string,std::string>>
out_edges(const std::string& node) const = 0;

// Returnerer alle etterfølgere nåbar via en kant med gitt etikett
virtual std::vector<std::string>
successors(const std::string& node, const std::string& edge_label) const = 0;
```

**Hvorfor akkurat disse?**

| Metode | Brukes av |
|--------|-----------|
| `nodes()` | Tarjan starter DFS fra alle noder → trenger en liste over alle |
| `out_edges()` | Tarjan traverserer alle nabokanter fra en node |
| `successors()` | Diamond-algoritmen følger én spesifikk kantetikett om gangen |

Alle andre metoder fra oppgave 2 (`insert_edge`, `disconnect`, `remove_node`,
`write`, `read`, `clear`) er **uendret**.

---

## 2. `incidenceListGraph.cpp` – tre nye metoder lagt til

```cpp
std::vector<std::string> IncidenceGraph::nodes() const {
    std::vector<std::string> result;
    for (const auto& n : nodes_) result.push_back(n->label);
    return result;
}

std::vector<std::pair<std::string,std::string>>
IncidenceGraph::out_edges(const std::string& node) const {
    // iterate over n->out, lag {edge->label, edge->to->label}-par
}

std::vector<std::string>
IncidenceGraph::successors(const std::string& node,
                            const std::string& edge_label) const {
    // iterate over n->out, filtrer på edge->label == edge_label
}
```

Resten av `incidenceListGraph.cpp` er identisk med oppgave 2-innlevering.

---

## 3. `adjacencyMatrixGraph.cpp` – tre nye metoder lagt til

```cpp
std::vector<std::string> MatrixGraph::nodes() const {
    return node_labels_;   // returnerer vektoren direkte
}

std::vector<std::pair<std::string,std::string>>
MatrixGraph::out_edges(const std::string& node) const {
    // iterer rad[i], samle alle {label, node_labels_[j]}-par
}

std::vector<std::string>
MatrixGraph::successors(const std::string& node,
                         const std::string& edge_label) const {
    // iterer rad[i], filtrer på label == edge_label
}
```

---

## 4. Navnerydding i `adjacencyMatrixGraph`

Private member-variabler ble omdøpt for å følge understrek-konvensjonen:

| Gammelt navn | Nytt navn |
|-------------|-----------|
| `node_labels` | `node_labels_` |
| `adjacency` | `adjacency_` |
| `find_node(...)` | `find_node_(...)` |
| `find_or_create_node(...)` | `find_or_create_node_(...)` |
| `remove_isolated_nodes()` | `remove_isolated_nodes_()` |

Dette er ikke funksjonelt, men gjør det lettere å skille private felt fra
lokale variabler på et blikk.

---

## 5. Nye filer (alt nytt i oppgave 3)

| Ny fil | Hva den inneholder |
|--------|---------------------|
| `scc.h` | Deklarasjon av `tarjan_scc()` |
| `scc.cpp` | Implementasjon av Tarjans algoritme (iterativ) |
| `diamond.h` | Deklarasjon av `diamond_query()` og `read_query()` |
| `diamond.cpp` | Implementasjon av diamond path query |
| `main_scc.cpp` | Kjørbart program for SCC med kommandolinjeflagg |
| `main_diamond.cpp` | Kjørbart program for diamond query |
