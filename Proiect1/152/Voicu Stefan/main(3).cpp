// voicu stefan grupa 152 proiect 1 lab poo
#include <iostream>
#include <set>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;
class Comanda{
private:

    int durata, id;
    string nume, telefon;
public:
    int getDurata() const {
        return durata;
    }
    int getId() const {
        return id;
    }
    Comanda(string _nume, string _telefon, int _durata, int _id) {
        durata = _durata;
        id = _id;
        telefon = _telefon;
        nume = _nume;
    }
    void setDurata(int _durata) {
        durata = _durata;
    }
};

class classcomp {
public:
  bool operator() (const Comanda& lhs, const Comanda& rhs) {
    return lhs.getId() < rhs.getId();
  }
};


class ListaDeAsteptare{
private:
    set<Comanda, classcomp> comenzi;
    int idmax;
    int timptotal, timpderulat;
public:
    ListaDeAsteptare () {
        idmax = 0;
        timptotal = timpderulat = 0;
    }
    ListaDeAsteptare(int csize, Comanda _comenzi[]) {
        idmax = -1;
        timptotal = timpderulat = 0;
        for (int i = 0; i < csize; i++) {
            comenzi.insert(_comenzi[i]);
            timptotal += _comenzi[i].getDurata();
            if (_comenzi[i].getId() > idmax) {
                idmax = _comenzi[i].getId();
            }
        }
        idmax++;
    }
    ~ListaDeAsteptare() {};
    void adaugaComanda(string _nume, string _telefon) {
        srand(time(NULL));
        int _durata = rand()%3 + 3;
        int _id = idmax;
        idmax++;
        Comanda c(_nume, _telefon, _durata, _id);
        comenzi.insert(c);
        cout << "In " << timptotal << " pregatim comanda dumneavoastra, care va putea fi ridicata in " << timptotal+_durata << " minute" << endl;
        timptotal += _durata;
    }
    void afisareOrdine() {
        set<Comanda>::iterator it;
        cout << "Ordinea comenzilor: ";
        for (it = comenzi.begin(); it != comenzi.end(); it++) {
            cout << (*it).getId() << " ";
        }
        cout << endl;
    }
    void eliminaComanda(int _id) {
        int semafor = 0;
        set<Comanda>::iterator it;
        for (it = comenzi.begin(); it != comenzi.end(); it++) {
            if ((*it).getId() == _id) {
                timptotal -= (*it).getDurata();
                comenzi.erase(it);
                semafor = 1;
                cout << "Comanda " << _id << " a fost eliminata cu succes!" << endl;
                break;
            }
        }
        if (semafor == 0) {
            cout << "Nu exista aceasta comanda" << endl;
        }
    }
    void adaugaTimp(int _timp) {
        timpderulat += _timp;
        if (timptotal < timpderulat) {
            timpderulat -= _timp;
            cout << "Nu puteti derula cu mai mult de " << timptotal - timpderulat << " minute, deoarece depaseste timpul total" << endl;
            return;
        }
        cout << "Timp de " << _timp << " minute, lista va avea urmatoarele modificari:" << endl;

        for (set<Comanda>::iterator it = comenzi.begin(); it != comenzi.end(); it++) {
            if ((*it).getDurata() == 0) {
                continue;
            }
            if ((*it).getDurata() <= _timp) {
                _timp -= (*it).getDurata();
                const Comanda & cmd = *it;
                (const_cast<Comanda*>(&cmd))->setDurata(0); //este ok sa modificam durata deoarece nu modificam id (cheia de sortare). am pacalit putin cpp-ul
                cout << "Comanda cu id-ul " << (*it).getId() << " poate fi ridicata acum." << endl;
                if (_timp == 0) {
                    break;
                }
            } else {
                const Comanda & cmd = *it;
                (const_cast<Comanda*>(&cmd))->setDurata((*it).getDurata() - _timp);
                cout << "Comanda cu id-ul " << (*it).getId() << " este in curs de pregatire si va fi gata in " << (*it).getDurata() << " minute." << endl;
                break;
            }
        }
    }
};

int main()
{
    // 1. crearea unei instanta a listei de asteptare
   // Putem fie sa adaugam cateva comenzi
   Comanda comenzi[] = {
           Comanda("Stefanescu", "0733222744", 3, 3),
           Comanda("Mihailescu", "0752222745", 4, 4),
           Comanda("Popescu", "0799222746", 3, 6)
   };

   ListaDeAsteptare lista(3, comenzi); // totalComenzi, adica id-ul unic al urmatoarei comenzi,
   // il vom putea gasi in constructor ca fiind maximul+1  dintre id-urile fiecarei comande (max(3,4,6)=6 => totalComenzi=6+1=7)

   // sau putem sa folosim constructorul default, iar numarComenzi si totalComenzi vor incepe de la 0:

   // 2 Adaugarea unei noi comenzi

   lista.adaugaComanda("Prastie",
                       "0786001002"); // idUnic si minutePregatire vor fi generate corespunzator in interiorul clasei

   // 3 Afisarea listei de asteptare cu id-urile comenzilor
   lista.afisareOrdine();

   // 4 Eliminarea unei comenzi,
   lista.eliminaComanda(
           4); // va elimina comanda cu id-ul unic egal cu 4. Daca nu exista, va afisa un mesaj corespunzator.

   lista.eliminaComanda(
           1001); // va elimina comanda cu id-ul unic egal cu 1001. Daca nu exista, va afisa un mesaj corespunzator.

   // 5 O metoda care va permite derularea cu un numar de minute
   lista.adaugaTimp(3);

   // 6 O metoda care va permite derularea cu un numar de minute
   lista.adaugaTimp(10);
   lista.adaugaTimp(3);
   lista.adaugaTimp(1);

    return 0;
}
