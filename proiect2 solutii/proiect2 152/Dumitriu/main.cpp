#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "IoBase.h"
#include "Functions.h"

using namespace std;

class Data : public IoBase{
private:
    int zi;
    int luna;
    int an;
public:
    Data(int zi, int luna, int an) : zi(zi), luna(luna), an(an) {}
    Data() {}

    istream &read(istream &is) override {
        cout << "Ziua infectarii:\n";
        is >> zi;
        cout << "Luna infectarii (in cifre):\n";
        is >> luna;
        cout << "Anul infectarii:\n";
        is >> an;
        return is;
    }

    ostream &write(ostream &os) const override {
        os << zi << ".";
        if(luna < 10)
            os << "0";
        os << luna << "." << an;
        return os;
    }
};

class Malware : public IoBase {
protected:
    double rating;
    Data data;
    string name, infectionMethod;
    vector<string> modifiedRegisters;

public:
    Malware(double rating, const Data &data, const string &name, const string &infectionMethod,
            const vector<string> &modifiedRegisters) : rating(rating), data(data), name(name),
                                                       infectionMethod(infectionMethod),
                                                       modifiedRegisters(modifiedRegisters) {}

    Malware() {}

    double getRating() const {
        return rating;
    }

    istream &read(istream &is) override {
        cout << "\nNume: ";
        is >> name;
        cout << "Data infectarii: ";
        is >> data;
        cout << "Rating (nr real): ";
        is >> rating;

        int n;
        string reg;
        cout << "Nr. registri modificati: ";
        is >> n;
        for(int i = 0; i < n; i++) {
            cout << "Registrul " << i + 1 << ": ";
            is >> reg;
            modifiedRegisters.push_back(reg);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        return IoBase::write(os);
    }
};

class Rootkit : public Malware {
private:
    vector<string> importList;
    vector<string> significantList;

public:
    Rootkit(double rating, const Data &data, const string &name, const string &infectionMethod,
            const vector<string> &modifiedRegisters, const vector<string> &importList,
            const vector<string> &significantList) : Malware(rating, data, name, infectionMethod, modifiedRegisters),
                                                     importList(importList), significantList(significantList) {}

    Rootkit() {}

    void calculateRating() {
        rating = 0;
        vector<string> checkString = {"System Service Descriptor Table", "SSDT", "NtCreateFile"};
        string checkImport = "ntoskrnl.exe";

        for(auto x : significantList) {
            for(auto y : checkString) {
                if(x == y)
                    rating += 100;
            }
        }

        bool ok = false;
        for(auto x : importList) {
            if(x == checkImport)
                ok = true;
        }
        if(ok)
            rating *= 2;
    }

    istream &read(istream &is) override {
        cout << "\nNume: ";
        is >> name;
        cout << "Data infectarii: ";
        is >> data;

        int n;
        string aux;
        cout << "Nr. registri modificati: ";
        is >> n;
        for(int i = 0; i < n; i++) {
            cout << "Registrul " << i + 1 << ": ";
            is >> aux;
            modifiedRegisters.push_back(aux);
        }

        cout << "Nr. importuri: ";
        is >> n;
        for(int i = 0; i < n; i++) {
            cout << "Importul " << i + 1 << ": ";
            is >> aux;
            importList.push_back(aux);
        }

        cout << "Nr. stringuri semnificative: ";
        is >> n;
        for(int i = 0; i < n; i++) {
            cout << "Stringul " << i + 1 << ": ";
            is >> aux;
            significantList.push_back(aux);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        os << "Rootkit\n";
        os << "Nume: " << name << "\n";
        os << "Data infectarii: " << data << "\n";
        os << "Rating: " << rating << "\n";
        return os;
    }
};

class Keylogger : public Malware {
private:
    vector<string> functionList;
    vector<string> keyList;

private:
public:
    Keylogger(double rating, const Data &data, const string &name, const string &infectionMethod,
              const vector<string> &modifiedRegisters, const vector<string> &functionList,
              const vector<string> &keyList) : Malware(rating, data, name, infectionMethod, modifiedRegisters),
                                               functionList(functionList), keyList(keyList) {}

