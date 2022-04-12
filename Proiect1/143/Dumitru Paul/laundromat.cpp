#include <iostream>
using namespace std;
class Durata{
private:
    int minute,secunde;
public:
    Durata(){
        minute=0;
        secunde=0;
    }
    Durata(int Minute,int Secunde){
        minute=Minute;
        secunde=Secunde;
    }
    int getsecunde(){
        return secunde;
    }
    int getminute(){
        return minute;
    }
    void setsecunde(int Secunde){
        Durata::secunde=Secunde;
    }
    void setminute(int Minute){
        Durata::minute=Minute;
    }
};
class Masina{
private:
    bool libera;
    Durata d;
    int capsule;
public:
    Masina(){
        libera=false;
        d.setsecunde(0);
        d.setminute(0);
        capsule=0;
    }
    Masina(bool Libera,Durata D,int Capsule){
        libera=Libera;
        d=D;
        capsule=Capsule;
    }
    bool getLibera(){
        return libera;
    }
    int getCapsule(){
        return capsule;
    }
    Durata getDurata(){
        return d;
    }
    void setLibera(bool Libera){
        libera=Libera;
    }
    void setDurata(Durata D){
        d=D;
    }
    void setCapsule(int Capsule){
        capsule=Capsule;
    }
};

class Spalatorie{
private:
    int n;
    Masina masini[100];
public:
    void listeazaMasini(){
        cout<<"Spalatoria in prezent:"<<'\n';
        for(int i=0;i<n;i++){
            cout<<i<<". ";
            if(masini[i].getCapsule()==0)
                cout<<"Masina este neutilizabila! Nu mai are capsule!"<<'\n';
            else if(masini[i].getLibera()==true)
                cout<<"Masina este libera"<<'\n';
            else
            {
                Durata d=masini[i].getDurata();
                cout<<"Masina este ocupata pentru inca "<<d.getminute()<<":"<<d.getsecunde()<<'\n';
            }

        }
    }
    Spalatorie(){
        n=0;
    }
    Spalatorie(int N,Masina Masini[]){
        n=N;
        for(int i=0;i<n;i++)
            masini[i]=Masini[i];
    }
    int getn() const{
        return n;
    }
    Masina *getmasini(){
        return masini;
    }
    void setn(int N){
        n=N;
    }
    void setmasini(Masina Masini[]){
        for(int i=0;i<n;i++)
            masini[i]=Masini[i];
    }
    void adaugaJob(int I,Durata D){
        int caps=masini[I].getCapsule();
        if(caps==0)
            cout<<"Masina "<<I<<" nu mai are capsule!"<<'\n';
        else{
            masini[I].setLibera(false);
            masini[I].setCapsule(caps-1);
            masini[I].setDurata(D);
        }

    }
    void actualizeazaTimp(Durata D){
        int secunde_D=D.getsecunde();
        int minute_D=D.getminute();
        int total_D=minute_D*60+secunde_D;
        for(int i=0;i<n;i++){
            Durata d=masini[i].getDurata();
            int secunde_d=d.getsecunde();
            int minute_d=d.getminute();
            int total_d=minute_d*60+secunde_d;
            if(total_D>total_d){
                masini[i].setLibera(true);
                Durata De;
                De.setsecunde(0);
                De.setminute(0);
                masini[i].setDurata(De);
            }
            else{
                total_d-=total_D;
                Durata De;
                De.setminute(total_d/60);
                De.setsecunde(total_d%60);
                masini[i].setDurata(De);
            }

        }
    }
};
void listeazaMasiniLibere(Spalatorie spalatorie){
    int n=spalatorie.getn();
    Masina masini[n];
    cout<<"Urmatoarele masini sunt libere: ";
    for(int i=0;i<n;i++){
        masini[i]=spalatorie.getmasini()[i];
        if(masini[i].getLibera()==true)
            cout<<i<<" ";
    }
    cout<<'\n';

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
