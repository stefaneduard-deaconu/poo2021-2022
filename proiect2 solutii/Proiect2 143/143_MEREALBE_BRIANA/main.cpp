//143
//MEREALBE CRIS-BRIANA
//de unde aflu ce compilator folosesc? 0-0


#include <iostream>
#include <memory>
#include <vector>
#include "util/IoBase.h"
#include "util/functions.h"

//#include <bits/stdc++.h>

using namespace std;

//Prin malware înțelegem un software rău intenționat pentru care se reține ratingul impactului
// (număr real), data de infectare (zi, luna, an), numele acestuia (care poate să fie format din
// mai multe cuvinte), metoda de infectare (dacă se cunoaște, altfel se reține șirul “unknown”) și
// un vector cu registrii modificați (reținuți ca stringuri).
//TODO:Aici am creat clasa de baza a unui virus - IMPACTUL, DATA, NUMELE VIRUSULUI, TIPUL DE INFECTARE, REGISTRII AFECTATI
class Malware : public IoBase {
protected:
    double impact;
    int zi,an,luna;
    string nume, infectare;
    vector <string> registrii;
public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    virtual double CalculeazaRating();

    Malware();
    Malware(double impact, int zi,int luna,int an, const string &nume, const string &infectare,
            const vector<string> &registrii):impact(impact), zi(zi), luna(luna), an(an), nume(nume),
                                             infectare(infectare), registrii(registrii) {}

    virtual ~Malware();
};
Malware::Malware():registrii() {
    impact = 0;
    zi = 0;
    luna = 0;
    an = 0;
    infectare = "";
    nume = "";
}

Malware::~Malware() {
    impact = 0;
    zi = luna = an = 0;
    nume.clear();
    infectare.clear();
    registrii.clear();
}
//TODO: Functia de citire generala a unui virus
istream &Malware::read(istream &is) {
    IoBase::read(is);

    cout << "Impact:\n";
    is >> impact;
    cout << "Data infectarii\n";
    cout<<"Zi:\n";
    is >> zi;
    cout << "Luna:\n";
    is >> luna;
    cout << "An:\n";
    is >> an;
    cout << "Numele virusului:\n";
    is >> nume;
    cout << "Tipul de infectare:\n";
    is >> infectare;
    int nr;
    while (true){
        try{
            cout << "nr de registrii afectati: ";
            is >> nr;
            is.get();
            if(nr<0)
                throw string("nr invalid!");
            else break;
        }
        catch (string s){
            cout << s << "\n";
        }
    }
    for (int i = 0; i < nr; ++i) {
        cout << "registrul:\n";
        string s;
        getline(is,s);
        registrii.push_back(s);

    }

    return is;

}
//TODO: Functia de afisare generala a unui virus
ostream &Malware::write(ostream &os) const {
    IoBase::write(os);

    os << "Impact: " << impact << "\n";
    os << "Data infectarii: "<< zi << "." << luna << "." << an << "\n";
    os << "Numele virusului: " << nume << "\n";
    os << "Tipul de infectare: " << infectare << "\n";
    os << "Registrii afectati: " << "\n";
    for(int i=0; i<registrii.size(); i++)
        os << registrii[i]<< "\n";

    os << "\n";

    return os;

}
//TODO: Functia care imi calculeaza ratingul final; se va adauga la ea in functie de tipul de malware
double Malware::CalculeazaRating() {
    double rating;
    rating+=impact;
    for(int i=0; i<registrii.size(); i++)
        if(registrii[i]=="HKLM-run" || registrii[i]=="HKCU-run")
            rating=rating+20;

    return  rating;

}

//Prin rootkit înțelegem un tip de malware ce are drept scop obținerea
// drepturilor de administrator asupra dispozitivului infectat. Pentru
// rootkit se reține lista importurilor care poate fi unul și oricât de
// multe (importurile fac referire la numele fișierelor .dll folosite)
// și o listă de stringuri semnificative (anumite stringuri dintr-un
// binar pot fi un indice asupra faptului că fișierul este rău intenționat).
//TODO: ROOTKIT - IMPORTURI, STRINGURI SEMNIFICATIVE + TOT DE LA MALWARE
class Rootkit : virtual public Malware {
protected:
    vector <string> importuri;
    vector <string> semnificative;
public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    double CalculeazaRating() override;

