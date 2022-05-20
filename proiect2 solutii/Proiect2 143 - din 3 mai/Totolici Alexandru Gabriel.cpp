#include <iostream>
#include <memory>
#include <vector>
#include <list>
using namespace std;

class Malware {
protected:
    int rating,an,luna,zi;
    string name,method;
    vector <string> registers;
public:
    Malware(){}
    Malware(int xrating, int xan, int xluna, int xzi, const string &name, const string &xmethod, const vector <string> &xregisters) :
    rating(xrating), an(xan), zi(xzi), name(name), method(xmethod), registers(xregisters) {}

    istream &read(istream &is) override {
        cout << "Introduceti rating: ";
        is >> rating;
        cout << "Introduceti zi: ";
        is >> zi;
        cout << "Introduceti luna: ";
        is >> luna;
        cout << "Introduceti an: ";
        is >> an;
        cout << "Introduceti nume: ";
        is >> name;
        cout << "Introduceti metoda de infectare: ";
        is >> method;
        int x;
        string registru;
        cout << "Introduceti nr registri modificati: ";
        is >> x;
        for ( int i=0; i<x ; i++) {
            cin >> registru;
            registers.push_back(registru);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        cout << "Rating impact: ";
        os << rating << endl;
        cout << "Zi: ";
        os << zi << endl;
        cout << "Luna: ";
        os << luna << endl;
        cout << "An: ";
        os << an << endl;
        cout << "Metoda de infectare: ";
        os << method << endl;
        cout << "Registri modificati: \n";
        for ( auto regis : registers)
            cout << regis << endl;
    }
};

class Rootkit : public virtual Malware{
protected:
    vector <string> imports;
    vector <string> strings;
public:
    Rootkit(){}

    Rootkit(int xrating, int xan, int xluna, int xzi, const string &name, const string &xmethod,
            const vector<string> &xregisters, const vector<string> &imports, const vector<string> &strings) : Malware(xrating, xan, xluna, xzi, name, xmethod, xregisters), imports(imports), strings(strings) {}

    istream &read (istream &is) override {
        Malware::read(is);
        int n;
        string s;
        cout << "Numar importuri: ";
        is >> n;
        for(int i=0 ; i<n; i++){
            is >> s;
            imports.push_back(s);
        }

        cout << "Numar stringuri semnificative: ";
        is >> n;
        for (int j=0; j<n; j++){
            is >> s;
            strings.push_back(s);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        os << "Importuri: ";
        for(auto imp: imports)
            os << imp << endl;
        os << "Stringuri semnificative: ";
        for(auto ss : strings)
            os << ss <<endl;
        return os;
    }

};

class Keylogger : public virtual Malware {
private:
    vector <string> functions;
    vector <string> keys;
public:
    Keylogger(){}

    Keylogger(int xrating, int xan, int xluna, int xzi, const string &name, const string &xmethod,
              const vector<string> &xregisters, const vector<string> &functions, vector<string> &keys) : Malware(xrating, xan, xluna, xzi,
                                                                                           name, xmethod, xregisters),
                                                                                   functions(functions), keys(keys) {}

    istream &read (istream &is) override {
        Malware::read(is);
        int n;
        string s;
        cout << "Numar functii: ";
        is >> n;
        for(int i=0 ; i<n; i++){
            is >> s;
            functions.push_back(s);
        }

        cout << "Numar taste speciale: ";
        is >> n;
        for (int j=0; j<n; j++){
            is >> s;
            keys.push_back(s);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        os << "Functii: ";
        for(auto f: functions)
            os << f << endl;
        os << "Taste speciale: ";
        for(auto k : keys)
            os << k <<endl;
        return os;
    }
};

class Kernel_Keylogger : public Rootkit, public Keylogger{
private:
    int registers;
    int folders;
public:
    Kernel_Keylogger(){};

    istream &read(istream &is) override {
        Rootkit::read(is);
        int n;
        string s;
        cout << "Numar functii: ";
        is >> n;
        for( int i=0; i<n ; i++){
            is >> s;
            functions.push_back(s);
        }
        cout << "Numar taste speciale: ";
        is >> n;
        for (int j=0; j<n; j++){
            is >> s;
            keys.push_back(s);
        }

        cout << "Folders Attack => 0 - False, 1 - True";
        is >> folders;
        cout << "Registers Attack => 0 - False, 1 - True";
        is >> registers;
        return is;
    }

    ostream &write(ostream &os) const override {
        Rootkit::write(os);
        os <<"Functii: ";
        for(auto x: functions)
            os << x << endl;
        os<<"Taste speciale: ";
        for(auto x: keys)
            os << x << endl;
        os<<"Fisiere: "<< folders;
        os<<"Registre: "<< registers;
        return os;
    }

};

class Ransomware : public Malware{
private:
    int cryptoRating;
    float hidingRating;
public:
    Ransomware(){};

    Ransomware(int xrating, int xan, int xluna, int xzi, const string &name, const string &xmethod,
               const vector<string> &xregisters, int cryptoRating, float hidingRating) : Malware(xrating, xan, xluna, xzi, name, xmethod,
                                                                             xregisters), cryptoRating(cryptoRating), hidingRating(hidingRating) {}

    istream &read(istream &is) override {
        Malware::read(is);
        cout << "Introduceti ratingul de criptare: ";
        is >> cryptoRating;
        cout << "Introduceti ratingul de obfuscare: ";
        is >> hidingRating;
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        cout << "Ratingul de criptare: ";
        os << cryptoRating;
        cout << "Ratingul de obfuscare: ";
        os << hidingRating;
        return os;
    }
};

shared_ptr<Malware> citireMW(){
    int tip;
    cout<<"1. rootkit\n2. keylogger\n3.kernel-keylogger\n4.ransomware";
    cin>>tip;
    shared_ptr<Malware>m;
    if(tip==1){
        m = make_shared<Rootkit>();
    } else if (tip==2){
        m = make_shared<Keylogger>();
    } else if(tip==3){
        m = make_shared<Kernel_Keylogger>();
    } else if(tip==4){
        m = make_shared<Ransomware>();
    }  else {
        cout << "Malware not found! ";
        return nullptr;
    }
    return m;
}

class computer{
private:
    vector <shared_ptr<Malware> > malwares;
    int finalRating;
public:
    istream &read(istream &is) override {
        int n;
        cout<<"Nr malwares: "; is>>n;
        for(int i=0; i<n; i++)
            malwares.push_back(citireMW());
        is >> finalRating;
        return is;
    }

    ostream &write(ostream &os) const override {
        os<<"Malware: ";
        for(int i=0; i < malwares.size(); i++)
            os<<*malwares[i]<<endl;
        os << finalRating;
        return os;
    }
};


int main() {

}


