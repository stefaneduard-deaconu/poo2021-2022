//CRIVOI CARLA
//143
//CLION

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
//structura care retinr data
struct  Data{
    int zi,luna,an;
};
// clasa mareware cu atributele specificate
class Malware{
protected:
    double raiting=0;
    Data data;
    string nume,metoda="unknow";
    vector<string> registru;
public:
    Malware(){
    }
    // constructor gol
    Malware(double raiting, const Data &data, const string &nume, const string &metoda, const vector <string> &registru)
            : raiting(raiting), data(data), nume(nume), metoda(metoda), registru(registru) {}
    // constructor cu toti parametrii
    virtual ~Malware() {
    }// destructor

    //set+get pt toate variabilele
    double getRaiting() const {
        return raiting;
    }

    const Data &getData() const {
        return data;
    }

    const string &getNume() const {
        return nume;
    }

    const string &getMetoda() const {
        return metoda;
    }

    const vector<string> &getRegistru() const {
        return registru;
    }

    void setRaiting(double raiting) {
        Malware::raiting = raiting;
    }

    void setData(const Data &data) {
        Malware::data = data;
    }

    void setNume(const string &nume) {
        Malware::nume = nume;
    }

    void setMetoda(const string &metoda) {
        Malware::metoda = metoda;
    }

    void setRegistru(const vector<string> &registru) {
        Malware::registru = registru;
    }
    //citirea unui obiect de tip malware
    friend istream &operator>>(istream &is,Malware &malware);
    //afisarea unui obiect de tip malware
    friend ostream &operator<<(ostream &os,const Malware &malware);

};
istream &operator>>(istream &is, Malware &malware){
    cout<<"Ziua, luna anul sunt:";
    is>>malware.data.zi>>malware.data.luna>>malware.data.an;
//    cout<<"Numele:"; is>>malware.nume;
    int numar;
    cout<<" Se cunoaste medoda de infectare? 1- da, 0-nu"<<endl;
    is>>numar;
    if(numar== 1){
        cout<<"Care este?";
        string met;
        is>>met;
        malware.setMetoda(met);
    }
    cout<<"Nr de registrii modificati: ";
    int item;
    is>>item;
    cout<<"Registrii modificati sunt: ";
    string registr;
    for(int i=0;i<item;i++){
            is>>registr;
            malware.registru.push_back(registr);
    }
    return is;

}
ostream &operator<<(ostream &os,const Malware &malware){
   os<<"Raitingul este:"<<malware.raiting<<endl<<"Numele este "<<malware.nume<<" care s-a infectat pe data "<<malware.data.zi<<'.'<<malware.data.luna<<'.'<<malware.data.an<<endl;
   os<<" Metoda de infectare este "<<malware.metoda;
   os<<"Au fost afectati urnmatorii registrii: ";
   for( auto reg : malware.registru)
       os<<reg<<' ';
    return os;
}


// clasa Rootkit cu atributele specifice
class Rootkit: virtual public Malware{
protected:
    vector<string> import,binar;
public:
    Rootkit(){}// constructoir gol
    Rootkit(double raiting, const Data &data, const string &nume, const string &metoda, const vector<string> &registru,
            const vector<string> &anImport, const vector<string> &binar) : Malware(raiting, data, nume, metoda,
                                                                                   registru), import(anImport),
                                                                           binar(binar) {}
    // constructor cu toti parametrii
    virtual ~Rootkit() {
    } //destructor
    void setAnImport(const vector<string> &anImport) {
        import = anImport;
    }

    void setBinar(const vector<string> &binar) {
        Rootkit::binar = binar;
    }
    //seteruri pt toate variabilele
    //get pt toate var
    const vector<string> &getAnImport() const {
        return import;
    }

    const vector<string> &getBinar() const {
        return binar;
    }
    virtual double calculeaza();
    //citirea unui obiect de tip Rootkit
    friend istream &operator>>(istream &is,Rootkit &rootkit);
    //afisarea unui obiect de tip Rootkit
    friend ostream &operator<<(ostream &os,const Rootkit &rootkit);

};


