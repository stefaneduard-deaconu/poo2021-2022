#include <iostream>
#include <vector>

using namespace std;

class Durata
{
private:
    int minute, secunde;
public:
    Durata()
    {

    }
    Durata(int m, int s)
    {
        minute = m;
        secunde = s;
    }
    Durata(Durata &durata)
    {
        this->minute = durata.minute;
        this->secunde = durata.secunde;
    }
    void setMinute(int _minute)
    {
        minute = _minute;
    }
    void setSecunde(int _secunde)
    {
        secunde = _secunde;
    }
    int getMinute()
    {
        return minute;
    }
    int getSecunde()
    {
        return secunde;
    }

    friend ostream &operator<<(ostream &os, const Durata &durata) {
        os << durata.minute << ":" << durata.secunde;
        return os;
    }
};

class Masina
{
private:
    bool stare;
    Durata durata;
    int capsule;
public:
    Masina()
    {

    }
    Masina(bool stare, Durata durata, int capsule)
    {
        this->stare = stare;
        this->capsule = capsule;
        this->durata = durata;
    }

    Masina(Masina &masina)
    {
        this->stare = masina.stare;
        this->capsule = masina.capsule;
        this->durata = masina.durata;
    }

    void setStare(bool stare)
    {
        this->stare = stare;
    }
    void setCapsule(int capsule)
    {
        this->capsule = capsule;
    }


    void setDurata(const Durata &durata) {
        Masina::durata = durata;
    }

    bool getStare()
    {
        return stare;
    }
    int getCapsule()
    {
        return capsule;
    }

    Durata &getDurata(){
        return durata;
    }
};

class Spalatorie
{
private:
    int numarMasini;
    vector<Masina> masini;
public:
    Spalatorie(){

    }
    Spalatorie(int numarMasini, vector<Masina> masini)
    {
        this->numarMasini = numarMasini;
        this->masini = masini;
    }
    void listeazaMasini()
    {
        int k = 0;
        for (auto i : masini)
        {
            cout << k << ". ";
            if(i.getCapsule() <= 0)
            {
                cout << "Masina este neutilizabila! Nu mai are capsule!";
            } else if (i.getDurata().getMinute() != 0 || i.getDurata().getSecunde() != 0)
            {
                cout << "Masina este ocupata pentru inca " << i.getDurata();
            } else
            {
                cout << "Masina este libera";
            }
            cout << "\n";
            k++;
        }
    }

    vector<Masina> &getMasini(){
        return masini;
    }

    void adaugaJob(int poz, Durata durata)
    {
        Durata durata69 = masini[poz].getDurata();
        int totalSecunde;
        totalSecunde = durata.getMinute() * 60 + durata.getSecunde() + durata69.getMinute() * 60 + durata69.getSecunde();
        masini[poz].setDurata(Durata(totalSecunde / 60, totalSecunde - (totalSecunde / 60) * 60));
    }
    void actualizeazaTimp(Durata durata)
    {
        for (auto i : masini)
        {
            Durata durata69 = i.getDurata();
            int totalSecunde = - durata.getMinute() * 60 - durata.getSecunde() + durata69.getMinute() * 60 + durata69.getSecunde();
            if (totalSecunde <= 0)
            {
                i.setDurata(Durata(0, 0));
            } else
            {
                i.setDurata(Durata(totalSecunde / 60, totalSecunde - (totalSecunde / 60) * 60));
            }

        }
    }
};


void listeazaMasiniLibere(Spalatorie spalatorie)
{
    vector<Masina> masini;
    masini = spalatorie.getMasini();
    int k = 0;
    cout << "Urmatoarele masini sunt libere: ";
    for (auto i : masini)
    {
        if (i.getCapsule() != 0 && (i.getDurata().getMinute() == 0 && i.getDurata().getSecunde() == 0))
        {
            cout << k;
        }
    }
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
