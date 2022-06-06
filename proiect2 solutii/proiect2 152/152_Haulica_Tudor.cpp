/*Haulica Tudor GRUPA 152
 * Compilator:GNU 11.2.0
 * Profesor:Stefan-Eduard Deaconu
 */

#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <variant>
#include <memory>
#include "util/Iobase.h"
#include "util/functions.h"
#include <typeinfo>
#include <algorithm>
using namespace std;

vector <string> badBins = {"System Service Descriptor Table", "SSDT", "NtCreateFile"};
vector <string> badKeys = {"[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
vector <string> badFunctions = {"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};


class Malware:  public IoBase {
protected:
  float rating=0;
  int zi,luna,an;
  string nume;
  string metoda;
  vector <string> registrii  ;

public:
    Malware(float rating, int zi, int luna, int an, const string &nume, const string &metoda,
            const vector<string> &registrii) : rating(rating), zi(zi), luna(luna), an(an), nume(nume), metoda(metoda),
                                               registrii(registrii) {}
    Malware() = default;

     istream &read(istream &is) override {
//        cout<<"Rating Malware: ";
//        is>>rating;
        cout<<"Zi: ";
        is>>zi;
        cout<<"Luna: ";
        is>>luna;
        cout<<"An: ";
        is>>an;
        is.get();
        cout<<"Nume Malware:\n";
        getline(cin,nume);
        cout<<"Metoda Infectare(Rootkit/Keylogger/KernelKeylogger/Ransomware): ";
        is>>metoda;
        cout<<"Numar registrii: ";
        string reg;
        int nrreg;
        is>>nrreg;
//         registrii = vector <string>(nrreg);
        cout<<"Registrii: ";
        for ( int i = 0 ; i < nrreg  ; i++ )
        { is>>reg;
            registrii.push_back(reg);
        }
        return is;
    }
    ostream &write(ostream &os) const override {
        cout<<"Zi: " << zi<< "\n";
        cout<<"Luna: "<< luna<< "\n";
        cout<<"An: "<< an <<"\n";
        cout<<"Nume: "<<nume <<"\n";
        cout<<"Metoda infectare: "<< metoda << "\n";
        cout<<"Registrii: ";
        for(auto &registru: registrii)
            cout<<registru<<" ";
        cout<<"\n";
        return os;
    }
     virtual float ImpactRating() {
        for (auto& i : registrii) {
            if (i == "HKLM-run" || i == "HKCU-run") {
               rating += 20;
            }
        }
        return rating;
    }


    float getRating() const {
        return rating;
    }

    int getZi() const {
        return zi;
    }

    int getLuna() const {
        return luna;
    }

    int getAn() const {
        return an;
    }

    const string &getNume() const {
        return nume;
    }

    const string &getMetoda() const {
        return metoda;
    }

    const vector<string> &getRegistrii() const {
        return registrii;
    }


    void setRating(float rating) {
        Malware::rating = rating;
    }

    void setZi(int zi) {
        Malware::zi = zi;
    }

    void setLuna(int luna) {
        Malware::luna = luna;
    }

    void setAn(int an) {
        Malware::an = an;
    }

    void setNume(const string &nume) {
        Malware::nume = nume;
    }

    void setMetoda(const string &metoda) {
        Malware::metoda = metoda;
    }

    void setRegistrii(const vector<string> &registrii) {
        Malware::registrii = registrii;
    }

};
class rootkit :virtual public Malware
{
protected:
    vector <string> importuri;
   vector <string> liststring;
public:


     rootkit(float rating, int zi, int luna, int an, const string &nume, const string &metoda,
            const vector<string> &registrii, const vector<string> &importuri, const vector<string> &liststring)
            : Malware(rating, zi, luna, an, nume, metoda, registrii), importuri(importuri), liststring(liststring) {}
    rootkit() = default;

    istream &read(istream &is) override
    {
        Malware::read(is);
        int nrimp,nrstring;
        cout<<"Numar importuri: ";
        is>>nrimp;
        importuri = vector <string>(nrimp);

        cout<<"Citire importuri: ";
        for (int i = 0 ; i < nrimp ; i++ )
        {    is>>importuri[i];
        }

        cout<<"Numar stringuri: ";
        is>> nrstring;
        liststring = vector <string>(nrstring);
        cout<<"Citire stringuri importante: ";
        is.get();
        for (int i = 0 ; i < nrstring ; i++ )
        {   getline(cin,liststring[i]);
        }
        cout<<"\n";

        return is;
    }
    ostream &write(ostream &os) const override{
        Malware::write(os);
        cout<<"Importuri: ";
        for(auto registru: importuri)
            cout<<registru<<" ";
        cout<<"\n";
        cout<<"Lista stringuri: ";
        for(auto& registru: liststring)
            cout<<registru<<" ";
        cout<<"\n";
        return os;
    }
    float ImpactRating() override {
        float r = 0;
        for (int i = 0;i < liststring.size();i++) {
            for (auto& j : badBins) {
                if (j == liststring[i]) {
                    r += 100;
                }
            }
        }
        for (int i = 0;i < importuri.size();i++) {
            if (importuri[i] == "ntoskrnl.exe") {
                r *= 2;
            }
        }
       rating = Malware::ImpactRating() + r;
        return rating;
    }

    const vector<string> &getImporturi() const {
        return importuri;
    }

    void setImporturi(const vector<string> &importuri) {
        rootkit::importuri = importuri;
    }

    const vector<string> &getListstring() const {
        return liststring;
    }

    void setListstring(const vector<string> &liststring) {
        rootkit::liststring = liststring;
    }

};
class keylogger: virtual public Malware
         { protected:
             vector <string> functii;
             vector <string> taste;
        public:
    keylogger(float rating, int zi, int luna, int an, const string &nume, const string &metoda,
              const vector<string> &registrii, const vector<string> &functii, const vector<string> &taste);
    keylogger() = default;

    istream &read(istream &is) override
    {
        Malware::read(is);
        int nrfunctii,nrtaste;
        string x;
        cout<<"Numar functii: ";
        is>>nrfunctii;
        cout<<"Citire functii: ";
        for (int i = 0 ; i < nrfunctii ; i++ )
        {   is>>x;
            functii.push_back(x);
        }

        cout<<"Numar taste: ";
        is>>nrtaste;
        taste = vector <string>(nrtaste);
        cout<<"Citire Taste: ";
        is.get();
        for (int i = 0 ; i < nrtaste; i++ )
        {  getline(cin,taste[i]);
        }

        return is;
    }
    ostream &write(ostream &os) const override{
        Malware::write(os);
        cout<<"Functii: ";
        for(auto &functie: functii)
            cout<<functie<<" ";
        cout<<"\n";
        cout<<"Taste: ";
        for(auto &tasta: taste)
            cout<<tasta<<" ";
        cout<<"\n";
        return os;
    }

    float ImpactRating() override
    {  float r = 0;
        for (int i = 0;i < taste.size();++i) {
            for (auto& j : badKeys) {
                if (taste[i] == j) {
                    r += 10;
                }
            }
            for (auto& j : badFunctions) {
                if (functii[i] == j) {
                    r += 30;
                }
            }
        }
        rating = r;
        return r;

    }

 const vector<string> &getFunctii()const {
        return functii;
    }

    void setFunctii(const vector<string> &functii) {
        keylogger::functii = functii;
    }

    const vector<string> &getTaste() const {
        return taste;
    }

    void setTaste(const vector<string> &taste) {
        keylogger::taste = taste;
    }


};

class ransomware: public Malware
{  protected:
    int ratingcriptare;
    int ratingobfuscare;
public:
    ransomware(float rating, int zi, int luna, int an, const string &nume, const string &metoda,
               const vector<string> &registrii, int ratingcriptare, int ratingobfuscare) : Malware(rating, zi, luna, an,
                                                                                                   nume, metoda,
                                                                                                   registrii),
                                                                                           ratingcriptare(
                                                                                                   ratingcriptare),
                                                                                           ratingobfuscare(
                                                                                                   ratingobfuscare) {}
     ransomware() = default;
    istream &read(istream &is)  override
    {
        Malware::read(is);
        cout<<"Rating Scriptare: ";
        is>>ratingcriptare;
        cout<<"Rating Obfuscare: ";
        is>>ratingobfuscare;
        return is;
    }
    ostream &write(ostream &os) const override{
        Malware::write(os);
        cout<<"Rating Criptare: ";
        cout<<ratingcriptare<<"\n";
        cout<<"Rating Obfuscare: ";
        cout<<ratingobfuscare<<"\n";

        return os;
    }

    float ImpactRating() override
    { float r = ratingobfuscare + ratingcriptare;
        rating = Malware::ImpactRating() + r;
        return rating;
    }
    int getRatingcriptare() const {
        return ratingcriptare;
    }

    void setRatingcriptare(int ratingcriptare) {
        ransomware::ratingcriptare = ratingcriptare;
    }

    int getRatingobfuscare() const {
        return ratingobfuscare;
    }

    void setRatingobfuscare(int ratingobfuscare) {
        ransomware::ratingobfuscare = ratingobfuscare;
    }

};
class KernelKeylogger:  public rootkit, public keylogger {
protected:
    bool ascundeF,ascundeR;
public:

    istream &read(istream &is) override {

        keylogger::read(is);
        int sz = 0;
        cout << "Numar importuri: ";
        is >> sz;
        importuri = vector <string>(sz);
        //cerr << sz << "\n";
        for (int i = 0 ;i < sz; ++i) {
            is >> importuri[i];

        }
        cout << "Numar stringuri binare: ";
        is >> sz;
        liststring = vector <string>(sz);
        for (int i = 0;i < sz;++i) {
            is >> liststring[i];
        }
        cout << "Fisiere ascunse(pentru da 1 si pentru nu 0)?\n";
        is >> ascundeF;
        cout << "Registrii ascunsi (pentru da 1 si pentru nu 0)?\n";
        is >> ascundeR;
        return is;
    }

    ostream &write(ostream &os) const override {
        keylogger::write(os);
        os << importuri.size() << " importuri:\n";
        for (int i = 0;i < importuri.size();++i) {
            os << importuri[i] << " ";
        }
        os << "\n";
        os << liststring.size() << " Stringuri Binare:\n";
        for (int i = 0;i < liststring.size();++i) {
            os << liststring[i] << " ";
        }
        os << "\n";
        os << "Fisiere ascunse? " << ascundeF<< "\n";
        os << "Regsitrii ascunsi ? " << ascundeR << "\n";
        return os;
    }
    float ImpactRating() override {
        float r = rootkit::ImpactRating() + keylogger::ImpactRating();
        if (ascundeF) {
            r += 20;
        }
        if (ascundeR){
            r += 30;
        }
       rating = Malware::ImpactRating() + r;
        return rating;
    }

    bool isAscundeF() const {
        return ascundeF;
    }

    bool isAscundeR() const {
        return ascundeR;
    }

    void setAscundeF(bool ascundeF) {
        KernelKeylogger::ascundeF = ascundeF;
    }

    void setAscundeR(bool ascundeR) {
        KernelKeylogger::ascundeR = ascundeR;
    }
};

shared_ptr<Malware> createPtr(int mal) {
    shared_ptr<Malware> p;
    if(mal == 1) //rootkit
    {
        p = make_shared<rootkit>();
    }
    if(mal == 2) //keylogger
    {
        p = make_shared<keylogger>();
    }
    if(mal == 3) //kernel-keylogger
    {
        p = make_shared<KernelKeylogger>();
    }
    if(mal == 4) //ransomware
    {
        p = make_shared<ransomware>();
    }
    return p;

}

class Calculator:virtual public IoBase
{
private:
    static int Nrcalc;
    int id;
    vector <shared_ptr<Malware>> malwares;
    float Rating = 0;
public:
    Calculator(int id, const vector<shared_ptr<Malware>> &malwares, float rating) :  malwares(malwares),
                                                                                    Rating(rating){
        id = ++Nrcalc;
                                                                                                   }
     Calculator(){
        id = ++Nrcalc;
    }
//       virtual istream &read(iostream &is, Calculator &calculator)
//    {
//        cout<<"Numarul de malware: ";
//        int nrM;
//        is>>nrM;
//        calculator.malwares = vector<shared_ptr<Malware>>(nrM);
//        for ( int i = 0 ; i < nrM ; i++)
//        {cout<<"Tipul de malware(1=rootkit, 2=keylogger, 3 =KernelKeylogger , 4= ransomware ): ";
//            int tip;
//            is>>tip;
//            shared_ptr<Malware> M = createPtr(tip);
//            is>> *M;
//            calculator.malwares[i] = M;
//            M->ImpactRating();
//            calculator.Rating =  M->ImpactRating();
//        }
//        return is;
//    };
//     virtual ostream &write(ostream &os,const Calculator &calculator)
//      { os << "id = " << calculator.id << "\n";
//          os << "malwares = " << calculator.malwares.size() << "\n";
//          for (int i = 0;i < calculator.malwares.size();++i) {
//              os << *calculator.malwares[i] << "\n";
//          }
//          os << "rating = " << calculator.Rating << "\n";
//          return os;
//
//      };

void addRootkit()
{
    shared_ptr<Malware> M = createPtr(1);
    cin>>*M;
    malwares.push_back(M);
    Rating += M->ImpactRating();

}
    void addKeylogger()
    {
        shared_ptr<Malware> M = createPtr(2);
        cin>>*M;
        malwares.push_back(M);
        Rating += M->ImpactRating();


    }
    void addKernelKeylogger()
    {
        shared_ptr<Malware> M = createPtr(3);
        cin>>*M;
        malwares.push_back(M);
        Rating += M->ImpactRating();

    }
    void addRansomware()
    {
        shared_ptr<Malware> M = createPtr(4);
        cin>>*M;
        malwares.push_back(M);
        Rating += M->ImpactRating();

    }
    int getId() const {
        return id;
    }

    const vector<shared_ptr<Malware>> &getMalwares() const {
        return malwares;
    }

    float getRating() const {
        return Rating;
    }

    void setId(int id) {
        Calculator::id = id;
    }

    void setMalwares(const vector<shared_ptr<Malware>> &malwares) {
        Calculator::malwares = malwares;
    }

    void setRating(float rating) {
        Rating = rating;
    }


};
int Calculator::Nrcalc = 0;



class Menu{
private:
     int optiune;
     vector<Calculator> calculatoare;
public:
    Menu(int optiune, const vector<Calculator> &calculatoare) : optiune(optiune), calculatoare(calculatoare) {}
    Menu() = default;
    void alegereOptiune()
    {
        cout << "1. Cerinta1." << '\n';
        cout << "2. Cerinta2." << '\n';
        cout << "3. Cerinta3." << '\n';
        cout << "4. Cerinta4." << '\n';
        cin>>optiune;

    }

    const vector<Calculator> &getCalculatoare() const {
        return calculatoare;
    }

    int getOptiune() const {
        return optiune;
    }

    void setOptiune(int optiune) {
        Menu::optiune = optiune;
    }

    void setCalculatoare(const vector<Calculator> &calculatoare) {
        Menu::calculatoare = calculatoare;
    }

    void Cerinta1() {
        cout<<"------CERINTA 1------\n";

        cout << "Numar Calculatoare: " << calculatoare.size() << "\n";
        for (auto &i: calculatoare) {
            cout<<"DATE CALCULATOR"<<"\n";
            cout << "ID:" << i.getId() << "\n";
            cout << "Rating Calculator:" << i.getRating() << "\n";

            for (auto &j: i.getMalwares()) {
                cout << *j;
                cout << "\n";
            }
              cout<<"AM AFISAT TOATE DATELE";
        }
    }
   void Cerinta2()
   {    cout<<"------CERINTA 2------\n";
       cout<<"Numar Calculatoare: "<< calculatoare.size()<<"\n";
        auto copy_computers = calculatoare;
        sort(copy_computers.begin(), copy_computers.end(), [&](Calculator a, Calculator b) {
           return a.getRating() < b.getRating();
       });
       for (auto &i: calculatoare) {
           cout<<"DATE CALCULATOR"<<"\n";
           cout << "ID:" << i.getId() << "\n";
           cout << "Rating Calculator:" << i.getRating() << "\n";

           for (auto &j: i.getMalwares()) {
               cout << *j;
               cout << "\n";
           }
           cout<<"AM AFISAT TOATE DATELE CALCULATORULUI CU ID:"<<i.getId()<<"\n";
       }

   }
   void Cerinta3()
   {   int k;
       cout<<"------CERINTA 3------\n";
       cout<<"k = ";
       cin>>k;
       cout<<"\n";
       cout<<"Numar Calculatoare: "<< calculatoare.size()<<"\n";
       auto copy_computers = calculatoare;
       sort(copy_computers.begin(), copy_computers.end(), [&](Calculator a, Calculator b) {
           return a.getRating() < b.getRating();
       });
       cout<<"Numar Calculatoare: "<< calculatoare.size()<<"\n";
       for(int  i = 0 ; i<k  ; i ++)
       {
           cout <<i<<"\n";
       }
       cout<<"-----AM TERMINAT-----\n";

   }
   void Cerinta4()
   {   cout<<"------CERINTA 4------\n";
       int cnt = 0;
       for (auto& i : calculatoare) {
           if (i.getRating() > 0) {
               ++cnt;
           }
       }
       int all = calculatoare.size();
       cout << "Procent infectare  = " << 100.0 * cnt / all << "%\n";

   }

};


int main() {
    cout<<"Alegeti una dintre urmatoarele cerinte:\n";
    Menu meniu;
    meniu.alegereOptiune();
    int N,M;
    int tip;
    cout<<"Numar Calculatoare: ";
    cin>>N;
   vector<Calculator> a(N);
      for (int  i =0 ;i<N; i++ )
      {   cout<<"CALCULATORUL: "<<i+1<<"\n";
          cout<<"Numar malware: ";
          cin>>M;
          for (int j = 0 ; j<M ; j++)
          { cout<<"Tipul de malware(1=rootkit, 2=keylogger, 3 =KernelKeylogger , 4= ransomware ): ";
              cin>>tip;
              if(tip==1)
              {
                  a[i].addRootkit();
              }
              if(tip==2)
              {
                  a[i].addKeylogger();
              }
              if(tip==3)
              {
                  a[i].addKernelKeylogger();
              }
              if(tip==4)
              {
                  a[i].addRansomware();
              }
          }
      }

      int opt=meniu.getOptiune();
      meniu.setCalculatoare(a);
      if(opt == 1) meniu.Cerinta1();
      if(opt == 2) meniu.Cerinta2();
      if(opt == 3) meniu.Cerinta3();
      if(opt == 4) meniu.Cerinta4();
      cout<<"\n";
      cout<<"---SUCCES!----";
      return 0;
}