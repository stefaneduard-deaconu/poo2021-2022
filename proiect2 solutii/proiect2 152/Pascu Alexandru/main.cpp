#include <iostream>
#include <vector>
#include "IoBase.h" // din laboratorul 5/6/7 -> folosit pentru a citi/scrie mai usor obiectele din clase
#include <memory>
using namespace std;

class data : public IoBase{
private:
    int zi, luna, an;
public:
    istream &read(istream &is) override {
        IoBase::read(is);
        is >> zi >> luna >> an;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os << "zi: " << zi << ", luna: " << luna << ", an: " << an;
        return os;
    }
};

class Malware : virtual public IoBase {
protected:
    double ratingImpact = 0;
    data dataInfectare;
    string nume;
    string metodaInfectare;
    vector<string> registriModificati;
public:

    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "data infectare: \n";
        is >> dataInfectare;
        cout << "nume: \n";
        is.get();
        getline(is, nume);
        cout << "metoda infectare: \n";
//        is.get();
        getline(is, metodaInfectare);
        if (metodaInfectare == "")
            metodaInfectare = "unknown";
        int nrReg;
        cout << "numarul de registri: \n";
        is >> nrReg;
        string reg;
        if (nrReg) {
            cout << "registrii: \n";
            is.get();
            for (int i = 0; i < nrReg; i++) {
//            is.get();
                getline(is, reg);
                registriModificati.push_back(reg);
            }
        }
        return is;
    }


    virtual double calculeazaRating() {
        double rating = 0;
        for (auto r : registriModificati) {
            if (r == "HKLM-run" or r == "HKCU-run") {
                rating += 20;
            }
        }
        ratingImpact = rating;
        return rating;
    };

    Malware(const data &dataInfectare, const string &nume, const string &metodaInfectare,
            const vector<string> &registriModificati) : dataInfectare(dataInfectare),
                                                        nume(nume), metodaInfectare(metodaInfectare),
                                                        registriModificati(registriModificati) {
        calculeazaRating();
    }
    Malware() : metodaInfectare("unknown") {
        calculeazaRating();
    };

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os << "rating Impact: " << ratingImpact;
        os << ", data infectarii: " << dataInfectare;
        os << ", nume: " << nume;
        os << ", metoda Infectare: " << metodaInfectare;
        os << ", registri modificati: \n";
        for (auto reg : registriModificati) {
            os << reg << ", ";
        }
        return os;
    }
};

class Rootkit : virtual public Malware {
protected:
    vector<string> listaImporturi;
    vector<string> stringuriSemnificative;
public:

    istream &read(istream &is) override {
        Malware::read(is);
        int nrImporturi, nrStringuri;
        string import, str;
        cout << "numarul de importuri: \n";
        is >> nrImporturi;
        if (nrImporturi) {
            cout << "importuri: \n";
            is.get();
            for (int i = 0; i < nrImporturi; i++) {
//            is.get();
                getline(is, import);
                listaImporturi.push_back(import);
            }
        }
        cout << "numarul de stringuri speciale: \n";
        is >> nrStringuri;
        if (nrStringuri) {
            cout << "stringuri: \n";
            is.get();
            for (int i = 0; i < nrStringuri; i++) {
//            is.get();
                getline(is, str);
                stringuriSemnificative.push_back(str);
            }
        }
        return is;
    }

    double calculeazaRating() override {
        double rating = Malware::calculeazaRating();
        string stringuri[] = {"System Service Descriptor Table", "SSDT", "NtCreateFile"};
        for (auto s : stringuriSemnificative) {
            for (auto s1 : stringuri) {
                if (s == s1)
                    rating += 100;
            }
        }
        string import = "ntoskrnl.exe";
        for (auto s : listaImporturi) {
            if (s == import)
                rating *= 2;
        }
        ratingImpact = rating;
        return rating;
    }

    Rootkit(double ratingImpact, const data &dataInfectare, const string &nume, const string &metodaInfectare,
            const vector<string> &registriModificati, const vector<string> &listaImporturi,
            const vector<string> &stringuriSemnificative) : Malware(dataInfectare, nume, metodaInfectare,
                                                                    registriModificati), listaImporturi(listaImporturi),
                                                            stringuriSemnificative(stringuriSemnificative) {
        calculeazaRating();
    }
    Rootkit() : Malware() {
         calculeazaRating();
    };


