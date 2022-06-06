//
// Created by Alex on 5/3/2022.
//

#include <bits/stdc++.h>
#include <ostream>

using namespace std;

template <typename T>
istream& operator>>(istream& is, vector<T> &v){
    int n;
    T x;
    is >> n;

    v.resize(0);

    for(int i = 0; i < n; ++i) {
        is >> x;
        v.push_back(x);
    }

    return is;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(const auto x: v)
        os << x << "\n";

    return os;
}

class IoBase {
private:
public:
    // metoda citire
    virtual istream& read(istream& is) {
        return is;
    }
    // metoda scriere
    virtual ostream& write(ostream& os) const {
        return os;
    }

    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }

    friend ostream &operator<<(ostream &os, const IoBase &base) {
        return base.write(os);
    }

};

class Malware : public IoBase{

private:
    double impact_rate = 0;
    string infection_date, name, method;
    vector<string> registers;

public:

    Malware() {impact_rate = 0; infection_date = name = method = ""; registers = {};}

    Malware(const string &infectionDate, const string &name,
            const vector<string> &registers, string method = "unknown") : infection_date(infectionDate), name(name),
                                               method(std::move(method)), registers(registers) {
        updateImpactRate();
    }


    const string &getInfectionDate() const {
        return infection_date;
    }

    void setInfectionDate(const string &infectionDate) {
        infection_date = infectionDate;
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        Malware::name = name;
    }

    const string &getMethod() const {
        return method;
    }

    void setMethod(const string &method) {
        Malware::method = method;
    }

    const vector<string> &getRegisters() const {
        return registers;
    }

    void setRegisters(const vector<string> &registers) {
        Malware::registers = registers;
    }

    void setImpactRate(const double &value){
        Malware::impact_rate = value;
    }

    const double &getImpactRate() const{
       return impact_rate;
    }

    ostream &write(ostream &os) const override;

    virtual void updateImpactRate();
};

void Malware::updateImpactRate() {
    for(auto r: registers) {
        if(r == "HKLM-run" || r == "HKCU-run"){
            setImpactRate(getImpactRate() + 20);
            return;
        }
    }

}

ostream &Malware::write(ostream &os) const {
    IoBase::write(os);
    os << "infection_date: " << infection_date << "\nname: " << name << "\nmethod: " << method << "\nimpact_rate: " << impact_rate << "\nregisters:\n" << registers;
    return os;
}

vector<string> default_rootkit_import_list {"System Service Descriptor Table", "SSDT", "NtCreateFile"};
vector<string> default_rootkit_string_list {"ntoskrnl.exe"};

class Rootkit : public Malware{

private:
    vector<string> import_list, special_strings;

public:

    Rootkit(const string &infectionDate, const string &name, const string &method, const vector<string> &registers,
            const vector<string> &importList, const vector<string> &specialStrings) : Malware(infectionDate, name,
                                                                                              registers, method),
                                                                                      import_list(importList),
                                                                                      special_strings(specialStrings) {
        updateImpactRate();
    }

    void updateImpactRate() override;

};

void Rootkit::updateImpactRate() {
    Malware::updateImpactRate();
    for(auto update_string: import_list)
        for(auto s: default_rootkit_import_list)
            if (s == update_string){
                setImpactRate(getImpactRate() + 100);
                return;
            }
    for(auto update_string: special_strings)
        for(auto s: default_rootkit_string_list)
            if (s == update_string){
                setImpactRate(getImpactRate() * 2);
                return;
            }
}

