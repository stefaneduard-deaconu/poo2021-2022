/* Nume Prenume: Nechita Maria-Ilinca Grupa: 143
Compilator:
Tutore de laborator : Deaconu Stefan-Eduard*/

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//Prin malware înțelegem un software rău intenționat pentru care se reține impactul impactului
//(număr real), data de infectare (zi, luna, an), numele acestuia
//(care poate să fie format din mai multe cuvinte),
//metoda de infectare (dacă se cunoaște, altfel se reține șirul “unknown”)
//un vector cu registrii modificați (reținuți ca stringuri).

// construim clasa Malware cu atributele mentionate mai sus
class Malware{
protected:
    double impact;
    int zi, luna, an;
    string nume, metoda_infectare;
    vector <string> registrii;
public:
    // constructorul - nul
    Malware (){zi=0,luna=0,an=0; nume=" ", metoda_infectare = " " ;}

    Malware(double impact, int zi, int luna, int an, const string &nume, const string &metodaInfectare, const vector<string> &registrii) : impact(impact), zi(zi), luna(luna), an(an), nume(nume),metoda_infectare(metodaInfectare), registrii(registrii) {}
    // constructor de copiere
    Malware(const Malware&ob){
        impact = ob.impact;
        zi = ob.zi;
        luna = ob.luna;
        an = ob.an;
        nume = ob.nume;
        metoda_infectare = ob.metoda_infectare;
        registrii = ob.registrii;}
    // operatorul atribuire
    Malware &operator=(const Malware &ob)
    {
        impact = ob.impact;
        zi = ob.zi;
        luna = ob.luna;
        an = ob.an;
        nume = ob.nume;
        metoda_infectare = ob.metoda_infectare;
        registrii = ob.registrii;
        return *this;
    }
   ~Malware();

    // setteri si getteri pentru fiecare atributa a clasei

    double getImpact() {return impact;}
    void setImpact(double _impact){impact=_impact;}

    int getZi() {return zi;}
    void setZi(int _zi){zi=_zi;}

    int getLuna() {return luna;}
    void setLuna(int _luna){luna=_luna;}

    int getAn() {return an;}
    void setAn(int _an){an=_an;}

    const string &getNume() {return nume;}
    void setNume(const string &_nume) {nume=_nume;}

    const string &getMetodaInfectare() {return metoda_infectare;}
    void setMetodaInfectare(const string &_metodainfectare) {metoda_infectare=_metodainfectare;}

    const vector<string> &getRegistrii() const {return registrii;}

    void setRegistrii(const vector<string> &registrii) {Malware::registrii = registrii;}

    // metode virtuale pure care vor fi folosite in urmatoarele clase
    virtual istream& readMalware(istream& is) = 0;
    virtual ostream& printMalware(ostream& os) = 0;
    virtual double calculeaza() = 0;
};

//Prin rootkit înțelegem un tip de malware ce are drept scop obținerea drepturilor de administrator asupra dispozitivului infectat.
//Pentru rootkit se reține lista importurilor care poate fi unul și oricât de multe
//(importurile fac referire la numele fișierelor .dll folosite) și
//o listă de stringuri semnificative (anumite stringuri dintr-un binar pot fi un indice asupra faptului că fișierul este rău intenționat).

class Rootkit:virtual public Malware{
private:
    vector <string> importuri;
    vector <string> semnificative;
public:
    // constructorii -nul, normal, copiere
    Rootkit():Malware(),importuri(),semnificative(){};
   Rootkit(const Rootkit & ob){
       impact = ob.impact;
       zi = ob.zi;
       luna = ob.luna;
       an = ob.an;
       nume = ob.nume;
       metoda_infectare = ob.metoda_infectare;
       registrii = ob.registrii;
       importuri = ob.importuri;
       semnificative = ob.semnificative;
   }
    Rootkit & operator=(const Rootkit &ob) {
        impact = ob.impact;
        zi = ob.zi;
        luna = ob.luna;
        an = ob.an;
        nume = ob.nume;
        metoda_infectare = ob.metoda_infectare;
        registrii = ob.registrii;
        importuri = ob.importuri;
        semnificative = ob.semnificative;
        return *this;
    }
    ~Rootkit(){
        importuri.clear();
        semnificative.clear();
    }

