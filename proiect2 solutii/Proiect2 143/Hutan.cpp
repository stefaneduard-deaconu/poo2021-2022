#include <bits/stdc++.h>

#include "util/IoBase.h"

using namespace std;

class Malware : public IoBase {
protected:
    double rating_impact;
    int zi, luna, an;
    string nume, metoda;
    vector<string> registrii;
public:
    Malware();

    Malware(int zi, int luna, int an, const string &nume, const string &metoda,
            const vector<string> &registrii);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    virtual int calculRating() {
        for (string registru: registrii) {
            if (registru == "HKLM-run" || registru == "HKCU-run") rating_impact += 30;
        }
    };
};

Malware::Malware() {}

Malware::Malware(int zi, int luna, int an, const string &nume, const string &metoda,
                 const vector<string> &registrii) : rating_impact(0), zi(zi), luna(luna), an(an), nume(nume),
                                                    metoda(metoda), registrii(registrii) {}


istream &Malware::read(istream &is) {
    IoBase::read(is);
    cout << "Data infectarii:" << '\n';
    cout << "Ziua:";
    is >> zi;
    cout << "Luna:";
    is >> luna;
    cout << "Anul:";
    is >> an;
    cout << "Numele Malwareului:";
    cin.ignore();
    getline(is, nume);
    cout << "Metoda de infectare:";
    cin.ignore();
    getline(is, metoda);
    cout << "Numarul registrilor infectati:";
    int n;
    cin >> n;
    string nume_registru;
    for (int i = 0; i < n; ++i) {
        cout << "Numele registrului infectat " << i + 1 << ':';
        cin.ignore();
        getline(is, nume_registru);
        registrii.push_back(nume_registru);
    }
    return is;
}

ostream &Malware::write(ostream &os) const {
    IoBase::write(os);
    os << "Data infectarii este:" << '\n';
    os << "Ziua: " << zi << '\n';
    os << "Luna: " << luna << '\n';
    os << "Anul: " << an << '\n';
    os << "Numele Malwareului este: " << nume << '\n';
    os << "Metoda de infectare este: " << metoda << '\n';
    os << "Numarul registrilor infectati: " << registrii.size() << '\n';
    os << "Registrii infectati sunt:\n";
    for (int i = 0; i < registrii.size(); ++i) {
        cout << "Numele registrului infectat " << i + 1 << "este : " << registrii[i];
    }
    return os;
}

class Rootkit : public virtual Malware {
protected:
    vector<string> importuri;
    vector<string> semnificative;
public:
    Rootkit();

    Rootkit(int zi, int luna, int an, const string &nume, const string &metoda, const vector<string> &registrii,
            const vector<string> &importuri, const vector<string> &semnificative);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    int calculRating() override;

};

Rootkit::Rootkit() {}

Rootkit::Rootkit(int zi, int luna, int an, const string &nume, const string &metoda, const vector<string> &registrii,
                 const vector<string> &importuri, const vector<string> &semnificative) : Malware(zi, luna, an, nume,
                                                                                                 metoda, registrii),
                                                                                         importuri(importuri),
                                                                                         semnificative(semnificative) {}

istream &Rootkit::read(istream &is) {
    Malware::read(is);
    cout << "Numarul importurilor (fisiere de tip .dll):";
    int n;
    cin >> n;
    string fisier;
    for (int i = 0; i < n; ++i) {
        cout << "Numele fisierului .dll importat cu numarul " << i + 1 << ":";
        cin.ignore();
        getline(is, fisier);
        importuri.push_back(fisier);
    }
    cout << "Numarul string-urilor semnificative:";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << "Stringul semnificativ numarul " << i + 1 << ":";
        cin.ignore();
        getline(is, fisier);
        semnificative.push_back(fisier);
    }
    return is;
}

ostream &Rootkit::write(ostream &os) const {
    Malware::write(os);
    os << "Numarul importurilor (fisiere de tip .dll) este: " << importuri.size() << '\n';
    for (int i = 0; i < importuri.size(); ++i) {
        os << "Numele fisierului .dll importat cu numarul " << i + 1 << " este: " << importuri[i] << '\n';
    }
    os << "Numarul string-urilor semnificative este: " << semnificative.size() << '\n';
    for (int i = 0; i < semnificative.size(); ++i) {
        os << "Stringul semnificativ cu numarul " << i + 1 << " este: " << semnificative[i] << '\n';
    }
    return os;
}