    Rootkit();
    virtual  ~Rootkit();
    Rootkit(double impact, int zi,int luna,int an, const string &nume, const string &infectare,
            const vector<string> &registrii, const vector<string> &importuri,
            const vector<string> &semnificative) : Malware(impact, zi, luna, an, nume, infectare, registrii),
                                                   importuri(importuri), semnificative(semnificative){}

};

Rootkit::Rootkit():Malware(),  importuri(), semnificative(){}
Rootkit::~Rootkit(){
    importuri.clear();
    semnificative.clear();
}
//TODO: Citire
istream &Rootkit::read(istream &is) {
    Malware::read(is);

    int nr1,nr2;
    while (true){
        try{
            cout << "nr de importuri: ";
            is >> nr1;
            is.get();
            if(nr1<0)
                throw string("nr invalid!");
            else break;
        }
        catch (string s){
            cout << s << "\n";
        }
    }
    for (int i = 0; i < nr1; ++i) {
        cout << "importul:\n";
        string s;
        getline(is,s);
        importuri.push_back(s);

    }
    while (true){
        try{
            cout << "nr de stringuri semnificative: ";
            is >> nr2;
            is.get();
            if(nr2<0)
                throw string("nr invalid!");
            else break;
        }
        catch (string s){
            cout << s << "\n";
        }
    }
    for (int i = 0; i < nr2; ++i) {
        cout << "stringul semnificativ:\n";
        string s;
        getline(is,s);
        semnificative.push_back(s);

    }

    return is;

}
//TODO: Afisare
ostream &Rootkit::write(ostream &os) const {
    os << "Rootkit\n";
    Malware::write(os);

    os << "Importuri:\n";
    for(int i=-0; i<importuri.size(); i++)
        os << importuri[i] << "\n";
    os << "Stringuri semnificative:\n";
    for(int i=-0; i< semnificative.size(); i++)
        os << semnificative[i] << "\n";

    os << "\n";

    return os;

}
//TODO: Rating final
double Rootkit::CalculeazaRating() {
    double rating=Malware::CalculeazaRating();

    for(int i = 0; i < semnificative.size(); i++)
        if(semnificative[i]=="System Service Descriptor Table" || semnificative[i]=="SSDT" ||  semnificative[i]=="NtCreateFile")
            rating+=100;
    for (int i = 0; i < importuri.size(); ++i)
        if(importuri[i]=="ntoskrnl.exe")
            rating=rating*2;

    return rating;

}

//Prin keylogger înțelegem un malware care înregistrează acțiunile de
// la tastatură și le trimite mai departe. Pentru un keylogger se
// reține o listă cu funcțiile folosite și o listă cu tastele speciale
// definite.
//TODO: KEYLOGGER - FUNCTII FOLOSITE, TASTE + TOT DE LA MALWARE
class Keylogger : virtual public Malware{
protected:
    vector <string> functii;
    vector <string> taste;
public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    double CalculeazaRating() override;

    Keylogger();
    virtual ~Keylogger();
    Keylogger(double impact, int zi,int luna,int an, const string &nume, const string &infectare,
              const vector<string> &registrii, const vector<string> &functii, const vector<string> &taste) :
            Malware(impact, zi, luna, an, nume, infectare, registrii), functii(functii), taste(taste){}
};

