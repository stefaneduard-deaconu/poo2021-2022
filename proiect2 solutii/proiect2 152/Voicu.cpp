#include <iostream>
#include <vector>
#include<cctype>
#include<algorithm>
#include<string>
#include<stdio.h>
using namespace std;
class Malware {
protected:
    bool isLoaded;
    bool isWritten; //ambele pt kernel keylogger ca sa nu fie afisat/citit dublu
    double rating;
    int zi, luna, an;
    string nume; //getline(cin, nume) ca e mai multe cuvinte
    string registri;
public:
    Malware() {
        isLoaded = false;
        isWritten = false;
    }
    virtual string getTipMalware() {return "impossible";}; // this func should be virtual pure, but we wanted to use "operator >>" so Malware can't be abstract
    friend istream & operator >>(istream &is, Malware & mal);
    friend ostream &operator <<(ostream &is, Malware &mal);
    double getRating() {
        return rating;
    }
};

istream & operator >>(istream &is, Malware & mal) {
    if (mal.isLoaded == true) {
        return is;
    }
    mal.isLoaded = true;
    mal.rating = 0;
    cout << "introdu numele malware-ului:" << endl;
    cin.ignore();
    getline(cin, mal.nume);
    cout << "introdu data infectarii, in formatul zi/luna/an dar separate prin spatii:" << endl;
    cin >> mal.zi >> mal.luna >> mal.an;
    cout << "specifica registrii modificati, separati prin spatiu: " << endl;
    cin.ignore();
    getline(cin, mal.registri);
    int i;
    for (i = 0; i < mal.registri.size() - 7; i++) {
        if (mal.registri.substr(i, 8) == "HKLM-run" || mal.registri.substr(i, 8) == "HKCU-run") {
            mal.rating += 20.0;
        }
    }
    return is;
}
ostream &operator <<(ostream &os, Malware &mal) {
    if (mal.isWritten == true) {
        return os;
    }
    mal.isWritten = true;
    cout << "Malware-ul este de tipul " << mal.getTipMalware() << "care a infectat calculatorul la data de " << mal.zi << "/" << mal.luna << "/" << mal.an << ", are numele " << mal.nume << "si a afectat registrii " << mal.registri << " avand ratingul " << mal.getRating() << endl;
    return os;
}
class Rootkit: virtual public Malware {
private:
    static const string TIP;
    string importuri;
    string stringurisemnificative;
public:
    string getTipMalware() override {return TIP;};
    friend istream & operator >> (istream &is, Rootkit & r);
    friend ostream & operator << (ostream &os, Rootkit & r);
};
const string Rootkit::TIP = "rootkit";
istream & operator >> (istream &is, Rootkit & r) {
    is >> (Malware&)r;
    cout << "introdu stringurile semnificative separate prin spatii:" << endl;
    cin >> r.stringurisemnificative;
    int i;
    string substring;
    for (i = 0; i < r.stringurisemnificative.size() - 3; i++) {
        if (r.stringurisemnificative.substr(i, 4) == "SSDT") {
            r.rating += 100.0;
        }
    }
    for (i = 0; i < r.stringurisemnificative.size() - 30; i++) {
        if (r.stringurisemnificative.substr(i, 31) == "System Service Descriptor Table") {
            r.rating += 100.0;
        }
    }
    for (i = 0; i < r.stringurisemnificative.size() - 11; i++) {
        if (r.stringurisemnificative.substr(i, 12) == "NtCreateFile") {
            r.rating += 100.0;
        }
    }
    cout << "introdu importurile separati prin spatiu: " << endl;
    cin >> r.importuri;
    for (i = 0; i < r.importuri.size() - 11; i++) {
        if (r.importuri.substr(i, 12) == "ntoskrnl.exe") {
            r.rating *= 2.0;
        }
    }
    return is;
}
ostream & operator << (ostream &os, Rootkit & r) {
    os << (Malware&)r;
    cout << "Lista de importuri este " << r.importuri << " si stringurile semnificative sunt " << r.stringurisemnificative << endl;
}
class Keylogger: virtual public Malware {
private:
    string functii;
    string tastespeciale;
public:
    string getTipMalware() override {return "keylogger";};
    friend istream & operator >> (istream &is, Keylogger & k);
    friend ostream & operator << (ostream &os, Keylogger & k);
};
ostream & operator << (ostream &os, Keylogger & k) {
    os << (Malware&)k;
    cout << "functiile folosite sunt " << k.functii << " si tastele speciale sunt " << k.tastespeciale << endl;
}
istream & operator >> (istream &is, Keylogger & k) {
    is >> (Malware&)k;
    cout << "introdu functiile folosite:" << endl;
    cin >> k.functii;
    int i;
    for (i = 0; i < k.functii.size() - 7; i++) {
        cout << k.functii.substr(i, 8);
        if (k.functii.substr(i, 8) == "ReadFile") {
            k.rating += 10.0;
        }
    }
    for (i = 0; i < k.functii.size() - 8; i++) {
        cout << k.functii.substr(i, 9);
        if (k.functii.substr(i, 9) == "WriteFile") {
            k.rating += 10.0;
        }
    }
    for (i = 0; i < k.functii.size() - 10; i++) {
        if (k.functii.substr(i, 11) == "CreateFileW" || k.functii.substr(i, 11) == "OpenProcess") {
            k.rating += 10.0;
        }
    }
    for (i = 0; i < k.functii.size() - 13; i++) {
        if (k.functii.substr(i, 14) == "RegisterHotkey") {
            k.rating += 10.0;
        }
    }
    for (i = 0; i < k.functii.size() - 15; i++) {
        if (k.functii.substr(i, 16) == "SetWindowsHookEx") {
            k.rating += 10.0;
        }
    }
    return is;
}
class KernelKeylogger: public Rootkit, public Keylogger {
public:
    string getTipMalware() override {return "kernel-keylogger";};
    friend istream & operator >> (istream &is, KernelKeylogger & kk);
    friend ostream & operator << (ostream &os, KernelKeylogger & kk);
};
ostream & operator << (ostream &os, KernelKeylogger & kk) {
    os << (Keylogger&)kk;
    os << (Rootkit&)kk;
    return os;
}
istream & operator >> (istream &is, KernelKeylogger & kk) {
    is >> (Keylogger&)kk;
    is >> (Rootkit&)kk;
    return is;
}
class Ransomware: public Malware {
private:
    double rCriptare;
    double rObfuscare;
public:
    string getTipMalware() override {return "ransomware";};
    friend istream & operator >> (istream &is, Ransomware & rw);
    friend ostream & operator << (ostream &os, Ransomware & rw);
};
ostream & operator << (ostream &os, Ransomware & rw) {
    os << (Malware&)rw;
    cout << "rating-ul de criptare este " << rw.rCriptare << " iar cel de obfuscare este " << rw.rObfuscare << endl;
    return os;
}
istream & operator >> (istream &is, Ransomware & rw) {
    is >> (Malware&)rw;
    cout << "introdu ratingurile de criptare si obfuscare separate printr-un spatiu:" << endl;
    cin >> rw.rCriptare >> rw.rObfuscare;
    rw.rating = rw.rObfuscare + rw.rCriptare;
    return is;
}
class Unknown: public Malware {
public:
    string getTipMalware() override {return "unknown";};
    friend istream & operator >> (istream &is, Unknown & unk);
    friend ostream & operator << (ostream &os, Unknown & unk);
};
ostream & operator << (ostream &os, Unknown & unk) {
    return os; //nu facem nimic dar trebuie sa existe
}
istream &operator>> (istream &is, Unknown &unk) {
    is >> (Malware&)unk;
    return is;
}
class Computer {
private:
    //id-ul nu trebuie pentru ca e index-ul din computers.
    vector<Malware> virusi;
    double ratingtotal;
    int id;
public:
    friend istream& operator >>(istream &is, Computer &calc);
    friend ostream& operator <<(ostream &os, Computer &calc);
    void setId(int _id) {
        id = _id;
    }
};
ostream& operator <<(ostream &os, Computer &calc) {
    cout << "Calculatorul cu id-ul " << calc.id << " are rating-ul impactului total de " << calc.ratingtotal << " si are virusii: " << endl;
    int i;
    vector<Malware>::iterator it;
    for (it = calc.virusi.begin(); it != calc.virusi.end(); it++) {
        os << *it;
    }
    return os;
}
istream & operator >> (istream &is, Computer &calc) {
    calc.ratingtotal = 0;
    cout << "cate malware-uri are calculatorul?" << endl;
    int i, n;
    cin >> n;
    for (i = 0; i < n; i++) {
        cout << "introdu tipul de malware :" << endl;
        string tip;
        cin >> tip;
        std::transform(tip.begin(), tip.end(), tip.begin(),
            [](unsigned char c){ return std::tolower(c); });
        if (tip == "rootkit") {
            Rootkit rkt;
            is >> rkt;
            calc.ratingtotal += rkt.getRating();
            calc.virusi.push_back(rkt);
        } else {
            if (tip == "keylogger") {
                Keylogger klgr;
                is >> klgr;
                calc.ratingtotal += klgr.getRating();
                calc.virusi.push_back(klgr);
            } else {
                if (tip == "kernel-keylogger") {
                    KernelKeylogger krnl;
                    is >> krnl;
                    calc.ratingtotal += krnl.getRating();
                    calc.virusi.push_back(krnl);
                } else {
                    if (tip == "ransomware") {
                        Ransomware rmw;
                        calc.ratingtotal += rmw.getRating();
                        is >> rmw;
                        calc.virusi.push_back(rmw);
                    } else {
                        Unknown unk;
                        is >> unk;
                        calc.virusi.push_back(unk);
                    }
                }
            }
        }
    }
    return is;
}
class Companie {
private:
    static int numarinfectari;
    vector<Computer> computers;
public:
    friend istream & operator >>(istream &is, Companie &company);
    friend ostream & operator <<(ostream &os, Companie &company);
    int getSize() {
        return computers.size();
    }
    vector<Computer> getComputers() {
        return computers;
    }
};
istream & operator >>(istream &is, Companie &company) {
    cout << "cate calculatoare are firma?" << endl;
    int n, i;
    cin >> n;
    for (i = 0; i < n; i++) {
        Computer calc;
        is >> calc;
        company.computers.push_back(calc);
    }
return is;
}
ostream & operator <<(ostream &os, Companie &compania) {
    int i, n;
    n = compania.getSize(); //numarul de calculatoare
    for (i = 0; i < n; i++) {
        os << compania.computers[i];
    }
    return os;
}
class SimpleMenu {
public:
    void listOptions() {
        cout << "1. afisarea informatiilor fiecarui calculator" << '\n';
        cout << "2. afisarea informatiilor tuturor calculatoarelor, ordonate dupa rating" << '\n';
        cout << "3. afisarea informatiilor primelor k(valoare introdusa ulterior) calculatoare dupa rating" << '\n';
        cout << "4. afisarea procentului de calculatoare infectate din firma" << '\n';
        cout << "5. iesire" << endl;
    }

