#include <iostream>
#include <vector>
#include <random>

using namespace std;
class Comanda{
private:
    string nume, nrtel;
    int durata, id;
public:
    Comanda(string _nume, string _nrtel, int _durata, int _id){
        nume=_nume;
        nrtel=_nrtel;
        durata= _durata;
        id=_id;
    }
    Comanda(string _nume, string _nrtel) {
        nume=_nume;
        nrtel=_nrtel;
        durata= rand() % 3+3;
        id=0;
        //cout<<durata<<endl<<endl;
    }

    void setId(int id) {
        Comanda::id = id;
    }

    const string &getNume() const {
        return nume;
    }

    const string &getNrtel() const {
        return nrtel;
    }

    int getId() const {
        return id;
    }
    int getDurata() const {
        return durata;
    }

    Comanda() {

    }
};
class ListaDeAsteptare{
private:
    vector<Comanda> lista;
    int timp;
public:
    ListaDeAsteptare(int n, Comanda _lista[100]) {
        for (int i=0;i<n;i++) {
            lista.push_back(_lista[i]);
        }
        timp=0;
    }
    ListaDeAsteptare() {
        timp=0;
    }
    void adaugaComanda(string _nume, string _nrtel) {
        Comanda c= Comanda(_nume, _nrtel);
        c.setId(lista[lista.size()-1].getId()+1);
        lista.push_back(c);
    }
    void afisareOrdine() {
        cout<<"Ordinea comenzilor:";
        for (int i=0;i<lista.size();i++) {
            cout<<lista[i].getId()<<" ";
        }
        cout<<endl;
    }
    void eliminaComanda(int _id) {
        int st=0;
        for (int i=0;i<lista.size();i++) {
            if (lista[i].getId()==_id) {
                lista.erase(lista.begin()+i);
                st=1;
            }
        }
        if (st==0) {
            cout<<"Nu exista aceasta comanda."<<endl<<"Comenzile existente: ";
            afisareOrdine();
        }
        else {
            cout<<"Comanda "<<_id<<" a fost eliminata cu succes.\n";
        }
    }
    void adaugaTimp(int _timp) {
        int ttotal=0;
        timp+=_timp;
        for (int i=0;i<lista.size();i++) {
            ttotal+=lista[i].getDurata();
        }
        if (ttotal<timp) {
            cout<<"Nu puteti derula cu mai mult de "<<ttotal<<" minute, deoarece depaseste timpul total!Timp de "<<timp-ttotal<<" minute\n";
            timp-=_timp;
        }
        else{
            cout<<"Timp de "<< _timp <<" minute, lista are urmatoarele modificari:\n";
            int l=lista.size();
            while (timp>=lista.front().getDurata()) {
                cout<<"Comanda cu id-ul "<< lista.front().getId() <<" poate fi ridicata chiar acum!\n";
                timp-=lista.front().getDurata();
                lista.erase(lista.begin());
            }
            if (l==lista.size()) {
                cout<<"Comanda cu id-ul "<< lista.front().getId()<< " este in curs de pregatire si va fi gata in "<<lista.front().getDurata()-timp<<" minute!\n";
            }
        }
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
    lista.adaugaComanda("Prastie","0786001002");
    lista.afisareOrdine();
    lista.eliminaComanda(4);
    lista.eliminaComanda(1001);
    lista.adaugaTimp(3);
    lista.adaugaTimp(10);
    lista.adaugaTimp(3);
    lista.adaugaTimp(1);

    return 0;
}
