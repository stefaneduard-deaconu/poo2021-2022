#include <iostream>
#include <string> // pentru tipul.. string    cine ar fi crezut?

using namespace std;

class Carte {

};

int main() {
    Carte c;
    c.citeste();
    c.afiseaza();
    // afiseaza titlul, numărul de pagini și pagina curentă, sub forma
    //   Cartea cu titlul "Pamflet" stă deschisă la pagina 29 din 103
    c.setPaginaCurenta(30);
    c.afiseaza();

    c.setPaginaCurenta(c.getPaginaMaxima() + 1);
    // cand rulam metoda de mai sus, ne va afisa mesajul
    // "Nu poți sări la pagina 104 din 103, deoarece nu există!"
}