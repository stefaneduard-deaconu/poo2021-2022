/*
Cucos Maria-Marianita, grupa 143
compilator:
Deaconu Stefan
*/

#include <iostream>
#include <memory>
#include <bits/stdc++.h>
#include "util/IoBase.h"
#include "util/functions.h"
using namespace std;

class Data{
private:
    int zi,luna,an;
public:
    friend class Malware;
    Data(int zi, int luna, int an) : zi(zi), luna(luna), an(an) {}
    Data(){
        zi=luna=an=0;
    }

    friend ostream &operator<<(ostream &os, const Data &data);

    bool operator==(const Data &rhs) const;

    bool operator!=(const Data &rhs) const;
};

bool Data::operator==(const Data &rhs) const {
    return zi == rhs.zi &&
           luna == rhs.luna &&
           an == rhs.an;
}

bool Data::operator!=(const Data &rhs) const {
    return !(rhs == *this);
}

ostream &operator<<(ostream &os, const Data &data) {
    os << "zi: " << data.zi << " luna: " << data.luna << " an: " << data.an;
    return os;
}

//Prin malware înțelegem un software rău intenționat pentru care
// se reține ratingul impactului (număr real), data de infectare (zi, luna, an),
// numele acestuia (care poate să fie format din mai multe cuvinte),
// metoda de infectare (dacă se cunoaște, altfel se reține șirul “unknown”) și un
// vector cu registrii modificați (reținuți ca stringuri)
class Malware : public IoBase{
protected:
    float rating;
    Data data_infectare;
    string nume;
    string metoda_infectare;
    vector<string> registrii_modificati;

public:
    Malware(float rating, const Data &dataInfectare, char *nume, const string &metodaInfectare,
            const vector<string> &registriiModificati) : rating(rating), data_infectare(dataInfectare), nume(nume),
                                                         metoda_infectare(metodaInfectare),
                                                         registrii_modificati(registriiModificati) {}

    virtual ~Malware();

    Malware() {
        rating=0;
    }

    void setRating(float rating);
    void setDataInfectare(const Data &dataInfectare);
    void setNume(const string &nume);
    void setMetodaInfectare(const string &metodaInfectare);
    void setRegistriiModificati(const vector<string> &registriiModificati);

    float getRating() const;
    const Data &getDataInfectare() const;
    const string &getNume() const;
    const string &getMetodaInfectare() const;
    const vector<string> &getRegistriiModificati() const;

    bool operator==(const Malware &rhs) const;
    bool operator!=(const Malware &rhs) const;

    virtual istream &read(istream &is) override;
    virtual ostream &write(ostream &os) const override;

    virtual float calc_rating() = 0;

};

istream &Malware::read(istream &is) {
    IoBase::read(is);
    cout << "Data infectare: ";
    is >> data_infectare.zi >> data_infectare.luna >> data_infectare.an;

    cout << "Nume: ";
    is.get();
    getline(is, nume);

    cout << "Metoda infectare: ";
    is.get();
    getline(is,metoda_infectare);

    cout << "Registrii modificati: ";
    string reg;
    int n;
    cout<<"nr registrii:";
    is>>n;
    is.get();
    for (int i = 0; i < n; ++i) {
        cout <<i+1<<". ";
        getline(is, reg);
        registrii_modificati.push_back(reg);
    }
    return is;
}

ostream &Malware::write(ostream &os) const {
    IoBase::write(os);
    os <<endl<< " data_infectare: " << data_infectare <<endl<< " nume: " << nume<<endl
       << " metoda_infectare: " << metoda_infectare<< endl << " registrii_modificati: ";
    for (int i = 0; i < registrii_modificati.size() ; ++i) {
        cout<<" "<< registrii_modificati[i];
    }
    os<<endl;
    return os;
}

float Malware::getRating() const {
    return rating;
}

const Data &Malware::getDataInfectare() const {
    return data_infectare;
}

const string &Malware::getNume() const {
    return nume;
}

const string &Malware::getMetodaInfectare() const {
    return metoda_infectare;
}

