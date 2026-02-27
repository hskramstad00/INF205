Bygg og kjør

Dette prosjektet implementerer en rettet graf med to representasjoner:
1) GraphIncidence: insidenslister (noder og kanter er objekter)
2) GraphMatrix: adjacensmatrise der hver celle inneholder en liste med kant-labels (støtter multikanter)

Begge implementasjoner følger samme grensesnitt i Graph.h.

Bygging (MSYS2/MinGW):
  mingw32-make clean
  mingw32-make

Kjøring:
  ./app.exe matrix <input.txt> <output.txt>
  ./app.exe incidence <input.txt> <output.txt>

Valgfrie operasjoner:
  ./app.exe matrix <input.txt> <output.txt> disconnect <A> <B>
  ./app.exe incidence <input.txt> <output.txt> remove_node <X>

Filformat:
Hver linje i input/output er:
  node_a_label edge_label node_b_label

Eksempel:
  A e1 B
  A e2 B
  B x B