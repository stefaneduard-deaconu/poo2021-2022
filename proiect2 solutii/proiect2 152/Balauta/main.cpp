#include <iostream>
#include <cstring>
#include <list>
#include "util/IoBase.h"
#include "util/functions.h"
#include <typeinfo>
#include <memory>
#include <bits/stdc++.h>

using namespace std;

class Malware : public IoBase{
    protected:
    double rating = 0;
    int zi, luna, an;
    string nume;
    string infectare = "unknown";
    int nrregistri;
    vector<string> registri;
    string registru;
    public:
    // IoBase - overrided functions
    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "Zi:";
        is >> zi;
        cout << "Luna:";
        is >> luna;
        cout << "An:";
        is >> an;
        cout << "Metoda de Infectare:";
        is >> infectare;
        cout << "Numarul de registri:";
        is >> nrregistri;
        cout << "Registri:";
        for (int i = 0; i < nrregistri; ++i){
            is >> registru;
            registri.push_back(registru);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os << "\n" << nume <<"\n";
        os << "Rating: "<<rating <<". ";
        os << "Zi: "<< zi <<". ";
        os << "Luna: "<< luna <<". ";
        os << "An: "<< an <<". ";
        os << "Metoda de infectare: "<< infectare <<". ";
        os << "Registri: ";
        for (string registru : registri){
            os << registru <<' ';
        }
        return os;
    }

    void setnume(string _nume){
        nume = _nume;
    }

    virtual void CalculRating(){
        int ok = 1;
        for (auto registru: registri){
            if ((registru == "HKLM-run" or registru == "HKCU-run") && ok == 1)
                rating += 20;
                ok = 0;
        }
    }

    string getnume(){return nume;}
    double getrating(){return rating;}
    int getzi(){return zi;}
    int getluna(){return luna;}
    int getan(){return an;}
    string getinfect(){return infectare;}
    vector<string> getregistri(){return registri;}
};

class Rootkit : virtual public Malware{
protected:
    vector<string> importuri;
    vector<string> stringuri;
public:

    istream &read(istream &is) override{
    Malware::read(is);
        int nrimp, nrstr;
        string import, stringg;
        ///read importuri
        cout << "Numarul de importuri:";
        is >> nrimp;
        cout << "Lista de importuri (separate prin virgula si spatiu, cu punct la final):";
        string s;
        int i = 0;
        while (i < nrimp){
            is >> import;
            int n = import.length();
            if(import[n-1] != ',' and import[n-1] != '.'){
                s += import;
                s += " ";
            }
            else {
                s += import;
                s.pop_back();
                importuri.push_back(s);
                s = "";
                i++;
            }

        }
        ///read stringuri
        cout << "Numarul de stringuri";
        is >> nrstr;
        cout << "Lista de stringuri(separate prin virgula si spatiu, cu punct la final):";
        s = "";
        i = 0;
        while (i < nrstr){
            is >> stringg;
            int n = stringg.length();
            if(stringg[n-1] != ',' and stringg[n-1] != '.'){
                s += stringg;
                s += " ";
            }
            else {
                s += stringg;
                s.pop_back();
                stringuri.push_back(s);
                s = "";
                i++;
            }

        }

    return is;
}

    ostream &write(ostream &os) const override{
        Malware::write(os);
        os << "\nImporturi:\n";
        for (string importt : importuri)
            os <<importt <<" ";
        os << "\nStringuri:\n";
        for (string stringgg : stringuri)
            os <<stringgg <<" ";
        return os;
    }

    vector<string> getimporturi(){return importuri;}
    vector<string> getstringuri(){return stringuri;}
    double getrating(){return rating;}

    void CalculRating(){
        for(auto stringg : stringuri){
            if(stringg == "System Service Descriptor Table" or stringg == "SSDT" or stringg == "NtCreateFile"){
                rating += 100;
            }
        }
        for(auto import : importuri){
            if (import == "ntoskrnl.exe"){
                rating *= 2;
            }
        }
        Malware::CalculRating();
    }
};

class Keylogger : virtual public Malware{
protected:
    vector<string> functii;
    vector<string> taste;
public:
    istream &read(istream &is) override{
        Malware::read(is);
        int nrfunc, nrtaste;
        string functie, tasta;
        ///read functii
        cout << "Numarul de functii:";
        is>>nrfunc;
        cout <<"Lista de functii (separate prin virgula si spatiu, cu punct la final):";
        string s;
        int i = 0;
        while (i < nrfunc) {
            is >> functie;
            int n = functie.length();
            if (functie[n - 1] != ',' and functie[n - 1] != '.') {
                s += functie;
                s += " ";
            } else {
                s += functie;
                s.pop_back();
                functii.push_back(s);
                s = "";
                i++;
            }
        }
        /// read taste
        cout << "Numarul de taste:";
        is >> nrtaste;
        cout <<"Lista de taste (separate prin virgula si spatiu, cu punct la final):";
        s = "";
        i = 0;
        while (i < nrtaste){
            is >> tasta;
            int n = tasta.length();
            if(tasta[n-1] != ',' and tasta[n-1] != '.'){
                s += tasta;
                s += " ";
            }
            else {
                s += tasta;
                s.pop_back();
                taste.push_back(s);
                s = "";
                i++;
            }

        }
        return is;
    }

