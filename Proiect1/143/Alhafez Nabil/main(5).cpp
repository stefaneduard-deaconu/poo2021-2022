#include <iostream>
#include <vector>
#include <type_traits>

using namespace std;

template<class T>
constexpr size_t len(T &a) {
    return sizeof(a) / sizeof(typename remove_all_extents<T>::type);
}

const int N = 1e4;

class Durata {
private:
    int minutes;
    int seconds;
public:

    Durata() : minutes(0), seconds(0) {};

    Durata(int min, int sec) : minutes(min), seconds(sec) {};

    inline void setMinute(int num) {
        this->minutes = num;
    }

    inline void setSecond(int num) {
        this->seconds = num;
    }

    [[nodiscard]]  inline int getMinute() const {
        return this->minutes;
    }

    [[nodiscard]] inline int getSecond() const {
        return this->seconds;
    }

    [[nodiscard]] inline string getMinuteAsString() const {
        if (minutes < 10)
            return "0" + to_string(minutes);
        return to_string(minutes);
    }

    [[nodiscard]] inline string getSecondAsString() const {
        if (seconds < 10)
            return "0" + to_string(seconds);
        return to_string(seconds);
    }

//    ostream& operator<<(ostream &os ) const{
//        toString();
//        return os;
//    }
    friend ostream &operator<<(ostream &os, const Durata &durata);

    Durata operator-(const Durata &rTime) const;

    void toString() const {
        cout << "Durata(minutes: " << minutes << ", "
             << "seconds: " << seconds
             << ")";
    }
};

ostream &operator<<(ostream &os, const Durata &durata) {
    durata.toString();
    return os;
}

Durata Durata::operator-(const Durata &rDurata) const {
    int rMin = this->minutes - rDurata.minutes;
    int rSec = this->seconds - rDurata.seconds;
    if (rMin < 0) {
        rSec = 0;
        rMin = 0;
    }
    return Durata(rMin, rSec);

}

class MasinaSpalat {

private:
    bool isFree;
    Durata durata;
    int capsuleNumber;

public:
    inline MasinaSpalat() :
            isFree(0), durata(Durata()),
            capsuleNumber(0) {};

    inline MasinaSpalat(bool isFree, const Durata &durata, int capsuleNumber) :
            isFree(isFree), durata(durata),
            capsuleNumber(capsuleNumber) {};


    inline void setIsFree(bool value) {
        this->isFree = value;
    }

    inline void setDurata(Durata value) {
        this->durata = value;
    }

    inline void setCapsuleNumber(int value) {
        this->capsuleNumber = value;
    }

    inline void decreaseCapsuleNumber(int index) {
        if (incaEsteCapsule())
            this->capsuleNumber--;
        else
            afiseazaNuEsteCapsule(index);
    }

    inline int getIsFree() const {
        return this->isFree;
    }

    inline Durata getDurata() const {
        return this->durata;
    }

    inline int getCapsuleNumber() const {
        return this->capsuleNumber;
    }

    inline bool incaEsteCapsule() const {
        return this->capsuleNumber > 0;
    }

    inline void afiseazaNuEsteCapsule(int index) const {
        cout << "Masina " << index << " nu mai are capsule!" << endl;
    }


    inline void toString() {
        cout << "MasinaSpalat(isFree: " << (bool) isFree << ", "
             << "durata: " << durata << ", "
             << "capsuleNumber: " << capsuleNumber
             << ")";

    }

    inline void toStringInfo() {
        if (incaEsteCapsule()) {
            if (getIsFree())
                cout << "Masina este libera" << endl;
            else
                cout << "Masina este ocupata pentru inca "
                     << durata.getMinuteAsString()
                     << ":"
                     << durata.getSecondAsString()
                     << endl;
            return;
        }
        cout << "Masina este neutilizabila! Nu mai are capsule!" << endl;
    }

    friend ostream &operator<<(ostream &os, MasinaSpalat masinaSpalat);


