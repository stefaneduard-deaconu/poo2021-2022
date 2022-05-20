#include <bits/stdc++.h>

/*
 * Cringanu Denis-Florin
 * mingw
 * Deaconu Stefan
 */

using namespace std;

const vector<string> rootkitStringRec = {"System Service Descriptor Table", "SSDT", "NtCreateFile"};
const vector<string> rootkitImportRec = {"ntoskrnl.exe"};

const vector<string> keyloggerStringRec = {"[Up]", "[Num Lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"};
const vector<string> keyloggerFunctionRec = {"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey", "SetWindowsHookEx"};

const vector<string> mallwareRec = {"HKLM-run", "HKCU-run"};

template <typename T>
istream& operator>>(istream& is, vector<T> &v){
    int n;
    T temp;
    cout << "Numarul de elemente = ";
    is >> n;
    for(int i = 0; i < n; i++){
        cout << "Elementul " << i << ":";
        is >> temp;
        v.push_back(temp);
    }

    return is;
}

istream& operator>>(istream& is, vector<string> &v){
    int n;
    string temp;
    cout << "Numarul de elemente = ";
    is >> n; is.get();
    for(int i = 0; i < n; i++){
        cout << "Elementul " << i << ":";
        getline(is, temp);
        //is >> temp;
        v.push_back(temp);
    }

    return is;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T> &v){
    os << "Numarul de elemente = " << v.size() << '\n';
    for(int i = 0; i < v.size(); i++){
        os << "Elementul " << i << ":" << v[i] << '\n';
    }

    return os;
}

class IOBase{
public:
    virtual istream &read(istream &is){
        return is;
    }

    virtual ostream &write(ostream &os) const{
        return os;
    }

    friend ostream &operator<<(ostream &os, const IOBase &base) {
        return base.write(os);
    }

    friend istream &operator>>(istream &is, IOBase &base) {
        return base.read(is);
    }
};

class malware : public IOBase {

protected:
    double rating;
    int zi, luna, an;
    string nume, metodaDeInfectare;

    vector<string> registriiAfectati;

public:
    malware() { }

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "nume:";
        is.get();
        getline(is, nume);

        cout << "Data infectarii:\nZi:";
        is >> zi;
        cout << "Luna:"; is >> luna;
        cout << "An:"; is >> an;

        cout << "Metoda infectarii:";
        is.get();
        getline(is, metodaDeInfectare);

        cout << "Registrii afectati:\n";
        is >> registriiAfectati;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "nume:" << nume;
        os << "\nData infectarii:\nZi:" << zi << "\nLuna:" << luna << "\nAn:" << an;

        os << "\nMetoda infectarii:" << metodaDeInfectare;

        os << "\nRegistrii afectati:\n" << registriiAfectati;

        return os;
    }

    const vector<string> &getRegistriiAfectati() const {
        return registriiAfectati;
    }

    void setRating(double rating) {
        malware::rating = rating;
    }
};

class rootkit : public virtual malware {

protected:
    vector<string> listaImporturi;
    vector<string> stringImportante;

public:
    istream &read(istream &is) override {
        malware::read(is);
        cout << "Lista de importuri:\n";
        is >> listaImporturi;
        cout << "Stringurile importante:\n";
        is >> stringImportante;

        return is;
    }

    ostream &write(ostream &os) const override {
        malware::write(os);
        os << "Lista de importuri:\n" << listaImporturi;
        os << "Stringurile importante:\n" << stringImportante;

        return os;
    }

    vector<string> getListaImporturi(){
        return listaImporturi;
    }

    vector<string> getStringImportante(){
        return stringImportante;
    }
};

class keylogger : public virtual malware {

protected:
    vector<string> listaFunctiilor, listaTasteSpeciale;

public:
    istream &read(istream &is) override {
        malware::read(is);
        cout << "Lista functiilor:\n";
        is >> listaFunctiilor;
        cout << "Lista testelor speciale:\n";
        is >> listaTasteSpeciale;

        return is;
    }

    ostream &write(ostream &os) const override {
        malware::write(os);
        os << "Lista functiilor:\n" << listaFunctiilor;
        os << "Lista testelor speciale:\n" << listaTasteSpeciale;

        return os;
    }

    vector<string> getListaFunctiilor(){
        return listaFunctiilor;
    }

    vector<string> getListaTasteSpeciale(){
        return listaTasteSpeciale;
    }
};

class kernel_keylogger : public keylogger, public rootkit {
protected:

    bool ascundeFisiere, ascundeRegistrii;

public:
    istream &read(istream &is) override {
        keylogger::read(is);
        cout << "Lista de importuri:\n";
        is >> listaImporturi;
        cout << "Stringurile importante:\n";
        is >> stringImportante;

        cout << "Ascunde fisiere (0-Nu,1-Da) :"; is >> ascundeFisiere;
        cout << "Ascunde registrii (0-Nu,1-Da) :"; is >> ascundeRegistrii;

        return is;
    }

