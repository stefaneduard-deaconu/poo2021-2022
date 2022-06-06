#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Malware
{
private:
    float rating;
    int zi,luna,an;
    string nume,metodaInfectare;
    vector <string> registrii;
public:

    virtual float calculeazaImpact()
    {

    }

    Malware(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
            const vector<string> &registrii) : zi(zi), luna(luna), an(an), nume(nume), metodaInfectare(metodaInfectare),
                                               registrii(registrii) {}

    friend ostream &operator<<(ostream &os, const Malware &malware) {
        os << "rating: " << malware.rating << " zi: " << malware.zi << " luna: " << malware.luna << " an: "
           << malware.an << " nume: " << malware.nume << " metodaInfectare: " << malware.metodaInfectare;
        return os;
    }

    float verificaRegistrii()
    {
        float _rating = 0;
        for (auto i: registrii)
        {
            if ((i == "HKLM-run") or (i == "HKCU-run"))
            {
                _rating += 20;
            }
        }
        return _rating;
    }

    const string &getMetodaInfectare() const {
        if (metodaInfectare != "")
        return metodaInfectare;
        else return "Unkown";
    }

    void setMetodaInfectare(const string &metodaInfectare) {
        Malware::metodaInfectare = metodaInfectare;
    }

    float getRating() const {
        return rating;
    }

    void setRating(float rating) {
        Malware::rating = rating;
    }

};

class Rootkit: public Malware
{
private:
    vector<string> importuri, semnificative;
public:
    Rootkit(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
            const vector<string> &registrii, const vector<string> &importuri, const vector<string> &semnificative)
            : Malware(zi, luna, an, nume, metodaInfectare, registrii), importuri(importuri),
              semnificative(semnificative) {}

    virtual float calculeazaImpact() override
    {

        float _rating = 0;
        for (auto i: semnificative)
        {
            if ((i == "System Service Descriptor Table") or (i == "SSDT") or (i == "NtCreateFile"))
            {
                _rating += 100;
            }
        }
        int multi = 1;
        for (auto i: importuri)
        {
            if (i == "ntoskrnl.exe") multi = 2;
        }
        _rating = _rating * multi;
        return _rating + verificaRegistrii();
    }

};

class Keylogger: public Malware
{
private:
    vector<string> functii, taste;
public:
    Keylogger(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
              const vector<string> &registrii, const vector<string> &functii, const vector<string> &taste) : Malware(zi,
                                                                                                                     luna,
                                                                                                                     an,
                                                                                                                     nume,
                                                                                                                     metodaInfectare,
                                                                                                                     registrii),
                                                                                                             functii(functii),
                                                                                                             taste(taste) {}

    virtual float calculeazaImpact () override
    {
        float _rating = 0;
        for (auto i: taste)
        {
            if ((i == "[Up]") or (i == "[Num Lock]") or (i == "[Down]") or (i == "[Right]") or (i == "[UP]") or (i == "[Left]") or (i == "[PageDown]"))
            {
                _rating += 30;
            }
        }
        for (auto i : functii)
        {
            if ((i == "CreateFileW") or (i == "OpenProcess") or (i == "ReadFile") or (i == "WriteFile") or (i == "RegisterHotKey") or (i == "SetWindowsHookEx"))
            {
                _rating += 10;
            }
        }
        return _rating + verificaRegistrii();
    }
};

class KernerlKeylogger: public Rootkit, public Keylogger
{
private:
    bool ascundeFisiere, ascundeRegistrii;
public:
    KernerlKeylogger(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
                     const vector<string> &registrii, const vector<string> &importuri,
                     const vector<string> &semnificative, int zi1, int luna1, int an1, const string &nume1,
                     const string &metodaInfectare1, const vector<string> &registrii1, const vector<string> &functii,
                     const vector<string> &taste, bool ascundeFisiere, bool ascundeRegistrii) : Rootkit(zi, luna, an,
                                                                                                        nume,
                                                                                                        metodaInfectare,
                                                                                                        registrii,
                                                                                                        importuri,
                                                                                                        semnificative),
                                                                                                Keylogger(zi1, luna1,
                                                                                                          an1, nume1,
                                                                                                          metodaInfectare1,
                                                                                                          registrii1,
                                                                                                          functii,
                                                                                                          taste),
                                                                                                ascundeFisiere(
                                                                                                        ascundeFisiere),
                                                                                                ascundeRegistrii(
                                                                                                        ascundeRegistrii) {}