const vector<string> &Malware::getRegistriiModificati() const {
    return registrii_modificati;
}

void Malware::setRating(float rating) {
    Malware::rating = rating;
}

void Malware::setDataInfectare(const Data &dataInfectare) {
    data_infectare = dataInfectare;
}

void Malware::setNume(const string &nume) {
    Malware::nume = nume;
}

void Malware::setMetodaInfectare(const string &metodaInfectare) {
    metoda_infectare = metodaInfectare;
}

void Malware::setRegistriiModificati(const vector<string> &registriiModificati) {
    registrii_modificati = registriiModificati;
}

Malware::~Malware() {
    registrii_modificati.clear();
}

bool Malware::operator==(const Malware &rhs) const {
    return rating == rhs.rating &&
           data_infectare == rhs.data_infectare &&
           nume == rhs.nume &&
           metoda_infectare == rhs.metoda_infectare &&
           registrii_modificati == rhs.registrii_modificati;
}

bool Malware::operator!=(const Malware &rhs) const {
    return !(rhs == *this);
}




//Prin rootkit înțelegem un tip de malware ce are drept scop obținerea drepturilor de
//administrator asupra dispozitivului infectat. Pentru rootkit se reține
// lista importurilor care poate fi unul și oricât de multe
//(importurile fac referire la numele fișierelor .dll folosite) și
//o listă de stringuri semnificative (anumite stringuri dintr-un binar pot fi un indice
//asupra faptului că fișierul este rău intenționat).
class Rootkit : virtual public Malware{
protected:
    vector<string> importuri;
    vector<string> secventa_semnificativa;

public:
    Rootkit(float rating, const Data &dataInfectare, char *nume, const string &metodaInfectare,
            const vector<string> &registriiModificati, const vector<string> &importuri,
            const vector<string> &secventaSemnificativa) : Malware(rating, dataInfectare, nume, metodaInfectare,
                                                                   registriiModificati), importuri(importuri),
                                                           secventa_semnificativa(secventaSemnificativa) {}

    Rootkit() {}
    virtual ~Rootkit();

    const vector<string> &getImporturi() const;
    const vector<string> &getSecventaSemnificativa() const;

    void setImporturi(const vector<string> &importuri);
    void setSecventaSemnificativa(const vector<string> &secventaSemnificativa);

    bool operator==(const Rootkit &rhs) const;
    bool operator!=(const Rootkit &rhs) const;

    virtual istream &read(istream &is) override;
    virtual ostream &write(ostream &os) const override;

    virtual float calc_rating();
};

//Pentru rootkit ratingul impactului crește cu 100 dacă se întâlnește unul din stringurile
// “System Service Descriptor Table”, “SSDT”, “NtCreateFile”. Dacă se regăsește
// importul “ntoskrnl.exe”, valoarea impactului se dublează
// (importurile se verifică după stringuri).
float Rootkit::calc_rating() {
    float val = rating;
    for(int i =0;i < registrii_modificati.size(); ++i)
        if(registrii_modificati[i] == "“HKLM-run" || registrii_modificati[i] == "HKCU-run"){
            val += 20;
            break;
        }

    for(int i = 0;i < secventa_semnificativa.size(); ++i)
        if(secventa_semnificativa[i] == "System Service Descriptor Table" || secventa_semnificativa[i] == "SSDT" || secventa_semnificativa[i] == "NtCreateFile" ){
            val += 100;
            break;
        }
    for(int i = 0;i < importuri.size(); ++i)
        if(importuri[i] == "ntoskrnl.exe"){
            val = val *2;
            break;
        }
    return val;
}


istream &Rootkit::read(istream &is) {
    Malware::read(is);
    int n;
    cout << "lista importurilor: numar: ";
    is >> n; is.get();
    for (int i = 0; i < n; ++i) {
        string imp;
        getline(is, imp);
        importuri.push_back(imp);
    }
    cout << "stringuri semnificative: numar:";
    is >> n; is.get();
    for (int i = 0; i < n; ++i) {
        string semnif;
        getline(is, semnif);
        secventa_semnificativa.push_back(semnif);
    }
    return is;
}

