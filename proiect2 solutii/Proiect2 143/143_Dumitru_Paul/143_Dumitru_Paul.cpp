#include <iostream>
#include <string>
#include <vector>
using namespace std;

class IoBase{
public:

    virtual istream &read(istream &is) {
        return is;
    }

    virtual ostream &write(ostream &os) const {
        return os;
    }

    friend ostream &operator<<(ostream &os, const IoBase &base) {
        return base.write(os);
    }

    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }
};

class Malware: public IoBase{
protected:
    float rating;
    int zi,luna,an;
    string metoda;
    vector<string> registrii;
public:
    Malware(float rating,int zi,int luna,int an,string metoda,vector<string> registrii):rating(rating),zi(zi),luna(luna)
    ,an(an),metoda(metoda),registrii(registrii){}
    Malware():metoda("unknown"){}

    istream &read(istream &is) override{
        IoBase::read(is);
        cout<<"Rating: ";
        is>>rating;
        cout<<"Zi: ";
        is>>zi;
        cout<<"Luna: ";
        is>>luna;
        cout<<"An: ";
        is>>an;
        cout<<"Metoda: ";
        is>>metoda;
        string reg;
        int n;
        cout<<"Numar registrii: ";
        is>>n;
        registrii.clear();
        for(int i=0;i<n;i++){
            cout<<"Registru: ";is>>reg;
            registrii.push_back(reg);
        }
        return is;
    }

    ostream &write(ostream &os) const override{
        IoBase::write(os);
        cout<<"Rating: "<<rating<<'\n';
        cout<<"Zi: "<<zi<<'\n';
        cout<<"Luna: "<<luna<<'\n';
        cout<<"An: "<<an<<'\n';
        cout<<"Metoda: "<<metoda<<'\n';
        cout<<"Registrii: ";
        string reg;
        for(auto reg:registrii)
            cout<<reg<<'\n';
        return os;
    }

    string getmetoda(){
        return metoda;
    }
    float getrating(){
        return rating;
    }
    int getzi(){
        return zi;
    }
    int getluna(){
        return luna;
    }
    int getan(){
        return an;
    }
    vector<string> getregistrii(){
        return registrii;
    }
    void setmetoda(string Metoda){
        metoda=Metoda;
    }
    void setrating(float Rating){
        rating=Rating;
    }
    void setzi(int Zi){
        zi=Zi;
    }
    void setluna(int Luna){
        luna=Luna;
    }
    void setan(int An){
        an=An;
    }
    void setregistrii(vector<string> Registrii){
        registrii=Registrii;
    }
};

class RootKit: public virtual Malware{
protected:
    vector<string> importuri;
    vector<string> stringuri_semnif;
public:
    RootKit(float rating,int zi,int luna,int an,string metoda,vector<string> registrii,vector<string> importuri,
            vector<string> stringuri_semnif):Malware(rating,zi,luna,an,metoda,registrii),importuri(importuri),
            stringuri_semnif(stringuri_semnif){}
    RootKit(){}

    istream &read(istream &is) override {
        Malware::read(is);
        int nr_importuri,nr_strings;
        string import,string_semnif;
        cout<<"Numar importuri: ";
        is>>nr_importuri;
        importuri.clear();
        for(int i=0;i<nr_importuri;i++){
            cout<<"Import: ";
            is>>import;
            importuri.push_back(import);
        }
        cout<<"Numar stringuri semnificative: ";
        is>>nr_strings;
        stringuri_semnif.clear();
        for(int i=0;i<nr_strings;i++){
            cout<<"String semnificativ: ";
            is>>string_semnif;
            stringuri_semnif.push_back(string_semnif);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        cout<<"Importuri: ";
        string import,string_semnif;
        for(auto import:importuri){
            cout<<import<<'\n';
        }
        cout<<"Stringuri semnificative: ";
        for(auto string_semnif:stringuri_semnif){
            cout<<string_semnif<<'\n';
        }
        return os;
    }
    float rating_calc(){
        rating=0;
        string import;
        for(auto import:importuri){
            if(import=="System Service Descriptor Table" || import=="SSDT" || import=="NtCreateFile")
                rating+=100;
            else if(import=="ntoskrnl.exe")
                rating*=2;
        }
        return rating;
    }

    vector<string> getimporturi(){
        return importuri;
    }
    vector<string> getstringuri(){
        return stringuri_semnif;
    }
    void setimporturi(vector<string> Importuri){
        importuri=Importuri;
    }
    void setstringuri(vector<string> Stringuri){
        stringuri_semnif=Stringuri;
    }
};

class KeyLogger: public virtual Malware{
protected:
    vector<string> functii;
    vector<string> taste;
public:
    KeyLogger(float rating,int zi,int luna,int an,string metoda,vector<string> registrii,vector<string> functii,
            vector<string> taste):Malware(rating,zi,luna,an,metoda,registrii),functii(functii),
                                             taste(taste){}
    KeyLogger(){}

