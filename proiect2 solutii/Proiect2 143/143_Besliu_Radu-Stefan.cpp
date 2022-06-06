/* Besliu Radu-Stefan 143
g++
Deaconu Stefan */

// Detalii pentru laborator :
// Timp efectiv : 1:30
// Timp comentat + verificari cu teste: 15 minute ( am comentat la final, imi este greu sa comentez in timp ce scriu :) )

// Intrebari:
// Am voie la colocviu sa nu scriu niciun constructor? Aici asa am facut si vad ca functioneaza totul ok. Ma gandesc ca
// utilizatorul foloseste meniul pentru a interactiona cu obiecte, nu cu ajutorul unui constructor
// In plus, daca faceam contructorul la una din clase, nu mai aveam constructor default dupa si trebuia sa-l implementez eu => si mai mult timp.

#include <bits/stdc++.h>

using namespace std;

// Clasa IoBase preluata din laboratoare
// Usureaza overload la istream si ostream
class IoBase {
public:
    virtual istream &read(istream &is) {
        return is;
    }

    virtual ostream &write(ostream &os) const {
        return os;
    }

    friend ostream &operator<<(ostream &os, const IoBase &base) {
        return base.write(os);
    }

    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }
};

// Clasa de baza Malware
class Malware : public IoBase {
protected:
    double ratingImpact;
    int ziInfectare, lunaInfectare, anInfectare;
    string nume, metodaInfectare;
    vector < string > registriiModificati;

public:
//    Metoda virtuala pentru calcularea rating-ului
    virtual double calculareRating();

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};



double Malware::calculareRating() {
    double ratingTotal = 0;
//    Daca se gaseste unul din cei 2 registrii modificati
//    Se aduna 20 si se iese din for.
    for (auto const &reg : registriiModificati) {
        if (reg == "HKLM-run" || reg == "HKCU-run") {
            ratingTotal += 20;
            break;
        }
    }
    return ratingTotal;
}

istream &Malware::read(istream &is) {
    IoBase::read(is);
    cout << "nume: ";
    getline(is, nume);
    cout << "metoda infectare: ";
    getline(is, metodaInfectare);
//    Daca la citire metoda de infectare nu este cunoscuta, se seteaza unknown
    if (metodaInfectare.empty()) metodaInfectare = "unknown";
    cout << "zi infectare: ";
    is >> ziInfectare;
    cout << "luna infectare: ";
    is >> lunaInfectare;
    cout << "an infectare: ";
    is >> anInfectare;
    int nrRegModificati;
    cout << "numar registrii modificati: ";
    is >> nrRegModificati;
    is.get();
    registriiModificati.resize(nrRegModificati);
//    Se citesc registrii modificati
    for (auto &reg : registriiModificati) {
        cout << "registru modificat: ";
        is >> reg;
    }
//    Se seteaza ratingImpact ( la fel pentru taote tipurile de malware )
    ratingImpact = calculareRating();
    return is;
}

ostream &Malware::write(ostream &os) const {
    IoBase::write(os);
    os << "nume: " << nume << ", zi infectare: " << ziInfectare << ", luna infectare: " << lunaInfectare << ", an infectare: " << anInfectare;
    os << ", metoda infectare: " << metodaInfectare << ", registrii modificati: ";
//    Afisare registrii modificati
    for (auto const &reg : registriiModificati) {
        os << reg << " ";
    }
    return os;
}

