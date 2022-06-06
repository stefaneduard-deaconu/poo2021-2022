#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>

#include "IoBase.h"

using namespace std;

class Data{
public:
    int zi, luna, an;
};

class Computer;

class Malware : public IoBase{
public:
    Malware(const Data &dataInfectare, const string &nume,
            const string &metodaInfectare,
            const vector<string> &registriiModificati) :
                impact_rating(0.0), data_infectare(dataInfectare),
                nume(nume), metoda_infectare(metodaInfectare),
                registrii_modificati(registriiModificati),
                has_impact(false){}

    Malware(): impact_rating(0.0), has_impact(false) {}

    double getImpactRating() const {
        return impact_rating;
    }

    const Data &getDataInfectare() const {
        return data_infectare;
    }

    void setDataInfectare(const Data &dataInfectare) {
        data_infectare = dataInfectare;
    }

    const string &getNume() const {
        return nume;
    }

    void setNume(const string &nume) {
        this->nume = nume;
    }

    const string &getMetodaInfectare() const {
        return metoda_infectare;
    }

    void setMetodaInfectare(const string &metodaInfectare) {
        metoda_infectare = metodaInfectare;
    }

    const vector<string> &getRegistriiModificati() const {
        return registrii_modificati;
    }

    void setRegistriiModificati(const vector<string> &registriiModificati) {
        registrii_modificati = registriiModificati;
    }

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    virtual void calculeaza_impact();


private:
    Data data_infectare;
    string nume;
    string metoda_infectare;
    vector<string> registrii_modificati;

    bool has_impact;

protected:
    double impact_rating;

};

void Malware::calculeaza_impact() {

    if (has_impact)
        return;

    for (string registru : registrii_modificati){
        if (registru == ("HKLM-run") || registru ==("HKCU-run"))
            has_impact = 1;
    }

    if (has_impact)
        impact_rating += 20.0;
}

istream &Malware::read(istream &is) {
    IoBase::read(is);
    cout    <<  "Introduceti numele: \n";
    is      >>  nume;

    cout    <<  "Introduceti data infectarii (zi, luna, an): \n";
    is      >>  data_infectare.zi   >>  data_infectare.luna >>  data_infectare.an;

    cout    <<  "Introduceti metoda de infectare (daca nu este cunoscuta, introduceti unknown): \n";
    is      >>  metoda_infectare;

    cout    <<  "Introduceti numarul de registrii modificati: \n";
    int numar;
    is      >>  numar;

    for (int i=1; i<= numar; i++){
        string registru;
        cout    <<  "Introduceti registru modificat: ";
        is      >>  registru;

        registrii_modificati.push_back(registru);
    }

    return is;
}

ostream &Malware::write(ostream &os) const {
    IoBase::write(os);

    os      <<  "Numele este: " <<  nume    <<  "\n"
            <<  "Data infectariie este: "   <<  data_infectare.zi   <<  "." <<  data_infectare.luna
            <<  "." <<  data_infectare.an   <<  "\n"
            <<  "Metoda infectarii este: "  <<  metoda_infectare    <<  "\n"
            <<  "Registrii modificati sunt: ";

    for (string str:registrii_modificati)
        os      <<  str <<  " ";

    os      <<  "\n";

    return os;
}

class Rootkit : public virtual Malware{
public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    virtual void calculeaza_impact() override;

    Rootkit(const Data &dataInfectare, const string &nume, const string &metodaInfectare,
            const vector<string> &registriiModificati, const vector<string> &listaImporturi,
            const vector<string> &stringuriSemnificative) :
                Malware(dataInfectare, nume, metodaInfectare,
                registriiModificati),
                lista_importuri(listaImporturi),
                stringuri_semnificative(stringuriSemnificative) {}

    Rootkit() {}

    const vector<string> &getListaImporturi() const {
        return lista_importuri;
    }

    void setListaImporturi(const vector<string> &listaImporturi) {
        lista_importuri = listaImporturi;
    }

    const vector<string> &getStringuriSemnificative() const {
        return stringuri_semnificative;
    }

