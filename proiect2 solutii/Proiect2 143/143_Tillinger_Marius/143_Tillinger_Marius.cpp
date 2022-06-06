/*  Tillinger Marius 143
 * Mingw
 * Stefan Deaconu
 * */


#include<bits/stdc++.h> //i dont need it but it's good to have anyways
#include <memory>
#include "util/IoBase.h"
#include <typeinfo>

using namespace std;

struct Data {       //data structure for remembering calendar data types
    int zi, luna, an;
};

class Malware : public IoBase {     //clasa Malware va primi functii din Iobase, din exercitiile din laborator
protected:
    float impact;
    Data datainf;
    string nume;
    string metoda;
    vector<string>  registrii;
public:
    Malware() {}

    istream &read(istream &is) override {  //metoda de citire implementata la laborator
        IoBase::read(is);
        cout << endl;
        cout << "Data:\n";
        cout << "zi: "; is >> datainf.zi; cout << endl << "luna: "; is >> datainf.luna; cout << endl << "an: "; is >> datainf.an;
        cout << endl;
        cout << "Nume: ";
        is >> nume; cout << endl;
        string _metoda;
        cout << "Metoda (sau introduceti <NONE>):";
        is >> _metoda;
        cout << endl;
        if (_metoda != "NONE") {
            metoda = _metoda;
        }
        else {
            metoda = "unknown";
        }
        cout << "Registrii (scrieti NONE pentru a trece mai departe): ";
        registrii.clear();
        string registru;

        while ( is>> registru && registru != "NONE") {
            registrii.push_back(registru);
        }

        cout << endl;

        //am citit toate datele importante pentru clasa Malware

        return is;
    }

    ostream &write(ostream &os) const override {        //functie de afisare importata din laboratoare
        IoBase::write(os);
        cout << endl;
        cout << "Impact: ";
        os << impact<<endl;
        cout << "Data: \n";
        cout << "zi: "; os << datainf.zi; cout << ", luna: "; os << datainf.luna; cout << ", an: "; os << datainf.an<<endl;
        cout << "Nume: ";
        os << nume<<endl;
        cout << "Metoda: ";
        os << metoda<<endl;
        cout << "Registrii: ";

        for (int i=0; i<registrii.size(); i++) {
            os << registrii[i] << " ";
        }
        cout<< endl;

        return os;
    }

    virtual float impactCalc();
};

float Malware::impactCalc() {
    Malware::impact = 0;

    for ( int i=0; i<Malware::registrii.size(); i++ ) {
        if ( Malware::registrii[i] == "HKLM-run" || Malware::registrii[i] == "HKCU-run" ) {
            Malware::impact += 20;
        }
    }

    return Malware::impact;
}

class Rootkit: virtual public Malware {     //mostenire clasa Malware
protected:
    vector<string> importuri;
    vector<string> semnificative;
public:
    Rootkit() {}

    istream &read(istream &is) override {       //mostenire functie de citire
        Malware::read(is);
        string import;
        string semnificativ;
        cout << "Importuri (scrieti NONE pentru a trece mai departe): " ;
        importuri.clear();
        semnificative.clear();      //golim vectorii

        while ( is >> import && import != "NONE" ) {
            importuri.push_back(import);
        }

        cout << endl;

        cout << "Semnificative (scrieti NONE pentru a trece mai departe): ";

        while ( is >> semnificativ && semnificativ != "NONE" ) {
            semnificative.push_back(semnificativ);
        }

        cout << endl;

        return is;

        //am citit atributele clasei Rootkit
    }

    ostream &write(ostream &os) const override {        //afisare rootkit
        Malware::write(os);
        cout << "Importuri: ";

        for (int i=0; i<importuri.size(); i++) {
            os << importuri[i] << " ";
        }
        cout<< endl;

        cout << "Semnificative: ";

        for (int i=0; i<semnificative.size(); i++) {
            os << semnificative[i] << " ";
        }
        cout<< endl;

        return os;
    }

    virtual float impactCalc();
};