    istream &read(istream &is) override {
        Malware::read(is);
        int nr_functii,nr_taste;
        string functie,tasta;
        cout<<"Numar functii: ";
        is>>nr_functii;
        functii.clear();
        for(int i=0;i<nr_functii;i++){
            cout<<"Functie: ";
            is>>functie;
            functii.push_back(functie);
        }
        cout<<"Numar taste: ";
        is>>nr_taste;
        taste.clear();
        for(int i=0;i<nr_taste;i++){
            cout<<"Tasta: ";
            is>>tasta;
            taste.push_back(tasta);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        cout<<"Functii: ";
        string functie,tasta;
        for(auto functie:functii){
            cout<<functie<<'\n';
        }
        cout<<"Taste: ";
        for(auto tasta:taste){
            cout<<tasta<<'\n';
        }
        return os;
    }

    float rating_calc(){
        rating=0;
        string tasta;
        for(auto tasta:taste){
            if(tasta=="[Up]" || tasta=="[Num Lock]" || tasta=="[Down]" || tasta=="[Right]" || tasta=="[UP]" ||
            tasta=="[Left]" || tasta=="[PageDown]")
                rating+=10;
        }
        string functie;
        for(auto functie:functii){
            if(functie=="CreateFileW" || functie=="OpenProcess" || functie=="ReadFile" || functie=="WriteFile" ||
            functie=="RegisterHotKey" || functie=="SetWindowsHookEx")
                rating+=30;
        }
        return rating;
    }

    vector<string> getfunctii(){
        return functii;
    }
    vector<string> gettaste(){
        return taste;
    }
    void setfunctii(vector<string> Functii){
        functii=Functii;
    }
    void settaste(vector<string> Taste){
        taste=Taste;
    }
};

class Kernel_Keylogger: public RootKit,public KeyLogger{
private:
    bool ascunde_fisiere;
    bool ascunde_reg;
public:
    Kernel_Keylogger(float rating,int zi,int luna,int an,string metoda,vector<string> registrii,
                     vector<string> functii, vector<string> taste,vector<string> importuri,
                     vector<string>stringuri_semnif,bool af,bool ar):RootKit(rating,zi,luna,an,metoda,registrii,
                                                                             importuri,stringuri_semnif),KeyLogger(rating,
                                                                                                                   zi,luna,an,metoda,registrii,
                                                                                                                   functii,taste),ascunde_fisiere(af),
                                                                                                                   ascunde_reg(ar){}
    Kernel_Keylogger(){}

    istream &read(istream &is) override {
        RootKit::read(is);
        int nr_functii,nr_taste;
        string functie,tasta;
        cout<<"Numar functii: ";
        is>>nr_functii;
        functii.clear();
        for(int i=0;i<nr_functii;i++){
            cout<<"Functie: ";
            is>>functie;
            functii.push_back(functie);
        }
        cout<<"Numar taste: ";
        is>>nr_taste;
        taste.clear();
        for(int i=0;i<nr_taste;i++){
            cout<<"Tasta: ";
            is>>tasta;
            taste.push_back(tasta);
        }
        cout<<"Ascunde fisiere?";
        is>>ascunde_fisiere;
        cout<<"Ascunde registri?";
        is>>ascunde_reg;
        return is;
    }