Keylogger::Keylogger():Malware(),  functii(), taste(){}
Keylogger::~Keylogger(){
    functii.clear();
    taste.clear();
}
//TODO: Citire
istream &Keylogger::read(istream &is) {
    Malware::read(is);

    int nr1,nr2;
    while (true){
        try{
            cout << "nr de functii folosite: ";
            is >> nr1;
            is.get();
            if(nr1<0)
                throw string("nr invalid!");
            else break;
        }
        catch (string s){
            cout << s << "\n";
        }
    }
    for (int i = 0; i < nr1; ++i) {
        cout << "functie:\n";
        string s;
        getline(is,s);
        functii.push_back(s);

    }
    while (true){
        try{
            cout << "nr de taste special definite: ";
            is >> nr2;
            is.get();
            if(nr2<0)
                throw string("nr invalid!");
            else break;
        }
        catch (string s){
            cout << s << "\n";
        }
    }
    for (int i = 0; i < nr2; ++i) {
        cout << "tasta special definita:\n";
        string s;
        getline(is,s);
        taste.push_back(s);

    }

    return is;

}
//TODO: Afisare
ostream &Keylogger::write(ostream &os) const {
    os << "Keylogger";
    Malware::write(os);

    os << "Functii:\n";
    for(int i=-0; i<functii.size(); i++)
        os << functii[i] << "\n";
    os << "Taste:\n";
    for(int i=-0; i<taste.size(); i++)
        os << taste[i] << "\n";

    os << "\n";

    return os;

}
//TODO: Rating final
double Keylogger::CalculeazaRating() {
    double rating=Malware::CalculeazaRating();

    for (int i = 0; i < taste.size(); ++i)
        if(taste[i] == "[Up]" || taste[i] == "[Num Lock]" || taste[i] == "[Down]" || taste[i] == "[Right]"
        || taste[i] == "[UP]" || taste[i] == "[Left]" || taste[i] == "[PageDown]")
            rating+=10;
    for (int i = 0; i < functii.size(); ++i)
        if(functii[i] == "CreateFileW" || functii[i] == "OpenProcess" || functii[i] == "ReadFile" || functii[i] == "WriteFile" || functii[i] == "RegisterHotKey" || functii[i] == "SetWindowsHookEx")
            rating+=30;

    return rating;

}

//Prin kernel-keylogger înțelegem un keylogger ce rulează în kernel-mode (de obicei
// prin intermediul unui rootkit). Prin urmare, putem considera că este are atât
// proprietățile unui rootkit cât și ale unui keylogger. În plus, dorim să memorăm
// dacă ascunde fișiere și registrii.
//TODO: KERNEL-KEYLOGGER: DACA ASCUNDE SAU NU FISIERE & REGISTRII + TOT DE LA MALWARE, ROOTKIT, KEYLOGGER
class KernelKeylogger : virtual  public Rootkit, virtual public Keylogger {
protected:
    bool ascunde_fisiere;
    bool ascunde_registrii;
public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    double CalculeazaRating() override;

    KernelKeylogger() = default;
    ~KernelKeylogger();
    KernelKeylogger(double impact, int zi, int luna, int an, const string &nume, const string &infectare,
                    const vector<string> &registrii, const vector<string> &importuri,
                    const vector<string> &semnificative, const vector<string> &functii, const vector<string> &taste, bool ascunde_fisiere, bool ascunde_registrii);

};

KernelKeylogger::KernelKeylogger(double impact, int zi, int luna, int an, const string &nume,
                                 const string &infectare, const vector <string> &registrii,
                                 const vector <string> &importuri, const vector <string> &semnificative,
                                 const vector <string> &functii, const vector <string> &taste,
                                 bool ascunde_fisiere, bool ascunde_registrii) :
        Malware (impact, zi, luna, an, nume, infectare, registrii),
        ascunde_fisiere(ascunde_fisiere), ascunde_registrii(ascunde_registrii) {

                    this->importuri = importuri;
                    this->semnificative = semnificative;
                    this->functii = functii;
                    this->taste = taste;

}


