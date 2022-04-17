//
// Created by Mihai145 on 3/4/2022.
//

#include <iostream>
#include <cstdlib>

using namespace std;

/* Afiseaza o eroare si apoi termina executia */
void error(char *message) {
    cout << message << '\n';
    exit(-1);
}

/* Durata = tuplu de forma (hh:mm) cu 0 <= hh <= 99 si 0 <= mm <= 60 */
class Durata {
private:
    int h, m;

public:
    Durata() { this->h = 0, this->m = 0; }

    Durata(int h, int m) {
        /* durata invalida */
        if (h < 0 || h > 99 || m < 0 || m >= 60) {
            error((char *) "Durata invalida");
        }

        this->h = h, this->m = m;
    }

    int getH() const {
        return h;
    }

    int getM() const {
        return m;
    }

    /* Returneaza durata formatata in stilul hh:mm */
    char *format() const {
        char *format = new char[6];
        int pos = 0;

        if (h >= 10) {
            format[pos++] = (char) (h / 10 + '0');
        }
        format[pos++] = (char) (h % 10 + '0');

        format[pos++] = ':';

        format[pos++] = (char) (m / 10 + '0');
        format[pos++] = (char) (m % 10 + '0');

        format[pos] = '\0';
        return format;
    }

    bool operator==(const Durata other) const {
        return (this->h == other.getH() && this->m == other.getM());
    }

    /* Scade din durata curenta o alta durata (nu vom avea durate negative, minimul este 00:00) */
    Durata &operator-=(const Durata other) {
        if (this->h < other.getH() || (this->h == other.getH() && this->m < other.getM())) {
            this->h = 0, this->m = 0;
            return *this;
        }

        if (this->m < other.getM()) {
            this->h = this->h - other.getH() - 1, this->m = this->m - other.getM() + 60;
            return *this;
        }

        this->h = this->h - other.getH(), this->m = this->m - other.getM();
        return *this;
    }
};

class MasinaSpalat {
private:
    bool liber;
    Durata timpOcupat;
    int nrCapsule;

public:
    MasinaSpalat() { this->liber = true, this->timpOcupat = Durata(0, 0), this->nrCapsule = 0; }

    MasinaSpalat(bool liber, Durata timpOcupat, int nrCapsule) {
        this->liber = liber;
        this->timpOcupat = timpOcupat;
        this->nrCapsule = nrCapsule;
    }

    bool isLiber() const {
        return liber;
    }

    /* Verifica daca o masina de spalat este pregatita pentru spalare */
    bool isReady() const {
        if (liber && nrCapsule > 0) {
            return true;
        }
        return false;
    }

    void setLiber(bool liber) {
        this->liber = liber;
    }

    void setTimpOcupat(const Durata &timpOcupat) {
        this->timpOcupat = timpOcupat;
    }

    void decrementNrCapsule() {
        this->nrCapsule--;
    }

    /* Afiseaza starea unei masini - libera, fara capsule, ocupata pentru o anumita durata */
    void afiseazaStare(int index) const {
        cout << index << ". ";

        if (!liber) {
            cout << "Masina este ocupata pentru inca " << timpOcupat.format() << "\n";
        } else if (nrCapsule == 0) {
            cout << "Masina este neutilizabila! Nu mai are capsule!\n";
        } else {
            cout << "Masina este libera\n";
        }
    }

    /* Actualizeaza starea unei masini (ocupata, libera) dupa ce trece o durata de timp */
    void actualizeazaTimp(Durata durata) {
        if (this->liber) {
            return;
        }

        this->timpOcupat -= durata;
        if (this->timpOcupat == Durata(0, 0)) {
            this->liber = true;
        }
    }
};

class Spalatorie {
private:
    int nrMasini;
    MasinaSpalat masini[5];

public:
    Spalatorie() { this->nrMasini = 0; }

    Spalatorie(int nrMasini, MasinaSpalat masini[]) {
        /* nrMasini <= 0, > 5 */
        if (nrMasini <= 0 || nrMasini > 5) {
            error((char *) "Numar de masini de spalat invalid");
        }

        this->nrMasini = nrMasini;
        for (int i = 0; i < nrMasini; i++) {
            this->masini[i] = masini[i];
        }
    }

    int getNrMasini() const {
        return nrMasini;
    }

    bool isFree(int index) const {
        /* index interogat gresit */
        if (index < 0 || index >= nrMasini) {
            return false;
        }

        return masini[index].isLiber();
    }

    void listeazaMasini() const {
        cout << "Spalatoria in prezent:\n";
        for (int i = 0; i < nrMasini; i++) {
            masini[i].afiseazaStare(i);
        }
    }

    void adaugaJob(int index, Durata durata) {
        /* index invalid */
        if (index < 0 || index >= nrMasini) {
            error((char *) "Masina nu exista");
        }

        if (!masini[index].isReady()) {
            masini[index].afiseazaStare(index);
            return;
        }

        masini[index].setLiber(false);
        masini[index].setTimpOcupat(durata);
        masini[index].decrementNrCapsule();
    }

    void actualizeazaTimp(Durata durata) {
        for (int i = 0; i < nrMasini; i++) {
            masini[i].actualizeazaTimp(durata);
        }
    }
};

void listeazaMasiniLibere(Spalatorie spalatorie) {
    int n = spalatorie.getNrMasini();

    cout << "Urmatoarele masini sunt libere: ";
    for (int i = 0; i < n; i++) {
        if (spalatorie.isFree(i)) {
            cout << i << ' ';
        }
    }
    cout << '\n';
}

int main() {

    /*
     * Cod exemplu
    */

    MasinaSpalat masini[5] = {
            MasinaSpalat(true, Durata(0, 0), 3),
            MasinaSpalat(true, Durata(0, 0), 2),
            MasinaSpalat(true, Durata(0, 0), 5),
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