    ostream &write(ostream &os) const override {
        RootKit::write(os);
        cout<<"Functii: ";
        string functie,tasta;
        for(auto functie:functii){
            cout<<functie<<'\n';
        }
        cout<<"Taste: ";
        for(auto tasta:taste){
            cout<<tasta<<'\n';
        }
        cout<<"Ascunde fisiere? "<<ascunde_fisiere<<'\n';
        cout<<"Ascunde registri? "<<ascunde_reg<<'\n';
        return os;
    }

    float rating_calculator(){
        rating=0;
        if(ascunde_fisiere)
            rating+=20;
        if(ascunde_reg)
            rating+=30;
        return rating;
    }

    bool getascundefis(){
        return ascunde_fisiere;
    }
    bool getascundereg(){
        return ascunde_reg;
    }
    void setascundefis(bool asc_fis){
        ascunde_fisiere=asc_fis;
    }
    void setascundereg(bool asc_reg){
        ascunde_reg=asc_reg;
    }

};


class Ransomware:public Malware{
private:
    int rating_criptare,rating_obfuscare;
public:
    Ransomware(float rating,int zi,int luna,int an,string metoda,vector<string> registrii,int rating_criptare,
               int rating_obfuscare):Malware(rating,zi,luna,an,metoda,registrii),rating_criptare(rating_criptare),
               rating_obfuscare(rating_obfuscare){}
    Ransomware(){}

    istream &read(istream &is) override {
        Malware::read(is);
        cout<<"Rating criptare: ";
        is>>rating_criptare;
        cout<<"Rating obfuscare: ";
        is>>rating_obfuscare;
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        cout<<"Rating criptare: "<<rating_criptare<<'\n';
        cout<<"Rating obfuscare: "<<rating_obfuscare<<'\n';
        return os;
    }

    int getratingcriptare(){
        return rating_criptare;
    }
    int getratingobf(){
        return rating_obfuscare;
    }
    void setratingcript(int RatingC){
        rating_criptare=RatingC;
    }
    void setratingobf(int RatingO){
        rating_obfuscare=RatingO;
    }
};

class Computer: public IoBase {
private:
    int id,nr;
    Malware malwares[100];
    int rating_final=0;
public:
    Computer(int _nr,int _id,int _rating_final,Malware _malwares[]){
        nr=_nr;
        id=_id;
        rating_final=_rating_final;
        for(int i=0;i<nr;i++)
            malwares[i]=_malwares[i];
    }
    Computer(){}

    istream &read(istream &is) override {
        IoBase::read(is);
        cout<<"Id: ";
        is>>id;
        cout<<"Numar de malwere: ";
        is>>nr;
        for(int i=0;i<nr;i++) {
            cout << "Malware: ";
            is >> malwares[i];
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout<<"Id: "<<id<<'\n';
        cout<<"Malwere: "<<'\n';
        for(int i=0;i<nr;i++)
            cout<<malwares[i]<<'\n';
        return os;
    }

    /*void rating_calc(int &rating_final){
        for(int i=0;i<nr;i++){
            if(malwares[i].getmetoda()=="rootkit")
                rating_final+=
        }
    }
    */

    int getid(){
        return id;
    }
    int getnr(){
        return nr;
    }
    int getratingfinal(){
        return rating_final;
    }
    void setid(int Id){
        id=Id;
    }
    void setnr(int Nr){
        nr=Nr;
    }
    void setratingfinal(int RatingF){
        rating_final=RatingF;
    }
};

int main() {
    int n;
    cout<<"Numar computere: ";
    cin>>n;
    Computer c[n];
    for(int i=0;i<n;i++)
        cin>>c[i];

    for(int i=0;i<n;i++)
        cout<<c[i];

}