ostream &Rootkit::write(ostream &os) const {
    Malware::write(os);
    cout<<"lista importuri:";
    for (int i = 0; i < importuri.size(); ++i) {
        os<<" "<<importuri[i];
    }
    cout<<endl<<"stringuri semnificative:";
    for (int i = 0; i < secventa_semnificativa.size(); ++i) {
        os<<" "<<secventa_semnificativa[i];
    }
    return os;
}



bool Rootkit::operator==(const Rootkit &rhs) const {
    return static_cast<const Malware &>(*this) == static_cast<const Malware &>(rhs) &&
           importuri == rhs.importuri &&
           secventa_semnificativa == rhs.secventa_semnificativa;
}

bool Rootkit::operator!=(const Rootkit &rhs) const {
    return !(rhs == *this);
}

void Rootkit::setImporturi(const vector<string> &importuri) {
    Rootkit::importuri = importuri;
}

void Rootkit::setSecventaSemnificativa(const vector<string> &secventaSemnificativa) {
    secventa_semnificativa = secventaSemnificativa;
}

const vector<string> &Rootkit::getImporturi() const {
    return importuri;
}

const vector<string> &Rootkit::getSecventaSemnificativa() const {
    return secventa_semnificativa;
}

Rootkit::~Rootkit() {
    importuri.clear();
    secventa_semnificativa.clear();
}




//Prin keylogger înțelegem un malware care înregistrează acțiunile de la tastatură și
// le trimite mai departe. Pentru un keylogger se reține
// o listă cu funcțiile folosite și o listă cu tastele speciale definite.
class Keylogger : virtual public Malware{
protected:
    vector<string> functii_folosite;
    vector<string> taste_special_definite;

public:
    Keylogger(float rating, const Data &dataInfectare, char *nume, const string &metodaInfectare,
              const vector<string> &registriiModificati, const vector<string> &functiiFolosite,
              const vector<string> &tasteSpecialDefinite) : Malware(rating, dataInfectare, nume, metodaInfectare, registriiModificati),
                                                            functii_folosite(functiiFolosite), taste_special_definite(tasteSpecialDefinite) {}
    Keylogger(){}
    virtual ~Keylogger();

    const vector<string> &getFunctiiFolosite() const;
    void setFunctiiFolosite(const vector<string> &functiiFolosite);

    const vector<string> &getTasteSpecialDefinite() const;
    void setTasteSpecialDefinite(const vector<string> &tasteSpecialDefinite);

    virtual istream &read(istream &is) override;
    virtual ostream &write(ostream &os) const override;

    virtual float calc_rating();

};
//Pentru keylogger ratingul impactului crește cu 10 la întâlnirea stringurilor “[Up]”,
//“[Num Lock]”, “[Down]”, “[Right]”, “[UP]”, “[Left]”, “[PageDown]” și cu 30 la întâlnirea unei din
//funcțiile: “CreateFileW”, “OpenProcess”, “ReadFile”, “WriteFile”, “RegisterHotKey”,
//“SetWindowsHookEx”
float Keylogger::calc_rating() {
    float val = rating;
    for(int i =0;i < registrii_modificati.size(); ++i)
        if(registrii_modificati[i] == "“HKLM-run" || registrii_modificati[i] == "HKCU-run"){
            val += 20;
            break;
        }
    for(int i = 0;i < functii_folosite.size(); ++i)
        if(functii_folosite[i] == "CreateFileW" || functii_folosite[i] == "OpenProcess" || functii_folosite[i] == "ReadFile" || functii_folosite[i] =="WriteFile" || functii_folosite[i] == "RegisterHotKey"  || functii_folosite[i] == "SetWindowsHookEx" )
            val += 30;
    for(int i = 0;i < taste_special_definite.size(); ++i)
        if(taste_special_definite[i] == "Up" || taste_special_definite[i] == "Num Lock" || taste_special_definite[i] == "Down" || taste_special_definite[i] =="Right" || taste_special_definite[i] == "UP"  || taste_special_definite[i] == "Left" || taste_special_definite[i] == "PageDown" )
            val += 10;
    return val;
}



