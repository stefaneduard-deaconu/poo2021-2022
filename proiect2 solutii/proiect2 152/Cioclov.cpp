#include <iostream>
#include <string>
#include <vector>
#include "IoBase.h"
#include <memory>
#include <algorithm>

using namespace std;

class Malware : public IoBase{
protected:
    float ratingImpact=0;
    int zi, luna, an;
    string nume, metodaInfectare;
    vector<string> registri;
public:

    Malware() {};

    Malware(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
            const vector<string> &registri);

    float getRatingImpact() const{
        return ratingImpact;
    }

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

};



istream& Malware::read(istream &is) {
    IoBase::read(is);
    cout<<"zi: ";
    is>>zi;
    cout<<"luna: ";
    is>>luna;
    cout<<"an: ";
    is>>an;
    cin.get();
    cout<<"nume: ";
    getline(cin, nume);
    cout<<"metodaInfectare: ";
    getline(cin, metodaInfectare);
    int n; string registru;
    cout<<"nr registri modificati: ";
    is>>n; string r;
    for(int i=0;i<n;i++) is>>r, registri.push_back(r);
    return is;
}
ostream& Malware::write(ostream &os) const{
    IoBase::write(os);
    cout<<"ratingImpact: "<<ratingImpact<<endl;
    cout<<"zi: "<<zi<<endl;
    cout<<"luna: "<<luna<<endl;
    cout<<"an: "<<an<<endl;
    cout<<"nume: "<<nume<<endl;
    cout<<"metodaInfectare: "<<metodaInfectare<<endl;
    cout<<"registri modificati: ";
    for(auto s: registri) cout<<s<<" ";
    cout<<endl;
    return os;
}

Malware::Malware(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
                 const vector<string> &registri) : zi(zi), luna(luna), an(an), nume(nume),
                                                   metodaInfectare(metodaInfectare), registri(registri) {}

class Rootkit: virtual public Malware{
    vector<string> importuri;
    vector<string> stringuri;
public:
    Rootkit() { };

    Rootkit(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
            const vector<string> &registri, const vector<string> &importuri, const vector<string> &stringuri);

    istream &read(istream &is) override ;
    ostream &write(ostream &os) const override ;

    void ratingRootkit(){
        for(auto s: stringuri)
            if(s == "System Service Descriptor Table" ||
               s == "SSDT" || s == "NtCreateFile") ratingImpact += 100;
        for(auto i: importuri)
            if(i == "ntoskrnl.exe") ratingImpact *= 2;
    }
};


istream& Rootkit::read(istream &is){
    Malware::read(is);
    int n; string s;
    cout<<"nr importuri: ";
    cin>>n;
    for(int i=0;i<n;i++) cin>>s, importuri.push_back(s);
    cout<<"nr stringuri: ";
    cin>>n; cin.get();
    for(int i=0;i<n;i++) getline(cin, s), stringuri.push_back(s);
    ratingRootkit();
    return is;
}
ostream& Rootkit::write(ostream &os) const{
    Malware::write(os);
    cout<<"lista importuri: : ";
    for(auto s: importuri) cout<<s<<" ";
    cout<<endl;
    cout<<"lista stringuri semnificative: ";
    for(auto s: stringuri) cout<<s<<endl;
    return os;
}

Rootkit::Rootkit(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
                 const vector<string> &registri, const vector<string> &importuri, const vector<string> &stringuri)
        : Malware(zi, luna, an, nume, metodaInfectare, registri), importuri(importuri),
          stringuri(stringuri) {ratingRootkit();}


class Keylogger : virtual public Malware{
    vector<string> functii;
    vector<string> taste;
public:
    Keylogger(){}

    Keylogger(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
              const vector<string> &registri, const vector<string> &functii, const vector<string> &taste);

    istream &read(istream &is) override ;
    ostream &write(ostream &os) const override ;

    void ratingKeylogger(){
        for(auto f: functii)
            if(f=="CreateFileW" || f=="OpenProcess" || f=="ReadFile" || f=="WriteFile" || f=="RegisterHotKey" || f=="SetWindowsHookEx")
                ratingImpact += 30;
        for(auto t: taste)
            if(t=="[Up]" || t=="[Num Lock]" || t=="[Down]" || t=="[Right]" || t=="[UP]" || t=="[Left]" || t=="[PageDown]")
                ratingImpact += 10;
    }

};