    ostream &write(ostream &os) const override{
        Malware::write(os);
        os << "\nFunctii:\n";
        for (string functie : functii)
            os <<functie <<" ";
        os << "\nTaste:\n";
        for (string tasta : taste)
            os <<tasta <<" ";
        return os;
    }

    vector<string> gettaste(){return taste;}
    vector<string> getfunctii(){return functii;}
    double getrating(){return rating;}

    void CalculRating(){
        Malware::CalculRating();
        for(auto tasta: taste){
            if (tasta == "[Up]" or tasta == "[Num Lock]" or tasta == "[Down]" or tasta == "[Right]" or tasta == "[UP]" or tasta == "[Left]" or tasta == "[PageDown]")
                rating += 10;
        }
        for(auto functie: functii){
            if (functie == "CreateFileW" or functie == "OpenProcess" or functie == "" or functie == "ReadFile" or functie == "WriteFile" or functie == "RegisterHotKey" or functie == "SetWindowsHookEx"){
                rating += 30;
            }
        }
    }
};

class KernelKeylogger : public Rootkit, public Keylogger{
private:
    bool ascundeF, ascundeR;
public:

    istream &read(istream &is) override {
        Rootkit::read(is);
        is >> ascundeF;
        is >> ascundeR;
        int nrfunc, nrtaste;
        string functie, tasta;
        cout << "Numarul de functii:";
        is>>nrfunc;
        cout <<"Lista de functii (separate prin virgula si spatiu, cu punct la final):";
        string s;
        int i = 0;
        while (i < nrfunc) {
            is >> functie;
            int n = functie.length();
            if (functie[n - 1] != ',' and functie[n - 1] != '.') {
                s += functie;
                s += " ";
            } else {
                s += functie;
                s.pop_back();
                functii.push_back(s);
                s = "";
                i++;
            }
        }
        /// read taste
        cout << "Numarul de taste:";
        is >> nrtaste;
        cout <<"Lista de taste (separate prin virgula si spatiu, cu punct la final):";
        s = "";
        i = 0;
        while (i < nrtaste){
            is >> tasta;
            int n = tasta.length();
            if(tasta[n-1] != ',' and tasta[n-1] != '.'){
                s += tasta;
                s += " ";
            }
            else {
                s += tasta;
                s.pop_back();
                taste.push_back(s);
                s = "";
                i++;
            }

        }
        return is;
    }

    ostream &write(ostream &os) const override{
        Rootkit::write(os);
        os << "\nFunctii:\n";
        for (string functie : functii)
            os <<functie <<" ";
        os << "\nTaste:\n";
        for (string tasta : taste)
            os <<tasta <<" ";
        return os;
    }

    void CalculRating(){
        Rootkit::CalculRating();
        for(auto tasta: taste){
            if (tasta == "[Up]" or tasta == "[Num Lock]" or tasta == "[Down]" or tasta == "[Right]" or tasta == "[UP]" or tasta == "[Left]" or tasta == "[PageDown]")
                rating += 10;
        }
        for(auto functie: functii){
            if (functie == "CreateFileW" or functie == "OpenProcess" or functie == "" or functie == "ReadFile" or functie == "WriteFile" or functie == "RegisterHotKey" or functie == "SetWindowsHookEx"){
                rating += 30;
            }
        }
        if (ascundeF == 1)
            rating += 20;
        if (ascundeR == 1)
            rating += 30;

    }

    double getrating(){return rating;}
};

class Ransomware : public Malware{
private:
    double rngCript;
    double rngObfuscare;
public:
    istream &read(istream &is) override{
        Malware::read(is);
        cout << "Rating de Criptare:";
        is >> rngCript;
        cout << "Rating de Obfuscare:";
        is >> rngObfuscare;
        return is;
    }

    ostream &write(ostream &os) const override{
        Malware::write(os);
        os << "\nRatingul de Criptare:";
        os << rngCript;
        os << "\nRatingul de Obfucsare:";
        os << rngObfuscare;
        return os;
    }

    void CalculRating(){
        rating += rngCript + rngObfuscare;
    }
    double getrating(){return rating;}

};

