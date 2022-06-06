#include <iostream>
#include <vector>
#include <cstring>
#include <memory>
#include <bits/stdc++.h>
#include "util/functions.h"
#include "util/IoBase.h"

using namespace std;

bool ok = 1;

template<typename T>
istream &operator>>(istream &is, vector<T> &vec) {
    // empty vector:
    vec.clear();
    // read length:
    int n;
    cout << "n: ";
    cin >> n;
    // read items
    for (int i = 0; i < n; ++i) {
        T var;
        cin >> var;
        vec.push_back(var);
    }
    return is;
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &vec) {
    os << "[ ";
    for(auto& var : vec) {
        os << var << ' ';
    }
    os << ']';

    return os;
}



//Nafornita Valentin @ 143 Proiect 2

/*Prin malware înțelegem un software rău intenționat pentru care se reține ratingul impactului (număr real), data de infectare (zi, luna, an), numele acestuia (care poate să fie format din mai multe cuvinte), metoda de infectare (dacă se cunoaște, altfel se reține șirul “unknown”) și un vector cu registrii modificați (reținuți ca stringuri). */

struct date{
    int day, month, year;
};

class malware: public IoBase{
protected:
    double impact;
    date event;
    string name;
    string method;
    vector<string> registers;

public:
    malware(double impact = 0,date event = {0,0,0},string name = "unknown",string method = "unknown"){
        this->impact = impact;
        this->event = event;
        this->name = name;
        this->method = method;
    }
    malware(double impact, const date &event, const string &name, const string &method, const vector<string> &registers)
            : impact(impact), event(event), name(name), method(method), registers(registers) {
        for(auto i: registers){
            if (i  == "HKCU-run" || i =="HKLM-run")
                impact += 20;
        }
    }

    istream &read(istream &is) override{
        IoBase::read(is);
        cout<<"Impactul asupra calculatorului:";
        is>>impact;
        cout<<"-----------\n";
        cout<<"Data cand a avut loc infectarea(format EU, sep ENTER):";
        is>>event.day>>event.month>>event.year;
        cout<<"-----------\n";
        cout<<"Numele virusului:";
        is>>name;
        cout<<"-----------\n";
        cout<<"Metoda:";
        is>>method;
        cout<<"-----------\n";
        cout<<"Numar registri afectati: ";
        int n;
        string a;
        is>>n;
        cout<<"\n Input sep ENTER registers: ";
        for (int i = 0; i < n; i++){
            is>>a;
            if (a == "HKCU-run" || a =="HKLM-run")
                impact += 20;
            registers.push_back(a);
        }
        cout<<"-----------\n";
        return is;
    }


   virtual ostream &write(ostream &os) const override{
        IoBase::write(os);
        os << "Impact: " << impact << " event: " << event.day <<'/'<< event.month <<'/'<< event.year
           << " name: " << name << " method: " << method << " registers: " << registers;
        return os;
    }
//dempurpose
     double getImpact() {
        return impact;
    }
//dempurpose
    void setName(const string &name) {
        malware::name = name;
    }

    virtual ~malware() {
        registers.clear();
        name.clear();

    }
};

/*Prin rootkit înțelegem un tip de malware ce are drept scop obținerea drepturilor de administrator asupra dispozitivului infectat. Pentru rootkit se reține lista importurilor care poate fi unul și oricât de multe (importurile fac referire la numele fișierelor .dll folosite) și o listă de stringuri semnificative (anumite stringuri dintr-un binar pot fi un indice asupra faptului că fișierul este rău intenționat). */

class rootkit: public virtual malware{
protected:
    vector<string> imports;
    vector<string> significant;
public:
    rootkit() = default;
    rootkit(double impact, const date &event, const string &name, const string &method, const vector<string> &registers,
            const vector<string> &imports, const vector<string> &significant) : malware(impact, event, name, method,
                                                                                        registers), imports(imports),
                                                                                significant(significant) {
        for (auto i: significant){
            if (i == "System Service Descriptor Table" || i == "SSDT" || i == "NtCreateFile")
                impact += 100;
        }
        for (auto i: imports){
            if (i == "ntoskrnl.exe")
                impact *= 2;
        }
    }

