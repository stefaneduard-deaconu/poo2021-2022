#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>


using namespace std;

class Malware{
protected:
    float rating;
    int an, luna, zi;
    string nume, infectare;
    vector<string>registrii;
public:
    Malware(float rating, int an, int luna, int zi, const string &nume, const string &infectare,
            const vector<string> &registrii) : rating(rating), an(an), luna(luna), zi(zi), nume(nume),
                                               infectare(infectare), registrii(registrii) {}
    //Malware &operator=(const Malware &ob);

    //Malware();
    virtual istream &read(istream &fin) = 0;
    friend istream &operator>>(istream &fin, Malware& ob){
        return ob.read(fin);
    }


    Malware():registrii(){
        rating = 0;
        an = 0;
        luna = 0;
        zi = 0;
        nume = "";
        infectare = "";
    }

    float getRating() const {
        return rating;
    }
    int getAn() const {
        return an;
    }
    int getLuna() const {
        return luna;
    }
    int getZi() const {
        return zi;
    }
    const string &getNume() const {
        return nume;
    }
    const string &getInfectare() const {
        return infectare;
    }
    const vector<string> &getRegistrii() const {
        return registrii;
    }
    void setRating(float rating) {
        Malware::rating = rating;
    }
    void setAn(int an) {
        Malware::an = an;
    }
    void setLuna(int luna) {
        Malware::luna = luna;
    }
    void setZi(int zi) {
        Malware::zi = zi;
    }
    void setNume(const string &nume) {
        Malware::nume = nume;
    }
    void setInfectare(const string &infectare) {
        Malware::infectare = infectare;
    }
    void setRegistrii(const vector<string> &registrii) {
        Malware::registrii = registrii;
    }

    friend ostream &operator<<(ostream &os, const Malware &malware) {
        os << "rating: " << malware.rating << " an: " << malware.an << " luna: " << malware.luna << " zi: "
           << malware.zi << " nume: " << malware.nume << " infectare: " << malware.infectare;
        return os;
    }

    virtual double calcul() = 0;
};

/*
 * Malware::Malware() : rating(0){}
Malware & Malware::operator=(const Malware &ob) {
    rating = ob.rating;
    an = ob.an;
    luna = ob.luna;
    zi = ob.zi;
    nume = ob.nume;
    infectare = ob.infectare;
    registrii = ob.registrii;
    return *this;
}
*/
class Rootkit : virtual public Malware{
protected:
    vector<string>importuri;
    vector<string>stringbin;
public:
    const vector<string> &getImporturi() const {
        return importuri;
    }
    void setImporturi(const vector<string> &importuri) {
        Rootkit::importuri = importuri;
    }
    const vector<string> &getStringbin() const {
        return stringbin;
    }
    void setStringbin(const vector<string> &stringbin) {
        Rootkit::stringbin = stringbin;
    }

    Rootkit(float rating, int an, int luna, int zi, const string &nume, const string &infectare,
            const vector<string> &registrii, const vector<string> &importuri, const vector<string> &stringbin)
            : Malware(rating, an, luna, zi, nume, infectare, registrii), importuri(importuri), stringbin(stringbin) {}

    Rootkit():Malware(), importuri(), stringbin(){}

    virtual istream& read(istream &fin);

    friend ostream &operator<<(ostream &os, const Rootkit &rootkit);

    virtual double calcul();

};

