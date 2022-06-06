#include <bits/stdc++.h>

#include "util/IoBase.h"
#include "util/functions.h"

using namespace std;

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
        cout<<"Metoda de infectare: "; is>>metoda_infectare;
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
        cout<<"Registri modificati: \n";
        for(auto x: registri_modificati)
            cout<<x<<endl;
        return os;
    }
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
        cout<<"Cate importuri: "; is>>n;
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
};

class keylogger: public virtual malware {
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
            os<<x<<endl;
        os<<"Taste speciale: ";
        for(auto x: taste_speciale)
            os<<x<<endl;
        return os;
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
            os<<x<<endl;
        os<<"Taste speciale: ";
        for(auto x: taste_speciale)
            os<<x<<endl;
        os<<"Fisiere: "<<fisiere;
        os<<"Registre: "<<registre;
        return os;
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

class computer:public IoBase{
private:
    vector<shared_ptr<malware>> lista_malware;
    float rating_final;
public:
    istream &read(istream &is) override {
        IoBase::read(is);
        int n;
        string s;
        cout<<"Cate malware-uri: ";
        is>>n;
        for(int i=0; i<n; i++){
            is>>s;
            lista_malware.push_back(citire_malware());
        }
        cout<<"Ratingul final";
        is>>rating_final;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        for(auto x: lista_malware)
            os<<x<<endl;
        cout<<"Ratingul final";
        os<<rating_final;
        return os;
    }

};

class BaseMenu{
public:
    virtual void listOptions() {}
    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};

class SimpleMenu: public BaseMenu{
private:
    vector<computer> c;
public:
    void listOptions() override{
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

    void option1() {
        for(auto x : c){
            cout<<x<<endl;
        }
    }

    void option2() {
    }

    void option3() {

    }

    void option4() {

    }

    void mainLoop() override {
        while(true){
            int option = chooseOption(1, 5);
            if (option == 1) {
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
    int n;
    computer c;
    cin>>n;
    for (int i=0;i<n;i++)
        cin>>c;
    SimpleMenu menu;
    menu.mainLoop();
}