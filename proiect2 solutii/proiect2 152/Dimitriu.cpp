#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class IoBase {
public:
    virtual istream& read(istream& is) {return is;}
    virtual ostream& write(ostream& os){return os;}

    friend istream& operator >> (istream &is, IoBase &base) {return base.read(is);}
    friend ostream& operator << (ostream &os, IoBase &base) {return base.write(os);}
}; ///clasa de citire copiata de la laborator


istream &operator >>(istream &is, vector<string> &v) {
    int N;
    cin >> N;
    v.clear();

    for(int i = 0; i < N; i++) {
        string x;
        cin >> x;
        v.push_back(x);
    }
    return is;
}

ostream &operator <<(ostream &os, vector<string> &v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i];
    }
    return os;
}

class malware : public IoBase {
private:
    double rating;
    int zi, luna, an;
    string name, infection;
    vector <string> modified;
public:
    malware() = default;
    virtual istream& read(istream& is);
    virtual ostream& write(ostream& os);
    virtual double computeRating();
    friend class Rootkit;
    friend class Keylogger;
    friend class Kernel_Key;
    friend class Ransomware;
};

istream& malware::read(istream& is) {
    cin >> rating >> zi >> luna >> an;
    cin.get();
    cin >> name >> infection;
    cin >> modified;
    return is;
}

ostream& malware::write(ostream& os) {
    cout << rating << " " << zi << " " << luna << " " << an << '\n';
    cout << name << " " << infection << '\n';
    cout << modified << '\n';
    return os;
}

double malware::computeRating() {
    double sum= 0;
    for(auto it : modified) {
        if(it == "HKLM-run" || it == "HKCU-run")
            sum += 20;
    }
    rating = sum;
    return sum;
}

class Rootkit : virtual public malware {
private:
    vector <string> imports;
    vector <string> regs;
public:
    Rootkit() = default;
    virtual istream& read(istream& is);
    virtual ostream& write(ostream& os);

    virtual double computeRating();
    friend class Kernel_Key;
};

double Rootkit::computeRating(){
    double sum = malware::computeRating();
    for(auto it : regs) {
        if(it == "System Service Descriptor Table" || it == "SSDT" || it == "NtCreateFile") {
            sum += 100;
        }
    }
    for(auto it : imports) {
        if(it == "ntoskrnl.exe")
            sum *= 2;
    }
    rating = sum;
    return sum;
}

istream& Rootkit::read(istream& is) {
    malware::read(is);
    cin >> imports;
    cin >> regs;
    return is;
}

ostream& Rootkit::write(ostream& os) {
    malware::write(os);
    cout << imports << '\n';
    cout << regs << '\n';
    return os;
}


class Keylogger : virtual public malware {
private:
    vector <string> functions;
    vector <string> keys;
public:
    Keylogger() = default;

    virtual istream& read(istream& is);
    virtual ostream& write(ostream& os);
    virtual double computeRating();
    friend class Kernel_Key;
};

double Keylogger::computeRating() {
    double sum = malware::computeRating();
    for(auto it : keys) {
        if(it == "[Up]" || it == "[Down]" || it == "[Right]" || it == "[Left]" || it == "[NumLock]" || it == "[UP]" || it == "[PageDown]")
            sum += 10;
    }

    for(auto it : functions) {
        if(it == "CreateFileW" || it == "OpenProcess" || it == "ReadFile" || it == "WriteFile" || it == "RegisterHotKey" || it == "SetWindowsHookEx")
            sum += 30;
    }
    rating = sum;
    return sum;
}

istream& Keylogger::read(istream& is) {
    malware::read(is);
    cin >> functions;
    cin >> keys;
    return is;
}

ostream& Keylogger::write(ostream& os) {
    malware::write(os);
    cout << functions << '\n';
    cout << keys << '\n';
    return os;
}

class Kernel_Key : public Rootkit, public Keylogger {
private:
    bool hides_regs, hides_files;
public:

    Kernel_Key() = default;

    istream& read(istream& is);
    ostream& write(ostream& os);
    double computeRating() {double sum = Keylogger::computeRating() + Rootkit::computeRating() - malware::computeRating(); if(hides_files) sum += 20; if(hides_regs) sum += 30; rating = sum; return sum;}
};

istream& Kernel_Key::read(istream& is) {
    malware::read(is);
    cin >> imports;
    cin >> regs;
    cin >> functions;
    cin >> keys;
    cin >> hides_regs >> hides_files;
    return is;
}

ostream& Kernel_Key::write(ostream& os) {
    malware::write(os);
    cout << imports << '\n';
    cout << regs << '\n';
    cout << functions << '\n';
    cout << keys << '\n';
    cout << hides_regs << " " << hides_files << '\n';
    return os;
}

class Ransomware : public malware {
private:
    int crypt;
    double obfuscare;
public:
    Ransomware() = default;

    istream& read(istream& is);
    ostream& write(ostream& os);
    double computeRating() {double sum = malware::computeRating() + crypt + obfuscare;rating = sum; return sum;};
};

