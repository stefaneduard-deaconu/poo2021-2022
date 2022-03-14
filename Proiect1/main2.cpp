#include <iostream>
#include <string>

using namespace std;

class Comanda {
private:
    string numeClient, numarTelefon;
    int minutePregatire;
    int idUnic;
public:
    Comanda() : minutePregatire(0), idUnic(0) {

    }

    Comanda(const string &numeClient, const string &numarTelefon, int minutePregatire, int idUnic) : numeClient(
            numeClient), numarTelefon(numarTelefon), minutePregatire(minutePregatire), idUnic(idUnic) {}

    // getters
    int getIdUnic() const {
        return idUnic;
    }

    int getMinutePregatire() const {
        return minutePregatire;
    }

    // setters
    void setMinutePregatire(int minutePregatire) {
        Comanda::minutePregatire = minutePregatire;
    }
};

class ListaDeAsteptare {
private:
    int numarComenzi;
    Comanda comenzi[100];
    int totalComenzi;
public:
    ListaDeAsteptare() : numarComenzi(0), totalComenzi(0) {
        srand(NULL);
    }

    ListaDeAsteptare(int numarComenzi, Comanda *_comenzi) : numarComenzi(numarComenzi),
                                                            totalComenzi(totalComenzi) {
        srand(NULL);

        int maxim = 0;

        for (int i = 0; i < numarComenzi; ++i) {
            comenzi[i] = _comenzi[i];
            if (comenzi[i].getIdUnic() > maxim) {
                maxim = comenzi[i].getIdUnic();
            }
        }

        totalComenzi = maxim + 1;
    }

    int timpCurentAsteptare() {
        int timp = 0;
        for (int i = 0; i < numarComenzi; ++i) {
            timp += comenzi[i].getMinutePregatire();
        }
        return timp;
    }

    void adaugaComanda(string numeClient, string numarClient) {

        int timpAsteptare = timpCurentAsteptare();
        int timpPregatire = rand() % 3 + 3;

        // creare comanda
        Comanda c(numeClient, numarClient, timpPregatire, totalComenzi + 1);
        totalComenzi++;

        // retinerea comenzii in lista:
        comenzi[numarComenzi++] = c;

        cout << "In " << timpAsteptare << " minute pregatim comanda dumneavoastra, care va putea fi ridicata peste "
             << timpAsteptare + timpPregatire << " minute." << '\n';
    }

    void afisareOrdine() {
        cout << "Ordinea comenzilor: ";
        for (int i = 0; i < numarComenzi; ++i) {
            cout << comenzi[i].getIdUnic() << ' ';
        }
        cout << '\n';
    }

    void removeAt(int i) {
        for (int j = i; j < numarComenzi - 1; ++j) {
            comenzi[j] = comenzi[j + 1];
        }
        numarComenzi--;
    }

    void eliminaComanda(int idUnic) {
        int i;
        for (i = 0; i < numarComenzi; ++i) {
            if (comenzi[i].getIdUnic() == idUnic) {
                removeAt(i);
                break;
            }
        }
        if (i == numarComenzi) {
//            didn't break'
            cout << "Nu exista aceasta comanda." << '\n';
            cout << "Comenzile existente: ";
            afisareOrdine();
        } else {
            cout << "Comanda " << idUnic << " a fost eliminata cu succes." << '\n';
        }
    }

    void adaugaTimp(int minute) {
        if (minute > timpCurentAsteptare()) {
            cout << "Nu puteti derula cu mai mult de " << timpCurentAsteptare()
                 << " minute, deoarece depaseste timpul total!";\

        } else {
            cout << "\nTimp de " << minute << " minute, lista are urmatoarele modificari:" << '\n';
            while (minute > 0) {
                // eliminam inca o comanda, si updatam numarul de minute
                if (comenzi[0].getMinutePregatire() <= minute) {
                    minute -= comenzi[0].getMinutePregatire();
                    cout << "Comanda cu id-ul " << comenzi[0].getIdUnic() << " poate fi ridicata chiar acum!" << '\n';
                    removeAt(0);
                } else {
                    cout << "Comanda cu id-ul " << comenzi[0].getIdUnic() << " este in curs de pregatire si va fi gata in ";
                    comenzi[0].setMinutePregatire(
                            comenzi[0].getMinutePregatire() - minute
                    );
                    cout << comenzi[0].getMinutePregatire() << " minute!" << '\n';
                    minute = 0;
                }
            }
        }
    }
};

int main() {
    // 1. crearea unei instanta a listei de asteptare
    // Putem fie sa adaugam cateva comenzi
    Comanda comenzi[100] = {
            Comanda("Stefanescu", "0733222744", 3, 3),
            Comanda("Mihailescu", "0752222745", 4, 4),
            Comanda("Popescu", "0799222746", 3, 6)
    };

    ListaDeAsteptare lista(3, comenzi); // totalComenzi, adica id-ul unic al urmatoarei comenzi,
    // il vom putea gasi in constructor ca fiind maximul+1  dintre id-urile fiecarei comande (max(3,4,6)=6 => totalComenzi=6+1=7)

    // sau putem sa folosim constructorul default, iar numarComenzi si totalComenzi vor incepe de la 0:
    ListaDeAsteptare lista2;

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
}

/*
 In 10 minute ne vom putea ocupa de comanda dumneavoastra, care va putea fi ridicata in 13 minute
Ordinea comenzilor:3 4 6 7
Comanda cu Id-ul unic 6 a fost eliminata cu succes
Comenzile existente: 3 6 7
Nu exista aceasta comanda
Comenzile existente: 3 6 7
Nu puteti derula cu mai mult de 9 minute, deoarece depaseste timpul total!Timp de1minute

 */