#include <bits/stdc++.h>

#include <utility>

class IoBase{
protected:
    virtual std::istream& read(std::istream& is)
    {
        return is;
    }

    virtual std::ostream& write(std::ostream& os) const
    {
        return os;
    }

    friend std::istream& operator>>(std::istream& is, IoBase& ib)
    {
        return ib.read(is);
    }

    friend std::ostream& operator<<(std::ostream& os, IoBase& ib)
    {
        return ib.write(os);
    }
};

class Malware:public IoBase{
protected:
    int day, month, year;
    std::string name;
    std::string method;
    std::vector<std::string> registers;

    static const std::vector<std::string> badRegisters;
public:
    Malware(): day(0), month(0), year(0), method("unknown") {}
    Malware(int day, int month, int year, std::string name, std::vector<std::string> registers): day(day), month(month), year(year), name(std::move(name)), method("unknown"), registers(std::move(registers)) {}
    Malware(int day, int month, int year, std::string name, std::string method, std::vector<std::string> registers): day(day), month(month), year(year), name(std::move(name)), method(std::move(method)), registers(std::move(registers)) {}

    std::istream& read(std::istream& is) override
    {
        std::cout << "Input date(day month year):";
        is >> day >> month >> year;

        std::cout << "Input name:";
        std::getline(is, name);

        std::cout << "Input method:";
        std::getline(is, method);

        std::cout << "Input number of registers:";
        int regCnt;
        is >> regCnt;

        std::cout << "Input registers:";
        while (regCnt--) {
            std::string reg;
            std::getline(is, reg);
            registers.push_back(reg);
        }

        return IoBase::read(is);
    }

    std::ostream& write(std::ostream& os) const override
    {
        os << "Date: " << day << " " << month << " " << year << "\n";
        os << "Name: " << name << "\n";
        os << "Method: " << method << "\n";
        os << "Registers:\n";
        for (const auto& reg:registers) {
            os << reg << "\n";
        }

        return IoBase::write(os);
    }

    virtual int computeRating()
    {
        int ret = 0;
        for (const auto& reg:registers) {
            ret += 20 * (std::find(badRegisters.begin(), badRegisters.end(), reg) != badRegisters.end());
        }

        return ret;
    }
};

const std::vector<std::string> Malware::badRegisters = {std::string("HKLM-run"), std::string("HKCU-run")};

class Rootkit:virtual public Malware{
protected:
    std::vector<std::string> imports;
    std::vector<std::string> strings;

    static const std::vector<std::string> badStrings;
    static const std::vector<std::string> badImports;

    int getMultiplicationOrder()
    {
        int ret = 0;
        for (const auto& import:imports) {
            ret += (std::find(badImports.begin(), badImports.end(), import) != badImports.end());
        }

        return ret;
    }
public:
    Rootkit(): Malware() {}
    Rootkit(int day, int month, int year, std::string name, std::vector<std::string> &registers,  std::vector<std::string> imports, std::vector<std::string> strings) : Malware(day, month, year, std::move(name), registers), imports(std::move(imports)), strings(std::move(strings)) {}
    Rootkit(int day, int month, int year, std::string name, std::string method, std::vector<std::string> registers, std::vector<std::string> imports, std::vector<std::string> strings) : Malware(day, month, year, std::move(name), std::move(method), std::move(registers)), imports(std::move(imports)), strings(std::move(strings)) {}

    std::istream& read(std::istream& is) override
    {
        Malware::read(is);

        int importsCnt;
        std::cout << "Input number of imports:";
        is >> importsCnt;

        std::cout << "Input imports:\n";
        while (importsCnt--) {
            std::string import;
            std::getline(is, import);
            imports.push_back(import);
        }

        int stringsCnt;
        std::cout << "Input number of significant strings:";
        is >> stringsCnt;

        std::cout << "Input significant strings:\n";
        while (stringsCnt--) {
            std::string str;
            std::getline(is, str);
            strings.push_back(str);
        }

        return is;
    }

