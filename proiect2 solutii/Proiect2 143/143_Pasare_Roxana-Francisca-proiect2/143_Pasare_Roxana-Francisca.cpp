#include <iostream>
#include "util/IoBase.h"
#include <vector>
#include <string>
#include <memory>

class Malware: public IoBase{
protected:
    double impact;
    int zi,luna, an;
    string denumire;
    string metode_de_infectare;
    vector <string> registrii;
public:
    Malware();
    Malware(const Malware& ob);
    Malware(double impact, int zi, int luna, int an, const string &denumire,const vector<string> &registrii,const string &metodeDeInfectare);

    virtual ~Malware();

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    virtual double calculeazaRaiting();
};

double Malware::calculeazaRaiting() {
    double raiting=impact;
    for (int i = 0; i < registrii.size(); i++)
        if (registrii[i] == "HKLM-run" || registrii[i] == "HKCU-run") {
            raiting = raiting + 20;
            break;
        }
    return raiting;
}

Malware::Malware(): registrii(){
    impact=0;
    zi=luna=an=0;
    denumire="";
    metode_de_infectare="";
}

Malware::Malware(const Malware &ob) {
    impact=ob.impact;
    zi=ob.zi;
    luna=ob.luna;
    an=ob.an;
    denumire=ob.denumire;
    metode_de_infectare=ob.metode_de_infectare;
    registrii=ob.registrii;
}

Malware::Malware(double impact, int zi, int luna, int an, const string &denumire,const vector<string> &registri, const string &metodeDeInfectare="unknown"):
                            impact(impact), zi(zi), luna(luna), an(an), denumire(denumire),metode_de_infectare(metodeDeInfectare), registrii(registrii) {}

Malware::~Malware() {
    impact=0;
    zi=luna=an=0;
    denumire.clear();
    metode_de_infectare.clear();
    registrii.clear();
}

