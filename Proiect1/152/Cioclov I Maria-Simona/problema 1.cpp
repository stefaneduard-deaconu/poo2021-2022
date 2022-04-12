#include <iostream>
#include <iomanip>
using namespace std;

class Durata{
    int minute, secunde;
public:
    Durata(){}
    Durata(int minute, int secunde) : minute(minute), secunde(secunde) {}

    friend ostream &operator<<(ostream &os, const Durata &durata) {
        os << durata.minute << ":" << setw(2) << setfill('0') << durata.secunde;
        return os;
    }

    bool operator<=(Durata timp){
        if(this->minute<timp.minute) return 1;
        if(this->minute>timp.minute) return 0;
        return this->secunde<=timp.secunde;
    }

    Durata operator-(Durata timp){
        Durata rez;
        rez.minute = ((this->minute*60 + this->secunde) - (timp.minute*60 + timp.secunde)) /60;
        rez.secunde =((this->minute*60 + this->secunde) - (timp.minute*60 + timp.secunde)) %60;
        return rez;
    }
};

class Masina {
    bool libera;
    Durata timp_ramas;
    int capsule;
public:
    Masina(){}
    Masina(bool libera, const Durata &timpRamas, int capsule) : libera(libera), timp_ramas(timpRamas), capsule(capsule) {}

    friend ostream &operator<<(ostream &os, const Masina &masina) {
        os << "libera: " << masina.libera << " timp_ramas: " << masina.timp_ramas << " capsule: " << masina.capsule;
        return os;
    }

    bool islibera() const {
        return libera;
    }

    Durata getTimpRamas() const{
        return timp_ramas;
    }

    int getCapsule() const {
        return capsule;
    }

    void setlibera(bool libera) {
        Masina::libera = libera;
    }

    void setTimpRamas(const Durata &timpRamas) {
        timp_ramas = timpRamas;
    }

    void setCapsule(int capsule) {
        Masina::capsule = capsule;
    }
};

class Spalatorie{
    int n;
    Masina masini[5];
public:
    void actualizeazaTimp(Durata timp){
        for(int i=0;i<n;i++)
        {
            if(masini[i].islibera()) continue;
            if(masini[i].getTimpRamas() <= timp)
            {
                masini[i].setlibera(true);
                masini[i].setTimpRamas(Durata(0,0));
            }
            masini[i].setTimpRamas(masini[i].getTimpRamas() - timp);
        }
    }

    void adaugaJob(int i, Durata timp_ramas){
        if(!masini[i].getCapsule())
        {
            cout<<"Masina "<<i<<" nu mai are capsule!\n";
            return;
        }

        masini[i].setCapsule(masini[i].getCapsule()-1);
        masini[i].setTimpRamas(timp_ramas);
        masini[i].setlibera(false);
    }

    Spalatorie(int n, Masina masini[]){
        this -> n = n;
        for(int i=0;i<n;i++)
            this -> masini[i] = masini[i];
    }

    friend ostream &operator<<(ostream &os, const Spalatorie &spalatorie) {
        os << "n: " << spalatorie.n << "\nmasini:\n";
        for(int i=0;i<spalatorie.n;i++)
            cout<<spalatorie.masini[i]<<endl;
        return os;
    }

    void listeazaMasini(){
        cout<<"Spalatoria in prezent:\n";
        for(int i=0;i<n;i++)
            if(!masini[i].islibera()) cout << i << ". Masina este ocupata pentru inca " << masini[i].getTimpRamas() << endl;
            else if(!masini[i].getCapsule()) cout << i << ". Masina este neutilizabila! Nu mai are capsule!" << endl;
            else cout << i << ". Masina este libera" << endl;
    }

    int getN() const {
        return n;
    }

    const Masina getMasini(int i) const {
        return masini[i];
    }
};

void listeazaMasiniLibere(Spalatorie spalatorie){
    int ok=0;
    for(int i=0;i<spalatorie.getN();i++)
        if(spalatorie.getMasini(i).islibera()) {ok=1; break;}
    if(!ok)
    {
        cout<<"Toate masinile sunt ocupate\n";
        return;
    }
    cout<<"Urmatoarele masini sunt libere: ";
    for(int i=0;i<spalatorie.getN();i++)
        if(spalatorie.getMasini(i).islibera()) cout<<i<<" ";
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

}