float Rootkit::impactCalc() {
    Rootkit::impact = 0;

    for ( int i=0; i<Rootkit::registrii.size(); i++ ) {
        if ( Rootkit::registrii[i] == "HKLM-run" || Rootkit::registrii[i] == "HKCU-run" ) {
            Rootkit::impact += 20;
        }
    }

    for ( int i=0; i<Rootkit::importuri.size(); i++ ) {
        if ( Rootkit::importuri[i] == "System Service Descriptor Table" || Rootkit::importuri[i] == "SSDT" || Rootkit::importuri[i] == "NtCreateFile" ) {
            Rootkit::impact += 100;
        }

        if ( Rootkit::importuri[i] == "ntoskrnl.exe" ) {
            Rootkit::impact *= 2;
        }
    }

    return Rootkit::impact;
}

class Keylogger : virtual public Malware {      //alta mostenire
protected:
    vector<string> functii;
    vector<string> taste;
public:
    Keylogger() {}

    istream &read(istream &is) override {       //citire pentru keylogger
        Malware::read(is);
        functii.clear();
        taste.clear();
        cout << "Fuctii (scrieti NONE pentru a trece mai departe): ";
        string functie;
        string tasta;

        while ( is >> functie && functie != "NONE" ) {
            functii.push_back(functie);
        }

        cout << endl;

        cout << "Taste (scrieti NONE pentru a trece mai departe): ";

        while ( is >> tasta && tasta != "NONE" ) {
            taste.push_back(tasta);
        }

        cout << endl;

        return is;
    }

    ostream &write(ostream &os) const override {        //afisare keylogger
        Malware::write(os);
        cout << "Functii: ";

        for (int i=0; i<functii.size(); i++) {
            os << functii[i] << " ";
        }
        cout<< endl;

        cout << "Taste: ";

        for (int i=0; i<taste.size(); i++) {
            os << taste[i] << " ";
        }
        cout<< endl;

        return os;
    }

    virtual float impactCalc();
};

float Keylogger::impactCalc() {
    Keylogger::impact = 0;

    for ( int i=0; i<Keylogger::registrii.size(); i++ ) {
        if ( Keylogger::registrii[i] == "HKLM-run" || Keylogger::registrii[i] == "HKCU-run" ) {
            Keylogger::impact += 20;
        }
    }

    for ( int i=0; i<Keylogger::functii.size(); i++ ) {
        if ( Keylogger::functii[i] == "CreateFileW" || Keylogger::functii[i] == "OpenProcess" || Keylogger::functii[i] == "ReadFile" || Keylogger::functii[i] == "WriteFile" || Keylogger::functii[i] == "RegisterHotKey" || Keylogger::functii[i] == "SetWindowsHookEx" ) {
            Keylogger::impact += 30;
        }
    }

    for (int i=0; i<Keylogger::taste.size(); i++ ) {
        if ( Keylogger::taste[i] == "[Up]" || Keylogger::taste[i] == "[Num Lock]" || Keylogger::taste[i] == "[Down]" || Keylogger::taste[i] == "[Right]" || Keylogger::taste[i] == "[UP]" || Keylogger::taste[i] == "[Left]" || Keylogger::taste[i] == "[PageDown]" ) {
            Keylogger::impact += 10;
        }
    }

    return Keylogger::impact;
}

class Kernel_Keylogger : public Rootkit, public Keylogger {     //mostenire in diamant
protected:
    bool fisiereAscunse;
    bool registriiAscunsi;
public:
    Kernel_Keylogger() {}

    istream &read(istream &is) override {       //cititm proprietatile obiectului mostenit in diamant
        Rootkit::read(is);

        Keylogger::functii.clear();
        Keylogger::taste.clear();
        cout << "Fuctii (scrieti NONE pentru a trece mai departe): ";
        string functie;
        string tasta;

        while ( is >> functie && functie != "NONE" ) {
            Keylogger::functii.push_back(functie);
        }

        cout << endl;

        cout << "Taste (scrieti NONE pentru a trece mai departe): ";

        while ( is >> tasta && tasta != "NONE" ) {
            Keylogger::taste.push_back(tasta);
        }

        cout << endl;

        cout << "Fisiere ascunse? (Da/Nu): ";
        string raspuns;
        cin >> raspuns;

        cout << endl;

        if (raspuns == "Da") {
            fisiereAscunse = true;
            impact += 20;
        }
        else if (raspuns == "Nu") {
            fisiereAscunse = false;
        }

        cout << "Registrii ascunsi? (Da/Nu): ";
        cin >> raspuns;

        cout << endl;

        if (raspuns == "Da") {
            registriiAscunsi = true;
            impact += 30;
        }
        else if (raspuns == "Nu") {
            registriiAscunsi = false;
        }

        return is;
    }