istream &operator>>(istream &is, Rootkit &rootkit){

    cout<<"Nr de importuri : ";
    int item;
    is>>item;
    cout<<"Importurile sunt: ";
    string imp;
    for(int i=0;i<item;i++){
        is>>imp;
        rootkit.import.push_back(imp);
    }
    cout<<"Nr de stringuri semnificative: ";
    is>>item;
    cout<<"Stringurile semnificative  sunt: ";
    string str;
    for(int i=0;i<item;i++){
        is>>str;
        rootkit.binar.push_back(str);
    }
    return is;

}
ostream &operator<<(ostream &os,const Rootkit &rootkit){
    os<<"Importurile sunt ";
    for( auto reg :rootkit.import)
        os<<reg<<' ';
    os<<"Stringurile semnificative sunt ";
    for( auto reg :rootkit.binar)
        os<<reg<<' ';
    return os;
}
////////////////////////////////////////
double Rootkit::calculeaza() {
    double val = getRaiting();
    for(int i =0;i < getRegistru().size(); ++i)
        if(getRegistru()[i] == "“HKLM-run" || getRegistru()[i] == "HKCU-run"){
            val += 20;
            break;
        }

    for(int i = 0;i < binar.size(); ++i)
        if(binar[i] == "System Service Descriptor Table" || binar[i] == "SSDT" || binar[i] == "NtCreateFile" ){
            val += 100;
            break;
        }
    for(int i = 0;i < import.size(); ++i)
        if(import[i] == "ntoskrnl.exe"){
            val = val *2;
            break;
        }
    return val;
}

//clasa keylogger
// constructor gol, constructor cu toate variabilele, destructor, set+get pt toate variabilele
class Keylogger:virtual public Malware{
protected:
    vector<string> functie, tasta;
public:
    Keylogger(){

    }
    Keylogger(double raiting, const Data &data, const string &nume, const string &metoda,
              const vector<string> &registru, const vector<string> &functie, const vector<string> &tasta) : Malware(
            raiting, data, nume, metoda, registru), functie(functie), tasta(tasta) {}

    virtual ~Keylogger() {

    }

    const vector<string> &getFunctie() const {
        return functie;
    }

    const vector<string> &getTasta() const {
        return tasta;
    }

    void setFunctie(const vector<string> &functie) {
        Keylogger::functie = functie;
    }

    void setTasta(const vector<string> &tasta) {
        Keylogger::tasta = tasta;
    }
    //citirea unui obiect de tip Keylogger
    friend istream &operator>>(istream &is,Keylogger &key);
    //afisarea unui obiect de tip Keylogger
    friend ostream &operator<<(ostream &os,const Keylogger &key);
    virtual double calculeaza();

};

istream &operator>>(istream &is, Keylogger &key){

    cout<<"Nr de functii : ";
    int item;
    is>>item;
    cout<<"Functii sunt: ";
    string imp;
    for(int i=0;i<item;i++){
        is>>imp;
        key.functie.push_back(imp);
    }
    cout<<"Nr de taste specifice: ";
    is>>item;
    cout<<"Tastele specifice sunt: ";
    string str;
    for(int i=0;i<item;i++){
        is>>str;
        key.tasta.push_back(str);
    }
    return is;

}
ostream &operator<<(ostream &os,const Keylogger &key){
    os<<"Functii sunt ";
    for( auto reg :key.functie)
        os<<reg<<' ';
    os<<endl;
    os<<"Tastele specifice sunt ";
    for( auto reg :key.tasta)
        os<<reg<<' ';
    os<<endl;
    return os;
}

