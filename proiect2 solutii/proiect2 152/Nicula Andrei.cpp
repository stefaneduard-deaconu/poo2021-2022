/// Facut dupa modelul prezentat de Oana la tutoriate

#include <bits/stdc++.h>

using namespace std;

class Malware{
protected:
    double impact;
    int day, month, year;
    string name, methodOfInfection;
    vector <string> registers;


public:
    Malware();
    Malware(const Malware& ob);
    Malware& operator=(const Malware& ob);
    virtual ~Malware();
    Malware(double impact, int day, int month, int year, const string &name, const string &methodOfInfection,
            const vector<string> &registers);

    double getImpact() const;
    void setImpact(double impact);

    int getDay() const;
    void setDay(int day);

    int getMonth() const;
    void setMonth(int month);

    int getYear() const;
    void setYear(int year);

    const string &getName() const;
    void setName(const string &name);

    const string &getMethodOfInfection() const;
    void setMethodOfInfection(const string &methodOfInfection);

    const vector<string> &getRegisters() const;
    void setRegisters(const vector<string> &registers);

    friend istream& operator>>(istream& is, Malware& ob){
        return ob.readMalware(is);
    }
    friend ostream& operator<<(ostream& os, Malware& ob){
        return ob.printMalware(os);
    }

    virtual istream& readMalware(istream& is) = 0;
    virtual ostream& printMalware(ostream& os) = 0;
    virtual double calculeaza() = 0;
};
Malware::Malware():registers() {
    Malware::impact = 0;
    Malware::day = 0;
    Malware::month = 0;
    Malware::year = 0;
    Malware::methodOfInfection = "";
    Malware::name = "";
}
Malware::Malware(const Malware &ob) {
    Malware::impact = ob.impact;
    Malware::day = ob.day;
    Malware::month = ob.month;
    Malware::year = ob.year;
    Malware::name = ob.name;
    Malware::methodOfInfection = ob.methodOfInfection;
    Malware::registers = ob.registers;
}
Malware & Malware::operator=(const Malware &ob) {
    Malware::impact = ob.impact;
    Malware::day = ob.day;
    Malware::month = ob.month;
    Malware::year = ob.year;
    Malware::name = ob.name;
    Malware::methodOfInfection = ob.methodOfInfection;
    Malware::registers = ob.registers;
    return *this;
}
Malware::~Malware() {
    Malware::impact = 0;
    Malware::day = 0;
    Malware::month = 0;
    Malware::year = 0;
    Malware::name.clear();
    Malware::methodOfInfection.clear();
    Malware::registers.clear();
}

double Malware::getImpact() const {
    return Malware::impact;
}

void Malware::setImpact(double impact) {
    Malware::impact = impact;
}

int Malware::getDay() const {
    return Malware::day;
}

void Malware::setDay(int day) {
    Malware::day = day;
}

int Malware::getMonth() const {
    return Malware::month;
}

void Malware::setMonth(int month) {
    Malware::month = month;
}

int Malware::getYear() const {
    return Malware::year;
}

void Malware::setYear(int year) {
    Malware::year = year;
}

const string &Malware::getName() const {
    return Malware::name;
}

void Malware::setName(const string &name) {
    Malware::name = name;
}

const string &Malware::getMethodOfInfection() const {
    return Malware::methodOfInfection;
}

void Malware::setMethodOfInfection(const string &methodOfInfection) {
    Malware::methodOfInfection = methodOfInfection;
}

const vector<string> &Malware::getRegisters() const {
    return Malware::registers;
}

void Malware::setRegisters(const vector<string> &registers) {
    Malware::registers = registers;
}

Malware::Malware(double impact, int day, int month, int year, const string &name, const string &methodOfInfection,
                 const vector<string> &registers) : impact(impact), day(day), month(month), year(year), name(name),
                                                    methodOfInfection(methodOfInfection), registers(registers) {}


class Rootkit: virtual public Malware{
protected:
    vector <string> imports;
    vector <string> signifiers;

public:
    const vector<string> &getImports() const;
    void setImports(const vector<string> &imports);

    const vector<string> &getSignifiers() const;
    void setSignifiers(const vector<string> &signifiers);

    Rootkit();
    Rootkit(const Rootkit& ob);
    Rootkit& operator=(const Rootkit& ob);
    virtual ~Rootkit();
    Rootkit(double impact, int day, int month, int year, const string &name, const string &metodaDeInfectare,
            const vector<string> &registers, const vector<string> &imports, const vector<string> &signifiers);

    virtual istream& readMalware(istream& is);
    virtual ostream& printMalware(ostream& os);
    virtual double calculeaza();
};

