#include <bits/stdc++.h>
#include "IoBase.h"

using namespace std;

class Fruit : public IoBase {
private:
    string name, species;
public:
    Fruit() {}

    Fruit(const string &name, const string &species) : name(name), species(species) {}
};

class Juice : public IoBase {
private:
    double qty;
public:
    Juice() {}

    Juice(double qty) : qty(qty) {}

    // metoda virtuala
    virtual double quantity() const {
        return qty;
    }
};

class SimpleJuice : public Juice {
private:
    Fruit flavour;
public:
    SimpleJuice() {}

    SimpleJuice(double qty, const Fruit &flavour) : Juice(qty), flavour(flavour) {}
};

class MixedJuice : public Juice {
private:
    vector<Fruit> fruits;
public:
    MixedJuice() {}

    MixedJuice(double qty, const vector<Fruit> &fruits) : Juice(qty), fruits(fruits) {}
};

class IcedJuice : public MixedJuice {
private:
    double iceQty;
public:
    IcedJuice() {}

    IcedJuice(double qty, const vector<Fruit> &fruits, double iceQty) : MixedJuice(qty, fruits), iceQty(iceQty) {}

    // virtual methods:
    double quantity() const override {
        return Juice::quantity() + iceQty;
    }
};

//int main() {
//    vector<shared_ptr<Juice> > stock = {
//            make_shared<SimpleJuice>(
//                    SimpleJuice(550, Fruit("Apple", "Granny Smith"))
//            ),
//            make_shared<MixedJuice>(
//                    MixedJuice(
//                            560,
//                            {
//                                    Fruit("Apple", "Granny Smith"),
//                                    Fruit("Banana", "Musa balbisiana"),
//                            }
//                    )
//            ),
//            make_shared<IcedJuice>(
//                    IcedJuice(
//                            560,
//                            {
//                                    Fruit("Apple", "Granny Smith"),
//                                    Fruit("Banana", "Musa balbisiana"),
//                            },
//                            150
//                    )
//            ),
//    };
//
//    for (auto juice : stock) {
//        cout << juice->quantity() << ' ';
//    }
//
//
//}

int main() {
    vector<int> v = {1, 2, 3};
}