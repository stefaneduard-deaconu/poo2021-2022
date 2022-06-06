#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


class masca {
protected:
    string tipProtectie;
public:
    masca(const string &tipProtectie) : tipProtectie(tipProtectie) {}

    masca();
    const string &getTipProtectie() const {
        return tipProtectie;
    }
    void setTipProtectie(const string &tipProtectie) {
        masca::tipProtectie = tipProtectie;
    }

    friend ostream &operator<<(ostream &os, masca &masca) {
        return masca.printMasca(os);
    }
    friend istream &operator>>(istream &is, masca &masca){
        return masca.readMasca(is);
    }
    virtual istream &readMasca(istream &is) = 0;
    virtual ostream &printMasca(ostream &os) = 0;
};

masca::masca() {
    tipProtectie = "";
}

class mascaChirurgicala : public masca{
protected:
    string culoare;
    int numarPliuri;
    bool model;
public:
    mascaChirurgicala(const string &tipProtectie, const string &culoare, int numarPliuri, bool model) : masca(
            tipProtectie), culoare(culoare), numarPliuri(numarPliuri), model(model) {}

    mascaChirurgicala();
    const string &getCuloare() const {
        return culoare;
    }
    void setCuloare(const string &culoare) {
        mascaChirurgicala::culoare = culoare;
    }
    int getNumarPliuri() const {
        return numarPliuri;
    }
    void setNumarPliuri(int numarPliuri) {
        mascaChirurgicala::numarPliuri = numarPliuri;
    }
    bool isModel() const {
        return model;
    }
    void setModel(bool model) {
        mascaChirurgicala::model = model;
    }

    istream &readMasca(istream &is);
    ostream &printMasca(ostream &os);
};

mascaChirurgicala::mascaChirurgicala() {
    culoare = "";
    numarPliuri = 0;
    model = 0;
    tipProtectie = "";
}

istream & mascaChirurgicala::readMasca(istream &is) {
    cout<<"Tipul de protectie al mastii este:\n";
    getline(is, tipProtectie);
    cout<<"Culoare mastii este:\n";
    getline(is, culoare);
    cout<<"Numarul de pliuri al mastii este:\n";
    is>>numarPliuri;
    is.get();
    cout<<"Daca masta are model introduceti 1 daca nu are model 0:\n";
    is>>model;
    is.get();
    return is;
}

ostream & mascaChirurgicala::printMasca(ostream &os) {
    os<<"Tipul de protectie: "<<tipProtectie<<'\n';
    os<<"Culoarea: "<<culoare<<'\n';
    os<<"Numarul de pliuri: "<<numarPliuri<<'\n';
    os<<"Model special: "<<model<<'\n';
    return os;
}

class mascaPolicarbonat : virtual public masca{
private:
    string tipPrindere;
public:
    mascaPolicarbonat(const string &tipProtectie, const string &tipPrindere) : masca(tipProtectie),
                                                                               tipPrindere(tipPrindere) {}
    mascaPolicarbonat();

    const string &getTipPrindere() const;
    void setTipPrindere(const string &tipPrindere);

    istream &readMasca(istream &is);
    ostream &printMasca(ostream &os);
};

istream & mascaPolicarbonat::readMasca(istream &is){
    cout<<"Tipul de protectie al mastii este:\n";
    getline(is, tipProtectie);
    cout<<"Tipul de prindere al mastii este:\n";
    getline(is, tipPrindere);
    return is;
}

ostream &mascaPolicarbonat::printMasca(ostream &os) {
    os<<"Tipul de protectie: "<<tipProtectie<<'\n';
    os<<"Tipul de prindere: "<<tipPrindere<<'\n';
    return os;
}
mascaPolicarbonat::mascaPolicarbonat() {
    tipPrindere = "";
    tipProtectie = "";
}

const string &mascaPolicarbonat::getTipPrindere() const {
    return tipPrindere;
}
void mascaPolicarbonat::setTipPrindere(const string &tipPrindere) {
    mascaPolicarbonat::tipPrindere = tipPrindere;
}

class dezinfectant{
protected:
    int numarSpecii;
    vector<string> ingrediente;
    vector<string> suprafete;
    double eficienta;
public:

    dezinfectant(int numarSpecii, const vector<string> &ingrediente, const vector<string> &suprafete)
            : numarSpecii(numarSpecii), ingrediente(ingrediente), suprafete(suprafete) {}