    ostream &write(ostream &os) const override {        //citire Kernel Keylogger la care inca nu stiu daca merge
        Rootkit::write(os);

        cout << "Functii: ";

        for (int i=0; i<Keylogger::functii.size(); i++) {
            os << Keylogger::functii[i] << " ";
        }
        cout<< endl;

        cout << "Taste: ";

        for (int i=0; i<Keylogger::taste.size(); i++) {
            os << Keylogger::taste[i] << " ";
        }
        cout<< endl;

        cout<< "Ascunse: ";

        if (fisiereAscunse) {
            cout << "fisiere au fost ascunse. \n";
        }
        else {
            cout << "fisiere nu au fost ascunse. \n";
        }

        if (registriiAscunsi)  {
            cout << "registrii au fost ascunsi. \n";
        }
        else {
            cout << "registrii nu au fost ascunsi. \n";
        }

        cout <<endl;

        return os;
    }

    float impactCalc();
};

float Kernel_Keylogger::impactCalc() {
    Kernel_Keylogger::impact = 0;

    for ( int i=0; i<Kernel_Keylogger::registrii.size(); i++ ) {
        if ( Kernel_Keylogger::registrii[i] == "HKLM-run" || Kernel_Keylogger::registrii[i] == "HKCU-run" ) {
            Kernel_Keylogger::impact += 20;
        }
    }

    for ( int i=0; i<Kernel_Keylogger::functii.size(); i++ ) {
        if ( Kernel_Keylogger::functii[i] == "CreateFileW" || Kernel_Keylogger::functii[i] == "OpenProcess" || Kernel_Keylogger::functii[i] == "ReadFile" || Kernel_Keylogger::functii[i] == "WriteFile" || Kernel_Keylogger::functii[i] == "RegisterHotKey" || Kernel_Keylogger::functii[i] == "SetWindowsHookEx" ) {
            Kernel_Keylogger::impact += 30;
        }
    }

    for (int i=0; i<Kernel_Keylogger::taste.size(); i++ ) {
        if ( Kernel_Keylogger::taste[i] == "[Up]" || Kernel_Keylogger::taste[i] == "[Num Lock]" || Kernel_Keylogger::taste[i] == "[Down]" || Kernel_Keylogger::taste[i] == "[Right]" || Kernel_Keylogger::taste[i] == "[UP]" || Kernel_Keylogger::taste[i] == "[Left]" || Kernel_Keylogger::taste[i] == "[PageDown]" ) {
            Kernel_Keylogger::impact += 10;
        }
    }

    for ( int i=0; i<Kernel_Keylogger::importuri.size(); i++ ) {
        if ( Kernel_Keylogger::importuri[i] == "System Service Descriptor Table" || Kernel_Keylogger::importuri[i] == "SSDT" || Kernel_Keylogger::importuri[i] == "NtCreateFile" ) {
            Kernel_Keylogger::impact += 100;
        }

        if ( Kernel_Keylogger::importuri[i] == "ntoskrnl.exe" ) {
            Kernel_Keylogger::impact *= 2;
        }
    }

    return Kernel_Keylogger::impact;
}

class Ransomware : public Malware {     //malware public inheritence for malware type ransomware
protected:
    int rating;
    int obfuscare;
public:
    Ransomware() {}

    istream &read(istream &is) override {
        Malware::read(is);
        cout << "Rating: ";
        is >> rating;

        cout << endl;

        cout << "Obfuscare: ";
        is >>obfuscare;

        cout << endl;

        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        cout << "Rating: ";
        os << rating << endl;
        cout << "Obfuscare: ";
        os << obfuscare << endl;

        return os;
    }

    float impactCalc();
};

float Ransomware::impactCalc() {
    Ransomware::impact = 0;
    Ransomware::impact = Ransomware::rating + Ransomware::obfuscare;
    return  Ransomware::impact;
}

//deleted shared_ptr for being useless

