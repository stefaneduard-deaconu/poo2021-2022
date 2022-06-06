//Lung Alexandra grupa 143
#include <bits/stdc++.h>
#include "util/IoBase.h"
#include "util/functions.h"
using namespace std;


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
    virtual void calc_rat();

    istream &read(istream &is) override {
        IoBase::read(is);
//        cout<<"Introdu ratingul:";
//        is >> rating;
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
            cout<<"Introdu metoda:";
            getline(is, metoda_infect);
        }else{
            metoda_infect="unknown";
            // else the method is unknown
        }
        int reg_afect;
        cout<<"Registrii:\n";
        cin>>reg;
        return is;
        // use the template for reading vectors
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os << "Rating: " << rating <<"\n";
        os << "Data infectare: " << zi <<"." << luna <<"." << an  <<"\n";
        os << "Nume: " << nume <<"\n";
        os << "Metoda infectare: " << metoda_infect <<"\n";
        cout<<"Registrii afectati: "<<"\n"<<reg<<"\n";
        // use the templates to write vectors
        return os;
    }

    double getRating() const;
};

void Malawer::calc_rat() {
    rating = 0;
    for(auto &x:reg)
        if(x == "HKLM-run" || x == "HKCU-run"){
            rating += 20;
            break;
        }


}

double Malawer::getRating() const {
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
    void calc_rat() override;

    istream &read(istream &is) override {
        Malawer::read(is);
        cout<<"Importuri:\n";
        cin>>importuri;
        cout<<"String.uri semnificative:\n";
        cin>>semnificativ_str;
        return is;
    }

    ostream &write(ostream &os) const override {
        Malawer::write(os);
        cout<<"\n";
        cout<<"Importuri: "<<importuri<<"\n";
        cout<<"String.uri semnificative: "<<semnificativ_str<<"\n";
        return os;
    }
};

void rootkit::calc_rat() {
    vector<string> semnificativ_str1 ={"System Service Descriptor Table","SSDT","NtCreateFile"};
    vector<string> importuri1 = {"ntoskrnl.exe"};

    Malawer::calc_rat();
    // calculate the rate using the information already in the Malware class ( HKLM-run and HKCU-run )

    for(auto &x:semnificativ_str)
        if(find(semnificativ_str1.begin(), semnificativ_str1.end(),x)!= semnificativ_str1.end())
            rating += 100;
    for(auto &x:importuri)
        if(find(importuri1.begin(), importuri1.end(), x)!= importuri1.end())
            rating *= 2;
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
    void calc_rat() override;

    ostream &write(ostream &os) const override;

    istream &read(istream &is) override;
};

istream &keylogger::read(istream &is) {
    Malawer::read(is);
    cout<<"Functii:\n";
    cin>>functii;
    cout<<"Taste speciale:\n";
    cin>>taste_speciale;
    return is;
}

ostream &keylogger::write(ostream &os) const {
    Malawer::write(os);
    cout<<"\n";
    cout<<"Functii: "<<functii<<"\n";
    cout<<"Taste speciale: "<<taste_speciale<<"\n";
    return os;
}