    virtual ~rootkit() {
        imports.clear();
        significant.clear();
    }
    void calcimpact(){ for (auto i: significant){
            if (i == "System Service Descriptor Table" || i == "SSDT" || i == "NtCreateFile")
                impact += 100;
        }
        for (auto i: imports){
            if (i == "ntoskrnl.exe")
                impact *= 2;
        }}
    istream &read(istream &is){
        if(ok)malware::read(is);
        cout<<"Proceed to input the number of imports, followed by the imports themselves:";
        cin>>imports;
        cout<<"Proceed to input the number of significants, followed by the significants themselves:";
        cin>>significant;
        for (auto i: significant){
            if (i == "System Service Descriptor Table" || i == "SSDT" || i == "NtCreateFile")
                impact += 100;
        }
        for (auto i: imports){
            if (i == "ntoskrnl.exe")
                impact *= 2;
        }
        return is;
    }
    virtual ostream &write(ostream &os) const override{
        if(ok)malware::write(os);

        os<<imports;
        os<<significant;
        return os;
    }
    /*Pentru rootkit ratingul impactului crește cu 100 dacă se întâlnește unul din stringurile “System Service Descriptor Table”, “SSDT”, “NtCreateFile”. Dacă se regăsește importul “ntoskrnl.exe”, valoarea impactului se dublează (importurile se verifică după stringuri).*/

    double getimpact(){
        return impact;
    }

};

/*Prin keylogger înțelegem un malware care înregistrează acțiunile de la tastatură și le trimite mai departe. Pentru un keylogger se reține o listă cu funcțiile folosite și o listă cu tastele speciale definite. */
class keylogger: public virtual malware{
protected:


protected:
    vector<string> functions;
    vector<string> keys;
public:
    keylogger() = default;
    virtual ~keylogger() {
    functions.clear();
    keys.clear();
    }
    keylogger(double impact, const date &event, const string &name, const string &method,
              const vector<string> &registers, const vector<string> &functions, const vector<string> &keys) : malware(
            impact, event, name, method, registers), functions(functions), keys(keys) {
        for (auto i: functions){
            if (i == "CreateFileW" || i == "OpenProcess" || i == "ReadFile"|| i == "SetWindowsHookEx”"|| i == "RegisterHotKey"|| i == "WriteFile")
                impact += 30;
        }
        for (auto i: keys){
            if (i == "[PageDown]" || i == "[Left]" || i == "[UP]"|| i == "[Right]”"|| i == "[Down]"|| i == "[Num Lock]")
                impact += 10;
        }
    }

    istream &read(istream &is){
        if(ok)malware::read(is);
        cout<<"Proceed to input the number of functions, followed by the functions themselves:";
        cin>>functions;
        cout<<"Proceed to input the number of keys, followed by the keys themselves:";
        cin>>keys;
        for (auto i: functions){
            if (i == "CreateFileW" || i == "OpenProcess" || i == "ReadFile"|| i == "SetWindowsHookEx”"|| i == "RegisterHotKey"|| i == "WriteFile")
                impact += 30;
        }
        for (auto i: keys){
            if (i == "[PageDown]" || i == "[Left]" || i == "[UP]"|| i == "[Right]”"|| i == "[Down]"|| i == "[Num Lock]")
                impact += 10;
        }
        return is;
    }
    ostream &write(ostream &os) const override{
        if(ok)malware::write(os);

        os<<functions;
        os<<keys;
        return os;
    }

    void addfunction(){
        string a;
        cout<<"Type in your fucntion:\n";
        cin>>a;
        functions.push_back(a);
    }

   double getimpact() {
        return impact;
    }

};

