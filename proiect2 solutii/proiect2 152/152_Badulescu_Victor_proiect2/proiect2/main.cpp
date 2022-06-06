#include <bits/stdc++.h>
#include "util/IOBase.h"
using namespace std;
struct data{
    int zi, luna, an;
};
class Malware : public IOBase{
protected:
    long long rating;
    data dataInfectare;
    string nume, metodaInfectare;
    vector<string>registriiAfectati;
public:
    Malware(const data &dataInfectare, const string &nume, const string &metodaInfectare,
            const vector<string> &registriiAfectati) : rating(0), dataInfectare(dataInfectare), nume(nume),
                                                       metodaInfectare(metodaInfectare),
                                                       registriiAfectati(registriiAfectati) {}
    
    Malware(): rating(0), metodaInfectare("unknown") {}

    istream &read(istream &is) override {
        IOBase::read(is);
        cout<<"<------------ Citirea datelor despre "<<tip()<<" ----------------------->\n";
        cout<<"Nume: ";
        is.get();
        getline(is, nume);
        cout<<"Data Infectare:\nZi: ";
        is >> dataInfectare.zi;
        cout<<"Luna: ";
        is >> dataInfectare.luna;
        cout<<"An: ";
        is >> dataInfectare.an;
        int x = -1;
        while(x!=1 && x!=0){
        cout<<"Se cunoaste metoda de infectare (1 = DA, 0 = NU): ";
            is>>x;
        }
        if(x) {
            cout << "Metoda de infectare: ";
            is >> metodaInfectare;
        }
        cout<<"Numar de registrii afectati: ";
        int n;
        is>>n;
        if(n>0) {
            cout << "Introduceti " << n << " registrii afectati: ";
            string registru;
            for (int i = 0; i < n; i++) {
                is >> registru;
                registriiAfectati.push_back(registru);
            }
        }
        return is;
    }
    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os<<"<------------ Afisarea datelor despre "<<tip()<<" ----------------------->\n";
        os << "Nume: ";
        os << nume<<'\n';
        os << "Rating infectare: ";
        os << rating<<'\n';
        os << "Data Infectare:\nZi: ";
        os << dataInfectare.zi<<'\n';
        os << "Luna: ";
        os << dataInfectare.luna<<'\n';
        os << "An: ";
        os << dataInfectare.an<<'\n';
        os << "Metoda de infectare: ";
        os << metodaInfectare<<'\n';
        if(!registriiAfectati.empty()) {
            os << "Registrii afectati:\n";
            for (auto x: registriiAfectati) {
                os << "->" << x << '\n';
            }
        }
        return os;
    }
    virtual string tip() const {return "Malware";}

    virtual void calcRating(){
        for(auto x : registriiAfectati)
            if(x == "HKLM-run" || x == "HKCU-run")
                rating+=20;
    }

    long long getRating(){
//        calcRating();
        return rating;
    }
};

class Rootkit : public virtual Malware{
protected:
    vector<string> importuri, stringuriSemnificative;
public:
    Rootkit(const data &dataInfectare, const string &nume, const string &metodaInfectare,
            const vector<string> &registriiAfectati, const vector<string> &importuri,
            const vector<string> &stringuriSemnificative) : Malware(dataInfectare, nume, metodaInfectare,
                                                                    registriiAfectati), importuri(importuri),
                                                            stringuriSemnificative(stringuriSemnificative){}

    Rootkit() {}

    istream &read(istream &is) override {
        Malware::read(is);
        cout<<"Numar de importuri: ";
        int n;
        is>>n;
        string import;
        if(n>0) {
            cout << "Scrieti " << n << " importuri: ";
            for (int i = 0; i < n; i++) {
                is >> import;
                importuri.push_back(import);
            }
        }
        cout<<"Numar de stringuri semnificative: ";
        is>>n;
        if(n>0) {
            cout << "Scrieti " << n << " stringuri semnificative (separate prin enter): \n";
            for (int i = 0; i < n; i++) {
                is.get();
                getline(is, import);
                stringuriSemnificative.push_back(import);
            }
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        if(!importuri.empty()) {
            os << "Importuri: \n";
            for (auto x: importuri) os << x << '\n';
        }
        if(!stringuriSemnificative.empty()) {
            os << "Stringuri semnificative: \n";
            for (auto x: stringuriSemnificative) os << x << '\n';
        }
        return os;
    }

    string tip() const override {
        return "Rootkit";
    }

    void calcRating() override {
        Malware::calcRating();
        for(auto x : stringuriSemnificative)
            if(x == "System Service Descriptor Table"
               || x == "SSDT"
               || x == "NtCreateFile")
                rating += 100;
        for(auto x : importuri)
            if(x == "ntoskrnl.exe") rating *= 2;
    }
};

class Keylogger : public virtual Malware{
protected:
    vector<string> functii, taste;
public:
    Keylogger(const data &dataInfectare, const string &nume, const string &metodaInfectare,
              const vector<string> &registriiAfectati, const vector<string> &functii, const vector<string> &taste)
            : Malware(dataInfectare, nume, metodaInfectare, registriiAfectati), functii(functii), taste(taste) {}

