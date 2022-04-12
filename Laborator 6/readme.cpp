#include <bits/stdc++.h>

// sau daca nu avem bits/
//  putem include <memory>
#include <memory> // shared_ptr, make_shared

// includem interfata din laboratorul trecut
#include "IoBase.h"

// TODO am listat aici codul din exemple, ca sa il putem copia mai rapid in cazul ca folositi CLion

using namespace std;


class Chair : public IoBase {
protected:
    double price;
    string color;
public:
    Chair(double price, const string &color) : price(price), color(color) {}

    // Afisarea si citirea cu ajutorul functiilor virtuale va deveni mai utila astazi,
    //  deoarece am mostenit IoBase, in CLion folosim Ctrl+O pentru a implementa read/write
    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout << "price: " << price;
        cout << ", color: " << color;
        return os;
    }
};

class ArmChair : public Chair {
protected:
    string armRestMaterial;
public:
    ArmChair(double price, const string &color, const string &armRestMaterial) : Chair(price, color),
                                                                                 armRestMaterial(armRestMaterial) {}

    ostream &write(ostream &os) const override {
        Chair::write(os);
        cout << ", armRestMaterial: " << armRestMaterial;
        return os;
    }
};

class Sofa : public Chair {
private:
    int maxPeople, length;
public:
    Sofa(double price, const string &color, int maxPeople, int length) : Chair(price, color), maxPeople(maxPeople),
                                                                         length(length) {}

    ostream &write(ostream &os) const override {
        Chair::write(os);
        cout << ", maxPeople: " << maxPeople;
        cout << ", length: " << length;
        return os;
    }
};

class MassageChair : public ArmChair {
private:
    int cntLevels, cableLength;
public:
    MassageChair(double price, const string &color, const string &armRestMaterial, int cntLevels, int cableLength)
            : ArmChair(price, color, armRestMaterial), cntLevels(cntLevels), cableLength(cableLength) {}

    ostream &write(ostream &os) const override {
        ArmChair::write(os);
        cout << ", cntLevels: " << cntLevels;
        cout << ", cableLength: " << cableLength;
        return os;
    }
};

int main() {
    vector<shared_ptr<Chair> > allKindsOfChairs = {
            make_shared<ArmChair>(
                    ArmChair(200, "brown", "Metal") // valoarea de aici este pusa in noul "smart pointer"
            ),
            make_shared<Sofa>(
                    Sofa(790, "cream", 5, 6.7)
            ),
            make_shared<MassageChair>(
                    MassageChair(590, "silver", "Plastic", 3, 2.7)
            ),
    };
    for (auto chair: allKindsOfChairs) {
        // datele afisate o sa difere in numar,
        //  in functie de tipul de scaun:
        cout << *chair << '\n'; // * este folosit pentru a lua valoarea de la acel pointer
    }

    // citirea de la tastatura a unui nou Chair
    shared_ptr<Chair> newChair;
    int type;

    // Pasul 1: alegem tipul
    cout << "Choose chair type (0=simple,1=ArmChair,2=Sofa,3=Massage): ";
    cin >> type;

    // Pasul 2: cream pointer de tip potrivit.
    if (type == 0) {
        newChair = new Chair;
    } else if (type == 1){
        newChair = new ArmChair;
    } else if (type == 2){
        newChair = new Sofa;
    } else if (type == 3){
        newChair = new MassageChair;
    }

    // Pasul 3: citire virtuala
    cin >> *newChair;

    // BONUS: Avem nevoie de citirea de scaune in mai multe zone ale codului (e.g.: atat in main, cat si intr-o clasa magazin).
    //        Ce am putea implementa ca sa refolosim usor codul?


}

// 5 exercitii:

// 0.  mobila la reduceri
// 1. Un magazin de sucuri
// 2. Un magazin de produse diverse
// 3.

//int main() {
//
//
//    return 0;
//}
