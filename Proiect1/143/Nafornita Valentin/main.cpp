//!! README:
//!
//!  1. Durata s-a construit cu struct -> se vor construi elemente de forma {ora,minut} pentru apeluri de functii
//!


#include <iostream>
#include <vector>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;
struct HM{
    int hours, minutes;
};

class Masina{
    bool ocupata;
    HM running;
    int capsule;

public:
    Masina(bool ocupata = 0, HM running = {0,0}, int capsule = 0){
        this->ocupata = ocupata;
        this->running = running;
        this->capsule = capsule;
    }

    inline  void update(HM running){
        int times60 = this->running.hours*60 + this->running.minutes;
        times60 -= (running.hours*60 + running.minutes);

        if (times60 <= 0){
            ocupata = 0;
            this->running.hours = this->running.minutes = 0;
            capsule--;
        }
        else{
            this->running.hours = times60 / 60;
            this->running.minutes =  times60 % 60;
        }
    }
    void modocupat(){
        ocupata=1;
    }
    void deccaps(){
        capsule--;
    }
    void modhm (HM a){
        running = a;
    }

    bool checkavailable();
    HM timeleft();
    int checkcapsule();
};

// ia valabilitate
inline bool Masina::checkavailable() {
    return ocupata;
}
// ia timp ramas
HM Masina::timeleft() {
    return running;
}
// ia capsule
int Masina::checkcapsule() {
    return capsule;
}

class Spalatorie{
    Masina flota[5];
    unsigned int n;

public:
    Spalatorie(unsigned int n, Masina flota[]){
        this->n = n;
        for (int i = 0; i < n; i++)
           this->flota[i] = flota[i];

    }

    void listeazaMasini(int);
    void actualizeazaTimp(HM);
    void adaugaJob(unsigned int, HM);
};
void Spalatorie::adaugaJob(unsigned int no , HM time) {
    if(flota[no].checkavailable() == 1 || flota[no].checkcapsule()<=0){
        cout<<no<<"->Ceva nu e in regula cu masina selectata: nu e valabila ori nu mai sunt capsule\n";
        return;
    }
    flota[no].modocupat();
    flota[no].deccaps();
    flota[no].modhm(time);
}

void Spalatorie::actualizeazaTimp(HM time) {
    for (int i = 0; i < n; i++){
        flota[i].update(time);
    }
}

void Spalatorie::listeazaMasini(int ok = 0) {
    for (int i = 0; i < n; i++){
        if (flota[i].checkcapsule() <= 0 && !ok) cout<<i<<" nu mai are capsule.\n";
        else{
            if (flota[i].checkavailable()&&!ok)cout<<i<<" e ocupata inca "<<flota[i].timeleft().hours<<":"<<flota[i].timeleft().minutes<<'\n';//da raspunsul la intrebare e ocupata?;

            else cout<<i<<" e libera.\n";
        }
    }
     cout<<"-----------------------------------*\n";
}

void listeazaMasiniLibere(Spalatorie   a){
    cout<<"Masinile care sunt libere:\n";a.listeazaMasini(1);
}



int main() {

// pe o masina ai functiile checkavailable, timeleft, checkcapsule, update
    Masina masini[5] = {
            Masina(0, {0,0}, 3),
            Masina(0, {0,0}, 2),
            Masina(0, {0,0}, 5),
    };

    Spalatorie spalatorie(3, masini);

     spalatorie.listeazaMasini();
    listeazaMasiniLibere(spalatorie);
    spalatorie.adaugaJob(1,{1,20});
    spalatorie.listeazaMasini();
    spalatorie.actualizeazaTimp({1,19});
    spalatorie.listeazaMasini();
    spalatorie.actualizeazaTimp({1,0});
    spalatorie.listeazaMasini();
    spalatorie.adaugaJob(1,{0,35});
    spalatorie.actualizeazaTimp({3,0});
    spalatorie.adaugaJob(1,{0,35});
    spalatorie.listeazaMasini();

    return 0;
}