    dezinfectant();

    dezinfectant(const dezinfectant& dezinfectant1);

    dezinfectant& operator=(const dezinfectant& dezinfectant1);

    int getNumarSpecii() const {
        return numarSpecii;
    }
    void setNumarSpecii(int numarSpecii) {
        dezinfectant::numarSpecii = numarSpecii;
    }
    const vector<string> &getIngrediente() const {
        return ingrediente;
    }
    void setIngrediente(const vector<string> &ingrediente) {
        dezinfectant::ingrediente = ingrediente;
    }
    const vector<string> &getSuprafete() const {
        return suprafete;
    }
    void setSuprafete(const vector<string> &suprafete) {
        dezinfectant::suprafete = suprafete;
    }
    double getEficienta() const {
        return eficienta;
    }
    void setEficienta(double eficienta) {
        dezinfectant::eficienta = eficienta;
    }

    virtual double calculeazaEficienta() = 0;

    friend ostream &operator<<(ostream &os, dezinfectant &dezinfectante);
    friend istream &operator>>(istream &is, dezinfectant &dezinfectante);
};

dezinfectant & dezinfectant::operator=(const dezinfectant &dezinfectant1) {
    numarSpecii = dezinfectant1.numarSpecii;
    ingrediente = dezinfectant1.ingrediente;
    suprafete = dezinfectant1.suprafete;
    eficienta = dezinfectant1.eficienta;
    return *this;
}

istream &operator>>(istream &is, dezinfectant &dezinfectante) {
    cout<<"Numarul de specii pe care il poate ucide:\n";
    is >> dezinfectante.numarSpecii;
    is.get();
    int numar;
    cout<<"Numarul de ingrediente folosite este:\n";
    is >> numar;
    is.get();
    for(int i = 1; i<= numar; ++i){
        cout<<"Ingredientul numarul "<<i<<" este:\n";
        string ingr;
        getline(is, ingr);
        dezinfectante.ingrediente.push_back(ingr);
    }
    cout<<"Numarul de suprafete pe care poate fi folosit:\n";
    is >> numar;
    is.get();
    for(int i = 1; i <= numar; ++i){
        cout<<"Suprafata numarul "<<i<<" este:\n";
        string supr;
        getline(is, supr);
        dezinfectante.suprafete.push_back(supr);
    }
    dezinfectante.calculeazaEficienta();
    return is;
}

ostream &operator<<(ostream &os, dezinfectant &dezinfectante) {
    os<<"Numarul de specii pe care dezinfectantul il ucide este:\n"<<dezinfectante.numarSpecii<<'\n';
    os<<"Ingredientele folosite sunt:\n";
    for(int i = 0 ; i < dezinfectante.ingrediente.size(); i++){
        os<<"Ingredientul cu numarul "<<i + 1<<" este:\n";
        os<<" - "<<dezinfectante.ingrediente[i]<<'\n';
    }
    os<<"Suprafetele pe care poate fi utilizat:\n";
    for(int i = 0; i < dezinfectante.suprafete.size(); i++){
        os<<"Suprafata numarul "<<i + 1<<" este:\n";
        os<<" - "<<dezinfectante.suprafete[i]<<'\n';
    }
    os<<"Eficienta este: " << dezinfectante.eficienta<<'\n';
    return os;
}

dezinfectant::dezinfectant() {
    numarSpecii = 0;
    ingrediente = {};
    suprafete = {};
    eficienta = 0;
}

dezinfectant::dezinfectant(const dezinfectant &dezinfectant1) {
    numarSpecii = dezinfectant1.numarSpecii;
    ingrediente = dezinfectant1.ingrediente;
    suprafete = dezinfectant1.suprafete;
    eficienta = dezinfectant1.eficienta;
}

class dezinfectantBacterii : virtual public dezinfectant{
protected:

public:
    dezinfectantBacterii(int numarSpecii, const vector<string> &ingrediente, const vector<string> &suprafete);
    dezinfectantBacterii();
    dezinfectantBacterii(const dezinfectantBacterii &dezinfectante);

    friend ostream &operator<<(ostream &os, dezinfectantBacterii &dezinfectante);
    friend istream &operator>>(istream &is, dezinfectantBacterii &dezinfectante);

    dezinfectantBacterii &operator=(const dezinfectantBacterii &dezinfectantBacterii1);

