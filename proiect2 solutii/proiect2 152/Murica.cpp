#include <bits/stdc++.h>
#include "util/IoBase.h"
#include <memory>
#include <vector>
#include <bits/stl_vector.h>

using namespace std;



class data {
protected:
    int zi, luna, an;
public:
    void setZi(int zi) {
        data::zi = zi;
    }

    void setLuna(int luna) {
        data::luna = luna;
    }

    void setAn(int an) {
        data::an = an;
    }

    int getZi() const {
        return zi;
    }

    int getLuna() const {
        return luna;
    }

    int getAn() const {
        return an;
    }
};
class malware : public IoBase {
protected :
    double impact;
    data d;
    string name, metoda;
    vector<string> registrii;
public:
    malware(const data &d, const string &name, const string &metoda, const vector<string> &registrii)
            : impact(0), d(d), name(name), metoda(metoda), registrii(registrii) {}

    malware(double impact, const data &d, const string &name, const vector<string> &registrii) : impact(impact), d(d),
    name(name), metoda("unknown"), registrii(registrii) {}

    double getImpact() const;

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;


    malware();
};

istream &malware::read(istream &is) {
    int a ;
    IoBase::read(is);
    cout<<"Nume:";
    is>>name;
    cout<<"Metoda:";
    is>>metoda;
    cout<<"Data:\nZiua:";
    is>>a;
    d.setZi(a);
    cout<<"Luna:";
    is>>a;
    d.setLuna(a);
    cout<<"An:";
    is>>a;
    d.setAn(a);
    cout<<"impact";
    is>>impact;
    cout<<"Nr registrii";
    is>>a;
    string c;
    cout<<"registrii";
    for(int i=0;i<a;i++) {
        is>>c;
        registrii.push_back(c);
    }
    return is;
}

ostream &malware::write(ostream &os) const {
    IoBase::write(os);
    os<<"Nume:"<<name<<"\nMetoda:"<<metoda<<endl<<"Impact"<<impact<<"\ndata:"<<d.getZi()<<d.getLuna()<<d.getAn()<<"\nNr registrii:"<<registrii.size()<<endl;
    for (auto x: registrii) {
        os<<x<<" ";
    }
    return os;
}

malware::malware() {

}

double malware::getImpact() const {
    return impact;
}


class rootkit: public malware{
private:
    vector<string> imports;
    vector<string> semnificative;
    int rating;
public:
    rootkit(double impact, const data &d, const string &name, const string &metoda, const vector<string> &registrii, const vector<string> &imports, const vector<string> &semnificative) : malware(d, name, metoda,registrii), imports(imports),semnificative(semnificative), rating(0) {}
    void setImpact();

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
    rootkit();
};


void rootkit::setImpact() {
    vector<string> rau={"System Service Descriptor Table", "SSDT", "NtCreateFile"};
    for (auto x : semnificative) {
        for (auto y : rau) {
            if (x==y) {
                impact+=100;
            }
        }
    }
    for (auto x: imports) {
        if (x=="ntoskrnl.exe") {
            impact*=2;
            break;
        }
    }

}

istream &rootkit::read(istream &is) {
    malware::read(is);
    cout<<"Nr imports";
    int a;
    is>>a;
    string c;
    cout<<"imports";
    for(int i=0;i<a;i++) {
        is>>c;
        imports.push_back(c);
    }
    cout<<"Nr semnificative";
    is>>a;
    cout<<"semnificative";
    for(int i=0;i<a;i++) {
        is>>c;
        semnificative.push_back(c);
    }
    return is;
}

ostream &rootkit::write(ostream &os) const {
    os<<"Rootkit"<<endl;
    malware::write(os);
    os<<"\nsemnificative\n";
    for (auto x: semnificative) {
        os<<x<<" ";
    }
    os<<"\nimports\n";
    for (auto x: imports) {
        os<<x<<" ";
    }
    return os;
}

rootkit::rootkit() {

}



