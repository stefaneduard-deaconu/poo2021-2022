#include <bits/stdc++.h>

using namespace std;

class Durata{
    int minute, secunde;
public:
    Durata(){
        minute = 0;
        secunde = 0;
        //Constructor gol
    }
    Durata(int _minute, int _secunde){
        minute = _minute;
        secunde = _secunde;
    }
    void setmin(int x){
        minute = x;
    }
    int getmin(){
        return minute;
    }
    void setsec(int x){
        secunde = x;
    }
    int getsec(){
        return secunde;
    }
};

class Masina{
    bool liber;
    Durata D;
    int capsule;
public:
    Masina(){
        liber = false;
        D.setsec(0);
        D.setmin(0);
        capsule = 0;
    }
    Masina(bool _liber,Durata _D, int _capsule){
        liber = _liber;
        D.setmin(_D.getmin());
        D.setsec(_D.getsec());
        capsule = _capsule;
    }
    void setcapsule(int x){
        capsule = x;
    }
    int getcapsule(){
        return capsule;
    }
    void setliber(bool x){
        liber = x;
    }
    int getliber(){
        return liber;
    }

    void setmin(int x){
        D.setmin(x);
    }
    int getmin(){
        return D.getmin();
    }
    void setsec(int x){
        D.setsec(x);
    }
    int getsec(){
        return D.getsec();
    }

    void afis(){
        cout <<liber <<" "<<D.getmin()<<" "<<D.getsec()<<" "<<capsule <<'\n' ;
    }
};

class Spalatorie{
    int n;
    Masina masini[50];
public:
    Spalatorie(){
        n = 0;
    //poate ceva in care vectorul masini sa fie gol, dar nu cred ca n este deja setat la 0
    }
    Spalatorie(int _n, Masina _masini[]){
        n = _n;
        for(int i = 0; i < n; ++i)
           masini[i] = _masini[i];
    }
    void listeazaMasini(){
        cout << "Spalatoria in prezent:\n";
        for(int i = 0; i < n; ++i){
            cout <<i<<". ";
            if (masini[i].getliber() == true and masini[i].getcapsule() != 0){
                cout << "Masina este libera\n";
            }
            else if (masini[i].getcapsule() == 0){
                cout << "Masina este neutilizabila! Nu mai are capsule!\n";
            }
            else{
                cout << "Masina este ocupata pentru inca ";
                cout << masini[i].getmin() << ":" << masini[i].getsec() <<'\n';
            }
        }
    }
    void afis(){
        cout << n <<'\n';
        for(int i = 0; i < n ; ++i)
            masini[i].afis();
    }
    int getn(){
        return n;
    };
    void setn(int x){
        n = x;
    }
    bool getliber(int i){
        if (masini[i].getliber() == true and masini[i].getcapsule() != 0)
            return true;
        return false;
    }
    void adaugaJob(int indice, Durata D){

        if(masini[indice].getcapsule() == 0){
            cout << "Masina ";
            cout << indice;
            cout <<" nu mai are capsule!\n";
        }
        else{
            masini[indice].setliber(false);
            masini[indice].setmin(D.getmin());
            masini[indice].setsec(D.getsec());
            masini[indice].setcapsule( masini[indice].getcapsule() - 1);
        }
    }
    void actualizeazaTimp(Durata D){
        for(int i = 0; i < n; ++i){
            if(masini[i].getmin() < D.getmin()){///daca masina se termina din cauza minutelor
                masini[i].setmin(0);
                masini[i].setsec(0);
                masini[i].setliber(true);
            }
            else if(masini[i].getmin() == D.getmin() and masini[i].getsec() <= D.getsec()){
                ///daca masina se termina din cazua secundelor
                masini[i].setmin(0);
                masini[i].setsec(0);
                masini[i].setliber(true);
            }
            else {
                masini[i].setmin(masini[i].getmin() - D.getmin());
                masini[i].setsec(masini[i].getsec() - D.getsec());
            }
        }
    }
};

void listeazaMasiniLibere(Spalatorie spalatorie){
    int N = spalatorie.getn();
    cout <<"Urmatoarele masini sunt libere: ";
    for(int i = 0; i < N; ++i)
        if(spalatorie.getliber(i) == true)
            cout << i <<" ";
    cout <<'\n';
}

int main() {
    Masina masini[5] = {
            Masina(true, Durata(0, 0), 3),
            Masina(true, Durata(0, 0), 2),
            Masina(true, Durata(0, 0), 5),
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