/*Prin kernel-keylogger înțelegem un keylogger ce rulează în kernel-mode (de obicei prin intermediul unui rootkit). Prin urmare, putem considera că este are atât proprietățile unui rootkit cât și ale unui keylogger. În plus, dorim să memorăm dacă ascunde fișiere și registrii. */

class kernelkeylogger:  public rootkit,  public keylogger{
public:
    kernelkeylogger() = default;
    kernelkeylogger(double impact, const date &event, const string &name, const string &method,
                    const vector<string> &registers, const vector<string> &imports, const vector<string> &significant,
                    double impact1, const date &event1, const string &name1, const string &method1,
                    const vector<string> &registers1, const vector<string> &functions, const vector<string> &keys,
                    bool hidesFile, bool hidesRegister, double bigImpact) : rootkit(impact, event, name, method, registers,
                                                                                 imports, significant),
                                                                         keylogger(impact1, event1, name1, method1,
                                                                                   registers1, functions, keys),
                                                                         hides_file(hidesFile),
                                                                         hides_register(hidesRegister),
                                                                         big_impact(bigImpact) {
        if(hides_file)
            impact += 20;
        if(hides_register)
            impact += 30;
    }

    istream &read(istream& is) override{

        rootkit::read(is);

        ok = 0;
        keylogger::read(is);
        ok = 1;

        cout<<"Hides files/registers answ 1/0:\n";
        is>>hides_file>>hides_register;

        if(hides_register)
            impact+=30;
        if(hides_file)
            impact+=20;
        return is;
    }
    ostream &write(ostream& os) const override{
        os<<"Receipt################\n";
        rootkit::write(os);

        ok = 0;
        keylogger::write(os);
        ok = 1;

        os<<"\nAscunde fisiere-"<<hides_file<<"\nAscunde registri-"<<hides_register<<'\n';
        os<<"EndReceipt################\n";
        return os;
    }

double getimpact() {
    return impact;
    }

    virtual ~kernelkeylogger() {

    }

protected:
    bool hides_file, hides_register;
    double big_impact;
};
/*Prin ransomware înțelegem un malware care criptează fișiere de pe disk. Pentru
acesta se reține ratingul de criptare (un număr de la 1 la 10) și un rating de obfuscare (un
număr real ce reprezintă procentul de obfuscare (obfuscare = metodă de a
ascunde/îngreuna intenția inițială a codului)).*/

class ransomware: public malware{

private:
    int crypt_rating, obfusc;
public:
    ransomware(double impact, const date &event, const string &name, const string &method,
               const vector<string> &registers, int cryptRating, int obfusc) : malware(impact, event, name, method,
                                                                                       registers),
                                                                               crypt_rating(cryptRating),
                                                                               obfusc(obfusc) {
        impact += crypt_rating + obfusc;
    }
    ransomware() = default;

    virtual ~ransomware() {crypt_rating = obfusc = 0;}


    istream &read(istream &is)override{
        malware::read(is);
        cout<<"\ncrypt rating:";
        is>>crypt_rating;
        cout<<"\nobfuscation rating:";
        is>>obfusc;
        impact += crypt_rating+obfusc;
        return is;
    }
    ostream &write(ostream &os) const override{
        malware::write(os);
        os<<"\ncrypt:"<<crypt_rating<<"\nobfusc:"<<obfusc;
        return os;
    }
    double getImpact() {
        return impact;
    }
};

/*Pentru fiecare computer din firmă se reține un id unic, incrementat automat, o listă de
malware (poate conține un malware sau mai*/

