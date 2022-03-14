#include<iostream>
using namespace std;

class Durata {              //clasa pentru durata de timp in care masina de spalat este inca ocupata
    int minute;
    int secunde;
public:
    Durata() {          //default constructor
        minute = 0;
        secunde = 0;
    }
    Durata(int num, int num1) {     //parameter construcor
        minute = num;
        secunde = num1;
    }

    int getMinute() {
        return minute;
    }

    int getSecunde() {
        return secunde;
    }

    void setMinute(int num);
    void setSecunde(int num);
};

void Durata::setMinute(int num) {
    Durata::minute = num;
}

void Durata::setSecunde(int num) {
    Durata::secunde = num;
}

class Masina {                  //clasa pentru masina de spalat
    bool free;
    Durata durata_spalare;
    int nrCapsule;
public:
    Masina() {      //default constructor
        free = true;
        durata_spalare.setSecunde(0);
        durata_spalare.setMinute(0);
        nrCapsule = 0;
    }

    Masina(bool ok, Durata _durata, int num){       //parameter construcor
        free = ok;
        durata_spalare = _durata;
        nrCapsule = num;
    }

    bool getFree() {
        return free;
    }

    Durata getDurata() {
        return durata_spalare;
    }

    int getCapsule() {
        return nrCapsule;
    }

    void setFree(bool ok);
    void setDurata(Durata x);
    void setCapsule(int num);
};

void Masina::setFree(bool ok) {
    Masina::free =  ok;
}

void Masina::setDurata(Durata x) {        //setarea duratei unei masini de spalat
    Masina::durata_spalare = x;
}

void Masina::setCapsule(int num) {
    Masina::nrCapsule = num;
}

class Spalatorie {
    int nrMasini;
    Masina masini[];
public:
    void citireSpalatorie();

    Spalatorie() {      //default construcor
        nrMasini = 0;
        for (int i=0; i<nrMasini; i++) {
            masini[i].setFree(1);
            masini[i].setCapsule(0);
            masini[i].setDurata(Durata(0,0));
        }
    }

    Spalatorie(int num, Masina _masini[]) {     //parameter constructor
        nrMasini = num;
        for (int i=0; i<nrMasini; i++) {
            masini[i] = _masini[i];
        }
    }

    int getNrMasini() {
        return nrMasini;
    }

    Masina getMasini(int index) {
        return (masini[index]);
    }

    void setNrMasini(int num);
    void setMasini(Masina _masini[]);

    void listeazaMasini();
    void adaugaJob(int num, Durata _durata);
    void actualizareTimp(Durata _durata);
};

void Spalatorie::adaugaJob(int num, Durata _durata) {       //method for adding a job
    if (masini[num].getCapsule() == 0){
        cout<<"Masina "<<num<<" este neutilizabila!\n";
    }
    else{
        masini[num].setCapsule(masini[num].getCapsule()-1);
        masini[num].setDurata(_durata);
        masini[num].setFree(false);
    }
}

// TODO bonus daca in loc sa scrii cod atat de lung, implementezi o metoda in Durata denumita    bool maiMare(Durata durata2)
//  Plus imbunatatire: folosit Spalatori::masini doar daca existau doua variabile denumite asa.

void Spalatorie::actualizareTimp(Durata _durata) {      //method for checking status
    for (int i=0; i<Spalatorie::nrMasini; i++) {
        if (Spalatorie::masini[i].getDurata().getMinute() < _durata.getMinute()) {
            Spalatorie::masini[i].setDurata(Durata(0,0));
            Spalatorie::masini[i].setFree(true);
        }
        else {
            if (Spalatorie::masini[i].getDurata().getMinute() == _durata.getMinute() && Spalatorie::masini[i].getDurata().getSecunde() <= _durata.getSecunde()) {
                Spalatorie::masini[i].setDurata(Durata(0,0));
                Spalatorie::masini[i].setFree(true);
            }
            else {
                if (Spalatorie::masini[i].getDurata().getMinute() == _durata.getMinute() && Spalatorie::masini[i].getDurata().getSecunde() > _durata.getSecunde()) {
                    int b = Spalatorie::masini[i].getDurata().getSecunde() -_durata.getSecunde();
                    Spalatorie::masini[i].setDurata(Durata(0,b));
                }
            }
        }
        if (Spalatorie::masini[i].getDurata().getMinute() > _durata.getMinute()) {
            if (Spalatorie::masini[i].getDurata().getSecunde() < _durata.getSecunde()) {
                int a = Spalatorie::masini[i].getDurata().getMinute()-1-_durata.getMinute();
                int b = Spalatorie::masini[i].getDurata().getSecunde() + (60-_durata.getSecunde());
                Spalatorie::masini[i].setDurata(Durata(a,b));
            }
            else {
                int a = Spalatorie::masini[i].getDurata().getMinute() - _durata.getMinute();
                int b = Spalatorie::masini[i].getDurata().getSecunde() - _durata.getSecunde();
                Spalatorie::masini[i].setDurata(Durata(a,b));
            }
        }
    }
}

