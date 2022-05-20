#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Malware{
protected:
    float impact;
    int zi,luna,an;
    string denumire;
    string metoda_infectare;
    vector <string> registrii;
public:
    Malware();
    Malware(const Malware& m);
    Malware& operator=(const Malware& m);
    Malware(float impact, int zi, int luna, int an, string denumire, string metoda_infectare, vector<string> registrii);
    ~Malware();

    void calculeazaImpact();

    float getimpact();
    void setimpact(float impact);

    int getzi();
    void setzi(int zi);

    int getluna();
    void setluna(int luna);

    int getan();
    void setan(int an);

    string getdenumire();
    void setdenumire(string denumire);

    string getmetoda_infectare();
    void setmetoda_infectare(string metoda_infectare);

    vector<string> getregistrii();
    void setregistrii( vector<string> registrii);

    friend istream& operator>>(istream& in, Malware& m);
    friend ostream& operator<<(ostream& out, const Malware& m);

};

Malware::Malware() {
    impact=0;
    zi=0;
    luna=0;
    an=0;
    denumire="";
    metoda_infectare="";
    registrii={};
}
Malware::Malware(const Malware &m)  ///c. de copiere
{
    impact=m.impact;
    zi=m.zi;
    luna=m.zi;
    an=m.an;
    denumire=m.denumire;
    metoda_infectare=m.metoda_infectare;
    registrii=m.registrii;
}
Malware & Malware::operator=(const Malware &m) {
    impact = m.impact;
    zi = m.zi;
    luna = m.luna;
    an = m.an;
    denumire = m.denumire;
    metoda_infectare=m.metoda_infectare;
    registrii = m.registrii;
    return *this;
}
Malware::~Malware() {
    impact=0;
    zi=luna=an=0;
    denumire.clear();
    metoda_infectare.clear();
    registrii.clear();
}

Malware::Malware(float impact, int zi, int luna, int an, string denumire, string metoda_infectare,
                 vector<string> registrii) : impact(impact), zi(zi), luna(luna), an(an), denumire(denumire), metoda_infectare(metoda_infectare), registrii(registrii) {}

float Malware::getimpact(){
    return impact;
}
void Malware::setimpact(float impact){
    this->impact=impact;
}
int Malware::getzi(){
    return zi;
}
void Malware::setzi(int zi){
    this->zi=zi;
}
int Malware::getluna(){
    return luna;
}
void Malware::setluna(int luna){
    this->luna=luna;
}
int Malware::getan(){
    return an;
}
void Malware::setan(int an){
    this->an=an;
}

string Malware::getdenumire(){
    return denumire;
}
void Malware::setdenumire(string denumire){
    this->denumire=denumire;
}

string Malware::getmetoda_infectare(){
    return metoda_infectare;
}
void Malware::setmetoda_infectare(string metoda_infectare) {
    this->metoda_infectare=metoda_infectare;
}

vector<string> Malware::getregistrii() {
    return registrii;
}
void Malware::setregistrii(vector<string> registrii) {
    this->registrii=registrii;
}
void Malware::calculeazaImpact(){
    for(int i=0; i<this->registrii.size();i++)
    {
        if(this->registrii[i]=="HKLM-run" || this->registrii[i]=="HKCU-run")
            impact+=20;
    }
}

istream &operator>>(istream &in, Malware& m){
    cout<<"Denumirea virusului este:";
    in>>m.denumire;
    cout<<"Data infectarii"<<endl<<"ziua:";
    in>>m.zi;
    cout<<"luna:";
    in>>m.luna;
    cout<<"an";
    in>>m.an;
    cout<<"Metoda de infectare:";
    in>>m.metoda_infectare;
    cout<<"Rating impact:";
    in>>m.impact;
    cout<<"Cati registrii au fost modificati?";
    int n;
    in>>n;
    cout<<"introduceti registrii modificati";
    for(int i=0;i<n;i++)
        in>>m.registrii[i];

    return in;
}

