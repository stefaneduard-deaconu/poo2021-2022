 #include <iostream>

using namespace std;

class Durata{
private:
    int minute;
    int secunde;
public:
    Durata() {
        minute=secunde=0;
    }
    Durata(int _minute, int _secunde){
        minute=_minute;
        secunde=_secunde;
    }

    int getMinute() const {
        return minute;
    }

    int getSecunde() const {
        return secunde;
    }

    void setMinute(int minute) {
        Durata::minute = minute;
    }

    void setSecunde(int secunde) {
        Durata::secunde = secunde;
    }

    void citire_durata(){
        cout<<"minute si secunde: ";
        cin>>minute>>secunde;
    }

    bool operator<(Durata op2) const;
    Durata operator=(Durata op2);
    friend Durata operator-(Durata op1, Durata op2);
};

Durata operator-(Durata op1, Durata op2) {
    Durata rez;
    if (op1.secunde>=op2.secunde){
        rez.minute=op1.minute-op2.minute;
        rez.secunde=op1.secunde-op2.secunde;
    }
    else{
        rez.minute=op1.minute-op2.minute-1;
        rez.secunde=60-(op2.secunde-op1.secunde);
    }
    return rez;

}

bool Durata::operator<(Durata op2) const {
    if(minute<op2.minute)
        return true;
    else if(minute==op2.minute && secunde<op2.secunde)
        return true;
    else return false;
}

Durata Durata::operator=(Durata op2) {
    minute=op2.minute;
    secunde=op2.secunde;
    return *this;
}


class MasinaSpalat{
private:
    bool libera;
    Durata spalare_curenta;
    int capsule;
public:
    MasinaSpalat() {
        libera= false;
        spalare_curenta.setMinute(0);  //se poate mai simplu?
        spalare_curenta.setSecunde(0);
        capsule=0;
    }

    MasinaSpalat(bool _libera, const Durata &spalareCurenta, int _capsule){
        libera=_libera;
        capsule=_capsule;
        this->spalare_curenta=spalareCurenta;
    }

    bool getLibera() const {
        return libera;
    }

    void setLibera(bool libera) {
        MasinaSpalat::libera = libera;
    }

    const Durata &getSpalareCurenta() const {
        return spalare_curenta;
    }

    void setSpalareCurenta(const Durata &spalareCurenta) {
        spalare_curenta = spalareCurenta;
    }

    int getCapsule() const {
        return capsule;
    }

    void setCapsule(int capsule) {
        MasinaSpalat::capsule = capsule;
    }

    void citire_MasinaSpalat(){
        cout<<endl;
        cout<<"este libera?: ";
        cin>>libera;
        cout<<"durata spalare: ";
        spalare_curenta.citire_durata();
        cout<<"nr capsule: ";
        cin>>capsule;
    }

};


class Spalatorie{
private:
    int nr_masini_spalat;
    MasinaSpalat masina[5];
public:
    Spalatorie() {
        nr_masini_spalat=0;
        MasinaSpalat masina[5];
    }

    Spalatorie(int _nr_masini_spalat ,MasinaSpalat *masina){
        nr_masini_spalat=_nr_masini_spalat;
        for (int i = 0; i < nr_masini_spalat; ++i) {
            this->masina[i]=masina[i];
        }
    }

    int getNrMasiniSpalat() const {
        return nr_masini_spalat;
    }

    void setNrMasiniSpalat(int nrMasiniSpalat) {
        nr_masini_spalat = nrMasiniSpalat;
    }

    const MasinaSpalat &getMasina(int i) const {
        return masina[i];
    }

    void citire_spalatorie(){
        cout<<"nr masini in spalatorie: ";
        cin>>nr_masini_spalat;
        cout<<"citire masini spalat ";
        for(int i=0;i<nr_masini_spalat;i++)
            masina[i].citire_MasinaSpalat();
    }

    void listeazaMasini();
    void adaugaJob(int i, Durata timp);
    void actualizeazaTimp(Durata timp);
};

void Spalatorie::actualizeazaTimp(Durata timp) {
    Durata x;
    for (int i = 0; i < nr_masini_spalat; ++i) {
        if(!masina[i].getLibera()) {
            if (masina[i].getSpalareCurenta() < timp) {
                masina[i].setLibera(true);
                masina[i].setSpalareCurenta(Durata(0,0));
            }
            else {
                x = masina[i].getSpalareCurenta() - timp;
                masina[i].setSpalareCurenta(x);
            }
        }

    }
}

void Spalatorie::adaugaJob(int i, Durata timp) {
//    int nr;
    if(masina[i].getCapsule()==0)
        cout<<"Masina "<<i<<" nu mai are capsule!"<<endl;
    else {
        masina[i].setLibera(false);
        masina[i].setCapsule(masina[i].getCapsule() - 1);
        masina[i].setSpalareCurenta(timp);
    }
}

void Spalatorie::listeazaMasini() {
    cout<<"Spalatoria in prezent:"<<endl;
    for (int i = 0; i < nr_masini_spalat; ++i) {
        cout<<i<<". ";
        if(masina[i].getCapsule()==0)
            cout<<"Masina este neutilizabila! Nu mai are capsule!"<<endl;
        else if(masina[i].getSpalareCurenta().getMinute()!=0 || masina[i].getSpalareCurenta().getSecunde()!=0) {
            cout << "Masina este ocupata pentru inca " << masina[i].getSpalareCurenta().getMinute() << ":";
            if (masina[i].getSpalareCurenta().getSecunde()<=9)
                cout<<"0";
            cout << masina[i].getSpalareCurenta().getSecunde() << endl;
        }
        else if (masina[i].getLibera())
            cout<<"Masina este libera"<<endl;
    }

}

void listeazaMasiniLibere(Spalatorie &_spalatorie){
    cout<<"Urmatoarele masini sunt libere: ";
    for (int i = 0; i < _spalatorie.getNrMasiniSpalat(); ++i) {
        if(_spalatorie.getMasina(i).getLibera())
            cout<<i<<" ";
    }
    cout<<endl;

}

int main() {
//declararea spalatoriei
    MasinaSpalat masini[5] = {
            MasinaSpalat(true, Durata(0, 0), 3),
            MasinaSpalat(true, Durata(0, 0), 2),
            MasinaSpalat(true, Durata(0, 0), 5),
    };
    Spalatorie spalatorie(
            3,
            masini
    );
// listare initiala
    spalatorie.listeazaMasini();
    listeazaMasiniLibere(spalatorie);
    spalatorie.adaugaJob(
            1,
            Durata(1, 20)
    );
    spalatorie.listeazaMasini();
    spalatorie.actualizeazaTimp(Durata(1, 19));
    spalatorie.listeazaMasini();
    spalatorie.actualizeazaTimp(Durata(1, 0));
    spalatorie.listeazaMasini(); // metoda
// adaugam inca o spalare la masina 1, ca sa ramana fara capsule
    spalatorie.adaugaJob(
            1,
            Durata(0, 35)
    );
    spalatorie.actualizeazaTimp(Durata(3, 0));
// Incercam sa adaugam inca o spalare. Ar trebui sa afiseze mesajul "Masina 1 nu mai are capsule!"
    spalatorie.adaugaJob(
            1,
            Durata(0, 35)
    );
// Ceea ce se poate observa si din listarea masinilor:
    spalatorie.listeazaMasini();

    return 0;
}


















