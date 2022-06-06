#include <iostream>
#include <utility>
#include <vector>
#include "IoBase.h"
#include "BaseMenu.h"
#include <algorithm>
#include <memory>

using namespace std;

template <class T>
istream& operator>>(istream &is, vector<T> &vec) {
    int n;
    cout << "Introduceti numarul de elemente: \n";
    is >> n;
    T aux;
    cout << "Introduceti elementele: \n";
    while (n--) {
        is >> aux;
        vec.push_back(aux);
    }
    return is;
}

template <class T>
ostream& operator<<(ostream &os, const vector<T> &vec) {
    os << "Eelementele sunt: \n";
    for (auto &y : vec) {
        os << y << "\n";
    }
    return os;
}

class Malware : public IoBase{
protected:
    double rating;
    int zi, luna, an;
    string nume;
    string metoda_infectare;
    vector<string> registrii;
public:
    Malware() {
        metoda_infectare = "unknown";
    }

    Malware(double rating, int zi, int luna, int an, string nume,
            const vector<string> &registrii, string metodaInfectare = "unknown") : rating(rating), zi(zi), luna(luna), an(an), nume(std::move(nume)),
                                               metoda_infectare(std::move(metodaInfectare)), registrii(registrii) {}

    virtual double CalcRating() {
        double sum = 0;
        for (auto &y:registrii) {
            if (y == "HKLM-run" || y == "HKCU-run") sum += 20;
        }
        return sum;
    };

    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "Rating: \n";
        is >> rating;
        cout << "zi luna an: \n";
        is >> zi >> luna >> an;
        cout << "Nume: \n";
        is.ignore(1);
        getline(is, nume);
        cout << "Este cunoscuta metoda de infetare(0=NU/1=DA)? \n";
        bool ok;
        is >> ok;
        if (ok) {
            cout << "Metoda infectare: \n";
            is >> metoda_infectare;
        }
        int n;
        cout << "Introduceti registrii: \n";
        is >> registrii;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os << "Rating: \n";
        os << rating << "\n";
        os << "zi luna an: \n";
        os << zi << luna << an << "\n";
        os << "Nume: \n";
        os << nume << "\n";
        os << "Metoda infectare: \n";
        os << metoda_infectare << "\n";
        os << "Registrii: \n";
        os << registrii;
        return os;
    }
};

class Rootkit : virtual public Malware {
protected:
    vector<string> importutri;
    vector<string> stringuri;
public:


    Rootkit() {}

    Rootkit(double rating, int zi, int luna, int an, const string &nume, const vector<string> &registrii,
            const string &metodaInfectare, const vector<string> &importutri, const vector<string> &stringuri) : Malware(
            rating, zi, luna, an, nume, registrii, metodaInfectare), importutri(importutri), stringuri(stringuri) {}

    double CalcRating() override {
        double sum = Malware::CalcRating();
        for (auto &y:stringuri) {
            if (y == "System Service Descriptor Table" || y == "SSDT" || y == "NtCreateFile") {
                sum += 100;
            }
        }
        for (auto &y:importutri) {
            if (y == "ntoskrnl.exe") sum *= 2;
        }
        return sum;
    }

    istream &read(istream &is) override {
        Malware::read(is);
        cout << "Introduceti importurile: \n";
        is >> importutri;
        cout << "Introduceti stringurile: \n";
        is >> stringuri;
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        os << "Importuri: \n";
        os << importutri << "\n";
        os << "Stringuri: \n";
        os << stringuri << "\n";
        return os;
    }


};

class KeyLogger : virtual public Malware {
protected:
    vector<string> functii;
    vector<string> taste;
public:
    KeyLogger() {}

    KeyLogger(double rating, int zi, int luna, int an, const string &nume, const vector<string> &registrii,
              const string &metodaInfectare, const vector<string> &functii, const vector<string> &taste) : Malware(
            rating, zi, luna, an, nume, registrii, metodaInfectare), functii(functii), taste(taste) {}