KernelKeylogger::~KernelKeylogger(){
    ascunde_fisiere = ascunde_registrii = 0;
}
//TODO: Citire
istream &KernelKeylogger::read(istream &is) {
    Rootkit::read(is);

    int nr1,nr2;
    while (true){
        try{
            cout << "nr de functii folosite: ";
            is >> nr1;
            is.get();
            if(nr1<0)
                throw string("nr invalid!");
            else break;
        }
        catch (string s){
            cout << s << "\n";
        }
    }
    for (int i = 0; i < nr1; ++i) {
        cout << "functie:\n";
        string s;
        getline(is,s);
        functii.push_back(s);

    }
    while (true){
        try{
            cout << "nr de taste special definite: ";
            is >> nr2;
            is.get();
            if(nr2<0)
                throw string("nr invalid!");
            else break;
        }
        catch (string s){
            cout << s << "\n";
        }
    }
    for (int i = 0; i < nr2; ++i) {
        cout << "tasta special definita:\n";
        string s;
        getline(is,s);
        taste.push_back(s);

    }
    cout << "Poate sa ascunda fisiere (introduceti 1 pt DA si 0 pt NU)\n";
    is >> ascunde_fisiere;
    cout << "Poate sa ascunda registrii (introduceti 1 pt DA si 0 pt NU)\n";
    is >> ascunde_registrii;

    return is;

}
//TODO: Afisare
ostream &KernelKeylogger::write(ostream &os) const {
    os << "Kernel-Keylogger\n";
    Malware::write(os);

    os << "Importuri:\n";
    for(int i=-0; i<importuri.size(); i++)
        os << importuri[i] << "\n";
    os << "Stringuri semnificative:\n";
    for(int i=-0; i< semnificative.size(); i++)
        os << semnificative[i] << "\n";
    os << "Functii:\n";
    for(int i=-0; i<functii.size(); i++)
        os << functii[i] << "\n";
    os << "Taste:\n";
    for(int i=-0; i<taste.size(); i++)
        os << taste[i] << "\n";
    string sir1, sir2;
    if(ascunde_fisiere==1)
        sir1="DA";
    else sir1="NU";
    if(ascunde_registrii==1)
        sir2="DA";
    else sir2="NU";
    os << "Poate sa ascunda fisiere " << sir1 << "\n";
    os << "Poate sa scunda registrii " << sir2 << "\n";

    os << "\n";

    return os;

}
//TODO: Rating final
double KernelKeylogger::CalculeazaRating() {
    double rating=Rootkit::CalculeazaRating();

    for (int i = 0; i < taste.size(); ++i)
        if(taste[i] == "[Up]" || taste[i] == "[Num Lock]" || taste[i] == "[Down]" || taste[i] == "[Right]"
           || taste[i] == "[UP]" || taste[i] == "[Left]" || taste[i] == "[PageDown]")
            rating+=10;
    for (int i = 0; i < functii.size(); ++i)
        if(functii[i] == "CreateFileW" || functii[i] == "OpenProcess" || functii[i] == "ReadFile" || functii[i] == "WriteFile" || functii[i] == "RegisterHotKey" || functii[i] == "SetWindowsHookEx")
            rating+=30;

    if(ascunde_registrii == 1)
        rating+=30;
    if(ascunde_fisiere == 1)
        rating+=20;

    return rating;

}

//Prin ransomware înțelegem un malware care criptează fișiere de pe disk.
// Pentru acesta se reține ratingul de criptare (un număr de la 1 la 10)
// și un rating de obfuscare (un număr real ce reprezintă procentul de
// obfuscare (obfuscare = metodă de a ascunde/îngreuna intenția inițială a codului)).
//TODO: RANSOMWARE - RATING DE CRIPTARE SI DE OBFUSCARE + TOT DE LA MALWARE
class  Ransomware : public Malware{
protected:
    int ratingCriptare;
    double ratingObfuscare;
public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    double CalculeazaRating() override;

    Ransomware();
    ~Ransomware();
    Ransomware(double impact, int zi, int luna, int an, const string &nume, const string &infectare,
               const vector<string> &registrii, double ratingCriptare, double ratingObfuscare):
            Malware(impact, zi, luna, an, nume, infectare, registrii), ratingCriptare(ratingCriptare),
            ratingObfuscare(ratingObfuscare){}
};