    double calculeazaEficienta();
};

double dezinfectantBacterii::calculeazaEficienta() {
    eficienta = (double)numarSpecii / (1000000000.0);
    return eficienta;
}

dezinfectantBacterii::dezinfectantBacterii() : dezinfectant(){}

istream &operator>>(istream &is, dezinfectantBacterii &dezinfectante) {
    cout<<"Numarul de specii pe care il poate ucide:\n";
    is >> dezinfectante.numarSpecii;
    is.get();
    int numar;
    cout<<"Numarul de ingrediente folosite este:\n";
    is >> numar;
    is.get();
    for(int i = 1; i<= numar; ++i){
        cout<<"Ingredientul numarul "<<i<<" este:\n";
        string ingr;
        getline(is, ingr);
        dezinfectante.ingrediente.push_back(ingr);
    }
    cout<<"Numarul de suprafete pe care poate fi folosit:\n";
    is >> numar;
    is.get();
    for(int i = 1; i <= numar; ++i){
        cout<<"Suprafata numarul "<<i<<" este:\n";
        string supr;
        getline(is, supr);
        dezinfectante.suprafete.push_back(supr);
    }
    dezinfectante.calculeazaEficienta();
    return is;
}
ostream &operator<<(ostream &os, dezinfectantBacterii &dezinfectante) {
    os<<"Numarul de specii pe care dezinfectantul il ucide este:\n"<<dezinfectante.numarSpecii<<'\n';
    os<<"Ingredientele folosite sunt:\n";
    for(int i = 0 ; i < dezinfectante.ingrediente.size(); i++){
        os<<"Ingredientul cu numarul "<<i + 1<<" este:\n";
        os<<" - "<<dezinfectante.ingrediente[i]<<'\n';
    }
    os<<"Suprafetele pe care poate fi utilizat:\n";
    for(int i = 0; i < dezinfectante.suprafete.size(); i++){
        os<<"Suprafata numarul "<<i + 1<<" este:\n";
        os<<" - "<<dezinfectante.suprafete[i]<<'\n';
    }
    os<<"Eficienta este: " << dezinfectante.eficienta<<'\n';
    return os;
}

dezinfectantBacterii::dezinfectantBacterii(int numarSpecii, const vector<string> &ingrediente,
                                           const vector<string> &suprafete) : dezinfectant(numarSpecii, ingrediente, suprafete){
    eficienta = calculeazaEficienta();
}

dezinfectantBacterii & dezinfectantBacterii::operator=(const dezinfectantBacterii &dezinfectantBacterii1) {
    dezinfectant::operator=(dezinfectantBacterii1);
    return *this;
}

class dezinfectantVirusi : virtual public dezinfectant{
protected:

public:
    dezinfectantVirusi(int numarSpecii, const vector<string> &ingrediente, const vector<string> &suprafete);
    dezinfectantVirusi(const dezinfectantVirusi &dezinfectantVirusi1);
    dezinfectantVirusi();

    dezinfectantVirusi &operator=(const dezinfectantVirusi &dezinfectantVirusi1);

    friend ostream &operator<<(ostream &os, dezinfectantVirusi &dezinfectante);
    friend  istream &operator>>(istream &is, dezinfectantVirusi &dezinfectante);

    double calculeazaEficienta();


};

dezinfectantVirusi::dezinfectantVirusi(const dezinfectantVirusi &dezinfectantVirusi1) : dezinfectant(dezinfectantVirusi1){}

dezinfectantVirusi::dezinfectantVirusi() : dezinfectant(){}

istream &operator>>(istream &is, dezinfectantVirusi &dezinfectante){
    cout<<"Numarul de specii pe care il poate ucide:\n";
    is >> dezinfectante.numarSpecii;
    is.get();
    int numar;
    cout<<"Numarul de ingrediente folosite este:\n";
    is >> numar;
    is.get();
    for(int i = 1; i<= numar; ++i){
        cout<<"Ingredientul numarul "<<i<<" este:\n";
        string ingr;
        getline(is, ingr);
        dezinfectante.ingrediente.push_back(ingr);
    }
    cout<<"Numarul de suprafete pe care poate fi folosit:\n";
    is >> numar;
    is.get();
    for(int i = 1; i <= numar; ++i){
        cout<<"Suprafata numarul "<<i<<" este:\n";
        string supr;
        getline(is, supr);
        dezinfectante.suprafete.push_back(supr);
    }
    dezinfectante.calculeazaEficienta();
    return is;
}