    Keylogger() {}

    istream &keyloggerRead(istream &is){
        cout<<"Numar de functii folosite: ";
        int n;
        is>>n;
        if(n>0) {
            cout << "Introduceti " << n << " functii: ";
            string functie;
            for (int i = 0; i < n; i++) {
                is >> functie;
                functii.push_back(functie);
            }
        }
        cout<<"Introduceti numarul de taste speciale: ";
        is>>n;
        if(n>0) {
            cout << "Introduceti " << n << " taste speciale (separate print enter): \n";
            string tasta;
//        is.ignore();
            for (int i = 0; i < n; i++) {
                is.get();
                getline(is, tasta);
                taste.push_back(tasta);
            }
        }
        return is;
    }

    ostream &keyloggerWrite(ostream &os) const {
        if(!functii.empty()) {
            os << "Functii folosite: \n";
            for (auto x: functii) os << x << '\n';
        }
        if(!taste.empty()) {
            os << "Taste speciale: \n";
            for (auto x: taste) os << x << '\n';
        }
        return os;
    }

    istream &read(istream &is) override {
        Malware::read(is);
        keyloggerRead(is);
        return is;
    }
    ostream &write(ostream &os) const override {
        Malware::write(os);
        keyloggerWrite(os);
        return os;
    }

    string tip() const override {
        return "Keylogger";
    }

    int keyloggerRating(){
        int rt = 0;
        for(auto x : taste)
            if(
                    x =="[Up]" || x == "[Down]" || x == "[Left]" || x == "[Right]" ||
                    x == "[Num Lock]" || x == "[PageDown]" || x == "[UP]"
                    )
                rt += 10;
        for(auto x : functii)
            if(
                    x == "CreateFileW" || x == "OpenProcess" || x == "ReadFile" ||
                    x == "WriteFile" || x == "RegisterHotKey" || x == "SetWindowsHookEx"
                    )
                rt += 30;
        return rt;
    }

    void calcRating() override {
        Malware::calcRating();
        rating  += keyloggerRating();
    }
};

class KernelKeylogger : public Keylogger, public Rootkit{
private:
    bool fisiere, registrii;
public:
    KernelKeylogger(const data &dataInfectare, const string &nume, const string &metodaInfectare,
                    const vector<string> &registriiAfectati, const vector<string> &functii, const vector<string> &taste,
                    const data &dataInfectare1, const string &nume1, const string &metodaInfectare1,
                    const vector<string> &registriiAfectati1, const vector<string> &importuri,
                    const vector<string> &stringuriSemnificative, bool fisiere, bool registrii) : Keylogger(
            dataInfectare, nume, metodaInfectare, registriiAfectati, functii, taste), Rootkit(dataInfectare1, nume1,
                                                                                              metodaInfectare1,
                                                                                              registriiAfectati1,
                                                                                              importuri,
                                                                                              stringuriSemnificative),
                                                                                                  fisiere(fisiere),
                                                                                                  registrii(
                                                                                                          registrii) {}

    KernelKeylogger(): fisiere(0), registrii(0) {}

    istream &read(istream &is)  {
        Rootkit::read(is);
        keyloggerRead(is);
        int nr = -1;
        while(nr!=1 && nr!=0) {
            cout << "Ascunde fisiere? (1 = DA, 0 = NU): ";
            is >> nr;
        }
        fisiere = nr;
        nr = -1;
        while(nr!=1 && nr!=0) {
            cout << "Ascunde registrii? (1 = DA, 0 = NU): ";
            is >> nr;
        }
        registrii = nr;
        return is;
    }

