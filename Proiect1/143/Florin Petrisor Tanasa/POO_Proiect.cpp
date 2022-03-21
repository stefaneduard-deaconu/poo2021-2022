#include <iostream>
#include <vector>
using namespace std;

class Durata{
    int minute, secunde;
public:
    Durata(){
        minute=0;
        secunde=0;
    }
    Durata(int minute_,int secunde_){
        minute = minute_;
        secunde = secunde_;
    }
    int getMinute(){
        return minute;
    }
    int getSecunde(){
        return secunde;
    }
    void setMinute(int minute_){
        minute = minute_;
    }
    void setSecunde(int secunde_){
        secunde = secunde_;
    }

    friend ostream &operator<<(ostream &os, const Durata &durata) {
        os << durata.minute << ":";
        if(durata.secunde<10){
            cout<<"0"<<durata.secunde;
        }
        else{
            cout<<durata.secunde;
        }
        return os;
    }
};

class Masina{
    bool Stare;
    Durata TimpRamas;
    int Pastile;
public:
    Masina(){
        Stare = false;
        TimpRamas.setMinute(0);
        TimpRamas.setSecunde(0);
        Pastile = 0;
    }
    Masina(bool stare,Durata timpramas,int pastile){
        Stare = stare;
        TimpRamas.setMinute(timpramas.getMinute());
        TimpRamas.setSecunde(timpramas.getSecunde());
        Pastile = pastile;
    }
    bool getStare(){
        return Stare;
    }
    void setStare(bool stare){
        Stare = stare;
    }
    Durata getTimpRamas(){
        return TimpRamas;
    }
    void setTimpRamas(Durata timpramas){
        TimpRamas.setMinute(timpramas.getMinute());
        TimpRamas.setSecunde(timpramas.getSecunde());
    }
    int getPastile(){
        return Pastile;
    }
    void setPastile(int pastile){
        Pastile = pastile;
    }
};

class Spalatorie{
    int NumarMasini;
    vector<Masina> Masini{5};
public:
    Spalatorie(){
        int i;
        Durata timp;
        timp.setSecunde(0);
        timp.setMinute(0);
        NumarMasini = 0;
        for(i=0;i<5;i++){
            Masini[i].setTimpRamas(timp);
            Masini[i].setPastile(0);
            Masini[i].setStare(true);
        }
    }

    Spalatorie(int a,Masina masinute[]){
        int i;
        NumarMasini = a;
        for(i=0;i<a;i++){
            Masini[i].setStare(masinute[i].getStare());
            Masini[i].setPastile(masinute[i].getPastile());
            Masini[i].setTimpRamas(masinute[i].getTimpRamas());
        }
    }

    int getNumarMasini(){
        return NumarMasini;
    }
    void setNumarmasini(int numar_masini){
        NumarMasini = numar_masini;
    }
    void listeazaMasini(){
        int i;
        cout<<"Spalatoria in prezent:"<<endl;
        for(i=0;i<getNumarMasini();i++){
            cout<<i<<".Masina de spalat este ";
            if(Masini[i].getStare()==true){
                cout<<"libera";
            }
            else{
                if(Masini[i].getPastile()==0){
                    cout<<"neutilizabila! Nu mai are capsule!";
                }
                else{
                    cout<<"ocupata pentru inca ";
                    cout<< Masini[i].getTimpRamas();
                }
            }
            cout<<'\n';
        }
    }
    void adaugaJob(int indice,Durata timp){
        int PastileCurente;
        if(Masini[indice].getPastile()>0) {
            Masini[indice].setTimpRamas(timp);
            PastileCurente =  Masini[indice].getPastile();
            Masini[indice].setPastile(PastileCurente-1);
            Masini[indice].setStare(false);
        }
        else{
            cout<<"Masina "<<indice<<" nu mai are capsule!"<<endl;
        }
    }
    vector<Masina> getMasini(){
        return Masini;
    }
    void actualizeazaTimp(Durata timp){
        int i;
        vector<Masina> uuu(5);
        Durata TimpRamas;
        int TimpRamasMinute,TimpRamasSecunde;
        uuu = getMasini();
        for(i=0;i<getNumarMasini();i++){
            TimpRamas = uuu[i].getTimpRamas();
            TimpRamasMinute= TimpRamas.getMinute();
            TimpRamasSecunde= TimpRamas.getSecunde();
            if(TimpRamasMinute<timp.getMinute()){
                TimpRamasMinute = 0;
                TimpRamasSecunde = 0;
                if(uuu[i].getPastile()>0) {
                    uuu[i].setStare(true);
                }
            }
            else if(TimpRamasMinute==timp.getMinute()){
                TimpRamasMinute=0;
                if(TimpRamasSecunde<=timp.getSecunde()){
                    TimpRamasSecunde=0;
                    if(uuu[i].getPastile()>0) {
                        uuu[i].setStare(true);
                    }
                }
                else {
                    TimpRamasSecunde = TimpRamasSecunde - timp.getSecunde();
                }
            }
            else{
                TimpRamasMinute = TimpRamasMinute - timp.getMinute();
                if(TimpRamasSecunde <= timp.getSecunde()){
                    TimpRamasSecunde = TimpRamasSecunde - timp.getSecunde();
                }
                else{
                    TimpRamasMinute--;
                    TimpRamasSecunde = 60 + TimpRamasSecunde - timp.getSecunde();
                }
            }
            uuu[i].setTimpRamas(Durata(TimpRamasMinute,TimpRamasSecunde));
        }
        Masini = uuu;
    }
};

void listeazaMasiniLibere(Spalatorie spala){
    int i,a=0;
    int vectorMasiniLibere[5];
    vector<Masina> uuu(5);

    uuu = spala.getMasini();

    for(i=0;i<spala.getNumarMasini();i++){
        if(uuu[i].getStare()==true){
            vectorMasiniLibere[a] = i;
            a++;
        }
    }
    cout<<"Urmatoarele masini sunt libere: ";
    for(i=0;i<a;i++){
        cout<<vectorMasiniLibere[i]<<" ";
    }
    cout<<endl;
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
//
spalatorie.adaugaJob(
            1,
            Durata(1, 20)
);
spalatorie.listeazaMasini();
//
spalatorie.actualizeazaTimp(Durata(1, 19));
spalatorie.listeazaMasini();

    spalatorie.actualizeazaTimp(Durata(1, 0));
    spalatorie.listeazaMasini(); // metoda

//// adaugam inca o spalare la masina 1, ca sa ramana fara capsule
    spalatorie.adaugaJob(
            1,
            Durata(0, 35)
    );
    spalatorie.actualizeazaTimp(Durata(3, 0));

//// Incercam sa adaugam inca o spalare. Ar trebui sa afiseze mesajul "Masina 1 nu mai are capsule!"
    spalatorie.adaugaJob(
            1,
            Durata(0, 35)
    );
//// Ceea ce se poate observa si din listarea masinilor:
spalatorie.listeazaMasini();
}