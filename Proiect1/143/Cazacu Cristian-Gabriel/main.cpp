#include <iostream>

class Durata{
    int start, fin;

public:
    Durata(){
        start=0; fin=0;
    }

    Durata(int start,int fin){
        this->start = start;
        this->fin = fin;
    }

    void printTime(){
        if(fin >= 10)
            std::cout<<start<<":"<<fin;
        else
            std::cout<<start<<":0"<<fin;
    }

    void updateTime(Durata);

    bool operator==(Durata);
};
bool Durata::operator==(Durata d) {
    if (this-> start == d.start && this-> fin == d.fin)
        return true;

        return false;
}

void Durata::updateTime(Durata d) {
    int time1 = start * 60 + fin;
    int time2 = d.start * 60 + d.fin;
    time1-=time2;
    if(time1>0) {
        start = time1 / 60;
        fin = time1 % 60;
    }
    else
    {
        start = 0;
        fin = 0;
    }

}

class Masina{
    bool status;
    Durata time;
    int capNr;

public:
    Masina(){
        status = true; time = Durata(0,0); capNr=0;
    }

    Masina(bool status,Durata time,int capNr){
        this->status = status; this->time=time; this->capNr=capNr;
    }

    bool getStatus();

    int getCapsules();

    Durata getTime();

    Durata setTime(Durata);

    int decrCap();

    void setStatus(bool);


};

bool Masina::getStatus() {
    return status;
}

int Masina::getCapsules() {
    return capNr;
}

Durata Masina::getTime() {
    return time;
}

Durata Masina::setTime(Durata d) {
    time = d;
}

int Masina::decrCap() {
    capNr--;
}

void Masina::setStatus(bool status) {
    this->status = status;
}

class spalatorie{
    int num; Masina v[50];
public:
    spalatorie() = default;

    spalatorie(int num,Masina *v){
        this->num=num;
        for(int i=0;i<num;++i) {
            this->v[i] = v[i];
        }
    }


    int getNum();

    void listeazaMasini();

    void adaugaJob(int,Durata);

    void actualizeazaTimp(Durata);

    friend void listeazaMasiniLibere(spalatorie);

};

int spalatorie::getNum() {
    return num;
}

void spalatorie::adaugaJob(int index, Durata d) {
    if(v[index].getCapsules()>0) {
        v[index].setTime(d);
        v[index].decrCap();
        v[index].setStatus(false);
    }
    else
        std::cout<<"Masina "<<index<<" nu mai are capsule"<<std::endl;
}

void spalatorie::listeazaMasini() {

    std::cout<<"Spalatoria in prezent: \n";
    for(int i=0;i<num;++i)
        if(v[i].getStatus() == true)
            if(v[i].getCapsules()>0)
                std::cout<<i<<". Masina este libera"<<std::endl;
            else
                std::cout<<i<<". Masina este neutilizabila! Nu mai are capsule!"<<std::endl;
        else
        {
            std::cout<<i<<". Masina este ocupata pentru inca ";
            v[i].getTime().printTime();
            std::cout<<std::endl;
        }

}

void spalatorie::actualizeazaTimp(Durata d) {
    for (int i = 0;i < num; ++i)
        if(v[i].getStatus()==false)
        {
            Durata aux = v[i].getTime();
            aux.updateTime(d);
            v[i].setTime(aux);

            if(aux == Durata(0,0))
                v[i].setStatus(true);
        }
}

void listeazaMasiniLibere(spalatorie spalatorie) {
    std::cout<<"Urmatoarele masini sunt libere: ";
    for (int i = 0; i< spalatorie.num ;++i)
        if (spalatorie.v[i].getStatus() == true)
            std::cout<<i<<" ";
    std::cout<<std::endl;
}

int main() {

    Masina masini[5] = {
            Masina(true, Durata(0, 0), 3),
            Masina(true, Durata(0, 0), 2),
            Masina(true, Durata(0, 0), 5),
    };
    spalatorie spalatorie(
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