Ransomware::Ransomware():Malware() {
    impact = 0;
    zi = 0;
    luna = 0;
    an = 0;
    infectare = "";
    nume = "";
    ratingCriptare= 0;
    ratingObfuscare = 0;

}
Ransomware::~Ransomware() {
    ratingCriptare = ratingObfuscare = 0;
}
//TODO: Citire
istream &Ransomware::read(istream &is) {
    Malware::read(is);

    cout << "Rating criptare: \n";
    is >> ratingCriptare;
    cout << "Rating obfuscare: \n";
    is >> ratingObfuscare;

    return is;

}
//TODO: Afisare
ostream &Ransomware::write(ostream &os) const {
    os << "Ransomware\n";
    Malware::write(os);

    os << "Rating criptare: " << ratingCriptare << "\n";
    os << "Rating obfuscare: " << ratingObfuscare << "\n";

    os << "\n";

    return os;

}
//TODO: Rating final
double Ransomware::CalculeazaRating() {
    double rating=Malware::CalculeazaRating();
    rating+=ratingObfuscare;
    rating+=ratingCriptare;

    return rating;

}

//Pentru fiecare computer din firmă se reține un id unic, incrementat
// automat, o listă de malware (poate conține un malware sau mai multe)
// și ratingul final ce este calculat drept suma ratingului impactului
// fiecărui malware.
//TODO: Clasa CALCULATOARELOR - ID, VECTOR DE VIRUSI SI RATING FINAL
class Computer : public IoBase{
protected:
    static int nr;
    int id;
    vector <shared_ptr<Malware> > virusi;
    double ratingFinal;
public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    Computer();

    double getRatingFinal() const;

};

//TODO: ID
int Computer::nr = 0;
Computer::Computer() : virusi(){
    ++nr;
    id=nr;
    ratingFinal = 0;
}
//TODO: Citirea
istream &Computer::read(istream &is) {
    IoBase::read(is);

    int nr;
    while (true){
        try{
            cout << "Cate malware-uri are computer-ul?\n";
            is >> nr;
            is.get();
            if(nr<0)
                throw string("nr invalid!");
            else break;
        }
        catch (string s){
            cout << s << "\n";
        }
    }
    int tip;
    for (int i = 0; i < nr; ++i) {

        cout << "Introduceti 1 pt malware de tip Rootkit, 2 pt Keylogger, 3 pt Kernel-Keylogger si 4 pt Ransomware:\n";
        cin >> tip;
        if(tip == 1){
            Rootkit m;
            is >> m;
            virusi.emplace_back(make_shared<Rootkit>(m));
            ratingFinal+=m.CalculeazaRating();
        }
        else if(tip == 2){
            Keylogger m;
            is >> m;
            virusi.emplace_back(make_shared<Keylogger>(m));
            ratingFinal+=m.CalculeazaRating();
        }
        else if (tip == 3){
            KernelKeylogger m;
            is >> m;
            virusi.emplace_back(make_shared<KernelKeylogger>(m));
            ratingFinal+=m.CalculeazaRating();
        }
        else if(tip == 4){
            Ransomware m;
            is >> m;
            virusi.emplace_back(make_shared<Ransomware>(m));
            ratingFinal+=m.CalculeazaRating();
        }
        else if(tip == 5)
            break;
    }

    return is;

}
//TODO: Afisarea
ostream &Computer::write(ostream &os) const {
    IoBase::write(os);
    os << id <<".Computer:\n";
    if(virusi.size()>0)
        os << "Toate malware-urile:\n";
    else
        os << "Niciun malware. All good!";
    for(const auto &i: virusi){
        auto *rootkit=dynamic_cast<Rootkit*>(i.get());
        auto *keylogger=dynamic_cast<Keylogger*>(i.get());
        auto *kernel=dynamic_cast<KernelKeylogger*>(i.get());
        auto *ransomware=dynamic_cast<Ransomware*>(i.get());

        if(ransomware)
        os << *ransomware;
        else if(keylogger)
            os << *keylogger;
        else if(kernel)
            os << *kernel;
        else if(rootkit)
            os << *rootkit;

    }
    os << "\n";

    return os;

}
//TODO: Getter ca sa accesez ratingul final
double Computer::getRatingFinal() const {
    return ratingFinal;
}