istream &Keylogger::read(istream &is) {
    Malware::read(is);
    int n; string s;
    cout<<"nr functii: ";
    cin>>n;
    for(int i=0;i<n;i++) cin>>s, functii.push_back(s);
    cout<<"nr taste: ";
    cin>>n;
    for(int i=0;i<n;i++) cin>>s, taste.push_back(s);
    ratingKeylogger();
    return is;
}
ostream &Keylogger::write(ostream &os) const {
    Malware::write(os);
    cout<<"lista functii folosite: ";
    for(auto s: functii) cout<<s<<" ";
    cout<<endl;
    cout<<"lista taste speciale definite: ";
    for(auto s: taste) cout<<s<<" ";
    cout<<endl;
    return os;
}

Keylogger::Keylogger(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
                     const vector<string> &registri, const vector<string> &functii, const vector<string> &taste)
        : Malware(zi, luna, an, nume, metodaInfectare, registri), functii(functii), taste(taste) {}


class KernelKeylogger: public Rootkit, public Keylogger{
    bool ascundeFisiere, ascundeRegistri;
public:

    KernelKeylogger(){}

    KernelKeylogger(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
                    const vector<string> &registri, const vector<string> &importuri, const vector<string> &stringuri,
                    int zi1, int luna1, int an1, const string &nume1, const string &metodaInfectare1,
                    const vector<string> &registri1, const vector<string> &functii, const vector<string> &taste,
                    bool ascundeFisiere, bool ascundeRegistri);

    istream &read(istream &is) override ;
    ostream &write(ostream &os) const override ;

    void ratingKernelKeylogger(){
        ratingRootkit();
        ratingKeylogger();
        if(ascundeFisiere) ratingImpact += 20;
        if(ascundeRegistri) ratingImpact += 30;
    }

};

istream &KernelKeylogger::read(istream &is) {
    Keylogger::read(is);
    cout<<"Ascunde fisiere? (1/0) ";
    cin>>ascundeFisiere;
    cout<<"\nAscunde registri? (1/0) ";
    cin>>ascundeRegistri;
    return is;
}
ostream &KernelKeylogger::write(ostream &os) const {
    Keylogger::write(os);
    if (ascundeFisiere) cout << "Ascunde fisiere." << endl;
    if (ascundeRegistri) cout << "Ascunde registri." << endl;
    return os;
}

KernelKeylogger::KernelKeylogger(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
                                 const vector<string> &registri, const vector<string> &importuri,
                                 const vector<string> &stringuri, int zi1, int luna1, int an1, const string &nume1,
                                 const string &metodaInfectare1, const vector<string> &registri1,
                                 const vector<string> &functii, const vector<string> &taste, bool ascundeFisiere,
                                 bool ascundeRegistri) : Rootkit(zi, luna, an, nume, metodaInfectare, registri,
                                                                 importuri, stringuri),
                                                         Keylogger(zi1, luna1, an1, nume1, metodaInfectare1, registri1,
                                                                   functii, taste), ascundeFisiere(ascundeFisiere),
                                                         ascundeRegistri(ascundeRegistri) {ratingKernelKeylogger();}

class Ransomware : public Malware{
    int ratingCriptare;
    float ratingObfuscare;
public:

    Ransomware(){}

    Ransomware(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
               const vector<string> &registri, int ratingCriptare, float ratingObfuscare);

    istream &read(istream &is) override ;
    ostream &write(ostream &os) const override ;

    void ratingRansomware(){
        ratingImpact = ratingObfuscare+ ratingCriptare;
    }
};

istream &Ransomware::read(istream &is) {
    Malware::read(is);
    cout<<"rating criptare: "; cin>>ratingCriptare;
    cout<<"rating obfuscare: "; cin>>ratingObfuscare;
    return is;
}
ostream &Ransomware::write(ostream &os) const {
    Malware::write(os);
    cout<<"rating criptare: "<<ratingCriptare<<endl;
    cout<<"rating obfuscare: "<<ratingObfuscare<<endl;
    return os;
}

Ransomware::Ransomware(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
                       const vector<string> &registri, int ratingCriptare, float ratingObfuscare) : Malware(zi, luna,
                                                                                                            an, nume,
                                                                                                            metodaInfectare,
                                                                                                            registri),
                                                                                                    ratingCriptare(
                                                                                                            ratingCriptare),
                                                                                                    ratingObfuscare(
                                                                                                            ratingObfuscare) {ratingRansomware();}


class Computer : public IoBase{
    static int nr_calculatoare;
    int id;
    vector<shared_ptr<Malware>> malware;
    float ratingFinal;
public:
    Computer();

    Computer(int id, const vector<shared_ptr<Malware>> &malware, float ratingFinal);