const vector<string> &Keylogger::getFunctiiFolosite() const {
    return functii_folosite;
}

void Keylogger::setFunctiiFolosite(const vector<string> &functiiFolosite) {
    functii_folosite = functiiFolosite;
}

const vector<string> &Keylogger::getTasteSpecialDefinite() const {
    return taste_special_definite;
}

void Keylogger::setTasteSpecialDefinite(const vector<string> &tasteSpecialDefinite) {
    taste_special_definite = tasteSpecialDefinite;
}

Keylogger::~Keylogger() {
    functii_folosite.clear();
    taste_special_definite.clear();
}

istream &Keylogger::read(istream &is) {
    Malware::read(is);
    int n;
    cout << "functii folosite: numar: ";
    is >> n;
    is.get();
    for (int i = 0; i < n; ++i) {
        string fct;
        getline(is, fct);
        functii_folosite.push_back(fct);
    }
    cout << "taste special definite: numar:";
    is >> n;
    is.get();
    for (int i = 0; i < n; ++i) {
        string taste;
        getline(is, taste);
        taste_special_definite.push_back(taste);
    }
    return is;
}

ostream &Keylogger::write(ostream &os) const {
    Malware::write(os);
    cout<<"functii folosite:";
    for (int i = 0; i < functii_folosite.size(); ++i) {
        os<<" "<< functii_folosite[i];
    }
    cout<<endl<<"taste special definite:";
    for (int i = 0; i < taste_special_definite.size(); ++i) {
        os<<" "<<taste_special_definite[i];
    }
    return os;
}


//Prin kernel-keylogger înțelegem un keylogger ce rulează în kernel-mode (de obicei prin intermediul unui rootkit).
// Prin urmare, putem considera că este are atât proprietățile unui rootkit cât și
// ale unui keylogger. În plus, dorim să memorăm dacă ascunde fișiere și registrii.

class Kernel_Keylogger : public Keylogger, public Rootkit{
private:
    bool ascunde_fisiere;
    bool ascunde_registrii;
public:
    Kernel_Keylogger(float rating, const Data &dataInfectare, char *nume, const string &metodaInfectare,
                     const vector<string> &registriiModificati, const vector<string> &functiiFolosite,
                     const vector<string> &tasteSpecialDefinite, float rating1, const Data &dataInfectare1, char *nume1,
                     const string &metodaInfectare1, const vector<string> &registriiModificati1,
                     const vector<string> &importuri, const vector<string> &secventaSemnificativa, bool ascundeFisiere,
                     bool ascundeRegistrii) : Keylogger(rating, dataInfectare, nume, metodaInfectare,
                                                        registriiModificati, functiiFolosite, tasteSpecialDefinite),
                                              Rootkit(rating1, dataInfectare1, nume1, metodaInfectare1,
                                                      registriiModificati1, importuri, secventaSemnificativa),
                                              ascunde_fisiere(ascundeFisiere), ascunde_registrii(ascundeRegistrii) {}

    Kernel_Keylogger(){
        ascunde_fisiere=ascunde_registrii= false;
    }

    bool isAscundeFisiere() const;
    void setAscundeFisiere(bool ascundeFisiere);

    bool isAscundeRegistrii() const;
    void setAscundeRegistrii(bool ascundeRegistrii);

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    float calc_rating();

};
//Pentru kernel keylogger se respectă valorile de la rootkit și keylogger și se adaugă
//valoarea 20 dacă ascunde fișiere, respectiv valoarea 30 dacă ascunde registrii.

