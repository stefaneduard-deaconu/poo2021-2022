#include <bits/stdc++.h>
using namespace std;

struct data{
    int zi,luna,an;
};
//Io Base lab 6
class IoBase {
private:
public:
    // metoda citire
    virtual istream &read(istream &is,bool flag) {
        return is;
    }
    // metoda scriere
    virtual ostream &write(ostream &os,bool flag) const {
    return os;
    }
    friend ostream &operator<<(ostream &os, const IoBase &base) {
        return base.write(os,true);
    }

    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is,true);
    }
};

class malware : public IoBase{
private:
    double impact;
    data infect_date;
    string name;
    string infect_method;
    vector < string > modified_registers;
public:
    malware() {}

    malware(double impact, const data &infectDate, const string &name, const string &infectMethod,
            const vector<string> &modifiedRegisters) : impact(impact), infect_date(infectDate), name(name),
                                                       infect_method(infectMethod),
                                                       modified_registers(modifiedRegisters) {}

    istream &read(istream &is,bool flag) override {
        IoBase::read(is,flag);
        cout << "impact: "<<endl; is >> impact;
        cout << "data de infectare: "<<endl; is >> infect_date.zi >> infect_date.luna >> infect_date.an;
        cout << "name: " << endl;
        is.get();
        getline(is,name);
        cout << "infect_method: " <<endl ;
        getline(is,infect_method);
        int n;
        cout << "nr infected  registers: \n"; is >> n;
        while(n --)
        {
            string s;
            is >> s;
            modified_registers.push_back(s);
        }
        return is;
    }
    ostream &write(ostream &os,bool flag) const override {
        IoBase::write(os,flag);
        os << "Impact:" << impact << "  Name: " << name << '\n';
        os << "infect_method: "<<infect_method << '\n';
        os << "registri affectati: "<<modified_registers.size() << '\n';
        for(auto it : modified_registers)
            os << it <<' ';
        os << '\n';
        return os;
    }

    virtual int get_rating(){
        for(auto it : modified_registers)
            if(it == "HKLM-run" or it == "HKCU-run")
                return 20;
        return 0;
    }
};



class rootkit : virtual public malware{
private:
    vector < string > import_list;
    vector < string > semnificative_string;
    static set < string > rootkitstring;
public:
    rootkit() {}

    rootkit(double impact, const data &infectDate, const string &name, const string &infectMethod,
            const vector<string> &modifiedRegisters, const vector<string> &importList,
            const vector<string> &semnificativeString) : malware(impact, infectDate, name, infectMethod,
                                                                 modifiedRegisters), import_list(importList),
                                                         semnificative_string(semnificativeString) {}

    istream &read(istream &is,bool flag) override {
        if(flag)
            malware::read(is,flag);
        int n;
        cout << "import list size\n"; is >> n;
        cout << "import list: \n";
        while(n --)
        {
            string s;
            is >> s;
            import_list.push_back(s);
        }

        cout << "semnificative list size\n"; is >> n;
        cout << "semnificative list: \n";
        while(n --)
        {
            string s;
            is >> s;
            semnificative_string.push_back(s);
        }
        return is;
    }
    ostream &write(ostream &os,bool flag) const override {
        if(flag)    malware::write(os, flag);
        os << "import list\n";
        for(auto it : import_list) os << it << '\n';
        os << "semnificative list\n";
        for(auto it : semnificative_string) os << it << '\n';
        return os;
    }
    int get_rating() override {
        int ans = malware::get_rating();
        for(auto it : semnificative_string)
            if(rootkitstring.find(it) != rootkitstring.end())
                ans += 100;
        for(auto it : import_list)
            if(it == "ntoskrnl.exe")
                ans *= 2;
        return  ans;
    }
};
set < string > rootkit :: rootkitstring = {"System Service Descriptor Table", "SSDT", "NtCreateFile"};