    int chooseOption(int first, int last, Companie &compania) {
        int option = -1;
        while (option < first || option > last) {
            cout << '\n';
            cout << "Pentru a rula o comanda alegeti un numar intre "
                 << first << " si " << last << '\n';
            listOptions();
            cout << "Alegere: ";
            cin >> option;
        }
        return option;
    }

    void option1(Companie &compania) {
        cout << compania;
    }

    void option2(Companie &compania) {
        vector<Computer> computers;
        computers = compania.getComputers();
        vector<Computer>::iterator it;
        for (it = computers.begin(); it != computers.end(); it++) {

        }
    }

    void option3(Companie &compania) {
        cout << "Aici vom modifica datele uneia dintre clădirile existente." << '\n';
    }
    void option4(Companie &compania) {

    }
    void mainLoop(Companie &compania) {
        while (true) {
            int option = chooseOption(1, 4, compania);
            if (option == 1) {
                //todo
            } else if (option == 2) {
                option2(compania);
            } else if (option == 3) {
                option3(compania);
            } else if (option == 4) {
                option4(compania);
            } else {
                break;
            }
        }
        cout << '\n'
             << "---------------------------------"
             << '\n'
             << "Program incheiat";
    }

};
int main() {
    string foo = "0123";
    int i = foo.size() - 4;
    string foo2 = foo.substr(i, 4);

    Companie compania;
    cin >> compania;
    SimpleMenu menu;
    menu.mainLoop(compania);
}