float Kernel_Keylogger::calc_rating() {
    float val = rating;

    for(int i =0;i < registrii_modificati.size(); ++i)
        if(registrii_modificati[i] == "“HKLM-run" || registrii_modificati[i] == "HKCU-run"){
            val += 20;
            break;
        }
    for(int i = 0;i < secventa_semnificativa.size(); ++i)
        if(secventa_semnificativa[i] == "System Service Descriptor Table" || secventa_semnificativa[i] == "SSDT" || secventa_semnificativa[i] == "NtCreateFile" ){
            val += 100;
            break;
        }
    for(int i = 0;i < importuri.size(); ++i)
        if(importuri[i] == "ntoskrnl.exe"){
            val = val *2;
            break;
        }

    for(int i = 0;i < functii_folosite.size(); ++i)
        if(functii_folosite[i] == "CreateFileW" || functii_folosite[i] == "OpenProcess" || functii_folosite[i] == "ReadFile" || functii_folosite[i] =="WriteFile" || functii_folosite[i] == "RegisterHotKey"  || functii_folosite[i] == "SetWindowsHookEx" )
            val += 30;
    for(int i = 0;i < taste_special_definite.size(); ++i)
        if(taste_special_definite[i] == "Up" || taste_special_definite[i] == "Num Lock" || taste_special_definite[i] == "Down" || taste_special_definite[i] =="Right" || taste_special_definite[i] == "UP"  || taste_special_definite[i] == "Left" || taste_special_definite[i] == "PageDown" )
            val += 10;

    if(ascunde_registrii)
        val += 30;
    if(ascunde_fisiere)
        val += 20;

    return val;
}

ostream &Kernel_Keylogger::write(ostream &os) const {
    Rootkit::write(os);

    cout<<endl<<"functii folosite:";
    for (int i = 0; i < functii_folosite.size(); ++i) {
        os<<" "<< functii_folosite[i];
    }
    cout<<endl<<"taste special definite:";
    for (int i = 0; i < taste_special_definite.size(); ++i) {
        os<<" "<<taste_special_definite[i];
    }

    cout<<endl<<"ascunde fisiere: "<<ascunde_fisiere<<endl;
    cout<<"ascunde registrii: "<<ascunde_registrii;

    return os;
}

istream &Kernel_Keylogger::read(istream &is) {
    Rootkit::read(is);
    int n;
    cout << "functii folosite: numar: ";
    is >> n;
    is.get();
    for (int i = 0; i < n; ++i) {
        string fct;
        getline(is, fct);
        functii_folosite.push_back(fct);
    }
    cout << "taste special definite: numar:";
    is >> n;
    is.get();
    for (int i = 0; i < n; ++i) {
        string taste;
        getline(is, taste);
        taste_special_definite.push_back(taste);
    }

    cout<<"ascunde fisiere: ";
    is>>ascunde_fisiere;
    is.get();
    cout<<"ascunde registrii: ";
    is>>ascunde_registrii;

    return is;
}


bool Kernel_Keylogger::isAscundeFisiere() const {
    return ascunde_fisiere;
}

void Kernel_Keylogger::setAscundeFisiere(bool ascundeFisiere) {
    ascunde_fisiere = ascundeFisiere;
}

bool Kernel_Keylogger::isAscundeRegistrii() const {
    return ascunde_registrii;
}

void Kernel_Keylogger::setAscundeRegistrii(bool ascundeRegistrii) {
    ascunde_registrii = ascundeRegistrii;
}




//Prin ransomware înțelegem un malware care criptează fișiere de pe disk.
// Pentru acesta se reține ratingul de criptare (un număr de la 1 la 10)
// și un rating de obfuscare (un număr real ce reprezintă procentul de obfuscare
// (obfuscare = metodă de a ascunde/îngreuna intenția inițială a codului)).
class Ransomware : public Malware{
private:
    int rating_criptare;
    float rating_obfuscare;
public:
    Ransomware(float rating, const Data &dataInfectare, char *nume, const string &metodaInfectare,
               const vector<string> &registriiModificati, int ratingCriptare, float ratingObfuscare) : Malware(rating,dataInfectare,nume,metodaInfectare,registriiModificati),
                                                                                                       rating_criptare(ratingCriptare), rating_obfuscare(ratingObfuscare) {}

