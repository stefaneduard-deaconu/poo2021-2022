#include <iostream>
#include <memory>
#include <vector>
#include "util/IoBase.h"

//#include <bits/stdc++.h>

using namespace std;

class Jucarie : public IoBase {
protected: // TODO mult mai bine decat private, ca sa le accesam in copii
    string denumire, tip;
    int volum;
    // ALt + INsert
    // Ctrl+O
public:
    istream &read(istream &is) override {
        IoBase::read(is);
        // 1. SHift+Alt+DblClick  to select names
        // 2. Shift+Alt+Click     to create cursors
        cout << "denumire: ";
        is >> denumire;
        cout << "tip: ";
        is >> tip;
        cout << "volum: ";
        is >> volum;
        return is; // pentru inlantuire, adica cin >> a >> b;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os << "Denumire: " << denumire;
        // ...
        return os;
    }
};

class Clasica : public Jucarie {
private:
    string material, culoare;
public:
    istream &read(istream &is) override {
        Jucarie::read(is);
        // ne ocupam STRICT de atributele din CLasica
        cout << "material: ";
        is >> material;
        cout << "culoare: ";
        is >> culoare;
        return is;
    }

    ostream &write(ostream &os) const override {
        return Jucarie::write(os);
    }
};

class  Educativa : public virtual Jucarie {
protected:
    string abilitateDezvoltata;
};

class Electronica : public virtual Jucarie {
protected:
    int numarBaterii;
};

class Moderna : public Educativa, public Electronica {
    string brand, model;
    // TODO numarul de baterii sa fie 1
    //  -> parametrii default
public:
    Moderna(...) : Electronica(1) {} // transmitem 1 la numarul de baterii
};

// class Copil de baza
//    -->  Cuminte, Neastamparat

class Copil : public IoBase{
protected:
    string nume, prenume, adresa;
    int varsta, numarFapteBune;
    vector<shared_ptr<Jucarie> > jucarii;
};
class CopilCuminte : public Copil{
private:
    int numarDulciuri;
};
class CopilNeastamparat : public Copil{

private:
    int numarCarbuni;
};
// TODO Pentru orice copil cuminte, numărul de fapte bune este cel puțin 10, în caz contrar, programul realizat trebuie să afişeze un mesaj corespunzător şi să îi permită lui Moş Crăciun să reintroducă valoarea.


// Meniu

// Ati lucrat meniuri din Lab 8?
// Mai exact CrudMenu?

// functie de citire a unui copil, ca shared_ptr

shared_ptr<Copil> citireCopil() {
    // citim tipul de copil
    cout << "Tipul Copil (1=cuminte, 2=neastamparat): ";
    int tip;
    cin >> tip;

    // alocam shared_ptr ul
    shared_ptr<Copil> c;
    if (tip == 1) {
        c = make_shared<CopilCuminte>();
    } else if (tip == 2) {
        c = make_shared<CopilNeastamparat>();
    }

    // citim virtual pe shared_ptr<Copil> pe care l-am alocat
    cin >> *c;

}

class Meniu {
private:
    vector<shared_ptr<Copil> > copii;
public:
    // afisam toate optiunile
    void listeazaOptiuni() {
        cout << "1. Citire n copii cu cate m cadouri" << '\n';
        cout << "2. Citire n copii cu cate m cadouri" << '\n';
        cout << "7. Stop" << '\n';

    }

    // alegem o optiune

    int alegeOptiune() {
        int option;

        while (option < 1 && option > 7 ) {
            cout << "Alegeti optiunea intre 1 si 7!" << '\n';

            cout << "Option: ";
            cin >> option;
        }
        return option;
    }

    // un main loop
    void run() {
        // meniul interactiv
        while(true) {
            listeazaOptiuni();
            // alegem optiune
            int option = alegeOptiune();
            if (option == 1) {
                citireCopii();
            } else if (option == 2) {
                afisareCopii();
            } else if (option == 7) {
                break;
            }
        }
    }

    // pentru fiecare optiune cream o functie

    void citireCopii() {
        int n;
        cin >> n;
        // citirea a n copii

//        copii.clear();

        for (int i = 0; i < n; ++i) {
            copii.push_back(
                    citireCopil()
                    );
        }
    }

    void afisareCopii() {
        // afisarea copiilor:
        cout << "Cei " << '\n' << " copii sunt:" << '\n';
        for (int i = 0; i < copii.size(); ++i) {
            cout << *copii[i] << '\n';
        }

    }



};

 int main() {
    return 0;
}