ostream& operator<<(ostream& out, const Malware& m){
    out << "Denumire:" << m.denumire <<endl;
    out << "Data de infectare:" << m.zi << "."<< m.luna << "."<< m.an << endl;
    out << "Metoda infectare" << m.metoda_infectare<<endl;
    out<<"Rating impact"<< m.impact <<endl;
    out<<"Registrii modificati:";
    for (auto registru: m.registrii)
        out<<registru<<", ";
    out<<endl;
    return out;
}


class Rootkit: virtual public Malware{
protected:
    vector <string> importuri;
    vector <string> stringuri_semnificative;
public:

    Rootkit(float impact, int zi, int luna, int an, const string &denumire, const string &metodaInfectare,
            const vector<string> &registrii, vector <string> importuri, vector <string> stringuri_semnificative);

    Rootkit();

    Rootkit(const Rootkit &r); ///c. de copiere

    ~Rootkit();

    const vector<string> &getImporturi() const;

    void setImporturi(const vector<string> &importuri);

    const vector<string> &getStringuriSemnificative() const;

    void setStringuriSemnificative(const vector<string> &stringuriSemnificative);

    void calculeazaImpact();

    friend istream& operator>>(istream& in, Rootkit& r);
    friend ostream& operator<<(ostream& out, const Rootkit& r);
};


Rootkit::Rootkit(float impact, int zi, int luna, int an, const string &denumire, const string &metodaInfectare,
                 const vector<string> &registrii, vector <string> importuri, vector <string> stringuri_semnificative) : Malware(impact, zi, luna, an, denumire, metodaInfectare,
                                                            registrii) {
    this->importuri=importuri;
    this->stringuri_semnificative=stringuri_semnificative;
}

Rootkit::Rootkit() {
    importuri={};
    stringuri_semnificative={};
}

Rootkit::Rootkit(const Rootkit &r) {

    importuri=r.importuri;
    stringuri_semnificative=r.stringuri_semnificative;
}

Rootkit::~Rootkit() {
    importuri.clear();
    stringuri_semnificative.clear();
}

const vector<string> &Rootkit::getImporturi() const {
    return importuri;
}

void Rootkit::setImporturi(const vector<string> &importuri) {
    Rootkit::importuri = importuri;
}

const vector<string> &Rootkit::getStringuriSemnificative() const {
    return stringuri_semnificative;
}

void Rootkit::setStringuriSemnificative(const vector<string> &stringuriSemnificative) {
    stringuri_semnificative = stringuriSemnificative;
}

void Rootkit::calculeazaImpact() {
    Malware::calculeazaImpact();
    for(int i=0; i<stringuri_semnificative.size();i++)
    {
        if(stringuri_semnificative[i]=="System Service Descriptor Table" || stringuri_semnificative[i]=="SSDT"||stringuri_semnificative[i]=="NtCreateFile")
            impact+=100;
    }
    for(int i=0;i<importuri.size();i++)
    {
        if(importuri[i]=="ntoskrnl.exe")
            impact*=2;
    }

}
istream& operator>>(istream& in, Rootkit& r){
    cout<<"Denumirea virusului este:";
    in>>r.denumire;
    cout<<"Data infectarii"<<endl<<"ziua:";
    in>>r.zi;
    cout<<"luna:";
    in>>r.luna;
    cout<<"an";
    in>>r.an;
    cout<<"Metoda de infectare:";
    in>>r.metoda_infectare;
    cout<<"Rating impact:";
    in>>r.impact;
    cout<<"Cati registrii au fost modificati?";
    int n;
    in>>n;
    cout<<"introduceti registrii modificati";
    for(int i=0;i<n;i++)
        in>>r.registrii[i];
    cout<<"numar de importuri";
    int nr;
    cin>>nr;
    for(int i=0;i<nr;i++)
        in>>r.importuri[i];
    cout<<"numar de stringuri semnificative";
    cin>>nr;
    for(int i=0; i<nr; i++)
        in>>r.stringuri_semnificative[i];

    return in;

}