    Keylogger() {}

    istream &read(istream &is) override {
        cout << "\nNume: ";
        is >> name;
        cout << "Data infectarii: ";
        is >> data;

        int n;
        string aux;
        cout << "Nr. registri modificati: ";
        is >> n;
        for(int i = 0; i < n; i++) {
            cout << "Registrul " << i + 1 << ": ";
            is >> aux;
            modifiedRegisters.push_back(aux);
        }

        cout << "Nr. functii: ";
        is >> n;
        for(int i = 0; i < n; i++) {
            cout << "Functia " << i + 1 << ": ";
            is >> aux;
            functionList.push_back(aux);
        }

        cout << "Nr. taste: ";
        is >> n;
        for(int i = 0; i < n; i++) {
            cout << "Tasta " << i + 1 << ": ";
            is >> aux;
            keyList.push_back(aux);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        return Malware::write(os);
    }

};

class KernelKeylogger : public Malware {
    //TODO: verifica
};

class Ransomware : public Malware {
private:
    int cryptRating;
    double obfuscationRating;

public:
    Ransomware(double rating, const Data &data, const string &name, const string &infectionMethod,
               const vector<string> &modifiedRegisters, int cryptRating, double obfuscationRating) : Malware(rating,
                                                                                                             data, name,
                                                                                                             infectionMethod,
                                                                                                             modifiedRegisters),
                                                                                                     cryptRating(
                                                                                                             cryptRating),
                                                                                                     obfuscationRating(
                                                                                                             obfuscationRating) {}

    Ransomware() {}

    istream &read(istream &is) override {
        cout << "\nNume: ";
        is >> name;
        cout << "Data infectarii: ";
        is >> data;

        int n;
        string aux;
        cout << "Nr. registri modificati: ";
        is >> n;
        for(int i = 0; i < n; i++) {
            cout << "Registrul " << i + 1 << ": ";
            is >> aux;
            modifiedRegisters.push_back(aux);
        }

        cout << "Rating criptare: ";
        is >> cryptRating;
        cout << "Rating obfuscare: ";
        is >> obfuscationRating;

        return is;
    }

    ostream &write(ostream &os) const override {
        return Malware::write(os);
    }
};

class Computer : public IoBase {
private:
    static int autoId;
    int id;
    vector<shared_ptr<Malware>> malwareList;
    double rating;

public:

    Computer(const vector<shared_ptr<Malware>> &malwareList) : malwareList(malwareList) {
        id = ++autoId;
    }

    Computer() {
        id = ++autoId;
    }

    void calculateRating() {
        rating = 0;
        for(auto x : malwareList) {
            rating += x->getRating();
        }
    }

    double getRating() {
        this->calculateRating();
        return rating;
    }

    istream &read(istream &is) override {
        int n;
        int tip;
        cout << "Numarul de virusi: ";
        is >> n;
        for(int i = 0; i < n; i++) {
            cout << "Virusul 1:\n";
            cout << "Tip? (1-rootkit, 2-keylogger, 3-kernel-keylogger, 4-ransomware): ";
            is >> tip;
            switch(tip) {
                case 1: {
                    Rootkit rootkit;
                    is >> rootkit;
                    malwareList.push_back(make_shared<Rootkit>(rootkit));
                    break;
                }
                case 2: {
                    Keylogger keylogger;
                    is >> keylogger;
                    malwareList.push_back(make_shared<Keylogger>(keylogger));
                    break;
                }
                case 3: {
                    //TODO
                    break;
                }
                case 4: {
                    Ransomware ransomware;
                    is >> ransomware;
                    malwareList.push_back(make_shared<Ransomware>(ransomware));
                }
                default: {
                    break;
                }
            }
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        os << "Calculatorul " << id << ":\n";
        os << "Rating: " << rating << "\n";
        int i = 0;
        for(auto x : malwareList) {
            os << "Virusul " << i + 1 << ":\n";
            i++;
            os << *x << "\n";
        }
        return os;
    }
};

int Computer::autoId = 0;

int main() {
    Computer a;
    cin >> a;
    a.calculateRating();
    cout << a;

    return 0;
}