    virtual float calculeazaImpact() override
    {
        float _rating = Rootkit::calculeazaImpact() + Keylogger::calculeazaImpact();
        if (ascundeFisiere) _rating += 20;
        if (ascundeRegistrii) _rating += 30;
        return _rating;
    }

};

class Ransomware: public Malware
{
private:
    int ratingCriptare;
    float obfuscare;
public:
    Ransomware(int zi, int luna, int an, const string &nume, const string &metodaInfectare,
               const vector<string> &registrii, int ratingCriptare, float obfuscare) : Malware(zi, luna, an, nume,
                                                                                               metodaInfectare,
                                                                                               registrii),
                                                                                       ratingCriptare(ratingCriptare),
                                                                                       obfuscare(obfuscare) {}

    virtual float calculeazaImpact() override
    {
        float _rating = ratingCriptare + obfuscare;
        return _rating + verificaRegistrii();

    }
};


class Computer
{
private:
    int id;
    float ratingFinal;
    vector<Malware> virusi;
public:
    Computer(int id, const vector<Malware> &virusi) : id(id), virusi(virusi) {}

    friend ostream &operator<<(ostream &os, const Computer &computer) {
        os << "id: " << computer.id << " ratingFinal: " << computer.ratingFinal;
        return os;
    }
    float calculeazaRatingFinal()
    {
        float _rating = 0;
        for (auto i : virusi)
        {
            i.setRating(i.calculeazaImpact());
            _rating += i.getRating();
        }
        return _rating;
    }

    float getRatingFinal() const {
        return ratingFinal;
    }

    void setRatingFinal(float ratingFinal) {
        Computer::ratingFinal = ratingFinal;
    }

    const vector<Malware> &getVirusi() const {
        return virusi;
    }

    void setVirusi(const vector<Malware> &virusi) {
        Computer::virusi = virusi;
    }
};

//cod luat din lab8
class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};

class Menu: public BaseMenu {
private:
    vector<Computer> Computers;
    bool init = "false";
public:
    void listOptions() override {
        cout << "1. Informatii calculatoare\n";
        cout << "2. Informatii calculatoare ordonate\n";
        cout << "3. Informatii primele k calculatoare ordonate\n";
        cout << "4. Procent calculatoare infectate\n";
        cout << "5. Iesire\n";
    }

    int chooseOption(int first, int last) override {
        int option = -1;
        if (init = false)
        {
            for (auto i : Computers)
            {
                i.setRatingFinal(i.calculeazaRatingFinal());
            }
        }
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
        for (auto i : Computers)
        {
            cout<< i;
        }
    }

    void option2() {
        vector<Computer> _Computers;
        _Computers = Computers;
        sort(_Computers.begin(), _Computers.end(), sortare);
        for (auto i : _Computers)
        {
            cout << i << " ";
        }
    }
    static bool sortare(Computer x, Computer y)
    {
        if (x.getRatingFinal() > y.getRatingFinal()) return false;
        else return true;
    }

    void option3()
    {
        int k = 0;
        cin >> k;
        if (k > Computers.size()) k = Computers.size();
        vector<Computer> _Computers;
        _Computers = Computers;
        sort(_Computers.begin(), _Computers.end(), sortare);
        for (int i = 0; i < k; i++)
        {
            cout << _Computers[i] << " ";
        }
    }

    void option4()
    {
        int nrInfectari;
        for (auto i : Computers)
        {
            if (i.getRatingFinal() > 0) nrInfectari++;
        }
        cout << float(nrInfectari * 100) / float(Computers.size());
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
            } else if (option == 5){
                break;
            }
        }
    }

    const vector<Computer> &getComputers() const {
        return Computers;
    }

    void setComputers(const vector<Computer> &computers) {
        Computers = computers;
    }
};


int main() {
    vector<Computer> calculatoare();
    Menu menu;
    menu.mainLoop();
    return 0;
}