class Computer {
protected:
    int id;
    static int current_id;
    vector<shared_ptr<Malware>> listaMalware;
    float ratingFinal;        //ratingul final se calculeaza si este initial 0
public:
    friend istream &operator>>(istream &in, Computer &c);
    friend ostream &operator<<(ostream &out, const Computer &c);

    Computer() : id (current_id++) {}

    int getId();

    const vector<shared_ptr<Malware>> &getListaMalware() const;

    float getRatingFinal();

    bool isInfected();
};

bool Computer::isInfected() {
    if ( Computer::listaMalware.size() > 0 ) {
        return true;
    }
    else {
        return false;
    }
}

int Computer::current_id = 1;

istream &operator>> ( istream &in, Computer &c ) {      //operatorul de citire pentru cate un calculator
    string tip;
    cout << "\n";
    c.listaMalware.clear();
    cout << "Alegeti tipul malwareului din meniul de mai jos sau apasati 5 pentru a merge mai departe\n";
    cout << "Tipul malwareului (1: Rootkit, 2: Keylogger, 3: Kernel-Keylogger, 4: Ransomware): \n";
    shared_ptr<Malware> m;
    while ( cin >> tip ) {         //changing the type of malware we are working with
        if ( tip == "1" ) {
            m = make_shared<Rootkit>();
            cin >> *m;
            c.listaMalware.push_back(m);
            cout << "\n";
            cout << "Alegeti tipul malwareului din meniul de mai jos sau apasati 5 pentru a merge mai departe\n";
            cout << "Tipul malwareului (1: Rootkit, 2: Keylogger, 3: Kernel-Keylogger, 4: Ransomware): \n";
        } else if ( tip == "2" ) {
            m = make_shared<Keylogger>();
            cin >> *m;
            c.listaMalware.push_back(m);
            cout << "\n";
            cout << "Alegeti tipul malwareului din meniul de mai jos sau apasati 5 pentru a merge mai departe\n";
            cout << "Tipul malwareului (1: Rootkit, 2: Keylogger, 3: Kernel-Keylogger, 4: Ransomware): \n";
        } else if ( tip == "3" ) {
            m = make_shared<Kernel_Keylogger>();
            cin >> *m;
            c.listaMalware.push_back(m);
            cout << "\n";
            cout << "Alegeti tipul malwareului din meniul de mai jos sau apasati 5 pentru a merge mai departe\n";
            cout << "Tipul malwareului (1: Rootkit, 2: Keylogger, 3: Kernel-Keylogger, 4: Ransomware): \n";
        } else if ( tip == "4" ) {
            m = make_shared<Ransomware>();
            cin >> *m;
            c.listaMalware.push_back(m);
            cout << "\n";
            cout << "Alegeti tipul malwareului din meniul de mai jos sau apasati 5 pentru a merge mai departe\n";
            cout << "Tipul malwareului (1: Rootkit, 2: Keylogger, 3: Kernel-Keylogger, 4: Ransomware): \n";
        } else {
            break;
        }
    }
    cout << endl;

    return in;
}

int Computer::getId() {
    return id;
}

const vector<shared_ptr<Malware>> &Computer::getListaMalware() const {
    return listaMalware;
}

float Computer::getRatingFinal() {
    Computer::ratingFinal = 0;

    for ( int i=0 ; i<Computer::listaMalware.size(); i++ ) {
        Computer::ratingFinal = Computer::ratingFinal + Computer::listaMalware[i]->impactCalc();
    }
    return Computer::ratingFinal;
}
//automatic id incrementation


class Meniu {       //basic menu class for adding interface
private:
    vector<Computer> calculatoare;
public:

