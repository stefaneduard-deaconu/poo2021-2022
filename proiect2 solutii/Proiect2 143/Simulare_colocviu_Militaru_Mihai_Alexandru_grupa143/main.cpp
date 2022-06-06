#include <bits/stdc++.h>
#include "util/functions.h"
#include "util/IoBase.h"
using namespace std;

//Template.uri

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

//Final Template.uri

struct Data{
    int zi;
    int luna;
    int an;
};

class Malware:public IoBase{
protected:
    float rating;
    Data data_infectare;
    string nume;
    string metoda_infectare;
    vector <string> registrii_afectati;

public:
    Malware(){
        rating=0;
        metoda_infectare="unknown";
        data_infectare.zi=data_infectare.luna=data_infectare.an=0;
    }

    Malware(float rating, const Data &dataInfectare, const string &nume, const string &metodaInfectare,
            const vector<string> &registriiAfectati) : rating(rating), data_infectare(dataInfectare), nume(nume),
                                                       metoda_infectare(metodaInfectare),
                                                       registrii_afectati(registriiAfectati) {}


    istream &read(istream &is) override {
        IoBase::read(is);
        cout<<"Rating:";
        cin>>rating;
        cout<<"Data infectare:";
        cin>>data_infectare.zi>>data_infectare.luna>>data_infectare.an;
        cin.get();
        cout<<"Nume:";
        getline(cin, nume);
        cout<<"Metoda Infectare:";
        getline(cin, metoda_infectare);
        cout<<"Registrii:\n";
        cin>>registrii_afectati;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout<<"Rating: "<<rating<<"\n";
        cout<<"Data infectarii : "<<data_infectare.zi<<" "<<data_infectare.luna<<" "<<data_infectare.an<<"\n";
        cout<<"Nume virus: "<<nume<<"\n";
        cout<<"Registrii: "<<"\n"<<registrii_afectati<<"\n";
        cout<<"Metoda infectare:"<<metoda_infectare<<"\n";
        return os;
    }

    virtual void calc_rating(){
        rating =0;
        for(auto & i : registrii_afectati){
            if(i=="HKLM-run" or i=="HKCU-run"){
                rating+=20;
            }
        }
    }

    float getRating() const {
        return rating;
    }

};

class Rootkit:public virtual Malware{
protected:
    vector<string> importuri;
    vector<string> semnificativ_str;

public:
    Rootkit()=default;

    Rootkit(float rating, const Data &dataInfectare, const string &nume, const string &metodaInfectare,
            const vector<string> &registriiAfectati, const vector<string> &importuri,
            const vector<string> &semnificativStr) : Malware(rating, dataInfectare, nume, metodaInfectare,
                                                             registriiAfectati), importuri(importuri),
                                                     semnificativ_str(semnificativStr) {}

    istream &read(istream &is) override {
        Malware::read(is);
        cout<<"Importuri:\n";
        cin>>importuri;
        cout<<"String.uri semnificative:\n";
        cin>>semnificativ_str;
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        cout<<"\n";
        cout<<"Importuri: "<<importuri<<"\n";
        cout<<"String.uri semnificative: "<<semnificativ_str<<"\n";

    }

    void calc_rating() override {
        Malware::calc_rating();

        vector<string> semnificativ_str_bad ={"System Service Descriptor Table","SSDT","NtCreateFile"};
        vector<string> importuri_bad = {"ntoskrnl.exe"};
        for(auto &x:semnificativ_str)
            for(auto &y:semnificativ_str_bad){
                if(x==y){
                    rating+=100;
                    break;
                }
            }
        for(auto &x:importuri)
            for(auto &y:importuri_bad){
                if(x==y){
                    rating*=2;
                    break;
                }
            }

    }

};

class Keylogger:public virtual Malware {
protected:
    vector<string> functii;
    vector<string> taste_speciale;
public:
    Keylogger() = default;

    Keylogger(float rating, const Data &dataInfectare, const string &nume, const string &metodaInfectare,
              const vector<string> &registriiAfectati, const vector<string> &functii,
              const vector<string> &tasteSpeciale) : Malware(rating, dataInfectare, nume, metodaInfectare,
                                                             registriiAfectati), functii(functii),
                                                     taste_speciale(tasteSpeciale) {}


