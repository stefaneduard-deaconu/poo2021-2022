#include <iostream>

using namespace std;

class Durata {
    int minute;
    int secunde;
public:
    Durata() {}

    Durata(int minute_, int secunde_) {
        minute = minute_;
        secunde = secunde_;
    }

    int getMinute() {
        return minute;
    }

    int getSecunde() {
        return secunde;
    }

    void setMinute(int minute_) {
        minute = minute_;
    }

    void setSecunde(int secunde_) {
        secunde = secunde_;
    }
};

class Masina {
    bool liber;
    int nrcapsule;
    Durata durata;
public:
    Masina() {}

    Masina(bool liber_, Durata durata_, int nrcapsule_) {
        liber = liber_;
        nrcapsule = nrcapsule_;
        durata = durata_;
    }

    int getNrcapsule() {
        return nrcapsule;
    }

    void setLiber(bool liber_) {
        liber = liber_;
    }

    void setNrcapsule(int nrcapsule_) {
        nrcapsule = nrcapsule_;
    }

    void setDurata(Durata durata_) {
        durata = durata_;
    }

    bool getLiber() {
        return liber;
    }

    Durata &getdurata() {
        return durata;
    }
};

class Spalatorie {
    int n;
    Masina masini[6];

public:

    Spalatorie() {}

    Spalatorie(int n_, Masina masini_[]) {
        n = n_;
        for (int i = 0; i < n_; i++)
            masini[i] = masini_[i];
    }

    void listeazaMasini() {
        cout << "Spalatoria in prezent:\n";
        for (int i = 0; i < n; i++) {
            if (masini[i].getNrcapsule() == 0)
                cout << i << ". Masina este neutilizabila! Nu mai are capsule!\n";
            else if (masini[i].getLiber())
                cout << i << ". Masina este libera\n";
            else {
                if (masini[i].getdurata().getMinute() != 0 || masini[i].getdurata().getSecunde() != 0) {
                    if (masini[i].getdurata().getSecunde() < 10)
                        cout << i << ". Masina este ocupata pentru inca " << masini[i].getdurata().getMinute() << ":"
                             << 0 << masini[i].getdurata().getSecunde() << "\n";
                    else
                        cout << i << ". Masina este ocupata pentru inca " << masini[i].getdurata().getMinute() << ":"
                             << masini[i].getdurata().getSecunde() << "\n";
                }
            }
        }
    }

    void adaugaJob(int i, Durata new_dur) {
        if (masini[i].getNrcapsule() == 0)
            cout << "Masina " << i << " nu mai are capsule!\n";
        else {
            masini[i].setNrcapsule(masini[i].getNrcapsule() - 1);
            masini[i].setDurata(new_dur);
            masini[i].setLiber(false);
        }
    }

    void actualizeazaTimp(Durata new_dur) {
        for (int i = 0; i < n; i++) {
            if (!masini[i].getLiber()) {
                if (masini[i].getdurata().getMinute() < new_dur.getMinute())
                    masini[i].setLiber(true);
                else if (masini[i].getdurata().getMinute() == new_dur.getMinute() &&
                         masini[i].getdurata().getSecunde() < new_dur.getSecunde())
                    masini[i].setLiber(true);
                else {
                    if (masini[i].getdurata().getSecunde() < new_dur.getSecunde()) {
                        masini[i].getdurata().setSecunde(
                                60 + masini[i].getdurata().getSecunde() - new_dur.getSecunde());
                        masini[i].getdurata().setMinute(masini[i].getdurata().getMinute() - 1);
                    } else
                        masini[i].getdurata().setSecunde(masini[i].getdurata().getSecunde() - new_dur.getSecunde());
                    masini[i].getdurata().setMinute(masini[i].getdurata().getMinute() - new_dur.getMinute());
                }
            }
        }
    }

    int getn() {
        return n;
    }

    Masina *getmasini() {
        return masini;
    }
};

void listeazaMasiniLibere(Spalatorie spalatorie) {
    cout << "Urmatoarele masini sunt libere: ";
    for (int i = 0; i < spalatorie.getn(); i++) {
        if (spalatorie.getmasini()->getLiber())
            cout << i << " ";
    }
    cout << "\n";
}

int main() {
    Masina masini[5] = {
            Masina(true, Durata(0, 0), 3),
            Masina(true, Durata(0, 0), 2),
            Masina(true, Durata(0, 0), 5),
    };
    Spalatorie spalatorie(3, masini);

    spalatorie.listeazaMasini();
    listeazaMasiniLibere(spalatorie);

    spalatorie.adaugaJob(1, Durata(1, 20));
    spalatorie.listeazaMasini();

    spalatorie.actualizeazaTimp(Durata(1, 19));
    spalatorie.listeazaMasini();

    spalatorie.actualizeazaTimp(Durata(1, 0));
    spalatorie.listeazaMasini(); // metoda

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