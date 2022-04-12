#include <iostream>
#include <utility>
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
    int getMinute() const{
        return minute;
    }
    int getSecunde() const{
        return secunde;
    }
    void setMinute(int _minute){
        minute = _minute;
    }
    void setSecunde(int _secunde){
        secunde = _secunde;
    }
    void afiseazaDurata() const{
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
    int getNrCapsule() const{
        return nrCapsule;
    }

    bool getDisponibilitate() const{
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
    Spalatorie(int _nrMasini, Masina _masini[10]){
        nrMasini = _nrMasini;
        for(int i=0 ; i < nrMasini ; i++)
            masini.push_back(_masini[i]);

    }

    void setNrMasini(int _nrMasini){
        nrMasini = _nrMasini;
    }
    int getNrMasini() const{
        return nrMasini;
    }
    void adaugaJob(int i, Durata timp){
        if(masini[i].getNrCapsule() == 0)
            cout << "Masina " << i << " nu mai are capsule! ";
        else {
            masini[i].setDisponibilitate(false);
            masini[i].setNrCapsule(masini[i].getNrCapsule()-1);
            masini[i].setDurata(timp);
        }
    }
    vector <Masina> getMasini(){
        return masini;
    }
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


int main() {
    Masina masini[5] = {
            Masina(true, Durata(0, 0), 3),
            Masina(true, Durata(0, 0), 3),
            Masina(true, Durata(0, 0), 3)

    };
    Spalatorie spalatorie(
            3,
            masini
    );

    listeazaMasiniLibere(spalatorie);

    spalatorie.adaugaJob(
            2,
            Durata(1, 0));

    listeazaMasiniLibere(spalatorie);




    masini[0].setDurata(Durata(12,12));
    cout << masini[0].getDurata().getMinute() << " ";
    for(int i=0 ; i < 3 ; i++)
    {
        cout << masini[i].getDurata().getMinute() << " ";
        cout << masini[i].getDurata().getSecunde() << " ";
        cout << masini[i].getNrCapsule() << endl; }
    //masini[1].setDurata(Durata(99,99));
    //cout << masini[1].getDurata().getMinute() << " ";
    //cout << masini[1].getDurata().getSecunde() << " ";

}