    Rootkit(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare, const vector<string> &registrii, const vector<string> &importuri, const vector<string> &semnificative): Malware(impact, zi, luna, an, denumire, metodaDeInfectare, registrii), importuri(importuri),semnificative(semnificative) {}

    // getteri si setteri
    const vector<string> &getImporturi() const {return importuri;}
    void setImporturi(const vector<string> &importuri) {Rootkit::importuri = importuri;}

    const vector<string> &getSeminificative() const {return semnificative;}
    void setSemnificative(const vector<string> &semnificative) {Rootkit::semnificative = semnificative;}

    virtual istream& readMalware(istream& is);
    virtual ostream& printMalware(ostream& os);
    virtual double calculeaza();
};

// Pentru rootkit ratingul impactului crește cu 100 dacă se întâlnește unul din stringurile “System Service Descriptor Table”,
// “SSDT”, “NtCreateFile”. Dacă se regăsește importul “ntoskrnl.exe”, valoarea impactului
// se dublează (importurile se verifică după stringuri).
double Rootkit :: calculeaza(){
    double value=impact;
    for (int i=1;i<importuri.size();i++)
    {
        if (importuri[i]=="System Service Descriptor Table" ||importuri[i]=="SSDT" || importuri[i]=="NtCreateFile" )
            value+=100;
    }
//Pentru orice tip de malware se adună 20 dacă registrii afectați sunt “HKLM-run” sau “HKCU-run”.
    for (int i=1;i<importuri.size();i++)
    {
        if (importuri[i]=="HKLM-run" ||importuri[i]=="HKCU-run")
            value+=20;
    }

    for (int i=1;i<importuri.size();i++)
  {
      if (importuri[i]=="ntoskrnl.exe")
          value=value*2;
  }
}

//istream & Rootkit::readMalware(istream &is){
//
//}

ostream & Rootkit::printMalware(ostream &os) {
    os << "Impact: " << impact << "\n";
    os << "Data: " << zi << '/' << luna << '/' << an << '\n';
    os << "Denumire: " << nume << '\n';
    os << "Metoda de inf: " << metoda_infectare << '\n';
    os << "Registrii:\n";
    for(int i = 0;i < registrii.size() ; ++i){
        cout  << registrii[i] << '\n';
    }
    os  << "Importuri:\n";
    for(int i = 0;i < importuri.size() ; ++i){
        cout  << importuri[i] << '\n';
    }
    os << "Semnificative:\n";
    for(int i = 0;i < semnificative.size() ; ++i){
        os << semnificative[i] << '\n';
    }
    return os;
}

//Prin keylogger înțelegem un malware care înregistrează acțiunile de la tastatură și le trimite mai departe.
//Pentru un keylogger se reține o listă cu funcțiile folosite și o listă cu tastele speciale definite.
class Keylogger:virtual public Malware{
private:
    vector <string> functii;
    vector <string> taste;
public:
    // constructorii -nul, normal, copiere
    Keylogger():Malware(),functii(),taste(){};
    Keylogger(const Keylogger & ob){
        impact = ob.impact;
        zi = ob.zi;
        luna = ob.luna;
        an = ob.an;
        nume = ob.nume;
        metoda_infectare = ob.metoda_infectare;
        registrii = ob.registrii;
        functii = ob.functii;
        taste = ob.taste;
    }
    Keylogger & operator=(const Keylogger &ob) {
        impact = ob.impact;
        zi = ob.zi;
        luna = ob.luna;
        an = ob.an;
        nume = ob.nume;
        metoda_infectare = ob.metoda_infectare;
        registrii = ob.registrii;
        functii = ob.functii;
        taste = ob.taste;
        return *this;
    }
    ~Keylogger(){
        functii.clear();
        taste.clear();
    }