    void setStringuriSemnificative(const vector<string> &stringuriSemnificative) {
        stringuri_semnificative = stringuriSemnificative;
    }

private:
    vector<string> lista_importuri;
    vector<string> stringuri_semnificative;
};

void Rootkit::calculeaza_impact() {
    Malware::calculeaza_impact();

    bool good = 0;
    for (string str: stringuri_semnificative){
        if (str == "System Service Descriptor Table" || str == "SSDT" || str == "NtCreateFile")
            impact_rating += 100.0;
    }

    for (string str: lista_importuri) {
        if (str == "ntoskrnl.exe")
            good = 1;
    }

    if (good)
        impact_rating *= 2.0;
}

istream &Rootkit::read(istream &is) {
    Malware::read(is);

    cout    <<  "Introduceti numarul de importuri: ";
    int numar_importuri;
    is      >>  numar_importuri;

    for (int i=1; i<= numar_importuri; i++){
        string str;
        cout    <<  "\nIntroduceti importul:";
        is      >>  str;
        lista_importuri.push_back(str);
    }

    cout    <<  "Introduceti numarul de siruri semnificative: ";
    int numar_siruri_semnificative;
    is      >>  numar_siruri_semnificative;

    for (int i=1; i<= numar_siruri_semnificative; i++){
        string str;
        cout    <<  "\nIntroduceti sirul semnificativ:";
        is      >>  str;
        stringuri_semnificative.push_back(str);
    }

    return is;
}

ostream &Rootkit::write(ostream &os) const {
    Malware::write(os);

    os      <<  "Importuri: \n";
    for (string str : lista_importuri)
        os      <<  str <<  " ";

    os      <<  "\nSiruri semnificative: ";
    for (string str : stringuri_semnificative)
        os      <<  str <<  " ";

    os      <<  "\n";

    return os;

}

class Keylogger : public virtual Malware{
protected:
    vector<string> functii_folosite;
    vector<string> taste_speciale;
public:
    Keylogger(const Data &dataInfectare, const string &nume, const string &metodaInfectare,
              const vector<string> &registriiModificati, const vector<string> &functiiFolosite,
              const vector<string> &tasteSpeciale):
              Malware(dataInfectare, nume, metodaInfectare, registriiModificati),
              functii_folosite(functiiFolosite), taste_speciale(tasteSpeciale) {}

    Keylogger() {}

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    virtual void calculeaza_impact() override;

    const vector<string> &getFunctiiFolosite() const {
        return functii_folosite;
    }

    void setFunctiiFolosite(const vector<string> &functiiFolosite) {
        functii_folosite = functiiFolosite;
    }

    const vector<string> &getTasteSpeciale() const {
        return taste_speciale;
    }

    void setTasteSpeciale(const vector<string> &tasteSpeciale) {
        taste_speciale = tasteSpeciale;
    }
};

void Keylogger::calculeaza_impact() {
    Malware::calculeaza_impact();

    for (string str : taste_speciale){
        if (str == "[Up]" || str == "[Num Lock]" || str == "[Down]" || str == "[Right]" ||
            str == "[UP]" || str == "[Left]" || str == "[PageDown]")
            impact_rating += 10;
    }

    for (string str : functii_folosite){
        if (str == "CreateFileW" || str == "OpenProcess" || str == "ReadFile" || str == "WriteFile" ||
            str == "RegisterHotKey" || str == "SetWindowsHookEx")
            impact_rating += 30;
    }
}

istream &Keylogger::read(istream &is) {
    Malware::read(is);

    cout    <<  "Introduceti numarul de functii folosite: ";
    int numar_functii;
    is      >>  numar_functii;
    for (int i=1; i <= numar_functii; i++){
        cout    <<  "\nIntroduceti functia: ";


        string str;
        is      >>  str;
        functii_folosite.push_back(str);
    }

    cout    <<  "\nIntroduceti numarul de taste speciale folosite: ";
    int numar_taste;
    is      >>  numar_taste;
    for (int i=1; i <= numar_taste; i++){
        cout    <<  "\nIntroduceti tasta speciala: ";

        string str;
        is      >>  str;
        taste_speciale.push_back(str);
    }
    cout    <<  "\n";
    return is;
}