    double CalcRating() override {
        double sum = Malware::CalcRating();


        for (auto &y:taste) {
            if (y == "[Up]" || y == "[Num Lock]" || y == "[Down]" || y == "[Right]" || y == "[Left]" || y == "PageDown") {
                sum += 10;
            }
        }

        for (auto &y:functii) {
            if (y == "CreateFileW" || y == "OpenProcess" || y == "ReadFile" || y == "WriteFile" || y == "RegisterHotKey" || y == "SetWindowsHookEx") {
                sum += 30;
            }
        }
        return sum;
    }

    istream &read(istream &is) override {
        Malware::read(is);
        cout << "Introduceti functiile: \n";
        is >> functii;
        cout << "Introduceti tastele: \n";
        is >> taste;
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        os << "Functii: \n";
        os << functii << "\n";
        os << "Taste: \n";
        os << taste << "\n";
        return os;
    }
};

class KernelKeylogger : public Rootkit, public KeyLogger {
private:
    bool ascunde_registrii;
    bool ascunde_fisiere;
public:
    KernelKeylogger() {}

    KernelKeylogger(double rating, int zi, int luna, int an, const string &nume, const vector<string> &registrii,
                    const string &metodaInfectare, const vector<string> &importutri, const vector<string> &stringuri,
                    double rating1, int zi1, int luna1, int an1, const string &nume1, const vector<string> &registrii1,
                    const string &metodaInfectare1, const vector<string> &functii, const vector<string> &taste,
                    bool ascundeRegistrii, bool ascundeFisiere) : Rootkit(rating, zi, luna, an, nume, registrii,
                                                                          metodaInfectare, importutri, stringuri),
                                                                  KeyLogger(rating1, zi1, luna1, an1, nume1, registrii1,
                                                                            metodaInfectare1, functii, taste),
                                                                  ascunde_registrii(ascundeRegistrii),
                                                                  ascunde_fisiere(ascundeFisiere) {}

    double CalcRating() override {
        double sum =  Rootkit::CalcRating() + KeyLogger::CalcRating() - Rootkit::Malware::CalcRating();
        sum += 20 * ascunde_fisiere + 30 * ascunde_registrii;
        return sum;
    }

    istream &read(istream &is) override {
        Rootkit::read(is);
        cout << "Introduceti functiile: \n";
        is >> functii;
        cout << "Introduceti tastele: \n";
        is >> taste;
        cout << "Ascunde fisiere ? (0=NU/1=DA) \n";
        is >> ascunde_fisiere;
        cout << "Ascunde registrii ? (0=NU/1=DA) \n";
        is >> ascunde_registrii;
        return is;
    }

    ostream &write(ostream &os) const override {
        Rootkit::write(os);
        os << "Functiile: \n";
        os << functii << "\n";
        os << "Tastele: \n";
        os << taste;
        cout << "Ascunde fisiere (0=NU/1=DA) \n";
        os << ascunde_fisiere << "\n";
        cout << "Ascunde registrii (0=NU/1=DA) \n";
        os << ascunde_registrii << "\n";
        return os;
    }
};

class Ransomware : public Malware {
private:
    int rating_criptare;
    double obfuscare;
public:
    Ransomware() {}

    Ransomware(double rating, int zi, int luna, int an, const string &nume, const vector<string> &registrii,
               const string &metodaInfectare, int rating1, double obfuscare) : Malware(rating, zi, luna, an, nume,
                                                                                       registrii, metodaInfectare),
                                                                               rating_criptare(rating1), obfuscare(obfuscare) {}

    double CalcRating() override {
        return rating + obfuscare + Malware::CalcRating();
    }

    istream &read(istream &is) override {
        Malware::read(is);
        cout << "Rating criptare: \n";
        is >> rating_criptare;
        cout << "Obfuscare: \n";
        is >> obfuscare;
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        os << "Rating criptare: \n";
        os << rating_criptare << "\n";
        os << "Obfuscare: \n";
        os << obfuscare << "\n";
        return os;
    }
};

class Calculator : public IoBase{
private:
    int id;
    static int cnt;
    int rating;
    vector<shared_ptr<Malware> > malware;
public:
    Calculator() : id(++cnt) {}

    Calculator(const vector<shared_ptr<Malware>> &malware);