    Ransomware() {
        rating_criptare=0;
        rating_obfuscare=0;
    }

    int getRatingCriptare() const;
    void setRatingCriptare(int ratingCriptare);

    float getRatingObfuscare() const;
    void setRatingObfuscare(float ratingObfuscare);

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    float calc_rating();
};

float Ransomware::calc_rating() {
    float val = rating_obfuscare + rating_criptare;
    for(int i =0;i < registrii_modificati.size(); ++i)
        if(registrii_modificati[i] == "“HKLM-run" || registrii_modificati[i] == "HKCU-run"){
            val += 20;
            break;
        }
    return val;
}

istream &Ransomware::read(istream &is) {
    Malware::read(is);
    cout<<"rating criptare: ";
    is>>rating_criptare;
    cout<<"rating obfuscare: ";
    is>>rating_obfuscare;
    return is;
}

ostream &Ransomware::write(ostream &os) const {
    Malware::write(os);
    os<<"rating criptare: "<<rating_criptare<<endl;
    os<<"rating obfuscare: "<<rating_obfuscare;
    return os;
}

int Ransomware::getRatingCriptare() const {
    return rating_criptare;
}

void Ransomware::setRatingCriptare(int ratingCriptare) {
    rating_criptare = ratingCriptare;
}

float Ransomware::getRatingObfuscare() const {
    return rating_obfuscare;
}

void Ransomware::setRatingObfuscare(float ratingObfuscare) {
    rating_obfuscare = ratingObfuscare;
}




//Pentru fiecare computer din firmă se reține un id unic, incrementat automat,
// o listă de malware (poate conține un malware sau mai multe) și
// ratingul final ce este calculat drept suma ratingului impactului fiecărui malware.
class Computer : public IoBase{
private:
    int ID;
    static int nr;
    vector<Malware*> lista_malware;
    float rating_final;
public:
    Computer(int id, const vector<Malware *> &listaMalware, float ratingFinal) : lista_malware(listaMalware),
                                                                                 rating_final(ratingFinal){
    }

    Computer(){
        rating_final=0;
    }
    virtual ~Computer() {
        lista_malware.clear();
    }

    int getId() const;
    void setId(int id);

    const vector<Malware *> &getListaMalware() const;
    void setListaMalware(const vector<Malware *> &listaMalware);

    float getRatingFinal() const;
    void setRatingFinal(float ratingFinal);

    // IoBase - overrided functions
    istream &read(istream &is) override {
        IoBase::read(is);
        int m;
        ID=++nr;
        cout << "lista malware: ";
        cout<< "m= ";
        is>>m;
        is.get();
        for(int i = 0;i < m; ++i){
            int tip;
            Malware *p = nullptr;
            while(true){
                try{
                    cout<<"Tipul de malware (1=Rootkit, 2=Keylogger, 3=Kernel-Keylogger, 4=Ransomware):";
                    is>>tip;
                    if(tip == 1){
                        p = new Rootkit;
                        break;
                    }
                    else if(tip == 2){
                        p = new Keylogger;
                        break;
                    }else if(tip == 3){
                        p = new Kernel_Keylogger;
                        break;
                    }
                    else if(tip == 4){
                        p = new Ransomware;
                        break;
                    }

                    else throw string("Tip invalid!");
                }
                catch(string s){
                    cout << s << '\n';
                }
            }
            is >> *p;
            rating_final += p->calc_rating();
            lista_malware.push_back(p);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout <<endl<< "ID: " << ID;
        cout << ", lista malware: ";
        for (int i = 0; i < lista_malware.size(); ++i) {
            cout<<*lista_malware[i]<< "\n";
        }
        cout << "rating final: " << rating_final;
        return os;
    }

};
int Computer::nr=0;

int Computer::getId() const {
    return ID;
}

void Computer::setId(int id) {
    ID = id;
}

const vector<Malware *> &Computer::getListaMalware() const {
    return lista_malware;
}

void Computer::setListaMalware(const vector<Malware *> &listaMalware) {
    lista_malware = listaMalware;
}

float Computer::getRatingFinal() const {
    return rating_final;
}

void Computer::setRatingFinal(float ratingFinal) {
    rating_final = ratingFinal;
}



//Programul realizat trebuie să aibă un meniu care permite:
//1. afișarea informațiilor pentru fiecare calculator
//2. afișarea informațiilor pentru fiecare calculator fiind ordonate după ratingul final
//3. afișarea primelor k calculatoare ordonate după ratingul final
//4. afișarea procentului de computere infectate din firmă
class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};