ostream& operator<<(ostream& out, const Rootkit& r){
    out << "Denumire:" << r.denumire <<endl;
    out << "Data de infectare:" << r.zi << "."<< r.luna << "."<< r.an << endl;
    out << "Metoda infectare" << r.metoda_infectare<<endl;
    out<<"Rating impact"<< r.impact <<endl;
    out<<"Registrii modificati:";
    for (auto registru: r.registrii)
        out<<registru<<", ";
    out<<"Importuri:";
    for (auto import: r.importuri)
        out<<import<<", ";
    out<<"Registrii modificati:";
    for (auto string_s: r.stringuri_semnificative)
        out<<string_s<<", ";
    out<<endl;

    return out;
}


class Keylogger: virtual public Malware{
protected:
    vector <string> functii;
    vector <string> taste_speciale;
public:
    ///constructori destructori un f mare semn de intreb
    Keylogger();

    virtual ~Keylogger();

    const vector<string> &getFunctii() const;

    void setFunctii(const vector<string> &functii);

    const vector<string> &getTasteSpeciale() const;

    void setTasteSpeciale(const vector<string> &tasteSpeciale);

    void calculeazaImpact();

    friend istream& operator>>(istream& in, Keylogger& k);
    friend ostream& operator<<(ostream& out, const Keylogger& k);
};

Keylogger::Keylogger() {
    functii={};
    taste_speciale={};
}


const vector<string> &Keylogger::getTasteSpeciale() const {
    return taste_speciale;
}

void Keylogger::setTasteSpeciale(const vector<string> &tasteSpeciale) {
    taste_speciale = tasteSpeciale;
}

const vector<string> &Keylogger::getFunctii() const {
    return functii;
}

void Keylogger::setFunctii(const vector<string> &functii) {
    Keylogger::functii = functii;
}

void Keylogger::calculeazaImpact(){
    Malware::calculeazaImpact();
    for(int i=0;i<taste_speciale.size();i++)
    {
        if(taste_speciale[i]=="[Up]"||taste_speciale[i]=="[Num Lock]"||taste_speciale[i]=="[Down]"||taste_speciale[i]=="[Right]"||taste_speciale[i]=="[UP]"||taste_speciale[i]=="[Left]"||taste_speciale[i]=="[PageDown]")
            impact+=10;
    }
    for(int i=0;i<functii.size();i++)
    {
        if(functii[i]=="CreateFileW"||functii[i]=="OpenProcess"||functii[i]=="ReadFile"||functii[i]=="WriteFile"||functii[i]=="RegisterHotKey"||functii[i]=="SetWindwsHookEx")
            impact+=30;
    }
}

Keylogger::~Keylogger() {
    functii.clear();
    taste_speciale.clear();
}
istream& operator>>(istream& in, Keylogger& k){
    cout<<"Denumirea virusului este:";
    in>>k.denumire;
    cout<<"Data infectarii"<<endl<<"ziua:";
    in>>k.zi;
    cout<<"luna:";
    in>>k.luna;
    cout<<"an";
    in>>k.an;
    cout<<"Metoda de infectare:";
    in>>k.metoda_infectare;
    cout<<"Rating impact:";
    in>>k.impact;
    cout<<"Cati registrii au fost modificati?";
    int n;
    in>>n;
    cout<<"introduceti registrii modificati";
    for(int i=0;i<n;i++)
        in>>k.registrii[i];
    cout<<"numar de functii";
    int nr;
    cin>>nr;
    for(int i=0;i<nr;i++)
        in>>k.functii[i];
    cout<<"numar de taste speciale";
    cin>>nr;
    for(int i=0; i<nr; i++)
        in>>k.taste_speciale[i];
    return in;

}
ostream& operator<<(ostream& out, const Keylogger& k){
    out << "Denumire:" << k.denumire <<endl;
    out << "Data de infectare:" << k.zi << "."<< k.luna << "."<< k.an << endl;
    out << "Metoda infectare" << k.metoda_infectare<<endl;
    out<<"Rating impact"<< k.impact <<endl;
    out<<"Registrii modificati:";
    for (auto registru: k.registrii)
        out<<registru<<", ";
    out<<"Importuri:";
    for (auto functie: k.functii)
        out<<functie<<", ";
    out<<"Registrii modificati:";
    for (auto tasta: k.taste_speciale)
        out<<tasta<<", ";
    out<<endl;

    return out;
}