double Keylogger::calculeaza() {
    double val = raiting;
    for(int i =0;i < registru.size(); ++i)
        if(registru[i] == "“HKLM-run" || registru[i] == "HKCU-run"){
            val += 20;
            break;
        }
    for(int i = 0;i < functie.size(); ++i)
        if(functie[i] == "CreateFileW" || functie[i] == "OpenProcess" || functie[i] == "ReadFile" || functie[i] =="WriteFile" || functie[i] == "RegisterHotKey"  || functie[i] == "SetWindowsHookEx" )
            val += 30;
    for(int i = 0;i < tasta.size(); ++i)
        if(tasta[i] == "Up" || tasta[i] == "Num Lock" || tasta[i] == "Down" || tasta[i] =="Right" || tasta[i] == "UP"  || tasta[i] == "Left" || tasta[i] == "PageDown" )
            val += 10;
    return val;
}
//clasa kernelKeylogger
// constructor gol, constructor cu toate variabilele, destructor, set+get pt toate variabilele
class KernelKeylogger: public Rootkit,public Keylogger{
protected:
    bool fctasc=0,regasc=0;
public:
    KernelKeylogger(){}
    KernelKeylogger(double raiting, const Data &data, const string &nume, const string &metoda,
                    const vector<string> &registru, const vector<string> &anImport, const vector<string> &binar,
                    double raiting1, const Data &data1, const string &nume1, const string &metoda1,
                    const vector<string> &registru1, const vector<string> &functie, const vector<string> &tasta,
                    bool fctasc, bool regasc);

    virtual ~KernelKeylogger();

    bool isFctasc() const;

    void setFctasc(bool fctasc);

    bool isRegasc() const;

    void setRegasc(bool regasc);

    KernelKeylogger(bool fctasc, bool regasc);

    //citirea unui obiect de tip KernelKeylogger
    friend istream &operator>>(istream &is,KernelKeylogger &key);
    //afisarea unui obiect de tip KernelKeylogger
    friend ostream &operator<<(ostream &os,const KernelKeylogger &key);
    double calculeaza();
};

istream &operator>>(istream &is, KernelKeylogger &key){

    cout<<"Exista functii ascunse: 1-da 0-nu ";
    bool item;
    is>>item;
    key.setFctasc(item);
    cout<<"Exista registrii ascunsi: 1-da 0-nu ";
    is>>item;
    key.setRegasc(item);
    return is;

}
ostream &operator<<(ostream &os,const KernelKeylogger &key){
    if(key.fctasc==0) os<<"Nu exista functii ascunse"<<endl;
    else os<<"Exista functii ascunse"<<endl;
    if(key.regasc==0) os<<"Nu exista registrii ascunsi"<<endl;
    else os<<"Exista registrii ascunsi"<<endl;
    return os;
}
double KernelKeylogger::calculeaza() {
    double val = raiting;
    for(int i =0;i < registru.size(); ++i)
        if(registru[i] == "HKLM-run" || registru[i] == "HKCU-run"){
            val += 20;
            break;
        }
    for(int i = 0;i < binar.size(); ++i)
        if(binar[i] == "System Service Descriptor Table" || binar[i] == "SSDT" || binar[i] == "NtCreateFile" ){
            val += 100;
            break;
        }
    for(int i = 0;i < import.size(); ++i)
        if(import[i] == "ntoskrnl.exe"){
            val = val *2;
            break;
        }
    for(int i = 0;i < functie.size(); ++i)
        if(functie[i] == "CreateFileW" || functie[i] == "OpenProcess" || functie[i] == "ReadFile" || functie[i] =="WriteFile" || functie[i] == "RegisterHotKey"  || functie[i] == "SetWindowsHookEx" )
            val += 30;
    for(int i = 0;i < tasta.size(); ++i)
        if(tasta[i] == "Up" || tasta[i] == "Num Lock" || tasta[i] == "Down" || tasta[i] =="Right" || tasta[i] == "UP"  || tasta[i] == "Left" || tasta[i] == "PageDown" )
            val += 10;
    if(regasc==true)
        val += 30;
    if(fctasc==1)
        val += 20;
    return val;
}

bool KernelKeylogger::isFctasc() const {
    return fctasc;
}

void KernelKeylogger::setFctasc(bool fctasc) {
    KernelKeylogger::fctasc = fctasc;
}

bool KernelKeylogger::isRegasc() const {
    return regasc;
}

void KernelKeylogger::setRegasc(bool regasc) {
    KernelKeylogger::regasc = regasc;
}