ostream &Keylogger::write(ostream &os) const {
    Malware::write(os);

    os      <<  "Functiile folosite sunt: ";
    for (string str: functii_folosite){
        os      <<  str <<  " ";
    }

    os      <<  "\nTastele speciale folosite sunt: ";
    for (string str: taste_speciale){
        os      <<  str <<  " ";
    }

    os      <<  "\n";
    return os;
}

class KernelKeylogger : public virtual Rootkit, public virtual Keylogger{
private:
    bool ascunde_fisiere;
    bool ascunde_registrii;
public:
    KernelKeylogger(const Data &dataInfectare, const string &nume, const string &metodaInfectare,
                    const vector<string> &registriiModificati, const vector<string> &functiiFolosite,
                    const vector<string> &tasteSpeciale, const vector<string> &listaImporturi,
                    const vector<string> &stringuriSemnificative, bool ascundeFisiere,
                    bool ascundeRegistrii):
                        Keylogger(dataInfectare, nume, metodaInfectare, registriiModificati,
                                  functiiFolosite,
                                  tasteSpeciale),
                                  ascunde_fisiere(ascundeFisiere),
                                  ascunde_registrii(ascundeRegistrii) {
        setListaImporturi(listaImporturi);
        setStringuriSemnificative(stringuriSemnificative);
    }

    KernelKeylogger() {}

    bool isAscundeFisiere() const {
        return ascunde_fisiere;
    }

    void setAscundeFisiere(bool ascundeFisiere) {
        ascunde_fisiere = ascundeFisiere;
    }

    bool isAscundeRegistrii() const {
        return ascunde_registrii;
    }

    void setAscundeRegistrii(bool ascundeRegistrii) {
        ascunde_registrii = ascundeRegistrii;
    }

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    void calculeaza_impact() override;

};

void KernelKeylogger::calculeaza_impact() {
    Rootkit::calculeaza_impact();
    Keylogger::calculeaza_impact();

    if (ascunde_fisiere)
        impact_rating += 20;

    if (ascunde_registrii)
        impact_rating += 30;
}

istream &KernelKeylogger::read(istream &is) {
    Rootkit::read(is);

    cout    <<  "Introduceti numarul de functii folosite: ";
    int numar_functii;
    is      >>  numar_functii;
    for (int i=1; i <= numar_functii; i++){
        cout    <<  "\nIntroduceti functia: ";


        string str;
        is      >>  str;
        Keylogger::functii_folosite.push_back(str);
    }

    cout    <<  "\nIntroduceti numarul de taste speciale folosite: ";
    int numar_taste;
    is      >>  numar_taste;
    for (int i=1; i <= numar_taste; i++){
        cout    <<  "\nIntroduceti tasta speciala: ";

        string str;
        is      >>  str;
        taste_speciale.push_back(str);
    }
    cout    <<  "\nAscunde registrii?(DA sau NU): ";
    string raspuns;
    is      >>  raspuns;
    if (raspuns == "DA")
        ascunde_registrii = true;
    else
        ascunde_registrii = false;

    cout    <<  "\nAscunde fisiere?(DA sau NU): ";
    is      >>  raspuns;
    if (raspuns == "DA")
        ascunde_fisiere = true;
    else
        ascunde_fisiere = false;

    cout    <<  "\n";
    return is;
}

ostream &KernelKeylogger::write(ostream &os) const {
    Rootkit::write(os);

    os      <<  "Functiile folosite sunt: ";
    for (string str: functii_folosite){
        os      <<  str <<  " ";
    }

    os      <<  "\nTastele speciale folosite sunt: ";
    for (string str: taste_speciale){
        os      <<  str <<  " ";
    }

    os      <<  "\n";

    if (ascunde_fisiere)
        os      <<  "Programul ascunde fisiere";
    else
        os      <<  "Programul NU ascunde fisiere";

    os      <<  "\n";
    if (ascunde_registrii)
        os      <<  "Programul ascunde registrii";
    else
        os      <<  "Programul NU ascunde registrii";

    return os;
}


