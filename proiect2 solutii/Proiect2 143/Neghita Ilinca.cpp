/* Nume Prenume: Nechita Maria-Ilinca Grupa: 143
Compilator:
Tutore de laborator : Deaconu Stefan-Eduard*/

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

//Prin malware înțelegem un software rău intenționat pentru care se reține impactul impactului
//(număr real), data de infectare (zi, luna, an), numele acestuia
//(care poate să fie format din mai multe cuvinte),
//metoda de infectare (dacă se cunoaște, altfel se reține șirul “unknown”)
//un vector cu registrii modificați (reținuți ca stringuri).

// construim clasa Malware cu atributele mentionate mai sus
class Malware{
protected:
    double impact{};
    int zi, luna, an;
    string nume, metoda_infectare;
    vector <string> registrii;
public:
    // constructorul - nul
    Malware (){zi=0,luna=0,an=0; nume=" ", metoda_infectare = " " ;}
    Malware(double impact, int zi, int luna, int an, string nume, string metodaInfectare, const vector<string> &registrii) : impact(impact), zi(zi), luna(luna), an(an), nume(std::move(nume)),metoda_infectare(std::move(metodaInfectare)), registrii(registrii) {}
    // constructor de copiere
    Malware(const Malware&ob){
        impact = ob.impact;
        zi = ob.zi;
        luna = ob.luna;
        an = ob.an;
        nume = ob.nume;
        metoda_infectare = ob.metoda_infectare;
        registrii = ob.registrii;}
    // operatorul atribuire
    Malware &operator=(const Malware &ob)
    = default;
    virtual ~Malware(){
        impact = 0;
        zi = luna = an = 0;
        nume.clear();
        metoda_infectare.clear();
        registrii.clear();
    };

    // setteri si getteri pentru fiecare atributa a clasei

    double getImpact() const {return impact;}
    void setImpact(double _impact){impact=_impact;}

    int getZi() const {return zi;}
    void setZi(int _zi){zi=_zi;}

    int getLuna() const {return luna;}
    void setLuna(int _luna){luna=_luna;}

    int getAn() const {return an;}
    void setAn(int _an){an=_an;}

    const string &getNume() {return nume;}
    void setNume(const string &_nume) {nume=_nume;}

    const string &getMetodaInfectare() {return metoda_infectare;}
    void setMetodaInfectare(const string &_metodainfectare) {metoda_infectare=_metodainfectare;}

    const vector<string> &getRegistrii() const {return registrii;}

    void setRegistrii(const vector<string> &vector) { Malware::registrii = vector;}

    // metode virtuale pure care vor fi folosite in urmatoarele clase
    virtual istream& readMalware(istream& is) = 0;
    virtual ostream& printMalware(ostream& os) = 0;
    virtual double calculeaza() = 0;
};

//Prin rootkit înțelegem un tip de malware ce are drept scop obținerea drepturilor de administrator asupra dispozitivului infectat.
//Pentru rootkit se reține lista importurilor care poate fi unul și oricât de multe
//(importurile fac referire la numele fișierelor .dll folosite) și
//o listă de stringuri semnificative (anumite stringuri dintr-un binar pot fi un indice asupra faptului că fișierul este rău intenționat).

class Rootkit:virtual public Malware{
protected:
    vector <string> importuri;
    vector <string> semnificative;
public:
    // constructorii -nul, normal, copiere
    Rootkit():Malware(),importuri(),semnificative(){};
    Rootkit(const Rootkit & ob) : Malware(ob) {
        impact = ob.impact;
        zi = ob.zi;
        luna = ob.luna;
        an = ob.an;
        nume = ob.nume;
        metoda_infectare = ob.metoda_infectare;
        registrii = ob.registrii;
        importuri = ob.importuri;
        semnificative = ob.semnificative;
    }
    Rootkit & operator=(const Rootkit &ob) {
        impact = ob.impact;
        zi = ob.zi;
        luna = ob.luna;
        an = ob.an;
        nume = ob.nume;
        metoda_infectare = ob.metoda_infectare;
        registrii = ob.registrii;
        importuri = ob.importuri;
        semnificative = ob.semnificative;
        return *this;
    }
    ~Rootkit() override{
        importuri.clear();
        semnificative.clear();
    }