ostream &operator<<(ostream &os, dezinfectantVirusi &dezinfectante) {
    os<<"Numarul de specii pe care dezinfectantul il ucide este:\n"<<dezinfectante.numarSpecii<<'\n';
    os<<"Ingredientele folosite sunt:\n";
    for(int i = 0 ; i < dezinfectante.ingrediente.size(); i++){
        os<<"Ingredientul cu numarul "<<i + 1<<" este:\n";
        os<<" - "<<dezinfectante.ingrediente[i]<<'\n';
    }
    os<<"Suprafetele pe care poate fi utilizat:\n";
    for(int i = 0; i < dezinfectante.suprafete.size(); i++){
        os<<"Suprafata numarul "<<i + 1<<" este:\n";
        os<<" - "<<dezinfectante.suprafete[i]<<'\n';
    }
    os<<"Eficienta este: " << dezinfectante.eficienta<<'\n';
    return os;
}

double dezinfectantVirusi::calculeazaEficienta() {
    eficienta = (double)numarSpecii / (1.5 * 1000000.0);
    return eficienta;
}

dezinfectantVirusi &dezinfectantVirusi::operator=(const dezinfectantVirusi &dezinfectantVirusi1) {
    dezinfectant::operator=(dezinfectantVirusi1);
    return *this;
}

dezinfectantVirusi::dezinfectantVirusi(int numarSpecii, const vector<string> &ingrediente,
                                       const vector<string> &suprafete) : dezinfectant(numarSpecii, ingrediente,
                                                                                       suprafete) {
    eficienta = calculeazaEficienta();
}

class dezinfectantFungi : virtual public dezinfectant{
protected:

public:
    dezinfectantFungi();

    dezinfectantFungi(int numarSpecii, const vector<string> &ingrediente, const vector<string> &suprafete);

    double calculeazaEficienta();

    friend ostream &operator<<(ostream &os, dezinfectantFungi &dezinfectante);
    friend istream &operator>>(istream &is, dezinfectantFungi &dezinfectante);
};

dezinfectantFungi::dezinfectantFungi(): dezinfectant() {}

dezinfectantFungi::dezinfectantFungi(int numarSpecii, const vector<string> &ingrediente,
                                     const vector<string> &suprafete) : dezinfectant(numarSpecii, ingrediente,
                                                                                     suprafete) {
    eficienta = calculeazaEficienta();
}

double dezinfectantFungi::calculeazaEficienta() {
    eficienta = (double)numarSpecii / (100000000.0);
    return eficienta;
}

istream &operator>>(istream &is, dezinfectantFungi &dezinfectante) {
    cout<<"Numarul de specii pe care il poate ucide:\n";
    is >> dezinfectante.numarSpecii;
    is.get();
    int numar;
    cout<<"Numarul de ingrediente folosite este:\n";
    is >> numar;
    is.get();
    for(int i = 1; i<= numar; ++i){
        cout<<"Ingredientul numarul "<<i<<" este:\n";
        string ingr;
        getline(is, ingr);
        dezinfectante.ingrediente.push_back(ingr);
    }
    cout<<"Numarul de suprafete pe care poate fi folosit:\n";
    is >> numar;
    is.get();
    for(int i = 1; i <= numar; ++i){
        cout<<"Suprafata numarul "<<i<<" este:\n";
        string supr;
        getline(is, supr);
        dezinfectante.suprafete.push_back(supr);
    }
    dezinfectante.calculeazaEficienta();
    return is;
}

ostream &operator<<(ostream &os, dezinfectantFungi &dezinfectante) {
    os<<"Numarul de specii pe care dezinfectantul il ucide este:\n"<<dezinfectante.numarSpecii<<'\n';
    os<<"Ingredientele folosite sunt:\n";
    for(int i = 0 ; i < dezinfectante.ingrediente.size(); i++){
        os<<"Ingredientul cu numarul "<<i + 1<<" este:\n";
        os<<" - "<<dezinfectante.ingrediente[i]<<'\n';
    }
    os<<"Suprafetele pe care poate fi utilizat:\n";
    for(int i = 0; i < dezinfectante.suprafete.size(); i++){
        os<<"Suprafata numarul "<<i + 1<<" este:\n";
        os<<" - "<<dezinfectante.suprafete[i]<<'\n';
    }
    os<<"Eficienta este: " << dezinfectante.eficienta<<'\n';
    return os;
}