class Ransomware : public Malware{
private:
    int rating_criptare;
    double rating_obfuscare;
public:
    Ransomware(const Data &dataInfectare, const string &nume, const string &metodaInfectare,
               const vector<string> &registriiModificati, int ratingCriptare, double ratingObfuscare) :
               Malware(dataInfectare, nume, metodaInfectare, registriiModificati),
               rating_criptare(ratingCriptare),
                rating_obfuscare(ratingObfuscare) {}

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    void calculeaza_impact() override;

    int getRatingCriptare() const {
        return rating_criptare;
    }

    void setRatingCriptare(int ratingCriptare) {
        rating_criptare = ratingCriptare;
    }

    double getRatingObfuscare() const {
        return rating_obfuscare;
    }

    void setRatingObfuscare(double ratingObfuscare) {
        rating_obfuscare = ratingObfuscare;
    }

    Ransomware() {}
};

void Ransomware::calculeaza_impact() {
    Malware::calculeaza_impact();

    impact_rating += (double)rating_criptare;
    impact_rating += rating_obfuscare;
}

istream &Ransomware::read(istream &is) {
    Malware::read(is);

    cout    <<  "Introduceti rating-ul de criptare: ";
    is      >>  rating_criptare;

    cout    <<  "\nIntroduceti rating-ul de obfuscare: ";
    is      >>  rating_obfuscare;

    cout    <<  "\n";
    return is;
}

ostream &Ransomware::write(ostream &os) const {
    Malware::write(os);

    os      <<  "Rating-ul de criptare este: "  <<  rating_criptare
            <<  "\nRating-ul de obfuscare este: " <<  rating_obfuscare
            <<  "\n";

    return os;
}

template <typename T>
istream& operator>>(istream& is, vector<shared_ptr<T>>& v) {
    v.clear();

    int lungime;
    cout << "Introduceti lungimea vectorului: \n";
    is      >> lungime;

    for (int i = 1; i <= lungime; i++) {
        shared_ptr<T> obiect = make_shared<T>();
        is      >> *obiect;
        v.push_back(obiect);
    }

    cout    <<  "\n";
    return is;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<shared_ptr<T>>& v) {
    os      <<  "Elementele vectorului sunt: \n";
    for (shared_ptr<T> obiect: v){
        os      <<  *obiect     <<  "\n";
    }

    os      <<  "\n";
    return os;
}

class Computer : public IoBase{
private:
    int id;
    static int id_curent;
    vector<shared_ptr<Malware>> virusi;
    int rating_final;

    void calculeaza_rating_final();

    void adauga_rating(int index_virus);

public:
    Computer(const vector<shared_ptr<Malware>> &virusi) :
            id(++id_curent), virusi(virusi), rating_final(0) {
        calculeaza_rating_final();
    }

    Computer(): id(++id_curent), rating_final(0)  {}

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    void adauga_virus(shared_ptr<Malware> virus);

    int getRatingFinal() const;

    void setRatingFinal(int ratingFinal);
};

void Computer::calculeaza_rating_final() {
    rating_final = 0;
    for (shared_ptr<Malware> virus : virusi){
        virus->calculeaza_impact();
        rating_final += virus->getImpactRating();
    }
}

void Computer::adauga_rating(int index_virus) {
    virusi[index_virus]->calculeaza_impact();
    rating_final += virusi[index_virus]->getImpactRating();
}

void Computer::adauga_virus(shared_ptr<Malware> virus) {
    virusi.push_back(virus);
    adauga_rating(virusi.size() - 1);
}

istream &Computer::read(istream &is) {
    IoBase::read(is);

    cout    <<  "Vom citi virusii specifici calculatorului: \n";
    is      >>  virusi;

    calculeaza_rating_final();
    cout    <<  "\n";
    return is;
}

ostream &Computer::write(ostream &os) const {
    IoBase::write(os);

    os      <<  "Id-ul calculatorului: "    <<  id  <<  "\n"
            <<  "Rating-ul final al calculatorului: "   <<  rating_final    <<  "\n"
            <<  "Vom afisa virusii specifici calculatorului: \n"
            <<  virusi
            <<  "\n";

    return os;
}