class SimpleMenu : public BaseMenu {
private:
    vector<Computer> calculatoare;
public:
    void listOptions() override;

    int chooseOption(int first, int last) override;

    void mainLoop() override;

    void option0();
    void option1();
    void option2();
    void option3();
    void option4();

};

void SimpleMenu::listOptions() {
    cout << "0. Citirea informatiilor pentru fiecare calculator." << '\n';
    cout << "1. Afisarea informatiilor pentru fiecare calculator." << '\n';
    cout << "2. Afisarea informatiilor pentru fiecare calculator fiind ordonate dupa ratingul final." << '\n';
    cout << "3. Afisarea primelor k calculatoare ordonate dupa ratingul final." << '\n';
    cout << "4. Afisarea procentului de computere infectate din firma." << '\n';
    cout << "5. Iesire." << '\n';
}

int SimpleMenu::chooseOption(int first, int last) {
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

void SimpleMenu::mainLoop(){
    while (true) {
    int option = chooseOption(0, 5);
    if(option == 0) {
    option0();
    }
    else if (option == 1) {
    option1();
    } else if (option == 2) {
    option2();
    } else if (option == 3) {
    option3();
    } else if (option == 4) {
    option4();
    } else if (option == 5) {
    break;
    }
    }
    cout << '\n'
    << "---------------------------------"
    << '\n'
    << "Programul s-a incheiat cu success";
}

void SimpleMenu::option0() {
    //citire inf calculatoare
    int n;
    cout<<"nr calculatoare: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        Computer calc;
        cin>>calc;
        calculatoare.push_back(calc);
    }

}

void SimpleMenu::option1() {
    //afisare inf calculatoare
    for (int i = 0; i < calculatoare.size(); ++i) {
        cout<<calculatoare[i]<<endl;
    }

}

void SimpleMenu::option2() {
    //inf calculatoarelor fiind ordonate dupa ratingul final
    for(int i = 0;i < calculatoare.size(); ++i)
        for(int j = i+1;j < calculatoare.size(); ++j)
            if(calculatoare[i].getRatingFinal() > calculatoare[j].getRatingFinal())
                swap(calculatoare[i],calculatoare[j]);

    for(int i = 0;i < calculatoare.size(); ++i)
        cout << calculatoare[i] << endl;
}

void SimpleMenu::option3() {
    //primele k calculatoare ordonate dupa ratingul final.
    int k;
    while(true){
        cout << "k= ";
        cin >> k;
        cin.get();
        if(k <= 0 )
            throw string("Nr invalid!");
        else
            break;
    }

    for(int i = 0;i < calculatoare.size(); ++i)
        for(int j = i+1;j < calculatoare.size(); ++j)
            if(calculatoare[i].getRatingFinal() > calculatoare[j].getRatingFinal())
                swap(calculatoare[i],calculatoare[j]);

    for(int i = 0;i < calculatoare.size() && i<k ; ++i)
        cout << calculatoare[i] << endl;
}

void SimpleMenu::option4() {
    //procentul de computere infectate din firma
    float procent;
    int nr = 0;
    for(int i = 0;i < calculatoare.size();++i)
        if(calculatoare[i].getRatingFinal() != 0)
            ++nr;
    if(calculatoare.size()) {
        procent = 100.0 * ((float) nr) / ((float) calculatoare.size());
        cout << "Procent: " << procent << '\n';
    }
    else
        cout << "Nu exista calculatoare\n";

}

int main() {

    SimpleMenu menu;
    menu.mainLoop();


}