KernelKeylogger::KernelKeylogger(double raiting, const Data &data, const string &nume, const string &metoda,
                                 const vector<string> &registru, const vector<string> &anImport,
                                 const vector<string> &binar, double raiting1, const Data &data1, const string &nume1,
                                 const string &metoda1, const vector<string> &registru1, const vector<string> &functie,
                                 const vector<string> &tasta, bool fctasc, bool regasc) : Rootkit(raiting, data, nume,
                                                                                                  metoda, registru,
                                                                                                  anImport, binar),
                                                                                          Keylogger(raiting1, data1,
                                                                                                    nume1, metoda1,
                                                                                                    registru1, functie,
                                                                                                    tasta),
                                                                                          fctasc(fctasc),
                                                                                          regasc(regasc) {}

KernelKeylogger::~KernelKeylogger() {

}

KernelKeylogger::KernelKeylogger(bool fctasc, bool regasc) : fctasc(fctasc), regasc(regasc) {}


//clasa Randware
// constructor gol, constructor cu toate variabilele, destructor, set+get pt toate variabilele
class Randware:public Malware{
private:
    int ratcrip,ratobfuscare;
public:
    Randware(){}
    Randware(double raiting, const Data &data, const string &nume, const string &metoda, const vector<string> &registru,
             int ratcrip, int ratobfuscare) : Malware(raiting, data, nume, metoda, registru), ratcrip(ratcrip),
                                              ratobfuscare(ratobfuscare) {}

    virtual ~Randware() {

    }

    int getRatcrip() const {
        return ratcrip;
    }

    void setRatcrip(int ratcrip) {
        Randware::ratcrip = ratcrip;
    }

    int getRatobfuscare() const {
        return ratobfuscare;
    }

    void setRatobfuscare(int ratobfuscare) {
        Randware::ratobfuscare = ratobfuscare;
    }
    //citirea unui obiect de tip Randware
    friend istream &operator>>(istream &is,Randware &key);
    //afisarea unui obiect de tip Randware
    friend ostream &operator<<(ostream &os,const Randware &key);
    double calculeaza();
};

istream &operator>>(istream &is, Randware &key){

    cout<<"Raitingul de criptare este: ";
    is>>key.ratcrip;
    cout<<endl<<"Procentul de obfuscare este :";is>>key.ratobfuscare;
    cout<<endl;

    return is;

}
ostream &operator<<(ostream &os,const Randware &key){
    cout<<"Raitingul de criptare este: ";
    os<<key.ratcrip;
    cout<<endl<<"Procentul de obfuscare este :";os<<key.ratobfuscare;
    cout<<endl;
    return os;
}

double Randware::calculeaza() {
    double val = ratobfuscare + ratcrip;
    for(int i =0;i < registru.size(); ++i)
        if(registru[i] == "“HKLM-run" || registru[i] == "HKCU-run"){
            val += 20;
            break;
        }
    return val;
}

// clasa calculatoare cu constructor gol, constructor cu toti parametrii, destructor, sett+gett pt toate variabilele
class Calculator{
private:
    int id=0;
    vector<Malware*> virusi;
    double  ratingfin=0;
public:
    Calculator(){}
    Calculator(int id, const vector<Malware *> &virusi, double ratingfin) : id(id), virusi(virusi),
                                                                            ratingfin(ratingfin) {}

    virtual ~Calculator() {

    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        Calculator::id = id;
    }

    const vector<Malware *> &getVirusi() const {
        return virusi;
    }

    void setVirusi(const vector<Malware *> &virusi) {
        Calculator::virusi = virusi;
    }

    double getRatingfin() const {
        return ratingfin;
    }

    void setRatingfin(double ratingfin) {
        Calculator::ratingfin = ratingfin;
    }
    //citirea unui obiect de tip Calculatoare
    friend istream &operator>>(istream &is,Calculator &pc);
    //afisarea unui obiect de tip Calculatoare
    friend ostream &operator<<(ostream &os,const Calculator &pc);

};


