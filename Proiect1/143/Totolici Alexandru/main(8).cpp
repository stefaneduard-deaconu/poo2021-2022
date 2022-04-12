#include <iostream>
#include <vector>
using namespace std;
class Durata{
private:
    int minute;
    int secunde;
public:
    Durata(){
        minute = 0;
        secunde = 0;
    }
    Durata(int _minute, int _secunde){
        minute = _minute;
        secunde = _secunde;
    }
    int getMinute(){
        return minute;
    }
    int getSecunde(){
        return secunde;
    }
    void setMinute(int _minute){
        minute = _minute;
    }
    void setSecunde(int _secunde){
        secunde = _secunde;
    }
    void afiseazaDurata(){
        if(secunde<10)
            cout<<minute<<":0"<<secunde;
        else
            cout<<minute<<":"<<secunde;
    }


};

class Masina{
private:
    bool disponibilitate;
    Durata durata;
    int nrCapsule;
public:
    Masina(){
        disponibilitate = false;
        durata = Durata(0,0);
        nrCapsule = 0;
    }

    Masina(bool _disponibilitate, Durata _durata, int _nrCapsule){
        disponibilitate = _disponibilitate;
        durata = _durata;
        nrCapsule = _nrCapsule;
    }
    int getNrCapsule(){
        return nrCapsule;
    }

    bool getDisponibilitate(){
        return disponibilitate;
    }

    Durata getDurata(){
        return durata;
    }
    void setDurata(Durata _durata){
        durata = _durata;
    }
    void setDisponibilitate(bool _disponibilitate){
        disponibilitate = _disponibilitate;
    }
    void setNrCapsule(int _nrCapsule){
        nrCapsule = _nrCapsule;
    }
};

class Spalatorie{
private:
    int nrMasini;
    vector <Masina> masini;
public:
    Spalatorie(){
        nrMasini = 0;
    }
    Spalatorie(int _nrMasini, vector <Masina> _masini){
        nrMasini = _nrMasini;
        for(int i=0 ; i < nrMasini ; i++)
            masini.push_back(_masini[i]);

    }
    void setNrMasini(int _nrMasini){
        nrMasini = _nrMasini;
    }
    int getNrMasini(){
        return nrMasini;
    }
    void adaugaJob(int i, Durata timp){
        if(masini[i].getNrCapsule() == 0)
            cout << "Masina " << i << " nu mai are capsule! " << endl;
        else {
            masini[i].setDisponibilitate(false);
            masini[i].setNrCapsule(masini[i].getNrCapsule()-1);
            masini[i].setDurata(timp);}
    }
    vector <Masina> getMasini(){
        return masini;
    }

    void actualizeazaTimp(Durata t){
        int minute = t.getMinute();
        int secunde = t.getSecunde();
        for(int i=0 ; i < getNrMasini() ; i++)
        {
            Durata d = masini[i].getDurata();
            if(d.getMinute() - minute < 0 ) {
                masini[i].setDurata(Durata(0,0));
                masini[i].setDisponibilitate(true);}
            else if(d.getSecunde() - secunde < 0)
            {
                masini[i].setDurata(Durata(d.getMinute()-minute-1,60+d.getSecunde() - secunde));
                if(masini[i].getDurata().getMinute() < 0){
                    masini[i].setDurata(Durata(0,0));
                    masini[i].setDisponibilitate(true);
                }
            }
            else masini[i].setDurata(Durata(d.getMinute()-minute,d.getSecunde()-secunde)); }
    }

    void listeazaMasini(){
        cout<<"Spalatoria in prezent: "<<endl;
        for(int i = 0; i < nrMasini; i++) {
            if(masini[i].getNrCapsule() == 0)
                cout << i << ". " << "Masina este neutilizabila. Nu mai are capsule!"<<endl;
            if (masini[i].getNrCapsule() != 0 && masini[i].getDisponibilitate() == 1 && masini[i].getDurata().getMinute() == 0 && masini[i].getDurata().getSecunde() == 0)
                cout << i << ". " << "Masina este libera."<<endl;
            else if (masini[i].getDurata().getMinute() != 0 || masini[i].getDurata().getSecunde() != 0)
            {
                cout << i << ". " << "Masina este ocupata pentru inca ";
                masini[i].getDurata().afiseazaDurata();
                cout<<endl;
            } } }
};

void listeazaMasiniLibere(Spalatorie S){
    cout<<"Urmatoarele masini sunt libere: ";
    for(int i=0 ; i < S.getNrMasini()  ; i++){
        if (S.getMasini()[i].getNrCapsule() != 0 &&
            S.getMasini()[i].getDisponibilitate() == 1 &&
            S.getMasini()[i].getDurata().getMinute() == 0 &&
            S.getMasini()[i].getDurata().getSecunde() == 0)
            cout << i << " ";
    }
    cout << endl;
}


int main(){
    vector <Masina> masini = {
            Masina(true, Durata(0,0),3),
            Masina(true, Durata(0,0),2),
            Masina(true, Durata(0,0),5) };

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
            spalatorie.listeazaMasini(); }