class KernelKeylogger: public virtual Keylogger, public virtual Rootkit{
protected:
    bool hide_registrii;
    bool hide_fisiere;
public:
    KernelKeylogger(float impact, int zi, int luna, int an, const string &denumire, const string &metodaInfectare,
                    const vector<string> &registrii, const vector<string> &importuri,
                    const vector<string> &stringuriSemnificative, bool hideRegistrii, bool hideFisiere);

    bool isHideRegistrii() const;

    void setHideRegistrii(bool hideRegistrii);

    bool isHideFisiere() const;

    void setHideFisiere(bool hideFisiere);

    void calculeazaImpact();

    friend istream& operator>>(istream& in, KernelKeylogger& kk);
    friend ostream& operator<<(ostream& out, const KernelKeylogger& kk);
};

bool KernelKeylogger::isHideRegistrii() const {
    return hide_registrii;
}

void KernelKeylogger::setHideRegistrii(bool hideRegistrii) {
    hide_registrii = hideRegistrii;
}

bool KernelKeylogger::isHideFisiere() const {
    return hide_fisiere;
}

void KernelKeylogger::setHideFisiere(bool hideFisiere) {
    hide_fisiere = hideFisiere;
}

void KernelKeylogger::calculeazaImpact() {
    Rootkit::calculeazaImpact();
    Keylogger::calculeazaImpact();
    if(hide_registrii==true)
        impact+=30;
    if(hide_fisiere==true)
        impact+=20;
}
istream& operator>>(istream& in, KernelKeylogger& kk){
    cout<<"Denumirea virusului este:";
    in>>kk.denumire;
    cout<<"Data infectarii"<<endl<<"ziua:";
    in>>kk.zi;
    cout<<"luna:";
    in>>kk.luna;
    cout<<"an";
    in>>kk.an;
    cout<<"Metoda de infectare:";
    in>>kk.metoda_infectare;
    cout<<"Rating impact:";
    in>>kk.impact;
    cout<<"Cati registrii au fost modificati?";
    int n;
    in>>n;
    cout<<"introduceti registrii modificati";
    for(int i=0;i<n;i++)
        in>>kk.registrii[i];

    cout<<"numar de importuri";
    int nr;
    cin>>nr;
    for(int i=0;i<nr;i++)
        in>>kk.importuri[i];
    cout<<"numar de stringuri semnificative";
    cin>>nr;
    for(int i=0; i<nr; i++)
        in>>kk.stringuri_semnificative[i];


    cout<<"numar de functii";
    cin>>nr;
    for(int i=0;i<nr;i++)
        in>>kk.functii[i];
    cout<<"numar de taste speciale";
    cin>>nr;
    for(int i=0; i<nr; i++)
        in>>kk.taste_speciale[i];
    return in;


}
ostream& operator<<(ostream& out, const KernelKeylogger& kk){

    out << "Denumire:" << kk.denumire <<endl;
    out << "Data de infectare:" << kk.zi << "."<< kk.luna << "."<< kk.an << endl;
    out << "Metoda infectare" << kk.metoda_infectare<<endl;
    out<<"Rating impact"<< kk.impact <<endl;
    out<<"Registrii modificati:";
    for (auto registru: kk.registrii)
        out<<registru<<", ";

    out<<"Importuri";
    for (auto import: kk.importuri)
        out<<import<<", ";
    out<<"Registrii modificati:";
    for (auto string_s: kk.stringuri_semnificative)
        out<<string_s<<", ";
    out<<endl;
    out<<"Functii:";
    for (auto functie: kk.functii)
        out<<functie<<", ";
    out<<"Taste speciale:";
    for (auto tasta: kk.taste_speciale)
        out<<tasta<<", ";
    out<<endl;
}


