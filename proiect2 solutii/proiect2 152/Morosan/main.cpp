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
        os<< zi << "-" << luna << "-" << an << endl;
        return os;
    }
};



class Malware : virtual public IoBase {
protected:
    double rating;
    data infectare;
    string nume;
    string metoda;
    vector<string> registri;
public:
    istream &read(istream &is) override {
        IoBase::read(is);
        cout<<"data de infectare:" <<endl;
        is >> infectare;
        cout<< "nume:" <<endl;
        is.get();
        getline(is, nume);
        cout<< "metoda de infectare" << endl;
        getline(is, metoda);
        if (metoda == "")
            metoda = "unknown";
        int nr;
        cout<<"nr de registri este:"<< endl;
        is >> nr;
        int i = 0;
        string reg;
        if(nr)
            cout<<"numele registrilor:" <<endl;
        is.get();
        while (i < nr){
            getline(is, reg);
            registri.push_back(reg);
            ++i;
        }
        return is;
    }
    virtual double calcul(){
        double aux = 0;
        for (auto r : registri)
            if (r=="HKLM-run" or r=="HKCU-run")
                 aux += 20;
        rating = aux;
        return rating;

    }

    Malware(const data &infectare, const string &nume, const string &metoda, const vector<string> &registri)
            : infectare(infectare), nume(nume), metoda(metoda), registri(registri) {calcul();}

    Malware():metoda("unknown") {calcul();}

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout<<nume<<" "<<rating;
        return os;

    }
};

class rootkit: virtual public Malware{
protected:
    vector<string> importuri;
    vector<string> stringuri;
public:
    rootkit(const data &infectare, const string &nume, const string &metoda, const vector<string> &registri,
            const vector<string> &importuri, const vector<string> &stringuri) : Malware(infectare, nume, metoda,
                                                                                        registri), importuri(importuri),
                                                                                stringuri(stringuri) {calcul();}
    rootkit(): Malware() {
    calcul();
}
    double calcul() override {
        double aux = Malware::calcul();
        for (const auto& s: stringuri)
            if (s == "System Service Descriptor Table" or s=="SSDT" or s=="NtCreateFile")
                aux += 100;
        for (const auto& i: importuri)
            if (i=="ntoskrnl.exe")
                aux *= 2;
        rating = aux;
        return aux;
    }
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
                importuri.push_back(import);
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
                stringuri.push_back(str);
            }
        }
        return is;
    }


};
class keylogger: virtual public Malware{
protected:
    vector<string> functii;
    vector<string> taste;

public:
    double calcul() override {
        double aux = Malware::calcul();
        for (const auto& t:taste)
            if (t=="[Up]" or t=="[Down]")
                aux += 10;
        for (const auto& f: functii)
            if(f=="CreateFileW" or f=="OpenProcess")
                aux += 30;
        rating = aux;
        return aux;
    }
    keylogger():Malware(){calcul();}

    keylogger(const data &infectare, const string &nume, const string &metoda, const vector<string> &registri,
              const vector<string> &functii, const vector<string> &taste) : Malware(infectare, nume, metoda, registri),
                                                                            functii(functii), taste(taste) {}

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
                taste.push_back(tasta);
            }
        }
        return is;
    }
};
class kernel_keylogger: public rootkit, public keylogger{
private:
    bool ascunderegistri;
    bool ascundefisiere;

public:
    istream &read(istream &is) override {
        rootkit::read(is);
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
                taste.push_back(tasta);
            }
        }
        cout << "Ascunde fisiere: ";
        is >> ascundefisiere;
        cout << "Ascunde registri: ";
        is >> ascunderegistri ;
        return is;
    }
    double calcul() override {
        double aux = rootkit::calcul() + keylogger::calcul() - Malware::calcul();
        if (ascunderegistri)
            aux += 30;
        if(ascundefisiere)
            aux += 20;
        rating = aux;
        return aux;
    }
    kernel_keylogger(): Malware(){
    calcul();

}

    kernel_keylogger(const data &infectare, const string &nume, const string &metoda, const vector<string> &registri,
                     const vector<string> &importuri, const vector<string> &stringuri, bool ascunderegistri,
                     bool ascundefisiere) : rootkit(infectare, nume, metoda, registri, importuri, stringuri),
                                            ascunderegistri(ascunderegistri), ascundefisiere(ascundefisiere) {}

};
class ransomware: virtual public Malware{
private:
    int criptare;
    double obfuscare;
public:
    double calcul() override {
        double aux = Malware::calcul();
        aux = aux + criptare + obfuscare;
        rating = aux;
        return aux;
    }
    ransomware(): Malware(){calcul();}

    ransomware(const data &infectare, const string &nume, const string &metoda, const vector<string> &registri,
               int criptare, double obfuscare) : Malware(infectare, nume, metoda, registri), criptare(criptare),
                                                 obfuscare(obfuscare) {}
    istream &read(istream &is) override {
        Malware::read(is);
        cout << "rating criptare: \n";
        is >> criptare;
        while (criptare < 1 or criptare > 10) {
            cout << " rating intre 1 si 10: \n";
            is >> criptare;
        }
        cout << "rating obfuscare: \n";
        is >> obfuscare;
        return is;
    }
};


shared_ptr<Malware> citesteMalware(int t) {
    shared_ptr<Malware> malware;
    switch (t) {
        case 1: {
            rootkit j1;
            cin >> j1;
            malware = make_shared<rootkit>(j1);
            break;
        }
        case 2: {
            keylogger j2;
            cin >> j2;
            malware = make_shared<keylogger>(j2);
            break;
        }
        case 3: {
            kernel_keylogger j3;
            cin >> j3;
            malware = make_shared<kernel_keylogger>(j3);
            break;
        }
        case 4: {
            ransomware j4;
            cin >> j4;
            malware = make_shared<ransomware>(j4);
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
            malware->calcul();
            listaMalware.push_back(malware);
        }
        return is;
    }

    double calculeazaRating() {
        double rating = 0;
        for (auto malware : listaMalware) {
            rating += malware->calcul();
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