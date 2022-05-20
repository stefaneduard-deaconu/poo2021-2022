#include <bits/stdc++.h>

#include "util/IoBase.h"
#include "util/functions.h"

using namespace std;

vector<string> rootkitDamage = {"System Service Descriptor Table", "SSDT", "NtCreateFile"};
vector<string> keyloggerTastaDamage = { "[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
vector<string> keyloggerfctDamage = {"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};

struct Data{
    int zi, luna, an;
};

class malware: public IoBase{
protected:
    float rating_impact;
    Data data;
    string nume, metoda_infectare;
    vector<string> registri_modificati;
public:
    malware(){}

    malware(float ratingImpact, const Data &data, const string &nume, const string &metodaInfectare,
            const vector<string> &registriModificati) : rating_impact(ratingImpact), data(data), nume(nume),
                                                        metoda_infectare(metodaInfectare),
                                                        registri_modificati(registriModificati) {}

    istream &read(istream &is) override {
        cout<<"Rating impact: "; is>>rating_impact;
        cout<<"Zi: "; is>>data.zi;
        cout<<"Luna: "; is>>data.luna;
        cout<<"An: "; is>>data.an;
        cout<<"Nume: "; is>>nume;
        cout<<"Metoda de infectare: ";
        is>>metoda_infectare;
        int n;
        string registru;
        cout<<"n="; is>>n;
        for(int i=0; i<n; i++){
            cin>>registru;
            registri_modificati.push_back(registru);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        cout<<"Rating impact: "; os<<rating_impact<<endl;
        cout<<"Zi: "; os<<data.zi<<endl;
        cout<<"Luna: "; os<<data.luna<<endl;
        cout<<"An: "; os<<data.an<<endl;
        cout<<"Nume: "; os<<nume<<endl;
        cout<<"Metoda de infectare: "; os<<metoda_infectare<<endl;
        cout<<"Registri modificati:";
        for(auto x: registri_modificati)
            cout<<x<<endl;
        return os;
    }

    virtual int rating(){}
};

class rootkit: public virtual malware{
protected:
    vector<string> imports;
    vector<string> stringuri_semnificative;
public:
    rootkit(){}

    rootkit(float ratingImpact, const Data &data, const string &nume, const string &metodaInfectare,
            const vector<string> &registriModificati, const vector<string> &imports,
            const vector<string> &stringuriSemnificative) : malware(ratingImpact, data, nume, metodaInfectare,
                                                                    registriModificati), imports(imports),
                                                            stringuri_semnificative(stringuriSemnificative) {}

    istream &read(istream &is) override {
        malware::read(is);
        int n;
        string s;
        cout<<"Cate importuri: ";
        is>>n;
        for(int i=0; i<n; i++){
            is>>s;
            imports.push_back(s);
        }
        cout<<"Cate semnificative: "; is>>n;
        for(int i=0; i<n; i++){
            is>>s;
            stringuri_semnificative.push_back(s);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        malware::write(os);
        os<<"Importuri: ";
        for(auto x: imports)
            os<<x<<endl;
        os<<"Semnificative: ";
        for(auto x: stringuri_semnificative)
            os<<x<<endl;
        return os;
    }

    int rating() override{
        for(auto x: stringuri_semnificative)
            for(auto y: rootkitDamage){
                if (x == y)
                    rating_impact+=100;
            }
        for(auto x: imports)
            if(x=="ntoskrnl.exe")
                rating_impact*=2;

        return rating_impact;
    }
};

class keylogger: public virtual malware{
protected:
    vector<string> functii;
    vector<string> taste_speciale;
public:
    keylogger(){}

    keylogger(float ratingImpact, const Data &data, const string &nume, const string &metodaInfectare,
              const vector<string> &registriModificati, const vector<string> &functii,
              const vector<string> &tasteSpeciale) : malware(ratingImpact, data, nume, metodaInfectare,
                                                             registriModificati), functii(functii),
                                                     taste_speciale(tasteSpeciale) {}

    istream &read(istream &is) override {
        malware::read(is);
        int n;
        string s;
        cout<<"Cate functii: ";
        is>>n;
        for(int i=0; i<n; i++){
            is>>s;
            functii.push_back(s);
        }
        cout<<"Cate taste speciale: ";
        is>>n;
        for(int i=0; i<n; i++){
            is>>s;
            taste_speciale.push_back(s);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        malware::write(os);
        os<<"Functii: ";
        for(auto x: functii)
            os<<x<<endl;
        os<<"Taste speciale: ";
        for(auto x: taste_speciale)
            os<<x<<endl;
        return os;
    }

    int rating() override{
        for(auto x: taste_speciale)
            for(auto y: keyloggerTastaDamage){
                if (x == y)
                    rating_impact+=10;
            }
        for(auto x: functii)
            for(auto y: keyloggerfctDamage){
                if (x == y)
                    rating_impact+=30;
            }
        return rating_impact;
    }
};

class kernelKeylogger: public keylogger, public rootkit{
private:
    int fisiere, registre;
public:
    kernelKeylogger(){};

    istream &read(istream &is) override {
        rootkit::read(is);
        int n;
        string s;
        cout<<"Cate functii: "; is>>n;
        for(int i=0; i<n; i++){
            is>>s;
            functii.push_back(s);
        }
        cout<<"Cate taste speciale: ";
        is>>n;
        for(int i=0; i<n; i++){
            is>>s;
            taste_speciale.push_back(s);
        }
        cout<<"Ataca fisiere?";
//      Introducem de la tastatura cu 0 si 1
//      True = 1, False = 0
        is>>fisiere;
        cout<<"Ataca registre?";
        is>>registre;
        return is;
    }

    ostream &write(ostream &os) const override {
        rootkit::write(os);
        os<<"Functii: ";
        for(auto x: functii)
            os<<x<<endl;
        os<<"Taste speciale: ";
        for(auto x: taste_speciale)
            os<<x<<endl;
        os<<"Fisiere: "<<fisiere;
        os<<"Registre: "<<registre;
        return os;
    }

    int rating() override {
        for(auto x: stringuri_semnificative)
            for(auto y: rootkitDamage){
                if (x == y)
                    rating_impact+=100;
            }
        for(auto x: imports)
            if(x=="ntoskrnl.exe")
                rating_impact*=2;

        for(auto x: taste_speciale)
            for(auto y: keyloggerTastaDamage){
                if (x == y)
                    rating_impact+=10;
            }
        for(auto x: functii)
            for(auto y: keyloggerfctDamage){
                if (x == y)
                    rating_impact+=30;
            }
        if(fisiere==1)
            rating_impact+=20;
        if(registre==1)
            rating_impact+=20;
        return rating_impact;
    }
};

class ransomware: public malware{
private:
    int rating_criptare;
    float rating_obfuscare;
public:
    ransomware() {}

    ransomware(float ratingImpact, const Data &data, const string &nume, const string &metodaInfectare,
               const vector<string> &registriModificati, int ratingCriptare, float ratingObfuscare) : malware(
            ratingImpact, data, nume, metodaInfectare, registriModificati), rating_criptare(ratingCriptare),
                                                                                                      rating_obfuscare(
                                                                                                              ratingObfuscare) {}

    istream &read(istream &is) override {
        malware::read(is);
        cout<<"Ratingul de criptare";
        is>>rating_criptare;
        cout<<"Ratingul de obfuscare:";
        is>>rating_obfuscare;
        return is;
    }

    ostream &write(ostream &os) const override {
        malware::write(os);
        cout<<"Ratingul de criptare";
        os<<rating_criptare;
        cout<<"Ratingul de obfuscare:";
        os<<rating_obfuscare;
        return os;
    }

    int rating() override{
        rating_impact+=rating_criptare+rating_obfuscare;
    }
};

shared_ptr<malware> citire_malware(){
    int tip;
    cout<<endl<<"1. rootkit"<<endl<<"2. keylogger"<<endl<<"3. kernel-keylogger"<<endl<<"4. ransomware"<<endl;
    cin>>tip;
    shared_ptr<malware>m;
    if(tip==1){
        m = make_shared<rootkit>();
    } else if (tip==2){
        m = make_shared<keylogger>();
    } else if(tip==3){
        m = make_shared<kernelKeylogger>();
    } else if(tip==4){
        m = make_shared<ransomware>();
    }  else {
        cout << "Ai ales gresit!";
        return nullptr;
    }
    cin>>*m;
    return m;
}

int ratingF(vector<shared_ptr<malware>> m){
    int rating_final = 0;
    for(int i=0; i<m.size(); i++){
        rating_final += m[i]->rating();
    }
    return rating_final;
}

class computer:public IoBase{
private:
    vector<shared_ptr<malware>> lista_malware;
    float rating_final=0;
public:
    istream &read(istream &is) override {
        IoBase::read(is);
        int n;
        cout<<"Cate malware-uri: ";
        is>>n;
        for(int i=0; i<n; i++){
            lista_malware.push_back(citire_malware());
        }
        rating_final= ratingF(lista_malware);
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os<<"Malware: \n";
        for(int i=0; i<lista_malware.size(); i++)
            os<<*lista_malware[i]<<endl;
        cout<<"Ratingul final";
        os<<rating_final;
        return os;
    }

    vector<shared_ptr<malware>> getmalware(){
        return lista_malware;
    }

    void setmalware(vector<shared_ptr<malware>> a){
        lista_malware = a;
    }

};

shared_ptr<computer> citeste_computer(){
    shared_ptr<computer>c;
    c = make_shared<computer>();
    cin>>*c;
    return c;
}

class BaseMenu{
public:
    virtual void listOptions() {}
    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};

class SimpleMenu: public BaseMenu{
private:
    vector<shared_ptr<computer>> comp;
public:
    void listOptions() override{
        cout << "0. Citire informatii pentru n calculatoare." << '\n';
        cout << "1. Afisare informatiilor pentru fiecare calculator." << '\n';
        cout << "2. Afisarea informatiilor pentru fiecare calculator fiind ordonate dupa ratingul final." << '\n';
        cout << "3. Afisarea informatiilor primelor k calculatoare ordonate dupa ratingul final." << '\n';
        cout << "4. Afisarea procentului de computere infectate din firma." << '\n';
        cout << "5. Iesire." << '\n';
    }

    int chooseOption(int first, int last) override {
        int option = -1;
        while(option < first || option > last){
            cout << '\n';
            cout << "Pentru a rula comanda, alegeti un numar intre "
                 << first << " si " << last << '\n';
            listOptions();
            cout << "Alegere: ";
            cin >> option;
        }
        return option;
    }

    void option0() {
        int n;
        cout<<"Cate pc-uri: "; cin>>n;
        for(int i = 0; i<n; i++){
            comp.push_back(citeste_computer());
        }
    }

    void option1() {
        for(int i = 0; i<comp.size(); i++)
            cout<<*comp[i];
        }

    void option2() {
        for(int i=0; i<comp.size(); i++)
            for(int j=i+1; j<comp.size(); j++)
                if(comp[i]->getmalware() <comp[j]->getmalware())
                    swap(comp[i], comp[j]);
        for(auto x: comp){
            cout<<*x;
        }
    }

    void option3() {
        int k;
        cout<<"k= "; cin>>k;
        for(int i=0; i<comp.size(); i++)
            for(int j=i+1; j<comp.size(); j++)
                if(comp[i]->getmalware() < comp[j]->getmalware())
                    swap(comp[i], comp[j]);
        for(int i=0; i<k; i++)
            cout<<*comp[i];
    }

    void option4() {
        int ct=0;
        for(int i=0; i<comp.size(); i++)
            if(comp[i]->getmalware().size()!=0)
                ct++;
        cout<<ct/comp.size()*100;
    }

    void mainLoop() override {
        while(true){
            int option = chooseOption(0, 5);
            if(option == 0){
                option0();
            } else if (option == 1) {
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
             << "Programul s-a încheiat cu success";
    }
};

int main(){
    SimpleMenu menu;
    menu.mainLoop();
}