class Client{
private:
    string nume;
    static int id;
public:

    const string &getNume() const {
        return nume;
    }
    void setNume(const string &nume) {
        Client::nume = nume;
    }
    static int getId() {
        return id;
    }
    static void setId(int id) {
        Client::id = id;
    }
    Client();

    Client(const string &nume);

    //Client(const Client &client);
    Client &operator=(const Client &client);

    friend ostream &operator<<(ostream &os, Client &client);
    friend istream &operator>>(istream &is, Client &client);
};

int Client::id = 0;
Client::Client() {
    nume = "";
    ++id;
}

Client::Client(const string &nume) : nume(nume) {}

Client & Client::operator=(const Client &client) {
    nume = client.nume;
    id = client.id;
    return *this;
}

ostream &operator<<(ostream &os, Client &client) {
    os<<"Numele clientului: "<<client.nume<<'\n';
    os<<"Id-ul clientului: "<<client.id<<'\n';
    return os;
}
istream &operator>>(istream &is, Client &client) {
    cout<<"Numele clientului este:\n";
    getline(is, client.nume);
    return is;
}


//-------------------------------------------------------ACHIZITIE------------------------------------------------------
class Achizitie{
private:
    int an, luna, zi;
    vector<dezinfectant*>dezinfectanti;
    vector<masca*>masti;
    double pret;
    Client client;
public:

    Achizitie();

    Achizitie(int an, int luna, int zi, const Client &client);

    void addDezinfectant(dezinfectant *d){
        if(dezinfectantBacterii *dez = dynamic_cast<dezinfectantBacterii*>(d)){
            dezinfectanti.push_back(new dezinfectantBacterii(*dez));
        }
        else if(dezinfectantVirusi *dez = dynamic_cast<dezinfectantVirusi*>(d)){
            dezinfectanti.push_back(new dezinfectantVirusi(*dez));
        }
        else if(dezinfectantFungi *dez = dynamic_cast<dezinfectantFungi*>(d)){
            dezinfectanti.push_back(new dezinfectantFungi(*dez));
        }
    }
    void addMasca(masca *m){
        if(mascaChirurgicala *masc = dynamic_cast<mascaChirurgicala*>(m)){
            masti.push_back(new mascaChirurgicala(*masc));
        }
        else if(mascaPolicarbonat *masc = dynamic_cast<mascaPolicarbonat*>(m)){
            masti.push_back(new mascaPolicarbonat(*masc));
        }
    }

    Achizitie &operator+=(dezinfectant *dez){
        dezinfectanti.push_back(dez);
        return *this;
    }

    Achizitie &operator+=(masca *masc){
        masti.push_back(masc);
        return *this;
    }

    double getTotal();

    int getAn() const {
        return an;
    }
    void setAn(int an) {
        Achizitie::an = an;
    }
    int getLuna() const {
        return luna;
    }
    void setLuna(int luna) {
        Achizitie::luna = luna;
    }
    int getZi() const {
        return zi;
    }
    void setZi(int zi) {
        Achizitie::zi = zi;
    }
    const vector<dezinfectant *> &getDezinfectanti() const {
        return dezinfectanti;
    }
    void setDezinfectanti(const vector<dezinfectant *> &dezinfectanti) {
        Achizitie::dezinfectanti = dezinfectanti;
    }
    const vector<masca *> &getMasti() const {
        return masti;
    }
    void setMasti(const vector<masca *> &masti) {
        Achizitie::masti = masti;
    }
    double getPret() const {
        return pret;
    }
    void setPret(double pret) {
        Achizitie::pret = pret;
    }
    const Client &getClient() const {
        return client;
    }
    void setClient(const Client &client) {
        Achizitie::client = client;
    }

    friend ostream &operator<<(ostream &os, Achizitie &achizitie);
    friend istream &operator>>(istream &is, Achizitie &achizitie);

    bool operator<(Achizitie &a){
        if(getTotal()<a.getTotal()){
            return 1;
        }
        return 0;
    }
    bool operator==(Achizitie &a){
        if(getTotal()==a.getTotal())
            return 1;
        return 0;
    }

};