int Rootkit::calculRating() {
    Malware::calculRating();
    for (string cuvant: importuri) {
        if (cuvant == "System Service Descriptor Table" || cuvant == "SSDT" || cuvant == "NtCreateFile")
            rating_impact += 100;
    }
    for (string cuvant: semnificative) {
        if (cuvant == "ntoskrnl.exe") rating_impact *= 2;
    }
    return rating_impact;
}

class Keylogger : public virtual Malware {
protected:
    vector<string> functii;
    vector<string> taste;
public:
    Keylogger();

    Keylogger(int zi, int luna, int an, const string &nume, const string &metoda, const vector<string> &registrii,
              const vector<string> &functii, const vector<string> &taste);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    int calculRating() override;

};

Keylogger::Keylogger() {}

Keylogger::Keylogger(int zi, int luna, int an, const string &nume, const string &metoda,
                     const vector<string> &registrii, const vector<string> &functii, const vector<string> &taste)
        : Malware(zi, luna, an, nume, metoda, registrii), functii(functii), taste(taste) {}

istream &Keylogger::read(istream &is) {
    Malware::read(is);
    cout << "Numarul functiilor folosite:";
    int n;
    cin >> n;
    string nume;
    for (int i = 0; i < n; ++i) {
        cout << "Numele functiei folosite cu numarul " << i + 1 << ":";
        cin.ignore();
        getline(is, nume);
        functii.push_back(nume);
    }
    cout << "Numarul tastelor speciale:";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << "Tasta speciala numarul " << i + 1 << ":";
        cin.ignore();
        getline(is, nume);
        taste.push_back(nume);
    }
    return is;
}

ostream &Keylogger::write(ostream &os) const {
    Malware::write(os);
    os << "Numarul functiilor folosite este: " << functii.size() << '\n';
    for (int i = 0; i < functii.size(); ++i) {
        os << "Numele functiei folosite cu numarul " << i + 1 << " este: " << functii[i] << '\n';
    }
    os << "Numarul tastelor speciale este: " << taste.size() << '\n';
    for (int i = 0; i < taste.size(); ++i) {
        os << "Tasta speciala numarul: " << i + 1 << " este: " << taste[i] << '\n';
    }
    return os;
}

int Keylogger::calculRating() {
    Malware::calculRating();
    for (string cuvant: taste) {
        if (cuvant == "[Up]" || cuvant == "[Num Lock]" || cuvant == "[Down]" || cuvant == "[Right]" ||
            cuvant == "[UP]" || cuvant == "[Left]" || cuvant == "[PageDown]")
            rating_impact += 10;
    }
    for (string cuvant: functii) {
        if (cuvant == "CreateFileW" || cuvant == "OpenProcess" || cuvant == "ReadFile" || cuvant == "WriteFile" ||
            cuvant == "RegisterHotKey" || cuvant == "SetWindowsHookEx")
            rating_impact += 30;
    }
    return rating_impact;
}

class Kernel_Keylogger : public virtual Rootkit, public virtual Keylogger {
private:
    bool ascunde_fisiere, ascunde_registrii;
public:
    Kernel_Keylogger();

    Kernel_Keylogger(int zi, int luna, int an, const string &nume, const string &metoda,
                     const vector<string> &registrii, const vector<string> &importuri,
                     const vector<string> &semnificative, const vector<string> &functii,
                     const vector<string> &taste, bool ascunde_fisere, bool ascunde_registrii) : Rootkit(zi, luna, an,
                                                                                                         nume, metoda,
                                                                                                         registrii,
                                                                                                         importuri,
                                                                                                         semnificative),
                                                                                                 Keylogger(zi, luna, an,
                                                                                                           nume, metoda,
                                                                                                           registrii,
                                                                                                           functii,
                                                                                                           taste),
                                                                                                 ascunde_fisiere(
                                                                                                         ascunde_fisere),
                                                                                                 ascunde_registrii(
                                                                                                         ascunde_registrii) {}

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    int calculRating() override;

};