vector<string> default_keylogger_keys = {"[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
vector<string> default_keylogger_functions = {"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};

class Keylogger : public Malware{

private:
    vector<string> functions, keys;

public:
    Keylogger(const string &infectionDate, const string &name, const string &method, const vector<string> &registers,
              const vector<string> &functions, const vector<string> &keys) : Malware(infectionDate, name,
                                                                                     registers, method), functions(functions),
                                                                             keys(keys) {
        updateImpactRate();
    }

    void updateImpactRate() override;

};

void Keylogger::updateImpactRate() {
    Malware::updateImpactRate();
    for(auto update_string: keys)
        for(auto s: default_keylogger_keys)
            if (s == update_string){
                setImpactRate(getImpactRate() + 10);
                return;
            }

    for(auto update_string: functions)
        for(auto s: default_keylogger_functions)
            if (s == update_string){
                setImpactRate(getImpactRate() + 30);
                return;
            }
}

class KernelKeylogger : public Rootkit, public Keylogger{

private:
    bool hiddes_files, hiddes_registers;

public:
    KernelKeylogger(const string &infectionDate, const string &name, const string &method,
                    const vector<string> &registers, const vector<string> &importList,
                    const vector<string> &specialStrings, const string &infectionDate1, const string &name1,
                    const string &method1, const vector<string> &registers1, const vector<string> &functions,
                    const vector<string> &keys, bool hiddesFiles, bool hiddesRegisters) : Rootkit(infectionDate, name,
                                                                                                  method, registers,
                                                                                                  importList,
                                                                                                  specialStrings),
                                                                                          Keylogger(infectionDate1,
                                                                                                    name1, method1,
                                                                                                    registers1,
                                                                                                    functions, keys),
                                                                                          hiddes_files(hiddesFiles),
                                                                                          hiddes_registers(
                                                                                                  hiddesRegisters) {
        updateImpactRate();
    }

    void updateImpactRate() override;
};

void KernelKeylogger::updateImpactRate() {
    Rootkit::updateImpactRate();
    Keylogger::updateImpactRate();
    if(hiddes_files)
        Rootkit::setImpactRate(Rootkit::getImpactRate() + 20);
    if(hiddes_registers)
        Rootkit::setImpactRate(Rootkit::getImpactRate() + 30);

}

class Ransomware : public Malware{

private:
    int crypt_rate;
    double obf_rate;

public:

    Ransomware(double impactRate, const string &infectionDate, const string &name, const string &method,
               const vector<string> &registers, int cryptRate, double obfRate) : Malware(infectionDate, name, registers,
                                                                                         method),
                                                                                crypt_rate(cryptRate),
                                                                                obf_rate(obfRate) {
        updateImpactRate();
    }

    void updateImpactRate() override;

};

void Ransomware::updateImpactRate() {
    Malware::updateImpactRate();
    setImpactRate(getImpactRate() + crypt_rate + obf_rate);
}

class Computer : public IoBase{

private:
    static int next_id;
    vector<Malware> malware_list;
    double final_rating;
    int id;

public:

    Computer(const vector<Malware> &malwareList) : malware_list(malwareList){
        ++next_id; id = next_id;
        final_rating = getSumImpactRate(malware_list);
    }

    static int getNextId() {
        return next_id;
    }

    static void setNextId(int nextId) {
        next_id = nextId;
    }

    const vector<Malware> &getMalwareList() const {
        return malware_list;
    }

    void setMalwareList(const vector<Malware> &malwareList) {
        malware_list = malwareList;
    }

    int getFinalRating() const {
        return final_rating;
    }

    void setFinalRating(int finalRating) {
        final_rating = finalRating;
    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        Computer::id = id;
    }

    double getSumImpactRate(vector<Malware> malwares);

    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "Computer with next_id " << next_id + 1 << "\n";
        cout << "Malware_list: "; is >> malware_list;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os << "id: " << id << "\nfinal rating: " << final_rating << "\nmalware_list:\n" << malware_list;
        return os;
    }

    bool operator<(const Computer &rhs) const{
        return this->final_rating < rhs.final_rating;
    }

    bool operator>(const Computer &rhs) const {
        return this->final_rating > rhs.final_rating;
    }

};

int Computer::next_id = 0;

double Computer::getSumImpactRate(vector<Malware> malwares) {
    double s = 0;
    for(auto m: malwares)
        s += m.getImpactRate();

    return s;
}

void customPrint(vector<Computer> array, int k) {
    if(k <= array.size()) {
        sort(array.begin(), array.end());

        cout << array;
    }
    else{
        cout << "Error: not possible!\n";
    }
}

void showPercentOfInfected(vector<Computer> array){
    int cnt_infected = 0;

    for(auto x: array)
        if(x.getMalwareList().size())
            ++cnt_infected;

    cout << "Percent of infected computers: " << cnt_infected * 100.0 / array.size() << "%\n";
}

int main(){

    vector<Computer> v = {
            Computer({Malware({"data", "nume1", {"HKLM-run", "ebx"}})}),
            Computer({Malware({"data", "nume2", {"eax", "ebx"}}), Malware({"data", "nume3", {"ecx", "edx"}})})
    };

//    cout << v;

    customPrint(v, 2);

    showPercentOfInfected(v);

    return 0;
}