istream & Rootkit::read(istream &fin) {
    cout<<"Data:\n";
    cout<<"Anul: ";
    fin>>an;
    int zileLuna[] = {0, 31, 28, 31, 30, 31 ,30, 31 ,31,30,31,30,31};
    cout<<"Luna:\n";
    while(true){
        try{
            fin>>luna;
            fin.get();
            if(luna < 1 || luna > 12){
                throw string("Luna este invalida!");
            }
            else{
                break;
            }
        }
        catch (string s){
            cout<< s << endl;
        }
    }
    cout<<"Zi:\n";
    while(true){
        try{
            fin>>zi;
            fin.get();
            if(zi < 1 || zi > zileLuna[luna]){
                throw string("Ziua este invalida!");
            }
            else{
                break;
            }
        }
        catch (string s){
            cout<<s<<endl;
        }
    }

    cout<<"Numele acestuia:\n";
    getline(fin, nume);
    cout<<"Metoda de infectare:\n";
    getline(fin, infectare);
    int numar;
    registrii.clear();
    cout<<"Numar registrii:\n";
    fin >> numar;
    fin.get();
    for(int i = 0; i <= numar - 1; i++){
        string registru;
        cout<<"Registrul:\n";
        getline(fin, registru);
        registrii.push_back(registru);
    }
    importuri.clear();
    stringbin.clear();
    cout<<"Numar importuri:\n";
    fin >> numar;
    fin.get();
    for(int i = 0; i <= numar - 1; i++){
        string import;
        cout<<"Importul:\n";
        getline(fin, import);
        importuri.push_back(import);
    }
    cout<<"Numar stringuri semnificative:\n";
    fin >> numar;
    fin.get();
    for(int i = 0 ; i <= numar - 1; i++){
        string stringbinar;
        cout<<"Stringul semnificativ:\n";
        getline(fin, stringbinar);
        stringbin.push_back(stringbinar);
    }
    return fin;
}

double Rootkit::calcul() {
    double suma = rating;
    for(int i = 0 ; i <= registrii.size() - 1; i++){
        if(registrii[i] == "HKLM-run" || registrii[i] == "HKCU-run"){
            suma = suma + 20;
            break;
        }
    }

    for(int i = 0; i <= stringbin.size() - 1; i++){
        if(stringbin[i] == "System Service Descriptor Table" || stringbin[i] == "SSDT" || stringbin[i] == "NtCreateFile"){
            suma = suma + 100;
            break;
        }
    }

    for(int i = 0 ; i <= importuri.size() - 1; i++){
        if(importuri[i] == "ntoskrnl.exe"){
            suma = suma * 2;
        }
    }
    return suma;
}

ostream &operator<<(ostream &os, const Rootkit &rootkit) {
    os << static_cast<const Malware &>(rootkit) << " stringbin: ";
    return os;
}


class Keylogger : virtual public Malware{
protected:
    vector<string>functii;
    vector<string>taste;
public:
    const vector<string> &getFunctii() const {
        return functii;
    }
    void setFunctii(const vector<string> &functii) {
        Keylogger::functii = functii;
    }
    const vector<string> &getTaste() const {
        return taste;
    }
    void setTaste(const vector<string> &taste) {
        Keylogger::taste = taste;
    }

    Keylogger();
    Keylogger(float rating, int an, int luna, int zi, const string &nume, const string &infectare,
              const vector<string> &registrii, const vector<string> &functii, const vector<string> &taste) : Malware(
            rating, an, luna, zi, nume, infectare, registrii), functii(functii), taste(taste) {}

    virtual istream& read(istream &fin);

    friend ostream &operator<<(ostream &os, const Keylogger &keylogger);

    virtual double calcul();
};

Keylogger::Keylogger() = default;

