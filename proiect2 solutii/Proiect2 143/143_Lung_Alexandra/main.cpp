//Lung Alexandra grupa 143
#include <bits/stdc++.h>
#include "util/IoBase.h"
#include "util/functions.h"
using namespace std;
/*Prin malware înțelegem un software rău intenționat pentru care se reține ratingul impactului (număr real), data de infectare (zi, luna, an), numele acestuia (care poate să fie format din mai multe cuvinte), metoda de infectare (dacă se cunoaște, altfel se reține șirul “unknown”) și un vector cu registrii modificați (reținuți ca stringuri).*/
class Malawer:public IoBase{
protected:
    double rating;
    unsigned int zi, luna ,an;
    string nume, metoda_infect;
    vector<string> reg;
public:
    Malawer() {
        rating = 0;
        an = zi = luna = 0;
        metoda_infect = "unknown";
    }

    Malawer(double rating, int zi, int luna ,int an, string nume,const vector<string> &reg,string metoda_infect = "unkown") : rating(rating),zi(zi),luna(luna),an(an),nume(std::move(nume)),reg(reg){metoda_infect = move(metoda_infect);}
    virtual double calc_rat();

    istream &read(istream &is) override {
        IoBase::read(is);
        cout<<"Introdu ratingul:";
        is >> rating;
        cout<<"Introdu data:";
        is >> zi  >> luna >> an;
        is.get();
        cout<<"Introdu nume:";
        getline(is,nume);
        int ok;
        cout<<"Apasa 1 daca vrei sa introduci metoda de inferctare altfel 0:\n";
        is >> ok;
        is.get();
        if(ok) {
            cout<<"Introdu metoda";
            getline(is, metoda_infect);
        }
        int reg_afect;
        cout<<"Introdu numarul registrilor afectati:";
        is >> reg_afect;
        cout<<"introdu registrii afectati:";
        reg.resize(reg_afect);
        for(int  i = 0;i < reg_afect; ++i){
            is >> reg[i];
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os << "Rating " << rating <<"\n";
        os << "Data infectare " << zi <<"." << luna <<"." << an  <<"\n";
        os << "Nume " << nume <<"\n";
        os << "Metoda infectare " << metoda_infect <<"\n";
        os << "Registrii afectati: ";
        for(auto &x:reg)
            cout << x << " ";
        cout<<"\n";
        return os;
    }
};

double Malawer::calc_rat() {
    rating = 0;
    for(auto &x:reg)
        if(x == "HKLM-run" || x == "HKCU-run")
            rating += 20;
    return rating;
}

/*Prin rootkit înțelegem un tip de malware ce are drept scop obținerea drepturilor de administrator asupra dispozitivului infectat. Pentru rootkit se reține lista importurilor care poate fi unul și oricât de multe (importurile fac referire la numele fișierelor .dll folosite) și o listă de stringuri semnificative (anumite stringuri dintr-un binar pot fi un indice asupra faptului că fișierul este rău intenționat).
*/
class rootkit: public virtual Malawer{
protected:
    vector<string> importuri;
    vector<string>semnificativ_str;
public:
    rootkit() : Malawer(){}

    rootkit(double rating, int zi, int luna, int an, const string &nume,
            const vector<string> &reg,const string &metodaInfect, const vector<string> &importuri, const vector<string> &seminificative_str) : Malawer(rating, zi, luna, an, nume, reg, metodaInfect), importuri(importuri), semnificativ_str(seminificative_str) {}
    double calc_rat() override;

    istream &read(istream &is) override {
        Malawer::read(is);
        cout<< "introdu numarul de importuri:";
        int nr;
        is >> nr;
        importuri.resize(nr);
        for(int i=0;i<nr;++i)
        is >> importuri[i];
        is >> nr;
        importuri.resize(nr);
        cout<<"introdu nr de siruri semnificative";
        for(int i=0;i<nr;++i)
        is >> semnificativ_str[i];
        return is;
    }

    ostream &write(ostream &os) const override {
        Malawer::write(os);
        return os;
    }
};

double rootkit::calc_rat() {
    vector<string> semnificativ_str1 ={"System Service Descriptor Table","SSDT","NtCreateFile"};
    vector<string> importuri1 = {"ntoskrnl.exe"};
    for(auto &x:semnificativ_str)
        if(find(semnificativ_str1.begin(), semnificativ_str1.end(),x)!= semnificativ_str1.end())
            rating += 100;
    for(auto &x:importuri)
        if(find(importuri1.begin(), importuri1.end(), x)!= importuri1.end())
            rating *= 2;
    return rating;
}

/*Prin keylogger înțelegem un malware care înregistrează acțiunile de la tastatură și le trimite mai departe. Pentru un keylogger se reține o listă cu funcțiile folosite și o listă cu tastele speciale definite.
*/
class keylogger:public virtual Malawer{
protected:
    vector<string> functii;
    vector<string> taste_speciale;
public:
    keylogger() :Malawer(){}