Achizitie::Achizitie() {
    an = 0;
    luna = 0;
    zi = 0;
    pret = 0;
    Client c;
    client = c;
}

Achizitie::Achizitie(int an, int luna, int zi, const Client &client) : an(an), luna(luna), zi(zi), client(client) {}





double Achizitie::getTotal() {
    double total;
    for(int i = 0; i < masti.size(); i++){
        if(mascaPolicarbonat *m = dynamic_cast<mascaPolicarbonat*>(masti[i]))
            total += 20;
        else if(mascaChirurgicala *m = dynamic_cast<mascaChirurgicala*>(masti[i])){
            if(m->getTipProtectie() == "ffp1"){
                total += 5;
            }
            else if(m->getTipProtectie() == "ffp2"){
                total += 10;
            }
            else if(m->getTipProtectie() == "ffp3"){
                total += 15;
            }
        }
    }
    for(int i = 0; i < dezinfectanti.size(); i++){
        if(dezinfectanti[i]->calculeazaEficienta() < 0.9){
            total += 10;
        }
        else if(dezinfectanti[i]->calculeazaEficienta()< 0.95){
            total += 20;
        }
        else if(dezinfectanti[i]->calculeazaEficienta() < 0.975){
            total += 30;
        }
        else if(dezinfectanti[i]->calculeazaEficienta() < 0.99){
            total += 40;
        }
        else if(dezinfectanti[i]->calculeazaEficienta() < 0.9999){
            total += 50;
        }
    }
    return total;
}

istream &operator>>(istream &is, Achizitie &achizitie){
    cout<<"Introduceti numarul de masti:\n";
    int numar;
    is >> numar;
    is.get();
    for(int i = 1; i<= numar; i++){
        string tip;
        masca *p = nullptr;
        while(true){
            try{
                cout<<"Introduceti tipul mstii - poli sau chir \n";
                getline(is, tip);
                if(tip == "poli"){
                    p = new mascaPolicarbonat;
                    break;
                }
                else if(tip == "chir"){
                    p = new mascaChirurgicala;
                    break;
                }
                else throw string("Tip invalid!");
            }
            catch (string s) {
                cout<<s<<'\n';
            }
        }
        is >> *p;
        achizitie.masti.push_back(p);
    }
    cout<<"Introduceti numarul de dezinfectante:\n";
    is >> numar;
    is.get();
    for(int i = 1; i <= numar ; i++){
        string tipd;
        dezinfectant *d = nullptr;
        while(true){
            try{
                cout<<"Introduceti tipul de dezinfectant - vir, fun, bac\n";
                getline(is, tipd);
                if(tipd == "vir"){
                    d = new dezinfectantVirusi;
                    break;
                }
                else if(tipd == "fun"){
                    d = new dezinfectantFungi;
                    break;
                }
                else if(tipd == "bac"){
                    d = new dezinfectantBacterii;
                    break;
                }
                else throw string("Tip invalid!");
            }
            catch (string s) {
                cout << s << '\n';
            }
        }
        is >> *d;
        achizitie.dezinfectanti.push_back(d);
    }
    cout<<"Introduceti client:\n";
    is>>achizitie.client;
    cout<<"Introduceti data:\n";
    cout<<"Anul:\n";
    is>>achizitie.an;
    cout<<"Luna:\n";
    is>>achizitie.luna;
    cout<<"Ziua:\n";
    is>>achizitie.zi;
    return is;
}

ostream &operator<<(ostream &os, Achizitie &achizitie) {
    os<<"Clientul: "<<achizitie.client<<'\n';
    os<<"Data:\n"<<"Anul: "<<achizitie.an<<"\nLuna: "<<achizitie.luna<<"\nZiua: "<<achizitie.zi<<'\n';
    os<<"Masti:\n";
    for(int i = 0 ; i < achizitie.masti.size(); i++){
        os << *achizitie.masti[i] << '\n';
    }
    os << "Dezinfectanti:\n";
    for(int i = 0; i < achizitie.dezinfectanti.size(); i++){
        os << *achizitie.dezinfectanti[i] << '\n';
    }
    return os;
}

class Manager{
protected:
    vector<Achizitie*> achizitii;
    vector<dezinfectant*> dezinfectanti;
    vector<masca*> masti;