    Keylogger(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare, const vector<string> &registrii, const vector<string> &importuri, const vector<string> &semnificative): Malware(impact, zi, luna, an, denumire, metodaDeInfectare, registrii), functii(functii),taste(taste) {}

    // getteri si setteri
    const vector<string> &getFunctii() const {return functii;}
    void setFunctii(const vector<string> &functii) {Keylogger::functii = functii;}

    const vector<string> &getTaste() const {return taste;}
    void setTaste(const vector<string> &taste) {Keylogger::taste = taste;}

    virtual double calculeaza();

};

//Pentru keylogger ratingul impactului crește cu 10 la întâlnirea stringurilor “[Up]”, “[Num Lock]”
//“[Down]”, “[Right]”, “[UP]”, “[Left]”, “[PageDown]” și
//cu 30 la întâlnirea unei din funcțiile: “CreateFileW”, “OpenProcess”, “ReadFile”, “WriteFile”,
//“RegisterHotKey”, “SetWindowsHookEx”.

double Keylogger :: calculeaza(){
    double value=impact;
    for (int i=1;i<taste.size();i++)
    {
        if (taste[i]=="[Up]" ||taste[i]=="[Num Lock]" || taste[i]=="[Down]" || taste[i]=="[Right]"||taste[i]=="[Left]"||taste[i]=="UP"||taste[i]=="[PageDown]")
            value+=10;
    }
//Pentru orice tip de malware se adună 20 dacă registrii afectați sunt “HKLM-run” sau “HKCU-run”.
    for (int i=1;i<functii.size();i++)
    {
        if (functii[i]=="CreateFileW" ||functii[i]=="OpenProcess" ||functii[i]=="ReadFile" ||functii[i]=="WriteFile" ||functii[i]=="RegisterHotKey" ||functii[i]=="SetWindowsHookEx")
            value+=30;
    }

};

//Pentru fiecare computer din firmă se reține un id unic, incrementat automat,
//o listă de malware (poate conține un malware sau mai multe) și
//ratingul final ce este calculat drept suma ratingului impactului fiecărui malware.

class Computer{
private:
    static int id;
    int cod;
    double rating_final;
    vector <Malware*> virusi;

public:
    // constructori + destructori

    Computer();
    Computer(const Computer& c){
        cod = c.cod;
        rating_final = c.rating_final;
        for(int i = 0;i< virusi.size(); ++i)
            delete virusi[i];
        virusi.clear();
        for(int i = 0;i < c.virusi.size(); ++i)
            addVirus(c.virusi[i]);
    }
    Computer& operator=(const Computer& c){
        cod = c.cod;
        rating_final = c.rating_final;
        for(int i = 0;i< virusi.size(); ++i)
            delete virusi[i];
        virusi.clear();
        for(int i = 0;i < c.virusi.size(); ++i)
            addVirus(c.virusi[i]);
        return *this;
    }
    ~Computer(){
        --id;
        cod = 0;
        rating_final = 0;
        for(int i = 0;i < virusi.size();++i)
            delete virusi[i];
        virusi.clear();
    }

    Computer(vector < Malware*> virus) {
        ++id;
        cod = id;
        for (int i = 0; i < virusi.size(); ++i)
            delete virusi[i];
        virusi.clear();
        for (int i = 0; i < virus.size(); ++i) {
            addVirus(virus[i]);
            rating_final += virus[i]->calculeaza();
        }
    }
        void addVirus(Malware *m);
//    friend istream& operator>>(istream& is, Computer& c);
//    friend ostream & operator<<(ostream& os, Computer& c);

// getteri si setteri
   int getCod() const { return cod; };
   void setCod(int cod) { Computer::cod = cod; }

   static int getId() {return id;}
   static void setId(int id) {Computer::id = id;}

