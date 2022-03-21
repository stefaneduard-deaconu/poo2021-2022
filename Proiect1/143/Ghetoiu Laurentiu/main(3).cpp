#include <iostream>

using namespace std;

// durata alcatuita din minute si secunde
class Durata {
public:
    Durata() {
        minute = 0;
        secunde = 0;
    }

    Durata(int minute, int secunde) : minute(minute), secunde(secunde) {}

    int getMinute() const {
        return minute;
    }

    void setMinute(int minute) {
        Durata::minute = minute;
    }

    int getSecunde() const {
        return secunde;
    }

    void setSecunde(int secunde) {
        Durata::secunde = secunde;
    }

private:
    int minute;
    int secunde;
};



// masina de spalat  - o variabila care ne spune daca e libera sau nu, o variabila de tip Data care ne spune cat timp mai
// este ocupata si o variabila capsule care ne spune cate capsule mai are
class Masina {

public:
    Masina() {
        libera =false;
        capsule = 0;
    }

    Masina(bool libera, const Durata &durata, int capsule) : libera(libera), durata(durata), capsule(capsule) {}

    bool isLibera() const {
        return libera;
    }

    void setLibera(bool libera) {
        Masina::libera = libera;
    }

    const Durata &getDurata() const {
        return durata;
    }

    void setDurata(const Durata &durata) {
        Masina::durata = durata;
    }

    int getCapsule() const {
        return capsule;
    }

    void setCapsule(int capsule) {
        Masina::capsule = capsule;
    }

private:
    bool libera;
    Durata durata;
    int capsule;
};

// clasa spalatorie -  poate sa fie alcatuita din mai multe masini
class Spalatorie {
public:
    // setters-getters-constructors pentru aceasta clasa
    Spalatorie() {
        nrMasini = 0;
    }

    Spalatorie(int nrMasini, Masina masini[6]) : nrMasini(nrMasini) {
        for (int i = 0; i < nrMasini; i++)
            this->masini[i] = masini[i];
    }

    int getNrMasini() const {
        return nrMasini;
    }

    void setNrMasini(int nrMasini) {
        Spalatorie::nrMasini = nrMasini;
    }

    const Masina *getMasini() const {
        return masini;
    }
    // metodele asociate clasei
    void listeazaMasini();

    void adaugaJob(int, Durata);

    void actualizeazaTimp(Durata);

private:
    int nrMasini;
    Masina masini[6];
};

// metoda ne spune starea spalatoriei in prezent, care masini sunt libere, care sunt ocupate si pentru cat timp,
// si cazul in care o masina nu mai este utilizabila pentru ca nu mai are capsule
void Spalatorie::listeazaMasini() {
    cout << "Spalatoria in prezent: \n";
    for (int i = 0; i < nrMasini; i++) {
        cout << i << ". ";
        if (masini[i].getCapsule() > 0) {
            if (masini[i].isLibera())
                cout << "Masina este libera";
            else {
                cout << "Masina este ocupata pentru inca ";

                cout << masini[i].getDurata().getMinute() << ":";
                if(masini[i].getDurata().getSecunde()<10)
                    cout<<"0";  // am adaugat un 0 pentru ca afisarea sa fie uniforma
                cout << masini[i].getDurata().getSecunde();
            }
        } else
            cout << "Masina neutilizabila! Nu mai are capsule!";
        cout << endl;
    }
}


// adauga un nou job unei masini anume, specifincand si cat dureaza noul job
void Spalatorie::adaugaJob(int index_masina, Durata durata) {
    if (masini[index_masina].getCapsule() <= 0) {
        cout << "Masina " << index_masina << " nu mai are capsule!\n";
        return;
    }
    masini[index_masina].setCapsule(masini[index_masina].getCapsule() - 1);
    masini[index_masina].setDurata(durata);
    masini[index_masina].setLibera(false);
}


// metoda care actualizeaza timpul tuturor masinilor si totodata si daca acestea au terminat spalarea sau timpul
// ramas pentru a termina
void Spalatorie::actualizeazaTimp(Durata durata) {
    // parcurge toate masinile din spalatorie si actualizeaza minutele si secundele
    for (int i = 0; i < nrMasini; i++) {
        int min_nou, sec_nou;
        Durata durata_nou;  // noua durata dupa actualizarea timpului
        min_nou = masini[i].getDurata().getMinute() - durata.getMinute();
        if (masini[i].getDurata().getSecunde() >= durata.getSecunde())
            sec_nou = masini[i].getDurata().getSecunde() - durata.getSecunde();
        else {
            min_nou = masini[i].getDurata().getMinute() - 1;
            sec_nou = masini[i].getDurata().getSecunde() + 60 - durata.getSecunde();
        }
        // daca timpul care a trecut depaseste durata in care era ocupata masina
        if (min_nou < 0 || sec_nou < 0 || (min_nou == 0 && sec_nou == 0)) {
            durata_nou.setMinute(0);
            durata_nou.setSecunde(0);
            masini[i].setLibera(true);
        } else
            masini[i].setLibera(false);
        durata_nou.setSecunde(sec_nou);
        durata_nou.setMinute(min_nou);
        masini[i].setDurata(durata_nou);
    }
}


// functia care listeza masinile libere
void listeazaMasiniLibere(Spalatorie spalatorie) {
    cout << "Urmatoarele masini sunt libere: ";
    for (int i = 0; i < spalatorie.getNrMasini(); i++)
        if (spalatorie.getMasini()[i].isLibera())
            cout << i << " ";
    cout << "\n";
}


int main() {
    // lista cu masini
    Masina masini[5] = {
            Masina(true, Durata(0, 0), 3),
            Masina(true, Durata(0, 0), 2),
            Masina(true, Durata(0, 0), 5),
    };
    // o spalatorie cu 3 masini
    Spalatorie spalatorie(3, masini);

    
    spalatorie.listeazaMasini();
    listeazaMasiniLibere(spalatorie);
    spalatorie.adaugaJob(1, Durata(1, 20));
    spalatorie.listeazaMasini();

    spalatorie.actualizeazaTimp(Durata(1, 19));
    spalatorie.listeazaMasini();

    spalatorie.actualizeazaTimp(Durata(1, 0));
    spalatorie.listeazaMasini();

    spalatorie.adaugaJob(1, Durata(0, 35));

    spalatorie.adaugaJob(1, Durata(0, 35));

    spalatorie.listeazaMasini();
    return 0;
}
