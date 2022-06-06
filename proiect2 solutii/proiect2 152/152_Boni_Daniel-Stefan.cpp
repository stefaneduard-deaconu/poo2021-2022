/*
Boni Daniel-Stefan 152
MinGW g++
Stefan-Eduard Deaconu
*/
///Din cauza unor probleme de sanatate, n-am putut sa ajung la facultate azi. am aflat de aceasta simulare abia la ora 14 de pe grupul de whatsapp al grupei, si m-am apucat atunci de cod.
///Imi cer scuze de trimiterea tarzie.
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Malware
{
private:
    float rating;
    int day;
    int month;
    int year;
    string name;
    string infectionMethod;
    vector<string> modifiedRegisters;
public:
    Malware() { infectionMethod = "unknown"; }
    Malware(float rating, int day, int month, int year, string name, vector<string> modifiedRegisters, string infectionMethod = "unknown")
    {
        this->rating = rating;
        this->day = day;
        this->month = month;
        this->year = year;
        this->name = name;
        this->modifiedRegisters = modifiedRegisters;
        this->infectionMethod = infectionMethod;
    }
    void setRating(const float rating)
    {
        this->rating = rating;
    }

    virtual float computeRating()
    {
        float value = rating;
        for(int i = 0; i < modifiedRegisters.size(); ++ i)
        {
            if(modifiedRegisters[i] == "HKLM-run" || modifiedRegisters[i] == "HKCU-run")
            {
                value += 20.0;
            }
        }
        return rating;
    }

    float getRating() const
    {
        return rating;
    }

    void setDay(const int day)
    {
        this->day = day;
    }
    int getDay() const
    {
        return day;
    }

    void setMonth(const int month)
    {
        this->month = month;
    }
    int getMonth() const
    {
        return month;
    }

    void setYear(const int year)
    {
        this->year = year;
    }
    int getYear() const
    {
        return year;
    }

    void setName(const string name)
    {
        this->name = name;
    }
    string getName() const
    {
        return name;
    }

    void setInfectionMethod(const string infectionMethod)
    {
        this->infectionMethod = infectionMethod;
    }
    string getInfectionMethod() const
    {
        return infectionMethod;
    }

    void setModifiedRegisters(vector<string>&modifiedRegisters)
    {
        this->modifiedRegisters = modifiedRegisters;
    }
    vector<string> getModifiedRegisters() const
    {
        return modifiedRegisters;
    }
    void addModifiedRegister(const string mRegister)
    {
        modifiedRegisters.push_back(mRegister);
    }
    string findModifiedRegister(const int index)
    {
        if(index >= 0 && index < modifiedRegisters.size())
            return modifiedRegisters[index];
        else
            return "<Error>";
    }
    int getModifiedRegistersSize()
    {
        return modifiedRegisters.size();
    }

    virtual void print()
    {
        cout<<"Malware: "<<name<<" infected this PC on "<<day<<"."<<month<<"."<<year<<" via "<<infectionMethod<<".\n";
        cout<<"It has the initial rating of: "<<rating<<".\n";
        cout<<"It affected the following registers: \n";
        for(int i = 0; i < modifiedRegisters.size(); ++ i)
        {
            cout<<modifiedRegisters[i]<<'\n';
        }
    }
};

class Rootkit: public virtual Malware
{
private:
    vector<string> imports;
    vector<string> importantStrings;
public:
    Rootkit(): Malware() {}
    Rootkit(float rating, int day, int month, int year, string name, vector<string> modifiedRegisters, vector<string> imports, vector<string> importantStrings, string infectionMethod = "unknown"):
            Malware(rating, day, month, year, name, modifiedRegisters, infectionMethod), imports(imports), importantStrings(importantStrings){}
    Rootkit(vector<string> imports, vector<string> importantStrings): imports(imports), importantStrings(importantStrings) {}

    void setImports(vector<string>&imports)
    {
        this->imports = imports;
    }
    vector<string> getImports() const
    {
        return imports;
    }
    void addImports(const string import)
    {
        imports.push_back(import);
    }
    string findImport(const int index)
    {
        if(index > -1 && index < imports.size())
            return imports[index];
        else
            return "<Error>";
    }
    int getImportsSize()
    {
        return imports.size();
    }

