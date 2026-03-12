# INF205 – Oversikt over kodebasen

> Gjelder både oppgavesett 2 og oppgavesett 3.

---

## Filstruktur

```
.
├── graph.h                     ← Abstrakt baseklasse (interface)
├── incidenceListGraph.h        ← Insidensliste – header
├── incidenceListGraph.cpp      ← Insidensliste – implementasjon
├── adjacencyMatrixGraph.h      ← Matrisebasert graf – header
├── adjacencyMatrixGraph.cpp    ← Matrisebasert graf – implementasjon
│
├── scc.h                       ← Tarjans SCC-algoritme – header
├── scc.cpp                     ← Tarjans SCC-algoritme – implementasjon
├── diamond.h                   ← Diamond path query – header
├── diamond.cpp                 ← Diamond path query – implementasjon
│
├── main.cpp                    ← Testprogram for oppgave 2 (uendret)
├── main_scc.cpp                ← Kommandolinjeprogram for oppgave 3.1
├── main_diamond.cpp            ← Kommandolinjeprogram for oppgave 3.2
│
├── graph_benchmark_scc.cpp     ← Grafgenerator for SCC-testing (gitt av lærer)
├── graph_benchmark.cpp         ← Grafgenerator for diamond-testing (gitt av lærer)
└── Makefile                    ← Byggesystem med alle demo-targets
```

---

## Hva løser hva?

| Fil | Oppgave(r) |
|-----|------------|
| `graph.h` | 2.3, 3.x (interface) |
| `incidenceListGraph.*` | 2.1, 2.2, 2.5, 2.6, 3.x |
| `adjacencyMatrixGraph.*` | 2.4, 2.2, 2.5, 2.6, 3.x |
| `scc.*` | 3.1 |
| `diamond.*` | 3.2 |
| `main.cpp` | 2.1–2.6 (test) |
| `main_scc.cpp` | 3.1 (kjørbart program) |
| `main_diamond.cpp` | 3.2 (kjørbart program) |
| `Makefile` | 3.3 |

---

## Arkitektur i et nøtteskall

```
          ┌─────────────────────────────────┐
          │          Graph  (abstrakt)       │
          │  insert_edge / disconnect /      │
          │  remove_node / write / read /    │
          │  clear / nodes / out_edges /     │
          │  successors                      │
          └──────────────┬──────────────────┘
                         │ arver
           ┌─────────────┴────────────┐
           ▼                          ▼
  IncidenceGraph              MatrixGraph
  (linked struktur)           (2D-vektor)

           │                          │
           └──────────┬───────────────┘
                      │ bruker Graph&
          ┌───────────┴───────────┐
          ▼                       ▼
     tarjan_scc()           diamond_query()
     (scc.cpp)              (diamond.cpp)
```

Algoritmene i oppgave 3 jobber **kun** mot `Graph&`-interfacet og vet ikke om de bruker
`IncidenceGraph` eller `MatrixGraph`. Det er poenget med den abstrakte baseklassen.