void keylogger::calc_rat() {
    vector<string> taste_speciale1 ={"[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
    vector<string> functii1 = {"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};

    Malawer::calc_rat();
    // calculate the rate using the information already in the Malware class ( HKLM-run and HKCU-run )

    for(auto &x:taste_speciale)
        if(find(taste_speciale1.begin(), taste_speciale1.end(), x)!= taste_speciale1.end())
            rating += 100;
    for(auto &x:functii)
        if(find(functii1.begin(), functii1.end(), x)!= functii1.end())
            rating *= 2;
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
    void calc_rat() override;

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

ostream &kernel_keylogger::write(ostream &os) const {
    Malawer::write(os);

    cout<<"\n";
    cout<<"Functii: "<<functii<<"\n";
    cout<<"Taste speciale: "<<taste_speciale<<"\n";

    cout<<"Importuri: "<<importuri<<"\n";
    cout<<"String.uri semnificative: "<<semnificativ_str<<"\n";

    cout<<"Numar fisiere: "<<nr_fis<<"\n";
    cout<<"Numar registrii: "<<nr_reg<<"\n";

    return os;
}

istream &kernel_keylogger::read(istream &is) {
    Malawer::read(is);

    cout<<"Functii:\n";
    cin>>functii;
    cout<<"Taste speciale:\n";
    cin>>taste_speciale;

    cout<<"Importuri:\n";
    cin>>importuri;
    cout<<"String.uri semnificative:\n";
    cin>>semnificativ_str;

    cout<<"Numar fisiere: ";
    cin>>nr_fis;
    cout<<"Numar registrii: ";
    cin>>nr_reg;
    return is;

}

void kernel_keylogger::calc_rat() {
    keylogger::calc_rat();

    // we calculate the rating for keylogger and now we calculate separately the rating we need to add for rootkit properties

    vector<string> semnificativ_str_bad ={"System_Service_Descriptor_Table","SSDT","NtCreateFile"};
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

    // now we add rating for nr of files and registers

    if(nr_fis)
        rating += 20;
    if(nr_reg)
        rating += 30;
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
    void calc_rat() override;

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

void ransomware::calc_rat() {
    Malawer::calc_rat();
    rating += rating_ob + double(rating_cript);
}

istream &ransomware::read(istream &is) {
    Malawer::read(is);
    cout<<"Rating cript: ";
    cin>>rating_cript;
    cout<<"Rating obfuscare: ";
    cin>>rating_ob;
    return is;
}

ostream &ransomware::write(ostream &os) const {
    Malawer::write(os);
    cout<<"Rating cript: "<<rating_cript<<"\n";
    cout<<"Rating obfuscare: "<<rating_ob<<"\n";
    return os;
}

/*
Pentru fiecare computer din firmă se reține un id unic, incrementat automat, o listă de malware (poate conține un malware sau mai multe) și ratingul final ce este calculat drept suma ratingului impactului fiecărui malware.

 */
class computer : public IoBase{
protected:
    static int id;
    int id_pc;
    vector<shared_ptr<Malawer>>vir;
    double rating_tot;
public:
    computer(){
        id_pc=id++;
        rating_tot=0;
    }

    explicit computer(const vector<shared_ptr<Malawer>> &virusi) : vir(virusi) {
        id_pc=id++;
        rating_tot=0;
        for(auto & i : vir){
            i->calc_rat();
            double current_rating=i->getRating();
            rating_tot+=current_rating;
        }
    }

    const vector<shared_ptr<Malawer>> &getVir() const {
        return vir;
    }

    double getRatingTot() const {
        return rating_tot;
    }

    ostream &write(ostream &os) const override;

    istream &read(istream &is) override;


};
int computer :: id = 1;

// we don t need one extra method to calculate thee total rating for a computer. As long as we read different kinds of viruses
// for a pc, we increment the total rating of the computer with the rating of the current virus

ostream &computer::write(ostream &os) const {
    cout<<"ID computer: "<<id_pc<<"\n";
    cout<<"Rating total: "<<rating_tot<<"\n";
    for(const auto & i : vir){
        auto *asKeylogger = dynamic_cast<keylogger *>(i.get());
        auto *asRootkit = dynamic_cast<rootkit *>(i.get());
        auto *asKernelKeylogger = dynamic_cast<kernel_keylogger *>(i.get());
        auto *asRansomware = dynamic_cast<ransomware *>(i.get());

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

istream &computer::read(istream &is) {
    cout << "Introduceti m virusi:\n";
    cout << "m= ";
    int m;
    cin >> m;
    if (m != 0) {
        for (int i = 0; i < m; i++) {
            double rating_total_curent = 0;
            cout << "Introduceti:\n 1. Rootkit\n 2. Keylogger\n 3. KernelKeylogger\n 4. Ransomware\n";
            int tip;
            cin >> tip;
            while (tip != 1 and tip != 2 and tip != 3 and tip != 4) {
                cout << "Tip invalid. Reintroduceti tipul de virus.\n";
                cin >> tip;
            }
            if (tip == 1) {
                rootkit virus;
                cin >> virus;
                virus.calc_rat();
                vir.push_back(make_shared<rootkit>(virus));
                rating_total_curent += virus.getRating();
            } else if (tip == 2) {
                keylogger virus;
                cin >> virus;
                virus.calc_rat();
                vir.push_back(make_shared<keylogger>(virus));
                rating_total_curent += virus.getRating();
            } else if (tip == 3) {
                kernel_keylogger virus;
                cin >> virus;
                virus.calc_rat();
                vir.push_back(make_shared<kernel_keylogger>(virus));
                rating_total_curent += virus.getRating();
            } else if (tip == 4) {
                ransomware virus;
                cin >> virus;
                virus.calc_rat();
                vir.push_back(make_shared<ransomware>(virus));
                rating_total_curent += virus.getRating();
            }
            rating_tot += rating_total_curent;
        }
    }

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
    vector<computer> calc;
public:
    SimpleMenu() = default;

    explicit SimpleMenu(const vector<computer> &calc) : calc(calc) {};

    void listOptions() override {
        cout << "1.Afisarea informatiilor despre calculatoare." << '\n';
        cout << "2.Afisarea informatiilor pentru fiecare calculator fiind ordonate dupa ratingul final." << '\n';
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

    void option1() {
        for (auto &x: calc) {
            cout << x << "\n";
        }
    }

    void option2() {
        for (int i = 0; i < calc.size() - 1; ++i)
            for (int j = i + 1; j < calc.size(); ++j)
                if (calc[i].getRatingTot() > calc[j].getRatingTot())
                    swap(calc[i], calc[j]);
        for (auto &x: calc)
            cout << x << "\n";
    }

    void option3() {
        int k;
        cout << "Introdu numarul k:";
        cin >> k;
        if (k > 0 and k <= calc.size()) {
            for (int i = 0; i < calc.size() - 1; ++i)
                for (int j = i + 1; j < calc.size(); ++j)
                    if (calc[i].getRatingTot() > calc[j].getRatingTot())
                        swap(calc[i], calc[j]);
            for (int i = 0; i < k; ++i)
                cout << calc[i] << "\n";
        } else cout << "K invalid";
    }

    void option4() {
        int nr_infect = 0;
        for (auto &x: calc)
            if (!x.getVir().empty())
                nr_infect++;
        int x = (int) calc.size();
        if (nr_infect != 0)
            cout << "Exista " << (double(nr_infect) / double(x)) * 100 << "% calculatoare infectate.\n";
        else cout << "Nu exista calculatoare infectate.";
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
            } else if (option == 5) {
                break;
            }
        }
        cout << '\n' << "---------------------------------" << '\n' << "Programul s-a incheiat cu success";
    }

};

int main() {
//    vector<shared_ptr<Malawer>> vir = {
//            make_shared<Malawer>(Malawer(8.0,11, 2, 2019,"dncfkj",{"eax", "ebx"})),
//            make_shared<Malawer>( Malawer (9.50,
//                                           13, 4,1995,
//                                           "fdejsba",
//                                           {"eax"})),
//            make_shared<rootkit>(rootkit(9,2,3,2020,"dsjfjah",{"eax"},"svb",{"ipo"},{"si"}))
//    };
//    vector<computer>calculatoare;
//    calculatoare.emplace_back(vir);

// now we read n computers and for each computer we read m kinds of whatever viruses we want, then we create a menu with the vector of computers

    vector<computer> calculatoare;
    cin>>calculatoare;

    SimpleMenu menu(calculatoare);
    menu.mainLoop();

    return 0;
}