    keylogger(double rating, int zi, int luna, int an, const string &nume,
              const vector<string> &reg,const vector<string> &functii, const vector<string> &taste_speciale,const string &metodaInfect) : Malawer(rating, zi, luna, an, nume, reg, metodaInfect),functii(functii),taste_speciale(taste_speciale) {}
    double calc_rat() override;

    ostream &write(ostream &os) const override;

    istream &read(istream &is) override;
};

istream &keylogger::read(istream &is) {
    Malawer::read(is);
    is >> functii >> taste_speciale;
    return is;
}

ostream &keylogger::write(ostream &os) const {
    Malawer::write(os);
    os << functii << taste_speciale;
    return os;
}

double keylogger::calc_rat() {
    vector<string> taste_speciale1 ={"[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
    vector<string> functii1 = {"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};
    for(auto &x:taste_speciale)
        if(find(taste_speciale1.begin(), taste_speciale1.end(), x)!= taste_speciale1.end())
            rating += 100;
    for(auto &x:functii)
        if(find(functii1.begin(), functii1.end(), x)!= functii1.end())
            rating *= 2;
    return rating;
}

/*
Prin kernel-keylogger înțelegem un keylogger ce rulează în kernel-mode (de obicei prin intermediul unui rootkit). Prin urmare, putem considera că este are atât proprietățile unui rootkit cât și ale unui	 keylogger. În plus, dorim să memorăm dacă ascunde fișiere și registrii.
 */
class kernel_keylogger : public virtual rootkit, public  virtual keylogger{
protected:
    int nr_fis, nr_reg;
public:
    kernel_keylogger() :rootkit(),keylogger(),nr_fis(0),nr_reg(0) {}

    kernel_keylogger(double rating, int zi, int luna, int an, const string &nume,
                     const vector<string> &reg, const string &metodaInfect, const vector<string> &importuri,
                     const vector<string> &seminificativeStr, double rating1, int zi1, int luna1, int an1,
                     const string &nume1, const vector<string> &reg1, const string &metodaInfect1,
                     const vector<string> &functii, const vector<string> &tasteSpeciale , int nr_fis, int nr_reg) : rootkit(rating, zi, luna, an,
                                                                                                   nume,
                                                                                                   reg, metodaInfect,importuri,
                                                                                                   seminificativeStr),
                                                                                           keylogger(rating1, zi1,
                                                                                                     luna1, an1, nume1,
                                                                                                     reg1, functii,
                                                                                                     tasteSpeciale,
                                                                                                     metodaInfect1),
                                                                                                     nr_reg(nr_reg), nr_fis(nr_fis) {}
    double calc_rat() override;

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

ostream &kernel_keylogger::write(ostream &os) const {
        keylogger::write(os);
        rootkit::write(os);
        os << nr_fis << " " <<  nr_reg << " ";
        return os;
}

istream &kernel_keylogger::read(istream &is) {
    keylogger::read(is);
    rootkit::read(is);
    is >> nr_fis >> nr_reg;
    return is;
}

double kernel_keylogger::calc_rat() {
    rating += rootkit::calc_rat() + keylogger::calc_rat();
    if(nr_fis)
        rating += 20;
    if(nr_reg)
        rating += 30;
    return rating;
}

/*
Prin ransomware înțelegem un malware care criptează fișiere de pe disk. Pentru acesta se reține ratingul de criptare (un număr de la 1 la 10) și un rating de obfuscare (un număr real ce reprezintă procentul de obfuscare (obfuscare = metodă de a ascunde/îngreuna intenția inițială a codului)).
 */
class ransomware : public Malawer{
    protected:
    int rating_cript;
    double rating_ob;
public:
    ransomware() : Malawer(),rating_cript(0),rating_ob(0) {}

    ransomware(double rating, int zi, int luna, int an, const string &nume,
               const vector<string> &reg,const string &metodaInfect, int rating_cript, int rating_ob) : Malawer(rating, zi, luna, an, nume, reg, metodaInfect),rating_ob(rating_ob), rating_cript(rating_cript) {}
    double calc_rat() override;
};

double ransomware::calc_rat() {
    rating += Malawer::calc_rat();
    rating += rating_ob + double(rating_cript);
    return rating;
}

/*
Pentru fiecare computer din firmă se reține un id unic, incrementat automat, o listă de malware (poate conține un malware sau mai multe) și ratingul final ce este calculat drept suma ratingului impactului fiecărui malware.

 */
class computer : public IoBase{
protected:
    static int id;
    vector<shared_ptr<Malawer>>vir;
    double rating_tot;
public:
    const vector<shared_ptr<Malawer>> &getVir() const {
        return vir;
    }

    double getRatingTot() const {
        return rating_tot;
    }

    computer():rating_tot(0){}
    explicit computer(const vector<shared_ptr<Malawer>> &vir):vir(vir),rating_tot(0){id++;}
    double calc_r();

    ostream &write(ostream &os) const override;
};
int computer :: id = 0;
double computer::calc_r() {
    rating_tot = 0;
    for(auto &x:vir){
        auto *rootkit = dynamic_cast<class rootkit *>(x.get());
        auto *kernel_keylogger = dynamic_cast< class kernel_keylogger*>(x.get());
        auto *keylogger = dynamic_cast<class keylogger*>(x.get());
        auto *mal = dynamic_cast<class Malawer*>(x.get());
        auto *randsome = dynamic_cast<class ransomware*>(x.get());
        if(rootkit)
            rating_tot += rootkit->calc_rat();
        if(keylogger)
            rating_tot += keylogger->calc_rat();
        if(mal)
            rating_tot += mal->calc_rat();
        if(kernel_keylogger)
            rating_tot += kernel_keylogger->calc_rat();
        if(randsome)
            rating_tot += randsome->calc_rat();
    }
    return rating_tot;
}
ostream &computer::write(ostream &os) const {
    IoBase::write(os);
    os<<"Id:"<<id<<"\n";
    for(auto &x:vir)
        os<<*x<<" ";
    os<<"\n";
    os<<"rating total: "<<rating_tot <<"\n";
    cout<<"\n";
    return os;
}
/*
Programul realizat trebuie să aibă un meniu care permite:
1. afișarea informațiilor pentru fiecare calculator
2. afișarea informațiilor pentru fiecare calculator fiind ordonate după ratingul final
 3. afișarea primelor k calculatoare ordonate după ratingul final
4. afișarea procentului de computere infectate din firmă

 */
class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};

class SimpleMenu : public BaseMenu {
protected:
    vector<computer>calc;
public:
    SimpleMenu()= default;

    explicit SimpleMenu(const vector<computer> &calc) : calc(calc) {};

    void listOptions() override {
        cout << "1.Afisarea informatiilor calculatoare." << '\n';
        cout << "2.Afisarea informatiilor pentru fiecare calculator fiind ordonate dupa ratingul final."<< '\n';
        cout << "3.Afisarea primelor k calculatoare ordonate dupa ratingul final." << '\n';
        cout << "4.Afisarea procentului de computere infectate din firma. " << '\n';
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
        for(int i=0;i<calc.size()-1;++i)
            for(int j=i+1;j<calc.size();++j)
                if(calc[i].getRatingTot() > calc[j].getRatingTot())
                    swap(calc[i], calc[j]);
        for(auto &x:calc)
            cout<<x<<"\n";
    }
    void option3() {
        int k;
        cout << "Introdu numarul k:";
        cin>>k;
        if(k > 0 and  k < calc.size()) {
            for(int i=0;i<calc.size()-1;++i)
                for(int j=i+1;j<calc.size();++j)
                    if(calc[i].getRatingTot() > calc[j].getRatingTot())
                        swap(calc[i], calc[j]);
            for (int i = 0; i < k; ++i)
                cout << calc[k];
        }
        else cout<<"K invalid";
    }

    void option4() {
        int nr_infect = 0;
        for(auto &x:calc)
            if(x.getVir().empty() != 0)
                nr_infect ++;
        int x = (int)calc.size();
        if(nr_infect != 0)
            cout << "Exista " <<(double(nr_infect)/double(x))*100<<"\n";
        else cout<<"Nu exista calculatoare infectate.";
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
    vector<shared_ptr<Malawer>> vir = {
            make_shared<Malawer>(Malawer(8.0,11, 2, 2019,"dncfkj",{"eax", "ebx"})),
            make_shared<Malawer>( Malawer (9.50,
            13, 4,1995,
            "fdejsba",
            {"eax"})),
            make_shared<rootkit>(rootkit(9,2,3,2020,"dsjfjah",{"eax"},"svb",{"ipo"},{"si"}))
    };
    vector<computer>calculatoare;
    calculatoare.emplace_back(vir);
    for(auto &p:calculatoare)
            p.calc_r();

    SimpleMenu menu(calculatoare);
    menu.mainLoop();
    return 0;
}

