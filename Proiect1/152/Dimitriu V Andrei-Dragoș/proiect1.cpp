///Problema 2 din fisier, Lista de asteptare

#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

class Comanda {
private:
    string name, tlf;
    int dur, id;
public:
    Comanda() {
        name = tlf = "";
        dur = id = 0;
    }

    Comanda(string _name, string _tlf, int _dur, int _id) {
        name = _name;
        tlf = _tlf;
        dur = _dur;
        id = _id;
    }

    void setComanda(string _name, string _tlf, int _dur, int _id) {
        name = _name;
        tlf = _tlf;
        dur = _dur;
        id = _id;
    }

    int getID() const {
        return id;
    }

    int getDur() const {
        return dur;
    }

    void setDur(int newDur) {
        dur = newDur;
    }
};

class ListaDeAsteptare {
private:
    Comanda comenzi[1005];
    int cnt;
public:
    ListaDeAsteptare(int k = 0, Comanda _comenzi[] = {}) {
        for(int i = 0; i < k; i++) {
            comenzi[i + 1] = _comenzi[i];
        }
        cnt = k;
    }

    int totalTime() const{
        int minutes =  0;
        for(int i = 1; i <= cnt; i++) {
            minutes += comenzi[i].getDur();
        }
        return minutes;
    }

    int generateID() const {
        int id = 0;
        for(int i = 1; i <= cnt; i++) {
            id = max(id, comenzi[i].getID());
        }
        return id + 1;
    }

    void adaugaComanda(string nume, string tlf) {
        srand(time(NULL));
        int id = generateID(), time = (rand() % 3) + 3, total = totalTime();
        comenzi[++cnt].setComanda(nume, tlf, time, id);
        cout << "Ne vom ocupa de comanda dvs. in " <<  total << " minute, iar aceasta va fi gata in " << time + total<< " minute" << '\n';
    }

    void afisareOrdine() {
        cout << "Comenzile in ordine sunt: ";
        for(int i = 1; i <= cnt; i++) {
            cout << comenzi[i].getID() << " ";
        }
        cout << '\n';
    }

    void eliminaComanda(int id) {
        int poz = -1;
        for(int i = 1; i <= cnt; i++) {
            if(comenzi[i].getID() == id) {
                poz = i;
                break;
            }
        }

        if(poz == -1) {
            cout << "Nu exista comanda " << id << '\n';
            afisareOrdine();
        }
        else {
            for(int i = poz; i < cnt; i++) {
                comenzi[i] = comenzi[i + 1];
            }
            cnt--;
            afisareOrdine();
        }
    }

    void eliminaComanda(int inc, int sf) {
        if(inc > sf)
            return;
        for(int i = inc; i < cnt; i++) {
            comenzi[i] = comenzi[i + sf - inc + 1];
        }
        cnt -= (sf - inc + 1);
    }

    void adaugaTimp(int minutes) {
        if(minutes > totalTime()) {
            cout << "Nu puteti derula cu " << minutes << " minute, deoarece timpul total este de "
            << totalTime() << '\n';
            return ;
        }
        int ct = 0, poz = 1;
        while(minutes != 0) {
            int min_crt = comenzi[poz].getDur();
            if(minutes >= min_crt) {
                cout << "Comanda " << comenzi[poz].getID() << " a fost ridicata" << '\n';
                ct++;
                minutes -= min_crt;
                poz++;
            }
            else {
                comenzi[poz].setDur(min_crt - minutes);
                minutes = 0;
            }
        }

        eliminaComanda(1, ct);
    }
};

int main() {
    Comanda comenzi[100] = {
            Comanda("Stefanescu", "0733222744", 3, 3),
            Comanda("Mihailescu", "0752222745", 4, 4),
            Comanda("Popescu", "0799222746", 3, 6)
    };
    ListaDeAsteptare lista(3, comenzi);
    ListaDeAsteptare lista2;
    lista.adaugaComanda("Prastie",
                        "0786001002");

    lista.afisareOrdine();
    lista.eliminaComanda(4);
    lista.eliminaComanda(1001);
    lista.adaugaTimp(10);
    lista.adaugaTimp(3);
    lista.adaugaTimp(1);

    return 0;

}