istream &Keylogger::read(istream &fin){
    cout<<"Data:\n";
    cout<<"Anul:\n";
    fin>>an;
    int zileLuna[] = {0, 31, 28, 31, 30, 31 ,30, 31 ,31,30,31,30,31};
    cout<<"Luna:\n";
    while(true){
        try{
            fin>>luna;
            fin.get();
            if(luna < 1 || luna > 12){
                throw string("Luna este invalida!");
            }
            else{
                break;
            }
        }
        catch (string s){
            cout<< s << endl;
        }
    }
    cout<<"Zi:\n";
    while(true){
        try{
            fin>>zi;
            fin.get();
            if(zi < 1 || zi > zileLuna[luna]){
                throw string("Ziua este invalida!");
            }
            else{
                break;
            }
        }
        catch (string s){
            cout<<s<<endl;
        }
    }

    cout<<"Numele acestuia:\n";
    getline(fin, nume);
    cout<<"Metoda de infectare:\n";
    getline(fin, infectare);
    int numar;
    registrii.clear();
    cout<<"Numar registrii:\n";
    fin >> numar;
    fin.get();
    for(int i = 1; i <= numar; i++){

        cout<<"Registrul:\n";
        string registru;
        getline(fin, registru);
        registrii.push_back(registru);
    }
    functii.clear();
    taste.clear();
    cout<<"Numar functii:\n";
    fin >> numar;
    fin.get();
    for(int i = 1; i <= numar; i++){
        string functie;
        cout<<"Functia:\n";
        getline(fin, functie);
        functii.push_back(functie);
    }
    cout<<"Numar taste:\n";
    fin >> numar;
    fin.get();
    for(int i = 0; i <= numar - 1; i++){
        string tastele;
        cout<<"Tastele apasate sunt: ";
        getline(fin, tastele);
        taste.push_back(tastele);
    }
    return fin;
}

double Keylogger::calcul(){

    double suma = rating;
    for(int i = 0 ; i <= registrii.size() - 1; i++){
        if(registrii[i] == "HKLM-run" || registrii[i] == "HKCU-run"){
            suma = suma + 20;
            break;
        }
    }
    for(int i = 0; i <= taste.size() - 1; i++){
        if(taste[i] == "[Up]" || taste[i] == "[Num Lock]" || taste[i] == "[Down]" || taste[i] == "[Right]" || taste[i] == "[UP]" || taste[i] == "[Left]" || taste[i] == "[PageDown]"){
            suma = suma + 10;
        }
    }
    for(int i = 0; i <= functii.size() - 1; i++){
        if(functii[i] == "CreateFile" || functii[i] == "OpenProcess" || functii[i] == "ReadFile" || functii[i] == "WriteFile" || functii[i] == "RegisterHotKey" || functii[i] == "SetWindowsHookEx"){
            suma = suma + 30;
        }
    }


    return suma;
}

ostream &operator<<(ostream &os, const Keylogger &keylogger) {
    os << static_cast<const Malware &>(keylogger) << " taste: ";
    return os;
}

class KernelKeylogger : public Rootkit, public Keylogger{
private:
    bool fisiere_asc, registrii_asc;
public:
    bool isFisiereAsc() const {
        return fisiere_asc;
    }
    void setFisiereAsc(bool fisiereAsc) {
        fisiere_asc = fisiereAsc;
    }
    bool isRegistriiAsc() const {
        return registrii_asc;
    }
    void setRegistriiAsc(bool registriiAsc) {
        registrii_asc = registriiAsc;
    }

    KernelKeylogger();
    KernelKeylogger(float rating, int an, int luna, int zi, const string &nume, const string &infectare,
                    const vector<string> &registrii, const vector<string> &functii, const vector<string> &taste,
                    bool fisiereAsc, bool registriiAsc) : Keylogger(rating, an, luna, zi, nume, infectare, registrii,
                                                                    functii, taste), fisiere_asc(fisiereAsc),
                                                          registrii_asc(registriiAsc) {}

    virtual istream &read(istream &fin);
    //virtual ostream &write(ostream &fout);

    virtual double calcul();
};

KernelKeylogger::KernelKeylogger() : fisiere_asc(false), registrii_asc(false) {}