// Clasa derivate Rootkit
class Rootkit : virtual public Malware {
protected:
    vector < string > importuri;
    vector < string > stringuriSemnificative;

public:
//    Metoda pentru calculare rating-ului
    double calculareRating() override;

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

double Rootkit::calculareRating() {
    double ratingTotal = Malware::calculareRating();
//    Daca se gaseste unul din stringuri, rating-ul creste cu 100
    for (auto const &str : stringuriSemnificative) {
        if (str == "System Service Descriptor Table" || str == "SSDT" || str == "NtCreateFile") {
            ratingTotal += 100;
        }
    }
//    Daca se gaseste acest import, valoare rating-ului se dubleaza
    for (auto const &imp : importuri) {
        if (imp == "ntoskrnl.exe") {
            ratingTotal *= 2;
        }
    }
    return ratingTotal;
}

istream &Rootkit::read(istream &is) {
    Malware::read(is);
    int nrImporturi;
    cout << "numar importuri: ";
    is >> nrImporturi;
    is.get();
    importuri.resize(nrImporturi);
    for (auto &imp : importuri) {
        cout << "import: ";
        getline(is, imp);
    }
    int nrStrSemn = 0;
    cout << "numar string-uri semnificative: ";
    is >> nrStrSemn;
    is.get();
    stringuriSemnificative.resize(nrStrSemn);
    for (auto &str : stringuriSemnificative) {
        cout << "string semnificativ: ";
        getline(is, str);
    }
    ratingImpact = calculareRating();
    return is;
}

ostream &Rootkit::write(ostream &os) const {
    Malware::write(os);
    os << "importuri: ";
    for (auto const &imp : importuri) {
        os << imp << " ";
    }
    os << ", string-uri semnificative: ";
    for (auto const &str : stringuriSemnificative) {
        os << str << " ";
    }
    os << ", rating impact: " << ratingImpact << '\n';
    return os;
}


// Clasa derivate Keylogger
class Keylogger : virtual public Malware {
protected:
    vector < string > functiiFolosite;
    vector < string > tasteSpeciale;

public:
//    Metoda pentru calcularea rating-ului
    double calculareRating() override;

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

double Keylogger::calculareRating() {
    double ratingTotal = Malware::calculareRating();
//    Daca se intalneste una dintre taste, rating-ul creste cu 10
    for (auto const &tasta : tasteSpeciale) {
        if (tasta == "[Up]" || tasta == "[Num Lock]" || tasta == "[Down]" || tasta == "[Right]" || tasta == "[UP]" || tasta == "[Left]" || tasta == "[PageDown]") {
            ratingTotal += 10;
        }
    }
//    Daca se intalneste una dintre functii, rating-ul creste cu 30
    for (auto const &functie : functiiFolosite) {
        if (functie == "CreateFileW" || functie == "OpenProcess" || functie == "ReadFile" || functie == "WriteFile" || functie == "RegisterHotKey" || functie == "SetWindowsHookEx") {
            ratingTotal += 30;
        }
    }
    return ratingTotal;
}

istream &Keylogger::read(istream &is) {
    Malware::read(is);
    int nrFunctiiFolosite;
    cout << "numar functii folosite: ";
    is >> nrFunctiiFolosite;
    is.get();
    functiiFolosite.resize(nrFunctiiFolosite);
    for (auto &func : functiiFolosite) {
        cout << "functie folosita: ";
        getline(is, func);
    }
    int nrTasteSpeciale;
    cout << "taste speciale: ";
    is >> nrTasteSpeciale;
    is.get();
    tasteSpeciale.resize(nrTasteSpeciale);
    for (auto &tasta : tasteSpeciale) {
        cout << "tasta speciala: ";
        getline(is, tasta);
    }
    ratingImpact = calculareRating();
    return is;
}

ostream &Keylogger::write(ostream &os) const {
    Malware::write(os);
    os << ", functii folosite: ";
    for (auto const &func : functiiFolosite) {
        os << func << " ";
    }
    os << ", taste speciale: ";
    for (auto const &tasta : tasteSpeciale) {
        os << tasta << " ";
    }
    os << ", rating impact: " << ratingImpact << '\n';
    return os;
}

// Clasa derivate KernelKeylogger
class KernelKeylogger : public Rootkit, public Keylogger {
private:
    bool ascundeFisiere;
    bool ascundeRegistrii;

public:
//    Metoda pentru calculare rating-ului
    double calculareRating() override;

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

double KernelKeylogger::calculareRating() {
//    Se initializeaza valoarea cu suma rating-ului de la Rootkit si Keylogger
//    Daca avem ratingTotal = 20 de la registrii, il scadem, deoarece este adunat de 2 ori
    double ratingTotal = Rootkit::calculareRating() + Keylogger::calculareRating() - Malware::calculareRating();
//    Daca ascunde fisiere, rating-ul creste cu 20
    if (ascundeFisiere) {
        ratingTotal += 20;
    }
//    Daca ascunde registrii, rating-ul creste cu 30
    if (ascundeRegistrii) {
        ratingTotal += 30;
    }
    return ratingTotal;
}

istream &KernelKeylogger::read(istream &is) {
    Rootkit::read(is);
    int nrFunctiiFolosite;
    cout << "numar functii folosite: ";
    is >> nrFunctiiFolosite;
    is.get();
    functiiFolosite.resize(nrFunctiiFolosite);
    for (auto &func : functiiFolosite) {
        cout << "functie folosita: ";
        getline(is, func);
    }
    int nrTasteSpeciale;
    cout << "taste speciale: ";
    is >> nrTasteSpeciale;
    is.get();
    tasteSpeciale.resize(nrTasteSpeciale);
    for (auto &tasta : tasteSpeciale) {
        cout << "tasta speciala: ";
        getline(is, tasta);
    }
    cout << "ascunde fisiere (1/0): ";
    is >> ascundeFisiere;
    cout << "ascunde registrii (1/0): ";
    is >> ascundeRegistrii;
    ratingImpact = calculareRating();
    return is;
}

ostream &KernelKeylogger::write(ostream &os) const {
    Rootkit::write(os);
    os << ", functii folosite: ";
    for (auto const &func : functiiFolosite) {
        os << func << " ";
    }
    os << ", taste speciale: ";
    for (auto const &tasta : tasteSpeciale) {
        os << tasta << " ";
    }
    os << "ascunde fisiere: " << ascundeFisiere << ", ascunde registrii: " << ascundeRegistrii << ", rating impact: " << ratingImpact << '\n';;
    return os;
}

// Clasa derivata Ransomware
class Ransomware : public Malware {
private:
    int ratingCriptare;
    double ratingObfuscare;

public:
//    Metoda pentru calcularea rating-ului
    double calculareRating() override;

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

double Ransomware::calculareRating() {
//    Metoda calcul: rating malware + rating criptare + rating obfuscare
    double ratingTotal = Malware::calculareRating() + ratingCriptare + ratingObfuscare;
    return ratingTotal;
}

istream &Ransomware::read(istream &is) {
    Malware::read(is);
    cout << "rating criptare: ";
    is >> ratingCriptare;
    cout << "rating obfuscare: ";
    is >> ratingObfuscare;
    ratingImpact = calculareRating();
    return is;
}

ostream &Ransomware::write(ostream &os) const {
    Malware::write(os);
    os << ", rating criptare: " << ratingCriptare << ", rating obfuscare: " << ratingObfuscare << ", rating impact: " << ratingImpact << '\n';
    return os;
}

// Clasa de baza Computer
class Computer : public IoBase {
private:
//    Id-ul static si unic
    static int idUnic;
    int idCurent;
//    Vector care poate contine orice tip de malware
    vector < shared_ptr < Malware > > malwares;
    double ratingFinal = 0;

public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

//    Metoda pentru updatarea si setarea id-ului curent al calculatorului
    static int setGetId();

