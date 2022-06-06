/*
 * Diaconescu Teodora-Csomina
 * Gcc - pot doar sa va spun ca am lucrat in Clion
 *
 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

int nr = -1;
struct data{
    int zi, luna, an;
};
class Malware{
protected:
    int rateImpact;
    data date;
    std::string metoda;
    std::vector<std::string> regMod;
    std::vector<std::string> nume;
public:
    Malware(std::vector<std::string> &nume, std::vector<std::string> &regMod, data &date, std::string &metoda) :
    nume{nume}, regMod{regMod}, date{date}, metoda{metoda} { rateImpact = 0; }

    Malware(std::vector<std::string> &nume, std::vector<std::string> &regMod, data &date) :
    nume{nume}, regMod{regMod}, date{date} { metoda = "unknown"; rateImpact = 0; }
    int Adaug()
    {
        int n = regMod.size();
        for(int i = 0; i < n; i++)
        {
            if(regMod[i].find("HKLM") || regMod[i].find("HKCU")) rateImpact += 20;
        }
        return rateImpact;
    }
    virtual int CalcGrad() { return 0; }

    friend std::ostream &operator<<(std::ostream &os, const Malware &malware) {
        os << "Nume: ";
        for(const auto & i : malware.nume)
        {
            os<<i<<' ';
        }
        os << "\nrateImpact: " << malware.rateImpact;

        return os;
    }

};

class Rootkit : public Malware {
protected:
    std::vector<std::string> importuri;
    std::vector<std::string> semnific;
public:
    Rootkit(std::vector<std::string> &importuri, std::vector<std::string> &semnific,std::vector<std::string> &nume, std::vector<std::string> &regMod, data &date) :
            importuri{importuri}, semnific{semnific}, Malware(nume, regMod, date) {}
    Rootkit(std::vector<std::string> &importuri, std::vector<std::string> &semnific,std::vector<std::string> &nume, std::vector<std::string> &regMod, data &date, std::string &metoda) :
    importuri{importuri}, semnific{semnific}, Malware(nume, regMod, date, metoda) {}

    int CalcGrad() override{
        rateImpact = 0;
        bool dublez = 0;
        int n = importuri.size();
        for(int i = 0; i < n; i++){
            if(importuri[i] == "SystemServiceDescriptorTable" || importuri[i] == "SSDT" || importuri[i] == "NtCreateFile") rateImpact += 100;
            if(importuri[i] == "ntoskrnl.exe") dublez = 1;
        }
        Adaug();
        if(dublez == 1) rateImpact *= 2;
        return rateImpact;
    }
};

class Keylogger : public Malware{
protected:
    std::vector<std::string> taste;
    std::vector<std::string> functii;
public:
    Keylogger(std::vector<std::string> &taste,std::vector<std::string> &functii,std::vector<std::string> &nume, std::vector<std::string> &regMod, data &date, std::string &metoda) :
    taste{taste}, functii{functii}, Malware(nume, regMod, date, metoda) {}
    Keylogger(std::vector<std::string> &taste,std::vector<std::string> &functii,std::vector<std::string> &nume, std::vector<std::string> &regMod, data &date) :
    taste{taste}, functii{functii}, Malware(nume, regMod, date) {}
    int CalcGrad() override{
        rateImpact = 0;
        long long n = taste.size();
        for(int i = 0; i < n; i++)
        {
            if(taste[i] == "[Up]" || taste[i] == "[Down]" || taste[i] == "[NumLock]" || taste[i] == "[Right]" || taste[i] == "[UP]" || taste[i] == "[Left]" || taste[i] == "[PageDomw]") rateImpact += 10;
        }
        n = functii.size();
        for(int i = 0; i < n; i++)
        {
            if(functii[i] == "CreateFileW" || functii[i] == "OpenProcess" || functii[i] == "ReadFile" || functii[i] == "WriteFile" || functii[i] == "RegisterHotKey" || functii[i] == "SetWindowsHookEx") rateImpact += 30;
        }
        Adaug();
        return rateImpact;
    }
};

class KernelKeylogger : public Malware{
protected:
    bool ascReg;
    bool ascFis;
    std::vector<std::string> importuri;
    std::vector<std::string> semnific;
    std::vector<std::string> taste;
    std::vector<std::string> functii;
public:
    KernelKeylogger(bool ascReg, bool ascFis,std::vector<std::string> &functii, std::vector<std::string> &importuri, std::vector<std::string> &semnific,std::vector<std::string> &taste,std::vector<std::string> &nume, std::vector<std::string> &regMod, data &date, std::string &metoda) :
    ascReg{ascReg}, ascFis(ascFis),taste{taste}, functii{functii}, importuri{importuri}, semnific{semnific}, Malware(nume, regMod, date, metoda){this->rateImpact = 0;}
    KernelKeylogger(bool ascReg, bool ascFis,std::vector<std::string> &functii, std::vector<std::string> &importuri, std::vector<std::string> &semnific,std::vector<std::string> &taste,std::vector<std::string> &nume, std::vector<std::string> &regMod, data &date) :
            ascReg{ascReg}, ascFis(ascFis),taste{taste}, functii{functii}, importuri{importuri}, semnific{semnific}, Malware(nume, regMod, date){this->rateImpact = 0;}
    int CalcGrad() override{
        rateImpact = 0;
        long long n = taste.size();
        for(int i = 0; i < n; i++)
        {
            if(taste[i] == "[Up]" || taste[i] == "[Down]" || taste[i] == "[NumLock]" || taste[i] == "[Right]" || taste[i] == "[UP]" || taste[i] == "[Left]" || taste[i] == "[PageDomw]") rateImpact += 10;
        }
        n = functii.size();
        for(int i = 0; i < n; i++)
        {
            if(functii[i] == "CreateFileW" || functii[i] == "OpenProcess" || functii[i] == "ReadFile" || functii[i] == "WriteFile" || functii[i] == "RegisterHotKey" || functii[i] == "SetWindowsHookEx") rateImpact += 30;
        }
        if(ascFis == 1) rateImpact += 20;
        if(ascReg == 1) rateImpact += 30;
        bool dublez = 0;
        n = importuri.size();
        for(int i = 0; i < n; i++){
            if(importuri[i] == "SystemServiceDescriptorTable" || importuri[i] == "SSDT" || importuri[i] == "NtCreateFile") rateImpact += 100;
            if(importuri[i] == "ntoskrnl.exe") dublez = 1;
        }
        Adaug();
        if(dublez == 1) rateImpact *= 2;

        return rateImpact;
    }
};

class Ransomware : public Malware{
    int rateCript;
    int rateObf;
public:
    Ransomware(int rateCript, int rateObf,std::vector<std::string> &nume, std::vector<std::string> &regMod, data &date, std::string &metoda) :
    rateCript{rateCript}, rateObf{rateObf}, Malware(nume, regMod, date, metoda) {}
    Ransomware(int rateCript, int rateObf, std::vector<std::string> &nume, std::vector<std::string> &regMod, data &date) :
    rateCript{rateCript}, rateObf{rateObf}, Malware(nume, regMod, date) {}
    int CalcGrad() override{
        rateImpact = 0;
        std::cout<<rateImpact<<"\n";
        Adaug();
        std::cout<<rateImpact<<"\n";
        rateImpact += rateObf + rateCript;
        std::cout<<rateImpact<<"\n";
        return rateImpact;
    }
};

class Calculator{
private:
    int id;
    int rating;
    int m;
    std::vector<std::shared_ptr<Malware>> mal;
public:
    Calculator()
    {
        rating = 0;
        std::cout<<"Adauga un calculator\n";
        id = ++nr;
        std::cout<<"Cati malware? ";
        std::cin>>m;
        for(int y = 0; y < m; y++)
        {
            std::string h;
            std::vector<std::string> nume;
            std::cout<<"Numar de cuvinte: ";
            int u;
            std::cin>>u;
            std::cout<<"Nume: ";
            for(int i = 0; i<u; i++)
            {
                std::cin>>h;
                nume.push_back(h);
            }
            std::cout<<"Data: ";
            data d{};
            std::cin>>d.zi>>d.luna>>d.an;
            std::vector<std::string> regMod;
            std::cout<<"Numar de reg modif: ";
            std::cin>>u;
            for(int i = 0; i<u; i++)
            {
                std::cin>>h;
                regMod.push_back(h);
            }
            std::string metoda = "NULL";
            std::cout<<"Cunosti metoda: ";
            std::cin>>h;
            if(h == "Da" || h == "DA" || h == "da")
            {
                std::cout<<"Metoda: ";
                std::cin>>metoda;
            }
            std::cout<<R"(rootkit\ keylogger\ kernel-keylogger\ ransomware)";
            std::cout<<"\nTip malware: ";
            std::cin>>h;
            if(h == "rootkit") {
                std::vector<std::string> importuri;
                std::vector<std::string> semnific;
                std::cout << "Numar Importuri: ";
                std::cin >> u;
                for (int t = 0; t < u; t++) {
                    std::cin >> h;
                    importuri.push_back(h);
                }
                std::cout << "Numar ceva semnificative: ";
                std::cin >> u;
                for (int i = 0; i < u; i++) {
                    std::cin >> h;
                    semnific.push_back(h);
                }

                if (metoda == "NULL") {
                    mal.push_back(std::make_shared<Rootkit> (importuri, semnific, nume, regMod, d));

                } else {
                    mal.push_back(std::make_shared<Rootkit> (importuri, semnific, nume, regMod, d, metoda));

                }
            }
            if(h == "keylogger"){
                std::vector<std::string> taste;
                std::vector<std::string> functii;
                std::cout << "Numar taste: ";
                std::cin >> u;
                for (int i = 0; i < u; i++) {
                    std::cin >> h;
                    taste.push_back(h);
                }
                std::cout << "Numar functii: ";
                std::cin >> u;
                for (int i = 0; i < u; i++) {
                    std::cin >> h;
                    functii.push_back(h);
                }

                if (metoda == "NULL") {
                    mal.push_back(std::make_shared<Keylogger> (taste, functii, nume, regMod, d));
                } else {
                    mal.push_back(std::make_shared<Keylogger> (taste, functii, nume, regMod, d, metoda));
                }
            }
            if(h == "kernel-keylogger"){
                std::vector<std::string> importuri;
                std::vector<std::string> semnific;
                std::cout << "Numar Importuri: ";
                std::cin >> u;
                for (int i = 0; i < u; i++) {
                    std::cin >> h;
                    importuri.push_back(h);
                }
                std::cout << "Numar ceva semnificative: ";
                std::cin >> u;
                for (int i = 0; i < u; i++) {
                    std::cin >> h;
                    semnific.push_back(h);
                }
                std::vector<std::string> taste;
                std::vector<std::string> functii;
                std::cout << "Numar taste: ";
                std::cin >> u;
                for (int i = 0; i < u; i++) {
                    std::cin >> h;
                    taste.push_back(h);
                }
                std::cout << "Numar functii: ";
                std::cin >> u;
                for (int i = 0; i < u; i++) {
                    std::cin >> h;
                    functii.push_back(h);
                }
                bool ascReg;
                bool ascFis;
                std::cout << "Au fost afectati reg: 0/1 ";
                std::cin >> ascReg;
                std::cout << "Au fost afectate fis: 0/1 ";
                std::cin >> ascFis;

                if (metoda == "NULL"){
                    mal.push_back(std::make_shared<KernelKeylogger> (ascReg, ascFis, functii, importuri, semnific, taste, nume, regMod, d));

                }
                else{
                    mal.push_back(std::make_shared<KernelKeylogger> (ascReg, ascFis, functii, importuri, semnific, taste, nume, regMod, d, metoda));
                }
            }
            if(h == "ransomware"){
                int rateCript;
                int rateObf;
                std::cout << "Rata criptare: ";
                std::cin >> rateCript;
                std::cout << "Rata obfuscare: ";
                std::cin >> rateObf;
                if(metoda == "NULL"){
                    mal.push_back(std::make_shared<Ransomware> (rateCript, rateObf, nume, regMod, d));
                }
                else{
                    mal.push_back(std::make_shared<Ransomware> (rateCript, rateObf, nume, regMod, d, metoda));
                }
            }
            std::cout<<rating<<"\n";
            rating += mal[y]->CalcGrad();
            std::cout<<mal[y]->CalcGrad()<<"\n";
            std::cout<<rating<<"\n";
        }

    }

    friend std::ostream &operator<<(std::ostream &os, const Calculator &calculator) {
        os << "id: " << calculator.id+1 << " rating: " << calculator.rating << " m: " << calculator.m << "\n";

        os << "Malware:\n";
        for(int i = 0; i < calculator.m; i++){
            os<<*calculator.mal[i]<<"\n";
        }

        return os;
    }

    int GetRating() const
    {
        return rating;
    }

    int GetId() const
    {
        return id;
    }

    int GetM() const
    {
        return m;
    }

};

std::vector<Calculator> v;

bool ptS(Calculator &c1, Calculator &c2){
    return c1.GetRating() > c2.GetRating();
}

bool ptS2(Calculator &c1, Calculator &c2) {
    return c1.GetId() < c2.GetId();
}

double CalcProc()
{
    int num = 0, p = 0;
    for(auto & i : v)
    {
        if(i.GetM() == 1) p++;
        num++;
    }
    double val = ((p * 100)* 1.) / num;
    return val;
}

void meniu()
{
    int n;
    std::cout<<"Buna ziua!\n";
    std::cout<<"Operatiuni si coduri:\n";
    std::cout<<"\t0: adauga un calculator\n";
    std::cout<<"\t1: afisarea informatiilor pentru fiecare calculator\n";
    std::cout<<"\t2: afisarea informatiilor pentru fiecare calculator fiind ordonate dupa ratingul final\n";
    std::cout<<"\t3: afisarea primelor k calculatoare ordonate dupa ratingul final\n";
    std::cout<<"\t4: afisarea procentului de computere infectate din firma\n";
    std::cout<<"\t5: terminarea programului\n";
    std::cin>>n;
    if(n == 0){
        Calculator a;
        v.push_back(a);
    }
    if(n == 1){
        for(auto & i : v)
        {
            std::cout<<i<<"\n";
        }
    }
    if(n == 2)
    {
        std::sort(v.begin(), v.end(),ptS);
        for(auto & i : v)
        {
            std::cout<<i<<"\n";
        }
        std::sort(v.begin(), v.end(),ptS2);
    }
    if(n == 3){
        std::cout<<"k: ";
        int k;
        std::cin>>k;
        std::cout<<"\n";
        std::sort(v.begin(), v.end(),ptS);
        for(int i = 0; i < std::min(k, int(v.size())); i++)
        {
            std::cout<<v[i]<<'\n';
        }
        std::sort(v.begin(), v.end(),ptS2);
    }
    if(n == 4){
        std::cout<<CalcProc()<<"\n";
    }
    if(n == 5) return;
    meniu();
}

int main() {
    meniu();
    return 0;
}