class Ransomware: virtual public Malware{
protected:
    int rating_cripare;
    float rating_obfuscare;
public:
    ///construct destruct dzeu stie
    int getRatingCripare() const;

    void setRatingCripare(int ratingCripare);

    float getRatingObfuscare() const;

    void setRatingObfuscare(float ratingObfuscare);

    void calculeazaImpact();
};

int Ransomware::getRatingCripare() const {
    return rating_cripare;
}

void Ransomware::setRatingCripare(int ratingCripare) {
    rating_cripare = ratingCripare;
}

float Ransomware::getRatingObfuscare() const {
    return rating_obfuscare;
}

void Ransomware::setRatingObfuscare(float ratingObfuscare) {
    rating_obfuscare = ratingObfuscare;
}

void Ransomware::calculeazaImpact() {
    Malware::calculeazaImpact();
    impact=impact+rating_obfuscare+rating_cripare;
}

class Computer{
protected:
    static int id;
    vector <Malware> virusi;
    int rating_final;
public:
    Computer();
    Computer(int id, vector <Malware> virusi, int rating_final);
    Computer(const Computer& c);
    virtual ~Computer();


    const int getId() const;

    const vector<Malware> &getVirusi() const;

    void setVirusi(const vector<Malware> &virusi);

    int getRatingFinal() const;

    void setRatingFinal(int ratingFinal);

    friend istream& operator>>(istream& in, Computer& c);
    friend ostream& operator<<(ostream& out,const Computer& c);

};

Computer::Computer() {
    id=0;
    virusi={};
    rating_final=0;
}
Computer::Computer(int id, vector<Malware> virusi, int rating_final) {
    this->id=id;
    this->rating_final=rating_final;
    this->virusi=virusi;
}
Computer::Computer(const Computer &c) {
    this->id=id;
    this->virusi=virusi;
    this->rating_final=rating_final;
}
Computer::~Computer() {
    virusi.clear();
    rating_final=0;

}

istream& operator>>(istream& in, Computer& c){
    cout<<"Id-ul calculatorului este:"<<endl;
    in>>c.id;
    cout<<"Cate tipuri de virusi?"<<endl;
    int nr;
    in>>nr;
    cout<<"introduceti tipurile de virusi"<<endl;
    for(int i=0;i<nr;i++)
        in>>c.virusi[i];

    return in;
}

ostream& operator<<(ostream& out, const Computer& c){
    out<<"id:"<<c.id<<endl;
    out<<"rating:"<<c.rating_final;
    out<<"tipuri de virusi:";
    for(int i=0; i< c.virusi.size(); i++)
    {
        cout<<c.virusi[i]<<endl;
    }
    return out;
}

const int Computer::getId() const {
    return id;
}

const vector<Malware> &Computer::getVirusi() const {
    return virusi;
}

void Computer::setVirusi(const vector<Malware> &virusi) {
    Computer::virusi = virusi;
}

int Computer::getRatingFinal() const {
    return rating_final;
}

void Computer::setRatingFinal(int ratingFinal) {
    rating_final = ratingFinal;
}



int main() {
    int k = 1;
    while(k == 1)
    {
        Computer c;
        int x;
        cout<<"Pt a citit, introduceti 1, pt a iesi 2";
        cin>>x;
        if(x==1)
        {
            cout<<"Introduceti calculatorul: ";
            cin>>c;
        }
        else
            k = 0;
    }
    return 0;
}