double KernelKeylogger::calcul(){
    double suma = rating;
    for(int i = 0 ; i <= registrii.size() - 1; i++){
        if(registrii[i] == "HKLM-run" || registrii[i] == "HKCU-run"){
            suma = suma + 20;
            break;
        }
    }
    for(int i = 0; i <= taste.size() - 1; i++){
        if(taste[i] == "[Up]" || taste[i] == "[Num Lock]" || taste[i] == "[Down]" || taste[i] == "[Right]" || taste[i] == "[UP]" || taste[i] == "[Left]" || taste[i] == "[PageDown]"){
            suma = suma + 10;
            break;
        }
    }
    for(int i = 0; i <= functii.size() - 1; i++){
        if(functii[i] == "CreateFile" || functii[i] == "OpenProcess" || functii[i] == "ReadFile" || functii[i] == "WriteFile" || functii[i] == "RegisterHotKey" || functii[i] == "SetWindowsHookEx"){
            suma = suma + 30;
            break;
        }
    }
    for(int i = 0; i <= stringbin.size() - 1; i++){
        if(stringbin[i] == "System Service Descriptor Table" || stringbin[i] == "SSDT" || stringbin[i] == "NtCreateFile"){
            suma = suma + 100;
            break;
        }
    }

    for(int i = 0 ; i <= importuri.size() - 1; i++){
        if(importuri[i] == "ntoskrnl.exe"){
            suma = suma * 2;
        }
    }
    if(registrii_asc){
        suma = suma + 30;
    }
    if(fisiere_asc){
        suma = suma + 20;
    }

    return suma;
}

istream &KernelKeylogger::read(istream &fin){
    cout<<"Data:\n";
    cout<<"Anul:\n";
    fin>>an;
    int zileLuna[] = {0, 31, 28, 31, 30, 31 ,30, 31 ,31,30,31,30,31};
    cout<<"Luna:\n";
    while(true){
        try{
            fin>>luna;
            fin.get();
            if(luna < 1 || luna > 12){
                throw string("Luna este invalida!");
            }
            else{
                break;
            }
        }
        catch (string s){
            cout<< s << endl;
        }
    }
    cout<<"Zi:\n";
    while(true){
        try{
            fin>>zi;
            fin.get();
            if(zi < 1 || zi > zileLuna[luna]){
                throw string("Ziua este invalida!");
            }
            else{
                break;
            }
        }
        catch (string s){
            cout<<s<<endl;
        }
    }

    cout<<"Numele acestuia:\n";
    getline(fin, nume);
    cout<<"Metoda de infectare:\n";
    getline(fin, infectare);
    int numar;
    registrii.clear();
    cout<<"Numar registrii:\n";
    fin >> numar;
    fin.get();
    for(int i = 0; i <= numar - 1; i++){
        string registru;
        cout<<"Registrul:\n";
        getline(fin, registru);
        registrii.push_back(registru);
    }
    importuri.clear();
    stringbin.clear();
    cout<<"Numar importuri:\n";
    fin >> numar;
    fin.get();
    for(int i = 0; i <= numar - 1; i++){
        string import;
        cout<<"Importul:\n";
        getline(fin, import);
        importuri.push_back(import);
    }
    cout<<"Numar stringuri semnificative:\n";
    fin >> numar;
    fin.get();
    for(int i = 0 ; i <= numar - 1; i++){
        string stringbinar;
        cout<<"Stringul semnificativ:\n";
        getline(fin, stringbinar);
        stringbin.push_back(stringbinar);
    }
    functii.clear();
    taste.clear();
    cout<<"Numar functii:\n";
    fin >> numar;
    fin.get();
    for(int i = 0; i <= numar - 1; i++){
        string functie;
        cout<<"Functia:\n";
        getline(fin, functie);
        functii.push_back(functie);
    }
    cout<<"Numar taste:\n";
    fin >> numar;
    fin.get();
    for(int i = 0; i <= numar - 1; i++){
        string tastele;
        cout<<"Tastele apasate sunt: ";
        getline(fin, tastele);
        taste.push_back(tastele);
    }
    cout<<"Se ascund fisiere?(1 = TRUE; 0 = FALSE)!\n";
    fin>>fisiere_asc;
    cout<<"Se ascund registrii?(1 = TRUE; 0 = FALSE)!\n";
    fin>>registrii_asc;
    return fin;
}

class ransomware : public Malware{
private:
    int criptare;
    float obfuscare;
public:
    ransomware(float rating, int an, int luna, int zi, const string &nume, const string &infectare,
               const vector<string> &registrii, int criptare, float obfuscare) : Malware(rating, an, luna, zi, nume,
                                                                                         infectare, registrii),
                                                                                 criptare(criptare),
                                                                                 obfuscare(obfuscare) {}
    ransomware();