    std::ostream& write(std::ostream& os) const override
    {
        Malware::write(os);

        os << "Imports:\n";
        for (const auto& import:imports) {
            os << import << "\n";
        }

        os << "Significant strings:\n";
        for (const auto& str:strings) {
            os << str << "\n";
        }

        return os;
    }

    int computeRating() override
    {
        int ret = 0;
        for (const auto& str:strings) {
            ret += 100 * (std::find(badStrings.begin(), badStrings.end(), str) != badStrings.end());
        }

        return (ret + Malware::computeRating()) * (1 << getMultiplicationOrder());
    }
};

const std::vector<std::string> Rootkit::badStrings = {"System Service Descriptor Table", "SSDT", "NtCreateFile"};
const std::vector<std::string> Rootkit::badImports = {"ntoskrnl.exe"};

class Keylogger:virtual public Malware{
protected:
    std::vector<std::string> functions;
    std::vector<std::string> keys;

    static const std::vector<std::string> badFunctions;
    static const std::vector<std::string> badKeys;
public:
    Keylogger() : Malware() {}
    Keylogger(int day, int month, int year, std::string name, std::vector<std::string> registers, std::vector<std::string> functions, std::vector<std::string> keys) : Malware(day, month, year, std::move(name), std::move(registers)), functions(std::move(functions)), keys(std::move(keys)) {}
    Keylogger(int day, int month, int year, std::string name, std::string method, std::vector<std::string> registers, std::vector<std::string> functions, std::vector<std::string> keys) : Malware(day, month, year, std::move(name), std::move(method), std::move(registers)), functions(std::move(functions)), keys(std::move(keys)) {}

    std::istream& read(std::istream& is) override
    {
        Malware::read(is);

        int functionsCnt;
        std::cout << "Input number of functions:";
        is >> functionsCnt;

        std::cout << "Input functions:\n";
        while (functionsCnt--) {
            std::string function;
            std::getline(is, function);
            functions.push_back(function);
        }

        int keysCnt;
        std::cout << "Input number of keys:";
        is >> keysCnt;

        std::cout << "Input keys:\n";
        while (keysCnt--) {
            std::string key;
            std::getline(is, key);
            keys.push_back(key);
        }

        return is;
    }

    std::ostream& write(std::ostream& os) const override
    {
        Malware::write(os);

        os << "Functions:\n";
        for (const auto& function:functions) {
            os << function << "\n";
        }

        os << "Keys:\n";
        for (const auto& key:keys) {
            os << key << "\n";
        }

        return os;
    }

    int computeRating() override
    {
        int ret = 0;

        for (const auto& function:functions){
            ret += 30 * (std::find(badFunctions.begin(), badFunctions.end(), function) != badFunctions.end());
        }

        for (const auto& key:keys) {
            ret += 10 * (std::find(badKeys.begin(), badKeys.end(), key) != badKeys.end());
        }

        return ret + Malware::computeRating();
    }
};

