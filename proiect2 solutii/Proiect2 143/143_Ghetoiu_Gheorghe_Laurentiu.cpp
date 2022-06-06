#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Preluat din laboratorul 7
class IoBase {
private:
public:
    // metoda citire
    virtual istream &read(istream &is) { // nu este nevoie de obiectul citit, pt ca avem this
        return is; // vom vedea ca in interfete deseori nu avem functionalitati
    }

    // metoda scriere
    virtual ostream &write(ostream &os) const { // nu este nevoie de obiectul citit, pt ca avem this
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


class Data : public IoBase {
    int zi, luna, an;
public:
    Data();

public:
    Data(int zi, int luna, int an);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

};

Data::Data(int zi, int luna, int an) : zi(zi), luna(luna), an(an) {}

Data::Data() {}

istream &Data::read(istream &is) {
    IoBase::read(is);
    cout << "zi:";
    is >> zi;
    is.get();
    cout << "luna: ";
    is >> luna;
    is.get();
    cout << "an: ";
    is >> an;
    is.get();
    return is;
}

ostream &Data::write(ostream &os) const {
    IoBase::write(os);
    os << zi << "." << luna << "." << an;
    return os;
}

class Virus : public IoBase {
protected:
    static double rating;
    Data dataDeInfectare;
    string metodaDeInfectare;
    vector<string> registrii;
public:
    virtual double calculeazaRating() {};

    Virus() : metodaDeInfectare("unknown") {}

    Virus(const Data &dataDeInfectare, const vector<string> &registrii, const string &metodaDeInfectare = "unknown");

    static double getRating();

    const Data &getDataDeInfectare() const;

    const string &getMetodaDeInfectare() const;

    const vector<string> &getRegistrii() const;

    static void setRating(double rating);

    void setDataDeInfectare(const Data &dataDeInfectare);

    void setMetodaDeInfectare(const string &metodaDeInfectare);

    void setRegistrii(const vector<string> &registrii);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

double Virus::rating = 0;

Virus::Virus(const Data &dataDeInfectare, const vector<string> &registrii, const string &metodaDeInfectare)
        : dataDeInfectare(dataDeInfectare), metodaDeInfectare(metodaDeInfectare), registrii(registrii) {}

double Virus::getRating() {
    return rating;
}

const Data &Virus::getDataDeInfectare() const {
    return dataDeInfectare;
}

const string &Virus::getMetodaDeInfectare() const {
    return metodaDeInfectare;
}

const vector<string> &Virus::getRegistrii() const {
    return registrii;
}

void Virus::setRating(double rating) {
    Virus::rating = rating;
}

void Virus::setDataDeInfectare(const Data &dataDeInfectare) {
    Virus::dataDeInfectare = dataDeInfectare;
}

void Virus::setMetodaDeInfectare(const string &metodaDeInfectare) {
    Virus::metodaDeInfectare = metodaDeInfectare;
}

void Virus::setRegistrii(const vector<string> &registrii) {
    Virus::registrii = registrii;
}

istream &Virus::read(istream &is) {
    IoBase::read(is);
    cout << "data de infectare:";
    is >> dataDeInfectare;
    cout << "metoda de infectare: ";
    cout << "daca metoda de infectare se cunoaste introduceti 1, altfel 0";
    int seCunoaste = 0;
    cin >> seCunoaste;
    cin.get();
    if (seCunoaste == 1) {
        cout<<"metoda: ";
        getline(is, metodaDeInfectare);
    }
    cout << "registrii: ";
    while (true) {
        cout << "Introduce registrul modificat sau 0 pentru a te opri: ";
        string registru;
        getline(is, registru);
        if (registru.compare("0")==0)
            break;
        registrii.push_back(registru);
    }
    return is;
}

ostream &Virus::write(ostream &os) const {
    IoBase::write(os);
    os << "data de infectare: " << dataDeInfectare << ", metoda de infectare: " << metodaDeInfectare;
    os << " ,registrii: ";
    for (auto registru: registrii) {
        os << registru << ", ";
    }
    return os;
}

class Rootkit : public virtual Virus {
protected:
    vector<string> importuri;
    vector<string> stringuriSemnificative;
public:
    Rootkit();

    Rootkit(const Data &dataDeInfectare, const string &metodaDeInfectare, const vector<string> &registrii,
            const vector<string> &importuri, const vector<string> &stringuriSemnificative);

    const vector<string> &getImporturi() const;

    void setImporturi(const vector<string> &importuri);

    const vector<string> &getStringuriSemnificative() const;

    void setStringuriSemnificative(const vector<string> &stringuriSemnificative);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

Rootkit::Rootkit() {}

Rootkit::Rootkit(const Data &dataDeInfectare, const string &metodaDeInfectare, const vector<string> &registrii,
                 const vector<string> &importuri, const vector<string> &stringuriSemnificative) : Virus(dataDeInfectare,
                                                                                                        registrii,
                                                                                                        metodaDeInfectare),
                                                                                                  importuri(importuri),
                                                                                                  stringuriSemnificative(
                                                                                                          stringuriSemnificative) {}

const vector<string> &Rootkit::getImporturi() const {
    return importuri;
}

void Rootkit::setImporturi(const vector<string> &importuri) {
    Rootkit::importuri = importuri;
}

const vector<string> &Rootkit::getStringuriSemnificative() const {
    return stringuriSemnificative;
}

void Rootkit::setStringuriSemnificative(const vector<string> &stringuriSemnificative) {
    Rootkit::stringuriSemnificative = stringuriSemnificative;
}

istream &Rootkit::read(istream &is) {
    Virus::read(is);
    while (true) {
        cout << "Introduceti importurile sau 0 pentru a va opri:";
        string s;
        getline(is, s);
        if (s.compare("0")==0)
            break;
        importuri.push_back(s);
    }
    while (true) {
        cout << "Introduceti stringurile semnificative sau 0 pentru a va opri:";
        string s;
        getline(is, s);
        if (s.compare("0")==0)
            break;
        stringuriSemnificative.push_back(s);
    }
    return is;
}

ostream &Rootkit::write(ostream &os) const {
    Virus::write(os);
    cout << "Importuri: ";
    for (auto s: importuri)
        os << s << ", ";
    cout << "Stringuri semnificative: ";
    for (auto s: stringuriSemnificative)
        os << s << ", ";
    return os;
}

class Keylogger : public virtual Virus {
protected:
    vector<string> functii;
    vector<string> tasteSpeciale;
public:
    Keylogger();

    Keylogger(const Data &dataDeInfectare, const string &metodaDeInfectare, const vector<string> &registrii,
              const vector<string> &functii, const vector<string> &tasteSpeciale);

    const vector<string> &getFunctii() const;

    void setFunctii(const vector<string> &functii);

    const vector<string> &getTasteSpeciale() const;

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    void setTasteSpeciale(const vector<string> &tasteSpeciale);
};

Keylogger::Keylogger() {}

Keylogger::Keylogger(const Data &dataDeInfectare, const string &metodaDeInfectare, const vector<string> &registrii,
                     const vector<string> &functii, const vector<string> &tasteSpeciale) : Virus(dataDeInfectare,
                                                                                                 registrii,
                                                                                                 metodaDeInfectare),
                                                                                           functii(functii),
                                                                                           tasteSpeciale(
                                                                                                   tasteSpeciale) {}

const vector<string> &Keylogger::getFunctii() const {
    return functii;
}

void Keylogger::setFunctii(const vector<string> &functii) {
    Keylogger::functii = functii;
}

const vector<string> &Keylogger::getTasteSpeciale() const {
    return tasteSpeciale;
}

void Keylogger::setTasteSpeciale(const vector<string> &tasteSpeciale) {
    Keylogger::tasteSpeciale = tasteSpeciale;
}

istream &Keylogger::read(istream &is) {
    Virus::read(is);
    while (true) {
        cout << "Introduceti functiile  sau 0 pentru a va opri:";
        string s;
        getline(is, s);
        if (s.compare("0")==0)
            break;
        functii.push_back(s);
    }
    while (true) {
        cout << "Introduceti tastele speciale  sau 0 pentru a va opri:";
        string s;
        getline(is, s);
        if (s.compare("0")==0)
            break;
        tasteSpeciale.push_back(s);
    }
    return is;
}

ostream &Keylogger::write(ostream &os) const {
    Virus::write(os);
    os << "Functii: ";
    for (auto s: functii)
        os << s << ", ";
    os << "Taste speciale";
    for (auto s: tasteSpeciale)
        os << s << ", ";
    return os;
}

class KernelKeylogger : public virtual Keylogger, public virtual Rootkit {
private:
    bool ascundeFisiere, ascundeRegistrii;
public:
    KernelKeylogger();

    bool isAscundeFisiere() const;

    void setAscundeFisiere(bool ascundeFisiere);

    bool isAscundeRegistrii() const;

    void setAscundeRegistrii(bool ascundeRegistrii);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;


};

KernelKeylogger::KernelKeylogger() {}

bool KernelKeylogger::isAscundeFisiere() const {
    return ascundeFisiere;
}

void KernelKeylogger::setAscundeFisiere(bool ascundeFisiere) {
    KernelKeylogger::ascundeFisiere = ascundeFisiere;
}

bool KernelKeylogger::isAscundeRegistrii() const {
    return ascundeRegistrii;
}

void KernelKeylogger::setAscundeRegistrii(bool ascundeRegistrii) {
    KernelKeylogger::ascundeRegistrii = ascundeRegistrii;
}

istream &KernelKeylogger::read(istream &is) {
    Rootkit::read(is);
    while (true) {
        cout << "Introduceti functiile  sau 0 pentru a va opri:";
        string s;
        getline(is, s);
        if (s.compare("0")==0)
            break;
        functii.push_back(s);
    }
    while (true) {
        cout << "Introduceti tastele speciale  sau 0 pentru a va opri:";
        string s;
        getline(is, s);
        if (s.compare("0")==0)
            break;
        tasteSpeciale.push_back(s);
    }
    cout << "ascunde fisiere";
    cin >> ascundeFisiere;
    cin.get();
    cout << "ascunde registrii";
    cin >> ascundeRegistrii;
    cin.get();
    return is;
}

ostream &KernelKeylogger::write(ostream &os) const {
    Rootkit::write(os);
    os << "Functii: ";
    for (auto s: functii)
        os << s << ", ";
    os << "Taste speciale";
    for (auto s: tasteSpeciale)
        os << s << ", ";
    os << "ascunde fisiere: " << ascundeFisiere;
    os << ", ascunde registrii: " << ascundeRegistrii;
    return os;
}


class Ransomware : public Virus {
private:
    double ratingObfuscare;
public:
    Ransomware();

    Ransomware(const Data &dataDeInfectare, const string &metodaDeInfectare, const vector<string> &registrii,
               double ratingObfuscare);

    double getRatingObfuscare() const;

    void setRatingObfuscare(double ratingObfuscare);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

Ransomware::Ransomware() {}

Ransomware::Ransomware(const Data &dataDeInfectare, const string &metodaDeInfectare, const vector<string> &registrii,
                       double ratingObfuscare) : Virus(dataDeInfectare, registrii, metodaDeInfectare),
                                                 ratingObfuscare(ratingObfuscare) {}

double Ransomware::getRatingObfuscare() const {
    return ratingObfuscare;
}

void Ransomware::setRatingObfuscare(double ratingObfuscare) {
    Ransomware::ratingObfuscare = ratingObfuscare;
}

istream &Ransomware::read(istream &is) {
    Virus::read(is);
    cout << "rating obfuscare";
    is >> ratingObfuscare;
    is.get();
    return is;
}

ostream &Ransomware::write(ostream &os) const {
    Virus::write(os);
    os << ", rating obfuscare:";
    os << ratingObfuscare;
    return os;
}

class Computer : public IoBase {
    static int idCurent;
    int idUnic;
    vector<shared_ptr<Virus>> malware;
    double ratingFinal;
public:
    Computer();

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    int getId() const;

    void setId(int id);

    const vector<shared_ptr<Virus>> &getMalware() const;

    void setMalware(const vector<shared_ptr<Virus>> &malware);

    double getRatingFinal() const;

    void setRatingFinal(double ratingFinal);

};

int Computer::idCurent = 0;


istream &Computer::read(istream &is) {
    IoBase::read(is);
    while (true) {
        shared_ptr<Virus> virus;
        cout
                << "Introduce tipul de malware sau 0 pentru a te opri(1. Rootkit, 2. Keylogger, 3. Kernel-Keylogger, 4. Ransomware): ";
        int optiune;
        cin >> optiune;
        cin.get();
        if (optiune == 0)
            break;
        if (optiune == 1)
            virus = make_shared<Rootkit>();
        if (optiune == 2)
            virus = make_shared<Keylogger>();
        if (optiune == 3)
            virus = make_shared<KernelKeylogger>();
        if (optiune == 4)
            virus = make_shared<Ransomware>();
        cin >> *virus;
        malware.push_back(virus);
    }

    return is;
}

ostream &Computer::write(ostream &os) const {
    IoBase::write(os);
    os<<"ID computer: "<<idCurent;
    for (auto virus: malware) {
        os << *virus << ", ";
    }

    return os;
}

int Computer::getId() const {
    return idUnic;
}

void Computer::setId(int id) {
    Computer::idUnic = id;
}

const vector<shared_ptr<Virus>> &Computer::getMalware() const {
    return malware;
}

void Computer::setMalware(const vector<shared_ptr<Virus>> &malware) {
    Computer::malware = malware;
}

double Computer::getRatingFinal() const {
    return ratingFinal;
}

void Computer::setRatingFinal(double ratingFinal) {
    Computer::ratingFinal = ratingFinal;
}

Computer::Computer() {
    idUnic = idCurent;
    idCurent++;
}


class Menu {
private:
    vector<Computer> computers;
public:
    void optiuni() {
        cout << "1. Citeste un nou calculator\n";
        cout << "2. Afiseaza informatii pentru fiecare calculator\n";
        cout << "3. Afiseaza informatii pentru fiecare calulator ordonate dupa ratingul final\n";
        cout << "4. Afisesaza primele k calculatoare ordonate dupa ratingul final\n";
        cout << "5. Afiseaza procentul de computere infectate din firma\n";
        cout << " 6. Exit\n";
    }

    int alegeOptiune() {
        cout << "Pentru a alege o optiune scrie doar indicele unei dintre urmatoarele:\n";
        optiuni();
        int optiune;
        cout << "Optiune: ";
        cin >> optiune;
        cin.get();
        return optiune;
    }

    void citesteCalculatoare() {
        Computer comp;
        cin >> comp;
        computers.push_back(comp);
    }

    void afiseazaCalculatoare() {
        int i=0;
        for (auto comp: computers) {
            cout << i << ": " << comp << endl;
            i++;
        }
    }

    void mainLoop() {
        while (true) {
            int optiune;
            optiune = alegeOptiune();
            if (optiune == 1)
                citesteCalculatoare();
            if (optiune == 2)
                afiseazaCalculatoare();
            if (optiune == 6)
                break;
        }
    }
};

int main() {
    Menu m1;
    m1.mainLoop();
    return 0;
}