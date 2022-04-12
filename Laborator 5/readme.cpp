#include <bits/stdc++.h>
#include <ostream>

using namespace std;

// Simple Inheritance:

// am pus struct ca sa simplificam putin primul exemplu:
struct Nota {
    int value;
    string subject;
};

// aceasta este clasa de baza/parinte
class PersoanaEvaluata {
protected: // atributele din clasa de bază se pun sub eticheta protected:
    vector<Nota> note;
public:
    // constructor cu toti parametrii
    PersoanaEvaluata(const vector<Nota> &note) : note(note) {}
    // metoda comuna tuturor derivatelor
    double mean() {
        double sum = 0;
        for (auto nota: note) {
            sum += nota.value;
        }
        return sum / note.size();
    }
};

// acestea sunt clasele derivate:
class Pupil : public PersoanaEvaluata { // aceasta este sintaxa pentru „moștenire publică”
private:
    // adaugam noi atribute
    string cycle;
public:
    // constructori:
    // TODO va rog sa-i implementati si in clasele derivate, pentru antrenament:
    Pupil(const vector<Nota> &note, const string &cycle) : PersoanaEvaluata(note), cycle(cycle) {}

    // adaugam SI noi metode
    void showGradeSheet() {
        // TODO va afisa toate notele, sub forma
        //  materie: nota
        // e.g.
        //  subject: literature, value: 10
        //  subject: mathematics, value: 9
    }

    void gradesGroupedBySubject() {
        // TODO similar cu showGradeSheet, dar daca aveti doua note la aceiasi materie

        // hint: step-by-step
        //  puteti prima data crea un vector cu toate materiile (vector<string>)
        //  iar dupa aceea parcurgeti cu un prim for subiectele, iar cu un al doilea for parcurgeti toate notele si le afisati pe cele cu acea materie

        // e.g. afisare
        // literature: 10 9
        // mathematics: 8 7 20
    }
};


template<typename T>
// T va fi tipul generic
T add(T a, T b) {
    return a + b;
}

ostream &operator>>(vector<string> v, int n);
//
//int main() {
//    cout << add(2,3) << '\n'; // afiseaza 5
//    cout << add(2.3,3.1) << '\n'; // afiseaza 5.4
//    // merge, deoarece face conversie catre string
//    cout << add(string("234"), string("5")) << '\n'; // afiseaza 2345
//}

//template <typename T>
//istream& operator>>(istream& is, vector<T> v) {
//    for (auto &item : v) {
//        is >> item;
//    }
//    return is;
//}
//
//int main() {
//    vector<string> vs;
//    vector<Pupil> vp;
//    cin >> vs;
//    cin >> vp;
//}

// 2. iMag

class Gift {
protected:
    string name, giverName;
public:
    Gift(const string &name, const string &giverName) : name(name), giverName(giverName) {}

    virtual void offerGift(string receivedBy) {
        cout << "The gift named " << '"' << name << '"'
             << " was received by " << '"' << receivedBy << '"'
             << " thanks to the courtesy of " << '"' << giverName << '"'
             << '\n';
    }
    // ...
};

class GiftCard : public Gift {
private:
    int sum;
public:
    GiftCard(const string &name, const string &giverName, int sum) : Gift(name, giverName), sum(sum) {}

    // ...
    // adăugăm chiar aici o metodă cu același antet ca în clasa părinte + cuvântul cheie override
    // în CLion,
    //  dăm   Ctrl+O   ca să deschidem un meniu în care putem alege metoda din părinte,
    //  dupa care vom completa strict corpul noii metode generate.
    void offerGift(string receivedBy) override {
//        // inlocuim:
//        Gift::offerGift(receivedBy);
        // cu codul nostru:
        cout << "Congratulations " << '"' << receivedBy << '"'
             << "! You received a gift card of " << sum << "USD from "
             << '"' << giverName << '"'
             << '\n';
    }
};

class GiftHoliday : public Gift {
private:
    string location;
public:
    GiftHoliday(const string &name, const string &giverName, const string &location) : Gift(name, giverName),
                                                                                       location(location) {}
};

class GiftFavouriteProduct : public Gift {
private:
    string category;
public:
    GiftFavouriteProduct(const string &name, const string &giverName, const string &category) : Gift(name, giverName),
                                                                                                category(category) {}
};

//int main() {
//    Gift simpleGift("No Name", "Eleanor Roosevelt");
//    GiftCard card("Andrei Popescu", "Popescu Miruna", 300);
//    GiftHoliday holiday("Ibiza platita!", "Leonard Coste", "Ibiza, Spain");
//    GiftFavouriteProduct phone("Pentru tine", "Costache Leurdean", "Apple Products");
//
//    simpleGift.offerGift("Ioan");
//    card.offerGift("Persida");
//    holiday.offerGift("Romeo");
//    phone.offerGift("Caligula");
//}

// IO Base

class IoBase {
private:
public:
    // metoda citire
    virtual istream& read(istream& is) { // nu este nevoie de obiectul citit, pt ca avem this
        return is; // vom vedea ca in interfete deseori nu avem functionalitati
    }
    // metoda scriere
    virtual ostream& write(ostream& os) const { // nu este nevoie de obiectul citit, pt ca avem this
        return os; // vom vedea ca in interfete deseori nu avem functionalitati
    }
    // ...
    friend ostream &operator<<(ostream &os, const IoBase &base) {
        return base.write(os);
    }
    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }
};

class PongGame : public IoBase {
private:
    string player1, player2;
    // TODO apasam Ctrl+O   sau Generate -> Override Functions...
    //  dupa care selectam toate functiile posibile
    //  (sunt listate doar cele virtuale din părinte)
public:
    // ...
    istream &read(istream &is) override {
        cout << "player1: ";
        is >> player1;
        cout << "player2: ";
        is >> player2;
        return IoBase::read(is);
    }

    ostream &write(ostream &os) const override {
        cout << "player1: " << player1;
        cout << " player2: " << player2;
        return IoBase::write(os);
    }
};
class Student {

};

int main() {
    vector<Student> students;
    cin >> students;

}



// atentie la:
// mereu folosi protected la atribute, si public la mostenire. Va simplificati viata in aceast mod