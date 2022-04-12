#include <iostream>

class Durata {
private:
    int ora, minut;
public:
    Durata(int ora, int minut) : ora(ora), minut(minut) {}

    Durata() {
        ora = 0;
        minut = 0;
    }

    int getOra() const {
        return ora;
    }

    int getMinut() const {
        return minut;
    }
};

class Masina {
private:
    bool liber;
    Durata curr;
    int capsule;
public:
    Masina(bool liber, const Durata &curr, int capsule) : liber(liber), curr(curr), capsule(capsule) {}

    Masina() {
        liber = true;
        curr = Durata(0, 0);
        capsule = 0;
    }

    bool isLiber() const {
        return liber;
    }

    const Durata &getCurr() const {
        return curr;
    }

    int getCapsule() const {
        return capsule;
    }

    void setCurr(const Durata &curr) {
        Masina::curr = curr;
    }

    void setCapsule(int capsule) {
        Masina::capsule = capsule;
    }

    void setLiber(bool liber) {
        Masina::liber = liber;
    }
};

class Spalatorie {
    int n;
    Masina *masini;

public:
    Spalatorie(int n, Masina *masini) : n(n), masini(masini) {}

    int getN() const {
        return n;
    }

    Masina *getMasini() const {
        return masini;
    }

    void listeazaMasini() {
        std::cout << "Spalatoria in prezent\n";
        for(int i = 0; i < n; i++) {
            if(masini[i].isLiber() && masini[i].getCapsule() != 0)
                std::cout << i <<". Masina este libera\n";
            else if(!masini[i].isLiber()) {
                Durata timpRamas = masini[i].getCurr();
                std::cout << i << ". Masina este ocupata pentru inca " << timpRamas.getOra() << ":";
                if(timpRamas.getMinut() < 10)
                    std::cout << "0";
                std::cout << timpRamas.getMinut() << "\n";
            }
            else if(masini[i].getCapsule() == 0) {
                std::cout << i << ". Masina este inutilizabila, nu mai are capsule!\n";
            }
        }
        std::cout << "\n";
    };

    void actualizeazaTimp(Durata timp) {
        int timpNou = timp.getMinut() + timp.getOra() * 60;
        for(int i = 0; i < n; i++) {
            if(!masini[i].isLiber()) {
                Durata timpI = masini[i].getCurr();
                int timpCurent = timpI.getMinut() + timpI.getOra() * 60;
                if (timpNou >= timpCurent) {
                    masini[i].setCurr(Durata(0, 0));
                    masini[i].setCapsule(masini[i].getCapsule() - 1);
                    masini[i].setLiber(true);
                } else {
                    timpCurent -= timpNou;
                    masini[i].setCurr(Durata(timpCurent / 60, timpCurent % 60));
                }
            }
        }
    }

    void adaugaJob(int index, Durata timp) {
        if(masini[index].getCapsule() == 0) {
            std::cout << "Nu se poate adauga job, masina " << index << " nu mai are capsule!\n";
        }
        else if (!masini[index].isLiber()){
            std::cout << "Nu se poate adauga job, masina " << index << " este ocupata!\n";
        }
        else {
            masini[index].setLiber(false);
            masini[index].setCurr(timp);
        }
    }
};

void listeazaMasiniLibere(Spalatorie spalatorie) {
    bool ok = false;
    Masina *masini = spalatorie.getMasini();

    std::cout << "Urmatoarele masini sunt libere: ";
    for(int i = 0; i < spalatorie.getN(); i++) {
        if(masini[i].isLiber()) {
            ok = true;
            std::cout << i << " ";
        }
    }
    if(ok == false)
        std::cout << "niciuna";
    std::cout << "\n";
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
}