Kernel_Keylogger::Kernel_Keylogger() {}

istream &Kernel_Keylogger::read(istream &is) {
    Malware::read(is);
    cout << "Numarul functiilor folosite:";
    int n;
    cin >> n;
    string nume;
    for (int i = 0; i < n; ++i) {
        cout << "Numele functiei folosite cu numarul " << i + 1 << ":";
        cin.ignore();
        getline(is, nume);
        functii.push_back(nume);
    }
    cout << "Numarul tastelor speciale:";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << "Tasta speciala numarul " << i + 1 << ":";
        cin.ignore();
        getline(is, nume);
        taste.push_back(nume);
    }
    cout << "Numarul importurilor (fisiere de tip .dll):";
    cin >> n;
    string fisier;
    for (int i = 0; i < n; ++i) {
        cout << "Numele fisierului .dll importat cu numarul " << i + 1 << ":";
        cin.ignore();
        getline(is, fisier);
        importuri.push_back(fisier);
    }
    cout << "Numarul string-urilor semnificative:";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << "Stringul semnificativ numarul " << i + 1 << ":";
        cin.ignore();
        getline(is, fisier);
        semnificative.push_back(fisier);
    }
    cout << "Ascunde fisiere?\n";
    cout << "1.DA\n2.NU\n";
    cout << "Introduceti numarul alegerii facute:";
    cin >> n;
    if (n == 1) {
        ascunde_fisiere = true;
    } else ascunde_fisiere = false;
    cout << "Ascunde registrii?\n";
    cout << "1.DA\n2.NU\n";
    cout << "Introduceti numarul alegerii facute:";
    cin >> n;
    if (n == 1) {
        ascunde_registrii = true;
    } else ascunde_registrii = false;
    return is;
}

ostream &Kernel_Keylogger::write(ostream &os) const {
    Malware::write(os);
    os << "Numarul functiilor folosite este: " << functii.size() << '\n';
    for (int i = 0; i < functii.size(); ++i) {
        os << "Numele functiei folosite cu numarul " << i + 1 << " este: " << functii[i] << '\n';
    }
    os << "Numarul tastelor speciale este: " << taste.size() << '\n';
    for (int i = 0; i < taste.size(); ++i) {
        os << "Tasta speciala numarul: " << i + 1 << " este: " << taste[i] << '\n';
    }
    os << "Numarul importurilor (fisiere de tip .dll) este: " << importuri.size() << '\n';
    for (int i = 0; i < importuri.size(); ++i) {
        os << "Numele fisierului .dll importat cu numarul " << i + 1 << " este: " << importuri[i] << '\n';
    }
    os << "Numarul string-urilor semnificative este: " << semnificative.size() << '\n';
    for (int i = 0; i < semnificative.size(); ++i) {
        os << "Stringul semnificativ cu numarul " << i + 1 << " este: " << semnificative[i] << '\n';
    }
    if (ascunde_fisiere == true) {
        os << "Kernel-Keylogger-ul ascunde fisiere!";
    } else os << "Kernel-Keylogger-ul NU ascunde fisiere!";
    if (ascunde_registrii == true) {
        os << "Kernel-Keylogger-ul ascunde registrii!";
    } else os << "Kernel-Keylogger-ul NU ascunde registrii!";
    return os;
}

int Kernel_Keylogger::calculRating() {
    Rootkit::calculRating();
    Keylogger::calculRating();
    //SE DUBLA APELAREA FUNCTIEI CALCUL RATING DIN CLASA DE BAZA MALWARE ASA CA O SCADEM O DATA
    for (string registru: registrii) {
        if (registru == "HKLM-run" || registru == "HKCU-run") rating_impact -= 30;
    }
    if (ascunde_fisiere == 1) {
        rating_impact += 20;
    }
    if (ascunde_registrii == 1) {
        rating_impact += 30;
    }
}

class Ransomware : public Malware {
private:
    int rating_criptare;
    double rating_obfuscare;
public:
    Ransomware();