    istream &read(istream &is) override ;
    ostream &write(ostream &os) const override ;

    void ratingF(){
        ratingFinal=0;
        for(auto m: malware)
            ratingFinal += m->getRatingImpact();
    }

    float getRatingFinal() const{
        return ratingFinal;
    }

    const vector<shared_ptr<Malware>> &getMalware() const {
        return malware;
    }
};

istream &Computer::read(istream &is) {
    IoBase::read(is);
    cout<<"Citire calculator "<<id<<":"<<endl;
    int n, tip;
    cout<<"nr malware: ";
    cin>>n;
    for(int i=0;i<n;i++) {
        shared_ptr<Malware> m;
        cout<<"tip malware (1. Rootkit, 2. Keylogger, 3. KernelKeylogger, 4. Ransomware): ";
        cin>>tip;
        if(tip==1) m= make_shared<Rootkit>();
        else if(tip==2) m= make_shared<Keylogger>();
        else if(tip==3) m= make_shared<KernelKeylogger>();
        else m= make_shared<Ransomware>();

        cin>>*m;
        malware.push_back(m);
    }

    ratingF();
    return is;
}
ostream &Computer::write(ostream &os) const {
    IoBase::write(os);
    cout<<"id calculator: "<<id<<endl;
    cout<<"lista malware: ";
    for(auto m: malware)
        cout<<*m<<endl;
    cout<<"\nrating final: "<<ratingFinal;
    return os;
}

int Computer::nr_calculatoare = 0;

Computer::Computer() { nr_calculatoare++; id=nr_calculatoare; }

Computer::Computer(int id, const vector<shared_ptr<Malware>> &malware, float ratingFinal) : id(id), malware(malware),
                                                                                            ratingFinal(ratingFinal) {nr_calculatoare++; ratingF();}

class Meniu {
public:
    void listareOptiuni();

    int alegeOptiune(int first, int last);

    void optiune1(vector<Computer> calculatoare){
        for(auto c:calculatoare)
            cout<<c<<endl<<endl;
    }

    static bool compara(Computer c1, Computer c2){
        return c1.getRatingFinal() < c2.getRatingFinal();
    }

    void optiune2(vector<Computer> calculatoare){
        sort(calculatoare.begin(), calculatoare.end(), compara);
        for(auto c:calculatoare)
            cout<<c<<endl<<endl;
    }

    void optiune3(vector<Computer> calculatoare){
        cout<<"Introduceeti k: ";
        int k; cin>>k; cout<<endl;
        sort(calculatoare.begin(), calculatoare.end(), compara);
        for(int i=0;i<k;i++)
            cout<<calculatoare[i]<<endl<<endl;
    }

    void optiune4(vector<Computer> calculatoare){
        int k;
        for(auto c: calculatoare)
            if(c.getMalware().size()!=0) k++;
        cout<<"Sunt infectate "<< k/100.0*calculatoare.size()<<" dintre calculatoarele firmei."<<endl;
    }

    void mainLoop(vector<Computer> calculatoare);
};

void Meniu::listareOptiuni() {
    cout << "1. Afisarea informatiilor pentru fiecare calculator." << '\n';
    cout << "2. Afisarea informatiilor pentru fiecare calculator, ordonate dupa ratingul final." << '\n';
    cout << "3. Afisarea primelor k calculatoare ordonate după ratingul final." << '\n';
    cout << "4. Afisarea procentului de computere infectate din firma." << '\n';
    cout << "5. Iesire din meniu." << '\n';
}

int Meniu::alegeOptiune(int first, int last) {
    int optiune=0;
    while(optiune < first || optiune > last)
    {
        cout<<"Pentru a rula comanda, alegeti un numar intre "<<first<<" si "<<last<<":"<<endl;
        listareOptiuni();
        cout<<"\nAlegere: ";
        cin>>optiune;
    }
    return optiune;
}

void Meniu::mainLoop(vector<Computer> calculatoare) {
    while(true){
        int optiune= alegeOptiune(1,5);
        if(optiune==1) optiune1(calculatoare);
        else if(optiune==2) optiune2(calculatoare);
        else if(optiune==3) optiune3(calculatoare);
        else if(optiune==4) optiune4(calculatoare);
        else break;
    }

    cout<<endl<<endl<<"Ati iesit din meniu."<<endl;
}

int main(){
    int n;
    vector<Computer> calculatoare;
    cout<<"Introduceti numarul de calculatoare: ";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        Computer c;
        cin>>c;
        calculatoare.push_back(c);
    }

    Meniu m;
    m.mainLoop(calculatoare);
}