class keylogger: public malware {
private:
    vector<string> functii, taste;
public:
    void setImpact() ;

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

void keylogger::setImpact() {
    vector<string> rau={"[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
    for (auto x : taste) {
        for (auto y : rau) {
            if (x==y) {
                impact+=10;
            }
        }
    }
    rau={"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};
    for (auto x: functii) {
        for (auto y : rau) {
            if (x == y) {
                impact += 20;
            }
        }
    }

}

istream &keylogger::read(istream &is) {
    malware::read(is);
    cout<<"Nr functii";
    int a;
    is>>a;
    string c;
    cout<<"functii";
    for(int i=0;i<a;i++) {
        is>>c;
        functii.push_back(c);
    }
    cout<<"Nr semnificative";
    is>>a;
    cout<<"taste";
    for(int i=0;i<a;i++) {
        is>>c;
        taste.push_back(c);
    }
    return is;
}

ostream &keylogger::write(ostream &os) const {
    os<<"keylogger"<<endl;
    malware::write(os);
    os<<"\nsemnificative\n";
    for (auto x: functii) {
        os<<x<<" ";
    }
    os<<"\nimports\n";
    for (auto x: taste) {
        os<<x<<" ";
    }
    return os;
}


class kernelkeylogger : public keylogger {
private:
    vector<string> imports;
    vector<string> semnificative;
    string ascunde;
public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
    void setImpact() ;
};

ostream &kernelkeylogger::write(ostream &os) const {
    os<<"kernelkeylogger"<<endl;
    keylogger::write(os);
    os<<"\nsemnificative\n";
    for (auto x: semnificative) {
        os<<x<<" ";
    }
    os<<"\nimports\n";
    for (auto x: imports) {
        os<<x<<" ";
    }
    os<<"\nAscunde: "<<ascunde<<endl;
    return os;

}

istream &kernelkeylogger::read(istream &is) {
    keylogger::read(is);
    cout<<"Nr imports";
    int a;
    is>>a;
    string c;
    cout<<"imports";
    for(int i=0;i<a;i++) {
        is>>c;
        imports.push_back(c);
    }
    cout<<"Nr semnificative";
    is>>a;
    cout<<"semnificative";
    for(int i=0;i<a;i++) {
        is>>c;
        semnificative.push_back(c);
    }
    cout<<"\nAscunde?";
    is>>ascunde;
    return is;
}

void kernelkeylogger::setImpact() {
    keylogger::setImpact();
    vector<string> rau={"System Service Descriptor Table", "SSDT", "NtCreateFile"};
    for (auto x : semnificative) {
        for (auto y : rau) {
            if (x==y) {
                impact+=100;
            }
        }
    }
    for (auto x: imports) {
        if (x=="ntoskrnl.exe") {
            impact*=2;
            break;
        }
    }
}


class ransomware : public malware {
    int rating;
    double obfuscare;
public:
    ransomware(double impact, const data &d, const string &name, const string &metoda, const vector <string> &registrii,
               int rating, double obfuscare) : malware(d, name, metoda, registrii), rating(rating),
                                               obfuscare(obfuscare) {}

    ransomware(double impact, const data &d, const string &name, const vector<string> &registrii, int rating,
               double obfuscare) : malware(impact, d, name, registrii), rating(rating), obfuscare(obfuscare) {}

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    ransomware();
};

istream &ransomware::read(istream &is) {
    malware::read(is);
    cout<<"\nrating: ";
    is>>rating;
    cout<<"\nobfuscare :";
    is>>obfuscare;
    return is;
}

ostream &ransomware::write(ostream &os) const {
    os<<endl<<"Ransomware"<<endl;
    malware::write(os);
    os<<"\nrating: "<<rating<<"\nobfuscare: "<<obfuscare;
    return os;
}

ransomware::ransomware() {

}
class calculator : public IoBase{
private:
    static int id;
    int idc;
    vector<shared_ptr<malware> > lista;
    int rating;
public:
    calculator(vector<shared_ptr<struct malware>> vector1) {
        idc=++id;
        lista=vector1;
        rating=0;
        for (auto x: lista) {
            rating+=x->getImpact();
        }

    }

    int getRating() const;

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os<<"ID: "<<idc<<endl;
        for (auto x: lista) {
            os<<*x<<endl;
        }
        os<<"\nRating "<<rating;
        return os;
    }

    calculator() {

    }
};

int calculator::id=0;

int calculator::getRating() const {
    return rating;
}

int main() {
    vector<calculator> calc;
    int n, m;
    int infectat=0;
    cout<<"cate calculatoare";
    cin>>n;
    for (int i=0;i<n;i++) {
        cout<<"Cate malware?";
        cin>>m;
        if (m>0) {
            infectat++;
        }
        vector<shared_ptr<malware>> lista;
        for(int l=0;l<m;l++) {
            cout<<"Ce tip";
            string tip;
            cin>>tip;
            if(tip=="rootkit") {
                rootkit a;
                cin>>a;
                a.setImpact();
                lista.push_back(make_shared<rootkit>(a));
            }
            if(tip=="keylogger") {
                keylogger a;
                cin>>a;
                a.setImpact();
                lista.push_back(make_shared<keylogger>(a));
            }
            if(tip=="ransomware") {
                ransomware a;
                cin>>a;
                lista.push_back(make_shared<ransomware>(a));
            }
            if(tip=="kernelkeylogger") {
                kernelkeylogger a;
                cin>>a;
                lista.push_back(make_shared<kernelkeylogger>(a));
            }
        }
        calc.push_back(calculator(lista));
    }
    for(auto x: calc) {
        cout<<x;
    }
    for (int i = 0; i < calc.size(); i++) {
        for (int j = i + 1; j <  calc.size(); j++) {
            if (calc[i].getRating() < calc[j].getRating()) {
                swap(calc[i], calc[j]);
            }
        }
    }
    cout<<endl<<"Calculatoare sortate"<<endl<<endl;
    for(auto x: calc) {
        cout<<x;
    }
    cout<<"infectate "<<double (n)/double(infectat);
    return 0;
}