#include <iostream>

using namespace std;

class Durata {
private:
    int h, m;
public:
    Durata() : h(0), m(0) {}

    Durata(int h, int m) : h(h), m(m) {}

    void afiseaza() const { // TODO sa le zic ca aici trebuie const
        cout << h << ":";
        if (m < 10) {
            cout << "0";
        }
        cout << m;
    }

    bool maiMicEgal(Durata durata) {
        if (h < durata.h) {
            return true;
        }
        if (h > durata.h) {
            return false;
        }
        return (m <= durata.m);
    }

    void scade(Durata durata) {
        if (maiMicEgal(durata)) {
            h = 0;
            m = 0;
        } else {
            // doua cazuri: durata.m are mai multa, sau mai putine, minute decat timpul ramas
            if (m < durata.m) {
                h -= durata.h + 1;
                m = 60 + m - durata.m;
            } else {
                h -= durata.h;
                m -= durata.m;
            }
            // exista posibilitatea sa fii ajuns la ora negativa, si chiar ora negativa si minut pozitiv.
            if (h < 0) {
                h = 0;
                m = 0;
            }
        }
    }
};

class Masina {
private:
    bool esteLibera;
    Durata timpRamasJob;
    int capsuleRamase;
public:
    Masina() {
        esteLibera = false;
        capsuleRamase = 0;
    }

    Masina(bool esteLibera, const Durata &timpRamasJob, int capsuleRamase) : esteLibera(esteLibera),
                                                                             timpRamasJob(timpRamasJob),
                                                                             capsuleRamase(capsuleRamase) {}

    // getters:
    bool getEsteLibera() const {
        return esteLibera;
    }

    const Durata &getTimpRamasJob() const {
        return timpRamasJob;
    }

    int getCapsuleRamase() const {
        return capsuleRamase;
    }

    // setters:
    void setEsteLibera(bool esteLibera) {
        Masina::esteLibera = esteLibera;
    }

    void setTimpRamasJob(const Durata &_timpRamasJob) {
        timpRamasJob = _timpRamasJob;
        // pentru siguranta
        if (timpRamasJob.maiMicEgal(Durata(0, 0))) {
            esteLibera = true;
        }
    }

    void actualizeazaTimp(Durata durata) {
        timpRamasJob.scade(durata);
        if (timpRamasJob.maiMicEgal(Durata(0, 0))) {
            esteLibera = true;
        }
    }

    void folosesteCapsula() {
        capsuleRamase--;
    }
};

class Spalatorie {
private:
    int n;
    Masina masini[5];
public:
    Spalatorie(int n, Masina _masini[]) : n(n) {
        for (int i = 0; i < n; ++i) {
            masini[i] = _masini[i];
        }
    }
    // getter
    int getN() const {
        return n;
    }

    const Masina *getMasini() const {
        return masini;
    }

    // metode cerute
    void listeazaMasini() {
        cout << "Spalatoria in prezent:" << '\n';
        for (int i = 0; i < n; ++i) {

            cout << i << ". Masina este ";
            if (masini[i].getCapsuleRamase() <= 0) {
                cout << "neutilizabila! Nu mai are capsule!";
            } else if (masini[i].getEsteLibera()) {
                cout << "libera";
            } else {
                cout << "ocupata pentru inca ";
                masini[i].getTimpRamasJob().afiseaza();
            }

            cout << '\n';
        }
    }

    void adaugaJob(int i, Durata durata) {
        if (!masini[i].getEsteLibera()) {
            cout << "Masina " << i << " nu este libera!" << '\n';
        } else {
            if (masini[i].getCapsuleRamase() <= 0) {
                cout << "Masina " << i << " nu mai are capsule!" << '\n';
            } else {
                masini[i].setEsteLibera(false);
                masini[i].setTimpRamasJob(durata);
                masini[i].folosesteCapsula();
            }
        }
    }

    void actualizeazaTimp(Durata d) {
        for (int i = 0; i < n; ++i) {
            masini[i].actualizeazaTimp(d);
        }
    }
};

void listeazaMasiniLibere(Spalatorie spalatorie) {
    cout << "Urmatoarele masini sunt libere: ";
    for (int i = 0; i < spalatorie.getN(); ++i) {
        if (spalatorie.getMasini()[i].getEsteLibera()) {
            cout << i << ' ';
        }
    }
    cout << '\n';

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

    spalatorie.listeazaMasini(); // = metoda care listeaza informatii despre fiecare masina de spalat din spalatorie:
    /*
     * Exemplu de output a metodei:
     *
        0. Masina este libera
        1. Masina este neutilizabila! Nu mai are capsule!
        2. Masina este ocupata pentru inca 1:20
     */

    listeazaMasiniLibere(spalatorie); // functie globala care afiseaza doar masinile libere. Afiseaza indicele lor:
    /*
     * Exemplu de output a functiei
     *
        Urmatoarele masini sunt libere: 0 2 3
     */


    // Metoda pentru adaugarea unei spalari intr-o anumita masina de spalat
    spalatorie.adaugaJob(
            1,
            Durata(1, 20)
    ); // va decrementa numarul de capsule, va retine noua durata, dar si ca nu mai este libera maxina

    spalatorie.listeazaMasini(); // metoda

    spalatorie.actualizeazaTimp(Durata(1, 19));
    spalatorie.listeazaMasini(); // metoda

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
