#include <iostream>
#include <string> // pentru tipul.. string    cine ar fi crezut?

using namespace std;


/*
 * 1.
 * Se cere să citim de la tastatură n bilete de avion.
 * Despre fiecare bilet stim ca este rezervat pe numele unui calator,
 *   și daca biletul are sau nu loc la clasa I
 *
 * Să se implementeze clasa Bilet, constructor, getter + setter (pentru nume calator),
 *   dupa care vom rezolva următoarele cerințe:
 *
 * a) Vom citi cele n bilete de avion. Pentru simplitate vom crea o metodă de citire a unui bilet,
 *    cu antetul   void citeste()
 *
 * b) Creați o funcție globală cu antetul:
 *
 *    void statisticaZboruri(int n, Bilet[] bilete);
 *
 *    Funcția va primi numărul de bilete, plus un array cu biletele și
 *     va afișa câte bilete sunt la clasa I și câte nu sunt la clasa I.
 *
 *
 *    Exemplu rulat:
 *
 *    statisticaZboruri(5, {Bilet("Popescu Leuraș", true),
 *                          Bilet("Manolescu Alexandra", true),
 *                          Bilet("Popescu Mănăila", false))
 *    va afișa
 *    Avem 2 bilete la clasa I, dar și 1 bilete la alte clase.
 *
 */

class Bilet {
private:
    string nume; // dacă nu ați mai folosit string, să îmi spuneți :)
    bool arePrimaClasa;
public:
    // constructori, getteri, setteri, tot ce avem nevoie :)
};

void statisticaZboruri(int n, Bilet bilete[]) {

}

int main() {
    // Completați voi codul pentru subpunctul a)



    // Exemplu pentru subpunctul b)

    Bilet bilete[] = {Bilet("Popescu Leuraș", true),
                      Bilet("Manolescu Alexandra", true),
                      Bilet("Popescu Mănăila", false)};
    statisticaZboruri(3, bilete);



    return 0;
}