    static Manager* instanta;

public:
    static Manager* getInstnta(){
        if(instanta == nullptr){
            instanta = new Manager();
        }
        return instanta;
    }
    void demo();
    void adaugaDezinfectant();
    void adaugaMasca();
    void celMaiEficientDezinfectant();
    void venitPeLuna(int luna);
    void venitMastiCuModel();
    void celMaiFidelClient();
    void ziuaCuCeleMaiSlabeVenituri();
    void TVA(int an);
};

void Manager::adaugaDezinfectant() {
    string tip;
    dezinfectant *d = nullptr;
    while(true){
        try{
            cout<<"Introduceti tipul de dezinfectant - vir, fun, bac\n";
            getline(cin, tip);
            if(tip == "vir"){
                d = new dezinfectantVirusi;
                break;
            }
            else if(tip == "fun"){
                d = new dezinfectantFungi;
                break;
            }
            else if(tip == "bac"){
                d = new dezinfectantBacterii;
                break;
            }
            else throw string("Tip invalid!");
        }
        catch (string s) {
            cout << s << '\n';
        }
    }
    cin >> *d;
    dezinfectanti.push_back(d);
}

void Manager::adaugaMasca() {
    string tip;
    masca *p = nullptr;
    while(true){
        try{
            cout<<"Introduceti tipul mstii - poli sau chir \n";
            getline(cin, tip);
            if(tip == "poli"){
                p = new mascaPolicarbonat;
                break;
            }
            else if(tip == "chir"){
                p = new mascaChirurgicala;
                break;
            }
            else throw string("Tip invalid!");
        }
        catch (string s) {
            cout<<s<<'\n';
        }
    }
    cin >> *p;
    masti.push_back(p);
}

void Manager::celMaiEficientDezinfectant() {
    int efMax = 0, pozmax = 0;
    for(int i = 0 ; i < dezinfectanti.size(); i++){
        if(dezinfectanti[i]->getEficienta() > efMax){
            efMax = dezinfectanti[i]->getEficienta();
            pozmax = i;
        }
    }
    cout << *dezinfectanti[pozmax]<<'\n';
}

void Manager::venitMastiCuModel() {
    double venit;
    for(int i = 0; i < achizitii.size(); i++){
        for(int j = 0; j < achizitii[i]->getMasti().size(); j++){
            if(mascaChirurgicala *m = dynamic_cast<mascaChirurgicala*>(achizitii[i]->getMasti()[j])){
                if(m->isModel()){
                    if(m->getTipProtectie() == "ffp1"){
                        venit += 7.5;
                    }
                    else if(m->getTipProtectie() == "ffp2"){
                        venit += 15;
                    }
                    else if(m->getTipProtectie() == "ffp3"){
                        venit += 22.5;
                    }
                }
            }
        }
    }
    cout << venit << '\n';
}

void Manager::venitPeLuna(int luna) {
    double venit;
    for(int i = 0; i < achizitii.size(); i++){
        if(achizitii[i]->getLuna() == luna){
            venit += achizitii[i]->getTotal();
        }
    }
    cout<<venit<<'\n';
}

void Manager::celMaiFidelClient() {
    int poz = 0, ma = 0;
    for(int i = 0; i < achizitii.size(); i++){
        int nr = 0;
        for(int j = i + 1; j < achizitii.size(); j++){
            if(achizitii[i]->getClient().getId() == achizitii[j]->getClient().getId()){
                nr++;
            }
        }
        if(nr > ma){
            ma = nr;
            poz = i;
        }
    }
    cout<<achizitii[poz]->getClient().getNume()<<'\n';
}

void Manager::ziuaCuCeleMaiSlabeVenituri() {
    double venMin = achizitii[0]->getTotal();
    int an = achizitii[0]->getAn(), luna = achizitii[0]->getLuna(), zi = achizitii[0]->getZi();
    for(int i = 1; i < achizitii.size(); i++){
        double venit = achizitii[i]->getTotal();
        if(venit < venMin){
            venMin = venit;
            an = achizitii[i]->getAn();
            luna = achizitii[i]->getLuna();
            zi = achizitii[i]->getZi();
        }
    }
    cout<<an<<"."<<luna<<"."<<zi<<'\n';
}

void Manager::TVA(int an) {
    double venit = 0;
    for(int i = 0; i < achizitii.size(); i++){
        if(achizitii[i]->getAn() == an){
            venit += achizitii[i]->getTotal();
        }
    }
    double tva = 0.19 * venit;
    cout<<tva<<'\n';
}


