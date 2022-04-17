#include <iostream>

using namespace std;

class Durata{
private:
    int minute = 0;
    int secunde = 0;
public:
    Durata(){
        minute = 0;
        secunde = 0;
    }

    Durata(int _minute, int _secunde){
        if(_minute >= 0) minute = _minute;
        else minute = 0;

        if(_secunde >= 0) secunde = _secunde;
        else secunde = 0;

        if(secunde >= 60){
            minute += secunde/60;
            secunde = secunde %60;
        }
    }
    int getMinute() const{
        return minute;
    }
    int getSecunde() const{
        return secunde;
    }

    void setMinute(int _min){
        if(_min >= 0) minute = _min;
        else cout<< "Nu poti avea un numar negativ de minute";
    }

    void setSecunde(int _sec){
        if(_sec >= 0) secunde = _sec;
        else cout<< "Nu poti avea un numar negativ de secunde";
    }

    int toSeconds() const{
        return minute*60 + secunde;
    }


};

class MasinaSpalat{
private:
    bool libera ;
    Durata timpRamas;
    int capsule;
public:
    MasinaSpalat( ){
        libera = true;
        timpRamas = Durata(0,0);
        capsule = 0;
    }

    MasinaSpalat( bool _libera, Durata _timpRamas, int _capsule){
        libera = _libera;
        timpRamas = _timpRamas;
        capsule = _capsule;
    }

    void actualizareTimp(Durata timp){
        if(timpRamas.toSeconds() > timp.toSeconds()){
                if(timpRamas.getSecunde() >= timp.getSecunde() ){
                    timpRamas.setSecunde( timpRamas.getSecunde() - timp.getSecunde() );
                    timpRamas.setMinute(timpRamas.getMinute() - timp.getMinute() );
                }else{
                    timpRamas.setSecunde( 60 + timpRamas.getSecunde() - timp.getSecunde() );
                    timpRamas.setMinute(timpRamas.getMinute() - timp.getMinute() - 1);
                }
        }else{
            timpRamas.setSecunde(0);
            timpRamas.setMinute(0);
            libera = true;
        }

    }

    bool isLibera() const {
        return libera;
    }

    int getCapsule() const{
        return capsule;
    }

    Durata getTimpRamas(){
        return timpRamas;
    }

    void setTimpRamas( Durata _durata){
        timpRamas = _durata;
    }

    void setLibera(bool status){
        libera = status;
    }

    void setCapsule(int cap){
        if(cap >= 0) capsule = cap;
        else cout<< "Nu poti avea un numar negativ de capsule";
    }


    void addCapsule(int capsule_extra){
        if(capsule_extra >= 0)
            capsule+= capsule_extra;
    }
    void consumaCapsula(){
        capsule--;
    }


};


class Spalatorie{
private:
    int numarMasini;
    MasinaSpalat *masini;
public:
    Spalatorie(int _numarMasini, MasinaSpalat _masini[]){
        numarMasini = _numarMasini;
        masini = _masini;
    }

    void listeazaMasini(){
        if(numarMasini == 0){
            cout<<"Deocamdata nu sunt masini in aceasta spalatorie.\n";
        }
        else{
            cout<<"Spalatoria in prezent: \n";
                for(int i=0; i<numarMasini;i++){
                    if(masini[i].getCapsule() == 0){
                        cout<<"Masina "<<i<<" este neutilizabila, nu mai are capsule.\n";
                    }else{
                        if(masini[i].isLibera()){
                            cout<<"Masina "<<i<<" este libera. Aceasta mai are "<<masini[i].getCapsule()<<" capsule.\n";
                        }else{
                            if(masini[i].getTimpRamas().getSecunde() >9)
                            cout<<"Masina "<<i<<" este ocupata pentru inca "<<masini[i].getTimpRamas().getMinute()<<":"<<masini[i].getTimpRamas().getSecunde()<<".\n";
                            else{
                                cout<<"Masina "<<i<<" este ocupata pentru inca "<<masini[i].getTimpRamas().getMinute()<<":0"<<masini[i].getTimpRamas().getSecunde()<<".\n";
                            }
                        }
                    }
                }
            }

    }

    int getNumarMasini() const{
        return numarMasini;
    }
    MasinaSpalat* getMasini(){
        return masini;
    }

    void adaugaJob(int masina, Durata durata){
        if(masini[masina].getCapsule() == 0){
            cout<<"Masina "<<masina<<" nu mai are capsule! Adaugati capsule sau incercati alta masina de spalat.\n";
        }else{

            if(!masini[masina].isLibera())cout << "Aceasta masina nu este libera!\n";
            else{
                masini[masina].consumaCapsula();
                masini[masina].setTimpRamas(durata);
                masini[masina].setLibera(false);
            }


        }
    }

    void actualizeazaTimp(Durata timp){
        for(int i = 0; i< numarMasini;i++){
            masini[i].actualizareTimp(timp);
        }

    }


};

void listeazaMasiniLibere( Spalatorie spalatorie){
    int nrLibere = 0;
    int libere[5];

    for(int i=0; i< spalatorie.getNumarMasini();i++){
        if(spalatorie.getMasini()->isLibera() == true){
            libere[nrLibere] = i;
            nrLibere++;
        }
    }
    if(nrLibere == 0) cout<< "Nu sunt masini libere la aceasta spalatorie\n";
    else{
        cout<<"Urmatoarele masini sunt libere:";
        for(int i=0; i<nrLibere;i++) cout<<" "<< libere[i];
        cout<<".\n";
    }

}


int main() {
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