double Rootkit::calculeaza() {
    double val = Rootkit::impact;

    for (int i = 0; i < Rootkit::registers.size(); i++) {
        if (Rootkit::registers[i] == "HKLM-run" || Rootkit::registers[i] == "HKCU-run") {
            val += 20;
            break;
        }
    }

    for (int i = 0; i < Rootkit::signifiers.size(); i++) {
        if (Rootkit::signifiers[i] == "System Service Descriptor Table" || Rootkit::signifiers[i] == "SSDT" || Rootkit::signifiers[i] == "NtCreateFile" ) {
            val += 100;
            break;
        }
    }

    for (int i = 0; i < Rootkit::imports.size(); i++) {
        if(Rootkit::imports[i] == "ntoskrnl.exe") {
            val = val * 2;
            break;
        }
    }
    return val;
}

Rootkit::Rootkit():Malware(),  imports(), signifiers(){}

Rootkit::Rootkit(const Rootkit &ob) {
    Rootkit::impact = ob.impact;
    Rootkit::day = ob.day;
    Rootkit::month = ob.month;
    Rootkit::year = ob.year;
    Rootkit::name = ob.name;
    Rootkit::methodOfInfection = ob.methodOfInfection;
    Rootkit::registers = ob.registers;
    Rootkit::imports = ob.imports;
    Rootkit::signifiers = ob.signifiers;
}

Rootkit & Rootkit::operator=(const Rootkit &ob) {
    Rootkit::impact = ob.impact;
    Rootkit::day = ob.day;
    Rootkit::month = ob.month;
    Rootkit::year = ob.year;
    Rootkit::name = ob.name;
    Rootkit::methodOfInfection = ob.methodOfInfection;
    Rootkit::registers = ob.registers;
    Rootkit::imports = ob.imports;
    Rootkit::signifiers = ob.signifiers;
    return *this;
}
Rootkit::~Rootkit(){
    Rootkit::imports.clear();
    Rootkit::signifiers.clear();
}

Rootkit::Rootkit(double impact, int day, int month, int year, const string &name, const string &methodOfInfection,
                 const vector<string> &registers, const vector<string> &imports, const vector<string> &signifiers)
        : Malware(impact, day, month, year, name, methodOfInfection, registers), imports(imports),
          signifiers(signifiers) {}

const vector<string> &Rootkit::getImports() const {
    return Rootkit::imports;
}

void Rootkit::setImports(const vector<string> &imports) {
    Rootkit::imports = imports;
}

const vector<string> &Rootkit::getSignifiers() const {
    return Rootkit::signifiers;
}