    void setImportantStrings(vector<string>&importantStrings)
    {
        this->importantStrings = importantStrings;
    }
    vector<string> getImportantStrings() const
    {
        return importantStrings;
    }
    void addImportantString(const string importantString)
    {
        importantStrings.push_back(importantString);
    }
    string findImportantString(const int index)
    {
        if(index > -1 && index < importantStrings.size())
            return importantStrings[index];
        else
            return "<Error>";
    }
    int getImportantStringsSize()
    {
        return importantStrings.size();
    }

    float computeRating() override
    {
        float value = Malware::computeRating();

        vector<string> check = {"System Service Descriptor Table", "SSDT", "NtCreateFile"};
        for(int i = 0; i < importantStrings.size(); ++ i)
        {
            if(importantStrings[i] == "System Service Descriptor Table" ||
               importantStrings[i] == "SSDT" ||
               importantStrings[i] == "NtCreateFile")
            {
                value += 100.0;
                break;
            }
        }
        for(int i = 0; i < imports.size(); ++ i)
        {
            if(imports[i] == "ntoskrnl.exe")
            {
                value *= 2;
                break;
            }
        }

        return value;
    }

    void print() override
    {
        Malware::print();
        cout<<"Type: Rootkit\n";
        cout<<"List of imports: \n";
        for(int i = 0; i < imports.size(); ++ i)
        {
            cout<<imports[i]<<'\n';
        }
        cout<<"List of important strings: \n";
        for(int i = 0; i < importantStrings.size(); ++ i)
        {
            cout<<importantStrings[i]<<'\n';
        }
    }
};

class Keylogger: public virtual Malware
{
private:
    vector<string> functions;
    vector<string> specialKeys;
public:
    Keylogger(): Malware() {}

    Keylogger(float rating, int day, int month, int year, string name, vector<string> modifiedRegisters, vector<string> functions, vector<string> specialKeys, string infectionMethod = "unknown"):
            Malware(rating, day, month, year, name, modifiedRegisters, infectionMethod), functions(functions), specialKeys(specialKeys){}

    Keylogger(vector<string> functions, vector<string> specialKeys): functions(functions), specialKeys(specialKeys){}

    void setFunctions(vector<string>&functions)
    {
        this->functions = functions;
    }
    vector<string> getFunctions() const
    {
        return functions;
    }
    void addFunctions(const string function)
    {
        functions.push_back(function);
    }
    string findFunction(const int index)
    {
        if(index > -1 && index < functions.size())
            return functions[index];
        else
            return "<Error>";
    }
    int getFunctionsSize()
    {
        return functions.size();
    }

    void setSpecialKeys(vector<string>&specialKeys)
    {
        this->specialKeys = specialKeys;
    }
    vector<string> getSpecialKeys() const
    {
        return specialKeys;
    }
    void addSpecialKeys(const string specialKey)
    {
        specialKeys.push_back(specialKey);
    }
    string findSpecialKey(const int index)
    {
        if(index > -1 && index < specialKeys.size())
            return specialKeys[index];
        else
            return "<Error>";
    }
    int getSpecialKeysSize()
    {
        return specialKeys.size();
    }