    istream &read(istream &is) override {
        Malware::read(is);
        cout<<"Functii:\n";
        cin>>functii;
        cout<<"Taste speciale:\n";
        cin>>taste_speciale;
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        cout<<"\n";
        cout<<"Functii: "<<functii<<"\n";
        cout<<"Taste speciale: "<<taste_speciale<<"\n";
        return os;
    }


    void calc_rating() override {
        rating=0;
        for(auto & i : registrii_afectati){
            if(i=="HKLM-run" or i=="HKCU-run"){
                rating+=20;
            }
        }

        vector <string> taste_speciale_bad ={"[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
        vector <string> functii_bad = {"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};
        for(auto &x:taste_speciale)
            for(auto &y:taste_speciale_bad){
                if(y == x) {
                    rating += 100;
                    break;
                }
            }

        for(auto &x:functii)
            for(auto &y:functii_bad){
                if(y == x) {
                    rating *=2;
                    break;
                }
            }
    }
};

class KernelKeylogger:public virtual Keylogger, public virtual Rootkit{
    int numar_fisiere;
    int numar_registrii;

public:
    KernelKeylogger()=default;

    KernelKeylogger(float rating, const Data &dataInfectare, const string &nume, const string &metodaInfectare,
                    const vector<string> &registriiAfectati, const vector<string> &functii,
                    const vector<string> &tasteSpeciale, float rating1, const Data &dataInfectare1, const string &nume1,
                    const string &metodaInfectare1, const vector<string> &registriiAfectati1,
                    const vector<string> &importuri, const vector<string> &semnificativStr, int numarFisiere,
                    int numarRegistrii) : Keylogger(rating, dataInfectare, nume, metodaInfectare, registriiAfectati,
                                                    functii, tasteSpeciale),
                                          Rootkit(rating1, dataInfectare1, nume1, metodaInfectare1, registriiAfectati1,
                                                  importuri, semnificativStr), numar_fisiere(numarFisiere),
                                          numar_registrii(numarRegistrii) {}
    ostream &write(ostream &os) const override {
        Malware::write(os);

        cout<<"\n";
        cout<<"Functii: "<<functii<<"\n";
        cout<<"Taste speciale: "<<taste_speciale<<"\n";

        cout<<"Importuri: "<<importuri<<"\n";
        cout<<"String.uri semnificative: "<<semnificativ_str<<"\n";

        cout<<"Numar fisiere: "<<numar_fisiere<<"\n";
        cout<<"Numar registrii "<<numar_registrii<<"\n";

        return os;
    }

    istream &read(istream &is) override {
        Malware::read(is);

        cout<<"Functii:\n";
        cin>>functii;
        cout<<"Taste speciale:\n";
        cin>>taste_speciale;

        cout<<"Importuri:\n";
        cin>>importuri;
        cout<<"String.uri semnificative:\n";
        cin>>semnificativ_str;

        cout<<"Numar fisiere: ";
        cin>>numar_fisiere;
        cout<<"Numar registrii: ";
        cin>>numar_registrii;
        return is;
    }

    void calc_rating() override {
        Keylogger::calc_rating();

        if(numar_fisiere)
            rating += 20;
        if(numar_registrii)
            rating += 30;
    }

};

class Ransomware : public virtual Malware{
protected:
    int rating_cript;
    float rating_ob;
public:
    Ransomware(){
        rating_cript=0;
        rating_ob=0;
    }

    Ransomware(float rating, const Data &dataInfectare, const string &nume, const string &metodaInfectare,
               const vector<string> &registriiAfectati, int ratingCript, float ratingOb) : Malware(rating,
                                                                                                   dataInfectare, nume,
                                                                                                   metodaInfectare,
                                                                                                   registriiAfectati),
                                                                                           rating_cript(ratingCript),
                                                                                           rating_ob(ratingOb) {}

    istream &read(istream &is) override {
        Malware::read(is);
        cout<<"Rating cript: ";
        cin>>rating_cript;
        cout<<"Rating obfuscare: ";
        cin>>rating_ob;
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        cout<<"Rating cript: "<<rating_cript<<"\n";
        cout<<"Rating obfuscare: "<<rating_ob<<"\n";
        return os;
    }

    void calc_rating() override {
        Malware::calc_rating();
        rating += rating_ob + rating_cript;
    }
};

class Computer: public IoBase{
private:
    int id_pc;
    static int id;
    vector<shared_ptr<Malware>> virusi;
    float rating_tot;

public:
    Computer(){
        id_pc=id++;
        rating_tot=0;
    }

    Computer(const vector<shared_ptr<Malware>> &virusi) : virusi(virusi) {
        id_pc=id++;
        for(int i=0;i,virusi.size();i++){
            float current_rating=virusi[i]->getRating();
            rating_tot+=current_rating;
        }
    }

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    float getRatingTot() const;

};

int Computer::id=0;

ostream &Computer::write(ostream &os) const {
    cout<<"ID computer: "<<id<<"\n";
    for(const auto & i : virusi){
        auto *asKeylogger = dynamic_cast<Keylogger *>(i.get());
        auto *asRootkit = dynamic_cast<Rootkit *>(i.get());
        auto *asKernelKeylogger = dynamic_cast<KernelKeylogger *>(i.get());
        auto *asRansomware = dynamic_cast<Ransomware *>(i.get());

        if(asKeylogger){
            cout<<*asKeylogger;
        }else if(asRootkit){
            cout<<*asRootkit;
        }else if(asKernelKeylogger){
            cout<<*asKernelKeylogger;
        }else if(asRansomware){
            cout<<*asRansomware;
        }
    }
    return os;
}

float Computer::getRatingTot() const {
    return rating_tot;
}


class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};

class SimpleMenu : public BaseMenu {
protected:
    vector<Computer>calc;
public:
    SimpleMenu()= default;