class keylogger : virtual public malware{
private:
    vector < string > used_functions;
    vector < string > key_defined;
    static set < string > keylogerkeys;
    static set < string > keyloggerfunctions;
public:
    istream &read(istream &is,bool flag) override {
        if(flag)
            malware::read(is,flag);
        int n;
        cout << "used_functions list size: \n"; is >> n;
        cout << "used_functions list: \n";
        while(n --)
        {
            string s;
            is >> s;
            used_functions.push_back(s);
        }

        cout << "key_defined list size: \n"; is >> n;
        cout << "key_defined list: \n";
        while(n --)
        {
            string s;
            is >> s;
            key_defined.push_back(s);
        }
        return is;
    }
    ostream &write(ostream &os,bool flag) const override {
        if(flag)
            malware::write(os,flag);
        os << "used_functions list: \n";
        for(auto it : used_functions) os << it << '\n';
        os << "key_defined list: \n";
        for(auto it : key_defined) os << it << '\n';
        return os;
    }
    int get_rating() override {
        int ans = malware::get_rating();
        for(auto it : key_defined)
            if(keylogerkeys.find(it) != keylogerkeys.end())
                ans += 10;
        for(auto it : used_functions)
            if(keyloggerfunctions.find(it) != keyloggerfunctions.end())
                ans += 30;
        return  ans;
    }
};
set < string > keylogger :: keylogerkeys = {"[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
set < string > keylogger :: keyloggerfunctions = {"CreateFileW", "OpenProcess", "ReadFile", "WriteFil", "RegisterHotKey", "SetWindowsHookEx"};

class kernel_keylogger : public rootkit, public keylogger{
private:
    bool hides_files;
    bool hides_registers;
public:
    istream &read(istream &is,bool flag) override {
        malware::read(is,flag);
        rootkit::read(is,false);
        keylogger::read(is, false);
        cout << "hides files? \n";
        is >> hides_files;
        cout << "hides registers? \n";
        is >> hides_registers;
        return is;
    }
    ostream &write(ostream &os,bool flag) const override {
        malware::write(os,flag);
        rootkit::write(os,false);
        keylogger::write(os,false);
        os << "hides files : " << hides_files << '\n';
        os << "hides registers :" << hides_registers << '\n';
        return os;
    }
    int get_rating() override {
        int ans = rootkit::get_rating() + keylogger::get_rating() - malware::get_rating();//va fi adaugat de 2 ori daca exista
        if(hides_files) ans += 20;
        if(hides_registers) ans += 30;
        return  ans;
    }
};

class ransomware : public malware{
private:
    double  crypt_rating;
    double obfusare;
public:
    istream &read(istream &is,bool flag) override {
        if(flag)
            malware::read(is,flag);
        cout <<"crypt rating:\n";
        is >> crypt_rating;
        cout << "obfuscare:\n";
        is >> obfusare;
        return is;
    }
    ostream &write(ostream &os,bool flag) const override {
        if(flag)    malware::write(os, flag);
        cout <<"crypt rating:\n";
        os << crypt_rating;
        cout << "obfuscare:\n";
        os << obfusare;
        return os;
    }
    int get_rating() override {
        return  malware :: get_rating() + crypt_rating + obfusare;
    }

};

class computer : public IoBase{
private:
    int id;
    static int current_id;
    vector < shared_ptr < malware > > malware_list;
    double infection_rating;
public:
    computer() : id(current_id++){}

    computer(int id, const vector<shared_ptr<malware>> &malwareList, double infectionRating) : id(current_id++), malware_list(
            malwareList), infection_rating(infectionRating) {compute_infection_rating();}

    double getInfectionRating() const {
        return infection_rating;
    }

    void compute_infection_rating(){
        infection_rating = 0;
        for(auto it : malware_list)
        {
//            cout << "rating la asta " << (*it).get_rating() << '\n';
            infection_rating += (*it).get_rating();
        }

    }
    istream &read(istream &is,bool flag) override {
        IoBase::read(is,flag);
        id = current_id++;

        int m;
        cout << "Malware count:  \n";
        is >> m;
        while(m--)
        {
            cout << "Malware type:\n";
            cout << "1: rookit\n" <<
                    "2: keylogger\n" <<
                    "3: kernel-keylogger\n" <<
                    "4: ransomware" << '\n';
            shared_ptr < malware > virus;
            int type;
            is >> type;
            if(type == 1)
            {
                rootkit ths;
                is >> ths;
                virus = make_shared < rootkit >(ths);
            }
            else if(type == 2)
            {
                keylogger ths;
                is >> ths;
                virus = make_shared < keylogger >(ths);
            }
            else if(type == 3)
            {
                kernel_keylogger ths;
                is >> ths;
                virus = make_shared < kernel_keylogger >(ths);
            }
            else if(type == 4)
            {
                ransomware ths;
                is >> ths;
                virus = make_shared < ransomware >(ths);
            }
            else{
                cout<<"invalid\n";
                m++;
            }
            malware_list.push_back(virus);
        }
        compute_infection_rating();
        return is;
    }
    ostream &write(ostream &os,bool flag) const override {
        IoBase::write(os,flag);
        os << "Malware cnt: " << malware_list.size() << '\n';
        os << "computerul "<<id << ": \n";
        for(auto it : malware_list)
            os << *it << '\n';
        cout << "rating infectare\n";
        cout << infection_rating << '\n';
        return os;
    }
    bool infected()
    {
        return !malware_list.empty();
    }
};
int computer :: current_id;

//lab 8
class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};
class SimpleMenu : public BaseMenu {
private:
    vector < computer > computers;//e ok daca pun datele aici ?
public:
    void listOptions() override {
        cout << "0. Citeste N calculatoare" << '\n';
        cout << "1. Afisare informatii calculatoare." << '\n';
        cout << "2. Afisare informatii calculatoare ordonate dupa ratingul final." << '\n';
        cout << "3. Afisare primele k calculatoare dupa ratingul final" << '\n';
        cout << "4. Afisare procent calculatoare infectate" << '\n';
        cout << "5. Iesire." << '\n';
    }