    ostream &write(ostream &os) const override {
        keylogger::write(os);
        os << "Lista de importuri:\n" << listaImporturi;
        os << "Stringurile importante:\n" << stringImportante;

        os << "Ascunde fisiere (0-Nu,1-Da) :" <<  ascundeFisiere << '\n';
        cout << "Ascunde registrii (0-Nu,1-Da) :" << ascundeRegistrii << '\n';

        return os;
    }

    bool isAscundeFisiere() const {
        return ascundeFisiere;
    }

    bool isAscundeRegistrii() const {
        return ascundeRegistrii;
    }
};

class ransomware : public malware {
    int ratingCriptare;
    double ratingObfuscare;

public:
    istream &read(istream &is) override {
        malware::read(is);
        cout << "Rating criptare:"; is >> ratingCriptare;
        cout << "Raing obfuscare:"; is >> ratingObfuscare;

        return is;
    }

    ostream &write(ostream &os) const override {
        malware::write(os);
        os << "Rating criptare:" << ratingCriptare << '\n';
        os << "Raing obfuscare:" << ratingObfuscare << '\n';

        return os;
    }

    int getRatingCriptare() const {
        return ratingCriptare;
    }

    double getRatingObfuscare() const {
        return ratingObfuscare;
    }
};

int searchFor(vector<string> listaDeCautat, string val){
    int cnt = 0;
    for(int i = 0; i < listaDeCautat.size(); i++){
        if(val == listaDeCautat[i])
            ++cnt;
    }
    return cnt;
}

class calculator : public IOBase {
    int idUnic;
    double rating;
    vector<shared_ptr<malware>> listaDeMalware;

public:
    istream &read(istream &is) override {
        IOBase::read(is);
        int n;
        cout << "Numarul de malware = "; is >> n;
        rating = 0;
        idUnic = 0;
        for(int i = 0; i < n; i++){
            int tip = 0;
            while(tip < 1 || tip > 4) {
                cout << "Tipul de malware:\n1-rootkit\n2-keylogger\n3-kernel_keylogger\n4-ransomware\ntip:";
                is >> tip;
                if(tip < 0 || tip > 4)
                    cout << "Valoare introdusa gresit!\n";
            }

            double currentRating = 0;
            shared_ptr<malware> temp;
            if(tip == 1){
                temp = make_shared<rootkit>();
                is >> *temp;
                listaDeMalware.push_back(temp);

                for(int i = 0; i < mallwareRec.size(); i++){
                    int cnt = searchFor(dynamic_cast<malware*>(temp.get())->getRegistriiAfectati(), mallwareRec[i]);
                    if(cnt > 0)
                        currentRating += 20;
                }

                for(int i = 0; i < rootkitStringRec.size(); i++){
                    int cnt = searchFor(dynamic_cast<rootkit*>(temp.get())->getStringImportante(), rootkitStringRec[i]);
                    if(cnt > 0)
                        currentRating += 100;
                }

                for(int i = 0; i < rootkitImportRec.size(); i++) {
                    int cnt = searchFor(dynamic_cast<rootkit *>(temp.get())->getListaImporturi(), rootkitImportRec[i]);
                    if(cnt > 0)
                        currentRating *= 2;
                }

                rating += currentRating;

            } else if(tip == 2){
                temp = make_shared<keylogger>();
                is >> *temp;
                listaDeMalware.push_back(temp);

                for(int i = 0; i < mallwareRec.size(); i++){
                    int cnt = searchFor(dynamic_cast<malware*>(temp.get())->getRegistriiAfectati(), mallwareRec[i]);
                    if(cnt > 0)
                        currentRating += 20;
                }

                for(int i = 0; i < keyloggerFunctionRec.size(); i++){
                    int cnt = searchFor(dynamic_cast<keylogger*>(temp.get())->getListaFunctiilor(), keyloggerFunctionRec[i]);
                    if(cnt > 0)
                        currentRating += 10;
                }

                for(int i = 0; i < keyloggerStringRec.size(); i++) {
                    int cnt = searchFor(dynamic_cast<keylogger *>(temp.get())->getListaTasteSpeciale(), keyloggerStringRec[i]);
                    if(cnt > 0)
                        currentRating += 30;
                }

                rating += currentRating;

            } else if(tip == 3){
                temp = make_shared<kernel_keylogger>();
                is >> *temp;
                listaDeMalware.push_back(temp);

                for(int i = 0; i < mallwareRec.size(); i++){
                    int cnt = searchFor(dynamic_cast<malware*>(temp.get())->getRegistriiAfectati(), mallwareRec[i]);
                    if(cnt > 0)
                        currentRating += 20;
                }

                for(int i = 0; i < rootkitStringRec.size(); i++){
                    int cnt = searchFor(dynamic_cast<rootkit*>(temp.get())->getStringImportante(), rootkitStringRec[i]);
                    if(cnt > 0)
                        currentRating += 100;
                }

                for(int i = 0; i < rootkitImportRec.size(); i++) {
                    int cnt = searchFor(dynamic_cast<rootkit *>(temp.get())->getListaImporturi(), rootkitImportRec[i]);
                    if(cnt > 0)
                        currentRating *= 2;
                }

                for(int i = 0; i < keyloggerFunctionRec.size(); i++){
                    int cnt = searchFor(dynamic_cast<keylogger*>(temp.get())->getListaFunctiilor(), keyloggerFunctionRec[i]);
                    if(cnt > 0)
                        currentRating += 10;
                }

                for(int i = 0; i < keyloggerStringRec.size(); i++) {
                    int cnt = searchFor(dynamic_cast<keylogger *>(temp.get())->getListaTasteSpeciale(), keyloggerStringRec[i]);
                    if(cnt > 0)
                        currentRating += 30;
                }

                bool ascundeFisiere = dynamic_cast<kernel_keylogger *>(temp.get())->isAscundeFisiere();
                if(ascundeFisiere)
                    currentRating += 20;
                bool ascundeRegistrii = dynamic_cast<kernel_keylogger *>(temp.get())->isAscundeRegistrii();
                if(ascundeFisiere)
                    currentRating += 30;

                rating += currentRating;

            } else if(tip == 3){
                temp = make_shared<ransomware>();
                is >> *temp;
                listaDeMalware.push_back(temp);

                currentRating = dynamic_cast<ransomware *>(temp.get())->getRatingCriptare() + dynamic_cast<ransomware *>(temp.get())->getRatingObfuscare();
                for(int i = 0; i < mallwareRec.size(); i++){
                    int cnt = searchFor(dynamic_cast<malware*>(temp.get())->getRegistriiAfectati(), mallwareRec[i]);
                    if(cnt > 0)
                        currentRating += 20;
                }

                rating += currentRating;
            }

            dynamic_cast<malware*>(temp.get())->setRating(currentRating);

        }

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Rating:" << rating << '\n';
        os << "ID:" << idUnic << '\n';
        os << "Numarul de malware: " << listaDeMalware.size() << '\n';
        for(int i = 0; i < listaDeMalware.size(); i++){
            os << *listaDeMalware[i];
        }

        return os;
    }