    explicit SimpleMenu(const vector<Computer> &calc) : calc(calc) {};

    void listOptions() override {
        cout << "1.Afisarea informatiilor calculatoare." << '\n';
        cout << "2.Afișarea informațiilor pentru fiecare calculator fiind ordonate după ratingul final."<< '\n';
        cout << "3.Afișarea primelor k calculatoare ordonate după ratingul final." << '\n';
        cout << "4.Afișarea procentului de computere infectate din firmă. " << '\n';
        cout << "5.Iesire." << '\n';
    }

    int chooseOption(int first, int last) override {
        int option = -1;
        while (option < first || option > last) {
            cout << '\n';
            cout << "Pentru a rula comanda, alegeti un numar intre " << first << " si " << last << '\n';
            listOptions();
            cout << "Alegere:";
            cin >> option;
        }
        return option;
    }

    void option1(){
        for(auto &x:calc){
            cout << x << "\n";
        }
    }
    void option2(){
        for(int i=0;i<calc.size()-1;i++){
            for(int j=i+1;j<calc.size();j++){
                float rating1=calc[i].getRatingTot();
                float rating2=calc[i].getRatingTot();
                if(rating1>rating2){
                    swap(calc[i], calc[j]);
                }
            }
        }
        for(auto &x:calc){
            cout << x << "\n";
        }

    }
    void option3() {
        cout<<"Inttrodu un numar k.\n";
        int k;
        cin>>k;
        for(int i=0;i<calc.size()-1;i++){
            for(int j=i+1;j<calc.size();j++){
                float rating1=calc[i].getRatingTot();
                float rating2=calc[i].getRatingTot();
                if(rating1>rating2){
                    swap(calc[i], calc[j]);
                }
            }
        }
        for(int i=0;i<k;i++){
            cout << calc[i] << "\n";
        }
    }

    void option4() {
        cout<<"Procentul final de calculatoare infectate este:\n";

    }

    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 5);
            if (option == 1) {
                option1();
            } else if (option == 2) {
                option2();
            } else if (option == 3) {
                option3();
            } else if (option == 4) {
                option4();
            }else if(option == 5){
                break;
            }
        }
        cout << '\n'<< "---------------------------------"<< '\n'<< "Programul s-a incheiat cu success";
    }

};

int main() {

//    Ransomware m;
//    cout<<m;
    return 0;
}
