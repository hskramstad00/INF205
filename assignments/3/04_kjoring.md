# Kjøring – hvordan bygge og kjøre alt

---

## Bygg alt på én gang

```bash
make all
```

Dette kompilerer og linker følgende programmer:

| Program | Hva det er |
|---------|------------|
| `graph` | Testprogram for oppgave 2 |
| `scc` | SCC-analyse (oppgave 3.1) |
| `diamond` | Diamond path query (oppgave 3.2) |
| `generate-graph` | Grafgenerator for diamond-testing |
| `graph-benchmark-scc` | Grafgenerator for SCC-testing |

> **Krav:** g++ med C++17-støtte (`-std=c++17`). Kompilerer uten warnings.

---

## Demo-targets (oppgave 3.3)

Disse fire targets kan kjøres direkte med `make`:

```bash
make pro22   # Oppgave 2.2: skriver graf til fil og leser den tilbake
make pro25   # Oppgave 2.5: disconnect og remove_node demo
make pro31   # Oppgave 3.1: genererer SCC-testgraf og kjører Tarjan
make pro32   # Oppgave 3.2: genererer knowledge graph og kjører diamond query
```

Hvert target bygger automatisk de nødvendige programmene hvis de ikke finnes.
Du trenger ikke kjøre `make all` først.

---

## Manuell kjøring – SCC

```bash
# Standard: verbose output, IncidenceGraph
./scc graf.dat

# Silent mode (kun statistikk + tid)
./scc -s graf.dat

# Bruk matriserepresentasjon
./scc -m matrix graf.dat

# Kombinert: verbose + matrise
./scc -v -m matrix graf.dat
```

### Eksempel på output (verbose)

```
Graph loaded from "scc08.dat" using incidence representation.
Nodes: 16

Strongly connected components (6 total):
  SCC 1 [1 node(s)]: n5
  SCC 2 [1 node(s)]: n11
  SCC 3 [11 node(s)]: n9, n4, n10, n2, n6, n15, n13, n3, n7, n8, n12
  ...

Summary: 6 SCC(s) found.
  Trivial (size 1): 5
  Non-trivial:      1
  Time: 0.030 ms
```

---

## Manuell kjøring – Diamond query

```bash
# Standard: verbose, IncidenceGraph
./diamond graf.dat query.dat

# Silent (kun antall par + tid)
./diamond -s graf.dat query.dat

# Matriserepresentasjon
./diamond -m matrix graf.dat query.dat
```

### Query-filformat

Filen må ha to linjer med mellomrom-separerte kantetiketter, avsluttet med `.`:

```
r0 r2 r4.
r1 r3 r5.
```

- Linje 1: etiketter for sti 1 (`r0`, `r2`, `r4`, ...)
- Linje 2: etiketter for sti 2 (`r1`, `r3`, `r5`, ...)
- Begge stier må ha **samme lengde**

### Eksempel på output (verbose)

```
Graph:  kb.dat (1000 nodes, incidence representation)
Path 1 labels (3): r0 r2 r4
Path 2 labels (3): r1 r3 r5

Diamond pairs (12 found):
  n0 -> n48
  n3 -> n51
  ...

Diamond pairs found: 12
Time: 1.42 ms
```

---

## Grafgeneratorer

### Generer SCC-testgraf

```bash
./graph-benchmark-scc <antall_noder> <antall_kanter> <utfil>

# Eksempel: 256 noder, 1024 kanter
./graph-benchmark-scc 256 1024 scc256.dat
./scc -v scc256.dat
```

### Generer knowledge graph + query

```bash
./generate-graph <antall_noder> <path_lengde> <grafil> <queryfil>

# Eksempel: 1000 noder, path-lengde 3
./generate-graph 1000 3 kb1000.dat query3.dat
./diamond -v kb1000.dat query3.dat
```

---

## Rydding

```bash
make clean   # fjerner .o-filer og kompilerte programmer, samt genererte testfiler
```

---

## Flagg-oversikt

| Flagg | Gjelder | Effekt |
|-------|---------|--------|
| `-v` | `scc`, `diamond` | Verbose – skriv ut alle komponenter/par (standard) |
| `-s` | `scc`, `diamond` | Silent – skriv kun oppsummering og tid |
| `-m incidence` | `scc`, `diamond` | Bruk IncidenceGraph (standard) |
| `-m matrix` | `scc`, `diamond` | Bruk MatrixGraph |