    int getCriptare() const;
    void setCriptare(int criptare);
    float getObfuscare() const;
    void setObfuscare(float obfuscare);

    virtual istream &read(istream &fin);

    friend ostream &operator<<(ostream &os, const ransomware &ransomware);

    virtual double calcul();
};

double ransomware::calcul(){
    double suma = rating;
    for(int i = 0 ; i <= registrii.size() - 1; i++){
        if(registrii[i] == "HKLM-run" || registrii[i] == "HKCU-run"){
            suma = suma + 20;
            break;
        }
    }
    suma = suma + criptare;
    suma = suma + obfuscare;

    return suma;
}

istream &ransomware::read(istream &fin) {
    cout<<"Data:\n";
    cout<<"Anul:\n";
    fin>>an;
    int zileLuna[] = {0, 31, 28, 31, 30, 31 ,30, 31 ,31,30,31,30,31};
    cout<<"Luna:\n";
    while(true){
        try{
            fin>>luna;
            fin.get();
            if(luna < 1 || luna > 12){
                throw string("Luna este invalida!");
            }
            else{
                break;
            }
        }
        catch (string s){
            cout<< s << endl;
        }
    }
    cout<<"Zi:\n";
    while(true){
        try{
            fin>>zi;
            fin.get();
            if(zi < 1 || zi > zileLuna[luna]){
                throw string("Ziua este invalida!");
            }
            else{
                break;
            }
        }
        catch (string s){
            cout<<s<<endl;
        }
    }

    cout<<"Numele acestuia:\n";
    getline(fin, nume);
    cout<<"Metoda de infectare:\n";
    getline(fin, infectare);
    int numar;
    registrii.clear();
    cout<<"Numar registrii:\n";
    fin >> numar;
    fin.get();
    for(int i = 0; i <= numar - 1; i++){
        string registru;
        cout<<"Registrul:\n";
        getline(fin, registru);
        registrii.push_back(registru);
    }
    cout<<"Ratingul de cripatare este:\n";
    fin >> criptare;
    cout<<"Ratingul de obfuscare:\n";
    fin >> obfuscare;
    return fin;
}

ransomware::ransomware() : criptare(0), obfuscare(0) {}

int ransomware::getCriptare() const {
    return criptare;
}
void ransomware::setCriptare(int criptare) {
    ransomware::criptare = criptare;
}
float ransomware::getObfuscare() const {
    return obfuscare;
}
void ransomware::setObfuscare(float obfuscare) {
    ransomware::obfuscare = obfuscare;
}

ostream &operator<<(ostream &os, const ransomware &ransomware) {
    os << static_cast<const Malware &>(ransomware) << " criptare: " << ransomware.criptare << " obfuscare: "
       << ransomware.obfuscare;
    return os;
}


class PC{
private:
    static unsigned int ID;
    unsigned int cod;
    double rating_f;
    //vector<Malware*>lista;
    vector<shared_ptr<Malware>>lista;
public:
    PC();

    const vector<Malware*> &getVirusi() const;
    explicit PC(const vector<shared_ptr<Malware>>&lista);

    int getCod() const;
    void setCod(int cod);

    double getRatingF() const;
    void setRatingF(double ratingF);

    friend istream &operator>>(istream &fin, PC &c);

    friend ostream &operator<<(ostream &os, const PC &pc);

