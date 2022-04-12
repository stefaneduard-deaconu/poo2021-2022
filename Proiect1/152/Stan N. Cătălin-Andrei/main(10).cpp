#include <iostream>
#include <vector>

using namespace std;

class Spalatorie;

class Durata {
private:
    int minute, secunde;
public:
    Durata():minute(0), secunde(0) {};

    Durata(int minute, int secunde) : minute(minute), secunde(secunde) {}

    void afis() const;

    Durata operator-(Durata &other);

    bool operator<(const Durata &other) const;

    bool operator==(const Durata &rhs) const;

    bool operator!=(const Durata &rhs) const;

    int getSec() const;
};

class Masina {
private:
    bool libera;
    Durata durata;
    int nrCapsule;
public:
    Masina() : libera(true), durata({0, 0}), nrCapsule(0) {};

    Masina(bool libera, const Durata &durata, int nrCapsule) : libera(libera), durata(durata), nrCapsule(nrCapsule) {}

    bool isLibera() const;

    void setDurata(const Durata &_durata);

    Durata &getDurata();

    void setLibera(bool libera);

    int getNrCapsule() const;

    void setNrCapsule(int nrCapsule);

    void afisDurata();
};

class Spalatorie {
private:
    int nrMasini;
    Masina masini[5];
public:
    Spalatorie(int nrMasini, Masina *masini) : nrMasini(nrMasini){
        for (int i = 0; i < nrMasini; ++i) {
            this->masini[i] = masini[i];
        }
    }
    void listeazaMasini();

    void adaugaJob(int nrMasina, Durata durata);

    void actualizeazaTimp(Durata durata);

    bool getFree(int n);

    int getNrMasini() const;
};


int Durata::getSec() const {
    return (minute * 60 + secunde);
}

bool Durata::operator<(const Durata &other) const {
    return (minute * 60 + secunde < other.minute * 60 + other.secunde);
}

Durata Durata::operator-(Durata &other) {
    if (*this < other) {
        return {0, 0};
    } else {
        int tmp = (*this).getSec() - other.getSec();
        return {tmp/60, tmp%60};
    }
}

void Durata::afis() const {
    cout << minute << ":";
    if (secunde < 10) cout << "0";
    cout << secunde;
}

bool Durata::operator==(const Durata &rhs) const {
    return minute == rhs.minute &&
           secunde == rhs.secunde;
}

bool Durata::operator!=(const Durata &rhs) const {
    return !(rhs == *this);
}

bool Spalatorie::getFree(int n) {
    return masini[n].isLibera();
}

int Spalatorie::getNrMasini() const {
    return nrMasini;
}

/// 4. Metoda care actualizeaza datele despre fiecare masina (daca a terminat spalarea, daca
/// mai are capsule, daca este libera), daca trece o anumita durata de timp

void Spalatorie::actualizeazaTimp(Durata durata) {
    for (int i = 0; i < nrMasini; ++i) {
        masini[i].setDurata(masini[i].getDurata() - durata);
        if (masini[i].getDurata() == Durata(0, 0)) {
            masini[i].setLibera(true);
        }
    }
}

/// 3. Metoda pentru adaugarea unei spalari pentru o anumita masina de spalat

void Spalatorie::adaugaJob(int nrMasina, Durata durata) {
    masini[nrMasina].setLibera(false);
    masini[nrMasina].setDurata(durata);
    masini[nrMasina].setNrCapsule(masini[nrMasina].getNrCapsule() - 1);
    if (masini[nrMasina].getNrCapsule() < 0) {
        cout << "Masina " << nrMasina << " nu mai are capsule!\n";
    }
}

/// 2. Metoda si functie de listare a masinilor de spalat

void Spalatorie::listeazaMasini() {
    cout << "Spalatoria in prezent:\n";
    for (int i = 0; i < nrMasini; ++i) {
        if (masini[i].getNrCapsule() <= 0) {
            cout << i << ". Masina este neutilizabila! Nu mai are capsule!\n";
        }
        else if (masini[i].isLibera()) {
            cout << i << ". Masina este libera\n";
        } else {
            cout << i << ". Masina este ocupata pentru inca ";
            masini[i].afisDurata();
            cout << "\n";
        }
    }
}


void listeazaMasiniLibere(Spalatorie S) {
    vector<int> tmp;
    for (int i = 0; i < S.getNrMasini(); ++i) {
        if (S.getFree(i)) {
            tmp.push_back(i);
        }
    }
    if (tmp.empty()) {
        cout << "Nu sunt masini libere\n";
    } else {
        cout << "Urmatoarele masini sunt libere: ";
        for (auto y:tmp) {
            cout << y << " ";
        }
        cout << "\n";
    }
}

//////////////

bool Masina::isLibera() const {
    return libera;
}

void Masina::setDurata(const Durata &_durata) {
    durata = _durata;
}

Durata &Masina::getDurata() {
    return durata;
}

void Masina::setLibera(bool _libera) {
    libera = _libera;
}

int Masina::getNrCapsule() const {
    return nrCapsule;
}

void Masina::setNrCapsule(int _nrCapsule) {
    nrCapsule = _nrCapsule;
}

void Masina::afisDurata() {
    durata.afis();
}

int main() {
    /// 1. Crearea unei spalatorii
    Masina masini[5] = {
            Masina(true, Durata(0, 0), 3),
            Masina(true, Durata(0, 0), 2),
            Masina(true, Durata(0, 0), 5),
    };
    Spalatorie spalatorie(
            3,
            masini
    );
    /// 5. Metodele for fi folosite intr-o succesiune logica, precum
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
    return 0;
}