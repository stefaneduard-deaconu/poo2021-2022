#include <bits/stdc++.h>
using namespace std;

class Durata {
private:
    int minute, secunde;

public:
    Durata(int minute, int secunde) : minute(minute), secunde(secunde) {}
    Durata(const Durata& other) : minute(other.minute), secunde(other.secunde) {}
    int get_minute() const{
        return minute;
    }
    int get_secunde() const{
        return secunde;
    }
    Durata operator - (const Durata& durata) {
        return {this->minute - durata.minute, this->secunde - durata.secunde};
    }
    bool operator > (const Durata& durata) const {
        if (this->minute > durata.minute)
            return true;
        else if (this->minute == durata.minute ) {
            if (this->secunde > durata.secunde)
                return true;
            else
                return false;
        }
        return false;
    }
    friend ostream& operator << (ostream& out, const Durata& durata) {
        if (durata.minute < 10) {
            if (durata.secunde < 10)
                out << "0" << durata.minute << ":" << "0" << durata.secunde;
            else
                out << "0" << durata.minute << ":" << durata.secunde;
        }
        else {
            if (durata.secunde < 10)
                out << durata.minute << ":" << "0" << durata.secunde;
            else
                out << durata.minute << ":" << durata.secunde;
        }
        return out;
    }
};

class MasinaSpalat {
private:
    bool available;
    Durata time_left;
    int capsule;
public:
    MasinaSpalat(bool available, Durata &timeLeft, int capsule) : available(available), time_left(timeLeft), capsule(capsule) {}
    bool get_available() const {
        return available;
    }
    Durata get_time_left() const {
        return time_left;
    }
    int get_capsule() const {
        return capsule;
    }
};

class Spalatorie {
private:
    int n;
    vector<MasinaSpalat> masini;
public:
    Spalatorie(int n, vector<MasinaSpalat> masini) : n(n), masini(masini) {}
    vector<MasinaSpalat> get_masini() {
        return masini;
    }
    void listeazaMasini() {
        cout << "Spalatoria in prezent:\n";
        for (unsigned long long i = 0; i < masini.size(); i++) {
            auto masina = masini[i];
            if (masina.get_capsule() == 0) {
                cout << i << ". Masina este neutilizabila! Nu mai are capsule!\n";
            }
            else if (masina.get_available()) {
                cout << i << ". Masina este libera\n";
            }
            else {
                cout << i << ". Masina este ocupata pentru inca " << masina.get_time_left() << "\n";
            }
        }
    }
    void adaugaJob(int index, Durata timp) {
        if (masini[index].get_capsule() == 0)
            cout << "Masina " << index << " nu mai are capsule!\n";
        else
            masini[index] = MasinaSpalat(false, timp, masini[index].get_capsule() - 1);
    }
    void actualizeazaTimp(const Durata& timp) {
        for (auto & i : masini) {
            if (i.get_time_left() > timp) {
                Durata d(i.get_time_left() - timp);
                i = MasinaSpalat(false, d, i.get_capsule());
            }
            else {
                Durata d(0, 0);
                i = MasinaSpalat(true, d, i.get_capsule());
            }
        }
    }
};
void listeazaMasiniLibere(Spalatorie spalatorie) {
    vector<MasinaSpalat> masini = spalatorie.get_masini();
    cout << "Urmatoarele masini sunt libere: ";
    for (unsigned long long i = 0; i < masini.size(); i++) {
        auto masina = masini[i];
        if (masina.get_available())
            cout << i << " ";
    }
    cout << "\n";
}

int main() {
    vector<MasinaSpalat> masini;
    Durata d(0, 0);
    masini.emplace_back(true, d, 3);
    masini.emplace_back(true, d, 2);
    masini.emplace_back(true, d, 5);
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