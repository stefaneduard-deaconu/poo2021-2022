#include <iostream>
using namespace std;

class Durata{
private:
    int minute;
    int secunde;

public:
    Durata(){
        minute=0;
        secunde=0;
    };
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

    void setMinute(int _minute) {
        Durata::minute = _minute;
    }

    void setSecunde(int _secunde) {
        Durata::secunde = _secunde;
    }

};


class MasinaSpalat{
private:
    bool ocupat;
    Durata durata_spalare;
    int nr_capsule;

public:
    MasinaSpalat(){
        nr_capsule=0;
        ocupat=true;
        durata_spalare.setMinute(0);
        durata_spalare.setSecunde(0);
    }
    MasinaSpalat(bool _ocupat, Durata _durata_spalare, int _nr_capsule){
        nr_capsule=_nr_capsule;
        ocupat=_ocupat;
        durata_spalare= _durata_spalare;
    }

    int getNrCapsule() const {
        return nr_capsule;
    }

    bool isOcupat() const {
        return ocupat;
    }

    const Durata &getDurataSpalare() const {
        return durata_spalare;
    }

    void setNrCapsule(int nrCapsule) {
        nr_capsule = nrCapsule;
    }

    void setOcupat(bool _ocupat) {
        MasinaSpalat::ocupat = _ocupat;
    }

    void setDurataSpalare(const Durata &durataSpalare) {
        durata_spalare = durataSpalare;
    }
};


class Spalatorie{
private:
    int nr_masini;
    MasinaSpalat masini[5];

public:
    Spalatorie(){
        nr_masini=0;
    };

    Spalatorie(int _nr_masini, MasinaSpalat _masini[]){
        nr_masini= _nr_masini;
        for(int i=0;i<_nr_masini;i++){
            masini[i]=_masini[i];
        }
    }

    int getNrMasini() const {
        return nr_masini;
    }

    const MasinaSpalat *getMasini() const {
        return masini;
    }

    void ListeazaMasini(){
        cout<<"Spalatoria in prezent:\n";
        for(int i=0;i<nr_masini;i++){
            cout<<i<<". ";

            int capsule=masini[i].getNrCapsule();
            if(capsule==0){
                cout<<"Masina este neutilizabila! Nu mai are capsule!\n";
            }else{
                Durata durata_curenta=masini[i].getDurataSpalare();
                int min=durata_curenta.getMinute();
                int sec=durata_curenta.getSecunde();

                if(min==0 && sec==0){
                    cout<<"Masina este libera\n";
                }else{
                    if(sec<10){
                        cout<<"Masina este ocupata pentru inca "<<min<<":"<<0<<sec<<"\n";
                    }else{
                        cout<<"Masina este ocupata pentru inca "<<min<<":"<<sec<<"\n";
                    }
                }
            }

        }
    }

    void adaugaJob(int index_masina, Durata durata_masina){
        int  nr_capsule=masini[index_masina].getNrCapsule();
        if(nr_capsule==0){
            cout<<"Masina "<<index_masina<<" nu mai are capsule!\n";
        }else{
            masini[index_masina].setDurataSpalare(durata_masina);
            nr_capsule--;
            masini[index_masina].setNrCapsule(nr_capsule);
            masini[index_masina].setOcupat(false);
        }
    }

    void actualizeazaTimp(Durata durata){
        for(int i=0;i<nr_masini;i++){
            Durata durata_veche= masini[i].getDurataSpalare();
            int min=durata_veche.getMinute();
            int sec=durata_veche.getSecunde();

            int timp_initial=min*60+sec;

            int min_new=durata.getMinute();
            int sec_new=durata.getSecunde();

            int timp_nou=min_new*60+sec_new;

            if(timp_initial-timp_nou>=0){
                timp_nou=timp_initial-timp_nou;
                min_new=timp_nou/60;
                sec_new=timp_nou-60*min_new;

                Durata durata_actualizata;
                durata_actualizata.setMinute(min_new);
                durata_actualizata.setSecunde(sec_new);

                masini[i].setDurataSpalare(durata_actualizata);
            }else{
                masini[i].setDurataSpalare(Durata(0,0));
            }
        }
    }
};

void listeazaMasiniLibere(Spalatorie spalatorie){
    int n=spalatorie.getNrMasini();
    MasinaSpalat masini[n];
    int free=0;
    for(int i=0;i<n;i++){
        masini[i]=spalatorie.getMasini()[i];
        if(free==0 && masini[i].isOcupat()){
            cout<<"Urmatoarele masini sunt ocupate: "<<i<<" ";
            free++;
        }else if (free!=0 && masini[i].isOcupat()){
            cout<<i<<" ";
            free++;
        }
    }
    if(free!=0){
        cout<<"\n";
    }else{
        cout<<"Nicio masina nu este libera\n";
    }
}


int main() {
    MasinaSpalat masini[5]= {MasinaSpalat(true, Durata(0, 0), 3),
                             MasinaSpalat(true, Durata(0, 0), 2),
                             MasinaSpalat(true, Durata(0, 0), 5),
    };
    Spalatorie spalatorie(3,masini);
    spalatorie.ListeazaMasini();
    listeazaMasiniLibere(spalatorie);
    spalatorie.adaugaJob(1, Durata(1,20));
    spalatorie.ListeazaMasini();

    spalatorie.actualizeazaTimp(Durata(1,19));
    spalatorie.ListeazaMasini();

    spalatorie.actualizeazaTimp(Durata(1,0));
    spalatorie.ListeazaMasini();

    spalatorie.adaugaJob(1,Durata(0,35));
    spalatorie.actualizeazaTimp(Durata(3,0));

    spalatorie.adaugaJob(1, Durata(0,35));
    spalatorie.ListeazaMasini();

    return 0;
}