void listeazaMasiniLibere(Spalatorie _spalatorie) {
    cout<<"Masinile libere sunt: ";
    for (int i=0; i<_spalatorie.getNrMasini(); i++) {
//        cout<<_spalatorie.getMasini(i).getFree()<<" ";
        if (_spalatorie.getMasini(i).getFree()) {
            cout<<i<<" ";
        }
    }
    cout<<endl;
}

void Spalatorie::listeazaMasini() {     //method for listing
    cout<<"Spalatoria in prezent: \n";
    for (int i=0; i<Spalatorie::nrMasini; i++) {
        if (Spalatorie::masini[i].getCapsule() == 0) {
            cout<<i<<". "<<"Masina nu mai are capsule\n";
        }
        else {
            // pe scurt, ies cel mai bine in castig daca orice metoda bool/ atribut il folosesti in if  fara ==  sau !=
            if (Spalatorie::masini[i].getFree()) {
                cout<<i<<". "<<"Masina este libera\n";
            }
            else {
                cout<<i<<". "<<"Masina este ocupata pentru inca "<<Spalatorie::masini[i].getDurata().getMinute()<<":"<<Spalatorie::masini[i].getDurata().getSecunde()<<"\n";
            }
        }
    }
}

void Spalatorie::citireSpalatorie() {
    cin>>Spalatorie::nrMasini;
    bool ok;
    Durata _durata;
    int num;

    for (int i=0; i<Spalatorie::nrMasini; i++) {
        cout<<"Introduceti starea masinii de spalat: ";
        cin>>ok;
        cout<<"Introduceti durata masinii de spalat: ";
        int a,b;
        cin>>a>>b;
        _durata = Durata(a, b);
        cout<<"Introduceti numarul de capsule ale masinii de spalat: ";
        cin>>num;
        Spalatorie::masini[i] = Masina(ok, _durata, num);
    }
}

void Spalatorie::setNrMasini(int num) {
    Spalatorie::nrMasini = num;
}

void Spalatorie::setMasini(Masina _masini[]) {
    for (int i=0; i<Spalatorie::nrMasini; i++) {
        Spalatorie::masini[i] = _masini[i];
    }
}

int main() {

    Masina masini[5] = {
            Masina(true, Durata(0,0), 3),
            Masina(true, Durata(0,0), 2),
            Masina(true, Durata(0,0), 5)
    };

    Spalatorie spalatorie {
            3, masini
    };
//    cout << "1. *********" << '\n';
    spalatorie.listeazaMasini();
//    cout << "2. *********" << '\n';
    listeazaMasiniLibere(spalatorie);
//    cout << "************" << '\n';

    spalatorie.adaugaJob(1, Durata(1,20));
    spalatorie.listeazaMasini();
    spalatorie.actualizareTimp(Durata(1,19));
    spalatorie.listeazaMasini();
    spalatorie.actualizareTimp(Durata(1,0));
    // TODO Cum facem aici ca sa afiseze 0:01 ?
    spalatorie.listeazaMasini();
    spalatorie.adaugaJob(1, Durata(0,35));
    spalatorie.actualizareTimp(Durata(3,0));
    spalatorie.adaugaJob(1,Durata(0,35));
    spalatorie.listeazaMasini();

    return 0;
}