    Ransomware(int zi, int luna, int an, const string &nume, const string &metoda, const vector<string> &registrii,
               int ratingCriptare, double ratingObfuscare);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

Ransomware::Ransomware() {}

Ransomware::Ransomware(int zi, int luna, int an, const string &nume, const string &metoda,
                       const vector<string> &registrii, int ratingCriptare, double ratingObfuscare) : Malware(zi, luna,
                                                                                                              an, nume,
                                                                                                              metoda,
                                                                                                              registrii),
                                                                                                      rating_criptare(
                                                                                                              ratingCriptare),
                                                                                                      rating_obfuscare(
                                                                                                              ratingObfuscare) {}

istream &Ransomware::read(istream &is) {
    Malware::read(is);
    cout << "Rating-ul criptarii:";
    is >> rating_criptare;
    cout << "Rating-ul obfuscarii:";
    is >> rating_obfuscare;
    return is;
}

ostream &Ransomware::write(ostream &os) const {
    Malware::write(os);
    os << "Rating-ul criptarii este: " << rating_criptare << ", iar rating-ul obfuscarii este: " << rating_obfuscare
       << '\n';
    return os;
}

class Computer : public IoBase {
private:
    int id;
    double rating_final;
    vector<shared_ptr<Malware>> lista_malware;
public:
    Computer();

    Computer(int id, double ratingFinal, const vector<shared_ptr<Malware>> &listaMalware);

    Computer(double ratingFinal, const vector<shared_ptr<Malware>> &listaMalware);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

};

Computer::Computer() {}

Computer::Computer(int id, double ratingFinal, const vector<shared_ptr<Malware>> &listaMalware) : id(id), rating_final(
        ratingFinal), lista_malware(listaMalware) {}

Computer::Computer(double ratingFinal, const vector<shared_ptr<Malware>> &listaMalware) : rating_final(ratingFinal),

                                                                                          lista_malware(listaMalware) {}

shared_ptr<Malware> citireMalware() {
    cout << "Alegeti tipul de malware:\n";
    cout << "1.Rootkit.\n2.Keylogger.\n3.Kernel-Keylogger.\n4.Ransomware.";
    cout << "Introduceti alegerea facuta:";
    int n;
    cin >> n;
    shared_ptr<Malware> malware;
    if (n == 1) {
        malware = make_shared<Rootkit>();
    } else if (n == 2) {
        malware = make_shared<Keylogger>();
    } else if (n == 3) {
        malware = make_shared<Kernel_Keylogger>();
    } else if (n == 4) {
        malware = make_shared<Ransomware>();
    }
    cin >> *malware;
    return malware;
}

istream &Computer::read(istream &is) {
    IoBase::read(is);
    cout << "Numarul de malwari ce afecteaza acest calculator:";
    int n;
    cin >> n;
    shared_ptr<Malware> curent;
    for (int i = 0; i < n; ++i) {
        curent = citireMalware();
        lista_malware.push_back(curent);
    }

}

ostream &Computer::write(ostream &os) const {
    IoBase::write(os);
    //@TODO
}

class Meniu {
private:
    vector<Computer> computerele_firmei;
public:
    void listeazaOptiuni() {
        cout << "1.Afisarea informatiilor pentru fiecare calculator.\n";
        cout << "2.Afișarea informațiilor pentru fiecare calculator fiind ordonate după ratingul final.\n";
        cout << "3.Afișarea primelor k calculatoare ordonate după ratingul final.\n";
        cout << "4.Afisarea procentului de computere infectate din firmă.\n";
        cout << "5.OPRIRE PROGRAM\n";
    }

    int alegeOptiune() {
        cout << "Alegeti una dintre optiunile de mai jos:\n";
        int alegere;
        listeazaOptiuni();
        cout << "Alegerea facuta:";
        cin >> alegere;
        return alegere;
    }

    void mainLoop() {
        while (true) {
            int alegere = alegeOptiune();
            if (alegere == 1) {

            } else if (alegere == 2) {

            } else if (alegere == 3) {

            } else if (alegere == 4) {

            } else if (alegere == 5) break;
        }
    }
};


int main() {
    Meniu meniu;
    meniu.mainLoop();
    return 0;
}