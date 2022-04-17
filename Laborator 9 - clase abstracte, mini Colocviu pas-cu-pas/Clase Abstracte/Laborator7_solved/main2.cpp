#include <iostream>

#include "util/IoBase.h"
#include "util/functions.h"

using namespace std;

/**
 * TODO discutam despre metode virtual si object slicing pe un exemplu mai simplu
 *  pe care sigur il auziti si la seminar!
 *  .
 *  Avem clasa de baza CakeShape = o forma de tort despre care stim inaltimea,
 *   dar nu si baza (patrat, dreptunghi, etc)
 *  Chiar si asa, putem calcula volumul, cu ajutorul unei functii virtuale
 *   care va calcula aria bazei:
 */


// TODO clasa CakeShape este ABSTRACTA,
//  deoarece avem o functie pura virtuala: baseArea()
class CakeShape {
protected:
    double height;
public:
    // calculam volumul
    double volume() {
        return baseArea() * height;
    }

    // spunem ca aria bazei va fi calculata in copii,
    //  prin suprascrierea metodei virtuale:

    // TODO deoarece nu stim forma bazei, nu putem
    //  calcula aria, deci functia nu numar ca este virtuala,
    //  este si pura=FARA COD
    virtual double baseArea() = 0;

    // constructorii
    CakeShape(double height) : height(height) {}

    CakeShape() : height(0) {}
};

// Pentru fiecare dintre clasele de mai jos am:
//      * adaugat laturile/raza;
//      * generat constructorii cu parametrii;
//      * si am calculat aria bazei, prin suprascriere.

//n  TODO clasa RectangleCake nu mai este ABSTRACTA,
//  deoarece am implementat prin override functia pura
class SquareCake : public CakeShape {
private:
    double side;
public:
    double baseArea() override {
        return side * side;
    }

    SquareCake(double height, double side) : CakeShape(height), side(side) {}

};

// TODO clasa RectangleCake nu mai este ABSTRACTA,
//  deoarece am implementat prin override functia pura
class RectangleCake : public CakeShape {
private:
    double side1, side2;
public:
    // overrided functions:
    double baseArea() override {
        return side1 * side2;
    }

    // constructori
    RectangleCake(double height, double side1, double side2) : CakeShape(height), side1(side1), side2(side2) {}

    RectangleCake() : side1(0), side2(0) {}
};
const double PI = 3.1459;

// TODO clasa RectangleCake nu mai este ABSTRACTA,
//  deoarece am implementat prin override functia pura
class CircleCake : public CakeShape {
private:
    double radius;
public:
    // overrided functions:
    double baseArea() override {
        return PI * radius * radius;
    }

    // constructori
    CircleCake(double height, double radius) : CakeShape(height), radius(radius) {}

    CircleCake() : radius(0) {}
};


int main() {
    // pentru prima clasa, dar si o clasa copil:
    CakeShape cake(4);
    SquareCake cube(2, 2);
    
    cout << cake.volume() << '\n'; // 0
    cout << cube.volume() << '\n'; // 8

    // pentru clasele derivate
    SquareCake squareCake(4, 5);
    RectangleCake rectangleCake(1, 5, 2);
    CircleCake circleCake(1, 5);

    cout << squareCake.volume() << '\n'; //     100
    cout << rectangleCake.volume() << '\n'; //  10
    cout << circleCake.volume() << '\n'; //     78.6475

    return 0;
}