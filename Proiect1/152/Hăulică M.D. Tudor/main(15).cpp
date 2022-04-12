#include <iostream>
#include <vector>
using namespace std;

class Durata {

    int minute, secunde;

public:

    Durata(int min, int sec) {
        this->minute = min;
        this->secunde = sec;
    }

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

};

class MasinaSpalat {

    bool libera;
    Durata timpSpalare;
    int numarCapsule;

public:

    MasinaSpalat(bool lib, Durata timp, int numar) : timpSpalare(timp) {
        this->libera = lib;
        this->numarCapsule = numar;
    }

    bool isLibera() const {
        return libera;
    }

    void setLibera(bool libera) {
        MasinaSpalat::libera = libera;
    }

    const Durata &getTimpSpalare() const {
        return timpSpalare;
    }

    void setTimpSpalare(const Durata &timpSpalare) {
        MasinaSpalat::timpSpalare = timpSpalare;
    }

    int getNumarCapsule() const {
        return numarCapsule;
    }

    void setNumarCapsule(int numarCapsule) {
        MasinaSpalat::numarCapsule = numarCapsule;
    }

};

class Spalatorie {

    int numarMasini;
    vector < MasinaSpalat > masiniSpalat;

public:

    int getNumarMasini() {
        return numarMasini;
    }

    void setNumarMasini(int numarMasini) {
        Spalatorie::numarMasini = numarMasini;
    }

    vector<MasinaSpalat> &getMasiniSpalat() {
        return masiniSpalat;
    }

    void setMasiniSpalat(vector<MasinaSpalat> &masini) {
        this->masiniSpalat.clear();

        for (MasinaSpalat masina : masini) {
            this->masiniSpalat.push_back(masina);
        }
    }

    Spalatorie(int numar, vector < MasinaSpalat > masini) {

        this->numarMasini = numar;
        this->masiniSpalat = masini;

    }

    void listeazaMasini() {
        cout << "Spalatoria in prezent:\n";
        vector < MasinaSpalat > masini = this -> getMasiniSpalat();
        int index = 0;

        for (MasinaSpalat masina : masini) {
            if (masina.isLibera())
                if (masina.getNumarCapsule() == 0)
                    cout << index << ". Masina este neutilizabila! Nu mai are capsule!\n";
                else
                    cout << index << ". Masina este libera\n";
            else {
                cout << index << ". Masina este ocupata pentru inca " << masina.getTimpSpalare().getMinute() << ":";
                if (masina.getTimpSpalare().getSecunde() < 10)
                    cout << "0";
                cout << masina.getTimpSpalare().getSecunde() << "\n";
            }
            index++;
        }
            cout << "\n";
    }

    void adaugaJob(int indexMasina, Durata durata) {
        vector < MasinaSpalat > masini = this -> getMasiniSpalat();

        if (!masini[indexMasina].isLibera()) {
            cout << "Masina " << indexMasina << " nu este libera!\n\n";
            return;
        }

        if(masini[indexMasina].getNumarCapsule() == 0) {
            cout << "Masina " << indexMasina << " nu mai are capsule!\n\n";
            return;
        }

        int capsule = masini[indexMasina].getNumarCapsule();
        masini[indexMasina].setNumarCapsule(capsule - 1);
        masini[indexMasina].setTimpSpalare(durata);
        masini[indexMasina].setLibera(false);
        this->setMasiniSpalat(masini);
    }

    void actualizeazaTimp(Durata durata) {
        vector < MasinaSpalat > masini = this -> getMasiniSpalat();

        for (int index = 0; index < masini.size(); ++index)
            if (!masini[index].isLibera()) {
                if (masini[index].getTimpSpalare().getMinute() < durata.getMinute() ||
                        (masini[index].getTimpSpalare().getMinute() == durata.getMinute() && masini[index].getTimpSpalare().getSecunde() < durata.getSecunde())) {
                    masini[index].setLibera(true);
                    masini[index].setTimpSpalare(Durata(0, 0));
                }
                else {

                    int timp1 = masini[index].getTimpSpalare().getMinute() * 60 + masini[index].getTimpSpalare().getSecunde();
                    int timp2 = durata.getMinute() * 60 + durata.getSecunde();
                    int timp = timp1 - timp2;

                    int minute = timp / 60;
                    int secunde = timp - 60 * minute;
                    masini[index].setTimpSpalare(Durata(minute, secunde));
                }
            }
        this->setMasiniSpalat(masini);
    }

};

void listeazaMasiniLibere(Spalatorie spalatorie) {

    vector<MasinaSpalat> masini = spalatorie.getMasiniSpalat();
    int count = 0;

    for (int index = 0; index < spalatorie.getNumarMasini(); ++index)
        if (masini[index].isLibera()) {
            count = 1;
            break;
        }

    if(count == 0) cout << "Nu exista masini libere!\n\n";
    else {
        cout << "Urmatoarele masini sunt libere: ";
        for (int index = 0; index < spalatorie.getNumarMasini(); ++index)
            if (masini[index].isLibera())
                cout << index << " ";
        cout << "\n\n";
    }
}

int main() {

    vector < MasinaSpalat > masini = {
            MasinaSpalat(true, Durata(0, 0), 3),
            MasinaSpalat(true, Durata(0, 0), 2),
            MasinaSpalat(true, Durata(0, 0), 5),
    };

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
    spalatorie.actualizeazaTimp(Durata(3, 0));

    spalatorie.adaugaJob(1, Durata(0, 35));
    spalatorie.listeazaMasini();

    return 0;
}