    Rootkit(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare, const vector<string> &registrii, const vector<string> &importuri, const vector<string> &semnificative): Malware(impact, zi, luna, an, denumire, metodaDeInfectare, registrii), importuri(importuri),semnificative(semnificative) {}

    // getteri si setteri
    const vector<string> &getImporturi() const {return importuri;}
    void setImporturi(const vector<string> &vector) { Rootkit::importuri = vector;}

    const vector<string> &getSeminificative() const {return semnificative;}
    void setSemnificative(const vector<string> &semnificative) {Rootkit::semnificative = semnificative;}

    istream& readMalware(istream& is) override;
    ostream& printMalware(ostream& os) override;
    double calculeaza() override;
};

// Pentru rootkit ratingul impactului crește cu 100 dacă se întâlnește unul din stringurile “System Service Descriptor Table”,
// “SSDT”, “NtCreateFile”. Dacă se regăsește importul “ntoskrnl.exe”, valoarea impactului
// se dublează (importurile se verifică după stringuri).
double Rootkit :: calculeaza(){
    double value=impact;
    for (int i=0;i<semnificative.size();i++)
    {
        if (semnificative[i]=="System Service Descriptor Table" ||semnificative[i]=="SSDT" || semnificative[i]=="NtCreateFile" )
           {value+=100;
            break;}
    }
//Pentru orice tip de malware se adună 20 dacă registrii afectați sunt “HKLM-run” sau “HKCU-run”.
    for (int i=0;i<registrii.size();i++)
    {
        if (registrii[i]=="HKLM-run" ||registrii[i]=="HKCU-run")
           {value+=20;
            break;}
    }

    for (int i=0;i<importuri.size();i++)
    {
        if (importuri[i]=="ntoskrnl.exe")
           {value=value*2;
            break;}
    }
    return value;
}