    void listeazaOptiuni() {
        cout << endl;
        cout << "1. afisarea informatiilor pentru fiecare calculator \n";
        cout << "2. afisarea informatiilor pentru fiecare calculator fiind ordonate dupa ratingul final \n";
        cout << "3. afisarea primelor k calculatoare ordonate dupa ratingul final \n";
        cout << "4. afisarea procentului de computere infectate din firma \n";
        cout << "5. Cititi n calculatoare si m malware uri pentru fiecare calculator \n";
        cout << "6. Stop \n";
    }
    //option picker
    int alegeOptiune() {
        int option;

        cout << "\nAlegeti o optiune: ";
        cin >> option;
        cout<<endl;

        if ( option >=1 && option <=6 && option == (int) option ) {
            return option;
        }
    }
    //main loop
    void run() {
        // meniul interactiv
        while(true) {
            listeazaOptiuni();
            // alegem optiune
            int option = alegeOptiune();
            if (option == 5) {
                citireCalc();
            }else if (option >6 || option <1) {
                cout << "Nu ai aceasta optiune, mai incearca :)\n\n";
            } else if (option == 1) {
                afisareCalc();
            } else if (option == 2) {
                afisareOrd();
            } else if (option == 3) {
                afisarePrimeK();
            } else if (option == 4) {
                afisareProcent();
            } else if (option == 6) {
                cout << "----------------------------------------------||----------------------------------------------------\n";
                calculatoare.clear();
                break;
            }
        }
    }

    //menu functions

    void citireCalc();
    void afisareCalc();
    void afisareOrd();
    void afisarePrimeK();
    void afisareProcent();

};

void Meniu::citireCalc () {
    int n;
    cout << "Numarul calculatoarelor: "; cin >> n; cout << endl;      //input nr of computers

    for ( int i=0; i<n; i++ ) {
        Computer c;
        cout << "Adaugati calculator: "; cin >> c;      //read every computer and adding it to the list of computers in the firm
        Meniu::calculatoare.push_back(c);
    }
}

void Meniu::afisareCalc() {

    for ( int i=0; i<Meniu::calculatoare.size(); i++ ) {
        cout << "Calculatorul cu id: " << Meniu::calculatoare[i].getId() << ", ";

        if (Meniu::calculatoare[i].getListaMalware().size() != 0 ) {
            cout << "cu lista de malwareuri: ";

            for (int j = 0; j < Meniu::calculatoare[i].getListaMalware().size(); j++) {
                Meniu::calculatoare[i].getListaMalware()[j]->impactCalc();
                cout << *Meniu::calculatoare[i].getListaMalware()[j];
            }
            cout << "cu ratingul final de: " << Meniu::calculatoare[i].getRatingFinal() << "\n\n";

        } else {
            cout << "fara malwareuri, cu ratingul final de: " << Meniu::calculatoare[i].getRatingFinal() << "\n\n";
        }
    }
}

void Meniu::afisareOrd() {
    sort ( Meniu::calculatoare.begin(), Meniu::calculatoare.end(), [](Computer a, Computer b) {return a.getRatingFinal() < b.getRatingFinal();});
    Meniu::afisareCalc();
}

void Meniu::afisarePrimeK() {
    sort ( Meniu::calculatoare.begin(), Meniu::calculatoare.end(), [](Computer a, Computer b) {return a.getRatingFinal() < b.getRatingFinal();});

    int k;
    cout << "\nSpecificati cate calculatoare sa afisati: "; cin >> k;

    for ( int i = 0 ; i < k ; i ++ ) {
        cout << "Calculatorul cu id: " << Meniu::calculatoare[i].getId() << ", ";

        if (Meniu::calculatoare[i].getListaMalware().size() != 0 ) {
            cout << "cu lista de malwareuri: ";

            for (int j = 0; j < Meniu::calculatoare[i].getListaMalware().size(); j++) {
                Meniu::calculatoare[i].getListaMalware()[j]->impactCalc();
                cout << *Meniu::calculatoare[i].getListaMalware()[j];
            }
            cout << "cu ratingul final de: " << Meniu::calculatoare[i].getRatingFinal() << "\n\n";

        } else {
            cout << "fara malwareuri, cu ratingul final de: " << Meniu::calculatoare[i].getRatingFinal() << "\n\n";
        }
    }
}

void Meniu::afisareProcent() {
    float procent;
    float lenght;
    float contor;
    for ( int i = 0 ; i < Meniu::calculatoare.size(); i++ ) {
        if ( Meniu::calculatoare[i].isInfected() ) {
            contor++;
        }
    }
    lenght = Meniu::calculatoare.size();
    procent = contor / lenght * 100 ;

    cout << procent << "%" << "\n";
}

int main() {
    Meniu m;
    m.run();
    return 0;
}