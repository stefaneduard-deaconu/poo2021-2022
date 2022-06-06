#include <bits/stdc++.h>

using namespace std;

class Durata {
    int ora, minut;

public:
    Durata(){
        ora = 0;
        minut = 0;
    }

    Durata(int a, int b){
        ora = a;
        minut = b;
    }

    void setOra(int x){
        ora = x;
    }

    void setMinut(int x){
        minut = x;
    }

    int getOra(){
        return ora;
    }

    int getMinut(){
        return minut;
    }
};

class Masina {
    bool esteLibera;
    Durata durata;
    int nrCapsule;

public:
    Masina(bool a, Durata b, int c){
        esteLibera = a;
        durata = b;
        nrCapsule = c;
    }

    Masina(){
        return;
    }

    void decNrCapsule(){
        --nrCapsule;
    }

    void decDurata(Durata a){
        durata.setMinut(durata.getMinut() - a.getMinut());
        if(durata.getMinut() < 0){
            durata.setMinut(durata.getMinut() + 60);
            durata.setOra(durata.getOra() - 1);
        }
        durata.setOra(durata.getOra() - a.getOra());
        if(durata.getOra() < 0){
            durata.setOra(0);
            durata.setMinut(0);
        }
        if(durata.getOra() == 0 && durata.getMinut() == 0)
            esteLibera = true;
    }

    void setDurata(Durata a){
        durata = a;
    }

    void setEsteLibera(bool a){
        esteLibera = a;
    }

    int getNrCapsule(){
        return nrCapsule;
    }

    bool getEsteLibera(){
        return esteLibera;
    }

    Durata getDurata(){
        return durata;
    }
};

class Spalatorie {
    int nrMasini;
    vector <Masina> masini;

public:
    Spalatorie(int a, Masina b[]){
        nrMasini = a;
        for(int i = 0; i < a; i++){
            masini.push_back(b[i]);
        }
    }

    void listeazaMasini();

    void adaugaJob(int idx, Durata durata);

    void actualizeazaTimp(Durata duata);

    int getNrMasini(){
        return nrMasini;
    }

    Masina getMasinaIdx(int idx){
        return masini[idx];
    }
};

void Spalatorie::adaugaJob(int idx, Durata durata){
    if(!masini[idx].getNrCapsule()){
        cout << "Masina " << idx << " nu mai are capsule!\n";
        return;
    }
    masini[idx].decNrCapsule();
    masini[idx].setDurata(durata);
    masini[idx].setEsteLibera(false);
}

void Spalatorie::listeazaMasini(){
    cout << "Spalatoria in prezent:\n";
    for(int i = 0; i < nrMasini; i++){
        cout << i << ". ";
        if(masini[i].getNrCapsule() > 0){
            if(masini[i].getEsteLibera())
                cout << "Masina este libera\n";
            else {
                cout << "Masina este ocupata pentru inca " << masini[i].getDurata().getOra() << ':';
                if(masini[i].getDurata().getMinut() < 10)
                    cout << '0';
                cout << masini[i].getDurata().getMinut() << '\n';
            }
        } else {
            cout << "Masina este neutilizabila! Nu mai are capsule!\n";
        }
    }
}

void Spalatorie::actualizeazaTimp(Durata durata){
    for(int i = 0; i < nrMasini; i++){
        masini[i].decDurata(durata);

    }
}

void listeazaMasiniLibere(Spalatorie spalatorie){
    cout << "Urmatoarele masini sunt libere:";
    for(int i = 0; i < spalatorie.getNrMasini(); i++){
        Masina masina = spalatorie.getMasinaIdx(i);
        if(masina.getNrCapsule() > 0){
            if(masina.getEsteLibera())
                cout << ' ' << i;
        }
    }
    cout << '\n';
}

int main() {

        // declararea spalatoriei
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