int Computer::id_curent = 0;

int Computer::getRatingFinal() const {
    return rating_final;
}

void Computer::setRatingFinal(int ratingFinal) {
    rating_final = ratingFinal;
}

class BaseMenu{
protected:
    vector<shared_ptr<Computer>>& calculatoare;

public:
    BaseMenu(vector<shared_ptr<Computer>>& calculatoare) : calculatoare(calculatoare) {}

    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};

class SimpleMenu : public BaseMenu{
public:
    SimpleMenu(vector<shared_ptr<Computer>> &calculatoare) : BaseMenu(calculatoare) {}

    void listOptions() override {
        cout    <<  "1. Afiseaza informatiile pentru fiecare calculator" <<  "\n";
        cout    <<  "2. Afiseaza informatiile pentru fiecare calculator ordonate dupa rating-ul final" <<  "\n";
        cout    <<  "3. Afiseaza primele k calculatoare ordonate dupa rating-ul final"    <<  "\n";
        cout    <<  "4. Afiseaza procentul de calculatoare infectate din firma"    <<  "\n";
        cout    <<  "5. Iesire" <<  "\n";
    }

    int chooseOption(int first, int last) override {
        int option = -1;
        while (option < first || option > last){
            cout    <<  "\n";
            cout    <<  "Pentru a rula comanda, alegeti un numar intre "
                    <<  first   <<  " si "  <<  last    <<  "\n";
            listOptions();
            cout    <<  "Alegere: ";
            cin     >>  option;
        }

        return option;
    }

    void option1(){
        cout    <<  calculatoare    <<  "\n";
    }

    void option2(){
        option3(calculatoare.size());
    }

    void option3(int k){
        cout    <<  "Primele k calculatoare sunt: "    <<  "\n";

        vector<shared_ptr<Computer>> calculatoare_ordonate(calculatoare);
        sort(calculatoare_ordonate.begin(), calculatoare_ordonate.end(), cmp_function);

        for (int i = 0; i < k; i++)
            cout    <<  *calculatoare_ordonate[i]    <<    "\n";
    }

    void option4(){
        int nr_calculatoare = calculatoare.size();
        int nr_calculatoare_virusate = 0;

        for (int i = 0; i < nr_calculatoare; i++){
            if (calculatoare[i]->getRatingFinal() > 0)
                nr_calculatoare_virusate ++ ;
        }

        double procentaj_virusare = double (nr_calculatoare_virusate);
        procentaj_virusare /= nr_calculatoare;
        procentaj_virusare *= 100.0;

        cout    <<  "Procentajul de virusare este: "    <<  procentaj_virusare  <<  "\n";
    }

    void mainLoop() override {
        while (true){
            int option = chooseOption(1, 5);
            if (option == 1){
                option1();
            } else if (option == 2){
                option2();
            } else if (option == 3){
                cout    <<  "Introduceti k: ";
                int k;
                cin     >>  k;
                cout    <<  "\n";
                option3(k);
            } else if (option == 4){
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

private:
    static bool cmp_function(shared_ptr<Computer> computer1, shared_ptr<Computer> computer2){
        return (computer1->getRatingFinal() < computer2->getRatingFinal());
    }

};

int main() {
    vector<shared_ptr<Malware>> virusi = {
            make_shared<Keylogger>(), make_shared<KernelKeylogger>(),
            make_shared<Ransomware>()
            };

    //ifstream fin ("in.txt");
    cin     >>  *virusi[0]  >>  *virusi[1]  >>  *virusi[2];
    //fin.close();

    vector<shared_ptr<Computer>> calculatoare = {
            make_shared<Computer>(vector<shared_ptr<Malware>>{virusi[0], virusi[1]}),
            make_shared<Computer>(vector<shared_ptr<Malware>>{virusi[2]}),
            make_shared<Computer>()
    };

    SimpleMenu simpleMenu(calculatoare);
    simpleMenu.mainLoop();

    return 0;
}