void Rootkit::setSignifiers(const vector<string> &signifiers) {
    Rootkit::signifiers = signifiers;
}
istream & Rootkit::readMalware(istream &is) {
    cout << "Impact:\n";
    is >> Rootkit::impact;
    is.get();
    cout << "Date:\n";
    cout << "Year:\n";
    bool bisect = 0;
    int dayle[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> Rootkit::year;
    is.get();
    if ((Rootkit::year % 4 == 0 && Rootkit::year % 100 != 0) || Rootkit::year % 400 == 0) {
        bisect = 1;
    }
    cout << "Month:\n";
    while (true) {
        try {
            is >> Rootkit::month;
            is.get();
            if (Rootkit::month < 1 || Rootkit::month > 12) {
                throw string("invalid month");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }
    cout << "Day:\n";
    while (true) {
        try {
            is >> Rootkit::day;
            is.get();
            if (Rootkit::day < 1 || (Rootkit::month == 2 && bisect == 1 && Rootkit::day > 29) || Rootkit::day > dayle[Rootkit::month]) {
                throw string("invalid day");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }
    cout << "Name:\n";
    getline(is, Rootkit::name);
    cout << "Method of infection:\n";
    getline(is, Rootkit::methodOfInfection);

    int nr;

    while (true) {
        try {

            cout << "Number of registers:\n";
            is >> nr;
            is.get();
            if (nr < 0) {
                throw string("invalid number");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }

    for (int i = 0; i < nr; i++) {
        cout << "Register:\n";
        string s;
        getline(is, s);
        registers.push_back(s);
    }

    while (true) {
        try {
            cout << "Number of imports:\n";
            is >> nr;
            is.get();
            if (nr < 0) {
                throw string("invalid number");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }

    for (int i = 0; i < nr ; i++) {
        cout << "Import:\n";
        string s;
        getline(is, s);
        imports.push_back(s);
    }

    while (true) {
        try {
            cout << "Number of signifiers:\n";
            is >> nr;
            is.get();
            if (nr < 0) {
                throw string("invalid number");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }

    for (int i = 0; i < nr; i++) {
        cout << "Signifier:\n";
        string s;
        getline(is, s);
        signifiers.push_back(s);
    }

    return is;
}

ostream & Rootkit::printMalware(ostream &os) {
    os << "Impact: " << Rootkit::impact << "\n";
    os << "Date: " << Rootkit::day << '/' << Rootkit::month << '/' << Rootkit::year << '\n';
    os << "Name: " << Rootkit::name << '\n';
    os << "Method of infection: " << Rootkit::methodOfInfection << '\n';
    os << "Registers:\n";
    for (int i = 0; i < Rootkit::registers.size(); i++) {
        cout  << Rootkit::registers[i] << '\n';
    }
    os  << "Imports:\n";
    for (int i = 0; i < Rootkit::imports.size(); i++) {
        cout << Rootkit::imports[i] << '\n';
    }
    os << "Signifiers:\n";
    for (int i = 0; i < Rootkit::signifiers.size(); i++) {
        os << Rootkit::signifiers[i] << '\n';
    }
    return os;
}

class Keylogger : virtual public Malware {
protected:
    vector <string> functions;
    vector <string> keyStrokes;

public:
    const vector<string> &getFunctions() const;
    void setFunctions(const vector<string> &functions);

    const vector<string> &getKeyStrokes() const;
    void setKeyStrokes(const vector<string> &keyStrokes);


    Keylogger() = default;
    Keylogger(double impact, int day, int month, int year, const string &name, const string &metodaDeInfectare,
              const vector<string> &registers, const vector<string> &functions, const vector<string> &keyStrokes);

    Keylogger(const Keylogger& ob);
    Keylogger& operator=(const Keylogger& ob);
    virtual ~Keylogger();

    virtual istream& readMalware(istream& is);
    virtual ostream& printMalware(ostream& os);

    virtual double calculeaza();
};

double Keylogger::calculeaza() {
    double val = Keylogger::impact;

    for (int i = 0; i < Keylogger::registers.size(); i++) {
        if (Keylogger::registers[i] == "HKLM-run" || Keylogger::registers[i] == "HKCU-run") {
            val += 20;
            break;
        }
    }

    for (int i = 0; i < Keylogger::functions.size(); i++) {
        if (Keylogger::functions[i] == "CreateFileW" || Keylogger::functions[i] == "OpenProcess" || Keylogger::functions[i] == "ReadFile" ||
                Keylogger::functions[i] == "WriteFile" || Keylogger::functions[i] == "RegisterHotKey" || Keylogger::functions[i] == "SetWindowsHookEx") {
            val += 30;
        }
    }

    for (int i = 0; i < Keylogger::keyStrokes.size(); i++) {
        if(Keylogger::keyStrokes[i] == "Up" || Keylogger::keyStrokes[i] == "Num Lock" || Keylogger::keyStrokes[i] == "Down" ||
            Keylogger::keyStrokes[i] =="Right" || Keylogger::keyStrokes[i] == "UP"  || Keylogger::keyStrokes[i] == "Left" || Keylogger::keyStrokes[i] == "PageDown") {
            val += 10;
        }
    }
    return val;
}

istream & Keylogger::readMalware(istream &is) {
    cout << "Impact:\n";
    is >> Keylogger::impact;
    is.get();
    cout << "Date:\n";
    cout << "Year:\n";
    bool bisect = 0;
    int dayle[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> Keylogger::year;
    is.get();
    if ((Keylogger::year % 4 == 0 && Keylogger::year % 100 != 0) || Keylogger::year % 400 == 0) {
        bisect = 1;
    }
    cout << "Month:\n";
    while (true) {
        try {
            is >> Keylogger::month;
            is.get();
            if (Keylogger::month < 1 || Keylogger::month > 12) {
                throw string("invalid month");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }
    cout << "Day:\n";
    while (true) {
        try {
            is >> Keylogger::day;
            is.get();
            if (Keylogger::day < 1 || (Keylogger::month == 2 && bisect == 1 && Keylogger::day > 29) || Keylogger::day > dayle[Keylogger::month]) {
                throw string("invalid day");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }
    cout << "Name:\n";
    getline(is, Keylogger::name);
    cout << "Method of infection:\n";
    getline(is, Keylogger::methodOfInfection);

    int nr;

    while (true) {
        try {

            cout << "Number of registers:\n";
            is >> nr;
            is.get();
            if (nr < 0) {
                throw string("invalid number");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }

    for (int i = 0; i < nr; i++) {
        cout << "Register:\n";
        string s;
        getline(is, s);
        registers.push_back(s);
    }

    while(true){
        try{

            cout << "Numar functions:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }

    for(int i = 0;i < nr ; ++i){
        cout << "Functions:\n";
        string s;
        getline(is, s);
        functions.push_back(s);
    }

    while (true) {
        try {
            cout << "Number of keyStrokes:\n";
            is >> nr;
            is.get();
            if (nr < 0) {
                throw string("invalid number");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }

    for (int i = 0; i < nr; i++) {
        cout << "KeyStrokes:\n";
        string s;
        getline(is, s);
        keyStrokes.push_back(s);
    }

    return is;
}

ostream & Keylogger::printMalware(ostream &os) {
    os << "Impact: " << impact << "\n";
    os << "Date: " << day << '/' << month << '/' << year << '\n';
    os << "Name: " << name << '\n';
    os << "Method of infection: " << methodOfInfection << '\n';
    os << "Registers:\n";
    for (int i = 0; i < registers.size(); i++) {
        cout  << registers[i] << '\n';
    }
    os  << "Functions:\n";
    for (int i = 0; i < functions.size(); i++) {
        cout  << functions[i] << '\n';
    }
    os << "KeyStrokes:\n";
    for (int i = 0; i < keyStrokes.size(); i++) {
        os << keyStrokes[i] << '\n';
    }
    return os;
}

Keylogger::Keylogger(const Keylogger &ob) {
    impact = ob.impact;
    day = ob.day;
    month = ob.month;
    year = ob.year;
    name = ob.name;
    methodOfInfection = ob.methodOfInfection;
    registers = ob.registers;
    functions = ob.functions;
    keyStrokes = ob.keyStrokes;
}
Keylogger & Keylogger::operator=(const Keylogger &ob) {
    impact = ob.impact;
    day = ob.day;
    month = ob.month;
    year = ob.year;
    name = ob.name;
    methodOfInfection = ob.methodOfInfection;
    registers = ob.registers;
    functions = ob.functions;
    keyStrokes = ob.keyStrokes;
    return *this;
}
Keylogger::~Keylogger(){
    functions.clear();
    keyStrokes.clear();
}

Keylogger::Keylogger(double impact, int day, int month, int year, const string &name, const string &methodOfInfection,
                     const vector<string> &registers, const vector<string> &functions, const vector<string> &keyStrokes)
        : Malware(impact, day, month, year, name, methodOfInfection, registers), functions(functions), keyStrokes(keyStrokes) {}

const vector<string> &Keylogger::getFunctions() const {
    return Keylogger::functions;
}

void Keylogger::setFunctions(const vector<string> &functions) {
    Keylogger::functions = functions;
}

const vector<string> &Keylogger::getKeyStrokes() const {
    return Keylogger::keyStrokes;
}

void Keylogger::setKeyStrokes(const vector<string> &keyStrokes) {
    Keylogger::keyStrokes = keyStrokes;
}

class KernelKeylogger: public Rootkit, public Keylogger{
private:
    bool hideFiles;
    bool hideRegisters;

public:
    KernelKeylogger() = default;
    KernelKeylogger(const KernelKeylogger& ob);
    KernelKeylogger& operator=(const KernelKeylogger& ob);
    ~KernelKeylogger();

    KernelKeylogger(double impact, int day, int month, int year, const string &name, const string &methodOfInfection,
                    const vector<string> &registers, const vector<string> &imports,
                    const vector<string> &signifiers, const vector<string> &functions, const vector<string> &keyStrokes, bool hideFiles, bool hideRegisters);

    istream& readMalware(istream& is);
    ostream& printMalware(ostream& os);
    double calculeaza();
};

double KernelKeylogger::calculeaza() {
    double val = impact;

    for (int i = 0; i < registers.size(); i++) {
        if (registers[i] == "HKLM-run" || registers[i] == "HKCU-run") {
            val += 20;
            break;
        }
    }

    for (int i = 0; i < signifiers.size(); i++) {
        if(signifiers[i] == "System Service Descriptor Table" || signifiers[i] == "SSDT" || signifiers[i] == "NtCreateFile") {
            val += 100;
            break;
        }

    }

    for(int i = 0; i < imports.size(); i++) {
        if (imports[i] == "ntoskrnl.exe") {
            val = val * 2;
            break;
        }
    }

    for (int i = 0; i < functions.size(); i++) {
        if(functions[i] == "CreateFileW" || functions[i] == "OpenProcess" || functions[i] == "ReadFile" || functions[i] =="WriteFile" ||
            functions[i] == "RegisterHotKey"  || functions[i] == "SetWindowsHookEx") {
            val += 30;
        }
    }

    for (int i = 0; i < keyStrokes.size(); i++) {
        if (keyStrokes[i] == "Up" || keyStrokes[i] == "Num Lock" || keyStrokes[i] == "Down" ||
            keyStrokes[i] == "Right" || keyStrokes[i] == "UP" || keyStrokes[i] == "Left" || keyStrokes[i] == "PageDown") {
            val += 10;
        }
    }

    if (hideRegisters) {
        val += 30;
    }

    if (hideFiles) {
        val += 20;
    }

    return val;
}

ostream & KernelKeylogger::printMalware(ostream &os) {
    os << "Impact: " << impact << "\n";
    os << "Date: " << day << '/' << month << '/' << year << '\n';
    os << "Name: " << name << '\n';
    os << "Method of infection: " << methodOfInfection << '\n';
    os << "Registers:\n";
    for (int i = 0; i < registers.size(); i++) {
        cout  << registers[i] << '\n';
    }
    os  << "Imports:\n";
    for (int i = 0; i < imports.size(); i++) {
        cout  << imports[i] << '\n';
    }
    os << "Signifiers:\n";
    for (int i = 0; i < signifiers.size(); i++) {
        os << signifiers[i] << '\n';
    }
    os  << "Functions:\n";
    for (int i = 0; i < functions.size(); i++) {
        cout  << functions[i] << '\n';
    }
    os << "KeyStrokes:\n";
    for (int i = 0; i < keyStrokes.size(); i++) {
        os << keyStrokes[i] << '\n';
    }
    return os;
}

istream & KernelKeylogger::readMalware(istream &is) {
    cout << "Impact:\n";
    is >> Keylogger::impact;
    is.get();
    cout << "Date:\n";
    cout << "Year:\n";
    bool bisect = 0;
    int dayle[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> Keylogger::year;
    is.get();
    if ((Keylogger::year % 4 == 0 && Keylogger::year % 100 != 0) || Keylogger::year % 400 == 0) {
        bisect = 1;
    }
    cout << "Month:\n";
    while (true) {
        try {
            is >> Keylogger::month;
            is.get();
            if (Keylogger::month < 1 || Keylogger::month > 12) {
                throw string("invalid month");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }
    cout << "Day:\n";
    while (true) {
        try {
            is >> Keylogger::day;
            is.get();
            if (Keylogger::day < 1 || (Keylogger::month == 2 && bisect == 1 && Keylogger::day > 29) || Keylogger::day > dayle[Keylogger::month]) {
                throw string("invalid day");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }
    cout << "Name:\n";
    getline(is, Keylogger::name);
    cout << "Method of infection:\n";
    getline(is, Keylogger::methodOfInfection);

    int nr;

    while (true) {
        try {

            cout << "Number of registers:\n";
            is >> nr;
            is.get();
            if (nr < 0) {
                throw string("invalid number");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }

    for (int i = 0; i < nr; i++) {
        cout << "Register:\n";
        string s;
        getline(is, s);
        registers.push_back(s);
    }

    while(true){
        try{

            cout << "Numar functions:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }

    for(int i = 0;i < nr ; ++i){
        cout << "Functions:\n";
        string s;
        getline(is, s);
        functions.push_back(s);
    }

    while (true) {
        try {
            cout << "Number of keyStrokes:\n";
            is >> nr;
            is.get();
            if (nr < 0) {
                throw string("invalid number");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }

    for (int i = 0; i < nr; i++) {
        cout << "KeyStrokes:\n";
        string s;
        getline(is, s);
        keyStrokes.push_back(s);
    }

    while (true) {
        try {
            cout << "Number of imports:\n";
            is >> nr;
            is.get();
            if (nr < 0) {
                throw string("invalid number");
            }
            else {
                break;
            }
        }
        catch (string s){
            cout << s << '\n';
        }
    }

    for (int i = 0; i < nr; i++) {
        cout << "Import:\n";
        string s;
        getline(is, s);
        imports.push_back(s);
    }

    while (true) {
        try {
            cout << "Number of signifiers:\n";
            is >> nr;
            is.get();
            if (nr < 0) {
                throw string("invalid number");
            }
            else {
                break;
            }
        }
        catch (string s){
            cout << s << '\n';
        }
    }

    for (int i = 0; i < nr; i++) {
        cout << "Signifier:\n";
        string s;
        getline(is, s);
        signifiers.push_back(s);
    }

    return is;
}

KernelKeylogger::KernelKeylogger(const KernelKeylogger &ob) {
    impact = ob.impact;
    day = ob.day;
    month = ob.month;
    name = ob.name;
    year = ob.year;
    methodOfInfection = ob.methodOfInfection;
    registers = ob.registers;
    functions = ob.functions;
    keyStrokes = ob.keyStrokes;
    imports = ob.imports;
    signifiers = ob.signifiers;
}

KernelKeylogger & KernelKeylogger::operator=(const KernelKeylogger &ob) {
    impact = ob.impact;
    day = ob.day;
    month = ob.month;
    name = ob.name;
    year = ob.year;
    methodOfInfection = ob.methodOfInfection;
    registers = ob.registers;
    functions = ob.functions;
    keyStrokes = ob.keyStrokes;
    imports = ob.imports;
    signifiers = ob.signifiers;
    return *this;
}

KernelKeylogger::~KernelKeylogger(){
    hideFiles = hideRegisters = 0;
}

KernelKeylogger::KernelKeylogger(double impact, int day, int month, int year, const string &name,
                                 const string &methodOfInfection, const vector<string> &registers,
                                 const vector<string> &imports, const vector<string> &signifiers, const vector<string> &functions, const vector<string> &keyStrokes,
                                 bool hideFiles, bool hideRegisters) : Malware(impact, day, month, year, name,
                                                                                       methodOfInfection, registers),
                                                                               hideFiles(hideFiles),
                                                                               hideRegisters(hideRegisters) {
    this->imports = imports;
    this->signifiers = signifiers;
    this->functions = functions;
    this->keyStrokes = keyStrokes;
}

class Ransomware : public Malware{
private:
    double encryptionRating;
    double obfuscationRating;

public:
    Ransomware();
    Ransomware(const Ransomware& ob);
    Ransomware& operator=(const Ransomware& ob);
    ~Ransomware();
    Ransomware(double impact, int day, int month, int year, const string &name, const string &methodOfInfection,
               const vector<string> &registers, double encryptionRating, double obfuscationRating);

    void setEncryptionRating(double encryptionRating);

    void setObfuscationRating(double obfuscationRating);

    istream& readMalware(istream& is);
    ostream& printMalware(ostream& os);
    double calculeaza();
};

double Ransomware::calculeaza() {
    double val = obfuscationRating + encryptionRating;
    for (int i = 0; i < registers.size(); i++) {
        if (registers[i] == "HKLM-run" || registers[i] == "HKCU-run") {
            val += 20;
            break;
        }
    }
    return val;
}

istream & Ransomware::readMalware(istream &is) {
    cout << "Impact:\n";
    is >> impact;
    is.get();
    cout << "Date:\n";
    cout << "Year:\n";
    bool bisect = 0;
    int dayle[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> year;
    is.get();
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        bisect = 1;
    }
    cout << "Month:\n";
    while (true) {
        try {
            is >> month;
            is.get();
            if (month < 1 || month > 12) {
                throw string("invalid month");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }
    cout << "Day:\n";
    while (true) {
        try {
            is >> day;
            is.get();
            if (day < 1 || (month == 2 && bisect == 1 && day > 29) || day > dayle[month]) {
                throw string("invalid day");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }
    cout << "Name:\n";
    getline(is, name);
    cout << "Method of infection:\n";
    getline(is, methodOfInfection);

    int nr;

    while (true) {
        try {
            cout << "Number of registers:\n";
            is >> nr;
            is.get();
            if (nr < 0) {
                throw string("invalid number");
            }
            else {
                break;
            }
        }
        catch (string s){
            cout << s << '\n';
        }
    }

    for (int i = 0; i < nr; i++) {
        cout << "Register:\n";
        string s;
        getline(is, s);
        registers.push_back(s);
    }

    cout << "Encryption rating:\n";
    is >> encryptionRating;
    is.get();

    cout << "Obfuscation rating:\n";
    is >> obfuscationRating;
    is.get();

    return is;
}

ostream & Ransomware::printMalware(ostream &os) {
    os << "Impact: " << impact << "\n";
    os << "Date: " << day << '/' << month << '/' << year << '\n';
    os << "Name: " << name << '\n';
    os << "Method of infection: " << methodOfInfection << '\n';
    os << "Registers:\n";
    for (int i = 0; i < registers.size(); i++) {
        cout  << registers[i] << '\n';
    }
    os <<  "Encryption rating: " << encryptionRating << '\n';
    os << "Obfuscation rating: " << obfuscationRating << '\n';
    return os;
}

Ransomware::Ransomware() {
    impact = 0;
    day = 0;
    month = 0;
    year = 0;
    methodOfInfection = "";
    name = "";
    encryptionRating= 0;
    obfuscationRating = 0;

}

Ransomware::Ransomware(const Ransomware &ob) {
    impact = ob.impact;
    day = ob.day;
    month = ob.month;
    name = ob.name;
    year = ob.year;
    methodOfInfection = ob.methodOfInfection;
    registers = ob.registers;
    obfuscationRating = ob.obfuscationRating;
    encryptionRating = ob.encryptionRating;
}

Ransomware & Ransomware::operator=(const Ransomware &ob) {
    impact = ob.impact;
    day = ob.day;
    month = ob.month;
    name = ob.name;
    year = ob.year;
    methodOfInfection = ob.methodOfInfection;
    registers = ob.registers;obfuscationRating = ob.obfuscationRating;
    encryptionRating = ob.encryptionRating;
    return *this;
}
Ransomware::~Ransomware() {
    encryptionRating = obfuscationRating = 0;
}

Ransomware::Ransomware(double impact, int day, int month, int year, const string &name, const string &methodOfInfection,
                       const vector<string> &registers, double encryptionRating, double obfuscationRating) :
                       Malware(impact, day, month, year, name, methodOfInfection, registers), encryptionRating(encryptionRating), obfuscationRating(obfuscationRating) {}

void Ransomware::setEncryptionRating(double encryptionRating) {
    Ransomware::encryptionRating = encryptionRating;
}

void Ransomware::setObfuscationRating(double obfuscationRating) {
    Ransomware::obfuscationRating = obfuscationRating;
}

class Computer{
private:
    static int id;
    int code;
    double finalRating;
    vector <Malware*> virus;

public:
    int getCode() const;
    void setCode(int code);

    double getFinalRating() const;
    void setFinalRating(double finalRating);

    const vector<Malware *> &getVirus() const;
    void setVirus(const vector<Malware *> &virus);

    Computer();
    Computer(const Computer& c);
    Computer& operator=(const Computer& c);
    ~Computer();
    Computer(vector < Malware*> virus);

    void addVirus(Malware *m);
    friend istream& operator>>(istream& is, Computer& c);
    friend ostream & operator<<(ostream& os, Computer& c);

};

istream& operator>>(istream& is, Computer& c){
    int nr;
    while (true) {
        try {
            cout << "Virus number\n";
            is >> nr;
            is.get();
            if (nr < 0) {
                throw string("invalid number");
            }
            else {
                break;
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }

    for(int i = 0; i < nr; i++) {
        string type;
        Malware *p = nullptr;
        while (true) {
            try {
                cout << "Enter the virus type: \'root\' / \'key\' / \'ker\' / \'ran\' \n";
                getline(is, type);
                if(type == "root") {
                    p = new Rootkit;
                    break;;
                }
                else if (type == "key") {
                    p = new Keylogger;
                    break;
                }
                else if (type == "ker") {
                    p = new KernelKeylogger;
                    break;
                }
                else if (type == "ran") {
                    p = new Ransomware;
                    break;
                }
                else {
                    throw string("invalid type");
                }
            }
            catch(string s) {
                cout << s << '\n';
            }
        }
        is >> *p;
        c.finalRating += p->calculeaza();
        c.virus.push_back(p);
    }

    return is;
}

ostream & operator<<(ostream& os, Computer& c){
    os << "Code: " << c.code << '\n';
    os << "Final rating: " << c.finalRating << '\n';
    os << "Virus:\n";
    for (int i = 0; i < c.virus.size(); i++) {
        cout << *c.virus[i] << '\n';
    }
    return os;
}

Computer::Computer(vector<Malware *> virus) {
    id++;
    code = id;
    for (int i = 0; i< virus.size(); i++) {
        delete virus[i];
    }
    virus.clear();
    for (int i = 0; i < virus.size(); i++) {
        addVirus(virus[i]);
        finalRating += virus[i]->calculeaza();
    }
}

void Computer::addVirus(Malware *m) {
    if (Ransomware *d = dynamic_cast<Ransomware*>(m)) {
        virus.push_back(new Ransomware(*d));
    }
    else if (Rootkit *d = dynamic_cast<Rootkit*>(m)) {
        virus.push_back(new Rootkit(*d));
    }
    else if (Keylogger *d = dynamic_cast<Keylogger*>(m)) {
        virus.push_back(new Keylogger(*d));
    }
    else if (KernelKeylogger *d = dynamic_cast<KernelKeylogger*>(m)) {
        virus.push_back(new KernelKeylogger(*d));
    }
}

int Computer::id = 0;

Computer::Computer() : virus() {
    ++id;
    code = id;
    finalRating = 0;
}

Computer::Computer(const Computer &c) {
    code = c.code;
    finalRating = c.finalRating;
    for (int i = 0; i< virus.size(); i++) {
        delete virus[i];
    }
    virus.clear();
    for (int i = 0; i < c.virus.size(); i++) {
        addVirus(c.virus[i]);
    }
}

Computer & Computer::operator=(const Computer &c) {
    code = c.code;
    finalRating = c.finalRating;
    for (int i = 0; i< virus.size(); i++) {
        delete virus[i];
    }
    virus.clear();
    for (int i = 0; i < c.virus.size(); i++) {
        addVirus(c.virus[i]);
    }
    return *this;
}

Computer::~Computer() {
    id--;
    code = 0;
    finalRating = 0;
    for (int i = 0; i < virus.size(); i++) {
        delete virus[i];
    }
    virus.clear();
}

int Computer::getCode() const {
    return Computer::code;
}

void Computer::setCode(int code) {
    Computer::code = code;
}

double Computer::getFinalRating() const {
    return Computer::finalRating;
}

void Computer::setFinalRating(double finalRating) {
    Computer::finalRating = finalRating;
}

const vector<Malware *> &Computer::getVirus() const {
    return Computer::virus;
}

void Computer::setVirus(const vector<Malware *> &virus) {
    Computer::virus = virus;
}

class MeniuInteractiv{
private:
    vector <Computer*> computers;

    static MeniuInteractiv* instanta;
    MeniuInteractiv() = default;
    MeniuInteractiv(const MeniuInteractiv& m) = default;
    MeniuInteractiv(MeniuInteractiv& m) = default;
    MeniuInteractiv& operator=(const MeniuInteractiv& m) = default;
    MeniuInteractiv& operator=(MeniuInteractiv& ob) = default;

public:
    static MeniuInteractiv* getInstanta(){
        if(instanta == nullptr)
            instanta = new MeniuInteractiv();
        return instanta;
    }

    static void deleteInstanta(){
        if(instanta != nullptr)
            delete instanta;
        instanta = nullptr;
    }

    ~MeniuInteractiv(){
        for(int i = 0;i < computers.size(); ++i)
            delete computers[i];
        computers.clear();
    }

    void demo();
    void addComputer();
    void showComputers();
    void showComputersRating();
    void showFirstK();
    void showPercentage();

};

void MeniuInteractiv::showPercentage() {
    double p;
    int nr = 0;
    for (int i = 0; i < computers.size(); i++) {
        if (computers[i]->getFinalRating() != 0) {
            ++nr;
        }
    }
    if (computers.size()) {
        p = 100.0 * ((double) nr) / ((double) computers.size());
        cout << "Percentage: " << p << '\n';
    }
    else {
        cout << "There are no computers\n";
    }
}

void MeniuInteractiv::showComputersRating() {
    for (int i = 0; i < computers.size(); i++) {
        for (int j = i + 1; j < computers.size(); j++) {
            if (computers[i]->getFinalRating() > computers[j]->getFinalRating()) {
                swap(computers[i], computers[j]);
            }
        }
    }
    for (int i = 0; i < computers.size(); i++) {
        cout << *computers[i] << '\n';
    }
    cout << '\n';
}

void MeniuInteractiv::showFirstK() {
    int k;
    while (true) {
        cout << "Enter K:\n";
        cin >> k;
        cin.get();
        if (k <= 0) {
            throw string("invalid number");
        }
        else {
            break;
        }
    }
    for (int i = 0; i < computers.size(); i++) {
        for (int j = i + 1; j < computers.size(); j++) {
            if (computers[i]->getFinalRating() > computers[j]->getFinalRating()) {
                swap(computers[i],computers[j]);
            }
        }
    }
    for (int i = 0; i < k && i < computers.size(); i++) {
        cout << *computers[i] << '\n';
    }
    cout << '\n';
}

void MeniuInteractiv::addComputer() {
    Computer *c = new Computer;
    cout << "Computer:\n";
    cin >> *c;
    computers.push_back(c);
}

void MeniuInteractiv::showComputers() {
    for (int i = 0; i < computers.size(); i++) {
        cout << *computers[i] << '\n';
    }
    cout << '\n';
}

void MeniuInteractiv::demo() {
    cout << "demo\n";
}

MeniuInteractiv* MeniuInteractiv::instanta = nullptr;

int main() {

    int option;
    MeniuInteractiv* m = m->getInstanta();
    while(true){
        cout << "0.Demo\n";
        cout << "1.Add Computer\n";
        cout << "2.Show Computers\n";
        cout << "3.Show Computers Ordered By Rating\n";
        cout << "4.Show First k Computers\n";
        cout << "5.Show The Percentage Of Infected Computers\n";
        cout << "6.Close\n";

        try {
            cin >> option;
            cin.get();
            if (option < 0 || option > 11) {
                throw string("invalid option");
            }
            else {
                switch (option) {
                    case 0: m->demo();
                    case 1: m->addComputer();
                    case 2: m->showComputers();
                    case 3: m->showComputersRating();
                    case 4: m->showFirstK();
                    case 5: m->showPercentage();
                    case 6: break;
                }
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }
    m->deleteInstanta();
    return 0;
}