    //virtual istream &read(istream &fin, PC &c);
    friend bool operator<(PC &a, PC &b);
};
/*
//istream &PC::read(istream &fin, PC &c) {
istream& operator>>(istream &fin, PC &c){
    int numar;
    cout<<"Numar virusi:\n";
    fin >> numar;
    fin.get();
    for(int i = 0; i <= numar - 1; i++){
        cout<<"Citire virus:\n";
        cout<<"Tipuri de virusi: 1 - Rootkit, 2 - Keylogger, 3 - KernelKeylogger, 4 - Ransomware  : \n";
        int tipVirus = 0;
        fin >> tipVirus;
        while(tipVirus < 1 || tipVirus > 4){
            cout<<"Virus incorect!";
            fin >> tipVirus;
        }
        shared_ptr <Malware> malware;
        if(tipVirus == 1){
            malware = make_shared<Rootkit>();
        }
        else if(tipVirus == 2){
            malware = make_shared<Keylogger>();
        }
        else if(tipVirus == 3){
            malware = make_shared<KernelKeylogger>();
        }
        else if(tipVirus == 4){
            malware = make_shared<ransomware>();
        }
        fin >> malware;
    }

}


 ---------------------------------------------------------------

istream& operator>>(istream& fin, PC& c){
    int numar;
    while(true){
        try{

            cout << "Numar virusuri:\n";
            fin >> numar;
            fin.get();
            if(numar < 0)
                throw string("Nr invalid!");
            else
                break;
        }
        catch (string s){
            cout << s << endl;
        }
    }
    for(int i = 0; i <= numar - 1; ++i){
        string tipVirus;
        Malware *p = nullptr;
        while(true){
            try{
                cout << "Introduceti tipul virsurului - root sau key sau ker sau ran \n";
                getline(fin, tipVirus);
                if(tipVirus == "root"){
                    p = new Rootkit;
                    break;
                }
                else if(tipVirus == "key"){
                    p = new Keylogger;
                    break;
                }else if(tipVirus == "ker"){
                    p = new KernelKeylogger;
                    break;
                }
                else if(tipVirus == "ran"){
                    p = new ransomware;
                    break;
                }

                else throw string("Tip invalid!");
            }
            catch(string s){
                cout << s << '\n';
            }
        }
        fin >> *p;
        c.rating_f += p->calcul();
        c.lista.push_back(p);
    }
    return fin;

}
*/
unsigned int PC::ID = 0;
bool operator<(PC &a, PC &b){
    return a.rating_f < b.rating_f;
}

//const vector<Malware*> &PC::getVirusi() const {
//    return lista;
//}
istream& operator>>(istream &fin, PC &c){
    int numar;
    cout<<"Numar virusi:\n";
    fin >> numar;
    fin.get();
    for(int i = 0; i <= numar - 1; i++){
        cout<<"Citire virus:\n";
        cout<<"Tipuri de virusi: 1 - Rootkit, 2 - Keylogger, 3 - KernelKeylogger, 4 - Ransomware  : \n";
        int tipVirus = 0;
        fin >> tipVirus;
        while(tipVirus < 1 || tipVirus > 4){
            cout<<"Virus incorect!";
            fin >> tipVirus;
        }
        shared_ptr <Malware> malware;
        if(tipVirus == 1){
            malware = make_shared<Rootkit>();
        }
        else if(tipVirus == 2){
            malware = make_shared<Keylogger>();
        }
        else if(tipVirus == 3){
            malware = make_shared<KernelKeylogger>();
        }
        else if(tipVirus == 4){
            malware = make_shared<ransomware>();
        }
        fin >> *malware;
        cout<<endl<<endl<<malware->calcul()<<endl<<endl;
        c.rating_f += malware->calcul();
        c.lista.push_back(malware);
    }

    return fin;
}


PC::PC() : cod(++ID), rating_f(0){}
PC::PC(const vector<shared_ptr<Malware>>&lista) : cod(++ID), lista(lista), rating_f(0) {}


int PC::getCod() const {
    return cod;
}
void PC::setCod(int cod) {
    PC::cod = cod;
}

double PC::getRatingF() const {
    return rating_f;
}
void PC::setRatingF(double ratingF) {
    rating_f = ratingF;
}

ostream &operator<<(ostream &os, const PC &pc) {
    os << "cod: " << pc.cod << " rating_f: " << pc.rating_f<<"  ";
    return os;
}


class Meniu{
private:
    vector<PC>computer;
public:
    Meniu();

    Meniu(const vector<PC> &computer);

