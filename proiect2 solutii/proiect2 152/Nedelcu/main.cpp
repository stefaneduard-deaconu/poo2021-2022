#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Date{
private:
    int zi, luna, an;
public:
    Date(int zi, int luna, int an) : zi(zi), luna(luna), an(an) {}

    Date() {zi = 1;
            luna = 1;
            an = 1990;}

    int getZi() const {
        return zi;
    }

    int getLuna() const {
        return luna;
    }

    int getAn() const {
        return an;
    }

    void setZi(int _zi) {
        Date::zi = _zi;
    }

    void setLuna(int _luna) {
        Date::luna = _luna;
    }

    void setAn(int _an) {
        Date::an = _an;
    }

    friend ostream &operator<<(ostream &os, const Date &date);
};

ostream &operator<<(ostream &os, const Date &date){
    os<<"Data: "<<date.zi<<"."<<date.luna<<"."<<date.an<<'\n';
    return os;
}

class Malware{
protected:
    double impact_rating =0;
private:

    Date infection_date;
    string name;
    string infection_method = "unknown";
    vector<string> registers={};
public:

    Malware( const Date &infectionDate, const string &name, const string &infectionMethod,
            const vector<string> &registers) : infection_date(infectionDate), name(name),
                                               infection_method(infectionMethod), registers(registers) {}

    Malware() {}

    Malware( const Date &infectionDate, const string &name, const vector<string> &registers)
            :  infection_date(infectionDate), name(name), registers(registers) {}

    double getImpactRating() const {
        return impact_rating;
    }

    const Date &getInfectionDate() const {
        return infection_date;
    }

    const string &getName() const {
        return name;
    }

    const string &getInfectionMethod() const {
        return infection_method;
    }

    const vector<string> &getRegisters() const {
        return registers;
    }

    friend ostream &operator<<(ostream &os, Malware &malware);
};

ostream &operator<<(ostream &os, Malware &malware){
    os<<"Nume: "<<malware.name<<'\n';
    os<<malware.infection_date;
    os<<"Metoda infectare: "<<malware.infection_method<<'\n';
    os<<"Registri afectati: "<<malware.registers.size();
    for(auto reg: malware.registers){
        os<<reg<<", ";
    }
    os<<"\nRatingul malware-ului: "<<malware.impact_rating<<"\n";

    return os;
}

class Rootkit: virtual public Malware{
private:
    vector<string> imports;
    vector<string> keywords;

protected:
    int calculateRatingRootKit(){
        int rating = 0;
        vector<string> s ={"System Service Descriptor Table", "SSDT", "NtCreateFile"};


        for(int j=0;j<=2;j++)
            if(count(keywords.begin(), keywords.end(), s[j])){
                rating+=100;
            }


        if(count(imports.begin(), imports.end(), "ntoskrnl.exe"))
            rating*=2;
        return rating;
    }

public:
    Rootkit( const Date &infectionDate, const string &name, const string &infectionMethod,
            const vector<string> &registers, const vector<string> &imports, const vector<string> &keywords) : Malware(
             infectionDate, name, infectionMethod, registers), imports(imports), keywords(keywords) {}

    Rootkit() {}


};

class Keylogger: virtual public Malware{
private:
    vector <string> functions;
    vector <string> special_keys;
protected:
    int calculateRatingKeylogger(){
        int rating =0;
        vector<string> s ={"[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
        vector<string>s2 ={ "CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};

        for(auto si:s){
            if(count(special_keys.begin(), special_keys.end(), si)){
                 rating+=30;
            }
        }

        for(auto si:s2){
            if(count(functions.begin(), functions.end(), si)){
                rating+=10;
            }
        }

        return rating;
        
    }
public:
};

class KernelKeylogger: public Rootkit, public Keylogger{
private:
    bool hidesFiles = false;
    bool hidesRegisters = false;

    int calculateRatingKernelKeylogger(){
        int rating = calculateRatingKeylogger();

        return rating;
    }
public:
};

class RansomWare: public Malware{
private:
    int ratingCriptare = 0;
    double ratingObfuscare = 0;
public:
};

class Computer{
protected:
    static int nextID;
private:
    int rating;
    int id;
    vector<Malware*> malware;
public:


    int getRating() const{
        return rating;
    }

    int getId() const {
        return id;
    }

    const vector<Malware*> &getMalware() const {
        return malware;
    }

    Computer() {
        id = nextID;
        nextID++;
        rating = 0;
    }

    void addMalware(Malware mal){
        malware.push_back(&mal);
    }

    explicit Computer(const vector<Malware*> &malware) : malware(malware) {
        id = nextID;
        nextID++;
        rating = 0;
        for(auto i: malware){
            rating+= i->getImpactRating();
        }
    }

    void setMalware(const vector<Malware*> &mal) {
        Computer::malware = mal;
        rating = 0;
        for(auto i: mal){
            rating+= i->getImpactRating();
        }
    }

    friend ostream &operator<<(ostream &os, const Computer &computer);

};

ostream &operator<<(ostream &os, const Computer &computer){
    os<<"Id-ul: "<<computer.id<<'\n';
    os<<"Primeste ratingul: "<<computer.rating<<'\n';

    if(computer.malware.empty()){
        os<<"Calculatorul nu este infectat\n";
    }else{
        os<<"Si este infectat cu urmatorii malware: \n";
        for(auto mal:computer.malware){
            vector<string>v = mal->getRegisters();
            for(auto i:v){
                os<<i<<" ";
            }
        }
    }

    os<<"\n\n\n";
    return os;

}
int Computer::nextID = 0;




int main() {

    Computer c,c2;
    cout<<c2;
    Malware mal(Date(), "Virusul", {"KLM", "GLM"});

    cout<<mal;

    c2.addMalware(mal);
    cout<<c2;


    return 0;
}