istream & Rootkit::readMalware(istream &is){
    cout << "Impact:\n";
    is >> impact;
    is.get();
    cout << "Data:\n";
    cout << "An:\n";
    int bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
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
    cout << "Denumire:\n";
    getline(is, nume);
    cout << "Metoda de infectare:\n";
    getline(is, metoda_infectare);
    int nr;
    while(true){
        try{

            cout << "Numar registrii:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Registru:\n";
        string s;
        getline(is, s);
        registrii.push_back(s);
    }

    while(true){
        try{

            cout << "Numar importuri:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Import:\n";
        string s;
        getline(is, s);
        importuri.push_back(s);
    }
    while(true){
        try{

            cout << "Numar semnificative:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Semnificativ:\n";
        string s;
        getline(is, s);
        semnificative.push_back(s);
    }
    return is;
}

ostream & Rootkit::printMalware(ostream &os) {
    os << "Impact: " << impact << "\n";
    os << "Data: " << zi << '/' << luna << '/' << an << '\n';
    os << "Denumire: " << nume << '\n';
    os << "Metoda de inf: " << metoda_infectare << '\n';
    os << "Registrii:\n";
    for(auto & i : registrii){
        cout  << i << '\n';
    }
    os  << "Importuri:\n";
    for(auto & i : importuri){
        cout  << i << '\n';
    }
    os << "Semnificative:\n";
    for(auto & i : semnificative){
        os << i << '\n';
    }
    return os;
}

//Prin keylogger înțelegem un malware care înregistrează acțiunile de la tastatură și le trimite mai departe.
//Pentru un keylogger se reține o listă cu funcțiile folosite și o listă cu tastele speciale definite.
class Keylogger:virtual public Malware{
protected:
    vector <string> functii;
    vector <string> taste;
public:
    // constructorii -nul, normal, copiere
    Keylogger():Malware(),functii(),taste(){};
    Keylogger(const Keylogger & ob) : Malware(ob) {
        impact = ob.impact;
        zi = ob.zi;
        luna = ob.luna;
        an = ob.an;
        nume = ob.nume;
        metoda_infectare = ob.metoda_infectare;
        registrii = ob.registrii;
        functii = ob.functii;
        taste = ob.taste;
    }
    Keylogger & operator=(const Keylogger &ob) {
        impact = ob.impact;
        zi = ob.zi;
        luna = ob.luna;
        an = ob.an;
        nume = ob.nume;
        metoda_infectare = ob.metoda_infectare;
        registrii = ob.registrii;
        functii = ob.functii;
        taste = ob.taste;
        return *this;
    }
    ~Keylogger(){
        functii.clear();
        taste.clear();
    }

    Keylogger(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare, const vector<string> &registrii, const vector<string> &importuri, const vector<string> &semnificative);

    // getteri si setteri
    const vector<string> &getFunctii() const {return functii;}
    void setFunctii(const vector<string> &functii) {Keylogger::functii = functii;}

    const vector<string> &getTaste() const {return taste;}
    void setTaste(const vector<string> &taste) {Keylogger::taste = taste;}

    istream& readMalware(istream& is) override;
    ostream& printMalware(ostream& os) override;
    double calculeaza() override;

};

//Pentru keylogger ratingul impactului crește cu 10 la întâlnirea stringurilor “[Up]”, “[Num Lock]”
//“[Down]”, “[Right]”, “[UP]”, “[Left]”, “[PageDown]” și
//cu 30 la întâlnirea unei din funcțiile: “CreateFileW”, “OpenProcess”, “ReadFile”, “WriteFile”,
//“RegisterHotKey”, “SetWindowsHookEx”.

double Keylogger :: calculeaza() {
    double value = impact;
    for (int i = 0; i < registrii.size(); ++i)
        if (registrii[i] == "“HKLM-run" || registrii[i] == "HKCU-run") {
            value += 20;
            break;
        }
    for (int i = 0; i < taste.size(); i++) {
        if (taste[i] == "[Up]" || taste[i] == "[Num Lock]" || taste[i] == "[Down]" || taste[i] == "[Right]" ||
            taste[i] == "[Left]" || taste[i] == "UP" || taste[i] == "[PageDown]")
            value += 10;
    }
//Pentru orice tip de malware se adună 20 dacă registrii afectați sunt “HKLM-run” sau “HKCU-run”.
    for (int i = 0; i < functii.size(); i++) {
        if (functii[i] == "CreateFileW" || functii[i] == "OpenProcess" || functii[i] == "ReadFile" ||
            functii[i] == "WriteFile" || functii[i] == "RegisterHotKey" || functii[i] == "SetWindowsHookEx")
            value += 30;
    }
    return value;
}

istream & Keylogger::readMalware(istream &is) {
    cout << "Impact:\n";
    is >> impact;
    is.get();
    cout << "Data:\n";
    cout << "An:\n";
    bool bisect = 0;
//verificam daca datele introduse sunt valide
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
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
    cout << "Denumire:\n";
    getline(is, nume);
    cout << "Metoda de infectare:\n";
    getline(is, metoda_infectare);
    int nr;

    while(true){
        try{

            cout << "Numar registrii:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Registru:\n";
        string s;
        getline(is, s);
        registrii.push_back(s);
    }

    while(true){
        try{

            cout << "Numar Functii:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Import:\n";
        string s;
        getline(is, s);
        functii.push_back(s);
    }
    while(true){
        try{

            cout << "Numar taste:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Taste:\n";
        string s;
        getline(is, s);
        taste.push_back(s);
    }
    return is;
}

ostream & Keylogger::printMalware(ostream &os) {
    os << "Impact: " << impact << "\n";
    os << "Data: " << zi << '/' << luna << '/' << an << '\n';
    os << "Denumire: " << nume << '\n';
    os << "Metoda de inf: " << metoda_infectare << '\n';
    os << "Registrii:\n";
    for(int i = 0;i < registrii.size() ; ++i){
        cout  << registrii[i] << '\n';
    }
    os  << "Functii:\n";
    for(int i = 0;i < functii.size() ; ++i){
        cout  << functii[i] << '\n';
    }
    os << "Taste:\n";
    for(int i = 0;i < taste.size() ; ++i){
        os << taste[i] << '\n';
    }
    return os;
}

Keylogger::Keylogger(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare,
                     const vector<string> &registrii, const vector<string> &importuri,
                     const vector<string> &semnificative) : Malware(impact, zi, luna, an, denumire, metodaDeInfectare, registrii), functii(functii),taste(taste) {}

//Prin kernel-keylogger înțelegem un keylogger ce rulează în kernel-mode (prin intermediul unui rootkit).
//Prin urmare, putem considera că este are atât proprietățile unui rootkit
//cât și ale unui keylogger. În plus, dorim să memorăm dacă ascunde fișiere și registrii.

class KernelKeylogger: virtual public  Rootkit,virtual public Keylogger{
private:
    bool hide_files;
    bool hide_registers;
public:
    KernelKeylogger() = default;

    KernelKeylogger(const KernelKeylogger &ob) {
        impact = ob.impact;
        zi = ob.zi;
        luna = ob.luna;
        nume = ob.nume;
        an = ob.an;
        metoda_infectare = ob.metoda_infectare;
        registrii = ob.registrii;
        functii = ob.functii;
        taste = ob.taste;
        importuri = ob.importuri;
        semnificative = ob.semnificative;
    }
    KernelKeylogger &operator=(const KernelKeylogger &ob) {
        impact = ob.impact;
        zi = ob.zi;
        luna = ob.luna;
        nume = ob.nume;
        an = ob.an;
        metoda_infectare = ob.metoda_infectare;
        registrii = ob.registrii;
        functii = ob.functii;
        taste = ob.taste;
        importuri = ob.importuri;
        semnificative = ob.semnificative;
        return *this;
    }
    KernelKeylogger(double impact, int zi, int luna, int an, const string &denumire,
                    const string &metodaDeInfectare, const vector<string> &registrii,
                    const vector<string> &importuri, const vector<string> &semnificative, const vector<string> &functii, const vector<string> &taste,
                    bool hideFiles, bool hideRegisters) : Malware(impact, zi, luna, an, denumire,metodaDeInfectare, registrii),
                                                          hide_files(hideFiles),hide_registers(hideRegisters) {
        this->importuri = importuri;
        this->semnificative = semnificative;
        this->functii = functii;
        this->taste = taste;
    }

    ~KernelKeylogger() override{
        hide_files = hide_registers= 0;
    }
    istream& readMalware(istream& is) override;
    ostream& printMalware(ostream& os) override;
    double calculeaza() override;

};

//Pentru kernel keylogger se respectă valorile de la rootkit și keylogger și se adaugă
//valoarea 20 dacă ascunde fișiere, respectiv valoarea 30 dacă ascunde registrii.
double KernelKeylogger :: calculeaza()
{
    double value = impact;
    for(int i =0;i < registrii.size(); ++i)
        if(registrii[i] == "“HKLM-run" || registrii[i] == "HKCU-run"){
            value += 20;
            break;
        }
    for(int i = 0;i < semnificative.size(); ++i)
        if(semnificative[i] == "System Service Descriptor Table" || semnificative[i] == "SSDT" || semnificative[i] == "NtCreateFile" ){
            value += 100;
            break;
        }
    for(int i = 0;i < importuri.size(); ++i)
        if(importuri[i] == "ntoskrnl.exe"){
            value = value *2;
            break;
        }
    for(int i = 0;i < functii.size(); ++i)
        if(functii[i] == "CreateFileW" || functii[i] == "OpenProcess" || functii[i] == "ReadFile" || functii[i] =="WriteFile" || functii[i] == "RegisterHotKey"  || functii[i] == "SetWindowsHookEx" )
            value += 30;
    for(int i = 0;i < taste.size(); ++i)
        if(taste[i] == "Up" || taste[i] == "Num Lock" || taste[i] == "Down" || taste[i] =="Right" || taste[i] == "UP"  || taste[i] == "Left" || taste[i] == "PageDown" )
            value += 10;
    if(hide_registers)
        value += 30;
    if(hide_files)
        value += 20;
    return value;
}

ostream & KernelKeylogger::printMalware(ostream &os) {
    os << "Impact: " << impact << "\n";
    os << "Data: " << zi << '/' << luna << '/' << an << '\n';
    os << "Denumire: " << nume << '\n';
    os << "Metoda de inf: " << metoda_infectare << '\n';
    os << "Registrii:\n";
    for(int i = 0;i < registrii.size() ; ++i){
        cout  << registrii[i] << '\n';
    }
    os  << "Importuri:\n";
    for(auto & i : importuri){
        cout  << i << '\n';
    }
    os << "Semnificative:\n";
    for(auto & i : semnificative){
        os << i << '\n';
    }
    os  << "Functii:\n";
    for(auto & i : functii){
        cout  << i << '\n';
    }
    os << "Taste:\n";
    for(auto & i : taste){
        os << i << '\n';
    }
    return os;
}
istream & KernelKeylogger::readMalware(istream &is) {
    cout << "Impact:\n";
    is >> impact;
    is.get();
    cout << "Data:\n";
    cout << "An:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
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
    cout << "Denumire:\n";
    getline(is, nume);
    cout << "Metoda de infectare:\n";
    getline(is, metoda_infectare);
    int nr;

    while(true){
        try{

            cout << "Numar registrii:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Registru:\n";
        string s;
        getline(is, s);
        registrii.push_back(s);
    }

    while(true){
        try{

            cout << "Numar Functii:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Functii:\n";
        string s;
        getline(is, s);
        functii.push_back(s);
    }
    while(true){
        try{

            cout << "Numar taste:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Taste:\n";
        string s;
        getline(is, s);
        taste.push_back(s);
    }
    while(true){
        try{

            cout << "Numar importuri:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Import:\n";
        string s;
        getline(is, s);
        importuri.push_back(s);
    }
    while(true){
        try{

            cout << "Numar semnificative:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Semnificativ:\n";
        string s;
        getline(is, s);
        semnificative.push_back(s);
    }
    return is;
}

//Prin ransomware înțelegem un malware care criptează fișiere de pe disk. Pentru acesta se reține:
//ratingul de criptare (un număr de la 1 la 10)
//și un rating de obfuscare (un număr real ce reprezintă procentul de obfuscare
//(obfuscare = metodă de a ascunde/îngreuna intenția inițială a codului)).

class Ransomware:public Malware{
private:
    Ransomware(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare,
               const vector<string> &registrii, int rating, double ofuscare);

    int criptare;
    double obfuscare;
public:
    // constructorii- nul, normal, de copiere, atributul =
    Ransomware() : Malware(), criptare(),obfuscare() {}
    Ransomware(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare,
               const vector<string> &registrii, double Criptare, double Obfuscare) : Malware(impact,zi,luna,an,
                                                                                                         denumire,
                                                                                                         metodaDeInfectare,registrii),
                                                                                                 criptare(Criptare),
                                                                                                 obfuscare(Obfuscare) {}
    Ransomware(const Ransomware &ob) : Malware(ob) {
        impact = ob.impact;
        zi = ob.zi;
        luna = ob.luna;
        nume = ob.nume;
        an = ob.an;
        metoda_infectare = ob.metoda_infectare;
        registrii = ob.registrii;
        obfuscare = ob.obfuscare;
        criptare = ob.criptare;
    }

    Ransomware & operator=(const Ransomware &ob) {
        impact = ob.impact;
        zi = ob.zi;
        luna = ob.luna;
        nume = ob.nume;
        an = ob.an;
        metoda_infectare = ob.metoda_infectare;
        registrii = ob.registrii;
        obfuscare = ob.obfuscare;
        criptare = ob.criptare;
        return *this;
    }

    ~Ransomware() override {
        criptare = obfuscare = 0;
    }

    int getCriptare() const {return criptare;}

    void setCriptare(int criptare) {Ransomware::criptare = criptare;}

    double getObfuscare() const {return obfuscare;}

    void setObfuscare(double obfuscare) {Ransomware::obfuscare = obfuscare;}

    istream& readMalware(istream& is);
    ostream& printMalware(ostream& os);
    double calculeaza();
};

double Ransomware::calculeaza() {
    double value = obfuscare + criptare;
    for(int i =0;i < registrii.size(); ++i)
        if(registrii[i] == "“HKLM-run" || registrii[i] == "HKCU-run"){
            value += 20;
            break;
        }
    return value;
}

istream & Ransomware::readMalware(istream &is) {
    cout << "Impact:\n";
    is >> impact;
    is.get();
    cout << "Data:\n";
    cout << "An:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
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
    cout << "Denumire:\n";
    getline(is, nume);
    cout << "Metoda de infectare:\n";
    getline(is, metoda_infectare);
    int nr;

    while(true){
        try{

            cout << "Numar registrii:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Registru:\n";
        string s;
        getline(is, s);
        registrii.push_back(s);
    }
    cout << "Rating criptare:\n";
    is >> criptare;
    is.get();
    cout << "Rating obfuscare:\n";
    is >> obfuscare;
    is.get();
    return is;
}
ostream & Ransomware::printMalware(ostream &os) {
    os << "Impact: " << impact << "\n";
    os << "Data: " << zi << '/' << luna << '/' << an << '\n';
    os << "Denumire: " << nume << '\n';
    os << "Metoda de inf: " << metoda_infectare << '\n';
    os << "Registrii:\n";
    for(auto & i : registrii){
        cout  << i << '\n';
    }
    os <<  "Rating criptare: " << criptare << '\n';
    os << "Rating obfuscare: " << obfuscare << '\n';
    return os;
}

//Pentru fiecare computer din firmă se reține un id unic, incrementat automat,
//o listă de malware (poate conține un malware sau mai multe) și
//ratingul final ce este calculat drept suma ratingului impactului fiecărui malware.

class Computer{
private:
    static int id;
    int cod;
    double rating_final{};
    vector <Malware*> virusi;

public:

    Computer();
    Computer(const Computer& c);
    Computer& operator=(const Computer& c);
    ~Computer();
    Computer(vector < Malware*> virus);

    int getId() {return id;}
    void setId(int id) {Computer::id = id;}

    int getCod() const {return cod;}
    void setCod(int cod) {Computer::cod = cod;}

    double getRatingFinal() const {return rating_final;}
    void setRatingFinal(double ratingFinal) {rating_final = ratingFinal;}

    const vector<Malware *> getVirusi() const {return virusi;}
    void setVirusi(const vector<Malware *> &virusi) {Computer::virusi = virusi;}

    void addVirus(Malware *m);
    friend istream& operator>>(istream& is, Computer& c);
    friend ostream & operator<<(ostream& os, Computer& c);

};
istream& operator>>(istream& is, Computer& c){
    int nr;
    while(true){
        try{

            cout << "Numar virusuri:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr; ++i){
        string tip;
        Malware *p = nullptr;
        while(true){
            try{
                cout << "Introduceti tipul virsurului - root sau key sau ker sau ran \n";
                getline(is, tip);
                if(tip == "root"){
                    p = new Rootkit;
                    break;
                }
                else if(tip == "key"){
                    p = new Keylogger;
                    break;
                }else if(tip == "ker"){
                    p = new KernelKeylogger;
                    break;
                }
                else if(tip == "ran"){
                    p = new Ransomware;
                    break;
                }

                else throw string("Tip invalid!");
            }
            catch(string s){
                cout << s << '\n';
            }
        }
        //is >> *p;
        c.rating_final += p->calculeaza();
        c.virusi.push_back(p);
    }
    return is;

}
ostream & operator<<(ostream& os, Computer& c){
    os << "Cod: " << c.cod << '\n';
    os << "Rating final: " << c.rating_final << '\n';
    os << "Virusi:\n";
    for(auto & i : c.virusi)
        cout << &i << '\n';
    return os;
}
Computer::Computer(vector<Malware *> virus) {
    ++id;
    cod = id;
    for(auto & i : virusi)
        delete i;
    virusi.clear();
    for(auto &i : virus) {
        addVirus(i);
        rating_final += i->calculeaza();
    }
}
void Computer::addVirus(Malware *m) {
    if(Ransomware *d = dynamic_cast<Ransomware*>(m))
        virusi.push_back(new Ransomware(*d));
    else if(Rootkit *d = dynamic_cast<Rootkit*>(m))
        virusi.push_back(new Rootkit(*d));
    else if(Keylogger *d = dynamic_cast<Keylogger*>(m))
        virusi.push_back(new Keylogger(*d));
    else if(KernelKeylogger *d = dynamic_cast<KernelKeylogger*>(m))
        virusi.push_back(new KernelKeylogger(*d));
}

int Computer::id = 0;
Computer::Computer() : virusi(){
    ++id;
    cod  = id;
    rating_final = 0;
}
Computer::Computer(const Computer &c) {
    cod = c.cod;
    rating_final = c.rating_final;
    for(int i = 0;i< virusi.size(); ++i)
        delete virusi[i];
    virusi.clear();
    for(int i = 0;i < c.virusi.size(); ++i)
        addVirus(c.virusi[i]);
}
Computer & Computer::operator=(const Computer &c) {
    cod = c.cod;
    rating_final = c.rating_final;
    for(int i = 0;i< virusi.size(); ++i)
        delete virusi[i];
    virusi.clear();
    for(int i = 0;i < c.virusi.size(); ++i)
        addVirus(c.virusi[i]);
    return *this;
}
Computer::~Computer() {
    --id;
    cod = 0;
    rating_final = 0;
    for(int i = 0;i < virusi.size();++i)
        delete virusi[i];
    virusi.clear();
}

// clasa Meniu Interactiv => singleton
class MeniuInteractiv{
private:
    vector < Computer*> calculatoare;

    static MeniuInteractiv* instanta;
    MeniuInteractiv() = default;
    MeniuInteractiv(const MeniuInteractiv& m) = default;
    MeniuInteractiv(MeniuInteractiv& m) = default;
    MeniuInteractiv& operator=(const MeniuInteractiv& m) = default;
    MeniuInteractiv& operator=(MeniuInteractiv& ob) = default;

public:
    static MeniuInteractiv* getInstanta(){
        if(instanta == nullptr)
            instanta = new MeniuInteractiv();
        return instanta;
    }
    static void deleteInstanta(){
        if(instanta != nullptr)
            delete instanta;
        instanta = nullptr;
    }
    ~MeniuInteractiv(){
        for(int i = 0;i < calculatoare.size(); ++i)
            delete calculatoare[i];
        calculatoare.clear();
    }
    void demo();
    void afisCalculatoare();
    void afisCalculatoareRating();
    void afisPrimeleK();
    void afisProcent();

};
void MeniuInteractiv::afisProcent() {
    double p;
    int nr = 0;
    for(int i = 0;i < calculatoare.size();++i)
        if(calculatoare[i]->getRatingFinal() != 0)
            ++nr;
    if(calculatoare.size()) {
        p = 100.0 * ((double) nr) / ((double) calculatoare.size());
        cout << "Procent: " << p << '\n';
    }
    else
        cout << "Nu exista calculatoare\n";
}
void MeniuInteractiv::afisCalculatoareRating() {
    for(int i = 0;i < calculatoare.size(); ++i)
        for(int j = i+1;j < calculatoare.size(); ++j)
            if(calculatoare[i]->getRatingFinal() > calculatoare[j]->getRatingFinal())
                swap(calculatoare[i],calculatoare[j]);

    for(int i = 0;i < calculatoare.size(); ++i)
        cout << *calculatoare[i] << '\n';
    cout << '\n';
}
void MeniuInteractiv::afisPrimeleK() {
    int k;
    while(true){
        cout << "K este:\n";
        cin >> k;
        cin.get();
        if(k <= 0 )
            throw string("Nr invalid!");
        else
            break;;
    }
    for(int i = 0;i < calculatoare.size(); ++i)
        for(int j = i+1;j < calculatoare.size(); ++j)
            if(calculatoare[i]->getRatingFinal() > calculatoare[j]->getRatingFinal())
                swap(calculatoare[i],calculatoare[j]);
    for(int i = 0 ;i < k && i < calculatoare.size(); ++i)
        cout << *calculatoare[i] << '\n';
    cout << '\n';

}

void MeniuInteractiv::afisCalculatoare() {
    for(int i = 0;i < calculatoare.size(); ++i)
        cout << *calculatoare[i] << '\n';
    cout << '\n';
}

void MeniuInteractiv::demo() {
    cout << "demo\n";
}
MeniuInteractiv* MeniuInteractiv::instanta = nullptr;

int main() {
    int choice;
    MeniuInteractiv *m = m->getInstanta();
    while (true){
        cout << "0.Demo\n";
        cout << "1.Afis Calculatoare\n";
        cout << "2.Afis Calculatoare dupa Rating\n";
        cout << "3.Afis primele k calculatoare\n";
        cout << "4.Afis procent de calculatoare infectate\n";
        cout << "5.Inchide\n";

        try{
            cin >> choice;
            cin.get();
            if(choice < 0 || choice > 5)
                throw string("optiune gresita!");
            else{
                switch(choice){
                    case 0:
                        m->demo();
                    case 1:
                        m->afisCalculatoare();
                    case 2:
                        m->afisCalculatoareRating();
                    case 3:
                        m->afisPrimeleK();
                    case 4:
                        m->afisProcent();
                    case 5:
                        break;

                }
            }}
        catch (string s){
            cout << s << '\n';
        }
    }
    m->deleteInstanta();
    return 0;
}
