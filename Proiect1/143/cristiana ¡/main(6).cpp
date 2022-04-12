#include <iostream>
using namespace std;
class Durata{
private:
    int minute;
    int secunde;
public:
    Durata()  ///contructor fara parametrii
    {
        minute=0;
        secunde=0;
    }
    Durata(int minute, int secunde) ///constructor cu parametrii
    {
        this->minute=minute;
        this->secunde=secunde;
    }
    ~Durata(){    ///destructor
        minute=0;
        secunde=0;
    }
    int get_minute(){
        return minute;
    }
    int get_secunde(){
        return secunde;
    }
    void set_secunde(int secunde)
    {
        this->secunde=secunde;
    }
    void set_minute(int minute)
    {
        this->minute=minute;
    }
    Durata operator+ (Durata durata);
    Durata operator- (Durata durata);
};

Durata Durata::operator+(Durata durata) {
    Durata temp;
    temp.secunde=this->secunde+durata.secunde;
    temp.minute=this->minute+durata.minute;
    if(temp.secunde>=60)
        {
            temp.minute=temp.minute+temp.secunde/60;
            temp.secunde=temp.secunde%60;
        }
    return temp;
}
Durata Durata::operator-(Durata durata) {
    Durata temp;
    temp.secunde=this->secunde-durata.secunde;
    temp.minute=this->minute-durata.minute;
    if(this->secunde<durata.secunde)
    {
        temp.secunde=60+temp.secunde; ///pt ca temp.secunde<0
        temp.minute=temp.minute-1;
    }
    if(temp.secunde<0||temp.minute<0)
    {
        temp.secunde=0;
        temp.minute=0;
    }
    return temp;
}
class Masina {
private:
    bool liber;
    Durata durata;
    int nr_capsule;
public:
    Masina() {
        liber = false;
        durata = Durata(0, 0);
        nr_capsule = 0;
    }

    Masina(bool liber, Durata durata, int nr_capsule) {
        this->liber = liber;
        this->durata = durata;
        this->nr_capsule = nr_capsule;
    }

    ~Masina() {
        liber = false;
        durata = Durata(0, 0);
        nr_capsule = 0;
    }

    bool getliber() {
        return liber;
    }
    void setliber(bool liber)
    {
        this->liber=liber;
    }
    int getnr_capsule(){
        return nr_capsule;
    }
    void setnr_capsule(int nr_capsule){
        this->nr_capsule=nr_capsule;
    }
    Durata getDurata(){
        return durata;
    }
    void setDurata(Durata durata){
        this->durata=durata;
    }
};
class Spalatorie{
private:
    int nr_masini;
    Masina masini[5];
public:
    friend void listeazaMasiniLibere(Spalatorie x);
    Spalatorie()
    {
        nr_masini=0;
    }
    Spalatorie(int nr_masini, Masina masini[])
    {
        this->nr_masini=nr_masini;
        for(int i=0;i<=nr_masini;i++)
            this->masini[i]=masini[i];
    }
    ~Spalatorie()
    {
        nr_masini=0;
    }
    int getnr_masini(){
        return nr_masini;
    }
    void listeazaMasini();
    void adaugaJob(int nr, Durata durata);
    void actualizeazaTimp(Durata durata);
};

void Spalatorie::listeazaMasini(){
    cout<<"Spalatoria in prezent"<<endl;
    for(int i=0;i<nr_masini;i++)
    {
        cout<<"Masina "<<i;
        if(masini[i].getnr_capsule()==0)
            cout<<" este neutilizabila! Nu mai are capsule!";
        else
            if(masini[i].getliber()==true)
                cout<<" este libera.";
            else
                cout<<" este ocupata pentru inca "<<masini[i].getDurata().get_minute()<<" minute si "<<masini[i].getDurata().get_secunde()<<" secunde.";
        cout<<endl;
    }
}

void Spalatorie::adaugaJob(int nr, Durata durata) {
    if(masini[nr].getnr_capsule()==0)
        cout<<"NU SE POATE! Masina "<<nr<<" nu mai are capsule!"<<endl;
    else
    {
        masini[nr].setnr_capsule(masini[nr].getnr_capsule()-1);
        masini[nr].setDurata(durata+masini[nr].getDurata());
        masini[nr].setliber(false);
    }
}
void Spalatorie::actualizeazaTimp(Durata durata) {
    for(int i=0;i<getnr_masini();i++)
    {
        if(masini[i].getliber()==false) {
            masini[i].setDurata(masini[i].getDurata() - durata);
            if (masini[i].getDurata().get_minute() ==0 && masini[i].getDurata().get_secunde() == 0)
                masini[i].setliber(true);
        }
    }
}
void listeazaMasiniLibere(Spalatorie spalatorie)
{
    cout<<"Urmatoarele masini sunt libere:";
    for(int i=0;i<spalatorie.getnr_masini();i++)
    {
        if(spalatorie.masini[i].getliber()==true)
            cout<<i<<" ";
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
    spalatorie.listeazaMasini();

    spalatorie.adaugaJob(
            1,
            Durata(0, 35)
    );
    spalatorie.actualizeazaTimp(Durata(3, 0));

    spalatorie.adaugaJob(
            1,
            Durata(0, 35)
    );

    spalatorie.listeazaMasini();
}