    ostream &write(ostream &os) const override {
        Rootkit::write(os);
        keyloggerWrite(os);
        os<<"Ascunde fisiere: "<<fisiere;
        os<<"\nAscunde registrii: "<<registrii<<'\n';
        return os;
    }

    string tip() const override {
        return "Kernel keylogger";
    }

    void calcRating() override {
        Rootkit::calcRating();
        rating += keyloggerRating();
        if(fisiere) rating += 20;
        if(registrii) rating += 30;
    }
};

class RansomWware : public Malware{
private:
    double criptare, obfuscare;
public:
    RansomWware(const data &dataInfectare, const string &nume, const string &metodaInfectare,
                const vector<string> &registriiAfectati, double criptare, double obfuscare) : Malware(dataInfectare,
                                                                                                      nume,
                                                                                                      metodaInfectare,
                                                                                                      registriiAfectati),
                                                                                              criptare(criptare),
                                                                                              obfuscare(obfuscare) {}

    RansomWware() {}

    istream &read(istream &is) override {
        Malware::read(is);
        cout<<"Rating de criptare: ";
        is>>criptare;
        cout<<"Rating de obfuscare: ";
        is>>obfuscare;
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        os<<"Rating de criptare: "<<criptare<<'\n';
        os<<"Rating de obfuscare: "<<obfuscare<<'\n';
        return os;
    }

    string tip() const override {
        return "Ransomware";
    }

    void calcRating() override {
        Malware::calcRating();
        rating += (criptare + obfuscare);
    }

};



class Computer:public IOBase{
private:
    int id;
    static int idCurent;
    static vector<shared_ptr<Malware>> possibleMalwares;
    long long rating = 0;
    vector<shared_ptr<Malware>> virusi;
public:
    Computer(const vector<shared_ptr<Malware>> &virusi) : id(idCurent++), virusi(virusi) {calcRating();}

    Computer(): id(idCurent++) {calcRating();}



    istream &read(istream &is) override {
        IOBase::read(is);
        cout<<"<----------Citire pentru calculatorul "<<id<<"--------------->\n";
        int n = -1;
        while(n<=0) {
            cout << "Numar de malwares: ";
            is >> n;
        }
//        for(int i=0;i<n;i++){
//            int m = -1;
//            while(m<1 || m>possibleMalwares.size()){
//                cout<<"Introduceti numarul corespunzator tipului curent de malware:\n";
//                int j=1;
//                for(const auto& x : possibleMalwares){
//                    cout<<j++<<". "<<x->tip()<<'\n';
//                }
//                is>>m;
//            }
//            shared_ptr<Malware> currentMalwarePtr = possibleMalwares[m-1];
//            auto currentMalware = *currentMalwarePtr;
//            is>>currentMalware;
//            currentMalware.calcRating();
//            currentMalwarePtr = &currentMalware;
//            virusi.push_back(currentMalwarePtr);
//        }


        for(int i=0;i<n;i++) {
            int m = -1;
            while (m < 1 || m > possibleMalwares.size()) {
                cout << "Introduceti numarul corespunzator tipului curent de malware:\n";
                int j = 1;
                for (const auto &x: possibleMalwares) {
                    cout << j++ << ". " << x->tip() << '\n';
                }
                is >> m;
            }
            shared_ptr<Malware> malwareptr;
            switch (m) {
                case 1:  malwareptr = make_shared<Rootkit>(Rootkit()); break;
                case 2:  malwareptr = make_shared<Keylogger>(Keylogger()); break;
                case 3:  malwareptr = make_shared<KernelKeylogger>(KernelKeylogger()); break;
                case 4:  malwareptr = make_shared<RansomWware>(RansomWware()); break;
                default: cout<<"CEVA A MERS PROST LA ALEGEREA MALWAREULUI\n"; m=0;
            }
            if(m){
                is>>*malwareptr;
                malwareptr->calcRating();
                virusi.push_back(malwareptr);
            }
        }
        return is;
    }
    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os<<"<----------Afisare pentru calculatorul "<<id<<"--------------->\n";
        os<<"Ratingul total al infectarii este "<<rating<<'\n';
        os<<"Virusi prezenti: \n";
        for(const auto &x : virusi)
            os<<*x;
        return os;
    }
    void setRating(long long rating) {
        this->rating = rating;
    }

    void calcRating(){
        for (auto x : virusi) rating += x->getRating();
    }

