#include <iostream>

#include "util/IoBase.h"
#include "util/functions.h"

using namespace std;

class Fraction : public IoBase {
protected:
    int a, b;
public:
    // constructori
    Fraction(int a, int b) : a(a), b(b) {}

    Fraction() {}

    // IoBase - overrided functions
    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "a: ";
        is >> a;
        cout << "b: ";
        is >> b;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout << "a: " << a;
        cout << ", b: " << b;
        return os;
    }
};

class IrrationalFraction : public Fraction {
private:
    // adaugam si radicalul dintr-un numar real
    double underSqrt;
public:
    // constructori:


    // IoBase - overrided functions

};

// Vom implementa cele doua clase
// Vom implementa <
// TODO aici editorul are un feature fain, genereaza toti op >, < etc

/*
Exemplu input:

2 3         -> citim fractia 2/3
1 2 2       -> citim fractia 1/2*sqrt(2)

Ca indiciu, vom avea 2/3 < 1/2*sqrt(2).
*/

// functie catre clasa de baza:
// TODO testati ce se intampla daca eliminati ampersand-ul
void show(const Fraction f) {
    cout << "Fractia este: " << f << '\n';
}

int main() {
    // level 0: constructori si operatori de afisare
    Fraction f1(2,3);
    IrrationalFraction f2(1,2,2);

//    // TODO Level 1: operator de citire
//    cin >> f1;
//    cin >> f2;
//    cout << f1 << " si " << f2;

//    // TODO level 2: Operator supraincarcat cu clase diferite
//    if (f1 < f2) {
//        cout << f1 << " < " << f2 << '\n';
//    } else {
//        cout << f2 << " < " << f1 << '\n';
//    }

//    // TODO Level 3: operatori si metode
//    cout << f1 - f2 << '\n';
//    // TODO Intrebari spre rezolvare:
//    //  -----------------------------
//    // TODO Cand scadem doua fractii, una de forma a/b si cealalta a/b*sqrt(c),
//    //      la ce forma ajungem?

    // Aveti deja implementata functia globala show(Fraction f).
    // TODO Ce se intampla cand urmatoarele 2 linii de cod?
    show(f1);
    show(f2);
    // TODO dar daca adaugam & la parametrul din show?
}