istream& Ransomware::read(istream& is) {
    malware::read(is);
    try {
        cin >> crypt >> obfuscare;
        if(!(crypt >= 1 && crypt <= 10))
            throw;
    }
    catch (...) {
        cout << "Crypt trebuie sa fie un numar intre 1 si 10!!! Recititi crypt: ";
        cin >> crypt;
    }

    return is;
}
ostream& Ransomware::write(ostream& os) {
    malware::write(os);
    cout << crypt << " " << obfuscare << '\n';
    return os;
}

class Computer : public IoBase{
private:
    static int count_id, infected;
    int id;
    double rating;
    vector <shared_ptr<malware>> virusi;
public:
    Computer() {id = ++count_id;virusi = {};rating = 0;}
    ostream& write(ostream& os);
    static double infectpercent() {return double(infected) / double(count_id) * 100;}
    double getRating();
    void addRootkit(Rootkit x) {virusi.push_back(make_shared<Rootkit>(x));};
    void addKeylogger(Keylogger x) {virusi.push_back(make_shared<Keylogger>(x));};
    void addKernelkey(Kernel_Key x) {virusi.push_back(make_shared<Kernel_Key>(x));};
    void addRansomware(Ransomware x) {virusi.push_back(make_shared<Ransomware>(x));};
    int getID() const {return id;}

    bool operator < (const Computer &other) const{return rating < other.rating;}
};

ostream& Computer::write(ostream &os){
    IoBase::write(os);
    cout << id << " " << rating << '\n';
    for(int i = 0; i < virusi.size(); i++)
        cout << *virusi[i];
    cout << '\n';
    return os;
}

double Computer::getRating() {
    double sum = 0;
    for(auto it : virusi) {
    sum += it->computeRating();
    }
    rating = sum;
    return sum;
}

int Computer::count_id, Computer::infected;

class BaseMenu {
public:
    virtual void listOptions() {}
    virtual int chooseOption(int first, int last) {return 1;}
    virtual void mainLoop() {}
};

class SimpleMenu : public BaseMenu {
private:
    map <int, Computer> comps;
public:
    void listOptions() override{
        cout << "1) Adauga Computer" << '\n';
        cout << "2) Afiseaza Computere" << '\n';
        cout << "3) Afiseaza Computere ordonate" << '\n';
        cout << "4) Afiseaza primele K Computere ordonate" << '\n';
        cout << "5) Procent infectare" << '\n';
        cout << "6) Iesire" << '\n';
    }

    int chooseOption(int first, int last) override{
        cout << "Alegeti optiunea: ";
        int x; cin >> x;
        if(!(x >= first && x <= last)) {
            return -1;
        }
        return x;
    }

    void mainLoop() override{
        while(true) {
            listOptions();
            int x = chooseOption(1, 6);
            while( x == -1) {
                cout << "Optiune inexistenta!" << '\n';
                x = chooseOption(1, 6);
            }

            if(x == 6)
                break;
            if(x == 5) {
                cout << "Procent infecater: " << Computer::infectpercent() << '\n';
            }

            if(x == 2) {
                for(auto it : comps) {
                    cout << it.second;
                }
            }

            if(x == 3) {
                vector<Computer> v;
                for(auto it : comps) {
                    v.push_back(it.second);
                }
                sort(v.begin(), v.end());
                for(int i = 0; i < v.size(); i++)
                    cout << v[i];
            }

            if(x == 4) {
                int K; cout << "Introduceti numarul de calculatoare dorti: "; cin >> K;
                vector<Computer> v;
                for(auto it : comps) {
                    v.push_back(it.second);
                }
                sort(v.begin(), v.end());
                for(int i = 0; i < max(int(v.size()), K); i++)
                    cout << v[i];
            }

            if(x == 1) {
                Computer crt;
                while(true) {
                    cout << "1) Adauga Rootkit" << '\n';
                    cout << "2) Adauga Keylogger" << '\n';
                    cout << "3) Adauga Kernel-Keylogger" << '\n';
                    cout << "4) Adauga Ransomware" << '\n';
                    cout << "5) Citire terminata" << '\n';
                    int xx = chooseOption(1, 5);
                    while( xx == -1) {
                        cout << "Optiune inexistenta!" << '\n';
                        xx = chooseOption(1, 5);
                    }

                    if(xx == 5)
                        break;
                    if(xx == 1) {Rootkit vrs; cin >> vrs;crt.addRootkit(vrs);}
                    if(xx == 2) {Keylogger vrs; cin >> vrs;crt.addKeylogger(vrs);}
                    if(xx == 3) {Kernel_Key vrs; cin >> vrs;crt.addKernelkey(vrs);}
                    if(xx == 4) {Ransomware vrs; cin >> vrs;crt.addRansomware(vrs);}
                }
                crt.getRating();
                comps[crt.getID()] = crt;
            }
        }
    }
};

int main() {
    SimpleMenu main;
    main.mainLoop();
    return 0;
}