const std::vector<std::string> Keylogger::badFunctions = {"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};
const std::vector<std::string> Keylogger::badKeys = {"[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};

class KernelKeylogger:public Rootkit, public Keylogger{
    bool hidesFiles;
    bool hidesRegisters;
public:KernelKeylogger(): Malware(), hidesFiles(false), hidesRegisters(false) {}
    KernelKeylogger(int day, int month, int year, std::string name, std::vector<std::string> registers, std::vector<std::string> imports, std::vector<std::string> strings, std::vector<std::string> functions, std::vector<std::string> keys, bool hidesFiles, bool hidesRegisters) : Rootkit(day, month, year, std::move(name), registers, std::move(imports), std::move(strings)), hidesFiles(hidesFiles), hidesRegisters(hidesRegisters)
    {
        this->functions = std::move(functions);
        this->keys = std::move(keys);
    }
    KernelKeylogger(int day, int month, int year, std::string name, std::string method, std::vector<std::string> registers, std::vector<std::string> imports, std::vector<std::string> strings, std::vector<std::string> functions, std::vector<std::string> keys, bool hidesFiles, bool hidesRegisters) : Rootkit(day, month, year, std::move(name), std::move(method), registers, std::move(imports), std::move(strings)), hidesFiles(hidesFiles), hidesRegisters(hidesRegisters)
    {
        this->functions = std::move(functions);
        this->keys = std::move(keys);
    }

    std::istream &read(std::istream &is) override {
        Rootkit::read(is);

        int functionsCnt;
        std::cout << "Input number of functions:";
        is >> functionsCnt;

        std::cout << "Input functions:\n";
        while (functionsCnt--) {
            std::string function;
            std::getline(is, function);
            functions.push_back(function);
        }

        int keysCnt;
        std::cout << "Input number of keys:";
        is >> keysCnt;

        std::cout << "Input keys:\n";
        while (keysCnt--) {
            std::string key;
            std::getline(is, key);
            keys.push_back(key);
        }

        return is;
    }

    std::ostream &write(std::ostream &os) const override {
        Rootkit::write(os);

        os << "Functions:\n";
        for (const auto& function:functions) {
            os << function << "\n";
        }

        os << "Keys:\n";
        for (const auto& key:keys) {
            os << key << "\n";
        }

        return os;
    }

    int computeRating() override {
        int ret = 0;

        for (const auto& str:strings) {
            ret += 100 * (std::find(badStrings.begin(), badStrings.end(), str) != badStrings.end());
        }

        return (ret + Keylogger::computeRating() + 20 * hidesFiles + 30 * hidesRegisters) * (1 << getMultiplicationOrder());
    }
};

class Ransomware:public Malware{
    int cryptRating;
    int hardenRating;
public:
    Ransomware(): Malware(), cryptRating(0), hardenRating(0) {}
    Ransomware(int day, int month, int year, std::string name, std::vector<std::string> registers, int cryptRating, int hardenRating) : Malware(day, month, year, std::move(name), std::move(registers)), cryptRating(cryptRating), hardenRating(hardenRating) {}
    Ransomware(int day, int month, int year, std::string name, std::string method, std::vector<std::string> registers, int cryptRating, int hardenRating) : Malware(day, month, year, std::move(name), std::move(method), std::move(registers)), cryptRating(cryptRating), hardenRating(hardenRating) {}

    std::istream &read(std::istream &is) override {
        Malware::read(is);

        std::cout << "Input crypting rating:";
        is >> cryptRating;

        std::cout << "Input hardening rating:";
        is >> hardenRating;

        return is;
    }

    std::ostream &write(std::ostream &os) const override {
        Malware::write(os);

        os << "Crypting rating: " << cryptRating << "\n";
        os << "Hardening rating: " << hardenRating << "\n";

        return os;
    }

    int computeRating() override {
        return Malware::computeRating() + cryptRating + hardenRating;
    }
};

int getRating(std::shared_ptr<Malware> malware)
{
    int rating = 0;
    auto asRansomware = dynamic_cast<Ransomware*>(malware.get());
    if (asRansomware) {
        rating += asRansomware->computeRating();
    } else {
        auto asKernelKeylogger = dynamic_cast<KernelKeylogger*>(malware.get());
        if (asKernelKeylogger) {
            rating += asKernelKeylogger->computeRating();
        } else {
            auto asKeylogger = dynamic_cast<Keylogger*>(malware.get());
            if (asKeylogger) {
                rating += asKeylogger->computeRating();
            } else {
                rating += dynamic_cast<Rootkit*>(malware.get())->computeRating();
            }
        }
    }

    return rating;
}

class Computer:public IoBase{
    static int currentId;
    int id;
    std::vector<std::shared_ptr<Malware>> malwareList;
    int rating;
public:
    Computer(): id(++currentId), rating(0) {}
    explicit Computer(std::vector<std::shared_ptr<Malware>> malwareList): id(++currentId), malwareList(std::move(malwareList))
    {
        rating = 0;
        for (const auto& malware:malwareList) {
            rating += getRating(malware);
        }
    }

    std::istream& read(std::istream& is) override
    {

    }
};

int Computer::currentId = 0;

int main() {

    return 0;
}