   double getRatingFinal() const {return rating_final;}
   void setRatingFinal(double ratingFinal) {rating_final = ratingFinal;}

   const vector<Malware *> &getVirusi() const {return virusi;}
   void setVirusi(const vector<Malware *> &virusi) {Computer::virusi = virusi;}
};

void Computer ::addVirus(Malware *m) {

}

// clasa Meniu Interactiv => singleton
        class MeniuInteractiv {
        private:
            vector<Computer *> calculatoare;
            static MeniuInteractiv *instanta;

            MeniuInteractiv() = default;
            MeniuInteractiv(const MeniuInteractiv &m) = default;
            MeniuInteractiv(MeniuInteractiv &m) = default;
            MeniuInteractiv &operator=(const MeniuInteractiv &m) = default;
            MeniuInteractiv &operator=(MeniuInteractiv &ob) = default;

        public:
            static MeniuInteractiv *getInstanta() {
                if (instanta == nullptr)
                    instanta = new MeniuInteractiv();
                return instanta;
            }

            static void deleteInstanta() {
                if (instanta != nullptr)
                    delete instanta;
                instanta = nullptr;
            }

            //destructor
            ~MeniuInteractiv() {
                for (int i = 0; i < calculatoare.size(); ++i)
                    delete calculatoare[i];
                calculatoare.clear();
            }

            void demo();
            void afisCalculatoare();
            void afisCalculatoareRating();
            void afisPrimeleK();
            void afisProcent();
        };

        void MeniuInteractiv::demo() {
            cout << "demo\n";
        }

        void MeniuInteractiv::afisCalculatoare() {
            for (int i = 0; i < calculatoare.size(); ++i)
               // cout << *calculatoare[i] << '\n';
            cout << '\n';
        }

// sortam calculatoarele in functie de rating
        void MeniuInteractiv::afisCalculatoareRating() {
            for (int i = 0; i < calculatoare.size(); ++i)
                for (int j = i + 1; j < calculatoare.size(); ++j)
                    if (calculatoare[i]->getRatingFinal() > calculatoare[j]->getRatingFinal())
                        swap(calculatoare[i], calculatoare[j]);

            for (int i = 0; i < calculatoare.size(); ++i)
                //cout << *calculatoare[i] << '\n';
            cout << '\n';
        }

        void MeniuInteractiv::afisPrimeleK() {
            int k;
            while (true) {
                cout << "K este:\n";
                cin >> k;
                cin.get();
                if (k <= 0)
                    throw string("Nr invalid!");
                else
                    break;;
            }
            for (int i = 0; i < calculatoare.size(); ++i)
                for (int j = i + 1; j < calculatoare.size(); ++j)
                    if (calculatoare[i]->getRatingFinal() > calculatoare[j]->getRatingFinal())
                        swap(calculatoare[i], calculatoare[j]);
            for (int i = 0; i < k && i < calculatoare.size(); ++i)
                //cout << *calculatoare[i] << '\n';
            cout << '\n';

        }


int main() {
    int choice;
    MeniuInteractiv *m = m->getInstanta();
    while (true){
        cout << "0.Demo\n";
        cout << "1.Afis Calculatoare\n";
        cout << "2.Afis Calculatoare dupa Rating\n";
        cout << "3.Afis primele k calculatoare\n";
        cout << "4.Afis procent de calculatoare infectate\n";
        cout << "5.Inchide\n";

        try{
            cin >> choice;
            cin.get();
            if(choice < 0 || choice > 5)
                throw string("optiune gresita!");
            else{
                switch(choice){
                    case 0:
                        m->demo();
                    case 1:
                        m->afisCalculatoare();
                    case 2:
                        m->afisCalculatoareRating();
                    case 3:
                        m->afisPrimeleK();
                    case 4:
                        m->afisProcent();
                    case 5:
                        break;

                }
            }}
        catch (string s){
            cout << s << '\n';
        }
    }
    m->deleteInstanta();
    return 0;
}