class computer:public IoBase{
protected:
    string id;
    //static int no_order;
    vector<shared_ptr<malware>> virus;
    double hit_rating;

public:
    computer()= default;
    computer(const string &id, const vector<shared_ptr<malware>> &virus, double hitRating) : id(id), virus(virus),
                                                                                             hit_rating(hitRating) {
        //no_order++;
        for (auto i: virus){
            hit_rating += i->getImpact();
        }
    }
    istream &read(istream &is) override{
        int m;
        bool ok;
        cout<<"Input no of viruses: ";
        is>>m;
        for (int i = 0; i < m; i++){
            ok = true;
            string nume_vir;
            cout<<"Input one of the following: malware, rootkit, keylogger, kkeylogger, ransomware: ";
            is>>nume_vir;
            if(nume_vir == "malware"){
                malware x;
                is>>x;
                ok = 0;
                virus.push_back(make_shared<malware>(x));
                hit_rating += x.getImpact();
            }
            if(nume_vir == "rootkit"){
                rootkit x;
                is>>x;
                ok = 0;
                virus.push_back(make_shared<rootkit>(x));
                hit_rating += x.getImpact();
            }
            if(nume_vir == "keylogger"){
                keylogger x;
                is>>x;
                ok = 0;
                virus.push_back(make_shared<keylogger>(x));
                hit_rating += x.getImpact();
            }
            if(nume_vir == "kkeylogger"){
                kernelkeylogger x;
                is>>x;
                ok = 0;
                virus.push_back(make_shared<kernelkeylogger>(x));
                hit_rating += x.getImpact();
            }
            if(nume_vir == "ransomware"){
                ransomware x;
                is>>x;
                ok = 0;
                virus.push_back(make_shared<ransomware>(x));
                hit_rating += x.getImpact();
            }
            if (ok == true){
                i--;
                cout<<"Wrong type; try again:\n";
            }

        }

        return is;
    }
    ostream &write(ostream &os)const override{
        for (auto i: virus){
            os<<*i<<'\n';

        }
//os<<"\nPc "<<no_order<<" "<<id<<"th in array has a score of: "<<hit_rating<<'.';
        os<<"Pc "<<" "<<id<<"th in array has a score of: "<<hit_rating<<'.\n';
        return os;
    }

    double getimpact(){
        return hit_rating;
    }
};

class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};

class SimpleMenu: public BaseMenu{
protected:
    vector<computer> PCs;
public:
    SimpleMenu(const vector<computer> &pCs) : PCs(pCs) {}

    SimpleMenu() = default;

    void listOptions() override {
        cout << "Type 1 for listing all PC units data." << '\n';
        cout << "Type 2 for PC listing, sorted by final rating"<< '\n';
        cout << "Type 3 for k worst PCs.(asc)" << '\n';
        cout << "Type 4 for %infected." << '\n';
        cout << "Type 5 for exitting." << '\n';
    }
    int chooseOption(int first, int last) override{
        int option;
        listOptions();
        cout<<"Type "<<first<<'-'<<last<<'\n';
        cin>>option;
        return (option>=first && option<=last) ? option : -1;
    }

    void opt1(){
        for (auto i: PCs)
            cout<<i<<"\n";
    }
    void opt2(){
        /*unde note are subiect si grade
        sort(note.begin(), note.end(), [](Nota a, Nota b){return a.subject<b.subject;});*/
        sort(PCs.begin(), PCs.end(), [](computer a, computer b){return a.getimpact()<b.getimpact();});
        for (auto i: PCs)
            cout<<i<<'\n';
    }
    void opt3(){
        cout<<"TODO cut k elements 😁";
        opt2();
    }
    double opt4(){
        int m;
        cout<<"Amt of PCs infected in the company";
        return PCs.size() / m * 100;
    }
    void mainLoop() override{
        while (true){
            int opt = chooseOption(1,5);
            if (opt == 1)opt1();
            else if (opt == 2)opt2();
                else if(opt == 3) opt3();
                    else if(opt == 4) opt4();
                        else if(opt == 5) break;
                            else cout<<"\nTry again, your input is invalid\n";
        }
        cout<<"\nProcess has terminated.\n";
    }
};

int main() {
    vector<computer> flota_companie;
    cin>>flota_companie;

    SimpleMenu menu(flota_companie);
    menu.mainLoop();

    return 0;
}