    void Calculeaza() {
        rating = 0;
        for (auto &y:malware) {
            rating += y->CalcRating();
        }
    }

    ostream &write(ostream &os) const override;

    bool operator<(const Calculator &other) const{
        return rating < other.rating;
    }

    istream &read(istream &is) override;

    int Infectat() {
        return (malware.size() != 0);
    }
};

int Calculator::cnt = 0;

ostream &Calculator::write(ostream &os) const {
    IoBase::write(os);
    os << "ID: \n";
    os << id << "\n";
    os << "Rating: \n";
    os << rating << "\n";
    os << "Informatii malware: \n";
    for (auto &y:malware) {
        y->write(os);
        os << "\n";
    }
    return os;
}

Calculator::Calculator(const vector<shared_ptr<Malware>> &malware) : malware(malware) , id(++cnt){}

istream &Calculator::read(istream &is) {
    int n;
    shared_ptr<Malware> aux;
    cout << "Vector malware: \n";
    cout << "Introduceti nr de elemente: \n";
    is >> n;
    while (n--) {
        cout << "Introduceti tipul de malware 0 = Rootkit, 1 = Keylogger, 2 = KernelKeylogger, 3 = Ransomware \n";
        int tip;
        is >> tip;
        if (tip == 0) aux = make_shared<Rootkit>();
        else if (tip == 1) aux = make_shared<KeyLogger>();
        else if (tip == 2) aux = make_shared<KernelKeylogger>();
        else if (tip == 3) aux = make_shared<Ransomware>();

        is >> *aux;
        malware.push_back(aux);
    }
    return is;
}

class Meniu : public BaseMenu {
private:
    vector<Calculator> calculatooare;
public:
    Meniu(const vector<Calculator> &calculatooare) : calculatooare(calculatooare) {}

    void mainloop() override {
        while (true) {
            showoptions();
            int opt = getoption(1, 5);
            if (opt == 5) return;

            if (opt == 1) {
                cout << "Calculatoare: \n";
                for (auto &y:calculatooare) {
                    cout << y << "\n\n";
                }
            }

            if (opt == 2) {
                vector<Calculator> aux = calculatooare;
                sort(aux.begin(), aux.end());
                cout << "Calculatoarele ordonate: \n";
                for (auto &y:aux) {
                    cout << y << "\n\n";
                }
            }

            if (opt == 3) {
                cout << "Introduceti k: \n";
                int k;
                cin >> k;
                vector<Calculator> aux = calculatooare;
                sort(aux.begin(), aux.end());
                cout << "Primele k calculatoarele ordonate: \n";
                int cnt = 0;
                for (auto &y:aux) {
                    if (cnt == k) break;
                    cout << y << "\n\n";
                }
            }

            if (opt == 4) {
                double total = calculatooare.size();
                double infectate = 0;
                for (auto &y:calculatooare) {
                    infectate += y.Infectat();
                }
                cout << "Procent infectare: \n";
                cout << infectate / total * 100 << "\n";
            }
        }
    }

    void showoptions() override {
        cout << "1. afișarea informațiilor pentru fiecare calculator. \n";
        cout << "2. afișarea informațiilor pentru fiecare calculator fiind ordonate după ratingul final . \n";
        cout << "3. afișarea primelor k calculatoare ordonate după ratingul final. \n";
        cout << "4. afișarea procentului de computere infectate din firmă . \n";
        cout << "5. exit. \n";
    }

    int getoption(int first, int last) override {
        int opt;
        try {
            cin >> opt;
            if (opt < first || opt > last) throw opt;
            return opt;
        }
        catch (int opt) {
            cout << "Optiunea " << opt << " nu este intre " << first << " si " << last << "\n";
            getoption(first, last);
        }
    }
};

int main() {
    vector<Calculator> calculatooare;
    int n;
    cout << "Introduceti numarul de calculatoare: \n";
    cin >> n;
    while (n--) {
        Calculator aux;
        cin >> aux;
        calculatooare.push_back(aux);
    }
    Meniu meniu(calculatooare);
    meniu.mainloop();
    return 0;
}