    inline void actualizeazaTimpulMasinii(Durata durata);

    inline bool ATerminat();

    inline void schimbaDacaATerminat();

};

ostream &operator<<(ostream &os, MasinaSpalat masinaSpalat) {
    masinaSpalat.toStringInfo();
    return os;
}

void MasinaSpalat::actualizeazaTimpulMasinii(Durata durata) {
    this->durata = this->durata - durata;
    schimbaDacaATerminat();

}

inline bool MasinaSpalat::ATerminat() {
    return this->durata.getMinute() == 0 && this->durata.getSecond() == 0;
}

inline void MasinaSpalat::schimbaDacaATerminat() {
    if (ATerminat())
        setIsFree(true);

}


class Spalatorie {
private:
    int count;
    MasinaSpalat masini[5];

public:

    inline Spalatorie(int count, const MasinaSpalat masini[]) : count(count) {
        setMasini(masini);
    }


    inline void setCount(int value) {
        this->count = value;
    }

    inline void setMasini(const MasinaSpalat masini[]) {
        for (int i = 0; i < count; i++)
            this->masini[i] = masini[i];
    }

    inline int getCount() { return count; }

    inline MasinaSpalat *getMasini() { return masini; }


    inline void addMasini(MasinaSpalat masini[]) {
        int j = checkIfWeOverflowing();

        for (int i = 0; i < len(masini); i++) {
            this->masini[j++] = masini[i];
            if (j >= N) {
                cout << 'Overflow error when adding to the array' << endl;
                exit(0);
            }
        }
    }

    inline void addMasina(MasinaSpalat masina) {

        int n = checkIfWeOverflowing();
        this->masini[n++] = masina;
    }

    inline void adaugaJob(int index, Durata durata) {
        if (index >= count)termina();
        auto masina = this->masini[index];
        masina.setDurata(durata);
        masina.setIsFree(false);
        masina.decreaseCapsuleNumber(index);
        this->masini[index] = masina;
    }

    inline int checkIfWeOverflowing() {
        unsigned int n = len(masini);
        if (n >= N) termina();
        return n;
    }

    void listeazaMasini() {
        cout << "Spalatoria in prezent:" << endl;
        for (int i = 0; i < this->count; ++i)
            cout << i << ". " << masini[i];
    }

    void actualizeazaTimp(Durata durata) {
        for (int i = 0; i < this->count; ++i)
            masini[i].actualizeazaTimpulMasinii(durata);
    }

    void termina() {
        cout << 'Overflow error' << endl;
        ::exit(0);
    }

    void toString() {
        cout << "Spalatorie(count: " << count << ", "
             << "masini length: " << len(masini)
             << ")";

    }

    ostream &operator()(ostream &os, const Spalatorie &durata);

};

void listeazaMasiniLibere(Spalatorie spalatorie) {
    string res = "Urmatoarele masini sunt libere:";
    MasinaSpalat *masini = spalatorie.getMasini();
    bool isThereFreeMasina = false;
    for (int i = 0; i < spalatorie.getCount(); ++i) {
        if ((*(masini + i)).getIsFree()) {
            res += " ";
            res += to_string(i);
            isThereFreeMasina = true;
        }

    }
    if (isThereFreeMasina)
        cout << res << endl;

};

int main() {
//    Durata durata(12, 33);
//    Durata durata2(43, 15);
////    durata2.toString();
//    MasinaSpalat masinaSpalat(false, durata, 3);
//    MasinaSpalat masinaSpalat2(true, durata2, 5);

//    cout << endl;

//    MasinaSpalat masini[] = {masinaSpalat, masinaSpalat2};
//    Spalatorie spalatorie(2, masini);
//    spalatorie.listeazaMasini();
//    listeazaMasiniLibere(spalatorie);
    MasinaSpalat masini[5] = {
            MasinaSpalat(true, Durata(0, 0), 3),
            MasinaSpalat(true, Durata(0, 0), 2),
            MasinaSpalat(true, Durata(0, 0), 5),
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
