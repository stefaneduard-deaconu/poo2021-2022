#include <iostream>
#include <fstream>
#include <algorithm>

#include "util/IoBase.h"
#include "util/functions.h"

#include <memory>

using namespace std;

vector <string> badBins = {"System Service Descriptor Table", "SSDT", "NtCreateFile"};
vector <string> badKeys = {"[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
vector <string> badFunctions = {"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};
class Malware;
shared_ptr<Malware> createPtr(int mal);

class Malware : public IoBase {
protected:
    double impactRating;
    int day, month, year;
    string name;
    vector <string> regs;
public:
    Malware() = default;
    Malware(double impactRating, int day, int month, int year, const string &name, const vector<string> &regs)
            : impactRating(impactRating), day(day), month(month), year(year), name(name), regs(regs) {}



    istream& read(istream &is) override {
        //cout << "Day = ";
        is >> day;
        //cout << "Month = ";
        is >> month;
        //cout << "Year = ";
        is >> year;
        //cout << "Name = ";
        is >> name;
        //cout << "Registers = ";
        int sz = 0;
        is >> sz;
        regs = vector <string>(sz);
        for (int i = 0;i < sz;++i) {
            is >> regs[i];
        }
        return is;
    }

    ostream& write(ostream &os) const override {
        os << "Impact Rating = ";
        os << impactRating << "\n";
        os << "Day = ";
        os << day << "\n";
        os << "Month = ";
        os << month << "\n";
        os << "Year = ";
        os << year << "\n";
        os << "Name = ";
        os << name << "\n";
        os << "Registers = ";
        for (int i = 0;i < regs.size();++i) {
            os << regs[i] << " ";
        }
        os << "\n";
        return os;
    }

    friend istream& operator>>(istream &is, Malware &malware) {
        return malware.read(is);
    }

    friend ostream& operator<<(ostream &os, Malware &malware) {
        return malware.write(os);
    }
    virtual string infectionMethod() {
        return "Unknown";
    }
    virtual double calculateImpactRating() {
        for (auto& i : regs) {
            if (i == "HKLM-run" || i == "HKCU-run") {
                impactRating += 20;
            }
        }
        return impactRating;
    }
    vector <string> getRegs() {
        return regs;
    }
    double getRating() {
        return impactRating;
    }
};

class Rootkit : virtual public Malware {
protected:
    vector <string> imports;
    vector <string> bins;

public:
    Rootkit() = default;
    Rootkit(double impactRating, int day, int month, int year, const string &name, const vector<string> &regs,
            const vector<string> &imports, const vector<string> &bins) : Malware(impactRating, day, month, year, name,
                                                                                 regs), imports(imports), bins(bins) {}

    istream &read(istream &is) override {
        Malware::read(is);
        int sz = 0;
        //cout << "How many imports? = \n";
        is >> sz;
        imports = vector <string>(sz);
        for (int i = 0;i < sz;++i) {
            is >> imports[i];
        }
        //cout << "How many binaries? = \n";
        is >> sz;
        bins = vector <string>(sz);
        for (int i = 0;i < sz;++i) {
            is >> bins[i];
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        os << imports.size() << " imports\n";
        for (int i = 0;i < imports.size();++i) {
            os << imports[i] << " ";
        }
        os << "\n";
        os << bins.size() << " binaries\n";
        for (int i = 0;i < bins.size();++i) {
            os << bins[i] << " ";
        }
        os << "\n";
        return os;
    }

    string infectionMethod() override {
        return "Rootkit";
    }
    double calculateImpactRating() override {
        double r = 0;
        for (int i = 0;i < bins.size();++i) {
            for (auto& j : badBins) {
                if (j == bins[i]) {
                    r += 100;
                }
            }
        }
        for (int i = 0;i < imports.size();++i) {
            if (imports[i] == "ntoskrnl.exe") {
                r *= 2;
            }
        }
        impactRating = Malware::calculateImpactRating() + r;
        return impactRating;
    }
};

class Keylogger : virtual public Malware {
protected:
    vector <string> keys;
    vector <string> usedFunctions;
public:
    Keylogger() = default;
    Keylogger(double impactRating, int day, int month, int year, const string &name, const vector<string> &regs,
              const vector<string> &keys, const vector<string> &usedFunctions) : Malware(impactRating, day, month, year,
                                                                                         name, regs), keys(keys),
                                                                                 usedFunctions(usedFunctions) {}

    istream &read(istream &is) override {
        Malware::read(is);
        //cout << "How many keys? = \n";
        int sz;
        is >> sz;
        // << sz << " ";
        is.get();
        keys = vector <string>(sz);
        for (int i = 0;i < sz;++i) {
            getline(is, keys[i]);
            //cerr << keys[i] << " ";
        }
        //cout << "How many used functions? = \n";
        is >> sz;
        usedFunctions = vector <string>(sz);
        for (int i = 0;i < sz;++i) {
            is >> usedFunctions[i];
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        os << keys.size() << " keys\n";
        for (int i = 0;i < keys.size();++i) {
            os << keys[i] << " ";
        }
        os << "\n";
        os << usedFunctions.size() << " usedFunctions\n";
        for (int i = 0;i < usedFunctions.size();++i) {
            os << usedFunctions[i] << " ";
        }
        os << "\n";
        return os;
    }

    string infectionMethod() override {
        return "Keylogger";
    }
    double calculateImpactRating() override {

        double r = 0;
        for (int i = 0;i < keys.size();++i) {
            for (auto& j : badKeys) {
                if (keys[i] == j) {
                    r += 10;
                }
            }
            for (auto& j : badFunctions) {
                if (usedFunctions[i] == j) {
                    r += 30;
                }
            }
        }
        impactRating = r;
        return r;
    }
};

class KernelKeylogger : public Rootkit, public Keylogger {
protected:
    bool hiddenFiles;
    bool hiddenRegs;
public:
    KernelKeylogger() = default;
    KernelKeylogger(double impactRating, int day, int month, int year, const string &name, const vector<string> &regs,
                    const vector<string> &imports, const vector<string> &bins, const vector<string> &keys,
                    const vector<string> &usedFunctions, bool hiddenFiles, bool hiddenRegs) : Rootkit(impactRating, day,
                                                                                                      month, year, name,
                                                                                                      regs, imports,
                                                                                                      bins),
                                                                                              Keylogger(impactRating,
                                                                                                        day, month,
                                                                                                        year, name,
                                                                                                        regs, keys,
                                                                                                        usedFunctions),
                                                                                              hiddenFiles(hiddenFiles),
                                                                                              hiddenRegs(hiddenRegs) {}

    istream &read(istream &is) override {

        Keylogger::read(is);
        int sz = 0;
        //cout << "How many imports? = \n";
        is >> sz;
        imports = vector <string>(sz);
        //cerr << sz << "\n";
        for (int i = 0;i < sz;++i) {
            is >> imports[i];

        }
        //cout << "How many binaries? = \n";
        is >> sz;
        bins = vector <string>(sz);
        for (int i = 0;i < sz;++i) {
            is >> bins[i];
        }
        //cout << "Hiding files?\n";
        is >> hiddenFiles;
        //cout << "Hiding registers?\n";
        is >> hiddenRegs;
        return is;
    }

    ostream &write(ostream &os) const override {
        Keylogger::write(os);
        os << imports.size() << " imports\n";
        for (int i = 0;i < imports.size();++i) {
            os << imports[i] << " ";
        }
        os << "\n";
        os << bins.size() << " binaries\n";
        for (int i = 0;i < bins.size();++i) {
            os << bins[i] << " ";
        }
        os << "\n";
        os << "Hiding files? " << hiddenFiles << "\n";
        os << "Hiding registers? " << hiddenRegs << "\n";
        return os;
    }

    string infectionMethod() override {
        return "Kernel-Keylogger";
    }
    double calculateImpactRating() override {
        double r = Rootkit::calculateImpactRating() + Keylogger::calculateImpactRating();
        if (hiddenFiles) {
            r += 20;
        }
        if (hiddenRegs){
            r += 30;
        }
        impactRating = Malware::calculateImpactRating() + r;
        return impactRating;
    }
};

class Ransomware : public Malware {
protected:
    int cryptRating;
    double hideRating;
public:
    Ransomware() = default;

    Ransomware(double impactRating, int day, int month, int year, const string &name, const vector<string> &regs,
               int cryptRating, double hideRating) : Malware(impactRating, day, month, year, name, regs),
                                                     cryptRating(cryptRating), hideRating(hideRating) {}

    istream &read(istream &is) override {
        Malware::read(is);
        //cout << "Crypt rating? = \n";
        is >> cryptRating;
        //cout << "Hide rating? = \n";
        is >> hideRating;
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        os << "Crypt rating = " << cryptRating << "\n";
        os << "Hide rating = " << hideRating << "\n";
        return os;
    }

    double calculateImpactRating() override {
        double r =  cryptRating + hideRating;
        impactRating = Malware::calculateImpactRating() + r;
        return impactRating;
    }

    string infectionMethod() override {
        return "Ransomware";
    }
};

class Computer {
private:
    static int cntComputers;
    vector <shared_ptr<Malware>> malwares;
    double rating;
    int id;
public:
    Computer() {
        id = ++cntComputers;
    };
    Computer(const vector <shared_ptr<Malware>> &malwares, double rating) : malwares(malwares), rating(rating) {
        id = ++cntComputers;
    }

    friend ostream &operator<<(ostream &os, const Computer &computer);
    friend istream &operator>>(istream &is, Computer &computer) {
        //cout << "How many malwares?: \n";
        int sz;
        is >> sz;
        computer.malwares = vector <shared_ptr<Malware>>(sz);
        for (int i = 0;i < sz;++i) {
            //cout << "What type of malware?(1 -> rootkit, 2 -> keylogger, 3 -> kernel-keylogger, 4 -> ransomware): \n";
            int mal;
            is >> mal;
            shared_ptr<Malware> p = createPtr(mal);
            is >> *p;
            computer.malwares[i] = p;
            p->calculateImpactRating();
            computer.rating += p->getRating();
        }
        return is;
    };
    inline bool operator<(const Computer &c) const {
        return this->rating > c.rating;
    }
    double getRating() {
        return rating;
    }
};

int Computer::cntComputers = 0;

shared_ptr<Malware> createPtr(int mal) {
    shared_ptr<Malware> p;
    switch(mal) {
        case 1: //rootkit
            p = make_shared<Rootkit>();
            break;
        case 2: //keylogger
            p = make_shared<Keylogger>();
            break;
        case 3: //kernel-keylogger
            p = make_shared<KernelKeylogger>();
            break;
        case 4: //ransomware
            p = make_shared<Ransomware>();
            break;
    }
    return p;

}

ostream &operator<<(ostream &os, const Computer &computer) {
    os << "id = " << computer.id << "\n";
    os << "malwares = " << computer.malwares.size() << "\n";
    for (int i = 0;i < computer.malwares.size();++i) {
        os << *computer.malwares[i] << "\n";
    }
    os << "rating = " << computer.rating << "\n";
    return os;
}

class Menu {
private:
    vector <string> options;
    vector <Computer> computers;
public:
    Menu(const vector<string> &options, const vector<Computer> &computers) : options(options), computers(computers) {}

    int listOptions() {
        for (int i = 0;i < options.size();++i) {
            cout << i << ". " << options[i] << "\n";
        }
        cout << "Introduceti cerinta: ";
        int choice;
        cin >> choice;
        return choice;
    }

    void chooseOption(int choice) {
        cout << "Ati ales cerinta " << choice << "\n";
        switch (choice) {
            case 1:
                this->printInfoComputers();
                break;
            case 2:
                this->printInfoSortedComputers();
                break;
            case 3:
                this->printInfoFirstkComputers();
                break;
            case 4:
                this->printInfectedProcent();
                break;
        }

    }

    void printInfoComputers() {
        cout << "Avem " << computers.size() << " calculatoare\n";
        for (auto& i : computers) {
            cout << i << "\n";
        }
        cout << "\n";
    }

    void printInfoSortedComputers() {
        cout << "Avem " << computers.size() << " calculatoare\n";
        auto copy_computers = computers;

        sort(copy_computers.begin(), copy_computers.end(), [&](Computer a, Computer b) {
            return a.getRating() < b.getRating();
        });

        cerr << "\n";
        for (auto& i : copy_computers) {
            cout << i << "\n";
        }
        cout << "\n";
    }

    void printInfoFirstkComputers() {
        int k;
        cout << "k = ";
        cin >> k;
        cout << "Avem " << computers.size() << " calculatoare\n";
        auto copy_computers = computers;
        sort(copy_computers.begin(), copy_computers.end(), [&](Computer a, Computer b) {
            return a.getRating() < b.getRating();
        });
        for (int i = 0;i < min(k, (int)copy_computers.size());++i) {
            cout << copy_computers[i] << "\n";
        }
    }

    void printInfectedProcent() {
        int cnt = 0;
        for (auto& i : computers) {
            if (i.getRating() > 0) {
                ++cnt;
            }
        }
        int all = computers.size();
        cout << "Infected procent = " << 100.0 * cnt / all << "%\n";
    }

    void printMenu() {
        while (true) {
            int choice = this->listOptions();
            if (choice == 0) {
                break;
            }
            chooseOption(choice);
        }
    }
};

int main() {
    ifstream fin("test.in");
    int N;
    fin >> N;
    vector <Computer> a(N);
    for (int i = 0; i < N;++i) {
        fin >> a[i];
        cout << a[i];
    }
    Menu m({"Iesire", "Afiseaza informatii despre calculatoare", "Afiseaza informatii despre calculatoare fiind ordonate dupa rating", "Afiseaza informatii despre primele k calculatoare ordonate dupa rating", "Afiseaza procentul de computere infectate din firma"}, a);
    m.printMenu();
    cout << "Programul s-a incheiat cu succes!\n";
    return 0;
}