void Manager::demo() {
    mascaChirurgicala mc1, mc2("ffp2", "verde brotăcel", 55,0), mc3(mc1), mc4, mc5;
    mc4 = mc2;
    std::cin >> mc5;
    std::cout << mc1 << mc2;
    mascaPolicarbonat* mp1=new mascaPolicarbonat(), * mp2=new mascaPolicarbonat();
    mascaPolicarbonat* mp3 = new mascaPolicarbonat("ffp2","elastic");
    std::cin >> *mp1 >> *mp2;
    std::cout <<*mp3;
    dezinfectant* d1 = new dezinfectantBacterii(100000000, std::vector<string>({"sulfatinon-ionici", "sulfati cationici", "parfumuri", "Linalool", "Metilpropanol butilpentil"}),std::vector<string>({"lemn", "sticla", "metal", "ceramica", "marmura"}));
    dezinfectant* d2 = new dezinfectantVirusi(50000000, std::vector<string>({"AlkilDimetilm Benzil Crlorura de amoniu", "parfumuri", "Butilpentil metilpropinal"}), std::vector<string>({"lemn", "sticla", "ceramica", "marmura"}));
    dezinfectant* d3 = new dezinfectantFungi(1400000, std::vector<string>({"Alkil EtilBenzil Crlorura de amoniu", "parfumuri", "Butilpentil metilpropinal"}), std::vector<string>({"sticla", "plastic"}));
    cout << d1->calculeazaEficienta() << " " << d2->calculeazaEficienta() << " " << d3->calculeazaEficienta() << "\n";
    Client c;
    c.setNume("PlushBio SRL");
    Achizitie* a1 = new Achizitie(26, 5, 2020, Client("PlushBio SRL"));
    *a1 += mp1; //se adauga masca de policarbonat mp1 in lista de masti achizitionate
    *a1 += (&mc1); //se adauga masca chirugicala mc1 in lista
    *a1 += d3; // se adauga dezinfectantu de fungi d3 in lista de dezinfectanti achizitionati
    Achizitie* a2 = new Achizitie(25, 5, 2020, Client("Gucci"));
    *a2 += d1;
    *a2 += d2;
    *a2 += d2;
    Achizitie a3, a4(*a1);
    a3 = *a2;
    if(*a1 < *a2) {
        cout << a1->getClient().getNume()<< " are valoarea facturii mai mica.\n";
    }else if (*a1 == *a2) {
        cout << a1->getClient().getNume() << " si " << a2->getClient().getNume() << " au aceasi valoare afacturii.\n";}
    else {
        cout << a2->getClient().getNume() << " are valoarea facturii mai mica.\n";
    }
}

Manager* Manager::instanta = nullptr;

int main() {

    int optiune;
    Manager *m = m->getInstnta();
    while(1){
        cout << "0.Demo\n";
        cout << "1.Adauga dezinf\n";
        cout << "2.Adauga masca\n";
        cout << "3.Cel mai ef dezinf\n";
        cout << "4.Venit pe luna\n";
        cout << "5.Venit pe masti\n";
        cout << "6.Modif reteta\n";
        cout << "7.Cel mai fidel\n";
        cout << "8.Cea mai slaba zi\n";
        cout << "9.TVA\n";
        cout << "10.Adauga achizitie\n";
        cout << "11.inchide\n";
        try{
            cin >> optiune;
            cin.get();
            if(optiune < 0 || optiune > 11)
                throw string("Optiune gresita!");
            else{ if(optiune == 0) m->demo();
                if (optiune == 1) m->adaugaDezinfectant();
                else if (optiune == 2) m->adaugaMasca();
                else if (optiune == 3) m->celMaiEficientDezinfectant();
                else if (optiune == 4) {
                    int luna;
                    cin >> luna;
                    cin.get();
                    m->venitPeLuna(luna);
                }
                else if (optiune == 5) m->venitMastiCuModel();
                else if (optiune == 7) m->celMaiFidelClient();
                else if(optiune == 8) m->ziuaCuCeleMaiSlabeVenituri();
                else if(optiune == 9) {
                    int an;
                    cin >> an;
                    cin.get();
                    m->TVA(an);
                }
                else if(optiune == 11) break;

            }
        }
        catch (string s){
            cout << s << '\n';
        }


    }
    return 0;
}