istream &operator>>(istream &is, Calculator &pc){
    cout<<"Nr de visrusi este "<<endl;
    int nr;
    is>>nr;
    int tip;
    Malware *p = nullptr;
    for(int i=0;i<nr;i++){
        cout<<" Ce tip de virus este ? 1-Rootkit 2-Keylogger 3- Kernel-Keylogger  4-Ransomware "<< endl;
        is>>tip;
        if(tip==1){
            p = new Rootkit;
            is>>*p;
            p->setNume("Rootkit");
            pc.virusi.push_back(p);

        }
        else if(tip==2){
            p = new Keylogger;
            is>>*p;
            p->setNume("Keylogger");
            pc.virusi.push_back(p);
        }
        else if(tip==3){
            p = new KernelKeylogger ;
            is>>*p;
            p->setNume("KernelKeylogger");
            pc.virusi.push_back(p);
        }
        else
        {
            p = new Randware;
            is>>*p;
            p->setNume("Randware");
            pc.virusi.push_back(p);
        }

    }
    cout<<endl;

    return is;

}
ostream &operator<<(ostream &os,const Calculator &pc){
    cout<<"Id este ";os<<pc.id<<endl;
    cout<<"Raitingul final este: ";
    os<<pc.ratingfin<<endl;
    cout<<"Lista de virusi este ";
    for(auto vir: pc.virusi)
    {
//        if(vir == new Rootkit) cout<<"Rootkit";
//        if(vir == new Keylogger) cout<<"Keylogger";
//        if(vir == new KernelKeylogger) cout<<"KernelKeylogger";
//        if(vir == new Randware) cout<<"Randware";
         cout<<*vir;
    }
    cout<<endl;
    return os;
}

vector<Calculator> pc;

////////////////////////////////////////////meniu//////////////////
class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};


void option1() {
    cout << "1. Afisare informatii pentru fiecare calculator."<< '\n';
    for(auto calculator : pc)
        cout<<calculator<<endl;

}

void option2() {
    cout << "2. Afisare informatii pentru fiecare calculator ordonate dupa raiting." << '\n';
    for(int i = 0;i < pc.size(); ++i)
        for(int j = i+1;j < pc.size(); ++j)
            if(pc[i].getRatingfin() > pc[j].getRatingfin())
                swap(pc[i],pc[j]);

    for(int i = 0;i < pc.size(); ++i)
        cout << pc[i] << '\n';
    cout << '\n';
}

void option3() {
    int k;
    cout << "3. Afisarea primelor k calculatoare ordonate dupa ratingul final." << '\n';
    cout<<" k este "; cin>>k;
    for(int i = 0;i < pc.size(); ++i)
        for(int j = i+1;j < pc.size(); ++j)
            if(pc[i].getRatingfin() > pc[j].getRatingfin())
                swap(pc[i],pc[j]);
    for(int i = 0 ;i < k && i < pc.size(); ++i)
        cout << pc[i] << '\n';
    cout << '\n';
}
void option4() {
    cout << "4. Afisarea procentului de computere infectate din firma" << '\n';
    double p;
    int nr = 0;
    for(int i = 0;i < pc.size();++i)
        if(pc[i].getRatingfin()!= 0)
            ++nr;
    if(pc.size()) {
        p = 100.0 * ((double) nr) / ((double) pc.size());
        cout << "Procent: "<< p << '\n';
    }
    else
        cout << "Nu exista calculatoare\n";
}

class SimpleMenu : public BaseMenu {
public:
    void listOptions() override
    {
            cout << "1. Afisare informatii pentru fiecare calculator." << '\n';
            cout << "2. Afisare informatii pentru fiecare calculator ordonate dupa raiting." << '\n';
            cout << "3. Afisarea primelor k calculatoare ordonate după ratingul final." << '\n';
            cout << "4. Afisarea procentului de computere infectate din firmă." << '\n';
            cout << "5. Iesire." << '\n';
    }

    int chooseOption(int first, int last) override {
        int option = -1;
        while (option < first || option > last) {
            cout << '\n';
            cout << "Pentru a rula comanda, alegeți un numar intre "
                 << first << " și " << last << '\n';
            listOptions();
            cout << "Alegere: ";
            cin >> option;
        }
        return option;
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
            }
            else if (option == 5) {
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
    cout << " Care este nr de calculatoare?"<<endl;
    int nr;
    cin >> nr;
    for (int i = 0; i < nr; i++) {
        Calculator calc;
        cin >> calc;
        calc.setId(i+1);
        pc.push_back(calc);
    }
    SimpleMenu menu;
    menu.mainLoop();
}