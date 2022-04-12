#include <random>
#include <iostream>
using namespace std;
//aici ne facem functia de random//
int randomnumber(){
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist6(3,5);
    return dist6(rng);
}
//aici de cream clasa Comanda//
class Comanda{
    string numePers;
    string numartel;
    int nrcomanda;
    int id;
public:
    //constructori//
    Comanda(){}
    Comanda(string numePers_, string numartel_, int nrcomanda_, int id_){
        numePers=numePers_;
        numartel=numartel_;
        nrcomanda=nrcomanda_;
        id=id_;
    }
    //getteri si setteri//
    string getNumePers(){
        return numePers;
    }
    void setNumePers(string numePers_) {
        numePers = numePers_;
    }
    string getNumartlf(){
        return numartel;
    }
    void setNumartlf(string numartel_) {
        numartel = numartel_;
    }
    int getNrcomanda(){
        return nrcomanda;
    }
    void setNrcomanda(int nrcomanda_) {
        nrcomanda = nrcomanda_;
    }
    int getId(){
        return id;
    }
    void setId(int id_) {
        id = id_;
    }
};
//1.aici ne cream clasa cu lista de asteptare//
class ListaDeAsteptare{
    int numarTotal;
    Comanda comenzi[101];
public:
    //constructori//
    ListaDeAsteptare(){}

    ListaDeAsteptare(int numarTotal_, Comanda comenzi_[]){
        numarTotal=numarTotal_;
        for(int i=0; i<numarTotal_; i++)
            comenzi[i]=comenzi_[i];
    }
    //2.metoda de afisare in ordine a comenzilor//
    void afisareOrdine(){
        cout<<"Ordinea comenzilor:";
        for(int i=0; i<numarTotal; i++)
            cout<<comenzi[i].getId()<<" ";
        cout<<"\n";
    }
    //3.metoda de adaugare a unei noi comenzi//
    void adaugaComanda(string nume, string numar){
        int timp=0,nr1,suma=0,Max=0;
        timp=randomnumber();
        cout<<"timp random: " << timp << endl;
        for(int i=0; i<numarTotal; i++) {
            suma = suma + comenzi[i].getNrcomanda();
            if (comenzi[i].getId()>Max)
                Max=comenzi[i].getId();
        }
        nr1=Max+1;
        Max++;
        Comanda temp(nume, numar,timp,nr1);
        comenzi[numarTotal]=temp;
        numarTotal++;
        cout<<"In "<<suma<<" minute ne vom putea ocupa de comanda dumneavoastra, care va putea fi ridicata in "<<suma+timp<<" minute\n";
    }
    //4.metoda de eliminare a unei comenzi si afisarea comenzilor ramase in ordine,
    // iar in cazul in care nu exista comanda vom afisa un mesaj//
    void eliminaComanda(int nr_id){
        int ok=0,poz=0, id1;
        for(int i=0; i<numarTotal-1; i++) {
            if (comenzi[i].getId() == nr_id) {
                ok=1;
                poz=i;
                id1=comenzi[poz].getId();
                for (int j = i; j < numarTotal - 1; j++)
                    comenzi[j] = comenzi[j + 1];
                numarTotal--;
            }
        }
        if(ok==1)
            cout<<"Comanda cu Id-ul unic "<<id1<<" a fost eliminata cu succes";
        else
            cout<<"Nu exista aceasta comanda";
        cout<<"\n";

        cout << "Comenzile existente: ";
        for (int i = 0; i < numarTotal; i++)
            cout << comenzi[i].getId() << " ";
        cout<<"\n";
    }
    //5.metoda care va permite derularea cu un numar de minute//
    void adaugaTimp(int timp_derulare){
        int i=0,suma=0;
        for(int i=0; i<numarTotal; i++)
            suma=suma+comenzi[i].getNrcomanda();
        if(timp_derulare<=suma){
        while(timp_derulare>comenzi[i].getNrcomanda()) {
            cout << "Comanda cu id-ul " << comenzi[i].getId() << " este in curs de pregatire si va fi gata in "<< comenzi[0].getNrcomanda() << " minute\n";
            if(timp_derulare<comenzi[i].getNrcomanda())
                cout<<"Comanda cu id-ul "<<comenzi[0].getId()<<" este in curs de pregatire si va fi gata in "<<comenzi[0].getNrcomanda()<<" minute!\n";
            timp_derulare = timp_derulare - comenzi[i].getNrcomanda();
            i++;
        }
        }
        else
               cout<<"Nu puteti derula cu mai mult de "<<suma<<" minute, deoarece depaseste timpul total! Timp de " <<timp_derulare-suma<< " minute\n";
    }
};
int main() {
    Comanda comenzi[100] = {
            Comanda("Stefanescu", "0733222744", 3, 3),
            Comanda("Mihailescu", "0752222745", 4, 4),
            Comanda("Popescu", "0799222746", 3, 6)
    };
    ListaDeAsteptare lista(3, comenzi);

    lista.adaugaComanda("Prastie", "0786001002");

    lista.afisareOrdine();

    lista.eliminaComanda(4);

    lista.eliminaComanda(1001);

    lista.adaugaTimp(10);

    lista.adaugaTimp(3);

    lista.adaugaTimp(1);
}