    ostream &write(ostream &os) const override {
        Malware::write(os);
        os << "Importuri: \n";
        for (auto imp : listaImporturi) {
            os << imp << ", ";
        }
        os << "Stringuri semnificative: \n";
        for (auto str : stringuriSemnificative) {
            os << str << ", ";
        }
        return os;
    }
};

class Keylogger : virtual public Malware {
protected:
    vector<string> functii;
    vector<string> tasteSpeciale;
public:

    istream &read(istream &is) override {
        Malware::read(is);
        int nrFunctii, nrTaste;
        string functie, tasta;
        cout << "numarul de functii: \n";
        is >> nrFunctii;
        if (nrFunctii) {
            cout << "functiile: \n";
            is.get();
            for (int i = 0; i < nrFunctii; i++) {
                getline(is, functie);
                functii.push_back(functie);
            }
        }
        cout << "numarul de taste: \n";
        is >> nrTaste;
        if (nrTaste) {
            cout << "tastele: \n";
            is.get();
            for (int i = 0; i < nrTaste; i++) {
                getline(is, tasta);
                tasteSpeciale.push_back(tasta);
            }
        }
        return is;
    }

    double calculeazaRating() override {
        string stringuri_10[] = {"[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
        string stringuri_30[] = {"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};
        double rating = Malware::calculeazaRating();
        for (auto tasta : tasteSpeciale) {
            for (auto s1 : stringuri_10) {
                if (s1 == tasta)
                    rating += 10;
            }
        }
        for (auto functie : functii) {
            for (auto s2 : stringuri_30) {
                if (s2 == functie)
                    rating += 30;
            }
        }
        ratingImpact = rating;
        return rating;
    }

    Keylogger(const data &dataInfectare, const string &nume, const string &metodaInfectare,
              const vector<string> &registriModificati, const vector<string> &functii, const vector<string> &tasteSpeciale)
            : Malware(dataInfectare, nume, metodaInfectare, registriModificati), functii(functii),
              tasteSpeciale(tasteSpeciale) {
        calculeazaRating();
    }

    Keylogger() : Malware() {
        calculeazaRating();
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        os << "Functii: ";
        for (auto f : functii) {
            os << f << ", ";
        }
        os << "Taste speciale: ";
        for (auto t : tasteSpeciale) {
            os << t << ", ";
        }
        return os;
    }
};

class KernelKeylogger : public Keylogger, public Rootkit {
private:
    bool ascundeFisiere, ascundeRegistri;
public:

    istream &read(istream &is) override {
        Rootkit::read(is);
        int nrFunctii, nrTaste;
        string functie, tasta;
        cout << "numarul de functii: \n";
        is >> nrFunctii;
        if (nrFunctii) {
            cout << "functiile: \n";
            is.get();
            for (int i = 0; i < nrFunctii; i++) {
                getline(is, functie);
                functii.push_back(functie);
            }
        }
        cout << "numarul de taste: \n";
        is >> nrTaste;
        if (nrTaste) {
            cout << "tastele: \n";
            is.get();
            for (int i = 0; i < nrTaste; i++) {
                getline(is, tasta);
                tasteSpeciale.push_back(tasta);
            }
        }
        cout << "Ascunde fisiere: ";
        is >> ascundeFisiere;
        cout << "Ascunde registri: ";
        is >> ascundeRegistri ;
        return is;
    }

    double calculeazaRating() override {
        double rating;
        rating = Rootkit::calculeazaRating() + Keylogger::calculeazaRating() - Malware::calculeazaRating();
        if (ascundeFisiere)
            rating += 20;
        if (ascundeRegistri)
            rating += 30;
        ratingImpact = rating;
        return rating;
    }

    KernelKeylogger(const data &dataInfectare, const string &nume, const string &metodaInfectare,
                    const vector<string> &registriModificati, const vector<string> &functii,
                    const vector<string> &tasteSpeciale, double ratingImpact, const data &dataInfectare1,
                    const string &nume1, const string &metodaInfectare1, const vector<string> &registriModificati1,
                    const vector<string> &listaImporturi, const vector<string> &stringuriSemnificative, bool ascundeFisiere,
                    bool ascundeRegistri) : Keylogger(dataInfectare, nume, metodaInfectare, registriModificati, functii,
                                                      tasteSpeciale),
                                            Rootkit(ratingImpact, dataInfectare1, nume1, metodaInfectare1,
                                                    registriModificati1, listaImporturi, stringuriSemnificative),
                                            ascundeFisiere(ascundeFisiere), ascundeRegistri(ascundeRegistri) {
        calculeazaRating();
    }

    KernelKeylogger() : Malware() {
        calculeazaRating();
    }

    ostream &write(ostream &os) const override {
        Rootkit::write(os);
        os << "Functii: ";
        for (auto f : functii) {
            os << f << ", ";
        }
        os << "Taste speciale: ";
        for (auto t : tasteSpeciale) {
            os << t << ", ";
        }
        os << "ascunde fisiere: " << ascundeFisiere << ", ascunde registri: " << ascundeRegistri;
        return os;
    }
};

class Ransomware : public Malware {
private:
    int ratingCriptare;
    double ratingObfuscare;
public:

    istream &read(istream &is) override {
        Malware::read(is);
        cout << "rating criptare: \n";
        is >> ratingCriptare;
        while (ratingCriptare < 1 or ratingCriptare > 10) {
            cout << "ratingul de criptare trebuie sa fie intre 1 si 10! Introduceti din nou: \n";
            is >> ratingCriptare;
        }
        cout << "rating obfuscare: \n";
        is >> ratingObfuscare;
        return is;
    }

    double calculeazaRating() override {
        double rating = Malware::calculeazaRating();
        rating += ratingCriptare + ratingObfuscare;
        ratingImpact = rating;
        return rating;
    }

    Ransomware(const data &dataInfectare, const string &nume, const string &metodaInfectare,
               const vector<string> &registriModificati, int ratingCriptare, double ratingObfuscare) : Malware(
            dataInfectare, nume, metodaInfectare, registriModificati), ratingCriptare(ratingCriptare), ratingObfuscare(
            ratingObfuscare) {
        calculeazaRating();
    }

    Ransomware() : Malware() {
        calculeazaRating();
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        os << "rating criptare: ";
        os << ratingCriptare;
        os << ", rating obfuscare: ";
        os << ratingObfuscare;
    }

};

shared_ptr<Malware> citesteMalware(int t) {
    shared_ptr<Malware> malware;
    switch (t) {
        case 1: {
            Rootkit j1;
            cin >> j1;
            malware = make_shared<Rootkit>(j1);
            break;
        }
        case 2: {
            Keylogger j2;
            cin >> j2;
            malware = make_shared<Keylogger>(j2);
            break;
        }
        case 3: { 
            KernelKeylogger j3;
            cin >> j3;
            malware = make_shared<KernelKeylogger>(j3);
            break;
        }
        case 4: { 
            Ransomware j4;
            cin >> j4;
            malware = make_shared<Ransomware>(j4);
        }
    }
    return malware;
}

class Computer : public IoBase {
private:
    int idc;
    static int id;
    vector < shared_ptr<Malware> > listaMalware;
    double ratingFinal = 0;
public:
    Computer(const vector < shared_ptr<Malware> > &listaMalware, double ratingFinal) : idc(++id),
                                                                                     listaMalware(listaMalware),
                                                                                     ratingFinal(ratingFinal) {}

    Computer():idc(++id){};

    istream &read(istream &is) override {
        IoBase::read(is);
        int m; // nr malware
        cout << "Numarul de malware-uri:\n";
        is >> m;
        for (int i = 0; i < m; i++) {
            int t;
            cout << "Tipul de malware: (1 pentru Rootkit, 2 pentru Keylogger, 3 pentru Kernel Keylogger, 4 pentru Ransomware):\n";
            is >> t;
            shared_ptr<Malware> malware = citesteMalware(t);
            malware->calculeazaRating();
            listaMalware.push_back(malware);
        }
        return is;
    }

    double calculeazaRating() {
        double rating = 0;
        for (auto malware : listaMalware) {
            rating += malware->calculeazaRating();
        }
        ratingFinal = rating;
        return rating;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os << "id: " << idc;
        os << ", lista Malware: \n";
        for (auto malware : listaMalware) {
            os << *malware << ", ";
        }
        os << "rating final: " << ratingFinal;
        return os;
    }

    int isInfected() {
        return listaMalware.size() != 0;
    }
};

class BaseMenu { // din laboratorul 8
public:
    virtual void vectorOptions() {}

    virtual int chooseOption(int first, int last) = 0;

    virtual void mainLoop() {}
};

class SimpleMenu : public BaseMenu {
private:
    vector<Computer> listaComputere;
public:
    SimpleMenu(const vector<Computer> &listaComputere) : listaComputere(listaComputere) {}

    SimpleMenu() = default;

    void vectorOptions() override {
        cout << "1. Afiseaza informatiile pentru fiecare calculator." << '\n';
        cout << "2. Afiseaza informatiile pentru fiecare calculator ordonate dupa ratingul final." << '\n';
        cout << "3. Afiseaza informatiile pentru primele k calculatoare ordonate dupa ratingul final." << '\n';
        cout << "4. Afiseaza procentul de computere infectate din firma." << '\n';
        cout << "5. Iesire" << '\n';
    }

    int chooseOption(int first, int last) override {
        int option = -1;
        while (option < first || option > last) {
            cout << '\n';
            cout << "Pentru a rula comanda, alegeti un numar intre "
                 << first << " si " << last << '\n';
            vectorOptions();
            cout << "Alegere: ";
            cin >> option;
        }
        return option;
    }
    void option1();
    void option2();
    void option3();
    void option4();
    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 5);
            if (option == 1) {
                option1();
            } else if (option == 2) {
                option2();
            } else if (option == 3) {
                option3();
            } else if (option == 4) {
                option4();
            }
            else
                break;
        }
        cout << '\n'
             << "---------------------------------"
             << '\n'
             << "Programul s-a incheiat cu success";
    }

};