    int getNrMalware(){
        return  listaDeMalware.size();
    }

    int getRating() const {
        return rating;
    }

    void setIdUnic(int idUnic) {
        calculator::idUnic = idUnic;
    }
};

int main() {
    int nr;
    vector<calculator> computers;
    cout << "Numarul de calculatoare din firma:"; cin >> nr;
    for(int i = 0; i < nr; i++){
        calculator temp;
        cin >> temp;
        computers.push_back(temp);
        computers[i].setIdUnic(i + 1);
    }

    while(true){
        int optiune = -1;
        while(optiune < 0 || optiune > 4){
            cout << "0. Exit \n"
                 << "1. afisarea informatiilor pentru fiecare calculator \n"
                 << "2. afisarea informatiilor pentru fiecare calculator fiind ordonate dupa ratingul final \n"
                 << "3. afisarea primelor k calculatoare ordonate dupa ratingul final \n"
                 << "4. afisarea procentului de computere infectate din firma \n";
            cout << "Optiune:"; cin >> optiune;
            if(optiune < 0 || optiune > 4)
                cout << "Ati introdus o optiune gresita!\n";
        }

        if(optiune == 0)
            break;
        else if(optiune == 1){
            cout << "Numarul de calculatoare din firma:" << computers.size();
            for(int i = 0; i < computers.size(); i++)
                cout << computers[i] << '\n';
        } else if(optiune == 2){
            vector<pair <int, int> > ratingSort;
            for(int i = 0; i < computers.size(); i++)
                ratingSort.push_back({computers[i].getRating(), i});
            sort(ratingSort.begin(), ratingSort.end());
            for(int i = 0; i < computers.size(); i++){
                cout << computers[ratingSort[i].second];
            }
        } else if(optiune == 3){
            int k;
            cout << "k = "; cin >> k;
            vector<pair <int, int> > ratingSort;
            for(int i = 0; i < computers.size(); i++)
                ratingSort.push_back({computers[i].getRating(), i});
            sort(ratingSort.begin(), ratingSort.end());
            try {
                for (int i = 0; i < k; i++) {
                    if(i >= computers.size())
                        throw out_of_range("Error! K mai mare decat lungimea vectorului!");
                    cout << computers[ratingSort[i].second];
                }
            } catch(out_of_range){
                cout << "K mai mare decat lungimea vectorului!\n";
                continue;
            }
        } else if(optiune == 4){
            int cnt = 0;
            for(int i = 0; i < computers.size(); i++) {
                cout << "lool " << computers[i].getNrMalware() << '\n';
                if (computers[i].getNrMalware() > 0)
                    ++cnt;
            }
            cout << "Procentul de calculatoare infectate este:" << (double)(cnt) / computers.size() * 100 << "%\n";
        }
    }

    return 0;
}