istream &Malware::read(istream &is) {
    IoBase::read(is);
    cout<<"Impact:\n";
    is>>impact;
    cout << "Data:\n";
    cout << "An:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    this->an=an;
    cout << "Luna:\n";
    while(true){
        try{
            is >> luna;
            is.get();
            if(luna < 1 || luna > 12)
                throw string("Luna invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    this->luna=luna;
    cout << "Ziua\n";
    while(true){
        try{
            is >> zi;
            is.get();
            if(zi < 1 || (luna == 2 && bisect == 1 && zi > 29) || zi > zile[luna])
                throw string("Zi invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    this->zi=zi;
    cout<<"Denumire:\n";
    getline(is,denumire);
    cout<<"Metoda de infectare:\n";
    int ok;
    cout << "Introduceti 1-daca vrei o valoare noua pentru citire, 0 altfel:\n";
    is >> ok;
    if (ok == 1) {
        cout<<"Citesc metoda de infectare:\n";
        is.get();
        getline(is, metode_de_infectare);
    }
    else{
        metode_de_infectare="unknown";
    }
    int nr;
    while(true){
        try{
            cout<<"Numarul de registrii:\n";
            is>>nr;
            if(nr<0)
                throw string ("Nu e bine!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }
    cout<<"Registrtii:\n";
    for(int i=0; i<nr; i++){
        cout<<"Registru:\n";
        string x;
        is>>x;
        registrii.push_back(x);
    }
    return is;
}

ostream &Malware::write(ostream &os)const {
    IoBase::write(os);
    os<<"Impact: "<<impact<<"\n";
    os<<"Data: "<<zi<<"/"<<luna<<"/"<<an<<"\n";
    os<<"Denumire: "<<denumire<<"\n";
    os<<"Metoda de infectare: "<<metode_de_infectare<<"\n";
    os<<"Registrii: ";
    for(int i=0; i<registrii.size(); i++)
        os<<registrii[i]<<"\n";
    return os;
}

class Rootkit: virtual public Malware{
protected:
    vector<string> importuri;
    vector<string> semnificative;
public:
    Rootkit();
    Rootkit(const Rootkit& ob);
    Rootkit(double impact, int zi, int luna, int an, const string &denumire,const vector<string> &registrii,const string &metodeDeInfectare, const vector<string> &importuri, const vector<string> &semnificative);

    virtual ~Rootkit();

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    double calculeazaRaiting() override;
};

double Rootkit::calculeazaRaiting() {
    double raiting=Malware::calculeazaRaiting();
    for(int i=0; i<semnificative.size(); i++){
        if(semnificative[i]=="System Service Descriptor Table"||semnificative[i]=="SSDT"||semnificative[i]=="NtCreateFile")
            raiting=raiting+100;
    }
    for(int i=0; i<importuri.size(); i++){
        if(importuri[i]=="ntoskrnl.exe")
            raiting=raiting*2;
    }
    return raiting;
}

Rootkit::Rootkit(): Malware(),importuri(),semnificative() {}

Rootkit::Rootkit(const Rootkit &ob) {
    impact=ob.impact;
    zi=ob.zi;
    luna=ob.luna;
    an=ob.an;
    denumire=ob.denumire;
    metode_de_infectare=ob.metode_de_infectare;
    registrii=ob.registrii;
    importuri=ob.importuri;
    semnificative=ob.semnificative;
}

Rootkit::Rootkit(double impact, int zi, int luna, int an, const string &denumire,
                 const vector<string> &registrii, const string &metodeDeInfectare,const vector<string> &importuri, const vector<string> &semnificative)
        : Malware(impact, zi, luna, an, denumire, registrii, metodeDeInfectare), importuri(importuri),
          semnificative(semnificative) {}

Rootkit::~Rootkit(){
    importuri.clear();
    semnificative.clear();
}

istream &Rootkit::read(istream &is) {
    Malware::read(is);
    int nr;
    while(true){
        try{
            cout<<"Numarul de importuri:\n";
            is>>nr;
            if(nr<0)
                throw string ("Nu e bine!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }
    cout<<"Importuri:\n";
    for(int i=0; i<nr; i++){
        cout<<"Import:\n";
        string x;
        is>>x;
        importuri.push_back(x);
    }
    nr=0;
    while(true){
        try{
            cout<<"Numarul de semnificative:\n";
            is>>nr;
            if(nr<0)
                throw string ("Nu e bine!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }
    cout<<"Semnificative:\n";
    for(int i=0; i<nr; i++){
        cout<<"Semnificativ:\n";
        string x;
        is>>x;
        semnificative.push_back(x);
    }
    return is;
}

ostream &Rootkit::write(ostream &os) const{
    Malware::write(os);
    os<<"Importuri:\n";
    for(int i=0; i<importuri.size(); i++)
        os<<importuri[i]<<"\n";
    os<<"Semnificative:\n";
    for(int i=0; i<semnificative.size(); i++)
        os<<semnificative[i]<<"\n";
    return os;
}

class Keylogger: virtual public Malware{
protected:
    vector<string> actiuni;
    vector<string> taste;
public:
    Keylogger();
    Keylogger(const Keylogger& ob);
    Keylogger(double impact, int zi, int luna, int an, const string &denumire, const string &metodeDeInfectare,const vector<string> &registrii, const vector<string> &actiuni, const vector<string> &taste);

    virtual ~Keylogger();

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    double calculeazaRaiting() override;
};

double Keylogger::calculeazaRaiting() {
    double raiting=Malware::calculeazaRaiting();
    for(int i=0; i<taste.size(); i++){
        if(taste[i]=="Up"||taste[i]=="Num Lock"||taste[i]=="Down"||taste[i]=="Right"||taste[i]=="UP"||taste[i]=="Left")
            raiting=raiting+10;
    }
    for(int i=0; i<actiuni.size(); i++){
        if(actiuni[i]=="CreateFileW"||actiuni[i]=="OpenProcess"||actiuni[i]=="ReadFile"||actiuni[i]=="WriteFile"||actiuni[i]=="RegisterHotKey"||actiuni[i]=="SetWindowsHookEx")
            raiting=raiting+30;
    }
    return raiting;
}

Keylogger::Keylogger():Malware(), actiuni(),taste() {}

Keylogger::Keylogger(const Keylogger &ob) {
    impact=ob.impact;
    zi=ob.zi;
    luna=ob.luna;
    an=ob.an;
    denumire=ob.denumire;
    metode_de_infectare=ob.metode_de_infectare;
    registrii=ob.registrii;
    actiuni=ob.actiuni;
    taste=ob.taste;
}

Keylogger::~Keylogger(){
    actiuni.clear();
    taste.clear();
}

Keylogger::Keylogger(double impact, int zi, int luna, int an, const string &denumire, const string &metodeDeInfectare,
                     const vector<string> &registrii, const vector<string> &actiuni, const vector<string> &taste)
        : Malware(impact, zi, luna, an, denumire, registrii, metodeDeInfectare), actiuni(actiuni), taste(taste) {}

istream &Keylogger::read(istream &is) {
    Malware::read(is);
    int nr;
    while(true){
        try{
            cout<<"Numarul de actiuni:\n";
            is>>nr;
            if(nr<0)
                throw string ("Nu e bine!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }
    cout<<"Actiuni:\n";
    for(int i=0; i<nr; i++){
        cout<<"Actiune:\n";
        string x;
        is>>x;
        actiuni.push_back(x);
    }
    nr=0;
    while(true){
        try{
            cout<<"Numarul de taste:\n";
            is>>nr;
            if(nr<0)
                throw string ("Nu e bine!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }
    cout<<"Taste:\n";
    for(int i=0; i<nr; i++){
        cout<<"Tasta:\n";
        string x;
        is>>x;
        taste.push_back(x);
    }
    return is;
}

ostream &Keylogger::write(ostream &os) const {
    Malware::write(os);
    os<<"Actiuni:\n";
    for(int i=0; i<actiuni.size(); i++)
        os<<actiuni[i]<<"\n";
    os<<"Taste:\n";
    for(int i=0; i<taste.size(); i++)
        os<<taste[i]<<"\n";
    return os;
}

class Kernel_Keylogger: public Rootkit, public Keylogger{
private:
    bool ascunde_fisiere;
    bool ascunde_registrii;
public:
    Kernel_Keylogger()=default;
    Kernel_Keylogger(const Kernel_Keylogger& ob);
    Kernel_Keylogger(double impact, int zi, int luna, int an, const string &denumire, const vector<string> &registrii,
                     const string &metodeDeInfectare, const vector<string> &importuri,
                     const vector<string> &semnificative,
                     const vector<string> &actiuni, const vector<string> &taste, bool ascundeFisiere,
                     bool ascundeRegistrii) : Malware(impact, zi, luna, an, denumire, registrii, metodeDeInfectare),ascunde_fisiere(ascundeFisiere),
                                              ascunde_registrii(ascundeRegistrii) {
        this->importuri=importuri;
        this->semnificative=semnificative;
        this->actiuni=actiuni;
        this->taste=taste;

    }
    ~Kernel_Keylogger();

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    double calculeazaRaiting() override;
};

double Kernel_Keylogger::calculeazaRaiting() {
    double raiting=Malware::calculeazaRaiting();
    for (int i = 0; i < semnificative.size(); i++) {
        if (semnificative[i] == "System Service Descriptor Table" || semnificative[i] == "SSDT" ||
            semnificative[i] == "NtCreateFile")
            raiting = raiting + 100;
    }

    for (int i = 0; i < importuri.size(); i++) {
        if (importuri[i] == "ntoskrnl.exe")
            raiting = raiting * 2;
    }

    for (int i = 0; i < taste.size(); i++) {
        if (taste[i] == "Up" || taste[i] == "Num Lock" || taste[i] == "Down" || taste[i] == "Right" ||
            taste[i] == "UP" || taste[i] == "Left")
            raiting = raiting + 10;
    }
    for (int i = 0; i < actiuni.size(); i++) {
        if (actiuni[i] == "CreateFileW" || actiuni[i] == "OpenProcess" || actiuni[i] == "ReadFile" ||
            actiuni[i] == "WriteFile" || actiuni[i] == "RegisterHotKey" || actiuni[i] == "SetWindowsHookEx")
            raiting = raiting + 30;
    }
    if (ascunde_fisiere == 1)
        raiting = raiting + 20;
    if(ascunde_registrii==1)
        raiting=raiting+30;
    return raiting;
}

Kernel_Keylogger::Kernel_Keylogger(const Kernel_Keylogger &ob) {
    impact=ob.impact;
    zi=ob.zi;
    luna=ob.luna;
    an=ob.an;
    denumire=ob.denumire;
    metode_de_infectare=ob.metode_de_infectare;
    registrii=ob.registrii;
    importuri=ob.importuri;
    semnificative=ob.semnificative;
    actiuni=ob.actiuni;
    taste=ob.taste;
    ascunde_fisiere=ob.ascunde_fisiere;
    ascunde_registrii=ob.ascunde_registrii;
}

Kernel_Keylogger::~Kernel_Keylogger() {
    ascunde_registrii= false;
    ascunde_fisiere= false;
}

istream &Kernel_Keylogger::read(istream &is){
    Malware::read(is);
    int nr;
    while(true){
        try{
            cout<<"Numarul de importuri:\n";
            is>>nr;
            if(nr<0)
                throw string ("Nu e bine!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }
    cout<<"Importuri:\n";
    for(int i=0; i<nr; i++){
        cout<<"Import:\n";
        string x;
        is>>x;
        importuri.push_back(x);
    }
    nr=0;
    while(true){
        try{
            cout<<"Numarul de semnificative:\n";
            is>>nr;
            if(nr<0)
                throw string ("Nu e bine!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }
    cout<<"Semnificative:\n";
    for(int i=0; i<nr; i++) {
        cout << "Semnificativ:\n";
        string x;
        is >> x;
        semnificative.push_back(x);
    }
    nr=0;
    while(true){
        try{
            cout<<"Numarul de actiuni:\n";
            is>>nr;
            if(nr<0)
                throw string ("Nu e bine!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }
    cout<<"Actiuni:\n";
    for(int i=0; i<nr; i++){
        cout<<"Actiune:\n";
        string x;
        is>>x;
        actiuni.push_back(x);
    }
    nr=0;
    while(true){
        try{
            cout<<"Numarul de taste:\n";
            is>>nr;
            if(nr<0)
                throw string ("Nu e bine!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }
    cout<<"Taste:\n";
    for(int i=0; i<nr; i++){
        cout<<"Tasta:\n";
        string x;
        is>>x;
        taste.push_back(x);
    }
    ascunde_fisiere=0;
    cout<<"Introduceti 1 daca ascunde fisiere si 0 altfel:\n";
    is>>ascunde_fisiere;
    ascunde_registrii=0;
    cout<<"Introduceti 1 daca ascunde registrii si 0 altfel:\n";
    is>>ascunde_registrii;
    return is;
}

ostream &Kernel_Keylogger::write(ostream &os) const {
    Malware::write(os);
    os<<"Importuri:\n";
    for(int i=0; i<importuri.size(); i++)
        os<<importuri[i]<<"\n";
    os<<"Semnificative:\n";
    for(int i=0; i<semnificative.size(); i++)
        os<<semnificative[i]<<"\n";
    os<<"Actiuni:\n";
    for(int i=0; i<actiuni.size(); i++)
        os<<actiuni[i]<<"\n";
    os<<"Taste:\n";
    for(int i=0; i<taste.size(); i++)
        os<<taste[i]<<"\n";
    if(ascunde_fisiere==0)
        cout<<"Nu ascunde fisierele.\n";
    else
        cout<<"Ascunde fisierele.\n";
    if(ascunde_registrii==0)
        cout<<"Nu ascunde registrii.\n";
    else
        cout<<"Ascunde registrii.\n";
    return os;
}

class Ransomware: public Malware{
private:
    int raiting_criptare;
    double raiting_obfuscare;
public:
    Ransomware();
    Ransomware(const Ransomware& ob);
    Ransomware(double impact, int zi, int luna, int an, const string &denumire, const vector<string> &registrii,
               const string &metodeDeInfectare, int raitingCriptare, double raitingObfuscare);
    ~Ransomware();

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    double calculeazaRaiting() override;
};

double Ransomware::calculeazaRaiting() {
    double raiting=Malware::calculeazaRaiting();
    raiting+=raiting_criptare+raiting_obfuscare;
    return raiting;
}

Ransomware::Ransomware(): Malware(){
    raiting_criptare=0;
    raiting_obfuscare=0;
}

Ransomware::Ransomware(const Ransomware& ob) {
    impact=ob.impact;
    zi=ob.zi;
    luna=ob.luna;
    an=ob.an;
    denumire=ob.denumire;
    metode_de_infectare=ob.metode_de_infectare;
    registrii=ob.registrii;
    raiting_criptare=ob.raiting_criptare;
    raiting_obfuscare=ob.raiting_obfuscare;
}

Ransomware::Ransomware(double impact, int zi, int luna, int an, const string &denumire, const vector<string> &registrii,
                       const string &metodeDeInfectare, int raitingCriptare, double raitingObfuscare) : Malware(
        impact, zi, luna, an, denumire, registrii, metodeDeInfectare), raiting_criptare(raitingCriptare),raiting_obfuscare(raitingObfuscare) {}

Ransomware::~Ransomware(){
    raiting_obfuscare=0;
    raiting_criptare=0;
}

istream &Ransomware::read(istream &is) {
    Malware::read(is);
    cout<<"Introduceti raiting-ul de criptare:\n";
    is>>raiting_criptare;
    cout<<"Introduceti raiting-ul de obfuscare:\n";
    is>>raiting_obfuscare;
    return is;
}

ostream &Ransomware::write(ostream &os) const {
    Malware::write(os);
    os<<"Raiting-ul de criptare este: "<<raiting_criptare<<"\n";
    os<<"Raiting-ul de obfuscare este: "<<raiting_obfuscare<<"\n";
    return os;
}

class Computer: public IoBase{
private:
    static int id;
    int cod;
    double raiting_final;
    vector<shared_ptr<Malware>> virusi;
public:
    Computer(){
        cod=++id;
    };

    Computer(const vector<shared_ptr<Malware>> &virusi);

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    double getRaitingFinal() const;
};
int Computer::id=0;

Computer::Computer(const vector<shared_ptr<Malware>> &virusi):virusi(virusi) {
    ++id;
    cod=id;
    for(int i=0; i<virusi.size(); i++)
        raiting_final=raiting_final+virusi[i]->calculeazaRaiting();
}

istream &Computer::read(istream &is) {
    IoBase::read(is);
    int nr;
    while(true){
        try{
            cout<<"Numarul de virusi:\n";
            is>>nr;
            if(nr<0)
                throw string ("Nu e bine!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }
    for(int i=0; i<nr; i++) {
        int tip;
        cout << "Introuduceti 1-rootkit, 2-keylogger, 3-kernel_logger, 4-ransomware.\n";
        is >> tip;
        if (tip < 0 || tip > 4) {
            cout << "Tip invalid!\n";
            cout << "Reintrodu tipul jucariei!\n";
            is >> tip;
        } else {
            if (tip == 1) {
                Rootkit p;
                is >> p;
                virusi.emplace_back(make_shared<Rootkit>(p));
                raiting_final+=p.calculeazaRaiting();
            } else if (tip == 2) {
                Keylogger p;
                is >> p;
                virusi.emplace_back(make_shared<Keylogger>(p));
                raiting_final+=p.calculeazaRaiting();
            } else if (tip == 3) {
                Kernel_Keylogger p;
                is >> p;
                virusi.emplace_back(make_shared<Kernel_Keylogger>(p));
                raiting_final+=p.calculeazaRaiting();
            } else if (tip == 4) {
                Ransomware p;
                is >> p;
                virusi.emplace_back(make_shared<Ransomware>(p));
                raiting_final+=p.calculeazaRaiting();
            }
        }
    }
    return is;
}

ostream &Computer::write(ostream &os) const {
    IoBase::write(os);
    os << "Cod: " << cod << "\n";
    os << "Raiting final: " << raiting_final << "\n";
    os << "Virusi:\n";
    for (const auto &i: virusi) {
        auto *asRootkit = dynamic_cast<Rootkit *>(i.get());
        auto *asKeylogger = dynamic_cast<Keylogger *>(i.get());
        auto *asKernel_Keylogger = dynamic_cast<Kernel_Keylogger *>(i.get());
        auto *asRansomware = dynamic_cast<Ransomware *>(i.get());

        if (asRootkit) {
            cout << *asRootkit;
        } else if (asKeylogger) {
            cout << *asKeylogger;
        } else if (asKernel_Keylogger) {
            cout << *asKernel_Keylogger;
        } else if (asRansomware) {
            cout << *asRansomware;
        }
    }
    return os;
}

double Computer::getRaitingFinal() const {
    return raiting_final;
}

class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};

class SimpleMenu : public BaseMenu {
private:
    vector<Computer*> calculatoare;
public:
    void listOptions() override {
        cout << "1. Adauga calculator." << '\n';
        cout << "2. Afisare informatiilor pentru fiecare calculator." << '\n';
        cout << "3. Afisare informatiilor pentru fiecare calculator fiind ordonate dupa raitingul final." << '\n';
        cout << "4. Afisarea primelor k calculatoare ordonate dupa raitingul final." << '\n';
        cout << "5. Afisare procent de computere infectate in firma." << '\n';
        cout << "6. Iesire." << '\n';
    }

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

    void option1();

    void option2();

    void option3();

    void option4();

    void option5();

    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 6);
            if (option == 1) {
                option1();
            } else if (option == 2) {
                option2();
            } else if (option == 3) {
                option3();
            }else if (option == 4) {
                option4();
            }else if (option == 5) {
                option5();
            }else if (option == 6) {
                break;
            }
        }
        cout << '\n'
             << "---------------------------------"
             << '\n'
             << "Programul s-a incheiat cu success";
    }

};

void SimpleMenu::option1() {
    Computer *c=new Computer;
    cout<<"Calculator:\n";
    cin>>*c;
    calculatoare.push_back(c);
}

void SimpleMenu::option2() {
    for(int i=0; i<calculatoare.size(); i++)
        cout<<*calculatoare[i]<<"\n";
    cout<<"\n";
}

void SimpleMenu::option3() {
    for(int i=0; i<calculatoare.size()-1; i++){
        for(int j=i+1; j<calculatoare.size(); j++){
            if(calculatoare[i]->getRaitingFinal()>calculatoare[j]->getRaitingFinal())
                swap(calculatoare[i],calculatoare[j]);
        }
    }
    for(int i=0; i<calculatoare.size(); i++)
        cout<<*calculatoare[i]<<"\n";
    cout<<"\n";
}

void SimpleMenu::option4() {
    int k;
    while(true){
        cout<<"Introduceti k:\n";
        cin>>k;
        try{
            if(k<=0)
                throw string("Numar invalid!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }
    for(int i=0; i<calculatoare.size()-1; i++){
        for(int j=i+1; j<calculatoare.size(); j++){
            if(calculatoare[i]->getRaitingFinal()>calculatoare[j]->getRaitingFinal())
                swap(calculatoare[i],calculatoare[j]);
        }
    }
    for(int i=0; i<k; i++)
        cout<<*calculatoare[i]<<"\n";
    cout<<"\n";
}

void SimpleMenu::option5() {
    double procent;
    int nr=0;
    for(int i=0; i<calculatoare.size(); i++)
        if(calculatoare[i]->getRaitingFinal()!=0)
            nr++;
    if(calculatoare.size()>0){
        procent=100.0*((double) nr)/((double)calculatoare.size());
        cout<<"Procentul de infectare este: "<<procent<<"\n";
    }
    else
        cout<<"Nu exista calculatoare!";
}
int main() {
    SimpleMenu menu;
    menu.mainLoop();
}