class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};
//TODO: MENIUL INTERACTIV
class SimpleMenu : public BaseMenu {
private:
    vector<Computer*> computers;
public:
    //TODO: OPTIONS
    void listOptions()  override {
        cout << "1. Citire n calculatoare cu cate m malwares. " << '\n';
        cout << "2. Afisare n calculatoare cu cate m malwares in ordinea infectarii." << '\n';
        cout << "3. Afisarea primelor k calculatoare ordonate dupa ratingul final. " << '\n';
        cout << "4. Afisarea procentului de calculatoare infectate din firma. " << '\n';
        cout << "5. Gata" << '\n';
    }
//TODO: CHOOSE OPTION
    int chooseOption(int first, int last) override {
        int option = -1;
        while (option < first || option > last) {
            cout << '\n';
            cout << "Pentru a rula comanda, alegeti un numar intre "
                 << first << " si " << last << '\n';
            listOptions();
            cout << "Alegere: ";
            cin >> option;
        }
        return option;
    }
//TODO:NEW COMPUTER
    void citireComputers() {
        int n;
        cout << "Cate computere doriti sa introduceti?\n";
        cin >> n;
        // citirea a n calculatoare

        for (int i = 0; i < n; ++i) {
            Computer *c=new Computer;
            cout<<"Computer nou:\n";
            cin>>*c;
            computers.push_back(c);
        }


    }
//TODO: ALL COMPUTERS
    void afisareComputers() {
//         afisarea calculatoarelor in ordine:
        for(int i = 0;i < computers.size(); ++i)
            for(int j = i+1;j < computers.size(); ++j)
                if(computers[i]->getRatingFinal() > computers[j]->getRatingFinal())
                    swap(computers[i],computers[j]);

        for(int i = 0;i < computers.size(); ++i)
            cout << *computers[i] << '\n';
        cout << '\n';

    }
//TODO: K COMPUTERS
    void afisareKcomputers() {
        cout << "Cate calculatoare doriti sa afiseze?";
        int k;
        cin >> k;
        for(int i = 0;i < computers.size(); ++i)
            for(int j = i+1;j < computers.size(); ++j)
                if(computers[i]->getRatingFinal() > computers[j]->getRatingFinal())
                    swap(computers[i],computers[j]);
        cout << "Cele " << k << " calculatoare sunt:\n";
        for(int i = 0 ;i < k && i < computers.size(); ++i)
            cout << *computers[i] << '\n';
        cout << '\n';
    }
//TODO: PROCENTUL
    void ComputersInfectedPercentage() {

        double percent;
        int nr = 0;
        for(int i = 0;i < computers.size();++i)
            if(computers[i]->getRatingFinal() != 0)
                ++nr;
        if(computers.size()) {
            percent = 100.0 * ((double) nr) / ((double) computers.size());
            if(percent == 0)
                cout << "Toate calculatoarele sunt safe\n";
            else
                cout << "Procent: " << percent << "%" << '\n';
        }
        else
            cout << "Nu exista calculatoare\n";
    }

//TODO: LOOP
    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 5);
            if (option == 1) {
                citireComputers();
            } else if (option == 2) {
                afisareComputers();
            } else if (option == 3) {
                afisareKcomputers();
            } else if (option == 4) {
                ComputersInfectedPercentage();
            } else if (option == 5) {
                break;
            }
        }
        cout << '\n'
             << "---------------------------------"
             << '\n'
             << "Programul s-a incheiat cu success <3";
    }

};

int main() {

    SimpleMenu menu;
    menu.mainLoop();
    return 0;
    //TODO: DONE <3
}