    long long getRating(){return rating;}

};



class BaseMenu{
public:
    virtual void listOptions() = 0;
    virtual int getOption(int first, int last) = 0;
    virtual void mainLoop(vector<Computer> calculatoare) = 0;
};

class AfisareInfoMenu : BaseMenu{
public:
    void listOptions() override {
        cout<<"1. Afisarea informatiilor despre fiecare calculator.\n";
        cout<<"2. Afisarea informatiilor despre fiecare calculator in functie de ratingul final.\n";
        cout<<"3. Afisarea informatiilor despre primele k calculatoare ordonate dupa ratingul final.\n";
        cout<<"4. Afisarea procentului calculatoarelor infectate.\n";
        cout<<"5. Inchide.\n";
    }

    int getOption(int first, int last) override {
        int opt = -1;
        while(opt < first || opt > last){
            cout<<"\nAlegeti una dintre urmatoarele optiuni prin introducerea numarului corespunzator: \n";
            listOptions();
            cin>>opt;
        }
        return opt;
    }
    void static afisare(int k,vector<Computer> &calculatoare){
        if(!k) k = calculatoare.size();
        for(auto x : calculatoare){
            cout<<x<<"\n";
            k--;
            if(!k) break;
        }
    }
    vector<Computer> static sortare(vector<Computer> &calculatoare){
        vector<pair<long long, Computer>> sortedCalc;
        for(auto x: calculatoare) {
            pair<long long, Computer> p;
            p.first = x.getRating();
            p.second = x;
            sortedCalc.push_back(p);
        }
        sort(sortedCalc.begin(), sortedCalc.end(), [](auto& a,auto & b){ return a.first>b.first;});
        vector<Computer>sortedCalc2;
        for(auto x : sortedCalc) sortedCalc2.push_back(x.second);
        return sortedCalc2;
    }



    void static op1(vector<Computer> calculatoare){
        afisare(0,calculatoare);
    }
    void static op2(vector<Computer>calculatoare){
        calculatoare = sortare(calculatoare);
        afisare(0,calculatoare);
    }
    void static op3(vector<Computer>calculatoare){
        int k = -1;
        while(k<1){
            cout<<"Introduceti numarul de calculatoare pentru afisare: ";
            cin>>k;
        }
        calculatoare = sortare(calculatoare);
        afisare(k, calculatoare);
    }
    void static op4(vector<Computer> calculatoare) {
        double nrCalc = 0;
        for(auto x : calculatoare) if(x.getRating()) nrCalc++;
        cout<<"Procentul de calculatoare infectate este: "<<(double) nrCalc / calculatoare.size() * 100<<"%\n";
    }

    vector<void (*)(vector<Computer>)> optiuni = {op1, op2, op3, op4};

    void mainLoop(vector<Computer> calculatoare) override {
        int opt;
        while(true){
            opt = getOption(1, 5);
            if(opt == 5) break;
            optiuni[opt-1](calculatoare);
        }
    }
};

vector<shared_ptr<Malware>> Computer::possibleMalwares = {
        make_shared<Rootkit>(Rootkit()),
        make_shared<Keylogger>(Keylogger()),
        make_shared<KernelKeylogger>(KernelKeylogger()),
        make_shared<RansomWware>(RansomWware())
};
int Computer::idCurent = 1;

int main() {

//    Malware mal;
//    cin>>mal;
//    cout<<mal;
//    Rootkit rt;
//    cin>>rt;
//    cout<<rt;
//    Keylogger keylogger;
//    cin>>keylogger;
//    cout<<keylogger;
//    KernelKeylogger kernelKeylogger;
//    cin>>kernelKeylogger;
//    cout<<kernelKeylogger;
//    RansomWware ransomWware;
//    cin>>ransomWware;
//    cout<<ransomWware;
//    cout<<ransomWware.getRating();


    vector<Computer> calculatoare;
    int n;
    cout<<"Numar de calculatoare: ";
    cin>>n;

    for(int i=0;i<n;i++) {
        Computer computer;
        cin>>computer;
        computer.calcRating();
        calculatoare.push_back(computer);
    }

    AfisareInfoMenu meniu;
    meniu.mainLoop(calculatoare);








//    for(auto x : calculatoare) cout<<x<<'\n';

//    vector<void (*)(int)> vect = {op1, op2, op3, op4};
//    vect[3](3);
    return 0;
}