void SimpleMenu::option1() {
    cout << "Se afiseaza informatiile pentru fiecare calculator..." << '\n';
    for (auto c : listaComputere) {
        c.calculeazaRating();
    }
    for (auto c : listaComputere) {
        cout << c << "\n";
    }
}

void SimpleMenu::option2() {
    cout << "Se afiseaza informatiile pentru fiecare calculator ordonate dupa ratingul final..." << '\n';
    for (auto c : listaComputere) {
        c.calculeazaRating();
    }
    vector<Computer> listaSortata = listaComputere;
    int sz = listaSortata.size();
    for (int i = 0; i < sz; i++) {
        for (int j = i + 1; j < sz; j++) {
            if (listaSortata[i].calculeazaRating() < listaSortata[j].calculeazaRating()) {
                swap(listaSortata[i], listaSortata[j]);
            }
        }
    }
    for (auto c : listaSortata) {
        cout << c << "\n";
    }
}

void SimpleMenu::option3() {
    cout << "Se afiseaza informatiile pentru primele k calculatoare ordonate dupa ratingul final..." << '\n';
    cout << "Introduceti k: ";
    for (auto c : listaComputere) {
        c.calculeazaRating();
    }
    int k;
    cin >> k;
    vector<Computer> listaSortata = listaComputere;
    int sz = listaSortata.size();
    for (int i = 0; i < sz; i++) {
        for (int j = i + 1; j < sz; j++) {
            if (listaSortata[i].calculeazaRating() < listaSortata[j].calculeazaRating()) {
                swap(listaSortata[i], listaSortata[j]);
            }
        }
    }
    for (int i = 0; i < k; i++) {
        cout << listaSortata[i] << "\n";
    }
}

void SimpleMenu::option4() {
    int sz = listaComputere.size();
    int infectate = 0;
    for (auto c : listaComputere) {
        if (c.isInfected())
            infectate++;
    }
    double ratio = 1.0 * infectate / sz;
    cout << ratio * 100 << "%";
}

int Computer::id = 0;

int main() {
    int n; // calculatoare
    vector<Computer> listaComputere;
    cout << "Numarul de computere: \n";
    cin >> n;
    for (int i = 0; i < n; i++) {
        Computer c;
        cin >> c;
        c.calculeazaRating();
        listaComputere.push_back(c);
    }
    SimpleMenu sm(listaComputere);
    sm.mainLoop();
    return 0;
}
