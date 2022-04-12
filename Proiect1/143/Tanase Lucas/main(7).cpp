//Tanase Stefan Lucas - 143
#include <iostream>
using namespace std;
class Durata {
private:
    int minute;
    int secunde;
public:
    Durata()
    {
        this->minute=0;
        this->secunde=0;
    }
    Durata(int minute, int secunde)
    {
        this->minute=minute;
        this->secunde=secunde;
    }
    int getMinute() {
        return this->minute;
    }
    void setMinute(int minute)
    {
        this->minute=minute;
    }
    int getSecunde() {
        return this->secunde;
    }
    void setSecunde(int secunde)
    {
        this->secunde=secunde;
    }
    bool Zero();
    void operator-=(Durata durata);

};
void Durata::operator-=(Durata durata) {
    if(this->minute - durata.getMinute()<0)
    {
        this->minute=0;
        this->secunde=0;
    }
    if(this->secunde - durata.getSecunde()<0)
    {
        this->secunde=60 + this->secunde - durata.getSecunde();
        this->minute=this->minute - 1;
    }



}
bool Durata::Zero()
{
    if(minute ==0 && secunde==0)
        return true;
    else return false;
}
class MasinaSpalat {
private:
    bool esteLibera;
    int nrCapsule;
    Durata durata;
public:
    MasinaSpalat()
    {
        this->esteLibera= false;
        this->nrCapsule=0;
        this->durata=Durata(0,0);
    }
    MasinaSpalat(bool esteLibera, Durata durata,int nrCapsule)
    {
        this->esteLibera=esteLibera;
        this->nrCapsule=nrCapsule;
        this->durata=durata;
    }
    int getNrCapsule() {
        return this->nrCapsule;
    }
    void setNrCapsule(int nrCapsule)
    {
        this->nrCapsule=nrCapsule;
    }
    bool getEsteLibera()
    {
        return this->esteLibera;
    }
    void setEsteLibera(bool esteLibera)
    {
        this->esteLibera=esteLibera;
    }
    Durata getDurata()
    {
        return this->durata;
    }
    void setDurata( Durata durata)
    {
        this->durata=durata;
    }
};
class Spalatorie {
private:
    int numarMasini;
    MasinaSpalat masini[5];
public:
    Spalatorie()
    {
        this->numarMasini=0;
    }
    Spalatorie(int numarMasini,MasinaSpalat masini[])
    {
        this->numarMasini=numarMasini;
        for(int i=0; i<numarMasini;i++)
        {
            this->masini[i]=masini[i];
        }
    }
    int getNumarMasini()
    {
        return this->numarMasini;
    }
    void setNumarMasini(int numarMasini)
    {
        this->numarMasini=numarMasini;
    }
    void listeazaMasini();
    MasinaSpalat getMasinaSpalat(int indice);
    void adaugaProgram(int indice, Durata durata);
    void actualizeazaTimp(Durata durata);
};
void Spalatorie::adaugaProgram(int indice, Durata durata) {
    if(!getMasinaSpalat(indice).getEsteLibera())
    {
        cout<<"Masina este ocupata."<<"\n";
        return;
    }
    if(getMasinaSpalat(indice).getNrCapsule()<=0) {
        cout <<"Masina "<<indice<<" nu mai are capsule."<<"\n";
        return;
    }
    masini[indice].setNrCapsule(masini[indice].getNrCapsule()-1);
    masini[indice].setDurata(durata);
    masini[indice].setEsteLibera(false);
}


void Spalatorie::listeazaMasini()
{

    for(int i=0;i<numarMasini;i++)

    {
        cout<<i<<". Masina este ";
        if(masini[i].getEsteLibera())
            cout<<"libera";
        else cout<<"ocupata";
        if(masini[i].getNrCapsule()>0)
            cout<<", are capsule";
        else cout<<", nu mai are capsule";
        if(!masini[i].getDurata().Zero())
            cout<<" si mai are "<<masini[i].getDurata().getMinute()<<":"<<masini[i].getDurata().getSecunde();
        cout<<"\n";
    }
}
MasinaSpalat Spalatorie::getMasinaSpalat(int indice) {
    return masini[indice];
}
void Spalatorie::actualizeazaTimp(Durata durata) {
    for(int i=0; i<numarMasini;i++)
    {
        masini[i].getDurata()-=durata;
        if(masini[i].getDurata().Zero())
            masini[i].setEsteLibera(true);
    }

}
void listeazaMasiniLibere(Spalatorie spalatorie)
{   cout<<"Urmatoarele masini sunt libere: ";
    for(int i=0;i<spalatorie.getNumarMasini();i++)
    {
        if(spalatorie.getMasinaSpalat(i).getEsteLibera())
            cout<<i<<" ";
    }
    cout<<"\n";

}

int main() {
    MasinaSpalat masini[5] = {
            MasinaSpalat(true, Durata(0, 0), 3),
            MasinaSpalat(true, Durata(0, 0), 2),
            MasinaSpalat(true, Durata(0, 0), 5),
    };
    Spalatorie spalatorie(3,masini);

    spalatorie.listeazaMasini();
    listeazaMasiniLibere(spalatorie);

    spalatorie.adaugaProgram(
            1,
            Durata(1, 20)
    );
    spalatorie.listeazaMasini();

    spalatorie.actualizeazaTimp(Durata(1, 19));
    spalatorie.listeazaMasini();

    spalatorie.actualizeazaTimp(Durata(1, 0));
    spalatorie.listeazaMasini();

    spalatorie.adaugaProgram(
            1,
            Durata(0, 35)
    );
    spalatorie.actualizeazaTimp(Durata(3, 0));

    spalatorie.adaugaProgram(
            1,
            Durata(0, 35)
    );
    spalatorie.listeazaMasini();


}