    int chooseOption(int first, int last) override {
        int option = -1;
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
    void option0() {
        int n;
        cout << "introduceti n";
        cin >> n;
        while(n--)
        {
            computer c;
            cin >> c;
            computers.push_back(c);
        }
    }
    void option1() {
        cout << "calculatoare sunt\n";
        for(auto it : computers)
            cout << it <<'\n';
    }

    void option2() {
        sort(computers.begin(),computers.end(),[](computer c1, computer c2){
            return c1.getInfectionRating() < c2.getInfectionRating();
        });
        for(auto it : computers)
            cout << it << '\n';
    }

    void option3() {
        int k;
        cout << "k= \n";
        cin >> k;
        sort(computers.begin(),computers.end(),[](computer c1, computer c2){
            return c1.getInfectionRating() < c2.getInfectionRating();
        });
        for(int i = 0;i < k and i < computers.size();i++)
            cout << computers[i] << '\n';
    }
    void option4() {
        int total = computers.size();
        int infected = 0;
        for(auto it : computers)
            infected += it.infected();
        cout << "computere infectate: " << (infected / total * 100.0) << "%\n";
    }
    void mainLoop() override {
        while (true) {
            int option = chooseOption(0, 5);
            if(option == 0){
                option0();
            }
            else if (option == 1) {
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
        cout << '\n'
             << "---------------------------------"
             << '\n'
             << "Programul s-a incheiat cu success";
    }

};//end lab 8 meniu


int main() {


    SimpleMenu menu;
    menu.mainLoop(); // păstrăm simplu: funcția mainLoop „ruleaza” meniul la infinit.
    return 0;
}