    static void ListaOptiuni();
    static int chooseOption(int first, int last);
    void MainLoop();
    void citireCalculatoare();
    void afisareCalculatoare();
    void afisareCalculatoareSortate();
    void afisarekCalculatoareSortate();
    void procentComputereInfectate();
};
void Meniu::ListaOptiuni() {
    cout << "1. Citeste calculatoare.\n";
    cout << "2. Afiseaza calculatoarele.\n";
    cout << "3. Afiseaza calculatoarele ordonate dupa ratingul final.\n";
    cout << "4. Afiseaza primele k calculatoare ordonate dupa ratingul final.\n";
    cout << "5. Afiseaza procentul de calculatoare infectate din firma.\n";
    cout << "6. Iesire.\n";
}

int Meniu::chooseOption(int first, int last) {
    int optiune = -1;
    while (optiune < first || optiune > last) {
        cout << endl;
        ListaOptiuni();
        cout << "Alegeti un numar intre " << first << " si " << last << " pentru o operatie:";
        cin >> optiune;
        cin.get();
    }
    return optiune;
}


void Meniu::MainLoop(){
    while (true) {
        int option = chooseOption(1, 6);
        if (option == 1) {
            citireCalculatoare();
        } else if (option == 2) {
            afisareCalculatoare();
        } else if (option == 3) {
            afisareCalculatoareSortate();
        } else if (option == 4) {
            afisarekCalculatoareSortate();
        } else if (option == 5) {
            procentComputereInfectate();
        } else if (option == 6) {
            break;
        }
    }
    cout << "\n---------------------------------\nProgramul s-a terminat.";
}

void Meniu::citireCalculatoare() {
    cout << "Numarul de calculatoare:\n";
    int n;
    cin >> n;
    cin.get();
    for (int i = 1; i <= n; i++){
        cout << "Citire calculator:\n";
        PC c;
        cin >> c;
        computer.push_back(c);
    }
}

void Meniu::afisareCalculatoare() {
    if (computer.empty())
        cout << "Nu s-au introdus calculatoare momentan\n";
    else {
        for (auto &calculator: computer)
            cout << calculator;
    }
}

void Meniu::afisareCalculatoareSortate() {
    if (computer.empty())
        cout << "Nu s-au introdus calculatoare momentan.\n";
    else {
        vector<PC> computers = computer;

        for (int i = 0; i < computers.size() - 1; ++i)
            for (int j = i + 1; j < computers.size(); ++j)
                if (computers[i] < computers[j])
                    swap(computers[i], computers[j]);
        for (auto &c : computers)
            cout << c;
    }
}

void Meniu::afisarekCalculatoareSortate() {
    if (computer.empty())
        cout << "Nu s-au introdus calculatoare momentan.\n";
    else {
        cout << "k=";
        int k;
        cin >> k;
        while (k > computer.size()) {
            cout << "k trebuie sa fie mai mic sau egal decat numarul de calculatoare(" << computer.size() << ")\nk=";
            cin >> k;
        }
        vector<PC> computers = computer;

        for (int i = 0; i < computers.size() - 1; ++i)
            for (int j = i + 1; j < computers.size(); ++j)
                if (computers[i] < computers[j])
                    swap(computers[i], computers[j]);
        for (int i = 0; i < k; ++i)
            cout << computers[i];
    }
}

void Meniu::procentComputereInfectate() {
    if (computer.empty())
        cout << "Nu s-au introdus calculatoare momentan.\n";
    else {
        int computereInfectateCNT = 0;
        int totalComputere = computer.size();

        for (int i = 0; i < totalComputere; ++i)
            if (computer[i].getRatingF())
                computereInfectateCNT++;

        double procent = double(computereInfectateCNT) / totalComputere * 100;
        cout << fixed << setw(2) << procent << "% din calculatoarele firmei sunt infectate.\n";
    }
}

Meniu::Meniu(const vector<PC> &computer) : computer(computer) {}

Meniu::Meniu() = default;

int main() {

    Meniu meniul;
    meniul.MainLoop();

    return 0;
}