    float computeRating() override
    {
        float value = Malware::computeRating();
        vector<string> badKeys = {"[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
        vector<string> badFunctions = {"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};

        for(int i = 0; i < specialKeys.size(); ++ i)
        {
            for(int j = 0; j < badKeys.size(); ++ j)
            {
                if (badKeys[j] == specialKeys[i]) {
                    value += 10.0;
                }
            }
        }
        bool found = false;
        for(int i = 0; i < functions.size() && !found; ++ i)
        {
            for(int j = 0; j < badFunctions.size(); ++ j)
            {
                if(badFunctions[j] == functions[i])
                {
                    found = true;
                    value += 30.0;
                    break;
                }
            }
        }
        return value;
    }

    void print() override
    {
        Malware::print();
        cout<<"Type: keylogger\n";
        cout<<"List of special keys: \n";
        for(int i = 0; i < specialKeys.size(); ++ i)
        {
            cout<<specialKeys[i]<<'\n';
        }

        cout<<"List of functions: \n";
        for(int i = 0; i < functions.size(); ++ i)
        {
            cout<<functions[i]<<'\n';
        }

    }

};

class KernelKeylogger: public Keylogger, public Rootkit
{
private:
    bool HidesFiles;
    bool HidesRegisters;
public:
    KernelKeylogger(): Keylogger() {}

    KernelKeylogger(float rating, int day, int month, int year, string name, vector<string> modifiedRegisters,
                    vector<string> functions, vector<string> specialKeys, vector<string> imports, vector<string> importantStrings,
                    bool HidesFiles, bool HidesRegisters, string infectionMethod = "unknown"):
                    Keylogger(functions, specialKeys),
                    Rootkit(imports, importantStrings),
                    Malware(rating, day, month, year, name, modifiedRegisters, infectionMethod)
    {
        this->HidesRegisters = HidesRegisters;
        this->HidesFiles = HidesFiles;
    }

    void setHidesFiles(const bool hf)
    {
        HidesFiles = hf;
    }
    bool getHidesFiles() const
    {
        return HidesFiles;
    }

    void setHidesRegisters(const bool hr)
    {
        HidesRegisters = hr;
    }
    bool getHidesRegisters() const
    {
        return HidesRegisters;
    }

    float computeRating() final
    {
        float value = Keylogger::computeRating();
        value += Rootkit::computeRating();
        if(HidesFiles)
            value += 20.0;
        if(HidesRegisters)
            value += 30.0;
        return value;
    }

    void print() final
    {
        Malware::print();
        cout<<"Type: kernel keylogger\n";
        cout<<"List of special keys: \n";
        for(int i = 0; i < getSpecialKeysSize(); ++ i)
        {
            cout<<findSpecialKey(i)<<'\n';
        }
        cout<<"List of functions: \n";
        for(int i = 0; i < getFunctionsSize(); ++ i)
        {
            cout<<findFunction(i)<<'\n';
        }
        cout<<"List of imports: \n";
        for(int i = 0; i < getImportsSize(); ++ i)
        {
            cout<<findImport(i)<<'\n';
        }
        cout<<"List of important strings: \n";
        for(int i = 0; i < getImportantStringsSize(); ++ i)
        {
            cout<<findImportantString(i)<<'\n';
        }
    }
};

class Ransomware: public Malware
{
private:
    int encryptionRating;
    int painRating;
public:
    Ransomware(): Malware() {}

    Ransomware(float rating, int day, int month, int year, string name, vector<string> modifiedRegisters, int encryptionRating, int painRating, string infectionMethod = "unknown"):
            Malware(rating, day, month, year, name, modifiedRegisters, infectionMethod)
    {
        this->encryptionRating = encryptionRating;
        this->painRating = painRating;
    }

    void setEncryptionRating(const int encryptionRating)
    {
        this->encryptionRating = encryptionRating;
    }
    int getEncryptionRating() const
    {
        return encryptionRating;
    }

    void setPainRating(const int painRating)
    {
        this->painRating = painRating;
    }
    int getPainRating() const
    {
        return painRating;
    }

    float computeRating() override
    {
        float value = Malware::computeRating();
        value += painRating;
        value += encryptionRating;
        return value;
    }

    void print() override
    {
        Malware::print();
        cout<<"Type: ransomware\n";
        cout<<"Encryption rating: "<<encryptionRating<<'\n';
        cout<<"Obfuscation rating: "<<painRating<<'\n';
    }
};
int currID;
class PC
{
private:
    int id;
    vector<shared_ptr<Malware> > malware;
public:
    PC()
    {
        ++currID;
        id = currID;
    }

    void addMalware(const shared_ptr<Malware> virus)
    {
        malware.push_back(virus);
    }

    vector<shared_ptr<Malware> > getMalware() const
    {
        return malware;
    }

    shared_ptr<Malware> findMalware(int index) const
    {
        if(index > -1 && index < malware.size())
            return malware[index];
        else
            return nullptr;
    }

    int getMalwareSize() const
    {
        return malware.size();
    }

    void print()
    {
        cout<<"PC "<<id<<" has "<<malware.size()<<" malware:\n";
        for(auto v: malware)
        {
            (*v).print();
            cout<<"-------------\n";
        }
        cout<<"<<<<<<<<<<<<>>>>>>>>>>>>\n\n";
    }
};


int main()
{


    vector<PC> pcs;
    int n;
    cin>>n;
    string dump;
    for(int i = 0; i < n; ++ i)
    {
        pcs.push_back(PC());
        int m;
        cin>>m;
        for(int j = 0; j < m; ++ j) {
            cout<< "Type of malware: 0 for simple malware, 1 for rootkit, 2 for keylogger, 3 for kernellogger, 4 for ransomware\n";
            int type;
            cin >> type;
            int rating;
            int day, month, year;
            string name;
            vector<string> registers;
            cout << "rating: ";
            cin >> rating;
            cout << "d/m/y: ";
            cin >> day >> month >> year;
            cout << "name: ";
            getline(cin, dump);
            getline(cin, name);
            int x;
            cout << "no of registers: ";
            cin >> x;
            getline(cin, dump);
            for (int k = 0; k < x; ++k) {
                string reg;
                getline(cin, reg);
                registers.push_back(reg);
            }
            cout << "does it have an infection method (0 or 1): ";
            cin >> x;
            string infection = "unknown";
            if (x) {
                cin >> infection;
            }


            if (type == 0) {
                Malware m(rating, day, month, year, name, registers, infection);
                pcs[i].addMalware(make_shared<Malware>(m));
            }
            if(type == 1) {
                cout << "no of imports: ";
                cin >> x;
                vector<string> imports;
                getline(cin, dump);
                for (int k = 0; k < x; ++k) {
                    string imp;
                    getline(cin, imp);
                    imports.push_back(imp);
                }

                cout << "no of important strings: ";
                cin >> x;
                vector<string> importantStrings;
                getline(cin, dump);
                for (int k = 0; k < x; ++k) {
                    string imp;
                    getline(cin, imp);
                    importantStrings.push_back(imp);
                }
                Rootkit r(rating, day, month, year, name, registers, imports, importantStrings, infection);
                pcs[i].addMalware(make_shared<Rootkit>(r));
            }
            if(type == 2) {
                cout << "no of functions: ";
                cin >> x;
                vector<string> functions;
                getline(cin, dump);
                for (int k = 0; k < x; ++k) {
                    string imp;
                    getline(cin, imp);
                    functions.push_back(imp);
                }

                cout << "no of special keys: ";
                cin >> x;
                vector<string> keys;
                getline(cin, dump);
                for (int k = 0; k < x; ++k) {
                    string imp;
                    getline(cin, imp);
                    keys.push_back(imp);
                }
                Keylogger r(rating, day, month, year, name, registers, functions, keys, infection);
                pcs[i].addMalware(make_shared<Keylogger>(r));
            }
            if(type == 3) {
                cout << "no of imports: ";
                cin >> x;
                vector<string> imports;
                getline(cin, dump);
                for (int k = 0; k < x; ++k) {
                    string imp;
                    getline(cin, imp);
                    imports.push_back(imp);
                }

                cout << "no of important strings: ";
                cin >> x;
                vector<string> importantStrings;
                getline(cin, dump);
                for (int k = 0; k < x; ++k) {
                    string imp;
                    getline(cin, imp);
                    importantStrings.push_back(imp);
                }

                cout << "no of functions: ";
                cin >> x;
                vector<string> functions;
                getline(cin, dump);
                for (int k = 0; k < x; ++k) {
                    string imp;
                    getline(cin, imp);
                    functions.push_back(imp);
                }

                cout << "no of special keys: ";
                cin >> x;
                vector<string> keys;
                getline(cin, dump);
                for (int k = 0; k < x; ++k) {
                    string imp;
                    getline(cin, imp);
                    keys.push_back(imp);
                }

                bool hidesFiles;
                bool hidesRegisters;
                cout << "hides registers: ";
                cin>> hidesRegisters;
                cout << "hides files: ";
                cin>> hidesFiles;

                KernelKeylogger kk(rating, day, month, year, name, registers, functions, keys, imports, importantStrings, hidesFiles, hidesRegisters, infection);
                pcs[i].addMalware(make_shared<KernelKeylogger>(kk));
            }
            if(type == 4)
            {
                int er;
                cout<<"encryption complexity: ";
                cin>>er;
                cout<<"obfuscation rating: ";
                int obr;
                cin>>obr;
                Ransomware r(rating, day, month, year, name, registers, er, obr, infection);
                pcs[i].addMalware(make_shared<Ransomware>(r));
            }
        }
        cout<<"---------PC "<<i<<" over---------\n";
    }
    for(int i = 0; i < n; ++ i)
    {
        pcs[i].print();
    }
    return 0;
}
