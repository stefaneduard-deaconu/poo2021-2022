#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include "IoBase.h"
#include "functions.h"
using namespace std;

vector <string> RootkitImpactFound = {"System Service Descriptor Table", "SSDT", "NtCreateFile"};
vector <string> KeyloggerStringFound = {"[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
vector<string>  KeyloggerFunctionFound = {"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};
class Malware : public IoBase{
protected:
    int rating,an,luna,zi;
    string name,method;
    vector <string> registers;
public:
    Malware(){}

    Malware(int rating, int an, int luna, int zi, const string &name, const string &method,
            const vector<string> &registers) : rating(rating), an(an), luna(luna), zi(zi), name(name), method(method),
                                               registers(registers) {}

    istream &read(istream &is) override {
        cout << "Introduceti rating: ";
        is >> rating;
        cout << "Introduceti zi: ";
        is >> zi;
        cout << "Introduceti luna: ";
        is >> luna;
        cout << "Introduceti an: ";
        is >> an;
        cout << "Introduceti nume: ";
        is >> name;
        cout << "Introduceti metoda de infectare: ";
        is >> method;
        int x;
        string registru;
        cout << "Introduceti nr registri modificati: ";
        is >> x;
        for ( int i=0; i<x ; i++) {
            cin >> registru;
            if(registru == "HKML-run" || registru == "HKCU-run")
                rating = rating + 20;
            registers.push_back(registru);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        cout << "Nume: ";
        os << name << endl;
        cout << "Rating impact: ";
        os << rating << endl;
        cout << "Zi: ";
        os << zi << endl;
        cout << "Luna: ";
        os << luna << endl;
        cout << "An: ";
        os << an << endl;
        cout << "Metoda de infectare: ";
        os << method << endl;
        cout << "Registri modificati: \n";
        for (auto registru : registers)
            cout << registru << endl;
    }
    virtual int calculate(){}
};

class Rootkit : public virtual Malware{
protected:
    vector <string> imports;
    vector <string> strings;
public:
    Rootkit(){}

    Rootkit(int rating, int an, int luna, int zi, const string &name, const string &method,
            const vector<string> &registers, const vector<string> &imports, const vector<string> &strings) : Malware(
            rating, an, luna, zi, name, method, registers), imports(imports), strings(strings) {}

    istream &read (istream &is) override {
        Malware::read(is);
        int numar;
        string string;
        cout << "Numar importuri: ";
        is >> numar;
        for(int i=0; i<numar; i++){
            is >> string;
            imports.push_back(string);
        }

        cout << "Numar stringuri semnificative: ";
        is >> numar;
        for (int j=0; j<numar; j++){
            is >> string;
            strings.push_back(string);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        os << "Importuri: ";
        for(auto importuri: imports)
            os << importuri << endl;
        os << "Stringuri semnificative: ";
        for(auto string : strings)
            os << string <<endl;
        return os;
    }

    int calculate() override{
        for(auto element: strings)
            for(auto item: RootkitImpactFound)
                if(element == item)
                    rating = rating + 100;
        for(auto element: imports)
            if(element == "ntoskrnl.exe")
                rating = rating * 2;
        return rating;
    }

};

class Keylogger : public virtual Malware {
protected:
    vector <string> functions;
    vector <string> keys;
public:
    Keylogger(){}

    Keylogger(int rating, int an, int luna, int zi, const string &name, const string &method,
              const vector<string> &registers, const vector<string> &functions, const vector<string> &keys) : Malware(
            rating, an, luna, zi, name, method, registers), functions(functions), keys(keys) {}

//    Keylogger(int xrating, int xan, int xluna, int xzi, const string &name, const string &xmethod,
//              const vector<string> &xregisters, const vector<string> &functions, vector<string> &keys) : Malware(xrating, xan, xluna, xzi,
//                                                                                                                 name, xmethod, xregisters),
//                                                                                                         functions(functions), keys(keys) {}

    istream &read (istream &is) override {
        Malware::read(is);
        int n;
        string s;
        cout << "Numar functii: ";
        is >> n;
        for(int i=0 ; i<n; i++){
            is >> s;
            functions.push_back(s);
        }

        cout << "Numar taste speciale: ";
        is >> n;
        for (int j=0; j<n; j++){
            is >> s;
            keys.push_back(s);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        os << "Functii: ";
        for(auto f: functions)
            os << f << endl;
        os << "Taste speciale: ";
        for(auto k : keys)
            os << k <<endl;
        return os;
    }
    int calculate() override{
        for(auto key: keys)
            for(auto item: KeyloggerStringFound)
                if(key == item)
                    rating = rating + 10;
        for(auto f: functions)
            for(auto item: KeyloggerFunctionFound)
                if(f == item)
                    rating = rating + 30;
        return rating;}

    };

class Kernel_Keylogger : public Rootkit, public Keylogger{
private:
    int registers;
    int folders;
public:
    Kernel_Keylogger(){};

    Kernel_Keylogger(int rating, int an, int luna, int zi, const string &name, const string &method,
                     const vector<string> &registers, const vector<string> &imports, const vector<string> &strings,
                     int rating1, int an1, int luna1, int zi1, const string &name1, const string &method1,
                     const vector<string> &registers1, const vector<string> &functions, const vector<string> &keys,
                     int registers2, int folders) : Rootkit(rating, an, luna, zi, name, method, registers, imports,
                                                            strings),
                                                    Keylogger(rating1, an1, luna1, zi1, name1, method1, registers1,
                                                              functions, keys), registers(registers2),
                                                    folders(folders) {}

    istream &read(istream &is) override {
        Rootkit::read(is);
        int n;
        string s;
        cout << "Numar functii: ";
        is >> n;
        for( int i=0; i<n ; i++){
            is >> s;
            functions.push_back(s);
        }
        cout << "Numar taste speciale: ";
        is >> n;
        for (int j=0; j<n; j++){
            is >> s;
            keys.push_back(s);
        }

        cout << "Folders Attack => 0 - False, 1 - True";
        is >> folders;
        cout << "Registers Attack => 0 - False, 1 - True";
        is >> registers;
        return is;
    }

    ostream &write(ostream &os) const override {
        Rootkit::write(os);
        os <<"Functii: ";
        for(auto x: functions)
            os << x << endl;
        os<<"Taste speciale: ";
        for(auto x: keys)
            os << x << endl;
        os<<"Fisiere: "<< folders;
        os<<"Registre: "<< registers;
        return os;
    }

    int calculate() override {
        for(auto element: strings)
            for(auto item: RootkitImpactFound)
                if(element == item)
                    rating = rating + 100;
        for(auto element: imports)
            if(element == "ntoskrnl.exe")
                rating = rating * 2;
        for(auto key: keys)
            for(auto item: KeyloggerStringFound)
                if(key == item)
                    rating = rating + 10;
        for(auto f: functions)
            for(auto item: KeyloggerFunctionFound)
                if(f == item)
                    rating = rating + 30;
        if(folders == 1)
            rating = rating + 20;
        if(registers == 1)
            rating = rating + 20;
        return rating;
    }

};

class Ransomware : public Malware{
private:
    int cryptoRating;
    float hidingRating;
public:
    Ransomware(){};

    Ransomware(int rating, int an, int luna, int zi, const string &name, const string &method,
               const vector<string> &registers, int cryptoRating, float hidingRating) : Malware(rating, an, luna, zi,
                                                                                                name, method,
                                                                                                registers),
                                                                                        cryptoRating(cryptoRating),
                                                                                        hidingRating(hidingRating) {}

    istream &read(istream &is) override {
        Malware::read(is);
        cout << "Introduceti ratingul de criptare: ";
        is >> cryptoRating;
        cout << "Introduceti ratingul de obfuscare: ";
        is >> hidingRating;
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        cout << "Ratingul de criptare: ";
        os << cryptoRating;
        cout << "Ratingul de obfuscare: ";
        os << hidingRating;
        return os;
    }
    int calculate(){
        rating = rating + cryptoRating + hidingRating;
    }
};

shared_ptr<Malware> citireMW(){
    int tip;
    cout<<"1. rootkit\n2. keylogger\n3.kernel-keylogger\n4.ransomware";
    cin>>tip;
    shared_ptr<Malware>m;
    if(tip==1){
        m = make_shared<Rootkit>();
    } else if (tip==2){
        m = make_shared<Keylogger>();
    } else if(tip==3){
        m = make_shared<Kernel_Keylogger>();
    } else if(tip==4){
        m = make_shared<Ransomware>();
    }  else {
        cout << "Malware not found! ";
        return nullptr;
    }
    cin >> *m;
    return m;
}

calculateFinalRating(vector<shared_ptr<Malware>>malwares){
    int fRating = 0;
    for(int i=0; i<malwares.size(); i++)
        fRating = fRating + malwares[i]->calculate();
    return fRating;
}

class computer: public IoBase{
private:
    vector <shared_ptr<Malware> > malwares;
    int finalRating = 0;
public:
    istream &read(istream &is) override {
        int n;
        cout<<"Nr malwares: ";
        is>>n;
        for(int i=0; i<n; i++)
            malwares.push_back(citireMW());
        finalRating = calculateFinalRating(malwares);
        return is;
    }

    ostream &write(ostream &os) const override {
        os<<"Malware: ";
        for(int i=0; i < malwares.size(); i++)
            os<<*malwares[i]<<endl;
        os << "Rating final: " << endl;
        os << finalRating;
        return os;
    }
    vector<shared_ptr<Malware>> getMalwares(){
        return malwares;
    }

    void setMalwares(const vector<shared_ptr<Malware>> &malwares) {
        computer::malwares = malwares;
    } };

    shared_ptr<computer> readComputer(){
        shared_ptr<computer> pc;
        pc = make_shared<computer>();
        cin >> *pc;
        return pc;
    }

class Menu{
private:
    vector <shared_ptr<computer>> pc;
public:
    void showOptions(){
        cout << "Choose your option: ";
        cout << "1. Citire n calculatoare + Afisare" << endl;
        cout << "2. Afisare calculatoare" << endl;
        cout << "3. Afisare informatii PC-uri sortate dupa rating" << endl;
        cout << "4. Afisare primele k PC-uri sortate dupa rating" << endl;
        cout << "5. Afisare procent calculatoare infectate" << endl;
    }
    void run(){
        showOptions();
        int option;
        cin >> option;
        while ( 0<option && option<6) {
            if(option == 1)
                citirePC();
            else if(option == 2)
                afisarePC();
            else if(option == 3)
                afisareSortare();
            else if(option == 4)
                afisarePrimeleK();
            else if(option == 5)
                afisareProcent();
            else {
                cout << "Programul s-a incheiat cu succes !" ;
                break;
            }
            showOptions();
            cin >> option;
        } }
        void citirePC(){
            int n;
            cout << "Total numar PC-uri: " ;
            cin >> n;
            for(int i=0; i<n; i++)
                pc.push_back(readComputer());
        }
        void afisarePC(){
            for(int i=0; i<pc.size(); i++)
                cout<< *pc[i];
        }
        void afisareSortare(){
            for(int i=0; i<pc.size(); i++)
                for(int j=i+1; j<pc.size(); j++)
                    if(pc[i]->getMalwares() < pc[j]->getMalwares())
                        swap(pc[i], pc[j]);
            for(auto cmp: pc)
                cout<<*cmp;
    }
        void afisarePrimeleK(){
            int k;
            cout << "k=?";
            cin >> k;
            for(int i=0; i<pc.size(); i++)
                for(int j=i+1; j<pc.size(); j++)
                    if(pc[i]->getMalwares() < pc[j]->getMalwares())
                        swap(pc[i], pc[j]);
            for(int i=0; i<k; i++)
                cout << *pc[i];
    }
        void afisareProcent(){
            int counter = 0;
            for(int i=0; i<pc.size(); i++)
                if(pc[i]->getMalwares().size() != 0)
                    counter++;
            cout << "Procentul este de " << counter/pc.size()*100 <<"%";
    }
};


int main() {
    Menu meniu;
    meniu.run();
    return 0;

}