    double getRatingFinal() const;
};

//  Initializarea id-ului static
int Computer::idUnic = 0;

//  Setarea id-ului curent
int Computer::setGetId() {
    idUnic += 1;
    return idUnic;
}

istream &Computer::read(istream &is) {
    IoBase::read(is);
    idCurent = setGetId();
    int nrMalware;
    cout << "numar malware: ";
    is >> nrMalware;
    malwares.resize(nrMalware);
//    Pentru fiecare malware, ii cerem utilizatorului un id care identifica malware-ul
//    Se citeste pana id-ul este corect
    for (auto &mal : malwares) {
        int choice = -1;
        while (choice < 1 || choice > 4) {
            cout << "(1: Rootkit, 2: Keylogger, 3: Kernel-Keylogger, 4: Ransomware): ";
            is >> choice;
        }
        is.get();
        if (choice == 1) {
            mal = make_shared < Rootkit > (Rootkit());
        }
        else if (choice == 2) {
            mal = make_shared < Keylogger > (Keylogger());
        }
        else if (choice == 3) {
            mal = make_shared < KernelKeylogger > (KernelKeylogger());
        }
        else {
            mal = make_shared < Ransomware > (Ransomware());
        }
//        Pentru toate cele 4 if-uri de mai sus se formeaza un obiect cu ajutorul
//        constructorului default, iar apoi utilizam make_shared pentru a-l seta in vector
        is >> *mal;
//        Se aduna rating-ul fiecarui malware la rating-ul final
        ratingFinal += mal->calculareRating();
    }
    return is;
}

ostream &Computer::write(ostream &os) const {
    IoBase::write(os);
    os << "id: " << idCurent << '\n';
    os << "malware: \n";
//    Se afiseaza fiecare malware
    for (auto const &mal : malwares) {
        os << *mal;
    }
    os << "rating final: " << ratingFinal << '\n';
    return os;
}

double Computer::getRatingFinal() const {
    return ratingFinal;
}

//  Functie de comparare ulitizata in functia sort
//  Se sorteaza calculatoarele crescator in functie de rating-ul final
bool cmpRatingFinal(const Computer& a, const Computer& b) {
    return a.getRatingFinal() < b.getRatingFinal();
}

int main() {
    vector < Computer > calculatoare;
    while (true) {
        cout << "1. Citire calculatoare.\n";
        cout << "2. Afisare informatii calculatoare.\n";
        cout << "3. Afisare informatii calculatoare ( sortare dupa rating ).\n";
        cout << "4. Afisarea primelor k calculatoare ( sortare dupa rating ).\n";
        cout << "5. Afisare procent calculatoare infectate.\n";
        cout << "6. Iesire.\n";
        int choice = - 1;
        while (choice < 1 || choice > 6) {
            cout << "Alegere: ";
            cin >> choice;
        }
        if (choice == 1) {
            int nrCalc;
            cout << "numar calculatoare: ";
            cin >> nrCalc;
            calculatoare.resize(nrCalc);
//            Se citesc nrCalc calculatoare
            for (auto &calc : calculatoare) {
                cin >> calc;
            }
        }
        else if (choice == 2) {
//            Se afiseaza calculatoarele citite
            for (auto const &calc : calculatoare) {
                cout << calc << "\n";
            }
        }
        else if (choice == 3) {
//            Se sorteaza calculatoarele folosind functia de sortare
            sort(calculatoare.begin(), calculatoare.end(), cmpRatingFinal);
            for (auto const &calc : calculatoare) {
                cout << calc << "\n";
            }
        }
//        Se sorteaza calculatoarele folosind functia de sortare
//        Daca avem calculatoare in firma, utilizatorul introduce un numar de cautare
//        al unui calculator ( trebuie sa fie valid )
        else if (choice == 4) {
            sort(calculatoare.begin(), calculatoare.end(), cmpRatingFinal);
            int k = -1;
            if (!calculatoare.size()) {
                cout << "Nu exista calculatoare in firma.\n";
            }
            else {
                while (k < 1 || k > calculatoare.size()) {
                    cin >> k;
                }
//                Se afiseaza cele k calculatoare
                for (int i = 0; i < k; ++i) {
                    cout << calculatoare[i] << '\n';
                }
            }
        }
//        Se calculeaza procentul de calculatoare infectate
        else if (choice == 5) {
            double nrTotalInfectate = 0;
            for (auto const &calc : calculatoare) {
                if (calc.getRatingFinal()) {
                    ++nrTotalInfectate;
                }
            }
            cout << "Procent calculatoare infectate: " << nrTotalInfectate / (double)calculatoare.size() * 100.0 << "%\n'";
        }
//        Se iese din meniu
        else {
            break;
        }
    }
    return 0;
}
