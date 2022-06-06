#include <bits/stdc++.h>

#include "util/IoBase.h"
#include "util/functions.h"

using namespace std;

vector<string> rootkitDamage = {"System Service Descriptor Table", "SSDT", "NtCreateFile"};
vector<string> keyloggerTastaDamage = { "[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
vector<string> keyloggerfctDamage = {"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};


class malware: public IoBase{
protected:
    int rating_impact, zi, luna, an;
    string nume, metoda_infectare;
    vector<string> registri_modificati;
public:
    malware(){}
    malware(int ratingImpact, int zi, int luna, int an, const string &nume, const string &metodaInfectare,
            const vector<string> &registriModificati) : rating_impact(ratingImpact), zi(zi), luna(luna), an(an),
                                                        nume(nume), metoda_infectare(metodaInfectare),
                                                        registri_modificati(registriModificati) {}

    istream &read(istream &is) override {
        cout<<"Rating impact: "; is>>rating_impact;
        cout<<"Zi: "; is>>zi;
        cout<<"Luna: "; is>>luna;
        cout<<"An: "; is>>an;
        cout<<"Nume: "; is>>nume;
        cout<<"Metoda de infectare: "; is>>metoda_infectare;
        int n; string registru;
        cout<<"n="; is>>n;
        for(int i=0; i<n; i++){
            cin>>registru;
            if(registru == "HKML-run")
                rating_impact+=20;
            registri_modificati.push_back(registru);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        cout<<"Zi: "; os<<zi<<endl;
        cout<<"Luna: "; os<<luna<<endl;
        cout<<"An: "; os<<an<<endl;
        cout<<"Nume: "; os<<nume<<endl;
        cout<<"Metoda de infectare: "; os<<metoda_infectare<<endl;
        cout<<"Registri modificati: ";
        for(auto x: registri_modificati)
            cout<<x<<' ';
        os<<endl;
    }
    virtual int calc_rating(){}
};

class rootkit: public virtual malware{
protected:
    vector<string> imports;
    vector<string> semnificative;
public:
    rootkit(){}
    rootkit(int ratingImpact, int zi, int luna, int an, const string &nume, const string &metodaInfectare,
            const vector<string> &registriModificati, const vector<string> &imports,
            const vector<string> &semnificative) : malware(ratingImpact, zi, luna, an, nume, metodaInfectare,
                                                           registriModificati), imports(imports),
                                                   semnificative(semnificative) {}

    istream &read(istream &is) override {
        malware::read(is);
        int n;
        string s;
        cout<<"Cate semnificative: "; is>>n;
        for(int i=0; i<n; i++){
            is>>s;
            semnificative.push_back(s);
        }
        cout<<"Cate importuri: "; is>>n;
        for(int i=0; i<n; i++){
            is>>s;
            imports.push_back(s);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        malware::write(os);
        os<<"Importuri: ";
        for(auto x: imports)
            os<<x<<' ';
        os<<endl<<"Semnificative: ";
        for(auto x: semnificative)
            os<<x<<' ';
        os<<endl;
        return os;
    }

    int calc_rating() override{
        for(auto x: semnificative)
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
    keylogger(int ratingImpact, int zi, int luna, int an, const string &nume, const string &metodaInfectare,
              const vector<string> &registriModificati, const vector<string> &functii,
              const vector<string> &tasteSpeciale) : malware(ratingImpact, zi, luna, an, nume, metodaInfectare,
                                                             registriModificati), functii(functii),
                                                     taste_speciale(tasteSpeciale) {}

    istream &read(istream &is) override {
        malware::read(is);
        int n;
        string s;
        cout<<"Cate functii: "; is>>n;
        for(int i=0; i<n; i++){
            is>>s;
            functii.push_back(s);
        }
        cout<<"Cate taste speciale: "; is>>n;
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
            os<<x<<' ';
        os<<endl<<"Taste speciale: ";
        for(auto x: taste_speciale)
            os<<x<<' ';
        os<<endl;
        return os;
    }

    int calc_rating() override{
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
        cout<<"Cate taste speciale: "; is>>n;
        for(int i=0; i<n; i++){
            is>>s;
            taste_speciale.push_back(s);
        }
        cout<<"Ataca fisiere? 0-nu    1-da";
        is>>fisiere;
        cout<<"Ataca registre? 0-nu    1-da";
        is>>registre;
        return is;
    }

    ostream &write(ostream &os) const override {
        rootkit::write(os);
        os<<"Functii: ";
        for(auto x: functii)
            os<<x<<' ';
        os<<endl<<"Taste speciale: ";
        for(auto x: taste_speciale)
            os<<x<<' ';
        os<<endl<<"Fisiere: "<<fisiere<<endl;
        os<<"Registre: "<<registre;
        return os;
    }

    int calc_rating() override {
        for(auto x: semnificative)
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
    int rating;
    float obfuscare;
public:
    istream &read(istream &is) override {
        malware::read(is);
        cout<<"Rating: "; is>>rating;
        cout<<"Obfuscare: "; is>>obfuscare;
        return is;
    }

    ostream &write(ostream &os) const override {
        malware::write(os);
        cout<<"Rating: "; os<<rating<<endl;
        cout<<"Obfuscare: "; os<<obfuscare<<endl;
        return os;
    }
    int calc_rating() override{
        rating_impact+=rating+obfuscare;
    }
};


shared_ptr<malware> citire_malware(){
    int tip; int rating = 0;
    cout<<"1. rootkit\n2. keylogger\n3.kernel-keylogger\n4.ransomware";
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

int calcleaza_rating(vector<shared_ptr<malware>> m){
    int rating_final = 0;
    for(int i=0; i<m.size(); i++){
        rating_final += m[i]->calc_rating();
    }
    return rating_final;
}

class calculator: public IoBase{
private:
    vector<shared_ptr<malware>> m;
    int rating_final = 0;
public:
    istream &read(istream &is) override {
        int n;
        cout<<"Cati malware: "; is>>n;
        for(int i=0; i<n; i++) {
            m.push_back(citire_malware());
        }
        rating_final = calcleaza_rating(m);
        return is;
    }

    ostream &write(ostream &os) const override {
        os<<"Malware: \n";
        for(int i=0; i<m.size(); i++)
            os<<*m[i]<<endl;
        os<<"Rating final: "<<rating_final<<endl<<endl;
        return os;
    }
    vector<shared_ptr<malware>> getm(){
        return m;
    }

    void setm(vector<shared_ptr<malware>> a){
        m = a;
    }
};

shared_ptr<calculator> citeste_calculator(){
    shared_ptr<calculator>c;
    c = make_shared<calculator>();
    cin>>*c;
    return c;
}


class Menu{
private:
    vector<shared_ptr<calculator>> pc;
public:
    void listOpt(){
        cout<<endl;
        cout<<"1. citeste n calculatoare si afiseaza le\n";
        cout<<"2. afiseaza calculatoarele\n";
        cout<<"3. afiseaza informatiile PC-urilor sortate dupa rating\n";
        cout<<"4. afiseaza primele k PC-uri sortate dupa rating\n";
        cout<<"5. cat la % sunt infectate\n";
    }
    void run(){
        listOpt();
        int opt;
        cin>>opt;
        while(0<opt && opt<6){
            if(opt==1)
                citestePC();
            else if(opt==2){
                afiseazaPC();
            }else if (opt==3){
                afiseazasortate();
            }else if(opt==4){
                primele_k_sortate();
            }else if(opt==5){
                cat_la_suta();
            }else break;
            listOpt();
            cin>>opt;
        }
    }
    void cat_la_suta(){
        int ct=0;
        for(int i=0; i<pc.size(); i++)
            if(pc[i]->getm().size()!=0)
                ct++;
        cout<<ct/pc.size()*100;
    }
    void afiseazasortate(){
        for(int i=0; i<pc.size(); i++)
            for(int j=i+1; j<pc.size(); j++)
                if(pc[i]->getm() < pc[j]->getm())
                    swap(pc[i], pc[j]);
        for(auto x: pc){
            cout<<*x;
        }
    }

    void primele_k_sortate(){
        int k;
        cout<<"k= "; cin>>k;
        for(int i=0; i<pc.size(); i++)
            for(int j=i+1; j<pc.size(); j++)
                if(pc[i]->getm() < pc[j]->getm())
                    swap(pc[i], pc[j]);
        for(int i=0; i<k; i++)
            cout<<*pc[i];
    }

    void citestePC(){
        int n;
        cout<<"Cate pc-uri: "; cin>>n;
        for(int i = 0; i<n; i++){
            pc.push_back(citeste_calculator());
        }
    }

    void afiseazaPC(){
        for(int i = 0; i<pc.size(); i++)
            cout<<*pc[i];
    }

};

int main(){
    Menu m;
    m.run();
}