class Computer : public IoBase{
private:
    int id;
    vector<shared_ptr<Malware> > listaMal;
    double rtgFinal = 0;
public:
    Computer(int _id){
        id = _id;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);

        os <<"\nComputerId: "<< id <<'\n';
        if(listaMal.size() == 0){
            os << "Computer nevirusat\n";
        }
        else {
            os <<"Malware:";
            for(auto mal : listaMal){
                os << *mal<<'\n';
            }
        }

        os <<"Rating Final:"<<rtgFinal<<'\n';
        return os;
    }

    void AddRootkit(Rootkit R){
        listaMal.push_back(make_shared<Rootkit>(R));
    }

    void AddKeylogger(Keylogger K){
        listaMal.push_back(make_shared<Keylogger>(K));
    }

    void AddKernelKeylogger(KernelKeylogger KK){
        listaMal.push_back(make_shared<KernelKeylogger>(KK));
    }

    void AddRansomware(Ransomware RR){
        listaMal.push_back(make_shared<Ransomware>(RR));
    }

    double CalculRatingFinal() {
        for (auto mal: listaMal) {
            mal->CalculRating();
            rtgFinal += mal->getrating();
        }
        return rtgFinal;
    }
    void setRatingFinal(double rtg){rtgFinal = rtg;}
    double getRatingFinal(){return rtgFinal;}

};

int n, m;
vector<Computer> computere;

void CitireInformatii(){
    computere.clear();
    cout << "Numarul de computere:";
    cin >> n;
    for(int i = 0; i < n; ++i){
        Computer C(i);
        cout << "Numarul de virusi:";
        cin >> m;
        for(int j = 0; j < m; ++j){
            cout << "Tipul de Malware:";
            string _nume;
            cin >> _nume;
            if(_nume == "Rootkit"){
                Rootkit R;
                cin >> R;
                R.setnume("Rootkit");
                C.AddRootkit(R);
            }
            else if(_nume == "Keylogger"){
                Keylogger K;
                cin >> K;
                K.setnume("Keylogger");
                C.AddKeylogger(K);
            }
            else if(_nume == "Ransomware"){
                Ransomware RR;
                cin >> RR;
                RR.setnume("Ransomware");
                C.AddRansomware(RR);
            }
            else if (_nume == "Kernel-Keylogger"){
                KernelKeylogger KK;
                cin >> KK;
                KK.setnume("Kernel-Keylogger");
                C.AddKernelKeylogger(KK);
            }
        }
        computere.push_back(C);
    }
}

bool compare(Computer A, Computer B){
    return A.getRatingFinal() < B.getRatingFinal();
}

class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};

class SimpleMenu : public BaseMenu {
public:
    void listOptions() override {
        cout << "1. Afiseaza informatiile pentru fiecare calculator ." << '\n';
        cout << "2. Afiseaza informatiile pentru fiecare calculator fiind ordonate dupa ratingul final." << '\n';
        cout << "3. Afiseaza primele k calculatoare ordonate dupa ratingul final." << '\n';
        cout << "4. Afiseaza procentul de computere infectate din firma." << '\n';
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

    void option1() {
        CitireInformatii();
        for(auto computer : computere){
            computer.CalculRatingFinal();
            cout << computer<<'\n';
        }
    }

    void option2() {
        CitireInformatii();
        for(int i = 0; i < computere.size(); ++i){
            computere[i].CalculRatingFinal();
        }
        sort(computere.begin(), computere.end(), compare);
        for(int i = 0; i < computere.size(); ++i){
            cout << computere[i];
        }
    }

    void option3() {
        CitireInformatii();
        cout << "K = ";
        int k;
        cin >> k;
        for(int i = 0; i < computere.size(); ++i){
            computere[i].CalculRatingFinal();
        }
        sort(computere.begin(), computere.begin() + k, compare);
        for(int i = 0; i < computere.size(); ++i){
            cout << computere[i];
        }

    }

    void option4(){
        CitireInformatii();
        int virusate = 0;
        for(int i = 0; i < computere.size(); ++i){
            computere[i].CalculRatingFinal();
            if(computere[i].getRatingFinal()){
                ++virusate;
            }
        }

        cout << "Procentul de computere infecate de firma este ";
        cout << (virusate * 100/ n);
        cout <<"%.";
    }

    void mainLoop() override {
        while (true) {
            int option = chooseOption(0, 4);
            if (option == 1) {
                option1();
            } else if (option == 2) {
                option2();
            } else if (option == 3) {
                option3();
            } else if (option == 4) {
                option4();
            } else if (option == 0){
                break;
            }
        }
        cout << '\n'
             << "---------------------------------"
             << '\n'
             << "Programul s-a incheiat cu success";
    }
};

int main() {
    SimpleMenu meniu;
    meniu.mainLoop();
    return 0;
}
