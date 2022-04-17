#include <iostream>
#include <vector>
using namespace std;

char mesaj_libera[] = "Masina este libera";
char mesaj_capsule[] = "Masina este neutilizabila! Nu mai are capsule!";
char mesaj_timp[] = "Masina este ocupata pentru inca: ";



// DURATA
class Durata{
private: int minute, secunde;
public:
    Durata() {}
    int conversiesec(int min,int sec){
        return 60*min+sec;
    }
    void setminute(int minute){
        this->minute = minute;
    }
    int getminute(){
        return minute;
    }
    void setsecunde(int secunde){
        this->secunde = secunde;
    }
    int getsecunde(){
        return secunde;
    }

    Durata(int minute, int secunde) : minute(minute), secunde(secunde) {}
};//durata
class Masina{
private:
    bool liber;
    int nr_capsule;
    Durata timp;

public:
    const Durata &getTimp() const {
        return timp;
    }
    int afisareminut (){
        return timp.getminute();
    }
    int afisaresecunda(){
        return timp.getsecunde();
    }
    void setTimp(const Durata &timp) {
        Masina::timp = timp;
    }

    void setactualsecunde(int secunde){
        Durata t;
        t.setsecunde(secunde);
    }
    void setactualminute(int minute){
        Durata t;
        t.setminute(minute);
    }
    int getactualsec(){
        Durata t;
        return t.getsecunde();
    }int getactualmin(){
        Durata t;
        return t.getminute();
    }

    Masina() {}

    bool getliber(){
        return liber;
    }
    void setliber(bool liber){
        this->liber = liber;
    }
    int getnr_capsule(){
        return nr_capsule;
    }
    void setnr_capsule(int nrc){
        nr_capsule = nrc;
    }


    Masina(bool liber, const Durata &timp, int nrCapsule) : liber(liber), timp(timp), nr_capsule(nrCapsule) {}

};//masini
class Spalatorie{
private:
    int nr_masini;
    Masina masini[5];
public:
    friend void listeazaMasiniLibere(Spalatorie s);
    void setNrMasini(int nrMasini) {
        nr_masini = nrMasini;
    }

    int getNrMasini() const {
        return nr_masini;
    }

    const Masina *getMasini() const {
        return masini;
    }

    Spalatorie(int nrMasini, Masina *masini) : nr_masini(nrMasini) {
        for(int i=0;i<nr_masini;i++)
            this->masini[i]=masini[i];
    }

    void listeazamasini() {
        cout<<"Spalatoria in prezent:"<<"\n";
        for (int m = 0; m < nr_masini; m++) {
            if (masini[m].getliber() == true)
                cout <<m<<"."<<mesaj_libera<<"\n"; // ,cout<<masini[m].getnr_capsule();
            else {
                if (masini[m].getnr_capsule() <= 0)
                    cout<<m<<"."<<mesaj_capsule<<"\n"; //,cout<<masini[m].getnr_capsule();
                else
                {if(masini[m].afisaresecunda()<10)
                        cout<<m<<"."<<mesaj_timp<<masini[m].afisareminut()<<":0"<<masini[m].afisaresecunda()<<"\n"; //,cout<<masini[m].getnr_capsule();
                    else cout<<m<<"."<<mesaj_timp<<masini[m].afisareminut()<<":"<<masini[m].afisaresecunda()<<"\n"; //,cout<<masini[m].getnr_capsule();
                }
            }
        }
    }

    void actualizeazatimp(Durata timp) {
        for(int i=0;i<nr_masini;i++){
            Durata aux = masini[i].getTimp();
            if (aux.conversiesec(aux.getminute(),aux.getsecunde()) <= timp.conversiesec(timp.getminute(),timp.getsecunde())){
                masini[i].setTimp(Durata(0,0));
                masini[i].setliber(true);
            }
            else{
                masini[i].setTimp(Durata((aux.getminute()-timp.getminute())%60,(aux.getsecunde()-timp.getsecunde())%60));
            }

        }
    }
    void adaugaJob(int nr_masinaspalat, Durata timp){
        if(masini[nr_masinaspalat].getnr_capsule()>=0){
            masini[nr_masinaspalat].setnr_capsule(masini[nr_masinaspalat].getnr_capsule()-1);
            masini[nr_masinaspalat].setTimp(timp);
            masini[nr_masinaspalat].setliber(false);
        }
        if (masini[nr_masinaspalat].getnr_capsule()<0){
            cout<<"Masina "<<nr_masinaspalat<<" nu mai are capsule!"<<"\n";
        }

    }
};//spalatorie
void listeazaMasiniLibere(Spalatorie s){
    int c = 0,v[s.getNrMasini()];
    cout<<"Urmatoarele masini sunt libere:";
    for (int i = 0; i < s.getNrMasini();i++)
    {if(s.masini[i].getliber() == true)
            //v[++c] = i;
            cout<<" "<<i;
    }
    cout<<"\n";

}
int main()
{ int minute, secunde, nr_capsule,nr_masini;bool liber;
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
    spalatorie.listeazamasini();
    listeazaMasiniLibere(spalatorie);

    spalatorie.adaugaJob(
            1,
            Durata(1, 20)
    );
    spalatorie.listeazamasini();

    spalatorie.actualizeazatimp(Durata(1, 19));
    spalatorie.listeazamasini();

    spalatorie.actualizeazatimp(Durata(1, 0));
    spalatorie.listeazamasini(); // metoda

// adaugam inca o spalare la masina 1, ca sa ramana fara capsule
    spalatorie.adaugaJob(
            1,
            Durata(0, 35)
    );
    spalatorie.actualizeazatimp(Durata(3, 0));

// Incercam sa adaugam inca o spalare. Ar trebui sa afiseze mesajul "Masina 1 nu mai are capsule!"
    spalatorie.adaugaJob(
            1,
            Durata(0, 35)
    );
// Ceea ce se poate observa si din listarea masinilor:
    spalatorie.listeazamasini();

    return 0;
}