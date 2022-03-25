#include <bits/stdc++.h>

using namespace std;
class Coords {

};
class Queue {
    void clear(); // elimină toate elementele
    void isEmpty(); // returneaza true doar atunci cand coada nu are elemente
    Coords operator[](int i); // returneaza coordonatele din coada, aflate la un anumit indice. Afișează un mesaj corespunzător și returneaza coordonatele -1, -1 dacă nu există un element pe indicele i.
    Queue operator+=(Coords new); // adaugă la final noile coordonate și returnează o copie a noii cozi.
    Queue operator–-();  // elimină primul element din coadă
};